#include "../include/Solution.hpp"

using namespace std;

Solution::Solution(vector<int> perm, int fitness, Origin org) : permutation(move(perm)), fitness(fitness), origin(org) {}
Solution::Solution(vector<int> perm, Origin org) : permutation(move(perm)), origin(org) {}