#pragma once

#include "iterator.h"


namespace ck {

template<typename T, size_t Size>
class Array {
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
        if (index >= Size) {
            throw std::out_of_range{"Out of bounds."};
        }
        return data_[index];
    }

    constexpr const_reference at(size_type index) const {
        if (index >= Size) {
            throw std::out_of_range{"Out of bounds."};
        }
        return data_[index];
    }

    ///
    /// Reverse indexing function. rat(i) == at(size() - i - 1).
    ///
    constexpr reference rat(size_type index) {
        if (index >= Size) {
            throw std::out_of_range{"Out of bounds."};
        }
        return data_[size() - index - 1];
    }

    ///
    /// Reverse indexing function. rat(i) == at(size() - i - 1).
    ///
    constexpr const_reference rat(size_type index) const {
        if (index >= Size) {
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

    constexpr reference front() {
        return data_;
    }

    constexpr const_reference front() const {
        return data_;
    }

    constexpr reference back() {
        return data_[Size - 1];
    }

    constexpr const_reference back() const {
        return data_[Size - 1];
    }

    constexpr pointer data() noexcept {
        return data_;
    }

    constexpr const_pointer data() const noexcept {
        return data_;
    }

    constexpr iterator begin() noexcept {
        // TODO: Not Implemented!
    }

    constexpr const_iterator begin() const noexcept {
        // TODO: Not Implemented!
    }

    constexpr const_iterator cbegin() const noexcept {
        // TODO: Not Implemented!
    }

    constexpr iterator end() noexcept {
        // TODO: Not Implemented!
    }

    constexpr const_iterator end() const noexcept {
        // TODO: Not Implemented!
    }

    constexpr const_iterator cend() const noexcept {
        // TODO: Not Implemented!
    }

    constexpr reverse_iterator rbegin() noexcept {
        // TODO: Not Implemented!
    }

    constexpr const_reverse_iterator rbegin() const noexcept {
        // TODO: Not Implemented!
    }

    constexpr const_reverse_iterator crbegin() const noexcept {
        // TODO: Not Implemented!
    }

    constexpr reverse_iterator rend() noexcept {
        // TODO: Not Implemented!
    }

    constexpr const_reverse_iterator rend() const noexcept {
        // TODO: Not Implemented!
    }

    constexpr const_reverse_iterator crend() const noexcept {
        // TODO: Not Implemented!
    }

    [[nodiscard]] constexpr bool empty() const noexcept {
        return Size == 0;
    }

    [[nodiscard]] constexpr size_type size() const noexcept {
        return Size;
    }

    [[nodiscard]] constexpr size_type max_size() const noexcept {
        return Size;
    }

    constexpr void fill(const T& value) {
        // TODO: Not Implemented!
    }

    constexpr void swap(Array& other) noexcept(std::is_nothrow_swappable_v<T>) {
        // TODO: Not Implemented!
    }

private:
    value_type data_[Size];
};

template<class T, std::size_t N>
constexpr bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    // TODO: Not Implemented!
    return false;
}

template<class T, std::size_t N>
constexpr bool operator<=>(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    // TODO: Not Implemented!
    return false;
}

// TODO: get(), swap(), to_array(), tuple_size(), tuple_element()



}
