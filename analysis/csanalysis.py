from csasettings import csaSettings
from csastatcalc import genBasicStats
from csadb import DbConnection

if __name__ == "__main__":
    print('CRISPR-search Analysis')
    dbConnection = DbConnection()
    dbConnection.loadDatabase()

    # Generate list of data sources
    cursor = dbConnection.getCursor()
    cursor.execute('SELECT genomeSource FROM Genomes;')
    sourceList = cursor.fetchall()
    sourceList = set(sourceList)
    sourceList = list(sourceList)
    sourceList = [source[0] for source in sourceList]

    # Generate base statistics
    stats = genBasicStats(dbConnection.getCursor(), csaSettings.evidenceLevel, sourceList)

    dbConnection.closeDatabase()
