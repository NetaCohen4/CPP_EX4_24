#include "node.hpp"
#include "treeDrawer.hpp"

template <typename T>
void TreeDrawer<T>::drawNode(sf::RenderWindow& window, Node<T>* node, float x, float y, float offsetX, float offsetY) {
    sf::Font font; // Local font declaration

    // Load the font
    /*
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font 'arial.ttf'" << std::endl;
        // Handle font loading error
    }
    */

    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf")) {
        std::cerr << "Failed to load font 'arial.ttf'" << std::endl;
        // Handle font loading error
        return; // Or other error handling mechanism
    }


    // Rest of your drawNode function implementation
    // Example code below (adjust as per your existing implementation)
    sf::CircleShape shape(50.f);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);

    // Example text rendering
    sf::Text text;
    text.setFont(font); // Set the font
    text.setString(std::to_string(node->get_value())); // Example: convert value to string
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - 10.f, y - 10.f); // Adjust position as needed
    window.draw(text);
}

