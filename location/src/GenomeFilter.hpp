#ifndef CRISPR_SEARCH_LOCATION_GENOMEFILTER_HPP
#define CRISPR_SEARCH_LOCATION_GENOMEFILTER_HPP

#include "cslocation.hpp"

namespace crisprsearch::location {
    /**
     * Genome filter class to filter special characters from FASTA description lines
     */
    class GenomeFilter {
    private:
        char* fileData;
    public:
        /**
         * Create new Genome filter from existing data pointer
         * @param data Pointer to FASTA file in memory
         */
        explicit GenomeFilter(char* data);
        /**
         * Create new Genome filter from FASTA file
         * @param filePath Full UNIX path to FASTA file
         */
        explicit GenomeFilter(string filePath);
        /**
         * Destructor, delete file data array
         */
        ~GenomeFilter();
        /**
         * Filter genome to remove special characters from FASTA descriptions
         */
        void filter();
        /**
         * Save the filtered genome to the specified path
         * @param outputPath Full UNIX path to genome output file
         */
        void save(string outputPath);
    };
}

#endif
