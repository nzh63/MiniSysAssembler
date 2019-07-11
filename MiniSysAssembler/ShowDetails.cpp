#include "pch.h"

void ShowDetails(InstructionList instruction_list, DataList data_list,
                 std::ostream& out) {
    out << "Code Segment\n";
    for (const Instruction& instruction : instruction_list) {
        out << '#' << instruction.assembly << '\n'
            << "Offset:\n\t" << std::setw(8)
            << std::setfill('0') << instruction.address << '\n'
            << "Machine code:\n";
        for (const auto machine_code : instruction.machine_code) {
            out << std::hex << '\t' << machine_code << '\t'
                << std::bitset<32>(machine_code) << '\n';
        }
        out << '\n';
    }
    out << "\nData Segment\n";
    for (const Data& data : data_list) {
        out << '#' << data.assembly << '\n'
            << "Offset:\n\t" <<
            std::setw(8) << std::setfill('0') << data.address << '\\n'
            << "Raw data:\n";
        for (const auto raw_data : data.raw_data) {
            out << std::hex << '\t' << raw_data << '\t'
                << std::bitset<8>(raw_data) << '\n';
        }
        out << '\n';
    }
}