#ifndef CRISPR_SEARCH_LOCATION_LOCATIONDB_HPP
#define CRISPR_SEARCH_LOCATION_LOCATIONDB_HPP

#include "cslocation.hpp"
#include "Genome.hpp"
#include "Crispr.hpp"
#include "Region.hpp"

namespace crisprsearch::location {
    /**
     * Exception for SQL failure
     */
    struct SQLException : public exception {
        const char * what () const throw () {
            return "Database exception";
        }
    };

    class LocationDb {
    private:
        sqlite3* dbConnection;
        bool regionExists = false;
        bool crisprExists = false;
        bool genomeExists = false;
        /// SQLite callback function for checking if tables already exist
        static int checkSqlTablesCallback(void *locDbObj, int argc, char **argv, char **columnName);
    public:
        explicit LocationDb(string path);
        ~LocationDb();
        int writeGenomeRecord(Genome genome);
        int writeCrisprRecord(Crispr crispr);
        int writeRegionRecord(Region region);
    };
}

#endif
