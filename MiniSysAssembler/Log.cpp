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

void Msg(const std::string &msg, const std::string &prefix, int level) {
#if !(_DEBUG)
    if (level <= LogLevel::log) return;
#endif
    static char name[][20] = {"Debug", "Log", "Note", "Waning", "Error"};
    std::cerr << prefix << (prefix != "" ? ": " : "") << name[level] << ": "
              << msg << '\n';
}

void Error(std::string msg, Instruction *instruction) {
    std::string prefix;
    if (!instruction) instruction = cur_instruction;
    if (instruction) {
        prefix =
            instruction->file + '(' + std::to_string(instruction->line) + ')';
    }
    Msg(msg, prefix, LogLevel::error);
}
void Warning(std::string msg, Instruction *instruction) {
    std::string prefix;
    if (!instruction) instruction = cur_instruction;
    if (instruction) {
        prefix =
            instruction->file + '(' + std::to_string(instruction->line) + ')';
    }
    Msg(msg, prefix, LogLevel::warning);
}
void Note(std::string msg, Instruction *instruction) {
    std::string prefix;
    if (!instruction) instruction = cur_instruction;
    if (instruction) {
        prefix =
            instruction->file + '(' + std::to_string(instruction->line) + ')';
    }
    Msg(msg, prefix, LogLevel::note);
}
void Log(std::string msg, Instruction *instruction) {
    std::string prefix;
    if (!instruction) instruction = cur_instruction;
    if (instruction) {
        prefix =
            instruction->file + '(' + std::to_string(instruction->line) + ')';
    }
    Msg(msg, prefix, LogLevel::log);
}
void Debug(std::string msg, Instruction *instruction) {
    std::string prefix;
    if (!instruction) instruction = cur_instruction;
    if (instruction) {
        prefix =
            instruction->file + '(' + std::to_string(instruction->line) + ')';
    }
    Msg(msg, prefix, LogLevel::debug);
}
