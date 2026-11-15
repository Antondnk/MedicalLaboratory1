#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "exceptions/Exceptions.h"

template <typename T>
class Collection {
private:
    std::vector<T> items;

public:
    Collection() = default;
    virtual ~Collection() = default;

    void add(const T& item);
    void remove(int index);
    T& get(int index);
    const T& get(int index) const;
    int size() const;
    bool empty() const;
    void clear();
    void display() const;
    int find_object(const T& item) const;

    typename std::vector<T>::iterator begin() { return items.begin(); }
    typename std::vector<T>::iterator end() { return items.end(); }
    typename std::vector<T>::const_iterator begin() const { return items.begin(); }
    typename std::vector<T>::const_iterator end() const { return items.end(); }

    template <typename Predicate>
    std::vector<T> find_by(Predicate pred) const {
        std::vector<T> result;
        std::copy_if(items.begin(), items.end(), std::back_inserter(result), pred);
        return result;
    }
};

#include "Collection.tpp"
