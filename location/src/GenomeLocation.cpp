#include "cslocation.hpp"
#include "GenomeLocation.hpp"
#include "GenomeDecompression.hpp"
#include "GenomeFilter.hpp"

namespace crisprsearch::location {
    GenomeLocation::GenomeLocation(string path, LocationDb* db, string name, string info, string source) {
        genomePath = path;
        dbConnection = db;
        genome = new Genome(name, source, info);
    }

    GenomeLocation::~GenomeLocation() {
        delete genome;
    }

    void GenomeLocation::loadGenome() {
        // Select file processing
        string fileExt = genomePath.substr(genomePath.find_last_of('.') + 1);

        // Create temp folder
        boost::filesystem::path tempFolder = "tmp";
        boost::filesystem::create_directory(tempFolder);

        if(fileExt == "gz") {
            // Decompression path
            // Decompress and write temporary file
            char* fileContent;
            try {
                GenomeDecompression decompression = GenomeDecompression(genomePath);
                fileContent = decompression.decompress();
            } catch (FileNotGoodException) {
                cout << "Failed to create FASTA file." << endl;
            }

            try {
                GenomeFilter filter = GenomeFilter(fileContent);
                filter.filter();
                filter.save("tmp/tmp.fa");
                processGenome();
            } catch (FileNotGoodException) {
                delete[] fileContent;
                cout << "Failed to create FASTA file." << endl;
            }
        }
        else if(fileExt == "fa" || fileExt == "fasta" || fileExt == "fst" || fileExt == "fna") {
            // Ready to use path
            try {
                GenomeFilter filter = GenomeFilter(genomePath);
                filter.filter();
                filter.save("tmp/tmp.fa");
                processGenome();
            } catch (FileNotGoodException) {
                cout << "Failed to create FASTA file." << endl;
            }
        }
        else {
            // File is invalid
            cout << "File for genome " << genome->getName() << " is invalid." << endl;
        }

        // Delete temporary folder
        boost::filesystem::remove_all(tempFolder);
    }

    void GenomeLocation::processGenome() {
        // Run CRISPRCasFinder to locate CRISPR
        int result = boost::process::system(CRISPR_CAS_FINDER_PATH + CCF_ARGS_STRING_1
        + CRISPR_CAS_FINDER_PATH + CCF_ARGS_STRING_2);
        if(result != 0) {
            cout << "Failed to execute CRISPRCasFinder." << endl;
            return;
        }

        try {
            genome->parseResultsJson("tmp/result/result.json");
        } catch(InvalidJSONException) {
            cout << "Failed to parse genome JSON." << endl;
            return;
        }
        dbConnection->writeGenomeRecord(*genome);
    }
}