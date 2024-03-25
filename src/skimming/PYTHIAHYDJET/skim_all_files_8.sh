#!/bin/bash


for i in {7001..7203}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
