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
        self.assertEqual(('AATTCATGATTTTAGAAGAATTAAACTAGC', 'RUG017', 'RUG-900'), f.fastaDb['c36be8fc-18fb-4ea8-b91d-4092a495819d-36'])
        self.assertEqual(('TTTGAGGATAGTGAAGTATTGCAAAAGAAAATAGAT', 'hRUG857', 'RUG-900'), f.fastaDb['1e1016e2-9cd4-4245-a064-a41fbd656b89-37'])
        self.assertEqual(('AGCGATTTCATACATATTCACCCCCGAATA', 'RUG081', 'RUG-900'), f.fastaDb['8f02a85f-1261-4c1e-8e1c-ed9025cac6f9-16'])

    def testFastaGen(self):
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.loadDatabase('test_dbs/rug900.sdb')
        f = FastaDbGen(self.db.getCursor(), 3)
        f.generateFasta()
        self.assertIsNotNone(f.fastaDb)
        self.assertIsNotNone(f.fasta)
        self.assertEqual(544624, len(f.fasta))

    def testFastaWrite(self):
        self.db.changeConnDb('test_dbs/' + str(uuid.uuid4()) + '.db')
        self.db.loadDatabase('test_dbs/rug900.sdb')
        f = FastaDbGen(self.db.getCursor(), 3)
        fileName = 'test_dbs/' + str(uuid.uuid4()) + '.db'
        f.exportFastaFile(fileName)
        file = open(fileName, "r")
        fileData = file.read()
        file.close()
        self.assertEqual(544624, len(fileData))
        self.assertEqual(f.fasta, fileData)