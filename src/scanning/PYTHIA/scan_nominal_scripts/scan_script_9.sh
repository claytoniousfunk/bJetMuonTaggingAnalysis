#!/bin/bash

# N = 1443 for PYTHIA DiJet

for i in {801..900}

do

    root -l -q "PYTHIA_scan.C($i)"

done

      


