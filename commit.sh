#! /bin/bash

# 提交代码到github

show_status() {
	git config core.quotepath false

	if git status | grep 'nothing to commit'; then
		return 1
	else
		echo "Changed file(s):"
		git status -s -u
		return 0
	fi
}

commit() {
	git add *
	git commit -m "commit"

	echo "committing ..."
	git push origin master
}

main() {
	rm -fr site

	if ! show_status; then
		return 0
	fi

	echo -e "--------------------------\nIs it ok [y/n]: \c"
	read answer

	if [ "$answer" == "y" ]; then
		commit
		
		python -m mkdocs gh-deploy --force
	fi
}

main

exit 0

