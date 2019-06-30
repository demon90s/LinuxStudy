CC = gcc
CFLAGS = -g -Wall
MYSQL_INCLUDE = $(shell mysql_config --cflags)
MYSQL_LIB = $(shell mysql_config --libs)

TARGETS = connect1 \
			connect2 \
			insert1 \
			insert2 \
			select1 \
			select2 \
			select3

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $(MYSQL_INCLUDE) -o $@ $< $(MYSQL_LIB)

clean:
	-rm -f $(TARGETS)