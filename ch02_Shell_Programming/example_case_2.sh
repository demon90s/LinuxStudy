#! /bin/bash

echo "Is it morning? Please enter yes or no"
read timeofday

case "$timeofday" in
    yes | y | YES | Yes) echo "Good morning";;
    n* | N*            ) echo "Good afternoon";;
    *                  ) echo "Sorry, answer not recognized";;
esac

exit 0

