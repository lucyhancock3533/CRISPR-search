/// .fa.gz Decompression unit tests
#include "gtest/gtest.h"
#include "cslocation.hpp"
#include "GenomeDecompression.hpp"

using namespace crisprsearch::location;

/**
 * Tests a successful GZip decompression
 */
TEST(locDecomp, testSuccess) {
    auto decomp = GenomeDecompression("test_data/locDecompSuccess.fa.gz");
    unique_ptr<char[]> result = decomp.decompress();

    // Load test data for correct decompression
    ifstream cdIn("test_data/locDecompSuccess.fa");
    if(!cdIn.good()) {
        FAIL();
    }
    string correctData;
    correctData.assign(istreambuf_iterator<char>(cdIn), istreambuf_iterator<char>());
    cdIn.close();

    ASSERT_STREQ(correctData.c_str(), result.get());
}

/**
 * Tests trying to ungzip a non-gzip file
 */
TEST(locDecomp, testInvalidFile) {
    auto decomp = GenomeDecompression("test_data/locDecompInvalid.fa");
    ASSERT_ANY_THROW(decomp.decompress());
}

/**
 * Tests trying to ungzip a non existant file
 */
TEST(locDecomp, testFileDoesntExist) {
    auto decomp = GenomeDecompression("test_data/thisdoesntexist.fa.gz");
    ASSERT_THROW(decomp.decompress(), FileNotGoodException);
}