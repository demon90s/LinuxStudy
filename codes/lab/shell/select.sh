#!/bin/bash

# 使用select制作一个简单的菜单

OPTIONS="Hello Quit"

select opt in $OPTIONS; do
	if [ "$opt" = "Quit" ]; then
		echo done
		exit
	elif [ "$opt" = "Hello" ]; then
		echo "Hello World"
	else
		echo "bad option"
	fi
done
