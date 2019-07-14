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

#include "Register.h"

int NameToId(const std::string& str2) {
    std::string str3 = toUppercase(str2);
    if (str3 == "ZERO") {
        return 0;
    } else if (str3 == "AT") {
        return 1;
    } else if (str3 == "V0") {
        return 2;
    } else if (str3 == "V1") {
        return 3;
    } else if (str3 == "A0") {
        return 4;
    } else if (str3 == "A1") {
        return 5;
    } else if (str3 == "A2") {
        return 6;
    } else if (str3 == "A3") {
        return 7;
    } else if (str3 == "T0") {
        return 8;
    } else if (str3 == "T1") {
        return 9;
    } else if (str3 == "T2") {
        return 10;
    } else if (str3 == "T3") {
        return 11;
    } else if (str3 == "T4") {
        return 12;
    } else if (str3 == "T5") {
        return 13;
    } else if (str3 == "T6") {
        return 14;
    } else if (str3 == "T7") {
        return 15;
    } else if (str3 == "S0") {
        return 16;
    } else if (str3 == "S1") {
        return 17;
    } else if (str3 == "S2") {
        return 18;
    } else if (str3 == "S3") {
        return 19;
    } else if (str3 == "S4") {
        return 20;
    } else if (str3 == "S5") {
        return 21;
    } else if (str3 == "S6") {
        return 22;
    } else if (str3 == "S7") {
        return 23;
    } else if (str3 == "T8") {
        return 24;
    } else if (str3 == "T9") {
        return 25;
    } else if (str3 == "K0" || str3 == "I0") {
        return 26;
    } else if (str3 == "K1" || str3 == "I1") {
        return 27;
    } else if (str3 == "GP" || str3 == "S9") {
        return 28;
    } else if (str3 == "SP") {
        return 29;
    } else if (str3 == "FP" || str3 == "S8") {
        return 30;
    } else if (str3 == "RA") {
        return 31;
    } else {
        return -1;
    }
}

int Register(const std::string& str) {
    std::string str2 = str.substr(1);
    try {
        if (isPositive(str2) && toNumber(str2, false) < 32) {
            return toNumber(str2, false);
        } else {
            int id = NameToId(str2);
            if (id != -1) {
                return id;
            } else {
                throw ExceptRegister(str);
            }
        }
    } catch (std::out_of_range) {
        throw ExceptRegister(str);
    }
}

bool isRegister(const std::string& str) {
    std::string str2 = str.substr(1);
    try {
        return str[0] == '$' && ((isPositive(str2) && (toNumber(str2) < 32)) ||
                                 NameToId(str2) != -1);
    } catch (std::out_of_range) {
        return false;
    }
}
