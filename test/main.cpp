/**
 * @file test/main.cpp
 * @author Pavan Dayal
 */

#include <cstdio>
#include <iostream>
#include <string>
#include "test_list.hpp"

std::string indent = " * ";

int main() {
    int fails = 0;
    int total = 0;
    int f, t;

    std::cerr << "testing lists:" << std::endl;
    f = test_list::run_all();
    t = test_list::NUM_TESTS;
    fprintf(stderr, "passed (%d/%d): %.2f%%\n", t-f, t, 100.0*(t-f)/t);
    fails += f;
    total += t;

    return f;
}
