#pragma once

#include <cstddef>

#include <iterator>

#include "memory.h"
#include "iterator.h"
#include "ckstl/functional.h"


namespace ck {

//template<class T, typename Allocator = Allocator<T>>
//class BinaryTreeNode {
//public:
//    BinaryTreeNode() = default;
//
//    explicit BinaryTreeNode(T value) : value_(std::move(value)) {}
//
//    BinaryTreeNode(T value, BinaryTreeNode* parent) : value_(std::move(value)), parent_(parent) {}
//
//    BinaryTreeNode(T value, BinaryTreeNode* parent, BinaryTreeNode* left_child, BinaryTreeNode* right_child)
//            : value_(std::move(value)), parent_(parent), left_child_(left_child), right_child_(right_child) {}
//
//    BinaryTreeNode(const BinaryTreeNode& rhs) : value_(rhs.value_) {
//        if (rhs.left_child_ != nullptr) {
//            left_child_ = Allocator::allocate(1);
//            Allocator::construct();
//            left_child_ = new BinaryTreeNode(*rhs.left_child_);
//        }
//
//        if (rhs.right_child_ != nullptr) {
//            right_child_ = new BinaryTreeNode(*rhs.right_child_);
//        }
//    }
//
//    BinaryTreeNode& operator=(BinaryTreeNode rhs) {
//        swap(*this, rhs);
//        return *this;
//    }
//
//    BinaryTreeNode(BinaryTreeNode&& rhs) noexcept: value_(std::move(rhs.value_)), left_child_(rhs.left_child_),
//                                                   right_child_(rhs.right_child_) {
//        rhs.left_child_ = nullptr;
//        rhs.right_child_ = nullptr;
//    }
//
//    BinaryTreeNode& operator=(BinaryTreeNode&& rhs) noexcept {
//        BinaryTreeNode temp{std::move(rhs)};
//        swap(*this, temp);
//
//        return *this;
//    }
//
//    ~BinaryTreeNode() {
//        delete left_child_;
//        delete right_child_;
//    }
//
//    friend void swap(BinaryTreeNode& lhs, BinaryTreeNode& rhs) noexcept {
//        using std::swap;
//        swap(lhs.value_, rhs.value_);
//        swap(lhs.left_child_, rhs.left_child_);
//        swap(lhs.right_child_, rhs.right_child_);
//    }
//
//    const T& value() const {
//        return value_;
//    }
//
//    T& value() {
//        return value_;
//    }
//
//    BinaryTreeNode* parent() const {
//        return parent_;
//    }
//
//    void parent(BinaryTreeNode* parent) {
//        parent_ = parent;
//    }
//
//    BinaryTreeNode* left_child() const {
//        return left_child_;
//    }
//
//    void left_child(BinaryTreeNode* child) {
//        left_child_ = child;
//    }
//
//    BinaryTreeNode* right_child() const {
//        return right_child_;
//    }
//
//    void right_child(BinaryTreeNode* child) {
//        right_child_ = child;
//    }
//
//    BinaryTreeNode* deepest_left_child() {
//        BinaryTreeNode* node = this;
//        while (node->left_child_ != nullptr) {
//            node = node->left_child_;
//        }
//
//        return node->left_child_;
//    }
//
//    BinaryTreeNode* deepest_right_child() {
//        BinaryTreeNode* node = this;
//        while (node->right_child_ != nullptr) {
//            node = node->right_child_;
//        }
//
//        return node->right_child_;
//    }
//
//    BinaryTreeNode* first_parent_from_left() {
//        BinaryTreeNode* node = this;
//        while (node->parent_ != nullptr && node->parent_->left_child_ != node) {
//            node = node->parent;
//        }
//
//        return node;
//    }
//
//    BinaryTreeNode* first_parent_from_right() {
//        BinaryTreeNode* node = this;
//        while (node->parent_ != nullptr && node->parent_->right_child_ != node) {
//            node = node->parent;
//        }
//
//        return node;
//    }
//
//private:
//    T value_{};
//    BinaryTreeNode* parent_{nullptr};
//    BinaryTreeNode* left_child_{nullptr};
//    BinaryTreeNode* right_child_{nullptr};
//};

template<typename T>
struct BinaryTreeNode {
    BinaryTreeNode(T val = {}, BinaryTreeNode* p = nullptr, BinaryTreeNode* lc = nullptr, BinaryTreeNode* rc = nullptr)
    : value(std::move(val)), parent(p), left_child(lc), right_child(rc) {}

    T value{};
    BinaryTreeNode* parent{nullptr};
    BinaryTreeNode* left_child{nullptr};
    BinaryTreeNode* right_child{nullptr};
};

template<class T>
class BinaryTreeIterator {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::bidirectional_iterator_tag;
    using node_type = BinaryTreeNode<T>;
    using node_pointer = node_type*;

    BinaryTreeIterator(BinaryTreeNode<T>* node) : node_(node) {}

    reference operator*() {
        return node_->value;
    }

