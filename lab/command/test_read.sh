#! /bin/bash

# read 从标准输入读取一行内容（或从一个文件流）

# 无选项，读取一行的数据存放到 name ，不包括换行
test_noopt_func()
{
	read name
	echo "$name"
}

# -a aname
# 把输入的内容以空白分隔，分配给数组 aname，变量 aname 在读取前会被 unset
test_opt_a_func()
{
	read -a aname

	local i=0
	while [ "$i" != ${#aname[@]} ]; do
		echo "element $i: ${aname[$i]}"
		i=$((i + 1))
	done
}

# -d delim
# 键入 delim （的首个字符）作为输入的结束，之后传送数据给脚本，而不是键入 enter 后
test_opt_d_func()
{
	read -d "#" name
	echo -e "\nyou enter: "
	echo "$name"
}

# -n nchars
# 读取 nchars 个字符后返回，而不等待完整的输入行，但若启用 delim ，则遇到 delim 会提前返回
test_opt_n_func()
{
	#read -n 3 name
	read -n 3 -d "#" name
	echo -e "\nyou enter: "
	echo "$name"
}

# -N nchars
# 读取 nchars 个字符后返回，而不是等待完整的输入行，除非遇到 EOF 或者读取超时
test_opt_N_func()
{
	read -N 3 name
	echo -e "\nyou enter: "
	echo "$name"
}

# -p prompt
# 读取任何输入之前，在标准错误上显示 prompt ，只有来自终端的输入才会有这个提示
test_opt_p_func()
{
	read -p "your name: " name
	echo -e "you enter: "
	echo "$name"
}

# -r
# 反斜杠不再是转义字符（是普通字符）
test_opt_r_func()
{
	read -r name
	echo "you enter: $name"
}

# -s
# silence 模式，如果输入来自终端，则不回显字符
test_opt_s_func()
{
	echo "Enter password: "
	read -s password
	echo "you enter: $password"
}

# -t timeout
# 设置一个读取超时时间 timeout ，如果在这么长时间内没有读取，则返回失败
# 仅在读取来自终端、管道或特殊文件的输入时有效，从常规文件读取时没有任何效果
# 如果 timeout 为0 ，则指定文件描述符上有输入可用时，返回成功，否则返回失败
test_opt_t_func()
{
	echo "Enter name in 5 seconds: ";
	read -t 5 name
	if [ "$?" != "0" ]; then
		echo "timeout~~"
		return 1
	fi
	echo "you enter: $name"
}

main_func()
{
	#test_noopt_func
	#test_opt_a_func
	#test_opt_d_func
	#test_opt_n_func
	#test_opt_N_func
	#test_opt_p_func
	#test_opt_r_func
	#test_opt_s_func
	test_opt_t_func
}

main_func $@
