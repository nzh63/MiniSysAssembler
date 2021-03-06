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

std::string toUppercase(std::string str) {
    for (auto& c : str) {
        if (c <= 'z' && c >= 'a') {
            c += 'A' - 'a';
        }
    }
    return str;
}

bool isNumber(const std::string& str) {
    if (str[0] == '-') {
        return isPositive(str.substr(1));
    } else {
        return isPositive(str);
    }
}
bool isPositive(const std::string& str) {
    static std::regex re(R"(^(?:\d+|0x[0-9abcdef]+)$)", std::regex::icase);
    std::cmatch m;
    std::regex_search(str.c_str(), m, re);
    if (m[0].matched) {
        return true;
    } else {
        return false;
    }
}

bool isDecimal(const std::string& str) {
    static std::regex re(R"(^\d+$)", std::regex::icase);
    std::cmatch m;
    if (str[0] == '-') {
        std::regex_search(str.substr(1).c_str(), m, re);
    } else {
        std::regex_search(str.c_str(), m, re);
    }
    if (m[0].matched) {
        return true;
    } else {
        return false;
    }
    
}

int toNumber(const std::string& str, bool enable_hex) {
    if (!isNumber(str)) throw std::runtime_error(str + " is not a number.");
    int ans;
    try {
        ans = std::stol(str, 0, enable_hex ? 0 : 10);
    } catch (std::out_of_range) {
        try {
            ans = (int)std::stoul(str, 0, enable_hex ? 0 : 10);
        } catch (std::out_of_range) {
            throw std::out_of_range("Number out of range.");
        }
    }
    return ans;
}

unsigned toUNumber(const std::string& str, bool enable_hex) {
    if (!isNumber(str)) throw std::runtime_error(str + " is not a number.");
    unsigned ans;
    try {
        ans = (int)std::stoul(str, 0, enable_hex ? 0 : 10);
    } catch (std::out_of_range) {
        throw std::out_of_range("Number out of range.");
    }
    return ans;
}

bool isSymbol(const std::string& str) {
    if (str.empty()) {
        return false;
    } else {
        std::regex re(R"(^[a-z0-9_.$]+$)", std::regex::icase);
        std::cmatch m;
        std::regex_search(str.c_str(), m, re);
        return !m.empty() && !isPositive(str.substr(0, 1)) && !isRegister(str);
    }
}

bool isMemory(const std::string& str) {
    std::regex re(R"(^\s*(\S+)\((\S+)\)\s*$)", std::regex::icase);
    std::cmatch m;
    std::regex_search(str.c_str(), m, re);
    if (!m.empty() && (isNumber(m[1].str()) || isSymbol(m[1].str())) &&
        isRegister(m[2].str())) {
        return true;
    } else {
        return false;
    }
}
