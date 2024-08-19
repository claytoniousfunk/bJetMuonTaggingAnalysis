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
#include "../../../headers/AnalysisSetupV2p2.h"
// vz-fit parameters
//#include "../../../headers/fitParameters/vzFitParams_PH_mu5.h"
//#include "../../../headers/fitParameters/vzFitParams_PH_mu7.h"
#include "../../../headers/fitParameters/vzFitParams_PH_mu12.h"
// hiBin-fit parameters
//#include "../../../headers/fitParameters/hiBinFitParams_mu5.h"
//#include "../../../headers/fitParameters/hiBinFitParams_mu7.h"
#include "../../../headers/fitParameters/hiBinFitParams_mu12.h"
// jetPt-fit parameters
//#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu5.h"
//#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu7.h"
#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu12.h"


TF1 *fitFxn_hiBin, *fitFxn_vz, *fitFxn_jetPt;
// vz-fit function
#include "../../../headers/fitFunctions/fitFxn_vz_PH.h"
// #include "../../../headers/fitFunctions/fitFxn_vz_PH_mu7.h"
// #include "../../../headers/fitFunctions/fitFxn_vz_PH_mu12.h"
// hiBin-fit function
#include "../../../headers/fitFunctions/fitFxn_hiBin.h"
// #include "../../../headers/fitFunctions/fitFxn_hiBin_mu7.h"
// #include "../../../headers/fitFunctions/fitFxn_hiBin_mu12.h"
// jetPt-fit function
#include "../../../headers/fitFunctions/fitFxn_jetPt.h"

// eta-phi mask function
#include "../../../headers/functions/etaPhiMask.h"
// getDr function
#include "../../../headers/functions/getDr.h"
// getJetPtBin function
#include "../../../headers/functions/getJetPtBin.h"
// getCentBin function
#include "../../../headers/functions/getCentBin_v2.h"
//#include "../../../headers/functions/getCentBin.h"
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
#include "../../../headers/config/config_PYTHIAHYDJET.h"
// read config
#include "../../../headers/config/readConfig.h"
// remove HYDJET jets function
#include "../../../headers/functions/jet_filter/remove_HYDJET_jet.h"


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
TH1D *h_leadingGenJetPt[NCentralityIndices];
TH1D *h_leadingGenJetPt_xJets_greaterThanPthat[NCentralityIndices];
TH2D *h_delta_muptrel_WTA_nom_flavor;
TH2D *h_matchedPartonFlavor_bHadronNumber;



