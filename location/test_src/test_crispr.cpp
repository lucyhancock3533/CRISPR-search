/// Crispr record class tests

#include "gtest/gtest.h"
#include "cslocation.hpp"
#include "Region.hpp"
#include "Crispr.hpp"

using namespace crisprsearch::location;
using boost::uuids::string_generator;

/**
 * Test creating a crispr from individual components
 */
TEST(locCrispr, testCrisprComponentCreate) {
    Crispr c = Crispr("assembly", 10, 20, 30);

    ASSERT_EQ("assembly", c.getSourceAssembly());
    ASSERT_EQ(10, c.getDrLength());
    ASSERT_EQ(20, c.getSpacerCount());
    ASSERT_EQ(30, c.getEvidenceLevel());

    uuid id;
    ASSERT_NO_THROW(id = string_generator()(c.getId()));
    ASSERT_NE(uuid::version_unknown, id.version());
}

/**
 * Test adding a region to this crispr
 */
TEST(locCrispr, testCrisprRegionAdd) {
    Crispr c = Crispr("assembly", 10, 20, 30);

    Region r1 = Region("seqTest1", "typeTest", 100, 399);
    Region r2 = Region("seqTest2", "typeTest", 100, 399);
    Region r3 = Region("seqTest3", "typeTest", 100, 399);

    c.addRegion(r1);
    c.addRegion(r2);
    c.addRegion(r3);

    ASSERT_EQ(3, (*c.getRegions()).size());
    ASSERT_EQ(r1.getId(), (*c.getRegions())[0].getId());
    ASSERT_EQ(r2.getId(), (*c.getRegions())[1].getId());
    ASSERT_EQ(r3.getId(), (*c.getRegions())[2].getId());
}