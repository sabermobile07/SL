CC = gcc
CFLAG =-g -Wall
LDFLAG = -lm -lGLESv2 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lfreetype -Iinclude -I../include
SRC = src
OBJ = obj
SRCS = $(wildcard main.c $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR = bin
BIN = result
# -fPIC -shared -o lib.so    to create shared library

all: $(BIN)

release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $@ $(LDFLAG)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAG) -c $< -o $@ $(LDFLAG)

clean:
	$(RM) -r $(BIN) $(OBJ)/*

run:
	./$(BIN)