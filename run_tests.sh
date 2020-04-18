#! /bin/sh

tests=$(find Build -name "*test")

for t in $tests
do
    valgrind $t
done
