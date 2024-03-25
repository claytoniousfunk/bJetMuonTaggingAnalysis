#!/bin/bash


for i in {1001..2000}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
