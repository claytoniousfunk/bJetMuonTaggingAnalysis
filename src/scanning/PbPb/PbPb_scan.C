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
#include "../../../headers/AnalysisSetupV2p3.h"
// eta-phi mask function
#include "../../../headers/functions/etaPhiMask.h"
// getDr function
#include "../../../headers/functions/getDr.h"
// getJetPtBin function
#include "../../../headers/functions/getJetPtBin.h"
// getCentBin function
//#include "../../../headers/functions/getCentBin_v2.h"
#include "../../../headers/functions/getCentBin.h"
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
#include "../../../headers/functions/jet_filter/passesJetTrkMaxFilter.h"
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
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn[NCentralityIndices];
TH2D *h_muJetDr_recoJetPt[NCentralityIndices];
// ~~~~~~~~~ analysis histograms ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D *h_muPtOverJetPt[NCentralityIndices][NJetPtIndices];
TH2D *h_mupt_jetpt[NCentralityIndices];
TH2D *h_mupt_muptrel[NCentralityIndices][NJetPtIndices];
TH2D *h_muptrel_jetpt[NCentralityIndices];
TH1D *h_NJetPerEvent[NCentralityIndices];
TH1D *h_NMuTaggedJetPerEvent[NCentralityIndices];
TH2D *h_muptrel_hiBin[NJetPtIndices];

