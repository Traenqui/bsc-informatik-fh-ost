#include "kwic.hpp"
#include "word.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// ==================== Word Tests ====================

TEST_CASE("test_cannot_create_empty_word")
{
  REQUIRE_THROWS_AS(Word{""}, std::invalid_argument);
}

TEST_CASE("test_cannot_create_word_with_space")
{
  REQUIRE_THROWS_AS(Word{"abc xyz"}, std::invalid_argument);
}

TEST_CASE("test_cannot_create_word_with_number")
{
  REQUIRE_THROWS_AS(Word{"abc3xyz"}, std::invalid_argument);
}

TEST_CASE("test_cannot_create_word_with_punctuation")
{
  REQUIRE_THROWS_AS(Word{"abc.xyz"}, std::invalid_argument);
}

TEST_CASE("test_output_operator")
{
  std::string const expected{"Python"};
  Word const w{expected};
  std::ostringstream output{};
  output << w;
  REQUIRE(output.str() == expected);
}

TEST_CASE("test_default_word_is_not_empty")
{
  std::ostringstream os{};
  Word w{};
  os << w;
  REQUIRE(os.str() != std::string{});
}

TEST_CASE("test_same_words_are_equal")
{
  REQUIRE(Word{"Ruby"} == Word{"Ruby"});
}

TEST_CASE("test_different_words_are_not_equal")
{
  REQUIRE_FALSE(Word{"ML"} == Word{"Haskell"});
}

TEST_CASE("test_same_word_with_different_cases_are_equal")
{
  REQUIRE(Word{"basic"} == Word{"BASIC"});
}

TEST_CASE("test_same_word_is_not_lower_than")
{
  REQUIRE(!(Word{"Erlang"} < Word{"Erlang"}));
}

TEST_CASE("test_smaller_word_is_smaller")
{
  REQUIRE(Word{"Erlang"} < Word{"Fortran"});
}

TEST_CASE("test_smaller_word_with_capital_letters_is_smaller")
{
  REQUIRE(Word{"ADA"} < Word{"java"});
}

TEST_CASE("test_same_word_with_different_cases_are_not_smaller")
{
  REQUIRE(!(Word{"Groovy"} < Word{"groovy"}));
}

TEST_CASE("test_greater_word_is_greater")
{
  REQUIRE(Word{"Rust"} > Word{"Prolog"});
}

TEST_CASE("test_greater_word_with_capital_letters_is_greater")
{
  REQUIRE(Word{"Lisp"} > Word{"brainfuck"});
}

TEST_CASE("test_smaller_word_is_less_equal")
{
  REQUIRE(Word{"Algol"} <= Word{"BCPL"});
}

TEST_CASE("test_same_word_is_less_equal")
{
  REQUIRE(Word{"Assembler"} <= Word{"Assembler"});
}

TEST_CASE("test_greater_word_is_greater_equal")
{
  REQUIRE(Word{"RPG"} >= Word{"Perl"});
}

TEST_CASE("test_same_word_is_greater_equal")
{
  REQUIRE(Word{"Scala"} >= Word{"Scala"});
}

TEST_CASE("test_input_operator_single_word")
{
  std::istringstream input{"Elixir"};
  Word w{};
  input >> w;
  REQUIRE(w == Word{"Elixir"});
}

TEST_CASE("test_input_operator_single_word_stream_good")
{
  std::istringstream input{"Cobol"};
  Word w{};
  REQUIRE(static_cast<bool>(input >> w));
}

TEST_CASE("test_input_operator_called_once_first_word")
{
  std::istringstream input{"Ceylon Go"};
  Word w{};
  input >> w;
  REQUIRE(w == Word{"Ceylon"});
}

TEST_CASE("test_input_operator_called_once_stream_good")
{
  std::istringstream input{"Lua Oberon"};
  Word w{};
  REQUIRE(input >> w);
}

TEST_CASE("test_input_operator_on_empty_stream_fail")
{
  std::istringstream input{};
  Word w{};
  input >> w;
  REQUIRE(input.fail());
}

TEST_CASE("test_input_operator_on_stream_without_word")
{
  std::istringstream input{"1337"};
  Word w{};
  input >> w;
  REQUIRE(input.fail());
}

TEST_CASE("test_input_operator_on_empty_stream_word_unchanged")
{
  std::istringstream input{};
  Word w{"Eiffel"};
  input >> w;
  REQUIRE(w == Word{"Eiffel"});
}

