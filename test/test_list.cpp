/**
 * @file test_list.cpp
 * @author Pavan Dayal
 */

#include "test_list.hpp"

const int test_list::NUM_TESTS = (
    test_array_list::NUM_TESTS
);

int test_list::run_all() {
    int fails = 0;
    fails += test_array_list::run_all();
    return fails;
}
