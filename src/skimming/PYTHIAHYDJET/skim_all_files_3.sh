#!/bin/bash


for i in {2001..2923}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
