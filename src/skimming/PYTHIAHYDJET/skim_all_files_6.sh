#!/bin/bash


for i in {5001..6000}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
