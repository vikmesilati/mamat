#!/bin/bash

if [[ $# -eq 0  ]]; then
	echo "Wrong number of arguments" >&2
	exit 1
fi

if [[ ! -f "./$1.txt" ]]; then
	echo "Course not found" >&2
	exit 1
fi

if [[ -d "./$1_stat" ]]; then
	rm -rf ./$1_stat
fi

mkdir ./$1_stat

awk '{print $2}' ./$1.txt | sed '1d' > ./$1_stat/grades.txt

x=$(sed -n '$=' ./$1_stat/grades.txt)

gcc -g -Wall calc_statistics.c -o prog.exe

./prog.exe "./$1_stat/grades.txt" "$x" "./$1_stat/course_statistics.txt"

cat ./$1_stat/course_statistics.txt
