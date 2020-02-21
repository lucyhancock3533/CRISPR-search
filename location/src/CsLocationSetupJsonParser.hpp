#ifndef CRISPR_SEARCH_LOCATION_CSLOCATIONSETUPJSONPARSER_HPP
#define CRISPR_SEARCH_LOCATION_CSLOCATIONSETUPJSONPARSER_HPP

#include "cslocation.hpp"

namespace crisprsearch::location {
    /**
     * Structure to store genome file information
     */
    struct CsLocationFile {
        string fileName;
        string genomeName;
        string genomeInfo;
        string genomeSource;
    };

    /**
     * Class to parse input JSON for setip
     */
    class CsLocationSetupJsonParser {
    private:
        vector<CsLocationFile> files;
    public:
        /**
         * Create new SetupJson object
         * @param path Full UNIX path to setup json
         */
        explicit CsLocationSetupJsonParser(string path);
        /**
         * Parse the JSON within the file specified in the constructor and load into class
         */
        void parseJson();
        /**
         * Get a list of the genomes contained in the setup file
         * @return Vector of CsLocationFile structs containing input genome information
         */
        vector<CsLocationFile> getFiles();
    };
}

#endif