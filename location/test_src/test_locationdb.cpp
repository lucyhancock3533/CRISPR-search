/// Location DB class tests

#include "gtest/gtest.h"
#include "cslocation.hpp"
#include "LocationDb.hpp"
#include "Region.hpp"
#include "Crispr.hpp"
#include "Genome.hpp"

using namespace crisprsearch::location;

/// Boolean test function, sets data to true if a record is found and called
int boolCallback(void *data, int argc, char **argv, char **columnName) {
    *((bool*)data) = true;
    return 0;
}

/**
 * Test writing a region to the database
 */
TEST(locDatabase, testRegionWrite) {
    // Open test database
    basic_random_generator<boost::mt19937> uuidGen;
    uuid idRaw = uuidGen();
    string id = boost::uuids::to_string(idRaw);
    auto db = new LocationDb("test_data/" + id + ".db");

    // Write region into database
    Region r = Region("seqTest", "typeTest", 100, 399);
    ASSERT_NO_THROW(db->writeRegionRecord(r, "", 0));
    delete db;

    // Check region present in database
    sqlite3* dbConnection;
    string path = "test_data/" + id + ".db";
    string statement = "SELECT * FROM Regions WHERE id = '" + r.getId() + "'";
    bool regionFound = false;
    sqlite3_open(path.c_str(), &dbConnection);
    sqlite3_exec(dbConnection, statement.c_str(), boolCallback, &regionFound, NULL);
    ASSERT_TRUE(regionFound);
    sqlite3_close(dbConnection);
}

/**
 * Test writing a crispr to the database
 */
TEST(locDatabase, testCrisprWrite) {
    // Open test database
    basic_random_generator<boost::mt19937> uuidGen;
    uuid idRaw = uuidGen();
    string id = boost::uuids::to_string(idRaw);
    auto db = new LocationDb("test_data/" + id + ".db");

    // Make crispr
    Crispr c = Crispr("assembly", 10, 20, 30);
    Region r1 = Region("seqTest1", "typeTest", 100, 399);
    Region r2 = Region("seqTest2", "typeTest", 100, 399);
    Region r3 = Region("seqTest3", "typeTest", 100, 399);
    c.addRegion(r1);
    c.addRegion(r2);
    c.addRegion(r3);

    // Write crispr to database
    ASSERT_NO_THROW(db->writeCrisprRecord(c, ""));
    delete db;

    sqlite3* dbConnection;
    string path = "test_data/" + id + ".db";
    // Check crispr in database
    string statement = "SELECT * FROM CRISPR WHERE id = '" + c.getId() + "'";
    bool regionFound = false;
    sqlite3_open(path.c_str(), &dbConnection);
    sqlite3_exec(dbConnection, statement.c_str(), boolCallback, &regionFound, NULL);
    ASSERT_TRUE(regionFound);
    // Check regions in database
    statement = "SELECT * FROM Regions WHERE crisprId = '" + c.getId() + "'";
    regionFound = false;
    sqlite3_exec(dbConnection, statement.c_str(), boolCallback, &regionFound, NULL);
    ASSERT_TRUE(regionFound);
    sqlite3_close(dbConnection);
}

/**
 * Test writing a genome to the database
 */
TEST(locDatabase, testGenomeWrite) {
    // Open test database
    basic_random_generator<boost::mt19937> uuidGen;
    uuid idRaw = uuidGen();
    string id = boost::uuids::to_string(idRaw);
    auto db = new LocationDb("test_data/" + id + ".db");

    // Make genome
    Genome g = Genome("name", "genomeSource", "genomeInfo");
    Crispr c = Crispr("assembly", 10, 20, 30);
    Region r1 = Region("seqTest1", "typeTest", 100, 399);
    Region r2 = Region("seqTest2", "typeTest", 100, 399);
    Region r3 = Region("seqTest3", "typeTest", 100, 399);
    c.addRegion(r1);
    c.addRegion(r2);
    c.addRegion(r3);
    g.addCrispr(c);

    // Write genome to database
    ASSERT_NO_THROW(db->writeGenomeRecord(g));
    delete db;

    sqlite3* dbConnection;
    string path = "test_data/" + id + ".db";
    // Check genome in database
    string statement = "SELECT * FROM Genomes WHERE id = '" + g.getId() + "'";
    bool regionFound = false;
    sqlite3_open(path.c_str(), &dbConnection);
    sqlite3_exec(dbConnection, statement.c_str(), boolCallback, &regionFound, NULL);
    ASSERT_TRUE(regionFound);
    // Check crispr in database
    statement = "SELECT * FROM CRISPR WHERE genomeId = '" + g.getId() + "'";
    regionFound = false;
    sqlite3_exec(dbConnection, statement.c_str(), boolCallback, &regionFound, NULL);
    ASSERT_TRUE(regionFound);
    // Check regions in database
    statement = "SELECT * FROM Regions WHERE crisprId = '" + c.getId() + "'";
    regionFound = false;
    sqlite3_exec(dbConnection, statement.c_str(), boolCallback, &regionFound, NULL);
    ASSERT_TRUE(regionFound);
    sqlite3_close(dbConnection);
}