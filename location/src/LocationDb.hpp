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
        const char *what() const throw() {
            return "Database exception";
        }
    };

    /**
     * LocationDB class for writing records into SQLite database
     */
    class LocationDb {
    private:
        sqlite3 *dbConnection;
        bool regionExists = false;
        bool crisprExists = false;
        bool genomeExists = false;

        /// SQLite callback function for checking if tables already exist
        static int checkSqlTablesCallback(void *locDbObj, int argc, char **argv, char **columnName);

    public:
        /**
         * Constructor to create and initialise database
         * @param path Full UNIX path to SQLite database file, does not have to exist, it will be created
         */
        explicit LocationDb(string path);

        /**
         * Database destructor, safely closes database
         */
        ~LocationDb();

        /**
         * Write a genome record into the database
         * @param genome Genome object for record
         */
        void writeGenomeRecord(Genome genome);

        /**
         * Write a crispr record into the database
         * @param crispr Crispr object for record
         * @param genomeId ID for associated genome
         */
        void writeCrisprRecord(Crispr crispr, string genomeId);

        /**
         * Write a region record into the database
         * @param region Region object for record
         * @param crisprId ID for associated crispr
         * @param regionNo Position of region in crispr array
         */
        void writeRegionRecord(Region region, string crisprId, int regionNo);
    };
}

#endif
