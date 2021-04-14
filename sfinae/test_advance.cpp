#include <vector>
#include <list>
#include <sstream>
#include <string>
#include <forward_list>

#include <gtest/gtest.h>
#include "advance.h"

TEST(Advance, Forward) {
    std::forward_list<int> l{1, 2, 3, 4, 5};
    auto it = l.begin();
    Advance(it, 2);
    ASSERT_EQ(3, *it);
    Advance(it, 0);
    ASSERT_EQ(3, *it);
}

TEST(Advance, Bidirectional) {
    std::list<std::string> l{"ab", "ba", "aba", "caba"};
    auto first = l.begin();
    Advance(first, 3);
    ASSERT_EQ("caba", *first);
    auto second = l.end();
    Advance(second, -3);
    ASSERT_EQ("ba", *second);
    Advance(second, 0);
    ASSERT_EQ("ba", *second);
}

TEST(Advance, RandomAccess) {
    std::vector<int> l{1, 3, 5, 7, 9};
    auto first = l.begin();
    Advance(first, 1);
    ASSERT_EQ(3, *first);
    auto second = l.end();
    Advance(second, -4);
    ASSERT_EQ(3, *second);
}

TEST(Advance, RandomAccessRaw) {
    int l[] = {-1, 1, 0, 4, 8};
    int *it = l;
    Advance(it, 2);
    ASSERT_EQ(0, *it);
    Advance(it, -1);
    ASSERT_EQ(1, *it);
}

class CheckIterator: public std::iterator<std::random_access_iterator_tag, int> {
public:
    CheckIterator& operator +=(ssize_t n) {
        ++was_called_;
        value_ += n;
        return *this;
    }

    CheckIterator& operator -=(ssize_t n) {
        ++was_called_;
        value_ -= n;
        return *this;
    }

    int CalledCount() const {
        return was_called_;
    }

    ssize_t GetValue() const {
        return value_;
    }
private:
    int was_called_ = 0;
    ssize_t value_ = 0;
};

TEST(Advance, RandomAccessFast) {
    for (int value : {-100, 100}) {
        CheckIterator iterator;
        Advance(iterator, value);
        ASSERT_EQ(value, iterator.GetValue());
        ASSERT_EQ(1, iterator.CalledCount());
    }

    const int n = 100000;
    std::vector<int> v(n);
    auto begin = std::clock();
    for (int i = 0; i < n; ++i) {
        v[i] = i;
        const int *start = v.data();
        Advance(start, i);
        ASSERT_EQ(i, *start);
    }
    auto end = std::clock();
    std::clock_t diff = end - begin;
    double passed = static_cast<double> (diff) / CLOCKS_PER_SEC;
    ASSERT_LE(passed, 0.3);
}

TEST(Advance, Input) {
    std::stringstream stream("1 2 3 4 5");
    std::istream_iterator<int> it(stream);
    Advance(it, 3);
    ASSERT_EQ(4, *it);
}

TEST(Advance, Output) {
    std::vector<int> dummy;
    auto it = std::back_inserter(dummy);
    Advance(it, 1);
}

