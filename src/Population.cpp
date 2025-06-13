#include "../include/Population.hpp"

using namespace std;

Population::Population(int n) : n(n) {
    this->chromosomes.resize(n);
}

void Population::sortByFitness() {
    std::sort(this->chromosomes.begin(), this->chromosomes.end(), [](const Chromosome& a, const Chromosome& b) {
        return a.fitness < b.fitness;
    });
}

Chromosome& Population::operator[](size_t index) {
    return chromosomes[index];
}

const Chromosome& Population::operator[](size_t index) const {
    return chromosomes[index];
}

Chromosome& Population::back() {
    return chromosomes[n - 1];
}