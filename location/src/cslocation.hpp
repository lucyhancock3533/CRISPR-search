#ifndef CRISPR_SEARCH_LOCATION_CSLOCATION_HPP
#define CRISPR_SEARCH_LOCATION_CSLOCATION_HPP

#include <string>
#include <memory>
#include <utility>
#include <cstring>
#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include <vector>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/copy.hpp>

#include "rapidjson/document.h"

using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::ifstream;
using std::ios_base;
using std::stringstream;
using std::make_unique;
using std::make_shared;
using std::exception;
using std::vector;

using boost::iostreams::input;
using boost::iostreams::filtering_streambuf;
using boost::iostreams::gzip_decompressor;

extern string CRISPR_CAS_FINDER_PATH;

#endif
