#!/bin/bash
# N = 253 for HYDJET
for i in {1..253}
do
    root -l  -b -q "HYDJET_trigger_scan.C($i)"
done

      


