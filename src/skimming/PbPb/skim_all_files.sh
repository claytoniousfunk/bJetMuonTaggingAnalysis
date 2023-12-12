#!/bin/bash

STARTGROUP=0
ENDGROUP=0
j=0

for i in {1..359}

do
    
    let j=$i-1

    if [ $i -eq 1 ] ; then
	let STARTGROUP=0
	let ENDGROUP=20

    elif [ $i -ne 359 ] ; then
	let STARTGROUP=20*$j+1
	let ENDGROUP=20*i
    
    elif [ $i -eq 359 ] ; then
	let STARTGROUP=20*$j+1
	let ENDGROUP=7176
    fi

    root -l -q "PbPb_skim.C($i,$STARTGROUP,$ENDGROUP)"

done
