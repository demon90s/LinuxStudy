#! /bin/bash

# 数组的操作
# 数组的下标从0开始

# 定义数组：array=(Val1 Val2 Val3)
# 修改元素：array[i]=ValA
# 访问元素：${array[i]}
# 数组长度：${#array[@]}

array=(Hello World Hi Wow)

# 数组遍历
traverse_func()
{
	local i=0
	while [ "$i" != ${#array[@]} ]
	do
		echo ${array[$i]}
		i=$((i + 1))
	done
}

# 数组查询 参数1是查询内容，返回 index
find_func()
{
	local i=0
	while [ "$i" != ${#array[@]} ]
	do
		if [ "${array[$i]}" = "$1" ]; then
			return $((i));
		fi
		i=$((i + 1))
	done

	return -1
}

main_func()
{
	array[1]=Hey

	traverse_func

	echo "请输入一个欲查询的内容："
	read str
	find_func $str
	echo "查询到的索引: $?"

	return 0
}

main_func $@
