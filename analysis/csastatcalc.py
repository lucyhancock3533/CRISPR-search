class StatCalc:
    cursor = None
    evidenceLevel = None
    sourceList = None
    sourceCounts = []
    sourcePercs = []

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

    def genPercStats(self):
        sources = [('All Sources', 'SELECT id FROM Genomes;', [])]
        sources += [(x, 'SELECT id FROM Genomes WHERE genomeSource = ?;', [x]) for x in self.sourceList]
        self.sourcePercs = [self.gpsCalc(x[0], x[1], x[2]) for x in sources]

    def gpsCalc(self, source, sqlGen, params):
        # Generate all present stats
        self.cursor.execute(sqlGen, params)
        idList = [x[0] for x in self.cursor.fetchall()]
        wCrispr = 0
        woCrispr = 0
        for id in idList:
            self.cursor.execute('SELECT id FROM CRISPR WHERE evidenceLevel >= ? AND genomeId = ?;', [self.evidenceLevel, id])
            if len(self.cursor.fetchall()) == 0:
                woCrispr += 1
            else:
                wCrispr += 1
        wcP = (wCrispr / (woCrispr + wCrispr)) * 100
        wocP = (woCrispr / (woCrispr + wCrispr)) * 100
        return source, round(wcP, 2), round(wocP, 2)
