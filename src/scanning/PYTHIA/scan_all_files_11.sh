#!/bin/bash

for i in {1001..1100}

do

    #root -l -q "PYTHIA_scan.C($i)"
    root -l -q "PYTHIA_scan_muonReco.C($i)"

done

      


