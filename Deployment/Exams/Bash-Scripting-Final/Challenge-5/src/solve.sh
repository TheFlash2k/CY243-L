# read a file, create a variable _occurances that will store the number of occurrances of every three lettered word:

file="/opt/random-data.txt"
counter=0
while read -r line
do
    for word in $line
    do
        if [ ${#word} -eq 3 ]
        then
            counter=$((counter+1))
        fi
    done
done < "$file"
echo 120