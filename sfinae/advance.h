#pragma once

#include <cstddef>

template<class Iterator>
inline void ForwardAdvance(Iterator& iterator, ssize_t n) {
    if (n <= 0)
        return;

    while (n--) ++iterator;
}

template<class Iterator>
inline void Advance(Iterator& iterator, ssize_t n, std::forward_iterator_tag) {
    ForwardAdvance(iterator, n);
}

template<class Iterator>
inline void Advance(Iterator& iterator, ssize_t n, std::input_iterator_tag) {
    ForwardAdvance(iterator, n);
}

template<class Iterator>
void Advance(Iterator& iterator, ssize_t n, std::output_iterator_tag) {
    ForwardAdvance(iterator, n);
}

template<class Iterator>
void Advance(Iterator& iterator, ssize_t n, std::bidirectional_iterator_tag) {
    if (n == 0)
        return;

    if (n > 0)
        while (n--) ++iterator;
    else
        while (n++) --iterator;
}

template<class Iterator>
void Advance(Iterator& iterator, ssize_t n, std::random_access_iterator_tag) {
    iterator += n;
}

template<class Iterator>
void Advance(Iterator& iterator, ssize_t n) {
    Advance(iterator, n,
            typename std::iterator_traits<Iterator>::iterator_category());
}
