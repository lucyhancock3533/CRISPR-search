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

    def generateSpacerLengthHist(self):
        if self.ids is None:
            self.setupIdLists()

        # Fetch database data
        lengths = []
        labels = []
        min = sys.maxsize
        max = 0
        for source in self.ids:
            spacers = []
            for id in source[2]:
                self.cursor.execute('SELECT sequence FROM Regions WHERE crisprId = ? AND type = ?;', [id, 'Spacer'])
                spacers = spacers + [x[0] for x in self.cursor.fetchall()]
            spacers = list(filter(lambda x: 'N' not in x, spacers))
            spacerLengths = sorted(list(map(len, spacers)))
            if spacerLengths[-1] > max:
                max = spacerLengths[-1]
            if spacerLengths[0] < min:
                min = spacerLengths[0]
            lengths.append(spacerLengths)
            labels.append(source[0])

        # Generate histogram
        plot.figure(figsize=(40, 15))  # Create 30x20 figure
        plot.hist(x=lengths, bins=max-min, weights=[np.ones(len(x)) / len(x) for x in lengths], density=True,
                  range=[min, max], histtype='bar', align='left',
                  label=labels)  # Render bar histogram for all datasets, weights being set to 1/n for percentile output
        plot.xticks(ticks=range(min, max), labels=range(min,max))
        plot.gca().yaxis.set_major_formatter(PercentFormatter(1))
        plot.legend(prop={'size': 20})
        self.lengthDistributionB64 = self.generateFigurePngB64()
        plot.savefig('tmp_lengthdist.png', dpi=220, bbox_inches='tight', pad_inches=0)  # TODO: Remove after HTML gen
        plot.clf()

    def generateSpacerHist(self):
        pass

    def generateArrayHist(self):
        pass

    def generateArraySpacerHist(self):
        pass