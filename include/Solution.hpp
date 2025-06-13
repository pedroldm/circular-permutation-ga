#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>
#include "Origin.hpp"

class Solution {
    public:
        std::vector<int> permutation;
        int fitness;
        Origin origin;

        Solution(std::vector<int> perm, int fit, Origin org);
        Solution(std::vector<int> perm, Origin org);
};

#endif
