#ifndef ORIGIN_HPP
#define ORIGIN_HPP

#include <ostream>

enum class Origin {
    RANDOM,
    CYCLIC_CROSSOVER,
    ORDER_CROSSOVER,
    SWAP_MUTATION,
    TWOOPT_MUTATION,
    REINSERTION_MUTATION
};

inline std::ostream& operator<<(std::ostream& os, Origin o) {
    switch(o) {
        case Origin::RANDOM:                return os << "INITIAL";
        case Origin::SWAP_MUTATION:         return os << "SWAP_MUTATION";
        case Origin::TWOOPT_MUTATION:       return os << "TWOOPT_MUTATION";
        case Origin::REINSERTION_MUTATION:  return os << "REINSERTION_MUTATION";
        case Origin::CYCLIC_CROSSOVER:      return os << "CYCLIC_CROSSOVER";
        case Origin::ORDER_CROSSOVER:       return os << "ORDER_CROSSOVER";
        default:                            return os << "UNKNOWN";
    }
}

inline std::string to_string(Origin o) {
    switch (o) {
        case Origin::RANDOM:                return "INITIAL";
        case Origin::SWAP_MUTATION:         return "SWAP_MUTATION";
        case Origin::TWOOPT_MUTATION:       return "TWOOPT_MUTATION";
        case Origin::REINSERTION_MUTATION:  return "REINSERTION_MUTATION";
        case Origin::CYCLIC_CROSSOVER:      return "CYCLIC_CROSSOVER";
        case Origin::ORDER_CROSSOVER:       return "ORDER_CROSSOVER";
        default:                            return "UNKNOWN";
    }
}

#endif
