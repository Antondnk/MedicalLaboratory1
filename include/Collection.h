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

    void add(const T& item) {
        items.push_back(item);
    }

    void remove(int index) {
        if (index < 0 || index >= static_cast<int>(items.size())) {
            throw IndexOutOfBoundsException("Ошибка: Невозможно удалить элемент, индекс вне диапазона!");
        }
        items.erase(items.begin() + index);
    }

    T& get(int index) {
        if (index < 0 || index >= static_cast<int>(items.size())) {
            throw IndexOutOfBoundsException("Ошибка: Индекс элемента выходит за границы коллекции!");
        }
        return items[index];
    }

    const T& get(int index) const {
        if (index < 0 || index >= static_cast<int>(items.size())) {
            throw IndexOutOfBoundsException("Ошибка: Индекс элемента выходит за границы коллекции!");
        }
        return items[index];
    }

    int size() const {
        return static_cast<int>(items.size());
    }

    bool empty() const {
        return items.empty();
    }

    void clear() {
        items.clear();
    }

    void display() const {
        if (items.empty()) {
            throw NotFoundException("Коллекция пуста!");
        }
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << "[" << i + 1 << "]\n" << items[i] << "\n";
        }
    }

    // Шаблонная функция для поиска элементов по заданному критерию (предикату)
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