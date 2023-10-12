#pragma once

#include "red_black_tree.h"
#include "pair.h"


namespace ck {


template<typename Compare>
class MapValueCompare {
public:

private:

};

template<typename T>
class MapIterator {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::bidirectional_iterator_tag;
    using tree_iterator = BinaryTreeDefaultIterator<T>;

    MapIterator() = default;

    reference operator*() const {
        return *this;
    }

    pointer operator->() const {
        return this;
    }

    MapIterator& operator++() {
        tree_iterator_++;
        return *this;
    }

    MapIterator operator++(int) {
        MapIterator temp{*this};
        tree_iterator_++;
        return temp;
    }

    MapIterator& operator--() {
        tree_iterator_--;
        return *this;
    }

    MapIterator operator--(int) {
        MapIterator temp{*this};
        tree_iterator_--;
        return temp;
    }

    bool operator==(const MapIterator& other) const {
        return tree_iterator_ == other.tree_iterator_;
    }

    bool operator!=(const MapIterator& other) const {
        return tree_iterator_ != other.tree_iterator_;
    }

private:
    tree_iterator tree_iterator_{};
};

template<typename T>
class ConstMapIterator {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using reference = const T&;
    using pointer = const T*;
    using iterator_category = std::bidirectional_iterator_tag;
    using tree_iterator = BinaryTreeDefaultIterator<T>;

    ConstMapIterator() = default;

    reference operator*() const {
        return *this;
    }

    pointer operator->() const {
        return this;
    }

    ConstMapIterator& operator++() {
        tree_it_++;
        return *this;
    }

    ConstMapIterator operator++(int) {
        ConstMapIterator temp{*this};
        tree_it_++;
        return temp;
    }

    ConstMapIterator& operator--() {
        tree_it_--;
        return *this;
    }

    ConstMapIterator operator--(int) {
        ConstMapIterator temp{*this};
        tree_it_--;
        return temp;
    }

    bool operator==(const ConstMapIterator& other) const {
        return tree_it_ == other.tree_it_;
    }

    bool operator!=(const ConstMapIterator& other) const {
        return tree_it_ != other.tree_it_;
    }

private:
    tree_iterator tree_it_{};
};


template<typename TKey, typename TVal,
        typename Compare = Less<TKey>, typename Allocator = Allocator<Pair<const TKey, TVal>>>
class Map {
public:
    using key_type = TKey;
    using mapped_type = TVal;
    using value_type = Pair<const TKey, TVal>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = Compare;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename AllocatorTraits<Allocator>::pointer;
    using const_pointer = typename AllocatorTraits<Allocator>::const_pointer;
    using iterator = MapIterator<value_type>;
    using const_iterator = ConstMapIterator<value_type>;
    using reverse_iterator = ReverseIterator<MapIterator<value_type>>;
    using const_reverse_iterator = ReverseIterator<ConstMapIterator<value_type>>;
    using node_type = void; // TODO: Set node_type
    using insert_return_type = void; // TODO: Set insert_return_type

    using value_compare = MapValueCompare<Compare>;

    // TODO: value_compare()

    Map() = default;

    explicit Map(const Compare& comp, const Allocator& alloc = Allocator());

    explicit Map(const Allocator& alloc);

    template<class InputIt>
    Map(InputIt first, InputIt last,
        const Compare& comp = Compare(),
        const Allocator& alloc = Allocator());

    template<class InputIt>
    Map(InputIt first, InputIt last,
        const Allocator& alloc);

    Map(const Map& other);

    Map(const Map& other, const Allocator& alloc);

    Map(Map&& other);

    Map(Map&& other, const Allocator& alloc);

    Map(std::initializer_list<value_type> init,
        const Compare& comp = Compare(),
        const Allocator& alloc = Allocator());

    Map(std::initializer_list<value_type> init,
        const Allocator&);

    ~Map() = default;

    Map& operator=(const Map& other);

    Map& operator=(Map&& other) noexcept(AllocatorTraits<Allocator>::is_always_equal::value
                                         && std::is_nothrow_move_assignable_v<Compare>);

    Map& operator=(std::initializer_list<value_type> ilist);

    allocator_type get_allocator() const noexcept;

    reference at(const key_type& key);

    const_reference at(const key_type& key) const;

    reference operator[](const key_type& key);

    reference operator[](key_type&& key);

    iterator begin() noexcept;

    const_iterator begin() const noexcept;

    const_iterator cbegin() const noexcept;

    iterator end() noexcept;

    const_iterator end() const noexcept;

    const_iterator cend() const noexcept;

    size_type count(const key_type& key) const;

    template<class K>
    size_type count(const K& x) const;

    iterator find(const key_type& key);

    const_iterator find(const key_type& key) const;

    template<class K>
    iterator find(const K& x);

    template<class K>
    const_iterator find(const K& x) const;

    bool contains(const key_type& key) const;

    template<class K>
    bool contains(const K& x) const;

    iterator lower_bound(const key_type& key);

    const_iterator lower_bound(const key_type& key) const;

    template<class K>
    iterator lower_bound(const K& x);

    template<class K>
    const_iterator lower_bound(const K& x) const;

    iterator upper_bound(const key_type& key);

    const_iterator upper_bound(const key_type& key) const;

    template<class K>
    iterator upper_bound(const K& x);

    template<class K>
    const_iterator upper_bound(const K& x) const;

private:
    RedBlackTree<value_type, value_compare, Allocator> tree_{};
};

}