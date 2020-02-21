#ifndef CRISPR_SEARCH_LOCATION_GENOMEDECOMPRESSION_HPP
#define CRISPR_SEARCH_LOCATION_GENOMEDECOMPRESSION_HPP

#include "cslocation.hpp"

namespace crisprsearch::location {
    class GenomeDecompression {
    private:
        string genomePath;
    public:
        explicit GenomeDecompression(string);
        shared_ptr<char> decompress();
    };
}

#endif
