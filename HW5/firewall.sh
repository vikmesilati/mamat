#!/bin/bash

cat "$1" | cut -f1 -d"#" > parsed.txt
sed '/^$/d' parsed.txt > parsed-blank.txt
cat parsed-blank.txt | awk '{ gsub(/[ ]+/,""); print }' > parsed-space.txt
for line in $(cat parsed-space.txt);
do IFS=',';
read -a strarr <<< "$line";
> temp.txt;
for val in "${strarr[@]}";
do
./firewall.exe "$val" | tee -a temp.txt > /dev/null;
done

sort temp.txt | uniq -c | awk '{if($1 >= 4) print $2;}';
done > out.txt

rm parsed.txt parsed-blank.txt parsed-space.txt