#! /bin/bash

# 启动脚本

./server &

for i in 1 2 3 4 5; do
	./client &
done
