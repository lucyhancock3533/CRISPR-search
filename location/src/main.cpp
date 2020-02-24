#include "cslocation.hpp"
#include "CsLocationSetupJsonParser.hpp"

string CRISPR_CAS_FINDER_PATH;

using namespace crisprsearch::location;

/// Location tool application main entry function
int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "Invalid command string." << endl;
        cout << "Valid format: " << argv[0] << " <setup file path>" << endl;
        cout << "For more information run: " << argv[0] << " --help" << endl;
        return 1;
    }

    if(string(argv[1]) == "--help") {
        cout << "Not implemented." << endl;
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

    return 0;
}