#! /bin/bash

tmp_file=/tmp/my_tmp_file_$$

trap 'rm -f $tmp_file' INT
echo creating file $tmp_file
date > $tmp_file

echo "press interrupt (CTRL-C) to interrupt ...."
while [ -f $tmp_file ]
do
	echo "File exists"
	sleep 1
done

echo "The file no longer exists"

trap - INT
echo creating file $tmp_file
date > $tmp_file

while [ -f $tmp_file ]
do
	echo "File exists"
	sleep 1
done

echo "We never get here"

exit 0
