#include "cslocation.hpp"
#include "LocationDb.hpp"

namespace crisprsearch::location {
    LocationDb::LocationDb(string path) {
        // Open database
        int errorCode = sqlite3_open(path.c_str(), &dbConnection);
        if (errorCode) {
            throw SQLException();
        }

        // Check if tables exist
        char *errMsg = 0;
        errorCode = sqlite3_exec(dbConnection, SQLITE_GET_TABLES, LocationDb::checkSqlTablesCallback, this, &errMsg);
        if (errorCode) {
            throw SQLException();
        }

        // Create missing tables
        if (!genomeExists) {
            errorCode = sqlite3_exec(dbConnection, SQLITE_CREATE_GENOME_TABLE, nullptr, nullptr, &errMsg);
            if (errorCode) {
                throw SQLException();
            }
        }
        if (!crisprExists) {
            errorCode = sqlite3_exec(dbConnection, SQLITE_CREATE_CRISPR_TABLE, nullptr, nullptr, &errMsg);
            if(errorCode) {
                throw SQLException();
            }
        }
        if (!regionExists) {
            errorCode = sqlite3_exec(dbConnection, SQLITE_CREATE_REGION_TABLE, nullptr, nullptr, &errMsg);
            if (errorCode) {
                throw SQLException();
            }
        }
    }

    LocationDb::~LocationDb() {
        // Safely close database
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

    int LocationDb::checkSqlTablesCallback(void *locDbObj, int argc, char **argv, char **columnName) {
        // Get name of table in record
        string tblName(argv[2]);
        // Set appropriate bool
        if(tblName == "Genomes") {
            ((LocationDb*)locDbObj)->genomeExists = true;
        }
        if(tblName == "CRISPR") {
            ((LocationDb*)locDbObj)->crisprExists = true;
        }
        if(tblName == "Regions") {
            ((LocationDb*)locDbObj)->regionExists = true;
        }
        return 0;
    }
}