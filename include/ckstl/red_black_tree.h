#pragma once

#include "binary_search_tree.h"
#include "iterator.h"


namespace ck {

template<class T, typename Compare = Less<T>, typename Allocator = Allocator<T>>
class RedBlackTree : public BinarySearchTree<T, Allocator> {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = BinaryTreeDefaultIterator<value_type>;
    using const_iterator = BinaryTreeDefaultIterator<value_type>;
    using reverse_iterator = ReverseIterator<BinaryTreeDefaultIterator<value_type>>;
    using const_reverse_iterator = ReverseIterator<BinaryTreeDefaultIterator<value_type>>;

private:

};

}
