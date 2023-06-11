#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

#include "MagicalContainer.hpp"

using namespace std;

bool static isPrime(int number){
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;  
        }
    }
    return true;
}

namespace ariel {
    

    void MagicalContainer::addElement(int element) {
        for(int run : elements){
            if(run == element){
                return;
            }
        }

        auto iter = std::lower_bound(elements.begin(), elements.end(), element);
        elements.insert(iter, element);

        // Rebuilding ascElement
        ascElem.clear();
        for (auto& element : elements) {
            ascElem.push_back(&element);
        }

        std::sort(ascElem.begin(), ascElem.end(), [](int* a, int* b) {
            return *a < *b;
        });

        // Rebuilding crossElements
        crossElem.clear();

        auto start = elements.begin();
        auto end = --elements.end();

        while (start < end) {
            crossElem.push_back(&*start);
            crossElem.push_back(&*end);
            start++;
            end--;
        }

        if (start == end) {
            crossElem.push_back(&*start);
        }

        // Rebuilding primeElements
        primeElem.clear();
        for(size_t i = 0; i < elements.size(); i++){
            if(isPrime(elements[i])){
                primeElem.push_back(&elements[i]);
            }
        }
    }

    void MagicalContainer::removeElement(int element) {
        // Check if elem is in mainElements
        auto it = find(elements.begin(), elements.end(), element);
        if (it == elements.end()) {
            throw runtime_error("Invalid argument");
        }

        // Erase the element from mainElements
        elements.erase(it);

        // Rebuilding ascElement
        ascElem.clear();
        for (auto& element : elements) {
            ascElem.push_back(&element);
        }

        std::sort(ascElem.begin(), ascElem.end(), [](int* a, int* b) {
            return *a < *b;
        });

        // Rebuilding crossElements
        crossElem.clear();

        auto start = elements.begin();
        auto end = --elements.end();

        while (start < end) {
            crossElem.push_back(&*start);
            crossElem.push_back(&*end);
            start++;
            end--;
        }

        if (start == end) {
            crossElem.push_back(&*start);
        }

        // Rebuilding primeElements
        primeElem.clear();
        for(size_t i = 0; i < elements.size(); i++){
            if(isPrime(elements[i])){
                primeElem.push_back(&elements[i]);
            }
        }
    }

    int MagicalContainer::size() const {
        return this->elements.size();
    }

    vector<int> MagicalContainer::getElements() const {
        return this->elements;
    }

    // AscendingIterator

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) : container(container),  ascIterator(container.ascElem.begin()), index(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other): container(other.container), ascIterator(other.ascIterator), index(other.index){}

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        if (ascIterator != container.ascElem.end()) {
        ++ascIterator;
        ++index;
        } else {
            throw std::out_of_range("Out of range");
        }
        return *this;
    }
    

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid arguments");
        }
        return ascIterator == other.ascIterator;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid argument");
        }
        return ascIterator != other.ascIterator;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid argument");
        }
        return ascIterator > other.ascIterator;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid argument");
        }
        return ascIterator < other.ascIterator;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::runtime_error("Iterators are pointing at different containers");
        }

        ascIterator = other.container.ascElem.begin() + (other.ascIterator - other.container.ascElem.begin());
        index = other.index;

        return *this;
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        if (ascIterator == container.ascElem.end()) {
            throw std::out_of_range("Out of range");
        }
        return **ascIterator;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::begin() {
        ascIterator = container.ascElem.begin();
        index = 0;
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::end() {
        ascIterator = container.ascElem.end();
        index = container.ascElem.size();
        return *this;
    }

    // SideCrossIterator

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) : container(container), crossIterator(container.crossElem.begin()), index(0) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other): container(other.container), crossIterator(other.crossIterator), index(other.index){}

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if (crossIterator != container.crossElem.end()) {
        ++crossIterator;
        ++index;
        } else {
            throw std::out_of_range("Out of range");
        }
        return *this;
    }
    

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid arguments");
        }
        return crossIterator == other.crossIterator;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid argument");
        }
        return crossIterator != other.crossIterator;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid argument");
        }
        return crossIterator > other.crossIterator;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid argument");
        }
        return crossIterator < other.crossIterator;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::runtime_error("Iterators are pointing at different containers");
        }

        crossIterator = other.container.crossElem.begin() + (other.crossIterator - other.container.crossElem.begin());
        index = other.index;

        return *this;
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        if (crossIterator == container.crossElem.end()) {
            throw std::out_of_range("Out of range");
        }
        return **crossIterator;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::begin() {
        crossIterator = container.crossElem.begin();
        index = 0;
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::end() {
        crossIterator = container.crossElem.end();
        index = container.crossElem.size();
        return *this;
    }

    // PrimeIterator

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) : container(container), primeIterator(container.primeElem.begin()), index(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other): container(other.container), primeIterator(other.primeIterator), index(other.index){}

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
        if (primeIterator != container.primeElem.end()) {
        ++primeIterator;
        ++index;
        } else {
            throw std::out_of_range("Out of range");
        }
        return *this;
    }
    

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid arguments");
        }
        return primeIterator == other.primeIterator;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid argument");
        }
        return primeIterator != other.primeIterator;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid argument");
        }
        return primeIterator > other.primeIterator;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::invalid_argument("Invalid argument");
        }
        return primeIterator < other.primeIterator;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
        if (container.getElements().size() != other.container.getElements().size()) {
            throw std::runtime_error("Iterators are pointing at different containers");
        }

        primeIterator = other.container.primeElem.begin() + (other.primeIterator - other.container.primeElem.begin());
        index = other.index;

        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        if (primeIterator == container.primeElem.end()) {
            throw std::out_of_range("Out of range");
        }
        return **primeIterator;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::begin() {
        primeIterator = container.primeElem.begin();
        index = 0;
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::end() {
        primeIterator = container.primeElem.end();
        index = container.primeElem.size();
        return *this;
    }
}