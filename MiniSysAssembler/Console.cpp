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

void ShowAboutMessage(std::ostream& out) {
    out << R"(A simple MiniSys-1 assembler
Copyright (c) 2019 nzh63, All Rights Reserved.
)";
}
void ShowHelpMessage(std::ostream& out) {
    ShowAboutMessage(out);
    out << R"(
Useage: MiniSysAssembler.exe [option] input_file_path [output_folder_path]

Options:
    --help              Show help message.
    --show-details      Output details.txt for details.

Eg:  MiniSysAssembler.exe C:\mycode.asm

)";
}

std::unordered_map<std::string, unsigned> allow_options{{"--help", 0},
                                                        {"--show-details", 1}};
