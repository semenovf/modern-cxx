#pragma once
#include <algorithm>
#include <array>
#include <utility>
#include <cstddef>

template<class K, class V, int MaxSize = 8>
class ConstexprMap {
public:
    using value_type = std::pair<K, V>;

public:
    constexpr ConstexprMap() = default;

    constexpr V& operator[](const K& key) {
        for (auto & item: data_) {
            if (item.first == key)
                return item.second;
        }

        if (size_ >= MaxSize)
            throw 0;

        int index = size_;
        size_++;
        data_[index].first = key;
        return data_[index].second;
    }

    constexpr const V& operator[](const K& key) const {
        for (auto & item: data_) {
            if (item.first == key)
                return item.second;
        }

        if (size_ >= MaxSize)
            throw 0;
    }

    constexpr bool Erase(const K& key) {
        int index = -1;

        for (int i = 0; i < size_; i++) {
            if (data_[i].first == key) {
                index = i;
                break;
            }
        }

        if (index >= 0) {
            while (index < size_ - 1) {
                data_[index].first = data_[index + 1].first;
                data_[index].second = data_[index + 1].second;
                index++;
            }

            size_--;
            return true;
        }

        return false;
    }

    constexpr bool Find(const K& key) const {
        for (auto & item: data_) {
            if (item.first == key)
                return true;
        }
        return false;
    }

    constexpr size_t Size() const {
        return size_;
    }

    constexpr std::pair<K, V>& GetByIndex(size_t pos) {
        if (pos >= size_)
            throw 0;

        return data_[pos];
    }

    constexpr const std::pair<K, V>& GetByIndex(size_t pos) const {
        if (pos >= size_)
            throw 0;

        return data_[pos];
    }

private:
    std::array<value_type, MaxSize> data_;
    size_t size_{0};
};
