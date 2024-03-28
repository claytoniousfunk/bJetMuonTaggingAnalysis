#!/bin/bash

for i in {1001..1443}

do
    
    root -l -q "PYTHIA_skim_simple.C($i)"

done

