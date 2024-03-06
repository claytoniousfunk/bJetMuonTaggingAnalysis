#!/bin/bash

# N = 7202 for PH DiJet

for i in {7001..7202}

do

    root -l -q "PYTHIAHYDJET_scan.C($i)"
    #root -l -q "PYTHIAHYDJET_scan_muonReco.C($i)"

done

      


