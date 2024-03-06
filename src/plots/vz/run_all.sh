#!/bin/bash

root -l -q 'plot_and_reweight_vz.C(1,0,1,0,0)'
root -l -q 'plot_and_reweight_vz.C(1,0,0,1,0)'
root -l -q 'plot_and_reweight_vz.C(1,0,0,0,1)'
root -l -q 'plot_and_reweight_vz.C(0,1,1,0,0)'
root -l -q 'plot_and_reweight_vz.C(0,1,0,1,0)'
root -l -q 'plot_and_reweight_vz.C(0,1,0,0,1)'
