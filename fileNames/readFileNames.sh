#!/bin/bash

# Prompt the user for the number of directories
echo "Enter the number of directories: "
read numDirectories

# Prompt the user for each directory
for i in $(seq 1 $numDirectories)
do
  echo "Enter directory path $i: "
  read directories[$i]
done

# Save the list of files in each directory, with their full paths, to a single text file
for directory in ${directories[@]}
do
  find $directory -type f >> all-files.txt
done

echo "List of files with full paths saved to all-files.txt"

