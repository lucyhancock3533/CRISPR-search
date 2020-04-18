import unittest
import uuid
from csasettings import CsaSettings
from csadb import DbConnection
from csastatcalc import StatCalc
from csadistribution import DistCalc
from csahtmlgen import CsaHTMLGenerator
from pathlib import Path

class TestCsaHTMLGeneration(unittest.TestCase):
    db = DbConnection()

    def testValidStatCalc(self):
        Path("./test_dbs").mkdir(parents=True, exist_ok=True)
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.loadDatabase('test_dbs/rug900.sdb')

        # Generate list of data sources
        cursor = self.db.getCursor()
        cursor.execute('SELECT genomeSource FROM Genomes;')
        sourceList = cursor.fetchall()
        sourceList = set(sourceList)
        sourceList = list(sourceList)
        sourceList = [source[0] for source in sourceList]

        html = CsaHTMLGenerator()
        sett = CsaSettings()
        s = StatCalc(self.db.getCursor(), sett.evidenceLevel, sourceList)
        s.genBasicStats()
        s.genPercStats()
        html.addBasic(s)

    def testInvalidStatCalc(self):
        html = CsaHTMLGenerator()
        s = CsaSettings()
        self.assertRaises(TypeError, html.addBasic, s)

    def testValidDistCalc(self):
        Path("./test_dbs").mkdir(parents=True, exist_ok=True)
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.loadDatabase('test_dbs/rug900.sdb')

        # Generate list of data sources
        cursor = self.db.getCursor()
        cursor.execute('SELECT genomeSource FROM Genomes;')
        sourceList = cursor.fetchall()
        sourceList = set(sourceList)
        sourceList = list(sourceList)
        sourceList = [source[0] for source in sourceList]

        html = CsaHTMLGenerator()
        sett = CsaSettings()
        d = DistCalc(self.db.getCursor(), sett.evidenceLevel, sourceList)
        d.generateSpacerLengthHist()
        d.generateArraySpacerHist()
        d.generateArrayHist()
        d.generateSpacerHist()
        html.addDist(d)


    def testInvalidDistCalc(self):
        html = CsaHTMLGenerator()
        s = CsaSettings()
        self.assertRaises(TypeError, html.addDist, s)

    def testHTMLGen(self):
        pass