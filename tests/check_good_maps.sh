#!/bin/sh

for file in $(ls maps/good/*); do
	./cub3D "$file"
	res=$?
	if [ $res -ne 0 ]; then
		printf "REJECTING FILE <%s>\n\n" "$file"
	fi
done;
