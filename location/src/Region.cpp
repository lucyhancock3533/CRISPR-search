#include "cslocation.hpp"
#include "Region.hpp"

namespace crisprsearch::location {
    string Region::getId() {
        return id;
    }

    string Region::getSequence() {
        return sequence;
    }

    string Region::getType() {
        return type;
    }

    int Region::getStartPos() {
        return startPos;
    }

    int Region::getEndPos() {
        return endPos;
    }

    Region::Region(string sequence, string type, int startPos, int endPos) {
        this->sequence = std::move(sequence);
        this->type = std::move(type);
        this->startPos = startPos;
        this->endPos = endPos;

        // Generate random UUID and convert to string for ID
        basic_random_generator<boost::mt19937> uuidGen;
        uuid idRaw = uuidGen();
        this->id = boost::uuids::to_string(idRaw);
    }
}