#!/usr/bin/python -tOO


from usage import usage


class overhead(usage) :

    def getvalueofinterest(self, values) :
        return int(values['OVERHEAD'])





if __name__ == "__main__":
    import sys
    if len(sys.argv) <= 1 :
        print 'Usage : %s <logfile>' % sys.argv[0]
        sys.exit(1)

    listofkeys = ('SENDER' , 'TIME' , 'OVERHEAD' ) 
    factor =  86400 
    fd = open( sys.argv[1] )
    c = overhead(fd, listofkeys, factor)
    c.gather()
    c.report() 


