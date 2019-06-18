#!/bin/bash

#check if we have the right arguments
if [ "$#" -ne 2 ]
then
    echo "Argument error:" 
    echo "./memtrap.sh <Ram in GB> <Number of processes>"
    exit 1
fi

close_memorytrap ()
{
    for i in $(seq 1 `jobs | wc -l`);
    do
        echo "killing: %$i"
        kill %$i
    done
}

RAM=$(($1 / $2))
NUMp=$2
TOTAL=$(($RAM * $NUMp))

echo -n "Start $NUMp processes consuming a total of $TOTAL Gb ram [y/n]: "
read -n 1 -r REPLY
if [[ ! $REPLY =~ ^[Yy]$ ]]
then
    echo "" #clean output
else
for i in $(seq 1 $NUMp)
    do
        #strip out Enter line
        ./memorytrap $RAM | grep -v Press &
    done 
fi

echo 
echo "Wait for memtraps..."
read -p "Press 'Enter' to release memory... "
close_memorytrap
