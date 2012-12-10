.SUFFIXES:
.SUFFIXES:.h .c .o .out

vpath %.h ./inc

CC=	gcc
TAR=	a.out
CF=	-c -g -Wall
LF=	
SRC=	$(shell find ./src -name "*.c")
OBJ=	$(patsubst %.c,%.o,$(SRC))
INC=	-I./inc 
LIB=    -lm

all:$(TAR)


$(TAR):$(OBJ)
	$(CC) $(INC) $(LF) -o $@ $^ $(LIB)

$(OBJ):%.o:%.c
	$(CC) $(INC) $(CF) -o $@ $<

clean:
	-rm $(TAR)

.INTERMEDIATE:$(OBJ)
