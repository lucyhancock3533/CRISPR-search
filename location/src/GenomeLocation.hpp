#ifndef CRISPR_SEARCH_LOCATION_GENOMELOCATION_HPP
#define CRISPR_SEARCH_LOCATION_GENOMELOCATION_HPP

#include "cslocation.hpp"
#include "LocationDb.hpp"

namespace crisprsearch::location {
    /**
     * Genome location class, to prepare and run CRISPRCasFinder
     */
    class GenomeLocation {
    private:
        Genome* genome;
        string genomePath;
        LocationDb* dbConnection;
        /**
         * Process genome function. Launches CCF and calls genome results parser.
         */
        void processGenome();
    public:
        /**
         * Build a GenomeLocation class to prepare and run CRISPRCasFinder
         * @param path Full UNIX path to the genome to search
         * @param db LocationDb object pointer, pointer to created and opened database object
         * @param name Name of genome being searched
         * @param info Info link of genome
         * @param source Source of genome to be searched
         */
        explicit GenomeLocation(string path, LocationDb* db, string name, string info, string source);
        /**
         * GenomeLocation destructor, cleans up any pointers used.
         */
        ~GenomeLocation();
        /**
         * Load a genome into processing directory and call processGenome to search for crispr.
         */
        void loadGenome();
    };
}

#endif