# fileNames folder

This folder contains .txt files containing all the files used for each dataset in the analysis.

## fileNames_HYDJET_MinBias.txt
- Dataset: /MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbAutumn18DR-NoPUmva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM
- Notes: Used to measure trigger turn-on curves in simulation and compare to PbPb MinBias data.

## fileNames_PYTHIAHYDJET_BJet.txt
- Dataset: /Bjet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM
- Notes: Used for statistical enhancement of the b-jet muon rel-pt templates.

## fileNames_PYTHIAHYDJET_DiJet.txt
Dataset: /DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM
Notes: Our primary MC forest used in this analysis, primarily to compare to PbPb SingleMuon.

## fileNames_PYTHIAHYDJET_DiJet_onlyMuonTaggedJets_noRecoJetPtCut.txt
Dataset: /DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM
Notes: Only muon-tagged jets in this forest.  No cut on the recoJet pT, which makes it possible to measure the jet-energy response matrices.

## fileNames_PYTHIAHYDJET_MuJet.txt
Dataset: /MuJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v3/AODSIM
Notes: Used for statistical enhancement of the b-jet and c-jet muon rel-pt templates.

## fileNames_PYTHIA_DiJet.txt
Dataset: /QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM
Notes: Our primary MC forest used in this analysis, primarily to compare to pp SingleMuon.

## fileNames_PYTHIA_DiJet_noRecoJetPtCut.txt
Dataset: /QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM
Notes: No cut on the recoJet pT, which makes it possible to measure the jet-energy response matrices.

## fileNames_PYTHIA_DiJet_noRecoJetPtCut_excludeNeutrinos.txt
Dataset: /QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM
Notes: No cut on the recoJet pT, and neutrino energy has been excluded from the MC.

## fileNames_PbPb_HardProbes.txt
Dataset: /HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD
Notes: PbPb diJet dataset.

## fileNames_PbPb_MB_0_1000_LS.txt
Dataset: /HIMinimumBias0/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD
Notes: PbPb MinBias, 2018 run #0.  Only set to forest 1000 LS.

## fileNames_PbPb_MinBias.txt
Dataset: /HIMinimumBias*/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD
Notes: PbPb MinBias, 2018 all runs.

## fileNames_PbPb_SingleMuon.txt
Dataset: /HISingleMuon/HIRun2018A-PromptReco-v2/AOD
Notes: PbPb SingleMuon 2018. Primary data forest for analysis. HLT_HIL3Mu5_NHitQ10_v1 trigger required for every event.

## fileNames_pp_MinBias.txt
Dataset: /HIZeroBias1/Run2017G-17Nov2017-v1/AOD
Notes: pp MinBias, 2017 run #1.

## fileNames_pp_SingleMuon.txt
Dataset: /SingleMuon/Run2017G-17Nov2017-v1/AOD
Notes: pp SingleMuon 2017. Primary data forest for analysis.  HLT_HIL3Mu5_NHitQ10_v1 trigger required for every event.
