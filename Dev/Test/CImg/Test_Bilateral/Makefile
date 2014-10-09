CC=clang++
LIBS=-lreadline -lpthread -lm -lX11
EXEC=test_bilateral
CCFLAGS=-g -Wall -Wextra -pedantic -O2

BIN_DIR=bin
SRC_DIR=src
OBJ_DIR=obj
HEA_DIR=include

all:$(EXEC)

$(EXEC):$(OBJ) main.o
	mkdir -p -v $(BIN_DIR)
	$(CC) $(CCFLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp $(HEA_DIR)/%.h
	mkdir -p -v $(OBJ_DIR)
	$(CC) $(CCFLAGS) -I $(HEA_DIR)/ -o $@ -c $<

$(OBJ_DIR)/main.o:main.cpp
	mkdir -p -v $(OBJ_DIR)
	$(CC) $(CCFLAGS) -I $(HEA_DIR)/ -o $@ -c $<

clean:
	rm -vf $(OBJ_DIR)/*.o

mproper:clean
	rm -rf $(BIN_DIR)/$(EXEC)