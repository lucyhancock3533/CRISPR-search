#ifndef CRISPR_SEARCH_LOCATION_CSLOCATION_HPP
#define CRISPR_SEARCH_LOCATION_CSLOCATION_HPP

#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include <vector>
#include <cctype>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/filesystem.hpp>
#include <boost/process.hpp>

#include "rapidjson/document.h"

#include <sqlite3.h>

#include "csl_constants.hpp"

using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::ifstream;
using std::ofstream;
using std::ios_base;
using std::stringstream;
using std::make_unique;
using std::make_shared;
using std::exception;
using std::vector;
using std::cout;
using std::endl;
using std::istreambuf_iterator;
using std::move;
using std::isalnum;
using std::remove_if;

using boost::iostreams::input;
using boost::iostreams::filtering_streambuf;
using boost::iostreams::gzip_decompressor;
using boost::uuids::uuid;
using boost::uuids::basic_random_generator;

using namespace rapidjson;

extern string CRISPR_CAS_FINDER_PATH;

namespace crisprsearch::location {
    struct InvalidJSONException : public exception {
        const char *what() const throw() {
            return "Setup JSON was invalid or missing required parameters.";
        }
    };

    struct FileNotGoodException : public exception {
        const char *what() const throw() {
            return "Could not load file";
        }
    };
}

#endif
