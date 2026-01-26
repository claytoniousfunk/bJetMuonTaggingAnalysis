#!/bin/bash

echo ""
echo "Plot SingleMuon jetEta distribution in PYTHIA and pp:"
echo ""

root -l -q '../plots/jetEta/plotJetEta_fineCentBins.C(1,0,0,0,0,1,0,0,80,500)'

echo ""
echo "Plot SingleMuon jetEta distribution in PYTHIA+HYDJET 50-80% and PbPb  50-80%:"
echo ""

root -l -q '../plots/jetEta/plotJetEta_fineCentBins.C(0,1,0,0,0,1,0,0,80,500)'

echo ""
echo "Plot SingleMuon jetEta distribution in PYTHIA+HYDJET 30-50% and PbPb  30-50%:"
echo ""

root -l -q '../plots/jetEta/plotJetEta_fineCentBins.C(0,0,1,0,0,1,0,0,80,500)'

echo ""
echo "Plot SingleMuon jetEta distribution in PYTHIA+HYDJET 10-30% and PbPb  10-30%:"
echo ""

root -l -q '../plots/jetEta/plotJetEta_fineCentBins.C(0,0,0,1,0,1,0,0,80,500)'

echo ""
echo "Plot SingleMuon jetEta distribution in PYTHIA+HYDJET 0-10% and PbPb  0-10%:"
echo ""

root -l -q '../plots/jetEta/plotJetEta_fineCentBins.C(0,0,0,0,1,1,0,0,80,500)'

echo ""
echo "Copying plots to Analysis Note folder"
echo ""
 
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/SingleMuon/pp/jetEta_SingleMuon_pp_mu12.pdf /home/clayton/Analysis/AN-23-055/figures_updated/jetEta/jetEta_SingleMuon_pp_mu12.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/SingleMuon/C4/jetEta_SingleMuon_C4_mu12.pdf /home/clayton/Analysis/AN-23-055/figures_updated/jetEta/jetEta_SingleMuon_C4_mu12.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/SingleMuon/C3/jetEta_SingleMuon_C3_mu12.pdf /home/clayton/Analysis/AN-23-055/figures_updated/jetEta/jetEta_SingleMuon_C3_mu12.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/SingleMuon/C2/jetEta_SingleMuon_C2_mu12.pdf /home/clayton/Analysis/AN-23-055/figures_updated/jetEta/jetEta_SingleMuon_C2_mu12.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/SingleMuon/C1/jetEta_SingleMuon_C1_mu12.pdf /home/clayton/Analysis/AN-23-055/figures_updated/jetEta/jetEta_SingleMuon_C1_mu12.pdf
