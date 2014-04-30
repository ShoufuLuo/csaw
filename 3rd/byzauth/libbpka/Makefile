TARGET=libbpka.a 

OBJECTS = bignum.o  byzantineauthenticationadapter.o  byzauthmatrix.o  digest.o  keyrepository.o  messageprocessor.o  peerfactory.o  proofrepository.o  rsa.o  self.o proxypeer.o message.o logger.o messagecache.o publickeyinfectionadapter.o diskmessagecache.o messagecachedebug.o byzantineauthenticationwrapper.o configfile.o 

CXXFLAGS += -I./

ifdef cygwin
CXXFLAGS += -g -Wall -DDEBUG
else

CXXFLAGS += -fPIC
ifndef release
CXXFLAGS += -g -Wall -fstack-protector-all -DDEBUG
else
CXXFLAGS += -O3
endif

endif

ifdef dryrun 
CXXFLAGS += -DDRYRUN
endif

ifdef profile
CXXFLAGS += -pg
LDFLAGS += -pg 
endif

all : $(TARGET) 


$(TARGET) : $(OBJECTS) 
	ar cru  $(TARGET)  $(OBJECTS)    

clean : 
	rm -f *~ $(TARGET) $(OBJECTS) 
	rm -rf doc TAGS
	$(MAKE) -C test clean 

test : $(TARGET)  
	$(MAKE) -C test 


tar : clean
	cd ..; tar --exclude .svn -cvf libbpka.tar libbpka/; mv libbpka.tar libbpka/ 
	gzip --best libbpka.tar 

tags : 
	etags -l c++ *.[ch]*

doc: 
	doxygen 

