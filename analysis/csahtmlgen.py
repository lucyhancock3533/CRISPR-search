from csastatcalc import StatCalc
from csadistribution import DistCalc

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

    def generateHTML(self):
        paramDict = {}
        paramDict['doGenerateBasic'] = self.doGenerateBasic
        paramDict['doGenerateDist'] = self.doGenerateDist
        if self.doGenerateBasic:
            paramDict['statCalc'] = self.basicStatCalc
        if self.doGenerateDist:
            paramDict['distCalc'] = self.distCalc
        return ''