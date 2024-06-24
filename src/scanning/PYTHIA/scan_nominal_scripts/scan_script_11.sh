#!/bin/bash

# N = 1443 for PYTHIA DiJet

for i in {1001..1100}

do

    root -l -q "PYTHIA_scan.C($i)"

done

      


