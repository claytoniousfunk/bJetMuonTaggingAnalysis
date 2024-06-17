#!/bin/bash

for i in {801..987}

do
    
    root -l -q "PYTHIA_skim_simple.C($i)"

done

