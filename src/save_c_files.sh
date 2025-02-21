#!/bin/bash

output_file="output.txt"
> $output_file  # Clear the output file

for file in *.c; do
    echo "Saving contents of $file" >> $output_file
    cat "$file" >> $output_file
    echo -e "\n\n" >> $output_file  # Add some spacing between files
done
