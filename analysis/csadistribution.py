import itertools
import numpy as np
import matplotlib.pyplot as plot
from matplotlib.ticker import PercentFormatter

class DistCalc:
    cursor = None
    sourceList = None
    evidenceLevel = None
    ids = None

    # Outputs
    lengthDistributionB64 = None
    spacerDistributionB64 = None
    arrayDistributionB64 = None
    arraySpacerDistributionB64 = None

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
        bins = 0
        for source in self.ids:
            spacers = []
            for id in source[2]:
                self.cursor.execute('SELECT sequence FROM Regions WHERE crisprId = ? AND type = ?;', [id, 'Spacer'])
                spacers = spacers + [x[0] for x in self.cursor.fetchall()]
            spacers = list(filter(lambda x: 'N' not in x, spacers))
            spacerLengths = sorted(list(map(len, spacers)))
            lenGroups = len([k for k, v in itertools.groupby(spacerLengths)])
            if lenGroups > bins:
                bins = lenGroups
            lengths.append(spacerLengths)
        labels = [s[0] for s in self.ids]
        plot.figure(figsize=(30, 20))
        plot.hist(x=lengths, bins=bins, weights=[np.ones(len(x)) / len(x) for x in lengths], density=True, histtype='bar', label=labels)
        plot.gca().yaxis.set_major_formatter(PercentFormatter(1))
        plot.legend(prop={'size': 20})
        plot.savefig('test.png', dpi=320, bbox_inches='tight', pad_inches=0)
        plot.clf()