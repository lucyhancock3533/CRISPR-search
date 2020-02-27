#ifndef CRISPR_SEARCH_LOCATION_CSL_CONSTANTS_HPP
#define CRISPR_SEARCH_LOCATION_CSL_CONSTANTS_HPP

#define SQLITE_GET_TABLES "SELECT * FROM sqlite_master WHERE TYPE = 'table';"
#define SQLITE_CREATE_GENOME_TABLE "CREATE TABLE Genomes(id UUID PRIMARY KEY NOT NULL, name TEXT NOT NULL, genomeInfo TEXT NOT NULL, genomeSource TEXT NOT NULL);"
#define SQLITE_CREATE_CRISPR_TABLE "CREATE TABLE CRISPR(id UUID PRIMARY KEY NOT NULL, genomeId UUID NOT NULL, sourceSequence TEXT NOT NULL, drLength NUMBER NOT NULL, spacers NUMBER NOT NULL, evidenceLevel NUMBER NOT NULL, regions NUMBER NOT NULL);"
#define SQLITE_CREATE_REGION_TABLE "CREATE TABLE Regions(id UUID PRIMARY KEY NOT NULL, crisprId UUID NOT NULL, sequence TEXT NOT NULL, type TEXT NOT NULL, regionNo NUMBER NOT NULL, startPos NUMBER NOT NULL, endPos NUMBER NOT NULL);"
#define SQLITE_INSERT_REGION "INSERT INTO Regions (id, crisprId, sequence, type, regionNo, startPos, endPos) VALUES (?, ?, ?, ?, ?, ?, ?);"
#define SQLITE_INSERT_CRISPR "INSERT INTO CRISPR (id, genomeId, sourceSequence, drLength, spacers, evidenceLevel, regions) VALUES (?, ?, ?, ?, ?, ?, ?);"
#define SQLITE_INSERT_GENOME "INSERT INTO Genomes (id, name, genomeInfo, genomeSource) VALUES (?, ?, ?, ?);"

#endif
