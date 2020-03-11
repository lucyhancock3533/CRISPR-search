from csasettings import csaSettings
import csadb
from csastatcalc import genBasicStats

if __name__ == "__main__":
    print('CRISPR-search Analysis')
    csadb.loadDatabase()

    # Generate list of data sources
    cursor = csadb.dbConn.cursor()
    cursor.execute('SELECT genomeSource FROM Genomes;')
    sourceList = cursor.fetchall()
    sourceList = set(sourceList)
    sourceList = list(sourceList)
    sourceList = [source[0] for source in sourceList]

    # Generate base statistics
    stats = genBasicStats(csadb.dbConn, csaSettings.evidenceLevel, sourceList)