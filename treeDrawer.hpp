#ifndef TREE_DRAWER_HPP
#define TREE_DRAWER_HPP

#include <SFML/Graphics.hpp>

template <typename T>
class TreeDrawer {
public:
    void drawNode(sf::RenderWindow& window, Node<T>* node, float x, float y, float offsetX, float offsetY);
};

#include "treeDrawer.cpp" // Include the implementation file

#endif // TREE_DRAWER_HPP
