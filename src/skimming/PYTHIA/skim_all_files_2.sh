#!/bin/bash

for i in {501..1000}

do
    
    root -l -q "PYTHIA_skim_simple.C($i)"

done

