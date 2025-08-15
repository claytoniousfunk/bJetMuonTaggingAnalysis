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
#include "../../../headers/fitParameters/trkptrelFitParams_pp.h"

TF1 *fitFxn_hiBin, *fitFxn_vz, *fitFxn_jetPt, *fitFxn_PYTHIA_JESb, *fitFxn_PYTHIA_bJetNeutrinoEnergy, *fitFxn_dR, *fitFxn_hadronPtRel, *fitFxn_trkptrel;
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
#include "../../../headers/fitFunctions/fitFxn_PbPb_trkptrel.h"


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
// dataset naming functions
#include "../../../headers/functions/configureOutputDatasetName/configureOutputDatasetName_PYTHIA_jetTrkMax.h"



//~~~~~~~~~~~  initialize histograms ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TH1D *h_jetPt;
TH1D *h_jetTrkMaxPt[NJetPtIndices];
TH1D *h_jetTrkMaxPtOverJetPt[NJetPtIndices];
TH1D *h_jetTrkMaxEta[NJetPtIndices];
TH1D *h_jetTrkMaxPhi[NJetPtIndices];
TH1D *h_jetTrkMaxDR[NJetPtIndices];
TH1D *h_jetTrkMaxDR_qJets[NJetPtIndices]; // quark jets
TH1D *h_jetTrkMaxDR_gJets[NJetPtIndices]; // gluon jets
TH1D *h_jetTrkMaxPtRel[NJetPtIndices];
TH2D *h_jetTrkMaxPtRel_recoJetPt[NTemplateIndices];
TH1D *h_dEta_jet_wta;
TH1D *h_dPhi_jet_wta;
TH1D *h_dR_jet_wta;
TH1D *h_dEta_trk_wta;
TH1D *h_dPhi_trk_wta;
TH1D *h_dR_trk_wta;

