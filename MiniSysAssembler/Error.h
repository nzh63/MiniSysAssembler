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

#pragma once

class ExceptNumberOrSymbol : public std::runtime_error {
   public:
    explicit ExceptNumberOrSymbol(const std::string &msg);
};
class ExceptNumber : public std::runtime_error {
   public:
    explicit ExceptNumber(const std::string &msg);
};
class ExceptPositive : public std::runtime_error {
   public:
    explicit ExceptPositive(const std::string &msg);
};
class ExceptRegister : public std::runtime_error {
   public:
    explicit ExceptRegister(const std::string &name);
};
class OperandError : public std::runtime_error {
   public:
    explicit OperandError(const std::string &mnemonic,
                          const std::string &msg = "Invalid operation");
};
class TooManyOperand : public OperandError {
   public:
    explicit TooManyOperand(const std::string &mnemonic)
        : OperandError(mnemonic, "Too mamy operands"){};
};
class UnkonwInstruction : public std::runtime_error {
   public:
    explicit UnkonwInstruction(const std::string &mnemonic);
};
class NumberOverflow : public std::runtime_error {
   public:
    explicit NumberOverflow(const std::string &name, const std::string &max,
                            const std::string &now);
};
