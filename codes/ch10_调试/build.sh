#! /bin/bash

# 自动编译源文件的脚本，使用方法：sh build.sh [rebuild | clear]

all_c_files=`ls *.c`
exclude_files=""

is_exclude_file() {
	for file in $exclude_files; do
		if [ "$file" = "$1" ]; then
			return 0
		fi
	done

	return 1
}

main() {
	if [ $1="DEBUG" ]; then
		Debug_flag=DEBUG
	fi

	for c_file in $all_c_files; do
		exe_file=${c_file%%.c*}

		if [ "$1" == "clear" ]; then
			rm -f $exe_file
			continue
		fi

		if is_exclude_file $c_file; then
			continue
		fi

		if [ $exe_file -nt $c_file ] && [ "$1" != "rebuild" ]; then
			continue
		fi

		echo "[BUILDING] $c_file -> $exe_file"
		if [ -n "$Debug_flag" ]; then
			gcc -g -Wall $c_file -o $exe_file -D$Debug_flag -lm
		else
			gcc -g -Wall $c_file -o $exe_file -lm
		fi

		if [ "$?" != "0" ]; then
			return 1
		fi
	done

	return 0
}

main $1

exit $?
