#!/bin/bash

# N = 1443 for PYTHIA DiJet

for i in {1201..1300}

do

    root -l -q "PYTHIA_scan.C($i)"

done

      


