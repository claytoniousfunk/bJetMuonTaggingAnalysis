#!/bin/bash

# N = 7176 for PbPb SingleMuon
# N = 214 for PbPb MinBias

for i in {1..214}

do

    root -l -q "PbPb_scan.C($i)"

done

