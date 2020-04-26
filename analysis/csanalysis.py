from csasettings import CsaSettings
from csastatcalc import StatCalc
from csadb import DbConnection
from csadistribution import DistCalc
from csahtmlgen import CsaHTMLGenerator
from jinja2 import FileSystemLoader
import sys
import os.path
from csablast import FastaDbGen, BLAST

csaSettings = CsaSettings()

def setupParameters():
    for i in range(1, len(sys.argv)):
        if sys.argv[i] == '--db' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.dbPath = sys.argv[i+1]
        elif sys.argv[i] == '--out' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.outputPath = sys.argv[i+1]
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

    if csaSettings.dbPath is None:
        print('No database was specified, run %s --help for more information.' % sys.argv[0], file=sys.stderr)
        sys.exit(1)

    if csaSettings.blastPath is None:
        print('BLAST path not specified, modules requiring BLAST disabled.', file=sys.stderr)
        csaSettings.doSimilar = False

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
        fasta = FastaDbGen(dbConnection.getCursor(), csaSettings.evidenceLevel)
        fasta.exportFastaFile('../test.fa')
        b = BLAST(csaSettings.blastPath)
        b.generateBlastDb('../test.fa')
        print(b.runBlastShortQuery('../test.fa', './run.fa'))

    htmlLoader = FileSystemLoader('.')
    outputHtml = htmlOutput.generateHTML(htmlLoader)
    file = open(csaSettings.outputPath, "w")
    file.write(outputHtml)
    file.close()

    dbConnection.closeDatabase()
