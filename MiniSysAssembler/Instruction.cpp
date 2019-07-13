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

MachineCodeHandle NewMachineCode(Instruction& i) {
    i.machine_code.push_back(0);
    return i.machine_code.begin() + (i.machine_code.size() - 1);
}

void SetOP(MachineCode& machine_code, unsigned OP) {
    if (OP >= 64) {
        throw std::runtime_error(
            "OP is too large. It should not larger than 63. "
            "Now it is " +
            std::to_string(OP));
    }
    machine_code &= 0b00000011111111111111111111111111;
    machine_code |= OP << 26;
}
void SetRS(MachineCode& machine_code, unsigned RS) {
    if (RS >= 32) {
        throw std::runtime_error(
            "RS is too large. It should not larger than 31. "
            "Now it is " +
            std::to_string(RS));
    }
    machine_code &= 0b11111100000111111111111111111111;
    machine_code |= RS << 21;
}
void SetRT(MachineCode& machine_code, unsigned RT) {
    if (RT >= 32) {
        throw std::runtime_error(
            "RT is too large. It should not larger than 31. "
            "Now it is " +
            std::to_string(RT));
    }
    machine_code &= 0b11111111111000001111111111111111;
    machine_code |= RT << 16;
}
void SetRD(MachineCode& machine_code, unsigned RD) {
    if (RD >= 32) {
        throw std::runtime_error(
            "RT is too large. It should not larger than 31. "
            "Now it is " +
            std::to_string(RD));
    }
    machine_code &= 0b11111111111111110000011111111111;
    machine_code |= RD << 11;
}
void SetShamt(MachineCode& machine_code, unsigned shamt) {
    if (shamt >= 32) {
        throw std::runtime_error(
            "Shamt is too large. It should not larger than 31. "
            "Now it is " +
            std::to_string(shamt));
    }
    machine_code &= 0b11111111111111111111100000111111;
    machine_code |= shamt << 6;
}
void SetFunc(MachineCode& machine_code, unsigned func) {
    if (func >= 64) {
        throw std::runtime_error(
            "Shamt is too large. It should not larger than 63. "
            "Now it is " +
            std::to_string(func));
    }
    machine_code &= 0b11111111111111111111111111000000;
    machine_code |= func << 0;
}
void SetImmediate(MachineCode& machine_code, int immediate) {
    int op = machine_code >> 26;
    if (op == 0b000100 || op == 0b000101) {
        immediate >>= 2;
    }
    if (immediate >= 65536) {
        throw std::runtime_error(
            "Immediate is too large. It should not larger than 65535. "
            "Now it is " +
            std::to_string(immediate));
    }
    machine_code &= 0xffff0000;
    machine_code |= (immediate << 0) & 0xffff;
}
void SetAddress(MachineCode& machine_code, unsigned address) {
    address >>= 2;
    if (address >= 67108864) {
        throw std::runtime_error(
            "Address is too large. It should not larger than 67108863. "
            "Now it is " +
            std::to_string(address));
    }
    machine_code &= 0b11111100000000000000000000000000;
    machine_code |= address << 0;
}

std::string GetMnemonic(const std::string& assembly) {
    static std::regex re("^\\s*(\\S+)");
    std::smatch match;
    std::regex_search(assembly, match, re);
    return match[1].matched ? match[1].str() : "";
}

void GetOperand(const std::string& assembly, std::string& op1, std::string& op2,
                std::string& op3) {
    static std::regex re_3("\\s*\\S+\\s*(\\S+)\\s*,\\s*(\\S+)\\s*,\\s*(\\S+)",
                           std::regex::icase),  // 三操作数
        re_2("\\s*\\S+\\s*(\\S+)\\s*,\\s*(\\S+)",
             std::regex::icase),                        // 二操作数
        re_1("\\s*\\S+\\s*(\\S+)", std::regex::icase);  // 一操作数
    std::smatch match;
    std::regex_match(assembly, match, re_3);
    if (!match.empty()) {  // 三操作数
        op1 = match[1].str();
        op2 = match[2].str();
        op3 = match[3].str();
    } else {
        op3 = "";
        std::regex_match(assembly, match, re_2);
        if (!match.empty()) {  // 二操作数
            op1 = match[1].str();
            op2 = match[2].str();
        } else {
            op2 = "";
            std::regex_match(assembly, match, re_1);
            if (!match.empty()) {  // 一操作数
                op1 = match[1].str();
            } else {
                op1 = "";
            }
        }
    }
}
