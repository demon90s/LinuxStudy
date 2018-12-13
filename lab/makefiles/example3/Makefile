# 使用特殊的宏定义
# $? 当前依赖文件列表中比目标文件新的文件
# $@ 当前目标的名字
# $< 当前依赖文件的名字

APP=myapp

# 之所以不用 $? 是因为链接时候所有的目标文件都需要链接
$(APP): foo.o bar.o main.o
	gcc -g -Wall -o $@ foo.o bar.o main.o 

bar.o: bar.c bar.h
foo.o: foo.c foo.h
main.o: main.c bar.h foo.h

.SUFFIXES:	.c
.c.o:
	gcc -g -Wall -o $@ -c $<

clean:
	-rm -f *.o $(APP)
