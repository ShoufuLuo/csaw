#!/usr/bin/python -tOO

import os
from usage import usage


# cat authentication.log | grep AUTHSTATUS | more 
# Mon Dec 18 20:17:22 2006        self.cpp 1278 Dec 18 2006 20:03:18      _authenticate_peer s       SENDER=33435b57ecf77b4226615e211ea507e2  :  AUTHSTATUS TIME=2764856 COMPLETION=0.181818 Trusted=10  Migrated=0  Probationary=9  Bootstrap=11      gcc4.1.1
 

class completion(usage) :

    def __init__(self, fd, listofkeys, factor):
        self.max = {}
        self.begintime = {} 
        usage.__init__( self, fd, listofkeys, factor)

        
    def getvalueofinterest(self, values) :
        return int(100.0 * float(values['COMPLETION'])) 


    def gather(self):
        prevtindex = 0
        while self.data() is not None:
            try:
                nmessages = self.getvalueofinterest(self.values)
                sender = self.values['SENDER']
                t = int(self.values['TIME'])
                if sender not in self.begintime:
                    self.begintime[sender] = t
                difft = t - self.begintime[sender] 
                tindex = self.gettimebucket('%s' % difft)


                    
                if sender not in self.max or self.max[sender] < nmessages:
                    self.max[sender] = nmessages
                else:
                    nmessages = self.max[sender]

                if tindex not in self.timeddata:
                    self.timeddata[tindex] = {}
                if sender not in self.timeddata[tindex]:
                    self.timeddata[tindex][sender] = []
                self.timeddata[tindex][sender] = self.timeddata[tindex][sender] + [nmessages]


                    
            except:
                pass


if __name__ == "__main__":
    import sys
    if len(sys.argv) <= 1 :
        print 'Usage : %s <logfile>' % sys.argv[0]
        sys.exit(1)

    listofkeys = ('SENDER' , 'TIME' , 'COMPLETION' ) 
    factor =  86400
    fd = os.popen( 'cat %s | grep AUTHSTATUS' % sys.argv[1] )
    c = completion(fd, listofkeys, factor)
    c.gather()
    c.report() 


