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
// JERCorrection params
#include "../../../headers/fitParameters/JERCorrectionParams_PYTHIA_mu12.h"
TF1 *fitFxn_PYTHIA_JERCorrection;
// JER-correction function
#include "../../../headers/fitFunctions/fitFxn_PYTHIA_JERCorrection.h"
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
#include "../../../headers/introductions/printIntroduction_pp_scan_V3p7.h"
// analysis config
#include "../../../headers/config/config_pp.h"
//#include "../../../headers/config/config_pp_SingleMuon.h"
//#include "../../../headers/config/config_pp_MB.h"
// read config
#include "../../../headers/config/readConfig.h"
// dataset naming functions
#include "../../../headers/functions/getDatasetName/getDatasetName_pp.h"
#include "../../../headers/functions/getInputFileName/getInputFileName_pp.h"
#include "../../../headers/functions/configureOutputDatasetName/configureOutputDatasetName_pp.h"





// initialize histograms
// ~~~~~~~~~ event variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// -----------------------------------------events w/ incl. reco jet -------
TH1D *h_vz;
TH1D *h_hiBin;
// ----------------------- events w/ incl. reco jet + incl. reco muon tag --
TH1D *h_vz_inclRecoMuonTag;
TH1D *h_hiBin_inclRecoMuonTag;
// ---------- events w/ incl. reco jet + incl. reco muon tag + trigger on --
TH1D *h_vz_inclRecoMuonTag_triggerOn;
TH1D *h_hiBin_inclRecoMuonTag_triggerOn;
// ~~~~~~~~~ jet variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ----------------------------------------- incl. reco jets --------------
TH1D *h_inclRecoJetPt;
TH1D *h_inclRecoJetEta;
TH1D *h_inclRecoJetPhi;
TH2D *h_inclRecoJetPt_inclRecoJetEta;
TH2D *h_inclRecoJetPt_inclRecoJetPhi;
TH2D *h_inclRecoJetEta_inclRecoJetPhi[NJetPtIndices];
// ------------------------------ incl. reco jets + incl. reco muon tag ----
TH1D *h_inclRecoJetPt_inclRecoMuonTag;
TH1D *h_inclRecoJetEta_inclRecoMuonTag;
TH1D *h_inclRecoJetPhi_inclRecoMuonTag;
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag;
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag;
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[NJetPtIndices];
// ------------------ incl. reco jets + incl. reco muon tag + trigger on ----
TH1D *h_inclRecoJetPt_inclRecoMuonTag_triggerOn;
TH1D *h_inclRecoJetEta_inclRecoMuonTag_triggerOn;
TH1D *h_inclRecoJetPhi_inclRecoMuonTag_triggerOn;
TH2D *h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn;
TH2D *h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn;
//TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[NJetPtIndices];
// ~~~~~~~~~ muon variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D *h_inclMuPt;
TH2D *h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn;
TH2D *h_mupt_recoJetPt_inclRecoMuonTag_triggerOn;
TH2D *h_mueta_recoJetPt_inclRecoMuonTag_triggerOn;
TH2D *h_muphi_recoJetPt_inclRecoMuonTag_triggerOn;
TH2D *h_muJetDr_recoJetPt;



