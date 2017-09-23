#! /bin/bash

# 提交代码到github

show_status() {
	if git status | grep 'nothing to commit'; then
		return 1
	else
		git status
		return 0
	fi
}

commit() {
	git add *
	git commit -m "commit"
	git push origin master
}

main() {
	if ! show_status; then
		return 0
	fi

	echo -e "\n--------------------------\nIs it ok [y/n]: \c"
	read answer

	if [ "$answer" == "y" ]; then
		commit
	fi
}

main

exit 0

