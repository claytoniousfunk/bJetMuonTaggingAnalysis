#!/bin/bash

# N = 7202 for PH DiJet
# N = 4257 for PH BJet
# N = 888 for PH MuJet

for i in {4001..4500}

do

    root -l -q "PYTHIAHYDJET_scan.C($i)"
    #root -l -q "PYTHIAHYDJET_scan_muonReco.C($i)"

done

      