    pointer operator->() {
        return &node_->value;
    }

protected:
    node_pointer node_{nullptr};
};

template<class T>
class BinaryTreeInOrderIterator : public BinaryTreeIterator<T> {
public:
    using value_type = typename BinaryTreeIterator<T>::value_type;
    using difference_type = typename BinaryTreeIterator<T>::difference_type;
    using reference = typename BinaryTreeIterator<T>::reference;
    using pointer = typename BinaryTreeIterator<T>::pointer;
    using iterator_category = typename BinaryTreeIterator<T>::iterator_category;
    using node_type = typename BinaryTreeIterator<T>::node_type;
    using node_pointer = typename BinaryTreeIterator<T>::node_pointer;

    BinaryTreeInOrderIterator& operator++() {
        if (this->node_->right_child != nullptr) {
            this->node_ = this->node_->right_child_->deepest_left_child();
        }
        else {
            this->node_ = this->node_->first_parent_from_left();
        }
        return *this;
    }

    BinaryTreeInOrderIterator operator++(int) {
        BinaryTreeInOrderIterator temp = *this;
        if (temp->node_->right_child != nullptr) {
            temp->node_ = temp->node_->right_child_->deepest_left_child();
        }
        else {
            temp->node_ = temp->node_->first_parent_from_left();
        }
        return temp;
    }

private:
    node_pointer deepest_left_child() {
        node_pointer node = this;
        while (node->left_child_ != nullptr) {
            node = node->left_child_;
        }

        return node->left_child_;
    }

    node_pointer deepest_right_child() {
        node_pointer node = this;
        while (node->right_child_ != nullptr) {
            node = node->right_child_;
        }

        return node->right_child_;
    }

    node_pointer first_parent_from_left() {
        node_pointer node = this;
        while (node->parent_ != nullptr && node->parent_->left_child_ != node) {
            node = node->parent;
        }

        return node;
    }

    node_pointer first_parent_from_right() {
        node_pointer node = this;
        while (node->parent_ != nullptr && node->parent_->right_child_ != node) {
            node = node->parent;
        }

        return node;
    }
};

template<typename T>
using BinaryTreeDefaultIterator = BinaryTreeInOrderIterator<T>;

struct BFS {};
struct InOrder {};
struct PreOrder {};
struct PostOrder {};

template<typename T>
bool is_left_child(const BinaryTreeNode<T>& node) {
    return node.parent->left_child == node;
}

template<typename T>
bool is_right_child(const BinaryTreeNode<T>& node) {
    return node.parent->right_child == node;
}

template<class T, typename Allocator = Allocator<T>>
class BinaryTree {
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

    using node_type = BinaryTreeNode<value_type>;
    using node_pointer = node_type*;
    using node_allocator = typename Allocator::template rebind<node_type>::type;

    BinaryTree() = default;

    BinaryTree(const BinaryTree& other) : root_(nullptr) {
        auto my_it = begin();
        for (auto it = other.begin(); it != other.end(); ++it, ++my_it) {
            emplace(my_it, *it);
        }
    }

    BinaryTree(BinaryTree&& other) noexcept: root_(std::exchange(other.root_, nullptr)) {}

    BinaryTree& operator=(BinaryTree other) {
        swap(*this, other);
        return *this;
    }

    BinaryTree& operator=(BinaryTree&& other) noexcept {
        BinaryTree temp{std::move(other)};
        swap(*this, temp);

        return *this;
    }

    ~BinaryTree() {
        delete root_;
    }

    friend void swap(BinaryTree& lhs, BinaryTree& rhs) noexcept {
        using std::swap;
        swap(lhs.root_, rhs.root_);
    }

    template<typename Method>
    BinaryTreeInOrderIterator<T> begin() noexcept {
        // TODO: Not Implemented!
        return {root_};
//        static_assert(false);
        throw std::invalid_argument{"Traverse option is not correct"};
    }

    template<>
    BinaryTreeInOrderIterator<T> begin<InOrder>() noexcept {
        // TODO: Not Implemented!
        return {leftmost_};
    }

    const_iterator begin() const noexcept {
        // TODO: Not Implemented!
    }

    const_iterator cbegin() const noexcept {
        // TODO: Not Implemented!
    }

    iterator end() noexcept {
        // TODO: Not Implemented!
    }

    const_iterator end() const noexcept {
        // TODO: Not Implemented!
    }

    const_iterator cend() const noexcept {
        // TODO: Not Implemented!
    }

    reverse_iterator rbegin() noexcept {
        // TODO: Not Implemented!
    }

    const_reverse_iterator rbegin() const noexcept {
        // TODO: Not Implemented!
    }

    const_reverse_iterator crbegin() const noexcept {
        // TODO: Not Implemented!
    }

    reverse_iterator rend() noexcept {
        // TODO: Not Implemented!
    }

    const_reverse_iterator rend() const noexcept {
        // TODO: Not Implemented!
    }

    const_reverse_iterator crend() const noexcept {
        // TODO: Not Implemented!
    }

    template<typename It, typename... Args >
    iterator emplace(It it, Args&&... args) {
        // TODO: Implement
        auto new_ptr = Allocator::allocate(1);
        Allocator::construct(new_ptr, std::forward<Args>(args)...);
    }

    template<typename It>
    iterator insert(It it, const_reference val) {

    }

    template<typename It>
    iterator insert_left(It it, const_reference val) {

    }

    template<typename It>
    iterator insert_right(It it, const_reference val) {

    }

protected:
    node_pointer root_{nullptr};
    node_pointer leftmost_{nullptr};
};

}
