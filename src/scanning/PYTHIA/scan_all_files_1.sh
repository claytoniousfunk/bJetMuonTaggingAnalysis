#!/bin/bash

# N = 1443 for PYTHIA DiJet

for i in {1..500}

do

    root -l -q "PYTHIA_scan.C($i)"
    #root -l -q "PYTHIA_scan_response.C($i)"

done

      


