#ifndef CRISPR_SEARCH_LOCATION_GENOMELOCATION_HPP
#define CRISPR_SEARCH_LOCATION_GENOMELOCATION_HPP

#include "cslocation.hpp"
#include "LocationDb.hpp"

namespace crisprsearch::location {
    class GenomeLocation {
    private:
        Genome* genome;
        string genomePath;
        LocationDb* dbConnection;
        char* fileContent;
    public:
        explicit GenomeLocation(string path, LocationDb* db, string name, string info, string source);
        ~GenomeLocation();
        void loadGenome();
    };
}

#endif