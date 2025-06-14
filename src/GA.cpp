#include "../include/GA.hpp"

using namespace std;
using json = nlohmann::json;

GA::GA(InstanceInterface& instance, int n, int p, double pe, double pm, double rhoe, int maxGens,
       int maxGensWithoutImprovement, double wheelBias, int mutationType, int crossoverType, int threads, int seed, int maxTime)
    : instance(instance), n(n), p(p), pe(pe), pm(pm), rhoe(rhoe), maxGens(maxGens), currP(p),
      maxGensWithoutImprovement(maxGensWithoutImprovement), wheelBias(wheelBias), mutationType(mutationType),
      crossoverType(crossoverType), seed(seed), rng(seed), ztn(0, n - 1), coinFlip(0, 1), maxTime(maxTime)
{
    this->currP = this->createInitialPopulation();
}

void GA::run() {
    this->currentGen = 0, 
    this->gensWithoutImprovement = 0;
    auto startTime = chrono::steady_clock::now();

    while(currentGen++ < this->maxGens && gensWithoutImprovement++ < this->maxGensWithoutImprovement) {
        auto currentTime = chrono::steady_clock::now();
        this->elapsedMinutes = chrono::duration_cast<chrono::minutes>(currentTime - startTime).count();
        if (this->elapsedMinutes >= this->maxTime)
            break;
        
        #ifdef _OPENMP
        #pragma omp parallel for num_threads(this->threads)
        #endif
        for(size_t i = 0 ; i < this->p ; i++)
            this->currP[i].fitness = this->instance.fitness(this->currP[i]);

        this->currP.sortByFitness();
        if(!this->convergenceLog.size() || this->currP[0].fitness < this->convergenceLog.back().bestFitness) {
            gensWithoutImprovement = 0;
            this->convergenceLog.push_back({
                currentGen, this->currP[0].fitness, this->currP[0].origin, std::chrono::duration<double>(currentTime - startTime).count()
            });
        }

        Population nextP = Population(this->p);
        this->reproduction(this->currP, nextP);
        this->currP = nextP;
    }
}

void GA::reproduction(Population& currP, Population& nextP) {
    size_t eliteCount = (size_t)(this->pe * this->p);
    size_t mutantsCount = (size_t)(this->pm * this->p);

    /* Copying elite individuals to next generation */
    #ifdef _OPENMP
    #pragma omp parallel for num_threads(this->threads)
    #endif
    for(size_t i = 0 ; i < eliteCount; i++) {
        nextP[i] = currP[i];
    }

    vector<double> biasedFitness(this->p);
    double totalBiasedFitness = 0.0;

    for (size_t i = 0; i < this->p; ++i) {
        biasedFitness[i] = pow(1.0 / currP[i].fitness, this->wheelBias);
        totalBiasedFitness += biasedFitness[i];
    }
    uniform_real_distribution<double> dist(0.0, totalBiasedFitness);

    /* Generating mutant individuals to next generation */
    #ifdef _OPENMP
    #pragma omp parallel for num_threads(this->threads)
    #endif
    for(size_t i = eliteCount ; i < eliteCount + mutantsCount ; i++) {
        int idx = this->biasedWheelSelection(currP, biasedFitness, totalBiasedFitness, dist);
        Chromosome mutant = Chromosome(currP[i]);
        mutant.origin = Origin::MUTATION;
        switch(this->mutationType) {
            case 1:
                this->swapMutation(mutant);
                break;
            case 2:
                this->twoOptMutation(mutant);
                break;
            case 3:
                this->reinsertionMutation(mutant);
                break;
        }
        nextP[i] = mutant;
    }

    /* Generating crossover individuals to next generation */
    #ifdef _OPENMP
    #pragma omp parallel for num_threads(this->threads)
    #endif
    for(size_t i = eliteCount + mutantsCount; i < this->p; i += 2) {
        int c1 = this->biasedWheelSelection(currP, biasedFitness, totalBiasedFitness, dist);
        int c2 = this->biasedWheelSelection(currP, biasedFitness, totalBiasedFitness, dist);
        std::pair<Chromosome, Chromosome> offspring;
        switch(this->crossoverType) {
            case 1:
                offspring = this->cyclicCrossover(currP[c1], currP[c2]);
                break;
            case 2:
                offspring = this->orderCrossover(currP[c1], currP[c2]);
                break;
            case 3:
                offspring = this->coinFlip(this->rng) ? this->cyclicCrossover(currP[c1], currP[c2]) : this->orderCrossover(currP[c1], currP[c2]);
        }
        nextP[i] = std::move(offspring.first);
        if (i + 1 < this->p) {
            nextP[i + 1] = std::move(offspring.second);
        }
    }
}

