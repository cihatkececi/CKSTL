#pragma once

#include <exception>

#include "memutil.h"


namespace ck {

template<typename T, typename Allocator = Allocator<T>>
class Vector {
public:
    Vector() : _data{nullptr}, _size{0}, _capacity{0} {}

//    explicit Vector(const size_t size) : _data{allocate<T>(size)}, _size{size}, _capacity{size} {}

    explicit Vector(size_t size, const T& value = T{}) : _data{Allocator::allocate(size)}, _size{size}, _capacity{size} {
        for (size_t i = 0; i < size; i++) {
            _data[i] = value;
        }
    }

    Vector(const Vector& rhs) : _data{Allocator::allocate(rhs._capacity)}, _size{rhs._size}, _capacity{rhs._capacity}  {
        std::copy(rhs._data, rhs._data+_size, _data);
    }

    Vector& operator=(Vector rhs) {
        swap(rhs);
        return *this;
    }

    Vector(Vector&& rhs) noexcept : _data{rhs._data}, _size{rhs._size}, _capacity{rhs._capacity} {
        rhs._data = nullptr;
        rhs._size = 0;
        rhs._capacity = 0;
    }

    Vector& operator=(Vector&& rhs) noexcept {
        T temp(std::move(rhs));
        swap(temp);

        return *this;
    }

    ~Vector() {
        if (_data) {
            _destroy_range(_data, _size);
            Allocator::deallocate(_data);
        }
    }

    void swap(Vector& rhs) noexcept {
        std::swap(_size, rhs._size);
        std::swap(_capacity, rhs._capacity);
        std::swap(_data, rhs._data);
    }

    T& get(size_t index) {
        if (index >= _size) {
            throw "Out of bounds";
        }
        return _data[index];
    }

    const T& get(size_t index) const {
        if (index >= _size) {
            throw "Out of bounds";
        }
        return _data[index];
    }

    T& operator[](size_t index) noexcept {
        return _data[index];
    }

    const T& operator[](size_t index) const noexcept {
        return _data[index];
    }

    void push_back(const T& value) {
        if (_size >= _capacity) {
            reserve(_capacity > 0 ? _capacity * 2 : 1);
        }

        _data[_size] = value;
        _size++;
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (_size >= _capacity) {
            reserve(_capacity * 2);
        }

        Allocator::construct(&_data[_size], std::forward<Args>(args)...);
        _size++;
    }

    void reserve(size_t capacity) {
        if (capacity > _capacity) {
            T* new_data = Allocator::allocate(capacity);
            for (size_t i = 0; i < _size; i++) {
                new_data[i] = std::move(_data[i]);
            }
            _destroy_range(_data, _size);
            Allocator::deallocate(_data);
            _data = new_data;
            _capacity = capacity;
        }
    }

    void resize(size_t new_size, const T& value = T{}) {
        if (new_size > _size) {
            if (new_size > _capacity) {
                if (new_size > _capacity * 2) {
                    reserve(new_size);
                }
                else {
                    reserve(_capacity * 2);
                }
                _construct_range(_data + _size, new_size - _size, value);
                _size = new_size;
            }
        }
        else if (new_size < _size) {
            _destroy_range(_data + new_size, _size - new_size);
            _size = new_size;
        }
    }

    constexpr size_t size() const {
        return _size;
    }

    constexpr bool empty() const {
        return _size == 0;
    }

    constexpr size_t capacity() const {
        return _capacity;
    }


private:
    T *_data;
    size_t _size;
    size_t _capacity;

    void _construct_range(T* pointer, size_t count, const T& value = T{}) {
        for (size_t i = 0; i < count; i++) {
            Allocator::construct(&pointer[i], value);
        }
    }

    void _destroy_range(T* pointer, size_t count) {
        for (size_t i = 0; i < count; i++) {
            Allocator::destroy(&pointer[i]);
        }
    }
};

}
