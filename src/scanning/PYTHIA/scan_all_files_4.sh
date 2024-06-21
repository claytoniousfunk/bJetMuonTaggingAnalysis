#!/bin/bash

# N = 1193 for PYTHIA DiJet

for i in {301..400}

do

    root -l -q "PYTHIA_scan.C($i)"
    #root -l -q "PYTHIA_scan_muonReco.C($i)"
    #root -l -q "PYTHIA_scan_response.C($i)"

done

      


