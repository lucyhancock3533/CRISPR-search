#ifndef CRISPR_SEARCH_LOCATION_REGION_HPP
#define CRISPR_SEARCH_LOCATION_REGION_HPP

#include "cslocation.hpp"

namespace crisprsearch::location {
    /**
     * Spacer region storage class
     */
    class Region {
    private:
        string id;
        string sequence;
        string type;
        int startPos;
        int endPos;
    public:
        /**
         * Create a new spacer region from values
         * @param sequence Genome sequence
         * @param type Type (leftFlank, rightFlank, spacer, DR)
         * @param startPos Start position within scaffold
         * @param endPos End position within scaffold
         */
        explicit Region(string sequence, string type, int startPos, int endPos);

        /**
         * Get the auto-generated ID for this region
         * @return UUID of region
         */
        string getId();

        /**
         * Get the genome sequence of this region
         * @return String of sequence
         */
        string getSequence();

        /**
         * Get the type of this region
         * @return String of region type (leftFlank, rightFlank, spacer, DR)
         */
        string getType();

        /**
         * Get the start position of this region within the scaffold
         * @return Start position within scaffold
         */
        int getStartPos();

        /**
         * Get the end position of this region within the scaffold
         * @return End position within scaffold
         */
        int getEndPos();
    };
}

#endif
