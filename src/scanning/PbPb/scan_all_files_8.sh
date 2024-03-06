#!/bin/bash

# N = 7176 for PbPb SingleMuon
# N = 1476 for PbPb HardProbes

for i in {7001..7176}

do

    root -l -q "PbPb_scan.C($i)"

done

      


