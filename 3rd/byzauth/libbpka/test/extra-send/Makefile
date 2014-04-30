# 
# Compute the non eager performance of authentication 
# by permitting the mail clients to eagerly communicate 
# at periodic intervals  
# 


TGSZ=10 
BSGFILE=bsg.dat 
TRACE=mesglog4.txt
KEYSIZE=16 
EAGER_INTERVAL=600 3600 86400 604800 



all : bootstrap genmakefiles 


clean : 
	rm -rf *~ *.dat 


bootstrap : 
	./bootstrapping.py $(TRACE) $(TGSZ) balance > $(BSGFILE) 



genmakefiles: 
	for i in $(EAGER_INTERVAL); \
	do \
		mkdir -p run-"$${i}" ;\
		./genmake.py "$${i}" ../$(BSGFILE) ../$(TRACE) > run-"$${i}"/Makefile ;\
		cp example.conf run-"$${i}" ;\
	done



