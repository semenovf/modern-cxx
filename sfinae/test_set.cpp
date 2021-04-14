#include <vector>
#include <ctime>

#include <gtest/gtest.h>
#include "clever_set.h"


TEST(CleverSet, Simple) {
    CleverSet<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    ASSERT_FALSE(s.find(4));
    ASSERT_TRUE(s.find(1));
    ASSERT_TRUE(s.erase(2));
}

struct FirstHashable {
    int x;

    bool operator==(const FirstHashable& r) const {
        return x == r.x;
    }
};

#define MAKE_HASH(TYPE) template<>\
    struct hash<TYPE> {\
        size_t operator()(const TYPE& x) const {\
            return hasher(x.x);\
        }\
        std::hash<int> hasher;\
    }

namespace std {
    MAKE_HASH(FirstHashable);
}

struct SecondHashable {
    int x;

    bool operator==(const SecondHashable& r) const {
        return x == r.x;
    }
    bool operator!=(const SecondHashable& r) const {
        return x != r.x;
    }
    bool operator<(const SecondHashable& r) const {
        return x < r.x;
    }
};

namespace std {
    MAKE_HASH(SecondHashable);
}

struct ThirdHashable {
    int x;
};

bool operator >(const ThirdHashable& a, const ThirdHashable& b) {
    return a.x > b.x;
}

namespace std {
    MAKE_HASH(ThirdHashable);
}

struct FirstComparable {
    int x;

    bool operator<(const FirstComparable& r) const {
        return x < r.x;
    }
};

struct SecondComparable {
    int x;

    friend bool operator>(const SecondComparable& a, const SecondComparable& b) {
        return a.x > b.x;
    }
};

namespace std {
    MAKE_HASH(SecondComparable);
}

struct FirstBad {
    int x;
};

struct SecondBad {
    int x;

    bool operator==(const SecondBad& r) const {
        return x == r.x;
    }
};

struct ThirdBad {
    int x;
};

namespace std {
    MAKE_HASH(ThirdBad);
}

template<class T>
void TestCase() {
    CleverSet<T> s;
    s.insert(T{1});
    ASSERT_TRUE(s.find(T{1}));
    ASSERT_FALSE(s.insert(T{1}));
    ASSERT_TRUE(s.insert(T{2}));
    ASSERT_TRUE(s.erase(T{2}));
    ASSERT_FALSE(s.erase(T{0}));
}

template<class T>
void LongTest() {
    CleverSet<T> s;
    const int n = 100000;
    for (int i = 0; i < n; ++i)
        ASSERT_TRUE(s.insert(T{n - i - 1}));
    for (int i = 0; i < n; ++i)
        ASSERT_TRUE(s.find(T{i}));
}

template<class T>
void AddressTest() {
    CleverSet<T> s;
    const size_t n = 100;
    std::vector<T> data(n, T{1});
    for (size_t i = 0; i < n; ++i)
        ASSERT_TRUE(s.insert(data[i]));
    ASSERT_EQ(n, s.size());

    CleverSet<T> t;
    T one{2};
    ASSERT_TRUE(t.insert(one));
    for (size_t i = 0; i < n; ++i)
        ASSERT_FALSE(t.insert(one));
    ASSERT_EQ(1u, t.size());
}


TEST(CleverSet, Hashable) {
    TestCase<FirstHashable>();
    TestCase<SecondHashable>();
    TestCase<ThirdHashable>();
    LongTest<FirstHashable>();
}

TEST(CleverSet, Comparable) {
    TestCase<FirstComparable>();
    TestCase<SecondComparable>();
    LongTest<FirstComparable>();
}

TEST(CleverSet, Address) {
    AddressTest<FirstBad>();
    AddressTest<SecondBad>();
    AddressTest<ThirdBad>();
}
