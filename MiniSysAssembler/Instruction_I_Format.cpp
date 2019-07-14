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

std::regex I_format_regex(
    "^(addiu?|andi|x?ori|lui|l[bhw]u?|s[bhw]|beq|bne|sltiu?|m[ft]c0|b[gl][et]z|"
    "bgezal|bltzal)",
    std::regex::icase);

MachineCode I_FormatInstruction(const std::string& mnemonic,
                                const std::string& assembly,
                                UnsolvedSymbolMap& unsolved_symbol_map,
                                MachineCodeHandle machine_code_it) {
    MachineCode& machine_code = *machine_code_it;
    machine_code = 0;
    std::string op1, op2, op3;
    GetOperand(assembly, op1, op2, op3);
    bool is_mem = std::regex_match(mnemonic, std::regex("^L[BHW]U?|S[BHW]$"));
    if (mnemonic == "MFC0" || mnemonic == "MTC0") {
        // 虽然它是R类型，但为了方便处理，归为I类型
        if (op3.empty()) {
            op3 = "0";
            Note("Unset sel field, set it to 0.");
        }
        unsigned sel = toUNumber(op3);
        if (sel > 7) throw NumberOverflow("Sel", "7", std::to_string(sel));
        SetOP(machine_code, 0b010000);
        SetRS(machine_code, mnemonic == "MFC0" ? 0 : 0b00100);
        SetRT(machine_code, Register(op1));
        SetRD(machine_code, Register(op2));
        SetShamt(machine_code, 0);
        SetFunc(machine_code, sel);
    } else if (is_mem) {  // 访存指令比较特别，拿出来单独写
        static std::regex re(
            "\\s*\\S+\\s*(\\S+)\\s*,\\s*(\\S+)\\s*\\(\\s*(\\S+)\\)",
            std::regex::icase);
        std::smatch match;
        std::regex_match(assembly, match, re);
        if (!match.empty()) {
            std::string op1 = match[1].str(), offset = match[2].str(),
                        op2 = match[3].str();
            if ((isNumber(offset) || isSymbol(offset))) {
                if (mnemonic == "LW") {
                    SetOP(machine_code, 0b100011);
                } else if (mnemonic == "LH") {
                    SetOP(machine_code, 0b100001);
                } else if (mnemonic == "LHU") {
                    SetOP(machine_code, 0b100101);
                } else if (mnemonic == "LB") {
                    SetOP(machine_code, 0b100000);
                } else if (mnemonic == "LBU") {
                    SetOP(machine_code, 0b100100);
                } else if (mnemonic == "SW") {
                    SetOP(machine_code, 0b101011);
                } else if (mnemonic == "SH") {
                    SetOP(machine_code, 0b101001);
                } else if (mnemonic == "SB") {
                    SetOP(machine_code, 0b101000);
                } else {
                    goto err;
                }
                SetRS(machine_code, Register(op2));
                SetRT(machine_code, Register(op1));
                // 右移两位在SetImmediate中完成
                if (isNumber(offset)) {
                    // BEQ与BNE的右移两位在SetImmediate中完成
                    SetImmediate(machine_code, toNumber(offset));
                } else {
                    SetImmediate(machine_code, 0);  // 标号，使用0占位
                    unsolved_symbol_map[offset].push_back(
                        SymbolRef{machine_code_it, cur_instruction});
                }
            } else {
                throw ExceptNumberOrSymbol(offset);
            }
        } else {
            if (isI_Format(assembly)) {
                throw OperandError(mnemonic);
            } else {
                throw UnkonwInstruction(mnemonic);
            }
        }
    } else {
        if (!op1.empty() && !op2.empty() && !op3.empty()) {  // 三操作数
            std::unordered_map<std::string, int> op{
                {"ADDI", 0b001000}, {"ADDIU", 0b001001}, {"ANDI", 0b001100},
                {"ORI", 0b001101},  {"XORI", 0b001110},  {"BEQ", 0b000100},
                {"BNE", 0b000101},  {"SLTI", 0b001010},  {"SLTIU", 0b001011}};
            auto it = op.find(mnemonic);
            if (it != op.end() && (isNumber(op3) || isSymbol(op3))) {
                if (mnemonic == "BEQ" || mnemonic == "BNE") {
                    std::swap(op1, op2);
                }
                SetOP(machine_code, op.at(mnemonic));
                SetRS(machine_code, Register(op2));
                SetRT(machine_code, Register(op1));
                if (isNumber(op3)) {
                    SetImmediate(machine_code, toNumber(op3));
                    if (mnemonic.front() == 'B') {
                        Warning(
                            "You are using an immediate value in branch "
                            "instruction, please make sure that you know what "
                            "you are doing.");
                    }
                } else {
                    SetImmediate(machine_code, 0);  // 标号，使用0占位
                    unsolved_symbol_map[op3].push_back(
                        SymbolRef{machine_code_it, cur_instruction});
                }
            }
        } else if (!op1.empty() && !op2.empty() && op3.empty()) {  // 两操作数
            std::unordered_map<std::string, int> op{
                {"LUI", 0b001111},   {"BGEZ", 0b000001}, {"BGTZ", 0b000111},
                {"BLEZ", 0b000110},  {"BLTZ", 0b000001}, {"BGEZAL", 0b000001},
                {"BLTZAL", 0b000001}};
            std::unordered_map<std::string, int> rt{
                {"BGEZ", 1}, {"BGTZ", 0},         {"BLEZ", 0},
                {"BLTZ", 0}, {"BGEZAL", 0b10001}, {"BLTZAL", 0b10000}};
            auto it = op.find(mnemonic);
            if (isNumber(op2) || isSymbol(op2)) {
                SetOP(machine_code, op.at(mnemonic));
                if (mnemonic == "LUI") {
                    SetRS(machine_code, 0);
                    SetRT(machine_code, Register(op1));
                } else {
                    SetRS(machine_code, Register(op1));
                    SetRT(machine_code, rt.at(mnemonic));
                }
                if (isNumber(op2)) {
                    SetImmediate(machine_code, toNumber(op2));
                    if (mnemonic.front() == 'B') {
                        Warning(
                            "You are using an immediate value in branch "
                            "instruction, please make sure that you know what "
                            "you are doing.");
                    }
                } else {
                    SetImmediate(machine_code, 0);  // 标号，使用0占位
                    unsolved_symbol_map[op2].push_back(
                        SymbolRef{machine_code_it, cur_instruction});
                }
            } else {
                throw ExceptNumberOrSymbol(op2);
            }
        } else {
        err:
            if (isI_Format(assembly)) {
                throw OperandError(mnemonic);
            } else {
                throw UnkonwInstruction(mnemonic);
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
               op == 0b000101 || op == 0b000001 || op == 0b000111 ||
               op == 0b000110) {
        return true;
    } else {
        return false;
    }
}
bool isI_Format(const std::string& assembly) {
    std::string mnemonic = GetMnemonic(assembly);
    std::cmatch m;
    std::regex_match(mnemonic.c_str(), m, I_format_regex);
    if (!m.empty() && m.prefix().str().empty() && m.suffix().str().empty()) {
        return true;
    } else {
        return false;
    }
}
