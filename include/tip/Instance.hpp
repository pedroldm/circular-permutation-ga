#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "../Solution.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

class Instance {
    public:
        std::string filePath;
        int tools;
        int slots;
        int HSCost;
        std::vector<int> HSSolution;
        std::vector<std::vector<int>> frequencyMatrix;

        Instance(std::string filePath);
        int fitness(Solution s);
};

#endif