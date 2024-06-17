#!/bin/bash

for i in {401..600}

do
    
    root -l -q "PYTHIA_skim_simple.C($i)"

done

