#ifndef SEVENSEGMENT_HPP_
#define SEVENSEGMENT_HPP_

#include <iosfwd>

auto printLargeDigit(int digit, std::ostream &out) -> void;

auto printLargeNumber(int number, std::ostream &out) -> void;

auto printLargeError(std::ostream &out) -> void;

#endif