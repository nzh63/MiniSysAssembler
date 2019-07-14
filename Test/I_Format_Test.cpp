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

#define I_Format_Test_fun_3(mnemonic, op1, op2, op3, value)                    \
    TEST_METHOD(mnemonic##_##value) {                                          \
        UnsolvedSymbolMap unsolved_symbol_map;                                 \
        std::vector<MachineCode> machine_code{0};                              \
        I_FormatInstruction(#mnemonic, #mnemonic " " #op1 ", " #op2 ", " #op3, \
                            unsolved_symbol_map, machine_code.begin());        \
        Assert::IsTrue(machine_code.front() == value);                         \
    }

#define I_Format_Test_fun_2(mnemonic, op1, op2, value)                  \
    TEST_METHOD(mnemonic##_##value) {                                   \
        UnsolvedSymbolMap unsolved_symbol_map;                          \
        std::vector<MachineCode> machine_code{0};                       \
        I_FormatInstruction(#mnemonic, #mnemonic " " #op1 ", " #op2,    \
                            unsolved_symbol_map, machine_code.begin()); \
        Assert::IsTrue(machine_code.front() == value);                  \
    }

namespace Test {
TEST_CLASS(I_Format_Test){
    public:
        I_Format_Test_fun_3(ADDI, $1, $2, 0x500, 0x20410500)
        I_Format_Test_fun_3(ADDI, $s1, $s2, -5, 0x2251fffb)
        I_Format_Test_fun_3(ADDIU, $1, $2, 0x500, 0x24410500)
        I_Format_Test_fun_3(ADDIU, $s1, $s2, -5, 0x2651fffb)
        I_Format_Test_fun_3(ORI, $t5, $t2, 100, 0x354d0064)
        I_Format_Test_fun_3(XORI, $29, $1, 100, 0x383d0064)
        I_Format_Test_fun_2(LUI, $a3, 0xFFFF, 0x3c07ffff)
        I_Format_Test_fun_2(LW, $a2, 0xFF0($v1), 0x8c660ff0)
        I_Format_Test_fun_2(SW, $27, 0x4($a3), 0xacfb0004)
        I_Format_Test_fun_3(BEQ, $s7, $t6, main, 0x12ee0000)
        I_Format_Test_fun_3(BNE, $v1, $a2, main, 0x14660000)
        I_Format_Test_fun_3(SLTI, $ra, $31, -5, 0x2bfffffb)
        I_Format_Test_fun_3(SLTIU, $3, $12, 0x75, 0x2d830075)
};
}
