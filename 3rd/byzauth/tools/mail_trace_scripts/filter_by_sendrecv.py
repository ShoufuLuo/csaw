#!/usr/bin/python

#
# Load the mail graph and try to filter the messages 
# by count of target addresses 


import string
import re
from traceparser import traceparser 




class SendRecvFilter:

    def __init__( self, filename ) :
        self.parser = traceparser(filename)
        self.senders = set()
        self.receivers = set() 
        while self.parser.Next():
            self.senders.add( self.parser.From())
            for to in self.parser.Tos():
                self.receivers.add( to )

        self.sendrecv = self.senders & self.receivers
        self.parser = traceparser(filename)
        while self.parser.Next():
            if self.parser.From() in self.sendrecv:
                print self.parser.Line()

    

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2 :
        print 'Usage : %s <mesglog>' % sys.argv[0]
        sys.exit(1)

    file = sys.argv[1]

    mg = SendRecvFilter(file)
    


