#include "cslocation.hpp"
#include "Genome.hpp"
#include "Crispr.hpp"
#include "Region.hpp"

namespace crisprsearch::location {

    Genome::Genome(string name, string genomeSource, string genomeInfo) {
        crisprs = make_shared<vector<Crispr>>();

        this->name = move(name);
        this->genomeInfo = move(genomeInfo);
        this->genomeSource = move(genomeSource);

        // Generate random UUID and convert to string for ID
        basic_random_generator<boost::mt19937> uuidGen;
        uuid idRaw = uuidGen();
        this->id = boost::uuids::to_string(idRaw);
    }

    string Genome::getId() {
        return id;
    }

    string Genome::getName() {
        return name;
    }

    string Genome::getGenomeSource() {
        return genomeSource;
    }

    string Genome::getGenomeInfo() {
        return genomeInfo;
    }

    shared_ptr<vector<Crispr>> Genome::getCrispr() {
        return crisprs;
    }

    void Genome::addCrispr(Crispr crispr) {
        crisprs->push_back(move(crispr));
    }

    void Genome::parseResultsJson(string path) {
        // Load result JSON
        ifstream resultFile(path);
        if (!resultFile.good()) {
            cout << "Could not load results file." << endl;
            return;
        }
        string fileData;
        fileData.assign(istreambuf_iterator<char>(resultFile), istreambuf_iterator<char>());
        resultFile.close();

        shared_ptr<Document> json = make_shared<Document>();
        if(json->Parse(fileData.c_str()).HasParseError()) {
            throw InvalidJSONException();
        }

        auto sequences =  (*json)["Sequences"].GetArray();
        for(int pos = 0; pos < sequences.Size(); pos++) {
            auto seqCrispr = sequences[pos]["Crisprs"].GetArray();
            for(int cpos = 0; cpos < seqCrispr.Size(); cpos++) {
                auto crisprObj = seqCrispr[cpos].GetObject();

                Crispr crispr = Crispr(string(sequences[pos]["Id"].GetString())
                        + string(sequences[pos]["Description"].GetString()), crisprObj["DR_Length"].GetInt(),
                        crisprObj["Spacers"].GetInt(), crisprObj["Evidence_Level"].GetInt());
                auto crRegions = crisprObj["Regions"].GetArray();

                for(int rpos = 0; rpos < crRegions.Size(); rpos++) {
                    auto regionObj = crRegions[rpos].GetObject();
                    Region region = Region(string(regionObj["Sequence"].GetString()),
                            string(regionObj["Type"].GetString()), regionObj["Start"].GetInt(), regionObj["End"].GetInt());
                    crispr.addRegion(region);
                }

                this -> addCrispr(crispr);
            }
        }
    }
}