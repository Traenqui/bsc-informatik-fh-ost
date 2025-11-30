#ifndef INDEXABLE_SET_HPP
#define INDEXABLE_SET_HPP

#include <set>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <string>

template <typename T, typename Compare = std::less<T>>
class IndexableSet : public std::set<T, Compare>
{
public:
    using std::set<T, Compare>::set;

    const T &front() const
    {
        if (this->empty())
            throw std::out_of_range("set is empty");
        return *this->begin();
    }

    const T &back() const
    {
        if (this->empty())
            throw std::out_of_range("set is empty");
        return *this->rbegin();
    }

    const T &operator[](ptrdiff_t index) const
    {
        return at(index);
    }

    const T &at(ptrdiff_t index) const
    {
        ptrdiff_t sz = static_cast<ptrdiff_t>(this->size());
        if (index < 0)
            index += sz;
        if (index < 0 || index >= sz)
            throw std::out_of_range("index out of range");
        auto it = this->begin();
        std::advance(it, index);
        return *it;
    }
};

struct caselessCompare
{
    bool operator()(const std::string &a, const std::string &b) const
    {
        std::string lower_a = a;
        std::string lower_b = b;
        std::transform(lower_a.begin(), lower_a.end(), lower_a.begin(), ::tolower);
        std::transform(lower_b.begin(), lower_b.end(), lower_b.begin(), ::tolower);
        return lower_a < lower_b;
    }
};

#endif