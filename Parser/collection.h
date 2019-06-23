//
// Created by nikit on 15.04.2019.
//

#ifndef PSL_COLLECTION_H
#define PSL_COLLECTION_H

template<typename T, class alloc = std::allocator<T> >
class collection {
public:
    typedef T *pointer;
    typedef T &reference;
    typedef size_t size_type;

    class index_out_of_bounds : public std::exception {
    private:
        size_type i, length;
    public:
        const char* what() const throw();

        index_out_of_bounds(size_type i, size_type length);
    };

    class iterator {
    private:
        size_type i;
        collection* outer;
    public:
        iterator(size_type i, collection* outer);

        bool operator<(const iterator &rhs) const;

        bool operator>(const iterator &rhs) const;

        bool operator<=(const iterator &rhs) const;

        bool operator>=(const iterator &rhs) const;

        bool operator==(const iterator &rhs) const;

        bool operator!=(const iterator &rhs) const;

        iterator operator+ (int i);
        iterator operator- (int i);
        iterator operator++ ();
        iterator operator-- ();

        T &operator*();
    };

private:
    alloc allocator;
    T **element_storage;
    size_type length;
public:
    collection();

    size_type size();

    collection &add(T value);
    collection &add_all(collection another);

    reference get(size_type i);
    reference set(size_type i, T value);

    reference operator[](size_type i);

    collection operator+(T element);

    iterator begin();
    iterator end();
};


#endif //PSL_COLLECTION_H
