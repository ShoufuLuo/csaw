#!/usr/bin/python -tOO

import os
from usage import usage


# cat authentication.log | grep AUTHSTATUS | more 
# Mon Dec 18 20:17:22 2006        self.cpp 1278 Dec 18 2006 20:03:18      _authenticate_peer s       SENDER=33435b57ecf77b4226615e211ea507e2  :  AUTHSTATUS TIME=2764856 COMPLETION=0.181818 Trusted=10  Migrated=0  Probationary=9  Bootstrap=11      gcc4.1.1
 

class optimistic(usage) :

    def __init__(self, fd, listofkeys, factor):
        self.max = {}
        self.begintime = {}
        self.candidates = set() 
        self.starttime = 0
        self.endtime = 86400*30 
        usage.__init__( self, fd, listofkeys, factor)

        
    def getvalueofinterest(self, values) :
        return int(1.0 * float(values['COMPLETION'])) 


    def gather(self):
        prevtindex = 0
        while self.data() is not None:
            try:
                nmessages = self.getvalueofinterest(self.values)
                sender = self.values['SENDER']
                t = int(self.values['TIME'])

                ''' non dimensionalize the t value by considering time
                from the first seen date of the peer'''
                if sender not in self.begintime:
                    self.begintime[sender] = t
                difft = t - self.begintime[sender] 
                tindex = self.gettimebucket('%s' % difft)

                ''' Use only those peers that have started off on authentication
                within the first thirty days'''    
                if self.starttime == 0:
                    self.starttime = t 
                    self.endtime = t + self.endtime
                if t < self.endtime:
                    if sender not in self.candidates:
                        self.candidates.add(sender)
                else:
                    if sender not in self.candidates:
                        continue

                if tindex not in self.timeddata:
                    self.timeddata[tindex] = {}
                if sender not in self.timeddata[tindex]:
                    self.timeddata[tindex][sender] = []
                self.timeddata[tindex][sender] = self.timeddata[tindex][sender] + [nmessages]
                #print '%s %d %d' % (sender, tindex, nmessages)
                   
            except:
                pass

        prevtindex = -1
        timelist = self.timeddata.keys()
        timelist.sort()
        for tindex in timelist:
            if prevtindex != -1: 
                for peer in self.timeddata[prevtindex].keys() :
                    ''' replace missing peers (who didnt talk) to get smooth data'''
                    if peer not in self.timeddata[tindex] :
                        self.timeddata[tindex][peer] = []
                        for value in self.timeddata[prevtindex][peer]:
                            self.timeddata[tindex][peer] = self.timeddata[tindex][peer] + [value]
            prevtindex = tindex

        ''' just take the best observation over a bucket for each peer and use it for gathering
        the stats'''
        maxbypeer = {} 
        for tindex in timelist:
            best = 0
            total = 0
            count = 0 
            for peer in self.timeddata[tindex].keys() :
                maxval = 0
                for value in  self.timeddata[tindex][peer]:
                    if maxval < value:
                        maxval = value

                if peer not in maxbypeer:
                    maxbypeer[peer] = maxval
                elif maxbypeer[peer] > maxval:
                    maxval = maxbypeer[peer]
                else:
                    maxbypeer[peer] = maxval
                    
                if best < maxval:
                    best = maxval 
                total = total + maxval
                count = count + 1
            average = total/count
            seconds = tindex*self.factor + self.starttime
            print '%d %d %d' % (seconds, average, best)

            


if __name__ == "__main__":
    import sys
    if len(sys.argv) <= 1 :
        print 'Usage : %s <logfile>' % sys.argv[0]
        sys.exit(1)

    listofkeys = ('SENDER' , 'TIME' , 'COMPLETION' ) 
    factor =  86400
    fd = os.popen( 'cat %s | grep OPTSTATUS' % sys.argv[1] )
    c = optimistic(fd, listofkeys, factor)
    c.gather()


