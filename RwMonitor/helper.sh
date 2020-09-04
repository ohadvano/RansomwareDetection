#!/bin/bash

if [ "$1" == "EXE_FILE" ]; then
	file $3  | cut -d":" -f2 | cut -c2-  > $2
elif [ "$1" == "EXE_SDHASH" ]; then
	sdhash -g $3 $4 | cut -d"|" -f3 > $2
fi


