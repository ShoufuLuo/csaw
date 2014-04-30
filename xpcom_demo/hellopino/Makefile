
TARGET = libpino.a

OBJECTS = hellopino.o

CXXFLAGS += -fPIC

all : $(TARGET) 

$(TARGET) : $(OBJECTS) 
	ar cru  $(TARGET)  $(OBJECTS)    

clean : 
	rm -f *~ $(TARGET) $(OBJECTS) 


