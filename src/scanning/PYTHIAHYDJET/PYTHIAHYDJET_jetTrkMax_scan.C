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


/*
  initialize your histograms here!
*/

TH1D *h_jetTrkMaxPt[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxPtOverJetPt[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxEta[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxPhi[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxDR[NCentralityIndices][NJetPtIndices];


void PYTHIAHYDJET_jetTrkMax_scan(int group = 1){

  
  TString input = Form("/eos/user/c/cbennett/skims/output_PYTHIAHYDJET_DiJet_withGS_withWTA_2/PYTHIAHYDJET_DiJet_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIAHYDJET_DiJet_jetTrkMax/PYTHIAHYDJET_scan_output_%i.root",group);

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

  for(int i = 0; i < NCentralityIndices; i++){

    for(int j = 0; j < NJetPtIndices; j++){

      if(i==0 && j==0){
	
	h_jetTrkMaxPt[i][j] = new TH1D(Form("h_jetTrkMaxPt_C%iJ%i",i,j),Form("jetTrkMaxPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),500,0,500);
	h_jetTrkMaxPtOverJetPt[i][j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_C%iJ%i",i,j),Form("jetTrkMaxPt / jetPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
	h_jetTrkMaxEta[i][j] = new TH1D(Form("h_jetTrkMaxEta_C%iJ%i",i,j),Form("jetTrkMaxEta, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_jetTrkMaxPhi[i][j] = new TH1D(Form("h_jetTrkMaxPhi_C%iJ%i",i,j),Form("jetTrkMaxPhi, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax);
	h_jetTrkMaxDR[i][j] = new TH1D(Form("h_jetTrkMaxDR_C%iJ%i",i,j),Form("jetTrkMaxDR, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NdRBins,dRBinMin,dRBinMax);

	
      }
      else if(i==0){

	h_jetTrkMaxPt[i][j] = new TH1D(Form("h_jetTrkMaxPt_C%iJ%i",i,j),Form("jetTrkMaxPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),500,0,500);
	h_jetTrkMaxPtOverJetPt[i][j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_C%iJ%i",i,j),Form("jetTrkMaxPt / jetPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
	h_jetTrkMaxEta[i][j] = new TH1D(Form("h_jetTrkMaxEta_C%iJ%i",i,j),Form("jetTrkMaxEta, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_jetTrkMaxPhi[i][j] = new TH1D(Form("h_jetTrkMaxPhi_C%iJ%i",i,j),Form("jetTrkMaxPhi, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax);
	h_jetTrkMaxDR[i][j] = new TH1D(Form("h_jetTrkMaxDR_C%iJ%i",i,j),Form("jetTrkMaxDR, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NdRBins,dRBinMin,dRBinMax);


      }
      else if(j==0){

	h_jetTrkMaxPt[i][j] = new TH1D(Form("h_jetTrkMaxPt_C%iJ%i",i,j),Form("jetTrkMaxPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),500,0,500);
	h_jetTrkMaxPtOverJetPt[i][j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_C%iJ%i",i,j),Form("jetTrkMaxPt / jetPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
	h_jetTrkMaxEta[i][j] = new TH1D(Form("h_jetTrkMaxEta_C%iJ%i",i,j),Form("jetTrkMaxEta, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_jetTrkMaxPhi[i][j] = new TH1D(Form("h_jetTrkMaxPhi_C%iJ%i",i,j),Form("jetTrkMaxPhi, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax);
	h_jetTrkMaxDR[i][j] = new TH1D(Form("h_jetTrkMaxDR_C%iJ%i",i,j),Form("jetTrkMaxDR, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NdRBins,dRBinMin,dRBinMax);

      }
      else{

	h_jetTrkMaxPt[i][j] = new TH1D(Form("h_jetTrkMaxPt_C%iJ%i",i,j),Form("jetTrkMaxPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),500,0,500);
	h_jetTrkMaxPtOverJetPt[i][j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_C%iJ%i",i,j),Form("jetTrkMaxPt / jetPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
	h_jetTrkMaxEta[i][j] = new TH1D(Form("h_jetTrkMaxEta_C%iJ%i",i,j),Form("jetTrkMaxEta, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_jetTrkMaxPhi[i][j] = new TH1D(Form("h_jetTrkMaxPhi_C%iJ%i",i,j),Form("jetTrkMaxPhi, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax);
	h_jetTrkMaxDR[i][j] = new TH1D(Form("h_jetTrkMaxDR_C%iJ%i",i,j),Form("jetTrkMaxDR, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NdRBins,dRBinMin,dRBinMax);

      }

      h_jetTrkMaxPt[i][j]->Sumw2();
      h_jetTrkMaxPtOverJetPt[i][j]->Sumw2();
      h_jetTrkMaxEta[i][j]->Sumw2();
      h_jetTrkMaxPhi[i][j]->Sumw2();
      h_jetTrkMaxDR[i][j]->Sumw2();
      
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
    if(w > 0.005) continue;
   
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
      double jetTrkMaxEta_i = em->jetTrkMaxEta[i];
      double jetTrkMaxPhi_i = em->jetTrkMaxPhi[i];
      double jetTrkMaxDR_i = em->jetTrkMaxDR[i];

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

          		
      int matchedPartonFlavor = em->matchedPartonFlavor[i];
      int refPartonFlavorForB = em->refparton_flavorForB[i];
      int hadronFlavorInt = em->matchedHadronFlavor[i];
      int bHadronNumber = em->bHadronNumber[i];

      int jetFlavorInt = matchedPartonFlavor;

      if(fabs(jetFlavorInt) == 5 && bHadronNumber == 2) jetFlavorInt = 17; // 17 = bJet from gluon-splitting 
		
      // jet kinematic cuts
      if(TMath::Abs(recoJetEta_i) > 1.6 || recoJetPt_i < 80.) continue;
		        
      int jetPtIndex = getJetPtBin(recoJetPt_i);

      h_jetTrkMaxPt[0][0]->Fill(jetTrkMax_i,w);
      h_jetTrkMaxPtOverJetPt[0][0]->Fill(jetTrkMax_i/recoJetPt_i,w);
      h_jetTrkMaxEta[0][0]->Fill(jetTrkMaxEta_i,w);
      h_jetTrkMaxPhi[0][0]->Fill(jetTrkMaxPhi_i,w);
      h_jetTrkMaxDR[0][0]->Fill(jetTrkMaxDR_i,w);

      h_jetTrkMaxPt[CentralityIndex][0]->Fill(jetTrkMax_i,w);
      h_jetTrkMaxPtOverJetPt[CentralityIndex][0]->Fill(jetTrkMax_i/recoJetPt_i,w);
      h_jetTrkMaxEta[CentralityIndex][0]->Fill(jetTrkMaxEta_i,w);
      h_jetTrkMaxPhi[CentralityIndex][0]->Fill(jetTrkMaxPhi_i,w);
      h_jetTrkMaxDR[CentralityIndex][0]->Fill(jetTrkMaxDR_i,w);

      h_jetTrkMaxPt[0][jetPtIndex]->Fill(jetTrkMax_i,w);
      h_jetTrkMaxPtOverJetPt[0][jetPtIndex]->Fill(jetTrkMax_i/recoJetPt_i,w);
      h_jetTrkMaxEta[0][jetPtIndex]->Fill(jetTrkMaxEta_i,w);
      h_jetTrkMaxPhi[0][jetPtIndex]->Fill(jetTrkMaxPhi_i,w);
      h_jetTrkMaxDR[0][jetPtIndex]->Fill(jetTrkMaxDR_i,w);

      h_jetTrkMaxPt[CentralityIndex][jetPtIndex]->Fill(jetTrkMax_i,w);
      h_jetTrkMaxPtOverJetPt[CentralityIndex][jetPtIndex]->Fill(jetTrkMax_i/recoJetPt_i,w);
      h_jetTrkMaxEta[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxEta_i,w);
      h_jetTrkMaxPhi[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxPhi_i,w);
      h_jetTrkMaxDR[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxDR_i,w);

      
      

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

  for(int i = 0; i < NCentralityIndices; i++){

    for(int j = 0; j < NJetPtIndices; j++){

      h_jetTrkMaxPt[i][j]->Write();
      h_jetTrkMaxPtOverJetPt[i][j]->Write();
      h_jetTrkMaxEta[i][j]->Write();
      h_jetTrkMaxPhi[i][j]->Write();
      h_jetTrkMaxDR[i][j]->Write();
      
    }

  }


  wf->Close();
  return;
  // END WRITE

}
