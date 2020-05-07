import sqlite3

"""SQLite database wrapper class"""
class DbConnection:
    dbConn = sqlite3.connect(':memory:')

    """Connect to a different database file than the in memory DB"""
    def changeConnDb(self, memDb):
        self.dbConn.close()
        self.dbConn = sqlite3.connect(memDb)

    """Load a stored database into the in memory database"""
    def loadDatabase(self, dbPath):
        diskConn = sqlite3.connect(dbPath)
        # Copy database into memory and close disk database
        diskSql = "".join(line for line in diskConn.iterdump())
        self.dbConn.executescript(diskSql)
        diskConn.close()

    """Add an SQL script to the in memory DB"""
    def addSql(self, sql):
        self.dbConn.executescript(sql)

    """Return a cursor on the database"""
    def getCursor(self):
        return self.dbConn.cursor()

    """Close the current database connection"""
    def closeDatabase(self):
        self.dbConn.close()