
include ../make.def

PROXY_LIB = ./proxy

CPPFLAGS += -fshort-wchar -I$(CHIMERA_LIB)/include -I$(PROXY_LIB)/include
LDFLAGS += -L$(CHIMERA_LIB)/src -lchimera -L$(PROXY_LIB)/ -lproxy -lpthread -lcrypto

FILES = ChimeraRider.cpp ChimeraRiderModule.cpp proxy.c

TARGET = libchimerard.$(DYLIB_SUFFIX)

build: iChimeraRider.h  iChimeraRider.xpt $(FILES)
	$(MAKE) -C $(PROXY_LIB)
	$(CXX) $(GECKO_DEFINES) $(FILES) -o $(TARGET) $(CPPFLAGS) $(GECKO_CONFIG_INCLUDE) $(GECKO_INCLUDES) $(LDFLAGS) $(GECKO_LDFLAGS)
	cp $(TARGET) iChimeraRider.xpt ../components/
	rm -rf manifest
	echo "interfaces	iChimeraRider.xpt" >> manifest
	echo "binary-component	$(TARGET)" >> manifest
	echo "category	profile-after-change ChimeraRider @ucsb.com/XPCOM/ChimeraRider;1" >> manifest

iChimeraRider.h: iChimeraRider.idl
	$(GECKO_SDK_PATH)/bin/xpidl -m header -I$(GECKO_SDK_PATH)/idl/ iChimeraRider.idl 

iChimeraRider.xpt: iChimeraRider.idl
	$(GECKO_SDK_PATH)/bin/xpidl -m typelib -I$(GECKO_SDK_PATH)/idl/  iChimeraRider.idl 

clean:
	rm -rf  iChimeraRider.xpt iChimeraRider.h *.o *.so *~ a.out *.dylib *.dSYM


