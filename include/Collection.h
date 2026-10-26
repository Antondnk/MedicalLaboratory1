#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "Exceptions.h"

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

    template <typename Predicate>
    std::vector<T> find_by(Predicate pred) const {
        std::vector<T> result;
        for (const auto& item : items) {
            if (pred(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

#include "Collection.tpp"