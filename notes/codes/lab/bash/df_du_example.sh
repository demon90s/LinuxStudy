#! /bin/bash

# df 输出磁盘占用情况
# -h 表示友好的输出
f_test_df()
{
	df -h
}

# du 输出文件夹的占用情况
# -h 表示友好的输出
# --max-depth=N 表示输出层级
f_test_du()
{
	du -h --max-depth=1 ..
}

f_main()
{
	#f_test_df
	f_test_du
}

f_main $@
