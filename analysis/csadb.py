import sqlite3

class DbConnection:
    dbConn = sqlite3.connect(':memory:')

    def loadDatabase(self, dbPath):
        diskConn = sqlite3.connect(dbPath)
        # Copy database into memory and close disk database
        diskSql = "".join(line for line in diskConn.iterdump())
        self.dbConn.executescript(diskSql)
        diskConn.close()

    def addSql(self, sql):
        self.dbConn.executescript(sql)

    def getCursor(self):
        return self.dbConn.cursor()

    def closeDatabase(self):
        self.dbConn.close()