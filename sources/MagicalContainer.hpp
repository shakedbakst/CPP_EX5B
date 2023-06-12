#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <vector>
#include <algorithm>


namespace ariel {

    class MagicalContainer {
    private:
        std::vector<int> elements;
        std::vector<int*> ascElem;
        std::vector<int*> crossElem;
        std::vector<int*> primeElem;


    public:
        MagicalContainer() = default; 
        ~MagicalContainer() = default; 

        void addElement(int element);
        void removeElement(int element);
        int size() const;
        std::vector<int> getElements() const;

        

        MagicalContainer(const MagicalContainer& other) = default;
        MagicalContainer& operator=(const MagicalContainer& other) = default;
        MagicalContainer(MagicalContainer&& other) = default;
        MagicalContainer& operator=(MagicalContainer&& other) = default;

        class AscendingIterator {
        private:
            MagicalContainer& container;
            std::vector<int*>::iterator ascIterator;
            size_t index;

        public:
            AscendingIterator(MagicalContainer& container);
            AscendingIterator(const AscendingIterator& other);
            ~AscendingIterator() = default;

            AscendingIterator(AscendingIterator&& other) = default;
            AscendingIterator& operator=(AscendingIterator&& other) = delete;

            AscendingIterator& operator++();

            AscendingIterator& operator=(const AscendingIterator& other);

            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;

            int operator*() const;

            AscendingIterator &begin();
            AscendingIterator &end();
        };

        class SideCrossIterator {
        private:
            MagicalContainer& container;
            std::vector<int*>::iterator crossIterator;
            size_t index;
           

        public:
            SideCrossIterator(MagicalContainer& container);
            SideCrossIterator(const SideCrossIterator& other);
            ~SideCrossIterator() = default;

            SideCrossIterator(SideCrossIterator&& other) = default;
            SideCrossIterator& operator=(SideCrossIterator&& other) = delete;

            SideCrossIterator& operator++();

            SideCrossIterator& operator=(const SideCrossIterator& other);

            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            bool operator>(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;

            int operator*() const;

            SideCrossIterator &begin();
            SideCrossIterator &end();

        };

        class PrimeIterator {
        private:
            MagicalContainer& container;
            std::vector<int*>::iterator primeIterator;
            size_t index;

        public:
            PrimeIterator(MagicalContainer& container);
            PrimeIterator(const PrimeIterator& other);
            ~PrimeIterator() = default;

            PrimeIterator(PrimeIterator&& other) = default;
            PrimeIterator& operator=(PrimeIterator&& other) = delete;

            PrimeIterator& operator++();

            PrimeIterator& operator=(const PrimeIterator& other);
            
            bool operator==(const PrimeIterator& other) const;
            bool operator!=(const PrimeIterator& other) const;
            bool operator>(const PrimeIterator& other) const;
            bool operator<(const PrimeIterator& other) const;
            
            int operator*() const;

            PrimeIterator &begin();
            PrimeIterator &end();
        };

    };

} 


#endif