///////////////////////  start the program
void pp_scan(int group = 1){


  TString inputDataset = "";
  TString inputFileName = "";

  inputDataset = getDatasetName(doSingleMuonSample,
				doMinBiasSample,
				doHighEGJetSample);

  inputFileName = getInputFileName(doSingleMuonSample,
				   doMinBiasSample,
				   doHighEGJetSample);

  TString input = Form("%s%s_%i.root",inputDataset.Data(),inputFileName.Data(),group);
  std::cout << "input dataset = " << input << std::endl;
  TString outputBaseDir = "/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/";

  TString outputDatasetName = "";
  outputDatasetName = configureOutputDatasetName(doSingleMuonSample,
						 doMinBiasSample,
						 doHighEGJetSample,
						 applyJet60Trigger,
						 applyJet80Trigger,
						 doJetTrkMaxFilter,
						 doEtaPhiMask,
						 doJESCorrection,
						 doBJetNeutrinoEnergyShift,
						 doJERCorrection,
						 apply_JER_smear,
						 apply_JEU_shift_up,
						 apply_JEU_shift_down);

  TString output = Form("%s%s/pp_scan_output_%i.root",outputBaseDir.Data(),outputDatasetName.Data(),group);

  std::cout << "output dataset = " << output << std::endl;

  //TString input = Form("../../../rootFiles/skimmingOutput/pp/output/pp_skim_output_%i.root",group);
  //TString input = "../../../rootFiles/skimmingOutput/pp/test/testFile.root";


  // TString input = Form("../../../rootFiles/skimmingOutput/pp/output_MinBias/pp_MinBias_skim_output_%i.root",group);
  // TString output = Form("output_SingleMuon_mu7/pp_MinBias_scan_output_%i.root",group);

  // TString input = Form("/eos/user/c/cbennett/skims/output_pp_SingleMuon/pp_SingleMuon_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_pp_SingleMuon_mu12_tight_pTmu-14_projectableTemplates_2025-06-30/pp_SingleMuon_scan_output_%i.root",group);

  // TString input = Form("/eos/user/c/cbennett/skims/output_skims_pp_HIZeroBias1/pp_MinBias_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_pp_MinBias_mu12_tight_pTmu-14_2025-06-30/pp_MinBias_scan_output_%i.root",group);

  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_pp_HighEGJet/pp_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_pp_HighEGJet_mu12_tight_pTmu-14_2025-10-13_applyJEUShiftDown/pp_HighEGJet_scan_output_%i.root",group);


  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_DATA_L2Relative_AK4PF.txt"); // L2Relative correction
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_DATA_L2L3Residual_AK4PF.txt"); // L2L3Residual correction
  JetCorrector JEC(Files);
  JetUncertainty JEU("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_Uncertainty_AK4PF.txt");
  /// >>>>>>>>>>>>>>> print out some info
  printIntroduction_pp_scan_V3p7();
  readConfig();
  // >>>>>>>>>>>>>>>> define histograms
  // ---------------------- event histograms --------------------------------
  // ------------ hiBin ---------------
  h_hiBin = new TH1D("h_hiBin","hiBin, events with inclRecoJet",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_inclRecoMuonTag = new TH1D("h_hiBin_inclRecoMuonTag","hiBin, events with inclRecoJet-inclRecoMuonTag",NhiBinBins,hiBinMin,hiBinMax);
  h_hiBin_inclRecoMuonTag_triggerOn = new TH1D("h_hiBin_inclRecoMuonTag_triggerOn","hiBin, events with inclRecoJet-inclRecoMuonTag-triggerOn",NhiBinBins,hiBinMin,hiBinMax);
  // ------------ vz ------------------
  h_vz = new TH1D("h_vz","vz, events with inclRecoJet",NVzBins,vzMin,vzMax);
  h_vz_inclRecoMuonTag = new TH1D("h_vz_inclRecoMuonTag","vz, events with inclRecoJet-inclRecoMuonTag",NVzBins,vzMin,vzMax);
  h_vz_inclRecoMuonTag_triggerOn = new TH1D("h_vz_inclRecoMuonTag_triggerOn","vz, events with inclRecoJet-inclRecoMuonTag-triggerOn",NVzBins,vzMin,vzMax);
  // ----------------------------------------- incl. reco jets --------------
  h_inclRecoJetPt = new TH1D("h_inclRecoJetPt","incl. reco p_{T}^{jet}",NPtBins,ptMin,ptMax);
  h_inclRecoJetEta = new TH1D("h_inclRecoJetEta","incl. reco #eta^{jet}",NEtaBins,etaMin,etaMax);
  h_inclRecoJetPhi = new TH1D("h_inclRecoJetPhi","incl. reco #phi^{jet}",NPhiBins,phiMin,phiMax);
  h_inclRecoJetPt_inclRecoJetEta = new TH2D("h_inclRecoJetPt_inclRecoJetEta","incl. reco #eta^{jet} vs. incl. reco p_{T}^{jet}",NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
  h_inclRecoJetPt_inclRecoJetPhi = new TH2D("h_inclRecoJetPt_inclRecoJetPhi","incl. reco #phi^{jet} vs. incl. reco p_{T}^{jet}",NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
  // ------------------------------ incl. reco jets + incl. reco muon tag ----
  h_inclRecoJetPt_inclRecoMuonTag = new TH1D("h_inclRecoJetPt_inclRecoMuonTag","incl. reco p_{T}^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax);
  h_inclRecoJetEta_inclRecoMuonTag = new TH1D("h_inclRecoJetEta_inclRecoMuonTag","incl. reco #eta^{jet}, tagged with incl. reco muon",NEtaBins,etaMin,etaMax);
  h_inclRecoJetPhi_inclRecoMuonTag = new TH1D("h_inclRecoJetPhi_inclRecoMuonTag","incl. reco #phi^{jet}, tagged with incl. reco muon",NPhiBins,phiMin,phiMax);
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag = new TH2D("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag","incl. reco #eta^{jet} vs. incl. reco p_{T}^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag = new TH2D("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag","incl. reco #phi^{jet} vs. incl. reco p_{T}^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
  // ---------- events w/ incl. reco jet + incl. reco muon tag + trigger on --
  h_inclRecoJetPt_inclRecoMuonTag_triggerOn = new TH1D("h_inclRecoJetPt_inclRecoMuonTag_triggerOn","incl. reco p_{T}^{jet}, tagged with incl. reco muon, trigger ON",NPtBins,ptMin,ptMax);
  h_inclRecoJetEta_inclRecoMuonTag_triggerOn = new TH1D("h_inclRecoJetEta_inclRecoMuonTag_triggerOn","incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON",NEtaBins,etaMin,etaMax);
  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn = new TH1D("h_inclRecoJetPhi_inclRecoMuonTag_triggerOn","incl. reco #phi^{jet}, tagged with incl. reco muon, trigger ON",NPhiBins,phiMin,phiMax);
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn = new TH2D("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn","incl. reco #eta^{jet} vs. incl. reco p_{T}^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax,NEtaBins,etaMin,etaMax);
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn = new TH2D("h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn","incl. reco #phi^{jet} vs. incl. reco p_{T}^{jet}, tagged with incl. reco muon",NPtBins,ptMin,ptMax,NPhiBins,phiMin,phiMax);
  h_inclMuPt = new TH1D("h_inclMuPt","incl. muon p_{T}; muon p_{T}; Entries",NMuPtBins,muPtMin,muPtMax);


  // muon-based 2d histograms
  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn = new TH2D("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn","muon #it{p}_{T}^{rel} vs jet #it{p}_{T}",NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn = new TH2D("h_mupt_recoJetPt_inclRecoMuonTag_triggerOn","muon #it{p}_{T} vs jet #it{p}_{T}",NMuPtBins,muPtMin,muPtMax,NPtBins,ptMin,ptMax);
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn = new TH2D("h_mueta_recoJetPt_inclRecoMuonTag_triggerOn","muon #it{#eta} vs jet #it{p}_{T}",NTrkEtaBins,trkEtaMin,trkEtaMax,NPtBins,ptMin,ptMax);
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn = new TH2D("h_muphi_recoJetPt_inclRecoMuonTag_triggerOn","muon #it{#phi} vs jet #it{p}_{T}",NPhiBins,phiMin,phiMax,NPtBins,ptMin,ptMax);
  h_muJetDr_recoJetPt = new TH2D("h_muJetDr_recoJetPt","#it{#Delta r}(muon,jet) vs jet #it{p}_{T}",NdRBins,dRBinMin,dRBinMax,NPtBins,ptMin,ptMax);
  

  // Sumw2 commands
  h_hiBin->Sumw2();
  h_hiBin_inclRecoMuonTag->Sumw2();
  h_hiBin_inclRecoMuonTag_triggerOn->Sumw2();
  h_vz->Sumw2();
  h_vz_inclRecoMuonTag->Sumw2();
  h_vz_inclRecoMuonTag_triggerOn->Sumw2();

  h_inclRecoJetPt->Sumw2();
  h_inclRecoJetEta->Sumw2();
  h_inclRecoJetPhi->Sumw2();
  h_inclRecoJetPt_inclRecoJetEta->Sumw2();
  h_inclRecoJetPt_inclRecoJetPhi->Sumw2();
  
  h_inclRecoJetPt_inclRecoMuonTag->Sumw2();
  h_inclRecoJetEta_inclRecoMuonTag->Sumw2();
  h_inclRecoJetPhi_inclRecoMuonTag->Sumw2();
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag->Sumw2();
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag->Sumw2();

  h_inclRecoJetPt_inclRecoMuonTag_triggerOn->Sumw2();
  h_inclRecoJetEta_inclRecoMuonTag_triggerOn->Sumw2();
  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Sumw2();
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn->Sumw2();
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Sumw2();
  h_inclMuPt->Sumw2();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn->Sumw2();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn->Sumw2();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn->Sumw2();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn->Sumw2();
  h_muJetDr_recoJetPt->Sumw2();
				 
				 





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
  cout << "	Variables initilized!" << endl << endl ;
  int NEvents = em->evtTree->GetEntries();
  cout << "	Number of events = " << NEvents << endl;


  // define event filters
  if(doSingleMuonSample || doHighEGJetSample){
    em->regEventFilter(NeventFilters_SingleMuon, eventFilters_SingleMuon);
  }

  else if(doMinBiasSample){
    em->regEventFilter(NeventFilters_MinBias, eventFilters_MinBias);
  }

  loadFitFxn_PYTHIA_JERCorrection();
  
  TRandom *randomGenerator = new TRandom2();

  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,300);
  JER_fxn->SetParameter(0,1.26585e-01);
  JER_fxn->SetParameter(1,-9.72986e-01);
  JER_fxn->SetParameter(2,3.67352e-04);
  
  
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

  // define JES correction function
  TF1 *fxn_JES_Corr = new TF1("fxn_JES_Corr","[0] + [1]*x",80,500);
  fxn_JES_Corr->SetParameter(0,0.907383);
  fxn_JES_Corr->SetParameter(1,0.000114088);
  
  
  // event loop
  int evi_frac = 0;
  for(int evi = 0; evi < NEvents; evi++){

    if(evi == 0) cout << "Processing events..." << endl;

    em->getEvent(evi); // load event info from eventMap
    // em->muonTriggerTree->GetEntry(evi);
    // em->jetEvtTree->GetEntry(evi);
    // if(em->njet > 0){
    //   em->recoJetTree->GetEntry(evi);
    // }
    // em->muonEvtTree->GetEntry(evi);
    // if(em->nMu > 0){
    //   em->muonTree->GetEntry(evi);
    // }

    if((100*evi / NEvents) % 5 == 0 && (100*evi / NEvents) > evi_frac){

      cout << "evt frac: " << evi_frac << "%" << endl;

    }

    evi_frac = 100*evi / NEvents;

    // global event cuts
    if(fabs(em->vz) > 15.0) continue;

    // event filters
    if(em->checkEventFilter()) continue; // comment out for local skims (already applied)

    // apply jet-trigger if activated in config
    if(applyJet60Trigger){
      if(em->HLT_HIAK4PFJet60_v1 == 0) continue;
    }
    if(applyJet80Trigger){
      if(em->HLT_HIAK4PFJet80_v1 == 0) continue;
    }

    
    // In data, event weight = 1
    double w = 1.0;
   
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};

    int matchFlagR[10] = {0,0,0,0,0,0,0,0,0,0};

    bool evtTriggerDecision = false;

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
    //if(triggerIsOn(triggerDecision_mu7,triggerDecision_mu7_Prescl)) evtTriggerDecision = true;
    // ******************************************
    
    // ******************************************
    // -------- mu12 configuration ---------------
    if(triggerIsOn(triggerDecision_mu12,triggerDecision_mu12_Prescl)) evtTriggerDecision = true;
    // ******************************************
   


    // set the weight equal to the "gluing" parameter
   
    // if(triggerDecision_Prescl == 0){ continue;}
    // else if(triggerDecision_Prescl == 1){
    //   w = 1.0 ;
    // }
    // else if(triggerDecision_Prescl == 3){
    //   w = 1.0 / 6.04088 ;
    // }
    // else if(triggerDecision_Prescl == 5){
    //   w = 1.0 / 8.68813 ;
    // }
    // else{ continue ;}
 
    double w_trig = w;

   
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

      //cout << "muon(" << m << ") pT = " << muPt_m << endl;
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
    //cout << "event " << evi << endl;
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
      double muJetDr_i = -99.0;

      if(doJetTrkMaxFilter){
	if(!passesJetTrkMaxFilter(jetTrkMax_i,x)) continue;
      }
     
      if(doEtaPhiMask){
	if(etaPhiMask(y,z)) continue;
      }

      if(doJESCorrection){
	x = x * fxn_JES_Corr->Eval(x);
      }


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
      
      double skipDoBJetNeutrinoEnergyShift_diceRoll = 0.0;
      double smear_doBJetNeutrinoEnergyShift = 0.0;
      if(doBJetNeutrinoEnergyShift){
	//if(doBJetNeutrinoEnergyShift && hasRecoJetMuon){
	skipDoBJetNeutrinoEnergyShift_diceRoll = randomGenerator->Rndm();
	if(skipDoBJetNeutrinoEnergyShift_diceRoll > neutrino_tag_fraction->GetBinContent(neutrino_tag_fraction->FindBin(x))) continue;
	neutrino_energy_map_proj = (TH1D*) neutrino_energy_map->ProjectionX("neutrino_energy_map_proj", neutrino_energy_map->GetYaxis()->FindBin(x),neutrino_energy_map->GetYaxis()->FindBin(x)+1);
	smear_doBJetNeutrinoEnergyShift = neutrino_energy_map_proj->GetRandom();
	x += smear_doBJetNeutrinoEnergyShift;
      }

      double mu_JERCorrection = 1.0;
      double sigma_JERCorrection = 0.2;
      double smear_JERCorrection = 0.0; // smeared pT
      double k_JERCorrection = 0.0; // smearing parameter
      if(doJERCorrection){
	k_JERCorrection = TMath::Sqrt(fitFxn_PYTHIA_JERCorrection->Eval(x)*fitFxn_PYTHIA_JERCorrection->Eval(x) - 1.);
	sigma_JERCorrection = k_JERCorrection*JER_fxn->Eval(x);
	smear_JERCorrection = randomGenerator->Gaus(mu_JERCorrection,sigma_JERCorrection);
	x = x * smear_JERCorrection;
      }

      
      //cout << "x" << endl;
     
      double muPtRel = -1.0;
      double muPt = -1.0;
      double muEta = -99.0;
      double muPhi = -99.0;
      double muDr = -99.0;

      bool hasInclRecoMuonTag = false;
		
      // jet kinematic cuts
      if(TMath::Abs(y) > etaMax || x < jetPtCut) continue;

      eventHasGoodJet = true;
      if(x > leadingRecoJetPt) leadingRecoJetPt = x;
  
      int jetPtIndex = getJetPtBin(x);

      // look for recoMuon match to recoJet		
      for(int m = 0; m < em->nMu; m++){

	double muPt_m = em->muPt->at(m);
	double muEta_m = em->muEta->at(m);
	double muPhi_m = em->muPhi->at(m);
	// skip if muon has already been matched to a jet in this event
	if(matchFlagR[m] == 1) continue;
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
	// 			     em->muInnerD0->at(m),
	// 			     em->muInnerDz->at(m),
	// 			     em->muPixelHits->at(m),
	// 			     em->muIsTracker->at(m),
	// 			     em->muIsGlobal->at(m),
	// 			     em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     


	if(isWDecayMuon(muPt_m,x)) continue; // skip if "WDecay" muon (has majority of jet pt) 

	// match to recoJets
	if(getDr(muEta_m,muPhi_m,y,z) < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel = getPtRel(muPt_m,muEta_m,muPhi_m,x,y,z);
	  muPt = muPt_m;
	  muEta = muEta_m;
	  muPhi = muPhi_m;
	  muJetDr_i = getDr(muEta_m,muPhi_m,y,z);

	}

      }
     
     
      // Fill the jet/event histograms
      h_inclRecoJetPt->Fill(x,w);
      h_inclRecoJetEta->Fill(y,w);
      h_inclRecoJetPhi->Fill(z,w);
      h_inclRecoJetPt_inclRecoJetEta->Fill(x,y,w);
      h_inclRecoJetPt_inclRecoJetPhi->Fill(x,z,w);
     
      if(hasInclRecoMuonTag){

	eventHasInclRecoMuonTag = true;

	h_inclRecoJetPt_inclRecoMuonTag->Fill(x,w);
	h_inclRecoJetEta_inclRecoMuonTag->Fill(y,w);
	h_inclRecoJetPhi_inclRecoMuonTag->Fill(z,w);
	h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag->Fill(x,y,w);
	h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag->Fill(x,z,w);

       
	if(evtTriggerDecision){
	 
	  eventHasInclRecoMuonTagPlusTrigger = true;

	  h_inclRecoJetPt_inclRecoMuonTag_triggerOn->Fill(x,w_trig);
	  h_inclRecoJetEta_inclRecoMuonTag_triggerOn->Fill(y,w_trig);
	  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Fill(z,w_trig);
	  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn->Fill(x,y,w_trig);
	  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Fill(x,z,w_trig);
	 
	  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn->Fill(muPtRel,x,w_trig);
	  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn->Fill(muPt,x,w_trig);
	  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn->Fill(muEta,x,w_trig);
	  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn->Fill(muPhi,x,w_trig);
	  h_muJetDr_recoJetPt->Fill(muJetDr_i,x,w_trig);

	  
	} 

      }

    }
    // END recoJet LOOP

    h_vz->Fill(em->vz,w);
    
    if(eventHasGoodJet && leadingRecoJetPt > 80){

      h_hiBin->Fill(em->hiBin,w);
      
      if(eventHasInclRecoMuonTag){

	h_vz_inclRecoMuonTag->Fill(em->vz,w);
	h_hiBin_inclRecoMuonTag->Fill(em->hiBin,w);

	if(eventHasInclRecoMuonTagPlusTrigger){

	  h_vz_inclRecoMuonTag_triggerOn->Fill(em->vz,w_trig);
	  h_hiBin_inclRecoMuonTag_triggerOn->Fill(em->hiBin,w_trig);
	 
	}
       
      }

    }


   

  } // end event loop


 
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  h_hiBin->Write();
  h_hiBin_inclRecoMuonTag->Write();
  h_hiBin_inclRecoMuonTag_triggerOn->Write();

  h_vz->Write();
  h_vz_inclRecoMuonTag->Write();
  h_vz_inclRecoMuonTag_triggerOn->Write();
   
  h_inclRecoJetPt->Write();
  h_inclRecoJetEta->Write();
  h_inclRecoJetPhi->Write();
  h_inclRecoJetPt_inclRecoJetEta->Write();
  h_inclRecoJetPt_inclRecoJetPhi->Write();
   
  h_inclRecoJetPt_inclRecoMuonTag->Write();
  h_inclRecoJetEta_inclRecoMuonTag->Write();
  h_inclRecoJetPhi_inclRecoMuonTag->Write();
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag->Write();
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag->Write();
   
  h_inclRecoJetPt_inclRecoMuonTag_triggerOn->Write();
  h_inclRecoJetEta_inclRecoMuonTag_triggerOn->Write();
  h_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Write();
  h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn->Write();
  h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Write();
  h_inclMuPt->Write();

  h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn->Write();
  h_mupt_recoJetPt_inclRecoMuonTag_triggerOn->Write();
  h_mueta_recoJetPt_inclRecoMuonTag_triggerOn->Write();
  h_muphi_recoJetPt_inclRecoMuonTag_triggerOn->Write();
  h_muJetDr_recoJetPt->Write();

  wf->Close();
  return;
  // END WRITE

}
