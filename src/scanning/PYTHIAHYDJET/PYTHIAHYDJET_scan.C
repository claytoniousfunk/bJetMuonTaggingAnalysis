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
#include "../../../../eventMap/eventMap.h"
// jet corrector
#include "../../../../JetEnergyCorrections/JetCorrector.h"
// jet uncertainty
#include "../../../../JetEnergyCorrections/JetUncertainty.h"
// general analysis variables
#include "../../../../headers/AnalysisSetupV2p1.h"
// vz-fit parameters
#include "../../../../headers/fitParameters/vzFitParams_PH.h"
// hiBin-fit parameters
#include "../../../../headers/fitParameters/hiBinFitParams.h"

TF1 *fitFxn_hiBin, *fitFxn_vz;
// vz-fit function
#include "../../../../headers/fitFunctions/fitFxn_vz_PH.h"
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
#include "../../../../headers/introductions/printIntroduction_PYTHIAHYDJET_scan_V3p7.h"
// analysis config
#include "../../../../headers/config/config_PYTHIAHYDJET.h"
// read config
#include "../../../../headers/config/readConfig.h"


//~~~~~~~~~~~  initialize histograms ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// >>>>>>>>>> Reco jets
// ----------------------------------------- event histograms -----------------
// >> NEvents
TH1D *h_NEvents;
// >> vz
TH1D *h_vz[NCentralityIndices];
TH1D *h_vz_inclGenMuonTag[NCentralityIndices];
TH1D *h_vz_inclRecoMuonTag[NCentralityIndices];
TH1D *h_vz_matchedRecoMuonTag[NCentralityIndices];
TH1D *h_vz_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH1D *h_vz_matchedRecoMuonTag_triggerOn[NCentralityIndices];
// >> hiBin
TH1D *h_hiBin;
TH1D *h_hiBin_inclGenMuonTag;
TH1D *h_hiBin_inclRecoMuonTag;
TH1D *h_hiBin_matchedRecoMuonTag;
TH1D *h_hiBin_inclRecoMuonTag_triggerOn;
TH1D *h_hiBin_matchedRecoMuonTag_triggerOn;
// ------------------------------- incl. reco jets per flavor -----------------
TH2D *h_inclRecoJetPt_flavor[NCentralityIndices];
TH2D *h_inclRecoJetEta_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPhi_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetEta[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetPhi[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoJetPhi[NCentralityIndices][NJetPtIndices];
// ------------------- incl. reco jets tagged to gen muon by flavor -----------
TH2D *h_inclRecoJetPt_inclGenMuonTag_flavor[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclGenMuonTag_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPhi_inclGenMuonTag_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[NCentralityIndices][NJetPtIndices];
// ------------------- incl. reco jets tagged to incl. reco muon by flavor ----
TH2D *h_inclRecoJetPt_inclRecoMuonTag_flavor[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoMuonTag_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPhi_inclRecoMuonTag_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[NCentralityIndices][NJetPtIndices];
// ------- incl. reco jets tagged to incl. reco muon by flavor, trigger on ----
TH2D *h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[NCentralityIndices][NJetPtIndices];
// ----------------- incl. reco jets tagged to matched reco muon by flavor ----
TH2D *h_inclRecoJetPt_matchedRecoMuonTag_flavor[NCentralityIndices];
TH2D *h_inclRecoJetEta_matchedRecoMuonTag_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPhi_matchedRecoMuonTag_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[NCentralityIndices][NJetPtIndices];
// ----- incl. reco jets tagged to matched reco muon by flavor, trigger on ----
TH2D *h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor[NCentralityIndices];
TH2D *h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[NCentralityIndices][NJetPtIndices];
// ------------------------------- in-jet reco muons by flavor, trigger on ----
TH2D *h_muptrel_inclRecoMuonTag_triggerOn_flavor[NCentralityIndices][NJetPtIndices];
TH2D *h_mupt_inclRecoMuonTag_triggerOn_flavor[NCentralityIndices][NJetPtIndices];
TH2D *h_mueta_inclRecoMuonTag_triggerOn_flavor[NCentralityIndices][NJetPtIndices];
TH2D *h_muphi_inclRecoMuonTag_triggerOn_flavor[NCentralityIndices][NJetPtIndices];

// >>>>>>>>>> Gen jets
// ------------------------------- incl. gen jets per flavor ------------------
TH2D *h_inclGenJetPt_flavor[NCentralityIndices];
// ------------------- incl. gen jets tagged to incl. gen muon by flavor ------
TH2D *h_inclGenJetPt_inclGenMuonTag_flavor[NCentralityIndices];
// ------------------- incl. gen jets tagged to incl. reco muon by flavor -----
TH2D *h_inclGenJetPt_inclRecoMuonTag_flavor[NCentralityIndices];
// ------- incl. gen jets tagged to incl. reco muon by flavor, trigger on -----
TH2D *h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor[NCentralityIndices];
// ----------------- incl. gen jets tagged to matched reco muon by flavor -----
TH2D *h_inclGenJetPt_matchedRecoMuonTag_flavor[NCentralityIndices];
// ----- incl. gen jets tagged to matched reco muon by flavor, trigger on -----
TH2D *h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor[NCentralityIndices];
// ------------------------------- in-jet reco muons by flavor, trigger on ----
TH2D *h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[NCentralityIndices][NJetPtIndices];
// ------------------------------------- analysis histograms ------------------
TH2D *h_recoGenDr_flavor[NCentralityIndices][NJetPtIndices];
TH2D *h_recoGenDpt_flavor[NCentralityIndices][NJetPtIndices];
TH2D *h_recoJetPt_pthat[NCentralityIndices];
TH2D *h_genJetPt_pthat[NCentralityIndices];
TH2D *h_refPartonFlavorForB_matchedPartonFlavor[NCentralityIndices];
TH2D *h_matchedRecoJetPt_genJetPt[NCentralityIndices];
TH2D *h_mupt_muptrel[NCentralityIndices][NJetPtIndices];
TH2D *h_mupt_jetpt[NCentralityIndices];
TH2D *h_muptrel_jetpt[NCentralityIndices];
TH2D *h_weight_pthat_xJets_C1J3;
TH2D *h_weight_pthat_bJets_C1J3;




void PYTHIAHYDJET_scan(TString input = "/eos/user/c/cbennett/forests/PYTHIAHYDJET_DiJet_5July22/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/crab_PYTHIAHYDJET_DiJet_5July22/220705_212159/0000/HiForestAOD_104.root", TString output = "out.root"){




  
  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../../JetEnergyCorrections/Autumn18_HI_V8_MC_L2Relative_AK4PF.txt"); // LXPLUS

  JetCorrector JEC(Files);

  JetUncertainty JEU("../../../../JetEnergyCorrections/Autumn18_HI_V8_MC_Uncertainty_AK4PF.txt");

  
  printIntroduction_PYTHIAHYDJET_scan_V3p7();
  readConfig();
  
  // define histograms
  // >> NEvents
  h_NEvents = new TH1D("h_NEvents","Number of events",1000,0,1000);
  // >> hiBin
  h_hiBin = new TH1D("h_hiBin","hiBin, events with inclRecoJet",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_inclGenMuonTag = new TH1D("h_hiBin_inclGenMuonTag","hiBin, events with inclRecoJet-inclGenMuonTag",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_inclRecoMuonTag = new TH1D("h_hiBin_inclRecoMuonTag","hiBin, events with inclRecoJet-inclRecoMuonTag",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_inclRecoMuonTag_triggerOn = new TH1D("h_hiBin_inclRecoMuonTag_triggerOn","hiBin, events with inclRecoJet-inclRecoMuonTag-triggerOn",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_matchedRecoMuonTag = new TH1D("h_hiBin_matchedRecoMuonTag","hiBin, events with inclRecoJet-matchedRecoMuonTag",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_matchedRecoMuonTag_triggerOn = new TH1D("h_hiBin_matchedRecoMuonTag_triggerOn","hiBin, events with inclRecoJet-matchedRecoMuonTag-triggerOn",NhiBinBins,hiBinMin,hiBinMax);
  h_weight_pthat_xJets_C1J3 = new TH2D("h_weight_pthat_xJets_C1J3","pthat vs w_{pthat}, xJets, 80 < p_{T} < 120 GeV, cent. 0-30%",2000,0,0.02,500,0,500);
  h_weight_pthat_bJets_C1J3 = new TH2D("h_weight_pthat_bJets_C1J3","pthat vs w_{pthat}, bJets, 80 < p_{T} < 120 GeV, cent. 0-30%",2000,0,0.02,500,0,500);

  h_hiBin->Sumw2();
  h_hiBin_inclGenMuonTag->Sumw2();
  h_hiBin_inclRecoMuonTag->Sumw2();
  h_hiBin_inclRecoMuonTag_triggerOn->Sumw2();
  h_hiBin_matchedRecoMuonTag->Sumw2();
  h_hiBin_matchedRecoMuonTag_triggerOn->Sumw2();
  h_weight_pthat_xJets_C1J3->Sumw2();
  h_weight_pthat_bJets_C1J3->Sumw2();

  
  for(int i = 0; i < NCentralityIndices; i++){
	
	
    if(i==0){
      // ----------------------------------------- event histograms -----------------
      // >> vz
      h_vz[i] = new TH1D(Form("h_vz_C%i",i),Form("vz, events with inclRecoJet, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      h_vz_inclGenMuonTag[i] = new TH1D(Form("h_vz_inclGenMuonTag_C%i",i),Form("vz, events with inclRecoJet-inclGenMuonTag, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag[i] = new TH1D(Form("h_vz_inclRecoMuonTag_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      h_vz_matchedRecoMuonTag[i] = new TH1D(Form("h_vz_matchedRecoMuonTag_C%i",i),Form("vz, events with inclRecoJet-matchedRecoMuonTag, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_vz_inclRecoMuonTag_triggerOn_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag-triggerOn, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      h_vz_matchedRecoMuonTag_triggerOn[i] = new TH1D(Form("h_vz_matchedRecoMuonTag_triggerOn_C%i",i),Form("vz, events with inclRecoJet-matchedRecoMuonTag-triggerOn, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      // ------------------------------- incl. reco jets per flavor -----------------
      h_inclRecoJetPt_flavor[i] = new TH2D(Form("h_inclRecoJetPt_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_flavor[i] = new TH2D(Form("h_inclRecoJetEta_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ------------------- incl. reco jets tagged to gen muon by flavor -----------
      h_inclRecoJetPt_inclGenMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPt_inclGenMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_inclGenMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetEta_inclGenMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_inclGenMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_inclGenMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ------------------- incl. reco jets tagged to incl. reco muon by flavor ----
      h_inclRecoJetPt_inclRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_inclRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetEta_inclRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_inclRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_inclRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ------- incl. reco jets tagged to incl. reco muon by flavor, trigger on ----
      h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ----------------- incl. reco jets tagged to matched reco muon by flavor ----
      h_inclRecoJetPt_matchedRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPt_matchedRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_matchedRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetEta_matchedRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_matchedRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_matchedRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ----- incl. reco jets tagged to matched reco muon by flavor, trigger on ----
      h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ------------------------------------- analysis histograms ------------------
      h_recoJetPt_pthat[i] = new TH2D(Form("h_recoJetPt_pthat_C%i",i),Form("reco p_{T}^{jet} vs. #hat{p}_{T}, hiBin %i - hiBin %i; reco p_{T}^{jet} [GeV]; #hat{p}_{T} [GeV]",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_genJetPt_pthat[i] = new TH2D(Form("h_genJetPt_pthat_C%i",i),Form("gen p_{T}^{jet} vs. #hat{p}_{T}, hiBin %i - hiBin %i; gen p_{T}^{jet} [GeV]; #hat{p}_{T} [GeV]",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_refPartonFlavorForB_matchedPartonFlavor[i] = new TH2D(Form("h_refPartonFlavorForB_matchedPartonFlavor_C%i",i),Form("refPartonFlavorForB vs matchedPartonFlavor, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),27,-5,22,27,-5,22);
      h_matchedRecoJetPt_genJetPt[i] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_C%i",i),Form("matchedRecoJetPt vs genJetPt, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_mupt_jetpt[i] = new TH2D(Form("h_mupt_jetpt_C%i",i),Form("jetPt vs. muPt, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
      h_muptrel_jetpt[i] = new TH2D(Form("h_muptrel_jetpt_C%i",i),Form("jetPt vs. muRelPt, hiBin %i - %i", centEdges[0], centEdges[NCentralityIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
    }
    else{
      // ----------------------------------------- event histograms -----------------
      h_vz[i] = new TH1D(Form("h_vz_C%i",i),Form("vz, events with inclRecoJet, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      h_vz_inclGenMuonTag[i] = new TH1D(Form("h_vz_inclGenMuonTag_C%i",i),Form("vz, events with inclRecoJet-inclGenMuonTag, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag[i] = new TH1D(Form("h_vz_inclRecoMuonTag_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      h_vz_matchedRecoMuonTag[i] = new TH1D(Form("h_vz_matchedRecoMuonTag_C%i",i),Form("vz, events with inclRecoJet-matchedRecoMuonTag, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_vz_inclRecoMuonTag_triggerOn_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag-triggerOn, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      h_vz_matchedRecoMuonTag_triggerOn[i] = new TH1D(Form("h_vz_matchedRecoMuonTag_triggerOn_C%i",i),Form("vz, events with inclRecoJet-matchedRecoMuonTag-triggerOn, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      // ------------------------------- incl. reco jets per flavor -----------------
      h_inclRecoJetPt_flavor[i] = new TH2D(Form("h_inclRecoJetPt_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_flavor[i] = new TH2D(Form("h_inclRecoJetEta_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ------------------- incl. reco jets tagged to gen muon by flavor -----------
      h_inclRecoJetPt_inclGenMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPt_inclGenMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_inclGenMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetEta_inclGenMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_inclGenMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_inclGenMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ------------------- incl. reco jets tagged to incl. reco muon by flavor ----
      h_inclRecoJetPt_inclRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_inclRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetEta_inclRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_inclRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_inclRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ------- incl. reco jets tagged to incl. reco muon by flavor, trigger on ----
      h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ----------------- incl. reco jets tagged to matched reco muon by flavor ----
      h_inclRecoJetPt_matchedRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPt_matchedRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_matchedRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetEta_matchedRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_matchedRecoMuonTag_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_matchedRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ----- incl. reco jets tagged to matched reco muon by flavor, trigger on ----
      h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco p_{T}^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NEtaBins,etaMin,etaMax,27,-5,22);
      h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. reco #phi^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPhiBins,phiMin,phiMax,27,-5,22);
      h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ------------------------------------- analysis histograms ------------------
      h_recoJetPt_pthat[i] = new TH2D(Form("h_recoJetPt_pthat_C%i",i),Form("reco p_{T}^{jet} vs. #hat{p}_{T}, hiBin %i - hiBin %i; reco p_{T}^{jet} [GeV]; #hat{p}_{T} [GeV]",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_genJetPt_pthat[i] = new TH2D(Form("h_genJetPt_pthat_C%i",i),Form("gen p_{T}^{jet} vs. #hat{p}_{T}, hiBin %i - hiBin %i; gen p_{T}^{jet} [GeV]; #hat{p}_{T} [GeV]",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_refPartonFlavorForB_matchedPartonFlavor[i] = new TH2D(Form("h_refPartonFlavorForB_matchedPartonFlavor_C%i",i),Form("refPartonFlavorForB vs matchedPartonFlavor, hiBin %i - %i",centEdges[i-1],centEdges[i]),27,-5,22,27,-5,22);
      h_matchedRecoJetPt_genJetPt[i] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_C%i",i),Form("matchedRecoJetPt vs genJetPt, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_mupt_jetpt[i] = new TH2D(Form("h_mupt_jetpt_C%i",i),Form("jetPt vs. muPt, hiBin %i - %i",centEdges[i-1],centEdges[i]),NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
      h_muptrel_jetpt[i] = new TH2D(Form("h_muptrel_jetpt_C%i",i),Form("jetPt vs. muRelPt, hiBin %i - %i", centEdges[i-1], centEdges[i]),NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
    }
	

    h_vz[i]->Sumw2();
    h_vz_inclGenMuonTag[i]->Sumw2();
    h_vz_inclRecoMuonTag[i]->Sumw2();
    h_vz_matchedRecoMuonTag[i]->Sumw2();
    h_vz_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_vz_matchedRecoMuonTag_triggerOn[i]->Sumw2();
  
    h_inclRecoJetPt_flavor[i]->Sumw2();
    h_inclRecoJetEta_flavor[i]->Sumw2();
    h_inclRecoJetPhi_flavor[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetEta[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetPhi[i]->Sumw2();

    h_inclRecoJetPt_inclGenMuonTag_flavor[i]->Sumw2();
    h_inclRecoJetEta_inclGenMuonTag_flavor[i]->Sumw2();
    h_inclRecoJetPhi_inclGenMuonTag_flavor[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag[i]->Sumw2();

    h_inclRecoJetPt_inclRecoMuonTag_flavor[i]->Sumw2();
    h_inclRecoJetEta_inclRecoMuonTag_flavor[i]->Sumw2();
    h_inclRecoJetPhi_inclRecoMuonTag_flavor[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[i]->Sumw2();

    h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor[i]->Sumw2();
    h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor[i]->Sumw2();
    h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i]->Sumw2();

    h_inclRecoJetPt_matchedRecoMuonTag_flavor[i]->Sumw2();
    h_inclRecoJetEta_matchedRecoMuonTag_flavor[i]->Sumw2();
    h_inclRecoJetPhi_matchedRecoMuonTag_flavor[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag[i]->Sumw2();
    
    h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor[i]->Sumw2();
    h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor[i]->Sumw2();
    h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[i]->Sumw2();

    h_recoJetPt_pthat[i]->Sumw2();
    h_genJetPt_pthat[i]->Sumw2();
    h_refPartonFlavorForB_matchedPartonFlavor[i]->Sumw2();
    h_matchedRecoJetPt_genJetPt[i]->Sumw2();
    h_mupt_jetpt[i]->Sumw2();
    h_muptrel_jetpt[i]->Sumw2();

    if(i==0){
      // tagging factorization config #1
      h_inclGenJetPt_flavor[i] = new TH2D(Form("h_inclGenJetPt_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_inclGenMuonTag_flavor[i] = new TH2D(Form("h_inclGenJetPt_inclGenMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_inclRecoMuonTag_flavor[i] = new TH2D(Form("h_inclGenJetPt_inclRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_matchedRecoMuonTag_flavor[i] = new TH2D(Form("h_inclGenJetPt_matchedRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
    }
    else{
      // tagging factorization config #1
      h_inclGenJetPt_flavor[i] = new TH2D(Form("h_inclGenJetPt_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_inclGenMuonTag_flavor[i] = new TH2D(Form("h_inclGenJetPt_inclGenMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_inclRecoMuonTag_flavor[i] = new TH2D(Form("h_inclGenJetPt_inclRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_matchedRecoMuonTag_flavor[i] = new TH2D(Form("h_inclGenJetPt_matchedRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with matched reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor[i] = new TH2D(Form("h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
    }

  

    h_inclGenJetPt_flavor[i]->Sumw2();
    h_inclGenJetPt_inclGenMuonTag_flavor[i]->Sumw2();
    h_inclGenJetPt_inclRecoMuonTag_flavor[i]->Sumw2();
    h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor[i]->Sumw2();
    h_inclGenJetPt_matchedRecoMuonTag_flavor[i]->Sumw2();
    h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor[i]->Sumw2();
	
    for(int j = 0; j < NJetPtIndices; j++){
	
      //
      if(i==0 && j==0){
	h_muptrel_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{rel}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
	h_mupt_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_mupt_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax,27,-5,22);
	h_mueta_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_mueta_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. #eta^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax,27,-5,22);
	h_muphi_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muphi_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. #phi^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax,27,-5,22);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. gen muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_recoGenDr_flavor[i][j] = new TH2D(Form("h_recoGenDr_C%iJ%i",i,j),Form("JetFlavorID vs #Delta r(recoJet,genJet), hiBin %i - hiBin %i, p_{T}^{jet} %3.0f - %3.0f ",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1,27,-5,22); 
	h_recoGenDpt_flavor[i][j] = new TH2D(Form("h_recoGenDpt_C%iJ%i",i,j),Form("JetFlavorID vs #Delta p_{T}/p_{T}(recoJet,genJet), hiBin %i - hiBin %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,5,27,-5,22); 
      }
      else if(i==0){
	h_muptrel_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{rel}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
	h_mupt_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_mupt_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax,27,-5,22);
	h_mueta_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_mueta_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. #eta^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax,27,-5,22);
	h_muphi_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muphi_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. #phi^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax,27,-5,22);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. gen muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_recoGenDr_flavor[i][j] = new TH2D(Form("h_recoGenDr_C%iJ%i",i,j),Form("JetFlavorID vs #Delta r(recoJet,genJet), hiBin %i - hiBin %i, p_{T}^{jet} %3.0f - %3.0f ",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),100,0,1,27,-5,22); 
	h_recoGenDpt_flavor[i][j] = new TH2D(Form("h_recoGenDpt_C%iJ%i",i,j),Form("JetFlavorID vs #Delta p_{T}/p_{T}(recoJet,genJet), hiBin %i - hiBin %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),100,0,5,27,-5,22); 
      }
      else if(j==0){
	h_muptrel_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{rel}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
	h_mupt_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_mupt_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax,27,-5,22);
	h_mueta_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_mueta_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. #eta^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax,27,-5,22);
	h_muphi_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muphi_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. #phi^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax,27,-5,22);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. gen muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_recoGenDr_flavor[i][j] = new TH2D(Form("h_recoGenDr_C%iJ%i",i,j),Form("JetFlavorID vs #Delta r(recoJet,genJet), hiBin %i - hiBin %i, p_{T}^{jet} %3.0f - %3.0f ",centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1,27,-5,22); 
	h_recoGenDpt_flavor[i][j] = new TH2D(Form("h_recoGenDpt_C%iJ%i",i,j),Form("JetFlavorID vs #Delta p_{T}/p_{T}(recoJet,genJet), hiBin %i - hiBin %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,5,27,-5,22); 
      }
      else{
	h_muptrel_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{rel}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
	h_mupt_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_mupt_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax,27,-5,22);
	h_mueta_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_mueta_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. #eta^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax,27,-5,22);
	h_muphi_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muphi_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. #phi^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax,27,-5,22);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. gen muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_recoGenDr_flavor[i][j] = new TH2D(Form("h_recoGenDr_C%iJ%i",i,j),Form("JetFlavorID vs #Delta r(recoJet,genJet), hiBin %i - hiBin %i, p_{T}^{jet} %3.0f - %3.0f ",centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),100,0,1,27,-5,22); 
	h_recoGenDpt_flavor[i][j] = new TH2D(Form("h_recoGenDpt_C%iJ%i",i,j),Form("JetFlavorID vs #Delta p_{T}/p_{T}(recoJet,genJet), hiBin %i - hiBin %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),100,0,5,27,-5,22); 
      }

      h_muptrel_inclRecoMuonTag_triggerOn_flavor[i][j]->Sumw2();
      h_mupt_inclRecoMuonTag_triggerOn_flavor[i][j]->Sumw2();
      h_mueta_inclRecoMuonTag_triggerOn_flavor[i][j]->Sumw2();
      h_muphi_inclRecoMuonTag_triggerOn_flavor[i][j]->Sumw2();
      h_mupt_muptrel[i][j]->Sumw2();
      h_inclRecoJetEta_inclRecoJetPhi[i][j]->Sumw2();
      h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[i][j]->Sumw2();
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j]->Sumw2();
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j]->Sumw2();
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[i][j]->Sumw2();
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[i][j]->Sumw2();
      h_recoGenDr_flavor[i][j]->Sumw2();
      h_recoGenDpt_flavor[i][j]->Sumw2();
      
      if(i==0 && j==0){
	h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{rel} (w.r.t. genJet), hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
      }
      else if(i==0){
	h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{rel} (w.r.t. genJet), hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
      }
      else if(j==0){
	h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{rel} (w.r.t. genJet), hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
      }
      else{
	h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[i][j] = new TH2D(Form("h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor_C%iJ%i",i,j),Form("JetFlavorID vs. p_{T}^{rel} (w.r.t. genJet), hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,27,-5,22);
      }

      h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[i][j]->Sumw2();

    }

  }


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
  cout << "	Loading tracks..." << endl;
  em->loadTrack();
  cout << "	Loading gen particles..." << endl;
  em->loadGenParticle();
  cout << "	Variables initilized!" << endl << endl ;
  int NEvents = em->evtTree->GetEntries();
  cout << "	Number of events = " << NEvents << endl;


  // define event filters
  em->regEventFilter(NeventFilters, eventFilters);

  TRandom *randomGenerator = new TRandom2();

  // jet-energy resolution fit function
  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,300);
  JER_fxn->SetParameter(0,-1.91758e-05);
  JER_fxn->SetParameter(1,-1.79691e+00);
  JER_fxn->SetParameter(2,1.09880e+01);

  // define vz & hiBin reweighting functions
  loadFitFxn_vz();

  loadFitFxn_hiBin();
  
 
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
    if(em->pthat <= pthatcut) continue;
    if(fabs(em->vz) > 15.0) continue;
    if(em->checkEventFilter()) continue;

    // calculate event weight
    double w_reweight_hiBin = fitFxn_hiBin->Eval(em->hiBin-10);
    //double w_reweight_hiBin = 1.0;

    //double w_reweight_vz = fitFxn_vz->Eval(em->vz);
    double w_reweight_vz = 1.0;
   
    double w = em->weight * w_reweight_hiBin * w_reweight_vz;

    
    if(w <= 0.0) continue;
   
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};

    int matchFlagR[10] = {0,0,0,0,0,0,0,0,0,0};
	
    int CentralityIndex = getCentBin(em->hiBin-10);
    if(CentralityIndex < 0) continue;

    bool evtTriggerDecision = false;

    int triggerDecision = em->HLT_HIL3Mu5_NHitQ10_v1;
    int triggerDecision_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl;
    //int triggerDecision = em->HLT_HIL3Mu12_v1;
    //int triggerDecision_Prescl = em->HLT_HIL3Mu12_v1_Prescl;

    if(triggerIsOn(triggerDecision,triggerDecision_Prescl)) {
      evtTriggerDecision = true;
      eventCounter++;
      w = w / ( triggerDecision_Prescl * 1.0 ) ; // set weight as 1/prescl for triggered events
    }
   
   
    bool eventHasGoodJet = false;
    bool eventHasInclRecoMuonTag = false;
    bool eventHasInclRecoMuonTagPlusTrigger = false;
    bool eventHasMatchedRecoMuonTag = false;
    bool eventHasMatchedRecoMuonTagPlusTrigger = false;

    double leadingGenJetPt_i = 0.0;
    double leadingGenJetEta_i = 0.0;
    double leadingGenJetPhi_i = 0.0;

    // quick genJet loop to get leadingGenJetPt
    for(int j = 0; j < em->ngj ; j++){

	double genJetPt_j = em->genjetpt[j];  // genJetPt
	double genJetEta_j = em->genjeteta[j]; // genJetEta
	double genJetPhi_j = em->genjetphi[j]; // genJetPhi

	if(fabs(genJetEta_j) > etaMax) continue;
	
	
	if(genJetPt_j > leadingGenJetPt_i){

	  leadingGenJetPt_i = genJetPt_j;
	  
	}	

    }

    // pthat filter cut
    if(!passesLeadingGenJetPthatFilter(leadingGenJetPt_i,em->pthat)) continue;    
   
    // RECO JET LOOP
    for(int i = 0; i < em->njet ; i++){

      // JET VARIABLES
				
      JEC.SetJetPT(em->rawpt[i]);
      JEC.SetJetEta(em->jeteta[i]);
      JEC.SetJetPhi(em->jetphi[i]);

      double x = JEC.GetCorrectedPT();  // recoJetPt
      double y = em->jeteta[i]; // recoJetEta
      double z = em->jetphi[i]; // recoJetPhi
      double jetTrkMax_i = em->jetTrkMax[i];

      JEU.SetJetPT(x);
      JEU.SetJetEta(y);
      JEU.SetJetPhi(z);

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
		
      int genMuIndex = -1;
      bool hasInclGenMuonTag = false;
      bool hasMatchedGenMuonTag = false;

      bool hasInclRecoMuonTag = false;
      bool hasMatchedRecoMuonTag = false;
		
      bool hasGenJetMatch = false;
		     		
      int matchedPartonFlavor = em->matchedPartonFlavor[i];
      int refPartonFlavorForB = em->refparton_flavorForB[i];
      int hadronFlavorInt = em->matchedHadronFlavor[i];

      int jetFlavorInt = matchedPartonFlavor;
	       	
		
      // jet kinematic cuts
      if(TMath::Abs(y) > etaMax || x < jetPtCut) continue;
     
      eventHasGoodJet = true;
		        
      int jetPtIndex = getJetPtBin(x);


      // fill genJetPt vs pthat
      h_recoJetPt_pthat[0]->Fill(x,em->pthat,w);
      h_recoJetPt_pthat[CentralityIndex]->Fill(x,em->pthat,w);

      if(jetFlavorInt == 0 && CentralityIndex == 1 && jetPtIndex == 3){
	h_weight_pthat_xJets_C1J3->Fill(em->weight,em->pthat);
      }

      if(fabs(jetFlavorInt) == 5 && CentralityIndex == 1 && jetPtIndex == 3){
	h_weight_pthat_bJets_C1J3->Fill(em->weight,em->pthat);
      }

      
      double dR_recoGen_min = 100.0;
      double dPt_recoGen_min = 100.0;

      // look for a genJet match

      for(int j = 0; j < em->ngj ; j++){


	if(x < 50) continue;	

	double xg = em->genjetpt[j];  // genJetPt
	double yg = em->genjeteta[j]; // genJetEta
	double zg = em->genjetphi[j]; // genJetPhi

	double dR_j = getDr(yg,zg,y,z);
	double dPt_j = x/xg;
			
	if(dR_j < dR_recoGen_min){
				
	  hasGenJetMatch = true;		
	  dR_recoGen_min = dR_j;
	  dPt_recoGen_min = dPt_j;

	}	

      }

      if(hasGenJetMatch){

	h_recoGenDr_flavor[0][0]->Fill(dR_recoGen_min,jetFlavorInt,w);
	h_recoGenDr_flavor[0][jetPtIndex]->Fill(dR_recoGen_min,jetFlavorInt,w);
	h_recoGenDr_flavor[CentralityIndex][0]->Fill(dR_recoGen_min,jetFlavorInt,w);
	h_recoGenDr_flavor[CentralityIndex][jetPtIndex]->Fill(dR_recoGen_min,jetFlavorInt,w);

	h_recoGenDpt_flavor[0][0]->Fill(dPt_recoGen_min,jetFlavorInt,w);
	h_recoGenDpt_flavor[0][jetPtIndex]->Fill(dPt_recoGen_min,jetFlavorInt,w);
	h_recoGenDpt_flavor[CentralityIndex][0]->Fill(dPt_recoGen_min,jetFlavorInt,w);
	h_recoGenDpt_flavor[CentralityIndex][jetPtIndex]->Fill(dPt_recoGen_min,jetFlavorInt,w);

      }


      if(!skipGenParticles){
	// look for a genMuon match to recoJet
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

	  // look for recoMuon match to genMuon
	  for(int l = 0; l < em->nMu; l++){


	    double aR = em->muPt->at(l);
	    double bR = em->muEta->at(l);
	    double cR = em->muPhi->at(l);

	    if(!isQualityMuon_tight(em->muChi2NDF->at(l),
				    em->muInnerD0->at(l),
				    em->muInnerDz->at(l),
				    em->muMuonHits->at(l),
				    em->muPixelHits->at(l),
				    em->muIsGlobal->at(l),
				    em->muIsPF->at(l),
				    em->muStations->at(l),
				    em->muTrkLayers->at(l))) continue; // skip if muon doesnt pass quality cuts	



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
	

      // look for recoMuon match to recoJet		
      for(int m = 0; m < em->nMu; m++){

	double muPt_m = em->muPt->at(m);
	double muEta_m = em->muEta->at(m);
	double muPhi_m = em->muPhi->at(m);

	if(matchFlagR[m] == 1) continue;
	// muon kinematic cuts
	if(muPt_m < muPtCut || fabs(muEta_m) > trkEtaMax) continue;
	// muon quality cuts
	if(!isQualityMuon_tight(em->muChi2NDF->at(m),
				em->muInnerD0->at(m),
				em->muInnerDz->at(m),
				em->muMuonHits->at(m),
				em->muPixelHits->at(m),
				em->muIsGlobal->at(m),
				em->muIsPF->at(m),
				em->muStations->at(m),
				em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     

			



	if(isWDecayMuon(muPt_m,x)) continue; // skip if "WDecay" muon (has majority of jet pt) 
			
			
	// match to genMuon
	bool isMatchedRecoMuon = false;

	if(!skipGenParticles){

	  for(int j = 0; j < em->gppdgIDp->size(); j++){
			
	    if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;
		
	    if(getDr(em->muEta->at(m),em->muPhi->at(m),em->gpetap->at(j),em->gpphip->at(j)) < epsilon){

	      isMatchedRecoMuon = true;
			
	    }

	  }
	}

	// match to recoJets
	if(getDr(em->muEta->at(m),em->muPhi->at(m),y,z) < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel = getPtRel(muPt_m,muEta_m,muPhi_m,x,y,z);
	  muPt = muPt_m;
	  muEta = muEta_m;
	  muPhi = muPhi_m;
				
	  if(isMatchedRecoMuon) hasMatchedRecoMuonTag = true;

	}
						


      }

      // Fill the jet/event histograms
     

      h_inclRecoJetPt_flavor[0]->Fill(x,jetFlavorInt,w);
      h_inclRecoJetPt_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
      h_inclRecoJetEta_flavor[0]->Fill(y,jetFlavorInt,w);
      h_inclRecoJetEta_flavor[CentralityIndex]->Fill(y,jetFlavorInt,w);
      h_inclRecoJetPhi_flavor[0]->Fill(z,jetFlavorInt,w);
      h_inclRecoJetPhi_flavor[CentralityIndex]->Fill(z,jetFlavorInt,w);
      h_inclRecoJetPt_inclRecoJetEta[0]->Fill(x,y,w);
      h_inclRecoJetPt_inclRecoJetEta[CentralityIndex]->Fill(x,y,w);
      h_inclRecoJetPt_inclRecoJetPhi[0]->Fill(x,z,w);
      h_inclRecoJetPt_inclRecoJetPhi[CentralityIndex]->Fill(x,z,w);
      
      h_refPartonFlavorForB_matchedPartonFlavor[0]->Fill(refPartonFlavorForB,matchedPartonFlavor,w);
      h_refPartonFlavorForB_matchedPartonFlavor[CentralityIndex]->Fill(refPartonFlavorForB,matchedPartonFlavor,w);



      // histograms by jetPt index

      h_inclRecoJetEta_inclRecoJetPhi[0][0]->Fill(y,z,w);
      h_inclRecoJetEta_inclRecoJetPhi[CentralityIndex][0]->Fill(y,z,w);
      if(jetPtIndex > 0){
	h_inclRecoJetEta_inclRecoJetPhi[0][jetPtIndex]->Fill(y,z,w);
	h_inclRecoJetEta_inclRecoJetPhi[CentralityIndex][jetPtIndex]->Fill(y,z,w);
      }






      
		
      if(hasInclGenMuonTag){

	h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[0][0]->Fill(y,z,w);
	h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[CentralityIndex][0]->Fill(y,z,w);
	if(jetPtIndex > 0){
	  h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[0][jetPtIndex]->Fill(y,z,w);
	  h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[CentralityIndex][jetPtIndex]->Fill(y,z,w);
	}

	h_inclRecoJetPt_inclGenMuonTag_flavor[0]->Fill(x,jetFlavorInt,w);
	h_inclRecoJetPt_inclGenMuonTag_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
	h_inclRecoJetEta_inclGenMuonTag_flavor[0]->Fill(y,jetFlavorInt,w);
	h_inclRecoJetEta_inclGenMuonTag_flavor[CentralityIndex]->Fill(y,jetFlavorInt,w);
	h_inclRecoJetPhi_inclGenMuonTag_flavor[0]->Fill(z,jetFlavorInt,w);
	h_inclRecoJetPhi_inclGenMuonTag_flavor[CentralityIndex]->Fill(z,jetFlavorInt,w);
	h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag[0]->Fill(x,y,w);
	h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag[CentralityIndex]->Fill(x,y,w);
	h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag[0]->Fill(x,z,w);
	h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag[CentralityIndex]->Fill(x,z,w);

      } 

      if(hasInclRecoMuonTag){

	eventHasInclRecoMuonTag = true;

	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0][0]->Fill(y,z,w);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[CentralityIndex][0]->Fill(y,z,w);
	if(jetPtIndex > 0){
	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0][jetPtIndex]->Fill(y,z,w);
	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[CentralityIndex][jetPtIndex]->Fill(y,z,w);
	}

	

	h_inclRecoJetPt_inclRecoMuonTag_flavor[0]->Fill(x,jetFlavorInt,w);
	h_inclRecoJetPt_inclRecoMuonTag_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
	h_inclRecoJetEta_inclRecoMuonTag_flavor[0]->Fill(y,jetFlavorInt,w);
	h_inclRecoJetEta_inclRecoMuonTag_flavor[CentralityIndex]->Fill(y,jetFlavorInt,w);
	h_inclRecoJetPhi_inclRecoMuonTag_flavor[0]->Fill(z,jetFlavorInt,w);
	h_inclRecoJetPhi_inclRecoMuonTag_flavor[CentralityIndex]->Fill(z,jetFlavorInt,w);
	h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[0]->Fill(x,y,w);
	h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[CentralityIndex]->Fill(x,y,w);
	h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[0]->Fill(x,z,w);
	h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[CentralityIndex]->Fill(x,z,w);

	
	if(evtTriggerDecision){
	 
	  eventHasInclRecoMuonTagPlusTrigger = true;

	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[0][0]->Fill(y,z,w);
	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[CentralityIndex][0]->Fill(y,z,w);
	  if(jetPtIndex > 0){
	    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[0][jetPtIndex]->Fill(y,z,w);
	    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[CentralityIndex][jetPtIndex]->Fill(y,z,w);
	  }

	  h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor[0]->Fill(x,jetFlavorInt,w);
	  h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
	  h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor[0]->Fill(y,jetFlavorInt,w);
	  h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(y,jetFlavorInt,w);
	  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor[0]->Fill(z,jetFlavorInt,w);
	  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(z,jetFlavorInt,w);
	  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[0]->Fill(x,y,w);
	  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(x,y,w);
	  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[0]->Fill(x,z,w);
	  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(x,z,w);


	    
	  h_muptrel_inclRecoMuonTag_triggerOn_flavor[0][0]->Fill(muPtRel,jetFlavorInt,w);
	  h_mupt_inclRecoMuonTag_triggerOn_flavor[0][0]->Fill(muPt,jetFlavorInt,w);
	  h_mueta_inclRecoMuonTag_triggerOn_flavor[0][0]->Fill(muEta,jetFlavorInt,w);
	  h_muphi_inclRecoMuonTag_triggerOn_flavor[0][0]->Fill(muPhi,jetFlavorInt,w);

	  h_mupt_jetpt[0]->Fill(muPt,x,w);
	  h_mupt_jetpt[CentralityIndex]->Fill(muPt,x,w);
	  
	  h_muptrel_jetpt[0]->Fill(muPtRel,x,w);
	  h_muptrel_jetpt[CentralityIndex]->Fill(muPtRel,x,w);
	 

	  if(jetPtIndex > 0){

	    	    
	    h_muptrel_inclRecoMuonTag_triggerOn_flavor[0][jetPtIndex]->Fill(muPtRel,jetFlavorInt,w);
	    h_muptrel_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][0]->Fill(muPtRel,jetFlavorInt,w);
	    h_muptrel_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][jetPtIndex]->Fill(muPtRel,jetFlavorInt,w);

	    h_mupt_inclRecoMuonTag_triggerOn_flavor[0][jetPtIndex]->Fill(muPt,jetFlavorInt,w);
	    h_mupt_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][0]->Fill(muPt,jetFlavorInt,w);
	    h_mupt_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][jetPtIndex]->Fill(muPt,jetFlavorInt,w);

	    h_mueta_inclRecoMuonTag_triggerOn_flavor[0][jetPtIndex]->Fill(muEta,jetFlavorInt,w);
	    h_mueta_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][0]->Fill(muEta,jetFlavorInt,w);
	    h_mueta_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][jetPtIndex]->Fill(muEta,jetFlavorInt,w);

	    h_muphi_inclRecoMuonTag_triggerOn_flavor[0][jetPtIndex]->Fill(muPhi,jetFlavorInt,w);
	    h_muphi_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][0]->Fill(muPhi,jetFlavorInt,w);
	    h_muphi_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][jetPtIndex]->Fill(muPhi,jetFlavorInt,w);

	    h_mupt_muptrel[0][0]->Fill(muPt,muPtRel,w);
	    h_mupt_muptrel[CentralityIndex][0]->Fill(muPt,muPtRel,w);
	    h_mupt_muptrel[CentralityIndex][jetPtIndex]->Fill(muPt,muPtRel,w);
	    
	  }
	} 

	if(hasMatchedRecoMuonTag){

	  eventHasMatchedRecoMuonTag = true;

	  h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[0][0]->Fill(y,z,w);
	  h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[CentralityIndex][0]->Fill(y,z,w);
	  if(jetPtIndex > 0){
	    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[0][jetPtIndex]->Fill(y,z,w);
	    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[CentralityIndex][jetPtIndex]->Fill(y,z,w);
	  }

	  h_inclRecoJetPt_matchedRecoMuonTag_flavor[0]->Fill(x,jetFlavorInt,w);
	  h_inclRecoJetPt_matchedRecoMuonTag_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
	  h_inclRecoJetEta_matchedRecoMuonTag_flavor[0]->Fill(y,jetFlavorInt,w);
	  h_inclRecoJetEta_matchedRecoMuonTag_flavor[CentralityIndex]->Fill(y,jetFlavorInt,w);
	  h_inclRecoJetPhi_matchedRecoMuonTag_flavor[0]->Fill(z,jetFlavorInt,w);
	  h_inclRecoJetPhi_matchedRecoMuonTag_flavor[CentralityIndex]->Fill(z,jetFlavorInt,w);
	  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag[0]->Fill(x,y,w);
	  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag[CentralityIndex]->Fill(x,y,w);
	  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag[0]->Fill(x,z,w);
	  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag[CentralityIndex]->Fill(x,z,w);

	  if(evtTriggerDecision){

	    eventHasMatchedRecoMuonTagPlusTrigger = true;

	    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[0][0]->Fill(y,z,w);
	    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[CentralityIndex][0]->Fill(y,z,w);
	    if(jetPtIndex > 0){
	      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[0][jetPtIndex]->Fill(y,z,w);
	      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[CentralityIndex][jetPtIndex]->Fill(y,z,w);
	    }
	  	   
	    h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor[0]->Fill(x,jetFlavorInt,w);
	    h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
	    h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor[0]->Fill(y,jetFlavorInt,w);
	    h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(y,jetFlavorInt,w);
	    h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor[0]->Fill(z,jetFlavorInt,w);
	    h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(z,jetFlavorInt,w);
	    h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn[0]->Fill(x,y,w);
	    h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn[CentralityIndex]->Fill(x,y,w);
	    h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[0]->Fill(x,z,w);
	    h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[CentralityIndex]->Fill(x,z,w);

	  }

	}

      }
       

    }
    // END recoJet LOOP

    if(eventHasGoodJet){

      h_hiBin->Fill(em->hiBin-10,w);
      h_vz[0]->Fill(em->vz,w);
      h_vz[CentralityIndex]->Fill(em->vz,w);

      if(eventHasInclRecoMuonTag){

	h_hiBin_inclRecoMuonTag->Fill(em->hiBin-10,w);
	h_vz_inclRecoMuonTag[0]->Fill(em->vz,w);
	h_vz_inclRecoMuonTag[CentralityIndex]->Fill(em->vz,w);

	if(eventHasInclRecoMuonTagPlusTrigger){

	  h_hiBin_inclRecoMuonTag_triggerOn->Fill(em->hiBin-10,w);
	  h_vz_inclRecoMuonTag_triggerOn[0]->Fill(em->vz,w);
	  h_vz_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(em->vz,w);

	}
       

      }

      if(eventHasMatchedRecoMuonTag){

	h_hiBin_matchedRecoMuonTag->Fill(em->hiBin-10,w);
	h_vz_matchedRecoMuonTag[0]->Fill(em->vz,w);
	h_vz_matchedRecoMuonTag[CentralityIndex]->Fill(em->vz,w);

	if(eventHasMatchedRecoMuonTagPlusTrigger){

	  h_hiBin_matchedRecoMuonTag_triggerOn->Fill(em->hiBin-10,w);
	  h_vz_matchedRecoMuonTag_triggerOn[0]->Fill(em->vz,w);
	  h_vz_matchedRecoMuonTag_triggerOn[CentralityIndex]->Fill(em->vz,w);

	}
       

      }
     

    }


    

    // start genJet LOOP
    for(int i = 0; i < em->ngj ; i++){


      double x = em->genjetpt[i];  // recoJetPt
      double y = em->genjeteta[i]; // recoJetEta
      double z = em->genjetphi[i]; // recoJetPhi

      double muPtRel = -1.0;

      if(TMath::Abs(y) > etaMax || x < jetPtCut) continue;


      // fill genJetPt vs pthat
      h_genJetPt_pthat[0]->Fill(x,em->pthat,w);
      h_genJetPt_pthat[CentralityIndex]->Fill(x,em->pthat,w);



      int jetPtIndex = getJetPtBin(x);

      //cout << "jetPt = " << x << " | index = " << jetPtIndex << endl;

      // GET FLAVOR FROM RECO MATCH
      bool hasRecoJetMatch = false;
      int recoJetFlavorFlag = 0;
      double minDr = 100.0;
      int jetFlavorInt = 19;
	
      double matchedRecoJetPt = -1.0;
		

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

     
      if(hasRecoJetMatch) {
	jetFlavorInt = em->refparton_flavorForB[recoJetFlavorFlag];
	matchedRecoJetPt = em->jetpt[recoJetFlavorFlag];
	//cout << "genJet flavor match: (event#" << evi << ", genJet#" << i << ", recoJet#" << recoJetFlavorFlag << ") = " << jetFlavorInt << endl;
      }

      int genMuIndex = -1;
      bool hasInclGenMuonTag = false;
      bool hasMatchedGenMuonTag = false;

      bool hasInclRecoMuonTag = false;
      bool hasMatchedRecoMuonTag = false;



      // look for a genMuon match
      if(!skipGenParticles){

	for(int j = 0; j < em->gppdgIDp->size(); j++){

	  //cout << "N_genParticles = " << em->gppdgIDp->size() << endl;
	  //cout << "pdg of particle " << j <<" = " << em->gppdgIDp->at(j) << endl;

                        
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

	  //cout << "genMuPt = " << a << ", genMuEta = " << b << endl;

	  for(int l = 0; l < em->nMu; l++){


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

	  for(int l = 0; l < em->gppdgIDp->size(); l++){

	    //cout << "genID = " << em->gppdgIDp->at(j) << endl;
			
	    if(TMath::Abs(em->gppdgIDp->at(l)) != 13) continue;

	    if(em->gpptp->at(l) < muPtCut || fabs(em->gpetap->at(l)) > trkEtaMax) continue;                        
		
	    if(getDr(em->muEta->at(m),em->muPhi->at(m),em->gpetap->at(l),em->gpphip->at(l)) < epsilon){

	      isMatchedRecoMuon = true;
			
	    }

	  }

	}

	// match to genJets
	if(getDr(em->muEta->at(m),em->muPhi->at(m),y,z) < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel = getPtRel(em->muPt->at(m),em->muEta->at(m),em->muPhi->at(m),x,y,z);

	  //cout << "(Event "<< evi << ", Jet " << i << ", Muon " << m << ") muPtRel = " << muPtRel << endl;
				
	  if(isMatchedRecoMuon) hasMatchedRecoMuonTag = true;

	}
						


      }

      // Fill the jet histograms

		

      h_inclGenJetPt_flavor[0]->Fill(x,jetFlavorInt,w);
      h_inclGenJetPt_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);

      h_matchedRecoJetPt_genJetPt[0]->Fill(matchedRecoJetPt,x,w);
      h_matchedRecoJetPt_genJetPt[CentralityIndex]->Fill(matchedRecoJetPt,x,w);
        

      if(hasInclGenMuonTag){

	
		
	h_inclGenJetPt_inclGenMuonTag_flavor[0]->Fill(x,jetFlavorInt,w);
	h_inclGenJetPt_inclGenMuonTag_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);

      } 

      if(hasInclRecoMuonTag){

	h_inclGenJetPt_inclRecoMuonTag_flavor[0]->Fill(x,jetFlavorInt,w);
	h_inclGenJetPt_inclRecoMuonTag_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
			
	if(evtTriggerDecision){
	  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor[0]->Fill(x,jetFlavorInt,w);
	  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
	  h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[0][0]->Fill(muPtRel,jetFlavorInt,w);
	  if(jetPtIndex > 0){
	    h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[0][jetPtIndex]->Fill(muPtRel,jetFlavorInt,w);
	    h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][0]->Fill(muPtRel,jetFlavorInt,w);
	    h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][jetPtIndex]->Fill(muPtRel,jetFlavorInt,w);
	  }
	} 

	if(hasMatchedRecoMuonTag){

	  h_inclGenJetPt_matchedRecoMuonTag_flavor[0]->Fill(x,jetFlavorInt,w);
	  h_inclGenJetPt_matchedRecoMuonTag_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);

	  if(evtTriggerDecision){
	    h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor[0]->Fill(x,jetFlavorInt,w);
	    h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
	  }


	}

      }
		


    }// end genJet loop
    


  } // end event loop

  h_NEvents->Fill(eventCounter);


 
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  h_NEvents->Write();

  h_hiBin->Write();
  h_hiBin_inclGenMuonTag->Write();
  h_hiBin_inclRecoMuonTag->Write();
  h_hiBin_inclRecoMuonTag_triggerOn->Write();
  h_hiBin_matchedRecoMuonTag->Write();
  h_hiBin_matchedRecoMuonTag_triggerOn->Write();
  h_weight_pthat_xJets_C1J3->Write();
  h_weight_pthat_bJets_C1J3->Write();

  
  for(int i = 0; i < NCentralityIndices; i++){

    h_vz[i]->Write();
    h_vz_inclGenMuonTag[i]->Write();
    h_vz_inclRecoMuonTag[i]->Write();
    h_vz_matchedRecoMuonTag[i]->Write();
    h_vz_inclRecoMuonTag_triggerOn[i]->Write();
    h_vz_matchedRecoMuonTag_triggerOn[i]->Write();

    h_inclRecoJetPt_flavor[i]->Write();
    h_inclRecoJetEta_flavor[i]->Write();
    h_inclRecoJetPhi_flavor[i]->Write();
    h_inclRecoJetPt_inclRecoJetEta[i]->Write();
    h_inclRecoJetPt_inclRecoJetPhi[i]->Write();

    h_inclRecoJetPt_inclGenMuonTag_flavor[i]->Write();
    h_inclRecoJetEta_inclGenMuonTag_flavor[i]->Write();
    h_inclRecoJetPhi_inclGenMuonTag_flavor[i]->Write();
    h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag[i]->Write();
    h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag[i]->Write();

    h_inclRecoJetPt_inclRecoMuonTag_flavor[i]->Write();
    h_inclRecoJetEta_inclRecoMuonTag_flavor[i]->Write();
    h_inclRecoJetPhi_inclRecoMuonTag_flavor[i]->Write();
    h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[i]->Write();
    h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[i]->Write();

    h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor[i]->Write();
    h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor[i]->Write();
    h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor[i]->Write();
    h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[i]->Write();
    h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i]->Write();

    h_inclRecoJetPt_matchedRecoMuonTag_flavor[i]->Write();
    h_inclRecoJetEta_matchedRecoMuonTag_flavor[i]->Write();
    h_inclRecoJetPhi_matchedRecoMuonTag_flavor[i]->Write();
    h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag[i]->Write();
    h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag[i]->Write();

    h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor[i]->Write();
    h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor[i]->Write();
    h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor[i]->Write();
    h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn[i]->Write();
    h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[i]->Write();

    
    h_recoJetPt_pthat[i]->Write();
    h_genJetPt_pthat[i]->Write();

    h_refPartonFlavorForB_matchedPartonFlavor[i]->Write();
    h_matchedRecoJetPt_genJetPt[i]->Write();
		
    h_inclGenJetPt_flavor[i]->Write();
    h_inclGenJetPt_inclGenMuonTag_flavor[i]->Write();
    h_inclGenJetPt_inclRecoMuonTag_flavor[i]->Write();
    h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor[i]->Write();
    h_inclGenJetPt_matchedRecoMuonTag_flavor[i]->Write();
    h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor[i]->Write();

    h_mupt_jetpt[i]->Write();
    h_muptrel_jetpt[i]->Write();

    for(int j = 0; j < NJetPtIndices; j++){

      h_inclRecoJetEta_inclRecoJetPhi[i][j]->Write();
      h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[i][j]->Write();
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j]->Write();
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j]->Write();
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[i][j]->Write();
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[i][j]->Write();
      
      h_muptrel_inclRecoMuonTag_triggerOn_flavor[i][j]->Write();
      h_mupt_inclRecoMuonTag_triggerOn_flavor[i][j]->Write();
      h_mueta_inclRecoMuonTag_triggerOn_flavor[i][j]->Write();
      h_muphi_inclRecoMuonTag_triggerOn_flavor[i][j]->Write();
      h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[i][j]->Write();
      h_mupt_muptrel[i][j]->Write();
      h_recoGenDr_flavor[i][j]->Write();
      h_recoGenDpt_flavor[i][j]->Write();
    }
  }


  wf->Close();
  return;
  // END WRITE

}
