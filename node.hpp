#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <exception>

template<typename T>
class Node {

    private:
        T value_;
        std::vector<Node<T>*> children_;

    public:
        Node() : value_(T()) {}

        Node(T value) : value_(value) {}

        T get_value() const { return value_; }

        std::vector<Node<T>*> get_children() {return children_;}

        void add_child(Node<T> *child) {
            children_.push_back(child);
        }
        

};

/*
template <typename T>
std::vector<Node<T>> Node<T>::get_children() {
    return children_;
}
*/
