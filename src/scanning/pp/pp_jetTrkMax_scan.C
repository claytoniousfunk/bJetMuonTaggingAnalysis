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
TH1D *h_jetPt;
TH1D *h_jetTrkMaxPt[NJetPtIndices];
TH1D *h_jetTrkMaxPtOverJetPt[NJetPtIndices];
TH1D *h_jetTrkMaxEta[NJetPtIndices];
TH1D *h_jetTrkMaxPhi[NJetPtIndices];
TH1D *h_jetTrkMaxDR[NJetPtIndices];
TH1D *h_jetTrkMaxPtRel[NJetPtIndices];


///////////////////////  start the program
void pp_jetTrkMax_scan(int group = 1){

  TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_pp_HighEGJet_withTrackMaxInfo_manual/pp_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_pp_jetTrkMax_jet60/pp_scan_output_%i.root",group);


  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_DATA_L2Relative_AK4PF.txt"); // L2Relative correction
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_DATA_L2L3Residual_AK4PF.txt"); // L2L3Residual correction
  JetCorrector JEC(Files);
  /// >>>>>>>>>>>>>>> print out some info
  printIntroduction_pp_scan_V3p7();
  readConfig();
  /////////////  Define histograms
  h_jetPt = new TH1D("h_jetPt","jetPt",NPtBins,ptMin,ptMax);

  h_jetPt->Sumw2();

  // loop through jet pT indices
  for(int j = 0; j < NJetPtIndices; j++){

    if(j==0){
      
      h_jetTrkMaxPt[j] = new TH1D(Form("h_jetTrkMaxPt_J%i",j),Form("jetTrkMaxPt, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),500,0,500);
      h_jetTrkMaxPtOverJetPt[j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_J%i",j),Form("jetTrkMaxPt / jetPt, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
      h_jetTrkMaxEta[j] = new TH1D(Form("h_jetTrkMaxEta_J%i",j),Form("jetTrkMaxEta, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
      h_jetTrkMaxPhi[j] = new TH1D(Form("h_jetTrkMaxPhi_J%i",j),Form("jetTrkMaxPhi, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax);
      h_jetTrkMaxDR[j] = new TH1D(Form("h_jetTrkMaxDR_J%i",j),Form("jetTrkMaxDR, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NdRBins,dRBinMin,dRBinMax);
      h_jetTrkMaxPtRel[j] = new TH1D(Form("h_jetTrkMaxPtRel_J%i",j),Form("jetTrkMaxPtRel, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax);

    }

    else{

      h_jetTrkMaxPt[j] = new TH1D(Form("h_jetTrkMaxPt_J%i",j),Form("jetTrkMaxPt, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),500,0,500);
      h_jetTrkMaxPtOverJetPt[j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_J%i",j),Form("jetTrkMaxPt / jetPt, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
      h_jetTrkMaxEta[j] = new TH1D(Form("h_jetTrkMaxEta_J%i",j),Form("jetTrkMaxEta, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax);
      h_jetTrkMaxPhi[j] = new TH1D(Form("h_jetTrkMaxPhi_J%i",j),Form("jetTrkMaxPhi, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax);
      h_jetTrkMaxDR[j] = new TH1D(Form("h_jetTrkMaxDR_J%i",j),Form("jetTrkMaxDR, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NdRBins,dRBinMin,dRBinMax);
      h_jetTrkMaxPtRel[j] = new TH1D(Form("h_jetTrkMaxPtRel_J%i",j),Form("jetTrkMaxPtRel, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax);

    }

    h_jetTrkMaxPt[j]->Sumw2();
    h_jetTrkMaxPtOverJetPt[j]->Sumw2();
    h_jetTrkMaxEta[j]->Sumw2();
    h_jetTrkMaxPhi[j]->Sumw2();
    h_jetTrkMaxDR[j]->Sumw2();
    h_jetTrkMaxPtRel[j]->Sumw2();
    
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

  // apply HLT
  if(em->HLT_HIAK4PFJet60_v1 == 0) continue;


  
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
      double jetTrkMaxEta_i = em->jetTrkMaxEta[i];
      double jetTrkMaxPhi_i = em->jetTrkMaxPhi[i];
      double jetTrkMaxDR_i = em->jetTrkMaxDR[i];
      double jetTrkMaxPtRel_i = getPtRel(jetTrkMax_i,jetTrkMaxEta_i,jetTrkMaxPhi_i,recoJetPt_i,recoJetEta_i,recoJetPhi_i);

      if(doJetTrkMaxFilter){
	if(!passesJetTrkMaxFilter(jetTrkMax_i,recoJetPt_i)) continue;
      }
     
      if(doEtaPhiMask){
	if(etaPhiMask(recoJetEta_i,recoJetPhi_i)) continue;
      }

      //cout << "x" << endl;
     
     		
      if(TMath::Abs(recoJetEta_i) > 1.6 || recoJetPt_i < 80.) continue;
      if(jetTrkMax_i < 5.) continue;

      int jetPtIndex = getJetPtBin(recoJetPt_i);
      
      if(jetPtIndex < 0) continue;

      h_jetPt->Fill(recoJetPt_i,w);
      
      h_jetTrkMaxPt[0]->Fill(jetTrkMax_i,w);
      h_jetTrkMaxPtOverJetPt[0]->Fill(jetTrkMax_i/recoJetPt_i,w);
      h_jetTrkMaxEta[0]->Fill(jetTrkMaxEta_i,w);
      h_jetTrkMaxPhi[0]->Fill(jetTrkMaxPhi_i,w);
      h_jetTrkMaxDR[0]->Fill(jetTrkMaxDR_i,w);
      h_jetTrkMaxPtRel[0]->Fill(jetTrkMaxPtRel_i,w);

      h_jetTrkMaxPt[jetPtIndex]->Fill(jetTrkMax_i,w);
      h_jetTrkMaxPtOverJetPt[jetPtIndex]->Fill(jetTrkMax_i/recoJetPt_i,w);
      h_jetTrkMaxEta[jetPtIndex]->Fill(jetTrkMaxEta_i,w);
      h_jetTrkMaxPhi[jetPtIndex]->Fill(jetTrkMaxPhi_i,w);
      h_jetTrkMaxDR[jetPtIndex]->Fill(jetTrkMaxDR_i,w);
      h_jetTrkMaxPtRel[jetPtIndex]->Fill(jetTrkMaxPtRel_i,w);

  
    }
    // END recoJet LOOP

 

  } // end event loop


 
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");
  // >>>>>>>>>> write histograms

  h_jetPt->Write();

  for(int j = 0; j < NJetPtIndices; j++){

    h_jetTrkMaxPt[j]->Write();
    h_jetTrkMaxPtOverJetPt[j]->Write();
    h_jetTrkMaxEta[j]->Write();
    h_jetTrkMaxPhi[j]->Write();
    h_jetTrkMaxDR[j]->Write();
    h_jetTrkMaxPtRel[j]->Write();
      
  }


  wf->Close();
  return;
  // END WRITE

}
