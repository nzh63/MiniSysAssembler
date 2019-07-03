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
    if (argc == 1) {
        ShowHelpMessage();
    } else if (argc == 2) {
        doAssemble(argv[1]);
    } else {
        doAssemble(argv[1], argv[2]);
    }
}
