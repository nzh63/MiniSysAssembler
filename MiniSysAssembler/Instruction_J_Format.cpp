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

std::regex J_format_regex("^(j|jal)", std::regex::icase);

MachineCode J_FormatInstruction(const std::string& mnemonic,
                                const std::string& assembly,
                                UnsolvedSymbolMap& unsolved_symbol_map,
                                MachineCodeHandle machine_code_it) {
    MachineCode& machine_code = *machine_code_it;
    if (isJ_Format(assembly)) {
        machine_code = 0;
        std::string op1, op2, op3;
        GetOperand(assembly, op1, op2, op3);
        if ((isNumber(op1) || isSymbol(op1)) && op2.empty() && op3.empty()) {
            if (mnemonic == "J") {
                SetOP(machine_code, 0b000010);
            } else {
                SetOP(machine_code, 0b000011);
            }
            if (isNumber(op1)) {
                SetAddress(machine_code, toNumber(op1));
            } else {
                SetAddress(machine_code, 0);  // 标号，使用0占位
                unsolved_symbol_map[op1].push_back(
                    SymbolRef{machine_code_it, cur_instruction});
            }
        } else {
            throw std::runtime_error("Invalid operation (" + mnemonic + ").");
        }
    } else {
        throw std::runtime_error("Unkonw instruction: " + mnemonic + ".");
    }
    return machine_code;
}

bool isJ_Format(MachineCode machine_code) {
    int op = machine_code >> 26;
    return op == 0b000010 || op == 0b000011;
}
bool isJ_Format(const std::string& assembly) {
    std::string mnemonic = GetMnemonic(assembly);
    std::cmatch m;
    std::regex_match(mnemonic.c_str(), m, J_format_regex);
    if (!m.empty() && m.prefix().str().empty() && m.suffix().str().empty()) {
        return true;
    } else {
        return false;
    }
}
