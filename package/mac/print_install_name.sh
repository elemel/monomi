otool -L -X $2 | awk '{ print $1 }' | grep /$1\$ || echo none
