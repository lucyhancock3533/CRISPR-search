#include "cslocation.hpp"
#include "GenomeDecompression.hpp"

#include <utility>

namespace crisprsearch::location {
    GenomeDecompression::GenomeDecompression(string path) {
        genomePath = std::move(path);
    }

    shared_ptr<char> GenomeDecompression::decompress() {
        return nullptr;
    }
}