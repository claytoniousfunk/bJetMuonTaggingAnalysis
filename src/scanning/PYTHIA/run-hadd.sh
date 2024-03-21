#!/bin/bash

# prompt user for output file name
echo "output file name:"
read OUTPUT_FILE_NAME
# prompt user for input file directory
echo "input file directory:"
read INPUT_FILE_DIRECTORY

#run hadd
echo "running hadd..."
START_TIME=$(date)
echo "-- start: $START_TIME"

hadd -j 8 -v 0 $OUTPUT_FILE_NAME $INPUT_FILE_DIRECTORY/*.root

END_TIME=$(date)
echo "-- end: $END_TIME"
echo "done. file saved as $OUTPUT_FILE_NAME"


