/**
 * instantiate templates for each datastructure so it is present in a.so
 * @file shared.cpp
 * @author Pavan Dayal
 */

#include <iostream>

#include "list/array_list.hpp"
template class pvn::ArrayList<int>;
template class pvn::ArrayList<char>;
template class pvn::ArrayList<bool>;
template class pvn::ArrayList<double>;
