//
// Created by nikit on 15.04.2019.
//

#include <sstream>
#include "collection.h"

template <typename T, class alloc>
collection<T, alloc>& collection<T, alloc>::add(T value) {
    T* value_ptr = allocator.allocate(1);
    *value_ptr = value;

    T** save = new pointer[length];
    for (size_type i = 0; i < length; i++) save[i] = element_storage[i];

    element_storage = new T*[length + 1];
    for (size_type i = 0; i < length; i++) element_storage[i] = save[i];

    delete[] save;

    element_storage[length] = value_ptr;
    length++;

    return *this;
}
template <typename T, class alloc>
typename collection<T, alloc>::reference
        collection<T, alloc>::get(collection<T, alloc>::size_type i) {
    if (i < length) {
        return *(element_storage[i]);
    } else throw collection<T, alloc>::index_out_of_bounds(i, length);
}

template<typename T, class alloc>
collection<T, alloc>::collection(): length(0) {}

template<typename T, class alloc>
typename collection<T, alloc>::reference
        collection<T, alloc>::operator[](collection<T, alloc>::size_type i) {
    return get(i);
}

template<typename T, class alloc>
typename collection<T, alloc>::reference
        collection<T, alloc>::set(collection::size_type i, T value) {
    reference ref = get(i);
    ref = value;
    return ref;
}

template<typename T, class alloc>
collection<T, alloc> collection<T, alloc>::operator+(T element) {
    collection<T, alloc> result;
    result.add_all(*this).add(element);
    return result;
}

template<typename T, class alloc>
collection<T, alloc> &collection<T, alloc>::add_all(collection<T, alloc> another) {
    for (collection<T, alloc>::iterator i = another.begin(); i < another.end(); i++) {
        add(another[i]);
    }
}

template<typename T, class alloc>
typename collection<T, alloc>::size_type
        collection<T, alloc>::size() {
    return length;
}

template<typename T, class alloc>
typename collection<T, alloc>::iterator collection<T, alloc>::begin() {
    return collection::iterator(0, this);
}

template<typename T, class alloc>
typename collection<T, alloc>::iterator collection<T, alloc>::end() {
    return collection::iterator(length, this);
}

template<typename T, class alloc>
const char *collection<T, alloc>::index_out_of_bounds::what() const throw() {
    std::stringstream stringstream;
    stringstream << "Array length: " << length << ", required index: " << i;
    return stringstream.str().c_str();
}

template<typename T, class alloc>
collection<T, alloc>::index_out_of_bounds::index_out_of_bounds(collection::size_type i, collection::size_type length)
    :i(i), length(length) {}

template<typename T, class alloc>
bool collection<T, alloc>::iterator::operator<(const collection::iterator &rhs) const {
    return i < rhs.i;
}

template<typename T, class alloc>
bool collection<T, alloc>::iterator::operator>(const collection::iterator &rhs) const {
    return i > rhs.i;
}

template<typename T, class alloc>
bool collection<T, alloc>::iterator::operator<=(const collection::iterator &rhs) const {
    return i <= rhs.i;
}

template<typename T, class alloc>
bool collection<T, alloc>::iterator::operator>=(const collection::iterator &rhs) const {
    return i >= rhs.i;
}

template<typename T, class alloc>
collection<T, alloc>::iterator::iterator(collection::size_type i, collection *outer)
    :i(i), outer(outer) {}

template<typename T, class alloc>
bool collection<T, alloc>::iterator::operator==(const collection::iterator &rhs) const {
    return i == rhs.i;
}

template<typename T, class alloc>
bool collection<T, alloc>::iterator::operator!=(const collection::iterator &rhs) const {
    return !(rhs == *this);
}

template<typename T, class alloc>
typename collection<T, alloc>::iterator collection<T, alloc>::iterator::operator+(int i) {
    return collection::iterator(this->i + i, outer);
}

template<typename T, class alloc>
typename collection<T, alloc>::iterator collection<T, alloc>::iterator::operator-(int i) {
    return collection::iterator(this->i - i, outer);
}

template<typename T, class alloc>
typename collection<T, alloc>::iterator collection<T, alloc>::iterator::operator++() {
    i++;
    return *this;
}

template<typename T, class alloc>
typename collection<T, alloc>::iterator collection<T, alloc>::iterator::operator--() {
    i--;
    return *this;
}

template<typename T, class alloc>
T &collection<T, alloc>::iterator::operator*() {
    return outer->get(i);
}
