LAYOUT_SRC = $(wildcard src/*.cpp)
LAYOUT_OBJ = $(LAYOUT_SRC:.cpp=.o)

EXE_SRC = $(wildcard exe/*.cpp)
EXE_OBJ = $(EXE_SRC:.cpp=.o)

TEST_SRC = $(wildcard test/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

LDFLAGS += -L/usr/lib/llvm-3.8/lib
LIBS += -lclang

INCLUDES += -I/usr/lib/llvm-3.8/include
CXXFLAGS += -Wall -fno-rtti -std=c++14

DEBUG ?= 1
ifeq ($(DEBUG), 1)
  CXXFLAGS += -g -DDEBUG -DENABLE_FAKING
  LDFLAGS += -g
else
  CXXFLAGS += -O3 -flto
  LDFLAGS += -flto
endif

.SUFFIXES: .cpp

all: layout test

layout: $(EXE_OBJ) $(LAYOUT_OBJ)
	$(CXX) $(LDFLAGS) -o layout $(EXE_OBJ) $(LAYOUT_OBJ) $(LIBS)

test: $(TEST_OBJ) $(LAYOUT_OBJ)
	$(CXX) $(LDFLAGS) -o layout_test $(TEST_OBJ) $(LAYOUT_OBJ) $(LIBS)

.cpp.o:
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(LAYOUT_OBJ) $(EXE_OBJ) $(TEST_OBJ) layout layout_test Makefile.bak
