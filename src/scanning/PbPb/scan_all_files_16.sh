#!/bin/bash

# N = 7176 for PbPb SingleMuon

for i in {7501..8000}

do

    root -l -q "PbPb_scan.C($i)"

done

      


