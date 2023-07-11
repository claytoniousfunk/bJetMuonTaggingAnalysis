
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

// User includes

// event map
#include "../../../../eventMap/eventMap.h"
// jet corrector
#include "../../../../JetEnergyCorrections/JetCorrector.h"
// jet uncertainty
#include "../../../../JetEnergyCorrections/JetUncertainty.h"
// general analysis variables
#include "../../../../headers/AnalysisSetupV2p1.h"
// vz-fit parameters
#include "../../../../headers/fitParameters/vzFitParams_PYTHIA.h"
// hiBin-fit parameters
#include "../../../../headers/fitParameters/hiBinFitParams.h"

TF1 *fitFxn_hiBin, *fitFxn_vz;
// vz-fit function
#include "../../../../headers/fitFunctions/fitFxn_vz_PYTHIA.h"
// hiBin-fit function
#include "../../../../headers/fitFunctions/fitFxn_hiBin.h"

// eta-phi mask function
#include "../../../../headers/functions/etaPhiMask.h"
// getDr function
#include "../../../../headers/functions/getDr.h"
// getJetPtBin function
#include "../../../../headers/functions/getJetPtBin.h"
// getCentBin function
#include "../../../../headers/functions/getCentBin_v2.h"
// getPtRel function
#include "../../../../headers/functions/getPtRel.h"
// isQualityMuon_hybridSoft function
#include "../../../../headers/functions/isQualityMuon_hybridSoft.h"
// isQualityMuon_tight function
#include "../../../../headers/functions/isQualityMuon_tight.h"
// isWDecayMuon function
#include "../../../../headers/functions/isWDecayMuon.h"
// triggerIsOn function
#include "../../../../headers/functions/triggerIsOn.h"
// pthat filter function
#include "../../../../headers/functions/passesLeadingGenJetPthatFilter.h"
// print introduction
#include "../../../../headers/introductions/printIntroduction_PYTHIA_scan_V3p7.h"
// analysis config
#include "../../../../headers/config/config_PYTHIA.h"
// read config
#include "../../../../headers/config/readConfig.h"

//~~~~~~~~~~~  initialize histograms ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D *h_inclGenMuonPt;
TH1D *h_inclGenMuonEta;
TH1D *h_matchedGenMuonPt;
TH1D *h_matchedGenMuonEta;
TH2D *h_matchedRecoMuonPtOverGenMuonPt_genMuonPt;
TH2D *h_matchedRecoMuonPtOverGenMuonPt_genMuonEta;