int GA::biasedWheelSelection(Population& p, std::vector<double>& biasedFitness, double& totalBiasedFitness, std::uniform_real_distribution<double>& dist) {
    double r = dist(rng);
    double accum = 0.0;
    for (size_t i = 0; i < this->p; ++i) {
        accum += biasedFitness[i];
        if (accum >= r) {
            return i;
        }
    }
    return this->n - 1;
}

void GA::swapMutation(Chromosome& c) {
    size_t i = this->ztn(this->rng);
    size_t j = this->ztn(this->rng);
    while (j == i)
        j = this->ztn(this->rng);

    std::swap(c.permutation[i], c.permutation[j]);
}

void GA::twoOptMutation(Chromosome& c) {
    size_t i = this->ztn(this->rng);
    size_t j = this->ztn(this->rng);
    while(i == j)
        j = this->ztn(this->rng);
    if (i > j) 
        std::swap(i, j);

    std::reverse(c.permutation.begin() + i, c.permutation.begin() + j + 1);
}

void GA::reinsertionMutation(Chromosome& c) {
    size_t from = this->ztn(this->rng);
    size_t to = this->ztn(this->rng);
    while (to == from) {
        to = this->ztn(this->rng);
    }

    int val = c.permutation[from];
    c.permutation.erase(c.permutation.begin() + from);
    c.permutation.insert(c.permutation.begin() + to, val);
}

pair<Chromosome, Chromosome> GA::cyclicCrossover(Chromosome& c1, Chromosome& c2) {
    Chromosome offspring1(this->n, -1, Origin::CYCLIC_CROSSOVER);
    Chromosome offspring2(this->n, -1, Origin::CYCLIC_CROSSOVER);
    vector<bool> visited(this->n, false);

    unordered_map<int, size_t> c1IndexValueMap;
    for (size_t i = 0; i < this->n; ++i) {
        c1IndexValueMap[c1[i]] = i;
    }

    size_t idx = this->ztn(this->rng);
    while (!visited[idx]) {
        visited[idx] = true;
        offspring1[idx] = c1[idx];
        offspring2[idx] = c2[idx];
        idx = c1IndexValueMap[c2[idx]];
    }

    for (size_t i = 0; i < this->n; ++i) {
        if (!visited[i]) {
            offspring1[i] = c2[i];
            offspring2[i] = c1[i];
        }
    }

    return { offspring1, offspring2 };
}

pair<Chromosome, Chromosome> GA::orderCrossover(Chromosome& c1, Chromosome& c2) {
    Chromosome o1(this->n, -1, Origin::ORDER_CROSSOVER);
    Chromosome o2(this->n, -1, Origin::ORDER_CROSSOVER);

    size_t start = this->ztn(this->rng);
    size_t end = this->ztn(this->rng);

    if (start > end) swap(start, end);

    for (size_t i = start; i <= end; ++i) {
        o1[i] = c1[i];
        o2[i] = c2[i];
    }

    auto fill = [&](Chromosome& offspring, Chromosome& donor) {
        unordered_set<int> used;
        for (size_t i = start; i <= end; ++i) {
            used.insert(offspring[i]);
        }

        size_t pos = (end + 1) % this->n;
        for (size_t i = 0; i < this->n; ++i) {
            int gene = donor[(end + 1 + i) % this->n];
            if (used.find(gene) == used.end()) {
                offspring[pos] = gene;
                used.insert(gene);
                pos = (pos + 1) % this->n;
            }
        }
    };

    fill(o1, c2);
    fill(o2, c1);

    return {o1, o2};
}

