/// Location DB class tests

#include "gtest/gtest.h"
#include "cslocation.hpp"
#include "LocationDb.hpp"
#include "Region.hpp"
#include "Crispr.hpp"
#include "Genome.hpp"

using namespace crisprsearch::location;

/**
 * Test writing a region to the database
 */
TEST(locDatabase, testRegionWrite) {
    // Open test database
    basic_random_generator<boost::mt19937> uuidGen;
    uuid idRaw = uuidGen();
    string id = boost::uuids::to_string(idRaw);
    LocationDb db = LocationDb("test_data/" + id + ".db");

    Region r = Region("seqTest", "typeTest", 100, 399);
    ASSERT_EQ(0, db.writeRegionRecord(r));
}

/**
 * Test writing a crispr to the database
 */
TEST(locDatabase, testCrisprWrite) {
    // Open test database
    basic_random_generator<boost::mt19937> uuidGen;
    uuid idRaw = uuidGen();
    string id = boost::uuids::to_string(idRaw);
    LocationDb db = LocationDb("test_data/" + id + ".db");

    // Make crispr
    Crispr c = Crispr("assembly", 10, 20, 30);
    Region r1 = Region("seqTest1", "typeTest", 100, 399);
    Region r2 = Region("seqTest2", "typeTest", 100, 399);
    Region r3 = Region("seqTest3", "typeTest", 100, 399);
    c.addRegion(r1);
    c.addRegion(r2);
    c.addRegion(r3);

    ASSERT_EQ(0, db.writeCrisprRecord(c));
}

/**
 * Test writing a genome to the database
 */
TEST(locDatabase, testGenomeWrite) {
    // Open test database
    basic_random_generator<boost::mt19937> uuidGen;
    uuid idRaw = uuidGen();
    string id = boost::uuids::to_string(idRaw);
    LocationDb db = LocationDb("test_data/" + id + ".db");

    // Make genome
    Crispr c = Crispr("assembly", 10, 20, 30);
    Region r1 = Region("seqTest1", "typeTest", 100, 399);
    Region r2 = Region("seqTest2", "typeTest", 100, 399);
    Region r3 = Region("seqTest3", "typeTest", 100, 399);
    c.addRegion(r1);
    c.addRegion(r2);
    c.addRegion(r3);
    Genome g = Genome("name", "genomeSource", "genomeInfo");
    g.addCrispr(c);

    ASSERT_EQ(0, db.writeGenomeRecord(g));
}