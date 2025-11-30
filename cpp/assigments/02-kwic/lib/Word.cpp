
#include "word.hpp"

#include <algorithm>
#include <cctype>
#include <istream>
#include <ostream>
#include <stdexcept>

namespace text 
{

Word::Word() : value{"default"} {}

Word::Word(std::string const& word) : value{word} {
  if (word.empty()) {
    throw std::invalid_argument("Word cannot be empty");
  }
  
  for (char c : word) {
    if (!std::isalpha(static_cast<unsigned char>(c))) {
      throw std::invalid_argument("Word can only contain alphabetic characters");
    }
  }
}

void Word::print(std::ostream& out) const {
  out << value;
}

void Word::read(std::istream& in) {
  char c;
  while (in.get(c) && !std::isalpha(static_cast<unsigned char>(c))) {
    // Continue
  }
  
  if (!in) {
    in.setstate(std::ios::failbit);
    return;
  }
  
  std::string newWord;
  newWord += c;
  
  while (in.peek() != std::istream::traits_type::eof() && 
         std::isalpha(static_cast<unsigned char>(in.peek()))) {
    in.get(c);
    newWord += c;
  }
  
  value = newWord;
}

char Word::toLower(char c) {
  return std::tolower(static_cast<unsigned char>(c));
}

int Word::compareCaseInsensitive(std::string const& lhs, std::string const& rhs) {
  auto lhsIt = lhs.begin();
  auto rhsIt = rhs.begin();
  
  while (lhsIt != lhs.end() && rhsIt != rhs.end()) {
    char lhsChar = toLower(*lhsIt);
    char rhsChar = toLower(*rhsIt);
    
    if (lhsChar < rhsChar) {
      return -1;
    } else if (lhsChar > rhsChar) {
      return 1;
    }
    
    ++lhsIt;
    ++rhsIt;
  }
  
  if (lhsIt == lhs.end() && rhsIt == rhs.end()) {
    return 0; 
  } else if (lhsIt == lhs.end()) {
    return -1; 
  } else {
    return 1;
  }
}

bool Word::operator==(Word const& other) const {
  return compareCaseInsensitive(value, other.value) == 0;
}

bool Word::operator!=(Word const& other) const {
  return !(*this == other);
}

bool Word::operator<(Word const& other) const {
  return compareCaseInsensitive(value, other.value) < 0;
}

bool Word::operator<=(Word const& other) const {
  return compareCaseInsensitive(value, other.value) <= 0;
}

bool Word::operator>(Word const& other) const {
  return compareCaseInsensitive(value, other.value) > 0;
}

bool Word::operator>=(Word const& other) const {
  return compareCaseInsensitive(value, other.value) >= 0;
}

std::ostream& operator<<(std::ostream& out, Word const& word) {
  word.print(out);
  return out;
}

std::istream& operator>>(std::istream& in, Word& word) {
  word.read(in);
  return in;
}

}
