#ifndef GA_HPP
#define GA_HPP

#include "Chromosome.hpp"
#include "Origin.hpp"
#include "tip/Instance.hpp"
#include "Population.hpp"

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
        std::uniform_int_distribution<size_t> dist;

        Instance instance;
    public:
        GA(Instance instance, int n, int p, double pe, double pm, double rhoe, int maxGens, int maxGensWithoutImprovement, int threads, int seed);
        std::pair<Chromosome, Chromosome> circularCrossover(Chromosome& c1, Chromosome& c2);
        Chromosome createRandomChromosome();
        Population createInitialPopulation();
        void calculatePopulationFitness(Population& pop);
};

#endif