void PYTHIA_scan_muonReco_bJets(TString input = "/eos/user/c/cbennett/forests/PYTHIA_forest_10Aug22/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/crab_PYTHIA_forest_10Aug22/220810_170721/0000/HiForestAOD_100.root", TString output = "out.root"){

  readConfig();

   // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt"); // LXPLUS
  JetCorrector JEC(Files);

  JetUncertainty JEU("../../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_Uncertainty_AK4PF.txt");


  // Define histograms
  h_inclGenMuonPt = new TH1D("h_inclGenMuonPt","gen muon p_{T}",NMuPtBins,muPtMin,muPtMax);
  h_inclGenMuonEta = new TH1D("h_inclGenMuonEta","gen muon #eta",NTrkEtaBins,trkEtaMin,trkEtaMax);
  h_matchedGenMuonPt = new TH1D("h_matchedGenMuonPt","gen muon p_{T}",NMuPtBins,muPtMin,muPtMax);
  h_matchedGenMuonEta = new TH1D("h_matchedGenMuonEta","gen muon #eta",NTrkEtaBins,trkEtaMin,trkEtaMax);
   
  h_matchedRecoMuonPtOverGenMuonPt_genMuonPt = new TH2D("h_matchedRecoMuonPtOverGenMuonPt_genMuonPt","p_{T}^{reco,#mu} / p_{T}^{gen,#mu} vs. p_{T}^{gen,#mu}",500,0,5,NMuPtBins,muPtMin,muPtMax);
  h_matchedRecoMuonPtOverGenMuonPt_genMuonEta = new TH2D("h_matchedRecoMuonPtOverGenMuonPt_genMuonEta","p_{T}^{reco,#mu} / p_{T}^{gen,#mu} vs. #eta^{gen,#mu}",500,0,5,NTrkEtaBins,trkEtaMin,trkEtaMax);

  h_inclGenMuonPt->Sumw2();
  h_inclGenMuonEta->Sumw2();
  h_matchedGenMuonPt->Sumw2();
  h_matchedGenMuonEta->Sumw2();

  h_matchedRecoMuonPtOverGenMuonPt_genMuonPt->Sumw2();
  h_matchedRecoMuonPtOverGenMuonPt_genMuonEta->Sumw2();

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

  loadFitFxn_vz();

  // event loop
  int evi_frac = 0;
  for(int evi = 0; evi < NEvents ; evi++){
    //for(int evi = 0; evi < 10 ; evi++){
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

    double w_reweight_vz = fitFxn_vz->Eval(em->vz);
    double w = em->weight * w_reweight_vz ;


    // gen muon loop
    for(int j = 0; j < em->gppdgIDp->size(); j++){

      bool isMatchedGenMuon = false;

      if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

      double genMuPt_j = em->gpptp->at(j);
      double genMuEta_j = em->gpetap->at(j);
      double genMuPhi_j = em->gpphip->at(j);

      if(fabs(genMuEta_j) > trkEtaMax) continue;
      

      // look for match to bJet

      bool hasBJetMatch = false;
      
      for(int jeti = 0; jeti < em->njet; jeti++){

	double jetPt_i = em->jetpt[jeti];
	double jetEta_i = em->jeteta[jeti];
	double jetPhi_i = em->jetphi[jeti];
	int flavor_i = em->partonFlavor[jeti];

	if(jetPt_i < 60.0 || fabs(jetEta_i) > 1.6  || fabs(flavor_i) != 5) continue;  // only consider bJets in our kinematic range

	double dR_ji = getDr(jetEta_i,jetPhi_i,genMuEta_j,genMuPhi_j);

	if(dR_ji < epsilon_mm){

	  hasBJetMatch = true;

	}

      }

      if(!hasBJetMatch) continue;

      

      h_inclGenMuonPt->Fill(genMuPt_j,w);
      h_inclGenMuonEta->Fill(genMuEta_j,w);


      // declare matched variables
      double matchedRecoMuPt_j = -99.0;
      double matchedRecoMuEta_j = -99.0;
      double matchedRecoMuPhi_j = -99.0;
      
      //reco muon loop
      double dR_min = 10.0;
      double dR_jk = 10.0;
      
      for(int k = 0; k < em->nMu; k++){

	if(!isQualityMuon_tight(em->muChi2NDF->at(k),
				em->muInnerD0->at(k),
				em->muInnerDz->at(k),
				em->muMuonHits->at(k),
				em->muPixelHits->at(k),
				em->muIsGlobal->at(k),
				em->muIsPF->at(k),
				em->muStations->at(k),
				em->muTrkLayers->at(k))) continue; // skip if muon doesnt pass quality cuts

	double recoMuPt_k = em->muPt->at(k);
	double recoMuEta_k = em->muEta->at(k);
	double recoMuPhi_k = em->muPhi->at(k);
	
	dR_jk = getDr(genMuEta_j, genMuPhi_j, recoMuEta_k, recoMuPhi_k);

	if(dR_jk > dR_min) continue;

	dR_min = dR_jk; 

	if(dR_jk < epsilon){
	  	  
	  isMatchedGenMuon = true;
	  matchedRecoMuPt_j = recoMuPt_k;
	  matchedRecoMuEta_j = recoMuEta_k;
	  matchedRecoMuPhi_j = recoMuPhi_k; 

	}

      } // end reco muon loop

      if(isMatchedGenMuon){

	h_matchedGenMuonPt->Fill(genMuPt_j,w);
	h_matchedGenMuonEta->Fill(genMuEta_j,w);

	h_matchedRecoMuonPtOverGenMuonPt_genMuonPt->Fill(matchedRecoMuPt_j / genMuPt_j, genMuPt_j, w);
	h_matchedRecoMuonPtOverGenMuonPt_genMuonEta->Fill(matchedRecoMuPt_j / genMuPt_j, genMuEta_j, w);

      }

    } // end gen muon loop

  } // end event loop
  delete f;

  // WRITE
  auto wf = TFile::Open(output,"recreate");

  h_inclGenMuonPt->Write();
  h_inclGenMuonEta->Write();
  h_matchedGenMuonPt->Write();
  h_matchedGenMuonEta->Write();

  h_matchedRecoMuonPtOverGenMuonPt_genMuonPt->Write();
  h_matchedRecoMuonPtOverGenMuonPt_genMuonEta->Write();

  wf->Close();
  return;
  

} // end program
