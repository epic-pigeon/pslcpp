//
// Created by nikit on 15.04.2019.
//

#ifndef PSL_COLLECTION_H
#define PSL_COLLECTION_H

template < typename T, class alloc = std::allocator<T> >
class collection {
public:
    typedef T* pointer;
    typedef T& reference;
    typedef size_t size_type;
private:
    alloc allocator;
    T** element_storage;
    size_type length = 0;
public:
    collection& add(T value) {
        T* value_ptr = allocator.allocate(1);
        *value_ptr = value;

        T** save = new T*[length];
        for (size_type i = 0; i < length; i++) save[i] = element_storage[i];

        element_storage = new T*[length + 1];
        for (size_type i = 0; i < length; i++) element_storage[i] = save[i];

        delete[] save;

        element_storage[length + 1] = value_ptr;
        length++;

        return *this;
    }
};


#endif //PSL_COLLECTION_H
