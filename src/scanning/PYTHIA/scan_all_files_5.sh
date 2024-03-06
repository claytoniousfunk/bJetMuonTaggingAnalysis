#!/bin/bash

# N = 1193 for PYTHIA DiJet

for i in {801..1000}

do

    #root -l -q "PYTHIA_scan.C($i)"
    root -l -q "PYTHIA_scan_muonReco.C($i)"

done

      


