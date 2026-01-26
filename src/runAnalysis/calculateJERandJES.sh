#!/bin/bash

echo ""
echo "Calculate JER and JES in PYTHIA and PYTHIA+HYDJET:"
echo ""

root -l -q '../jetEnergyResolutionCalculator/jetEnergyResolutionCalculator_pt.C(1,0,0,0,0)'
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/jetEnergyResolutionCalculator/figures/sigma_pp.pdf /home/clayton/Analysis/AN-23-055/figures_updated/JER/JER_muTaggedJets_pp_pt.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/jetEnergyResolutionCalculator/figures/mu_pp.pdf /home/clayton/Analysis/AN-23-055/figures_updated/JES/JES_muTaggedJets_pp_pt.pdf

root -l -q '../jetEnergyResolutionCalculator/jetEnergyResolutionCalculator_pt.C(0,1,0,0,0)'
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/jetEnergyResolutionCalculator/figures/sigma_C4.pdf /home/clayton/Analysis/AN-23-055/figures_updated/JER/JER_muTaggedJets_C4_pt.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/jetEnergyResolutionCalculator/figures/mu_C4.pdf /home/clayton/Analysis/AN-23-055/figures_updated/JES/JES_muTaggedJets_C4_pt.pdf

root -l -q '../jetEnergyResolutionCalculator/jetEnergyResolutionCalculator_pt.C(0,0,1,0,0)'
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/jetEnergyResolutionCalculator/figures/sigma_C3.pdf /home/clayton/Analysis/AN-23-055/figures_updated/JER/JER_muTaggedJets_C3_pt.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/jetEnergyResolutionCalculator/figures/mu_C3.pdf /home/clayton/Analysis/AN-23-055/figures_updated/JES/JES_muTaggedJets_C3_pt.pdf

root -l -q '../jetEnergyResolutionCalculator/jetEnergyResolutionCalculator_pt.C(0,0,0,1,0)'
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/jetEnergyResolutionCalculator/figures/sigma_C2.pdf /home/clayton/Analysis/AN-23-055/figures_updated/JER/JER_muTaggedJets_C2_pt.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/jetEnergyResolutionCalculator/figures/mu_C2.pdf /home/clayton/Analysis/AN-23-055/figures_updated/JES/JES_muTaggedJets_C2_pt.pdf

root -l -q '../jetEnergyResolutionCalculator/jetEnergyResolutionCalculator_pt.C(0,0,0,0,1)'
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/jetEnergyResolutionCalculator/figures/sigma_C1.pdf /home/clayton/Analysis/AN-23-055/figures_updated/JER/JER_muTaggedJets_C1_pt.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/jetEnergyResolutionCalculator/figures/mu_C1.pdf /home/clayton/Analysis/AN-23-055/figures_updated/JES/JES_muTaggedJets_C1_pt.pdf
