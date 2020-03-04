/// Region class tests

#include "gtest/gtest.h"
#include "cslocation.hpp"
#include "Region.hpp"

using namespace crisprsearch::location;
using boost::uuids::string_generator;

/**
 * Test creating new Region from individual components
 */
TEST(locRegion, testRegionComponentCreate) {
    Region r = Region("seqTest", "typeTest", 100, 399);

    ASSERT_EQ("seqTest", r.getSequence());
    ASSERT_EQ("typeTest", r.getType());
    ASSERT_EQ(100, r.getStartPos());
    ASSERT_EQ(399, r.getEndPos());

    uuid id;
    ASSERT_NO_THROW(id = string_generator()(r.getId()));
    ASSERT_NE(uuid::version_unknown, id.version());
}