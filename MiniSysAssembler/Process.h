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
int GeneratedMachineCode(InstructionList& instruction_list,
                         UnsolvedSymbolMap& unsolved_symbol_map,
                         SymbolMap& symbol_map);
int GeneratedDataSegment(DataList& data_list,
                         UnsolvedSymbolMap& unsolved_symbol_map,
                         SymbolMap& symbol_map);
void ProcessInstruction(const std::string& assembly, Instruction& instruction,
                     UnsolvedSymbolMap& unsolved_symbol_map);
void ProcessData(const std::string& assembly, Data& data,
                     UnsolvedSymbolMap& unsolved_symbol_map);
std::string ProcessLabel(unsigned int address, const std::string& assembly,
                         SymbolMap& symbol_map);
int SolveSymbol(UnsolvedSymbolMap& unsolved_symbol_map,
                const SymbolMap& symbol_map);

extern Instruction* cur_instruction;
extern unsigned cur_address;
