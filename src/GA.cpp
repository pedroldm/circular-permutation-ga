#include "../include/GA.hpp"

using namespace std;

GA::GA(Instance instance, int n, int p, double pe, double pm, double rhoe, int maxGens, int maxGensWithoutImprovement, int threads, int seed)
    : instance(instance), n(n), p(p), pe(pe), pm(pm), rhoe(rhoe), maxGens(maxGens), 
      maxGensWithoutImprovement(maxGensWithoutImprovement), threads(threads),
      seed(seed), rng(seed), dist(0, n - 1) {}

pair<Chromosome, Chromosome> GA::circularCrossover(Chromosome& c1, Chromosome& c2) {
    Chromosome offspring1(this->n, -1, Origin::CYCLIC_CROSSOVER);
    Chromosome offspring2(this->n, -1, Origin::CYCLIC_CROSSOVER);
    vector<bool> visited(this->n, false);

    unordered_map<int, size_t> c1IndexValueMap;
    for (size_t i = 0; i < this->n; ++i) {
        c1IndexValueMap[c1[i]] = i;
    }

    size_t idx = this->dist(this->rng);
    while (!visited[idx]) {
        visited[idx] = true;
        offspring1[idx] = c1[idx];
        offspring2[idx] = c2[idx];
        idx = c1IndexValueMap[c2[idx]];
    }

    for (size_t i = 0; i < this->n; ++i) {
        if (!visited[i]) {
            offspring1[i] = c2[i];
            offspring2[i] = c1[i];
        }
    }

    return { offspring1, offspring2 };
}

Chromosome GA::createRandomChromosome() {
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rng);
    return Chromosome(perm, Origin::RANDOM);
}

Population GA::createInitialPopulation() {
    Population pop = Population(this->p);
    for(unsigned i = 0 ; i < this->p ; i++) {
        pop[i] = this->createRandomChromosome();
    }
    return pop;
}

void GA::calculatePopulationFitness(Population& pop) {
    for (auto& chromo : pop) {
        chromo.fitness = this->instance.fitness(chromo);
    }
}