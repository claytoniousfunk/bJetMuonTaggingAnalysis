#!/bin/bash

# N = 7176 for PbPb SingleMuon
# N = 1476 for PbPb HardProbes

for i in {501..1000}

do

    root -l -q "PbPb_scan.C($i)"

done

      


