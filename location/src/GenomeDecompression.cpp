#include "cslocation.hpp"
#include "GenomeDecompression.hpp"

namespace crisprsearch::location {
    GenomeDecompression::GenomeDecompression(string path) {
        genomePath = move(path);
    }

    char* GenomeDecompression::decompress() {
        // Decompress file using boost gzip filter
        ifstream toDecompress(genomePath, ios_base::in | ios_base::binary);

        // Check file exists
        if (!toDecompress.good()) {
            throw FileNotGoodException();
        }

        // Do decompression
        filtering_streambuf<input> decompressionStream;
        decompressionStream.push(gzip_decompressor());
        decompressionStream.push(toDecompress);
        stringstream output;
        boost::iostreams::copy(decompressionStream, output);

        toDecompress.close();

        // Copy into output pointer
        char* outputPtr = new char[output.str().length() + 1];
        memcpy(outputPtr, output.str().c_str(), output.str().length());
        outputPtr[output.str().length()] = '\0';
        return outputPtr;
    }
}