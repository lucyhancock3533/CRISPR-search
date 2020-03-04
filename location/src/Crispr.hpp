#ifndef CRISPR_SEARCH_LOCATION_CRISPR_HPP
#define CRISPR_SEARCH_LOCATION_CRISPR_HPP

#include "cslocation.hpp"
#include "Region.hpp"

namespace crisprsearch::location {
    /**
     * Crispr storage class
     */
    class Crispr {
    private:
        string id;
        string sourceAssembly;
        int drLength;
        int spacers;
        int evidenceLevel;
        shared_ptr<vector<Region>> regions;
    public:
        /**
         * Crispr constructor for making new crispr object
         * @param sourceAssembly Assembly crispr array was found in
         * @param drLength Length of repeat
         * @param spacers Number of spacers
         * @param evidenceLevel CRISPRCasFinder evidence level
         */
        explicit Crispr(string sourceAssembly, int drLength, int spacers, int evidenceLevel);

        /**
         * Get the auto-generated ID for this crispr
         * @return UUID as string
         */
        string getId();

        /**
         * Get the repeat length of this crispr
         * @return Repeat length
         */
        int getDrLength();

        /**
         * Get the number of spacers in this crispr array
         * @return Number of spacer regions
         */
        int getSpacerCount();

        /**
         * Get the CRISPRCasFinder evidence level for this crispr array
         * @return CRISPRCasFinder evidence level
         */
        int getEvidenceLevel();

        /**
         * Get the assembly this crispr array was found within
         * @return String of assembly name
         */
        string getSourceAssembly();

        /**
         * Get the regions of this crispr array
         * @return Shared pointer to Region vector of regions
         */
        shared_ptr<vector<Region>> getRegions();

        /**
         * Add a region to this crispr array
         * @param region Region to add to array
         */
        void addRegion(Region region);
    };
}

#endif
