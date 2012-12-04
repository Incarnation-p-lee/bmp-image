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

all:$(TAR)


$(TAR):$(OBJ)
	echo $(OBJ)
	$(CC) $(INC) $(LF) -o $@ $^

$(OBJ):%.o:%.c
	$(CC) $(INC) $(CF) -o $@ $<

.INTERMEDIATE:$(OBJ)
