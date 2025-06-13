#ifndef ORIGIN_HPP
#define ORIGIN_HPP

#include <ostream>

enum class Origin {
    RANDOM,
    CYCLIC_CROSSOVER,
    MUTATION,
};

inline std::ostream& operator<<(std::ostream& os, Origin o) {
    switch(o) {
        case Origin::RANDOM:            return os << "INITIAL";
        case Origin::MUTATION:           return os << "MUTATION";
        case Origin::CYCLIC_CROSSOVER:   return os << "CYCLIC_CROSSOVER";
        default:                         return os << "UNKNOWN";
    }
}

inline std::string to_string(Origin o) {
    switch (o) {
        case Origin::RANDOM:             return "INITIAL";
        case Origin::MUTATION:           return "MUTATION";
        case Origin::CYCLIC_CROSSOVER:   return "CYCLIC_CROSSOVER";
        default:                         return "UNKNOWN";
    }
}

#endif
