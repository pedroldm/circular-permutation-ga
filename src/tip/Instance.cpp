#include "../../include/tip/TIPInstance.hpp"

using namespace std;

TIPInstance::TIPInstance(string filePath) : filePath(filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + filePath);
    }

    file >> this->tools >> this->slots;
    this->emptySpaces = this->slots - this->tools;

    this->HSChromosome.resize(this->slots);
    for (int i = 0; i < this->slots; i++) {
        string value;
        file >> value;
        HSChromosome[i] = (value == "x") ? -1 : stoi(value) - 1;
    }

    file >> this->WSACost;

    this->frequencyMatrix.resize(this->tools, vector<int>(this->tools));
    for (int i = 0; i < this->tools; i++) {
        for (int j = 0; j < this->tools; ++j) {
            file >> this->frequencyMatrix[i][j];
        }
    }
}

int TIPInstance::fitness(Chromosome s) const {
    unordered_map<int, int> toolIndex;

    for (int i = 0; i < this->tools; i++) {
        toolIndex[s.permutation[i]] = i;
    }

    int totalCost = 0;

    for (int i = 0; i < this->tools; i++) {
        for (int j = i + 1; j < this->tools; j++) {
            if (!this->frequencyMatrix[i][j]) 
                continue;
            int dist = abs(toolIndex[i] - toolIndex[j]);
            int circularDist = min(dist, (this->tools - dist) + this->emptySpaces);
            totalCost += this->frequencyMatrix[i][j] * circularDist;
        }
    }

    return totalCost;
}