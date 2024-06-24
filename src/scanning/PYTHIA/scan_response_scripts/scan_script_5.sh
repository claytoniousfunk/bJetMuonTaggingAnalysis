#!/bin/bash

# N = 987 for PYTHIA DiJet withNeutrinos

for i in {401..500}

do

    root -l -q "PYTHIA_scan_response.C($i)"

done

      


