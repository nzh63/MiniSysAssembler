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

ExceptNumberOrSymbol::ExceptNumberOrSymbol(const std::string &msg)
    : std::runtime_error(msg + " should be a number or a symbol."){};

ExceptNumber::ExceptNumber(const std::string &msg)
    : std::runtime_error(msg + " should be a number."){};

ExceptPositive::ExceptPositive(const std::string &msg)
    : std::runtime_error(msg + " should be a positive number."){};

ExceptRegister::ExceptRegister(const std::string &name)
    : std::runtime_error(name + " is not a register."){};

OperandError::OperandError(const std::string &mnemonic, const std::string &msg)
    : std::runtime_error(msg + " (" + mnemonic + ")."){};

UnkonwInstruction::UnkonwInstruction(const std::string &mnemonic)
    : std::runtime_error("Unkonw instruction: " + mnemonic + "."){};

NumberOverflow::NumberOverflow(const std::string &name, const std::string &max,
                               const std::string &now)
    : std::runtime_error(name + " is too large. It should not larger than " +
                         max + ". Now it is " + now){};
