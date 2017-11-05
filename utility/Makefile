EXEC=main
CXXFLAGS=-g -Wall 

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all:$(OBJS)
	g++ -o $(EXEC) $(OBJS)
	@echo build succ
.cpp .o:
	g++ -o $@ -c $<
clean:
	@rm -f $(OBJS) $(EXEC)
