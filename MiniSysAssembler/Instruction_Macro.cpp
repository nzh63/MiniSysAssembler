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

std::regex Macro_format_regex("^(mov|push|pop)\\s", std::regex::icase);

MachineCode Macro_FormatInstruction(const std::string& BIT,
                                    const std::string& assembly,
                                    UnsolvedSymbolMap& unsolved_symbol_map,
                                    MachineCodeHandle machine_code_it) {
    std::string op1, op2, op3;
    GetOperand(assembly, op1, op2, op3);
    if (BIT == "MOV") {
        if (!op3.empty()) {
            throw std::runtime_error("Invalid operation (" + BIT + ").");
        } else {
            if (isRegister(op1) && isRegister(op2)) {
                R_FormatInstruction("OR", "OR " + op1 + ", $0, " + op2,
                                    unsolved_symbol_map, machine_code_it);
            } else if (isRegister(op1) && (isNumber(op2) || isSymbol(op2))) {
                bool is_large_num;
                if (isSymbol(op2) || toUNumber(op2) <= 0xffff) {
                    is_large_num = 0;
                } else {
                    is_large_num = 1;
                }
                if (is_large_num) {
                    unsigned number = toUNumber(op2);
                    I_FormatInstruction(
                        "LUI",
                        "LUI " + op1 + ", " + std::to_string(number >> 16),
                        unsolved_symbol_map, machine_code_it);
                    MachineCodeHandle new_handel =
                        NewMachineCode(*cur_instruction);
                    I_FormatInstruction("ORI",
                                        "ORI " + op1 + ", " + op1 + ", " +
                                            std::to_string(number % 0x10000),
                                        unsolved_symbol_map, new_handel);
                    cur_address += 4;
                } else {
                    I_FormatInstruction("ORI", "ORI " + op1 + ", $0, " + op2,
                                        unsolved_symbol_map, machine_code_it);
                }
            }
        }
    }
    return cur_instruction->machine_code.front();
}

bool isMacro_Format(const std::string& assembly) {
    std::cmatch m;
    std::regex_search(assembly.c_str(), m, Macro_format_regex);
    if (!m.empty()) {
        return true;
    } else {
        return false;
    }
}
