from csasettings import CsaSettings
from csastatcalc import StatCalc
from csadb import DbConnection
import sys

csaSettings = CsaSettings()

def setupParameters():
    for i in range(1, len(sys.argv)):
        if sys.argv[i] == '--db' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.dbPath = sys.argv[i+1]
        if sys.argv[i] == '--out' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.outputPath = sys.argv[i+1]
        if sys.argv[i] == '--evidence-level' and (len(sys.argv) - (i + 1)) >= 1:
            csaSettings.evidenceLevel = int(sys.argv[i+1])
        if sys.argv[i] == '--skip-stat-calc':
            csaSettings.doStatCalc = False

    if csaSettings.dbPath == '':
        print('No database was specified, run %s --help for more information.' % sys.argv[0])
        sys.exit(1)

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

    stats = StatCalc(dbConnection.getCursor(), csaSettings.evidenceLevel, sourceList)
    if csaSettings.doStatCalc:
        print('Generating statistics... (This may take some time)')
        stats.genBasicStats()
        stats.genPercStats()

    dbConnection.closeDatabase()
