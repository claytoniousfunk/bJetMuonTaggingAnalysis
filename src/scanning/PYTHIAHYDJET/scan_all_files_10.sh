#!/bin/bash

# N = 7202 for PH DiJet

for i in {4501..5000}

do

    root -l -q "PYTHIAHYDJET_scan.C($i)"
    #root -l -q "PYTHIAHYDJET_scan_muonReco.C($i)"

done

      


