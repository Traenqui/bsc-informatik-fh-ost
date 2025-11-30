#include "kwic.hpp"
#include "word.hpp"
#include <iostream>
#include <sstream>

auto main() -> int
{
    std::cout << "=== KWIC - Keyword in Context ===" << std::endl;
    std::cout << "Enter lines of text (Ctrl+D to finish):" << std::endl;
    std::cout << std::endl;

    text::kwic(std::cin, std::cout);

    return 0;
}
