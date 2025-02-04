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
//#include "../../../headers/AnalysisSetupV2p2.h"
#include "../../../headers/AnalysisSetupV2p3.h"
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
#include "../../../headers/config/config_pp_SingleMuon.h"
//#include "../../../headers/config/config_pp_MB.h"
// read config
#include "../../../headers/config/readConfig.h"
// initialize histograms



///////////////////////  start the program
void pp_skeleton(int group = 1){

  TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_pp_HighEGJet_withTrackMaxInfo_manual/pp_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_pp_SKELETON/pp_scan_output_%i.root",group);


  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_DATA_L2Relative_AK4PF.txt"); // L2Relative correction
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_DATA_L2L3Residual_AK4PF.txt"); // L2L3Residual correction
  JetCorrector JEC(Files);
  /// >>>>>>>>>>>>>>> print out some info
  printIntroduction_pp_scan_V3p7();
  readConfig();
  // >>>>>>>>>>>>>>>> define histograms

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
      double muJetDr_i = -99.0;

      if(doJetTrkMaxFilter){
	if(!passesJetTrkMaxFilter(jetTrkMax_i,recoJetPt_i)) continue;
      }
     
      if(doEtaPhiMask){
	if(etaPhiMask(y,z)) continue;
      }

      //cout << "x" << endl;
     
     		
      // jet kinematic cuts
      if(TMath::Abs(y) > etaMax || x < jetPtCut) continue;

      int jetPtIndex = getJetPtBin(x);


    }
     
     
  
  }
  // END recoJet LOOP

 

} // end event loop


 
delete f;
// WRITE
auto wf = TFile::Open(output,"recreate");

// >>>>> write histograms
 
 
for(int j = 0; j < NJetPtIndices; j++){

 }
 


wf->Close();
return;
// END WRITE

}
