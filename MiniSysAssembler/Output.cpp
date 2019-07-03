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

static void OutputHeader(std::ostream& out) {
    out << R"(memory_initialization_radix = 16;
memory_initialization_vector =
)";
}

void OutputInstruction(std::ostream& out,
                       const InstructionList& instruction_list) {
    OutputHeader(out);
    int i = 0;
    for (const auto& instruction : instruction_list) {
        for (auto m : instruction.machine_code) {
            out << std::setw(8) << std::setfill('0') << std::hex << m
                << (i == 16384 - 1 ? ';' : ',') << "\n";
            i++;
        }
    }
    for (; i < 16384; i++) {
        out << std::setw(8) << std::setfill('0') << std::hex << 0
            << (i == 16384 - 1 ? ';' : ',') << "\n";
    }
}

void OutputDataSegment(std::ostream& out, const DataList& instruction_list) {
    OutputHeader(out);
    int i = 0;
    char data[4] = {0};
    for (const auto& instruction : instruction_list) {
        for (auto m : instruction.raw_data) {
            data[i % 4] = m;
            i++;
            if (i % 4 == 0) {
                out << std::setw(8) << std::setfill('0') << std::hex
                    << *(std::uint32_t*)data << (i == 16384 - 1 ? ';' : ',')
                    << "\n";
                memset(data, 0, sizeof data);
            }
        }
    }
    while (i < 16384 * 4) {
        i++;
        if (i % 4 == 0) {
            out << std::setw(8) << std::setfill('0') << std::hex
                << *(std::uint32_t*)data << (i == 16384 * 4 ? ';' : ',')
                << "\n";
            memset(data, 0, sizeof data);
        }
    }
}
