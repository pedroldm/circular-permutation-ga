#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "../Chromosome.hpp"

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
        int emptySpaces;
        int HSCost;
        std::vector<int> HSChromosome;
        std::vector<std::vector<int>> frequencyMatrix;

        Instance(std::string filePath);
        int fitness(Chromosome s);
};

#endif