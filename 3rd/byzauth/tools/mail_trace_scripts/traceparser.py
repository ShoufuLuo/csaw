#!/usr/bin/python

# Parse the mail trace eg: 
# 2764919 3732    k0151po08339    b430fdfb5e0b6ab003cd1c34f74f0dc2        7512325afef6887544d84e322619161c f1d5346a5b23e5f19547056b58288343

import string
import re

class traceparser:

    def __init__( self, filename) :
        self.fp = open( filename, 'r' )
        self.pattern = re.compile( r'((\S*)(\s+))' )

    def Next(self):
        self.valid = 0
        tokens = ()
        line = self.fp.readline()
        if len(line) == 0:
            return 0
            
        for match in self.pattern.findall(line):
            tokens = tokens + (match[1] , )

        self.line = line[0:len(line)-1]
        self.date = tokens[0]
        self.size = tokens[1] 
        self.frm = tokens[3]
        self.tos = tokens[4:]
        self.valid = 1
        return 1

    def Date(self):
        if self.valid:
            return self.date
        raise 'not a valid record'

    def Size(self):
        if self.valid:
            return self.size
        raise 'not a valid record'
    
    def From(self):
        if self.valid:
            return self.frm
        raise 'not a valid record'

    def Tos(self):
        if self.valid:
            return self.tos
        raise 'not a valid record'

    def Line(self):
        if self.valid :
            return self.line
        raise 'not a valid record' 
    

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2 :
        print 'Usage : %s <mesglog>' % sys.argv[0]
        sys.exit(1)

    file = sys.argv[1]
    mg = traceparser(file)
    while mg.Next() :
        print mg.Line()

