#!/bin/bash

echo ""
echo "Plot SingleMuon jetPt distribution in PYTHIA and pp:"
echo ""

root -l -q '../plots/jetPt/plotJetPt_fineCentBins.C(1,0,0,0,0,1,0,0)'

echo ""
echo "Plot SingleMuon jetPt distribution in PYTHIA+HYDJET 50-80% and PbPb  50-80%:"
echo ""

root -l -q '../plots/jetPt/plotJetPt_fineCentBins.C(0,1,0,0,0,1,0,0)'

echo ""
echo "Plot SingleMuon jetPt distribution in PYTHIA+HYDJET 30-50% and PbPb  30-50%:"
echo ""

root -l -q '../plots/jetPt/plotJetPt_fineCentBins.C(0,0,1,0,0,1,0,0)'

echo ""
echo "Plot SingleMuon jetPt distribution in PYTHIA+HYDJET 10-30% and PbPb  10-30%:"
echo ""

root -l -q '../plots/jetPt/plotJetPt_fineCentBins.C(0,0,0,1,0,1,0,0)'

echo ""
echo "Plot SingleMuon jetPt distribution in PYTHIA+HYDJET 0-10% and PbPb  0-10%:"
echo ""

root -l -q '../plots/jetPt/plotJetPt_fineCentBins.C(0,0,0,0,1,1,0,0)'


echo ""
echo "Copying plots to Analysis Note folder"
echo ""
 
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/SingleMuon/pp/jetPt_SingleMuon_pp_mu12.pdf /home/clayton/Analysis/AN-23-055/figures_updated/jetPt/jetPt_SingleMuon_pp_mu12.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/SingleMuon/C4/jetPt_SingleMuon_C4_mu12.pdf /home/clayton/Analysis/AN-23-055/figures_updated/jetPt/jetPt_SingleMuon_C4_mu12.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/SingleMuon/C3/jetPt_SingleMuon_C3_mu12.pdf /home/clayton/Analysis/AN-23-055/figures_updated/jetPt/jetPt_SingleMuon_C3_mu12.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/SingleMuon/C2/jetPt_SingleMuon_C2_mu12.pdf /home/clayton/Analysis/AN-23-055/figures_updated/jetPt/jetPt_SingleMuon_C2_mu12.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/SingleMuon/C1/jetPt_SingleMuon_C1_mu12.pdf /home/clayton/Analysis/AN-23-055/figures_updated/jetPt/jetPt_SingleMuon_C1_mu12.pdf
