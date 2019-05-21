#! /bin/bash

# 方法1
# -lt(<)
# -gt(>)
# -le(<=)
# -ge(>=)
# -eq(==)
# -ne(!=)

example()
{
	rhs=3
	lhs=4
	if [ $rhs -lt $lhs ] ; then
		echo "$rhs < $lhs"
	fi

	rhs=4
	lhs=3
	if [ $rhs -gt $lhs ]; then
		echo "$rhs > $lhs"
	fi

	rhs=4
	lhs=4
	if [ $rhs -le $lhs ]; then
		echo "$rhs <= $lhs"
	fi

	if [ $rhs -ge $lhs ]; then
		echo "$rhs >= $lhs"
	fi

	if [ $rhs -eq $lhs ]; then
		echo "$rhs == $lhs"
	fi

	rhs=0
	lhs=1
	if [ $rhs -ne $lhs ]; then
		echo "$rhs != $lhs"
	fi
}

# 方法2
# 使用 ((expr))
example2()
{
	if ((2 > 1)); then
		echo "2 > 1"
	fi

	if !((2 < 1)); then
		echo "2 < 1 is false"
	fi
}

main()
{
	#example
	example2
}

main
