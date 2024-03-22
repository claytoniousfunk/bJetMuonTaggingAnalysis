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
// general analysis variables
#include "../../../headers/AnalysisSetupV2p1.h"

// eta-phi mask function
#include "../../../headers/functions/etaPhiMask.h"
// getDr function
#include "../../../headers/functions/getDr.h"
// getJetPtBin function
#include "../../../headers/functions/getJetPtBin.h"
// getCentBin function
#include "../../../headers/functions/getCentBin_v2.h"
// getPtRel function
#include "../../../headers/functions/getPtRel.h"
// isQualityMuon_hybridSoft function
#include "../../../headers/functions/isQualityMuon_hybridSoft.h"
// isQualityMuon_tight function
#include "../../../headers/functions/isQualityMuon_tight.h"
// isWDecayMuon function
#include "../../../headers/functions/isWDecayMuon.h"
// isWDecayMuon_raw function (input is rawJetPt)
#include "../../../headers/functions/isWDecayMuon_raw.h"
// triggerIsOn function
#include "../../../headers/functions/triggerIsOn.h"
// pthat filter function
#include "../../../headers/functions/passesLeadingGenJetPthatFilter.h"
// JetTrkMax filter function
#include "../../../headers/functions/passesJetTrkMaxFilter.h"
// print introduction
#include "../../../headers/introductions/printIntroduction_PbPb_scan_V3p7.h"
// analysis config
//#include "../../../headers/config/config_PbPb_SingleMuon.h"
#include "../../../headers/config/config_PbPb_MinBias.h"
//#include "../../../headers/config/config_PbPb_diJet.h"
// read config
#include "../../../headers/config/readConfig.h"
// initialize histograms
// ~~~~~~~~~ event variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D *h_NEvents;
// -----------------------------------------events w/ incl. reco jet -------
TH1D *h_vz[NCentralityIndices];
TH1D *h_hiBin;
// ----------------------- events w/ incl. reco jet + incl. reco muon tag --
TH1D *h_vz_inclRecoMuonTag[NCentralityIndices];
TH1D *h_hiBin_inclRecoMuonTag;
// ---------- events w/ incl. reco jet + incl. reco muon tag + trigger on --
TH1D *h_vz_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH1D *h_hiBin_inclRecoMuonTag_triggerOn;
// ~~~~~~~~~ jet variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ----------------------------------------- incl. reco jets --------------
TH1D *h_inclRecoJetPt[NCentralityIndices];
TH1D *h_inclRecoJetEta[NCentralityIndices];
TH1D *h_inclRecoJetPhi[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetEta[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetPhi[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoJetPhi[NCentralityIndices][NJetPtIndices];
// ------------------------------ incl. reco jets + incl. reco muon tag ----
TH1D *h_inclRecoJetPt_inclRecoMuonTag[NCentralityIndices];
TH1D *h_inclRecoJetEta_inclRecoMuonTag[NCentralityIndices];
TH1D *h_inclRecoJetPhi_inclRecoMuonTag[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[NCentralityIndices][NJetPtIndices];
// ------------------ incl. reco jets + incl. reco muon tag + trigger on ----
TH1D *h_inclRecoJetPt_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH1D *h_inclRecoJetEta_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH1D *h_inclRecoJetPhi_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[NCentralityIndices][NJetPtIndices];
// ~~~~~~~~~ muon variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D *h_inclMuPt;
TH1D *h_muptrel_inclRecoMuonTag_triggerOn[NCentralityIndices][NJetPtIndices];
TH1D *h_mupt_inclRecoMuonTag_triggerOn[NCentralityIndices][NJetPtIndices];
TH1D *h_mueta_inclRecoMuonTag_triggerOn[NCentralityIndices][NJetPtIndices];
TH1D *h_muphi_inclRecoMuonTag_triggerOn[NCentralityIndices][NJetPtIndices];
// ~~~~~~~~~ analysis histograms ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D *h_muPtOverJetPt[NCentralityIndices][NJetPtIndices];
TH1D *h_muJetDr[NCentralityIndices][NJetPtIndices];
TH2D *h_mupt_jetpt[NCentralityIndices];
TH2D *h_mupt_muptrel[NCentralityIndices][NJetPtIndices];
TH2D *h_muptrel_jetpt[NCentralityIndices];

///////////////////////  start the program
void PbPb_scan(int group = 1){

  // TString input = Form("../../../rootFiles/skimmingOutput/PbPb/output_HardProbes/PbPb_HardProbes_skim_output_%i.root",group);
  // TString output = Form("output_HardProbes_mu12/PbPb_HardProbes_scan_output_%i.root",group);

  // TString input = Form("../../../rootFiles/skimmingOutput/PbPb/output_MinBias/PbPb_MinBias_skim_output_%i.root",group);
  // TString output = Form("output_MinBias_mu12/PbPb_MinBias_scan_output_%i.root",group);

  TString input = Form("../../../rootFiles/skimmingOutput/PbPb/output_SingleMuon/PbPb_SingleMuon_skim_output_%i.root",group);
  TString output = Form("output_SingleMuon_mu5/PbPb_SingleMuon_scan_output_%i.root",group);
  
  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_DATA_L2Relative_AK4PF.txt"); // L2Relative correction
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_DATA_L2L3Residual_AK4PF.txt"); // L2L3Residual correction
  JetCorrector JEC(Files);
  /// print out some info
  printIntroduction_PbPb_scan_V3p7();
  readConfig();
  // define histograms
  h_NEvents = new TH1D("h_NEvents","Number of events (L3Mu5 trigger)",100,0,10000);
  h_hiBin = new TH1D("h_hiBin","hiBin, events with inclRecoJet",200,0,200);
  h_hiBin_inclRecoMuonTag = new TH1D("h_hiBin_inclRecoMuonTag","hiBin, events with inclRecoJet-inclRecoMuonTag",200,0,200);
  h_hiBin_inclRecoMuonTag_triggerOn = new TH1D("h_hiBin_inclRecoMuonTag_triggerOn","hiBin, events with inclRecoJet-inclRecoMuonTag-triggerOn",200,0,200);
  h_inclMuPt = new TH1D("h_inclMuPt","incl. muon p_{T}; muon p_{T}; Entries",NMuPtBins,muPtMin,muPtMax);

  h_NEvents->Sumw2();
  h_hiBin->Sumw2();
  h_hiBin_inclRecoMuonTag->Sumw2();
  h_hiBin_inclRecoMuonTag_triggerOn->Sumw2();
  h_inclMuPt->Sumw2();
  
  // for loop through the centrality indices
  for(int i = 0; i < NCentralityIndices; i++){
    // the inclusive centrality histogram	
    if(i==0){
      // ---------------------- event histograms --------------------------------
      h_vz[i] = new TH1D(Form("h_vz_C%i",i),Form("vz, events with inclRecoJet, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag[i] = new TH1D(Form("h_vz_inclRecoMuonTag_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_vz_inclRecoMuonTag_triggerOn_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag-triggerOn, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      // ----------------------------------------- incl. reco jets --------------   
      h_inclRecoJetPt[i] = new TH1D(Form("h_inclRecoJetPt_C%i",i),Form("incl. reco p_{T}^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax);
      h_inclRecoJetEta[i] = new TH1D(Form("h_inclRecoJetEta_C%i",i),Form("incl. reco #eta^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NEtaBins,etaMin,etaMax);
      h_inclRecoJetPhi[i] = new TH1D(Form("h_inclRecoJetPhi_C%i",i),Form("incl. reco #phi^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPhiBins,phiMin,phiMax);
      h_inclRecoJetPt_inclRecoJetEta[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ------------------------------ incl. reco jets + incl. reco muon tag ----
      h_inclRecoJetPt_inclRecoMuonTag[i] = new TH1D(Form("h_inclRecoJetPt_inclRecoMuonTag_C%i",i),Form("incl. reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax);
      h_inclRecoJetEta_inclRecoMuonTag[i] = new TH1D(Form("h_inclRecoJetEta_inclRecoMuonTag_C%i",i),Form("incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NEtaBins,etaMin,etaMax);
      h_inclRecoJetPhi_inclRecoMuonTag[i] = new TH1D(Form("h_inclRecoJetPhi_inclRecoMuonTag_C%i",i),Form("incl. reco #phi^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPhiBins,phiMin,phiMax);
      h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ---------- events w/ incl. reco jet + incl. reco muon tag + trigger on --
      h_inclRecoJetPt_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax);
      h_inclRecoJetEta_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NEtaBins,etaMin,etaMax);
      h_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #phi^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPhiBins,phiMin,phiMax);
      h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // --------------- analysis histograms ------------------------------------
      h_mupt_jetpt[i] = new TH2D(Form("h_mupt_jetpt_C%i",i),Form("jetPt vs. muPt, hiBin %i - %i", centEdges[0], centEdges[NCentralityIndices-1]),NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
      h_muptrel_jetpt[i] = new TH2D(Form("h_muptrel_jetpt_C%i",i),Form("jetPt vs. muRelPt, hiBin %i - %i", centEdges[0], centEdges[NCentralityIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
    }
    else{
      // ---------------------- event histograms --------------------------------
      h_vz[i] = new TH1D(Form("h_vz_C%i",i),Form("vz, events with inclRecoJet, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag[i] = new TH1D(Form("h_vz_inclRecoMuonTag_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_vz_inclRecoMuonTag_triggerOn_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag-triggerOn, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      // ----------------------------------------- incl. reco jets --------------   
      h_inclRecoJetPt[i] = new TH1D(Form("h_inclRecoJetPt_C%i",i),Form("incl. reco p_{T}^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax);
      h_inclRecoJetEta[i] = new TH1D(Form("h_inclRecoJetEta_C%i",i),Form("incl. reco #eta^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NEtaBins,etaMin,etaMax);
      h_inclRecoJetPhi[i] = new TH1D(Form("h_inclRecoJetPhi_C%i",i),Form("incl. reco #phi^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPhiBins,phiMin,phiMax);
      h_inclRecoJetPt_inclRecoJetEta[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ------------------------------ incl. reco jets + incl. reco muon tag ----
      h_inclRecoJetPt_inclRecoMuonTag[i] = new TH1D(Form("h_inclRecoJetPt_inclRecoMuonTag_C%i",i),Form("incl. reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax);
      h_inclRecoJetEta_inclRecoMuonTag[i] = new TH1D(Form("h_inclRecoJetEta_inclRecoMuonTag_C%i",i),Form("incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NEtaBins,etaMin,etaMax);
      h_inclRecoJetPhi_inclRecoMuonTag[i] = new TH1D(Form("h_inclRecoJetPhi_inclRecoMuonTag_C%i",i),Form("incl. reco #phi^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPhiBins,phiMin,phiMax);
      h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ---------- events w/ incl. reco jet + incl. reco muon tag + trigger on --
      h_inclRecoJetPt_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax);
      h_inclRecoJetEta_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NEtaBins,etaMin,etaMax);
      h_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #phi^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPhiBins,phiMin,phiMax);
      h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #eta^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
      h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%i",i),Form("incl. reco #phi^{jet} vs. incl reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
      // ----------- analysis histograms -----------------------------------------
      h_mupt_jetpt[i] = new TH2D(Form("h_mupt_jetpt_C%i",i),Form("jetPt vs. muPt, hiBin %i - %i", centEdges[i-1], centEdges[i]),NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
      h_muptrel_jetpt[i] = new TH2D(Form("h_muptrel_jetpt_C%i",i),Form("jetPt vs. muRelPt, hiBin %i - %i", centEdges[i-1], centEdges[i]),NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);    
    }
    // sumw2 commands
    h_vz[i]->Sumw2();
    h_vz_inclRecoMuonTag[i]->Sumw2();
    h_vz_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_inclRecoJetPt[i]->Sumw2();
    h_inclRecoJetEta[i]->Sumw2();
    h_inclRecoJetPhi[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetEta[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetPhi[i]->Sumw2();
    h_inclRecoJetPt_inclRecoMuonTag[i]->Sumw2();
    h_inclRecoJetEta_inclRecoMuonTag[i]->Sumw2();
    h_inclRecoJetPhi_inclRecoMuonTag[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[i]->Sumw2();
    h_inclRecoJetPt_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_inclRecoJetEta_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_mupt_jetpt[i]->Sumw2();
    h_muptrel_jetpt[i]->Sumw2();
    // loop through jet pt indices
    for(int j = 0; j < NJetPtIndices; j++){
      if(i==0 && j==0){
	h_muptrel_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_muptrel_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("p_{T}^{rel}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_mupt_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_mupt_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("p_{T}^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax);
	h_mueta_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_mueta_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("#eta^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_muphi_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_muphi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("#phi^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax);
	h_muPtOverJetPt[i][j] = new TH1D(Form("h_muPtOverJetPt_C%iJ%i",i,j),Form("p_{T}^{#mu} / p_{T}^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
	h_muJetDr[i][j] = new TH1D(Form("h_muJetDr_C%iJ%i",i,j),Form("#DeltaR(muon,jet), hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs. muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      }
      else if(i==0){
	h_muptrel_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_muptrel_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("p_{T}^{rel}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_mupt_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_mupt_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("p_{T}^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax);
	h_mueta_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_mueta_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("#eta^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_muphi_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_muphi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("#phi^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax);
	h_muPtOverJetPt[i][j] = new TH1D(Form("h_muPtOverJetPt_C%iJ%i",i,j),Form("p_{T}^{#mu} / p_{T}^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
	h_muJetDr[i][j] = new TH1D(Form("h_muJetDr_C%iJ%i",i,j),Form("#DeltaR(muon,jet), hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs. muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      }
      else if(j==0){
	h_muptrel_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_muptrel_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("p_{T}^{rel}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_mupt_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_mupt_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("p_{T}^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax);
	h_mueta_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_mueta_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("#eta^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_muphi_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_muphi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("#phi^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax);
	h_muPtOverJetPt[i][j] = new TH1D(Form("h_muPtOverJetPt_C%iJ%i",i,j),Form("p_{T}^{#mu} / p_{T}^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
	h_muJetDr[i][j] = new TH1D(Form("h_muJetDr_C%iJ%i",i,j),Form("#DeltaR(muon,jet), hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs. muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      }
      else{
	h_muptrel_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_muptrel_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("p_{T}^{rel}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_mupt_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_mupt_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("p_{T}^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax);
	h_mueta_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_mueta_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("#eta^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_muphi_inclRecoMuonTag_triggerOn[i][j] = new TH1D(Form("h_muphi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("#phi^{#mu}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax);
	h_muPtOverJetPt[i][j] = new TH1D(Form("h_muPtOverJetPt_C%iJ%i",i,j),Form("p_{T}^{#mu} / p_{T}^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
	h_muJetDr[i][j] = new TH1D(Form("h_muJetDr_C%iJ%i",i,j),Form("#DeltaR(muon,jet), hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs. muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      }
      h_muptrel_inclRecoMuonTag_triggerOn[i][j]->Sumw2();
      h_mupt_inclRecoMuonTag_triggerOn[i][j]->Sumw2();
      h_mueta_inclRecoMuonTag_triggerOn[i][j]->Sumw2();
      h_muphi_inclRecoMuonTag_triggerOn[i][j]->Sumw2();
      h_muPtOverJetPt[i][j]->Sumw2();
      h_muJetDr[i][j]->Sumw2();
      h_mupt_muptrel[i][j]->Sumw2();
      h_inclRecoJetEta_inclRecoJetPhi[i][j]->Sumw2();
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j]->Sumw2();
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j]->Sumw2();
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
  cout << "	Variables initilized!" << endl << endl ;
  int NEvents = em->evtTree->GetEntries();
  cout << "	Number of events = " << NEvents << endl;
  //int NJets = em->recoJetTree->GetEntries();
  int NJets = em->recoJetTree->GetEntries();
  cout << "     Number of jets = " << NJets << endl;

  // define event filters
  em->regEventFilter(NeventFilters, eventFilters);
  
  
  
  TRandom *randomGenerator = new TRandom2();

  // jet-energy resolution fit function
  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,300);
  JER_fxn->SetParameter(0,-1.91758e-05);
  JER_fxn->SetParameter(1,-1.79691e+00);
  JER_fxn->SetParameter(2,1.09880e+01);


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
    if(fabs(em->vz) > 15.0) continue;
    // event filters
    if(em->checkEventFilter()) continue;

    // In data, event weight = 1
    double w = 1.0;

   
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};

    int matchFlagR[10] = {0,0,0,0,0,0,0,0,0,0};
	
    int CentralityIndex = getCentBin(em->hiBin);
    if(CentralityIndex < 0) continue;

    bool evtTriggerDecision = false;

    int triggerDecision = em->HLT_HIL3Mu5_NHitQ10_v1;
    int triggerDecision_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl;

    // int triggerDecision = em->HLT_HIL3Mu7_NHitQ10_v1;
    // int triggerDecision_Prescl = em->HLT_HIL3Mu7_NHitQ10_v1_Prescl;

    // int triggerDecision = em->HLT_HIL3Mu12_v1;
    // int triggerDecision_Prescl = em->HLT_HIL3Mu12_v1_Prescl;
    

    // if(triggerDecision_Prescl == 0) continue;
    // else if(triggerDecision_Prescl == 1){
    //   w = 1.0;
    // }
    // else if(triggerDecision_Prescl == 2){
    //   w = 1.0 / 0.0318182;
    // }
    // else if(triggerDecision_Prescl == 3){
    //   w = 1.0 / 13.4136;
    // }
    // else if(triggerDecision_Prescl == 5){
    //   w = 1.0 / 8.80909;
    // }
    // else if(triggerDecision_Prescl == 7){
    //   w = 1.0 / 1.48182;
    // }
    // else if(triggerDecision_Prescl == 11){
    //   w = 1.0 / 6.06818;
    // }
    // else if(triggerDecision_Prescl == 13){
    //   w = 1.0 / 9.90455;
    // }
    // else if(triggerDecision_Prescl == 15){
    //   w = 1.0 / 0.318182;
    // }
    // else if(triggerDecision_Prescl == 17){
    //   w = 1.0 / 0.15;
    // }
    // else if(triggerDecision_Prescl == 23){
    //   w = 1.0 / 9.80455;
    // }
    // else{continue ; }

    double w_trig = w;
    //double w_trig = 1.0 / ( triggerDecision_Prescl * 1.0 ); // set weight as 1/prescl for triggered events
    //double w_trig = 1.0; // don't scale by prescales for templates
    
    // skip if the trigger is off or if the prescale is zero
    if(triggerIsOn(triggerDecision,triggerDecision_Prescl)){
      evtTriggerDecision = true;
      eventCounter++;
    }
   
    bool eventHasGoodJet = false;
    bool eventHasInclRecoMuonTag = false;
    bool eventHasInclRecoMuonTagPlusTrigger = false;
    bool eventHasMatchedRecoMuonTag = false;
    bool eventHasMatchedRecoMuonTagPlusTrigger = false;

    
    // RECO MUON LOOP
    for(int m = 0; m < em->nMu; m++){

      double muPt_m = em->muPt->at(m);
      double muEta_m = em->muEta->at(m);
      double muPhi_m = em->muPhi->at(m);

      //cout << "(muPt, muEta, muPhi) = (" << muPt_m << ", " << muEta_m << ", " << muPhi_m << ")" << endl;

      // skip if muon has already been matched to a jet in this event
      // muon kinematic cuts
      if(muPt_m < muPtCut || fabs(muEta_m) > trkEtaMax) continue;
      // muon quality cuts
      // if(!isQualityMuon_tight(em->muChi2NDF->at(m),
      // 			      em->muInnerD0->at(m),
      // 			      em->muInnerDz->at(m),
      // 			      em->muMuonHits->at(m),
      // 			      em->muPixelHits->at(m),
      // 			      em->muIsGlobal->at(m),
      // 			      em->muIsPF->at(m),
      // 			      em->muStations->at(m),
      // 			      em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts

      if(!isQualityMuon_hybridSoft(em->muChi2NDF->at(m),
				   em->muInnerD0->at(m),
				   em->muInnerDz->at(m),
				   em->muPixelHits->at(m),
				   em->muIsTracker->at(m),
				   em->muIsGlobal->at(m),
				   em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     

      h_inclMuPt->Fill(muPt_m,w);

    }

    double leadingRecoJetPt = 0.0;
    // RECO JET LOOP
    for(int i = 0; i < em->njet ; i++){

      // JET VARIABLES
		
      JEC.SetJetPT(em->rawpt[i]);
      JEC.SetJetEta(em->jeteta[i]);
      JEC.SetJetPhi(em->jetphi[i]);

      double x = JEC.GetCorrectedPT();  // use manual JEC
      //double x = em->jetpt[i]; // use built-in JEC
      double y = em->jeteta[i]; // recoJetEta
      double z = em->jetphi[i]; // recoJetPhi
      double jetTrkMax_i = em->jetTrkMax[i]; 


      double sigma = 0.663*JER_fxn->Eval(x);
      double mu = 1.0;

      double smear = randomGenerator->Gaus(mu,sigma);
      //cout << "smear = " << smear << endl;
      
      //x = x*smear;
      if(doJetTrkMaxFilter){
	if(!passesJetTrkMaxFilter(jetTrkMax_i,x)) continue;
      }      


      //cout << "rawPt = " << em->rawpt[i] << "  |  jetPt = " << em->jetpt[i] << "  |  corrPt = " << x << endl;
      if(doEtaPhiMask){
	if(etaPhiMask(y,z)) continue;
      }

      //cout << "Event " << evi << ", jet " << i << endl;
      //cout << "~~~~  jetPt = " << em->jetpt[i] << ", corrJetPt = " << x << endl;

      double muPtRel = -1.0;
      double muPt = -1.0;
      double muEta = -1.0;
      double muPhi = -1.0;
      double muJetDr = -1.0;

      bool hasInclRecoMuonTag = false;
		
      // jet kinematic cuts
      if(TMath::Abs(y) > etaMax || x < jetPtCut) continue;

      if(x > leadingRecoJetPt) leadingRecoJetPt = x;
      
      eventHasGoodJet = true;
		        
      int jetPtIndex = getJetPtBin(x);

      //cout << "nMu = " << em->nMu << endl;

      // look for recoMuon match to recoJet		
      for(int m = 0; m < em->nMu; m++){

	double muPt_m = em->muPt->at(m);
	double muEta_m = em->muEta->at(m);
	double muPhi_m = em->muPhi->at(m);
	double muJetDr_m = getDr(muEta_m,muPhi_m,y,z);
	// skip if muon has already been matched to a jet in this event
	if(matchFlagR[m] == 1) continue;
	// muon kinematic cuts
	if(muPt_m < muPtCut || fabs(muEta_m) > trkEtaMax) continue;
	// muon quality cuts
	// ------ tight muon ID -----
	// if(!isQualityMuon_tight(em->muChi2NDF->at(m),
	// 			em->muInnerD0->at(m),
	// 			em->muInnerDz->at(m),
	// 			em->muMuonHits->at(m),
	// 			em->muPixelHits->at(m),
	// 			em->muIsGlobal->at(m),
	// 			em->muIsPF->at(m),
	// 			em->muStations->at(m),
	// 			em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     
	// ------ hybrid-soft muon ID ----
	if(!isQualityMuon_hybridSoft(em->muChi2NDF->at(m),
				    em->muInnerD0->at(m),
				    em->muInnerDz->at(m),
				    em->muPixelHits->at(m),
				    em->muIsTracker->at(m),
				    em->muIsGlobal->at(m),
				    em->muTrkLayers->at(m))) continue; 
			



	if(isWDecayMuon(muPt_m,x)) continue; // skip if "WDecay" muon (has majority of jet pt)
	//if(isWDecayMuon_raw(muPt_m,em->rawpt[i])) continue;
       
	// match to recoJets
	if(muJetDr_m < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel = getPtRel(muPt_m,muEta_m,muPhi_m,x,y,z);
	  muPt = muPt_m;
	  muEta = muEta_m;
	  muPhi = muPhi_m;
	  muJetDr = muJetDr_m;

	}

      }

      // Fill the jet/event histograms
      h_inclRecoJetPt[0]->Fill(x,w);
      h_inclRecoJetPt[CentralityIndex]->Fill(x,w);

      h_inclRecoJetEta[0]->Fill(y,w);
      h_inclRecoJetEta[CentralityIndex]->Fill(y,w);

      h_inclRecoJetPhi[0]->Fill(z,w);
      h_inclRecoJetPhi[CentralityIndex]->Fill(z,w);

      h_inclRecoJetPt_inclRecoJetEta[0]->Fill(x,y,w);
      h_inclRecoJetPt_inclRecoJetEta[CentralityIndex]->Fill(x,y,w);

      h_inclRecoJetPt_inclRecoJetPhi[0]->Fill(x,z,w);
      h_inclRecoJetPt_inclRecoJetPhi[CentralityIndex]->Fill(x,z,w);

      h_inclRecoJetEta_inclRecoJetPhi[0][0]->Fill(y,z,w);
      h_inclRecoJetEta_inclRecoJetPhi[CentralityIndex][0]->Fill(y,z,w);
      if(jetPtIndex > 0){
	h_inclRecoJetEta_inclRecoJetPhi[0][jetPtIndex]->Fill(y,z,w);
	h_inclRecoJetEta_inclRecoJetPhi[CentralityIndex][jetPtIndex]->Fill(y,z,w);
      }
     
      if(hasInclRecoMuonTag){

	eventHasInclRecoMuonTag = true;

	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0][0]->Fill(y,z,w);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[CentralityIndex][0]->Fill(y,z,w);
	if(jetPtIndex > 0){
	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0][jetPtIndex]->Fill(y,z,w);
	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[CentralityIndex][jetPtIndex]->Fill(y,z,w);
	}

	h_inclRecoJetPt_inclRecoMuonTag[0]->Fill(x,w);
	h_inclRecoJetPt_inclRecoMuonTag[CentralityIndex]->Fill(x,w);

	h_inclRecoJetEta_inclRecoMuonTag[0]->Fill(y,w);
	h_inclRecoJetEta_inclRecoMuonTag[CentralityIndex]->Fill(y,w);

	h_inclRecoJetPhi_inclRecoMuonTag[0]->Fill(z,w);
	h_inclRecoJetPhi_inclRecoMuonTag[CentralityIndex]->Fill(z,w);

	h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[0]->Fill(x,y,w);
	h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[CentralityIndex]->Fill(x,y,w);

	h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[0]->Fill(x,z,w);
	h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[CentralityIndex]->Fill(x,z,w);
       
	if(evtTriggerDecision){
	 
	  eventHasInclRecoMuonTagPlusTrigger = true;

	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[0][0]->Fill(y,z,w_trig);
	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[CentralityIndex][0]->Fill(y,z,w_trig);
	  if(jetPtIndex > 0){
	    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[0][jetPtIndex]->Fill(y,z,w_trig);
	    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[CentralityIndex][jetPtIndex]->Fill(y,z,w_trig);
	  }

	  h_inclRecoJetPt_inclRecoMuonTag_triggerOn[0]->Fill(x,w_trig);
	  h_inclRecoJetPt_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(x,w_trig);

	  h_inclRecoJetEta_inclRecoMuonTag_triggerOn[0]->Fill(y,w_trig);
	  h_inclRecoJetEta_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(y,w_trig);

	  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn[0]->Fill(z,w_trig);
	  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(z,w_trig);

	  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[0]->Fill(x,y,w_trig);
	  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(x,y,w_trig);

	  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[0]->Fill(x,z,w_trig);
	  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(x,z,w_trig);

	  h_mupt_jetpt[0]->Fill(muPt,x,w_trig);
	  h_mupt_jetpt[CentralityIndex]->Fill(muPt,x,w_trig);

	  h_muptrel_jetpt[0]->Fill(muPtRel,x,w_trig);
	  h_muptrel_jetpt[CentralityIndex]->Fill(muPtRel,x,w_trig);

	  
	  h_muptrel_inclRecoMuonTag_triggerOn[0][0]->Fill(muPtRel,w_trig);
	  h_mupt_inclRecoMuonTag_triggerOn[0][0]->Fill(muPt,w_trig);
	  h_mueta_inclRecoMuonTag_triggerOn[0][0]->Fill(muEta,w_trig);
	  h_muphi_inclRecoMuonTag_triggerOn[0][0]->Fill(muPhi,w_trig);
	  h_muPtOverJetPt[0][0]->Fill(muPt/x,w_trig);
	  h_muJetDr[0][0]->Fill(muJetDr,w_trig);
	  h_mupt_muptrel[0][0]->Fill(muPt,muPtRel,w_trig);
	  
	  
	 
	  if(jetPtIndex > 0){
	    h_muptrel_inclRecoMuonTag_triggerOn[0][jetPtIndex]->Fill(muPtRel,w_trig);
	    h_muptrel_inclRecoMuonTag_triggerOn[CentralityIndex][0]->Fill(muPtRel,w_trig);
	    h_muptrel_inclRecoMuonTag_triggerOn[CentralityIndex][jetPtIndex]->Fill(muPtRel,w_trig);

	    h_mupt_inclRecoMuonTag_triggerOn[0][jetPtIndex]->Fill(muPt,w_trig);
	    h_mupt_inclRecoMuonTag_triggerOn[CentralityIndex][0]->Fill(muPt,w_trig);
	    h_mupt_inclRecoMuonTag_triggerOn[CentralityIndex][jetPtIndex]->Fill(muPt,w_trig);

	    h_mueta_inclRecoMuonTag_triggerOn[0][jetPtIndex]->Fill(muEta,w_trig);
	    h_mueta_inclRecoMuonTag_triggerOn[CentralityIndex][0]->Fill(muEta,w_trig);
	    h_mueta_inclRecoMuonTag_triggerOn[CentralityIndex][jetPtIndex]->Fill(muEta,w_trig);

	    h_muphi_inclRecoMuonTag_triggerOn[0][jetPtIndex]->Fill(muPhi,w_trig);
	    h_muphi_inclRecoMuonTag_triggerOn[CentralityIndex][0]->Fill(muPhi,w_trig);
	    h_muphi_inclRecoMuonTag_triggerOn[CentralityIndex][jetPtIndex]->Fill(muPhi,w_trig);

	    h_muPtOverJetPt[0][jetPtIndex]->Fill(muPt/x,w_trig);
	    h_muPtOverJetPt[CentralityIndex][0]->Fill(muPt/x,w_trig);
	    h_muPtOverJetPt[CentralityIndex][jetPtIndex]->Fill(muPt/x,w_trig);

	    h_muJetDr[0][jetPtIndex]->Fill(muJetDr,w_trig);
	    h_muJetDr[CentralityIndex][0]->Fill(muJetDr,w_trig);
	    h_muJetDr[CentralityIndex][jetPtIndex]->Fill(muJetDr,w_trig);

	    h_mupt_muptrel[0][jetPtIndex]->Fill(muPt,muPtRel,w_trig);
	    h_mupt_muptrel[CentralityIndex][0]->Fill(muPt,muPtRel,w_trig);
	    h_mupt_muptrel[CentralityIndex][jetPtIndex]->Fill(muPt,muPtRel,w_trig);
	   
	  }
	} 

      }

    }
    // END recoJet LOOP

    h_vz[0]->Fill(em->vz,w);
    h_vz[CentralityIndex]->Fill(em->vz,w);
    
    if(eventHasGoodJet && leadingRecoJetPt > 60){

      h_hiBin->Fill(em->hiBin,w);

      if(eventHasInclRecoMuonTag){

	h_vz_inclRecoMuonTag[0]->Fill(em->vz,w);
	h_vz_inclRecoMuonTag[CentralityIndex]->Fill(em->vz,w);

	h_hiBin_inclRecoMuonTag->Fill(em->hiBin,w);

	if(eventHasInclRecoMuonTagPlusTrigger){

	  h_vz_inclRecoMuonTag_triggerOn[0]->Fill(em->vz,w_trig);
	  h_vz_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(em->vz,w_trig);

	  h_hiBin_inclRecoMuonTag_triggerOn->Fill(em->hiBin,w_trig);
	 
	}
       

      }

    }

  } // end event loop

  h_NEvents->Fill(eventCounter);

 
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");
  
  h_NEvents->Write();
  h_hiBin->Write();
  h_hiBin_inclRecoMuonTag->Write();
  h_hiBin_inclRecoMuonTag_triggerOn->Write();
  h_inclMuPt->Write();

  for(int i = 0; i < NCentralityIndices; i++){

    h_vz[i]->Write();
    h_vz_inclRecoMuonTag[i]->Write();
    h_vz_inclRecoMuonTag_triggerOn[i]->Write();
   
    h_inclRecoJetPt[i]->Write();
    h_inclRecoJetEta[i]->Write();
    h_inclRecoJetPhi[i]->Write();
    h_inclRecoJetPt_inclRecoJetEta[i]->Write();
    h_inclRecoJetPt_inclRecoJetPhi[i]->Write();
   
    h_inclRecoJetPt_inclRecoMuonTag[i]->Write();
    h_inclRecoJetEta_inclRecoMuonTag[i]->Write();
    h_inclRecoJetPhi_inclRecoMuonTag[i]->Write();
    h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[i]->Write();
    h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[i]->Write();
   
    h_inclRecoJetPt_inclRecoMuonTag_triggerOn[i]->Write();
    h_inclRecoJetEta_inclRecoMuonTag_triggerOn[i]->Write();
    h_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i]->Write();
    h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[i]->Write();
    h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i]->Write();

    h_mupt_jetpt[i]->Write();
    h_muptrel_jetpt[i]->Write();

    for(int j = 0; j < NJetPtIndices; j++){

      h_inclRecoJetEta_inclRecoJetPhi[i][j]->Write();
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j]->Write();
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j]->Write();

      h_muptrel_inclRecoMuonTag_triggerOn[i][j]->Write();
      h_mupt_inclRecoMuonTag_triggerOn[i][j]->Write();
      h_mueta_inclRecoMuonTag_triggerOn[i][j]->Write();
      h_muphi_inclRecoMuonTag_triggerOn[i][j]->Write();
      h_muPtOverJetPt[i][j]->Write();
      h_muJetDr[i][j]->Write();
      h_mupt_muptrel[i][j]->Write();
     
    }
  }


  wf->Close();
  return;
  // END WRITE

}
