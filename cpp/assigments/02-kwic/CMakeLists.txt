Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.0
  URL_HASH       "SHA256=75b04c94471a70680f10f5d0d985bd1a96b8941d040d6a7bfd43f6c6b1de9daf"
)

FetchContent_MakeAvailable(Catch2)
cmake_minimum_required(VERSION 3.19)

project("Kwic"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_library("KwicLib" "lib/Kwic.cpp")
target_include_directories("KwicLib" PUBLIC "lib")

add_library("WordLib" "lib/Word.cpp")
target_include_directories("WordLib" PUBLIC "lib")

add_executable("KwicTest" "test/tests.cpp")
target_link_libraries("KwicTest" PRIVATE "KwicLib" "WordLib" "Catch2::Catch2WithMain")

add_executable("KwicApp" "app/main.cpp")
target_link_libraries("KwicApp" PRIVATE "KwicLib" "WordLib")