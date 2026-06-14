cmake_minimum_required(VERSION 3.20)
project(cpp_cinema_predictor)

# 1. Nastavení C++20 standardu
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Definice tvého programu (targetu)
add_executable(cpp_cinema_predictor src/main.cpp include/Matrix.hpp include/Regression.hpp)

# 3. Přidání kompilačních flagů pro tvůj program
target_compile_options(cpp_cinema_predictor PRIVATE
        -Wall
        -Wextra
        -pedantic
        -fsanitize=address,undefined,leak
)

# 4. KRITICKÉ: Sanitizery musíme předat i linkeru, jinak program neslinkuješ!
target_link_options(cpp_cinema_predictor PRIVATE
        -fsanitize=address,undefined,leak
)

add_executable(cinema_tests test/test.cpp include/Matrix.hpp include/Regression.hpp)

target_compile_options(cinema_tests PRIVATE
        -Wall
        -Wextra
        -pedantic
        -fsanitize=address,undefined,leak
)

target_link_options(cinema_tests PRIVATE
        -fsanitize=address,undefined,leak
)