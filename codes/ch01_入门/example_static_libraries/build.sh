#! /bin/bash

# 构建可执行程序

sh build_static_lib.sh
gcc -c program.c
gcc -o program -L. program.o -lfoo

exit 0
