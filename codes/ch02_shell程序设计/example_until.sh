#! /bin/bash

until who | grep "$1" > /dev/null
do
    echo "Waiting for $1 login"
    sleep 5
done

echo -e '\a'
echo "**** $1 has just logged in ****"

exit 0

