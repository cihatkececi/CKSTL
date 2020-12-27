#pragma once

#include "memutil.h"


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
    explicit ListIterator(ListNode<T>* node) : _node{node} {}

    ListIterator& operator++() {
        _node = _node->next;
        return *this;
    }

    ListIterator operator++(int) {
        ListIterator temp = *this;
        _node = _node->next;
        return temp;
    }

    ListIterator& operator--() {
        _node = _node->prev;
        return *this;
    }

    ListIterator operator--(int) {
        ListIterator temp = *this;
        _node = _node->prev;
        return temp;
    }

    T& operator*() const {
        return _node->value;
    }

    T* operator->() const {
        return &_node->value;
    }

    bool operator==(const ListIterator& rhs) const {
        return _node == rhs._node;
    }

    bool operator!=(const ListIterator& rhs) const {
        return _node != rhs._node;
    }

protected:
    ListNode<T>* _node;
};


template<typename T>
class ConstListIterator : public ListIterator<T> {
public:
    using ListIterator<T>::ListIterator;

    explicit ConstListIterator(const ListNode<T>* node) : ListIterator<T>::ListIterator{
            const_cast<ListNode<T>*>(node)} {}

    const T& operator*() const {
        return this->_node->value;
    }

    const T* operator->() const {
        return &this->_node->value;
    }
};


template<typename T, typename Allocator = Allocator<T>>
class List {
public:
    using Iterator = ListIterator<T>;
    using ConstIterator = ConstListIterator<T>;
    using NodeAllocator = typename Allocator::template rebind<ListNode<T>>::type;

    List() {
        _end.next = &_end;
        _end.prev = &_end;
    }

    List(size_t n, const T& value = T{}) {
        for (size_t i = 0; i < n; i++) {
            emplace_back(value);
        }
    }

    List(const List& rhs) : List{} {
        for (auto it = rhs.begin(); it != rhs.end(); it++) {
            emplace_back(*it);
        }
//        _size = rhs._size;
    }

    List(List&& rhs) noexcept : _end{std::move(rhs._end)}, _size{rhs._size} {
        _end.next->prev = &_end;
        _end.prev->next = &_end;
        rhs._end.next = &rhs._end;
        rhs._end.prev = &rhs._end;
        rhs._size = 0;
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
        auto node = _end.next;
        while (node != &_end) {
            auto next_node = node->next;
            NodeAllocator::destroy(node);
            NodeAllocator::deallocate(node);
            node = next_node;
        }
    }

    T& back() {
        if (_size > 0) {
            return _end.prev->value;
        }
        throw "List is empty.";

    }

    const T& back() const {
        if (_size > 0) {
            return _end.prev->value;
        }
        throw "List is empty.";

    }

    T& front() {
        if (_size > 0) {
            return _end.next->value;
        }
        throw "List is empty.";

    }

    const T& front() const {
        if (_size) {
            return _end.next->value;
        }
        throw "List is empty.";

    }

    void push_back(const T& value) {
        // TODO: Check constructor type.
        _emplace(&_end, value);
    }

    void push_front(const T& value) {
        // TODO: Check constructor type.
        _emplace(_end.next, value);
    }

    template<typename... Args>
    void emplace_back(Args&& ... args) {
        _emplace(&_end, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void emplace_front(Args&& ... args) {
        _emplace(_end.next, std::forward<Args>(args)...);
    }

    void pop_back() {
        if (_size > 0) {
            _remove_node(_end.prev);
        }
    }

    void pop_front() {
        if (_size > 0) {
            _remove_node(_end.next);
        }
    }

    [[nodiscard]] size_t size() const {
        return _size;
    }

    void remove(const T& value) {
        remove_if([&](const T& rhs) { return rhs == value; });
    }

    template<typename Cond>
    void remove_if(Cond cond) {
        for (auto node = _end.next; node != _end;) {
            ListNode<T>* next = node->next;

            if (cond(node->value)) {
                _remove_node(node);
            }
            node = next;
        }
    }

    Iterator begin() {
        return Iterator{_end.next};
    }

    Iterator begin() const {
        return ConstIterator{_end.next};
    }

    Iterator end() {
        return Iterator(&_end);
    }

    Iterator end() const {
        return ConstIterator(&_end);
    }

    void swap(List& rhs) noexcept {
        std::swap(_size, rhs._size);
        std::swap(_end, rhs._end);
    }

private:
    ListNode<T> _end{};
    size_t _size{0};

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
        _size++;
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