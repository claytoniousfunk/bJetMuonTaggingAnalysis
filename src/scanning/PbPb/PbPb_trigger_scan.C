// general ROOT/C includes
#include <iostream>
#include "TFile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TProfile2D.h"
#include <TF1.h>
#include "assert.h"
#include <fstream>
#include "TMath.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TMath.h"
#include <TNtuple.h>
#include "TChain.h"
#include <TString.h>
#include <TLatex.h>
#include <TCut.h>
#include "TDatime.h"
#include <vector>
#include "TCanvas.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// event map
#include "../../../eventMap/eventMap.h"
// jet corrector
#include "../../../JetEnergyCorrections/JetCorrector.h"
// jet uncertainty
#include "../../../JetEnergyCorrections/JetUncertainty.h"
// general analysis variables
#include "../../../headers/AnalysisSetupV2p3.h"
// eta-phi mask function
#include "../../../headers/functions/etaPhiMask.h"
// getDr function
#include "../../../headers/functions/getDr.h"
// getJetPtBin function
#include "../../../headers/functions/getJetPtBin.h"
// getCentBin function
//#include "../../../headers/functions/getCentBin_v2.h" // coarse centrality
#include "../../../headers/functions/getCentBin.h" // nominal centrality
// getPtRel function
#include "../../../headers/functions/getPtRel.h"
// isQualityMuon_hybridSoft function
#include "../../../headers/functions/isQualityMuon_hybridSoft.h"
// isQualityMuon_tight function
#include "../../../headers/functions/isQualityMuon_tight.h"
// isWDecayMuon function
#include "../../../headers/functions/isWDecayMuon.h"
// triggerIsOn function
#include "../../../headers/functions/triggerIsOn.h"
// pthat filter function
#include "../../../headers/functions/passesLeadingGenJetPthatFilter.h"
// JetTrkMax filter function
#include "../../../headers/functions/jet_filter/passesJetTrkMaxFilter.h"
// print introduction
#include "../../../headers/introductions/printIntroduction_PYTHIAHYDJET_scan_V3p7.h"
// analysis config
//#include "../../../headers/config/config_PbPb_MinBias.h"
//#include "../../../headers/config/config_PbPb_diJet.h"
#include "../../../headers/config/config_PbPb.h"
// read config
#include "../../../headers/config/readConfig.h"

TH1D *muPt_trigOn[5];
TH1D *muPt_trigOff[5];
TH1D *muPt_all[5];

TH1D *muEta_trigOn[5];
TH1D *muEta_trigOff[5];
TH1D *muEta_all[5];

TH1D *muPhi_trigOn[5];
TH1D *muPhi_trigOff[5];
TH1D *muPhi_all[5];

TH1D *muChi2NDF_trigOn[5];
TH1D *muInnerD0_trigOn[5];
TH1D *muInnerDz_trigOn[5];
TH1D *muPixelHits_trigOn[5];
TH1D *muIsTracker_trigOn[5];
TH1D *muIsGlobal_trigOn[5];
TH1D *muTrkLayers_trigOn[5];
TH1D *muIsPF_trigOn[5];
TH1D *muStations_trigOn[5];
TH1D *muMuonHits_trigOn[5];
	
TH1D *muChi2NDF_trigOff[5];
TH1D *muInnerD0_trigOff[5];
TH1D *muInnerDz_trigOff[5];
TH1D *muPixelHits_trigOff[5];
TH1D *muIsTracker_trigOff[5];
TH1D *muIsGlobal_trigOff[5];
TH1D *muTrkLayers_trigOff[5];
TH1D *muIsPF_trigOff[5];
TH1D *muStations_trigOff[5];
TH1D *muMuonHits_trigOff[5];

TH1D *muChi2NDF_all[5];
TH1D *muInnerD0_all[5];
TH1D *muInnerDz_all[5];
TH1D *muPixelHits_all[5];
TH1D *muIsTracker_all[5];
TH1D *muIsGlobal_all[5];
TH1D *muTrkLayers_all[5];
TH1D *muIsPF_all[5];
TH1D *muStations_all[5];
TH1D *muMuonHits_all[5];


