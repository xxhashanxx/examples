C = gcc
CXX = g++

SOURCE_CXX = main.cpp
TARGET = main
LDFLAGS_COMMON = -std=c++2a
all:
	$(CXX) $(SOURCE_CXX) $(OBJECTS_C) $(LDFLAGS_COMMON) -o $(TARGET)
clean:
	del /Q *.o $(TARGET) *.exe