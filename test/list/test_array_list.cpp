/**
 * @file list/test_array_list.cpp
 * @author Pavan Dayal
 */

#include "test_array_list.hpp"
#include <sstream>
#include <cstring>

using namespace pvn;

static ArrayList<int> gimme(int n) {
    return ArrayList<int>(n);
}

int test_array_list::test_construct() {
    ArrayList<int> a;
    ArrayList<char> b;

    struct test { int x; };
    ArrayList<test> c{};

    ArrayList<double> d(4);
    ArrayList<double> e(4, 2.0);

    ArrayList<char> s{'1', '2', '3'};
    ArrayList<char> s2 = {'1', '2', '3'};
    ArrayList<char> s3({'1', '2', '3'});

    int x[] = {1, 2, 3};
    ArrayList<int> x2(x, x+3);
    ArrayList<int> y = {5, 6, 7};

    // copy constructor
    ArrayList<int> x3(x2);
    testnotequal("stole data instead of copying", x2.data(), x3.data());
    ArrayList<int> x4 = y;
    testnotequal("stole data instead of copying", x4.data(), y.data());
    int* d3 = x3.data();
    int* d4 = x4.data();
    x4 = x3;
    testequal("changed other other variable during copy", d3, x3.data());
    testnotequal("kept old data", d4, x4.data());
    x4 = x4;
    testnotequal("move didnt delete change self", (void*) NULL, x4.data());
    testequal("move didnt delete change self", *d3, *x4.data());

    // move constructor
    x2 = ArrayList<int>();
    x3 = gimme(3);
    int* d2 = x2.data();
    ArrayList<int> z(std::move(x2));
    testequal("didnt remove data on rvalue for move", (void*) NULL, x2.data());
    testequal("didnt move the data", d2, z.data());

    return EXIT_SUCCESS;
}

int test_array_list::test_size() {
    ArrayList<int> a;
    testequal("size should be zero", 0, a.size());
    testequal("capacity should be zero", 8, a.capacity());

    ArrayList<char> b{};
    testequal("size should be zero", 0, b.size());
    testequal("capacity should be positive", 8, b.capacity());

    ArrayList<float> c(9);
    testequal("size should be zero", 0, c.size());
    testequal("capacity should be positive", 9, c.capacity());

    ArrayList<float> d(9, 3);
    testequal("size should be nonzero", 9, d.size());
    testequal("capacity should be double size", 18, d.capacity());

    ArrayList<char> e(2, 'e');
    testequal("size should be nonzero", 2, e.size());
    testequal("capacity should be double size", 4, e.capacity());

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
    testequal("capacity should stay same", 9, d.capacity());

    e.clear();
    testequal("clear: size should shrink to zero", 0, e.size());
    testequal("capacity should stay same", 4, e.capacity());

    c.reserve(8);
    testequal("size should be same", 0, c.size());
    testequal("capacity should be same", 9, c.capacity());

    c.reserve(9);
    testequal("size should be same", 0, c.size());
    testequal("capacity should be same", 9, c.capacity());

    c.reserve(12);
    testequal("size should be same", 0, c.size());
    testequal("capacity should be big", 24, c.capacity());

    return EXIT_SUCCESS;
}

int test_array_list::test_insert() {
    // data()
    // insert(j, x)
    // insert(j, n, fill)
    // insert(pos, x)
    // insert(pos, n, fill)
    // insert(pos, pos, fill)
    //make sure pos and return diff obj addresses
    // fill(filler)
    return EXIT_SUCCESS;
}

int test_array_list::test_iterator() {
    // construct from ptr
    // ++ -- pre and post
    // ==, !=, <, >
    return EXIT_SUCCESS;
}

int test_array_list::test_remove() {
    // remove(j)
    // remove (j, n)
    // remove (pos)
    // remove (pos, pos)
    // resize(n)
    // resize(n, fill)
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
    testfn(fails, test_array_list::test_insert, "insert");
    testfn(fails, test_array_list::test_iterator, "iterator");
    testfn(fails, test_array_list::test_remove, "remove");

    indent = bak;
    return fails;
}

