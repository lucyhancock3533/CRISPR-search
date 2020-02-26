#include "cslocation.hpp"
#include "LocationDb.hpp"

namespace crisprsearch::location {
    LocationDb::LocationDb(string path) {
        int errorCode = sqlite3_open(path.c_str(), &dbConnection);
        // TODO: Error handling
    }

    LocationDb::~LocationDb() {
        sqlite3_close(dbConnection);
    }

    int LocationDb::writeGenomeRecord(Genome genome) {
        return 1;
    }

    int LocationDb::writeRegionRecord(Region region) {
        return 1;
    }

    int LocationDb::writeCrisprRecord(Crispr crispr) {
        return 1;
    }
}