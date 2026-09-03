#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <ranges>
#include <string_view>
#include <vector>
#include <algorithm>
#include <charconv>
#include <numeric>

struct Result {int count1; long long count2;};

std::string loadData(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) {
        throw std::runtime_error("Could not open file: " + filepath + "\n");
    }
    std::stringstream contents;
    contents << in.rdbuf();
    return contents.str();
}

[[nodiscard]]
constexpr auto lines(std::string_view sv) {
    return sv
        | std::views::split('\n')
        | std::ranges::to<std::vector<std::string>>();
}

Result solve(std::string_view sv) {
    auto data = lines(sv);
    int count1 = 0;
    std::vector<long long> beams;
    beams.resize(data[0].size(), 0);

    for (int i = 0; i < data.size() - 1; ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            if (data[i][j] == 'S') { 
                data[i + 1][j] = '|';
                beams[j] = 1;
            }

            if (data[i + 1][j] == '.' && data[i][j] == '|') {
                data[i + 1][j] = '|';
            }
            if (data[i + 1][j] == '^' && data[i][j] == '|') {
                if (data[i + 1][j - 1] == '.') {
                    data[i + 1][j - 1] = '|';
                }
                if (data[i + 1][j + 1] == '.') {
                    data[i + 1][j + 1] = '|';
                }
                count1 += 1;
                beams[j - 1] += beams[j];
                beams[j + 1] += beams[j];
                beams[j] = 0;
            }
        }
    }

    long long count2 = std::ranges::fold_left(beams, 0, std::plus<>());
    
    return Result{count1, count2};
}


int main(const int argc, const char** argv) {
    if (argc != 2) {
         throw std::runtime_error("Usage: ./main <filepath>\n");
     }

    std::string path = std::string(INPUT_DIR) + "/" + argv[1];
    std::string input;
    input = loadData(path);

    auto start = std::chrono::steady_clock::now();

    auto [r1, r2] = solve(input);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        end - start
    );

    std::println("Solution: {}, {}", r1, r2);
    std::println("Execution time: {} ms", duration.count());
}