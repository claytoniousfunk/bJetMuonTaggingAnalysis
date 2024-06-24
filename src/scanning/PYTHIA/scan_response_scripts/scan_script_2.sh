#!/bin/bash

# N = 987 for PYTHIA DiJet withNeutrinos

for i in {101..200}

do

    root -l -q "PYTHIA_scan_response.C($i)"

done

      


