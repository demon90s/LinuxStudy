#! /bin/bash

# source 在当前环境下执行命令
# 它具有一种类似C语言 include 的功能, 可以引入其他模块

source ./colors.sh

[ $? ] && echo "[DEBUG] inport color module succ" || exit 1

set_red_text
echo "Hahaha red red red"
