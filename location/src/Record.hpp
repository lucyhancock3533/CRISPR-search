#ifndef CRISPR_SEARCH_LOCATION_RECORD_HPP
#define CRISPR_SEARCH_LOCATION_RECORD_HPP

#include "cslocation.hpp"

namespace crisprsearch::location {
    class Record {
    private:
        string id;
        string sequence;
        string type;
        int startPos;
        int endPos;
    public:
        explicit Record(string sequence, string type, int startPos, int endPos);
        string getId();
        string getSequence();
        string getType();
        int getStartPos();
        int getEndPos();
    };
}

#endif
