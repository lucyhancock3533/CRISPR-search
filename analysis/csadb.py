from csasettings import csaSettings
import sqlite3

# Load database connections
diskConn = sqlite3.connect(csaSettings.dbPath)
dbConn = sqlite3.connect(':memory:')

# Copy database into memory and close disk database
diskSql = "".join(line for line in diskConn.iterdump())
dbConn.executescript(diskSql)
diskConn.close()
diskConn = None
