#!/bin/bash

for i in {1..60}

do

    root -l -q "PYTHIA_scan.C($i)"

done

      


