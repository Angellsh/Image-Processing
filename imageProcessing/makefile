CXX = g++
CXXFLAGS = -std=c++11

TARGET = project2.out
SRC_DIR = src
SRC = $(SRC_DIR)/image.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)