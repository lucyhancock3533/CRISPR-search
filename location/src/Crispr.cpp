#include "Crispr.hpp"

#include <utility>

namespace crisprsearch::location {
    Crispr::Crispr(string sourceAssembly, int drLength, int spacers, int evidenceLevel) {
        this->sourceAssembly = move(sourceAssembly);
        this->drLength = drLength;
        this->spacers = spacers;
        this->evidenceLevel = evidenceLevel;

        // Create vector
        regions = make_shared<vector<Region>>();

        // Generate random UUID and convert to string for ID
        basic_random_generator<boost::mt19937> uuidGen;
        uuid idRaw = uuidGen();
        this->id = boost::uuids::to_string(idRaw);
    }

    string Crispr::getId() {
        return id;
    }

    int Crispr::getDrLength() {
        return drLength;
    }

    int Crispr::getSpacerCount() {
        return spacers;
    }

    int Crispr::getEvidenceLevel() {
        return evidenceLevel;
    }

    shared_ptr<vector<Region>> Crispr::getRegions() {
        return regions;
    }

    void Crispr::addRegion(Region region) {
        regions->push_back(move(region));
    }

    string Crispr::getSourceAssembly() {
        return sourceAssembly;
    }
}