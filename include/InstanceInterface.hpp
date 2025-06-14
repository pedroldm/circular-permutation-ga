#ifndef INSTANCE_INTERFACE_HPP
#define INSTANCE_INTERFACE_HPP

#include "Chromosome.hpp"

class InstanceInterface {
public:
    virtual ~InstanceInterface() = default;
    virtual int fitness(Chromosome s) const = 0;
};

#endif
