#!/bin/bash

# N = 987 for PYTHIA DiJet withNeutrinos

for i in {601..700}

do

    root -l -q "PYTHIA_scan_response.C($i)"

done

      


