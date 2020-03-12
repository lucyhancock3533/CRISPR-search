class StatCalc:
    cursor = None
    evidenceLevel = None
    sourceList = None
    sourceCounts = []

    def __init__(self, cursor, evidenceLevel, sourceList):
        self.cursor = cursor
        self.evidenceLevel = evidenceLevel
        self.sourceList = sourceList

    def genBasicStats(self):
        # Generate all vs confident stats
        self.cursor.execute('SELECT id FROM CRISPR;')
        cCount = len(self.cursor.fetchall())
        self.cursor.execute('SELECT id FROM CRISPR WHERE evidenceLevel >= ?;', [self.evidenceLevel])
        ccCount = len(self.cursor.fetchall())
        self.sourceCounts.append(('All Data', cCount, ccCount))

        # Generate for sources
        for source in self.sourceList:
            self.cursor.execute('SELECT id FROM Genomes WHERE genomeSource = ?;', [source])
            idList = [x[0] for x in self.cursor.fetchall()]
            crispr = []
            for id in idList:
                self.cursor.execute('SELECT id FROM CRISPR WHERE genomeId = ?;', [id])
                crispr = crispr + self.cursor.fetchall()
            icCount = len(crispr)
            crispr = []
            for id in idList:
                self.cursor.execute('SELECT id FROM CRISPR WHERE evidenceLevel >= ? AND genomeId = ?;', [self.evidenceLevel, id])
                crispr = crispr + self.cursor.fetchall()
            iccCount = len(crispr)
            self.sourceCounts.append((source, icCount, iccCount))

        print(self.sourceCounts)