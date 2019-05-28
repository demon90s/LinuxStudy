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

example2()
{
	# 输出文件大小的排序
	# -n 表示用数字排序
	# -r 表示逆序（从大到小）
	# -k 5 表示以第5栏排序
	ls -l | sort -nrk 5
}

main()
{
	#example1
	example2
}

main
