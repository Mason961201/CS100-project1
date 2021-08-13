//
// test_bst.cpp
// CSE 100 Project 1
//
// A BST tester using Catch unit testing framework.
//
// ATTENTION: This is not an exchaustive test suite and
// passing all tests does not guarantee full score on the
// project. You may want to add your own test cases by
// following the examples given.
// 
// Last modified by Heitor Schueroff on 01/10/2019
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <vector>
#include <string>

#include "../src/BST.hpp"

using namespace std;

/**
 * Tests inserting elements from a vector into a BST.
 *
 * Parameters:
 *     bst - the BST to insert elements into
 *     v - vector whose elements are to be inserted
 *     expected_height - the expected height of the BST after inserting elements
 */
template <typename T>
void test_bst(BST<T> &bst, vector<T> v, unsigned int expected_height) {
    INFO("Inserting elements into BST");

    for (T i : v) REQUIRE(bst.insert(i));
    for (T i : v) CHECK(*(bst.find(i)) == i);

    CHECK(bst.height() == expected_height);

    INFO("Testing inorder traversal with BSTIterator");

    sort(v.begin(), v.end());
    auto it = bst.begin();
    auto end = bst.end();
    
    for (T i : v) {
        REQUIRE(*(it++) == i);
    }
    REQUIRE(it == end);
}

TEST_CASE("Building BST with integers") {
    BST<int> bst;

    SECTION("adding one element to BST") {
        test_bst<int>(bst, vector<int>{1}, 1);
        REQUIRE_FALSE(bst.insert(1));
	REQUIRE(bst.find(0) == bst.end());
    }

    SECTION("adding elements in random order") {
        test_bst<int>(bst, vector<int>{10, 5, 15, 7, -2, 12}, 3);
	REQUIRE_FALSE(bst.insert(-2));
	
    }
    SECTION("testing methods on empty BST") {
        CHECK(bst.size() == 0);
        CHECK(bst.height() == 0);
        CHECK(bst.empty());
        CHECK(bst.find(0) == bst.end());
        CHECK(bst.begin() == bst.end());
    }

    SECTION("adding one element to BST") {
        test_bst<int>(bst, vector<int>{1}, 1);
        REQUIRE_FALSE(bst.insert(1));
        REQUIRE(bst.find(0) == bst.end());
    }

    SECTION("adding elements in random order") {
        test_bst<int>(bst, vector<int>{10, 5, 15, 7, -2, 12}, 3);
        REQUIRE_FALSE(bst.insert(-2));
        REQUIRE(bst.find(8) == bst.end());
    }

    SECTION("adding elements in sorted order") {
        test_bst<int>(bst, vector<int>{-2, 0, 2, 3, 5}, 5);
        REQUIRE_FALSE(bst.insert(5));
        REQUIRE(bst.find(8) == bst.end());
    }
}
TEST_CASE("test BST with different integers"){
        BST<int> bst;

        SECTION("add elements"){
                REQUIRE(bst.empty());
                test_bst<int>(bst, vector<int>{6,3,5,4,7,1}, 4);
                REQUIRE_FALSE(bst.empty());
                REQUIRE_FALSE(bst.insert(6));
                REQUIRE_FALSE(bst.insert(3));
                REQUIRE_FALSE(bst.insert(5));
                REQUIRE(bst.size() == 6);
                REQUIRE(bst.insert(9));
                REQUIRE(bst.size() == 7);
                REQUIRE(bst.height() == 4);
                REQUIRE(bst.find(0) == bst.end());
                WARN("Calling BST::inorder(), ensure output is in ascending order");
                bst.inorder();
        }
}
TEST_CASE("test BST with different integers - 1"){
        BST<int> bst;

        SECTION("add elements"){
                REQUIRE(bst.empty());
                test_bst<int>(bst, vector<int>{1,2,3,4}, 4);
                REQUIRE_FALSE(bst.empty());
                REQUIRE_FALSE(bst.insert(2));
                REQUIRE_FALSE(bst.insert(3));
                REQUIRE_FALSE(bst.insert(4));
                REQUIRE(bst.size() == 4);
                REQUIRE(bst.insert(9));
                REQUIRE(bst.size() == 5);
                REQUIRE(bst.height() == 5);
                REQUIRE(bst.find(0) == bst.end());
                WARN("Calling BST::inorder(), ensure output is in ascending order");
                bst.inorder();
        }
}

TEST_CASE("test BST with different double"){
        BST<double> bst;

        SECTION("add elements"){
                REQUIRE(bst.empty());
                test_bst<double>(bst, vector<double>{1.1,2.1,3.1,4.1}, 4);
                REQUIRE_FALSE(bst.empty());
                REQUIRE_FALSE(bst.insert(2.1));
                REQUIRE_FALSE(bst.insert(3.1));
                REQUIRE_FALSE(bst.insert(4.1));
                REQUIRE(bst.size() == 4);
                REQUIRE(bst.insert(9.0));
                REQUIRE(bst.size() == 5);
                REQUIRE(bst.height() == 5);
                REQUIRE(bst.find(0) == bst.end());
                WARN("Calling BST::inorder(), ensure output is in ascending order");
                bst.inorder();
        }
}

TEST_CASE("Deconstruct"){
    BST<int> * a = new BST<int>();
    delete a;
}
TEST_CASE("Building BST with strings") {
    BST<string> bst;

    SECTION("adding elements in random order") {
        test_bst(bst, vector<string>{"c", "a", "d", "b", "e", "f"}, 4);
        WARN("Calling BST::inorder(), ensure output is in ascending order");
        bst.inorder();
    }
    SECTION("adding one element to BST") {
        test_bst<string>(bst, vector<string>{"foo"}, 1);
        REQUIRE_FALSE(bst.insert("foo"));
        REQUIRE(bst.find("bar") == bst.end());
    }

    SECTION("adding elements in random order") {
        test_bst(bst, vector<string>{"c", "a", "d", "b", "e", "f"}, 4);
        WARN("Calling BST::inorder(), ensure output is in ascending order");
        bst.inorder();
    }
}
