// general ROOT/C includes
#include <iostream>
#include "TFile.h"
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
#include "../../../eventMap/eventMap.h"
// jet corrector
#include "../../../JetEnergyCorrections/JetCorrector.h"
// jet uncertainty
#include "../../../JetEnergyCorrections/JetUncertainty.h"
// general analysis variables
//#include "../../../headers/AnalysisSetupV2p2.h"
#include "../../../headers/AnalysisSetupV2p3.h"
// vz-fit parameters
//#include "../../../headers/fitParameters/vzFitParams_PYTHIA_mu5.h"
//#include "../../../headers/fitParameters/vzFitParams_PYTHIA_mu7.h"
#include "../../../headers/fitParameters/vzFitParams_PYTHIA_mu12.h"
// jetPt-fit parameters
//#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu5.h"
//#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu7.h"
#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu12.h"
// JESb fit params
//#include "../../../headers/fitParameters/JESbFitParams_PYTHIA_mu7.h"
//#include "../../../headers/fitParameters/JESbFitParams_PYTHIA_mu12.h"
//#include "../../../headers/fitParameters/JESbFitParams_PYTHIA_mu12_useMax.h"
#include "../../../headers/fitParameters/JESbFitParams_PYTHIA_mu12_newFitMethod.h"
// bJetNeutrinoEnergy fit params
#include "../../../headers/fitParameters/bJetNeutrinoEnergyFitParams_PYTHIA_mu12.h"
// muptrel fit parameters
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C1J1.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C1J2.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C1J3.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C1J4.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C1J5.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C1J6.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C2J1.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C2J2.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C2J3.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C2J4.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C2J5.h"
#include "../../../headers/fitParameters/muptrelFitParams/muptrelFitParams_C2J6.h"
// dR fit parameters
#include "../../../headers/fitParameters/dRFitParams/dRFitParams.h"
// hadronPtRel parameters
#include "../../../headers/fitParameters/hadronPtRelFitParams.h"

TF1 *fitFxn_hiBin, *fitFxn_vz, *fitFxn_jetPt, *fitFxn_PYTHIA_JESb, *fitFxn_PYTHIA_bJetNeutrinoEnergy, *fitFxn_dR, *fitFxn_hadronPtRel;
TF1 *fitFxn_muptrel_C1J1, *fitFxn_muptrel_C1J2, *fitFxn_muptrel_C1J3, *fitFxn_muptrel_C1J4, *fitFxn_muptrel_C1J5, *fitFxn_muptrel_C1J6;
TF1 *fitFxn_muptrel_C2J1, *fitFxn_muptrel_C2J2, *fitFxn_muptrel_C2J3, *fitFxn_muptrel_C2J4, *fitFxn_muptrel_C2J5, *fitFxn_muptrel_C2J6;
// dR fit function
#include "../../../headers/fitFunctions/fitFxn_dR.h"
// hadronPtRel parameters
#include "../../../headers/fitFunctions/fitFxn_hadronPtRel.h"
// muptrel fit functions
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C1J1.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C1J2.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C1J3.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C1J4.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C1J5.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C1J6.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C2J1.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C2J2.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C2J3.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C2J4.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C2J5.h"
#include "../../../headers/fitFunctions/fitFxn_muptrel/fitFxn_muptrel_C2J6.h"
// vz-fit function
#include "../../../headers/fitFunctions/fitFxn_vz_PYTHIA.h"
// jetPt-fit function
#include "../../../headers/fitFunctions/fitFxn_jetPt.h"
// JESb-fit function
#include "../../../headers/fitFunctions/fitFxn_PYTHIA_JESb.h"
// bJetNeutrinoEnergy-fit function
#include "../../../headers/fitFunctions/fitFxn_PYTHIA_bJetNeutrinoEnergy.h"
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
// triggerIsOn function
#include "../../../headers/functions/triggerIsOn.h"
// pthat filter function
#include "../../../headers/functions/passesLeadingGenJetPthatFilter.h"
// JetTrkMax filter function
#include "../../../headers/functions/jet_filter/passesJetTrkMaxFilter.h"
// print introduction
#include "../../../headers/introductions/printIntroduction_PYTHIA_scan_V3p7.h"
// analysis config
#include "../../../headers/config/config_PYTHIA.h"
// read config
#include "../../../headers/config/readConfig.h"
// remove HYDJET jets function
#include "../../../headers/functions/jet_filter/remove_HYDJET_jet.h"



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
TH2D *h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_flavor;
TH2D *h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_genNeutrinoPt;
TH2D *h_inclRecoJetEta_inclGenMuonTag_flavor;
TH2D *h_inclRecoJetPhi_inclGenMuonTag_flavor;
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag;
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag;
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[NJetPtIndices];
// ------------------- incl. reco jets tagged to incl. reco muon by flavor -----
TH2D *h_inclRecoJetPt_inclRecoMuonTag_flavor;
TH2D *h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_flavor;
TH2D *h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_genNeutrinoPt;
TH2D *h_inclRecoJetEta_inclRecoMuonTag_flavor;
TH2D *h_inclRecoJetPhi_inclRecoMuonTag_flavor;
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag;
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag;
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[NJetPtIndices];
// ------------------- incl. reco jets tagged to incl. reco muon w/ trigger by flavor ----
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
// ----- leading reco jets tagged to matched reco muon by flavor, trigger on ----
TH2D *h_leadingRecoJetPt_inclRecoMuonTag_triggerOn_flavor;
// ------------------------------- in-jet reco muons by flavor, trigger on ----
// all jets
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets;
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_allJets;
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_allJets;
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_allJets;
TH2D *h_muJetDr_recoJetPt_allJets;
// u/ubar jets
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_uJets;
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_uJets;
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_uJets;
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_uJets;
TH2D *h_muJetDr_recoJetPt_uJets;
// d/dbar jets
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_dJets;
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_dJets;
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_dJets;
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_dJets;
TH2D *h_muJetDr_recoJetPt_dJets;
// s/sbar jets
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_sJets;
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_sJets;
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_sJets;
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_sJets;
TH2D *h_muJetDr_recoJetPt_sJets;
// c/cbar jets
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_cJets;
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_cJets;
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_cJets;
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_cJets;
TH2D *h_muJetDr_recoJetPt_gJets;
// b/bbar jets
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets;
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bJets;
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bJets;
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bJets;
TH2D *h_muJetDr_recoJetPt_bJets;
// bGS jets
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets;
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets;
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets;
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets;
TH2D *h_muJetDr_recoJetPt_bGSJets;
// gluon jets
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_gJets;
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_gJets;
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_gJets;
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_gJets;
TH2D *h_muJetDr_recoJetPt_gJets;
// x jets
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_xJets;
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_xJets;
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_xJets;
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_xJets;
TH2D *h_muJetDr_recoJetPt_xJets;

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
// ---------------------------- Analysis histograms ---------------------------
TH2D *h_recoGenDr_flavor[NJetPtIndices];
TH2D *h_recoGenDpt_flavor[NJetPtIndices];
TH2D *h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[NJetPtIndices][7];
TH2D *h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[NJetPtIndices][7];
TH2D *h_muJetDr_flavor[NJetPtIndices];



