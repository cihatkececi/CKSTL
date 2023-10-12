#include "catch.hpp"

#include "ckstl/binary_tree.h"


using namespace ck;

TEST_CASE("BinaryTreeNode constructors", "[BinaryTree,BinaryTreeNode]") {
    SECTION("Default constructor") {
        BinaryTreeNode<int> tree_node;

        REQUIRE(tree_node.parent == nullptr);
        REQUIRE(tree_node.left_child == nullptr);
        REQUIRE(tree_node.right_child == nullptr);
        REQUIRE(tree_node.value == int{});
    }

    SECTION("Value constructor") {
        BinaryTreeNode<int> tree_node(5);

        REQUIRE(tree_node.parent == nullptr);
        REQUIRE(tree_node.left_child == nullptr);
        REQUIRE(tree_node.right_child == nullptr);
        REQUIRE(tree_node.value == 5);
    }

    SECTION("Value and parent constructor") {
        auto* parent = new BinaryTreeNode<int>();
        auto* tree_node = new BinaryTreeNode<int>(5, parent);
        parent->left_child = tree_node;

        REQUIRE(tree_node->parent == parent);
        REQUIRE(tree_node->left_child == nullptr);
        REQUIRE(tree_node->right_child == nullptr);
        REQUIRE(tree_node->value == 5);

        delete parent;
    }

    SECTION("Value, parent, and children constructor") {
        auto* parent = new BinaryTreeNode<int>();
        auto* left_child = new BinaryTreeNode<int>();
        auto* right_child = new BinaryTreeNode<int>();
        auto* tree_node = new BinaryTreeNode<int>(5, parent, left_child, right_child);
        parent->left_child = tree_node;

        REQUIRE(tree_node->parent == parent);
        REQUIRE(tree_node->left_child == left_child);
        REQUIRE(tree_node->right_child == right_child);
        REQUIRE(tree_node->value == 5);

        SECTION("Copy constructor") {
            BinaryTreeNode<int> copied_node(*tree_node);

            REQUIRE(copied_node.parent == nullptr);
            REQUIRE(copied_node.left_child != nullptr);
            REQUIRE(copied_node.right_child != nullptr);
            REQUIRE(copied_node.value == tree_node->value);
        }

        SECTION("Move constructor") {
            BinaryTreeNode<int> moved_node(std::move(*tree_node));

            REQUIRE(moved_node.parent == nullptr);
            REQUIRE(moved_node.left_child == left_child);
            REQUIRE(moved_node.right_child == right_child);
            REQUIRE(moved_node.value == 5);

            REQUIRE(tree_node->left_child == nullptr);
            REQUIRE(tree_node->right_child == nullptr);
        }

        delete parent;
    }
}
