#!/bin/bash

STARTGROUP=0
ENDGROUP=0
j=0

#for i in {1..6033}
for i in {1..767}

do
    
    root -l -q "pp_skim_simple.C($i)"

done

