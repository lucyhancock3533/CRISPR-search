#include "cslocation.hpp"
#include "GenomeLocation.hpp"
#include "GenomeDecompression.hpp"

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
            GenomeDecompression decompression = GenomeDecompression(genomePath);
            unique_ptr<char[]> fileContent = decompression.decompress();
            ofstream decompressedFile("tmp/tmp.fa", std::ios::out);
            if(decompressedFile.good()) {
                decompressedFile << fileContent.get();
                decompressedFile.close();

                processGenome();
            }
        }
        else if(fileExt == "fa" || fileExt == "fasta" || fileExt == "fst" || fileExt == "fna") {
            // Ready to use path
            boost::filesystem::path tempFile = "tmp/tmp.fa";
            boost::filesystem::path sourceFile = genomePath;
            boost::filesystem::copy_file(sourceFile, tempFile);
            processGenome();
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
        }

        // TODO: Parse
    }
}