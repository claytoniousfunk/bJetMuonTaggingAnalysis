#!/bin/bash


for i in {8001..8117}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
