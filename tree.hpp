#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "node.hpp"

template<typename T>
class Tree {
private:
    Node<T>* root_ = nullptr;
    size_t max_children_num = 2;

public:
    Tree() {}
    Tree(size_t children_num) : max_children_num(children_num) {}

    Node<T>* get_root_() const { return root_; }
    void add_root(Node<T>& root);
    void add_sub_node(Node<T>& root_node, Node<T>& child);

    friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
        printTree(os, tree.root_, 0);
        return os;
    }

    class Pre_Order_Iterator { // DFS
    private:
        std::stack<Node<T>*> stack;
        Node<T>* current;

    public:
        Pre_Order_Iterator(Node<T>* node_ptr) : current(node_ptr) {
            if (node_ptr) {
                const auto& children = current->get_children();
                for (auto it = children.rbegin(); it != children.rend(); ++it) {
                    stack.push(*it);
                }
            }
        }

        bool operator!=(const Pre_Order_Iterator& other) const {
            return this->current != other.current;
        }

        Pre_Order_Iterator& operator++() {
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
                const auto& children = current->get_children();
                for (auto it = children.rbegin(); it != children.rend(); ++it) {
                    stack.push(*it);
                }
            } else {
                current = nullptr;
            }
            return *this;
        }

        T operator*() const {
            return current->get_value();
        }
    };

    class Post_Order_Iterator {
    private:
        std::stack<Node<T>*> stack;
        Node<T>* current;

    public:
        Post_Order_Iterator(Node<T>* node_ptr) : current(nullptr) {
            if (node_ptr) {
                pushAllChildren(node_ptr);
                if (!stack.empty()) {
                    current = stack.top();
                    stack.pop();
                }
            }
        }

        bool operator!=(const Post_Order_Iterator& other) const {
            return this->current != other.current;
        }

        Post_Order_Iterator& operator++() {
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }

        T operator*() const {
            return current->get_value();
        }

    private:
        void pushAllChildren(Node<T>* node) {
            std::stack<Node<T>*> temp_stack;
            temp_stack.push(node);

            while (!temp_stack.empty()) {
                Node<T>* current = temp_stack.top();
                temp_stack.pop();
                stack.push(current);

                for (auto child : current->get_children()) {
                    temp_stack.push(child);
                }
            }
        }
    };

    class In_Order_Iterator {
    private:
        std::stack<std::pair<Node<T>*, size_t>> stack;
        Node<T>* current;

    public:
        In_Order_Iterator(Node<T>* node_ptr) : current(nullptr) {
            if (node_ptr) {
                stack.push(std::make_pair(node_ptr, 0));
                moveToNext();
            }
        }

        bool operator!=(const In_Order_Iterator& other) const {
            return this->current != other.current;
        }

        In_Order_Iterator& operator++() {
            moveToNext();
            return *this;
        }

        T operator*() const {
            return current->get_value();
        }

    private:
        void moveToNext() {
            while (!stack.empty()) {
                auto& top = stack.top();
                Node<T>* node = top.first;
                size_t& child_index = top.second;

                const auto& children = node->get_children();
                if (child_index < children.size()) {
                    stack.push(std::make_pair(children[child_index], 0));
                    ++child_index;
                } else {
                    current = node;
                    stack.pop();
                    return;
                }
            }
            current = nullptr;
        }
    };

    class BFS_Iterator {
    private:
        std::queue<Node<T>*> queue;
        Node<T>* current;

    public:
        BFS_Iterator(Node<T>* node_ptr) : current(node_ptr) {
            if (node_ptr) {
                const auto& children = current->get_children();
                for (auto child : children) {
                    queue.push(child);
                }
            }
        }

        bool operator!=(const BFS_Iterator& other) const {
            return this->current != other.current;
        }

        BFS_Iterator& operator++() {
            if (!queue.empty()) {
                current = queue.front();
                queue.pop();
                const auto& children = current->get_children();
                for (auto child : children) {
                    queue.push(child);
                }
            } else {
                current = nullptr;
            }
            return *this;
        }

        T operator*() const {
            return current->get_value();
        }
    };

    Pre_Order_Iterator begin_pre_order() { return Pre_Order_Iterator(this->root_); }
    Pre_Order_Iterator end_pre_order() { return Pre_Order_Iterator(nullptr); }

    Post_Order_Iterator begin_post_order() { return Post_Order_Iterator(this->root_); }
    Post_Order_Iterator end_post_order() { return Post_Order_Iterator(nullptr); }

    In_Order_Iterator begin_in_order() { return In_Order_Iterator(this->root_); }
    In_Order_Iterator end_in_order() { return In_Order_Iterator(nullptr); }

    Pre_Order_Iterator begin_dfs_scan() { return Pre_Order_Iterator(this->root_); }
    Pre_Order_Iterator end_dfs_scan() { return Pre_Order_Iterator(nullptr); }

    BFS_Iterator begin_bfs_scan() { return BFS_Iterator(this->root_); }
    BFS_Iterator end_bfs_scan() { return BFS_Iterator(nullptr); }

private:

    static void printTree(std::ostream& os, Node<T>* node, int depth) {
        if (!node) return;
        os << std::string(static_cast<std::string::size_type>(depth * 2), ' ') << node->get_value() << "\n";
        for (const auto& child : node->get_children()) {
            printTree(os, child, depth + 1);
        }
    }

};

template <typename T>
void Tree<T>::add_root(Node<T>& root) {
    root_ = &root;
}

template <typename T>
void Tree<T>::add_sub_node(Node<T>& root_node, Node<T>& child) {
    root_node.add_child(&child);
}
