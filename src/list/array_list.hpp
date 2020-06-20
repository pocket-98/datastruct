/*
 * array list
 * @file list/array_list.hpp
 * @author Pavan Dayal
 */

#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <initializer_list>

namespace pvn {

    template <typename T>
    class ArrayList {
        public:
        class Iterator;

        private:
        size_t n;
        size_t max;
        T* arr;

        public:
        /**
         * default constructer: reserve capacity for 8 elements
         */
        ArrayList() : ArrayList(8) {}

        /**
         * construct empty array with specified max capacity
         * @param max the max capacity of the new array
         */
        explicit ArrayList(size_t max);

        /**
         * construct an array filled copies of an elements
         * @param n the size of the new array
         * @param filler the value to copy for each element
         */
        explicit ArrayList(size_t n, const T& filler);

        /**
         * construct with a list of elements {a,b,c}
         * @param elems the list of elements
         */
        ArrayList(std::initializer_list<T> elems);

        /**
         * construct by copying an interval of elements [a,b)
         * @param a pointer to first element to copy
         * @param b pointer immediately after last element to copy
         */
        ArrayList(const T* a, const T* b);

        /**
         * construct by copying an interval of elements [a,b)
         * @param a iterator to first element to copy
         * @param b iterator immediately after last element to copy
         */
        ArrayList(Iterator a, Iterator b);

        /**
         * construct by copying another array
         * @param other array to copy
         */
        ArrayList(const ArrayList& other);
        ArrayList& operator=(const ArrayList& other);

        /**
         * construct by moving an rvalue array
         * @param tmp other array to steal from
         */
        ArrayList(ArrayList&& tmp);
        ArrayList& operator=(ArrayList&& tmp);

        /**
         * deconstructor
         */
        ~ArrayList();

        /**
         * get the number of elements
         * @return the number of elements in the array
         */
        size_t size();

        /**
         * get the max possible number of elements
         * @return the max number of elements possible in the array
         */
        size_t capacity();

        /** reset the size to 0 */
        void clear();

        /** shrink capacity down to current size */
        void shrink();

        /**
         * ensure minimum capacity
         * @param min the minimum the capacity should be set to
         */
        void reserve(size_t min);

        /**
         * either shrink the array down to `n` or insert default elements
         * growing the array up to `n`
         * @param n the new array size
         */
        void resize(size_t size);

        /**
         * either shrink the array down to `n` or insert default elements
         * growing the array up to `n` filling with `filler`
         * @param n the new array size
         * @param filler what to copy into new array elements
         */
        void resize(size_t size, const T& filler);

        /**
         * replace every element with a copy of `filler`
         * @param filler what to copy into every element
         */
        void fill(const T& filler);

        /**
         * get pointer to underlying data
         * @return pointer to first element in array
         */
        T* data();

        /**
         * insert the element `x` into array at position `j`
         * @param j index to insert into
         * @param x element to insert
         * @return iterator for position of inserted element
         */
        Iterator insert(ssize_t j, const T& x);

        //Iterator insert(ssize_t j, size_t n, const T& filler);
        Iterator insert(Iterator j, const T& x);
        //Iterator insert(Iterator j, size_t n, const T& filler);
        //Iterator insert(Iterator j, Iterator k, const T& filler);

        //Iterator remove(ssize_t j);
        //Iterator remove(ssize_t j, ssize_t n);
        //Iterator remove(Iterator j);
        //Iterator remove(Iterator j, Iterator k);
    };

    template <typename T>
    class ArrayList<T>::Iterator {
        friend class ArrayList<T>;
        private:
            T* ptr;
            explicit Iterator(T* p);
        public:
            Iterator& operator++();
            Iterator operator++(int zero);
            Iterator& operator--();
            Iterator operator--(int zero);
            bool operator==(const Iterator& other);
            bool operator!=(const Iterator& other);
            T& operator*();
    };
}

#include "array_list.tpp"

#endif // ARRAY_LIST_HPP
