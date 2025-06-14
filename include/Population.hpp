#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include <algorithm>
#include "Chromosome.hpp"

class Population {
    private:
        int n;
        std::vector<Chromosome> chromosomes;

    public:
        Population(int n);
        void sortByFitness();

        Chromosome& operator[](size_t index);
        const Chromosome& operator[](size_t index) const;
        auto begin() { return chromosomes.begin(); }
        auto end() { return chromosomes.end(); }
        auto begin() const { return chromosomes.begin(); }
        auto end() const { return chromosomes.end(); }
        Chromosome& back();
};

#endif
