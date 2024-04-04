#!/bin/bash

# Prompt user for directory path
echo "Enter starting file number:"
read FILE_NUMBER_START
echo "Enter ending file number:"
read FILE_NUMBER_END


for((i=FILE_NUMBER_START; i <= FILE_NUMBER_END; i++)) ; 

do

    root -l -q "PbPb_scan.C($i)"

done

      


