#!/bin/bash

STARTGROUP=0
ENDGROUP=0
j=0

for i in {1..60}

do
    
    let j=$i-1

    if [ $i -eq 1 ] ; then
	let STARTGROUP=0
	let ENDGROUP=20

    elif [ $i -ne 60 ] ; then
	let STARTGROUP=20*$j+1
	let ENDGROUP=20*i
    
    elif [ $i -eq 60 ] ; then
	let STARTGROUP=20*$j+1
	let ENDGROUP=1193
    fi

    root -l -q "pp_skim.C($i,$STARTGROUP,$ENDGROUP)"

done

