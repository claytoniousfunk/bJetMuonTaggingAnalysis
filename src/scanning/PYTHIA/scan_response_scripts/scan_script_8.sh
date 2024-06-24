#!/bin/bash

# N = 987 for PYTHIA DiJet withNeutrinos

for i in {701..800}

do

    root -l -q "PYTHIA_scan_response.C($i)"

done

      


