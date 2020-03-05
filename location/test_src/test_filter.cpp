/// Test genome symbol filtering
#include "gtest/gtest.h"
#include "cslocation.hpp"
#include "GenomeDecompression.hpp"
#include "GenomeFilter.hpp"

using namespace crisprsearch::location;

TEST(locFilter, testNoFilterRequired) {
    GenomeDecompression dec = GenomeDecompression("test_data/nofilter.fa.gz");
    char* file = dec.decompress();

    char* fileCopy = new char[strlen(file) + 1];
    fileCopy[strlen(file)] = '\0';
    memcpy(fileCopy, file, strlen(file));

    ASSERT_STREQ(file, fileCopy);

    basic_random_generator<boost::mt19937> uuidGen;
    uuid idRaw = uuidGen();
    string id = boost::uuids::to_string(idRaw);
    GenomeFilter filt = GenomeFilter(file);
    filt.filter();
    filt.save("test_data/" + id + ".tmp");

    ifstream filei("test_data/" + id + ".tmp");
    if (!filei.good()) {
        FAIL();
    }
    string data;
    data.assign(istreambuf_iterator<char>(filei), istreambuf_iterator<char>());
    filei.close();

    int res = strcmp(data.c_str(), fileCopy);
    delete[] fileCopy;
    ASSERT_EQ(0, res);
}

TEST(locFilter, testFilterRequired) {
    GenomeFilter f = GenomeFilter(string("test_data/filter.fasta"));
    f.filter();
    basic_random_generator<boost::mt19937> uuidGen;
    uuid idRaw = uuidGen();
    string id = boost::uuids::to_string(idRaw);
    f.save("test_data/" + id + ".tmp");

    ifstream filei("test_data/" + id + ".tmp");
    if (!filei.good()) {
        FAIL();
    }
    string data;
    data.assign(istreambuf_iterator<char>(filei), istreambuf_iterator<char>());
    filei.close();

    ifstream filej("test_data/filter.post.fasta");
    if (!filej.good()) {
        FAIL();
    }
    string dataj;
    dataj.assign(istreambuf_iterator<char>(filej), istreambuf_iterator<char>());
    filej.close();

    int r = data == dataj;
    ASSERT_NE(0, r);
}