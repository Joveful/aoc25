cmake_minimum_required(VERSION 3.23)
project(aoc25 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)

include(CTest)
add_test(NAME TestDay01 COMMAND day01 test.txt)
add_test(NAME TestDay02 COMMAND day02 test.txt)
add_test(NAME TestDay03 COMMAND day03 test.txt)

set(day01PassRegex "Solution: 6")
set(day02PassRegex "Solution: 4174379265")
set(day03PassRegex "Solution: 357")

set_property(TEST TestDay01
            PROPERTY PASS_REGULAR_EXPRESSION "${day01PassRegex}"
)   
set_property(TEST TestDay02
            PROPERTY PASS_REGULAR_EXPRESSION "${day02PassRegex}"
)
set_property(TEST TestDay03
            PROPERTY PASS_REGULAR_EXPRESSION "${day03PassRegex}"
)