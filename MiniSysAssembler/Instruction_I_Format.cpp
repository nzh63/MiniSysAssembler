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

std::regex I_format_regex("^(addiu?|andi|x?ori|lui|[ls]w|beq|bne|sltiu?)\\s",
                          std::regex::icase);

MachineCode I_FormatInstruction(const std::string& mnemonic,
                                const std::string& assembly,
                                UnsolvedSymbolMap& unsolved_symbol_map,
                                MachineCodeHandle machine_code_it) {
    MachineCode& machine_code = *machine_code_it;
    machine_code = 0;
    std::string op1, op2, op3;
    GetOperand(assembly, op1, op2, op3);

    if (mnemonic == "LW" || mnemonic == "SW") {  // LW和SW比较特别，拿出来单独写
        static std::regex re(
            "\\s*\\S+\\s*(\\S+)\\s*,\\s*(\\S+)\\s*\\(\\s*(\\S+)\\)",
            std::regex::icase);
        std::smatch match;
        std::regex_match(assembly, match, re);
        if (!match.empty()) {
            std::string op1 = match[1].str(), offect = match[2].str(),
                        op2 = match[3].str();
            if (isRegister(op1) && isRegister(op2) &&
                (isNumber(offect) || isSymbol(offect))) {
                if (mnemonic == "LW") {
                    SetOP(machine_code, 0b100011);
                } else {
                    SetOP(machine_code, 0b101011);
                }
                SetRS(machine_code, Register(op2));
                SetRT(machine_code, Register(op1));
                // 右移两位在SetImmediate中完成
                if (isNumber(offect)) {
                    // BEQ与BNE的右移两位在SetImmediate中完成
                    SetImmediate(machine_code, toNumber(offect));
                } else {
                    SetImmediate(machine_code, 0);  // 标号，使用0占位
                    unsolved_symbol_map[offect].push_back(
                        SymbolRef{machine_code_it, cur_instruction});
                }
            } else {
                goto err;
            }
        } else {
        err:
            if (isI_Format(assembly)) {
                throw std::runtime_error("Invalid operation (" + mnemonic + ").");
            } else {
                throw std::runtime_error("Unkonw instruction: " + mnemonic + ".");
            }
        }
    } else {
        std::unordered_map<std::string, int> op{
            {"ADDI", 0b001000}, {"ADDIU", 0b001001}, {"ANDI", 0b001100},
            {"ORI", 0b001101},  {"XORI", 0b001110},  {"BEQ", 0b000100},
            {"BNE", 0b000101},  {"SLTI", 0b001010},  {"SLTIU", 0b001011}};
        auto it = op.find(mnemonic);
        if (it != op.end() && isRegister(op1) && isRegister(op2) &&
            (isNumber(op3) || isSymbol(op3))) {
            if (mnemonic == "BEQ" || mnemonic == "BNE") {
                std::swap(op1, op2);
            }
            SetOP(machine_code, op.at(mnemonic));
            SetRS(machine_code, Register(op2));
            SetRT(machine_code, Register(op1));
            if (isNumber(op3)) {
                // BEQ与BNE的右移两位在SetImmediate中完成
                SetImmediate(machine_code, toNumber(op3));
            } else {
                SetImmediate(machine_code, 0);  // 标号，使用0占位
                unsolved_symbol_map[op3].push_back(
                    SymbolRef{machine_code_it, cur_instruction});
            }
        } else if (mnemonic == "LUI" && isRegister(op1) &&
                   (isNumber(op2) || isSymbol(op2)) && op3.empty()) {
            SetOP(machine_code, 0b001111);
            SetRS(machine_code, 0);
            SetRT(machine_code, Register(op1));
            if (isNumber(op2)) {
                SetImmediate(machine_code, toNumber(op2));
            } else {
                SetImmediate(machine_code, 0);  // 标号，使用0占位
                unsolved_symbol_map[op2].push_back(
                    SymbolRef{machine_code_it, cur_instruction});
            }
        } else {
            if (isI_Format(assembly)) {
                throw std::runtime_error("Invalid operation (" + mnemonic + ").");
            } else {
                throw std::runtime_error("Unkonw instruction: " + mnemonic + ".");
            }
        }
    }
    return machine_code;
}

bool isI_Format(MachineCode machine_code) {
    int op = machine_code >> 26;
    if (op >> 3 == 1) {
        return true;
    } else if (op == 0b100011 || op == 0b101011 || op == 0b000100 ||
               op == 0b000101) {
        return true;
    } else {
        return false;
    }
}
bool isI_Format(const std::string& assembly) {
    std::cmatch m;
    std::regex_search(assembly.c_str(), m, I_format_regex);
    if (!m.empty()) {
        return true;
    } else {
        return false;
    }
}
