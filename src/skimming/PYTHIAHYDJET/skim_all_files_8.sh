#!/bin/bash


for i in {7001..8000}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
