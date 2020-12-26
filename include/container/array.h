#pragma once


namespace ck {

template<typename T, size_t Size>
class Array {
public:
     T& get(size_t index) {
        if (index >= Size) {
            throw "Out of bounds.";
        }
        return _data[index];
    }

    const T& get(size_t index) const {
        if (index >= Size) {
            throw "Out of bounds.";
        }
        return _data[index];
    }

    T& operator[](size_t index) {
        return _data[index];
    }

    const T& operator[](size_t index) const {
        return _data[index];
    }

    size_t size() {
        return Size;
    }

private:
    T _data[Size];
};

}
