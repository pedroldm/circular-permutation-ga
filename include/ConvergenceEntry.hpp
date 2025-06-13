#ifndef CONVERGENCEENTRY_HPP
#define CONVERGENCEENTRY_HPP

#include "Origin.hpp"

struct ConvergenceEntry {
    int generation;
    int bestFitness;
    Origin origin;
    double elapsedSeconds;
};

#endif