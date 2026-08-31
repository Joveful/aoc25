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

long long solve(std::string_view sv) {
    auto data = lines(sv);

    auto values = data 
        | std::views::take(data.size() - 1)
        | std::views::transform([](const auto d) {
            std::vector<int> vec;
            
            const char* first = d.data();
            const char* last = d.data() + d.size();
            while (first < last) {
                if (std::isspace(*first)) ++first;

                int val{};
                auto [ptr, ec] = std::from_chars(first, last, val);
                if (ec == std::errc())
                    vec.push_back(val);

                first = ptr;
            }
            return vec;
        })
        | std::ranges::to<std::vector<std::vector<int>>>();

    auto ops = data[data.size() - 1]
        | std::views::filter([](const auto c) {
            return (c == '+' || c == '*');
        })
        | std::ranges::to<std::vector<char>>();

    std::vector<long long> opsResults;
    for (int j = 0; j < values[0].size(); ++j) {
        long long partial{};
        if (ops[j] == '*') partial = 1;

        for (int i = 0; i < values.size(); ++i) {
            switch (ops[j]) {
                case '+':
                    partial += values[i][j];
                    break;
                case '*':
                    partial *= values[i][j];
                    break;
            }
        }
        opsResults.push_back(partial);
    }

    long long result = std::ranges::fold_left(
        opsResults, 0, std::plus<long long>()
    );
        
    return result;
}


int main(const int argc, const char** argv) {
    if (argc != 2) {
         throw std::runtime_error("Usage: ./main <filepath>\n");
     }

    std::string path = std::string(INPUT_DIR) + "/" + argv[1];
    std::string input;
    input = loadData(path);

    long long result = solve(input);
    std::cout << "Solution: " << result << '\n';
}