#!/bin/bash

# Prompt user for directory path
echo "Enter starting file number:"
read FILE_NUMBER_START
echo "Enter ending file number:"
read FILE_NUMBER_END


for i in {FILE_NUMBER_START..FILE_NUMBER_END}

do

    root -l -q "pp_scan.C($i)"

done

      


