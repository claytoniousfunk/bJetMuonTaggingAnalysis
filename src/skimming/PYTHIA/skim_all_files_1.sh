#!/bin/bash

for i in {1..200}

do
    
    root -l -q "PYTHIA_skim_simple.C($i)"

done

