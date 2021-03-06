# Makefile for accelerator-toolkit

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
 CC := g++
 LL := ar
endif
ifeq ($(UNAME_S),Darwin)
 CC := llvm-g++
 LL := llvm-ar-mp-3.7
endif

CPP_FILES := $(wildcard src/*.cpp)
CPP_FILES := $(filter-out src/main.cpp, $(CPP_FILES))
CPP_FILES := $(filter-out src/test.cpp, $(CPP_FILES))
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := 
CC_FLAGS := -Wall -std=c++11 -pedantic -O3 -pthread # -g (for debugging)

MAIN_OBJ := obj/main.o
TEST_OBJ := obj/test.o

LIB_NAME := lib/libacctool.a

all: lib main test
	@echo "done"
	
lib: $(OBJ_FILES)
	$(LL) rvs $(LIB_NAME) $^

main: $(OBJ_FILES) $(MAIN_OBJ)
	$(CC) $(CC_FLAGS) $(LD_FLAGS) -o $@ $^

test: $(OBJ_FILES) $(TEST_OBJ)
	$(CC) $(CC_FLAGS) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp src/%.hpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

clean:
	@rm -f obj/*.o lib/*.a *.exe main *.stackdump
	@echo project cleaned

