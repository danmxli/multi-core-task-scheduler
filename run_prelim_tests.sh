#!/bin/bash

for infile in *.in; do
    outfile="${infile%.in}.out"
    tempout="temp.out"
    
    echo "Running test: $infile"
    valgrind --leak-check=full -s ./a.out < "$infile" > "$tempout"
    
    if diff -u "$tempout" "$outfile" > diff.log; then
        echo "Test passed!"
    else
        echo "Test failed! Here's what's different:"
        cat diff.log
    fi
    echo "-----------------------"
done

# Cleanup
rm temp.out diff.log