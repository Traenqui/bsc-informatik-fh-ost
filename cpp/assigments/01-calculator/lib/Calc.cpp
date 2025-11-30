
#include "Calc.hpp"
#include <stdexcept>
#include <string>
#include <limits>
#include <istream>

auto calc(int x, int y, char op) -> int
{
  switch (op) {
  case '+':
    return x + y;
  case '-':
    return x - y;
  case '*':
    return x * y;
  case '/':
    if (y == 0)
      throw std::invalid_argument("Error: Division duch 0");
    return x / y;
  case '%':
    if (y == 0)
      throw std::invalid_argument("Error: Modulo mit 0, wa willsch?");
    return x % y;

  default:
    throw std::invalid_argument{ "unknown operator" };
  }
}

auto calc(std::istream& in) -> int
{
  int a{}, b{};
  char op{};
  if (!(in >> a >> op >> b)) {
    throw std::invalid_argument{ "invalid format" };
  }
  in >> std::ws;
  if (in.peek() != std::char_traits<char>::eof()) {
    throw std::invalid_argument{ "trailing characters" };
  }
  return calc(a, b, op);
}
