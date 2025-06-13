#include "../include/GA.hpp"

using namespace std;

GA::GA(Instance instance, int n, int p, double pe, double pm, double rhoe, int maxGens, int maxGensWithoutImprovement, int threads, int seed)
    : instance(instance), n(n), p(p), pe(pe), pm(pm), rhoe(rhoe), maxGens(maxGens), 
      maxGensWithoutImprovement(maxGensWithoutImprovement), threads(threads), seed(seed), rng(seed) {}

Solution GA::createRandomSolution() {
    vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    std::shuffle(perm.begin(), perm.end(), rng);
    return Solution(perm, Origin::RANDOM);
}