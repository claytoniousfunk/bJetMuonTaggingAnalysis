#!/bin/bash

# N = 7202 for PH DiJet
# N = 3472 for PH DiJet w/ WTA
# N = 4257 for PH BJet
# N = 2923 for PH MuJet

for i in {6601..6750}

do

    root -l  -b -q "PYTHIAHYDJET_scan.C($i)"
    #root -l -q "PYTHIAHYDJET_scan_muonReco.C($i)"

done

      


