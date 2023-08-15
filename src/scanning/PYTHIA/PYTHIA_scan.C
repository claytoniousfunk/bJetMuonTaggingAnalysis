
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

// User includes

// event map
#include "../../../../eventMap/eventMap.h"
// jet corrector
#include "../../../../JetEnergyCorrections/JetCorrector.h"
// jet uncertainty
#include "../../../../JetEnergyCorrections/JetUncertainty.h"
// general analysis variables
#include "../../../../headers/AnalysisSetupV2p1.h"
// vz-fit parameters
#include "../../../../headers/fitParameters/vzFitParams_PYTHIA.h"
// hiBin-fit parameters
#include "../../../../headers/fitParameters/hiBinFitParams.h"

TF1 *fitFxn_hiBin, *fitFxn_vz;
// vz-fit function
#include "../../../../headers/fitFunctions/fitFxn_vz_PYTHIA.h"
// hiBin-fit function
#include "../../../../headers/fitFunctions/fitFxn_hiBin.h"

// eta-phi mask function
#include "../../../../headers/functions/etaPhiMask.h"
// getDr function
#include "../../../../headers/functions/getDr.h"
// getJetPtBin function
#include "../../../../headers/functions/getJetPtBin.h"
// getCentBin function
#include "../../../../headers/functions/getCentBin_v2.h"
// getPtRel function
#include "../../../../headers/functions/getPtRel.h"
// isQualityMuon_hybridSoft function
#include "../../../../headers/functions/isQualityMuon_hybridSoft.h"
// isQualityMuon_tight function
#include "../../../../headers/functions/isQualityMuon_tight.h"
// isWDecayMuon function
#include "../../../../headers/functions/isWDecayMuon.h"
// triggerIsOn function
#include "../../../../headers/functions/triggerIsOn.h"
// pthat filter function
#include "../../../../headers/functions/passesLeadingGenJetPthatFilter.h"
// JetTrkMax filter function
#include "../../../../headers/functions/passesJetTrkMaxFilter.h"
// print introduction
#include "../../../../headers/introductions/printIntroduction_PYTHIA_scan_V3p7.h"
// analysis config
#include "../../../../headers/config/config_PYTHIA.h"
// read config
#include "../../../../headers/config/readConfig.h"




//~~~~~~~~~~~  initialize histograms ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// >>>>>>>>>> Reco jets
// ----------------------------------------- event histograms -----------------
TH1D *h_vz;
TH1D *h_vz_inclRecoMuonTag;
TH1D *h_vz_inclRecoMuonTag_triggerOn;
// ------------------------------- incl. reco jets per flavor -----------------
TH2D *h_inclRecoJetPt_flavor;
TH2D *h_inclRecoJetEta_flavor;
TH2D *h_inclRecoJetPhi_flavor;
TH2D *h_inclRecoJetPt_inclRecoJetEta;
TH2D *h_inclRecoJetPt_inclRecoJetPhi;
TH2D *h_inclRecoJetEta_inclRecoJetPhi[NJetPtIndices];
// ------------------- incl. reco jets tagged to gen muon by flavor -----------
TH2D *h_inclRecoJetPt_inclGenMuonTag_flavor;
TH2D *h_inclRecoJetEta_inclGenMuonTag_flavor;
TH2D *h_inclRecoJetPhi_inclGenMuonTag_flavor;
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag;
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag;
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[NJetPtIndices];
// ------------------- incl. reco jets tagged to incl. gen muon by flavor -----
TH2D *h_inclRecoJetPt_inclRecoMuonTag_flavor;
TH2D *h_inclRecoJetEta_inclRecoMuonTag_flavor;
TH2D *h_inclRecoJetPhi_inclRecoMuonTag_flavor;
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag;
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag;
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[NJetPtIndices];
// ------------------- incl. reco jets tagged to incl. reco muon by flavor ----
TH2D *h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor;
TH2D *h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor;
TH2D *h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor;
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn;
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn;
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[NJetPtIndices];
// ----------------- incl. reco jets tagged to matched reco muon by flavor ----
TH2D *h_inclRecoJetPt_matchedRecoMuonTag_flavor;
TH2D *h_inclRecoJetEta_matchedRecoMuonTag_flavor;
TH2D *h_inclRecoJetPhi_matchedRecoMuonTag_flavor;
TH2D *h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag;
TH2D *h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag;
TH2D *h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[NJetPtIndices];
// ----- incl. reco jets tagged to matched reco muon by flavor, trigger on ----
TH2D *h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor;
TH2D *h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor;
TH2D *h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor;
TH2D *h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn;
TH2D *h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn;
TH2D *h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[NJetPtIndices];
// ------------------------------- in-jet reco muons by flavor, trigger on ----
TH2D *h_muptrel_inclRecoMuonTag_triggerOn_flavor[NJetPtIndices];
TH2D *h_mupt_inclRecoMuonTag_triggerOn_flavor[NJetPtIndices];
TH2D *h_mueta_inclRecoMuonTag_triggerOn_flavor[NJetPtIndices];
TH2D *h_muphi_inclRecoMuonTag_triggerOn_flavor[NJetPtIndices];
// >>>>>>>>>> Gen jets
// ------------------------------- incl. gen jets per flavor ------------------
TH2D *h_inclGenJetPt_flavor;
// ------------------- incl. gen jets tagged to incl. gen muon by flavor ------
TH2D *h_inclGenJetPt_inclGenMuonTag_flavor;
// ------------------- incl. gen jets tagged to incl. reco muon by flavor -----
TH2D *h_inclGenJetPt_inclRecoMuonTag_flavor;
// ------- incl. gen jets tagged to incl. reco muon by flavor, trigger on -----
TH2D *h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor;
// ----------------- incl. gen jets tagged to matched reco muon by flavor -----
TH2D *h_inclGenJetPt_matchedRecoMuonTag_flavor;
// ----- incl. gen jets tagged to matched reco muon by flavor, trigger on -----
TH2D *h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor;
// ------------------------------- in-jet reco muons by flavor, trigger on ----
TH2D *h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[NJetPtIndices];
TH2D *h_recoJetPt_pthat;
TH2D *h_genJetPt_pthat;


