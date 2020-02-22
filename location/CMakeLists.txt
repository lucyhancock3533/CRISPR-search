cmake_minimum_required(VERSION 3.10)
project(CRISPR_search_location)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(src/)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.65.0 COMPONENTS iostreams regex)

find_package(ZLIB)
include_directories(${ZLIB_DEPS})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
include("${CMAKE_SOURCE_DIR}/rapidjson.cmake")
include_directories(${RAPIDJSON_INCLUDE_DIR})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(cslocation src/main.cpp src/GenomeDecompression.cpp src/GenomeDecompression.hpp src/cslocation.hpp src/CsLocationSetupJsonParser.cpp src/CsLocationSetupJsonParser.hpp)
    add_dependencies(cslocation rapidjson)
    target_link_libraries(cslocation z ${Boost_LIBRARIES})

    add_executable(cslocation-test test_src/test_main.cpp test_src/test_decompression.cpp src/GenomeDecompression.cpp src/GenomeDecompression.hpp src/cslocation.hpp src/CsLocationSetupJsonParser.cpp src/CsLocationSetupJsonParser.hpp test_src/test_setupjson.cpp)
    add_dependencies(cslocation-test rapidjson)
    target_link_libraries(cslocation-test z ${Boost_LIBRARIES} ${GTEST_LIBRARIES} pthread)
	
	install(TARGETS cslocation DESTINATION bin)
endif()