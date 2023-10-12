#pragma once

#include "memory.h"


namespace ck {


template<typename T>
struct ListNode {
    T value;
    ListNode* next;
    ListNode* prev;
};


template<typename T>
class ListIterator {
public:
    explicit ListIterator(ListNode<T>* node) : node_{node} {}

    ListIterator& operator++() {
        node_ = node_->next;
        return *this;
    }

    ListIterator operator++(int) {
        ListIterator temp = *this;
        node_ = node_->next;
        return temp;
    }

    ListIterator& operator--() {
        node_ = node_->prev;
        return *this;
    }

    ListIterator operator--(int) {
        ListIterator temp = *this;
        node_ = node_->prev;
        return temp;
    }

    T& operator*() const {
        return node_->value;
    }

    T* operator->() const {
        return &node_->value;
    }

    bool operator==(const ListIterator& rhs) const {
        return node_ == rhs.node_;
    }

    bool operator!=(const ListIterator& rhs) const {
        return node_ != rhs.node_;
    }

protected:
    ListNode<T>* node_;
};


template<typename T>
class ConstListIterator : public ListIterator<T> {
public:
    using ListIterator<T>::ListIterator;

    explicit ConstListIterator(const ListNode<T>* node) : ListIterator<T>::ListIterator{
            const_cast<ListNode<T>*>(node)} {}

    const T& operator*() const {
        return this->node_->value;
    }

    const T* operator->() const {
        return &this->node_->value;
    }
};


template<typename T, typename Allocator = Allocator<T>>
class List {
public:
    using Iterator = ListIterator<T>;
    using ConstIterator = ConstListIterator<T>;
    using NodeAllocator = typename Allocator::template rebind<ListNode<T>>::type;

    List() {
        end_.next = &end_;
        end_.prev = &end_;
    }

    List(size_t n, const T& value = T{}) {
        for (size_t i = 0; i < n; i++) {
            emplace_back(value);
        }
    }

    List(const List& rhs) : List{} {
        for (auto it = rhs.begin(); it != rhs.end(); ++it) {
            emplace_back(*it);
        }
//        _size = rhs._size;
    }

    List(List&& rhs) noexcept : end_{std::move(rhs.end_)}, size_{rhs.size_} {
        end_.next->prev = &end_;
        end_.prev->next = &end_;
        rhs.end_.next = &rhs.end_;
        rhs.end_.prev = &rhs.end_;
        rhs.size_ = 0;
    }

    List& operator=(List rhs) {
        swap(rhs);
        return *this;
    }

    List& operator=(List&& rhs) noexcept {
        T temp(std::move(rhs));
        swap(temp);

        return *this;
    }

    ~List() {
        auto node = end_.next;
        while (node != &end_) {
            auto next_node = node->next;
            NodeAllocator::destroy(node);
            NodeAllocator::deallocate(node);
            node = next_node;
        }
    }

    T& back() {
        if (size_ > 0) {
            return end_.prev->value;
        }
        throw "List is empty.";

    }

    const T& back() const {
        if (size_ > 0) {
            return end_.prev->value;
        }
        throw "List is empty.";

    }

    T& front() {
        if (size_ > 0) {
            return end_.next->value;
        }
        throw "List is empty.";

    }

    const T& front() const {
        if (size_) {
            return end_.next->value;
        }
        throw "List is empty.";

    }

    void push_back(const T& value) {
        // TODO: Check constructor type.
        _emplace(&end_, value);
    }

    void push_front(const T& value) {
        // TODO: Check constructor type.
        _emplace(end_.next, value);
    }

    template<typename... Args>
    void emplace_back(Args&& ... args) {
        _emplace(&end_, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void emplace_front(Args&& ... args) {
        _emplace(end_.next, std::forward<Args>(args)...);
    }

    void pop_back() {
        if (size_ > 0) {
            _remove_node(end_.prev);
        }
    }

    void pop_front() {
        if (size_ > 0) {
            _remove_node(end_.next);
        }
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }

    void remove(const T& value) {
        remove_if([&](const T& rhs) { return rhs == value; });
    }

    template<typename Cond>
    void remove_if(Cond cond) {
        for (auto node = end_.next; node != end_;) {
            ListNode<T>* next = node->next;

            if (cond(node->value)) {
                _remove_node(node);
            }
            node = next;
        }
    }

    Iterator begin() {
        return Iterator{end_.next};
    }

    Iterator begin() const {
        return ConstIterator{end_.next};
    }

    Iterator end() {
        return Iterator(&end_);
    }

    Iterator end() const {
        return ConstIterator(&end_);
    }

    void swap(List& rhs) noexcept {
        std::swap(size_, rhs.size_);
        std::swap(end_, rhs.end_);
    }

private:
    ListNode<T> end_{};
    size_t size_{0};

    void _link_node(ListNode<T>* new_node, ListNode<T>* pos) {
        new_node->next = pos;
        new_node->prev = pos->prev;
        pos->prev = new_node;
        new_node->prev->next = new_node;
    }

    template<typename... Args>
    void _emplace(ListNode<T>* pos, Args&& ... args) {
        ListNode<T>* new_node = NodeAllocator::allocate(1);
        NodeAllocator::construct(new_node, std::forward<Args>(args)...);
        _link_node(new_node, pos);
//        if (_size == 0) {
//            _link_node(pos, new_node);
//        }
        size_++;
    }

    void _unlink_node(ListNode<T>* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void _remove_node(ListNode<T>* node) {
        _unlink_node(node);
        NodeAllocator::destroy(node);
        NodeAllocator::deallocate(node);
    }
};

}