#!/bin/bash

# N = 7176 for PbPb SingleMuon

for i in {5001..5500}

do

    root -l -q "PbPb_scan.C($i)"

done

      


