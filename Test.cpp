/*
    Ex4
    325195774
    netaco432@gmail.com
*/

#include "doctest.h"
#include "tree.hpp"
#include "complex.hpp"

TEST_CASE("Test Node")
{
    Node<int> int_node(1);
    CHECK(int_node.get_value() == 1);

    Node<double> double_node(1.0);
    CHECK(double_node.get_value() == 1.0);

    Node<char> char_node('1');
    CHECK(char_node.get_value() == '1');

    Node<Complex> complex_node(Complex(0.0, 0.0));
    CHECK(complex_node.get_value() == Complex(0.0, 0.0));
}

TEST_CASE("Test Node addChild")
{
    Node<Complex> complex_node(Complex(0.0, 0.0));
    Node<Complex> node_son(Complex(1.0, 1.0));
    complex_node.add_child(&node_son);
    std::vector<Node<Complex>*> tmp_vec;
    tmp_vec.push_back(&node_son);
    CHECK(complex_node.get_children() == tmp_vec);
}

/*
    exception test - extra child

    Iterator tests

*/