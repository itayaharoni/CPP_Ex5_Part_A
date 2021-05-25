#include "doctest.h"
#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;
#include "BinaryTree.hpp"
using namespace ariel;

TEST_CASE("Testing BinaryTree<int>.") {
    BinaryTree<int> bt;
    CHECK_NOTHROW(bt.add_root(1));
    CHECK_NOTHROW(bt.add_right(1,2));
    CHECK_NOTHROW(bt.add_left(1,3));
    CHECK_THROWS(bt.add_right(4,5));
    CHECK_NOTHROW(bt.add_right(2,4));
    CHECK_NOTHROW(bt.add_left(4,5));
    string bt_in_order;

    // In-order traversal.
    for(int it:bt){
        CHECK_NOTHROW(bt_in_order+=to_string(it));
    }
    CHECK(bt_in_order=="31254");
    string bt_post_order;

    // Post-order traversal.
    for(auto itr=bt.begin_postorder(); itr!=bt.end_postorder(); ++itr){
        CHECK_NOTHROW(bt_post_order+=to_string(*itr));
    }
    CHECK(bt_post_order=="35421");
    string bt_pre_order;

    // Pre-order traversal.
    for(auto itr=bt.begin_preorder(); itr!=bt.end_preorder(); ++itr){
        CHECK_NOTHROW(bt_pre_order+=to_string(*itr));
    }
    CHECK(bt_pre_order=="13245");
}
