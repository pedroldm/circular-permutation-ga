#include "../../include/cbp/CBPInstance.hpp"

using namespace std;

CBPInstance::CBPInstance(string filePath) : filePath(filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + filePath);
    }

    std::string dummy;
    std::getline(file, dummy);
    
    file >> this->nodeCount >> this->criticNodes >> this->edgeCount;
    this->adjacencyMatrix.resize(this->nodeCount, vector<bool>(this->nodeCount));

    int n1, n2;
    for(int i = 0 ; i < edgeCount ; i++) {
        file >> n1 >> n2;
        this->adjacencyMatrix[n1-1][n2-1] = true;
        this->adjacencyMatrix[n2-1][n1-1] = true;
    }
}

int CBPInstance::fitness(Chromosome s) const {
    std::vector<int> position(this->nodeCount);
    for (int i = 0; i < this->nodeCount; ++i) {
        position[s[i]] = i;
    }

    int maxDistance = 0;

    for (int i = 0; i < this->nodeCount; ++i) {
        for (int j = i + 1; j < this->nodeCount; ++j) {
            if (!this->adjacencyMatrix[i][j])
                continue;

            int pos_i = position[i];
            int pos_j = position[j];

            int d = std::abs(pos_i - pos_j);
            int cyclicDistance = std::min(d, this->nodeCount - d);

            if (cyclicDistance > maxDistance) {
                maxDistance = cyclicDistance;
            }
        }
    }

    return maxDistance;
}