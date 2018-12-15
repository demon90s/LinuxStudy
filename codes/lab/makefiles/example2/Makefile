# 构建多个目标的例子
#
CC = gcc
CFlags = -g -Wall

all: main1 main2

main1: main1.o
main2: main2.o

main1.o: main1.c
main2.o: main2.c

clean:
	-rm -f *.o main1 main2
