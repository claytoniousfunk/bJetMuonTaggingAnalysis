#!/bin/bash

for i in {601..800}

do
    
    root -l -q "PYTHIA_skim_simple.C($i)"

done

