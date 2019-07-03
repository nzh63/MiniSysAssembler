/*
 * Copyright 2019 nzh63
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "pch.h"

int doAssemble(const std::string &input_file_path,
               const std::string &output_folder_path) {
    std::fstream file;
    file.open(input_file_path, std::ios_base::in);
    InstructionList instruction_list;
    DataList data_list;
    int line = 0;
    enum { global, data, text };
    int state = global;
    while (!file.eof()) {
        line++;
        std::string input;
        getline(file, input);
        std::regex re(R"(^\s*\.(data|text))", std::regex::icase);
        std::cmatch m;
        std::regex_search(input.c_str(), m, re);
        if (!m.empty()) {
            state = (toUppercase(m[1].str()) == "DATA") ? data : text;
            continue;
        }
        if (state == global) {
            throw std::runtime_error("Need a segment.");
        } else if (state == text) {
            Instruction instruction;
            instruction.file = input_file_path;
            instruction.line = line;
            instruction.assembly = input;
            instruction_list.push_back(instruction);
        } else if (state == data) {
            Data instruction;
            instruction.file = input_file_path;
            instruction.line = line;
            instruction.assembly = input;
            data_list.push_back(instruction);
        }
    }
    file.close();

    UnsolvedSymbolMap unsolved_symbol_map;
    SymbolMap symbol_map;
    if (GeneratedDataSegment(data_list, unsolved_symbol_map, symbol_map)) {
        Debug("Error occurs, exiting.");
        return 1;
    }
    if (GeneratedMachineCode(instruction_list, unsolved_symbol_map,
                             symbol_map)) {
        Debug("Error occurs, exiting.");
        return 1;
    }
    if (SolveSymbol(unsolved_symbol_map, symbol_map)) {
        Debug("Error occurs, exiting.");
        return 1;
    }

    file.open(output_folder_path + "prgmip32.coe", std::ios_base::out);
    if (file.is_open()) {
        OutputInstruction(file, instruction_list);
    }
    file.close();

    file.open(output_folder_path + "dmem32.coe", std::ios_base::out);
    if (file.is_open()) {
        OutputDataSegment(file, data_list);
    }
    file.close();

    return 0;
}
