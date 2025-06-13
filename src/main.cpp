#include <iostream>
#include "../include/GA.hpp"
#include "../include/tip/Instance.hpp"
#include "../include/Chromosome.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    string filePath;
    int p = 1000;
    double pe = 0.10;
    double pm = 0.20;
    double rhoe = 0.60;
    double wheelBias = 50.0;
    int mutationType = 1;
    int maxGens = 1000;
    int maxGensWithoutImprovement = 1000;
    int threads = 4;
    int seed = 123;
    int maxTime = 10;

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
        else if (arg.find("--wheelBias=") == 0)
            wheelBias = std::atof(arg.substr(12).c_str());
        else if (arg.find("--threads=") == 0)
            threads = std::atoi(arg.substr(10).c_str());
        else if (arg.find("--seed=") == 0)
            seed = std::atoi(arg.substr(7).c_str());
        else if (arg.find("--maxTime=") == 0)
            maxTime = std::atoi(arg.substr(10).c_str());
        else if (arg.find("--mutationType=") == 0)
            mutationType = std::atoi(arg.substr(15).c_str());
    }

    Instance instance(filePath);
    GA ga(
        instance,
        instance.tools,
        p,
        pe,
        pm,
        rhoe,
        maxGens,
        maxGensWithoutImprovement,
        wheelBias,
        mutationType,
        threads,
        seed,
        maxTime
    );
    ga.run();
    ga.JSONOutput(cout);
}