#include "cslocation.hpp"
#include "CsLocationSetupJsonParser.hpp"

#include <utility>

using namespace rapidjson;

namespace crisprsearch::location {
    CsLocationSetupJsonParser::CsLocationSetupJsonParser(string json) {
        jsonString = move(json);
        files = vector<CsLocationFile>();
    }

    void CsLocationSetupJsonParser::parseJson() {
        // Parse JSON Document
        shared_ptr<Document> json = make_shared<Document>();
        if(json->Parse(jsonString.c_str()).HasParseError()) {
            throw InvalidJSONException();
        }

        // Check all required members are present
        if(!json->HasMember("ccfPath") || !json->HasMember("dbPath") || !json->HasMember("genomes")) {
            throw InvalidJSONException();
        }

        // Get ccfPath from document
        if((*json)["ccfPath"].IsString()) {
            CRISPR_CAS_FINDER_PATH = string((*json)["ccfPath"].GetString());
        }
        else {
            throw InvalidJSONException();
        }

        // Get dbPath from document
        if((*json)["dbPath"].IsString()) {
            crisprDbpath = string((*json)["dbPath"].GetString());
        }
        else {
            throw InvalidJSONException();
        }

        // Parse Genomes
        parseGenomesArray(json);
    }

    void CsLocationSetupJsonParser::parseGenomesArray(shared_ptr<Document> json) {
        // Parse genomes array
        if((*json)["genomes"].IsArray()) {
            // Build genomes from array into vector
            for(int pos = 0; pos < (*json)["genomes"].GetArray().Size(); pos++) {
                CsLocationFile file;

                // Add file name
                if((*json)["genomes"].GetArray()[pos].HasMember("file") &&
                (*json)["genomes"].GetArray()[pos]["file"].IsString()) {
                    file.fileName = string((*json)["genomes"].GetArray()[pos]["file"].GetString());
                }
                else {
                    throw InvalidJSONException();
                }

                // Add genome name
                if((*json)["genomes"].GetArray()[pos].HasMember("name") &&
                   (*json)["genomes"].GetArray()[pos]["name"].IsString()) {
                    file.genomeName = string((*json)["genomes"].GetArray()[pos]["name"].GetString());
                }
                else {
                    throw InvalidJSONException();
                }

                // Add genome source
                if((*json)["genomes"].GetArray()[pos].HasMember("source") &&
                   (*json)["genomes"].GetArray()[pos]["source"].IsString()) {
                    file.genomeSource = string((*json)["genomes"].GetArray()[pos]["source"].GetString());
                }
                else {
                    throw InvalidJSONException();
                }

                // Add genome info
                if((*json)["genomes"].GetArray()[pos].HasMember("info") &&
                   (*json)["genomes"].GetArray()[pos]["info"].IsString()) {
                    file.genomeInfo = string((*json)["genomes"].GetArray()[pos]["info"].GetString());
                }
                else {
                    throw InvalidJSONException();
                }

                // Add to vector
                files.push_back(file);
            }
        }
        else {
            throw InvalidJSONException();
        }
    }

    vector<CsLocationFile> CsLocationSetupJsonParser::getFiles() {
        return files;
    }

    string CsLocationSetupJsonParser::getCrisprDbPath() {
        return crisprDbpath;
    }
}
