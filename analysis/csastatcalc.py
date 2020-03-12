def genBasicStats(cursor, evidenceLevel, sourceList):
    print('Generating statistics... (This may take some time)')

    # Generate all vs confident stats
    cursor.execute('SELECT id FROM CRISPR;')
    cCount = len(cursor.fetchall())
    cursor.execute('SELECT id FROM CRISPR WHERE evidenceLevel >= ?;', [evidenceLevel])
    ccCount = len(cursor.fetchall())

    # Generate for sources
    sourceCounts = []
    for source in sourceList:
        cursor.execute('SELECT id FROM Genomes WHERE genomeSource = ?;', [source])
        idList = [x[0] for x in cursor.fetchall()]
        crispr = []
        for id in idList:
            cursor.execute('SELECT id FROM CRISPR WHERE genomeId = ?;', [id])
            crispr = crispr + cursor.fetchall()
        icCount = len(crispr)
        crispr = []
        for id in idList:
            cursor.execute('SELECT id FROM CRISPR WHERE evidenceLevel >= ? AND genomeId = ?;', [evidenceLevel, id])
            crispr = crispr + cursor.fetchall()
        iccCount = len(crispr)
        sourceCounts.append((source, icCount, iccCount))

    html = "<p>CRISPR found: %s<br/>Confident CRISPR found: %s</p>" % (cCount, ccCount)
    for x in sourceCounts:
        nHtml = "<p>Source: %s<br/>CRISPR found: %s<br/>Confident CRISPR found: %s</p>" % x
        html += nHtml

    return html