void PYTHIA_scan(TString input = "/eos/user/c/cbennett/forests/PYTHIA_forest_10Aug22/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/crab_PYTHIA_forest_10Aug22/220810_170721/0000/HiForestAOD_100.root", TString output = "out.root"){


  printIntroduction_PYTHIA_scan_V3p7();
  readConfig();

  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt"); // LXPLUS
  JetCorrector JEC(Files);


  JetUncertainty JEU("../../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_Uncertainty_AK4PF.txt");


  
  h_vz = new TH1D("h_vz","vz, events with inclRecoJets",NVzBins,vzMin,vzMax);
  h_vz_inclRecoMuonTag = new TH1D("h_vz_inclRecoMuonTag","vz, events with inclRecoJets-inclRecoMuonTag",NVzBins,vzMin,vzMax);
  h_vz_inclRecoMuonTag_triggerOn = new TH1D("h_vz_inclRecoMuonTag_triggerOn","vz, events with inclRecoJets-inclRecoMuonTag-triggerOn",NVzBins,vzMin,vzMax);
  
	
  // Define histograms
  h_inclRecoJetPt_flavor = new TH2D("h_inclRecoJetPt_flavor","JetFlavorID vs incl. reco p_{T}^{jet}",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclRecoJetEta_flavor = new TH2D("h_inclRecoJetEta_flavor","JetFlavorID vs incl. reco #eta^{jet}",NEtaBins,etaMin,etaMax,27,-5,22);
  h_inclRecoJetPhi_flavor = new TH2D("h_inclRecoJetPhi_flavor","JetFlavorID vs incl. reco #phi^{jet}",NPhiBins,phiMin,phiMax,27,-5,22);
  h_inclRecoJetPt_inclRecoJetEta = new TH2D("h_inclRecoJetPt_inclRecoJetEta","incl. reco p_{T}^{jet} vs. incl. reco #eta^{jet}",NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
  h_inclRecoJetPt_inclRecoJetPhi = new TH2D("h_inclRecoJetPt_inclRecoJetPhi","incl. reco p_{T}^{jet} vs. incl. reco #phi^{jet}",NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);

  h_inclRecoJetPt_inclGenMuonTag_flavor = new TH2D("h_inclRecoJetPt_inclGenMuonTag_flavor","JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. gen muon",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclRecoJetEta_inclGenMuonTag_flavor = new TH2D("h_inclRecoJetEta_inclGenMuonTag_flavor","JetFlavorID vs incl. reco #eta^{jet}, tagged with incl. gen muon",NEtaBins,etaMin,etaMax,27,-5,22);
  h_inclRecoJetPhi_inclGenMuonTag_flavor = new TH2D("h_inclRecoJetPhi_inclGenMuonTag_flavor","JetFlavorID vs incl. reco #phi^{jet}, tagged with incl. gen muon",NPhiBins,phiMin,phiMax,27,-5,22);
  h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag = new TH2D("h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag","incl. reco p_{T}^{jet} vs. incl. reco #eta^{jet}, tagged with incl. gen muon",NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
  h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag = new TH2D("h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag","incl. reco p_{T}^{jet} vs. incl. reco #phi^{jet}, tagged with incl. gen muon",NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
  
  h_inclRecoJetPt_inclRecoMuonTag_flavor = new TH2D("h_inclRecoJetPt_inclRecoMuonTag_flavor","JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclRecoJetEta_inclRecoMuonTag_flavor = new TH2D("h_inclRecoJetEta_inclRecoMuonTag_flavor","JetFlavorID vs incl. reco #eta^{jet}, tagged with incl. reco muon",NEtaBins,etaMin,etaMax,27,-5,22);
  h_inclRecoJetPhi_inclRecoMuonTag_flavor = new TH2D("h_inclRecoJetPhi_inclRecoMuonTag_flavor","JetFlavorID vs incl. reco #phi^{jet}, tagged with incl. reco muon",NPhiBins,phiMin,phiMax,27,-5,22);
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag = new TH2D("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag","incl. reco p_{T}^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag = new TH2D("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag","incl. reco p_{T}^{jet} vs. incl. reco #phi^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);

  h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor = new TH2D("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor","JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor = new TH2D("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor","JetFlavorID vs incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON",NEtaBins,etaMin,etaMax,27,-5,22);
  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor = new TH2D("h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor","JetFlavorID vs incl. reco #phi^{jet}, tagged with incl. reco muon, trigger ON",NPhiBins,phiMin,phiMax,27,-5,22);
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn = new TH2D("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn","incl. reco p_{T}^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON",NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn = new TH2D("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn","incl. reco p_{T}^{jet} vs. incl. reco #phi^{jet}, tagged with incl. reco muon, trigger ON",NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
  
  h_inclRecoJetPt_matchedRecoMuonTag_flavor = new TH2D("h_inclRecoJetPt_matchedRecoMuonTag_flavor","JetFlavorID vs incl. reco p_{T}^{jet}, tagged with matched reco muon",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclRecoJetEta_matchedRecoMuonTag_flavor = new TH2D("h_inclRecoJetEta_matchedRecoMuonTag_flavor","JetFlavorID vs incl. reco #eta^{jet}, tagged with matched reco muon",NEtaBins,etaMin,etaMax,27,-5,22);
  h_inclRecoJetPhi_matchedRecoMuonTag_flavor = new TH2D("h_inclRecoJetPhi_matchedRecoMuonTag_flavor","JetFlavorID vs incl. reco #phi^{jet}, tagged with matched. reco muon",NPhiBins,phiMin,phiMax,27,-5,22);
  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag = new TH2D("h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag","incl. reco p_{T}^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon",NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag = new TH2D("h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag","incl. reco p_{T}^{jet} vs. incl. reco #phi^{jet}, tagged with matched reco muon",NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);

  h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor = new TH2D("h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor","JetFlavorID vs incl. reco p_{T}^{jet}, tagged with matched reco muon, trigger ON",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor = new TH2D("h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor","JetFlavorID vs incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON",NEtaBins,etaMin,etaMax,27,-5,22);
  h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor = new TH2D("h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor","JetFlavorID vs incl. reco #phi^{jet}, tagged with matched. reco muon, trigger ON",NPhiBins,phiMin,phiMax,27,-5,22);
  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn = new TH2D("h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn","incl. reco p_{T}^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON",NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn = new TH2D("h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn","incl. reco p_{T}^{jet} vs. incl. reco #phi^{jet}, tagged with matched reco muon, trigger ON",NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
  

  h_inclGenJetPt_flavor = new TH2D("h_inclGenJetPt_flavor","JetFlavorID vs incl. gen p_{T}^{jet}",NPtBins,ptMin,ptMax,27,-5,22);

  h_inclGenJetPt_inclGenMuonTag_flavor = new TH2D("h_inclGenJetPt_inclGenMuonTag_flavor","JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. gen muon",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclGenJetPt_inclRecoMuonTag_flavor = new TH2D("h_inclGenJetPt_inclRecoMuonTag_flavor","JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor = new TH2D("h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor","JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. reco muon, trigger ON",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclGenJetPt_matchedRecoMuonTag_flavor = new TH2D("h_inclGenJetPt_matchedRecoMuonTag_flavor","JetFlavorID vs incl. gen p_{T}^{jet}, tagged with matched reco muon",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor = new TH2D("h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor","JetFlavorID vs incl. gen p_{T}^{jet}, tagged with matched reco muon, trigger ON",NPtBins,ptMin,ptMax,27,-5,22);

  h_recoJetPt_pthat = new TH2D("h_recoJetPt_pthat","reco p_{T}^{jet} vs. #hat{p}_{T}, PYTHIA; reco p_{T}^{jet} [GeV]; #hat{p}_{T} [GeV]",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_genJetPt_pthat = new TH2D("h_genJetPt_pthat","gen p_{T}^{jet} vs. #hat{p}_{T}, PYTHIA; gen p_{T}^{jet} [GeV]; #hat{p}_{T} [GeV]",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);

  /////////////  Sumw2 commands
  h_vz->Sumw2();
  h_vz_inclRecoMuonTag->Sumw2();
  h_vz_inclRecoMuonTag_triggerOn->Sumw2();

  h_inclRecoJetPt_flavor->Sumw2();
  h_inclRecoJetEta_flavor->Sumw2();
  h_inclRecoJetPhi_flavor->Sumw2();
  h_inclRecoJetPt_inclRecoJetEta->Sumw2();
  h_inclRecoJetPt_inclRecoJetPhi->Sumw2();

  h_inclRecoJetPt_inclGenMuonTag_flavor->Sumw2();
  h_inclRecoJetEta_inclGenMuonTag_flavor->Sumw2();
  h_inclRecoJetPhi_inclGenMuonTag_flavor->Sumw2();
  h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag->Sumw2();
  h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag->Sumw2();
  
  h_inclRecoJetPt_inclRecoMuonTag_flavor->Sumw2();
  h_inclRecoJetEta_inclRecoMuonTag_flavor->Sumw2();
  h_inclRecoJetPhi_inclRecoMuonTag_flavor->Sumw2();
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag->Sumw2();
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag->Sumw2();

  h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor->Sumw2();
  h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor->Sumw2();
  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor->Sumw2();
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn->Sumw2();
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Sumw2();

  h_inclRecoJetPt_matchedRecoMuonTag_flavor->Sumw2();
  h_inclRecoJetEta_matchedRecoMuonTag_flavor->Sumw2();
  h_inclRecoJetPhi_matchedRecoMuonTag_flavor->Sumw2();
  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag->Sumw2();
  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag->Sumw2();
  
  h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor->Sumw2();
  h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor->Sumw2();
  h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor->Sumw2();
  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn->Sumw2();
  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn->Sumw2();

  h_inclGenJetPt_flavor->Sumw2();
  h_inclGenJetPt_inclGenMuonTag_flavor->Sumw2();
  h_inclGenJetPt_inclRecoMuonTag_flavor->Sumw2();
  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor->Sumw2();
  h_inclGenJetPt_matchedRecoMuonTag_flavor->Sumw2();
  h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor->Sumw2();

  h_recoJetPt_pthat->Sumw2();	
  h_genJetPt_pthat->Sumw2();	

	
  for(int j = 0; j < NJetPtIndices; j++){
	
    //
    if(j==0) {
      h_muptrel_inclRecoMuonTag_triggerOn_flavor[j] = new TH2D(Form("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J%i",j),Form("JetFlavorID vs. p_{T}^{rel}, p_{T}^{jet} %3.0f - %3.0f", jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
      h_mupt_inclRecoMuonTag_triggerOn_flavor[j] = new TH2D(Form("h_mupt_inclRecoMuonTag_triggerOn_flavor_J%i",j),Form("JetFlavorID vs. p_{T}^{#mu}, p_{T}^{jet} %3.0f - %3.0f", jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax,27,-5,22);
      h_mueta_inclRecoMuonTag_triggerOn_flavor[j] = new TH2D(Form("h_mueta_inclRecoMuonTag_triggerOn_flavor_J%i",j),Form("JetFlavorID vs. #eta^{#mu}, p_{T}^{jet} %3.0f - %3.0f", jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax,27,-5,22);
      h_muphi_inclRecoMuonTag_triggerOn_flavor[j] = new TH2D(Form("h_muphi_inclRecoMuonTag_triggerOn_flavor_J%i",j),Form("JetFlavorID vs. #phi^{#mu}, p_{T}^{jet} %3.0f - %3.0f", jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetEta_inclRecoJetPhi[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. gen muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON,  p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
    }
    else {
      h_muptrel_inclRecoMuonTag_triggerOn_flavor[j] = new TH2D(Form("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J%i",j),Form("JetFlavorID vs. p_{T}^{rel}, p_{T}^{jet} %3.0f - %3.0f", jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
      h_mupt_inclRecoMuonTag_triggerOn_flavor[j] = new TH2D(Form("h_mupt_inclRecoMuonTag_triggerOn_flavor_J%i",j),Form("JetFlavorID vs. p_{T}^{#mu}, p_{T}^{jet} %3.0f - %3.0f", jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax,27,-5,22);
      h_mueta_inclRecoMuonTag_triggerOn_flavor[j] = new TH2D(Form("h_mueta_inclRecoMuonTag_triggerOn_flavor_J%i",j),Form("JetFlavorID vs. #eta^{#mu}, p_{T}^{jet} %3.0f - %3.0f", jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax,27,-5,22);
      h_muphi_inclRecoMuonTag_triggerOn_flavor[j] = new TH2D(Form("h_muphi_inclRecoMuonTag_triggerOn_flavor_J%i",j),Form("JetFlavorID vs. #phi^{#mu}, p_{T}^{jet} %3.0f - %3.0f", jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetEta_inclRecoJetPhi[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. gen muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON,  p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      }

    h_muptrel_inclRecoMuonTag_triggerOn_flavor[j]->Sumw2();
    h_mupt_inclRecoMuonTag_triggerOn_flavor[j]->Sumw2();
    h_mueta_inclRecoMuonTag_triggerOn_flavor[j]->Sumw2();
    h_muphi_inclRecoMuonTag_triggerOn_flavor[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[j]->Sumw2();

    if(j==0){
      h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[j] = new TH2D(Form("h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor_J%i",j),Form("JetFlavorID vs. p_{T}^{rel} (w.r.t. genJet), p_{T}^{jet} %3.0f - %3.0f", jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
    }
    else{
      h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[j] = new TH2D(Form("h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor_J%i",j),Form("JetFlavorID vs. p_{T}^{rel} (w.r.t. genJet), p_{T}^{jet} %3.0f - %3.0f", jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
    }

    h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[j]->Sumw2();

  }



  TFile *f = TFile::Open(input);
  cout << "File opened!" << endl;
  auto em = new eventMap(f);
  em->isMC = 1;
  em->AASetup = 0;
  cout << "Initializing variables ... " << endl;
  em->init();
  cout << "Loading jet..." << endl;
  em->loadJet(jetTreeString);
  cout << "Loading muon..." << endl;
  em->loadMuon(muonTreeString);
  cout << "Loading muon triggers..." << endl;
  em->loadMuonTrigger(hltString);
  cout << "Loading tracks..." << endl;
  em->loadTrack();
  cout << "Loading gen particles..." << endl;
  em->loadGenParticle();
  cout << "Variables initilized!" << endl << endl ;

  int NEvents = em->evtTree->GetEntries();
  cout << "Number of events = " << NEvents << endl;


  // define event filters
  em->regEventFilter(NeventFilters, eventFilters);

  TRandom *randomGenerator = new TRandom2();

  // jet-energy resolution fit function
  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,300);
  JER_fxn->SetParameter(0,1.26585e-01);
  JER_fxn->SetParameter(1,-9.72986e-01);
  JER_fxn->SetParameter(2,3.67352e-04);

  loadFitFxn_vz();

  // event loop
  int evi_frac = 0;
  for(int evi = 0; evi < NEvents ; evi++){
    
    if(evi==0) cout << "Processing events..." << endl;
    
    em->getEvent(evi);

    if((100*evi / NEvents) % 5 == 0 && 100*evi / NEvents > evi_frac) cout << "evt frac: " << evi_frac << "%" << endl;
    evi_frac = 100 * evi/NEvents;

    // global event cuts
    //cout << "Applying global event cuts..." << endl;
    if(em->pthat <= pthatcut) continue;
    if(fabs(em->vz) > 15.0) continue;
    if(em->checkEventFilter()) continue;
    //cout << "Event #" << evi << " passed the global cuts!" << endl;
	
    double w_reweight_vz = fitFxn_vz->Eval(em->vz);
    //double w_reweight_vz = 1.0;

    double w_pthat = em->weight;

    double w = w_pthat * w_reweight_vz;

	
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};

    int matchFlagR[10] = {0,0,0,0,0,0,0,0,0,0};

    bool evtTriggerDecision = false;
    bool evtHasGoodJet = false;
    bool evtHasGoodMuonTaggedJet = false;
    bool evtHasGoodMuonTaggedJetTriggerOn = false;
    
    int triggerDecision = em->HLT_HIL3Mu5_NHitQ10_v1; 
    int triggerDecision_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl; 
    
    if(triggerIsOn(triggerDecision,triggerDecision_Prescl)){
      evtTriggerDecision = true;
      w = w / (triggerDecision_Prescl * 1.0) ; // set weight to 1/prescl for triggered events 
    }
    double leadingRecoJetPt = -1.0;
    double leadingGenJetPt = -1.0;

    // RECO JET LOOP
    for(int i = 0; i < em->njet ; i++){

      // JET VARIABLES
		
		
      JEC.SetJetPT(em->rawpt[i]);
      JEC.SetJetEta(em->jeteta[i]);
      JEC.SetJetPhi(em->jetphi[i]);

      double x = JEC.GetCorrectedPT();  // apply manual JEC
      //double x = em->jetpt[i];  // use built-in JEC
      double y = em->jeteta[i]; // recoJetEta
      double z = em->jetphi[i]; // recoJetPhi
      double jetTrkMax_i = em->jetTrkMax[i];

      
      JEU.SetJetPT(x);
      JEU.SetJetEta(y);
      JEU.SetJetPhi(z);

      // initialize 
      double correctedPt_down = 1.0;
      double correctedPt_up = 1.0;

      if(apply_JEU_shift_up){
	correctedPt_up = x * (1 + JEU.GetUncertainty().second);
	x = correctedPt_up;
      }
      else if(apply_JEU_shift_down){
	correctedPt_down = x * (1 - JEU.GetUncertainty().first);
	x = correctedPt_down;
      }

      double mu = 1.0;
      double sigma = 0.2;
      double smear = 0.0;

      if(apply_JER_smear){
	sigma = 0.663*JER_fxn->Eval(x); // apply a 20% smear
	smear = randomGenerator->Gaus(mu,sigma);
	x = x * smear;
      }

      if(!passesJetTrkMaxFilter(jetTrkMax_i,x)) continue;
      
      if(etaPhiMask(y,z)) continue;

      double muPtRel = -1.0;
      double muPt = -1.0;
      double muEta = -1.0;
      double muPhi = -1.0;
		
      if(TMath::Abs(y) > etaMax || x < jetPtCut) continue;
		
      int jetPtIndex = getJetPtBin(x);

      //cout << "jetPt = " << x << " | index = " << jetPtIndex << endl;

      if(x > leadingRecoJetPt) leadingRecoJetPt = x;



      int jetFlavorInt = em->partonFlavor[i];
      int hadronFlavorInt = em->hadronFlavor[i];

      if(jetFlavorInt == 0) {
	//	cout << "partonFlavor = " << jetFlavorInt << " | hadronFlavor = " << hadronFlavorInt << endl;
	//cout << "	recoPt = " << x << " | refPt =  " << em->ref_jetpt[i] << endl;
      }


			

      int genMuIndex = -1;
      bool hasInclGenMuonTag = false;
      bool hasMatchedGenMuonTag = false;

      bool hasInclRecoMuonTag = false;
      bool hasMatchedRecoMuonTag = false;


      if(!skipGenParticles){
	// look for a genMuon match
	for(int j = 0; j < em->gppdgIDp->size(); j++){

                        
	  bool isMatchedGenMuon = false;

	  if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

	  genMuIndex++;

	  if(matchFlag[genMuIndex] == 1) continue; // skip if muon has been matched to a jet already

	  if(isWDecayMuon(em->gpptp->at(j),x)) continue; // skip if "WDecay" muon (has majority of jet pt)
		
	  double a = em->gpptp->at(j);
	  double am = -1.0;
	  double b = em->gpetap->at(j);
	  double bm = -1.0;
	  double c = em->gpphip->at(j);
	  double cm = -1.0;


	  if(a < muPtCut || fabs(b) > trkEtaMax) continue;                        

	  for(int l = 0; l < em->nMu; l++){

	    if(em->muPt->at(l) < muPtCut || fabs(em->muEta->at(l)) > trkEtaMax) continue;
	 
	    if(!isQualityMuon_tight(em->muChi2NDF->at(l),
				    em->muInnerD0->at(l),
				    em->muInnerDz->at(l),
				    em->muMuonHits->at(l),
				    em->muPixelHits->at(l),
				    em->muIsGlobal->at(l),
				    em->muIsPF->at(l),
				    em->muStations->at(l),
				    em->muTrkLayers->at(l))) continue; // skip if muon doesnt pass quality cuts	


	    if(isWDecayMuon(em->muPt->at(l),x)) continue; // skip if "WDecay" muon (has majority of jet pt)	
			
	    double aR = em->muPt->at(l);
	    double bR = em->muEta->at(l);
	    double cR = em->muPhi->at(l);

	    if(getDr(b,c,bR,cR) < epsilon){
				
	      isMatchedGenMuon = true;
	      am = aR;
	      bm = bR;
	      cm = cR;
			
	    }

	  }

	  if(getDr(b,c,y,z) < deltaRCut){
				
	    matchFlag[genMuIndex] = 1;
	    hasInclGenMuonTag = true;
	    if(isMatchedGenMuon) hasMatchedGenMuonTag = true;

	  } 

	} // end genMuon loop
      }

	

      // look for recoMuon match		
		
      for(int m = 0; m < em->nMu; m++){

	if(matchFlagR[m] == 1) continue;

	if(em->muPt->at(m) < muPtCut || fabs(em->muEta->at(m)) > trkEtaMax) continue;
			 
	if(!isQualityMuon_tight(em->muChi2NDF->at(m),
				em->muInnerD0->at(m),
				em->muInnerDz->at(m),
				em->muMuonHits->at(m),
				em->muPixelHits->at(m),
				em->muIsGlobal->at(m),
				em->muIsPF->at(m),
				em->muStations->at(m),
				em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     


	if(isWDecayMuon(em->muPt->at(m),x)) continue; // skip if "WDecay" muon (has majority of jet pt) 
			
	// match to genMuon
	bool isMatchedRecoMuon = false;

	if(!skipGenParticles){
	  for(int j = 0; j < em->gppdgIDp->size(); j++){


	    //cout << "genID = " << em->gppdgIDp->at(j) << endl;
			
	    if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

	    if(em->gpptp->at(j) < muPtCut || fabs(em->gpetap->at(j)) > trkEtaMax) continue;                        
		
	    if(getDr(em->muEta->at(m),em->muPhi->at(m),em->gpetap->at(j),em->gpphip->at(j)) < epsilon){

	      isMatchedRecoMuon = true;
			
	    }

	  }
	}
	// match to recoJets
	if(getDr(em->muEta->at(m),em->muPhi->at(m),y,z) < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel = getPtRel(em->muPt->at(m),em->muEta->at(m),em->muPhi->at(m),x,y,z);
	  muPt = em->muPt->at(m);
	  muEta = em->muEta->at(m);
	  muPhi = em->muPhi->at(m);
	  
	  if(isMatchedRecoMuon) hasMatchedRecoMuonTag = true;

	}
						


      }

      // Fill the jet histograms
      evtHasGoodJet = true;
      h_inclRecoJetPt_flavor->Fill(x,jetFlavorInt,w);
      h_inclRecoJetEta_flavor->Fill(y,jetFlavorInt,w);
      h_inclRecoJetPhi_flavor->Fill(z,jetFlavorInt,w);
      h_inclRecoJetPt_inclRecoJetEta->Fill(x,y,w);
      h_inclRecoJetPt_inclRecoJetPhi->Fill(x,z,w);
      h_inclRecoJetEta_inclRecoJetPhi[0]->Fill(y,z,w);
      if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi[jetPtIndex]->Fill(y,z,w);
		
      // FACTORIZATION CONFIG #1

      if(hasInclGenMuonTag){
		
	h_inclRecoJetPt_inclGenMuonTag_flavor->Fill(x,jetFlavorInt,w);
	h_inclRecoJetEta_inclGenMuonTag_flavor->Fill(y,jetFlavorInt,w);
	h_inclRecoJetPhi_inclGenMuonTag_flavor->Fill(z,jetFlavorInt,w);
	h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag->Fill(x,y,w);
	h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag->Fill(x,z,w);
	h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[0]->Fill(y,z,w);
	if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[jetPtIndex]->Fill(y,z,w);

      } 

      if(hasInclRecoMuonTag){

	evtHasGoodMuonTaggedJet = true;

	h_inclRecoJetPt_inclRecoMuonTag_flavor->Fill(x,jetFlavorInt,w);
	h_inclRecoJetEta_inclRecoMuonTag_flavor->Fill(y,jetFlavorInt,w);
	h_inclRecoJetPhi_inclRecoMuonTag_flavor->Fill(z,jetFlavorInt,w);
	h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag->Fill(x,y,w);
	h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag->Fill(x,z,w);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0]->Fill(y,z,w);
	if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[jetPtIndex]->Fill(y,z,w);
			
	if(evtTriggerDecision){

	  evtHasGoodMuonTaggedJetTriggerOn = true;
	  
	  h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor->Fill(x,jetFlavorInt,w);
	  h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor->Fill(y,jetFlavorInt,w);
	  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor->Fill(z,jetFlavorInt,w);
	  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn->Fill(x,y,w);
	  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Fill(x,z,w);

	  h_muptrel_inclRecoMuonTag_triggerOn_flavor[0]->Fill(muPtRel,jetFlavorInt,w);
	  h_mupt_inclRecoMuonTag_triggerOn_flavor[0]->Fill(muPt,jetFlavorInt,w);
	  h_mueta_inclRecoMuonTag_triggerOn_flavor[0]->Fill(muEta,jetFlavorInt,w);
	  h_muphi_inclRecoMuonTag_triggerOn_flavor[0]->Fill(muPhi,jetFlavorInt,w);

	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0]->Fill(y,z,w);
	 

	  if(jetPtIndex > 0) {

	    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[jetPtIndex]->Fill(y,z,w);

	    h_muptrel_inclRecoMuonTag_triggerOn_flavor[jetPtIndex]->Fill(muPtRel,jetFlavorInt,w);
	    h_mupt_inclRecoMuonTag_triggerOn_flavor[jetPtIndex]->Fill(muPt,jetFlavorInt,w);
	    h_mueta_inclRecoMuonTag_triggerOn_flavor[jetPtIndex]->Fill(muEta,jetFlavorInt,w);
	    h_muphi_inclRecoMuonTag_triggerOn_flavor[jetPtIndex]->Fill(muPhi,jetFlavorInt,w);
	    
	  }
	    
	} 

	if(hasMatchedRecoMuonTag){

	  h_inclRecoJetPt_matchedRecoMuonTag_flavor->Fill(x,jetFlavorInt,w);
	  h_inclRecoJetEta_matchedRecoMuonTag_flavor->Fill(y,jetFlavorInt,w);
	  h_inclRecoJetPhi_matchedRecoMuonTag_flavor->Fill(z,jetFlavorInt,w);
	  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag->Fill(x,y,w);
	  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag->Fill(x,z,w);

	  h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[0]->Fill(y,z,w);
	  if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[jetPtIndex]->Fill(y,z,w);

	  if(evtTriggerDecision) {

	    h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor->Fill(x,jetFlavorInt,w);
	    h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor->Fill(y,jetFlavorInt,w);
	    h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor->Fill(z,jetFlavorInt,w);
	    h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn->Fill(x,y,w);
	    h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn->Fill(x,z,w);
	    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[0]->Fill(y,z,w);
	    if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[jetPtIndex]->Fill(y,z,w);

	  }

	}

      }
	
      //}



      //}

    }
    // END recoJet LOOP

    // fill reco-based event histograms
    if(evtHasGoodJet){

      h_vz->Fill(em->vz,w);

      if(evtHasGoodMuonTaggedJet){

	h_vz_inclRecoMuonTag->Fill(em->vz,w);

	if(evtHasGoodMuonTaggedJetTriggerOn){

	  h_vz_inclRecoMuonTag_triggerOn->Fill(em->vz,w);

	}

      }

    }
	
    if(leadingRecoJetPt > 0) h_recoJetPt_pthat->Fill(leadingRecoJetPt,em->pthat,w);

    // GEN JET LOOP
    for(int i = 0; i < em->ngj ; i++){

      // JET VARIABLES
		
		


      double x = em->genjetpt[i];  // recoJetPt
      double y = em->genjeteta[i]; // recoJetEta
      double z = em->genjetphi[i]; // recoJetPhi

      double muPtRel = -1.0;
		
      if(TMath::Abs(y) > etaMax || x < jetPtCut) continue;

      if(x > leadingGenJetPt) leadingGenJetPt = x;

      ////// get flavor from reco match
      bool hasRecoJetMatch = false;
      int recoJetFlavorFlag = 0;
      double minDr = 100.0;
      int jetFlavorInt = 19;
	

		

      for(int k = 0; k < em->njet; k++){
		
	double dr = getDr(em->jeteta[k],em->jetphi[k],y,z);

	if(dr < minDr){ 

	  minDr = dr;

	  if(minDr < epsilon_mm){

	    recoJetFlavorFlag = k;
	    hasRecoJetMatch = true;
			
	  }	
	}

      }

     
      if(hasRecoJetMatch) jetFlavorInt = em->partonFlavor[recoJetFlavorFlag];

		        
      int jetPtIndex = getJetPtBin(x);

      //cout << "jetPt = " << x << " | index = " << jetPtIndex << endl;




      if(jetFlavorInt == 0) {
	//	cout << "partonFlavor = " << jetFlavorInt << " | hadronFlavor = " << hadronFlavorInt << endl;
	//cout << "	recoPt = " << x << " | refPt =  " << em->ref_jetpt[i] << endl;
      }


			

      int genMuIndex = -1;
      bool hasInclGenMuonTag = false;
      bool hasMatchedGenMuonTag = false;

      bool hasInclRecoMuonTag = false;
      bool hasMatchedRecoMuonTag = false;


      if(!skipGenParticles){
	// look for a genMuon match
	for(int j = 0; j < em->gppdgIDp->size(); j++){

                        
	  bool isMatchedGenMuon = false;

	  if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

	  genMuIndex++;

	  if(matchFlag[genMuIndex] == 1) continue; // skip if muon has been matched to a jet already

	  if(isWDecayMuon(em->gpptp->at(j),x)) continue; // skip if "WDecay" muon (has majority of jet pt)
		
	  double a = em->gpptp->at(j);
	  double am = -1.0;
	  double b = em->gpetap->at(j);
	  double bm = -1.0;
	  double c = em->gpphip->at(j);
	  double cm = -1.0;

	  if(a < muPtCut || fabs(b) > trkEtaMax) continue;                        

	  for(int l = 0; l < em->nMu; l++){

	    if(em->muPt->at(l) < muPtCut || fabs(em->muEta->at(l)) > trkEtaMax) continue;
	  
	    if(!isQualityMuon_tight(em->muChi2NDF->at(l),
				    em->muInnerD0->at(l),
				    em->muInnerDz->at(l),
				    em->muMuonHits->at(l),
				    em->muPixelHits->at(l),
				    em->muIsGlobal->at(l),
				    em->muIsPF->at(l),
				    em->muStations->at(l),
				    em->muTrkLayers->at(l))) continue; // skip if muon doesnt pass quality cuts	


	    //if(isWDecayMuon(em->muPt->at(l),x)) continue; // skip if "WDecay" muon (has majority of jet pt)	
			

			
	    double aR = em->muPt->at(l);
	    double bR = em->muEta->at(l);
	    double cR = em->muPhi->at(l);

			

	    if(getDr(b,c,bR,cR) < epsilon){
				
	      isMatchedGenMuon = true;
	      am = aR;
	      bm = bR;
	      cm = cR;
			
	    }

			

	  }

	  if(getDr(b,c,y,z) < deltaRCut){
				
	    matchFlag[genMuIndex] = 1;
	    hasInclGenMuonTag = true;
	    if(isMatchedGenMuon) hasMatchedGenMuonTag = true;
	
	  } 

	} // end genMuon loop
      }
	

      // look for recoMuon match		
		
      for(int m = 0; m < em->nMu; m++){

	if(matchFlagR[m] == 1) continue;

	if(em->muPt->at(m) < muPtCut || fabs(em->muEta->at(m)) > trkEtaMax) continue;

	if(!isQualityMuon_tight(em->muChi2NDF->at(m),
				em->muInnerD0->at(m),
				em->muInnerDz->at(m),
				em->muMuonHits->at(m),
				em->muPixelHits->at(m),
				em->muIsGlobal->at(m),
				em->muIsPF->at(m),
				em->muStations->at(m),
				em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     


	if(isWDecayMuon(em->muPt->at(m),x)) continue; // skip if "WDecay" muon (has majority of jet pt) 
			
			
	// match to genMuon
			

	bool isMatchedRecoMuon = false;

	for(int j = 0; j < em->gppdgIDp->size(); j++){


	  //cout << "genID = " << em->gppdgIDp->at(j) << endl;
			
	  if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

	  if(em->gpptp->at(j) < muPtCut || fabs(em->gpetap->at(j)) > trkEtaMax) continue;                        
		
	  if(getDr(em->muEta->at(m),em->muPhi->at(m),em->gpetap->at(j),em->gpphip->at(j)) < epsilon){

	    isMatchedRecoMuon = true;
			
	  }

	}

	// match to recoJets
	if(getDr(em->muEta->at(m),em->muPhi->at(m),y,z) < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel = getPtRel(em->muPt->at(m),em->muEta->at(m),em->muPhi->at(m),x,y,z);
				
	  if(isMatchedRecoMuon) hasMatchedRecoMuonTag = true;

	}
						


      }

      // Fill the jet histograms

      h_inclGenJetPt_flavor->Fill(x,jetFlavorInt,w);



      // FACTORIZATION CONFIG #1

      if(hasInclGenMuonTag){
		
	h_inclGenJetPt_inclGenMuonTag_flavor->Fill(x,jetFlavorInt,w);

      } 

      if(hasInclRecoMuonTag){

	h_inclGenJetPt_inclRecoMuonTag_flavor->Fill(x,jetFlavorInt,w);
			
	if(evtTriggerDecision){
	  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor->Fill(x,jetFlavorInt,w);
	  h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[0]->Fill(muPtRel,jetFlavorInt,w);
	  if(jetPtIndex > 0) h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[jetPtIndex]->Fill(muPtRel,jetFlavorInt,w);
	} 

	if(hasMatchedRecoMuonTag){

	  h_inclGenJetPt_matchedRecoMuonTag_flavor->Fill(x,jetFlavorInt,w);

	  if(evtTriggerDecision) 	h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor->Fill(x,jetFlavorInt,w);


	}

      }
	
      //}



      //}

    }
    // END genJet LOOP
	
    if(leadingGenJetPt > 0) h_genJetPt_pthat->Fill(leadingGenJetPt,em->pthat,w);


	

  } // END EVENT LOOP
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  h_vz->Write();
  h_vz_inclRecoMuonTag->Write();
  h_vz_inclRecoMuonTag_triggerOn->Write();
  
  h_inclRecoJetPt_flavor->Write();
  h_inclRecoJetEta_flavor->Write();
  h_inclRecoJetPhi_flavor->Write();
  h_inclRecoJetPt_inclRecoJetEta->Write();
  h_inclRecoJetPt_inclRecoJetPhi->Write();

  h_inclRecoJetPt_inclGenMuonTag_flavor->Write();
  h_inclRecoJetEta_inclGenMuonTag_flavor->Write();
  h_inclRecoJetPhi_inclGenMuonTag_flavor->Write();
  h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag->Write();
  h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag->Write();

  h_inclRecoJetPt_inclRecoMuonTag_flavor->Write();
  h_inclRecoJetEta_inclRecoMuonTag_flavor->Write();
  h_inclRecoJetPhi_inclRecoMuonTag_flavor->Write();
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag->Write();
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag->Write();

  h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor->Write();
  h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor->Write();
  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor->Write();
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn->Write();
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Write();
  
  h_inclRecoJetPt_matchedRecoMuonTag_flavor->Write();
  h_inclRecoJetEta_matchedRecoMuonTag_flavor->Write();
  h_inclRecoJetPhi_matchedRecoMuonTag_flavor->Write();
  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag->Write();
  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag->Write();

  h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor->Write();
  h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor->Write();
  h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor->Write();
  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn->Write();
  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn->Write();

  h_inclGenJetPt_flavor->Write();
  h_inclGenJetPt_inclGenMuonTag_flavor->Write();
  h_inclGenJetPt_inclRecoMuonTag_flavor->Write();
  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor->Write();
  h_inclGenJetPt_matchedRecoMuonTag_flavor->Write();
  h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor->Write();


  for(int j = 0; j < NJetPtIndices; j++){

    h_inclRecoJetEta_inclRecoJetPhi[j]->Write();
    h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[j]->Write();
    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j]->Write();
    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j]->Write();
    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[j]->Write();
    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[j]->Write();

    h_muptrel_inclRecoMuonTag_triggerOn_flavor[j]->Write();
    h_mupt_inclRecoMuonTag_triggerOn_flavor[j]->Write();
    h_mueta_inclRecoMuonTag_triggerOn_flavor[j]->Write();
    h_muphi_inclRecoMuonTag_triggerOn_flavor[j]->Write();
    
    h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[j]->Write();

  }


  h_recoJetPt_pthat->Write();	
  h_genJetPt_pthat->Write();	


  wf->Close();
  return;
  // END WRITE



}







