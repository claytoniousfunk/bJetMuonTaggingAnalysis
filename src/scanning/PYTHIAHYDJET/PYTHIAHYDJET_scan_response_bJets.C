
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
#include "../../../headers/AnalysisSetupV2p1.h"
// vz-fit parameters
#include "../../../headers/fitParameters/vzFitParams_PH.h"
// hiBin-fit parameters
#include "../../../headers/fitParameters/hiBinFitParams.h"

TF1 *fitFxn_hiBin, *fitFxn_vz;
// vz-fit function
#include "../../../headers/fitFunctions/fitFxn_vz_PH.h"
// hiBin-fit function
#include "../../../headers/fitFunctions/fitFxn_hiBin.h"

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
// print introduction
#include "../../../headers/introductions/printIntroduction_PYTHIAHYDJET_response_v2.h"
// analysis config
#include "../../../headers/config/config_PYTHIAHYDJET.h"
// read config
#include "../../../headers/config/readConfig.h"


void PYTHIAHYDJET_scan_response_bJets(TString input = "root://cmsxrootd.fnal.gov//store/user/cbennett/PYTHIAHYDJET_DiJet_onlyMuJets_noRecoJetPtCut_5Jun23/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/crab_PYTHIAHYDJET_DiJet_onlyMuJets_noRecoJetPtCut_5Jun23/230606_054515/0000/HiForestAOD_1.root", TString output = "out.root"){

  
  printIntroduction();
  readConfig();

  // JET ENERGY CORRECTIONS
  vector<string> Files;
  
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_L2Relative_AK4PF.txt"); // LXPLUS

  JetCorrector JEC(Files);

  JetUncertainty JEU("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_Uncertainty_AK4PF.txt");



  // WEIGHT FUNCTIONS

  


  //  initialize histograms
  // JETS

  TH2D *h_matchedRecoJetPt_genJetPt[NCentralityIndices];
  TH2D *h_matchedRecoJetPt_genJetPt_var[NCentralityIndices];
  TH2D *h_matchedRecoJetPtOverGenJetPt_genJetPt[NCentralityIndices][7];
  TH2D *h_matchedRecoJetPtOverGenJetPt_genJetEta[NCentralityIndices][7];



  // Define histograms
  const int N1 = 7;
  double ptAxis1[N1] = {50,60,80,120,200,300,500};
  const int N2 = 32;
  double ptAxis2[N2] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,500};



  for(int i = 0; i < NCentralityIndices; i++){

    if(i==0) h_matchedRecoJetPt_genJetPt[i] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_C%i",i),Form("genJetPt vs. matchedRecoJetPt, hiBin %i - %i", centEdges[0]-10,centEdges[NCentralityIndices-1]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
    else h_matchedRecoJetPt_genJetPt[i] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_C%i",i),Form("genJetPt vs. matchedRecoJetPt, hiBin %i - %i", centEdges[i-1]-10,centEdges[i]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax) ;

    h_matchedRecoJetPt_genJetPt[i]->Sumw2(); 

    if(i==0) h_matchedRecoJetPt_genJetPt_var[i] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_var_C%i",i),Form("genJetPt vs. matchedRecoJetPt, hiBin %i - %i, var bins", centEdges[0]-10,centEdges[NCentralityIndices-1]-10),N1-1,ptAxis1,N2-1,ptAxis2);
    else h_matchedRecoJetPt_genJetPt_var[i] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_var_C%i",i),Form("genJetPt vs. matchedRecoJetPt, hiBin %i - %i, var bins", centEdges[i-1]-10,centEdges[i]-10),N1-1,ptAxis1,N2-1,ptAxis2) ;

    h_matchedRecoJetPt_genJetPt_var[i]->Sumw2();  
		
    if(i==0) {
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][0] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_allJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, all flavors, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][1] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_bJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, bJets, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][2] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_cJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, cJets, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][3] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_udJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, udJets, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][4] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_sJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, sJets, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][5] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_gJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, gJets, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][6] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_xJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, xJets, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NPtBins,ptMin,ptMax);

      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][0] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_allJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, all flavors, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][1] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_bJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, bJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][2] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_cJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, cJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][3] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_udJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, udJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][4] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_sJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, sJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][5] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_gJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, gJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][6] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_xJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, xJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[0],centEdges[NCentralityIndices-1]),500,0,5,NEtaBins,etaMin,etaMax);      
    }
    else{
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][0] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_allJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, all flavors, hiBin %i - %i",centEdges[i-1],centEdges[i]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][1] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_bJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, bJets, hiBin %i - %i",centEdges[i-1],centEdges[i]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][2] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_cJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, cJets, hiBin %i - %i",centEdges[i-1],centEdges[i]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][3] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_udJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, udJets, hiBin %i - %i",centEdges[i-1],centEdges[i]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][4] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_sJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, sJets, hiBin %i - %i",centEdges[i-1],centEdges[i]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][5] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_gJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, gJets, hiBin %i - %i",centEdges[i-1],centEdges[i]),500,0,5,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPtOverGenJetPt_genJetPt[i][6] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetPt_xJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetPt, xJets, hiBin %i - %i",centEdges[i-1],centEdges[i]),500,0,5,NPtBins,ptMin,ptMax); 

      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][0] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_allJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, all flavors, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[i-1],centEdges[i]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][1] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_bJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, bJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[i-1],centEdges[i]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][2] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_cJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, cJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[i-1],centEdges[i]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][3] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_udJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, udJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[i-1],centEdges[i]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][4] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_sJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, sJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[i-1],centEdges[i]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][5] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_gJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, gJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[i-1],centEdges[i]),500,0,5,NEtaBins,etaMin,etaMax);
      h_matchedRecoJetPtOverGenJetPt_genJetEta[i][6] = new TH2D(Form("h_matchedRecoJetPtOverGenJetPt_genJetEta_xJets_C%i",i),Form("matchedRecoJetPt/genJetPt vs genJetEta, xJets, hiBin %i - %i, p_{T}^{jet} > 50 GeV",centEdges[i-1],centEdges[i]),500,0,5,NEtaBins,etaMin,etaMax); 
    }  

    h_matchedRecoJetPtOverGenJetPt_genJetPt[i][0]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[i][1]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[i][2]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[i][3]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[i][4]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[i][5]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[i][6]->Sumw2();

    h_matchedRecoJetPtOverGenJetPt_genJetEta[i][0]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[i][1]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[i][2]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[i][3]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[i][4]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[i][5]->Sumw2();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[i][6]->Sumw2();

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
    if(em->hiBin > 190) continue;
    if(em->checkEventFilter()) continue;
    //cout << "Event #" << evi << " passed the global cuts!" << endl;

    // apply HLT
    int triggerDecision = em->HLT_HIL3Mu5_NHitQ10_v1;
    int triggerDecision_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl;
    //if(!triggerIsOn(triggerDecision,triggerDecision_Prescl)) continue;

    // RECO VARIABLES
	
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};

    int CentralityIndex = getCentBin(em->hiBin-10);

    if(CentralityIndex < 0) continue;


    fitFxn_hiBin = new TF1("fitFxn_hiBin","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x+[6]*x*x*x*x*x*x+[7]*x*x*x*x*x*x*x+[8]*x*x*x*x*x*x*x*x",0,190);
    fitFxn_hiBin->SetParameter(0,hiBinFitParam_0);
    fitFxn_hiBin->SetParameter(1,hiBinFitParam_1);
    fitFxn_hiBin->SetParameter(2,hiBinFitParam_2);
    fitFxn_hiBin->SetParameter(3,hiBinFitParam_3);
    fitFxn_hiBin->SetParameter(4,hiBinFitParam_4);
    fitFxn_hiBin->SetParameter(5,hiBinFitParam_5);
    fitFxn_hiBin->SetParameter(6,hiBinFitParam_6);
    fitFxn_hiBin->SetParameter(7,hiBinFitParam_7);
    fitFxn_hiBin->SetParameter(8,hiBinFitParam_8);

    double w_reweight_hiBin = fitFxn_hiBin->Eval(em->hiBin-10);


    TF1 *fitFxn_vz = new TF1("fitFxn_vz","[0]+[1]*x",-15,15);
    fitFxn_vz->SetParameter(0,1.02162);
    fitFxn_vz->SetParameter(1,-0.0215271);
	
    double w_reweight_vz = fitFxn_vz->Eval(em->vz);
	

    double w = em->weight * w_reweight_vz * w_reweight_hiBin;

    // GEN JET LOOP
    for(int i = 0; i < em->ngj ; i++){

      // JET VARIABLES
      double x = em->genjetpt[i];
      double y = em->genjeteta[i];
      double z = em->genjetphi[i];

      double matchedRecoJetPt = 0.0;
      double matchedRawJetPt = 0.0;
			
      if(TMath::Abs(y) > etaMax || x < jetPtCut) continue;
	
      // GET FLAVOR FROM RECO MATCH
      bool hasRecoJetMatch = false;
      bool hasRecoJetMuon = false;
      double minDr = 100.0;
      int recoJetFlavorFlag = 0;
      int jetFlavorInt = 19;
	
      for(int k = 0; k < em->njet; k++){
		
	double dr = getDr(em->jeteta[k],em->jetphi[k],y,z);

	if(dr < minDr){ 

	  minDr = dr;

	  if(minDr < epsilon_mm){
				
	    hasRecoJetMatch = true;
	    recoJetFlavorFlag = k;

	    if(em->mupt[k] > 7.0) hasRecoJetMuon = true;

	    JEC.SetJetPT(em->rawpt[k]);
	    JEC.SetJetEta(em->jeteta[k]);
	    JEC.SetJetPhi(em->jetphi[k]);

	    matchedRecoJetPt = JEC.GetCorrectedPT();
	    //matchedRecoJetPt = em->jetpt[k];
	    matchedRawJetPt = em->rawpt[k];

	    JEU.SetJetPT(matchedRecoJetPt);
	    JEU.SetJetEta(em->jeteta[k]);
	    JEU.SetJetPhi(em->jetphi[k]);

	    double correctedPt_down = x * (1 - JEU.GetUncertainty().first);
	    double correctedPt_up = x * (1 + JEU.GetUncertainty().second);

	    //matchedRecoJetPt = correctedPt_down;
	    //matchedRecoJetPt = correctedPt_up;

	    
	    //if(x>60) cout << "dR(reco,gen) = " << minDr << " | genPt = " << x << " | rawPt = " << em->rawpt[k] << " | jetPt = " << em->jetpt[k] << " | corrPt = " << JEC.GetCorrectedPT() << endl;

	  }	
	}

      }

      jetFlavorInt = em->refparton_flavorForB[recoJetFlavorFlag];
     

      if(TMath::Abs(jetFlavorInt) != 5) continue; // only accept bJets	


			
			
      // fill response matrix
      if(hasRecoJetMatch && hasRecoJetMuon) {
	h_matchedRecoJetPt_genJetPt[0]->Fill(matchedRecoJetPt,x,w);
	h_matchedRecoJetPt_genJetPt[CentralityIndex]->Fill(matchedRecoJetPt,x,w);

	h_matchedRecoJetPt_genJetPt_var[0]->Fill(matchedRecoJetPt,x,w);
	h_matchedRecoJetPt_genJetPt_var[CentralityIndex]->Fill(matchedRecoJetPt,x,w);

	h_matchedRecoJetPtOverGenJetPt_genJetPt[0][0]->Fill(matchedRecoJetPt/x,x,w);
	h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][0]->Fill(matchedRecoJetPt/x,x,w);

	if(x>60){
	  h_matchedRecoJetPtOverGenJetPt_genJetEta[0][0]->Fill(matchedRecoJetPt/x,y,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][0]->Fill(matchedRecoJetPt/x,y,w);
	}


	if(fabs(jetFlavorInt) == 5){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][1]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][1]->Fill(matchedRecoJetPt/x,x,w);
				
	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][1]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][1]->Fill(matchedRecoJetPt/x,y,w);
	  }
	} 
	if(fabs(jetFlavorInt) == 4){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][2]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][2]->Fill(matchedRecoJetPt/x,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][2]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][2]->Fill(matchedRecoJetPt/x,y,w);
	  }

	} 
	if(fabs(jetFlavorInt) == 1 || fabs(jetFlavorInt) == 2){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][3]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][3]->Fill(matchedRecoJetPt/x,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][3]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][3]->Fill(matchedRecoJetPt/x,y,w);
	  }
	} 
	if(fabs(jetFlavorInt) == 3){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][4]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][4]->Fill(matchedRecoJetPt/x,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][4]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][4]->Fill(matchedRecoJetPt/x,y,w);
	  }

	}  
	if(jetFlavorInt == 21){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][5]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][5]->Fill(matchedRecoJetPt/x,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][5]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][5]->Fill(matchedRecoJetPt/x,y,w);
	  }

	}  
	if(jetFlavorInt == 0){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][6]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][6]->Fill(matchedRecoJetPt/x,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][6]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][6]->Fill(matchedRecoJetPt/x,y,w);
	  }

	}
      }
			



		

		




    }
    // END GEN JET LOOP

	

  } // END EVENT LOOP
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  for(int j = 0; j < NCentralityIndices; j++){
    
    h_matchedRecoJetPt_genJetPt[j]->Write();
    h_matchedRecoJetPt_genJetPt_var[j]->Write();
    
    h_matchedRecoJetPtOverGenJetPt_genJetPt[j][0]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[j][1]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[j][2]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[j][3]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[j][4]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[j][5]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetPt[j][6]->Write();

    h_matchedRecoJetPtOverGenJetPt_genJetEta[j][0]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[j][1]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[j][2]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[j][3]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[j][4]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[j][5]->Write();
    h_matchedRecoJetPtOverGenJetPt_genJetEta[j][6]->Write();


  }






  wf->Close();
  return;
  // END WRITE



}







