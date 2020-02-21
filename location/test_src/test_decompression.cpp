/// .fa.gz Decompression unit tests
#include "gtest/gtest.h"
#include "cslocation.hpp"
#include "GenomeDecompression.hpp"

using crisprsearch::location::GenomeDecompression;

/**
 *
 */
TEST(locDecomp, locDecompSuccess) {
    auto decomp = GenomeDecompression("test_data/locDecompSuccess.fa.gz");
    unique_ptr<char[]> result = decomp.decompress();

    // Load test data for correct decompression
    ifstream cdIn("test_data/locDecompSuccess.fa");
    if(!cdIn.good()) {
        FAIL();
    }
    string correctData;
    correctData.assign(std::istreambuf_iterator<char>(cdIn), std::istreambuf_iterator<char>());
    cdIn.close();

    ASSERT_STREQ(correctData.c_str(), result.get());
}

/**
 *
 */
TEST(locDecomp, locDecompInvalidFile) {
    auto decomp = GenomeDecompression("test_data/locDecompInvalid.fa");
    ASSERT_ANY_THROW(decomp.decompress());
}

/**
 *
 */
TEST(locDecomp, locDecompNoFile) {
    auto decomp = GenomeDecompression("test_data/thisdoesntexist.fa.gz");
    ASSERT_THROW(decomp.decompress(), FileNotGoodException);
}