void PYTHIAHYDJET_scan(int group = 1){

  
  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_PYTHIAHYDJET_DiJet_withGS_withWTA_2/PYTHIAHYDJET_DiJet_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_newJetBins_JEUShiftDown/PYTHIAHYDJET_scan_output_%i.root",group);

  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_PYTHIAHYDJET_MuJet_withGS_withWTA_2/PYTHIAHYDJET_MuJet_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIAHYDJET_MuJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_newJetBins_JERsmear/PYTHIAHYDJET_scan_output_%i.root",group);

  TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_PYTHIAHYDJET_BJet_withGS_withWTA_2/PYTHIAHYDJET_BJet_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIAHYDJET_BJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_newJetBins_JEUShiftUp/PYTHIAHYDJET_scan_output_%i.root",group);

  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_skim_PYTHIAHYDJET_DiJet_additionalMC_fullStats/PYTHIAHYDJET_DiJet_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_additionalMC_fullStats/PYTHIAHYDJET_scan_output_%i.root",group);

  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_skim_PYTHIAHYDJET_DiJet_additionalMC_2024-08-05/PYTHIAHYDJET_DiJet_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_fineCent/PYTHIAHYDJET_scan_output_%i.root",group);

  
  
  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_L2Relative_AK4PF.txt"); // LXPLUS

  JetCorrector JEC(Files);

  JetUncertainty JEU("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_Uncertainty_AK4PF.txt");

  
  // printIntroduction_PYTHIAHYDJET_scan_V3p7();
  readConfig();
  
  // define histograms
  // >> NEvents
  h_NEvents = new TH1D("h_NEvents","Number of events",1000,0,1000);
  h_delta_muptrel_WTA_nom_flavor = new TH2D("h_delta_muptrel_WTA_nom_flavor","h_delta_muptrel_WTA_nom_flavor",1000,-1,1,27,-5,22);
  // >> hiBin
  h_hiBin = new TH1D("h_hiBin","hiBin, events with inclRecoJet",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_inclGenMuonTag = new TH1D("h_hiBin_inclGenMuonTag","hiBin, events with inclRecoJet-inclGenMuonTag",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_inclRecoMuonTag = new TH1D("h_hiBin_inclRecoMuonTag","hiBin, events with inclRecoJet-inclRecoMuonTag",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_inclRecoMuonTag_triggerOn = new TH1D("h_hiBin_inclRecoMuonTag_triggerOn","hiBin, events with inclRecoJet-inclRecoMuonTag-triggerOn",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_matchedRecoMuonTag = new TH1D("h_hiBin_matchedRecoMuonTag","hiBin, events with inclRecoJet-matchedRecoMuonTag",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_matchedRecoMuonTag_triggerOn = new TH1D("h_hiBin_matchedRecoMuonTag_triggerOn","hiBin, events with inclRecoJet-matchedRecoMuonTag-triggerOn",NhiBinBins,hiBinMin,hiBinMax);
  h_weight_pthat_xJets_C1J3 = new TH2D("h_weight_pthat_xJets_C1J3","pthat vs w_{pthat}, xJets, 80 < p_{T} < 120 GeV, cent. 0-30%",2000,0,0.02,500,0,500);
  h_weight_pthat_bJets_C1J3 = new TH2D("h_weight_pthat_bJets_C1J3","pthat vs w_{pthat}, bJets, 80 < p_{T} < 120 GeV, cent. 0-30%",2000,0,0.02,500,0,500);
  h_matchedPartonFlavor_bHadronNumber = new TH2D("h_matchedPartonFlavor_bHadronNumber","matchedPartonFlavor vs bHadronNumber",27,-5,22,5,0,5);

  h_delta_muptrel_WTA_nom_flavor->Sumw2();
  h_hiBin->Sumw2();
  h_hiBin_inclGenMuonTag->Sumw2();
  h_hiBin_inclRecoMuonTag->Sumw2();
  h_hiBin_inclRecoMuonTag_triggerOn->Sumw2();
  h_hiBin_matchedRecoMuonTag->Sumw2();
  h_hiBin_matchedRecoMuonTag_triggerOn->Sumw2();
  h_weight_pthat_xJets_C1J3->Sumw2();
  h_weight_pthat_bJets_C1J3->Sumw2();
  h_matchedPartonFlavor_bHadronNumber->Sumw2();

  
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
      h_leadingGenJetPt[i] = new TH1D(Form("h_leadingGenJetPt_C%i",i),Form("leadingGenJetPt, hiBin %i - %i",centEdges[0], centEdges[NCentralityIndices-1]),500,0,500);
      h_leadingGenJetPt_xJets_greaterThanPthat[i] = new TH1D(Form("h_leadingGenJetPt_xJets_greaterThanPthat_C%i",i),Form("leadingGenJetPt, xJets, pT > pThat, hiBin %i - %i",centEdges[0], centEdges[NCentralityIndices-1]),500,0,500);
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
      h_leadingGenJetPt[i] = new TH1D(Form("h_leadingGenJetPt_C%i",i),Form("leadingGenJetPt, hiBin %i - %i",centEdges[i-1], centEdges[i]),500,0,500);
      h_leadingGenJetPt_xJets_greaterThanPthat[i] = new TH1D(Form("h_leadingGenJetPt_xJets_greaterThanPthat_C%i",i),Form("leadingGenJetPt, xJets, pT > pThat, hiBin %i - %i",centEdges[i-1], centEdges[i]),500,0,500);
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

    h_leadingGenJetPt[i]->Sumw2();
    h_leadingGenJetPt_xJets_greaterThanPthat[i]->Sumw2();

    
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
  em->regEventFilter(NeventFilters, eventFilters);

  TRandom *randomGenerator = new TRandom2();

  // jet-energy resolution fit function
  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,300);
  JER_fxn->SetParameter(0,-1.91758e-05);
  JER_fxn->SetParameter(1,-1.79691e+00);
  JER_fxn->SetParameter(2,1.09880e+01);

  // define vz , hiBin, & jetPt reweighting functions
  loadFitFxn_vz();
  loadFitFxn_hiBin();
  loadFitFxn_jetPt();

  // xDump reweight
  //TFile *f_xDump = TFile::Open("../xDumpReweight.root");
  //TH1D *h_xDump;
  //f_xDump->GetObject("r",h_xDump);
 
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
    // event filters
    if(em->checkEventFilter()) continue;
    // hiHF cut
    if(em->hiHF > 6000) continue;
    

    // calculate event weight
    
    double w_reweight_hiBin = 1.0;
    if(doHiBinReweight){
      w_reweight_hiBin = fitFxn_hiBin->Eval(em->hiBin-10);
    }

    double w_reweight_vz = 1.0;
    if(doVzReweight){
      w_reweight_vz = fitFxn_vz->Eval(em->vz);
    }
    

    double w_pthat = em->weight;
    
    double w = w_pthat * w_reweight_hiBin * w_reweight_vz;

    
    if(w <= 0.0) continue;
   
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};

    int matchFlagR[10] = {0,0,0,0,0,0,0,0,0,0};
	
    int CentralityIndex = getCentBin(em->hiBin-10);
    if(CentralityIndex < 0) continue;

    bool evtTriggerDecision = false;

    // int triggerDecision = em->HLT_HIL3Mu5_NHitQ10_v1;
    // int triggerDecision_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl;

    // int triggerDecision = em->HLT_HIL3Mu7_NHitQ10_v1;
    // int triggerDecision_Prescl = em->HLT_HIL3Mu7_NHitQ10_v1_Prescl;

    int triggerDecision = em->HLT_HIL3Mu12_v1;
    int triggerDecision_Prescl = em->HLT_HIL3Mu12_v1_Prescl;

    if(triggerIsOn(triggerDecision,triggerDecision_Prescl)) {
      evtTriggerDecision = true;
      eventCounter++;
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
    if(doGenJetPthatFilter){
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
    }
    

    // quick recoJet loop to get leadingRecoJetPt
    double leadingRecoJetPt_i = 0.0;
    double leadingRecoJetEta_i = 0.0;
    double leadingRecoJetPhi_i = 0.0;
    int leadingRecoJetFlavor_i = -100;


    if(doLeadingXjetDumpFilter){
      for(int j = 0; j < em->njet ; j++){

	JEC.SetJetPT(em->rawpt[j]);
	JEC.SetJetEta(em->jeteta[j]);
	JEC.SetJetPhi(em->jetphi[j]);
      
	double testJetPt_j = JEC.GetCorrectedPT();
	double testJetEta_j = em->jeteta[j];
	double testJetPhi_j = em->jetphi[j];
	int testJetFlavor_j = em->matchedPartonFlavor[j];

	if(fabs(testJetEta_j) > etaMax) continue;
      
	if(testJetPt_j > leadingRecoJetPt_i){
	  leadingRecoJetPt_i = testJetPt_j;
	  leadingRecoJetFlavor_i = testJetFlavor_j;
	}

      }

    
      bool leadingXjetDump = false;
      double xDumpPthatScalar = 1.0;
      // dump event if flavor==x && pT > pThat
      if(leadingRecoJetFlavor_i == 0 && leadingRecoJetPt_i > xDumpPthatScalar * em->pthat){
	leadingXjetDump = true;
	continue; // dump event
      }
    }

    // reweight if we didn't dump the event.
    

    //double xDump_reweight_subFactor = h_xDump->GetBinContent(h_xDump->FindBin(leadingGenJetPt_i));
    double xDump_reweight_subFactor = 0.0; // ignore xDump reweight for now
    double xDump_reweight_factor = 1. / (1. - xDump_reweight_subFactor);

    //cout << "xDump_reweight_factor = " << xDump_reweight_factor << endl;

    if(doXdumpReweight){
      w = w * xDump_reweight_factor ;
    }
    
    if(leadingRecoJetPt_i != 0.0){
      h_leadingGenJetPt[0]->Fill(leadingGenJetPt_i,1.);
      h_leadingGenJetPt[CentralityIndex]->Fill(leadingGenJetPt_i,1.);
      if(leadingRecoJetFlavor_i == 0 && leadingRecoJetPt_i > em->pthat){
	h_leadingGenJetPt_xJets_greaterThanPthat[0]->Fill(leadingGenJetPt_i,1.);
	h_leadingGenJetPt_xJets_greaterThanPthat[CentralityIndex]->Fill(leadingGenJetPt_i,1.);
      }
    }





    
    
   
    // RECO JET LOOP
    for(int i = 0; i < em->njet ; i++){

      // JET VARIABLES
				
      JEC.SetJetPT(em->rawpt[i]);
      JEC.SetJetEta(em->jeteta[i]);
      JEC.SetJetPhi(em->jetphi[i]);

      double recoJetPt_i = JEC.GetCorrectedPT();  // recoJetPt
      double recoJetEta_i = em->jeteta[i]; // recoJetEta
      double recoJetPhi_i = em->jetphi[i]; // recoJetPhi
      // double y = em->jet_wta_eta[i]; // recoJetEta with WTA axis
      // double z = em->jet_wta_phi[i]; // recoJetPhi with WTA axis
      double jetTrkMax_i = em->jetTrkMax[i];

      // cout << endl;
      // cout << "em->jet_wta_eta[i] = " << em->jet_wta_eta[i] << endl;
      // cout << "em->jeteta[i] = " << em->jeteta[i] << endl;
      // cout << endl;
      
      JEU.SetJetPT(recoJetPt_i);
      JEU.SetJetEta(recoJetEta_i);
      JEU.SetJetPhi(recoJetPhi_i);

      double correctedPt_down = 1.0;
      double correctedPt_up = 1.0;

      if(apply_JEU_shift_up){
	correctedPt_up = recoJetPt_i * (1 + JEU.GetUncertainty().second);
	recoJetPt_i = correctedPt_up;
      }
      else if(apply_JEU_shift_down){
	correctedPt_down = recoJetPt_i * (1 - JEU.GetUncertainty().first);
	recoJetPt_i = correctedPt_down;
      }

      double mu = 1.0;
      double sigma = 0.2;
      double smear = 0.0;

      if(apply_JER_smear){
	sigma = 0.663*JER_fxn->Eval(recoJetPt_i); // apply a 20% smear
	smear = randomGenerator->Gaus(mu,sigma);
	recoJetPt_i = recoJetPt_i * smear;
      }

      if(doJetTrkMaxFilter){
	if(!passesJetTrkMaxFilter(jetTrkMax_i,recoJetPt_i)) continue;
      }

      if(doEtaPhiMask){
	if(etaPhiMask(recoJetEta_i,recoJetPhi_i)) continue;
      }

      if(doRemoveHYDJETjet){
	if(remove_HYDJET_jet(em->pthat, recoJetPt_i)) continue;
      }

      // in-jet muon variables
      double muPtRel_i = -1.0;
      double muPt_i = -1.0;
      double muEta_i = -1.0;
      double muPhi_i = -1.0;
		
      int genMuIndex = -1;
      bool hasInclGenMuonTag = false;
      bool hasMatchedGenMuonTag = false;

      bool hasInclRecoMuonTag = false;
      bool hasMatchedRecoMuonTag = false;
		
      bool hasGenJetMatch = false;
		     		
      int matchedPartonFlavor = em->matchedPartonFlavor[i];
      int refPartonFlavorForB = em->refparton_flavorForB[i];
      int hadronFlavorInt = em->matchedHadronFlavor[i];
      int bHadronNumber = em->bHadronNumber[i];

      int jetFlavorInt = matchedPartonFlavor;

      if(fabs(jetFlavorInt) == 5 && bHadronNumber == 2) jetFlavorInt = 17; // 17 = bJet from gluon-splitting 
		
      // jet kinematic cuts
      if(TMath::Abs(recoJetEta_i) > etaMax || recoJetPt_i < jetPtCut) continue;
     
      if(recoJetPt_i > 60) eventHasGoodJet = true;
		        
      int jetPtIndex = getJetPtBin(recoJetPt_i);

      if(jetPtIndex < 0) continue;
      
      // fill genJetPt vs pthat
      h_recoJetPt_pthat[0]->Fill(recoJetPt_i,em->pthat,w);
      h_recoJetPt_pthat[CentralityIndex]->Fill(recoJetPt_i,em->pthat,w);

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


	if(recoJetPt_i < 50) continue;	

	double genJetPt_j = em->genjetpt[j];  // genJetPt
	double genJetEta_j = em->genjeteta[j]; // genJetEta
	double genJetPhi_j = em->genjetphi[j]; // genJetPhi

	double dR_j = getDr(genJetEta_j,genJetPhi_j,recoJetEta_i,recoJetPhi_i);
	double dPt_j = recoJetPt_i/genJetPt_j;
			
	if(dR_j < dR_recoGen_min){
				
	  hasGenJetMatch = true;		
	  dR_recoGen_min = dR_j;
	  dPt_recoGen_min = dPt_j;

	}	

      }

      // if(jetFlavorInt == 0 && dR_recoGen_min > 0.5 && x > 100.){
      // 	cout << "EVENT #" << evi << ", xJet, dR_min(Reco,Gen) =" << dR_recoGen_min << endl;
      // 	cout << "--- Reco Jets ---" << evi << endl;
      // 	for(int k = 0; k < em->njet; k++){
      // 	  cout << "(pt, eta, phi, flavor) = (" << em->jetpt[k] << ", " << em->jeteta[k] << ", " << em->jetphi[k] << ", " << em->matchedPartonFlavor[k] << ")" << endl;
      // 	}
      // 	cout << "--- Gen Jets ---" << evi << endl;
      // 	for(int k = 0; k < em->ngj; k++){
      // 	  cout << "(pt, eta, phi, flavor) = (" << em->genjetpt[k] << ", " << em->genjeteta[k] << ", " << em->genjetphi[k] << ", ?)" << endl;
      // 	}
      // }

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
	for(int j = 0; j < em->gpptp->size(); j++){

                        
	  bool isMatchedGenMuon = false;

	  if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

	  genMuIndex++;

	  if(matchFlag[genMuIndex] == 1) continue; // skip if muon has been matched to a jet already

	  if(isWDecayMuon(em->gpptp->at(j),recoJetPt_i)) continue; // skip if "WDecay" muon (has majority of jet pt)

	  double genMuonPt_j = em->gpptp->at(j);
	  double genMuonPt_matched_j = -1.0;
	  double genMuonEta_j = em->gpetap->at(j);
	  double genMuonEta_matched_j = -1.0;
	  double genMuonPhi_j = em->gpphip->at(j);
	  double genMuonPhi_matched_j = -1.0;

	  if(genMuonPt_j < muPtCut || genMuonPt_j > muPtMaxCut || fabs(genMuonEta_j) > 2.0) continue;                        

	  // look for recoMuon match to genMuon
	  for(int l = 0; l < em->nMu; l++){


	    double recoMuonPt_l = em->muPt->at(l);
	    double recoMuonEta_l = em->muEta->at(l);
	    double recoMuonPhi_l = em->muPhi->at(l);

	    if(!isQualityMuon_tight(em->muChi2NDF->at(l),
				    em->muInnerD0->at(l),
				    em->muInnerDz->at(l),
				    em->muMuonHits->at(l),
				    em->muPixelHits->at(l),
				    em->muIsGlobal->at(l),
				    em->muIsPF->at(l),
				    em->muStations->at(l),
				    em->muTrkLayers->at(l))) continue; // skip if muon doesnt pass quality cuts

	    // if(!isQualityMuon_hybridSoft(em->muChi2NDF->at(l),
	    // 				 em->muInnerD0->at(l),
	    // 				 em->muInnerDz->at(l),
	    // 				 em->muPixelHits->at(l),
	    // 				 em->muIsTracker->at(l),
	    // 				 em->muIsGlobal->at(l),
	    // 				 em->muTrkLayers->at(l))) continue; // skip if muon doesnt pass quality cuts	



	    if(getDr(genMuonEta_j,genMuonPhi_j,recoMuonEta_l,recoMuonPhi_l) < epsilon){
				
	      isMatchedGenMuon = true;
	      genMuonPt_matched_j = recoMuonPt_l;
	      genMuonEta_matched_j = recoMuonEta_l;
	      genMuonPhi_matched_j = recoMuonPhi_l;
			
	    }

	  }

	  if(getDr(genMuonEta_j,genMuonPhi_j,recoJetEta_i,recoJetPhi_i) < deltaRCut){
				
	    matchFlag[genMuIndex] = 1;
	    hasInclGenMuonTag = true;
	    if(isMatchedGenMuon) hasMatchedGenMuonTag = true;

	  } 

	} // end genMuon loop
      }
	

      // look for recoMuon match to recoJet
      
      for(int m = 0; m < em->nMu; m++){

	double recoMuonPt_m = em->muPt->at(m);
	double recoMuonEta_m = em->muEta->at(m);
	double recoMuonPhi_m = em->muPhi->at(m);

	if(matchFlagR[m] == 1) continue;
	// muon kinematic cuts
	if(recoMuonPt_m < muPtCut || recoMuonPt_m > muPtMaxCut || fabs(recoMuonEta_m) > 2.0) continue;
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
	// 			     em->muInnerD0->at(m),
	// 			     em->muInnerDz->at(m),
	// 			     em->muPixelHits->at(m),
	// 			     em->muIsTracker->at(m),
	// 			     em->muIsGlobal->at(m),
	// 			     em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     

			



	if(isWDecayMuon(recoMuonPt_m,recoJetPt_i)) continue; // skip if "WDecay" muon (has majority of jet pt) 
			

	// match to genMuon
	bool isMatchedRecoMuon = false;

	if(!skipGenParticles){

	  for(int j = 0; j < em->gpptp->size(); j++){
			
	    if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;
		
	    if(getDr(recoMuonEta_m,recoMuonPhi_m,em->gpetap->at(j),em->gpphip->at(j)) < epsilon){

	      isMatchedRecoMuon = true;
			
	    }

	  }
	}

	// match to recoJets
	if(getDr(recoMuonEta_m,recoMuonPhi_m,recoJetEta_i,recoJetPhi_i) < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel_i = getPtRel(recoMuonPt_m,recoMuonEta_m,recoMuonPhi_m,recoJetPt_i,recoJetEta_i,recoJetPhi_i);

	  double delta = (getPtRel(recoMuonPt_m,recoMuonEta_m,recoMuonPhi_m,recoJetPt_i,recoJetEta_i,recoJetPhi_i) - getPtRel(recoMuonPt_m,recoMuonEta_m,recoMuonPhi_m,recoJetPt_i,em->jet_wta_eta[i],em->jet_wta_phi[i])) / getPtRel(recoMuonPt_m,recoMuonEta_m,recoMuonPhi_m,recoJetPt_i,em->jet_wta_eta[i],em->jet_wta_phi[i]);
	  
	  h_delta_muptrel_WTA_nom_flavor->Fill(delta,jetFlavorInt);

	  muPt_i = recoMuonPt_m;
	  muEta_i = recoMuonEta_m;
	  muPhi_i = recoMuonPhi_m;
				
	  if(isMatchedRecoMuon) hasMatchedRecoMuonTag = true;

	}
						


      }

      // Fill the jet/event histograms
     

      h_inclRecoJetPt_flavor[0]->Fill(recoJetPt_i,jetFlavorInt,w);
      h_inclRecoJetPt_flavor[CentralityIndex]->Fill(recoJetPt_i,jetFlavorInt,w);
      h_inclRecoJetEta_flavor[0]->Fill(recoJetEta_i,jetFlavorInt,w);
      h_inclRecoJetEta_flavor[CentralityIndex]->Fill(recoJetEta_i,jetFlavorInt,w);
      h_inclRecoJetPhi_flavor[0]->Fill(recoJetPhi_i,jetFlavorInt,w);
      h_inclRecoJetPhi_flavor[CentralityIndex]->Fill(recoJetPhi_i,jetFlavorInt,w);
      h_inclRecoJetPt_inclRecoJetEta[0]->Fill(recoJetPt_i,recoJetEta_i,w);
      h_inclRecoJetPt_inclRecoJetEta[CentralityIndex]->Fill(recoJetPt_i,recoJetEta_i,w);
      h_inclRecoJetPt_inclRecoJetPhi[0]->Fill(recoJetPt_i,recoJetPhi_i,w);
      h_inclRecoJetPt_inclRecoJetPhi[CentralityIndex]->Fill(recoJetPt_i,recoJetPhi_i,w);
      
      h_refPartonFlavorForB_matchedPartonFlavor[0]->Fill(refPartonFlavorForB,matchedPartonFlavor,w);
      h_refPartonFlavorForB_matchedPartonFlavor[CentralityIndex]->Fill(refPartonFlavorForB,matchedPartonFlavor,w);

      h_matchedPartonFlavor_bHadronNumber->Fill(matchedPartonFlavor,bHadronNumber,w);

      // histograms by jetPt index

      h_inclRecoJetEta_inclRecoJetPhi[0][0]->Fill(recoJetEta_i,recoJetPhi_i,w);
      h_inclRecoJetEta_inclRecoJetPhi[CentralityIndex][0]->Fill(recoJetEta_i,recoJetPhi_i,w);
      if(jetPtIndex > 0){
	h_inclRecoJetEta_inclRecoJetPhi[0][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w);
	h_inclRecoJetEta_inclRecoJetPhi[CentralityIndex][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w);
      }



      double w_jet = w;
      if(doJetPtReweight){
	if(hasInclRecoMuonTag && evtTriggerDecision) w_jet = w_pthat * w_reweight_vz * fitFxn_jetPt->Eval(recoJetPt_i);
      }


      
		
      if(hasInclGenMuonTag){

	h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[0][0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[CentralityIndex][0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	if(jetPtIndex > 0){
	  h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[0][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	  h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[CentralityIndex][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	}

	h_inclRecoJetPt_inclGenMuonTag_flavor[0]->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	h_inclRecoJetPt_inclGenMuonTag_flavor[CentralityIndex]->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	h_inclRecoJetEta_inclGenMuonTag_flavor[0]->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	h_inclRecoJetEta_inclGenMuonTag_flavor[CentralityIndex]->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	h_inclRecoJetPhi_inclGenMuonTag_flavor[0]->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	h_inclRecoJetPhi_inclGenMuonTag_flavor[CentralityIndex]->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag[0]->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag[CentralityIndex]->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag[0]->Fill(recoJetPt_i,recoJetPhi_i,w_jet);
	h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag[CentralityIndex]->Fill(recoJetPt_i,recoJetPhi_i,w_jet);

      } 

      if(hasInclRecoMuonTag){

	eventHasInclRecoMuonTag = true;

	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0][0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[CentralityIndex][0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	if(jetPtIndex > 0){
	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[CentralityIndex][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	}

	

	h_inclRecoJetPt_inclRecoMuonTag_flavor[0]->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	h_inclRecoJetPt_inclRecoMuonTag_flavor[CentralityIndex]->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	h_inclRecoJetEta_inclRecoMuonTag_flavor[0]->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	h_inclRecoJetEta_inclRecoMuonTag_flavor[CentralityIndex]->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	h_inclRecoJetPhi_inclRecoMuonTag_flavor[0]->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	h_inclRecoJetPhi_inclRecoMuonTag_flavor[CentralityIndex]->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[0]->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag[CentralityIndex]->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[0]->Fill(recoJetPt_i,recoJetPhi_i,w_jet);
	h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag[CentralityIndex]->Fill(recoJetPt_i,recoJetPhi_i,w_jet);

	
	if(evtTriggerDecision){
	 
	  eventHasInclRecoMuonTagPlusTrigger = true;

	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[0][0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[CentralityIndex][0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	  if(jetPtIndex > 0){
	    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[0][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[CentralityIndex][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	  }

	  h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor[0]->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	  h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor[0]->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	  h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor[0]->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[0]->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[0]->Fill(recoJetPt_i,recoJetPhi_i,w_jet);
	  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn[CentralityIndex]->Fill(recoJetPt_i,recoJetPhi_i,w_jet);


	    
	  h_muptrel_inclRecoMuonTag_triggerOn_flavor[0][0]->Fill(muPtRel_i,jetFlavorInt,w_jet);
	  h_mupt_inclRecoMuonTag_triggerOn_flavor[0][0]->Fill(muPt_i,jetFlavorInt,w_jet);
	  h_mueta_inclRecoMuonTag_triggerOn_flavor[0][0]->Fill(muEta_i,jetFlavorInt,w_jet);
	  h_muphi_inclRecoMuonTag_triggerOn_flavor[0][0]->Fill(muPhi_i,jetFlavorInt,w_jet);

	  h_mupt_jetpt[0]->Fill(muPt_i,recoJetPt_i,w_jet);
	  h_mupt_jetpt[CentralityIndex]->Fill(muPt_i,recoJetPt_i,w_jet);
	  
	  h_muptrel_jetpt[0]->Fill(muPtRel_i,recoJetPt_i,w_jet);
	  h_muptrel_jetpt[CentralityIndex]->Fill(muPtRel_i,recoJetPt_i,w_jet);
	 

	  if(jetPtIndex > 0){

	    	    
	    h_muptrel_inclRecoMuonTag_triggerOn_flavor[0][jetPtIndex]->Fill(muPtRel_i,jetFlavorInt,w_jet);
	    h_muptrel_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][0]->Fill(muPtRel_i,jetFlavorInt,w_jet);
	    h_muptrel_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][jetPtIndex]->Fill(muPtRel_i,jetFlavorInt,w_jet);

	    h_mupt_inclRecoMuonTag_triggerOn_flavor[0][jetPtIndex]->Fill(muPt_i,jetFlavorInt,w_jet);
	    h_mupt_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][0]->Fill(muPt_i,jetFlavorInt,w_jet);
	    h_mupt_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][jetPtIndex]->Fill(muPt_i,jetFlavorInt,w_jet);

	    h_mueta_inclRecoMuonTag_triggerOn_flavor[0][jetPtIndex]->Fill(muEta_i,jetFlavorInt,w_jet);
	    h_mueta_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][0]->Fill(muEta_i,jetFlavorInt,w_jet);
	    h_mueta_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][jetPtIndex]->Fill(muEta_i,jetFlavorInt,w_jet);

	    h_muphi_inclRecoMuonTag_triggerOn_flavor[0][jetPtIndex]->Fill(muPhi_i,jetFlavorInt,w_jet);
	    h_muphi_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][0]->Fill(muPhi_i,jetFlavorInt,w_jet);
	    h_muphi_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][jetPtIndex]->Fill(muPhi_i,jetFlavorInt,w_jet);

	    h_mupt_muptrel[0][0]->Fill(muPt_i,muPtRel_i,w_jet);
	    h_mupt_muptrel[CentralityIndex][0]->Fill(muPt_i,muPtRel_i,w_jet);
	    h_mupt_muptrel[CentralityIndex][jetPtIndex]->Fill(muPt_i,muPtRel_i,w_jet);
	    
	  }
	} 

	if(hasMatchedRecoMuonTag){

	  eventHasMatchedRecoMuonTag = true;

	  h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[0][0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	  h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[CentralityIndex][0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	  if(jetPtIndex > 0){
	    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[0][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[CentralityIndex][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	  }

	  h_inclRecoJetPt_matchedRecoMuonTag_flavor[0]->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPt_matchedRecoMuonTag_flavor[CentralityIndex]->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	  h_inclRecoJetEta_matchedRecoMuonTag_flavor[0]->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	  h_inclRecoJetEta_matchedRecoMuonTag_flavor[CentralityIndex]->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPhi_matchedRecoMuonTag_flavor[0]->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPhi_matchedRecoMuonTag_flavor[CentralityIndex]->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag[0]->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag[CentralityIndex]->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag[0]->Fill(recoJetPt_i,recoJetPhi_i,w_jet);
	  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag[CentralityIndex]->Fill(recoJetPt_i,recoJetPhi_i,w_jet);

	  if(evtTriggerDecision){

	    eventHasMatchedRecoMuonTagPlusTrigger = true;

	    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[0][0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[CentralityIndex][0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	    if(jetPtIndex > 0){
	      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[0][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[CentralityIndex][jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	    }
	  	   
	    h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor[0]->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	    h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	    h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor[0]->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	    h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	    h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor[0]->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	    h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	    h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn[0]->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	    h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn[CentralityIndex]->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	    h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[0]->Fill(recoJetPt_i,recoJetPhi_i,w_jet);
	    h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[CentralityIndex]->Fill(recoJetPt_i,recoJetPhi_i,w_jet);

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


      double genJetPt_i = em->genjetpt[i];  // genJetPt
      double genJetEta_i = em->genjeteta[i]; // genJetEta
      double genJetPhi_i = em->genjetphi[i]; // genJetPhi

      // muPtRel to fill if necessary
      double muPtRel_i = -1.0;

      if(TMath::Abs(genJetEta_i) > etaMax || genJetPt_i < jetPtCut) continue;


      // fill genJetPt vs pthat
      h_genJetPt_pthat[0]->Fill(genJetPt_i,em->pthat,w);
      h_genJetPt_pthat[CentralityIndex]->Fill(genJetPt_i,em->pthat,w);



      int jetPtIndex = getJetPtBin(genJetPt_i);

      //cout << "jetPt = " << x << " | index = " << jetPtIndex << endl;

      // GET FLAVOR FROM RECO MATCH
      bool hasRecoJetMatch = false;
      int recoJetFlavorFlag = 0;
      double minDr = 100.0;
      int jetFlavorInt = 19;
      int bHadronNumber = 0;
	
      double matchedRecoJetPt_i = -1.0;
		

      for(int k = 0; k < em->njet; k++){
		
	if(remove_HYDJET_jet(em->pthat,em->jetpt[k])) continue;
	double dr = getDr(em->jeteta[k],em->jetphi[k],genJetEta_i,genJetPhi_i);

	if(dr < minDr){ 

	  minDr = dr;

	  if(minDr < epsilon_mm){

	    recoJetFlavorFlag = k;
	    hasRecoJetMatch = true;
	    			
	  }	
	}

      }

     
      if(hasRecoJetMatch) {
	jetFlavorInt = em->matchedPartonFlavor[recoJetFlavorFlag];
	bHadronNumber = em->bHadronNumber[recoJetFlavorFlag];
	if(fabs(jetFlavorInt) == 5 && bHadronNumber == 2) jetFlavorInt = 17;
	matchedRecoJetPt_i = em->jetpt[recoJetFlavorFlag];
	//cout << "genJet flavor match: (event#" << evi << ", genJet#" << i << ", recoJet#" << recoJetFlavorFlag << ") = " << jetFlavorInt << endl;
      }

      int genMuIndex = -1;
      bool hasInclGenMuonTag = false;
      bool hasMatchedGenMuonTag = false;

      bool hasInclRecoMuonTag = false;
      bool hasMatchedRecoMuonTag = false;

      // look for a genMuon match
      if(!skipGenParticles){

	for(int j = 0; j < em->gpptp->size(); j++){

	  //cout << "N_genParticles = " << em->gppdgIDp->size() << endl;
	  //cout << "pdg of particle " << j <<" = " << em->gppdgIDp->at(j) << endl;

                        
	  bool isMatchedGenMuon = false;

	  if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

	  genMuIndex++;

	  if(matchFlag[genMuIndex] == 1) continue; // skip if muon has been matched to a jet already

	  if(isWDecayMuon(em->gpptp->at(j),genJetPt_i)) continue; // skip if "WDecay" muon (has majority of jet pt)

	  double genMuonPt_j = em->gpptp->at(j);
	  double genMuonPt_matched_j = -1.0;
	  double genMuonEta_j = em->gpetap->at(j);
	  double genMuonEta_matched_j = -1.0;
	  double genMuonPhi_j = em->gpphip->at(j);
	  double genMuonPhi_matched_j = -1.0;


	  if(genMuonPt_j < muPtCut || fabs(genMuonEta_j) > 2.0) continue;

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

	    // if(!isQualityMuon_hybridSoft(em->muChi2NDF->at(l),
	    // 				 em->muInnerD0->at(l),
	    // 				 em->muInnerDz->at(l),
	    // 				 em->muPixelHits->at(l),
	    // 				 em->muIsTracker->at(l),
	    // 				 em->muIsGlobal->at(l),
	    // 				 em->muTrkLayers->at(l))) continue; // skip if muon doesnt pass quality cuts	
	    
	    //if(isWDecayMuon(em->muPt->at(l),x)) continue; // skip if "WDecay" muon (has majority of jet pt)	
			
		
	    double recoMuonPt_l = em->muPt->at(l);
	    double recoMuonEta_l = em->muEta->at(l);
	    double recoMuonPhi_l = em->muPhi->at(l);
			

	    if(getDr(genMuonEta_j,genMuonPhi_j,recoMuonEta_l,recoMuonPhi_l) < epsilon){
				
	      isMatchedGenMuon = true;
	      genMuonPt_matched_j = recoMuonPt_l;
	      genMuonEta_matched_j = recoMuonEta_l;
	      genMuonPhi_matched_j = recoMuonPhi_l;
			
	    }

	  }

	  if(getDr(genMuonEta_j,genMuonPhi_j,genJetEta_i,genJetPhi_i) < deltaRCut){
				
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

	// if(!isQualityMuon_hybridSoft(em->muChi2NDF->at(m),
	// 			     em->muInnerD0->at(m),
	// 			     em->muInnerDz->at(m),
	// 			     em->muPixelHits->at(m),
	// 			     em->muIsTracker->at(m),
	// 			     em->muIsGlobal->at(m),
	// 			     em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     

	if(isWDecayMuon(em->muPt->at(m),genJetPt_i)) continue; // skip if "WDecay" muon (has majority of jet pt) 
	
			
	// match to genMuon
			

	bool isMatchedRecoMuon = false;

	if(!skipGenParticles){

	  for(int l = 0; l < em->gpptp->size(); l++){

	    //cout << "genID = " << em->gppdgIDp->at(j) << endl;
			
	    if(TMath::Abs(em->gppdgIDp->at(l)) != 13) continue;

	    if(em->gpptp->at(l) < muPtCut || fabs(em->gpetap->at(l)) > 2.0) continue;                        
		
	    if(getDr(em->muEta->at(m),em->muPhi->at(m),em->gpetap->at(l),em->gpphip->at(l)) < epsilon){

	      isMatchedRecoMuon = true;
			
	    }

	  }

	}

	// match to genJets
	if(getDr(em->muEta->at(m),em->muPhi->at(m),genJetEta_i,genJetPhi_i) < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel_i = getPtRel(em->muPt->at(m),em->muEta->at(m),em->muPhi->at(m),genJetPt_i,genJetEta_i,genJetPhi_i);
	  
	  //cout << "(Event "<< evi << ", Jet " << i << ", Muon " << m << ") muPtRel = " << muPtRel << endl;
				
	  if(isMatchedRecoMuon) hasMatchedRecoMuonTag = true;

	}
						


      }

      // Fill the jet histograms

		

      h_inclGenJetPt_flavor[0]->Fill(genJetPt_i,jetFlavorInt,w);
      h_inclGenJetPt_flavor[CentralityIndex]->Fill(genJetPt_i,jetFlavorInt,w);

      h_matchedRecoJetPt_genJetPt[0]->Fill(matchedRecoJetPt_i,genJetPt_i,w);
      h_matchedRecoJetPt_genJetPt[CentralityIndex]->Fill(matchedRecoJetPt_i,genJetPt_i,w);
     

      if(hasInclGenMuonTag){

	h_inclGenJetPt_inclGenMuonTag_flavor[0]->Fill(genJetPt_i,jetFlavorInt,w);
	h_inclGenJetPt_inclGenMuonTag_flavor[CentralityIndex]->Fill(genJetPt_i,jetFlavorInt,w);

      } 

      if(hasInclRecoMuonTag){

	h_inclGenJetPt_inclRecoMuonTag_flavor[0]->Fill(genJetPt_i,jetFlavorInt,w);
	h_inclGenJetPt_inclRecoMuonTag_flavor[CentralityIndex]->Fill(genJetPt_i,jetFlavorInt,w);
			
	if(evtTriggerDecision){
	  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor[0]->Fill(genJetPt_i,jetFlavorInt,w);
	  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(genJetPt_i,jetFlavorInt,w);
	  h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[0][0]->Fill(muPtRel_i,jetFlavorInt,w);
	  if(jetPtIndex > 0){
	    h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[0][jetPtIndex]->Fill(muPtRel_i,jetFlavorInt,w);
	    h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][0]->Fill(muPtRel_i,jetFlavorInt,w);
	    h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[CentralityIndex][jetPtIndex]->Fill(muPtRel_i,jetFlavorInt,w);
	  }
	} 

	if(hasMatchedRecoMuonTag){

	  h_inclGenJetPt_matchedRecoMuonTag_flavor[0]->Fill(genJetPt_i,jetFlavorInt,w);
	  h_inclGenJetPt_matchedRecoMuonTag_flavor[CentralityIndex]->Fill(genJetPt_i,jetFlavorInt,w);

	  if(evtTriggerDecision){
	    h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor[0]->Fill(genJetPt_i,jetFlavorInt,w);
	    h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor[CentralityIndex]->Fill(genJetPt_i,jetFlavorInt,w);
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
  h_delta_muptrel_WTA_nom_flavor->Write();
  h_hiBin->Write();
  h_hiBin_inclGenMuonTag->Write();
  h_hiBin_inclRecoMuonTag->Write();
  h_hiBin_inclRecoMuonTag_triggerOn->Write();
  h_hiBin_matchedRecoMuonTag->Write();
  h_hiBin_matchedRecoMuonTag_triggerOn->Write();
  h_weight_pthat_xJets_C1J3->Write();
  h_weight_pthat_bJets_C1J3->Write();
  h_matchedPartonFlavor_bHadronNumber->Write();
  
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

    h_leadingGenJetPt[i]->Write();
    h_leadingGenJetPt_xJets_greaterThanPthat[i]->Write();
    
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
