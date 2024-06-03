#!/bin/bash

# N = 1443 for PYTHIA DiJet
# N = 1262 for PYTHIA DiJet response (noRecoJetPtCut)

for i in {1001..1443}

do

    #root -l -q "PYTHIA_scan.C($i)"
    root -l -q "PYTHIA_scan_response.C($i)"

done

      


