#include "cslocation.hpp"
#include "GenomeDecompression.hpp"

namespace crisprsearch::location {
    GenomeDecompression::GenomeDecompression(string path) {
        genomePath = move(path);
    }

    unique_ptr<char[]> GenomeDecompression::decompress() {
        // Decompress file using boost gzip filter
        ifstream toDecompress(genomePath, ios_base::in | ios_base::binary);

        // Check file exists
        if(!toDecompress.good()) {
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
        unique_ptr<char[]> outputPtr = make_unique<char[]>(output.str().length() + 1);
        memcpy(outputPtr.get(), output.str().c_str(), output.str().length());
        outputPtr.get()[output.str().length()] = '\0';
        return outputPtr;
    }
}