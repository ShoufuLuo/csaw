#!/usr/bin/python -tOO


import random 


class synthetic_trace :

    """ get a given number of users and generate sythentic trace of
    mail exchange """
    
    def __init__(self, numusers, nmessages):
        self.numusers = numusers
        self.nmessages = nmessages 
        self.endpoints = () 
        for i in range(0, numusers):
            self.endpoints = self.endpoints + (('endpoint-%d@orgmeta.com' % i) ,)

    def generate(self):
        t = 0
        m = 0
        while m < self.nmessages:
            i = random.randint(0, self.numusers - 1)
            j = random.randint(0, self.numusers - 1)
            if i == j :
                continue
            self.__Write_Message(t, i, j )
            m = m + 1
            t = t + random.randint(1, 3600)

    def __Write_Message(self, t, i, j):
        print '%d 1 mesgid %s %s' % (t, self.endpoints[i], self.endpoints[j]) 
        
            


    
if __name__ == '__main__':
    import sys
    if len(sys.argv) == 1:
        raise AttributeError('usage : %s <numendpoints> <nmessages>' % sys.argv[0])

    st = synthetic_trace(int(sys.argv[1]), int(sys.argv[2]))
    st.generate()


