/**
 * test array_list, sorted_list, linked_list, and double_list
 * @file list/test_array_list.hpp
 * @author Pavan Dayal
 */
#ifndef TEST_ARRAY_LIST_HPP
#define TEST_ARRAY_LIST_HPP

#include "../test.hpp"
#include "list/array_list.hpp"

namespace test_array_list {
    // return 0 for success and 1 for failure
    int test_construct();
    int test_size();
    int test_resize();

    // returns number of failures for all tests
    extern const int NUM_TESTS;
    int run_all();
}

#endif // TEST_ARRAY_LIST_HPP

