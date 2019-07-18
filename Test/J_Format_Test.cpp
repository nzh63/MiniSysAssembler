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

#include <filesystem>
#include "CppUnitTest.h"

#include "../MiniSysAssembler/pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define J_Format_Test_fun_1(mnemonic, op1, value)                       \
    TEST_METHOD(mnemonic##_##value) {                                   \
        UnsolvedSymbolMap unsolved_symbol_map;                          \
        std::vector<MachineCode> machine_code{0};                       \
        J_FormatInstruction(#mnemonic, #mnemonic " " #op1,              \
                            unsolved_symbol_map, machine_code.begin()); \
        Assert::IsTrue(machine_code.front() == value);                  \
    }

namespace Test {
TEST_CLASS(J_Format_Test) {
   public:
    J_Format_Test_fun_1(J, 5, 0x08000005);
    J_Format_Test_fun_1(JAL, 5, 0x0c000005);
};
}  // namespace Test
