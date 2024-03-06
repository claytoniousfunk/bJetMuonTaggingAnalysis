#!/bin/bash

echo ""
echo "Comparing vz distribution in PYTHIA and pp:"
echo ""

root -l -q '/home/clayton/Analysis/code/normalizeAndCompareSpectra/normalizeAndCompareSpectraVz.C(1,0)' 

echo ""
echo "Comparing vz distribution in PYTHIA+HYDJET and PbPb:"
echo ""

root -l -q '/home/clayton/Analysis/code/normalizeAndCompareSpectra/normalizeAndCompareSpectraVz.C(0,1)' 



echo ""
echo "Comparing hiBin distribution in PYTHIA+HYDJET and PbPb:"
echo ""

root -l -q /home/clayton/Analysis/code/normalizeAndCompareSpectra/normalizeAndCompareSpectraHiBin.C 

echo ""
echo "Comparing jet spectra in pp:"
echo ""

root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPt.C(1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetEta.C(1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPhi.C(1,0,0,1,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPt.C(1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetEta.C(1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPhi.C(1,0,0,0,1)'

echo ""
echo "Comparing jet spectra in PbPb:"
echo ""

root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPt.C(0,1,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetEta.C(0,1,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPhi.C(0,1,0,1,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPt.C(0,0,1,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetEta.C(0,0,1,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPhi.C(0,0,1,1,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPt.C(0,1,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetEta.C(0,1,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPhi.C(0,1,0,0,1)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPt.C(0,0,1,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetEta.C(0,0,1,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotJetPhi.C(0,0,1,0,1)'

echo ""
echo "Comparing muon spectra in pp:"
echo ""

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(1,0,0,1,0,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(1,0,0,1,0,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(1,0,0,1,0,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(1,0,0,1,0,1,0,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(1,0,0,1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(1,0,0,1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(1,0,0,1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(1,0,0,1,0,0,1,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(1,0,0,1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(1,0,0,1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(1,0,0,1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(1,0,0,1,0,0,0,1)'

echo ""
echo "Comparing muon spectra in PbPb:"
echo ""

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,1,0,1,0,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,1,0,1,0,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,1,0,1,0,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,1,0,1,0,1,0,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,1,0,1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,1,0,1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,1,0,1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,1,0,1,0,0,1,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,1,0,1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,1,0,1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,1,0,1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,1,0,1,0,0,0,1)'


root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,1,0,0,1,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,1,0,0,1,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,1,0,0,1,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,1,0,0,1,1,0,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,1,0,0,1,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,1,0,0,1,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,1,0,0,1,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,1,0,0,1,0,1,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,1,0,0,1,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,1,0,0,1,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,1,0,0,1,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,1,0,0,1,0,0,1)'


root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,0,1,1,0,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,0,1,1,0,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,0,1,1,0,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,0,1,1,0,1,0,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,0,1,1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,0,1,1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,0,1,1,0,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,0,1,1,0,0,1,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,0,1,1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,0,1,1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,0,1,1,0,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,0,1,1,0,0,0,1)'


root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,0,1,0,1,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,0,1,0,1,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,0,1,0,1,1,0,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,0,1,0,1,1,0,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,0,1,0,1,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,0,1,0,1,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,0,1,0,1,0,1,0)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,0,1,0,1,0,1,0)'

root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPt.C(0,0,1,0,1,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonEta.C(0,0,1,0,1,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonPhi.C(0,0,1,0,1,0,0,1)'
root -l -q '/home/clayton/Analysis/code/plotPt/plotMuonRelPt.C(0,0,1,0,1,0,0,1)'



#echo "Calculating b-jet correction factors:"
#echo ""

#root -l -q /home/clayton/Analysis/code/projectFlavor/projectFlavorV1p2_pythia.C
#root -l -q '/home/clayton/Analysis/code/projectFlavor/projectFlavorV1p2_ph.C(1,0)'
#root -l -q '/home/clayton/Analysis/code/projectFlavor/projectFlavorV1p2_ph.C(0,1)'

#echo ""
#echo "Plotting b-jet correction factors:"
#echo ""

#root -l -q /home/clayton/Analysis/code/projectFlavor/plotCorrFactors.C

#echo ""
#echo "Creating pt-ptRel maps:"
#echo ""

#root -l -q '/home/clayton/Analysis/code/etaPhiMap/ptPtRelMap.C(1,0,1,0,0)'
#root -l -q '/home/clayton/Analysis/code/etaPhiMap/ptPtRelMap.C(1,0,0,1,0)'
#root -l -q '/home/clayton/Analysis/code/etaPhiMap/ptPtRelMap.C(1,0,0,0,1)'

#root -l -q '/home/clayton/Analysis/code/etaPhiMap/ptPtRelMap.C(0,1,1,0,0)'
#root -l -q '/home/clayton/Analysis/code/etaPhiMap/ptPtRelMap.C(0,1,0,1,0)'
#root -l -q '/home/clayton/Analysis/code/etaPhiMap/ptPtRelMap.C(0,1,0,0,1)'


#echo ""
#echo "Calculating JER/JES:"
#echo ""

#root -l -q '/home/clayton/Analysis/code/RecoRefCompare/RecoRefCompare_selfCalc.C(1,0,0)'
#root -l -q '/home/clayton/Analysis/code/RecoRefCompare/RecoRefCompare_selfCalc.C(0,1,0)'
#root -l -q '/home/clayton/Analysis/code/RecoRefCompare/RecoRefCompare_selfCalc.C(0,0,1)'






