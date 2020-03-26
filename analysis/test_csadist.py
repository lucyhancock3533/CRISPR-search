import unittest
import uuid
from csadb import DbConnection
from csadistribution import DistCalc
from pathlib import Path

class TestCsaDistribution(unittest.TestCase):
    db = DbConnection()
    sql = ''

    def testSpacerLenDist(self):
        Path("./test_dbs").mkdir(parents=True, exist_ok=True)
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.addSql(self.sql)
        d = DistCalc(self.db.getCursor(), 3, ['RUG-900'])
        self.assertIsNotNone(d.lengthDistributionB64)
        self.assertNotEqual(len(d.lengthDistributionB64), 0)

    def testSpacerDist(self):
        Path("./test_dbs").mkdir(parents=True, exist_ok=True)
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.addSql(self.sql)
        d = DistCalc(self.db.getCursor(), 3, ['RUG-900'])
        self.assertIsNotNone(d.spacerDistributionB64)
        self.assertNotEqual(len(d.spacerDistributionB64), 0)

    def testArrayDist(self):
        Path("./test_dbs").mkdir(parents=True, exist_ok=True)
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.addSql(self.sql)
        d = DistCalc(self.db.getCursor(), 3, ['RUG-900'])
        self.assertIsNotNone(d.arrayDistributionB64)
        self.assertNotEqual(len(d.arrayDistributionB64), 0)

    def testArraySpacerDist(self):
        Path("./test_dbs").mkdir(parents=True, exist_ok=True)
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.addSql(self.sql)
        d = DistCalc(self.db.getCursor(), 3, ['RUG-900'])
        self.assertIsNotNone(d.arraySpacerDistributionB64)
        self.assertNotEqual(len(d.arraySpacerDistributionB64), 0)