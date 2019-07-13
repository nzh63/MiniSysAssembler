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

std::regex R_format_regex(
    "^(addu?|subu?|and|[xn]?or|sltu?|s(?:ll|rl|ra)v?|jr|multu?|divu?|m[tf]hi|"
    "m[tf]lo|jalr|break|syscall|eret)",
    std::regex::icase);

MachineCode R_FormatInstruction(const std::string& mnemonic,
                                const std::string& assembly,
                                UnsolvedSymbolMap& unsolved_symbol_map,
                                MachineCodeHandle machine_code_it) {
    MachineCode& machine_code = *machine_code_it;
    machine_code = 0;
    std::string op1, op2, op3;
    GetOperand(assembly, op1, op2, op3);
    SetOP(machine_code, 0);
    if (!op1.empty() && !op2.empty() && !op3.empty()) {  // 三操作数
        // 三个操作数均为寄存器的有这些
        std::unordered_map<std::string, int> func1{
            {"ADD", 0b100000},  {"ADDU", 0b100001}, {"SUB", 0b100010},
            {"SUBU", 0b100011}, {"AND", 0b100100},  {"OR", 0b100101},
            {"XOR", 0b100110},  {"NOR", 0b100111},  {"SLT", 0b101010},
            {"SLTU", 0b101011}, {"SLLV", 0b000100}, {"SRLV", 0b000110},
            {"SRAV", 0b000111}};
        // 两个操作数为寄存器，一个操作数为立即数的有这些
        // 为方便处理，mfc0与mtc0视为I类型指令
        std::unordered_map<std::string, int> func2{
            {"SLL", 0b000000}, {"SRL", 0b000010}, {"SRA", 0b000011}};
        auto it1 = func1.find(mnemonic);
        auto it2 = func2.find(mnemonic);

        if (it1 != func1.end()) {
            // 三个操作数均为寄存器
            if (mnemonic == "SLLV" || mnemonic == "SRLV" ||
                mnemonic == "SRAV") {
                std::swap(op2, op3);
            }
            SetFunc(machine_code, func1.at(mnemonic));
            SetRS(machine_code, Register(op2));
            SetRT(machine_code, Register(op3));
            SetRD(machine_code, Register(op1));
            SetShamt(machine_code, 0);
        } else if (it2 != func2.end() && (isNumber(op3) || isSymbol(op3))) {
            // 两个操作数为寄存器，一个操作数为立即数或标号
            SetFunc(machine_code, func2.at(mnemonic));
            SetRS(machine_code, 0);
            SetRT(machine_code, Register(op2));
            SetRD(machine_code, Register(op1));
            if (isNumber(op3)) {
                SetShamt(machine_code, toNumber(op3));
            } else {
                SetShamt(machine_code, 0);  // 标号，使用0占位
                unsolved_symbol_map[op3].push_back(
                    SymbolRef{machine_code_it, cur_instruction});
            }
        } else {
            goto err;
        }
    } else if (!op1.empty() && !op2.empty() && op3.empty()) {  // 两操作数
        // 只有两个操作数为寄存器的有这些
        std::unordered_map<std::string, int> func3{{"MULT", 0b011000},
                                                   {"MULTU", 0b011001},
                                                   {"DIV", 0b011010},
                                                   {"DIVU", 0b011011},
                                                   {"JALR", 0b0001001}};
        auto it3 = func3.find(mnemonic);
        if (it3 != func3.end()) {
            if (mnemonic != "JALR") {
                SetRS(machine_code, Register(op1));
                SetRT(machine_code, Register(op2));
                SetRD(machine_code, 0);
            } else {
                SetRS(machine_code, Register(op2));
                SetRT(machine_code, 0);
                SetRD(machine_code, Register(op1));
            }
            SetShamt(machine_code, 0);
            SetFunc(machine_code, func3.at(mnemonic));
        } else {
            goto err;
        }
    } else if (!op1.empty() && op2.empty() && op3.empty()) {  // 一操作数
        // 只有一个操作数为寄存器的有这些
        std::unordered_map<std::string, int> func4{{"JR", 0b001000},
                                                   {"MFHI", 0b010000},
                                                   {"MFLO", 0b010010},
                                                   {"MTHI", 0b010001},
                                                   {"MTLO", 0b010011}};
        auto it4 = func4.find(mnemonic);
        if (it4 != func4.end()) {
            if (mnemonic != "MFHI" && mnemonic != "MFLO") {
                SetRS(machine_code, Register(op1));
                SetRT(machine_code, 0);
                SetRD(machine_code, 0);
            } else {
                SetRS(machine_code, 0);
                SetRT(machine_code, 0);
                SetRD(machine_code, Register(op1));
            }
            SetShamt(machine_code, 0);
            SetFunc(machine_code, func4.at(mnemonic));
        } else {
            throw std::runtime_error(op1 + " shoulb be a register.");
        }
    } else if (op1.empty() && op2.empty() && op3.empty()) {  // 无操作数
        std::unordered_map<std::string, int> func5{
            {"BREAK", 0b001101}, {"SYSCALL", 0b001100}, {"ERET", 0b011000}};
        auto it5 = func5.find(mnemonic);
        if (it5 != func5.end()) {
            if (mnemonic == "ERET") {
                SetOP(machine_code, 0b010000);
            }
            SetRS(machine_code, mnemonic == "ERET" ? 0b10000 : 0);
            SetRT(machine_code, 0);
            SetRD(machine_code, 0);
            SetShamt(machine_code, 0);
            SetFunc(machine_code, func5.at(mnemonic));
        } else {
            goto err;
        }
    } else {
    err:
        if (isR_Format(assembly)) {
            throw std::runtime_error("Invalid operation (" + mnemonic + ").");
        } else {
            throw std::runtime_error("Unkonw instruction: " + mnemonic + ".");
        }
    }
    return machine_code;
}

bool isR_Format(MachineCode machine_code) { return (machine_code >> 26 == 0); }

bool isR_Format(const std::string& assembly) {
    std::string mnemonic = GetMnemonic(assembly);
    std::cmatch m;
    std::regex_match(mnemonic.c_str(), m, R_format_regex);
    if (!m.empty() && m.prefix().str().empty() && m.suffix().str().empty()) {
        return true;
    } else {
        return false;
    }
}
