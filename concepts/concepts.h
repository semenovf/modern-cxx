#pragma once

#include <type_traits>
#include <iterator>

template <class P, class T>
concept bool Predicate = requires(P p, T t) {
    typename std::enable_if<std::is_same<decltype(p(t)), bool>::value>::type;
};

template <class T>
concept bool RandomAccessIterable = requires(T t, typename T::difference_type n) {
    { t.begin() } -> typename T::iterator;
    { t.end() } -> typename T::iterator;
    { t.begin()[n] } -> decltype(*(std::declval<T>().begin() + n));
};

template <class T>
concept bool Subscriptable = requires(T t) {
    { t[size_t{0}] } -> typename
            std::enable_if<
                !std::is_same<
                    decltype(t[size_t{0}]), void
                >::value, decltype(t[size_t{0}])
            >::type;
};

template <class T>
concept bool Indexable = Subscriptable<T> || RandomAccessIterable<T>;

#include <string>

class String : protected std::string
{
public:
    using iterator = std::string::iterator;

    String () : std::string() {}

    iterator begin () { return std::string::begin(); }
    iterator end () { return std::string::end(); }

    std::string::reference operator [] (size_t ind) {
        return std::string::operator [] (ind);
    }
};

static_assert(Indexable<String>, "fail");
