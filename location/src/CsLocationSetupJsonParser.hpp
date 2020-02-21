#ifndef CRISPR_SEARCH_LOCATION_CSLOCATIONSETUPJSONPARSER_HPP
#define CRISPR_SEARCH_LOCATION_CSLOCATIONSETUPJSONPARSER_HPP

#include "cslocation.hpp"

namespace crisprsearch::location {
    struct CsLocationFile {
        string fileName;
        string genomeName;
        string genomeInfo;
        string genomeSource;
    };

    class CsLocationSetupJsonParser {
    private:
        vector<CsLocationFile> files;
    public:
        explicit CsLocationSetupJsonParser(string path);
        void parseJson();
        vector<CsLocationFile> getFiles();
    };
}

#endif