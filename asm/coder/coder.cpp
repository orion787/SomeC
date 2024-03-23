#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using std::map;

namespace {
    map<std::string, unsigned> opcodes = {
        {"ADD",  0x80},
        {"SUB",  0x90},
        {"MUL",  0xA0},
        {"DIV",  0xB0},
        {"IN",   0xC0},
        {"OUT",  0xC4},
        {"MOVI", 0x00}
    };

    map<std::string, unsigned> regs = {
        {"A", 0x00},
        {"B", 0x01},
        {"C", 0x02},
        {"D", 0x03}
    };

    int processMnemonic(const std::string& opcode, const std::vector<std::string>& operands) {
        int res = 0xFF;

        if (opcode == "ADD" || opcode == "SUB" || opcode == "MUL" || opcode == "DIV")
            return res & (opcodes[opcode] | (regs[operands[0]] << 2) | regs[operands[1]]);

        else if (opcode == "IN" || opcode == "OUT")
            return res & (opcodes[opcode] | regs[operands[0]]);

        else if (opcode == "MOVI")
            return stoi(operands[0]);

        else {
            std::cerr << "Unknown command" << std::endl;
            abort();
        }
            
    }

    void printhex(int num) {
        std::cout << "0x" << std::hex << num << std::endl;
    }
}

int main() {
    std::string line;

    while (true) {
        std::string opcode;
        std::vector<std::string> operands;


        std::getline(std::cin, line);


        if (line.empty()) break;

        size_t spacePos = line.find(' ');
        if (spacePos != std::string::npos) {
            opcode = line.substr(0, spacePos);

            line.erase(0, spacePos + 1);

            std::stringstream ss(line);
            std::string operand;
            while (std::getline(ss, operand, ',')) {
                size_t start = operand.find_first_not_of(" ");
                size_t end = operand.find_last_not_of(" ");
                if (start != std::string::npos && end != std::string::npos)
                    operands.push_back(operand.substr(start, end - start + 1));
                
            }
        }
        else {
            std::cerr << "Invalid input";
        }

        int result = processMnemonic(opcode, operands);

        printhex(result);
    }
    return 0;
}
