from csasettings import CsaSettings
from csastatcalc import StatCalc
from csadb import DbConnection

if __name__ == "__main__":
    print('CRISPR-search Analysis')
    csaSettings = CsaSettings()
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
    print('Generating statistics... (This may take some time)')
    stats.genBasicStats()

    dbConnection.closeDatabase()
