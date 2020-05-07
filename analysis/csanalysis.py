from csasettings import CsaSettings
from csastatcalc import StatCalc
from csadb import DbConnection
from csadistribution import DistCalc
from csahtmlgen import CsaHTMLGenerator
from jinja2 import FileSystemLoader
import sys
import os.path
from csasimilar import SimilarityCalc
from pathlib import Path

csaSettings = CsaSettings()

def setupParameters():
    for i in range(1, len(sys.argv)):
        if sys.argv[i] == '--db' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.dbPath = sys.argv[i+1]
        elif sys.argv[i] == '--out' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.outputPath = sys.argv[i+1]
        elif sys.argv[i] == '--blast-db-path' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.blastDbPath = sys.argv[i+1]
            Path(csaSettings.blastDbPath).mkdir(parents=True, exist_ok=True)
        elif sys.argv[i] == '--similarity-cutoff' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.similarityPercCutoff = int(sys.argv[i+1])
        elif sys.argv[i] == '--blast-path' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.blastPath = sys.argv[i+1]
            if not os.path.exists(csaSettings.blastPath + '/bin/blastn') \
                    and not os.path.exists(csaSettings.blastPath + '/bin/makeblastdb'):
                print('BLAST executables not found at %s.' % csaSettings.blastPath, file=sys.stderr)
                sys.exit(1)
        elif sys.argv[i] == '--evidence-level' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.evidenceLevel = int(sys.argv[i+1])
        elif sys.argv[i] == '--skip-stat-calc':
            csaSettings.doStatCalc = False
        elif sys.argv[i] == '--skip-dist-calc':
            csaSettings.doDistCalc = False
        elif sys.argv[i] == '--skip-similar':
            csaSettings.doSimilar = False
        elif sys.argv[i] == '--external-fasta-db' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.doExternal = True
            csaSettings.externalDbs.append(sys.argv[i+1])

    if csaSettings.dbPath is None:
        print('No database was specified, run %s --help for more information.' % sys.argv[0], file=sys.stderr)
        sys.exit(1)

    if csaSettings.blastPath is None:
        print('BLAST path not specified, modules requiring BLAST disabled.', file=sys.stderr)
        csaSettings.doSimilar = False
        csaSettings.doExternal = False

if __name__ == "__main__":
    print('CRISPR-search Analysis')
    setupParameters()
    dbConnection = DbConnection()
    dbConnection.loadDatabase(csaSettings.dbPath)

    # Generate list of data sources
    cursor = dbConnection.getCursor()
    cursor.execute('SELECT genomeSource FROM Genomes;')
    sourceList = cursor.fetchall()
    sourceList = set(sourceList)
    sourceList = list(sourceList)
    sourceList = [source[0] for source in sourceList]

    htmlOutput = CsaHTMLGenerator()

    if csaSettings.doStatCalc:
        stats = StatCalc(dbConnection.getCursor(), csaSettings.evidenceLevel, sourceList)
        print('Generating statistics... (This may take some time)')
        stats.genBasicStats()
        stats.genPercStats()
        htmlOutput.addBasic(stats)

    if csaSettings.doDistCalc:
        dist = DistCalc(dbConnection.getCursor(), csaSettings.evidenceLevel, sourceList)
        print('Generating distributions... (This may take some time)')
        dist.generateSpacerLengthHist()
        dist.generateArraySpacerHist()
        dist.generateArrayHist()
        dist.generateSpacerHist()
        htmlOutput.addDist(dist)

    if csaSettings.doSimilar:
        print('Generating similarities... (This may take a very long time)')
        similar = SimilarityCalc(dbConnection.getCursor(), csaSettings.evidenceLevel,
                                 csaSettings.similarityPercCutoff, csaSettings.blastDbPath, csaSettings.blastPath)
        similar.doSimilarityCalc()
        htmlOutput.addSimilar(similar)

    if csaSettings.doExternal:
        print('Generating external searches... (This may take a very long time)')
        for x in csaSettings.externalDbs:
            similar = SimilarityCalc(dbConnection.getCursor(), csaSettings.evidenceLevel,
                                     csaSettings.similarityPercCutoff, x, csaSettings.blastPath, generateDb=False)
            similar.doSimilarityCalc()
            htmlOutput.addExternal(similar, externalName=x)

    print('Generating output HTML...')
    htmlLoader = FileSystemLoader(os.path.dirname(os.path.realpath(__file__)))
    outputHtml = htmlOutput.generateHTML(htmlLoader)
    file = open(csaSettings.outputPath, "w")
    file.write(outputHtml)
    file.close()

    dbConnection.closeDatabase()