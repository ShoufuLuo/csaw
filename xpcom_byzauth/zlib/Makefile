

TARGET=libmozz.a

OBJECTS= adler32.o compress.o crc32.o deflate.o gzio.o infback.o inffast.o inflate.o \
	inftrees.o trees.o uncompr.o zutil.o


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

all : $(TARGET) 


$(TARGET) : $(OBJECTS) 
	ar cru  $(TARGET)  $(OBJECTS)    

clean : 
	rm -f *~ $(TARGET) $(OBJECTS) 
