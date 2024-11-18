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
#include "../../../headers/AnalysisSetupV2p2.h"

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
//#include "../../../headers/config/config_pp_SingleMuon.h"
#include "../../../headers/config/config_pp_MB.h"
// read config
#include "../../../headers/config/readConfig.h"
// initialize histograms
// ~~~~~~~~~ event variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// -----------------------------------------events w/ incl. reco jet -------

TH1D *h_mu5, *h_mu7, *h_mu12;
TH1D *h_mu5_prescales, *h_mu7_prescales, *h_mu12_prescales;
TH1D *h_mu5_mupt_7to9, *h_mu7_mupt_9to14, *h_mu12_mupt_14;
TH1D *h_mu5_jetpt_80, *h_mu7_jetpt_80, *h_mu12_jetpt_80;
TH1D *h_mu5_muptrel, *h_mu7_muptrel, *h_mu12_muptrel;


///////////////////////  start the program
void pp_scan_trigger(int group = 1){

  //TString input = Form("../../../rootFiles/skimmingOutput/pp/output/pp_skim_output_%i.root",group);
  //TString input = "../../../rootFiles/skimmingOutput/pp/test/testFile.root";


  // TString input = Form("../../../rootFiles/skimmingOutput/pp/output_MinBias/pp_MinBias_skim_output_%i.root",group);
  // TString output = Form("output_SingleMuon_mu7/pp_MinBias_scan_output_%i.root",group);

  TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_pp_SingleMuon/pp_SingleMuon_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_pp_SingleMuon_triggerScan/pp_SingleMuon_scan_output_%i.root",group);

  //TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_skims_pp_HIZeroBias1/pp_MinBias_skim_output_%i.root",group);
  //TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_pp_MinBias_mu12_tight_pTmu-14_evtFilterFix_newJetBins/pp_MinBias_scan_output_%i.root",group);


  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_DATA_L2Relative_AK4PF.txt"); // L2Relative correction
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_DATA_L2L3Residual_AK4PF.txt"); // L2L3Residual correction
  JetCorrector JEC(Files);
  /// >>>>>>>>>>>>>>> print out some info
  printIntroduction_pp_scan_V3p7();
  readConfig();
  // >>>>>>>>>>>>>>>> define histograms
  // ---------------------- event histograms --------------------------------

  h_mu5 = new TH1D("h_mu5","mu5 trig",100,0,100);
  h_mu7 = new TH1D("h_mu7","mu7 trig",100,0,100);
  h_mu12 = new TH1D("h_mu12","mu12 trig",100,0,100);
  
  h_mu5_prescales = new TH1D("h_mu5_prescales","mu5 prescales",100,0,100);
  h_mu7_prescales = new TH1D("h_mu7_prescales","mu7 prescales",100,0,100);
  h_mu12_prescales = new TH1D("h_mu12_prescales","mu12 prescales",100,0,100);

  h_mu5_mupt_7to9 = new TH1D("h_mu5_mupt_7to9","muon pT, mu5 events", NMuPtBins, muPtMin, muPtMax);
  h_mu7_mupt_9to14 = new TH1D("h_mu7_mupt_9to14","muon pT, mu7 events", NMuPtBins, muPtMin, muPtMax);
  h_mu12_mupt_14 = new TH1D("h_mu12_mupt_14","muon pT, mu12 events", NMuPtBins, muPtMin, muPtMax);

  h_mu5_jetpt_80 = new TH1D("h_mu5_jetpt_80","jet pT, mu5 events", NPtBins, ptMin, ptMax);
  h_mu7_jetpt_80 = new TH1D("h_mu7_jetpt_80","jet pT, mu7 events", NPtBins, ptMin, ptMax);
  h_mu12_jetpt_80 = new TH1D("h_mu12_jetpt_80","jet pT, mu12 events", NPtBins, ptMin, ptMax);

  h_mu5_muptrel = new TH1D("h_mu5_muptrel", "muon pTrel, mu5 events", NMuRelPtBins, muRelPtMin, muRelPtMax);
  h_mu7_muptrel = new TH1D("h_mu7_muptrel", "muon pTrel, mu7 events", NMuRelPtBins, muRelPtMin, muRelPtMax);
  h_mu12_muptrel = new TH1D("h_mu12_muptrel", "muon pTrel, mu12 events", NMuRelPtBins, muRelPtMin, muRelPtMax);

  // Sumw2 commands
  h_mu5->Sumw2();
  h_mu7->Sumw2();
  h_mu12->Sumw2();

  h_mu5_prescales->Sumw2();
  h_mu7_prescales->Sumw2();
  h_mu12_prescales->Sumw2();

  h_mu5_mupt_7to9->Sumw2();
  h_mu7_mupt_9to14->Sumw2();
  h_mu12_mupt_14->Sumw2();

  h_mu5_jetpt_80->Sumw2();
  h_mu7_jetpt_80->Sumw2();
  h_mu12_jetpt_80->Sumw2();

  h_mu5_muptrel->Sumw2();
  h_mu7_muptrel->Sumw2();
  h_mu12_muptrel->Sumw2();



  
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

    h_mu5_prescales->Fill(triggerDecision_mu5_Prescl);
    h_mu7_prescales->Fill(triggerDecision_mu7_Prescl);
    h_mu12_prescales->Fill(triggerDecision_mu12_Prescl);

    h_mu5->Fill(triggerDecision_mu5);
    h_mu7->Fill(triggerDecision_mu7);
    h_mu12->Fill(triggerDecision_mu12);
    
      

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
      if(muPt_m < 7. || muPt_m > 1000. || fabs(muEta_m) > 2.0) continue;
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


      if(muPt_m > 7. && muPt_m < 9. && triggerDecision_mu5==1) h_mu5_mupt_7to9->Fill(muPt_m);
      if(muPt_m > 9. && muPt_m < 14. && triggerDecision_mu7==1) h_mu7_mupt_9to14->Fill(muPt_m);
      if(muPt_m > 14. && triggerDecision_mu12==1) h_mu12_mupt_14->Fill(muPt_m);

      
     
      

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

      if(doJetTrkMaxFilter){
	if(!passesJetTrkMaxFilter(jetTrkMax_i,x)) continue;
      }
     
      if(doEtaPhiMask){
	if(etaPhiMask(y,z)) continue;
      }

      //cout << "x" << endl;
     
      double muPtRel = -1.0;
      double muPt = -1.0;
      double muEta = -1.0;
      double muPhi = -1.0;

      bool hasInclRecoMuonTag = false;
		
      // jet kinematic cuts
      if(TMath::Abs(y) > 1.6 || x < 80.) continue;

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
	if(muPt_m < 7. || muPt_m > 1000. || fabs(muEta_m) > 2.0) continue;
	// muon quality cuts
	// if(!isQualityMuon_tight(em->muChi2NDF->at(m),
	// 			em->muInnerD0->at(m),
	// 			em->muInnerDz->at(m),
	// 			em->muMuonHits->at(m),
	// 			em->muPixelHits->at(m),
	// 			em->muIsGlobal->at(m),
	// 			em->muIsPF->at(m),
	// 			em->muStations->at(m),
	// 			em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts

	if(!isQualityMuon_hybridSoft(em->muChi2NDF->at(m),
				     em->muInnerD0->at(m),
				     em->muInnerDz->at(m),
				     em->muPixelHits->at(m),
				     em->muIsTracker->at(m),
				     em->muIsGlobal->at(m),
				     em->muTrkLayers->at(m))) continue; // skip if muon doesnt pass quality cuts     


	if(isWDecayMuon(muPt_m,x)) continue; // skip if "WDecay" muon (has majority of jet pt) 

	// match to recoJets
	if(getDr(muEta_m,muPhi_m,y,z) < epsilon_mm){

	  matchFlagR[m] = 1;
				
	  hasInclRecoMuonTag = true;

	  muPtRel = getPtRel(muPt_m,muEta_m,muPhi_m,x,y,z);
	  muPt = muPt_m;
	  muEta = muEta_m;
	  muPhi = muPhi_m;

	}

      }
     
     
      // Fill the jet/event histograms
      if(triggerDecision_mu5==1){
	h_mu5_jetpt_80->Fill(x);
	if(hasInclRecoMuonTag && muPt > 7. && muPt < 9.){
	  h_mu5_muptrel->Fill(muPtRel);
	}
      }

      if(triggerDecision_mu7==1){
	h_mu7_jetpt_80->Fill(x);
	if(hasInclRecoMuonTag && muPt > 9. && muPt < 14.){
	  h_mu7_muptrel->Fill(muPtRel);
	}
      }

      if(triggerDecision_mu12==1){
	h_mu12_jetpt_80->Fill(x);
	if(hasInclRecoMuonTag && muPt > 14.){
	  h_mu12_muptrel->Fill(muPtRel);
	}
      }
  

    }
    // END recoJet LOOP

  } // end event loop


 
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  h_mu5->Write();
  h_mu7->Write();
  h_mu12->Write();

  h_mu5_prescales->Write();
  h_mu7_prescales->Write();
  h_mu12_prescales->Write();

  h_mu5_mupt_7to9->Write();
  h_mu7_mupt_9to14->Write();
  h_mu12_mupt_14->Write();

  h_mu5_jetpt_80->Write();
  h_mu7_jetpt_80->Write();
  h_mu12_jetpt_80->Write(); 

  h_mu5_muptrel->Write();
  h_mu7_muptrel->Write();
  h_mu12_muptrel->Write();
  
  wf->Close();
  return;
  // END WRITE

}
