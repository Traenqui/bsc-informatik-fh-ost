#include "Pocketcalculator.hpp"
#include "Calc.hpp"
#include "Sevensegment.hpp"

#include <iosfwd>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>

namespace
{
  inline std::size_t printed_width(int value)
  {
    return std::to_string(value).size();
  }
}

auto pocketcalculator(std::istream &input, std::ostream &output) -> void
{
  std::string line;
  while (std::getline(input, line))
  {
    if (line.empty())
    {
      printLargeError(output);
      continue;
    }

    try
    {
      std::istringstream iss(line);
      int a{}, b{};
      char op{};

      if (!(iss >> a >> op >> b))
      {
        throw std::invalid_argument{"invalid format"};
      }

      iss >> std::ws;

      if (iss.peek() != std::char_traits<char>::eof())
      {
        throw std::invalid_argument{"trailing characters"};
      }

      const int result = calc(a, b, op);

      if (printed_width(result) > 8)
      {
        printLargeError(output);
      }
      else
      {
        printLargeNumber(result, output);
      }
    }
    catch (...)
    {
      printLargeError(output);
    }
  }
}
