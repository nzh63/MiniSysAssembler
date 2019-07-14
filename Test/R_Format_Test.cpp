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

#define R_Format_Test_fun_3(mnemonic, op1, op2, op3, value)                    \
    TEST_METHOD(mnemonic##_##value) {                                          \
        UnsolvedSymbolMap unsolved_symbol_map;                                 \
        std::vector<MachineCode> machine_code{0};                              \
        R_FormatInstruction(#mnemonic, #mnemonic " " #op1 ", " #op2 ", " #op3, \
                            unsolved_symbol_map, machine_code.begin());        \
        Assert::IsTrue(machine_code.front() == value);                         \
    }

#define R_Format_Test_fun_1(mnemonic, op1, value)                       \
    TEST_METHOD(mnemonic##_##value) {                                   \
        UnsolvedSymbolMap unsolved_symbol_map;                          \
        std::vector<MachineCode> machine_code{0};                       \
        R_FormatInstruction(#mnemonic, #mnemonic " " #op1,              \
                            unsolved_symbol_map, machine_code.begin()); \
        Assert::IsTrue(machine_code.front() == value);                  \
    }

namespace Test {
TEST_CLASS(R_Format_Test){
    public:
        R_Format_Test_fun_3(ADD, $15, $t3, $t2, 0x016a7820)
        R_Format_Test_fun_3(ADDU, $s2, $s5, $s6, 0x02b69021)
        R_Format_Test_fun_3(SUB, $s2, $zero, $at, 0x00019022)
        R_Format_Test_fun_3(SUBU, $v1, $v0, $0, 0x00401823)
        R_Format_Test_fun_3(AND, $t9, $t8, $gp, 0x031cc824)
        R_Format_Test_fun_3(OR, $13, $15, $27, 0x01fb6825)
        R_Format_Test_fun_3(XOR, $2, $0, $1, 0x00011026)
        R_Format_Test_fun_3(NOR, $9, $9, $7, 0x01274827)
        R_Format_Test_fun_3(SLT, $s1, $s2, $s5, 0x0255882a)
        R_Format_Test_fun_3(SLTU, $a0, $s3, $a2, 0x0266202b)
        R_Format_Test_fun_3(SLL, $8, $k0, 9, 0x001a4240)
        R_Format_Test_fun_3(SRL, $k0, $k1, 4, 0x0001bd102)
        R_Format_Test_fun_3(SRA, $fp, $ra, 1, 0x001ff043)
        R_Format_Test_fun_3(SLLV, $8, $t4, $9, 0x012c4004)
        R_Format_Test_fun_3(SRLV, $k0, $s6, $4, 0x0096d006)
        R_Format_Test_fun_3(SRAV, $k1, $ra, $1, 0x003fd807)
        R_Format_Test_fun_1(JR, $k1, 0x03600008)
        R_Format_Test_fun_1(JR, $ra, 0x03e00008)
};
}
