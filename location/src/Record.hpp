#ifndef CRISPR_SEARCH_LOCATION_RECORD_HPP
#define CRISPR_SEARCH_LOCATION_RECORD_HPP

#include "cslocation.hpp"

namespace crisprsearch::location {
    /**
     * Spacer record storage class
     */
    class Record {
    private:
        string id;
        string sequence;
        string type;
        int startPos;
        int endPos;
    public:
        /**
         * Create a new spacer record from values
         * @param sequence Genome sequence
         * @param type Type (leftFlank, rightFlank, spacer, DR)
         * @param startPos Start position within scaffold
         * @param endPos End position within scaffold
         */
        explicit Record(string sequence, string type, int startPos, int endPos);
        /**
         * Get the auto-generated ID for this record
         * @return UUID of record
         */
        string getId();
        /**
         * Get the genome sequence of this record
         * @return String of sequence
         */
        string getSequence();
        /**
         * Get the type of this record
         * @return String of record type (leftFlank, rightFlank, spacer, DR)
         */
        string getType();
        /**
         * Get the start position of this record within the scaffold
         * @return Start position within scaffold
         */
        int getStartPos();
        /**
         * Get the end position of this record within the scaffold
         * @return End position within scaffold
         */
        int getEndPos();
    };
}

#endif
