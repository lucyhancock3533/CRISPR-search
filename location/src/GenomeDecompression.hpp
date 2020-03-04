#ifndef CRISPR_SEARCH_LOCATION_GENOMEDECOMPRESSION_HPP
#define CRISPR_SEARCH_LOCATION_GENOMEDECOMPRESSION_HPP

#include "cslocation.hpp"

struct FileNotGoodException : public exception {
    const char *what() const throw() {
        return "Could not load file";
    }
};

namespace crisprsearch::location {
    /**
     * Genome decompression class. Un GZips .fa.gz files and produces a byte array of the .fa file content
     */
    class GenomeDecompression {
    private:
        string genomePath;
    public:
        /**
         * Decompression class constructor
         * @param path Full UNIX path to .fa.gz file
         */
        explicit GenomeDecompression(string path);

        /**
         * Decompress specified .fa.gz file
         * @return Byte array containing raw .fa file content
         */
        unique_ptr<char[]> decompress();
    };
}

#endif
