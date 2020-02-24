#include "Genome.hpp"

#include <utility>

namespace crisprsearch::location {

    Genome::Genome(string name, string genomeSource, string genomeInfo) {
        crisprs = make_shared<vector<Crispr>>();

        this->name = move(name);
        this->genomeInfo = move(genomeInfo);
        this->genomeSource = move(genomeSource);

        // Generate random UUID and convert to string for ID
        basic_random_generator<boost::mt19937> uuidGen;
        uuid idRaw = uuidGen();
        this->id = boost::uuids::to_string(idRaw);
    }

    string Genome::getId() {
        return id;
    }

    string Genome::getName() {
        return name;
    }

    string Genome::getGenomeSource() {
        return genomeSource;
    }

    string Genome::getGenomeInfo() {
        return genomeInfo;
    }

    shared_ptr<vector<Crispr>> Genome::getCrispr() {
        return crisprs;
    }

    void Genome::addCrispr(Crispr crispr) {
        crisprs->push_back(move(crispr));
    }
}