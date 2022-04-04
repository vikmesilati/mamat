#!/bin/bash

wget -q -O 3082 https://www.ynetnews.com/category/3082

cat 3082 | grep -Eo "https://www.ynetnews.com/article/[a-zA-Z0-9]*" | sort -u > articles.txt 
echo $(wc -l articles.txt | awk '{print $1}') >> results.csv

for line in $(cat articles.txt);
do echo -n "$line," >> results.csv;
wget -q -O result.txt $line | cat result.txt | grep "Bennett" > bennet.txt | cat result.txt | grep "Netanyahu" > netanyahu.txt;
x=$(wc -w bennet.txt | awk '{print $1}');
y=$(wc -w netanyahu.txt | awk '{print $1}');
if [[ $x == "0" && $y == "0" ]]; then
	echo "-" >> results.csv
else
	echo "Bennett, $x,Netanyahu, $y" >> results.csv
fi
done 
