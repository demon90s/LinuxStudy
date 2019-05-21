#! /bin/bash

# tr 可以转换字符

some_words="Hello, World"

echo ${some_words}

# 将所有小写字母转换成大写字母
echo ${some_words} | tr a-z A-Z