#!/usr/bin/python -tOO


#------------------------------------------------------------------------------------
#
# Objective: Get the completion time and overhead plots from the 
# eager protocol execution data generated through testprotocol2 
#
# Sample: 
# AUTHSTATUS   SENDER=xxx  TIME=4754715  BASESENT=74  OVERHEAD=47  COMPLETION=1.000000  


 

from get_key_val import get_key_val 
import string
import re
from numpy import array, average, median, max  


EXIT_VALUE=0.80 


class eager_prot(get_key_val):

   def __init__(self, fname):
      self.sent = {} 
      self.overhead = {} 
      self.completion = {} 
      self.ratio = {} 
      self.time = 0 
      get_key_val.__init__( self, 
                            open(fname) , [ 'SENDER', 'TIME' , 
                                            'BASESENT', 'OVERHEAD', 'COMPLETION' ] 
                            ) 




   def process(self): 
      ''' run once and it should be able to gather all the values of interest 
      for processing one log file from eager execution '''
      while self.data() is not None:
         sender = self.values[ 'SENDER' ] 
         assert( self.time >= self.values[ 'TIME' ] ) 
         assert( self.completion[ sender ] <= float(self.values[ 'COMPLETION' ])  ) 
         
         self.time = int(self.values[ 'TIME' ])
         self.completion[ sender ] = float(self.values[ 'COMPLETION' ]) 

         self.sent[ sender ] = int(self.values[ 'BASESENT' ])
         self.overhead[ sender ] = int(self.values[ 'OVERHEAD' ]) 
         if self.sent[ sender ] > 0 :
            self.ratio[ sender ] = self.overhead[ sender ] / float( self.sent[ sender ] ) 
         
         self.update_stats() 
         if self.done():
            self.report() 
            break 

      


   def update_stats(self):
      self.completion_info = self.__get_stats( self.completion ) 
      self.overhead_info = self.__get_stats( self.overhead, True ) 
      self.ratio_info = self.__get_stats( self.ratio, True ) 




   def __get_stats(self, mapofvalues, avoidzeroes = False):
      ''' note that for sending out message stats it makes sense to average
      over non zero because most of the peers have 0 overhead ''' 
      if len(mapofvalues) == 0:
         return (0.0, 0.0, 0.0) 
      if avoidzeroes == False:
         a = array( mapofvalues.values() ) 
         return (average(a) , median(a), max(a))  
      else:
         zero_free_list = [] 
         for (key,value) in mapofvalues.items(): 
            if value > 0:
               zero_free_list.append(value) 
         if len(zero_free_list) == 0:
            return (0.0, 0.0, 0.0)  
         a = array( zero_free_list ) 
         return (average(a) , median(a), max(a)) 

      

   def done(self):
      if self.completion_info[0] > EXIT_VALUE : 
         return True 
      return False
      


   def report(self):
      ''' print time, completion info, and overhead info '''  
      valuelist = (self.time,) + self.completion_info + self.overhead_info + self.ratio_info 
      print '%d\t%f %f %f\t%f %f %f\t%f %f %f\n' % valuelist 




if __name__ == "__main__":
    import sys
    if len(sys.argv) <= 1 :
        print 'Usage : %s <logfile>' % sys.argv[0]
        sys.exit(1)

    object = eager_prot( sys.argv[1] ) 
    object.process() 

