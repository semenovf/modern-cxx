#pragma once

#include <set>
#include <unordered_set>
#include <type_traits>
#include <iostream>

template <typename T>
struct CleverSetTraits
{
    template <class U>
    static auto test_hashable (U*) -> decltype(std::hash<U>(), bool{true});
    template<typename>
    static auto test_hashable(...) -> std::false_type;

    template <class U>
    static auto test_equality_op (U*) -> decltype(std::declval<U>() == std::declval<U>());
    template<typename>
    static auto test_equality_op(...) -> std::false_type;

    template <class U>
    static auto test_non_equality_op (U*) -> decltype(std::declval<U>() != std::declval<U>());
    template<typename>
    static auto test_non_equality_op(...) -> std::false_type;

    template <class U>
    static auto test_less_op (U*) -> decltype(std::declval<U>() < std::declval<U>());
    template<typename>
    static auto test_less_op(...) -> std::false_type;

    template <class U>
    static auto test_more_op (U*) -> decltype(std::declval<U>() > std::declval<U>());
    template<typename>
    static auto test_more_op(...) -> std::false_type;

    using hashable                 = typename std::is_same<bool, decltype(test_hashable<T>(nullptr))>::type;
    using has_equality_op_type     = typename std::is_same<bool, decltype(test_equality_op<T>(nullptr))>::type;
    using has_non_equality_op_type = typename std::is_same<bool, decltype(test_non_equality_op<T>(nullptr))>::type;
    using has_less_op_type         = typename std::is_same<bool, decltype(test_less_op<T>(nullptr))>::type;
    using has_more_op_type         = typename std::is_same<bool, decltype(test_more_op<T>(nullptr))>::type;
};

template <typename T>
constexpr bool Hashable_v = CleverSetTraits<T>::hashable::value;

template <typename T>
constexpr bool HasEqualityOp_v = CleverSetTraits<T>::has_equality_op_type::value;

template <typename T>
constexpr bool HasNonEqualityOp_v = CleverSetTraits<T>::has_non_equality_op_type::value;

template <typename T>
constexpr bool HasLessOp_v = CleverSetTraits<T>::has_less_op_type::value;

template <typename T>
constexpr bool HasMoreOp_v = CleverSetTraits<T>::has_more_op_type::value;

template <typename T>
inline typename std::enable_if<!CleverSetTraits<T>::has_less_op_type::value
        && CleverSetTraits<T>::has_more_op_type::value, bool>::type
operator < (const T & a, const T & b)
{
    return (a > b);
}

template <typename T>
struct DataType
{
    static constexpr bool variant_1 = Hashable_v<T>
                && (HasEqualityOp_v<T> || HasNonEqualityOp_v<T>);

    static constexpr bool variant_2 = !variant_1
                && (HasLessOp_v<T> || HasMoreOp_v<T>);

    static constexpr bool variant_3 = !(variant_1 || variant_2);

    using type = typename std::conditional<variant_1
            , std::unordered_set<T>
            , typename std::conditional<variant_2
                    , std::set<T>
                    , std::unordered_set<const T *>>::type>::type;
};

template<class T>
class CleverSet {
    template <typename U>
    std::enable_if_t<DataType<U>::variant_1 || DataType<U>::variant_2, bool>
    insert(const U& value)
    {
        return data_.insert(value).second;
    }

    template <typename U>
    std::enable_if_t<DataType<U>::variant_3, bool>
    insert(const U& value)
    {
        return data_.insert(& value).second;
    }

public:
    bool insert(const T& value)
    {
        return insert<T>(value);
    }

    bool erase(const T& value) {
        return data_.erase(value) > 0;
    }

    bool find(const T& value) const {
        auto result = data_.find(value) != data_.end();
        return result;
    }

    size_t size() const {
        return data_.size();
    }

private:
    typename DataType<T>::type data_;
};
