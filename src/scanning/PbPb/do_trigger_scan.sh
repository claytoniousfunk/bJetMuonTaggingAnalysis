#!/bin/bash
# N = 7176 for PbPb SingleMuon
# N = 1476 for PbPb HardProbes
# N = 218 for PbPb MinBias
for i in {1..218}
do
    root -l -q "PbPb_trigger_scan.C($i)"
done

      


