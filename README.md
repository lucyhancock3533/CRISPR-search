# CRISPR-search

## Location tool:

Tested on Ubuntu 18.04 LTS

To build you will require:
GCC8+, boost 1.65+, zlib, sqlite3, google test

Once all the libraries above are installed cd into the location directory and run:

`cmake .`
`make`

To run tests from the same directory run:
`bin/cslocation-test`
Do not change directory to run this command

To run CRISPRCasFinder must be installed from here: https://crisprcas.i2bc.paris-saclay.fr/
The install process for CRISPRCasFinder can be kinda buggy, it logs a terminal UI to a log file sometimes...

For more information on running the location tool run:
`cslocation --help`




## Analysis tool:
Requires python 3.8 and pipenv, which can be installed from pip, BLAST is optionally required to run similarities.

To install dependencies run:
`pipenv install`

To run tests, from the analysis directory:
`pipenv run python -m unittest discover`

To run tool run:
`pipenv run python csanalysis.py --db <path to db> --blast-path <path to blast>`
