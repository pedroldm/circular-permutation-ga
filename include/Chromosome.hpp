#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#include <vector>
#include <limits>
#include <cstddef>
#include "Origin.hpp"

class Chromosome {
    public:
        std::vector<int> permutation;
        int fitness;
        Origin origin;

        Chromosome();
        Chromosome(std::vector<int> perm, int fit, Origin org);
        Chromosome(std::vector<int> perm, Origin org);
        Chromosome(int n, int def, Origin org);

        int& operator[](size_t index);
        const int& operator[](size_t index) const;
};

#endif
