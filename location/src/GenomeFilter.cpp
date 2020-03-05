#include "cslocation.hpp"
#include "GenomeFilter.hpp"

namespace crisprsearch::location {
    /// Filter non-allowed FASTA characters
    bool removeChar(char c) {
        if(isalnum(c)) {
            return false;
        }

        switch(c){
            case '\n':
                return false;
            case '\r':
                return false;
            case '>':
                return false;
            case ' ':
                return false;
        }

        return true;
    }

    GenomeFilter::GenomeFilter(char* data) {
        fileData = data;
    }

    GenomeFilter::GenomeFilter(string filePath) {
        // Open file into memory
        ifstream file(filePath);
        if (!file.good()) {
            cout << "Could not load FASTA file." << endl;
            throw FileNotGoodException();
        }
        string data;
        data.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
        file.close();

        fileData = new char[data.length() + 1];
        memcpy(fileData, data.c_str(), data.length());
        fileData[data.length()] = '\0';
    }

    void GenomeFilter::filter() {
        // Filter chars from data
        string f = string(fileData);
        f.erase(remove_if(f.begin(), f.end(), removeChar), f.end());
        // Move into new char[]
        delete[] fileData;
        fileData = new char[f.length() + 1];
        memcpy(fileData, f.c_str(), f.length());
        fileData[f.length()] = '\0';
    }

    void GenomeFilter::save(string outputPath) {
        ofstream decompressedFile(outputPath, std::ios::out);
        if(decompressedFile.good()) {
            decompressedFile << fileData;
            decompressedFile.close();
        }
        else {
            throw FileNotGoodException();
        }
    }

    GenomeFilter::~GenomeFilter() {
        delete[] fileData;
    }
}