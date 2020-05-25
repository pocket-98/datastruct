/**
 * array list
 * @file list/array_list.tpp
 * @author Pavan Dayal
 */

#include "array_list.hpp"
#include <cstdlib>

using namespace pvn;

template <typename T>
ArrayList<T>::ArrayList(size_t max) {
    this->n = 0;
    this->max = max;
    this->arr = static_cast<T*>(malloc(sizeof(T) * max));
}

template <typename T>
ArrayList<T>::ArrayList(size_t n, const T& filler) {
    T* p;
    this->n = n;
    this->max = 2*n;
    this->arr = static_cast<T*>(malloc(sizeof(T) * this->max));
    p = this->arr;
    while (n--) {
        *(p++) = filler;
    }
}

template <typename T>
ArrayList<T>::~ArrayList() {
    free(this->arr);
}

template <typename T>
size_t ArrayList<T>::size() {
    return this->n;
}

template <typename T>
size_t ArrayList<T>::capacity() {
    return this->max;
}

template <typename T>
void ArrayList<T>::clear() {
    this->n = 0;
}

template <typename T>
void ArrayList<T>::shrink() {
    this->arr = static_cast<T*>(realloc(this->arr, sizeof(T)*this->n));
    this->max = this->n;
}

template <typename T>
void ArrayList<T>::reserve(size_t max) {}

template <typename T>
void ArrayList<T>::resize(size_t max) {}

template <typename T>
void ArrayList<T>::resize(size_t n, const T& filler) {}

template <typename T>
T* ArrayList<T>::insert(size_t j, const T& x) {return NULL;}

template <typename T>
T* ArrayList<T>::insert(size_t j, size_t n, const T& x) {return NULL;}

template <typename T>
T* ArrayList<T>::insert(T* j, const T& x) {return NULL;}

template <typename T>
T* ArrayList<T>::insert(T* j, size_t n, const T& x) {return NULL;}


template <typename T>
T* ArrayList<T>::remove(size_t j) {return NULL;}

template <typename T>
T* ArrayList<T>::remove(size_t j, size_t k) {return NULL;}

template <typename T>
T* ArrayList<T>::remove(T* j) {return NULL;}

template <typename T>
T* ArrayList<T>::remove(T* j, T* k) {return NULL;}
