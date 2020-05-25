/*
 * array list
 * @file list/array_list.hpp
 * @author Pavan Dayal
 */

#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

namespace pvn {

    template <typename T>
    class ArrayList {
        private:
        size_t n;
        size_t max;
        T* arr;

        public:
        ArrayList() : ArrayList(8) {}
        explicit ArrayList(size_t max);
        explicit ArrayList(size_t n, const T& filler);
        ~ArrayList();

        size_t size();
        size_t capacity();
        void clear();
        void shrink();

        void reserve(size_t max);
        void resize(size_t max);
        void resize(size_t n, const T& filler);

        T* insert(size_t j, const T& x);
        T* insert(size_t j, size_t n, const T& x);
        T* insert(T* j, const T& x);
        T* insert(T* j, size_t n, const T& x);

        T* remove(size_t j);
        T* remove(size_t j, size_t k);
        T* remove(T* j);
        T* remove(T* j, T* k);
    };
}

#include "array_list.tpp"

#endif // ARRAY_LIST_HPP
