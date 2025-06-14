#ifndef CBPINSTANCE_HPP
#define CBPINSTANCE_HPP

#include "../Chromosome.hpp"
#include "../InstanceInterface.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

class CBPInstance : public InstanceInterface {
    public:
        std::string filePath;
        int nodeCount;
        int edgeCount;
        int criticNodes;
        std::vector<std::vector<bool>> adjacencyMatrix;

        CBPInstance(std::string filePath);
        int fitness(Chromosome s) const override;
};

#endif