#! /bin/bash

# 数组的操作
# 数组的下标从0开始

# 定义数组：array=(Val1 Val2 Val3)
# 修改元素：array[i]=ValA
# 访问元素：${array[i]}
# 数组长度：${#array[@]}

main_func()
{
	array=(Hello World Hi Wow)
	array[1]=Hey

	local i=0
	while [ "$i" != ${#array[@]} ]
	do
		echo ${array[$i]}
		i=$((i + 1))
	done

	return 0
}

main_func $@
