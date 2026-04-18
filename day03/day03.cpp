#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <array>
#include <ranges>
#include <string_view>

std::string loadData(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) {
        throw std::runtime_error("Could not open file: " + filepath + "\n");
    }
    std::stringstream contents;
    contents << in.rdbuf();
    return contents.str();
}

[[nodiscard]] constexpr auto lines(std::string_view sv) {
    return sv
        | std::views::split('\n')
        | std::views::transform([](auto r) { return std::string_view(r); });
}

long long solve(const std::string& input, int n) {
    long long joltage = 0;
    long long totalJolts = 0;
    int highest = 0;
    int currentIndex = 0;
    auto rows = lines(input);

    for (auto row : rows) {
        for (int i = 0; i < n; ++i) {
            int j = currentIndex;
            std::ranges::for_each(std::views::counted(row.begin() + currentIndex, row.size() - (n - 1) + i - currentIndex), [&](char c) {
                j += 1;
                if (c - '0' > highest) {
                    highest = c - '0';
                    currentIndex = j;
                }
            });
            joltage += std::pow(10, n - 1 - i) * highest;
            highest = 0;
        }
        totalJolts += joltage;
        currentIndex = 0;
        joltage = 0;
    }
    return totalJolts;
}

int main(int argc, const char** argv) {
    if (argc != 2) {
         throw std::runtime_error("Usage: ./main <filepath>\n");
     }

    std::string path = std::string(INPUT_DIR) + "/" + argv[1];
    std::string input;
    input = loadData(path);
    // Part 1
    // long long result = solve(input, 2);
    long long result = solve(input, 12);
    std::cout << "Solution: " << result << '\n';
}