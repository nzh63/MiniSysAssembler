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

#pragma once

using MachineCode = std::uint32_t;
using MachineCodeHandle = std::vector<MachineCode>::iterator;

struct Instruction {
    std::string assembly, file;
    unsigned line;
    unsigned address;
    bool done = false;
    std::vector<MachineCode> machine_code;
};

struct SymbolRef {
    MachineCodeHandle machine_code_handle;
    Instruction* instruction;
};

using InstructionList = std::vector<Instruction>;
using UnsolvedSymbolMap =
    std::unordered_map<std::string, std::vector<SymbolRef>>;
using SymbolMap = std::unordered_map<std::string, unsigned int>;

MachineCodeHandle NewMachineCode(Instruction& i);

void SetOP(MachineCode& machine_code, unsigned OP);
void SetRS(MachineCode& machine_code, unsigned RS);
void SetRT(MachineCode& machine_code, unsigned RT);
void SetRD(MachineCode& machine_code, unsigned RD);
void SetShamt(MachineCode& machine_code, unsigned shamt);
void SetFunc(MachineCode& machine_code, unsigned func);
void SetImmediate(MachineCode& machine_code, int immediate);
void SetImmediate(MachineCode& machine_code, int immediate);
void SetAddress(MachineCode& machine_code, unsigned address);

std::string GetMnemonic(const std::string& assembly);
void GetOperand(const std::string& assembly, std::string& op1, std::string& op2,
                std::string& op3);

#include "Instruction_I_Format.h"
#include "Instruction_J_Format.h"
#include "Instruction_Macro.h"
#include "Instruction_R_Format.h"
