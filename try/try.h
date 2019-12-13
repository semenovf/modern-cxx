#pragma once

#include <functional>
#include <exception>
#include <stdexcept>
#include <memory>
#include <cstring>

// Избавляемся от дублирования кода
class Basic {
protected:
    std::unique_ptr<std::string> what_;
    std::exception_ptr exptr_;

protected:
    Basic () {
    }

    Basic (std::exception const & ex) : what_(new std::string(ex.what())) {
    }

    Basic (std::exception_ptr exptr) : exptr_(exptr) {
    }

public:
    void Throw () {
        if (exptr_) {
            std::rethrow_exception(exptr_);
        } else {
            if (what_)
                throw std::runtime_error(*what_);

            throw std::runtime_error("No exception");
        }
    }

    bool IsFailed () const {
        return static_cast<bool>(what_) || static_cast<bool>(exptr_);
    }
};

template <class T>
class Try : public Basic
{
private:
    std::unique_ptr<T> value_;

public:
    Try () : Basic() {
    }

    Try (T rhs) : Basic(), value_(new T(rhs)) {
    }

    Try (std::exception const & ex) : Basic(ex) {
    }

    Try (std::exception_ptr exptr) : Basic(exptr) {
    }

    T const & Value () const {
        if (what_)
            throw std::runtime_error(*what_);

        if (value_)
            return *value_;

        throw std::runtime_error("Object is empty");
    }
};

template <>
class Try<void> : public Basic
{
public:
    Try (): Basic(std::exception()) {
    }

    Try (const Try&) : Basic() {
    }

    Try (std::exception const & ex) : Basic(ex) {
    }

    Try (std::exception_ptr exptr) : Basic(exptr) {
    }
};

// Избавляемся от дублирования кода
template <class ReturnType>
Try<ReturnType> TryRunHelper(std::function<Try<ReturnType>()> f)
{
    try {
        return f();
    } catch (const std::exception& e) {
        return Try<ReturnType>(std::current_exception());
    } catch (const char* s) {
        return Try<ReturnType>(std::runtime_error(s));
    } catch (int en) {
        return Try<ReturnType>(std::runtime_error(std::strerror(en)));
    } catch (...) {
        return Try<ReturnType>(std::runtime_error("Unknown exception"));
    }
}

template <class Function, class... Args>
auto TryRun(Function func, Args... args)
        -> Try<typename std::enable_if<!std::is_same<void,decltype(func(args...))>::value, decltype(func(args...))>::type> {
    using ReturnType = decltype(func(args...));

    return TryRunHelper<ReturnType>([&func, &args...] {
        ReturnType ret = func(args...);
        return Try<ReturnType>(ret);
    });
}

template <class Function, class... Args>
auto TryRun(Function func, Args... args)
        -> Try<typename std::enable_if<std::is_same<void,decltype(func(args...))>::value>::type> {
    using ReturnType = decltype(func(args...));

    return TryRunHelper<ReturnType>([&func, &args...] {
        func(args...);
        return Try<ReturnType>();
    });
}

// template <class Function, class... Args>
// auto TryRun(Function func, Args... args)
//         -> Try<typename std::enable_if<!std::is_same<void,decltype(func(args...))>::value, decltype(func(args...))>::type> {
//     using ReturnType = decltype(func(args...));
//
//     try {
//         ReturnType ret = func(args...);
//         return Try<ReturnType>(ret);
//     } catch (const std::exception& e) {
//         return Try<ReturnType>(std::current_exception());
//     } catch (const char* s) {
//         return Try<ReturnType>(std::runtime_error(s));
//     } catch (int en) {
//         return Try<ReturnType>(std::runtime_error(std::strerror(en)));
//     } catch (...) {
//         return Try<ReturnType>(std::runtime_error("Unknown exception"));
//     }
// }
//
// template <class Function, class... Args>
// auto TryRun(Function func, Args... args)
//         -> Try<typename std::enable_if<std::is_same<void,decltype(func(args...))>::value>::type> {
//     using ReturnType = decltype(func(args...));
//
//     try {
//         func(args...);
//         return Try<ReturnType>();
//     } catch (const std::exception& e) {
//         return Try<ReturnType>(std::current_exception());
//     } catch (const char* s) {
//         return Try<ReturnType>(std::runtime_error(s));
//     } catch (int en) {
//         return Try<ReturnType>(std::runtime_error(std::strerror(en)));
//     } catch (...) {
//         return Try<ReturnType>(std::runtime_error("Unknown exception"));
//     }
//
//     return Try<ReturnType>(std::exception()/*func(args...)*/);
// }
