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
#include "../../../../eventMap/eventMap.h"
// jet corrector
#include "../../../../JetEnergyCorrections/JetCorrector.h"
// jet uncertainty
#include "../../../../JetEnergyCorrections/JetUncertainty.h"
// general analysis variables
#include "../../../../headers/AnalysisSetupV2p1.h"
// vz-fit parameters
#include "../../../../headers/fitParameters/vzFitParams_PH.h"
// hiBin-fit parameters
#include "../../../../headers/fitParameters/hiBinFitParams.h"

TF1 *fitFxn_hiBin, *fitFxn_vz;
// vz-fit function
#include "../../../../headers/fitFunctions/fitFxn_vz_PH.h"
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
#include "../../../../headers/introductions/printIntroduction_PYTHIAHYDJET_scan_V3p7.h"
// analysis config
#include "../../../../headers/config/config_PYTHIAHYDJET.h"
// read config
#include "../../../../headers/config/readConfig.h"

//~~~~~~~~~~~  initialize histograms ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D *h_inclGenMuonPt[NCentralityIndices];
TH1D *h_inclGenMuonEta[NCentralityIndices];
TH1D *h_matchedGenMuonPt[NCentralityIndices];
TH1D *h_matchedGenMuonEta[NCentralityIndices];
TH2D *h_matchedRecoMuonPtOverGenMuonPt_genMuonPt[NCentralityIndices];
TH2D *h_matchedRecoMuonPtOverGenMuonPt_genMuonEta[NCentralityIndices];

