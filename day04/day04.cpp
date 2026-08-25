#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <ranges>
#include <string_view>
#include <vector>
#include <algorithm>

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

int removeRolls(const std::string& input) {
    auto rows = lines(input);
    int n = rows.size();
    int m = rows[0].size();

    const std::array<std::pair<int, int>, 8> directions {{
        {-1,-1}, {-1,0}, {-1,1},
        {0,-1},          {0,1},
        {1,-1},  {1,0},  {1,1}
    }};

    int total = 0;

    while (true) {
        int iter = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (rows[i][j] != '@') continue;

                auto neighbors =
                    directions 
                    | std::views::transform([&](auto d) {
                        return std::pair{i + d.first, j + d.second};
                    })
                    | std::views::filter([&](auto p) {
                        auto [r, c] = p;
                        return r >= 0 && r < n && c >= 0 && c < m;
                    });

                int count = std::count_if(neighbors.begin(), neighbors.end(), [&](auto p) {
                    auto [r, c] = p;
                    return rows[r][c] == '@';
                });

                if (count < 4) {
                    iter += 1;
                    rows[i][j] = '.';
                }
            }
        }
        if (iter > 0) total += iter;
        else break;
    }
    return total;
}

// part 2 solution: 8701
int main(const int argc, const char** argv) {
    if (argc != 2) {
         throw std::runtime_error("Usage: ./main <filepath>\n");
     }

    std::string path = std::string(INPUT_DIR) + "/" + argv[1];
    std::string input;
    input = loadData(path);

    int result = removeRolls(input);
    std::cout << "Solution: " << result << '\n';
}