from csastatcalc import StatCalc
from csadistribution import DistCalc
from csasimilar import SimilarityCalc
from jinja2 import Environment, select_autoescape

class CsaHTMLGenerator:
    doGenerateBasic = False
    doGenerateDist = False
    doGenerateSimilar = False
    doGenerateExternal = False

    basicStatCalc = None
    distCalc = None
    similarCalc = None
    externalCalc = []

    def addBasic(self, statCalc):
        if isinstance(statCalc, StatCalc):
            self.doGenerateBasic = True
            self.basicStatCalc = statCalc
        else:
            raise TypeError('Provided object is not of type StatCalc')

    def addDist(self, distCalc):
        if isinstance(distCalc, DistCalc):
            self.doGenerateDist = True
            self.distCalc = distCalc
        else:
            raise TypeError('Provided object is not of type DistCalc')

    def addSimilar(self, similarCalc):
        if isinstance(similarCalc, SimilarityCalc):
            self.doGenerateSimilar = True
            self.similarCalc = similarCalc
        else:
            raise TypeError('Provided object is not of type SimilarityCalc')

    def addExternal(self, externalCalc, externalName='Database name unknown'):
        if isinstance(externalCalc, SimilarityCalc):
            self.doGenerateExternal = True
            self.externalCalc.append((externalName, externalCalc))
        else:
            raise TypeError('Provided object is not of type SimilarityCalc')

    def generateHTML(self, templateLoader):
        paramDict = self.assembleParamDict()
        jinjaEnv = Environment(loader=templateLoader, autoescape=select_autoescape(['html', 'htm']))
        template = jinjaEnv.get_template('csanalysis_output.html')
        return template.render(paramDict)

    def assembleParamDict(self):
        paramDict = {'doGenerateBasic': self.doGenerateBasic,
                     'doGenerateDist': self.doGenerateDist,
                     'doGenerateSimilar': self.doGenerateSimilar,
                     'doGenerateExternal': self.doGenerateExternal}
        if self.doGenerateBasic:
            paramDict['crisprCounts'] = self.basicStatCalc.sourceCounts
            paramDict['crisprPercs'] = self.basicStatCalc.sourcePercs
        if self.doGenerateDist:
            paramDict['lengthPng'] = self.distCalc.lengthDistributionB64
            paramDict['spacerPng'] = self.distCalc.spacerDistributionB64
            paramDict['spacerNzPng'] = self.distCalc.spacerDistributionNoZeroB64
            paramDict['arrayPng'] = self.distCalc.arrayDistributionB64
            paramDict['arraySpacerPng'] = self.distCalc.arraySpacerDistributionB64
        if self.doGenerateSimilar:
            paramDict['similarities'] = self.similarCalc.similarities
        if self.doGenerateExternal:
            paramDict['externals'] = [(x[0], x[1].similarities) for x in self.externalCalc]
        return paramDict