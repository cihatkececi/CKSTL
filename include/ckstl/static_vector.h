#pragma once

#include <cstddef>

#include <stdexcept>

#include "iterator.h"


namespace ck {

template<typename T, size_t Capacity>
class StaticVector {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = PointerIterator<value_type>;
    using const_iterator = ConstPointerIterator<value_type>;
    using reverse_iterator = ReverseIterator<PointerIterator<value_type>>;
    using const_reverse_iterator = ReverseIterator<ConstPointerIterator<value_type>>;

    constexpr reference at(size_type index) {
        if (index >= size_) {
            throw std::out_of_range{"Out of bounds."};
        }
        return data_[index];
    }

    constexpr const_reference at(size_type index) const {
        if (index >= size_) {
            throw std::out_of_range{"Out of bounds."};
        }
        return data_[index];
    }

    ///
    /// Reverse indexing function. rat(i) == at(size() - i - 1).
    ///
    constexpr reference rat(size_type index) {
        if (index >= size()) {
            throw std::out_of_range{"Out of bounds."};
        }
        return data_[size() - index - 1];
    }

    ///
    /// Reverse indexing function. rat(i) == at(size() - i - 1).
    ///
    constexpr const_reference rat(size_type index) const {
        if (index >= size()) {
            throw std::out_of_range{"Out of bounds."};
        }
        return data_[size() - index - 1];
    }

    constexpr reference operator[](size_type index) {
        return data_[index];
    }

    constexpr const_reference operator[](size_type index) const {
        return data_[index];
    }

    [[nodiscard]] constexpr size_type capacity() const {
        return Capacity;
    }

    [[nodiscard]] constexpr bool empty() const noexcept {
        return size() == 0;
    }

    [[nodiscard]] constexpr size_type size() const noexcept {
        return size_;
    }

    [[nodiscard]] constexpr size_type max_size() const noexcept {
        return Capacity;
    }

private:
    value_type data_[Capacity];
    size_type size_{0};
};

}
