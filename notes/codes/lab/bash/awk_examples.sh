#! /bin/bash -x

# awk 扫描一个模式，并对符合的模式执行一个动作
# awk 以行为处理单位，然后根据相应的命令，来处理文本

# 输出匹配的行
example1()
{
	# 输出文件中存在 test 的行
	awk '/test/ {print}' << !TEST_FILE!
test
test123
123test
tteesstt
!TEST_FILE!

	# 输出第二个字符串等于WOW的行
	awk '$2=="Wow" {print}' << !TEST_FILE!
nihao www
Hello Wow BBB
foo xxx lll
Bird Wow hei
!TEST_FILE!
}

# 输出分割字符串，默认采取空白分割，使用 -F 'X' 或 FS='X' 表示用 X 分割
# $0 代表整个行 $1,$2,$3... 分别代表第几个子串
example2()
{
	# 输出每行第二个子串
	awk '{print $2}' << !TEST_FILE!
abc world hello
uuid moc c++
welldown GOOD bug
!TEST_FILE!

	# 输出每行第二个子串，使用的是:分割
	awk -F ':' '{print $2}' << !TEST_FILE!
abc:world:hello
uuid:moc:c++
welldown:GOOD:bug
!TEST_FILE!
}

main()
{
	example1
	#example2
}

main
