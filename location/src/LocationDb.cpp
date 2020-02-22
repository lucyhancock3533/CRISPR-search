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
}