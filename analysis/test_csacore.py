import unittest
import uuid
from csadb import DbConnection
from csastatcalc import StatCalc
from pathlib import Path

class TestCsaCore(unittest.TestCase):
    db = DbConnection()
    sql = "PRAGMA foreign_keys=OFF;BEGIN TRANSACTION;CREATE TABLE Genomes(id UUID PRIMARY KEY NOT NULL, name TEXT NOT NULL, genomeInfo TEXT NOT NULL, genomeSource TEXT NOT NULL);INSERT INTO Genomes VALUES('641736e6-6058-45dd-976d-bc52bac2adab','t1','','testData1');INSERT INTO Genomes VALUES('59461410-4c87-4f57-8ae7-79907c0939b0','t2','','testData1');INSERT INTO Genomes VALUES('c6f6bee6-1509-4555-8a40-8d2407bc6e04','t3','','testData2');INSERT INTO Genomes VALUES('acc0c0af-0436-4895-9688-02be466b6590','t4','','testData2');CREATE TABLE CRISPR(id UUID PRIMARY KEY NOT NULL, genomeId UUID NOT NULL, sourceSequence TEXT NOT NULL, drLength NUMBER NOT NULL, spacers NUMBER NOT NULL, evidenceLevel NUMBER NOT NULL, regions NUMBER NOT NULL);INSERT INTO CRISPR VALUES('59205fce-baa1-477a-88f5-9da0da1e945e','641736e6-6058-45dd-976d-bc52bac2adab','ta',38,1,4,5);INSERT INTO CRISPR VALUES('8e5b396a-8c66-4a74-ad66-1476e4762954','641736e6-6058-45dd-976d-bc52bac2adab','tb',38,1,1,5);INSERT INTO CRISPR VALUES('8b885d01-f42b-4c99-bacb-32ad5c5b1c07','c6f6bee6-1509-4555-8a40-8d2407bc6e04','tc',38,1,4,5);INSERT INTO CRISPR VALUES('76774c66-419f-4a2b-99e9-36df02a40a54','c6f6bee6-1509-4555-8a40-8d2407bc6e04','td',38,1,1,5);CREATE TABLE Regions(id UUID PRIMARY KEY NOT NULL, crisprId UUID NOT NULL, sequence TEXT NOT NULL, type TEXT NOT NULL, regionNo NUMBER NOT NULL, startPos NUMBER NOT NULL, endPos NUMBER NOT NULL);"

    def testBasicStats(self):
        Path("./test_dbs").mkdir(parents=True, exist_ok=True)
        # Change database
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.addSql(self.sql)
        # Generate and assert basic stats
        s = StatCalc(self.db.getCursor(), 3, ['testData1', 'testData2'])
        s.genBasicStats()
        self.assertEqual(s.sourceCounts[0][1], 4)
        self.assertEqual(s.sourceCounts[0][2], 2)
        self.assertEqual(s.sourceCounts[1][1], 2)
        self.assertEqual(s.sourceCounts[1][2], 1)
        self.assertEqual(s.sourceCounts[2][1], 2)
        self.assertEqual(s.sourceCounts[2][2], 1)
        pass

    def testPercStats(self):
        Path("./test_dbs").mkdir(parents=True, exist_ok=True)
        # Change Database
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.addSql(self.sql)
        # Generate and assert percentage stats
        s = StatCalc(self.db.getCursor(), 3, ['testData1', 'testData2'])
        s.genPercStats()
        self.assertEqual(s.sourcePercs[1][1], 50)
        self.assertEqual(s.sourcePercs[2][2], 50)
        pass