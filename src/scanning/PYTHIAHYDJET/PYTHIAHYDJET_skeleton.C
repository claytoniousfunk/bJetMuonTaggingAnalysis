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
// hadronPtRel parameters
#include "../../../headers/fitParameters/hadronPtRelFitParams.h"

TF1 *fitFxn_hiBin, *fitFxn_vz, *fitFxn_jetPt, *fitFxn_hadronPtRel;
// hadronPtRel parameters
#include "../../../headers/fitFunctions/fitFxn_hadronPtRel.h"
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
#include "../../../headers/functions/getCentBin_v2.h" // course centrality binning
//#include "../../../headers/functions/getCentBin.h" // fine centrality binning 
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


void PYTHIAHYDJET_skeleton(int group = 1){

  
  TString input = Form("/eos/user/c/cbennett/skims/output_PYTHIAHYDJET_DiJet_withGS_withWTA_2/PYTHIAHYDJET_DiJet_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_removeHYDJETjet_jetTrkMaxFilter_vzReweight_hiBinReweight_newJetBins_templateWeightAnalysis_weightCut0p002_SKELETON/PYTHIAHYDJET_scan_output_%i.root",group);

  // TString input = Form("/eos/user/c/cbennett/skims/output_PYTHIAHYDJET_MuJet_withGS_withWTA_2/PYTHIAHYDJET_MuJet_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIAHYDJET_MuJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_removeHYDJETjet_jetTrkMaxFilter_vzReweight_hiBinReweight_newJetBins_templateWeightAnalysis_weightCut0p002/PYTHIAHYDJET_scan_output_%i.root",group);

  // TString input = Form("/eos/user/c/cbennett/skims/output_PYTHIAHYDJET_BJet_withGS_withWTA_2/PYTHIAHYDJET_BJet_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIAHYDJET_BJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_removeHYDJETjet_jetTrkMaxFilter_vzReweight_hiBinReweight_newJetBins_templateWeightAnalysis_weightCut0p002/PYTHIAHYDJET_scan_output_%i.root",group);


  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch8/PYTHIAHYDJET_DiJet_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PH_DiJet_batch8_scan_mu12_tight_pTmu-14_pThat-45_hiHFcut_removeHYDJETjet_jetTrkMaxFilter_vzReweight_hiBinReweight_newJetBins_fineCentBins/PYTHIAHYDJET_scan_output_%i.root",group);      

  
  
  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_L2Relative_AK4PF.txt"); // LXPLUS

  JetCorrector JEC(Files);
  
  JetUncertainty JEU("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_Uncertainty_AK4PF.txt");
 
  readConfig();
 

  /*
    Define all your histograms here!!
  */


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

  // load fit functions
  loadFitFxn_vz();
  loadFitFxn_hiBin();
  loadFitFxn_jetPt();

  // define a random-generator 
  TRandom *randomGenerator = new TRandom2();
 
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
		        
      int jetPtIndex = getJetPtBin(recoJetPt_i);

      if(jetPtIndex < 0) continue;

      
      double dR_recoGen_min = 100.0;
      double dPt_recoGen_min = 100.0;

      // look for a genJet match

      for(int j = 0; j < em->ngj ; j++){


	if(recoJetPt_i < 20) continue;	

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
	  


	  muPt_i = recoMuonPt_m;
	  muEta_i = recoMuonEta_m;
	  muPhi_i = recoMuonPhi_m;
				
	  if(isMatchedRecoMuon) hasMatchedRecoMuonTag = true;

	}

      }

    }
    // END recoJet LOOP


  } // end event loop


 
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  /*
    write all your histograms to a file!

    histogram->Write();

    or

    histogram->Write("name");

  */




  wf->Close();
  return;
  // END WRITE

}
