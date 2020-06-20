/**
 * instantiate templates for each datastructure so it is present in libpvn.so
 * @file instantiate.cpp
 * @author Pavan Dayal
 */

#include <iostream>

#include "list/array_list.hpp"
template class pvn::ArrayList<int>;
//template class pvn::ArrayList<int*>;
//template class pvn::ArrayList<unsigned int>;
//template class pvn::ArrayList<unsigned int*>;
//template class pvn::ArrayList<long int>;
//template class pvn::ArrayList<long int*>;
//template class pvn::ArrayList<unsigned long int>;
//template class pvn::ArrayList<unsigned long int*>;
//template class pvn::ArrayList<char>;
//template class pvn::ArrayList<char*>;
//template class pvn::ArrayList<const char*>;
//template class pvn::ArrayList<bool>;
//template class pvn::ArrayList<double>;
//template class pvn::ArrayList<double*>;
//template class pvn::ArrayList<void*>;
