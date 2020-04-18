from csastatcalc import StatCalc
from csadistribution import DistCalc
from jinja2 import Environment, select_autoescape

class CsaHTMLGenerator:
    doGenerateBasic = False
    doGenerateDist = False

    basicStatCalc = None
    distCalc = None

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

    def generateHTML(self, templateLoader):
        paramDict = self.assembleParamDict()
        jinjaEnv = Environment(loader=templateLoader, autoescape=select_autoescape(['html', 'htm']))
        template = jinjaEnv.get_template('csanalysis_output.html')
        return template.render(paramDict)

    def assembleParamDict(self):
        paramDict = {}
        paramDict['doGenerateBasic'] = self.doGenerateBasic
        paramDict['doGenerateDist'] = self.doGenerateDist
        if self.doGenerateBasic:
            paramDict['crisprCounts'] = self.basicStatCalc.sourceCounts
            paramDict['crisprPercs'] = self.basicStatCalc.sourcePercs
        if self.doGenerateDist:
            paramDict['lengthPng'] = self.distCalc.lengthDistributionB64
            paramDict['spacerPng'] = self.distCalc.spacerDistributionB64
            paramDict['spacerNzPng'] = self.distCalc.spacerDistributionNoZeroB64
            paramDict['arrayPng'] = self.distCalc.arrayDistributionB64
            paramDict['arraySpacerPng'] = self.distCalc.arraySpacerDistributionB64
        return paramDict