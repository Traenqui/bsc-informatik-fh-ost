Include(FetchContent)
 
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.0
  URL_HASH       "SHA256=75b04c94471a70680f10f5d0d985bd1a96b8941d040d6a7bfd43f6c6b1de9daf"
)
 
FetchContent_MakeAvailable(Catch2)
cmake_minimum_required(VERSION 3.19)
 
project("PocketCalculator"
    LANGUAGES CXX
)
 
set(CMAKE_CXX_STANDARD 20)
 
add_library(PocketcalculatorLib
  lib/Calc.cpp
  lib/Sevensegment.cpp
  lib/Pocketcalculator.cpp
)
target_include_directories("PocketcalculatorLib" PUBLIC "lib")
 
add_executable("PocketcalculatorTest" "tests/PocketcalculatorTest.cpp")
target_link_libraries("PocketcalculatorTest" PRIVATE "PocketcalculatorLib" "Catch2::Catch2WithMain")
 
add_executable("PocketcalculatorApp" "app/PocketcalculatorApp.cpp")
target_link_libraries("PocketcalculatorApp" PRIVATE "PocketcalculatorLib")