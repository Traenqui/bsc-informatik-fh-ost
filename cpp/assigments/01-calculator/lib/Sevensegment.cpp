#include "Sevensegment.hpp"

#include <array>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

std::array<std::string, 5> const minus{"   ", "   ", " - ", "   ", "   "};
std::array<std::array<std::string, 5>, 10> const digits{
    {
        {" - ",
         "| |",
         "   ",
         "| |",
         " - "},
        {"   ",
         "  |",
         "   ",
         "  |",
         "   "},
        {" - ",
         "  |",
         " - ",
         "|  ",
         " - "},
        {" - ",
         "  |",
         " - ",
         "  |",
         " - "},
        {"   ",
         "| |",
         " - ",
         "  |",
         "   "},
        {" - ",
         "|  ",
         " - ",
         "  |",
         " - "},
        {" - ",
         "|  ",
         " - ",
         "| |",
         " - "},
        {" - ",
         "  |",
         "   ",
         "  |",
         "   "},
        {" - ",
         "| |",
         " - ",
         "| |",
         " - "},
        {" - ",
         "| |",
         " - ",
         "  |",
         " - "},
    }};

static const std::array<std::string, 5> glyph_E{" - ", "|  ", " - ", "|  ", " - "};
static const std::array<std::string, 5> glyph_r{"   ", "   ", " - ", "|  ", "   "};
static const std::array<std::string, 5> glyph_o{"   ", "   ", " - ", "| |", " - "};

auto printLargeDigit(int digit, std::ostream &output) -> void
{
    if (digit < 0 || digit > 9)
    {
        throw std::invalid_argument("printLargeDigit expects 0..9");
    }

    for (const auto &line : digits[static_cast<std::size_t>(digit)])
    {
        output << line << '\n';
    }
}

inline const std::array<std::string, 5> &glyphFor(char c)
{
    if (c == '-')
        return minus;
    return digits[static_cast<std::size_t>(c - '0')];
}

auto printLargeNumber(int i, std::ostream &output) -> void
{
    const std::string text = std::to_string(i);

    for (int row = 0; row < 5; ++row)
    {
        for (std::size_t col = 0; col < text.size(); ++col)
        {
            const auto &glyph = glyphFor(text[col]);
            output << glyph[static_cast<std::size_t>(row)];
        }
        output << '\n';
    }
}

auto printLargeError(std::ostream &out) -> void
{
    const std::array<const std::array<std::string, 5> *, 5> word{
        &glyph_E, &glyph_r, &glyph_r, &glyph_o, &glyph_r};

    for (int row = 0; row < 5; ++row)
    {
        for (std::size_t i = 0; i < word.size(); ++i)
        {
            out << (*word[i])[static_cast<std::size_t>(row)];
        }
        out << '\n';
    }
}