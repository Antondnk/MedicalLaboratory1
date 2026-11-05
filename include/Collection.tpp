#pragma once
#include "Collection.h"

template <typename T>
void Collection<T>::add(const T& item) {
    items.push_back(item);
}

template <typename T>
void Collection<T>::remove(int index) {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        throw IndexOutOfBoundsException("Невозможно удалить элемент: индекс " + std::to_string(index + 1) +
            " вне диапазона (в коллекции элементов: " + std::to_string(items.size()) + ").");
    }
    items.erase(items.begin() + index);
}

template <typename T>
T& Collection<T>::get(int index) {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        throw IndexOutOfBoundsException("Элемента с номером " + std::to_string(index + 1) +
            " нет (в коллекции элементов: " + std::to_string(items.size()) + ").");
    }
    return items[index];
}

template <typename T>
const T& Collection<T>::get(int index) const {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        throw IndexOutOfBoundsException("Элемента с номером " + std::to_string(index + 1) +
            " нет (в коллекции элементов: " + std::to_string(items.size()) + ").");
    }
    return items[index];
}

template <typename T>
int Collection<T>::size() const {
    return static_cast<int>(items.size());
}

template <typename T>
bool Collection<T>::empty() const {
    return items.empty();
}

template <typename T>
void Collection<T>::clear() {
    items.clear();
}

template <typename T>
void Collection<T>::display() const {
    if (items.empty()) {
        throw NotFoundException("Коллекция пуста!");
    }
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "[" << i + 1 << "]\n" << items[i] << "\n";
    }
}

template <typename T>
int Collection<T>::find_object(const T& item) const {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i] == item) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
