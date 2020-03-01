#include "cslocation.hpp"
#include "GenomeLocation.hpp"

namespace crisprsearch::location {

    GenomeLocation::GenomeLocation(string path, LocationDb* db, string name, string info, string source) {
        fileContent = 0;
        genomePath = path;
        dbConnection = db;
        genome = new Genome(name, source, info);
    }

    GenomeLocation::~GenomeLocation() {
        if(fileContent != 0) {
            delete[] fileContent;
        }
        delete genome;
    }

    void GenomeLocation::loadGenome() {
        string fileExt = genomePath.substr(genomePath.find_last_of('.') + 1);
        cout << fileExt << endl;
    }
}