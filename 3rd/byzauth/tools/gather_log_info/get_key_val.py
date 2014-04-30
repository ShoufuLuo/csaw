#!/usr/bin/python -tOO


import string
import re



class get_key_val:

    def __init__(self, fp, keyset):
        self.fp = fp
        self.keyset = keyset
        self.patterns = {}  
        for key in self.keyset:
            self.patterns[key] = re.compile( r'%s=(\S*)(\s*)' % key)
            #print  r'%s=(\S*)(\s*)' % key
            #print repr(self.patterns[key])
            
    def data(self):
        while 1:
            line = self.fp.readline()
            #print line
            if len(line) == 0:
                return None 

            count = 0
            self.values = {} 
            for key in self.keyset:
                m = self.patterns[key].search(line)
                if m is not None :
                    #print m.group(1) 
                    self.values[key] = m.group(1)
                    count = count + 1

            if count == len(self.keyset):
                return self.values 

        
        
                

if __name__ == "__main__":
    import sys
    if len(sys.argv) <= 2 :
        print 'Usage : %s <key1> <key2> ... ' % sys.argv[0]
        sys.exit(1)

    file = sys.stdin 
    object = get_key_val(file, sys.argv[1:])

    while object.data() is not None:
        s = ''
        for key in sys.argv[1:]:
            s = '%s %s' % (s, object.values[key])
        print s

