#! /bin/bash

# wc 可以统计文件的单词数量、行数、字节数

example1()
{
	# 输出文件的单词数量、行数、字节数
	wc --words --lines --bytes <<  !TEST_FILE!
hello wc
hi bash
!TEST_FILE!
}

main()
{
	example1
}

main
