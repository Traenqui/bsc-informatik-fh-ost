#ifndef CALC_HPP
#define CALC_HPP

#include <iosfwd>

auto calc(int, int, char) -> int;
auto calc(std::istream &in) -> int;

#endif