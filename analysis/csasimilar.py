import uuid
import os
from csablast import FastaDbGen, BLAST
from tqdm import tqdm

class SimilarityCalc:
    fastaDb = None
    blastIns = None
    cursor = None
    evidenceLevel = None
    similarityPercCutoff = None
    similarities = None
    blastDb = None

    def __init__(self, cursor, evidenceLevel, similarityPercCutoff, dbPath, blastPath, generateDb=True):
        fileName = ''
        if generateDb:
            self.fastaDb = FastaDbGen(cursor, evidenceLevel)
            self.cursor = cursor
            self.evidenceLevel = evidenceLevel
            fileName = '/' + str(uuid.uuid4()) + '.fa'
            self.fastaDb.exportFastaFile(dbPath + fileName)
        self.blastIns = BLAST(blastPath)
        self.blastIns.generateBlastDb(dbPath + fileName)
        self.similarityPercCutoff = similarityPercCutoff
        self.blastDb = dbPath + fileName

    def doSimilarityCalc(self):
        self.cursor.execute('SELECT id, name, genomeSource FROM Genomes;')
        genomeIds = self.cursor.fetchall()
        genomeResults = []
        for genome in tqdm(genomeIds):
            results = []
            self.cursor.execute('SELECT id FROM CRISPR WHERE evidenceLevel >= ? AND genomeId = ?;',
                                [self.evidenceLevel, genome[0]])
            crisprIds = [x[0] for x in self.cursor.fetchall()]
            for crispr in crisprIds:
                self.cursor.execute('SELECT sequence FROM Regions WHERE crisprId = ? AND type = ?;', [crispr, 'Spacer'])
                spacers = [x[0] for x in self.cursor.fetchall()]
                for spacer in spacers:
                    if 'N' not in spacer:
                        fn = './' + str(uuid.uuid4()) + '.fa'
                        file = open(fn, "w")
                        file.write('>query\n' + spacer)
                        file.close()
                        blastRes = self.blastIns.runBlastShortQuery(self.blastDb, fn)
                        os.remove(fn)

                        if len(blastRes) > 0:
                            # Calculate relevant matches
                            minBit = float(blastRes[0][1]) * (self.similarityPercCutoff/100)
                            # add matches to results
                            for i in range(1, len(blastRes)):
                                if float(blastRes[i][1]) >= minBit:
                                    results.append(blastRes[i])
            if len(results) > 0 and self.fastaDb is not None:
                genomeResults.append((genome[1] + ' - ' + genome[2], [self.replaceIdForNameFastaDb(x) for x in results]))
            elif len(results) > 0 and self.fastaDb is None:
                genomeResults.append((genome[1] + ' - ' + genome[2]))
        self.similarities = genomeResults

    def replaceIdForNameFastaDb(self, ipt):
        return self.fastaDb.fastaDb[ipt[0]][1] + ' - ' + self.fastaDb.fastaDb[ipt[0]][2] + ' - ' + ipt[0], ipt[1], ipt[2], ipt[3]

    def replaceId(self, ipt):
        return ipt[0], ipt[1], ipt[2], ipt[3]