#! /bin/bash

example_func1()
{
    echo "Enter password"
    read trythis

    while [ "$trythis" != "secret" ]; do
        echo "Sorry, try again"
        read trythis
    done
}

# 死循环
example_func2()
{
    while true ; do
        echo "Hi~~~"
        sleep 1
    done
}

main_func()
{
    #example_func1
    example_func2
}

main_func $@