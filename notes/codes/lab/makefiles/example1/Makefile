# Makefile 例子

# Which compiler
CC = gcc

# Where to install
INSTDIR = ./bin

# Where are include files kept
INCLUDE = .

# Options for development
CFlags = -g -Wall

# Options for release
# CFLAGS = -O -Wall

LIBCORE = libcore.a

myapp: main.o bar.o foo.o $(LIBCORE)
	$(CC) -o myapp main.o bar.o foo.o lib/$(LIBCORE)

# 进入子目录构建
$(LIBCORE):
	(cd lib;$(MAKE))

# Use: gcc -MM *.c 自动生成依赖关系
bar.o: bar.c bar.h common.h lib/core.h
foo.o: foo.c foo.h common.h lib/core.h
main.o: main.c foo.h common.h bar.h

clean:
	-rm -f *.o myapp;\
	cd lib;\
	make clean;\
	cd ..

install: myapp
	@mkdir -p $(INSTDIR) &&\
	if [ -d $(INSTDIR) ];\
		then\
		cp myapp $(INSTDIR);\
		chmod a+x $(INSTDIR)/myapp;\
		chmod og-w $(INSTDIR)/myapp;\
		echo "Installed in $(INSTDIR)";\
	fi
