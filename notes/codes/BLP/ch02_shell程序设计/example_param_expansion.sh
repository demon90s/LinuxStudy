#! /bin/bash

unset foo
echo ${foo:-bar}	# bar

foo=fud
echo ${foo:-bar}	# fud

foo=/usr/bin/X11/startx
echo ${foo#*/}		# usr/bin/X11/startx
echo ${foo##*/}		# startx

bar=/usr/local/ect/local/networks
echo ${bar%local*}	# /usr/local/ect/
echo ${bar%%local*}	# /usr/

# 替换
far=Hello-Every-Body
echo ${far//-/_}	# Hello_Every_Body

# 截取(${var:start:len})
far=123456
echo ${far:0:3}     # 123

exit 0
