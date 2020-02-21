/// Setup JSON parser tests
#include "gtest/gtest.h"
#include "cslocation.hpp"
#include "CsLocationSetupJsonParser.hpp"

using namespace crisprsearch::location;

TEST(locSetupJson, testParse) {
    const string json = "{ccfPath:\"/this/is/a/path\", "
                        "genomes:[{name:\"A\", info:\"A\", source:\"A\", file:\"A\"}, "
                        "{name:\"B\", info:\"B\", source:\"B\", file:\"B\"}]}";
    CRISPR_CAS_FINDER_PATH = "";

    auto parser = CsLocationSetupJsonParser(json);
    parser.parseJson();

    ASSERT_EQ("/this/is/a/path", CRISPR_CAS_FINDER_PATH);
    ASSERT_EQ(2, parser.getFiles().size());
    ASSERT_EQ("A", parser.getFiles()[0].genomeName);
    ASSERT_EQ("B", parser.getFiles()[1].genomeSource);
}

TEST(locSetupJson, testNoGenomes) {
    const string json = "{ccfPath:\"/this/is/a/path2\", genomes:[]}";
    CRISPR_CAS_FINDER_PATH = "";

    auto parser = CsLocationSetupJsonParser(json);
    parser.parseJson();

    ASSERT_EQ("/this/is/a/path2", CRISPR_CAS_FINDER_PATH);
    ASSERT_EQ(0, parser.getFiles().size());
}

TEST(locSetupJson, testMissingCCFPath) {
    const string json = "{genomes:[{name:\"A\", info:\"A\", source:\"A\", file:\"A\"}, "
                        "{name:\"B\", info:\"B\", source:\"B\", file:\"B\"}]}";
    CRISPR_CAS_FINDER_PATH = "";

    auto parser = CsLocationSetupJsonParser(json);
    ASSERT_ANY_THROW(parser.parseJson());
}

TEST(locSetupJson, testInvalidJSON) {
    const string json = "This is not json";
    CRISPR_CAS_FINDER_PATH = "";

    auto parser = CsLocationSetupJsonParser(json);
    ASSERT_ANY_THROW(parser.parseJson());
}