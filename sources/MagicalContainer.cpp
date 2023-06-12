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
        for(int i : elements){
            if(i == element){
                return;
            }
        }
    
        auto it = std::upper_bound(elements.begin(), elements.end(), element);
        elements.insert(it, element);

        // Rebuilding ascElement
        ascElem.resize(elements.size());
        std::transform(elements.begin(), elements.end(), ascElem.begin(), [](int& e) { return &e; });
        std::sort(ascElem.begin(), ascElem.end(), [](int* a, int* b) {
            return *a < *b;
        });

        // Rebuilding crossElements
        crossElem.clear();
        crossElem.reserve(elements.size());
        auto start = elements.begin();
        auto end = elements.end() - 1;

        while (start <= end) {
            crossElem.push_back(&(*start));
            if (start != end) {
                crossElem.push_back(&(*end));
            }
            start++;
            end--;
        }

        // Rebuilding primeElements
        primeElem.clear();
        primeElem.reserve(elements.size());
        for (int& p : elements) {
            if (isPrime(p)) {
                primeElem.push_back(&p);
            }
        }
    }


    void MagicalContainer::removeElement(int element) {
        bool inElem = false;
        for(int i : elements){
            if(i == element){
                inElem = true;
            }
        }
        if(!inElem){
            throw std::runtime_error("The Element not in the container!");
        }

        auto it = std::upper_bound(elements.begin(), elements.end(), element);
        elements.erase(it);
    }


    int MagicalContainer::size() const {
        return this->elements.size();
    }

    vector<int> MagicalContainer::getElements() const {
        return this->elements;
    }

    //------------------------------AscendingIterator------------------------------//

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) : container(container), index(0) {
        ascIterator = container.ascElem.begin();
    }

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other): container(other.container), index(other.index){
        ascIterator = other.ascIterator;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        if (ascIterator != container.ascElem.end()) {
        ++ascIterator;
        ++index;
        } else {
            throw std::runtime_error("Run time error");
        }
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
        if(this != &other){
            if (&container != &other.container) {
                throw std::runtime_error("Iterators are pointing at different containers");
            }

            ascIterator = other.ascIterator;
            index = other.index;
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

    int MagicalContainer::AscendingIterator::operator*() const {
        if (ascIterator == container.ascElem.end()) {
            throw std::out_of_range("Out of range");
        }
        return *(*ascIterator);
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

    //------------------------------SideCrossIterator------------------------------//

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) : container(container), index(0) {
        crossIterator = container.crossElem.begin(); 
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other): container(other.container), index(other.index){
        crossIterator = other.crossIterator;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if (crossIterator != container.crossElem.end()) {
        ++crossIterator;
        ++index;
        } else {
            throw std::runtime_error("Run time error");
        }
        return *this;
    }
    
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
        if(this != &other){
            if (&container != &other.container) {
                throw std::runtime_error("Iterators are pointing at different containers");
            }

            crossIterator = other.crossIterator;
            index = other.index;
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

    int MagicalContainer::SideCrossIterator::operator*() const {
        if (crossIterator == container.crossElem.end()) {
            throw std::out_of_range("Out of range");
        }
        return *(*crossIterator);
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

    //------------------------------PrimeIterator------------------------------//

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) : container(container), index(0) {
        primeIterator = container.primeElem.begin();
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other): container(other.container), index(other.index){
        primeIterator = other.primeIterator;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
        if (primeIterator != container.primeElem.end()) {
        ++primeIterator;
        ++index;
        } else {
            throw std::runtime_error("Run time error");
        }
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
        if(this != &other){
            if (&container != &other.container) {
                throw std::runtime_error("Iterators are pointing at different containers");
            }

            primeIterator = other.primeIterator;
            index = other.index;
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

    int MagicalContainer::PrimeIterator::operator*() const {
        if (primeIterator == container.primeElem.end()) {
            throw std::out_of_range("Out of range");
        }
        return *(*primeIterator);
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