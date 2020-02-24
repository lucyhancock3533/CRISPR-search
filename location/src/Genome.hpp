#ifndef CRISPR_SEARCH_LOCATION_GENOME_HPP
#define CRISPR_SEARCH_LOCATION_GENOME_HPP

#include "cslocation.hpp"
#include "Crispr.hpp"

namespace crisprsearch::location {
    class Genome {
    private:
        string id;
        string name;
        string genomeSource;
        string genomeInfo;
        shared_ptr<vector<Crispr>> crisprs;
    public:
        explicit Genome(string name, string genomeSource, string genomeInfo);
        string getId();
        string getName();
        string getGenomeSource();
        string getGenomeInfo();
        shared_ptr<vector<Crispr>> getCrispr();
        void addCrispr(Crispr crispr);
    };
}

#endif
