#!/bin/bash

cat "$1" | cut -f1 -d"#" > parsed.txt
sed '/^$/d' parsed.txt > parsed-blank.txt
cat parsed-blank.txt | awk '{ gsub(/[ ]+/,""); print }' > parsed-space.txt
for line in $(cat parsed-space.txt);
do IFS=',';
read -a strarr <<< "$line";
for val in "${strarr[@]}";
do
./firewall.exe "$val";
done > temp.txt
sort temp.txt | uniq -c | awk '{print $2, $1}';
sleep 20;
done > out.txt

rm parsed.txt parsed-blank.txt parsed-space.txt