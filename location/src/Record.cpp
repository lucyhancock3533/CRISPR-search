#include "cslocation.hpp"
#include "Record.hpp"

namespace crisprsearch::location {

    string Record::getId() {
        return id;
    }

    string Record::getSequence() {
        return sequence;
    }

    string Record::getType() {
        return type;
    }

    int Record::getStartPos() {
        return startPos;
    }

    int Record::getEndPos() {
        return endPos;
    }

    Record::Record(string sequence, string type, int startPos, int endPos) {
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