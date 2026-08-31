cmake_minimum_required(VERSION 3.23)
project(aoc25 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
add_subdirectory(day06)

include(CTest)
add_test(NAME TestDay01 COMMAND day01 test.txt)
add_test(NAME TestDay02 COMMAND day02 test.txt)
add_test(NAME TestDay03 COMMAND day03 test.txt)
add_test(NAME TestDay04 COMMAND day04 test.txt)
add_test(NAME TestDay05 COMMAND day05 test.txt)
add_test(NAME TestDay06 COMMAND day06 test.txt)

set(day01PassRegex "Solution: 6")
set(day02PassRegex "Solution: 4174379265")
set(day03PassRegex "Solution: 3121910778619")
set(day04PassRegex "Solution: 43")
set(day05PassRegex "Solution: 3, 14")
set(day06PassRegex "Solution: 3263827")

set_property(TEST TestDay01
            PROPERTY PASS_REGULAR_EXPRESSION "${day01PassRegex}"
)   
set_property(TEST TestDay02
            PROPERTY PASS_REGULAR_EXPRESSION "${day02PassRegex}"
)
set_property(TEST TestDay03
            PROPERTY PASS_REGULAR_EXPRESSION "${day03PassRegex}"
)
set_property(TEST TestDay04
            PROPERTY PASS_REGULAR_EXPRESSION "${day04PassRegex}"
)
set_property(TEST TestDay05
            PROPERTY PASS_REGULAR_EXPRESSION "${day05PassRegex}"
)
set_property(TEST TestDay06
            PROPERTY PASS_REGULAR_EXPRESSION "${day06PassRegex}"
)