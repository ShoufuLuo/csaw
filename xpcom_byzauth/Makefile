
include ../make.def

MOZILLA_ZLIB = ./zlib/

CPPFLAGS += -I$(BYZAUTH_LIB)/libbpka
LDFLAGS += -lcrypto -L$(BYZAUTH_LIB)/libbpka -lbpka -L$(MOZILLA_ZLIB) -lmozz -L$(BOOST_LIB) -lboost_serialization

FILES = ByzauthAdapterImpl.cpp ByzauthModule.cpp base64.cpp

TARGET = libbyzauth.$(DYLIB_SUFFIX) 

build: IByzauthAdapter.h  IByzauthAdapter.xpt $(FILES)
	$(MAKE) -C $(MOZILLA_ZLIB)
	$(CXX) $(GECKO_DEFINES) $(FILES) -o $(TARGET) $(CPPFLAGS) $(GECKO_CONFIG_INCLUDE) $(GECKO_INCLUDES) $(LDFLAGS) $(GECKO_LDFLAGS) 	
	cp $(TARGET) IByzauthAdapter.xpt ../components/
	rm -rf manifest
	echo "interfaces		IByzauthAdapter.xpt " >> manifest
	echo "binary-component 	$(TARGET)" >> manifest
	echo "category		profile-after-change	ByzantineAuthentication	@rutgers.edu/XPCOM/ByzauthAdapter;1" >> manifest

IByzauthAdapter.h :  IByzauthAdapter.idl
	$(GECKO_SDK_PATH)/bin/xpidl -m header -I$(GECKO_SDK_PATH)/idl/  IByzauthAdapter.idl 

IByzauthAdapter.xpt :  IByzauthAdapter.idl
	$(GECKO_SDK_PATH)/bin/xpidl -m typelib -I$(GECKO_SDK_PATH)/idl/  IByzauthAdapter.idl 

clean:
	make clean -C $(MOZILLA_ZLIB)
	rm -rf IByzauthAdapter.xpt  IByzauthAdapter.h *.o *.so *~ a.out *.dylib *.dSYM
	rm -f $(TARGET) 
