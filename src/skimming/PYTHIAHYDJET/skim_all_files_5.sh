#!/bin/bash


for i in {4001..5000}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
