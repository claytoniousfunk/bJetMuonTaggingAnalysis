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


void PYTHIA_skeleton(int group = 1){


  //TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_PYTHIA_DiJet_withGS/PYTHIA_DiJet_skim_output_%i.root",group);
  TString input = Form("/eos/user/c/cbennett/skims/output_PYTHIA_DiJet_withGS/PYTHIA_DiJet_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-45_removeHYDJETjet_jetTrkMaxFilter_vzReweight_jetPtReweight_hadronPtRelReweight_newJetBins_J1JetPTCut75/PYTHIA_DiJet_scan_output_%i.root",group);


  printIntroduction_PYTHIA_scan_V3p7();
  readConfig();

  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt"); // LXPLUS
  JetCorrector JEC(Files);


  JetUncertainty JEU("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_Uncertainty_AK4PF.txt");

  /////////////  Define histograms
  
  /////////////  Sumw2 commands

  // loop through jet pT indices
  for(int j = 0; j < NJetPtIndices; j++){
    

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

    
    // pthat filter cut
    if(doGenJetPthatFilter){
      if(!passesLeadingGenJetPthatFilter(leadingGenJetPt_i,em->pthat)) continue;
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
      

    }
    // END recoJet LOOP
	

  } // END EVENT LOOP
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  // >>>>>>>>>> write histograms

  
  wf->Close();
  return;
  // END WRITE



}







