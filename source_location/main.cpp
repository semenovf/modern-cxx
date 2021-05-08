#include <iostream>
#include <string>
#include <cassert>

// #if __GNUC__
// #   ifndef GCC_VERSION
// #       define GCC_VERSION (__GNUC__ * 10000 \
//                 + __GNUC_MINOR__ * 100 \
//                 + __GNUC_PATCHLEVEL__)
// #   endif
// #endif

#if defined(__has_include) // C++17
#   if __has_include(<source_location>)
#       include <source_location>
        using source_location = std::source_location;
#       define PFS_NO_STD_SOURCE_LOCATION 0
#   elif __cplusplus > 201103L
#       if __GNUC__ && __has_include(<experimental/source_location>)
#           include <experimental/source_location>
            using source_location = std::experimental::fundamentals_v2::source_location;
#           define PFS_NO_STD_SOURCE_LOCATION 0
#       endif
#   endif
#endif

#ifndef PFS_NO_STD_SOURCE_LOCATION
#   define PFS_NO_STD_SOURCE_LOCATION 1

#   define CURRENT_SOURCE_LOCATION source_location{__LINE__, __FILE__, __PRETTY_FUNCTION__}

class source_location
{
    std::uint_least32_t _line {0};
    std::uint_least32_t _column {0};
    char const * _file_name {nullptr};
    char const * _function_name {nullptr};

public:
    source_location () noexcept = default;
    source_location (source_location const & other) = default;
    source_location (source_location && other) noexcept = default;

    source_location (std::uint_least32_t line
            , char const * file_name
            , char const * function_name
            , std::uint_least32_t column = 0)
        : _line(line)
        , _column(column)
        , _file_name(file_name)
        , _function_name(function_name)
    {}

    std::uint_least32_t line () const noexcept
    {
        return _line;
    }

    std::uint_least32_t column () const noexcept
    {
        return _column;
    }

    char const * file_name () const noexcept
    {
        return _file_name;
    }

    char const * function_name () const noexcept
    {
        return _function_name;
    }
};

#endif

int main ()
{
#if PFS_NO_STD_SOURCE_LOCATION
    source_location loc = CURRENT_SOURCE_LOCATION; auto __test_line = __LINE__;
    std::cout << "Using pre-C++20 custom implementation of source_location\n\n";
    std::cout << loc.file_name()
        << ':' << loc.line()
        << ": " << loc.function_name() << "\n";

    assert(loc.line() == __test_line);
#else
    source_location loc = source_location::current(); auto __test_line = __LINE__;
    std::cout << "Using C++20 implementation of source_location\n\n";
    std::cout << loc.file_name()
        << ':' << loc.line()
        << ": " << loc.function_name() << "\n";

    assert(loc.line() == __test_line);
#endif

    return 0;
}
