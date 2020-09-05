
CC=gcc 


SRCS=./serial.c 
OBJS=$(patsubst %.c,%.o,$(SRCS)) 
INC= -I/usr/include 
NAME=test

 
CFLAGS=-Wall -Wextra  

D_CFLAGS=-DDEBUG -g -O0 $(INC) 

R_CFLAGS=-DNDEBUG -O3 

CFLAGS += -pthread  -I./inc 
LDFLAGS = -L/lib64 -L./lib

LDLIBS = 


all: build 


build: $(OBJS)
	$(CC) $(CFLAGS) $(D_CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME) $(OBJS) 


clean: 
	rm -f *.o $(NAME)