void PYTHIA_jetTrkMax_scan(int group = 1){

  TString inputDataset = "";
  TString inputFileName = "";


  inputDataset = "/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skim_PYTHIA_DiJet_withJetTrackMaxInfo/";
  inputFileName = "PYTHIA_DiJet_skim_output";


  TString input = "";
  input = Form("%s%s_%i.root",inputDataset.Data(),inputFileName.Data(),group);

  std::cout << "input dataset = " << input << std::endl;

  TString outputBaseDir = "/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/";
    
  TString outputDatasetName = "";

  outputDatasetName = configureOutputDatasetName(generator,
						 doDiJetSample,
						 pthatcut,
						 doVzReweight,
						 doJetPtReweight,
						 doGenJetPthatFilter,
						 doLeadingXjetDumpFilter,
						 doXdumpReweight,
						 doJetTrkMaxFilter,
						 doRemoveHYDJETjet,
						 doEtaPhiMask,
						 doDRReweight,
						 doWeightCut,
						 doJetAxisSmearing,
						 mu_phi,
						 sigma_phi,
						 mu_eta,
						 sigma_eta,
						 doHadronPtRelReweight,
						 doHadronPtRelReweightToMuon,
						 doBJetEnergyShift,
						 doBJetNeutrinoEnergyShift,
						 doJERCorrection,
						 doJESCorrection,				   
						 apply_JER_smear,
						 apply_JEU_shift_up,
						 apply_JEU_shift_down);

  TString output = Form("%s%s/PYTHIAHYDJET_scan_output_%i.root",outputBaseDir.Data(),outputDatasetName.Data(),group);

  std::cout << "output dataset = " << output << std::endl;


  // TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skim_PYTHIA_DiJet_withJetTrackMaxInfo/PYTHIA_DiJet_skim_output_%i.root",group);

  // TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIA_DiJet_jetTrkMax_pThat-20_trkpT-14_jetPtReweight_vzReweight_dRReweight_trkptrelReweight-byJetBin_2025-06-30/PYTHIA_DiJet_scan_output_%i.root",group);

  printIntroduction_PYTHIA_scan_V3p7();
  readConfig();

  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt"); // LXPLUS
  JetCorrector JEC(Files);

  JetUncertainty JEU("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_Uncertainty_AK4PF.txt");

  /////////////  Define histograms
  h_jetPt = new TH1D("h_jetPt","jetPt",NPtBins,ptMin,ptMax);
  h_jetPt->Sumw2();
  
  h_dEta_trk_wta = new TH1D("h_dEta_trk_wta","#it{#Delta}#it{#eta}(leading-track,WTA-axis); #it{#Delta}#it{#eta}; Entries",100,-0.8,0.8);
  h_dPhi_trk_wta = new TH1D("h_dPhi_trk_wta","#it{#Delta}#it{#phi}(leading-track,WTA-axis); #it{#Delta}#it{#phi}; Entries",50,-0.8,0.8);
  h_dR_trk_wta = new TH1D("h_dR_trk_wta","#it{#Delta}#it{r}(leading-track,WTA-axis); #it{#Delta}#it{r}; Entries",100,0,0.4);
  h_dEta_trk_wta->Sumw2();
  h_dPhi_trk_wta->Sumw2();
  h_dR_trk_wta->Sumw2();

  h_dEta_jet_wta = new TH1D("h_dEta_jet_wta","#it{#Delta}#it{#eta}(E-scheme,WTA-axis); #it{#Delta}#it{#eta}; Entries",100,-0.8,0.8);
  h_dPhi_jet_wta = new TH1D("h_dPhi_jet_wta","#it{#Delta}#it{#phi}(E-scheme,WTA-axis); #it{#Delta}#it{#phi}; Entries",50,-0.8,0.8);
  h_dR_jet_wta = new TH1D("h_dR_jet_wta","#it{#Delta}#it{r}(E-scheme,WTA-axis); #it{#Delta}#it{r}; Entries",100,0,0.4);
  h_dEta_jet_wta->Sumw2();
  h_dPhi_jet_wta->Sumw2();
  h_dR_jet_wta->Sumw2();


  // loop through template indices
  for(int t = 0; t < NTemplateIndices; t++){

    h_jetTrkMaxPtRel_recoJetPt[t] = new TH2D(Form("h_jetTrkMaxPtRel_recoJetPt_T%i",t),Form("track #it{p}_{T}^{rel} vs jet $it{p}_{T}, allJets, %s", templateIndexNames[t].c_str()),NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
    h_jetTrkMaxPtRel_recoJetPt[t]->Sumw2();
    
  }


  
  // loop through jet pT indices
  for(int j = 0; j < NJetPtIndices; j++){

    if(j==0){
      
      h_jetTrkMaxPt[j] = new TH1D(Form("h_jetTrkMaxPt_J%i",j),Form("jetTrkMaxPt, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,100);
      h_jetTrkMaxPtOverJetPt[j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_J%i",j),Form("jetTrkMaxPt / jetPt, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),100,0,1);
      h_jetTrkMaxEta[j] = new TH1D(Form("h_jetTrkMaxEta_J%i",j),Form("jetTrkMaxEta, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NTrkEtaBins,trkEtaMin,trkEtaMax);
      h_jetTrkMaxPhi[j] = new TH1D(Form("h_jetTrkMaxPhi_J%i",j),Form("jetTrkMaxPhi, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NPhiBins,phiMin,phiMax);
      h_jetTrkMaxDR[j] = new TH1D(Form("h_jetTrkMaxDR_J%i",j),Form("jetTrkMaxDR, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NdRBins,dRBinMin,dRBinMax);
      h_jetTrkMaxDR_qJets[j] = new TH1D(Form("h_jetTrkMaxDR_qJets_J%i",j),Form("jetTrkMaxDR, quark jets, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NdRBins,dRBinMin,dRBinMax);
      h_jetTrkMaxDR_gJets[j] = new TH1D(Form("h_jetTrkMaxDR_gJets_J%i",j),Form("jetTrkMaxDR, gluon jets, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NdRBins,dRBinMin,dRBinMax);
      h_jetTrkMaxPtRel[j] = new TH1D(Form("h_jetTrkMaxPtRel_J%i",j),Form("jetTrkMaxPtRel, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[0],jetPtEdges[NJetPtIndices-1]),NMuRelPtBins,muRelPtMin,muRelPtMax);

    }

    else{

      h_jetTrkMaxPt[j] = new TH1D(Form("h_jetTrkMaxPt_J%i",j),Form("jetTrkMaxPt, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,100);
      h_jetTrkMaxPtOverJetPt[j] = new TH1D(Form("h_jetTrkMaxPtOverJetPt_J%i",j),Form("jetTrkMaxPt / jetPt, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),100,0,1);
      h_jetTrkMaxEta[j] = new TH1D(Form("h_jetTrkMaxEta_J%i",j),Form("jetTrkMaxEta, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NTrkEtaBins,trkEtaMin,trkEtaMax);
      h_jetTrkMaxPhi[j] = new TH1D(Form("h_jetTrkMaxPhi_J%i",j),Form("jetTrkMaxPhi, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NPhiBins,phiMin,phiMax);
      h_jetTrkMaxDR[j] = new TH1D(Form("h_jetTrkMaxDR_J%i",j),Form("jetTrkMaxDR, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NdRBins,dRBinMin,dRBinMax);
      h_jetTrkMaxDR_qJets[j] = new TH1D(Form("h_jetTrkMaxDR_qJets_J%i",j),Form("jetTrkMaxDR, quark jets, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NdRBins,dRBinMin,dRBinMax);
      h_jetTrkMaxDR_gJets[j] = new TH1D(Form("h_jetTrkMaxDR_gJets_J%i",j),Form("jetTrkMaxDR, gluon jets, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NdRBins,dRBinMin,dRBinMax);
      h_jetTrkMaxPtRel[j] = new TH1D(Form("h_jetTrkMaxPtRel_J%i",j),Form("jetTrkMaxPtRel, p_{T}^{jet} %3.0f - %3.0f",jetPtEdges[j-1],jetPtEdges[j]),NMuRelPtBins,muRelPtMin,muRelPtMax);

    }

    h_jetTrkMaxPt[j]->Sumw2();
    h_jetTrkMaxPtOverJetPt[j]->Sumw2();
    h_jetTrkMaxEta[j]->Sumw2();
    h_jetTrkMaxPhi[j]->Sumw2();
    h_jetTrkMaxDR[j]->Sumw2();
    h_jetTrkMaxDR_qJets[j]->Sumw2();
    h_jetTrkMaxDR_gJets[j]->Sumw2();
    h_jetTrkMaxPtRel[j]->Sumw2();
    
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

  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,300);
  JER_fxn->SetParameter(0,-1.91758e-05);
  JER_fxn->SetParameter(1,-1.79691e+00);
  JER_fxn->SetParameter(2,1.09880e+01);

  TF1 *ptrel_reweight_fxn = new TF1("ptrel_reweight_fxn","[0] + [1]*x + [2]*x*x + [3]*x*x*x",0,5);
  double ptrel_reweight_param_0[NJetPtIndices-1] = {1.45261e+00,1.56644e+00,1.47540e+00,1.54805e+00,1.74787e+00,1.77217e+00};
  double ptrel_reweight_param_1[NJetPtIndices-1] = {-8.93318e-01,-1.02836e+00,-8.21530e-01,-8.53191e-01,-1.16147e+00,-1.13383e+00};
  double ptrel_reweight_param_2[NJetPtIndices-1] = {3.29664e-01,3.26709e-01,2.34548e-01,2.19521e-01,3.27115e-01,3.01231e-01};
  double ptrel_reweight_param_3[NJetPtIndices-1] = {-2.88554e-02,-2.60798e-02,-1.86332e-02,-1.65286e-02,-2.61209e-02,-2.32847e-02};

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

  loadFitFxn_trkptrel();


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

    if(em->HLT_HIAK4PFJet60_v1 == 0) continue;
    //if(em->HLT_HIAK4PFJet80_v1 == 0) continue;
    //if(em->HLT_HIAK4PFJet100_v1 == 0) continue;
    
    double w_reweight_vz = 1.0;
    if(doVzReweight){
      w_reweight_vz = fitFxn_vz->Eval(em->vz);
    }
    

    double w_pthat = em->weight;

    double w = w_pthat * w_reweight_vz;

    // RECO JET LOOP
    for(int i = 0; i < em->njet ; i++){

      // JET VARIABLES
		
      JEC.SetJetPT(em->rawpt[i]);
      JEC.SetJetEta(em->jeteta[i]);
      JEC.SetJetPhi(em->jetphi[i]);

      double recoJetPt_i = JEC.GetCorrectedPT();  // apply manual JEC
      double recoJetPt_JERSmear_i = recoJetPt_i;
      double recoJetPt_JEUShiftUp_i = recoJetPt_i;
      double recoJetPt_JEUShiftDown_i = recoJetPt_i;
      double recoJetEta_i = em->jeteta[i]; // recoJetEta
      double recoJetPhi_i = em->jetphi[i]; // recoJetPhi
      double recoJetEtaWTA_i = em->jet_wta_eta[i]; // recoJetEta with WTA axis
      double recoJetPhiWTA_i = em->jet_wta_phi[i]; // recoJetPhi with WTA axis
      double jetTrkMax_i = em->jetTrkMax[i];
      double jetTrkMaxEta_i = em->jetTrkMaxEta[i];
      double jetTrkMaxPhi_i = em->jetTrkMaxPhi[i];
      double jetTrkMaxDR_i = em->jetTrkMaxDR[i];
      double jetTrkMaxDRManual_i = getDr(jetTrkMaxEta_i,jetTrkMaxPhi_i,recoJetEta_i,recoJetPhi_i);
      //std::cout << "out-of-box dR = " << jetTrkMaxDR_i << " | manual dR = " << jetTrkMaxDRManual_i << "\n";

      // experimental dR smear
      double val_etaSmear = randomGenerator->Gaus(mu_eta,sigma_eta);
      double val_phiSmear = randomGenerator->Gaus(mu_phi,sigma_phi);
      double recoJetEtaSmear_i = recoJetEta_i + val_etaSmear;
      double recoJetPhiSmear_i = recoJetPhi_i + val_phiSmear;
      if(doJetAxisSmearing){
	recoJetEta_i = recoJetEtaSmear_i;
	recoJetPhi_i = recoJetPhiSmear_i;
      }
      double jetTrkMaxPtRel_i = getPtRel(jetTrkMax_i,jetTrkMaxEta_i,jetTrkMaxPhi_i,recoJetPt_i,recoJetEta_i,recoJetPhi_i);
      // recalculate dR(leading-hadron,jet) with smeared jet axis
      jetTrkMaxDR_i = getDr(jetTrkMaxEta_i,jetTrkMaxPhi_i,recoJetEtaSmear_i,recoJetPhiSmear_i);

      double dEta_trk_wta_i = jetTrkMaxEta_i - recoJetEtaWTA_i;
      double dPhi_trk_wta_i = acos(cos(jetTrkMaxPhi_i - recoJetPhiWTA_i));
      double dR_trk_wta_i = getDr(jetTrkMaxEta_i,jetTrkMaxPhi_i,recoJetEtaWTA_i,recoJetPhiWTA_i);

      double dEta_jet_wta_i = recoJetEta_i - recoJetEtaWTA_i;
      double dPhi_jet_wta_i = acos(cos(recoJetPhi_i - recoJetPhiWTA_i));
      double dR_jet_wta_i = getDr(recoJetEta_i,recoJetPhi_i,recoJetEtaWTA_i,recoJetPhiWTA_i);

      JEU.SetJetPT(recoJetPt_i);
      JEU.SetJetEta(recoJetEta_i);
      JEU.SetJetPhi(recoJetPhi_i);

      double correctedPt_down = 1.0;
      double correctedPt_up = 1.0;

      correctedPt_up = recoJetPt_i * (1 + JEU.GetUncertainty().second);
      recoJetPt_JEUShiftUp_i = correctedPt_up;
 
      correctedPt_down = recoJetPt_i * (1 - JEU.GetUncertainty().first);
      recoJetPt_JEUShiftDown_i = correctedPt_down;

      double mu = 1.0;
      double sigma = 0.2;
      double smear = 0.0;

      sigma = 0.663*JER_fxn->Eval(recoJetPt_i); // apply a 20% smear
      smear = randomGenerator->Gaus(mu,sigma);
      recoJetPt_JERSmear_i = recoJetPt_i * smear;

      double jetPtArray[NTemplateIndices] = {recoJetPt_i,recoJetPt_JERSmear_i,recoJetPt_JEUShiftUp_i,recoJetPt_JEUShiftDown_i};
      
      double w_jetPt = 1.0;

      //double w_jet = w * w_jetPt * fitFxn_dR->Eval(jetTrkMaxDR_i);
      double w_jet = w * w_jetPt;

      
      if(doDRReweight){
	w_jet = w * fitFxn_dR->Eval(jetTrkMaxDR_i);
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
      
      if(TMath::Abs(recoJetEta_i) > 1.6 || recoJetPt_i < 80.) continue;
      if(jetTrkMax_i < 14.) continue;
		
      int jetPtIndex = getJetPtBin(recoJetPt_i);

      if(jetPtIndex < 0) continue;

      /////////////////////////////////////
      // apply trkptrel reweight

      ptrel_reweight_fxn->SetParameter(0,ptrel_reweight_param_0[jetPtIndex-1]);
      ptrel_reweight_fxn->SetParameter(1,ptrel_reweight_param_1[jetPtIndex-1]);
      ptrel_reweight_fxn->SetParameter(2,ptrel_reweight_param_2[jetPtIndex-1]);
      ptrel_reweight_fxn->SetParameter(3,ptrel_reweight_param_3[jetPtIndex-1]);

      if(doHadronPtRelReweightToMuon){
	w_jet = w_jet * ptrel_reweight_fxn->Eval(jetTrkMaxPtRel_i);
      }

      //

      ////////////////////////////////////
      

      int partonFlavor = em->partonFlavor[i];
      int hadronFlavor = em->hadronFlavor[i];
      int jetFlavorInt = partonFlavor;
      int bHadronNumber = em->bHadronNumber[i];

      if(fabs(jetFlavorInt) == 5 && bHadronNumber == 2) jetFlavorInt = 17; // 17 = bJet from gluon-splitting

      h_dEta_trk_wta->Fill(dEta_trk_wta_i, w_jet);
      h_dPhi_trk_wta->Fill(dPhi_trk_wta_i, w_jet);
      h_dR_trk_wta->Fill(dR_trk_wta_i, w_jet);

      h_dEta_jet_wta->Fill(dEta_jet_wta_i, w_jet);
      h_dPhi_jet_wta->Fill(dPhi_jet_wta_i, w_jet);
      h_dR_jet_wta->Fill(dR_jet_wta_i, w_jet);
      
      h_jetPt->Fill(recoJetPt_i,w_jet);
      
      h_jetTrkMaxPt[0]->Fill(jetTrkMax_i,w_jet);
      h_jetTrkMaxPtOverJetPt[0]->Fill(jetTrkMax_i/recoJetPt_i,w_jet);
      h_jetTrkMaxEta[0]->Fill(jetTrkMaxEta_i,w_jet);
      h_jetTrkMaxPhi[0]->Fill(jetTrkMaxPhi_i,w_jet);
      h_jetTrkMaxDR[0]->Fill(jetTrkMaxDR_i,w_jet);
      if(jetFlavorInt == 21) h_jetTrkMaxDR_gJets[0]->Fill(jetTrkMaxDR_i,w_jet);
      else h_jetTrkMaxDR_qJets[0]->Fill(jetTrkMaxDR_i,w_jet);
      h_jetTrkMaxPtRel[0]->Fill(jetTrkMaxPtRel_i,w_jet);

      h_jetTrkMaxPt[jetPtIndex]->Fill(jetTrkMax_i,w_jet);
      h_jetTrkMaxPtOverJetPt[jetPtIndex]->Fill(jetTrkMax_i/recoJetPt_i,w_jet);
      h_jetTrkMaxEta[jetPtIndex]->Fill(jetTrkMaxEta_i,w_jet);
      h_jetTrkMaxPhi[jetPtIndex]->Fill(jetTrkMaxPhi_i,w_jet);
      h_jetTrkMaxDR[jetPtIndex]->Fill(jetTrkMaxDR_i,w_jet);
      if(jetFlavorInt == 21) h_jetTrkMaxDR_gJets[jetPtIndex]->Fill(jetTrkMaxDR_i,w_jet);
      else h_jetTrkMaxDR_qJets[jetPtIndex]->Fill(jetTrkMaxDR_i,w_jet);
      h_jetTrkMaxPtRel[jetPtIndex]->Fill(jetTrkMaxPtRel_i,w_jet);

      for(int t = 0; t < NTemplateIndices; t++){

	h_jetTrkMaxPtRel_recoJetPt[t]->Fill(jetTrkMaxPtRel_i,jetPtArray[t],w_jet);
	
      }
      

    }
    // END recoJet LOOP
	

  } // END EVENT LOOP
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  // >>>>>>>>>> write histograms

  h_jetPt->Write();
  h_dEta_trk_wta->Write();
  h_dPhi_trk_wta->Write();
  h_dR_trk_wta->Write();  
  h_dEta_jet_wta->Write();
  h_dPhi_jet_wta->Write();
  h_dR_jet_wta->Write();  
  
  for(int j = 0; j < NJetPtIndices; j++){

    h_jetTrkMaxPt[j]->Write();
    h_jetTrkMaxPtOverJetPt[j]->Write();
    h_jetTrkMaxEta[j]->Write();
    h_jetTrkMaxPhi[j]->Write();
    h_jetTrkMaxDR[j]->Write();
    h_jetTrkMaxDR_qJets[j]->Write();
    h_jetTrkMaxDR_gJets[j]->Write();
    h_jetTrkMaxPtRel[j]->Write();
      
  }

  for(int t = 0; t < NTemplateIndices; t++){
    h_jetTrkMaxPtRel_recoJetPt[t]->Write();
  }
  
  wf->Close();
  return;
  // END WRITE



}







