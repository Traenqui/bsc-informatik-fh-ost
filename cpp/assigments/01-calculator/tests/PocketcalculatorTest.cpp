#include "Pocketcalculator.hpp"
#include "Sevensegment.hpp"

#include <catch2/catch_test_macros.hpp>
#include <sstream>

static std::string renderNumber(int v)
{
  std::ostringstream os;
  printLargeNumber(v, os);
  return os.str();
}

static std::string renderError()
{
  std::ostringstream os;
  printLargeError(os);
  return os.str();
}

TEST_CASE("testEmptyStream")
{
  std::istringstream input{};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == "");
}

TEST_CASE("single valid expression: 6*7 -> 42")
{
  std::istringstream input{"6*7\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderNumber(42));
}

TEST_CASE("handles whitespace around tokens")
{
  std::istringstream input{"   6   *   7   \n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderNumber(42));
}

TEST_CASE("multiple lines are processed independently")
{
  std::istringstream input{"1+1\n2*3\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderNumber(2) + renderNumber(6));
}

TEST_CASE("invalid format -> Error")
{
  std::istringstream input{"foo bar\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderError());
}

TEST_CASE("trailing junk -> Error")
{
  std::istringstream input{"1+2 x\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderError());
}

TEST_CASE("unknown operator -> Error")
{
  std::istringstream input{"1$2\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderError());
}

TEST_CASE("division by zero -> Error")
{
  std::istringstream input{"1/0\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderError());
}

TEST_CASE("modulo by zero -> Error")
{
  std::istringstream input{"5%0\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderError());
}

TEST_CASE("exactly 8 characters passes")
{
  // 12345670 + 8 = 12345678 (8 chars)
  std::istringstream input{"12345670+8\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderNumber(12345678));
}

TEST_CASE("nine characters overflows -> Error")
{
  // 123456780 + 9 = 123456789 (9 chars) -> Error
  std::istringstream input{"123456780+9\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderError());
}

TEST_CASE("negative number exactly 8 chars passes")
{
  // 0 - 1234567 = -1234567 (8 chars incl '-')
  std::istringstream input{"0-1234567\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderNumber(-1234567));
}

TEST_CASE("negative number with 9 chars -> Error")
{
  // 0 - 12345678 = -12345678 (9 chars incl '-') -> Error
  std::istringstream input{"0-12345678\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderError());
}

TEST_CASE("good line then bad line")
{
  std::istringstream input{"2+2\nnope\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderNumber(4) + renderError());
}

TEST_CASE("bad line then good line")
{
  std::istringstream input{"nope\n3*3\n"};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == renderError() + renderNumber(9));
}