#pragma once


namespace ck {

template<class T>
class UniquePtr {
public:

    UniquePtr() : raw_(new T) {}

    explicit UniquePtr(T* raw) : raw_(raw) {}

    UniquePtr(const UniquePtr& other) = delete;

    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr(UniquePtr&& other) noexcept : raw_(other.raw_) {
        other.raw_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        swap(*this, other);
        return *this;
    }

    ~UniquePtr() {
        delete raw_;
    }

    T& operator*() const {
        return *raw_;
    }

    T* operator->() const {
        return raw_;
    }

    explicit operator bool() {
        return raw_ != nullptr;
    }

    T* release() {
        T* temp = raw_;
        raw_ = nullptr;
        return temp;
    }

    void reset(T* new_ptr) {
        T* temp = raw_;
        raw_ = new_ptr;
        delete temp;
    }

    T* get() const {
        return raw_;
    }

private:
    T* raw_;
};


template<class T>
class UniquePtr<T[]> {
public:

    UniquePtr() : raw_(new T{}) {}

    explicit UniquePtr(T raw[]) : raw_(raw) {}

    UniquePtr(const UniquePtr& other) = delete;

    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr(UniquePtr&& other) noexcept : raw_(other.raw_) {
        other.raw_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        swap(*this, other);
        return *this;
    }

    ~UniquePtr() {
        delete[] raw_;
    }

    T& operator[](size_t i) const {
        return raw_[i];
    }

    explicit operator bool() {
        return raw_ != nullptr;
    }

    T* release() {
        T* temp = raw_;
        raw_ = nullptr;
        return temp;
    }

    void reset(T new_ptr[]) {
        T* temp = raw_;
        raw_ = new_ptr;
        delete[] temp;
    }

    T* get() const {
        return raw_;
    }

private:
    T* raw_;
};

}
