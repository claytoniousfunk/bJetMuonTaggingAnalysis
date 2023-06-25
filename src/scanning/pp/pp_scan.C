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
// triggerIsOn function
#include "../../../headers/functions/triggerIsOn.h"
// pthat filter function
#include "../../../headers/functions/passesLeadingGenJetPthatFilter.h"
// print introduction
#include "../../../headers/introductions/printIntroduction_pp_scan_V3p7.h"
// analysis config
#include "../../../headers/config/config_pp_SingleMuon.h"
// read config
#include "../../../headers/config/readConfig.h"
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
TH2D *h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[NJetPtIndices];
// ~~~~~~~~~ muon variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D *h_muptrel_inclRecoMuonTag_triggerOn[NJetPtIndices];
TH1D *h_mupt_inclRecoMuonTag_triggerOn[NJetPtIndices];
TH1D *h_mueta_inclRecoMuonTag_triggerOn[NJetPtIndices];
TH1D *h_muphi_inclRecoMuonTag_triggerOn[NJetPtIndices];
///////////////////////  start the program
void pp_scan(TString input = "root://cmsxrootd.fnal.gov//store/user/cbennett/pp_SingleMuon_L3Mu5_18Dec22/SingleMuon/crab_pp_SingleMuon_L3Mu5_18Dec22/221217_212444/0000/HiForestAOD_10.root", TString output = "out.root"){
  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Fall17_17Nov2017F_V6_DATA_L2Relative_AK4PF.txt"); // L2Relative correction
  Files.push_back("../../../JetEnergyCorrections/Fall17_17Nov2017F_V6_DATA_L2L3Residual_AK4PF.txt"); // L2L3Residual correction
  JetCorrector JEC(Files);
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
  
  // loop through jet pt indices
  for(int j = 0; j < NJetPtIndices; j++){
    if(j == 0){
      h_muptrel_inclRecoMuonTag_triggerOn[j] = new TH1D(Form("h_muptrel_inclRecoMuonTag_triggerOn_J%i",j),Form("muon p_{T}^{rel}, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_mupt_inclRecoMuonTag_triggerOn[j] = new TH1D(Form("h_mupt_inclRecoMuonTag_triggerOn_J%i",j),Form("muon p_{T}, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuPtBins,muPtMin,muPtMax);
      h_mueta_inclRecoMuonTag_triggerOn[j] = new TH1D(Form("h_mueta_inclRecoMuonTag_triggerOn_J%i",j),Form("muon #eta, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
      h_muphi_inclRecoMuonTag_triggerOn[j] = new TH1D(Form("h_muphi_inclRecoMuonTag_triggerOn_J%i",j),Form("muon #phi, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_J%i",j),Form("incl. reco #phi^{jet} vs incl. reco #eta^{jet}, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecobJetPhi_inclRecoMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs incl. reco #eta^{jet}, tagged with incl. reco muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j] = new TH2D(Form("h_inclRecoJetEta_inclRecobJetPhi_inclRecoMuonTag_triggerOn_J%i",j),Form("incl. reco #phi^{jet} vs incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
    }
    else{
      h_muptrel_inclRecoMuonTag_triggerOn[j] = new TH1D(Form("h_muptrel_inclRecoMuonTag_triggerOn_J%i",j),Form("muon p_{T}^{rel}, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax);
      h_mupt_inclRecoMuonTag_triggerOn[j] = new TH1D(Form("h_mupt_inclRecoMuonTag_triggerOn_J%i",j),Form("muon p_{T}, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuPtBins,muPtMin,muPtMax);
      h_mueta_inclRecoMuonTag_triggerOn[j] = new TH1D(Form("h_mueta_inclRecoMuonTag_triggerOn_J%i",j),Form("muon #eta, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax);
      h_muphi_inclRecoMuonTag_triggerOn[j] = new TH1D(Form("h_muphi_inclRecoMuonTag_triggerOn_J%i",j),Form("muon #phi, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi[j] = new TH2D(Form("h_inclRecoJetEta_inclRecoJetPhi_J%i",j),Form("incl. reco #phi^{jet} vs incl. reco #eta^{jet}, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j] = new TH2D(Form("h_inclRecoJetEta_inclRecobJetPhi_inclRecoMuonTag_J%i",j),Form("incl. reco #phi^{jet} vs incl. reco #eta^{jet}, tagged with incl. reco muon, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
      h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j] = new TH2D(Form("h_inclRecoJetEta_inclRecobJetPhi_inclRecoMuonTag_triggerOn_J%i",j),Form("incl. reco #phi^{jet} vs incl. reco #eta^{jet}, tagged with incl. reco muon, trigger ON, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NEtaBins,etaMin,etaMax,NPhiBins,phiMin,phiMax);
    }
    h_muptrel_inclRecoMuonTag_triggerOn[j]->Sumw2();
    h_mupt_inclRecoMuonTag_triggerOn[j]->Sumw2();
    h_mueta_inclRecoMuonTag_triggerOn[j]->Sumw2();
    h_muphi_inclRecoMuonTag_triggerOn[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j]->Sumw2();
    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j]->Sumw2();
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

  
 // event loop
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

   bool evtTriggerDecision = false;

   int triggerDecision = em->HLT_HIL3Mu5_NHitQ10_v1;
   int triggerDecision_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl;

   // skip if the trigger is off or if the prescale is zero
   if(triggerIsOn(triggerDecision,triggerDecision_Prescl)) evtTriggerDecision = true;
   
   // set the weight as 1/prescale value

   double w_trig = 1.0 / ( triggerDecision_Prescl * 1.0 );
   
   bool eventHasGoodJet = false;
   bool eventHasInclRecoMuonTag = false;
   bool eventHasInclRecoMuonTagPlusTrigger = false;
   bool eventHasMatchedRecoMuonTag = false;
   bool eventHasMatchedRecoMuonTagPlusTrigger = false;
   
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

     if(etaPhiMask(y,z)) continue;
     
     double muPtRel = -1.0;
     double muPt = -1.0;
     double muEta = -1.0;
     double muPhi = -1.0;

     bool hasInclRecoMuonTag = false;
		
     // jet kinematic cuts
     if(TMath::Abs(y) > etaMax || x < jetPtCut) continue;

     eventHasGoodJet = true;
		        
     int jetPtIndex = getJetPtBin(x);

     // look for recoMuon match to recoJet		
     for(int m = 0; m < em->nMu; m++){

       double muPt_m = em->muPt->at(m);
       double muEta_m = em->muEta->at(m);
       double muPhi_m = em->muPhi->at(m);
       // skip if muon has already been matched to a jet in this event
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

       // match to recoJets
       if(getDr(em->muEta->at(m),em->muPhi->at(m),y,z) < epsilon_mm){

	 matchFlagR[m] = 1;
				
	 hasInclRecoMuonTag = true;

	 muPtRel = getPtRel(muPt_m,muEta_m,muPhi_m,x,y,z);
	 muPt = muPt_m;
	 muEta = muEta_m;
	 muPhi = muPhi_m;

       }

     }

     // Fill the jet/event histograms
     h_inclRecoJetPt->Fill(x,w);
     h_inclRecoJetEta->Fill(y,w);
     h_inclRecoJetPhi->Fill(z,w);
     h_inclRecoJetPt_inclRecoJetEta->Fill(x,y,w);
     h_inclRecoJetPt_inclRecoJetPhi->Fill(x,z,w);
     h_inclRecoJetEta_inclRecoJetPhi[0]->Fill(y,z,w);
     if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi[jetPtIndex]->Fill(y,z,w);
     
     if(hasInclRecoMuonTag){

       eventHasInclRecoMuonTag = true;

       h_inclRecoJetPt_inclRecoMuonTag->Fill(x,w);
       h_inclRecoJetEta_inclRecoMuonTag->Fill(y,w);
       h_inclRecoJetPhi_inclRecoMuonTag->Fill(z,w);
       h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag->Fill(x,y,w);
       h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag->Fill(x,z,w);
       h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0]->Fill(y,z,w);
       if(jetPtIndex > 0) h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[jetPtIndex]->Fill(y,z,w);
       
       if(evtTriggerDecision){
	 
	 eventHasInclRecoMuonTagPlusTrigger = true;

	 h_inclRecoJetPt_inclRecoMuonTag_triggerOn->Fill(x,w_trig);
	 h_inclRecoJetEta_inclRecoMuonTag_triggerOn->Fill(y,w_trig);
	 h_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Fill(z,w_trig);
	 h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn->Fill(x,y,w_trig);
	 h_inclRecoJetPt_inclRecoJetPhi_inclRecoMuonTag_triggerOn->Fill(x,z,w_trig);
	 
	 h_muptrel_inclRecoMuonTag_triggerOn[0]->Fill(muPtRel,w_trig);
	 h_mupt_inclRecoMuonTag_triggerOn[0]->Fill(muPt,w_trig);
	 h_mueta_inclRecoMuonTag_triggerOn[0]->Fill(muEta,w_trig);
	 h_muphi_inclRecoMuonTag_triggerOn[0]->Fill(muPhi,w_trig);

	 h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[0]->Fill(y,z,w_trig);

	 if(jetPtIndex > 0){

	   h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[jetPtIndex]->Fill(y,z,w_trig);
	   
	   h_muptrel_inclRecoMuonTag_triggerOn[jetPtIndex]->Fill(muPtRel,w_trig);
	   h_mupt_inclRecoMuonTag_triggerOn[jetPtIndex]->Fill(muPt,w_trig);
	   h_mueta_inclRecoMuonTag_triggerOn[jetPtIndex]->Fill(muEta,w_trig);
	   h_muphi_inclRecoMuonTag_triggerOn[jetPtIndex]->Fill(muPhi,w_trig);
	 }
       } 

     }

   }
   // END recoJet LOOP

   if(eventHasGoodJet){

     h_vz->Fill(em->vz,w);
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

 for(int j = 0; j < NJetPtIndices; j++){

   h_muptrel_inclRecoMuonTag_triggerOn[j]->Write();
   h_mupt_inclRecoMuonTag_triggerOn[j]->Write();
   h_mueta_inclRecoMuonTag_triggerOn[j]->Write();
   h_muphi_inclRecoMuonTag_triggerOn[j]->Write();
   h_inclRecoJetEta_inclRecoJetPhi[j]->Write();
    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag[j]->Write();
    h_inclRecoJetEta_inclRecoJetPhi_inclRecoMuonTag_triggerOn[j]->Write();
     
 }
 


 wf->Close();
 return;
 // END WRITE

}
