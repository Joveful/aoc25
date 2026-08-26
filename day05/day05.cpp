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

int solve(std::string_view sv) {
    auto data = lines(sv);

    auto ranges = data
        | std::views::filter([](std::string& s) {
            return s.contains('-');
        })
        | std::views::transform([](std::string& s) {
            long long fst, snd;
            auto [ptr, _] = std::from_chars(s.data(), s.data() + s.size(), fst);
            std::from_chars(++ptr, s.data() + s.size(), snd);
            return std::pair<long long,long long>{fst, snd};
        })
        | std::ranges::to<std::vector<std::pair<long long, long long>>>();

    auto ingredients = data
        | std::views::filter([](std::string& s) {
            return !s.contains('-') && !s.empty();
        })
        | std::views::transform([](std::string& s) {
            return std::stoll(s);
        });

    std::ranges::sort(ranges);
    long long validIds = 0;
    if (!ranges.empty()) {
        auto [start, end] = ranges.front();
        for (auto [nextStart, nextEnd] : ranges | std::views::drop(1)) {
            if (nextStart <= end + 1) {
                end = std::max(end, nextEnd);
            } else {
                validIds += end - start + 1;
                start = nextStart;
                end = nextEnd;
            }
        }
        validIds += end - start + 1;
    }
    std::println("Number of valid IDs: {}", validIds);


    int count = std::count_if(ingredients.begin(), ingredients.end(), [&](long long x) {
        return std::any_of(ranges.begin(), ranges.end(), [&](auto p) {
            return p.first <= x && p.second >= x;
        });
    });

    return count;
}


int main(const int argc, const char** argv) {
    if (argc != 2) {
         throw std::runtime_error("Usage: ./main <filepath>\n");
     }

    std::string path = std::string(INPUT_DIR) + "/" + argv[1];
    std::string input;
    input = loadData(path);

    int result = solve(input);
    std::cout << "Solution: " << result << '\n';
}