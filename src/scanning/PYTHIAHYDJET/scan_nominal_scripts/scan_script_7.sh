#!/bin/bash

# N = 7202 for PH DiJet
# N = 3472 for PH DiJet w/ WTA
# N = 4257 for PH BJet
# N = 2923 for PH MuJet
# N = 6190 for PH DiJet additionalMC

for i in {6001..7000}

do

    root -l  -b -q "PYTHIAHYDJET_scan.C($i)"

done

      


