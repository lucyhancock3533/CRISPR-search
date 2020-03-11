from csasettings import csaSettings
import sqlite3

# Load database connections
dbConn = sqlite3.connect(':memory:')

def loadDatabase():
    diskConn = sqlite3.connect(csaSettings.dbPath)
    # Copy database into memory and close disk database
    diskSql = "".join(line for line in diskConn.iterdump())
    dbConn.executescript(diskSql)
    diskConn.close()
