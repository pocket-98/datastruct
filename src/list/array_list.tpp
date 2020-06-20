/**
 * array list
 * @file list/array_list.tpp
 * @author Pavan Dayal
 */

#include "array_list.hpp"
#include <cstdlib>
#include <cstring>
#include <stdexcept>

using namespace pvn;
#define T_IT ArrayList<T>::Iterator

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
ArrayList<T>::ArrayList(std::initializer_list<T> elems) {
    T* p;
    const T* a;
    const T* b;
    this->n = elems.size();
    this->max = 2 * this->n;
    this->arr = static_cast<T*>(malloc(sizeof(T) * this->max));
    a = elems.begin();
    b = elems.end();
    p = this->arr;
    while (a != b) {
        *(p++) = *(a++);
    }
}

template <typename T>
ArrayList<T>::ArrayList(const T* a, const T* b) {
    T* p;
    this->n = 0;
    this->max = 8;
    this->arr = static_cast<T*>(malloc(sizeof(T) * this->max));
    p = this->arr;
    while (a != b) {
        // ensure capacity
        if (this->max <= this->n) {
            this->max = 2 * this->n;
            this->arr = static_cast<T*>(
                realloc(this->arr, sizeof(T) * this->max)
            );
            p = this->arr + this->n;
        }
        // copy value *a into array
        *(p++) = *(a++);
        ++(this->n);
    }
}

template <typename T>
ArrayList<T>::ArrayList(T_IT a, T_IT b) {
    T* p;
    this->n = 0;
    this->max = 8;
    this->arr = static_cast<T*>(malloc(sizeof(T) * this->max));
    p = this->arr;
    while (a != b) {
        // ensure capacity
        if (this->max <= this->n) {
            this->max = 2 * this->n;
            this->arr = static_cast<T*>(
                realloc(this->arr, sizeof(T) * this->max)
            );
            p = this->arr + this->n;
        }
        // copy value *a into array
        *(p++) = *(a++);
        ++(this->n);
    }
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
    this->n = other.n;
    this->max = other.max;
    this->arr = static_cast<T*>(malloc(sizeof(T) * this->max));
    memcpy(this->arr, other.arr, sizeof(T) * this->n);
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other) {
    if (this != &other) {
        this->n = other.n;
        this->max = other.max;
        free(this->arr);
        this->arr = static_cast<T*>(malloc(sizeof(T) * this->max));
        memcpy(this->arr, other.arr, sizeof(T) * this->n);
    }
    return *this;
}

template <typename T>
ArrayList<T>::ArrayList(ArrayList<T>&& tmp) {
    this->n = tmp.n;
    this->max = tmp.max;
    this->arr = tmp.arr;
    tmp.arr = NULL;
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T>&& tmp) {
    if (this != &tmp) {
        free(this->arr);
        this->n = tmp.n;
        this->max = tmp.max;
        this->arr = tmp.arr;
        tmp.arr = NULL;
    }
    return *this;
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
    this->arr = static_cast<T*>(realloc(this->arr, sizeof(T) * this->n));
    this->max = this->n;
}

template <typename T>
void ArrayList<T>::reserve(size_t min) {
    if (this->max < min) {
        this->max = 2*min;
        this->arr = static_cast<T*>(realloc(this->arr, sizeof(T) * this->max));
    }
}

template <typename T>
void ArrayList<T>::resize(size_t size) {
    reserve(size);
    T* p = this->arr + this->n;
    if (size < this->n) {
        this->n = size;
    }
    while (this->n < size) {
        *(p++) = T();
        ++(this->n);
    }
}

template <typename T>
void ArrayList<T>::resize(size_t size, const T& filler) {
    reserve(size);
    T* p = this->arr + n;
    if (size < this->n) {
        this->n = size;
    }
    while (this->n < size) {
        *(p++) = filler;
        ++(this->n);
    }
}

template <typename T>
void ArrayList<T>::fill(const T& filler) {
    T* p = this->arr;
    size_t j = this->n;
    while (j--) {
        *(p++) = filler;
    }
}

template <typename T>
T* ArrayList<T>::data() {
    return this->arr;
}

template <typename T>
typename T_IT ArrayList<T>::insert(ssize_t j, const T& x) {
    T* p;
    if (j < 0) {
        j += n;
    }
    if (abs(j) > this->n) {
        throw std::out_of_range("index too high");
    } else if (j < 0) {
        throw std::out_of_range("index too low");
    }
    // j in {0, 1, 2, ..., n}
    reserve(this->n + 1);
    j = this->n - j;
    p = this->arr + (this->n++);
    while (j--) {
        *p = *(p-1); // copy values to the right 1 step
        --p;
    }
    *p = x;
    return T_IT(p);
}

//template <typename T>
//typename T_IT ArrayList<T>::insert(ssize_t j, size_t n, const T& filler) {
//    return NULL;
//}

template <typename T>
typename T_IT ArrayList<T>::insert(T_IT j, const T& x) {
    T* p;
    ssize_t jj = j.ptr - this->arr; // ptr j may become invalid
    reserve(this->n + 1);
    jj = this->n - jj;
    p = this->arr + (this->n++);
    while (jj--) {
        *p = *(p-1); // copy values to the right 1 step
        --p;
    }
    *p = x;
    return T_IT(p);
}

//template <typename T>
//T_IT ArrayList<T>::insert(T_IT j, size_t n, const T& filler)

//template <typename T>
//T_IT ArrayList<T>::insert(T_IT j, T_IT k, const T& filler)


//template <typename T>
//T_IT ArrayList<T>::remove(ssize_t j) {return NULL;}
//
//template <typename T>
//T_IT ArrayList<T>::remove(ssize_t j, ssize_t k) {return NULL;}
//
//template <typename T>
//T_IT ArrayList<T>::remove(T_IT j) {return NULL;}
//
//template <typename T>
//T_IT ArrayList<T>::remove(T_IT j, T_IT k) {return NULL;}


template <typename T>
T_IT::Iterator(T* p) {
    this->ptr = p;
}

template <typename T>
typename T_IT& T_IT::operator++() {
    ++(this->ptr);
    return *this;
}

template <typename T>
typename T_IT T_IT::operator++(int zero) {
    return T_IT(zero + this->ptr++);
}

template <typename T>
typename T_IT& T_IT::operator--() {
    --(this->ptr);
    return *this;
}

template <typename T>
typename T_IT T_IT::operator--(int zero) {
    return T_IT(zero + this->ptr--);
}

template <typename T>
bool T_IT::operator==(const T_IT& other) {
    return this->ptr == other.ptr;
}

template <typename T>
bool T_IT::operator!=(const T_IT& other) {
    return this->ptr != other.ptr;
}

template <typename T>
T& T_IT::operator*() {
    return *(this->ptr);
}

