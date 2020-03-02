/// Genome class tests

#include "gtest/gtest.h"
#include "cslocation.hpp"
#include "Genome.hpp"
#include "Crispr.hpp"

using namespace crisprsearch::location;
using boost::uuids::string_generator;

/**
 * Test creating a Genome from individual components
 */
TEST(locGenome, testGenomeComponentCreation) {
    Genome g = Genome("name", "genomeSource", "genomeInfo");

    ASSERT_EQ("name", g.getName());
    ASSERT_EQ("genomeSource", g.getGenomeSource());
    ASSERT_EQ("genomeInfo", g.getGenomeInfo());

    uuid id;
    ASSERT_NO_THROW(id = string_generator()(g.getId()));
    ASSERT_NE(uuid::version_unknown, id.version());
}

/**
 * Test adding a CRISPR to a Genome
 */
TEST(locGenome, testGenomeCrisprAdd) {
    Genome g = Genome("name", "genomeSource", "genomeInfo");

    Crispr c1 = Crispr("assembly", 10, 20, 30);
    Crispr c2 = Crispr("assembly", 10, 20, 30);
    Crispr c3 = Crispr("assembly", 10, 20, 30);

    g.addCrispr(c1);
    g.addCrispr(c2);
    g.addCrispr(c3);

    ASSERT_EQ(3, (*g.getCrispr()).size());
    ASSERT_EQ(c1.getId(), (*g.getCrispr())[0].getId());
    ASSERT_EQ(c2.getId(), (*g.getCrispr())[1].getId());
    ASSERT_EQ(c3.getId(), (*g.getCrispr())[2].getId());
}

/**
 * Test creating a Genome from the CRISPRCasFinder results json
 */
TEST(locGenome, testGenomeResultsJson) {
    Genome g = Genome("name", "genomeSource", "genomeInfo");
    g.parseResultsJson("test_data/result.json");
    ASSERT_EQ(8, g.getCrispr().get()->size());
    ASSERT_EQ(73, (*g.getCrispr().get())[0].getRegions().get()->size());
}