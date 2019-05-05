#! /bin/bash -x

# sed 是一个非交互式的文本编辑器，或者可以理解为一个过滤器

# 替换文本
example1()
{
	some_text="Hello sed, easy to learn"

	# 将 Hello 替换成 Hi ，然后输出到 stdout
	echo $some_text | sed 's/Hello/Hi/g'
}

# 删除内容
example2()
{
	this_file=$0

	# 输出文件内容，但忽略掉第1行到第12行
	cat $this_file | sed '1,12d'
}

# 显示第几行的内容
example3()
{
	this_file=$0

	# 输出第6到第12行的内容, -n意思是不把原文件内容输出出来, 默认会输出
	cat $this_file | sed -n '6,12p'
}

main()
{
	#example1
	#example2 $0
	example3 $0
}

main $@
