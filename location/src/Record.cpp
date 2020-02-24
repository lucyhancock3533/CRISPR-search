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
        this->sequence = sequence;
        this->type = type;
        this->startPos = startPos;
        this->endPos = endPos;
        this->id = "IDNOTIMPLEMENTED";
    }
}