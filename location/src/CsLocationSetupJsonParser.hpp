#ifndef CRISPR_SEARCH_LOCATION_CSLOCATIONSETUPJSONPARSER_HPP
#define CRISPR_SEARCH_LOCATION_CSLOCATIONSETUPJSONPARSER_HPP

#include "cslocation.hpp"

namespace crisprsearch::location {
    struct InvalidJSONException : public exception {
        const char * what () const throw () {
            return "Setup JSON was invalid or missing required parameters.";
        }
    };

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
        string crisprDbpath;
    public:
        /**
         * Create new SetupJson object
         * @param json Full JSON setup string
         */
        explicit CsLocationSetupJsonParser(string json);
        /**
         * Parse the JSON within the file specified in the constructor and load into class
         */
        void parseJson();
        /**
         * Get a list of the genomes contained in the setup file
         * @return Vector of CsLocationFile structs containing input genome information
         */
        vector<CsLocationFile> getFiles();
        /**
         * Get a string containing the path to the CRISPR SQLite DB
         * @return Full UNIX path to CRISPR db file
         */
        string getCrisprDbPath();
    };
}

#endif