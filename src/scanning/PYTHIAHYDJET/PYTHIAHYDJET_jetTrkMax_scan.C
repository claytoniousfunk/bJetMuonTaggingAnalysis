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
//#include "../../../headers/AnalysisSetupV2p2.h"
#include "../../../headers/AnalysisSetupV2p3.h"
//#include "../../../headers/AnalysisSetupV2p4.h"
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
#include "../../../headers/fitParameters/hadronPtRelFitParams_PbPb.h"
// dR parameters
#include "../../../headers/fitParameters/dRFitParams/dRFitParams_PbPb.h"
#include "../../../headers/fitParameters/muptFitParams.h"
#include "../../../headers/fitParameters/trkptrelFitParams_PbPb.h"

TF1 *fitFxn_hiBin, *fitFxn_vz, *fitFxn_jetPt, *fitFxn_hadronPtRel, *fitFxn_dR, *fitFxn_mupt, *fitFxn_trkptrel;
// hadronPtRel parameters
#include "../../../headers/fitFunctions/fitFxn_hadronPtRel.h"
// dR function
#include "../../../headers/fitFunctions/fitFxn_dR_PbPb.h"
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
#include "../../../headers/fitFunctions/fitFxn_mupt.h"
#include "../../../headers/fitFunctions/fitFxn_PbPb_trkptrel.h"
// eta-phi mask function
#include "../../../headers/functions/etaPhiMask.h"
// getDr function
#include "../../../headers/functions/getDr.h"
// getJetPtBin function
#include "../../../headers/functions/getJetPtBin.h"
// getCentBin function
//#include "../../../headers/functions/getCentBin_v2.h" // course centrality binning
#include "../../../headers/functions/getCentBin.h" // fine centrality binning
//#include "../../../headers/functions/getCentBin_v3.h" // ultra-fine centrality binning 
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
// dataset naming functions
#include "../../../headers/functions/configureOutputDatasetName/configureOutputDatasetName_PYTHIAHYDJET_jetTrkMax.h"

/*
  initialize your histograms here!
*/

