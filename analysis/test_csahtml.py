import unittest
import uuid
from csasettings import CsaSettings
from csadb import DbConnection
from csastatcalc import StatCalc
from csadistribution import DistCalc
from csahtmlgen import CsaHTMLGenerator
from pathlib import Path
from jinja2 import DictLoader

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

    def testBlankHTMLGen(self):
        html = CsaHTMLGenerator()
        template = '<html><head><title>Unittest</title></head><body><p>Unittest</p></body></html>'
        htmlLoader = DictLoader({'csanalysis_output.html': template})
        self.assertEqual(len(template), len(html.generateHTML(htmlLoader)))
        self.assertEqual(template, html.generateHTML(htmlLoader))