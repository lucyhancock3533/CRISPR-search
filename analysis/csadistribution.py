import sys
import base64

# Use AGG backend to remove tkinter exceptions when running headless
import matplotlib
matplotlib.use("Agg")

import numpy as np
import matplotlib.pyplot as plot
from matplotlib.ticker import PercentFormatter
from io import BytesIO

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

    def generateFigurePngB64(self):
        img = BytesIO()
        plot.savefig(img, format="png", dpi=220, bbox_inches='tight', pad_inches=0)
        return base64.encodebytes(img.getvalue()).decode()

    def plotHistogram(self, data, minSize, maxSize, labels, ticks=None):
        plot.hist(x=data, bins=maxSize-minSize, weights=[np.ones(len(x)) / len(x) for x in data], density=True,
                  range=[minSize, maxSize], histtype='bar', align='left',
                  label=labels)  # Render bar histogram for all datasets, weights being set to 1/n for percentile output
        if ticks is None:
            ticks = list(range(minSize, maxSize))
        plot.xticks(ticks=ticks, labels=ticks)
        plot.gca().yaxis.set_major_formatter(PercentFormatter(1))
        plot.legend(prop={'size': 20})

    def cleanFigure(self):
        plot.clf()
        plot.cla()
        plot.close()

    def generateSpacerLengthHist(self):
        if self.ids is None:
            self.setupIdLists()

        # Fetch database data
        lengths = []
        labels = []
        minSize = sys.maxsize
        maxSize = 0
        for source in self.ids:
            spacers = []
            for id in source[2]:
                self.cursor.execute('SELECT sequence FROM Regions WHERE crisprId = ? AND type = ?;', [id, 'Spacer'])
                spacers = spacers + [x[0] for x in self.cursor.fetchall()]
            spacers = list(filter(lambda x: 'N' not in x, spacers))
            spacerLengths = sorted(list(map(len, spacers)))
            if spacerLengths[-1] > maxSize:
                maxSize = spacerLengths[-1]
            if spacerLengths[0] < minSize:
                minSize = spacerLengths[0]
            lengths.append(spacerLengths)
            labels.append(source[0])

        # Generate histogram
        plot.figure(figsize=(40, 15))
        self.plotHistogram(lengths, minSize, maxSize, labels)
        self.lengthDistributionB64 = self.generateFigurePngB64()
        plot.savefig('tmp_lengthdist.png', dpi=220, bbox_inches='tight', pad_inches=0)  # TODO: Remove after HTML gen
        self.cleanFigure()

    def generateSpacerHist(self):
        pass

    def generateArrayHist(self):
        pass

    def generateArraySpacerHist(self):
        if self.ids is None:
            self.setupIdLists()

        # Fetch data
        spacersPerArray = []
        labels = []
        maxSize = 0
        for source in self.ids:
            spacerCount = []
            for id in source[1]:
                self.cursor.execute('SELECT spacers FROM CRISPR WHERE genomeId = ? AND evidenceLevel >= ?;',
                                    [id, self.evidenceLevel])
                spacerCount += [x[0] for x in self.cursor.fetchall()]
            spacerCount = sorted(spacerCount)
            labels.append(source[0])
            if spacerCount[-1] > maxSize:
                maxSize = spacerCount[-1]
            spacersPerArray.append(spacerCount)

        # Generate histogram
        plot.figure(figsize=(50, 15))
        self.plotHistogram(spacersPerArray, 0, maxSize, labels, np.arange(0, maxSize, 10).tolist())
        self.arraySpacerDistributionB64 = self.generateFigurePngB64()
        plot.savefig('tmp_arrayspacerdist.png', dpi=220, bbox_inches='tight', pad_inches=0)  # TODO: Remove after HTML gen
        self.cleanFigure()