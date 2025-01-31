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
#include "../../../headers/config/config_PbPb_SingleMuon.h"
//#include "../../../headers/config/config_PbPb_MinBias.h"
//#include "../../../headers/config/config_PbPb_diJet.h"
// read config
#include "../../../headers/config/readConfig.h"


/*
  initialize histograms
*/



///////////////////////  start the program
void PbPb_skeleton(int group = 1){

  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_skims_PbPb_HardProbes/PbPb_HardProbes_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PbPb_HardProbes_mu12_tight_pTmu-14_evtFilterFix_hiHFcut_newJetBins/PbPb_HardProbes_scan_output_%i.root",group);

  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_skims_PbPb_HIMinimumBias0/PbPb_MinBias_skim_output_%i.root",group);
  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PbPb_MinBias_mu12_tight_pTmu-14_evtFilterFix_hiHFcut_newJetBins/PbPb_MinBias_scan_output_%i.root",group);

  TString input = Form("/eos/user/c/cbennett/skims/output_PbPb_SingleMuon_withWTA/PbPb_SingleMuon_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PbPb_SingleMuon_scan_mu12_tight_pTmu-14_hiHFcut_newJetBins_fineCentBins/PbPb_SingleMuon_scan_output_%i.root",group);
  
  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_DATA_L2Relative_AK4PF.txt"); // L2Relative correction
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_DATA_L2L3Residual_AK4PF.txt"); // L2L3Residual correction
  JetCorrector JEC(Files);
  /// print out some info
  printIntroduction_PbPb_scan_V3p7();
  readConfig();
  // define histograms
    
  // for loop through the centrality indices
  for(int i = 0; i < NCentralityIndices; i++){
    // the inclusive centrality histogram	
    if(i==0){
    // loop through jet pt indices
    for(int j = 0; j < NJetPtIndices; j++){
      if(i==0 && j==0){
      }
      else if(i==0){
      }
      else if(j==0){
      }
      else{
      }
      // Sumw2

      
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

    // In data, event weight = 1
    double w = 1.0;
	
    int CentralityIndex = getCentBin(em->hiBin);
    if(CentralityIndex < 0) continue;
  
    double leadingRecoJetPt = 0.0;
    // RECO JET LOOP
    for(int i = 0; i < em->njet ; i++){

      // JET VARIABLES
		
      JEC.SetJetPT(em->rawpt[i]);
      JEC.SetJetEta(em->jeteta[i]);
      JEC.SetJetPhi(em->jetphi[i]);

      double recoJetPt_i = JEC.GetCorrectedPT();  // use manual JEC
      //double x = em->jetpt[i]; // use built-in JEC
      double recoJetEta_i = em->jeteta[i]; // recoJetEta
      double recoJetPhi_i = em->jetphi[i]; // recoJetPhi
      double jetTrkMax_i = em->jetTrkMax[i];
      double jetTrkMaxEta_i = em->jetTrkMaxEta[i];
      double jetTrkMaxPhi_i = em->jetTrkMaxPhi[i];
      double jetTrkMaxDR_i = em->jetTrkMaxDR[i]; 

           
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

		
      // jet kinematic cuts
      if(TMath::Abs(y) > etaMax || x < jetPtCut) continue;

      if(x > leadingRecoJetPt) leadingRecoJetPt = x;
    		        
      int jetPtIndex = getJetPtBin(x);


      // Fill the jet/event histograms

    }
    // END recoJet LOOP

  } // end event loop
 
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  /*
    write your histograms
  */
  
  for(int i = 0; i < NCentralityIndices; i++){

    for(int j = 0; j < NJetPtIndices; j++){

    
    }
    
  }

  wf->Close();
  return;
  // END WRITE

}
