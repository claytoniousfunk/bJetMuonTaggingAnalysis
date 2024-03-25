#!/bin/bash


for i in {3001..4000}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
