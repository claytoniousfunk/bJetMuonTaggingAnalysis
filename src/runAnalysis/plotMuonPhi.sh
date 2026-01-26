#!/bin/bash

echo ""
echo "Plot SingleMuon muonPhi distribution in PYTHIA and pp:"
echo ""

root -l -q '../plots/muonPhi/plotMuonPhi.C(1,0,0,0,0,1,0,80,100)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(1,0,0,0,0,1,0,100,120)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(1,0,0,0,0,1,0,120,150)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(1,0,0,0,0,1,0,150,200)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(1,0,0,0,0,1,0,200,300)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(1,0,0,0,0,1,0,300,500)'

echo ""
echo "Plot SingleMuon muonPhi distribution in PYTHIA+HYDJET 50-80% and PbPb  50-80%:"
echo ""

root -l -q '../plots/muonPhi/plotMuonPhi.C(0,1,0,0,0,1,0,80,100)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,1,0,0,0,1,0,100,120)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,1,0,0,0,1,0,120,150)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,1,0,0,0,1,0,150,200)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,1,0,0,0,1,0,200,300)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,1,0,0,0,1,0,300,500)'

echo ""
echo "Plot SingleMuon muonPhi distribution in PYTHIA+HYDJET 30-50% and PbPb  30-50%:"
echo ""

root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,1,0,0,1,0,80,100)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,1,0,0,1,0,100,120)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,1,0,0,1,0,120,150)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,1,0,0,1,0,150,200)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,1,0,0,1,0,200,300)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,1,0,0,1,0,300,500)'

echo ""
echo "Plot SingleMuon muonPhi distribution in PYTHIA+HYDJET 10-30% and PbPb  10-30%:"
echo ""

root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,1,0,1,0,80,100)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,1,0,1,0,100,120)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,1,0,1,0,120,150)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,1,0,1,0,150,200)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,1,0,1,0,200,300)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,1,0,1,0,300,500)'

echo ""
echo "Plot SingleMuon muonPhi distribution in PYTHIA+HYDJET 0-10% and PbPb  0-10%:"
echo ""

root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,0,1,1,0,80,100)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,0,1,1,0,100,120)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,0,1,1,0,120,150)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,0,1,1,0,150,200)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,0,1,1,0,200,300)'
root -l -q '../plots/muonPhi/plotMuonPhi.C(0,0,0,0,1,1,0,300,500)'

echo ""
echo "Copying plots to Analysis Note folder"
echo ""
 
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/pp/muonPhi_SingleMuon_pp_mu12_pTjet-80to100.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_pp_mu12_pTjet-80to100.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/pp/muonPhi_SingleMuon_pp_mu12_pTjet-100to120.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_pp_mu12_pTjet-100to120.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/pp/muonPhi_SingleMuon_pp_mu12_pTjet-120to150.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_pp_mu12_pTjet-120to150.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/pp/muonPhi_SingleMuon_pp_mu12_pTjet-150to200.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_pp_mu12_pTjet-150to200.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/pp/muonPhi_SingleMuon_pp_mu12_pTjet-200to300.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_pp_mu12_pTjet-200to300.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/pp/muonPhi_SingleMuon_pp_mu12_pTjet-300to500.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_pp_mu12_pTjet-300to500.pdf


cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C4/muonPhi_SingleMuon_C4_mu12_pTjet-80to100.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C4_mu12_pTjet-80to100.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C4/muonPhi_SingleMuon_C4_mu12_pTjet-100to120.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C4_mu12_pTjet-100to120.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C4/muonPhi_SingleMuon_C4_mu12_pTjet-120to150.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C4_mu12_pTjet-120to150.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C4/muonPhi_SingleMuon_C4_mu12_pTjet-150to200.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C4_mu12_pTjet-150to200.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C4/muonPhi_SingleMuon_C4_mu12_pTjet-200to300.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C4_mu12_pTjet-200to300.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C4/muonPhi_SingleMuon_C4_mu12_pTjet-300to500.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C4_mu12_pTjet-300to500.pdf


cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C3/muonPhi_SingleMuon_C3_mu12_pTjet-80to100.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C3_mu12_pTjet-80to100.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C3/muonPhi_SingleMuon_C3_mu12_pTjet-100to120.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C3_mu12_pTjet-100to120.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C3/muonPhi_SingleMuon_C3_mu12_pTjet-120to150.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C3_mu12_pTjet-120to150.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C3/muonPhi_SingleMuon_C3_mu12_pTjet-150to200.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C3_mu12_pTjet-150to200.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C3/muonPhi_SingleMuon_C3_mu12_pTjet-200to300.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C3_mu12_pTjet-200to300.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C3/muonPhi_SingleMuon_C3_mu12_pTjet-300to500.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C3_mu12_pTjet-300to500.pdf

cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C2/muonPhi_SingleMuon_C2_mu12_pTjet-80to100.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C2_mu12_pTjet-80to100.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C2/muonPhi_SingleMuon_C2_mu12_pTjet-100to120.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C2_mu12_pTjet-100to120.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C2/muonPhi_SingleMuon_C2_mu12_pTjet-120to150.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C2_mu12_pTjet-120to150.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C2/muonPhi_SingleMuon_C2_mu12_pTjet-150to200.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C2_mu12_pTjet-150to200.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C2/muonPhi_SingleMuon_C2_mu12_pTjet-200to300.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C2_mu12_pTjet-200to300.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C2/muonPhi_SingleMuon_C2_mu12_pTjet-300to500.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C2_mu12_pTjet-300to500.pdf

cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C1/muonPhi_SingleMuon_C1_mu12_pTjet-80to100.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C1_mu12_pTjet-80to100.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C1/muonPhi_SingleMuon_C1_mu12_pTjet-100to120.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C1_mu12_pTjet-100to120.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C1/muonPhi_SingleMuon_C1_mu12_pTjet-120to150.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C1_mu12_pTjet-120to150.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C1/muonPhi_SingleMuon_C1_mu12_pTjet-150to200.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C1_mu12_pTjet-150to200.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C1/muonPhi_SingleMuon_C1_mu12_pTjet-200to300.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C1_mu12_pTjet-200to300.pdf
cp /home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muPhi/SingleMuon/C1/muonPhi_SingleMuon_C1_mu12_pTjet-300to500.pdf /home/clayton/Analysis/AN-23-055/figures_updated/muPhi/muonPhi_SingleMuon_C1_mu12_pTjet-300to500.pdf



