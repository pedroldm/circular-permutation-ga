#ifndef GA_HPP
#define GA_HPP

#include "Chromosome.hpp"
#include "Origin.hpp"
#include "InstanceInterface.hpp"
#include "Population.hpp"
#include "ConvergenceEntry.hpp"
#include "tip/TIPInstance.hpp"
#include "JSON.hpp"

#include <random>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <unordered_set>

class GA {
    private:
        int n;
        int p;
        double pe;
        double pm;
        double rhoe;
        int maxGens;
        int maxGensWithoutImprovement;
        double wheelBias;
        int mutationType;
        int crossoverType;
        Population currP;

        int currentGen;
        int gensWithoutImprovement;
        int elapsedMinutes;

        int threads;
        int seed;
        int maxTime;
        std::mt19937 rng;
        std::uniform_int_distribution<size_t> ztn;
        std::uniform_int_distribution<size_t> coinFlip;

        std::vector<ConvergenceEntry> convergenceLog;

        InstanceInterface& instance;
    public:
        GA(InstanceInterface& instance, int n, int p, double pe, double pm, double rhoe, int maxGens, 
            int maxGensWithoutImprovement, double wheelBias, int mutationType, int crossoverType, int threads, int seed, int maxTime);
        void run();
        std::pair<Chromosome, Chromosome> cyclicCrossover(Chromosome& c1, Chromosome& c2);
        Chromosome createRandomChromosome();
        Population createInitialPopulation();
        void calculatePopulationFitness(Population& pop);
        void reproduction(Population& currP, Population& nextP);
        int biasedWheelSelection(Population& p, std::vector<double>& biasedFitness, double& totalBiasedFitness, std::uniform_real_distribution<double>& dist);
        void swapMutation(Chromosome& c);
        void twoOptMutation(Chromosome& c);
        void reinsertionMutation(Chromosome& c);
        void TIPJSONOutput(std::ostream& os);
        std::pair<Chromosome, Chromosome> orderCrossover(Chromosome& c1, Chromosome& c2);
        void CBPJSONOutput(std::ostream& os);
};

#endif