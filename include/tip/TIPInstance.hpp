#ifndef TIPINSTANCE_HPP
#define TIPINSTANCE_HPP

#include "../Chromosome.hpp"
#include "../InstanceInterface.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

class TIPInstance : public InstanceInterface {
    public:
        std::string filePath;
        int tools;
        int slots;
        int emptySpaces;
        int WSACost;
        std::vector<int> HSChromosome;
        std::vector<std::vector<int>> frequencyMatrix;

        TIPInstance(std::string filePath);
        int fitness(Chromosome s) const override;
};

#endif