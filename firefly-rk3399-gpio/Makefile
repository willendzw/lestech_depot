
CC=gcc 


SRCS=./lock.c 
OBJS=$(patsubst %.c,%.o,$(SRCS)) 
INC= -I/usr/include 
NAME=test

 
CFLAGS=-Wall -Wextra  

D_CFLAGS=-DDEBUG -g -O0 $(INC) 

R_CFLAGS=-DNDEBUG -O3 

CFLAGS += -pthread  -I/home/toybrick/firefly-rk3399-gpio/inc 
LDFLAGS = -L/lib64 -L/home/toybrick/firefly-rk3399-gpio/lib

LDLIBS = -lfireflyrk3399gpio 


all: build 


build: $(OBJS)
	$(CC) $(CFLAGS) $(D_CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME) $(OBJS) 


clean: 
	rm -f *.o $(NAME)
