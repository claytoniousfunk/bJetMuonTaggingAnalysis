#!/bin/bash

# N = 7176 for PbPb SingleMuon

for i in {6501..7000}

do

    root -l -q "PbPb_scan.C($i)"

done

      


