#! /bin/bash -x

# awk 扫描一个模式，并对符合的模式执行一个动作

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
}

main()
{
	example1
}

main
