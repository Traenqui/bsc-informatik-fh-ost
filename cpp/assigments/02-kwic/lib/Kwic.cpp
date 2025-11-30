#include "kwic.hpp"
#include "word.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace text
{

    using Line = std::vector<Word>;

    void kwic(std::istream &in, std::ostream &out)
    {
        auto comparator = [](Line const &lhs, Line const &rhs)
        {
            return std::lexicographical_compare(
                lhs.begin(), lhs.end(),
                rhs.begin(), rhs.end());
        };

        std::set<Line, decltype(comparator)> allRotations(comparator);

        std::string inputLine;
        while (std::getline(in, inputLine))
        {
            if (inputLine.empty())
            {
                continue; 
            }

            Line words;
            std::istringstream lineStream(inputLine);
            Word w;
            while (lineStream >> w)
            {
                words.push_back(w);
            }

            if (words.empty())
            {
                continue; 
            }

            for (size_t i = 0; i < words.size(); ++i)
            {
                Line rotation = words;
                std::rotate(rotation.begin(), rotation.begin() + i, rotation.end());
                allRotations.insert(rotation);
            }
        }

        for (auto const &line : allRotations)
        {
            for (auto const &w : line)
            {
                out << w << ' ';   
            }
            out << '\n';
        }
            }

        }
