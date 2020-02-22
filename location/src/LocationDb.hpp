#ifndef CRISPR_SEARCH_LOCATION_LOCATIONDB_HPP
#define CRISPR_SEARCH_LOCATION_LOCATIONDB_HPP

#include "cslocation.hpp"

namespace crisprsearch::location {
    class LocationDb {
    private:
        sqlite3* dbConnection;
    public:
        explicit LocationDb(string path);
        ~LocationDb();
        //void writeGenomeRecord(Genome);
        //void writeCrisprRecord(Crispr);
        //void writeRecordRecord(Record);
    };
}

#endif
