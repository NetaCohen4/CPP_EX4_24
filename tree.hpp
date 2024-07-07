/*
    Ex4
    325195774
    netaco432@gmail.com
*/

#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "node.hpp"

#include <SFML/Graphics.hpp>
#include "treeDrawer.hpp"

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
        std::stack<Node<T>*> stack;
        Node<T>* current;

        void pushLeft(Node<T>* node_ptr) {
            while (node_ptr != nullptr) {
                stack.push(node_ptr);
                if (!node_ptr->get_children().empty()) {
                    node_ptr = node_ptr->get_children()[0]; // Go to the left child
                } else {
                    node_ptr = nullptr;
                }
            }
        }

    public:
        In_Order_Iterator(Node<T>* node_ptr) : current(nullptr) {
            pushLeft(node_ptr);
            if (!stack.empty()) {
                current = stack.top();
            }
        }

        bool operator!=(const In_Order_Iterator& other) const {
            return this->current != other.current;
        }

        In_Order_Iterator& operator++() {
            if (stack.empty()) {
                current = nullptr;
                return *this;
            }
            current = stack.top();
            stack.pop();
            
            if (!current->get_children().empty() && current->get_children().size() > 1) {
                Node<T>* node = current->get_children()[1]; // Right child
                pushLeft(node);
            }
            
            if (!stack.empty()) {
                current = stack.top();
            } else {
                current = nullptr;
            }
            
            return *this;
        }

        T operator*() const {
            return current->get_value();
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
        /*
        os << std::string(static_cast<std::string::size_type>(depth * 2), ' ') << node->get_value() << "\n";
        for (const auto& child : node->get_children()) {
            printTree(os, child, depth + 1);
        }
        */

        sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Tree Demo");
        /*
        std::cout << "Yeah\n";
        // Example usage:
        TreeDrawer<double> drawer;
        // Add nodes to the tree

        // Example drawing:
        drawer.drawNode(window, node, 400.f, 300.f, 0.f, 0.f);

        window.display();
        */


        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            TreeDrawer<double> drawer;
            // Add nodes to the tree

            // Example drawing:
            drawer.drawNode(window, node, 400.f, 300.f, 0.f, 0.f);
            //tree.printTree(window);
            window.display();
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
