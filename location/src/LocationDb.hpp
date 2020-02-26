#ifndef CRISPR_SEARCH_LOCATION_LOCATIONDB_HPP
#define CRISPR_SEARCH_LOCATION_LOCATIONDB_HPP

#include "cslocation.hpp"
#include "Genome.hpp"
#include "Crispr.hpp"
#include "Region.hpp"

namespace crisprsearch::location {
    class LocationDb {
    private:
        sqlite3* dbConnection;
    public:
        explicit LocationDb(string path);
        ~LocationDb();
        int writeGenomeRecord(Genome genome);
        int writeCrisprRecord(Crispr crispr);
        int writeRegionRecord(Region region);
    };
}

#endif
