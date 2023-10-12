#pragma once

#include "binary_tree.h"
#include "vector.h"


namespace ck {

constexpr auto parent(auto i) {
    return (i - 1) / 2;
}

constexpr auto left_child(auto i) {
    return 2 * i + 1;
}

constexpr auto right_child(auto i) {
    return 2 * i + 2;
}

template<class RandomIt, class Index, class Compare>
constexpr void sift_down_heap(RandomIt first, Index start, Index end, Compare comp) {
    while (left_child(start) < end) {
        auto child = left_child(start);

        if (child + 1 < end && comp(*(first + child), *(first + child + 1))) {
            ++child;
        }

        if (comp(*(first + start), *(first + child))) {
            std::swap(*(first + start), *(first + child));
            start = child;
        }
        else {
            return;
        }
    }
}

template<class RandomIt>
constexpr bool is_heap(RandomIt first, RandomIt last) {
    // TODO: Implement is_heap
    assert(false && "Not implemented!");
    return false;
}

//template< class ExecutionPolicy, class RandomIt >
//bool is_heap( ExecutionPolicy&& policy, RandomIt first, RandomIt last );

template<class RandomIt, class Compare>
constexpr bool is_heap(RandomIt first, RandomIt last, Compare comp) {
    // TODO: Implement is_heap
    assert(false && "Not implemented!");
    return false;
}

//template< class ExecutionPolicy, class RandomIt, class Compare >
//bool is_heap( ExecutionPolicy&& policy,
//              RandomIt first, RandomIt last, Compare comp );

template<class RandomIt>
constexpr RandomIt is_heap_until(RandomIt first, RandomIt last) {
    // TODO: Implement is_heap_until
    assert(false && "Not implemented!");
    return {};
}

//template< class ExecutionPolicy, class RandomIt >
//RandomIt is_heap_until( ExecutionPolicy&& policy,
//                        RandomIt first, RandomIt last );

template<class RandomIt, class Compare>
constexpr RandomIt is_heap_until(RandomIt first, RandomIt last,
                                 Compare comp) {
    // TODO: Implement is_heap_until
    assert(false && "Not implemented!");
    return {};
}

//template< class ExecutionPolicy, class RandomIt, class Compare >
//RandomIt is_heap_until( ExecutionPolicy&& policy,
//                        RandomIt first, RandomIt last, Compare comp );

template<class RandomIt>
constexpr void make_heap(RandomIt first, RandomIt last) {
    make_heap(first, last, Less<typename RandomIt::value_type>{});
}

template<class RandomIt, class Compare>
constexpr void make_heap(RandomIt first, RandomIt last, Compare comp) {
    const auto size = last - first;

    auto start = size / 2;

    while (start > 0) {
        --start;
        sift_down_heap(first, start, size, comp);
    }
}

template<class RandomIt>
constexpr void push_heap(RandomIt first, RandomIt last) {
    push_heap(first, last, Less<typename RandomIt::value_type>{});
}

template<class RandomIt, class Compare>
constexpr void push_heap(RandomIt first, RandomIt last, Compare comp) {
    const auto size = last - first;

    auto current = size - 1;
    auto par = parent(current);

    while (comp(*(first + par), *(first + current))) {
        std::swap(*(first + par), *(first + current));
        current = par;
        par = parent(current);
    }
}

template<class RandomIt>
constexpr void pop_heap(RandomIt first, RandomIt last) {
    pop_heap(first, last, Less<typename RandomIt::value_type>{});
}

template<class RandomIt, class Compare>
constexpr void pop_heap(RandomIt first, RandomIt last, Compare comp) {
    const auto size = last - first;
    const decltype(size) start = 0;
    const auto end = size - 1;

    std::swap(*first, *(last - 1));
    sift_down_heap(first, start, end, comp);
}

template<class RandomIt>
constexpr void sort_heap(RandomIt first, RandomIt last) {
    sort_heap(first, last, Less<typename RandomIt::value_type>{});
}

template<class RandomIt, class Compare>
constexpr void sort_heap(RandomIt first, RandomIt last, Compare comp) {
    while (first != last)
        pop_heap(first, last--, comp);
}


template<class T, class Container = Vector<T>, class Compare = Less<typename Container::value_type>>
class Heap {
public:
    using container_type = Container;
    using value_compare = Compare;
    using value_type = Container::value_type;
    using size_type = Container::size_type;
    using reference = Container::reference;
    using const_reference = Container::const_reference;

    Heap() = default;

    Heap(const Compare& comp, const Container& cont) : comp_{comp}, container_{cont} {
        ck::make_heap(container_.begin(), container_.end(), comp_);
    }

    Heap(const Compare& comp, Container&& cont) : comp_{comp}, container_{std::move(cont)} {
        ck::make_heap(container_.begin(), container_.end(), comp_);
    }

    template<class InputIt>
    Heap(InputIt first, InputIt last, const Compare& compare = Compare())
            : comp_{compare}, container_(first, last) {
        ck::make_heap(container_.begin(), container_.end(), comp_);
    }

    const_reference top() const {
        return container_.front();
    }

    bool empty() const {
        return container_.empty();
    }

    size_type size() const {
        return container_.size();
    }

    void push(const value_type& value) {
        container_.push_back();
        push_heap(container_.begin(), container_.end(), comp_);
    }

    void push(value_type&& value) {
        container_.push_back();
        push_heap(container_.begin(), container_.end(), comp_);
    }

    void pop() {
        pop_heap(container_.begin(), container_.end(), comp_);
        container_.pop_back();
    }

private:
    Compare comp_;
    Container container_;
};

template<class T, class Container = Vector<T>, class Compare = Less<typename Container::value_type>>
using PriorityQueue = Heap<T, Container, Compare>;

template<class T, class Container = Vector<T>>
using MaxHeap = Heap<T, Container>;

template<class T, class Container = Vector<T>>
using MinHeap = Heap<T, Container, Greater<typename Container::value_type>>;

}
