/**
 * @file list/test_array_list.cpp
 * @author Pavan Dayal
 */

#include "test_array_list.hpp"
#include <sstream>
#include <cstring>

using namespace pvn;

template class pvn::ArrayList<int>;
template class pvn::ArrayList<char>;
template class pvn::ArrayList<double>;

int test_array_list::test_construct() {
    ArrayList<int> a;
    ArrayList<char> b;

    struct test {
        int x;
    };
    ArrayList<test> c{};

    ArrayList<double> d(4);
    ArrayList<double> e(4, 2.0);
    return EXIT_SUCCESS;
}

int test_array_list::test_size() {
    ArrayList<int> a;
    testequal("size should be zero", 0, a.size());
    testequal("capacity should be zero", 8, a.capacity());

    ArrayList<char> b{};
    testequal("size should be zero", 0, b.size());
    testequal("capacity should be zero", 8, b.capacity());

    ArrayList<float> c(9);
    testequal("size should be zero", 0, c.size());
    testequal("capacity should be zero", 9, c.capacity());

    ArrayList<float> d(9, 3);
    testequal("size should be nonzero", 9, d.size());
    testequal("capacity should be nonzero", 18, d.capacity());

    ArrayList<char> e(2, 'e');
    testequal("size should be nonzero", 2, e.size());
    testequal("capacity should be nonzero", 4, e.capacity());

    d.shrink();
    testequal("shrink: size should stay same", 9, d.size());
    testequal("capacity should shrink to size", 9, d.capacity());

    a.shrink();
    testequal("shrink: size should stay zero", 0, a.size());
    testequal("capacity should shrink to zero", 0, a.capacity());

    a.clear();
    testequal("clear: size should stay zero", 0, a.size());
    testequal("capacity should stay at zero", 0, a.capacity());

    d.clear();
    testequal("clear: size should stay zero", 0, d.size());
    testequal("capacity should stay at zero", 9, d.capacity());

    e.clear();
    testequal("clear: size should shrink to zero", 0, e.size());
    testequal("capacity should stay at zero", 4, e.capacity());

    return EXIT_SUCCESS;
}

int test_array_list::test_resize() {
    // resize
    // reserve
    return EXIT_SUCCESS;
}

const int test_array_list::NUM_TESTS = 3;

int test_array_list::run_all() {
    int fails = 0;
    std::string bak = indent;
    indent = "   * ";

    std::cerr << " > list/array_list.hpp" << std::endl;
    testfn(fails, test_array_list::test_construct, "constructor");
    testfn(fails, test_array_list::test_size, "size and capacity");
    testfn(fails, test_array_list::test_resize, "resize");

    indent = bak;
    return fails;
}

