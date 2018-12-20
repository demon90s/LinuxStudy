#! /bin/bash

# filename: first.sh
# description: This file looks through all the files in the current directory...

for file in *
do
	if grep -q POSIX $file
	then
		echo $file
	fi
done

exit 0

