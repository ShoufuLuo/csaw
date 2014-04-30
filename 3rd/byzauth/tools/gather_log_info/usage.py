#!/usr/bin/python -tOO


#------------------------------------------------------------------------------------
# Get the usage of cache from output logfile.  
#
# Objective: Split the time horizon into buckets and gather the observations about output
# from each peer.  For every peer aggregate and get an average over the time bucket.  Then
# get median, top 5%, bottom 5%, mix and max (5 items) to give users a feel of what is happening
# here
# 
#
# SENDER=33435b57ecf77b4226615e211ea507e2  TIME=2764837  NUMDEST=1 OVERHEAD=534
# BASEOVERHEAD=948 SIZE=3961  COMPLETION=0.100000 CACHENMESG=10 CACHENBYTES=25487


 

from get_key_val import get_key_val 
import string
import re




class usage(get_key_val):

   def __init__(self, fd, listofkeys, factor):
      self.factor = factor
      self.timeddata = {}
      get_key_val.__init__(self, fd,  listofkeys)
      
      
   def gettimebucket(self, seconds):
      return int(seconds)/self.factor


   def getvalueofinterest(self, values):
      return int(values['TIME']) 

   
   def gather(self):
      while self.data() is not None:
         try:
            nmessages = self.getvalueofinterest(self.values)
            tindex = self.gettimebucket(self.values['TIME'])
            sender = self.values['SENDER']

            if tindex not in self.timeddata:
               self.timeddata[tindex] = {}
            if sender not in self.timeddata[tindex]:
               self.timeddata[tindex][sender] = []
            self.timeddata[tindex][sender] = self.timeddata[tindex][sender] + [nmessages]
         except:
            pass

   def report(self):
      sortedbytime = [] 
      for bucket in self.timeddata.keys():
         distribution = [] 
         self.values = self.timeddata[bucket]

         for sender in self.values.keys():
            total = 0
            for obs in self.values[sender]:
               total += obs
            average = obs/len(self.values[sender]) 
            distribution.append(average)
            
         distribution.sort()
         count = len(distribution)
         median = distribution[count/2]
         minimum = distribution[0]
         maximum = distribution[count-1]
         # print distribution 
         # b = s/f i.e. s = b*f
         seconds = bucket*self.factor 
         sortedbytime = sortedbytime + [ (bucket, seconds, median, minimum, maximum) ]
         
      sortedbytime.sort( lambda x,y: cmp(x[0],y[0]) )

      for x in sortedbytime:
         print '%d %d %d %d' % (x[1], x[2], x[3], x[4])   
            



if __name__ == "__main__":
    import sys
    if len(sys.argv) <= 1 :
        print 'Usage : %s <logfile>' % sys.argv[0]
        sys.exit(1)

    listofkeys = ('SENDER' , 'TIME' , 'CACHENMESG' , 'CACHENBYTES') 
    factor =  86400/3 
    fd = open( sys.argv[1] )
    c = usage(fd, listofkeys, factor)
    c.gather()
    c.report() 
