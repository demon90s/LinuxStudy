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

exit 0
