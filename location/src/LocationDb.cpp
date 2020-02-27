#include "cslocation.hpp"
#include "LocationDb.hpp"

namespace crisprsearch::location {
    LocationDb::LocationDb(string path) {
        // Open database
        int errorCode = sqlite3_open(path.c_str(), &dbConnection);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }

        // Check if tables exist
        char *errMsg = 0;
        errorCode = sqlite3_exec(dbConnection, SQLITE_GET_TABLES, LocationDb::checkSqlTablesCallback, this, &errMsg);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }

        // Create missing tables
        if (!genomeExists) {
            errorCode = sqlite3_exec(dbConnection, SQLITE_CREATE_GENOME_TABLE, nullptr, nullptr, &errMsg);
            if (errorCode) {
                cout << sqlite3_errmsg(this->dbConnection) << endl;
                throw SQLException();
            }
        }
        if (!crisprExists) {
            errorCode = sqlite3_exec(dbConnection, SQLITE_CREATE_CRISPR_TABLE, nullptr, nullptr, &errMsg);
            if(errorCode) {
                cout << sqlite3_errmsg(this->dbConnection) << endl;
                throw SQLException();
            }
        }
        if (!regionExists) {
            errorCode = sqlite3_exec(dbConnection, SQLITE_CREATE_REGION_TABLE, nullptr, nullptr, &errMsg);
            if (errorCode) {
                cout << sqlite3_errmsg(this->dbConnection) << endl;
                throw SQLException();
            }
        }
    }

    LocationDb::~LocationDb() {
        // Safely close database
        sqlite3_close(dbConnection);
    }

    void LocationDb::writeGenomeRecord(Genome genome) {
        throw SQLException();
    }

    void LocationDb::writeRegionRecord(Region region, string crisprId, int regionNo) {
        // Prepare SQL statement for insertion
        sqlite3_stmt* stmt;
        int errorCode = sqlite3_prepare_v2(this->dbConnection, SQLITE_INSERT_REGION, -1, &stmt, nullptr);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }

        // Bind parameters
        string id = region.getId();
        errorCode = sqlite3_bind_text(stmt, 1, id.c_str(), -1, NULL);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_bind_text(stmt, 2, crisprId.c_str(), -1, NULL);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        string sequence = region.getSequence();
        errorCode = sqlite3_bind_text(stmt, 3, sequence.c_str(), -1, NULL);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        string type = region.getType();
        errorCode = sqlite3_bind_text(stmt, 4, type.c_str(), -1, NULL);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_bind_int(stmt, 5, regionNo);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_bind_int(stmt, 6, region.getStartPos());
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_bind_int(stmt, 7, region.getEndPos());
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }

        // Execute and finalise statement
        errorCode = sqlite3_step(stmt);
        if (errorCode != SQLITE_DONE) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_finalize(stmt);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
    }

    void LocationDb::writeCrisprRecord(Crispr crispr, string genomeId) {
        // Prepare SQL statement for insertion
        sqlite3_stmt* stmt;
        int errorCode = sqlite3_prepare_v2(this->dbConnection, SQLITE_INSERT_CRISPR, -1, &stmt, nullptr);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }

        // Bind parameters
        string id = crispr.getId();
        errorCode = sqlite3_bind_text(stmt, 1, id.c_str(), -1, NULL);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_bind_text(stmt, 2, genomeId.c_str(), -1, NULL);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        string sourceSequence = crispr.getSourceAssembly();
        errorCode = sqlite3_bind_text(stmt, 3, sourceSequence.c_str(), -1, NULL);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_bind_int(stmt, 4, crispr.getDrLength());
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_bind_int(stmt, 5, crispr.getSpacerCount());
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_bind_int(stmt, 6, crispr.getEvidenceLevel());
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_bind_int(stmt, 7, (*crispr.getRegions()).size());
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }

        // Execute and finalise statement
        errorCode = sqlite3_step(stmt);
        if (errorCode != SQLITE_DONE) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }
        errorCode = sqlite3_finalize(stmt);
        if (errorCode) {
            cout << sqlite3_errmsg(this->dbConnection) << endl;
            throw SQLException();
        }

        // Insert associated regions
        shared_ptr<vector<Region>> regions = crispr.getRegions();
        for(int pos = 0; pos < (*regions).size(); pos++) {
            writeRegionRecord((*regions)[pos], crispr.getId(), pos);
        }
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