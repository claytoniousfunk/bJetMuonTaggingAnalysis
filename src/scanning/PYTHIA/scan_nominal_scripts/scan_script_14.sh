#!/bin/bash

# N = 1443 for PYTHIA DiJet

for i in {1301..1400}

do

    root -l -q "PYTHIA_scan.C($i)"

done

      


