#ifndef GA_HPP
#define GA_HPP

#include "Solution.hpp"
#include "Origin.hpp"
#include "tip/Instance.hpp"

#include <random>
#include <vector>
#include <numeric>
#include <algorithm>

class GA {
    private:
        int n;
        int p;
        double pe;
        double pm;
        double rhoe;
        int maxGens;
        int maxGensWithoutImprovement;

        int threads;
        int seed;
        std::mt19937 rng;

        Instance instance;
        
    public:
        GA(Instance instance, int n, int p, double pe, double pm, double rhoe, int maxGens, int maxGensWithoutImprovement, int threads, int seed);
        Solution createRandomSolution();
};

#endif