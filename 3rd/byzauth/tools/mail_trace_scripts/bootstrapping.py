#!/usr/bin/python -tOO 
#
# Generate the trusted group by using only 
# local heuristics based on sent and receive
# connectivity in the email graph 



import string
import re
from traceparser import traceparser
import sys
import random  



class bootstrapping:
    ''' For each message in the trace, collect all to addresses it is sent
    to.  Generate a count of messages for a given from to tuple
    The graph is stored in forward and backward direction. 
    '''
    def __init__(self, filename, numtg) :
        self.parser = traceparser(filename)
        self.outgoing = dict()
        self.incoming = dict()
        count = 0
        while self.parser.Next():
            count = count + 1
            if (count % 8192) == 0:
                sys.stderr.write( 'processed %d records\n' % count )
                
            # maintain outgoing dict of dicts
            if self.parser.From() not in self.outgoing :
                self.outgoing[self.parser.From()] = dict()
                
            tounique = {}
            for to in self.parser.Tos():
                tounique[to] = 1
                
            for to in tounique.keys():
                if to not in self.outgoing[self.parser.From()]:
                    self.outgoing[self.parser.From()][to] = 1
                else :
                    self.outgoing[self.parser.From()][to] = self.outgoing[self.parser.From()][to] + 1

                # maintain the incoming dict of dicts 
                if to not in self.incoming:
                    self.incoming[to] = dict()
                if self.parser.From() not in self.incoming[to]:
                     self.incoming[to][self.parser.From()] = 1
                else:
                    self.incoming[to][self.parser.From()] = self.incoming[to][self.parser.From()] + 1
                

        # want to find intersection, followed by outgoing followed by incoming
        # two way is possibly the best especially because we want to trim
        # the size of simulation
        count = 0
        self.trustgroup = dict() 
        for peer in self.outgoing.keys():
            
            count = count + 1
            if (count % 8192) == 0:
                sys.stderr.write('computed trust group for %d peers\n' % count)

            # For each peer that receives some messages
            # Also sends by the for condition 
            if self.incoming.has_key(peer): 
                # sort by the send x receive activity for each 
                # sender, receiver tuple according to call back value
                sequence = 0 
                sortlist = []
                for receiver in self.outgoing[peer].keys():
                    if receiver == peer:
                        continue 
                    if self.incoming[peer].has_key(receiver):
                        product = self.getpriority(peer,
                                                   receiver,
                                                   self.outgoing[peer][receiver],
                                                   self.incoming[peer][receiver],
                                                   sequence 
                                                   )
                        sequence = sequence + 1 
                        sortlist.append( (product, receiver) ) 

                sortlist.sort()

                tg = [] 
                for (product,receiver) in sortlist:
                    if len(tg) > numtg:
                        break
                    tg.append( receiver ) 
                
                self.trustgroup[peer] = tg



    def write_trusted_groups(self): 
        for peer in self.trustgroup.keys(): 
            str = '%s\t' % peer
            for trusted in self.trustgroup[peer]:
                str = '%s  %s' % (str, trusted)
            print str
        




class serial_bootstrapping(bootstrapping):
    def getpriority(self, sender, receiver, numsent, numrecvd, sequence):
        return sequence



class random_bootstrapping(bootstrapping):
    def getpriority(self, sender, receiver, numsent, numrecvd, sequence):
        return random.randint(0,1000000) 



class product_bootstrapping(bootstrapping):
    def getpriority(self, sender, receiver, numsent, numrecvd, sequence):
        return numsent * numrecvd



class balance_bootstrapping(bootstrapping):
    def getpriority(self, sender, receiver, numsent, numrecvd, sequence):
        if numsent == 0 or numrecvd == 0:
            return 0
        balance = float(numsent)/float(numrecvd)
        return -(balance + 1.0/balance)
    


class sent_bootstrapping(bootstrapping):
    def getpriority(self, sender, receiver, numsent, numrecvd, sequence):
        return numsent

    

class recvd_bootstrapping(bootstrapping):
    def getpriority(self, sender, receiver, numsent, numrecvd, sequence):
        return numrecvd
    
        




if __name__ == "__main__":
    import sys
    if len(sys.argv) != 4 :
        print 'Usage : %s <mesglog> <tgsz> <selectiontype = serial|random|product|balance|sent|recvd' % sys.argv[0]
        sys.exit(1)

    file = sys.argv[1]
    tgsz = int(sys.argv[2])
    rule = sys.argv[3]

    exec('tg = %s_bootstrapping(file, tgsz)' % rule)
        
    tg.write_trusted_groups() 