void PbPb_trigger_scan(int group = 1){
  

  // TString input = Form("/eos/user/c/cbennett/skims/output_skims_PbPb_HIMinimumBias0/PbPb_MinBias_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PbPb_MinBias_triggerEffScan_mu12_tight/PbPb_SingleMuon_scan_output_%i.root",group);

  TString input = Form("/eos/user/c/cbennett/skims/output_skims_PbPb_HardProbes/PbPb_HardProbes_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PbPb_HardProbes_triggerEffScan_mu12_tight/PbPb_SingleMuon_scan_output_%i.root",group);


  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_L2Relative_AK4PF.txt"); // LXPLUS

  JetCorrector JEC(Files);

  JetUncertainty JEU("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_Uncertainty_AK4PF.txt");


  //~~~~~~~~~~~  initialize histograms ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  muPt_trigOn[0] = new TH1D("muPt_trigOn_C0","muPt_trigOn, cent. 0-90%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_trigOn[1] = new TH1D("muPt_trigOn_C1","muPt_trigOn, cent. 0-10%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_trigOn[2] = new TH1D("muPt_trigOn_C2","muPt_trigOn, cent. 10-30%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_trigOn[3] = new TH1D("muPt_trigOn_C3","muPt_trigOn, cent. 30-50%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_trigOn[4] = new TH1D("muPt_trigOn_C4","muPt_trigOn, cent. 50-90%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
	
  muEta_trigOn[0] = new TH1D("muEta_trigOn_C0","muEta_trigOn, cent. 0-90%; muEta; Entries",100,-5,5);
  muEta_trigOn[1] = new TH1D("muEta_trigOn_C1","muEta_trigOn, cent. 0-10%; muEta; Entries",100,-5,5);
  muEta_trigOn[2] = new TH1D("muEta_trigOn_C2","muEta_trigOn, cent. 10-30%; muEta; Entries",100,-5,5);
  muEta_trigOn[3] = new TH1D("muEta_trigOn_C3","muEta_trigOn, cent. 30-50%; muEta; Entries",100,-5,5);
  muEta_trigOn[4] = new TH1D("muEta_trigOn_C4","muEta_trigOn, cent. 50-90%; muEta; Entries",100,-5,5);
	
  muPhi_trigOn[0] = new TH1D("muPhi_trigOn_C0","muPhi_trigOn, cent. 0-90%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_trigOn[1] = new TH1D("muPhi_trigOn_C1","muPhi_trigOn, cent. 0-10%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_trigOn[2] = new TH1D("muPhi_trigOn_C2","muPhi_trigOn, cent. 10-30%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_trigOn[3] = new TH1D("muPhi_trigOn_C3","muPhi_trigOn, cent. 30-50%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_trigOn[4] = new TH1D("muPhi_trigOn_C4","muPhi_trigOn, cent. 50-90%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
	
  muChi2NDF_trigOn[0] = new TH1D("muChi2NDF_trigOn_C0","muChi2NDF_trigOn, cent. 0-90%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_trigOn[1] = new TH1D("muChi2NDF_trigOn_C1","muChi2NDF_trigOn, cent. 0-10%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_trigOn[2] = new TH1D("muChi2NDF_trigOn_C2","muChi2NDF_trigOn, cent. 10-30%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_trigOn[3] = new TH1D("muChi2NDF_trigOn_C3","muChi2NDF_trigOn, cent. 30-50%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_trigOn[4] = new TH1D("muChi2NDF_trigOn_C4","muChi2NDF_trigOn, cent. 50-90%; muChi2NDF; Entries",100,0,50);	
	
  muInnerD0_trigOn[0] = new TH1D("muInnerD0_trigOn_C0","muInnerD0_trigOn, cent. 0-90%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_trigOn[1] = new TH1D("muInnerD0_trigOn_C1","muInnerD0_trigOn, cent. 0-10%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_trigOn[2] = new TH1D("muInnerD0_trigOn_C2","muInnerD0_trigOn, cent. 10-30%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_trigOn[3] = new TH1D("muInnerD0_trigOn_C3","muInnerD0_trigOn, cent. 30-50%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_trigOn[4] = new TH1D("muInnerD0_trigOn_C4","muInnerD0_trigOn, cent. 50-90%; muInnerD0; Entries",100,-1,1);	
	
  muInnerDz_trigOn[0] = new TH1D("muInnerDz_trigOn_C0","muInnerDz_trigOn, cent. 0-90%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_trigOn[1] = new TH1D("muInnerDz_trigOn_C1","muInnerDz_trigOn, cent. 0-10%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_trigOn[2] = new TH1D("muInnerDz_trigOn_C2","muInnerDz_trigOn, cent. 10-30%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_trigOn[3] = new TH1D("muInnerDz_trigOn_C3","muInnerDz_trigOn, cent. 30-50%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_trigOn[4] = new TH1D("muInnerDz_trigOn_C4","muInnerDz_trigOn, cent. 50-90%; muInnerDz; Entries",100,-1,1);	
	
  muPixelHits_trigOn[0] = new TH1D("muPixelHits_trigOn_C0","muPixelHits_trigOn, cent. 0-90%; muPixelHits; Entries",30,0,30);	
  muPixelHits_trigOn[1] = new TH1D("muPixelHits_trigOn_C1","muPixelHits_trigOn, cent. 0-10%; muPixelHits; Entries",30,0,30);	
  muPixelHits_trigOn[2] = new TH1D("muPixelHits_trigOn_C2","muPixelHits_trigOn, cent. 10-30%; muPixelHits; Entries",30,0,30);	
  muPixelHits_trigOn[3] = new TH1D("muPixelHits_trigOn_C3","muPixelHits_trigOn, cent. 30-50%; muPixelHits; Entries",30,0,30);	
  muPixelHits_trigOn[4] = new TH1D("muPixelHits_trigOn_C4","muPixelHits_trigOn, cent. 50-90%; muPixelHits; Entries",30,0,30);	
	
  muIsTracker_trigOn[0] = new TH1D("muIsTracker_trigOn_C0","muIsTracker_trigOn, cent. 0-90%; muIsTracker; Entries",2,0,2);	
  muIsTracker_trigOn[1] = new TH1D("muIsTracker_trigOn_C1","muIsTracker_trigOn, cent. 0-10%; muIsTracker; Entries",2,0,2);	
  muIsTracker_trigOn[2] = new TH1D("muIsTracker_trigOn_C2","muIsTracker_trigOn, cent. 10-30%; muIsTracker; Entries",2,0,2);	
  muIsTracker_trigOn[3] = new TH1D("muIsTracker_trigOn_C3","muIsTracker_trigOn, cent. 30-50%; muIsTracker; Entries",2,0,2);	
  muIsTracker_trigOn[4] = new TH1D("muIsTracker_trigOn_C4","muIsTracker_trigOn, cent. 50-90%; muIsTracker; Entries",2,0,2);	
	
  muIsGlobal_trigOn[0] = new TH1D("muIsGlobal_trigOn_C0","muIsGlobal_trigOn, cent. 0-90%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_trigOn[1] = new TH1D("muIsGlobal_trigOn_C1","muIsGlobal_trigOn, cent. 0-10%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_trigOn[2] = new TH1D("muIsGlobal_trigOn_C2","muIsGlobal_trigOn, cent. 10-30%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_trigOn[3] = new TH1D("muIsGlobal_trigOn_C3","muIsGlobal_trigOn, cent. 30-50%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_trigOn[4] = new TH1D("muIsGlobal_trigOn_C4","muIsGlobal_trigOn, cent. 50-90%; muIsGlobal; Entries",2,0,2);	
	
  muTrkLayers_trigOn[0] = new TH1D("muTrkLayers_trigOn_C0","muTrkLayers_trigOn, cent. 0-90%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_trigOn[1] = new TH1D("muTrkLayers_trigOn_C1","muTrkLayers_trigOn, cent. 0-10%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_trigOn[2] = new TH1D("muTrkLayers_trigOn_C2","muTrkLayers_trigOn, cent. 10-30%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_trigOn[3] = new TH1D("muTrkLayers_trigOn_C3","muTrkLayers_trigOn, cent. 30-50%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_trigOn[4] = new TH1D("muTrkLayers_trigOn_C4","muTrkLayers_trigOn, cent. 50-90%; muTrkLayers; Entries",30,0,30);	
	
  muIsPF_trigOn[0] = new TH1D("muIsPF_trigOn_C0","muIsPF_trigOn, cent. 0-90%; muIsPF; Entries",2,0,2);	
  muIsPF_trigOn[1] = new TH1D("muIsPF_trigOn_C1","muIsPF_trigOn, cent. 0-10%; muIsPF; Entries",2,0,2);	
  muIsPF_trigOn[2] = new TH1D("muIsPF_trigOn_C2","muIsPF_trigOn, cent. 10-30%; muIsPF; Entries",2,0,2);	
  muIsPF_trigOn[3] = new TH1D("muIsPF_trigOn_C3","muIsPF_trigOn, cent. 30-50%; muIsPF; Entries",2,0,2);	
  muIsPF_trigOn[4] = new TH1D("muIsPF_trigOn_C4","muIsPF_trigOn, cent. 50-90%; muIsPF; Entries",2,0,2);	
	
  muStations_trigOn[0] = new TH1D("muStations_trigOn_C0","muStations_trigOn, cent. 0-90%; muStations; Entries",10,0,10);	
  muStations_trigOn[1] = new TH1D("muStations_trigOn_C1","muStations_trigOn, cent. 0-10%; muStations; Entries",10,0,10);	
  muStations_trigOn[2] = new TH1D("muStations_trigOn_C2","muStations_trigOn, cent. 10-10%; muStations; Entries",10,0,10);	
  muStations_trigOn[3] = new TH1D("muStations_trigOn_C3","muStations_trigOn, cent. 10-50%; muStations; Entries",10,0,10);	
  muStations_trigOn[4] = new TH1D("muStations_trigOn_C4","muStations_trigOn, cent. 50-90%; muStations; Entries",10,0,10);	
	
  muMuonHits_trigOn[0] = new TH1D("muMuonHits_trigOn_C0","muMuonHits_trigOn, cent. 0-90%; muMuonHits; Entries",30,0,30);	
  muMuonHits_trigOn[1] = new TH1D("muMuonHits_trigOn_C1","muMuonHits_trigOn, cent. 0-10%; muMuonHits; Entries",30,0,30);	
  muMuonHits_trigOn[2] = new TH1D("muMuonHits_trigOn_C2","muMuonHits_trigOn, cent. 10-30%; muMuonHits; Entries",30,0,30);	
  muMuonHits_trigOn[3] = new TH1D("muMuonHits_trigOn_C3","muMuonHits_trigOn, cent. 30-50%; muMuonHits; Entries",30,0,30);	
  muMuonHits_trigOn[4] = new TH1D("muMuonHits_trigOn_C4","muMuonHits_trigOn, cent. 50-90%; muMuonHits; Entries",30,0,30);	
	
  muPt_trigOff[0] = new TH1D("muPt_trigOff_C0","muPt_trigOff, cent. 0-90%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_trigOff[1] = new TH1D("muPt_trigOff_C1","muPt_trigOff, cent. 0-10%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_trigOff[2] = new TH1D("muPt_trigOff_C2","muPt_trigOff, cent. 10-30%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_trigOff[3] = new TH1D("muPt_trigOff_C3","muPt_trigOff, cent. 30-50%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_trigOff[4] = new TH1D("muPt_trigOff_C4","muPt_trigOff, cent. 50-90%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
	
  muEta_trigOff[0] = new TH1D("muEta_trigOff_C0","muEta_trigOff, cent. 0-90%; muEta; Entries",100,-5,5);
  muEta_trigOff[1] = new TH1D("muEta_trigOff_C1","muEta_trigOff, cent. 0-10%; muEta; Entries",100,-5,5);
  muEta_trigOff[2] = new TH1D("muEta_trigOff_C2","muEta_trigOff, cent. 10-30%; muEta; Entries",100,-5,5);
  muEta_trigOff[3] = new TH1D("muEta_trigOff_C3","muEta_trigOff, cent. 30-50%; muEta; Entries",100,-5,5);
  muEta_trigOff[4] = new TH1D("muEta_trigOff_C4","muEta_trigOff, cent. 50-90%; muEta; Entries",100,-5,5);
	
  muPhi_trigOff[0] = new TH1D("muPhi_trigOff_C0","muPhi_trigOff, cent. 0-90%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_trigOff[1] = new TH1D("muPhi_trigOff_C1","muPhi_trigOff, cent. 0-10%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_trigOff[2] = new TH1D("muPhi_trigOff_C2","muPhi_trigOff, cent. 10-30%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_trigOff[3] = new TH1D("muPhi_trigOff_C3","muPhi_trigOff, cent. 30-50%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_trigOff[4] = new TH1D("muPhi_trigOff_C4","muPhi_trigOff, cent. 50-90%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
	
  muChi2NDF_trigOff[0] = new TH1D("muChi2NDF_trigOff_C0","muChi2NDF_trigOff, cent. 0-90%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_trigOff[1] = new TH1D("muChi2NDF_trigOff_C1","muChi2NDF_trigOff, cent. 0-10%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_trigOff[2] = new TH1D("muChi2NDF_trigOff_C2","muChi2NDF_trigOff, cent. 10-30%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_trigOff[3] = new TH1D("muChi2NDF_trigOff_C3","muChi2NDF_trigOff, cent. 30-50%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_trigOff[4] = new TH1D("muChi2NDF_trigOff_C4","muChi2NDF_trigOff, cent. 50-90%; muChi2NDF; Entries",100,0,50);	
	
  muInnerD0_trigOff[0] = new TH1D("muInnerD0_trigOff_C0","muInnerD0_trigOff, cent. 0-90%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_trigOff[1] = new TH1D("muInnerD0_trigOff_C1","muInnerD0_trigOff, cent. 0-10%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_trigOff[2] = new TH1D("muInnerD0_trigOff_C2","muInnerD0_trigOff, cent. 10-30%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_trigOff[3] = new TH1D("muInnerD0_trigOff_C3","muInnerD0_trigOff, cent. 30-50%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_trigOff[4] = new TH1D("muInnerD0_trigOff_C4","muInnerD0_trigOff, cent. 50-90%; muInnerD0; Entries",100,-1,1);	
	
  muInnerDz_trigOff[0] = new TH1D("muInnerDz_trigOff_C0","muInnerDz_trigOff, cent. 0-90%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_trigOff[1] = new TH1D("muInnerDz_trigOff_C1","muInnerDz_trigOff, cent. 0-10%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_trigOff[2] = new TH1D("muInnerDz_trigOff_C2","muInnerDz_trigOff, cent. 10-30%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_trigOff[3] = new TH1D("muInnerDz_trigOff_C3","muInnerDz_trigOff, cent. 30-50%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_trigOff[4] = new TH1D("muInnerDz_trigOff_C4","muInnerDz_trigOff, cent. 50-90%; muInnerDz; Entries",100,-1,1);	
	
  muPixelHits_trigOff[0] = new TH1D("muPixelHits_trigOff_C0","muPixelHits_trigOff, cent. 0-90%; muPixelHits; Entries",30,0,30);	
  muPixelHits_trigOff[1] = new TH1D("muPixelHits_trigOff_C1","muPixelHits_trigOff, cent. 0-10%; muPixelHits; Entries",30,0,30);	
  muPixelHits_trigOff[2] = new TH1D("muPixelHits_trigOff_C2","muPixelHits_trigOff, cent. 10-30%; muPixelHits; Entries",30,0,30);	
  muPixelHits_trigOff[3] = new TH1D("muPixelHits_trigOff_C3","muPixelHits_trigOff, cent. 30-50%; muPixelHits; Entries",30,0,30);	
  muPixelHits_trigOff[4] = new TH1D("muPixelHits_trigOff_C4","muPixelHits_trigOff, cent. 50-90%; muPixelHits; Entries",30,0,30);	
	
  muIsTracker_trigOff[0] = new TH1D("muIsTracker_trigOff_C0","muIsTracker_trigOff, cent. 0-90%; muIsTracker; Entries",2,0,2);	
  muIsTracker_trigOff[1] = new TH1D("muIsTracker_trigOff_C1","muIsTracker_trigOff, cent. 0-10%; muIsTracker; Entries",2,0,2);	
  muIsTracker_trigOff[2] = new TH1D("muIsTracker_trigOff_C2","muIsTracker_trigOff, cent. 10-30%; muIsTracker; Entries",2,0,2);	
  muIsTracker_trigOff[3] = new TH1D("muIsTracker_trigOff_C3","muIsTracker_trigOff, cent. 30-50%; muIsTracker; Entries",2,0,2);	
  muIsTracker_trigOff[4] = new TH1D("muIsTracker_trigOff_C4","muIsTracker_trigOff, cent. 50-90%; muIsTracker; Entries",2,0,2);	
	
  muIsGlobal_trigOff[0] = new TH1D("muIsGlobal_trigOff_C0","muIsGlobal_trigOff, cent. 0-90%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_trigOff[1] = new TH1D("muIsGlobal_trigOff_C1","muIsGlobal_trigOff, cent. 0-10%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_trigOff[2] = new TH1D("muIsGlobal_trigOff_C2","muIsGlobal_trigOff, cent. 10-30%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_trigOff[3] = new TH1D("muIsGlobal_trigOff_C3","muIsGlobal_trigOff, cent. 30-50%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_trigOff[4] = new TH1D("muIsGlobal_trigOff_C4","muIsGlobal_trigOff, cent. 50-90%; muIsGlobal; Entries",2,0,2);	
	
  muTrkLayers_trigOff[0] = new TH1D("muTrkLayers_trigOff_C0","muTrkLayers_trigOff, cent. 0-90%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_trigOff[1] = new TH1D("muTrkLayers_trigOff_C1","muTrkLayers_trigOff, cent. 0-10%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_trigOff[2] = new TH1D("muTrkLayers_trigOff_C2","muTrkLayers_trigOff, cent. 10-30%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_trigOff[3] = new TH1D("muTrkLayers_trigOff_C3","muTrkLayers_trigOff, cent. 30-50%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_trigOff[4] = new TH1D("muTrkLayers_trigOff_C4","muTrkLayers_trigOff, cent. 50-90%; muTrkLayers; Entries",30,0,30);	
	
  muIsPF_trigOff[0] = new TH1D("muIsPF_trigOff_C0","muIsPF_trigOff, cent. 0-90%; muIsPF; Entries",2,0,2);	
  muIsPF_trigOff[1] = new TH1D("muIsPF_trigOff_C1","muIsPF_trigOff, cent. 0-10%; muIsPF; Entries",2,0,2);	
  muIsPF_trigOff[2] = new TH1D("muIsPF_trigOff_C2","muIsPF_trigOff, cent. 10-30%; muIsPF; Entries",2,0,2);	
  muIsPF_trigOff[3] = new TH1D("muIsPF_trigOff_C3","muIsPF_trigOff, cent. 30-50%; muIsPF; Entries",2,0,2);	
  muIsPF_trigOff[4] = new TH1D("muIsPF_trigOff_C4","muIsPF_trigOff, cent. 50-90%; muIsPF; Entries",2,0,2);	
	
  muStations_trigOff[0] = new TH1D("muStations_trigOff_C0","muStations_trigOff, cent. 0-90%; muStations; Entries",10,0,10);	
  muStations_trigOff[1] = new TH1D("muStations_trigOff_C1","muStations_trigOff, cent. 0-10%; muStations; Entries",10,0,10);	
  muStations_trigOff[2] = new TH1D("muStations_trigOff_C2","muStations_trigOff, cent. 10-30%; muStations; Entries",10,0,10);	
  muStations_trigOff[3] = new TH1D("muStations_trigOff_C3","muStations_trigOff, cent. 30-50%; muStations; Entries",10,0,10);	
  muStations_trigOff[4] = new TH1D("muStations_trigOff_C4","muStations_trigOff, cent. 50-90%; muStations; Entries",10,0,10);	
	
  muMuonHits_trigOff[0] = new TH1D("muMuonHits_trigOff_C0","muMuonHits_trigOff, cent. 0-90%; muMuonHits; Entries",30,0,30);	
  muMuonHits_trigOff[1] = new TH1D("muMuonHits_trigOff_C1","muMuonHits_trigOff, cent. 0-10%; muMuonHits; Entries",30,0,30);	
  muMuonHits_trigOff[2] = new TH1D("muMuonHits_trigOff_C2","muMuonHits_trigOff, cent. 10-30%; muMuonHits; Entries",30,0,30);	
  muMuonHits_trigOff[3] = new TH1D("muMuonHits_trigOff_C3","muMuonHits_trigOff, cent. 30-50%; muMuonHits; Entries",30,0,30);	
  muMuonHits_trigOff[4] = new TH1D("muMuonHits_trigOff_C4","muMuonHits_trigOff, cent. 50-90%; muMuonHits; Entries",30,0,30);	
	
	
	
	
  muPt_all[0] = new TH1D("muPt_all_C0","muPt_all, cent. 0-90%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_all[1] = new TH1D("muPt_all_C1","muPt_all, cent. 0-10%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_all[2] = new TH1D("muPt_all_C2","muPt_all, cent. 10-30%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_all[3] = new TH1D("muPt_all_C3","muPt_all, cent. 30-50%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
  muPt_all[4] = new TH1D("muPt_all_C4","muPt_all, cent. 50-90%; muPt [GeV]; Entries",NMuPtBins,muPtMin,muPtMax);
	
  muEta_all[0] = new TH1D("muEta_all_C0","muEta_all, cent. 0-90%; muEta; Entries",100,-5,5);
  muEta_all[1] = new TH1D("muEta_all_C1","muEta_all, cent. 0-10%; muEta; Entries",100,-5,5);
  muEta_all[2] = new TH1D("muEta_all_C2","muEta_all, cent. 10-30%; muEta; Entries",100,-5,5);
  muEta_all[3] = new TH1D("muEta_all_C3","muEta_all, cent. 30-50%; muEta; Entries",100,-5,5);
  muEta_all[4] = new TH1D("muEta_all_C4","muEta_all, cent. 50-90%; muEta; Entries",100,-5,5);
	
  muPhi_all[0] = new TH1D("muPhi_all_C0","muPhi_all, cent. 0-90%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_all[1] = new TH1D("muPhi_all_C1","muPhi_all, cent. 0-10%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_all[2] = new TH1D("muPhi_all_C2","muPhi_all, cent. 10-30%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_all[3] = new TH1D("muPhi_all_C3","muPhi_all, cent. 30-50%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());
  muPhi_all[4] = new TH1D("muPhi_all_C4","muPhi_all, cent. 50-90%; muPhi; Entries",100,-TMath::Pi(),TMath::Pi());

  muChi2NDF_all[0] = new TH1D("muChi2NDF_all_C0","muChi2NDF_all, cent. 0-90%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_all[1] = new TH1D("muChi2NDF_all_C1","muChi2NDF_all, cent. 0-10%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_all[2] = new TH1D("muChi2NDF_all_C2","muChi2NDF_all, cent. 10-30%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_all[3] = new TH1D("muChi2NDF_all_C3","muChi2NDF_all, cent. 30-50%; muChi2NDF; Entries",100,0,50);	
  muChi2NDF_all[4] = new TH1D("muChi2NDF_all_C4","muChi2NDF_all, cent. 50-90%; muChi2NDF; Entries",100,0,50);	
	
  muInnerD0_all[0] = new TH1D("muInnerD0_all_C0","muInnerD0_all, cent. 0-90%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_all[1] = new TH1D("muInnerD0_all_C1","muInnerD0_all, cent. 0-10%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_all[2] = new TH1D("muInnerD0_all_C2","muInnerD0_all, cent. 10-30%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_all[3] = new TH1D("muInnerD0_all_C3","muInnerD0_all, cent. 30-50%; muInnerD0; Entries",100,-1,1);	
  muInnerD0_all[4] = new TH1D("muInnerD0_all_C4","muInnerD0_all, cent. 50-90%; muInnerD0; Entries",100,-1,1);	
	
  muInnerDz_all[0] = new TH1D("muInnerDz_all_C0","muInnerDz_all, cent. 0-90%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_all[1] = new TH1D("muInnerDz_all_C1","muInnerDz_all, cent. 0-10%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_all[2] = new TH1D("muInnerDz_all_C2","muInnerDz_all, cent. 10-30%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_all[3] = new TH1D("muInnerDz_all_C3","muInnerDz_all, cent. 30-50%; muInnerDz; Entries",100,-1,1);	
  muInnerDz_all[4] = new TH1D("muInnerDz_all_C4","muInnerDz_all, cent. 50-90%; muInnerDz; Entries",100,-1,1);	
	
  muPixelHits_all[0] = new TH1D("muPixelHits_all_C0","muPixelHits_all, cent. 0-90%; muPixelHits; Entries",30,0,30);	
  muPixelHits_all[1] = new TH1D("muPixelHits_all_C1","muPixelHits_all, cent. 0-10%; muPixelHits; Entries",30,0,30);	
  muPixelHits_all[2] = new TH1D("muPixelHits_all_C2","muPixelHits_all, cent. 10-30%; muPixelHits; Entries",30,0,30);	
  muPixelHits_all[3] = new TH1D("muPixelHits_all_C3","muPixelHits_all, cent. 30-50%; muPixelHits; Entries",30,0,30);	
  muPixelHits_all[4] = new TH1D("muPixelHits_all_C4","muPixelHits_all, cent. 50-90%; muPixelHits; Entries",30,0,30);	
	
  muIsTracker_all[0] = new TH1D("muIsTracker_all_C0","muIsTracker_all, cent. 0-90%; muIsTracker; Entries",2,0,2);	
  muIsTracker_all[1] = new TH1D("muIsTracker_all_C1","muIsTracker_all, cent. 0-10%; muIsTracker; Entries",2,0,2);	
  muIsTracker_all[2] = new TH1D("muIsTracker_all_C2","muIsTracker_all, cent. 10-30%; muIsTracker; Entries",2,0,2);	
  muIsTracker_all[3] = new TH1D("muIsTracker_all_C3","muIsTracker_all, cent. 30-50%; muIsTracker; Entries",2,0,2);	
  muIsTracker_all[4] = new TH1D("muIsTracker_all_C4","muIsTracker_all, cent. 50-90%; muIsTracker; Entries",2,0,2);	
	
  muIsGlobal_all[0] = new TH1D("muIsGlobal_all_C0","muIsGlobal_all, cent. 0-90%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_all[1] = new TH1D("muIsGlobal_all_C1","muIsGlobal_all, cent. 0-10%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_all[2] = new TH1D("muIsGlobal_all_C2","muIsGlobal_all, cent. 10-30%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_all[3] = new TH1D("muIsGlobal_all_C3","muIsGlobal_all, cent. 30-50%; muIsGlobal; Entries",2,0,2);	
  muIsGlobal_all[4] = new TH1D("muIsGlobal_all_C4","muIsGlobal_all, cent. 50-90%; muIsGlobal; Entries",2,0,2);	
	
  muTrkLayers_all[0] = new TH1D("muTrkLayers_all_C0","muTrkLayers_all, cent. 0-90%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_all[1] = new TH1D("muTrkLayers_all_C1","muTrkLayers_all, cent. 0-10%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_all[2] = new TH1D("muTrkLayers_all_C2","muTrkLayers_all, cent. 10-30%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_all[3] = new TH1D("muTrkLayers_all_C3","muTrkLayers_all, cent. 30-50%; muTrkLayers; Entries",30,0,30);	
  muTrkLayers_all[4] = new TH1D("muTrkLayers_all_C4","muTrkLayers_all, cent. 50-90%; muTrkLayers; Entries",30,0,30);	
	
  muIsPF_all[0] = new TH1D("muIsPF_all_C0","muIsPF_all, cent. 0-90%; muIsPF; Entries",2,0,2);	
  muIsPF_all[1] = new TH1D("muIsPF_all_C1","muIsPF_all, cent. 0-10%; muIsPF; Entries",2,0,2);	
  muIsPF_all[2] = new TH1D("muIsPF_all_C2","muIsPF_all, cent. 10-30%; muIsPF; Entries",2,0,2);	
  muIsPF_all[3] = new TH1D("muIsPF_all_C3","muIsPF_all, cent. 30-50%; muIsPF; Entries",2,0,2);	
  muIsPF_all[4] = new TH1D("muIsPF_all_C4","muIsPF_all, cent. 50-90%; muIsPF; Entries",2,0,2);	
	
  muStations_all[0] = new TH1D("muStations_all_C0","muStations_all, cent. 0-90%; muStations; Entries",10,0,10);	
  muStations_all[1] = new TH1D("muStations_all_C1","muStations_all, cent. 0-10%; muStations; Entries",10,0,10);	
  muStations_all[2] = new TH1D("muStations_all_C2","muStations_all, cent. 10-30%; muStations; Entries",10,0,10);	
  muStations_all[3] = new TH1D("muStations_all_C3","muStations_all, cent. 30-50%; muStations; Entries",10,0,10);	
  muStations_all[4] = new TH1D("muStations_all_C4","muStations_all, cent. 50-90%; muStations; Entries",10,0,10);	
	
  muMuonHits_all[0] = new TH1D("muMuonHits_all_C0","muMuonHits_all, cent. 0-90%; muMuonHits; Entries",30,0,30);	
  muMuonHits_all[1] = new TH1D("muMuonHits_all_C1","muMuonHits_all, cent. 0-10%; muMuonHits; Entries",30,0,30);	
  muMuonHits_all[2] = new TH1D("muMuonHits_all_C2","muMuonHits_all, cent. 10-30%; muMuonHits; Entries",30,0,30);	
  muMuonHits_all[3] = new TH1D("muMuonHits_all_C3","muMuonHits_all, cent. 30-50%; muMuonHits; Entries",30,0,30);	
  muMuonHits_all[4] = new TH1D("muMuonHits_all_C4","muMuonHits_all, cent. 50-90%; muMuonHits; Entries",30,0,30);	
	
	
  double muonPtCutoff_qualityCuts = 14.0;
  
  // printIntroduction_PYTHIAHYDJET_scan_V3p7();
  readConfig();


  TFile *f = TFile::Open(input);
  cout << "	File opened!" << endl;
  auto em = new eventMap(f);
  em->isMC = isMC_status;
  em->AASetup = AASetup_status;
  cout << "	Initializing variables ... " << endl;
  em->init();
  cout << "	Loading jet..." << endl;
  em->loadJet(jetTreeString);
  cout << "	Loading muon..." << endl;
  em->loadMuon(muonTreeString);
  cout << "	Loading muon triggers..." << endl;
  em->loadMuonTrigger(hltString);
  //cout << "	Loading tracks..." << endl;
  //em->loadTrack();
  cout << "	Loading gen particles..." << endl;
  em->loadGenParticle();
  // cout << "	Variables initilized!" << endl << endl ;
  int NEvents = em->evtTree->GetEntries();
  cout << "	Number of events = " << NEvents << endl;
  int NJets = em->recoJetTree->GetEntries();
  cout << "     Number of jets = " << NJets << endl;

  // define event filters
  em->regEventFilter(NeventFilters_HardProbes, eventFilters_HardProbes);

 
  // event loop
  int eventCounter = 0;
  int evi_frac = 0;
  for(int evi = 0; evi < NEvents; evi++){

    if(evi == 0) cout << "Processing events..." << endl;

    em->getEvent(evi); // load event info from eventMap

    if((100*evi / NEvents) % 5 == 0 && (100*evi / NEvents) > evi_frac){

      cout << "evt frac: " << evi_frac << "%" << endl;

    }

    evi_frac = 100*evi / NEvents;

    // global event cuts
    if(fabs(em->vz) > 15.0 || em->hiBin > 160 || em->hiBin < 0) continue;
    if(em->checkEventFilter()) continue;
    
    

    // int triggerDecision = em->HLT_HIL3Mu5_NHitQ10_v1;
    // int triggerDecision_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl;

    // int triggerDecision = em->HLT_HIL3Mu7_NHitQ10_v1;
    // int triggerDecision_Prescl = em->HLT_HIL3Mu7_NHitQ10_v1_Prescl;

    int triggerDecision = em->HLT_HIL3Mu12_v1;
    int triggerDecision_Prescl = em->HLT_HIL3Mu12_v1_Prescl;

    double w = 1.0;
    double w_trig = 1.0 * triggerDecision_Prescl;

    
    for(int m = 0; m < em->nMu; m++){

      double muEta = em->muEta->at(m); 
      double muPt = em->muPt->at(m);

      // muon kinematic cuts
      if(fabs(muEta) > 2.0) continue;

      // muon quality cuts
      /*
	if(!isQualityMuon_hybridSoft(em->muChi2NDF->at(m), 
	em->muInnerD0->at(m), 
	em->muInnerDz->at(m), 
	em->muPixelHits->at(m), 
	em->muIsTracker->at(m), 
	em->muIsGlobal->at(m), 
	em->muTrkLayers->at(m))) continue;
      */
      /*
	if(!isQualityMuon_tight_muMuonHits10(em->muChi2NDF->at(m),
	em->muInnerD0->at(m),
	em->muInnerDz->at(m),
	em->muMuonHits->at(m),
	em->muPixelHits->at(m),
	em->muIsGlobal->at(m),
	em->muIsPF->at(m),
	em->muStations->at(m),
	em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts
      */

      //cout << "muMuonHits = " << em->muMuonHits->at(m) << endl;
			
      /*			
				if(!isQualityMuon_hybridSoft_muTrkLayers10(em->muChi2NDF->at(m), 
				em->muInnerD0->at(m), 
				em->muInnerDz->at(m), 
				em->muPixelHits->at(m), 
				em->muIsTracker->at(m), 
				em->muIsGlobal->at(m), 
				em->muTrkLayers->at(m))) continue;
      */	
									      
      if(!isQualityMuon_tight(em->muChi2NDF->at(m),
			      em->muInnerD0->at(m),
			      em->muInnerDz->at(m),
			      em->muMuonHits->at(m),
			      em->muPixelHits->at(m),
			      em->muIsGlobal->at(m),
			      em->muIsPF->at(m),
			      em->muStations->at(m),
			      em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts
						      
						    
      /*
	if(!isQualityMuon_tight_muTrkLayers10(em->muChi2NDF->at(m),
	em->muInnerD0->at(m),
	em->muInnerDz->at(m),
	em->muMuonHits->at(m),
	em->muPixelHits->at(m),
	em->muIsGlobal->at(m),
	em->muIsPF->at(m),
	em->muStations->at(m),
	em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts
      */
			


      /*
	if(!isQualityMuon_tight_muTrkLayers10_muMuonHits10(em->muChi2NDF->at(m),
	em->muInnerD0->at(m),
	em->muInnerDz->at(m),
	em->muMuonHits->at(m),
	em->muPixelHits->at(m),
	em->muIsGlobal->at(m),
	em->muIsPF->at(m),
	em->muStations->at(m),
	em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts
      */
			
      /*			
				if(!isQualityMuon_experimental(em->muChi2NDF->at(m),
				em->muInnerD0->at(m),
				em->muInnerDz->at(m),
				em->muMuonHits->at(m),
				em->muPixelHits->at(m),
				em->muIsGlobal->at(m),
				em->muIsTracker->at(m),
				em->muIsPF->at(m),
				em->muStations->at(m),
				em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts
      */
			
			
			
			
      if(triggerDecision == 1){

	muPt_trigOn[0]->Fill(muPt,w_trig);
	if(muPt > muonPtCutoff_qualityCuts){
	  muEta_trigOn[0]->Fill(muEta,w_trig);
	  muPhi_trigOn[0]->Fill(em->muPhi->at(m),w_trig);
	  muChi2NDF_trigOn[0]->Fill(em->muChi2NDF->at(m),w);
	  muInnerD0_trigOn[0]->Fill(em->muInnerD0->at(m),w);
	  muInnerDz_trigOn[0]->Fill(em->muInnerDz->at(m),w);
	  muPixelHits_trigOn[0]->Fill(em->muPixelHits->at(m),w);
	  muIsTracker_trigOn[0]->Fill(em->muIsTracker->at(m),w);
	  muIsGlobal_trigOn[0]->Fill(em->muIsGlobal->at(m),w);
	  muTrkLayers_trigOn[0]->Fill(em->muTrkLayers->at(m),w);
	  muIsPF_trigOn[0]->Fill(em->muIsPF->at(m),w);
	  muStations_trigOn[0]->Fill(em->muStations->at(m),w);
	  muMuonHits_trigOn[0]->Fill(em->muMuonHits->at(m),w);
	}
	if(em->hiBin >= 0 && em->hiBin <=20){
	  muPt_trigOn[1]->Fill(muPt,w_trig);
	  if(muPt > muonPtCutoff_qualityCuts){
	    muEta_trigOn[1]->Fill(muEta,w_trig);
	    muPhi_trigOn[1]->Fill(em->muPhi->at(m),w_trig);
	    muChi2NDF_trigOn[1]->Fill(em->muChi2NDF->at(m),w);
	    muInnerD0_trigOn[1]->Fill(em->muInnerD0->at(m),w);
	    muInnerDz_trigOn[1]->Fill(em->muInnerDz->at(m),w);
	    muPixelHits_trigOn[1]->Fill(em->muPixelHits->at(m),w);
	    muIsTracker_trigOn[1]->Fill(em->muIsTracker->at(m),w);
	    muIsGlobal_trigOn[1]->Fill(em->muIsGlobal->at(m),w);
	    muTrkLayers_trigOn[1]->Fill(em->muTrkLayers->at(m),w);
	    muIsPF_trigOn[1]->Fill(em->muIsPF->at(m),w);
	    muStations_trigOn[1]->Fill(em->muStations->at(m),w);
	    muMuonHits_trigOn[1]->Fill(em->muMuonHits->at(m),w);
	  }
	}
	if(em->hiBin > 20 && em->hiBin <=60){
	  muPt_trigOn[2]->Fill(muPt,w_trig);
	  if(muPt > muonPtCutoff_qualityCuts){
	    muEta_trigOn[2]->Fill(muEta,w_trig);
	    muPhi_trigOn[2]->Fill(em->muPhi->at(m),w);
	    muChi2NDF_trigOn[2]->Fill(em->muChi2NDF->at(m),w);
	    muInnerD0_trigOn[2]->Fill(em->muInnerD0->at(m),w);
	    muInnerDz_trigOn[2]->Fill(em->muInnerDz->at(m),w);
	    muPixelHits_trigOn[2]->Fill(em->muPixelHits->at(m),w);
	    muIsTracker_trigOn[2]->Fill(em->muIsTracker->at(m),w);
	    muIsGlobal_trigOn[2]->Fill(em->muIsGlobal->at(m),w);
	    muTrkLayers_trigOn[2]->Fill(em->muTrkLayers->at(m),w);
	    muIsPF_trigOn[2]->Fill(em->muIsPF->at(m),w);
	    muStations_trigOn[2]->Fill(em->muStations->at(m),w);
	    muMuonHits_trigOn[2]->Fill(em->muMuonHits->at(m),w);
	  }
	}
	if(em->hiBin > 60 && em->hiBin <=100){
	  muPt_trigOn[3]->Fill(muPt,w_trig);
	  if(muPt > muonPtCutoff_qualityCuts){
	    muEta_trigOn[3]->Fill(muEta,w_trig);
	    muPhi_trigOn[3]->Fill(em->muPhi->at(m),w_trig);
	    muChi2NDF_trigOn[3]->Fill(em->muChi2NDF->at(m),w);
	    muInnerD0_trigOn[3]->Fill(em->muInnerD0->at(m),w);
	    muInnerDz_trigOn[3]->Fill(em->muInnerDz->at(m),w);
	    muPixelHits_trigOn[3]->Fill(em->muPixelHits->at(m),w);
	    muIsTracker_trigOn[3]->Fill(em->muIsTracker->at(m),w);
	    muIsGlobal_trigOn[3]->Fill(em->muIsGlobal->at(m),w);
	    muTrkLayers_trigOn[3]->Fill(em->muTrkLayers->at(m),w);
	    muIsPF_trigOn[3]->Fill(em->muIsPF->at(m),w);
	    muStations_trigOn[3]->Fill(em->muStations->at(m),w);
	    muMuonHits_trigOn[3]->Fill(em->muMuonHits->at(m),w);
	  }
	}
	if(em->hiBin > 100 && em->hiBin <=160){
	  muPt_trigOn[4]->Fill(muPt,w_trig);
	  if(muPt > muonPtCutoff_qualityCuts){
	    muEta_trigOn[4]->Fill(muEta,w_trig);
	    muPhi_trigOn[4]->Fill(em->muPhi->at(m),w);
	    muChi2NDF_trigOn[4]->Fill(em->muChi2NDF->at(m),w);
	    muInnerD0_trigOn[4]->Fill(em->muInnerD0->at(m),w);
	    muInnerDz_trigOn[4]->Fill(em->muInnerDz->at(m),w);
	    muPixelHits_trigOn[4]->Fill(em->muPixelHits->at(m),w);
	    muIsTracker_trigOn[4]->Fill(em->muIsTracker->at(m),w);
	    muIsGlobal_trigOn[4]->Fill(em->muIsGlobal->at(m),w);
	    muTrkLayers_trigOn[4]->Fill(em->muTrkLayers->at(m),w);
	    muIsPF_trigOn[4]->Fill(em->muIsPF->at(m),w);
	    muStations_trigOn[4]->Fill(em->muStations->at(m),w);
	    muMuonHits_trigOn[4]->Fill(em->muMuonHits->at(m),w);
	  }
	}
      }

			
      if(triggerDecision==0){

				
	muPt_trigOff[0]->Fill(muPt,w);
	if(muPt > muonPtCutoff_qualityCuts){
	  muEta_trigOff[0]->Fill(muEta,w);
	  muPhi_trigOff[0]->Fill(em->muPhi->at(m),w);
	  muChi2NDF_trigOff[0]->Fill(em->muChi2NDF->at(m),w);
	  muInnerD0_trigOff[0]->Fill(em->muInnerD0->at(m),w);
	  muInnerDz_trigOff[0]->Fill(em->muInnerDz->at(m),w);
	  muPixelHits_trigOff[0]->Fill(em->muPixelHits->at(m),w);
	  muIsTracker_trigOff[0]->Fill(em->muIsTracker->at(m),w);
	  muIsGlobal_trigOff[0]->Fill(em->muIsGlobal->at(m),w);
	  muTrkLayers_trigOff[0]->Fill(em->muTrkLayers->at(m),w);
	  muIsPF_trigOff[0]->Fill(em->muIsPF->at(m),w);
	  muStations_trigOff[0]->Fill(em->muStations->at(m),w);
	  muMuonHits_trigOff[0]->Fill(em->muMuonHits->at(m),w);
	}
	if(em->hiBin >= 0 && em->hiBin <=20){
	  muPt_trigOff[1]->Fill(muPt,w);
	  if(muPt > muonPtCutoff_qualityCuts){
	    muEta_trigOff[1]->Fill(muEta,w);
	    muPhi_trigOff[1]->Fill(em->muPhi->at(m),w);
	    muChi2NDF_trigOff[1]->Fill(em->muChi2NDF->at(m),w);
	    muInnerD0_trigOff[1]->Fill(em->muInnerD0->at(m),w);
	    muInnerDz_trigOff[1]->Fill(em->muInnerDz->at(m),w);
	    muPixelHits_trigOff[1]->Fill(em->muPixelHits->at(m),w);
	    muIsTracker_trigOff[1]->Fill(em->muIsTracker->at(m),w);
	    muIsGlobal_trigOff[1]->Fill(em->muIsGlobal->at(m),w);
	    muTrkLayers_trigOff[1]->Fill(em->muTrkLayers->at(m),w);
	    muIsPF_trigOff[1]->Fill(em->muIsPF->at(m),w);
	    muStations_trigOff[1]->Fill(em->muStations->at(m),w);
	    muMuonHits_trigOff[1]->Fill(em->muMuonHits->at(m),w);
	  }
	}
	if(em->hiBin > 20 && em->hiBin <=60){
	  muPt_trigOff[2]->Fill(muPt,w);
	  if(muPt > muonPtCutoff_qualityCuts){
	    muEta_trigOff[2]->Fill(muEta,w);
	    muPhi_trigOff[2]->Fill(em->muPhi->at(m),w);
	    muChi2NDF_trigOff[2]->Fill(em->muChi2NDF->at(m),w);
	    muInnerD0_trigOff[2]->Fill(em->muInnerD0->at(m),w);
	    muInnerDz_trigOff[2]->Fill(em->muInnerDz->at(m),w);
	    muPixelHits_trigOff[2]->Fill(em->muPixelHits->at(m),w);
	    muIsTracker_trigOff[2]->Fill(em->muIsTracker->at(m),w);
	    muIsGlobal_trigOff[2]->Fill(em->muIsGlobal->at(m),w);
	    muTrkLayers_trigOff[2]->Fill(em->muTrkLayers->at(m),w);
	    muIsPF_trigOff[2]->Fill(em->muIsPF->at(m),w);
	    muStations_trigOff[2]->Fill(em->muStations->at(m),w);
	    muMuonHits_trigOff[2]->Fill(em->muMuonHits->at(m),w);
	  }
	}
	if(em->hiBin > 60 && em->hiBin <=100){
	  muPt_trigOff[3]->Fill(muPt,w);
	  if(muPt > muonPtCutoff_qualityCuts){
	    muEta_trigOff[3]->Fill(muEta,w);
	    muPhi_trigOff[3]->Fill(em->muPhi->at(m),w);
	    muChi2NDF_trigOff[3]->Fill(em->muChi2NDF->at(m),w);
	    muInnerD0_trigOff[3]->Fill(em->muInnerD0->at(m),w);
	    muInnerDz_trigOff[3]->Fill(em->muInnerDz->at(m),w);
	    muPixelHits_trigOff[3]->Fill(em->muPixelHits->at(m),w);
	    muIsTracker_trigOff[3]->Fill(em->muIsTracker->at(m),w);
	    muIsGlobal_trigOff[3]->Fill(em->muIsGlobal->at(m),w);
	    muTrkLayers_trigOff[3]->Fill(em->muTrkLayers->at(m),w);
	    muIsPF_trigOff[3]->Fill(em->muIsPF->at(m),w);
	    muStations_trigOff[3]->Fill(em->muStations->at(m),w);
	    muMuonHits_trigOff[3]->Fill(em->muMuonHits->at(m),w);
	  }
	}
	if(em->hiBin > 100 && em->hiBin <=160){
	  muPt_trigOff[4]->Fill(muPt,w);
	  if(muPt > muonPtCutoff_qualityCuts){
	    muEta_trigOff[4]->Fill(muEta,w);
	    muPhi_trigOff[4]->Fill(em->muPhi->at(m),w);
	    muChi2NDF_trigOff[4]->Fill(em->muChi2NDF->at(m),w);
	    muInnerD0_trigOff[4]->Fill(em->muInnerD0->at(m),w);
	    muInnerDz_trigOff[4]->Fill(em->muInnerDz->at(m),w);
	    muPixelHits_trigOff[4]->Fill(em->muPixelHits->at(m),w);
	    muIsTracker_trigOff[4]->Fill(em->muIsTracker->at(m),w);
	    muIsGlobal_trigOff[4]->Fill(em->muIsGlobal->at(m),w);
	    muTrkLayers_trigOff[4]->Fill(em->muTrkLayers->at(m),w);
	    muIsPF_trigOff[4]->Fill(em->muIsPF->at(m),w);
	    muStations_trigOff[4]->Fill(em->muStations->at(m),w);
	    muMuonHits_trigOff[4]->Fill(em->muMuonHits->at(m),w);
	  }
	}

      }


      muPt_all[0]->Fill(muPt,w);

      if(muPt > muonPtCutoff_qualityCuts){
	muEta_all[0]->Fill(muEta,w);
	muPhi_all[0]->Fill(em->muPhi->at(m),w);
	muChi2NDF_all[0]->Fill(em->muChi2NDF->at(m),w);
	muInnerD0_all[0]->Fill(em->muInnerD0->at(m),w);
	muInnerDz_all[0]->Fill(em->muInnerDz->at(m),w);
	muPixelHits_all[0]->Fill(em->muPixelHits->at(m),w);
	muIsTracker_all[0]->Fill(em->muIsTracker->at(m),w);
	muIsGlobal_all[0]->Fill(em->muIsGlobal->at(m),w);
	muTrkLayers_all[0]->Fill(em->muTrkLayers->at(m),w);
	muIsPF_all[0]->Fill(em->muIsPF->at(m),w);
	muStations_all[0]->Fill(em->muStations->at(m),w);
	muMuonHits_all[0]->Fill(em->muMuonHits->at(m),w);
      }
      if(em->hiBin >= 0 && em->hiBin <=20){
	muPt_all[1]->Fill(muPt,w);
	if(muPt > muonPtCutoff_qualityCuts){
	  muEta_all[1]->Fill(muEta,w);
	  muPhi_all[1]->Fill(em->muPhi->at(m),w);
	  muChi2NDF_all[1]->Fill(em->muChi2NDF->at(m),w);
	  muInnerD0_all[1]->Fill(em->muInnerD0->at(m),w);
	  muInnerDz_all[1]->Fill(em->muInnerDz->at(m),w);
	  muPixelHits_all[1]->Fill(em->muPixelHits->at(m),w);
	  muIsTracker_all[1]->Fill(em->muIsTracker->at(m),w);
	  muIsGlobal_all[1]->Fill(em->muIsGlobal->at(m),w);
	  muTrkLayers_all[1]->Fill(em->muTrkLayers->at(m),w);
	  muIsPF_all[1]->Fill(em->muIsPF->at(m),w);
	  muStations_all[1]->Fill(em->muStations->at(m),w);
	  muMuonHits_all[1]->Fill(em->muMuonHits->at(m),w);
	}
      }
      if(em->hiBin > 20 && em->hiBin <=60){
	muPt_all[2]->Fill(muPt,w);
	if(muPt > muonPtCutoff_qualityCuts){
	  muEta_all[2]->Fill(muEta,w);
	  muPhi_all[2]->Fill(em->muPhi->at(m),w);
	  muChi2NDF_all[2]->Fill(em->muChi2NDF->at(m),w);
	  muInnerD0_all[2]->Fill(em->muInnerD0->at(m),w);
	  muInnerDz_all[2]->Fill(em->muInnerDz->at(m),w);
	  muPixelHits_all[2]->Fill(em->muPixelHits->at(m),w);
	  muIsTracker_all[2]->Fill(em->muIsTracker->at(m),w);
	  muIsGlobal_all[2]->Fill(em->muIsGlobal->at(m),w);
	  muTrkLayers_all[2]->Fill(em->muTrkLayers->at(m),w);
	  muIsPF_all[2]->Fill(em->muIsPF->at(m),w);
	  muStations_all[2]->Fill(em->muStations->at(m),w);
	  muMuonHits_all[2]->Fill(em->muMuonHits->at(m),w);
	}
      }
      if(em->hiBin > 60 && em->hiBin <=100){
	muPt_all[3]->Fill(muPt,w);
	if(muPt > muonPtCutoff_qualityCuts){
	  muEta_all[3]->Fill(muEta,w);
	  muPhi_all[3]->Fill(em->muPhi->at(m),w);
	  muChi2NDF_all[3]->Fill(em->muChi2NDF->at(m),w);
	  muInnerD0_all[3]->Fill(em->muInnerD0->at(m),w);
	  muInnerDz_all[3]->Fill(em->muInnerDz->at(m),w);
	  muPixelHits_all[3]->Fill(em->muPixelHits->at(m),w);
	  muIsTracker_all[3]->Fill(em->muIsTracker->at(m),w);
	  muIsGlobal_all[3]->Fill(em->muIsGlobal->at(m),w);
	  muTrkLayers_all[3]->Fill(em->muTrkLayers->at(m),w);
	  muIsPF_all[3]->Fill(em->muIsPF->at(m),w);
	  muStations_all[3]->Fill(em->muStations->at(m),w);
	  muMuonHits_all[3]->Fill(em->muMuonHits->at(m),w);
	}
      }
      if(em->hiBin > 100 && em->hiBin <=160){
	muPt_all[4]->Fill(muPt,w);
	if(muPt > muonPtCutoff_qualityCuts){
	  muEta_all[4]->Fill(muEta,w);
	  muPhi_all[4]->Fill(em->muPhi->at(m),w);
	  muChi2NDF_all[4]->Fill(em->muChi2NDF->at(m),w);
	  muInnerD0_all[4]->Fill(em->muInnerD0->at(m),w);
	  muInnerDz_all[4]->Fill(em->muInnerDz->at(m),w);
	  muPixelHits_all[4]->Fill(em->muPixelHits->at(m),w);
	  muIsTracker_all[4]->Fill(em->muIsTracker->at(m),w);
	  muIsGlobal_all[4]->Fill(em->muIsGlobal->at(m),w);
	  muTrkLayers_all[4]->Fill(em->muTrkLayers->at(m),w);
	  muIsPF_all[4]->Fill(em->muIsPF->at(m),w);
	  muStations_all[4]->Fill(em->muStations->at(m),w);
	  muMuonHits_all[4]->Fill(em->muMuonHits->at(m),w);
	}
      }

			
    }



  }

  TFile *wf = TFile::Open(output,"recreate");	

  for(int i = 0; i < 5; i++){

    muPt_trigOn[i]->Write();
    muEta_trigOn[i]->Write();
    muPhi_trigOn[i]->Write();
    muChi2NDF_trigOn[i]->Write();
    muInnerD0_trigOn[i]->Write();
    muInnerDz_trigOn[i]->Write();
    muPixelHits_trigOn[i]->Write();
    muIsTracker_trigOn[i]->Write();
    muIsGlobal_trigOn[i]->Write();
    muTrkLayers_trigOn[i]->Write();
    muIsPF_trigOn[i]->Write();
    muStations_trigOn[i]->Write();
    muMuonHits_trigOn[i]->Write();

    muPt_trigOff[i]->Write();
    muEta_trigOff[i]->Write();
    muPhi_trigOff[i]->Write();
    muChi2NDF_trigOff[i]->Write();
    muInnerD0_trigOff[i]->Write();
    muInnerDz_trigOff[i]->Write();
    muPixelHits_trigOff[i]->Write();
    muIsTracker_trigOff[i]->Write();
    muIsGlobal_trigOff[i]->Write();
    muTrkLayers_trigOff[i]->Write();
    muIsPF_trigOff[i]->Write();
    muStations_trigOff[i]->Write();
    muMuonHits_trigOff[i]->Write();
		
    muPt_all[i]->Write();
    muEta_all[i]->Write();
    muPhi_all[i]->Write();
    muChi2NDF_all[i]->Write();
    muInnerD0_all[i]->Write();
    muInnerDz_all[i]->Write();
    muPixelHits_all[i]->Write();
    muIsTracker_all[i]->Write();
    muIsGlobal_all[i]->Write();
    muTrkLayers_all[i]->Write();
    muIsPF_all[i]->Write();
    muStations_all[i]->Write();
    muMuonHits_all[i]->Write();




  }

  wf->Close();
  return;
	

}
