#! /bin/bash

# 字符串比较例程

# 判断大小
# s1 = s2 s1 != s2 s1 < s2 s1 > s2
# 注意点：
# 1. 判断符号两端须有空格
# 2. > < 符号前加\ ，否则可能被解析为重定向
func1()
{
	s1="hello"
	s2="hello"
	s3="hellO"

	if [ "$s1" = "$s2" ]; then
		echo "s1('$s1') equal to s2('$s2')"
	else
		echo "s1('$s1') not equal to s2('$s2')"
	fi

	if [ "$s1" != "$s3" ]; then
		echo "s1('$s1') not equal to s3('$s3')"
	else
		echo "s1('$s1') equal to s3('$s3')"
	fi

	if [ "$s1" \> "$s3" ]; then
		echo "s1('s1') > s3('s3')"
	else
		echo "s1('s1') <= s3('s3')"
	fi

	if [ "$s3" \< "$s1" ]; then
		echo "s3('s3') < s1('s1')"
	else
		echo "s3('s3') >= s1('s1')"
	fi
}

# 判断字符串是否为空
# -n string 不为空则真
# -z string 为空则真
func2()
{
	s1=hello
	s2=

	if [ -n "$s1" ]; then
		echo "s1('$s1') is not empty string"
	fi

	if [ -z "$s2" ]; then
		echo "s2('$s2') is empty string"
	fi
}

main_func()
{
	#func1
	func2
}

main_func
