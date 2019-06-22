CC = gcc
CFLAGS = -g -Wall

# how to get it: mysql_config --cflags
MYSQL_INCLUDE = -I/usr/include/mysql

# how to get it: mysql_config --libs
MYSQL_LIB = -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -latomic -ldl

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