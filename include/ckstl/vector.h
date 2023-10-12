#pragma once

#include <exception>

#include "memory.h"
#include "iterator.h"


namespace ck {

template<typename T, typename Allocator = Allocator<T>>
class Vector {
public:
    using value_type = T;
    using allocator_type = Allocator;
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

    Vector() = default;

//    explicit Vector(const size_t size) : _data{allocate<T>(size)}, _size{size}, _capacity{size} {}

    explicit Vector(size_t size, const T& value = T{}) : data_{Allocator::allocate(size)}, size_{size},
                                                         capacity_{size} {
        for (size_t i = 0; i < size; i++) {
            data_[i] = value;
        }
    }

    Vector(const Vector& rhs) : data_{Allocator::allocate(rhs.capacity_)}, size_{rhs.size_}, capacity_{rhs.capacity_} {
        std::copy(rhs.data_, rhs.data_ + size_, data_);
    }

    Vector& operator=(Vector rhs) {
        swap(*this, rhs);
        return *this;
    }

    Vector(Vector&& rhs) noexcept: data_{rhs.data_}, size_{rhs.size_}, capacity_{rhs.capacity_} {
        rhs.data_ = nullptr;
        rhs.size_ = 0;
        rhs.capacity_ = 0;
    }

    Vector& operator=(Vector&& rhs) noexcept {
        Vector temp(std::move(rhs));
        swap(*this, temp);

        return *this;
    }

    Vector(std::initializer_list<T> vals)
            : data_{Allocator::allocate(vals.size())}, size_{vals.size()}, capacity_{vals.size()} {
        std::copy(vals.begin(), vals.end(), data_);
    }

    ~Vector() {
        if (data_) {
            destroy_range_(data_, size_);
            Allocator::deallocate(data_);
        }
    }

    friend void swap(Vector& lhs, Vector& rhs) noexcept {
        using std::swap;
        swap(lhs.size_, rhs.size_);
        swap(lhs.capacity_, rhs.capacity_);
        swap(lhs.data_, rhs.data_);
    }

    reference at(size_type index) {
        if (index >= size_) {
            throw std::out_of_range{"Out of bounds"};
        }
        return data_[index];
    }

    const_reference at(size_type index) const {
        if (index >= size_) {
            throw std::out_of_range{"Out of bounds"};
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

    reference operator[](size_type index) noexcept {
        return data_[index];
    }

    const_reference operator[](size_type index) const noexcept {
        return data_[index];
    }

    void push_back(const_reference value) {
        if (size_ >= capacity_) {
            reserve(capacity_ > 0 ? capacity_ * 2 : 1);
        }

        data_[size_] = value;
        size_++;
    }

    template<typename... Args>
    void emplace_back(Args&& ... args) {
        if (size_ >= capacity_) {
            reserve(capacity_ * 2);
        }

        Allocator::construct(&data_[size_], std::forward<Args>(args)...);
        size_++;
    }

    void reserve(size_type capacity) {
        if (capacity > capacity_) {
            T* new_data = Allocator::allocate(capacity);
            for (size_t i = 0; i < size_; i++) {
                new_data[i] = std::move(data_[i]);
            }
            destroy_range_(data_, size_);
            Allocator::deallocate(data_);
            data_ = new_data;
            capacity_ = capacity;
        }
    }

    void resize(size_type new_size, const T& value = T{}) {
        if (new_size > size_) {
            if (new_size > capacity_) {
                if (new_size > capacity_ * 2) {
                    reserve(new_size);
                }
                else {
                    reserve(capacity_ * 2);
                }
                construct_range_(data_ + size_, new_size - size_, value);
                size_ = new_size;
            }
        }
        else if (new_size < size_) {
            destroy_range_(data_ + new_size, size_ - new_size);
            size_ = new_size;
        }
    }

    constexpr void pop_back() {
        resize(size() - 1);
    }

    constexpr size_type size() const {
        return size_;
    }

    constexpr bool empty() const {
        return size_ == 0;
    }

    constexpr size_type capacity() const {
        return capacity_;
    }

    iterator begin() {
        return data_;
    }

    iterator end() {
        return data_ + size_;
    }

    pointer data() {
        return data_;
    }

    const_pointer data() const {
        return data_;
    }

private:
    pointer data_{nullptr};
    size_type size_{0};
    size_type capacity_{0};

    void construct_range_(T* pointer, size_t count, const T& value = T{}) {
        for (size_t i = 0; i < count; i++) {
            Allocator::construct(&pointer[i], value);
        }
    }

    void destroy_range_(T* pointer, size_t count) {
        for (size_t i = 0; i < count; i++) {
            Allocator::destroy(&pointer[i]);
        }
    }
};

}