Chromosome GA::createRandomChromosome() {
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rng);
    return Chromosome(perm, Origin::RANDOM);
}

Population GA::createInitialPopulation() {
    Population pop = Population(this->p);
    for(unsigned i = 0 ; i < this->p ; i++) {
        pop[i] = this->createRandomChromosome();
    }
    return pop;
}

void GA::calculatePopulationFitness(Population& pop) {
    for (auto& chromo : pop) {
        chromo.fitness = this->instance.fitness(chromo);
    }
}

void GA::TIPJSONOutput(ostream& os) {
    json j;

    const TIPInstance* instPtr = dynamic_cast<const TIPInstance*>(&this->instance);

    j["instance"]["filePath"]     = instPtr->filePath;
    j["instance"]["tools"]        = instPtr->tools;
    j["instance"]["slots"]        = instPtr->slots;
    j["instance"]["emptySpaces"]  = instPtr->emptySpaces;
    j["instance"]["WSACost"]      = instPtr->WSACost;

    j["parameters"]["n"]                           = this->n;
    j["parameters"]["p"]                           = this->p;
    j["parameters"]["pe"]                          = this->pe;
    j["parameters"]["pm"]                          = this->pm;
    j["parameters"]["rhoe"]                        = this->rhoe;
    j["parameters"]["maxGens"]                     = this->maxGens;
    j["parameters"]["maxGensWithoutImprovement"]   = this->maxGensWithoutImprovement;
    j["parameters"]["wheelBias"]                   = this->wheelBias;
    j["parameters"]["mutationType"]                = this->mutationType;
    j["parameters"]["threads"]                     = this->threads;
    j["parameters"]["seed"]                        = this->seed;
    j["parameters"]["maxTime"]                     = this->maxTime;

    j["convergence"] = json::array();
    for (const auto& entry : this->convergenceLog) {
        j["convergence"].push_back({
            {"generation", entry.generation},
            {"fitness", entry.bestFitness},
            {"origin", to_string(entry.origin)},
            {"elapsedSeconds", entry.elapsedSeconds}
        });
    }

    j["top_individuals"] = json::array();
    size_t topCount = min<size_t>(20, this->p);

    for (size_t i = 0; i < topCount; ++i) {
        const Chromosome& c = this->currP[i];
        j["top_individuals"].push_back({
            {"fitness", c.fitness},
            {"origin", to_string(c.origin)},
            {"permutation", c.permutation}
        });
    }

    os << setw(4) << j << endl;
}

void GA::CBPJSONOutput(ostream& os) {
    json j;

    j["parameters"]["n"]                           = this->n;
    j["parameters"]["p"]                           = this->p;
    j["parameters"]["pe"]                          = this->pe;
    j["parameters"]["pm"]                          = this->pm;
    j["parameters"]["rhoe"]                        = this->rhoe;
    j["parameters"]["maxGens"]                     = this->maxGens;
    j["parameters"]["maxGensWithoutImprovement"]   = this->maxGensWithoutImprovement;
    j["parameters"]["wheelBias"]                   = this->wheelBias;
    j["parameters"]["mutationType"]                = this->mutationType;
    j["parameters"]["threads"]                     = this->threads;
    j["parameters"]["seed"]                        = this->seed;
    j["parameters"]["maxTime"]                     = this->maxTime;

    j["convergence"] = json::array();
    for (const auto& entry : this->convergenceLog) {
        j["convergence"].push_back({
            {"generation", entry.generation},
            {"fitness", entry.bestFitness},
            {"origin", to_string(entry.origin)},
            {"elapsedSeconds", entry.elapsedSeconds}
        });
    }

    j["top_individuals"] = json::array();
    size_t topCount = min<size_t>(20, this->p);

    for (size_t i = 0; i < topCount; ++i) {
        const Chromosome& c = this->currP[i];
        j["top_individuals"].push_back({
            {"fitness", c.fitness},
            {"origin", to_string(c.origin)},
            {"permutation", c.permutation}
        });
    }

    os << setw(4) << j << endl;
}