#!/bin/sh

for file in $(ls maps/bonus/good/*); do
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./cub3D "$file"
	res=$?
	if [ $res -ne 0 ]; then
		printf "REJECTING FILE <%s>\n\n" "$file"
	fi
done;
