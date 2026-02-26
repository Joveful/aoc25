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

int solvePart1(const std::string& input) {
    std::array<int, 2> jolts{0, 0};
    int totalJolts = 0;
    auto rows = lines(input);

    auto highestJolt = [&](char c, std::array<int, 2>& jolts) {
        if (jolts[0] < c - '0') {
            jolts[0] = c - '0';
            jolts[1] = 0;
        } else if (jolts[1] < c - '0') {
            jolts[1] = c - '0';
        }
    };

    for (auto row : rows) {
        std::ranges::for_each(row | std::views::take(row.size() - 1), [&](char c) {
            highestJolt(c, jolts);
        });
        char lastChar = row.back();
        if (jolts[1] < lastChar - '0')
            jolts[1] = lastChar - '0';

        totalJolts += 10 * jolts[0] + jolts[1];
        jolts[0] = 0;
        jolts[1] = 0;
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
    int result = solvePart1(input);
    std::cout << "Solution: " << result << '\n';
}