#pragma once


namespace ck {

template<typename T>
class ConstPointerIterator {
public:
    // TODO: Implement!

private:

};

template<typename T>
class PointerIterator {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::contiguous_iterator_tag;

    PointerIterator() = default;

    PointerIterator(pointer ptr) : ptr_(ptr) {}

    reference operator*() const {
        return *ptr_;
    }

    pointer operator->() const {
        return ptr_;
    }

    PointerIterator& operator++() {
        ++ptr_;
        return *this;
    }

    PointerIterator operator++(int) {
        PointerIterator temp{*this};
        ++ptr_;
        return temp;
    }

    PointerIterator& operator--() {
        --ptr_;
        return *this;
    }

    PointerIterator operator--(int) {
        PointerIterator temp{*this};
        --ptr_;
        return temp;
    }

    reference operator[](difference_type n) const {
        return ptr_[n];
    }

    PointerIterator& operator+=(difference_type n) {
        ptr_ += n;
        return *this;
    }

    PointerIterator operator+(difference_type n) const {
        return PointerIterator(ptr_ + n);
    }

    PointerIterator& operator-=(difference_type n) {
        ptr_ -= n;
        return *this;
    }

    PointerIterator operator-(difference_type n) const {
        return PointerIterator(ptr_ - n);
    }

    difference_type operator-(const PointerIterator& other) const {
        return ptr_ - other.ptr_;
    }

    bool operator==(const PointerIterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const PointerIterator& other) const {
        return ptr_ != other.ptr_;
    }

    bool operator<(const PointerIterator& other) const {
        return ptr_ < other.ptr_;
    }

    bool operator<=(const PointerIterator& other) const {
        return ptr_ <= other.ptr_;
    }

    bool operator>(const PointerIterator& other) const {
        return ptr_ > other.ptr_;
    }

    bool operator>=(const PointerIterator& other) const {
        return ptr_ >= other.ptr_;
    }

private:
    pointer ptr_;
};

template<typename T>
PointerIterator<T> operator+(typename PointerIterator<T>::difference_type n, const PointerIterator<T>& it) {
    return {it->ptr_ + n};
}

template<typename BaseIt>
class ReverseIterator {
public:
    explicit ReverseIterator(BaseIt base) : base_(base) {}

private:
    BaseIt base_{};
};

template<typename TContainer>
class BackInsertIterator {
public:
    using iterator_category = std::output_iterator_tag;
    using value_type        = void;
    using pointer           = void;
    using reference         = void;
    using container_type = TContainer;
    using difference_type = ptrdiff_t;

    constexpr BackInsertIterator(TContainer& container) : container_(container) {}

    constexpr BackInsertIterator& operator=(const typename TContainer::reference_type val) {
        container_->push_back(val);
        return *this;
    }

    constexpr BackInsertIterator& operator=(typename TContainer::value_type&& val) {
        container_->push_back(std::move(val));
        return *this;
    }

    constexpr BackInsertIterator& operator*() noexcept {
        return *this;
    }

    constexpr BackInsertIterator& operator++() noexcept {
        return *this;
    }

    constexpr BackInsertIterator operator++(int) noexcept {
        return *this;
    }
    
private:
    TContainer* container_;
};

template<typename TContainer>
constexpr BackInsertIterator<TContainer> back_inserter(TContainer& container) noexcept {
    return {container};
}


template<typename TContainer>
class FrontInsertIterator {
public:
    using iterator_category = std::output_iterator_tag;
    using value_type        = void;
    using pointer           = void;
    using reference         = void;
    using container_type = TContainer;
    using difference_type = ptrdiff_t;

    constexpr FrontInsertIterator(TContainer& container) : container_(container) {}

    constexpr FrontInsertIterator& operator=(const typename TContainer::reference_type val) {
        container_->push_front(val);
        return *this;
    }

    constexpr FrontInsertIterator& operator=(typename TContainer::value_type&& val) {
        container_->push_front(std::move(val));
        return *this;
    }

    constexpr FrontInsertIterator& operator*() noexcept {
        return *this;
    }

    constexpr FrontInsertIterator& operator++() noexcept {
        return *this;
    }

    constexpr FrontInsertIterator operator++(int) noexcept {
        return *this;
    }

private:
    TContainer* container_;
};

template<typename TContainer>
constexpr FrontInsertIterator<TContainer> front_inserter(TContainer& container) noexcept {
    return {container};
}

}
