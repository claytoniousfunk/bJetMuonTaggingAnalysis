#!/bin/bash


for i in {6001..6184}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
