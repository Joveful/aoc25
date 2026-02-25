#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Part 1 answer: 1123
// Part 2 answer: 6695


void loadData(const std::string& filename, std::vector<std::pair<char, int>>& v) {
    std::ifstream fd(filename);
    if (!fd.is_open()) {
        std::runtime_error("Could not open file: " + filename + "\n");
    }

    std::string input;
    while (std::getline(fd, input)) {
        std::pair<char, int> a = std::make_pair(input[0], std::stoi(input.substr(1)));
        v.emplace_back(a);
    }
}

int countRotations(const std::vector<std::pair<char, int>>& in) {
    int dial = 50;
    int count = 0;
    for (auto i : in) {
        if (i.first == 'R') {
            int fullrot = (dial + i.second) / 100;
            count += fullrot;
            dial = (dial + i.second) % 100;
        } else {
            int s1 = dial - i.second;
            int carry = 1;
            if (s1 <= 0) {
                if (dial == 0) {carry = 0;}
                int fullrot = std::abs(s1 / 100) + carry;
                count += fullrot;
                dial = (100 + (s1 % 100)) % 100; // convert mod to positive values
            } else {
                dial = s1;
            }
        }
        // Used in Part 1
        //if (dial == 0) {count += 1;}
    }
    return count;
}

int main(int argc, const char** argv) {
    if (argc < 2) {
        std::runtime_error("Usage: day01 <input_file>\n");
    }

    std::string path = std::string(INPUT_DIR) + "/" + argv[1];
    std::vector<std::pair<char, int>> instructions;
    loadData(path, instructions);
    std::cout << "Solution: " << countRotations(instructions) << '\n';
}