TH1D *h_jetPt[NCentralityIndices];
TH1D *h_jetTrkMaxPt[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxPtOverJetPt[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxEta[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxPhi[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxDR[NCentralityIndices][NJetPtIndices];
TH1D *h_jetTrkMaxPtRel[NCentralityIndices][NJetPtIndices];
TH2D *h_jetTrkMaxPtRel_recoJetPt[NCentralityIndices][NTemplateIndices];
TH1D *h_dEta_jet_wta;
TH1D *h_dPhi_jet_wta;
TH1D *h_dR_jet_wta;
TH1D *h_dEta_trk_wta;
TH1D *h_dPhi_trk_wta;
TH1D *h_dR_trk_wta;


void PYTHIAHYDJET_jetTrkMax_scan(int group = 1){


  TString inputDataset = "";
  TString inputFileName = "";

  inputDataset = "/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skim_PH_DiJet_onlyJets_withTrackMaxInfo_withHLT/";
  inputFileName = "PYTHIAHYDJET_DiJet_skim_output";

  TString input = "";
  input = Form("%s%s_%i.root",inputDataset.Data(),inputFileName.Data(),group);

  std::cout << "input dataset = " << input << std::endl;

  TString outputBaseDir = "/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/";
  TString outputDatasetName = "";

  outputDatasetName = configureOutputDatasetName(generator,
						 doDiJetSample,
						 doMuJetSample,
						 doBJetSample,
						 doDiJetSample_batch1,
						 doDiJetSample_batch2,
						 doDiJetSample_batch3,
						 doDiJetSample_batch4,
						 doDiJetSample_batch5,
						 doDiJetSample_batch6,
						 doDiJetSample_batch7,
						 doDiJetSample_batch8,
						 doDiJetSample_batch9,
						 doDiJetSample_batch10,
						 doDiJetSample_batch11,
						 doDiJetSample_batch12,
						 doDiJetSample_batch13,
						 doDiJetSample_batch14,
						 doDiJetSample_batch15,
						 pthatcut,
						 doVzReweight,
						 doHiBinReweight,
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
						 doBJetEnergyShift,
						 doBJetNeutrinoEnergyShift,		 
						 doJERCorrection,
						 doJESCorrection,
						 apply_JER_smear,
						 apply_JEU_shift_up,
						 apply_JEU_shift_down,
						 hiBinShift);


  outputDatasetName.Append("_trkptrelReweight");
  
  TString output = Form("%s%s/PYTHIAHYDJET_scan_output_%i.root",outputBaseDir.Data(),outputDatasetName.Data(),group);

  std::cout << "output dataset = " << output << std::endl;
  
  // JET ENERGY CORRECTIONS
  vector<string> Files;
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_L2Relative_AK4PF.txt"); // LXPLUS

  JetCorrector JEC(Files);
  
  JetUncertainty JEU("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_Uncertainty_AK4PF.txt");
 
  readConfig();
 

  /*
    Define all your histograms here!!
  */

  h_dEta_trk_wta = new TH1D("h_dEta_trk_wta","#it{#Delta}#it{#eta}(leading-track,WTA-axis); #it{#Delta}#it{#eta}; Entries",200,-0.8,0.8);
  h_dPhi_trk_wta = new TH1D("h_dPhi_trk_wta","#it{#Delta}#it{#phi}(leading-track,WTA-axis); #it{#Delta}#it{#phi}; Entries",100,-0.8,0.8);
  h_dR_trk_wta = new TH1D("h_dR_trk_wta","#it{#Delta}#it{r}(leading-track,WTA-axis); #it{#Delta}#it{r}; Entries",400,0,0.4);
  h_dEta_trk_wta->Sumw2();
  h_dPhi_trk_wta->Sumw2();
  h_dR_trk_wta->Sumw2();  

  h_dEta_jet_wta = new TH1D("h_dEta_jet_wta","#it{#Delta}#it{#eta}(E-scheme,WTA-axis); #it{#Delta}#it{#eta}; Entries",200,-0.8,0.8);
  h_dPhi_jet_wta = new TH1D("h_dPhi_jet_wta","#it{#Delta}#it{#phi}(E-scheme,WTA-axis); #it{#Delta}#it{#phi}; Entries",100,-0.8,0.8);
  h_dR_jet_wta = new TH1D("h_dR_jet_wta","#it{#Delta}#it{r}(E-scheme,WTA-axis); #it{#Delta}#it{r}; Entries",400,0,0.4);
  h_dEta_jet_wta->Sumw2();
  h_dPhi_jet_wta->Sumw2();
  h_dR_jet_wta->Sumw2();  

  for(int i = 0; i < NCentralityIndices; i++){

    if(i==0) h_jetPt[i] = new TH1D(Form("h_jetPt_C%i",i),Form("jetPt, hiBin %i - %i", centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax);
    else h_jetPt[i] = new TH1D(Form("h_jetPt_C%i",i),Form("jetPt, hiBin %i - %i", centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax);

    for(int t = 0; t < NTemplateIndices; t++){

      if(i==0){
	h_jetTrkMaxPtRel_recoJetPt[i][t] = new TH2D(Form("h_jetTrkMaxPtRel_recoJetPt_C%iT%i",i,t),Form("track #it{p}_{T}^{rel} vs jet #it{p}_{T}, allJets, %i < hiBin < %i, %s",centEdges[0], centEdges[NCentralityIndices-1],templateIndexNames[t].c_str()),NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
      }
      else{
	h_jetTrkMaxPtRel_recoJetPt[i][t] = new TH2D(Form("h_jetTrkMaxPtRel_recoJetPt_C%iT%i",i,t),Form("track #it{p}_{T}^{rel} vs jet #it{p}_{T}, allJets, %i < hiBin < %i, %s",centEdges[i-1], centEdges[i],templateIndexNames[t].c_str()),NMuRelPtBins,muRelPtMin,muRelPtMax,NPtBins,ptMin,ptMax);
      }

      h_jetTrkMaxPtRel_recoJetPt[i][t]->Sumw2();
      
    }


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
  cout << "	Loading triggers..." << endl;
  em->loadMuonTrigger(hltString);
  //cout << "	Loading tracks..." << endl;
  //em->loadTrack();
  // cout << "	Loading gen particles..." << endl;
  // em->loadGenParticle();
  // cout << "	Variables initilized!" << endl << endl ;
  int NEvents = em->evtTree->GetEntries();
  cout << "	Number of events = " << NEvents << endl;
  int NJets = em->recoJetTree->GetEntries();
  cout << "     Number of jets = " << NJets << endl;

  // define event filters
  em->regEventFilter(NeventFilters, eventFilters);
  
  TRandom *randomGenerator = new TRandom2();

  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,300);
  JER_fxn->SetParameter(0,-1.91758e-05);
  JER_fxn->SetParameter(1,-1.79691e+00);
  JER_fxn->SetParameter(2,1.09880e+01);

  
  // load fit functions
  loadFitFxn_vz();
  loadFitFxn_hiBin();
  loadFitFxn_jetPt();
  loadFitFxn_hadronPtRel();
  loadFitFxn_dR();
  loadFitFxn_mupt();
  loadFitFxn_trkptrel();
 
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
    
    // apply HLT
    if(em->HLT_HICsAK4PFJet60Eta1p5_v1 == 0) continue;
    if(em->HLT_HICsAK4PFJet60Eta1p5_v1_Prescl < 0) continue;

    // if(em->HLT_HICsAK4PFJet80Eta1p5_v1 == 0) continue;
    // if(em->HLT_HICsAK4PFJet80Eta1p5_v1_Prescl < 0) continue;

    
    // calculate event weight
    
    double w_reweight_hiBin = 1.0;
    if(doHiBinReweight){
      w_reweight_hiBin = fitFxn_hiBin->Eval(hiBin_shifted);
    }
    
    double w_reweight_vz = 1.0;

    double w_pthat = em->weight;
    
    double w = w_pthat * w_reweight_hiBin * w_reweight_vz;
    
    if(w <= 0.0) continue;
    //if(w > 0.005) continue;
   
    int CentralityIndex = getCentBin(em->hiBin-hiBinShift);
    // int CentralityIndex = 1;
    
    if(CentralityIndex < 0) continue;
   
    // RECO JET LOOP
    for(int i = 0; i < em->njet ; i++){

      // JET VARIABLES
				
      JEC.SetJetPT(em->rawpt[i]);
      JEC.SetJetEta(em->jeteta[i]);
      JEC.SetJetPhi(em->jetphi[i]);

      double recoJetPt_i = JEC.GetCorrectedPT();  // recoJetPt
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

      // experimental dR smear
      double mu_dRsmear = 0.0; // set to 0 for additive smear, set to 1 for multiplicative
      double sigma_dRsmear = 0.01;
      double val_dRsmear = 0.0;
      if(doJetAxisSmearing){
	val_dRsmear = randomGenerator->Gaus(mu_dRsmear,sigma_dRsmear);
	recoJetEta_i = recoJetEta_i + randomGenerator->Gaus(mu_dRsmear,sigma_dRsmear); 
	recoJetPhi_i = recoJetPhi_i + randomGenerator->Gaus(mu_dRsmear,sigma_dRsmear);
      }
      // recalculate dR(leading-hadron,jet) with smeared jet axis
      jetTrkMaxDR_i = getDr(jetTrkMaxEta_i,jetTrkMaxPhi_i,recoJetEta_i,recoJetPhi_i);

      double jetTrkMaxPtRel_i = getPtRel(jetTrkMax_i,jetTrkMaxEta_i,jetTrkMaxPhi_i,recoJetPt_i,recoJetEta_i,recoJetPhi_i);

      double dEta_trk_wta_i = jetTrkMaxEta_i - recoJetEtaWTA_i;
      double dPhi_trk_wta_i = acos(cos(jetTrkMaxPhi_i - recoJetPhiWTA_i));
      double dR_trk_wta_i = getDr(jetTrkMaxEta_i,jetTrkMaxPhi_i,recoJetEtaWTA_i,recoJetPhiWTA_i);

      double dEta_jet_wta_i = recoJetEta_i - recoJetEtaWTA_i;
      double dPhi_jet_wta_i = acos(cos(recoJetPhi_i - recoJetPhiWTA_i));
      double dR_jet_wta_i = getDr(recoJetEta_i,recoJetPhi_i,recoJetEtaWTA_i,recoJetPhiWTA_i);      

      // cout << endl;
      // cout << "em->jet_wta_eta[i] = " << em->jet_wta_eta[i] << endl;
      // cout << "em->jeteta[i] = " << em->jeteta[i] << endl;
      // cout << endl;
      
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

      if(doJetTrkMaxFilter){
	if(!passesJetTrkMaxFilter(jetTrkMax_i,recoJetPt_i)) continue;
      }

      if(doEtaPhiMask){
	if(etaPhiMask(recoJetEta_i,recoJetPhi_i)) continue;
      }

      if(doRemoveHYDJETjet){
	if(remove_HYDJET_jet(em->pthat, recoJetPt_i)) continue;
      }

      // apply no reweight
      // double w_jet = w;

      // apply mupt reweight
      // double w_jet = w * fitFxn_mupt->Eval(jetTrkMax_i);

      // apply trkptrel reweight
      double w_jet = w * fitFxn_trkptrel->Eval(jetTrkMaxPtRel_i);
      
      // apply dR reweight
      // double w_jet = w * fitFxn_dR->Eval(jetTrkMaxDR_i);

      // apply hadronPtRel reweight
      // double w_jet = w * fitFxn_hadronPtRel->Eval(jetTrkMaxPtRel_i);


          		
      int matchedPartonFlavor = em->matchedPartonFlavor[i];
      int refPartonFlavorForB = em->refparton_flavorForB[i];
      int hadronFlavorInt = em->matchedHadronFlavor[i];
      int bHadronNumber = em->bHadronNumber[i];

      int jetFlavorInt = matchedPartonFlavor;

      if(fabs(jetFlavorInt) == 5 && bHadronNumber == 2) jetFlavorInt = 17; // 17 = bJet from gluon-splitting 
      
      // jet kinematic cuts
      if(TMath::Abs(recoJetEta_i) > 1.6 || recoJetPt_i < 80.) continue;
      if(jetTrkMax_i < 14.) continue;
		        
      int jetPtIndex = getJetPtBin(recoJetPt_i);

      if(jetPtIndex < 0) continue;

      h_dEta_trk_wta->Fill(dEta_trk_wta_i, w_jet);
      h_dPhi_trk_wta->Fill(dPhi_trk_wta_i, w_jet);
      h_dR_trk_wta->Fill(dR_trk_wta_i, w_jet);

      h_dEta_jet_wta->Fill(dEta_jet_wta_i, w_jet);
      h_dPhi_jet_wta->Fill(dPhi_jet_wta_i, w_jet);
      h_dR_jet_wta->Fill(dR_jet_wta_i, w_jet);

      h_jetPt[0]->Fill(recoJetPt_i,w_jet);
      h_jetPt[CentralityIndex]->Fill(recoJetPt_i,w_jet);

      h_jetTrkMaxPt[0][0]->Fill(jetTrkMax_i,w_jet);
      h_jetTrkMaxPtOverJetPt[0][0]->Fill(jetTrkMax_i/recoJetPt_i,w_jet);
      h_jetTrkMaxEta[0][0]->Fill(jetTrkMaxEta_i,w_jet);
      h_jetTrkMaxPhi[0][0]->Fill(jetTrkMaxPhi_i,w_jet);
      h_jetTrkMaxDR[0][0]->Fill(jetTrkMaxDR_i,w_jet);
      h_jetTrkMaxPtRel[0][0]->Fill(jetTrkMaxPtRel_i,w_jet);

      h_jetTrkMaxPt[CentralityIndex][0]->Fill(jetTrkMax_i,w_jet);
      h_jetTrkMaxPtOverJetPt[CentralityIndex][0]->Fill(jetTrkMax_i/recoJetPt_i,w_jet);
      h_jetTrkMaxEta[CentralityIndex][0]->Fill(jetTrkMaxEta_i,w_jet);
      h_jetTrkMaxPhi[CentralityIndex][0]->Fill(jetTrkMaxPhi_i,w_jet);
      h_jetTrkMaxDR[CentralityIndex][0]->Fill(jetTrkMaxDR_i,w_jet);
      h_jetTrkMaxPtRel[CentralityIndex][0]->Fill(jetTrkMaxPtRel_i,w_jet);

      h_jetTrkMaxPt[0][jetPtIndex]->Fill(jetTrkMax_i,w_jet);
      h_jetTrkMaxPtOverJetPt[0][jetPtIndex]->Fill(jetTrkMax_i/recoJetPt_i,w_jet);
      h_jetTrkMaxEta[0][jetPtIndex]->Fill(jetTrkMaxEta_i,w_jet);
      h_jetTrkMaxPhi[0][jetPtIndex]->Fill(jetTrkMaxPhi_i,w_jet);
      h_jetTrkMaxDR[0][jetPtIndex]->Fill(jetTrkMaxDR_i,w_jet);
      h_jetTrkMaxPtRel[0][jetPtIndex]->Fill(jetTrkMaxPtRel_i,w_jet);

      h_jetTrkMaxPt[CentralityIndex][jetPtIndex]->Fill(jetTrkMax_i,w_jet);
      h_jetTrkMaxPtOverJetPt[CentralityIndex][jetPtIndex]->Fill(jetTrkMax_i/recoJetPt_i,w_jet);
      h_jetTrkMaxEta[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxEta_i,w_jet);
      h_jetTrkMaxPhi[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxPhi_i,w_jet);
      h_jetTrkMaxDR[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxDR_i,w_jet);
      h_jetTrkMaxPtRel[CentralityIndex][jetPtIndex]->Fill(jetTrkMaxPtRel_i,w_jet);

      for(int t = 0; t < NTemplateIndices; t++){

	h_jetTrkMaxPtRel_recoJetPt[0][t]->Fill(jetTrkMaxPtRel_i,jetPtArray[t],w_jet);
	h_jetTrkMaxPtRel_recoJetPt[CentralityIndex][t]->Fill(jetTrkMaxPtRel_i,jetPtArray[t],w_jet);
	
      }

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

  h_dEta_trk_wta->Write();
  h_dPhi_trk_wta->Write();
  h_dR_trk_wta->Write();  

  h_dEta_jet_wta->Write();
  h_dPhi_jet_wta->Write();
  h_dR_jet_wta->Write();

  for(int i = 0; i < NCentralityIndices; i++){

    h_jetPt[i]->Write();

    for(int t = 0; t < NTemplateIndices; t++){
      h_jetTrkMaxPtRel_recoJetPt[i][t]->Write();
    }
    
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
