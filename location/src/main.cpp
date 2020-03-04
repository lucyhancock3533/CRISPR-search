#include "cslocation.hpp"
#include "CsLocationSetupJsonParser.hpp"
#include "GenomeLocation.hpp"

string CRISPR_CAS_FINDER_PATH;

using namespace crisprsearch::location;

void printHelp(char *cmd);

/// Location tool application main entry function
int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Invalid command string." << endl;
        cout << "Valid format: " << argv[0] << " <setup file path>" << endl;
        cout << "For more information run: " << argv[0] << " --help" << endl;
        return 1;
    }

    if (string(argv[1]) == "--help") {
        printHelp(argv[0]);
        return 0;
    }

    // Load JSON file
    ifstream setupFile(argv[1]);
    if (!setupFile.good()) {
        cout << "Could not load setup file." << endl;
        return 1;
    }
    string fileData;
    fileData.assign(istreambuf_iterator<char>(setupFile), istreambuf_iterator<char>());
    setupFile.close();

    // Parse JSON File
    auto setup = CsLocationSetupJsonParser(fileData);
    try {
        setup.parseJson();
    }
    catch (InvalidJSONException e) {
        cout << e.what() << endl;
        return 1;
    }

    // Open DB
    LocationDb *locDb = new LocationDb(setup.getCrisprDbPath());

    // Process genomes
    vector<CsLocationFile> files = setup.getFiles();
    for (int pos = 0; pos < files.size(); pos++) {
        cout << "[" << (pos + 1) << "/" << files.size() << "] Processing genome " << files[pos].genomeName << endl;
        GenomeLocation genome = GenomeLocation(files[pos].fileName, locDb, files[pos].genomeName,
                                               files[pos].genomeInfo, files[pos].genomeSource);
        genome.loadGenome();
    }
    return 0;
}

void printHelp(char *cmd) {
    cout << "CRISPR-Search location tool" << endl;
    cout << "Uses CRISPRCasFinder to search through a catalog of genomes and record CRISPR arrays into" << endl;
    cout << "the database." << endl << endl;
    cout << "Command should be called as " << cmd << " <setup json file>" << endl;
    cout << "Setup JSON format:" << endl;
    cout << "{\"ccfPath\":\"<Full path to CRISPRCasFinder.pl>\", \"dbPath\":\"<Path to output database>\"," << endl;
    cout << "\"genomes\":[(Array of genome objects) {\"name\":\"<Genome name>\", \"source\":\"<Genome source>\","
         << endl;
    cout << "\"info\":\"<Link to genome information>\", \"file\":\"<Full path to (compressed) FASTA>\"}]}" << endl;
}