///////////////////////  start the program
void PbPb_scan(int group = 1){

  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_PbPb_HardProbes_2/PbPb_DiJet_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PbPb_HardProbes_scan_jet60_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates/PbPb_HardProbes_scan_output_%i.root",group);

  TString input = Form("/eos/user/c/cbennett/skims/output_skims_PbPb_HIMinimumBias0/PbPb_MinBias_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PbPb_MinBias_scan_mu12_tight_pTmu-14_hiHFcut_3CentBins_projectableTemplates_2025-06-25/PbPb_MinBias_scan_output_%i.root",group);

  // TString input = Form("/eos/user/c/cbennett/skims/output_PbPb_SingleMuon_withWTA/PbPb_SingleMuon_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PbPb_SingleMuon_scan_mu12_tight_pTmu-14_hiHFcut_3CentBins_projectableTemplates_2025-06-25/PbPb_SingleMuon_scan_output_%i.root",group);
  
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

  for(int j = 0; j < NJetPtIndices; j++){
    if(j==0){
      h_muptrel_hiBin[j] = new TH2D(Form("h_muptrel_hiBin_J%i",j),Form("muptrel vs hiBin, %3.0f < pTjet < %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NhiBinBins,hiBinMin,hiBinMax) ;
    }
    else{
      h_muptrel_hiBin[j] = new TH2D(Form("h_muptrel_hiBin_J%i",j),Form("muptrel vs hiBin, %3.0f < pTjet < %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,NhiBinBins,hiBinMin,hiBinMax) ;
    }
    h_muptrel_hiBin[j]->Sumw2();
  }
  
  // for loop through the centrality indices
  for(int i = 0; i < NCentralityIndices; i++){
    // the inclusive centrality histogram	
    if(i==0){
      // ---------------------- event histograms --------------------------------
      h_vz[i] = new TH1D(Form("h_vz_C%i",i),Form("vz, events with inclRecoJet, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag[i] = new TH1D(Form("h_vz_inclRecoMuonTag_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_vz_inclRecoMuonTag_triggerOn_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag-triggerOn, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NVzBins,vzMin,vzMax);
      h_NJetPerEvent[i] = new TH1D(Form("h_NJetPerEvent_C%i",i),Form("Number of incl. jets per event, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),100,0,100);
      h_NMuTaggedJetPerEvent[i] = new TH1D(Form("h_NMuTaggedJetPerEvent_C%i",i),Form("Number of #it{#mu}-tagged jets per event, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),100,0,100);
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
      // muon-based 2d histograms
      h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C%i",i),Form("muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, %i < hiBin < %i",centEdges[0], centEdges[NCentralityIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
      h_mupt_recoJetPt_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_C%i",i),Form("muon #it{p}_{T} vs jet #it{p}_{T}, %i < hiBin < %i",centEdges[0], centEdges[NCentralityIndices-1]),NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
      h_mueta_recoJetPt_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_C%i",i),Form("muon #it{#eta} vs jet #it{p}_{T}, %i < hiBin < %i",centEdges[0], centEdges[NCentralityIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
      h_muphi_recoJetPt_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_C%i",i),Form("muon #it{#phi} vs jet #it{p}_{T}, %i < hiBin < %i",centEdges[0], centEdges[NCentralityIndices-1]),NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
      h_muJetDr_recoJetPt[i] = new TH2D(Form("h_muJetDr_recoJetPt_C%i",i),Form("#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, %i < hiBin < %i",centEdges[0], centEdges[NCentralityIndices-1]),NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);
    }
    else{
      // ---------------------- event histograms --------------------------------
      h_vz[i] = new TH1D(Form("h_vz_C%i",i),Form("vz, events with inclRecoJet, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag[i] = new TH1D(Form("h_vz_inclRecoMuonTag_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      h_vz_inclRecoMuonTag_triggerOn[i] = new TH1D(Form("h_vz_inclRecoMuonTag_triggerOn_C%i",i),Form("vz, events with inclRecoJet-inclRecoMuonTag-triggerOn, hiBin %i - %i",centEdges[i-1],centEdges[i]),NVzBins,vzMin,vzMax);
      h_NJetPerEvent[i] = new TH1D(Form("h_NJetPerEvent_C%i",i),Form("Number of incl. jets per event, hiBin %i - %i",centEdges[i-1],centEdges[i]),100,0,100);
      h_NMuTaggedJetPerEvent[i] = new TH1D(Form("h_NMuTaggedJetPerEvent_C%i",i),Form("Number of #it{#mu}-tagged jets per event, hiBin %i - %i",centEdges[i-1],centEdges[i]),100,0,100);
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
      // muon-based 2d histograms
      h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C%i",i),Form("muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, %i < hiBin < %i",centEdges[i-1], centEdges[i]),NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
      h_mupt_recoJetPt_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_C%i",i),Form("muon #it{p}_{T} vs jet #it{p}_{T}, %i < hiBin < %i",centEdges[i-1], centEdges[i]),NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
      h_mueta_recoJetPt_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_C%i",i),Form("muon #it{#eta} vs jet #it{p}_{T}, %i < hiBin < %i",centEdges[i-1], centEdges[i]),NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
      h_muphi_recoJetPt_inclRecoMuonTag_triggerOn[i] = new TH2D(Form("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_C%i",i),Form("muon #it{#phi} vs jet #it{p}_{T}, %i < hiBin < %i",centEdges[i-1], centEdges[i]),NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
      h_muJetDr_recoJetPt[i] = new TH2D(Form("h_muJetDr_recoJetPt_C%i",i),Form("#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, %i < hiBin < %i",centEdges[i-1], centEdges[i]),NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);
    }
    // sumw2 commands
    h_NJetPerEvent[i]->Sumw2();
    h_NMuTaggedJetPerEvent[i]->Sumw2();
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
    h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_mupt_recoJetPt_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_mueta_recoJetPt_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_muphi_recoJetPt_inclRecoMuonTag_triggerOn[i]->Sumw2();
    h_muJetDr_recoJetPt[i]->Sumw2();
    
    // loop through jet pt indices
    for(int j = 0; j < NJetPtIndices; j++){
      if(i==0 && j==0){
	h_muPtOverJetPt[i][j] = new TH1D(Form("h_muPtOverJetPt_C%iJ%i",i,j),Form("p_{T}^{#mu} / p_{T}^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs. muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      }
      else if(i==0){	
	h_muPtOverJetPt[i][j] = new TH1D(Form("h_muPtOverJetPt_C%iJ%i",i,j),Form("p_{T}^{#mu} / p_{T}^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs. muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      }
      else if(j==0){
	h_muPtOverJetPt[i][j] = new TH1D(Form("h_muPtOverJetPt_C%iJ%i",i,j),Form("p_{T}^{#mu} / p_{T}^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs. muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      }
      else{
	h_muPtOverJetPt[i][j] = new TH1D(Form("h_muPtOverJetPt_C%iJ%i",i,j),Form("p_{T}^{#mu} / p_{T}^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
	h_mupt_muptrel[i][j] = new TH2D(Form("h_mupt_muptrel_C%iJ%i",i,j),Form("muPtRel vs. muPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f",centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
	h_inclRecoJetEta_inclRecoJetPhi[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_C%iJ%i",i,j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      }

      h_muPtOverJetPt[i][j]->Sumw2();
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
    // hiHF cut
    if(em->hiHF > 6000) continue;

    // apply jet-trigger if activated in config
    if(applyJet60Trigger){
      if(em->HLT_HICsAK4PFJet60Eta1p5_v1 == 0) continue;
    }
    if(applyJet80Trigger){
      if(em->HLT_HICsAK4PFJet80Eta1p5_v1 == 0) continue;
    }

    // In data, event weight = 1
    double w = 1.0;

   
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};

    int matchFlagR[10] = {0,0,0,0,0,0,0,0,0,0};
	
    int CentralityIndex = getCentBin(em->hiBin);
    if(CentralityIndex < 0) continue;

    bool evtTriggerDecision = false;

    int triggerDecision_mu5 = em->HLT_HIL3Mu5_NHitQ10_v1;
    int triggerDecision_mu5_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl;

    int triggerDecision_mu7 = em->HLT_HIL3Mu7_NHitQ10_v1;
    int triggerDecision_mu7_Prescl = em->HLT_HIL3Mu7_NHitQ10_v1_Prescl;

    int triggerDecision_mu12 = em->HLT_HIL3Mu12_v1;
    int triggerDecision_mu12_Prescl = em->HLT_HIL3Mu12_v1_Prescl;


    // ******************************************
    // -------- mu5 configuration ---------------
    // if(triggerIsOn(triggerDecision_mu5,triggerDecision_mu5_Prescl) &&
    //    !triggerIsOn(triggerDecision_mu7,triggerDecision_mu7_Prescl) &&
    //    !triggerIsOn(triggerDecision_mu12,triggerDecision_mu12_Prescl)){
    //   evtTriggerDecision = true;
    //   eventCounter++;
    // }
    // ******************************************
    
    // ******************************************
    // -------- mu7 configuration ---------------
    // if(triggerIsOn(triggerDecision_mu7,triggerDecision_mu7_Prescl)){
    //  evtTriggerDecision = true;
    //  eventCounter++;
    // }
    // ******************************************
    
    // ******************************************
    // -------- mu12 configuration ---------------
    if(triggerIsOn(triggerDecision_mu12,triggerDecision_mu12_Prescl)){
      evtTriggerDecision = true;
      eventCounter++;
    }
    // ******************************************



    

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
   
    
    
   
    bool eventHasGoodJet = false;
    bool eventHasInclRecoMuonTag = false;
    bool eventHasInclRecoMuonTagPlusTrigger = false;
    bool eventHasMatchedRecoMuonTag = false;
    bool eventHasMatchedRecoMuonTagPlusTrigger = false;
    int inclJetCounter = 0;
    int muTaggedJetCounter = 0;

    
    // RECO MUON LOOP
    for(int m = 0; m < em->nMu; m++){

      double muPt_m = em->muPt->at(m);
      double muEta_m = em->muEta->at(m);
      double muPhi_m = em->muPhi->at(m);

      //cout << "(muPt, muEta, muPhi) = (" << muPt_m << ", " << muEta_m << ", " << muPhi_m << ")" << endl;

      // skip if muon has already been matched to a jet in this event
      // muon kinematic cuts
      if(muPt_m < muPtCut || muPt_m > muPtMaxCut || fabs(muEta_m) > 2.0) continue;
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

      // if(!isQualityMuon_hybridSoft(em->muChi2NDF->at(m),
      // 				   em->muInnerD0->at(m),
      // 				   em->muInnerDz->at(m),
      // 				   em->muPixelHits->at(m),
      // 				   em->muIsTracker->at(m),
      // 				   em->muIsGlobal->at(m),
      // 				   em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     

      h_inclMuPt->Fill(muPt_m,w);

    }

    double leadingRecoJetPt = 0.0;
    // RECO JET LOOP
    for(int i = 0; i < em->njet ; i++){

      if(onlyOneMuonTaggedJetPerEvent){
	if(eventHasInclRecoMuonTag) continue;
      }
      
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
	if(muPt_m < muPtCut || muPt_m > muPtMaxCut || fabs(muEta_m) > 2.0) continue;
	// muon quality cuts
	// ------ tight muon ID -----
	if(!isQualityMuon_tight(em->muChi2NDF->at(m),
				em->muInnerD0->at(m),
				em->muInnerDz->at(m),
				em->muMuonHits->at(m),
				em->muPixelHits->at(m),
				em->muIsGlobal->at(m),
				em->muIsPF->at(m),
				em->muStations->at(m),
				em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     
	// ------ hybrid-soft muon ID ----
	// if(!isQualityMuon_hybridSoft(em->muChi2NDF->at(m),
	// 			    em->muInnerD0->at(m),
	// 			    em->muInnerDz->at(m),
	// 			    em->muPixelHits->at(m),
	// 			    em->muIsTracker->at(m),
	// 			    em->muIsGlobal->at(m),
	// 			    em->muTrkLayers->at(m))) continue; 
			



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

      inclJetCounter++;
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
	muTaggedJetCounter++;
	
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

	  
	  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn[0]->Fill(muPtRel,x,w_trig);
	  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn[0]->Fill(muPt,x,w_trig);
	  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn[0]->Fill(muEta,x,w_trig);
	  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn[0]->Fill(muPhi,x,w_trig);
	  h_muJetDr_recoJetPt[0]->Fill(muJetDr,x,w_trig);

	  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(muPtRel,x,w_trig);
	  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(muPt,x,w_trig);
	  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(muEta,x,w_trig);
	  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(muPhi,x,w_trig);
	  h_muJetDr_recoJetPt[CentralityIndex]->Fill(muJetDr,x,w_trig);

	  h_muPtOverJetPt[0][0]->Fill(muPt/x,w_trig);
	  h_mupt_muptrel[0][0]->Fill(muPt,muPtRel,w_trig);
	 
	  if(jetPtIndex > 0){
	    
	    h_muPtOverJetPt[0][jetPtIndex]->Fill(muPt/x,w_trig);
	    h_muPtOverJetPt[CentralityIndex][0]->Fill(muPt/x,w_trig);
	    h_muPtOverJetPt[CentralityIndex][jetPtIndex]->Fill(muPt/x,w_trig);

	    h_mupt_muptrel[0][jetPtIndex]->Fill(muPt,muPtRel,w_trig);
	    h_mupt_muptrel[CentralityIndex][0]->Fill(muPt,muPtRel,w_trig);
	    h_mupt_muptrel[CentralityIndex][jetPtIndex]->Fill(muPt,muPtRel,w_trig);

	    h_muptrel_hiBin[0]->Fill(muPtRel,em->hiBin,w_trig);
	    h_muptrel_hiBin[jetPtIndex]->Fill(muPtRel,em->hiBin,w_trig);
	   
	  }
	} 

      }

    }
    // END recoJet LOOP

    h_NJetPerEvent[0]->Fill(inclJetCounter);
    h_NJetPerEvent[CentralityIndex]->Fill(inclJetCounter);

    h_NMuTaggedJetPerEvent[0]->Fill(muTaggedJetCounter);
    h_NMuTaggedJetPerEvent[CentralityIndex]->Fill(muTaggedJetCounter);

    h_vz[0]->Fill(em->vz,w);
    h_vz[CentralityIndex]->Fill(em->vz,w);
    
    if(eventHasGoodJet && leadingRecoJetPt > 80){

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

    h_NJetPerEvent[i]->Write();
    h_NMuTaggedJetPerEvent[i]->Write();
    
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

    h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn[i]->Write();
    h_mupt_recoJetPt_inclRecoMuonTag_triggerOn[i]->Write();
    h_mueta_recoJetPt_inclRecoMuonTag_triggerOn[i]->Write();
    h_muphi_recoJetPt_inclRecoMuonTag_triggerOn[i]->Write();
    h_muJetDr_recoJetPt[i]->Write();
    
    for(int j = 0; j < NJetPtIndices; j++){

      h_inclRecoJetEta_inclRecoJetPhi[i][j]->Write();
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[i][j]->Write();
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[i][j]->Write();
      h_muPtOverJetPt[i][j]->Write();
      h_mupt_muptrel[i][j]->Write();
     
    }
  }

  for(int j = 0; j < NJetPtIndices; j++){
    h_muptrel_hiBin[j]->Write();
  }

  wf->Close();
  return;
  // END WRITE

}
