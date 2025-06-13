#include <iostream>
#include "../include/GA.hpp"
#include "../include/tip/Instance.hpp"
#include "../include/Solution.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    string filePath;
    int p;
    double pe;
    double pm;
    double rhoe;
    int maxGens;
    int maxGensWithoutImprovement;
    int threads;
    int seed;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg.find("--filePath=") == 0)
            filePath = arg.substr(11);
        else if (arg.find("--p=") == 0)
            p = std::atoi(arg.substr(4).c_str());
        else if (arg.find("--pe=") == 0)
            pe = std::atof(arg.substr(5).c_str());
        else if (arg.find("--pm=") == 0)
            pm = std::atof(arg.substr(5).c_str());
        else if (arg.find("--rhoe=") == 0)
            rhoe = std::atof(arg.substr(7).c_str());
        else if (arg.find("--maxGens=") == 0)
            maxGens = std::atoi(arg.substr(10).c_str());
        else if (arg.find("--maxGensWithoutImprovement=") == 0)
            maxGensWithoutImprovement = std::atoi(arg.substr(28).c_str());
        else if (arg.find("--threads=") == 0)
            threads = std::atoi(arg.substr(10).c_str());
        else if (arg.find("--seed=") == 0)
            seed = std::atoi(arg.substr(7).c_str());
    }

    Instance instance(filePath);
    GA ga(instance, instance.tools, p, pe, pm, rhoe, maxGens, maxGensWithoutImprovement, threads, seed);
}