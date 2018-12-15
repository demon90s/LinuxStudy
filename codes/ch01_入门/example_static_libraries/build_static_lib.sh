#! /bin/bash

# 构建静态库

gcc -c bill.c fred.c
ar crv libfoo.a bill.o fred.o

exit 0
