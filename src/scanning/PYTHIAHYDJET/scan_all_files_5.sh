#!/bin/bash

# N = 7202 for PH DiJet
# N = 3472 for PH DiJet w/ WTA
# N = 4257 for PH BJet
# N = 888 for PH MuJet

for i in {2001..2500}

do

    root -l -q "PYTHIAHYDJET_scan.C($i)"
    #root -l -q "PYTHIAHYDJET_scan_muonReco.C($i)"

done

      

