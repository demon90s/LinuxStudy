#! /bin/bash

// 提交代码到github

show_status() {
	git status
}

commit() {
	git add *
	git commit -m "commit"
	git push origin master
}

main() {
	show_status

	echo -e "\n--------------------------\nIs it ok [y/n]: \c"
	read answer

	if [ "$answer" == "y" ]; then
		commit
	fi
}

main

exit 0

