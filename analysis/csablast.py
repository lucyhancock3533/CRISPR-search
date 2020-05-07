import subprocess
import csv

"""FASTA Database holding class"""
class FastaDbGen:
    cursor = None
    evidenceLevel = None
    """String containing fasta file"""
    fasta = None
    """Dictionary mapping IDs in fasta to source genomes"""
    fastaDb = None

    def __init__(self, cursor, evidenceLevel):
        self.cursor = cursor
        self.evidenceLevel = evidenceLevel

    """Generate FASTA ID mapping database"""
    def generateFastaDb(self):
        self.fastaDb = {}

        # Fetch genomes
        self.cursor.execute('SELECT id, name, genomeSource FROM Genomes;')
        genomes = self.cursor.fetchall()

        # Fetch relevant arrays for genomes
        for genome in genomes:
            name = genome[1]
            source = genome[2]
            self.cursor.execute('SELECT id, spacers FROM CRISPR WHERE genomeId = ? AND evidenceLevel >= ?;',
                                [genome[0], self.evidenceLevel])
            arrays = self.cursor.fetchall()

            # Fetch spacers for arrays
            for array in arrays:
                self.cursor.execute('SELECT sequence FROM Regions WHERE crisprId = ? AND type = ?;',
                                    [array[0], 'Spacer'])
                spacers = [x[0] for x in self.cursor.fetchall()]
                for i in range(0, len(spacers)):
                    if 'N' not in spacers[i]:
                        # If the spacer doesn't contain Ns, store in fasta db
                        self.fastaDb[array[0] + '-' + str(i)] = (spacers[i], name, source)

    """Generate fasta file and store in fasta variable"""
    def generateFasta(self):
        if self.fastaDb == None:
            self.generateFastaDb()
        self.fasta = ''

        for k in self.fastaDb:
            self.fasta += '>{}\n'.format(k)
            self.fasta += '{}\n'.format(self.fastaDb[k][0])

    """Generate fasta file and save to disk"""
    def exportFastaFile(self, filePath):
        if self.fasta == None:
            self.generateFasta()

        file = open(filePath, "w")
        file.write(self.fasta)
        file.close()

"""BLAST executable wrapper class, not windows compatible"""
class BLAST:
    blastPath = None

    def __init__(self, blastPath):
        self.blastPath = blastPath

    """Generates a BLAST database and returns a string containing the path"""
    def generateBlastDb(self, fastaFile):
        # Execute blast db generation and discard stdout output
        subprocess.check_output([self.blastPath + '/bin/makeblastdb', '-dbtype', 'nucl', '-in', fastaFile])
        # Return path to database
        return fastaFile

    """Run a blastn-short query capturing the result and returning it as a list of lists, from rowns then columns of the output tsv"""
    def runBlastShortQuery(self, blastDb, queryFile):
        # Run blast query outputting as tsv, capture output in variable
        blastProcess = subprocess.check_output([self.blastPath + '/bin/blastn', '-task', 'blastn-short', '-db',
                                         blastDb, '-query', queryFile, '-outfmt', '6 sseqid bitscore qseq sseq']).decode()
        # Return parsed format
        return self.parseBlastShortQuery(blastProcess)

    def parseBlastShortQuery(self, result):
        # Parse tsv into list of lists, of rows then columns
        return [line for line in csv.reader(result.splitlines(), dialect='excel-tab')]