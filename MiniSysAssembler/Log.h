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
void Msg(const std::string &msg, const std::string &prefix = "", int level = 1);
void Error(std::string msg, Instruction *instruction = nullptr);
void Warning(std::string msg, Instruction *instruction = nullptr);
void Note(std::string msg, Instruction *instruction = nullptr);
void Log(std::string msg, Instruction *instruction = nullptr);
void Debug(std::string msg, Instruction *instruction = nullptr);

namespace LogLevel {
enum { debug, log, note, warning, error };
}
