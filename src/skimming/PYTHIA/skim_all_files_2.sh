#!/bin/bash

for i in {201..400}

do
    
    root -l -q "PYTHIA_skim_simple.C($i)"

done

