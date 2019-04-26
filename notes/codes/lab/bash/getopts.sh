#! /bin/bash

# getopts 命令用于获取命令选项和其参数, 选项由 - 开头, 后面可以跟着一个字符串表示其参数
# 调用一次 getopts opnames opt 后, opt 被设置成下一个选项值, 如果该选项有参数, 那么参数就保存在 OPTARG 中.
# 选项后面跟着: 代表此选项有一个参数, 比如 s: ,代表 -s 后面需要一个参数

version=1
opnames="vs:"

# sh getopts.sh -v -s hello
while getopts ${opnames} opt; do
    case "$opt" in
        v) echo "version is ${version}" ;;
        s) echo "your param is ${OPTARG}" ;;
        *) echo "Usage: ${0} -v|-s param" ;;
    esac
done