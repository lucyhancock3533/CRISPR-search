#include "Genome.hpp"

namespace crisprsearch::location {

    Genome::Genome(string name, string genomeSource, string genomeInfo) {
        crisprs = make_shared<vector<Crispr>>();
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

    }
}