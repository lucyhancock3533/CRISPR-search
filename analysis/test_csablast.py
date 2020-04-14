import unittest
import uuid
from csadb import DbConnection
from csablast import FastaDbGen

class TestFastaGen(unittest.TestCase):
    db = DbConnection()

    def testFastaDbGen(self):
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.loadDatabase('test_dbs/rug900.sdb')
        f = FastaDbGen(self.db.getCursor(), 3)
        f.generateFastaDb()
        self.assertIsNotNone(f.fastaDb)
        # Assert expected database

    def testFastaGen(self):
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.loadDatabase('test_dbs/rug900.sdb')
        f = FastaDbGen(self.db.getCursor(), 3)
        f.generateFasta()
        self.assertIsNotNone(f.fastaDb)
        self.assertIsNotNone(f.fasta)
        self.assertNotEquals(0, len(f.fasta))