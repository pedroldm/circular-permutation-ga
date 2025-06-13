#include "../../include/tip/Instance.hpp"

using namespace std;

Instance::Instance(string filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + filePath);
    }

    file >> this->tools >> this->slots;

    this->HSSolution.resize(this->slots);
    for (int i = 0; i < this->slots; i++) {
        string value;
        file >> value;
        HSSolution[i] = (value == "x") ? -1 : stoi(value) - 1;
    }

    file >> this->HSCost;

    this->frequencyMatrix.resize(this->tools, vector<int>(this->tools));
    for (int i = 0; i < this->tools; i++) {
        for (int j = 0; j < this->tools; ++j) {
            file >> this->frequencyMatrix[i][j];
        }
    }
}

int Instance::fitness(Solution s) {
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
            int circularDist = min(dist, (this->tools - dist) + (this->slots - this->tools));
            totalCost += this->frequencyMatrix[i][j] * circularDist;
        }
    }

    return totalCost;
}