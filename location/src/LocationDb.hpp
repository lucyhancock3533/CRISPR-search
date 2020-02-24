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
        void writeGenomeRecord(Genome genome);
        void writeCrisprRecord(Crispr crispr);
        void writeRegionRecord(Region region);
    };
}

#endif