void PYTHIA_scan(int group = 1){


  TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_PYTHIA_DiJet_withGS/PYTHIA_DiJet_skim_output_%i.root",group);
  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skim_testForest_PYTHIA_DiJet/PYTHIA_DiJet_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjet_jetTrkMaxFilter_vzReweight_jetPtReweight_projectableTemplates/PYTHIA_DiJet_scan_output_%i.root",group);


  printIntroduction_PYTHIA_scan_V3p7();
  readConfig();

  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt"); // LXPLUS
  JetCorrector JEC(Files);


  JetUncertainty JEU("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_Uncertainty_AK4PF.txt");


  
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
  h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_flavor = new TH2D("h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_flavor","JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. gen muon & gen neutrino",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_genNeutrinoPt = new TH2D("h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_genNeutrinoPt","JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. gen muon & gen neutrino",NPtBins,ptMin,ptMax,100,0,100);
  h_inclRecoJetEta_inclGenMuonTag_flavor = new TH2D("h_inclRecoJetEta_inclGenMuonTag_flavor","JetFlavorID vs incl. reco #eta^{jet}, tagged with incl. gen muon",NEtaBins,etaMin,etaMax,27,-5,22);
  h_inclRecoJetPhi_inclGenMuonTag_flavor = new TH2D("h_inclRecoJetPhi_inclGenMuonTag_flavor","JetFlavorID vs incl. reco #phi^{jet}, tagged with incl. gen muon",NPhiBins,phiMin,phiMax,27,-5,22);
  h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag = new TH2D("h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag","incl. reco p_{T}^{jet} vs. incl. reco #eta^{jet}, tagged with incl. gen muon",NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
  h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag = new TH2D("h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag","incl. reco p_{T}^{jet} vs. incl. reco #phi^{jet}, tagged with incl. gen muon",NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
  
  h_inclRecoJetPt_inclRecoMuonTag_flavor = new TH2D("h_inclRecoJetPt_inclRecoMuonTag_flavor","JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_flavor = new TH2D("h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_flavor","JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. reco muon & gen neutrino",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_genNeutrinoPt = new TH2D("h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_genNeutrinoPt","JetFlavorID vs incl. reco p_{T}^{jet}, tagged with incl. gen muon & gen neutrino",NPtBins,ptMin,ptMax,100,0,100);
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
  
  h_leadingRecoJetPt_inclRecoMuonTag_triggerOn_flavor = new TH2D("h_leadingRecoJetPt_inclRecoMuonTag_triggerOn_flavor","JetFlavorID vs leading reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON",NPtBins,ptMin,ptMax,27,-5,22);
  
  
  h_inclGenJetPt_flavor = new TH2D("h_inclGenJetPt_flavor","JetFlavorID vs incl. gen p_{T}^{jet}",NPtBins,ptMin,ptMax,27,-5,22);

  h_inclGenJetPt_inclGenMuonTag_flavor = new TH2D("h_inclGenJetPt_inclGenMuonTag_flavor","JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. gen muon",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclGenJetPt_inclRecoMuonTag_flavor = new TH2D("h_inclGenJetPt_inclRecoMuonTag_flavor","JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor = new TH2D("h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor","JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. reco muon, trigger ON",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclGenJetPt_matchedRecoMuonTag_flavor = new TH2D("h_inclGenJetPt_matchedRecoMuonTag_flavor","JetFlavorID vs incl. gen p_{T}^{jet}, tagged with matched reco muon",NPtBins,ptMin,ptMax,27,-5,22);
  h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor = new TH2D("h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor","JetFlavorID vs incl. gen p_{T}^{jet}, tagged with matched reco muon, trigger ON",NPtBins,ptMin,ptMax,27,-5,22);

  h_recoJetPt_pthat = new TH2D("h_recoJetPt_pthat","reco p_{T}^{jet} vs. #hat{p}_{T}, PYTHIA; reco p_{T}^{jet} [GeV]; #hat{p}_{T} [GeV]",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_genJetPt_pthat = new TH2D("h_genJetPt_pthat","gen p_{T}^{jet} vs. #hat{p}_{T}, PYTHIA; gen p_{T}^{jet} [GeV]; #hat{p}_{T} [GeV]",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);

  // muon-based 2d histograms
  // allJets
  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets = new TH2D("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets","muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, allJets",NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_allJets = new TH2D("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_allJets","muon #it{p}_{T} vs jet #it{p}_{T}, allJets",NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_allJets = new TH2D("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_allJets","muon #it{#eta} vs jet #it{p}_{T}, allJets",NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_allJets = new TH2D("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_allJets","muon #it{#phi} vs jet #it{p}_{T}, allJets",NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
  h_muJetDr_recoJetPt_allJets = new TH2D("h_muJetDr_recoJetPt_allJets","#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, allJets",NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);
  // uJets
  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_uJets = new TH2D("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_uJets","muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, uJets",NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_uJets = new TH2D("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_uJets","muon #it{p}_{T} vs jet #it{p}_{T}, uJets",NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_uJets = new TH2D("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_uJets","muon #it{#eta} vs jet #it{p}_{T}, uJets",NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_uJets = new TH2D("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_uJets","muon #it{#phi} vs jet #it{p}_{T}, uJets",NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
  h_muJetDr_recoJetPt_uJets = new TH2D("h_muJetDr_recoJetPt_uJets","#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, uJets",NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);
  // dJets
  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_dJets = new TH2D("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_dJets","muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, dJets",NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_dJets = new TH2D("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_dJets","muon #it{p}_{T} vs jet #it{p}_{T}, dJets",NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_dJets = new TH2D("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_dJets","muon #it{#eta} vs jet #it{p}_{T}, dJets",NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_dJets = new TH2D("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_dJets","muon #it{#phi} vs jet #it{p}_{T}, dJets",NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
  h_muJetDr_recoJetPt_dJets = new TH2D("h_muJetDr_recoJetPt_dJets","#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, dJets",NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);
  // sJets
  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_sJets = new TH2D("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_sJets","muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, sJets",NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_sJets = new TH2D("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_sJets","muon #it{p}_{T} vs jet #it{p}_{T}, sJets",NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_sJets = new TH2D("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_sJets","muon #it{#eta} vs jet #it{p}_{T}, sJets",NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_sJets = new TH2D("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_sJets","muon #it{#phi} vs jet #it{p}_{T}, sJets",NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
  h_muJetDr_recoJetPt_sJets = new TH2D("h_muJetDr_recoJetPt_sJets","#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, sJets",NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);
  // cJets
  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_cJets = new TH2D("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_cJets","muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, cJets",NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_cJets = new TH2D("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_cJets","muon #it{p}_{T} vs jet #it{p}_{T}, cJets",NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_cJets = new TH2D("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_cJets","muon #it{#eta} vs jet #it{p}_{T}, cJets",NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_cJets = new TH2D("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_cJets","muon #it{#phi} vs jet #it{p}_{T}, cJets",NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
  h_muJetDr_recoJetPt_cJets = new TH2D("h_muJetDr_recoJetPt_cJets","#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, cJets",NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);
  // bJets
  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets = new TH2D("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets","muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, bJets",NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bJets = new TH2D("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bJets","muon #it{p}_{T} vs jet #it{p}_{T}, bJets",NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bJets = new TH2D("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bJets","muon #it{#eta} vs jet #it{p}_{T}, bJets",NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bJets = new TH2D("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bJets","muon #it{#phi} vs jet #it{p}_{T}, bJets",NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
  h_muJetDr_recoJetPt_bJets = new TH2D("h_muJetDr_recoJetPt_bJets","#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, bJets",NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);
  // bGSJets
  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets = new TH2D("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets","muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, bGSJets",NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets = new TH2D("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets","muon #it{p}_{T} vs jet #it{p}_{T}, bGSJets",NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets = new TH2D("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets","muon #it{#eta} vs jet #it{p}_{T}, bGSJets",NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets = new TH2D("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets","muon #it{#phi} vs jet #it{p}_{T}, bGSJets",NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
  h_muJetDr_recoJetPt_bGSJets = new TH2D("h_muJetDr_recoJetPt_bGSJets","#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, bGSJets",NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);
  // gJets
  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_gJets = new TH2D("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_gJets","muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, gJets",NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_gJets = new TH2D("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_gJets","muon #it{p}_{T} vs jet #it{p}_{T}, gJets",NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_gJets = new TH2D("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_gJets","muon #it{#eta} vs jet #it{p}_{T}, gJets",NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_gJets = new TH2D("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_gJets","muon #it{#phi} vs jet #it{p}_{T}, gJets",NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
  h_muJetDr_recoJetPt_gJets = new TH2D("h_muJetDr_recoJetPt_gJets","#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, gJets",NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);  
  // xJets
  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_xJets = new TH2D("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_xJets","muon #it{p}_{T}^{rel} vs jet #it{p}_{T}, xJets",NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_xJets = new TH2D("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_xJets","muon #it{p}_{T} vs jet #it{p}_{T}, xJets",NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_xJets = new TH2D("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_xJets","muon #it{#eta} vs jet #it{p}_{T}, xJets",NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_xJets = new TH2D("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_xJets","muon #it{#phi} vs jet #it{p}_{T}, xJets",NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
  h_muJetDr_recoJetPt_xJets = new TH2D("h_muJetDr_recoJetPt_xJets","#it{#Delta r}(muon,jet) vs jet #it{p}_{T}, xJets",NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);  

  
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
  h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_flavor->Sumw2();
  h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_genNeutrinoPt->Sumw2();
  h_inclRecoJetEta_inclGenMuonTag_flavor->Sumw2();
  h_inclRecoJetPhi_inclGenMuonTag_flavor->Sumw2();
  h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag->Sumw2();
  h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag->Sumw2();
  
  h_inclRecoJetPt_inclRecoMuonTag_flavor->Sumw2();
  h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_flavor->Sumw2();
  h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_genNeutrinoPt->Sumw2();
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

  h_leadingRecoJetPt_inclRecoMuonTag_triggerOn_flavor->Sumw2();

  h_inclGenJetPt_flavor->Sumw2();
  h_inclGenJetPt_inclGenMuonTag_flavor->Sumw2();
  h_inclGenJetPt_inclRecoMuonTag_flavor->Sumw2();
  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor->Sumw2();
  h_inclGenJetPt_matchedRecoMuonTag_flavor->Sumw2();
  h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor->Sumw2();

  h_recoJetPt_pthat->Sumw2();	
  h_genJetPt_pthat->Sumw2();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Sumw2();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Sumw2();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Sumw2();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Sumw2();
  h_muJetDr_recoJetPt_allJets->Sumw2();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Sumw2();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Sumw2();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Sumw2();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Sumw2();
  h_muJetDr_recoJetPt_uJets->Sumw2();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Sumw2();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Sumw2();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Sumw2();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Sumw2();
  h_muJetDr_recoJetPt_dJets->Sumw2();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Sumw2();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Sumw2();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Sumw2();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Sumw2();
  h_muJetDr_recoJetPt_sJets->Sumw2();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Sumw2();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Sumw2();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Sumw2();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Sumw2();
  h_muJetDr_recoJetPt_cJets->Sumw2();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Sumw2();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Sumw2();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Sumw2();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Sumw2();
  h_muJetDr_recoJetPt_bJets->Sumw2();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Sumw2();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Sumw2();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Sumw2();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Sumw2();
  h_muJetDr_recoJetPt_bGSJets->Sumw2();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Sumw2();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Sumw2();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Sumw2();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Sumw2();
  h_muJetDr_recoJetPt_gJets->Sumw2();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Sumw2();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Sumw2();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Sumw2();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Sumw2();
  h_muJetDr_recoJetPt_xJets->Sumw2();
  
  for(int j = 0; j < NJetPtIndices; j++){
	
    //
    if(j==0) {
      
      h_inclRecoJetEta_inclRecoJetPhi[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. gen muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON,  p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_recoGenDr_flavor[j] = new TH2D(Form("h_recoGenDr_J%i",j),Form("JetFlavorID vs #Delta r(recoJet,genJet), p_{T}^{jet} %3.0f - %3.0f ",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1,27,-5,22); 
      h_recoGenDpt_flavor[j] = new TH2D(Form("h_recoGenDpt_J%i",j),Form("JetFlavorID vs #Delta p_{T}/p_{T}(recoJet,genJet), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,5,27,-5,22);

      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][0] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_allJets_J%i",j),Form("allJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][1] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_bJets_J%i",j),Form("bJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][2] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_cJets_J%i",j),Form("cJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][3] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_udJets_J%i",j),Form("udJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][4] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_sJets_J%i",j),Form("sJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][5] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_gJets_J%i",j),Form("gJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][6] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_xJets_J%i",j),Form("xJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][0] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_allJets_J%i",j),Form("allJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][1] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_J%i",j),Form("bJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][2] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_cJets_J%i",j),Form("cJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][3] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_udJets_J%i",j),Form("udJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][4] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_sJets_J%i",j),Form("sJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][5] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_gJets_J%i",j),Form("gJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][6] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_xJets_J%i",j),Form("xJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      

    }
    else {
      
      h_inclRecoJetEta_inclRecoJetPhi[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. gen muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON,  p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_J%i",j),Form("incl. reco #phi^{jet} vs. incl. reco #eta^{jet}, tagged with matched reco muon, trigger ON, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_recoGenDr_flavor[j] = new TH2D(Form("h_recoGenDr_J%i",j),Form("JetFlavorID vs #Delta r(recoJet,genJet), p_{T}^{jet} %3.0f - %3.0f ",jetPtEdges[j-1],jetPtEdges[j]),100,0,1,27,-5,22); 
      h_recoGenDpt_flavor[j] = new TH2D(Form("h_recoGenDpt_J%i",j),Form("JetFlavorID vs #Delta p_{T}/p_{T}(recoJet,genJet), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,5,27,-5,22);
      // new response matrices
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][0] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_allJets_J%i",j),Form("allJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][1] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_bJets_J%i",j),Form("bJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][2] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_cJets_J%i",j),Form("cJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][3] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_udJets_J%i",j),Form("udJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][4] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_sJets_J%i",j),Form("sJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][5] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_gJets_J%i",j),Form("gJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][6] = new TH2D(Form("h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon_xJets_J%i",j),Form("xJets, muon pTrel (genJet,genMuon) vs. muon pTrel(recoJet,matchedRecoMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax,NMuRelPtBins,muRelPtMin,muRelPtMax);
      
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][0] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_allJets_J%i",j),Form("allJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][1] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_J%i",j),Form("bJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][2] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_cJets_J%i",j),Form("cJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][3] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_udJets_J%i",j),Form("udJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][4] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_sJets_J%i",j),Form("sJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][5] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_gJets_J%i",j),Form("gJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][6] = new TH2D(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_xJets_J%i",j),Form("xJets, muon pTrel(recoJet,matchedRecoMuon) / muon pTrel (genJet,genMuon) vs. muon pTrel (genJet,genMuon), p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,5,NMuRelPtBins,muRelPtMin,muRelPtMax);
      
      
      }


    h_inclRecoJetEta_inclRecoJetPhi[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[j]->Sumw2();
    h_recoGenDr_flavor[j]->Sumw2();
    h_recoGenDpt_flavor[j]->Sumw2();
    for(int k = 0; k < NJetPtIndices; k++){
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][k]->Sumw2();
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][k]->Sumw2();
    }

    
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
  //em->regEventFilter(NeventFilters, eventFilters);

  
  TRandom *randomGenerator = new TRandom2();

  // jet-energy resolution fit function
  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,300);
  JER_fxn->SetParameter(0,1.26585e-01);
  JER_fxn->SetParameter(1,-9.72986e-01);
  JER_fxn->SetParameter(2,3.67352e-04);

  loadFitFxn_vz();
  loadFitFxn_jetPt();
  loadFitFxn_PYTHIA_JESb();
  loadFitFxn_PYTHIA_bJetNeutrinoEnergy();
  loadFitFxn_dR();
  loadFitFxn_hadronPtRel();
  // load muptrel fix fxns
  loadFitFxn_muptrel_C1J1();
  loadFitFxn_muptrel_C1J2();
  loadFitFxn_muptrel_C1J3();
  loadFitFxn_muptrel_C1J4();
  loadFitFxn_muptrel_C1J5();
  loadFitFxn_muptrel_C1J6();
  loadFitFxn_muptrel_C2J1();
  loadFitFxn_muptrel_C2J2();
  loadFitFxn_muptrel_C2J3();
  loadFitFxn_muptrel_C2J4();
  loadFitFxn_muptrel_C2J5();
  loadFitFxn_muptrel_C2J6();  

  TFile *f_neutrino_energy_fraction_map = TFile::Open("/eos/cms/store/group/phys_heavyions/cbennett/maps/neutrino_energy_fraction_map.root");
  TH2D *neutrino_energy_fraction_map;
  TH1D *neutrino_energy_fraction_map_proj;
  f_neutrino_energy_fraction_map->GetObject("neutrino_energy_fraction_map",neutrino_energy_fraction_map);

  TFile *f_neutrino_energy_map = TFile::Open("/eos/cms/store/group/phys_heavyions/cbennett/maps/neutrino_energy_map.root");
  TH2D *neutrino_energy_map;
  TH1D *neutrino_energy_map_proj;
  f_neutrino_energy_map->GetObject("neutrino_energy_map",neutrino_energy_map);

  TFile *f_neutrino_tag_fraction = TFile::Open("/eos/cms/store/group/phys_heavyions/cbennett/maps/neutrino_tag_fraction.root");
  TH1D *neutrino_tag_fraction;
  f_neutrino_tag_fraction->GetObject("neutrino_tag_fraction",neutrino_tag_fraction);
  
  //f_neutrino_energy_fraction_map->Close();

  cout << "map entries = " << neutrino_energy_fraction_map->GetEntries() << endl;


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

    double w_reweight_vz = 1.0;
    if(doVzReweight){
      w_reweight_vz = fitFxn_vz->Eval(em->vz);
    }
    

    double w_pthat = em->weight;

    double w = w_pthat * w_reweight_vz;

	
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};
    int matchFlag_nu[10] = {0,0,0,0,0,0,0,0,0,0};

    int matchFlagR[10] = {0,0,0,0,0,0,0,0,0,0};

    bool evtTriggerDecision = false;
    bool evtHasGoodJet = false;
    bool evtHasGoodMuonTaggedJet = false;
    bool evtHasGoodMuonTaggedJetTriggerOn = false;
    
    int triggerDecision_mu5 = em->HLT_HIL3Mu5_NHitQ10_v1;
    int triggerDecision_mu5_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl;

    int triggerDecision_mu7 = em->HLT_HIL3Mu7_v1;
    int triggerDecision_mu7_Prescl = em->HLT_HIL3Mu7_v1_Prescl;

    int triggerDecision_mu12 = em->HLT_HIL3Mu12_v1;
    int triggerDecision_mu12_Prescl = em->HLT_HIL3Mu12_v1_Prescl;


    // ******************************************
    // -------- mu5 configuration ---------------
    // if(triggerIsOn(triggerDecision_mu5,triggerDecision_mu5_Prescl) &&
    //    !triggerIsOn(triggerDecision_mu7,triggerDecision_mu7_Prescl) &&
    //    !triggerIsOn(triggerDecision_mu12,triggerDecision_mu12_Prescl)) evtTriggerDecision = true;
    // ******************************************
    
    // ******************************************
    // -------- mu7 configuration ---------------
    // if(triggerIsOn(triggerDecision_mu7,triggerDecision_mu7_Prescl)) evtTriggerDecision = true;
    // ******************************************
    
    // ******************************************
    // -------- mu12 configuration ---------------
    if(triggerIsOn(triggerDecision_mu12,triggerDecision_mu12_Prescl)) evtTriggerDecision = true;
    // ******************************************


    
    double leadingRecoJetPt = -1.0;
    double leadingGenJetPt = -1.0;

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
    if(doGenJetPthatFilter){
      if(!passesLeadingGenJetPthatFilter(leadingGenJetPt_i,em->pthat)) continue;
    }

    // quick recoJet loop to get leadingRecoJetPt
    double leadingRecoJetPt_i = 0.0;
    double leadingRecoJetEta_i = 0.0;
    double leadingRecoJetPhi_i = 0.0;
    int leadingRecoJetFlavor_i = -100;

    // find leadingRecoJet
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


    // RECO JET LOOP
    for(int i = 0; i < em->njet ; i++){

      // JET VARIABLES
		
      JEC.SetJetPT(em->rawpt[i]);
      JEC.SetJetEta(em->jeteta[i]);
      JEC.SetJetPhi(em->jetphi[i]);

      double recoJetPt_i = JEC.GetCorrectedPT();  // apply manual JEC
      double recoJetEta_i = em->jeteta[i]; // recoJetEta
      double recoJetPhi_i = em->jetphi[i]; // recoJetPhi
      double jetTrkMax_i = em->jetTrkMax[i];
      double nuPtShift_i = 0.0;

      double matchedGenJetPt_i = -999.0;
      double matchedGenJetEta_i = -999.0;
      double matchedGenJetPhi_i = -999.0;

      double recoJetRecoMuonPtRel_i = -999.0;
      double genJetGenMuonPtRel_i = -999.0;
      
      double w_jetPt = 1.0;
      
      JEU.SetJetPT(recoJetPt_i);
      JEU.SetJetEta(recoJetEta_i);
      JEU.SetJetPhi(recoJetPhi_i);

      // initialize 
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
      double muEta_i = -99.0;
      double muPhi_i = -99.0;
      double muJetDr_i = -1.0;

      // in-jet neutrino variables
      double nuPt_i = 0.0;
      double nuEta_i = -99.0;
      double nuPhi_i = -99.0;

      bool hasGenJetMatch = false;
      
      if(TMath::Abs(recoJetEta_i) > 1.6 || recoJetPt_i < jetPtCut) continue;
		
      int jetPtIndex = getJetPtBin(recoJetPt_i);

      if(recoJetPt_i > leadingRecoJetPt) leadingRecoJetPt = recoJetPt_i;

      int partonFlavor = em->partonFlavor[i];
      int hadronFlavor = em->hadronFlavor[i];
      int jetFlavorInt = partonFlavor;
      int bHadronNumber = em->bHadronNumber[i];

      if(fabs(jetFlavorInt) == 5 && bHadronNumber == 2) jetFlavorInt = 17; // 17 = bJet from gluon-splitting
  

      int genMuIndex = -1;
      int genNuIndex = -1;
      bool hasInclGenMuonTag = false;
      bool hasMatchedGenMuonTag = false;
      bool hasGenNeutrinoTag = false;

      bool hasInclRecoMuonTag = false;
      bool hasMatchedRecoMuonTag = false;

      double dR_recoGen_min = 100.0;
      double dPt_recoGen_min = 100.0;
      double dR_min;

      // look for a genJet match

      for(int j = 0; j < em->ngj ; j++){

	if(recoJetPt_i < jetPtCut) continue;	

	double genJetPt_j = em->genjetpt[j];  // genJetPt
	double genJetEta_j = em->genjeteta[j]; // genJetEta
	double genJetPhi_j = em->genjetphi[j]; // genJetPhi

	double dR_j = getDr(genJetEta_j,genJetPhi_j,recoJetEta_i,recoJetPhi_i);
	double dPt_j = recoJetPt_i/genJetPt_j;
			
	if(dR_j < dR_recoGen_min){
				
	  hasGenJetMatch = true;
	  matchedGenJetPt_i = genJetPt_j;
	  matchedGenJetEta_i = genJetEta_j;
	  matchedGenJetPhi_i = genJetPhi_j;
	  dR_recoGen_min = dR_j;
	  dPt_recoGen_min = dPt_j;

	}	

      }

      if(hasGenJetMatch){

	h_recoGenDr_flavor[0]->Fill(dR_recoGen_min,jetFlavorInt,w);
	if(jetPtIndex > 0) h_recoGenDr_flavor[jetPtIndex]->Fill(dR_recoGen_min,jetFlavorInt,w);
	h_recoGenDpt_flavor[0]->Fill(dPt_recoGen_min,jetFlavorInt,w);
	if(jetPtIndex > 0) h_recoGenDpt_flavor[jetPtIndex]->Fill(dPt_recoGen_min,jetFlavorInt,w);
	

      }


      if(!skipGenParticles){
	// look for a genNeutrino match
	for(int j = 0; j < em->gpptp->size(); j++){

	  if(TMath::Abs(em->gppdgIDp->at(j)) != 12 && TMath::Abs(em->gppdgIDp->at(j)) != 14 && TMath::Abs(em->gppdgIDp->at(j)) != 16 && TMath::Abs(em->gppdgIDp->at(j)) != 18) continue;

	  genNuIndex++;

	  if(matchFlag_nu[genNuIndex] == 1) continue; // skip if neutrino has been matched to a jet already

	  double genNeutrinoPt_j = em->gpptp->at(j);
	  double genNeutrinoEta_j = em->gpetap->at(j);
	  double genNeutrinoPhi_j = em->gpphip->at(j);
	  
	  if(genNeutrinoPt_j < nuPtCut || genNeutrinoPt_j > nuPtMaxCut || fabs(genNeutrinoEta_j) > 2.0) continue;  

	  if(getDr(genNeutrinoEta_j,genNeutrinoPhi_j,recoJetEta_i,recoJetPhi_i) < deltaRCut){

	    matchFlag_nu[genNuIndex] = 1;
	    hasGenNeutrinoTag = true;
	    nuPt_i = genNeutrinoPt_j;
	    nuEta_i = genNeutrinoEta_j;
	    nuPhi_i = genNeutrinoPhi_j;

	  } 

	} // end gen neutrino loop

	// NEUTRINO DIRECT ENERGY ADDITION CORRECTION 
	if(doNeutrinoEnergyAddition){
	  if(hasGenNeutrinoTag){
	    //cout << "old pT = " << recoJetPt_i << endl;
	    recoJetPt_i += nuPt_i; // add neutrino energy directly
	    //cout << "new pT = " << recoJetPt_i << endl;
	  }
	}

	// // OLGAS SUGGESTED METHOD
	double skipInclNeutrinoEnergySubtraction_diceRoll = 0.0;
	double smear_InclNeutrinoEnergySubtraction = 0.0;
	if(doInclNeutrinoEnergySubtraction){
	  skipInclNeutrinoEnergySubtraction_diceRoll = randomGenerator->Rndm(); // roll the dice to see if we alter the energy or not
	  if(skipInclNeutrinoEnergySubtraction_diceRoll > neutrino_tag_fraction->GetBinContent(neutrino_tag_fraction->FindBin(recoJetPt_i))) continue;
	  neutrino_energy_fraction_map_proj = (TH1D*) neutrino_energy_fraction_map->ProjectionX("neutrino_energy_fraction_map_proj", neutrino_energy_fraction_map->GetYaxis()->FindBin(recoJetPt_i),neutrino_energy_fraction_map->GetYaxis()->FindBin(recoJetPt_i)+1);
	  smear_InclNeutrinoEnergySubtraction = recoJetPt_i * neutrino_energy_fraction_map_proj->GetRandom();
	  //cout << "pT-pre-smear = " << recoJetPt_i << endl;
	  recoJetPt_i -= smear_InclNeutrinoEnergySubtraction;
	  //cout << "pT-post-nu-smear = " << recoJetPt_i << endl;
	  
	}
	
	// look for a genMuon match
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
	  double genMuonPtRel_j = -999.0;
	  double genMuonPtRel_matched_j = -999.0;


	  if(genMuonPt_j < muPtCut || genMuonPt_j > muPtMaxCut || fabs(genMuonEta_j) > 2.0) continue;                        

	  for(int l = 0; l < em->nMu; l++){

	    if(em->muPt->at(l) < muPtCut || fabs(em->muEta->at(l)) > 2.0) continue;
	 
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


	    if(isWDecayMuon(em->muPt->at(l),recoJetPt_i)) continue; // skip if "WDecay" muon (has majority of jet pt)	
			
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

	  if(getDr(genMuonEta_j,genMuonPhi_j,recoJetEta_i,recoJetPhi_i) < deltaRCut){
				
	    matchFlag[genMuIndex] = 1;
	    hasInclGenMuonTag = true;
	    
	    if(isMatchedGenMuon){
	      hasMatchedGenMuonTag = true;
	      if(hasGenJetMatch){
		recoJetRecoMuonPtRel_i = getPtRel(genMuonPt_matched_j,genMuonEta_matched_j,genMuonPhi_matched_j,recoJetPt_i,recoJetEta_i,recoJetPhi_i);
		genJetGenMuonPtRel_i   = getPtRel(genMuonPt_j,genMuonEta_j,genMuonPhi_j,matchedGenJetPt_i,matchedGenJetEta_i,matchedGenJetPhi_i);
	      }
	    }
	    

	  } 

	} // end genMuon loop
      }

	

      // look for recoMuon match		
		
      for(int m = 0; m < em->nMu; m++){

	if(matchFlagR[m] == 1) continue;

	if(em->muPt->at(m) < muPtCut || em->muPt->at(m) > muPtMaxCut  || fabs(em->muEta->at(m)) > 2.0) continue;
			 
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

	if(doBJetEnergyShift){
	  recoJetPt_i = recoJetPt_i * (1.0 / fitFxn_PYTHIA_JESb->Eval(recoJetPt_i));
	}
	
	double skipDoBJetNeutrinoEnergyShift_diceRoll = 0.0;
	if(doBJetNeutrinoEnergyShift){
          skipDoBJetNeutrinoEnergyShift_diceRoll = randomGenerator->Rndm(); // roll the dice to see if we alter the energy or not
          //cout << "dice roll = " << skipDoBJetNeutrinoEnergyShift_diceRoll << " | " << neutrino_tag_fraction->GetBinContent(neutrino_tag_fraction->FindBin(recoJetPt_i)) << endl;

	  if(skipDoBJetNeutrinoEnergyShift_diceRoll > neutrino_tag_fraction->GetBinContent(neutrino_tag_fraction->FindBin(recoJetPt_i))) continue;

	  neutrino_energy_map_proj = (TH1D*) neutrino_energy_map->ProjectionX("neutrino_energy_map_proj", neutrino_energy_map->GetYaxis()->FindBin(recoJetPt_i),neutrino_energy_map->GetYaxis()->FindBin(recoJetPt_i)+1);
          nuPtShift_i = neutrino_energy_map_proj->GetRandom();
          //cout << "pT-nu = " << nuPtShift_i << endl;
          //cout << "pT-nu-smear = " << recoJetPt_i * nuPtShift_i << endl;
          recoJetPt_i = recoJetPt_i + nuPtShift_i;
          //cout << "pT-post-nu-smear = " << recoJetPt_i << endl;
	}
	
	
	if(isWDecayMuon(em->muPt->at(m),recoJetPt_i)) continue; // skip if "WDecay" muon (has majority of jet pt)

	// match to genMuon
	bool isMatchedRecoMuon = false;

	if(!skipGenParticles){
	  for(int j = 0; j < em->gpptp->size(); j++){

	    //cout << "genID = " << em->gppdgIDp->at(j) << endl;
			
	    if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

	    if(em->gpptp->at(j) < muPtCut || em->gpptp->at(j) > muPtMaxCut || fabs(em->gpetap->at(j)) > trkEtaMax) continue;                    
		
	    if(getDr(em->muEta->at(m),em->muPhi->at(m),em->gpetap->at(j),em->gpphip->at(j)) < epsilon){

	      isMatchedRecoMuon = true;
			
	    }

	  }
	}
	// match to recoJets
	if(getDr(em->muEta->at(m),em->muPhi->at(m),recoJetEta_i,recoJetPhi_i) < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel_i = getPtRel(em->muPt->at(m),em->muEta->at(m),em->muPhi->at(m),recoJetPt_i,recoJetEta_i,recoJetPhi_i);
	  muPt_i = em->muPt->at(m);
	  muEta_i = em->muEta->at(m);
	  muPhi_i = em->muPhi->at(m);
	  muJetDr_i = getDr(em->muEta->at(m),em->muPhi->at(m),recoJetEta_i,recoJetPhi_i);
	  
	  if(isMatchedRecoMuon) hasMatchedRecoMuonTag = true;

	}
						


      }

      double w_jet = w;
      if(doJetPtReweight){
	if(hasInclRecoMuonTag && evtTriggerDecision) w_jet = w_pthat * w_reweight_vz * fitFxn_jetPt->Eval(recoJetPt_i);
      }

      if(doDRReweight){
	if(hasInclRecoMuonTag && evtTriggerDecision) w_jet = w_pthat * w_reweight_vz * fitFxn_jetPt->Eval(recoJetPt_i) * fitFxn_dR->Eval(muJetDr_i);
      }

      if(doHadronPtRelReweight){
	if(hasInclRecoMuonTag && evtTriggerDecision) w_jet = w_pthat * w_reweight_vz * fitFxn_jetPt->Eval(recoJetPt_i) * fitFxn_hadronPtRel->Eval(muPtRel_i);
      }
      
      double w_muptrel = w_jet;
      if(doMuPtRelReweight){
	if(hasInclRecoMuonTag && evtTriggerDecision && jetPtIndex > 0){

	  if(jetPtIndex == 1) w_muptrel = w_jet * fitFxn_muptrel_C1J1->Eval(muPtRel_i);
	  else if(jetPtIndex == 2) w_muptrel = w_jet * fitFxn_muptrel_C1J2->Eval(muPtRel_i);
	  else if(jetPtIndex == 3) w_muptrel = w_jet * fitFxn_muptrel_C1J3->Eval(muPtRel_i);
	  else if(jetPtIndex == 4) w_muptrel = w_jet * fitFxn_muptrel_C1J4->Eval(muPtRel_i);
	  else if(jetPtIndex == 5) w_muptrel = w_jet * fitFxn_muptrel_C1J5->Eval(muPtRel_i);
	  else if(jetPtIndex == 6) w_muptrel = w_jet * fitFxn_muptrel_C1J6->Eval(muPtRel_i);
	  else{};

	  // if(jetPtIndex == 1) w_muptrel = w_jet * fitFxn_muptrel_C2J1->Eval(muPtRel_i);
	  // else if(jetPtIndex == 2) w_muptrel = w_jet * fitFxn_muptrel_C2J2->Eval(muPtRel_i);
	  // else if(jetPtIndex == 3) w_muptrel = w_jet * fitFxn_muptrel_C2J3->Eval(muPtRel_i);
	  // else if(jetPtIndex == 4) w_muptrel = w_jet * fitFxn_muptrel_C2J4->Eval(muPtRel_i);
	  // else if(jetPtIndex == 5) w_muptrel = w_jet * fitFxn_muptrel_C2J5->Eval(muPtRel_i);
	  // else if(jetPtIndex == 6) w_muptrel = w_jet * fitFxn_muptrel_C2J6->Eval(muPtRel_i);
	  // else{};

	}
      }

      if(hasMatchedGenMuonTag && hasGenJetMatch){
	h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[0][0]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[0][0]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	// fill by flavor
	if(fabs(jetFlavorInt) == 5 || jetFlavorInt == 17){
	  h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[0][1]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	  h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[0][1]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	}
	else if(fabs(jetFlavorInt) == 4){
	  h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[0][2]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	  h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[0][2]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	}
	else if(fabs(jetFlavorInt) == 3){
	  h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[0][3]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	  h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[0][3]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	}
	else if(fabs(jetFlavorInt) == 1 || fabs(jetFlavorInt) == 2){
	  h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[0][4]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	  h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[0][4]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	}
	else if(jetFlavorInt == 21){
	  h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[0][5]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	  h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[0][5]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	}
	else if(jetFlavorInt == 0){
	  h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[0][6]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	  h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[0][6]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	}
	else{};
	
	if(jetPtIndex > 0){
	  h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[jetPtIndex][0]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	  h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[jetPtIndex][0]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);

	  // fill by flavor
	  if(fabs(jetFlavorInt) == 5 || jetFlavorInt == 17){
	    h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[jetPtIndex][1]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	    h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[jetPtIndex][1]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	  }
	  else if(fabs(jetFlavorInt) == 4){
	    h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[jetPtIndex][2]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	    h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[jetPtIndex][2]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	  }
	  else if(fabs(jetFlavorInt) == 3){
	    h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[jetPtIndex][3]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	    h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[jetPtIndex][3]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	  }
	  else if(fabs(jetFlavorInt) == 1 || fabs(jetFlavorInt) == 2){
	    h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[jetPtIndex][4]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	    h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[jetPtIndex][4]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	  }
	  else if(jetFlavorInt == 21){
	    h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[jetPtIndex][5]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	    h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[jetPtIndex][5]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	  }
	  else if(jetFlavorInt == 0){
	    h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[jetPtIndex][6]->Fill(genJetGenMuonPtRel_i,recoJetRecoMuonPtRel_i,w_jet);
	    h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[jetPtIndex][6]->Fill(recoJetRecoMuonPtRel_i/genJetGenMuonPtRel_i,genJetGenMuonPtRel_i,w_jet);
	  }
	  else{};

	  
	}
      }

      // Fill the jet histograms
      evtHasGoodJet = true;
      h_inclRecoJetPt_flavor->Fill(recoJetPt_i,jetFlavorInt,w_jet);
      h_inclRecoJetEta_flavor->Fill(recoJetEta_i,jetFlavorInt,w_jet);
      h_inclRecoJetPhi_flavor->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
      h_inclRecoJetPt_inclRecoJetEta->Fill(recoJetPt_i,recoJetEta_i,w_jet);
      h_inclRecoJetPt_inclRecoJetPhi->Fill(recoJetPt_i,recoJetPhi_i,w_jet);
      h_inclRecoJetEta_inclRecoJetPhi[0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
      if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi[jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);

      
		
      // FACTORIZATION CONFIG #1

      if(hasInclGenMuonTag){
		
	h_inclRecoJetPt_inclGenMuonTag_flavor->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	h_inclRecoJetEta_inclGenMuonTag_flavor->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	h_inclRecoJetPhi_inclGenMuonTag_flavor->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag->Fill(recoJetPt_i,recoJetPhi_i,w_jet);
	h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi_inclGenMuonTag[jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);

	if(hasGenNeutrinoTag){
	  h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_flavor->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_genNeutrinoPt->Fill(recoJetPt_i,nuPt_i,w_jet);
	}

      } 

      if(hasInclRecoMuonTag){

	evtHasGoodMuonTaggedJet = true;

	h_inclRecoJetPt_inclRecoMuonTag_flavor->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	h_inclRecoJetEta_inclRecoMuonTag_flavor->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	h_inclRecoJetPhi_inclRecoMuonTag_flavor->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag->Fill(recoJetPt_i,recoJetPhi_i,w_jet);
	h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);

	if(hasGenNeutrinoTag){
	  h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_flavor->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_genNeutrinoPt->Fill(recoJetPt_i,nuPt_i,w_jet);
	}
	
	
	if(evtTriggerDecision){

	  evtHasGoodMuonTaggedJetTriggerOn = true;
	  
	  h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	  h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn_flavor->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Fill(recoJetPt_i,recoJetPhi_i,w_jet);
	  	  
	  h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);

	  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Fill(muPtRel_i,recoJetPt_i,w_jet);
	  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Fill(muPt_i,recoJetPt_i,w_jet);
	  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Fill(muEta_i,recoJetPt_i,w_jet);
	  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Fill(muPhi_i,recoJetPt_i,w_jet);
	  h_muJetDr_recoJetPt_allJets->Fill(muJetDr_i,recoJetPt_i,w_jet);

	  if(fabs(jetFlavorInt) == 1){
	    h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Fill(muPtRel_i,recoJetPt_i,w_jet);
	    h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Fill(muPt_i,recoJetPt_i,w_jet);
	    h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Fill(muEta_i,recoJetPt_i,w_jet);
	    h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Fill(muPhi_i,recoJetPt_i,w_jet);
	    h_muJetDr_recoJetPt_dJets->Fill(muJetDr_i,recoJetPt_i,w_jet);
	  }
	  else if(fabs(jetFlavorInt) == 2){
	    h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Fill(muPtRel_i,recoJetPt_i,w_jet);
	    h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Fill(muPt_i,recoJetPt_i,w_jet);
	    h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Fill(muEta_i,recoJetPt_i,w_jet);
	    h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Fill(muPhi_i,recoJetPt_i,w_jet);
	    h_muJetDr_recoJetPt_uJets->Fill(muJetDr_i,recoJetPt_i,w_jet);
	  }
	  else if(fabs(jetFlavorInt) == 3){
	    h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Fill(muPtRel_i,recoJetPt_i,w_jet);
	    h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Fill(muPt_i,recoJetPt_i,w_jet);
	    h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Fill(muEta_i,recoJetPt_i,w_jet);
	    h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Fill(muPhi_i,recoJetPt_i,w_jet);
	    h_muJetDr_recoJetPt_sJets->Fill(muJetDr_i,recoJetPt_i,w_jet);
	  }
	  else if(fabs(jetFlavorInt) == 4){
	    h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Fill(muPtRel_i,recoJetPt_i,w_jet);
	    h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Fill(muPt_i,recoJetPt_i,w_jet);
	    h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Fill(muEta_i,recoJetPt_i,w_jet);
	    h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Fill(muPhi_i,recoJetPt_i,w_jet);
	    h_muJetDr_recoJetPt_cJets->Fill(muJetDr_i,recoJetPt_i,w_jet);
	  }
	  else if(fabs(jetFlavorInt) == 5){
	    h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Fill(muPtRel_i,recoJetPt_i,w_jet);
	    h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Fill(muPt_i,recoJetPt_i,w_jet);
	    h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Fill(muEta_i,recoJetPt_i,w_jet);
	    h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Fill(muPhi_i,recoJetPt_i,w_jet);
	    h_muJetDr_recoJetPt_bJets->Fill(muJetDr_i,recoJetPt_i,w_jet);
	  }
	  else if(jetFlavorInt == 17){
	    h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Fill(muPtRel_i,recoJetPt_i,w_jet);
	    h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Fill(muPt_i,recoJetPt_i,w_jet);
	    h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Fill(muEta_i,recoJetPt_i,w_jet);
	    h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Fill(muPhi_i,recoJetPt_i,w_jet);
	    h_muJetDr_recoJetPt_bGSJets->Fill(muJetDr_i,recoJetPt_i,w_jet);
	  }
	  else if(jetFlavorInt == 21){
	    h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Fill(muPtRel_i,recoJetPt_i,w_jet);
	    h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Fill(muPt_i,recoJetPt_i,w_jet);
	    h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Fill(muEta_i,recoJetPt_i,w_jet);
	    h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Fill(muPhi_i,recoJetPt_i,w_jet);
	    h_muJetDr_recoJetPt_gJets->Fill(muJetDr_i,recoJetPt_i,w_jet);
	  }
	  else if(jetFlavorInt == 0){
	    h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Fill(muPtRel_i,recoJetPt_i,w_jet);
	    h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Fill(muPt_i,recoJetPt_i,w_jet);
	    h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Fill(muEta_i,recoJetPt_i,w_jet);
	    h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Fill(muPhi_i,recoJetPt_i,w_jet);
	    h_muJetDr_recoJetPt_xJets->Fill(muJetDr_i,recoJetPt_i,w_jet);
	  }
	  else{};
	  
	  if(jetPtIndex > 0) {

	    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	    
	  }
	    
	} 

	if(hasMatchedRecoMuonTag){

	  h_inclRecoJetPt_matchedRecoMuonTag_flavor->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	  h_inclRecoJetEta_matchedRecoMuonTag_flavor->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPhi_matchedRecoMuonTag_flavor->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	  h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	  h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag->Fill(recoJetPt_i,recoJetPhi_i,w_jet);

	  h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	  if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag[jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);

	  if(evtTriggerDecision) {

	    h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor->Fill(recoJetPt_i,jetFlavorInt,w_jet);
	    h_inclRecoJetEta_matchedRecoMuonTag_triggerOn_flavor->Fill(recoJetEta_i,jetFlavorInt,w_jet);
	    h_inclRecoJetPhi_matchedRecoMuonTag_triggerOn_flavor->Fill(recoJetPhi_i,jetFlavorInt,w_jet);
	    h_inclRecoJetPt_inclRecoJetEta_matchedRecoMuonTag_triggerOn->Fill(recoJetPt_i,recoJetEta_i,w_jet);
	    h_inclRecoJetPt_inclRecoJetPhi_matchedRecoMuonTag_triggerOn->Fill(recoJetPt_i,recoJetPhi_i,w_jet);
	    h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[0]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	    if(jetPtIndex > 0) {
	      h_inclRecoJetEta_inclRecoJetPhi_matchedRecoMuonTag_triggerOn[jetPtIndex]->Fill(recoJetEta_i,recoJetPhi_i,w_jet);
	    }

	  }

	}

      }
	
      //}



      //}

    }
    // END recoJet LOOP

    // fill reco-based event histograms
    if(evtHasGoodJet && leadingRecoJetPt > 60){

      h_vz->Fill(em->vz,w);

      if(evtHasGoodMuonTaggedJet){

	h_vz_inclRecoMuonTag->Fill(em->vz,w);

	if(evtHasGoodMuonTaggedJetTriggerOn){

	  h_vz_inclRecoMuonTag_triggerOn->Fill(em->vz,w);
	  h_leadingRecoJetPt_inclRecoMuonTag_triggerOn_flavor->Fill(leadingRecoJetPt_i,leadingRecoJetFlavor_i,w);

	}

      }

    }
	
    if(leadingRecoJetPt > 0) h_recoJetPt_pthat->Fill(leadingRecoJetPt,em->pthat,w);

    // GEN JET LOOP
    for(int i = 0; i < em->ngj ; i++){

      // JET VARIABLES
      double genJetPt_i = em->genjetpt[i];  // recoJetPt
      double genJetEta_i = em->genjeteta[i]; // recoJetEta
      double genJetPhi_i = em->genjetphi[i]; // recoJetPhi

      double muPtRel_i = -1.0;

      // apply gen-pT smear
      double mu = 1.0;
      double sigma = 0.2;
      double smear = 0.0;

      
      

      
      if(TMath::Abs(genJetEta_i) > 1.6 || genJetPt_i < jetPtCut) continue;

      if(genJetPt_i > leadingGenJetPt) leadingGenJetPt = genJetPt_i;

      ////// get flavor from reco match
      bool hasRecoJetMatch = false;
      int recoJetFlavorFlag = 0;
      double minDr = 100.0;
      int jetFlavorInt = 19;
      int bHadronNumber = 0;

      
      for(int k = 0; k < em->njet; k++){
		
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
	jetFlavorInt = em->partonFlavor[recoJetFlavorFlag];
	bHadronNumber = em->bHadronNumber[recoJetFlavorFlag];
	if(fabs(jetFlavorInt) == 5 && bHadronNumber == 2) jetFlavorInt = 17;
	//cout << "jetFlavorInt = " << jetFlavorInt << endl;
      }

      if(apply_genJetPt_smear && (fabs(jetFlavorInt) == 5 || fabs(jetFlavorInt) == 17)){
	sigma = 0.663*JER_fxn->Eval(genJetPt_i); // apply a 20% smear
	smear = randomGenerator->Gaus(mu,sigma);
	//cout << "pre-smear-pT = " << genJetPt_i << endl;
	genJetPt_i = genJetPt_i * smear;
	//cout << "post-smear-pT = " << genJetPt_i << endl;
      }

		        
      int jetPtIndex = getJetPtBin(genJetPt_i);

  		

      int genMuIndex = -1;
      bool hasInclGenMuonTag = false;
      bool hasMatchedGenMuonTag = false;

      bool hasInclRecoMuonTag = false;
      bool hasMatchedRecoMuonTag = false;


      if(!skipGenParticles){
	// look for a genMuon match
	for(int j = 0; j < em->gpptp->size(); j++){

                        
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

	  if(genMuonPt_j < muPtCut || fabs(genMuonEta_j) > trkEtaMax) continue;                        

	  for(int l = 0; l < em->nMu; l++){

	    if(em->muPt->at(l) < muPtCut || em->muPt->at(l) > muPtMaxCut || fabs(em->muEta->at(l)) > 2.0) continue;
	  
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

	if(em->muPt->at(m) < muPtCut || em->muPt->at(m) > muPtMaxCut || fabs(em->muEta->at(m)) > 2.0) continue;

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

	for(int j = 0; j < em->gpptp->size(); j++){


	  //cout << "genID = " << em->gppdgIDp->at(j) << endl;
			
	  if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

	  if(em->gpptp->at(j) < muPtCut || fabs(em->gpetap->at(j)) > 2.0) continue;                        
		
	  if(getDr(em->muEta->at(m),em->muPhi->at(m),em->gpetap->at(j),em->gpphip->at(j)) < epsilon){

	    isMatchedRecoMuon = true;
			
	  }

	}

	// match to recoJets
	if(getDr(em->muEta->at(m),em->muPhi->at(m),genJetEta_i,genJetPhi_i) < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel_i = getPtRel(em->muPt->at(m),em->muEta->at(m),em->muPhi->at(m),genJetPt_i,genJetEta_i,genJetPhi_i);
				
	  if(isMatchedRecoMuon) hasMatchedRecoMuonTag = true;

	}
						


      }


      
      
      // Fill the jet histograms

      h_inclGenJetPt_flavor->Fill(genJetPt_i,jetFlavorInt,w);



      // FACTORIZATION CONFIG #1

      if(hasInclGenMuonTag){
		
	h_inclGenJetPt_inclGenMuonTag_flavor->Fill(genJetPt_i,jetFlavorInt,w);

      } 

      if(hasInclRecoMuonTag){

	h_inclGenJetPt_inclRecoMuonTag_flavor->Fill(genJetPt_i,jetFlavorInt,w);
			
	if(evtTriggerDecision){
	  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor->Fill(genJetPt_i,jetFlavorInt,w);
	  h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[0]->Fill(muPtRel_i,jetFlavorInt,w);
	  if(jetPtIndex > 0) h_muptrelGenJet_inclRecoMuonTag_triggerOn_flavor[jetPtIndex]->Fill(muPtRel_i,jetFlavorInt,w);
	} 

	if(hasMatchedRecoMuonTag){

	  h_inclGenJetPt_matchedRecoMuonTag_flavor->Fill(genJetPt_i,jetFlavorInt,w);

	  if(evtTriggerDecision) h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor->Fill(genJetPt_i,jetFlavorInt,w);


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
  h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_flavor->Write();
  h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_genNeutrinoPt->Write();
  h_inclRecoJetEta_inclGenMuonTag_flavor->Write();
  h_inclRecoJetPhi_inclGenMuonTag_flavor->Write();
  h_inclRecoJetPt_inclRecoJetEta_inclGenMuonTag->Write();
  h_inclRecoJetPt_inclRecoJetPhi_inclGenMuonTag->Write();

  h_inclRecoJetPt_inclRecoMuonTag_flavor->Write();
  h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_flavor->Write();
  h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_genNeutrinoPt->Write();
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

  h_leadingRecoJetPt_inclRecoMuonTag_triggerOn_flavor->Write();

  h_inclGenJetPt_flavor->Write();
  h_inclGenJetPt_inclGenMuonTag_flavor->Write();
  h_inclGenJetPt_inclRecoMuonTag_flavor->Write();
  h_inclGenJetPt_inclRecoMuonTag_triggerOn_flavor->Write();
  h_inclGenJetPt_matchedRecoMuonTag_flavor->Write();
  h_inclGenJetPt_matchedRecoMuonTag_triggerOn_flavor->Write();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Write();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Write();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Write();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_allJets->Write();
  h_muJetDr_recoJetPt_allJets->Write();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Write();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Write();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Write();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_uJets->Write();
  h_muJetDr_recoJetPt_uJets->Write();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Write();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Write();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Write();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_dJets->Write();
  h_muJetDr_recoJetPt_dJets->Write();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Write();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Write();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Write();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_sJets->Write();
  h_muJetDr_recoJetPt_sJets->Write();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Write();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Write();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Write();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_cJets->Write();
  h_muJetDr_recoJetPt_cJets->Write();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Write();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Write();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Write();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bJets->Write();
  h_muJetDr_recoJetPt_bJets->Write();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Write();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Write();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Write();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets->Write();
  h_muJetDr_recoJetPt_bGSJets->Write();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Write();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Write();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Write();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_gJets->Write();
  h_muJetDr_recoJetPt_gJets->Write();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Write();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Write();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Write();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn_xJets->Write();
  h_muJetDr_recoJetPt_xJets->Write();
  

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

    h_recoGenDr_flavor[j]->Write();
    h_recoGenDpt_flavor[j]->Write();

    for(int k = 0; k < NJetPtIndices; k++){
      h_muptrelGenJetGenMuon_muptrelRecoJetRecoMuon[j][k]->Write();
      h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon[j][k]->Write();
    }

    h_muJetDr_flavor[j]->Write();
    
  }


  h_recoJetPt_pthat->Write();	
  h_genJetPt_pthat->Write();	


  wf->Close();
  return;
  // END WRITE



}







