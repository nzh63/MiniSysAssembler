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

#define Register_Test_fun(name, value) \
    TEST_METHOD(Test_##name) { Assert::IsTrue(Register("$" #name) == value); }

#define Register_Test_error(name, funname) \
    TEST_METHOD(Test_Error_##funname) {    \
        try {                              \
            Register("$" #name);           \
        } catch (...) {                    \
            return;                        \
        }                                  \
        Assert::Fail();                    \
    }

namespace Test {
TEST_CLASS(Register_Test) {
   public:
    Register_Test_fun(0, 0);
    Register_Test_fun(1, 1);
    Register_Test_fun(2, 2);
    Register_Test_fun(3, 3);
    Register_Test_fun(4, 4);
    Register_Test_fun(5, 5);
    Register_Test_fun(6, 6);
    Register_Test_fun(7, 7);
    Register_Test_fun(8, 8);
    Register_Test_fun(9, 9);
    Register_Test_fun(10, 10);
    Register_Test_fun(11, 11);
    Register_Test_fun(12, 12);
    Register_Test_fun(13, 13);
    Register_Test_fun(14, 14);
    Register_Test_fun(15, 15);
    Register_Test_fun(16, 16);
    Register_Test_fun(17, 17);
    Register_Test_fun(18, 18);
    Register_Test_fun(19, 19);
    Register_Test_fun(20, 20);
    Register_Test_fun(21, 21);
    Register_Test_fun(22, 22);
    Register_Test_fun(23, 23);
    Register_Test_fun(24, 24);
    Register_Test_fun(25, 25);
    Register_Test_fun(26, 26);
    Register_Test_fun(27, 27);
    Register_Test_fun(28, 28);
    Register_Test_fun(29, 29);
    Register_Test_fun(30, 30);
    Register_Test_fun(31, 31);
    Register_Test_fun(zero, 0);
    Register_Test_fun(at, 1);
    Register_Test_fun(v0, 2);
    Register_Test_fun(v1, 3);
    Register_Test_fun(a0, 4);
    Register_Test_fun(a1, 5);
    Register_Test_fun(a2, 6);
    Register_Test_fun(a3, 7);
    Register_Test_fun(t0, 8);
    Register_Test_fun(t1, 9);
    Register_Test_fun(t2, 10);
    Register_Test_fun(t3, 11);
    Register_Test_fun(t4, 12);
    Register_Test_fun(t5, 13);
    Register_Test_fun(t6, 14);
    Register_Test_fun(t7, 15);
    Register_Test_fun(s0, 16);
    Register_Test_fun(s1, 17);
    Register_Test_fun(s2, 18);
    Register_Test_fun(s3, 19);
    Register_Test_fun(s4, 20);
    Register_Test_fun(s5, 21);
    Register_Test_fun(s6, 22);
    Register_Test_fun(s7, 23);
    Register_Test_fun(t8, 24);
    Register_Test_fun(t9, 25);
    Register_Test_fun(k0, 26);
    Register_Test_fun(i0, 26);
    Register_Test_fun(k1, 27);
    Register_Test_fun(i1, 27);
    Register_Test_fun(gp, 28);
    Register_Test_fun(s9, 28);
    Register_Test_fun(sp, 29);
    Register_Test_fun(fp, 30);
    Register_Test_fun(s8, 30);
    Register_Test_fun(ra, 31);
    Register_Test_error(32, 32);
    Register_Test_error(-1, _1);
    Register_Test_error(1000000, 1000000);
    Register_Test_error(-1000000, _1000000);
    Register_Test_error(0x10000, 0x10000);
    Register_Test_error(0xa, 0xa);
    Register_Test_error(0x0, 0x0);
    Register_Test_error(foo, foo);
};
}  // namespace Test
