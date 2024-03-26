#!/bin/bash

# N = 7202 for PH DiJet
# N = 6863 for PH DiJet withGS

for i in {6501..6863}

do

    root -l -q "PYTHIAHYDJET_scan.C($i)"
    #root -l -q "PYTHIAHYDJET_scan_muonReco.C($i)"

done

      


