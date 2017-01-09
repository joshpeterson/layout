ifeq ($(OS),Windows_NT)
  uname_S := Windows
else
  uname_S := $(shell uname -s)
endif

ifeq ($(uname_S), Darwin)
  LDFLAGS += -L/usr/local/opt/llvm@3.8/lib/llvm-3.8/lib
  INCLUDES += -I/usr/local/opt/llvm@3.8/lib/llvm-3.8/include
endif

ifeq ($(uname_S), Linux)
  LDFLAGS += -L/usr/lib/llvm-3.8/lib
  INCLUDES += -I/usr/lib/llvm-3.8/include
  TEST_LIBS += -lstdc++fs
endif

LAYOUT_SRC = $(wildcard src/*.cpp)
LAYOUT_OBJ = $(LAYOUT_SRC:.cpp=.o)

EXE_SRC = $(wildcard exe/*.cpp)
EXE_OBJ = $(EXE_SRC:.cpp=.o)

TEST_SRC = $(wildcard test/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

LIBS += -lclang
CXXFLAGS += -Wall -Werror -fno-rtti -std=c++14

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
	$(CXX) $(LDFLAGS) -o layout_test $(TEST_OBJ) $(LAYOUT_OBJ) $(LIBS) $(TEST_LIBS)

.cpp.o:
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(LAYOUT_OBJ) $(EXE_OBJ) $(TEST_OBJ) layout layout_test Makefile.bak
