#!/usr/bin/python

#
# Load the mail graph and try to filter the messages 
# by count of target addresses 


import string
import re
from traceparser import traceparser 




class MailGraphFilter:

    def filter( self, filename, filtervalue) :
        self.parser = traceparser(filename)  
        while self.parser.Next():
            if(len(self.parser.Tos()) > filtervalue):
                continue
            print self.parser.Line()
            



if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3 :
        print 'Usage : %s <mesglog> <filter by #outgoing>' % sys.argv[0]
        sys.exit(1)

    file = sys.argv[1]
    count = int(sys.argv[2])

    mg = MailGraphFilter()
    mg.filter(file, count)


