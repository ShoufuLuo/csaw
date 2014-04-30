#!/usr/bin/python

#
# Load the mail graph and output send and
# receive count by address



import string
import re
import shelve 
from traceparser import traceparser 




class GetSendRecvStats:

    def __init__(self):
        self.sent = {}
        self.recvd = {}
        self.result = {} 
        
    def process( self, filename) :
        self.parser = traceparser(filename)  
        while self.parser.Next():
            ''' ignore the emails that go nowhere '''
            if len(self.parser.Tos()) == 1 and self.parser.Tos()[0] == self.parser.From() :
                continue

            self.__inc( self.sent, self.parser.From() )  
            for to in self.parser.Tos():
                if to != self.parser.From():
                    self.__inc( self.recvd, to )

        usekeys = [] 
        for item in self.sent.keys():
            if self.recvd.has_key(item):
                usekeys.append(item)

        for item in usekeys:
            numrecvd = self.recvd[item]
            numsent = self.sent[item]
            ratio = float(numrecvd)
            ratio = ratio / float(numsent)
            self.result[ item ] = (ratio, numsent, numrecvd )

        return self.result 
            


    def __inc(self,  datamap , item ):
        if item not in datamap:
            datamap[item] = 0
        datamap[item] = datamap[item] + 1
        



if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2 :
        print 'Usage : %s <mesglog> [<shelfsave]'  % sys.argv[0]
        sys.exit(1)

    file = sys.argv[1]
    stats = GetSendRecvStats()
    output = stats.process(file)

    if len(sys.argv) == 3 :
        d = shelve.open(sys.argv[2])
        for item in output.keys():
            d[item] = output[item]
        d.close()
        
    else:
        for item in output.keys():
            print repr(output[item]) , item 




