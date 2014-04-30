
TARGET = libproxy.a

OBJECTS = PinoComment.o PinoPacket.o PinoPacketReceiver.o PinoPacketSender.o PinoField.o

CXXFLAGS = -I./include -fPIC

LDFLAGS = -lcrypto -L./ -lproxy -L../../../chimera/src -lchimera

ifndef release
CXXFLAGS += -g -Wall -fstack-protector-all -DDEBUG
else
CXXFLAGS += -O3
endif

all : $(TARGET) 

test: $(TARGET)
	g++ test.c -I../../../chimera/include $(CXXFLAGS) $(LDFLAGS) -o test

$(TARGET) : $(OBJECTS) 
	ar cru $(TARGET) $(OBJECTS)

clean : 
	rm -rf *.o $(TARGET) $(OBJECTS) test.o test *.dSYM





