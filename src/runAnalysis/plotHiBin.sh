#!/bin/bash

echo ""
echo "Plot hiBin distribution in PYTHIA+HYDJET and PbPb:"
echo ""

root -l -q '../plots/hiBin/plot_and_reweight_hiBin.C'
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/hiBin/hiBin.pdf /home/clayton/Analysis/AN-23-055/figures_updated/hiBin/hiBin.pdf
