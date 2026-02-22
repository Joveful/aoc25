#include <charconv>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <ranges>
#include <string_view>

void loadData(const std::string& filepath, std::string& s) {
    std::ifstream in(filepath);
    if (!in) {
        throw std::runtime_error("Could not open file");
    }

    std::getline(in, s);
}

template<typename T>
int numOfDigits(T number) {
    int digits = 0;
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

[[nodiscard]] constexpr auto lines(std::string_view sv) {
    return sv
        | std::views::split(',')
        | std::views::transform([](auto r) { return std::string_view(r); });
}

long long solve(std::string_view str) {
    auto ll = lines(str);
    long long sum = 0;
    long long v1{}, v2{};

    for (auto line : ll) {
        // Extract top (v2) and bottom (v1) of the dash-separated range
        auto ptr = std::from_chars(line.begin(), line.end(), v1).ptr;
        ptr++;
        std::from_chars(ptr, line.end(), v2);

        for (long long i = v1; i <= v2; i++) {
            int digits = numOfDigits(i);
            for (int j = 1; j < digits; j++) {
                if (digits % j == 0) {
                    long long sep = std::pow(10, digits - j + 1);
                    long long pattern = i / sep;
                    long long ssum = 0;
                    for (int k = j; k < digits; k += j) {
                        long long sep2 = std::pow(10, digits - k + 1);
                        long long p2 = i / sep2;
                        std::cout << i << " " << pattern << " " << p2 % (long long) std::pow(10, k) << '\n';
                        if ((p2 % (long long) std::pow(10, j - 1)) == 0) {
                            ssum = i;
                        } else { 
                            ssum = 0;

                            break; }
                    }
                    sum += ssum;
                }
            }
            /* Part 1
            if (numOfDigits(i) % 2 == 0) {
                long long sep = std::pow(10, numOfDigits(i) / 2);
                long long tmp = i / sep;

                if ((i % sep) == tmp) {
                    sum += i;
                }
            }
            */
        }
    }
    return sum;
}

int main(int argc, const char** argv) {
    if (argc < 2) {
        throw std::runtime_error("Give filepath as argument\n");
    }

    std::string file{argv[1]};
    std::string input;
    loadData(file, input);
    std::cout << solve(input) << '\n';
}
