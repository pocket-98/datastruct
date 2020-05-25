/**
 * test array_list, sorted_list, linked_list, and double_list
 * @file test_list.hpp
 * @author Pavan Dayal
 */
#ifndef TEST_LIST_HPP
#define TEST_LIST_HPP

#include "list/test_array_list.hpp"

namespace test_list {
    // returns number of failures for all tests
    extern const int NUM_TESTS;
    int run_all();
}

#endif // TEST_LIST_HPP

