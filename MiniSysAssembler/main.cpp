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

int main(int argc, char* argv[]) {
    if (argc == 1 || std::string(argv[1]) == "--help") {
        ShowHelpMessage();
    } else {
        std::string asm_path, out_path = "./";
        unsigned parameters = 0, fill_parameters = 0;
        for (int i = 1; i < argc; i++) {
            if (allow_options.find(argv[i]) != allow_options.end()) {
                parameters |= allow_options.at(argv[i]);
            } else {
                if (fill_parameters > 2 || argv[i][0] == '-') {
                    std::cerr << "Bad option " << argv[i] << ". Type "
                              << argv[0] << " --help for useage.";
                } else if (fill_parameters == 0) {
                    fill_parameters++;
                    asm_path = argv[i];
                } else {
                    fill_parameters++;
                    out_path = argv[i];
                    if (out_path.back() != '/' && out_path.back() != '\\') {
                        out_path.push_back('/');
					}
                }
            }
        }
        doAssemble(asm_path, out_path, parameters);
    }
}
