#!/bin/sh

for file in $(ls maps/bad/*); do
	./cub3D "$file"
	res=$?
	if [ $res -ne 1 ]; then
		printf "SUCCESS ON FILE <%s>\n\n" "$file"
	fi
done;
