class FastaDbGen:
    cursor = None
    evidenceLevel = None
    fasta = None
    fastaDb = None

    def __init__(self, cursor, evidenceLevel):
        self.cursor = cursor
        self.evidenceLevel = evidenceLevel

    def generateFastaDb(self):
        self.fastaDb = {}

        # Fetch genomes
        self.cursor.execute('SELECT id, name, genomeSource FROM Genomes;')
        genomes = self.cursor.fetchall()

        # Fetch relevant arrays for genomes
        for genome in genomes:
            name = genome[1]
            source = genome[2]
            self.cursor.execute('SELECT id, spacers FROM CRISPR WHERE genomeId = ? AND evidenceLevel >= ?;',
                                [genome[0], self.evidenceLevel])
            arrays = self.cursor.fetchall()

            # Fetch spacers for arrays
            for array in arrays:
                self.cursor.execute('SELECT sequence FROM Regions WHERE crisprId = ? AND type = ?;',
                                    [array[0], 'Spacer'])
                spacers = [x[0] for x in self.cursor.fetchall()]
                for i in range(0, len(spacers)):
                    if 'N' not in spacers[i]:
                        self.fastaDb[array[0] + '-' + str(i)] = (spacers[i], name, source)

    def generateFasta(self):
        if self.fastaDb == None:
            self.generateFastaDb()
        self.fasta = ''

        for k in self.fastaDb:
            self.fasta += '>{}\n'.format(k)
            self.fasta += '{}\n'.format(self.fastaDb[k][0])

    def exportFastaFile(self, filePath):
        if self.fasta == None:
            self.generateFasta()

        file = open(filePath, "w")
        file.write(self.fasta)
        file.close()