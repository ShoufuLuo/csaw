#!/usr/bin/python -tOO


from usage import usage


class cachenmesg(usage) :

    def getvalueofinterest(self, values) :
        return int(values['CACHENMESG'])





if __name__ == "__main__":
    import sys
    if len(sys.argv) <= 1 :
        print 'Usage : %s <logfile>' % sys.argv[0]
        sys.exit(1)

    listofkeys = ('SENDER' , 'TIME' , 'CACHENMESG' ) 
    factor =  86400
    fd = open( sys.argv[1] )
    c = cachenmesg(fd, listofkeys, factor)
    c.gather()
    c.report() 


