#!/bin/bash

echo ""
echo "Plot vz distribution in PYTHIA and pp:"
echo ""

root -l -q '../plots/vz/plot_and_reweight_vz.C(1,0)'
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/vzReweight/PYTHIA/vzReweight_pp.pdf /home/clayton/Analysis/AN-23-055/figures_updated/vz/vzReweight_pp.pdf

echo ""
echo "Plot vz distribution in PYTHIA+HYDJET and PbPb:"
echo ""

root -l -q '../plots/vz/plot_and_reweight_vz.C(0,1)'
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/vzReweight/PYTHIAHYDJET/vzReweight_PbPb.pdf /home/clayton/Analysis/AN-23-055/figures_updated/vz/vzReweight_PbPb.pdf
