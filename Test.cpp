
#include "doctest.h"
#include "tree.hpp"

TEST_CASE("Test Node")
{
    Node<int> int_node(1);
    CHECK(int_node.get_value() == 1);
}