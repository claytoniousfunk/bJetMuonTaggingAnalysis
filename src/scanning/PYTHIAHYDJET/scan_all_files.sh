#!/bin/bash

# N = 7202 for PH DiJet

for i in {1..384}

do

    root -l -q "PYTHIAHYDJET_scan.C($i)"

done

      


