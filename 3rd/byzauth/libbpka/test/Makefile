ifdef cygwin
CXXFLAGS += -I.. -g -Wall -D_DEBUG -DDEBUG
LDFLAGS += -L.. -lbpka -lboost_serialization-gcc-mt -lcrypto -Wl,--allow-multiple-definition -L/usr/lib -lz
else
ifndef release 
CXXFLAGS += -I.. -g -Wall -fstack-protector-all -D_DEBUG -DDEBUG 
LDFLAGS += -L.. -lbpka -lboost_serialization -lcrypto -Wl,--allow-multiple-definition 
else
CXXFLAGS += -I.. -O3
LDFLAGS += -O3 -L.. -lbpka -lboost_serialization -lcrypto -Wl,--allow-multiple-definition
endif
ifdef profile
CXXFLAGS += -pg
LDFLAGS += -pg 
endif
endif



TARGETS = testprotocol2 testprotocol3 analyze_cache testprotocol4 

# test_restart testconfigfile test_clean_protoinit testprotocol_extrasend testprotocol_extrasend_simple
# testbignum testbignum2 testrsa testsend testkeyrep testproofrep testprotocol testprotocol2 testcr testprotocol3

all : $(TARGETS)


trace : 
	rm -rf peerdata bs.txt trace.txt
	../../tools/mail_trace_scripts/synthetic_trace.py 15 4000 > trace.txt
	../../tools/mail_trace_scripts/bootstrapping.py trace.txt 8 balance > bs.txt


test : testprotocol3 trace 
	./testprotocol3 bs.txt trace.txt 8 1000000 100 15

## testsend testrsa trace 
# TODO - check why testsend fails ./testsend
#			testsend: keyrepository.cpp:15: bool KeyRepository::find(const std::string&, KeyInfo&): Assertion `info.until_time > 0' failed. 
#	./testsend
#	./testrsa
# testing testprotocol3 the lazy protocol simulation with a synthentic
# mail trace 
#



testprotocol_extrasend_simple : testprotocol_extrasend_simple.o 
	g++ testprotocol_extrasend_simple.o -o testprotocol_extrasend_simple $(CXXFLAGS)  $(LDFLAGS)


get_mesg_stats :  get_mesg_stats.o
	g++  get_mesg_stats.o $(CXXFLAGS)  $(LDFLAGS) -o get_mesg_stats


testbignum : testbignum.o 
	g++  testbignum.o $(CXXFLAGS)  $(LDFLAGS) -o testbignum 

testbignum2 : testbignum2.o 
	g++  testbignum2.o $(CXXFLAGS)  $(LDFLAGS) -o testbignum2 

testchunkify : testchunkify.o 
	g++  testchunkify.o $(CXXFLAGS)  $(LDFLAGS) -o testchunkify 

testrsa : testrsa.o 
	g++ testrsa.o $(CXXFLAGS)  $(LDFLAGS) -o testrsa

testsend : testsend.o 
	g++ testsend.o $(CXXFLAGS)  $(LDFLAGS) -o testsend

testcr : testcr.o 
	g++ testcr.o $(CXXFLAGS)  $(LDFLAGS) -o testcr 


testkeyrep : testkeyrep.o 
	g++ testkeyrep.o $(CXXFLAGS)  $(LDFLAGS) -o testkeyrep 

testproofrep : testproofrep.o 
	g++ testproofrep.o $(CXXFLAGS)  $(LDFLAGS) -o testproofrep 

testprotocol : testprotocol.o 
	g++ testprotocol.o $(CXXFLAGS)  $(LDFLAGS) -o testprotocol 

testprotocol2: testprotocol2.o 
	g++ testprotocol2.o $(CXXFLAGS)  $(LDFLAGS) -o testprotocol2 



testprotocol3: testprotocol3.o 
	g++ testprotocol3.o $(CXXFLAGS)  $(LDFLAGS) -o testprotocol3


testprotocol4: testprotocol4.o 
	g++ testprotocol4.o $(CXXFLAGS)  $(LDFLAGS) -o testprotocol4


analyze_cache: analyze_cache.o 
	g++ analyze_cache.o $(CXXFLAGS)  $(LDFLAGS) -o analyze_cache

test_restart : test_restart.o 
	g++ test_restart.o $(CXXFLAGS)  $(LDFLAGS) -o test_restart 

testconfigfile : testconfigfile.o 
	g++ testconfigfile.o $(CXXFLAGS)  $(LDFLAGS) -o testconfigfile 


test_clean_protoinit : test_clean_protoinit.cpp
	g++ test_clean_protoinit.cpp $(CXXFLAGS)  $(LDFLAGS) -o test_clean_protoinit 


testprotocol_extrasend : testprotocol_extrasend.cpp 
	g++ testprotocol_extrasend.cpp  $(CXXFLAGS)  $(LDFLAGS)  -o testprotocol_extrasend


test_serialization : test_serialization.cpp 
	g++ -g -o test_serialization test_serialization.cpp 



clean : 
	rm -f *.o *~ core* $(TARGETS) *.log peerdata/* *.cache *.log testsend testrsa
	rm -rf tgs*.data 
	rm -rf peerdata bs.txt trace.txt 

