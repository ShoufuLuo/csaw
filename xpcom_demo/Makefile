
include ../make.def

CORE_LIB = ./hellopino
CPPFLAGS += -I$(CORE_LIB)

LDFLAGS += -L$(CORE_LIB) -lpino

FILES = helloxpcomImpl.cpp helloxpcomModule.cpp

TARGET = libhxpdemo.$(DYLIB_SUFFIX)

build: ihelloxpcom.h  ihelloxpcom.xpt $(FILES)
	$(CXX) $(GECKO_DEFINES) $(FILES) -o $(TARGET) $(CPPFLAGS) $(GECKO_CONFIG_INCLUDE) $(GECKO_INCLUDES) $(LDFLAGS) $(GECKO_LDFLAGS)
	cp $(TARGET) ihelloxpcom.xpt ../components/
	rm -rf manifest
	echo "interfaces	ihelloxpcom.xpt" >> manifest
	echo "binary-component	$(TARGET)" >> manifest
	echo "category	profile-after-change helloxpcom @pinocchio.com/XPCOM/Demo;1" >> manifest

ihelloxpcom.h: ihelloxpcom.idl
	$(GECKO_SDK_PATH)/bin/xpidl -m header -I$(GECKO_SDK_PATH)/idl/ ihelloxpcom.idl 

ihelloxpcom.xpt: ihelloxpcom.idl
	$(GECKO_SDK_PATH)/bin/xpidl -m typelib -I$(GECKO_SDK_PATH)/idl/  ihelloxpcom.idl 

clean :
	rm -f  ihelloxpcom.xpt  ihelloxpcom.h *.o *.so *~ a.out *.dylib test

test:
	$(CXX) -Wl,-z,defs -I$(CORE_LIB) test.c -o test -L$(CORE_LIB) -lpino


