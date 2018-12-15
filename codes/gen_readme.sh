#! /bin/bash

# 创建 README.md 的脚本

filename=README.md
chapters=18

main()
{
	rm -f $filename
	touch $filename

	echo -e "# Linux程序设计\n" >> $filename
	echo -e "学习环境：CentOS 7\n" >> $filename
	echo -e "对于第五章和第六章使用了头 curses.h 和 term.h 中的功能，需要安装 curses 开发包：yum install ncurses-devel.x86_64，并在构建程序时加入链接选项 -lncurses\n" >> $filename
	echo -e "对于第七章的 dbm 库的使用，需要安装 gdbm 开发包：yum install gdbm-devel.x86_64，并在构建程序时加入链接选项 -lgdbm -lgdbm_compat\n" >> $filename
	echo -e "---\n" >> $filename

	# gen exercises
	echo -e "## 实验例程\n" >> $filename
	local i=1
	while [ $i -le $chapters ]; do
		local chapter_prefix=ch$(printf "%.2d\n" $i)
		local chapter_num=$i
		i=$((i+1))

		local chapter_dir=$(ls -d $chapter_prefix* 2>/dev/null)
		if [ "$chapter_dir" == "" ]; then
			continue
		fi

		cd "$chapter_dir"

		local chapter_name="第${chapter_num}章 ${chapter_dir#*_}"
		echo -e "### $chapter_name\n" >> ../$filename

		local c_files=$(ls -f *.c 2>/dev/null)
		for c_file in $c_files; do
			local fname=$(head -1 $c_file)
			local tmp=${fname%%：*}
			if [ "" != "$fname" ] && [ "// 实验" = "$tmp" ]; then
				fname=${fname#*实验：}
				echo -e "[$fname](./$chapter_dir/$c_file)\n" >> ../$filename
			fi
		done

		local sh_files=$(ls -f *.sh 2>/dev/null)
		for sh_file in $sh_files; do
			local fname=$(head -1 $sh_file)
			local tmp=${fname%%：*}
			if [ "" != "$fname" ] && [ "# 实验" = "$tmp" ]; then
				fname=${fname#*实验：}
				echo -e "[$fname](./$chapter_dir/$sh_file)\n" >> ../$filename
			fi
		done

		local make_files=$(ls -f Makefile* 2>/dev/null)
		for make_file in $make_files; do
			local fname=$(head -1 $make_file)
			local tmp=${fname%%：*}
			if [ "" != "$fname" ] && [ "# 实验" = "$tmp" ]; then
				fname=${fname#*实验：}
				echo -e "[$fname](./$chapter_dir/$make_file)\n" >> ../$filename
			fi
		done

		cd ..
	done

}

main $@
