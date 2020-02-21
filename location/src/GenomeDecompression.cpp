#include "cslocation.hpp"
#include "GenomeDecompression.hpp"

namespace crisprsearch::location {
    GenomeDecompression::GenomeDecompression(string path) {
        genomePath = std::move(path);
    }

    unique_ptr<char[]> GenomeDecompression::decompress() {
        return nullptr;
    }
}