#! /bin/bash

# 自动编译源文件的脚本，使用方法：sh build.sh [rebuild | clear]

# CentOS7
#QTDIR=/usr/lib64/qt-3.3
QTDIR=/usr/local/qt-3.3

all_c_files=`ls *.cpp`
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
	for c_file in $all_c_files; do
		exe_file=${c_file%%.c*}

		if [ "$1" = "clear" ]; then
			rm -f $exe_file
			rm -f ${exe_file}.moc
			continue
		fi

		if is_exclude_file $c_file; then
			continue
		fi

		if [ $exe_file -nt $c_file ] && [ "$1" != "rebuild" ]; then
			continue
		fi

		# create moc file for qt program
		if [ -f ${exe_file}.h ]; then
			$QTDIR/bin/moc ${exe_file}.h -o ${exe_file}.moc
		fi

		echo "[BUILDING] $c_file -> $exe_file"
		# CentOS7
		#g++ $c_file -o $exe_file -I$QTDIR/include -L$QTDIR/lib -lqt-mt
		g++ $c_file -o $exe_file -I$QTDIR/include -L$QTDIR/lib -lqt

		if [ "$?" != "0" ]; then
			return 1
		fi
	done

	return 0
}

main $1

exit $?
