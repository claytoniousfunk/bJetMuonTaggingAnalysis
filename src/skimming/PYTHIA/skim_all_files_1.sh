#!/bin/bash

for i in {1..500}

do
    
    root -l -q "PYTHIA_skim_simple.C($i)"

done

