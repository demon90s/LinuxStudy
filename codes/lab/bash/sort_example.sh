#! /bin/bash

# sort 对行进行排序，默认是升序

example1()
{
	# 输出排序后的行
	sort << !TEST_FILE!
b
c
a
!TEST_FILE!
}

main()
{
	example1
}

main
