#include "pch.h"

void ShowDetails(InstructionList instruction_list, DataList data_list,
                 std::ostream& out) {
    out << "Code Segment\n          Machine code\nOffset    hex       bin    "
           "                         \tassembly\n";
    for (const Instruction& instruction : instruction_list) {
        auto offset = instruction.address;
        for (const auto machine_code : instruction.machine_code) {
            out << std::hex << std::setw(8) << std::setfill('0') << offset
                << "  " << std::setw(8) << std::setfill('0') << machine_code
                << "  " << std::bitset<32>(machine_code) << "\t"
                << instruction.assembly << '\n';
            offset += 4;
        }
    }
    out << "\nData Segment\n          Raw data\nOffset    hex bin     "
           "\tassembly\n";
    for (const Data& data : data_list) {
        auto offset = data.address;
        for (const auto raw_data : data.raw_data) {
            out << std::hex << std::setw(8) << std::setfill('0') << offset
                << "  " << std::setw(2) << std::setfill('0')
                << (unsigned)raw_data << "  " << std::bitset<8>(raw_data)
                << "\t" << data.assembly << '\n';
            offset += 1;
        }
    }
}