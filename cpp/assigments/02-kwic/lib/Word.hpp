#ifndef WORD_HPP_
#define WORD_HPP_

#include <iosfwd>
#include <string>

namespace text 
{

class Word {
public:
  Word();
  
  explicit Word(std::string const& word);
  
  void print(std::ostream& out) const;
  void read(std::istream& in);
  
  bool operator==(Word const& other) const;
  bool operator!=(Word const& other) const;
  bool operator<(Word const& other) const;
  bool operator<=(Word const& other) const;
  bool operator>(Word const& other) const;
  bool operator>=(Word const& other) const;
  
private:
  std::string value;
  
  static char toLower(char c);
  static int compareCaseInsensitive(std::string const& lhs, std::string const& rhs);
};

std::ostream& operator<<(std::ostream& out, Word const& word);
std::istream& operator>>(std::istream& in, Word& word);

}

#endif
