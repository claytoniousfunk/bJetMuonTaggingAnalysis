#!/bin/bash

for i in {1201..1300}

do

    root -l -q "PYTHIA_scan.C($i)"
    #root -l -q "PYTHIA_scan_muonReco.C($i)"

done
