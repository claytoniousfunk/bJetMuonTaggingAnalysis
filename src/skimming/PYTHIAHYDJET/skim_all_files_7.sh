#!/bin/bash


for i in {6001..7000}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