void PYTHIAHYDJET_scan_muonReco(TString input = "/eos/user/c/cbennett/forests/PYTHIAHYDJET_DiJet_5July22/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/crab_PYTHIAHYDJET_DiJet_5July22/220705_212159/0000/HiForestAOD_104.root", TString output = "out.root"){

  readConfig();

  vector<string> Files;
  Files.push_back("../../../../JetEnergyCorrections/Autumn18_HI_V8_MC_L2Relative_AK4PF.txt"); // LXPLUS

  JetCorrector JEC(Files);

  JetUncertainty JEU("../../../../JetEnergyCorrections/Autumn18_HI_V8_MC_Uncertainty_AK4PF.txt");

  for(int c = 0; c < NCentralityIndices; c++){

    if(c == 0){

      h_inclGenMuonPt[c] = new TH1D(Form("h_inclGenMuonPt_C%i",c),Form("gen muon p_{T}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NMuPtBins,muPtMin,muPtMax);
      h_inclGenMuonEta[c] = new TH1D(Form("h_inclGenMuonEta_C%i",c),Form("gen muon #eta, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
      h_matchedGenMuonPt[c] = new TH1D(Form("h_matchedGenMuonPt_C%i",c),Form("matched-gen muon p_{T}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NMuPtBins,muPtMin,muPtMax);
      h_matchedGenMuonEta[c] = new TH1D(Form("h_matchedGenMuonEta_C%i",c),Form("matched-gen muon #eta, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
   
      h_matchedRecoMuonPtOverGenMuonPt_genMuonPt[c] = new TH2D(Form("h_matchedRecoMuonPtOverGenMuonPt_genMuonPt_C%i",c),Form("p_{T}^{reco,#mu} / p_{T}^{gen,#mu} vs. p_{T}^{gen,#mu}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NMuPtBins,muPtMin,muPtMax);
      h_matchedRecoMuonPtOverGenMuonPt_genMuonEta[c] = new TH2D("h_matchedRecoMuonPtOverGenMuonPt_genMuonEta",Form("p_{T}^{reco,#mu} / p_{T}^{gen,#mu} vs. #eta^{gen,#mu}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NTrkEtaBins,trkEtaMin,trkEtaMax);

    }

    else{

      h_inclGenMuonPt[c] = new TH1D(Form("h_inclGenMuonPt_C%i",c),Form("gen muon p_{T}, hiBin %i - %i",centEdges[c-1],centEdges[c]),NMuPtBins,muPtMin,muPtMax);
      h_inclGenMuonEta[c] = new TH1D(Form("h_inclGenMuonEta_C%i",c),Form("gen muon #eta, hiBin %i - %i",centEdges[c-1],centEdges[c]),NTrkEtaBins,trkEtaMin,trkEtaMax);
      h_matchedGenMuonPt[c] = new TH1D(Form("h_matchedGenMuonPt_C%i",c),Form("matched-gen muon p_{T}, hiBin %i - %i",centEdges[c-1],centEdges[c]),NMuPtBins,muPtMin,muPtMax);
      h_matchedGenMuonEta[c] = new TH1D(Form("h_matchedGenMuonEta_C%i",c),Form("matched-gen muon #eta, hiBin %i - %i",centEdges[c-1],centEdges[c]),NTrkEtaBins,trkEtaMin,trkEtaMax);
   
      h_matchedRecoMuonPtOverGenMuonPt_genMuonPt[c] = new TH2D(Form("h_matchedRecoMuonPtOverGenMuonPt_genMuonPt_C%i",c),Form("p_{T}^{reco,#mu} / p_{T}^{gen,#mu} vs. p_{T}^{gen,#mu}, hiBin %i - %i",centEdges[c-1],centEdges[c]),500,0,5,NMuPtBins,muPtMin,muPtMax);
      h_matchedRecoMuonPtOverGenMuonPt_genMuonEta[c] = new TH2D("h_matchedRecoMuonPtOverGenMuonPt_genMuonEta_C%i",Form("p_{T}^{reco,#mu} / p_{T}^{gen,#mu} vs. #eta^{gen,#mu}, hiBin %i - %i",centEdges[c-1],centEdges[c]),500,0,5,NTrkEtaBins,trkEtaMin,trkEtaMax);

    }

    h_inclGenMuonPt[c]->Sumw2();
    h_inclGenMuonEta[c]->Sumw2();
    h_matchedGenMuonPt[c]->Sumw2();
    h_matchedGenMuonEta[c]->Sumw2();

    h_matchedRecoMuonPtOverGenMuonPt_genMuonPt[c]->Sumw2();
    h_matchedRecoMuonPtOverGenMuonPt_genMuonEta[c]->Sumw2();

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

  loadFitFxn_vz();

  loadFitFxn_hiBin();
  
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
    if(em->checkEventFilter()) continue;

    // calculate event weight
    double w_reweight_hiBin = fitFxn_hiBin->Eval(em->hiBin-10);
    //double w_reweight_hiBin = 1.0;

    //double w_reweight_vz = fitFxn_vz->Eval(em->vz);
    double w_reweight_vz = 1.0;
   
    double w = em->weight * w_reweight_hiBin * w_reweight_vz;

    
    if(w <= 0.0) continue;

    int CentralityIndex = getCentBin(em->hiBin-10);
    if(CentralityIndex < 0) continue;

    // gen muon loop
    for(int j = 0; j < em->gppdgIDp->size(); j++){

      bool isMatchedGenMuon = false;

      if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

      double genMuPt_j = em->gpptp->at(j);
      double genMuEta_j = em->gpetap->at(j);
      double genMuPhi_j = em->gpphip->at(j);

      if(fabs(genMuEta_j) > trkEtaMax) continue;

      h_inclGenMuonPt[0]->Fill(genMuPt_j,w);
      h_inclGenMuonEta[0]->Fill(genMuEta_j,w);

      h_inclGenMuonPt[CentralityIndex]->Fill(genMuPt_j,w);
      h_inclGenMuonEta[CentralityIndex]->Fill(genMuEta_j,w);

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

	h_matchedGenMuonPt[0]->Fill(genMuPt_j,w);
	h_matchedGenMuonEta[0]->Fill(genMuEta_j,w);

	h_matchedGenMuonPt[CentralityIndex]->Fill(genMuPt_j,w);
	h_matchedGenMuonEta[CentralityIndex]->Fill(genMuEta_j,w);

	h_matchedRecoMuonPtOverGenMuonPt_genMuonPt[0]->Fill(matchedRecoMuPt_j / genMuPt_j, genMuPt_j, w);
	h_matchedRecoMuonPtOverGenMuonPt_genMuonEta[0]->Fill(matchedRecoMuPt_j / genMuPt_j, genMuEta_j, w);

	h_matchedRecoMuonPtOverGenMuonPt_genMuonPt[CentralityIndex]->Fill(matchedRecoMuPt_j / genMuPt_j, genMuPt_j, w);
	h_matchedRecoMuonPtOverGenMuonPt_genMuonEta[CentralityIndex]->Fill(matchedRecoMuPt_j / genMuPt_j, genMuEta_j, w);

      }

    } // end gen muon loop


    

  } // end event loop
  delete f;

  auto wf = TFile::Open(output,"recreate");

  for(int c = 0; c < NCentralityIndices; c++){
    
    h_inclGenMuonPt[c]->Write();
    h_inclGenMuonEta[c]->Write();
    h_matchedGenMuonPt[c]->Write();
    h_matchedGenMuonEta[c]->Write();

    h_matchedRecoMuonPtOverGenMuonPt_genMuonPt[c]->Write();
    h_matchedRecoMuonPtOverGenMuonPt_genMuonEta[c]->Write();

  }
  wf->Close();
  return;



} // end program
