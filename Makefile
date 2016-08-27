LIB_LAYOUT_SRC = $(wildcard src/*.cpp)
LIB_LAYOUT_OBJ = $(LIB_LAYOUT_SRC:.cpp=.o)

LAYOUT_SRC = $(wildcard support/*.cpp)
LAYOUT_OBJ = $(LAYOUT_SRC:.cpp=.o)

TEST_SRC = $(wildcard test/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

INCLUDES += -I/usr/lib/llvm-3.8/include
CXXFLAGS += -Wall
LDFLAGS += -L/usr/lib/llvm-3.8/lib
LIBS += -lclang

CXX = clang++

.SUFFIXES: .cpp

all: layout test

layout: $(LAYOUT_OBJ) $(LIB_LAYOUT_OBJ)
	$(CXX) $(LDFLAGS) -o layout $(LAYOUT_OBJ) $(LIB_LAYOUT_OBJ) $(LIBS)

test: $(TEST_OBJ) $(LIB_LAYOUT_OBJ)
	$(CXX) $(LDFLAGS) -o layout_test $(TEST_OBJ) $(LIB_LAYOUT_OBJ) $(LIBS)

.cpp.o:
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_LAYOUT_OBJ) $(LAYOUT_OBJ) $(TEST_OBJ) layout layout_test Makefile.bak
