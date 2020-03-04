#ifndef CRISPR_SEARCH_LOCATION_GENOME_HPP
#define CRISPR_SEARCH_LOCATION_GENOME_HPP

#include "cslocation.hpp"
#include "Crispr.hpp"

namespace crisprsearch::location {
    /**
     * Genome storage class
     */
    class Genome {
    private:
        string id;
        string name;
        string genomeSource;
        string genomeInfo;
        shared_ptr<vector<Crispr>> crisprs;
    public:
        /**
         * Component constructor for creating a new Genome object
         * @param name Name of genome
         * @param genomeSource Source of genome
         * @param genomeInfo Information about genome
         */
        explicit Genome(string name, string genomeSource, string genomeInfo);

        /**
         * Get the auto-generated ID of this Genome
         * @return UUID string
         */
        string getId();

        /**
         * Get the name of this Genome
         * @return Genome name string
         */
        string getName();

        /**
         * Get the source of this Genome
         * @return Genome source string
         */
        string getGenomeSource();

        /**
         * Get the information about this Genome
         * @return Genome info string
         */
        string getGenomeInfo();

        /**
         * Get the crisprs found within this genome
         * @return Pointer to vector of genomes
         */
        shared_ptr<vector<Crispr>> getCrispr();

        /**
         * Add a crispr array to thie genome
         * @param crispr Crispr to add to Genome
         */
        void addCrispr(Crispr crispr);

        /**
         * Parse the CRISPRCasFinder results and build the genome
         * @param path Full UNIX path to the CRISPRCasFinder results json
         */
        void parseResultsJson(string path);
    };
}

#endif
