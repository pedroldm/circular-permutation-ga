#include "../include/Chromosome.hpp"

using namespace std;

Chromosome::Chromosome() : permutation(), fitness(numeric_limits<int>::max()), origin() {}
Chromosome::Chromosome(vector<int> perm, int fitness, Origin org) : permutation(move(perm)), fitness(fitness), origin(org) {}
Chromosome::Chromosome(vector<int> perm, Origin org) : permutation(move(perm)), origin(org) {}
Chromosome::Chromosome(int n, int def, Origin org) : permutation(n, def), fitness(numeric_limits<int>::max()), origin(org) {}

int& Chromosome::operator[](size_t index) {
    return permutation[index];
}

const int& Chromosome::operator[](size_t index) const {
    return permutation[index];
}