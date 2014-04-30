#!/usr/bin/python -tOO 


import sys 

if len(sys.argv) != 4 : 
    print 'Usage : %s <interval (seconds)> <bsgfile> <tracefile> ' % sys.argv[0] 
    sys.exit(1) 

stopat = 4752000 
interval = int(sys.argv[1]) 
bsgfile = sys.argv[2] 
trace = sys.argv[3] 
keysize = 16 
trustedgroupsize = 10 
completionfile = '../completion.%d.dat' % interval 

print ''' 
all: 
\trm -rf peerdata *.log 
\t../testprotocol2 %s %s %d %d %d %d
\t../gather_log_info/completion.py authentication.log > %s \n\n''' % (bsgfile, 
                                                      trace, 
                                                      trustedgroupsize, 
                                                      keysize, 
                                                      interval, 
                                                      stopat, 
                                                      completionfile) 






