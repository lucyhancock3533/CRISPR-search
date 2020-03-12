from csasettings import csaSettings
import sqlite3

class DbConnection:
    dbConn = sqlite3.connect(':memory:')

    def loadDatabase(self):
        diskConn = sqlite3.connect(csaSettings.dbPath)
        # Copy database into memory and close disk database
        diskSql = "".join(line for line in diskConn.iterdump())
        self.dbConn.executescript(diskSql)
        diskConn.close()

    def getCursor(self):
        return self.dbConn.cursor()

    def closeDatabase(self):
        self.dbConn.close()