class DistCalc:
    cursor = None
    sourceList = None
    evidenceLevel = None
    ids = None

    def __init__(self, cursor, evidenceLevel, sourceList):
        self.cursor = cursor
        self.sourceList = sourceList
        self.evidenceLevel = evidenceLevel

    """Create Lists of IDs for use in distribution calculation functions"""
    def setupIdLists(self):
        self.ids = []
        for source in self.sourceList:
            self.cursor.execute('SELECT id FROM Genomes WHERE genomeSource = ?;', [source])
            genomeIds = [x[0] for x in self.cursor.fetchall()]
            crisprIds = []
            for id in genomeIds:
                self.cursor.execute('SELECT id FROM CRISPR WHERE evidenceLevel >= ? AND genomeId = ?;',
                                    [self.evidenceLevel, id])
                crisprIds = crisprIds + [x[0] for x in self.cursor.fetchall()]
            self.ids.append((source, genomeIds, crisprIds))

    def generateSpacerLengthHist(self):
        if self.ids == None:
            self.setupIdLists()
        lengths = []
        for source in self.ids:
            spacers = []
            for id in source[2]:
                self.cursor.execute('SELECT sequence FROM Regions WHERE crisprId = ? AND type = ?;', [id, 'Spacer'])
                spacers = spacers + [x[0] for x in self.cursor.fetchall()]
            spacers = list(filter(lambda x: 'N' not in x, spacers))
            spacerLengths = list(map(len, spacers))
            lengths.append((source[0], spacerLengths))