#!/bin/bash

# N = 1443 for PYTHIA DiJet

for i in {901..1000}

do

    root -l -q "PYTHIA_scan.C($i)"

done

      