TEST_CASE("test_input_operator_stops_on_slash")
{
  std::istringstream input{"PL/SQL"};
  Word w{};
  input >> w;
  REQUIRE(w == Word{"PL"});
}

TEST_CASE("test_input_operator_stops_at_end_of_word")
{
  std::istringstream input{"VB6"};
  Word w{};
  int i{};
  input >> w >> i;
  REQUIRE(i == 6);
}

TEST_CASE("test_input_operator_skips_leading_non_alpha")
{
  std::istringstream input{"3switchBF"};
  Word w{};
  input >> w;
  REQUIRE(w == Word{"switchBF"});
}

TEST_CASE("test_input_operator_overwrites_word")
{
  std::istringstream input{"Kotlin"};
  Word w{"JavaScript"};
  input >> w;
  REQUIRE(w == Word{"Kotlin"});
}

TEST_CASE("test_exercise_example")
{
  std::istringstream input{"compl33tely ~ weird !!?!! 4matted in_put"};
  Word w{};
  input >> w;
  REQUIRE(w == Word{"compl"});
  input >> w;
  REQUIRE(w == Word{"tely"});
  input >> w;
  REQUIRE(w == Word{"weird"});
  input >> w;
  REQUIRE(w == Word{"matted"});
  input >> w;
  REQUIRE(w == Word{"in"});
  input >> w;
  REQUIRE(w == Word{"put"});
  input >> w;
  REQUIRE(w == Word{"put"});
}

// ==================== KWIC Tests ====================

TEST_CASE("kwic_basic_example")
{
  std::istringstream input{"this is a test\nthis is another test"};
  std::ostringstream output;

  text::kwic(input, output);

  std::string expected =
      "a test this is\n"
      "another test this is\n"
      "is a test this\n"
      "is another test this\n"
      "test this is a\n"
      "test this is another\n"
      "this is a test\n"
      "this is another test\n";

  REQUIRE(output.str() == expected);
}

TEST_CASE("kwic_clarifying_example")
{
  std::istringstream input{"a b c d\na a b\nb b c"};
  std::ostringstream output;

  text::kwic(input, output);

  std::string expected =
      "a a b\n"
      "a b a\n"
      "a b c d\n"
      "b a a\n"
      "b b c\n"
      "b c b\n"
      "b c d a\n"
      "c b b\n"
      "c d a b\n"
      "d a b c\n";

  REQUIRE(output.str() == expected);
}

TEST_CASE("kwic_single_line")
{
  std::istringstream input{"hello world"};
  std::ostringstream output;

  text::kwic(input, output);

  std::string expected =
      "hello world\n"
      "world hello\n";

  REQUIRE(output.str() == expected);
}

TEST_CASE("kwic_single_word")
{
  std::istringstream input{"lonely"};
  std::ostringstream output;

  text::kwic(input, output);

  std::string expected = "lonely\n";

  REQUIRE(output.str() == expected);
}

TEST_CASE("kwic_empty_input")
{
  std::istringstream input{""};
  std::ostringstream output;

  text::kwic(input, output);

  REQUIRE(output.str() == "");
}

TEST_CASE("kwic_case_insensitive_sorting")
{
  std::istringstream input{"Apple banana\nBanana apple"};
  std::ostringstream output;

  text::kwic(input, output);

  std::string expected =
      "Apple banana\n"
      "banana Apple\n";

  REQUIRE(output.str() == expected);
}

TEST_CASE("kwic_ignores_punctuation")
{
  std::istringstream input{"hello, world!\nworld! hello,"};
  std::ostringstream output;

  text::kwic(input, output);

  std::string expected =
      "hello world\n"
      "world hello\n";

  REQUIRE(output.str() == expected);
}

TEST_CASE("kwic_duplicate_lines")
{
  std::istringstream input{"same line\nsame line"};
  std::ostringstream output;

  text::kwic(input, output);

  std::string expected =
      "line same\n"
      "same line\n";

  REQUIRE(output.str() == expected);
}

TEST_CASE("kwic_empty_lines_ignored")
{
  std::istringstream input{"first line\n\nsecond line"};
  std::ostringstream output;

  text::kwic(input, output);

  std::string expected =
      "first line\n"
      "line first\n"
      "line second\n"
      "second line\n";

  REQUIRE(output.str() == expected);
}

TEST_CASE("kwic_multiple_spaces")
{
  std::istringstream input{"one  two   three"};
  std::ostringstream output;

  text::kwic(input, output);

  std::string expected =
      "one two three\n"
      "three one two\n"
      "two three one\n";

  REQUIRE(output.str() == expected);
}
