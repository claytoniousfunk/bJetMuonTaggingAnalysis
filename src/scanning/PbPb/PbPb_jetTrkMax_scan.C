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
//#include "../../../headers/AnalysisSetupV2p3.h"
#include "../../../headers/AnalysisSetupV2p4.h" // ultra-fine cent bins
// eta-phi mask function
#include "../../../headers/functions/etaPhiMask.h"
// getDr function
#include "../../../headers/functions/getDr.h"
// getJetPtBin function
#include "../../../headers/functions/getJetPtBin.h"
// getCentBin function
//#include "../../../headers/functions/getCentBin_v2.h" // course cent bins
//#include "../../../headers/functions/getCentBin.h" // nominal cent bins
#include "../../../headers/functions/getCentBin_v3.h" // ultra-fine
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
#include "../../../headers/config/config_PbPb_DiJet_withTrackMaxInfo.h"
// read config
#include "../../../headers/config/readConfig.h"


/*
  initialize histograms
*/

TH1D *h_jetPt[NCentralityIndices];
TH1D *h_jetTrkMaxPt[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxPtOverJetPt[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxEta[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxPhi[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxDR[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxPtRel[NCentralityIndices][NJetPtIndices];


///////////////////////  start the program
void PbPb_jetTrkMax_scan(int group = 1){

  
  TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_PbPb_DiJet_onlyJets_withTrackMaxInfo_partial/PbPb_DiJet_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PbPb_DiJet_onlyJets_withTrackMaxInfo_partial_jetTrkMax_jet60_ultraFineCentBins_2025-07-14/PbPb_scan_output_%i.root",group);
  
  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_DATA_L2Relative_AK4PF.txt"); // L2Relative correction
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_DATA_L2L3Residual_AK4PF.txt"); // L2L3Residual correction
  JetCorrector JEC(Files);
  /// print out some info
  printIntroduction_PbPb_scan_V3p7();
  readConfig();
  // define histograms
    
  /*
    Define all your histograms here!!
  */

  for(int i = 0; i < NCentralityIndices; i++){

    if(i==0) h_jetPt[i] = new TH1D(Form("h_jetPt_C%i",i),Form("jetPt, hiBin %i - %i", centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax);
    else h_jetPt[i] = new TH1D(Form("h_jetPt_C%i",i),Form("jetPt, hiBin %i - %i", centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax);
    
    for(int j = 0; j < NJetPtIndices; j++){
	
      if(i==0 && j==0){

	h_jetTrkMaxPt[i][j] = new TH1D(Form("h_jetTrkMaxPt_C%iJ%i",i,j),Form("jetTrkMaxPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),500,0,500);
	h_jetTrkMaxPtOverJetPt[i][j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_C%iJ%i",i,j),Form("jetTrkMaxPt / jetPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
	h_jetTrkMaxEta[i][j] = new TH1D(Form("h_jetTrkMaxEta_C%iJ%i",i,j),Form("jetTrkMaxEta, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_jetTrkMaxPhi[i][j] = new TH1D(Form("h_jetTrkMaxPhi_C%iJ%i",i,j),Form("jetTrkMaxPhi, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax);
	h_jetTrkMaxDR[i][j] = new TH1D(Form("h_jetTrkMaxDR_C%iJ%i",i,j),Form("jetTrkMaxDR, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NdRBins,dRBinMin,dRBinMax);
	h_jetTrkMaxPtRel[i][j] = new TH1D(Form("h_jetTrkMaxPtRel_C%iJ%i",i,j),Form("jetTrkMaxPtRel, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax);

	
      }
      else if(i==0){

	h_jetTrkMaxPt[i][j] = new TH1D(Form("h_jetTrkMaxPt_C%iJ%i",i,j),Form("jetTrkMaxPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),500,0,500);
	h_jetTrkMaxPtOverJetPt[i][j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_C%iJ%i",i,j),Form("jetTrkMaxPt / jetPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
	h_jetTrkMaxEta[i][j] = new TH1D(Form("h_jetTrkMaxEta_C%iJ%i",i,j),Form("jetTrkMaxEta, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_jetTrkMaxPhi[i][j] = new TH1D(Form("h_jetTrkMaxPhi_C%iJ%i",i,j),Form("jetTrkMaxPhi, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax);
	h_jetTrkMaxDR[i][j] = new TH1D(Form("h_jetTrkMaxDR_C%iJ%i",i,j),Form("jetTrkMaxDR, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NdRBins,dRBinMin,dRBinMax);
	h_jetTrkMaxPtRel[i][j] = new TH1D(Form("h_jetTrkMaxPtRel_C%iJ%i",i,j),Form("jetTrkMaxPtRel, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[0],centEdges[NCentralityIndices-1],jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax);

      }
      else if(j==0){

	h_jetTrkMaxPt[i][j] = new TH1D(Form("h_jetTrkMaxPt_C%iJ%i",i,j),Form("jetTrkMaxPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),500,0,500);
	h_jetTrkMaxPtOverJetPt[i][j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_C%iJ%i",i,j),Form("jetTrkMaxPt / jetPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
	h_jetTrkMaxEta[i][j] = new TH1D(Form("h_jetTrkMaxEta_C%iJ%i",i,j),Form("jetTrkMaxEta, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_jetTrkMaxPhi[i][j] = new TH1D(Form("h_jetTrkMaxPhi_C%iJ%i",i,j),Form("jetTrkMaxPhi, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax);
	h_jetTrkMaxDR[i][j] = new TH1D(Form("h_jetTrkMaxDR_C%iJ%i",i,j),Form("jetTrkMaxDR, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NdRBins,dRBinMin,dRBinMax);
	h_jetTrkMaxPtRel[i][j] = new TH1D(Form("h_jetTrkMaxPtRel_C%iJ%i",i,j),Form("jetTrkMaxPtRel, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax);

      }
      else{

	h_jetTrkMaxPt[i][j] = new TH1D(Form("h_jetTrkMaxPt_C%iJ%i",i,j),Form("jetTrkMaxPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),500,0,500);
	h_jetTrkMaxPtOverJetPt[i][j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_C%iJ%i",i,j),Form("jetTrkMaxPt / jetPt, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
	h_jetTrkMaxEta[i][j] = new TH1D(Form("h_jetTrkMaxEta_C%iJ%i",i,j),Form("jetTrkMaxEta, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax);
	h_jetTrkMaxPhi[i][j] = new TH1D(Form("h_jetTrkMaxPhi_C%iJ%i",i,j),Form("jetTrkMaxPhi, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax);
	h_jetTrkMaxDR[i][j] = new TH1D(Form("h_jetTrkMaxDR_C%iJ%i",i,j),Form("jetTrkMaxDR, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NdRBins,dRBinMin,dRBinMax);
	h_jetTrkMaxPtRel[i][j] = new TH1D(Form("h_jetTrkMaxPtRel_C%iJ%i",i,j),Form("jetTrkMaxPtRel, hiBin %i - %i, p_{T}^{jet} %3.0f - %3.0f", centEdges[i-1],centEdges[i],jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax);

      }

      h_jetTrkMaxPt[i][j]->Sumw2();
      h_jetTrkMaxPtOverJetPt[i][j]->Sumw2();
      h_jetTrkMaxEta[i][j]->Sumw2();
      h_jetTrkMaxPhi[i][j]->Sumw2();
      h_jetTrkMaxDR[i][j]->Sumw2();
      h_jetTrkMaxPtRel[i][j]->Sumw2();
      
    }

    h_jetPt[i]->Sumw2();
    
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
  // cout << "	Loading muon..." << endl;
  // em->loadMuon(muonTreeString);
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

    // apply HLT
    if(em->HLT_HICsAK4PFJet60Eta1p5_v1 == 0) continue;
    //if(em->HLT_HICsAK4PFJet80Eta1p5_v1 == 0) continue;


    // In data, event weight = 1
    double w = 1.0;
	
    int CentralityIndex = getCentBin(em->hiBin);

    // int CentralityIndex = 1; // temporarily bypass the call to hiBin.  Need to get that branch from a reforest.  Skip for now and just use 0-100$
    
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

      double jetTrkMaxPtRel_i = getPtRel(jetTrkMax_i,jetTrkMaxEta_i,jetTrkMaxPhi_i,recoJetPt_i,recoJetEta_i,recoJetPhi_i);

           
      //x = x*smear;
      if(doJetTrkMaxFilter){
	if(!passesJetTrkMaxFilter(jetTrkMax_i,recoJetPt_i)) continue;
      }      

      //cout << "rawPt = " << em->rawpt[i] << "  |  jetPt = " << em->jetpt[i] << "  |  corrPt = " << x << endl;
      if(doEtaPhiMask){
	if(etaPhiMask(recoJetEta_i,recoJetPhi_i)) continue;
      }

      //cout << "Event " << evi << ", jet " << i << endl;
      //cout << "~~~~  jetPt = " << em->jetpt[i] << ", corrJetPt = " << x << endl;

		
      // jet kinematic cuts
      if(TMath::Abs(recoJetEta_i) > 1.6 || recoJetPt_i < 80.) continue;
      if(jetTrkMax_i < 5.) continue;
        
      int jetPtIndex = getJetPtBin(recoJetPt_i);

      if(jetPtIndex < 0) continue;

      // Fill the jet/event histograms

      h_jetPt[0]->Fill(recoJetPt_i,w);
      h_jetPt[CentralityIndex]->Fill(recoJetPt_i,w);

	
      h_jetTrkMaxPt[0][0]->Fill(jetTrkMax_i,w);
      h_jetTrkMaxPtOverJetPt[0][0]->Fill(jetTrkMax_i/recoJetPt_i,w);
      h_jetTrkMaxEta[0][0]->Fill(jetTrkMaxEta_i,w);
      h_jetTrkMaxPhi[0][0]->Fill(jetTrkMaxPhi_i,w);
      h_jetTrkMaxDR[0][0]->Fill(jetTrkMaxDR_i,w);
      h_jetTrkMaxPtRel[0][0]->Fill(jetTrkMaxPtRel_i,w);

      h_jetTrkMaxPt[CentralityIndex][0]->Fill(jetTrkMax_i,w);
      h_jetTrkMaxPtOverJetPt[CentralityIndex][0]->Fill(jetTrkMax_i/recoJetPt_i,w);
      h_jetTrkMaxEta[CentralityIndex][0]->Fill(jetTrkMaxEta_i,w);
      h_jetTrkMaxPhi[CentralityIndex][0]->Fill(jetTrkMaxPhi_i,w);
      h_jetTrkMaxDR[CentralityIndex][0]->Fill(jetTrkMaxDR_i,w);
      h_jetTrkMaxPtRel[CentralityIndex][0]->Fill(jetTrkMaxPtRel_i,w);

      h_jetTrkMaxPt[0][jetPtIndex]->Fill(jetTrkMax_i,w);
      h_jetTrkMaxPtOverJetPt[0][jetPtIndex]->Fill(jetTrkMax_i/recoJetPt_i,w);
      h_jetTrkMaxEta[0][jetPtIndex]->Fill(jetTrkMaxEta_i,w);
      h_jetTrkMaxPhi[0][jetPtIndex]->Fill(jetTrkMaxPhi_i,w);
      h_jetTrkMaxDR[0][jetPtIndex]->Fill(jetTrkMaxDR_i,w);
      h_jetTrkMaxPtRel[0][jetPtIndex]->Fill(jetTrkMaxPtRel_i,w);

      h_jetTrkMaxPt[CentralityIndex][jetPtIndex]->Fill(jetTrkMax_i,w);
      h_jetTrkMaxPtOverJetPt[CentralityIndex][jetPtIndex]->Fill(jetTrkMax_i/recoJetPt_i,w);
      h_jetTrkMaxEta[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxEta_i,w);
      h_jetTrkMaxPhi[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxPhi_i,w);
      h_jetTrkMaxDR[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxDR_i,w);
      h_jetTrkMaxPtRel[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxPtRel_i,w);

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

  h_jetPt[i]->Write();
  
  for(int j = 0; j < NJetPtIndices; j++){

    h_jetTrkMaxPt[i][j]->Write();
    h_jetTrkMaxPtOverJetPt[i][j]->Write();
    h_jetTrkMaxEta[i][j]->Write();
    h_jetTrkMaxPhi[i][j]->Write();
    h_jetTrkMaxDR[i][j]->Write();
    h_jetTrkMaxPtRel[i][j]->Write();
      
  }

 }
 wf->Close();
 return;
  // END WRITE

}
