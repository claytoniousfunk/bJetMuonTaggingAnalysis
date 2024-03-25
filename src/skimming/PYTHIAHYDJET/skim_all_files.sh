#!/bin/bash

for i in {1..6863}

do
    
    root -l -q "PYTHIAHYDJET_skim_simple.C($i)"

done
