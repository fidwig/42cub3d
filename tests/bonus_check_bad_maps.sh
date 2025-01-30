#!/bin/sh

for file in $(ls maps/bonus/bad/*); do
	printf "%s:\n" "$file"
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./cub3D "$file"
	res=$?
	if [ $res -ne 1 ]; then
		printf "SUCCESS ON FILE <%s>\n\n" "$file"
	fi
	printf "\n"
done;
