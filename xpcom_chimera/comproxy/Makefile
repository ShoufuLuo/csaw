
TARGET=libproxy.a

OBJECTS = PinoComment.o PinoPacket.o PinoStoreCenter.o 

CXXFLAGS += -I./include -I../../../chimera/include -fPIC
LDFLAGS = -lcrypto -L./ -lproxy -L../../../chimera/src -lchimera

ifndef release
CXXFLAGS += -g -Wall -fstack-protector-all -DDEBUG
else
CXXFLAGS += -O3
endif

all : $(TARGET) 

test: $(TARGET)
	g++ test.c $(CXXFLAGS) $(LDFLAGS) -o test

$(TARGET) : $(OBJECTS) 
	ar cru  $(TARGET)  $(OBJECTS)    


clean : 
	rm -rf *~ $(TARGET) $(OBJECTS) test.o test *.dSYM





