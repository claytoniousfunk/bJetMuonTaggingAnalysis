#!/bin/bash

for i in {1101..1163}

do

    root -l -q "PYTHIA_scan.C($i)"

done
