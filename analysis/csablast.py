class FastaDbGen:
    cursor = None
    evidenceLevel = None
    fasta = None
    fastaDb = None

    def __init__(self, cursor, evidenceLevel):
        self.cursor = cursor
        self.evidenceLevel = evidenceLevel

    def generateFastaDb(self):
        pass

    def generateFasta(self):
        pass

    def exportFastaFile(self, filePath):
        pass