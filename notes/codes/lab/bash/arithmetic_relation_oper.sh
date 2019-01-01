#! /bin/bash

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

main()
{
	example
}

main
