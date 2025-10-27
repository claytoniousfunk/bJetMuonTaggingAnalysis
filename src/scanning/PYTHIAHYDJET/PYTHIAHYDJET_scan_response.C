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
#include "../../../headers/AnalysisSetupV2p3.h"
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
// JERCorrection params
#include "../../../headers/fitParameters/JERCorrectionParams_PYTHIA_mu12.h"
TF1 *fitFxn_hiBin, *fitFxn_vz, *fitFxn_jetPt, *fitFxn_PYTHIA_JESb, *fitFxn_PYTHIA_JERCorrection;

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
// JER-correction function
#include "../../../headers/fitFunctions/fitFxn_PYTHIA_JERCorrection.h"

// eta-phi mask function
#include "../../../headers/functions/etaPhiMask.h"
// getDr function
#include "../../../headers/functions/getDr.h"
// getJetPtBin function
#include "../../../headers/functions/getJetPtBin.h"
// getCentBin function
#include "../../../headers/functions/getCentBin.h" // fine cent bins
//#include "../../../headers/functions/getCentBin_v2.h" // course cent bins
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
#include "../../../headers/functions/getDatasetName/getDatasetName.h"
#include "../../../headers/functions/getInputFileName/getInputFileName.h"
#include "../../../headers/functions/configureOutputDatasetName/configureOutputDatasetName_PYTHIAHYDJET_response.h"


void PYTHIAHYDJET_scan_response(int group = 1){

  TString inputDataset = "";
  TString inputFileName = "";

  inputDataset = "/eos/user/c/cbennett/skims/output_skim_PH_DiJet_pTjet-5_withJetTriggers/";
  inputFileName = "PYTHIAHYDJET_DiJet_skim_output";
  TString input = Form("%s%s_%i.root",inputDataset.Data(),inputFileName.Data(),group);

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
						 doHadronPtRelReweight,
						 doBJetEnergyShift,
						 doBJetNeutrinoEnergyShift,						 
						 doJERCorrection,
						 doJESCorrection,						 
						 apply_JER_smear,
						 apply_JEU_shift_up,
						 apply_JEU_shift_down,
						 hiBinShift,
						 applyJet60Trigger,
						 applyJet80Trigger);


  //TString output = Form("%s%s/PYTHIAHYDJET_scan_output_%i.root",outputBaseDir.Data(),outputDatasetName.Data(),group);
  TString output = Form("%s%s_muTaggedJets/PYTHIAHYDJET_scan_output_%i.root",outputBaseDir.Data(),outputDatasetName.Data(),group);

  std::cout << "output dataset = " << output << std::endl;

  readConfig();

  // JET ENERGY CORRECTIONS
  vector<string> Files;
  
  Files.push_back("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_L2Relative_AK4PF.txt"); // LXPLUS

  JetCorrector JEC(Files);

  JetUncertainty JEU("../../../JetEnergyCorrections/Autumn18_HI_V8_MC_Uncertainty_AK4PF.txt");

  // WEIGHT FUNCTIONS

  //  initialize histograms
  // JETS

  TH2D *h_matchedRecoJetPt_genJetPt[NCentralityIndices][7];
  TH2D *h_matchedRecoJetPt_genJetPt_var[NCentralityIndices];
  TH2D *h_matchedRecoJetPtOverGenJetPt_genJetPt[NCentralityIndices][7];
  TH2D *h_matchedRecoJetPtOverGenJetPt_genJetEta[NCentralityIndices][7];
  TH2D *h_inclGenJetPt_flavor[NCentralityIndices];
  TH2D *h_inclGenJetPt_inclGenMuonTag_flavor[NCentralityIndices];
  TH2D *h_inclGenJetPt_inclRecoMuonTag_flavor[NCentralityIndices];


  // Define histograms
  const int N1 = 7;
  double ptAxis1[N1] = {80,100,120,150,200,300,500};
  const int N2 = 32;
  double ptAxis2[N2] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,500};



  for(int i = 0; i < NCentralityIndices; i++){

    if(i==0) {
      h_matchedRecoJetPt_genJetPt[i][0] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_allJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, allJets, hiBin %i - %i", centEdges[0]-10,centEdges[NCentralityIndices-1]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][1] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_bJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, bJets, hiBin %i - %i", centEdges[0]-10,centEdges[NCentralityIndices-1]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][2] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_cJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, cJets, hiBin %i - %i", centEdges[0]-10,centEdges[NCentralityIndices-1]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][3] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_udJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, udJets, hiBin %i - %i", centEdges[0]-10,centEdges[NCentralityIndices-1]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][4] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_sJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, sJets, hiBin %i - %i", centEdges[0]-10,centEdges[NCentralityIndices-1]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][5] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_gJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, gJets, hiBin %i - %i", centEdges[0]-10,centEdges[NCentralityIndices-1]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][6] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_xJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, xJets, hiBin %i - %i", centEdges[0]-10,centEdges[NCentralityIndices-1]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_inclGenJetPt_flavor[i] = new TH2D(Form("h_inclGenJetPt_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_inclGenMuonTag_flavor[i] = new TH2D(Form("h_inclGenJetPt_inclGenMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_inclRecoMuonTag_flavor[i] = new TH2D(Form("h_inclGenJetPt_inclRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[0],centEdges[NCentralityIndices-1]),NPtBins,ptMin,ptMax,27,-5,22);
    }
    else {
      h_matchedRecoJetPt_genJetPt[i][0] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_allJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, allJets, hiBin %i - %i", centEdges[i-1]-10,centEdges[i]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][1] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_bJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, bJets, hiBin %i - %i", centEdges[i-1]-10,centEdges[i]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][2] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_cJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, cJets, hiBin %i - %i", centEdges[i-1]-10,centEdges[i]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][3] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_udJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, udJets, hiBin %i - %i", centEdges[i-1]-10,centEdges[i]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][4] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_sJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, sJets, hiBin %i - %i", centEdges[i-1]-10,centEdges[i]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][5] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_gJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, gJets, hiBin %i - %i", centEdges[i-1]-10,centEdges[i]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_matchedRecoJetPt_genJetPt[i][6] = new TH2D(Form("h_matchedRecoJetPt_genJetPt_xJets_C%i",i),Form("genJetPt vs. matchedRecoJetPt, xJets, hiBin %i - %i", centEdges[i-1]-10,centEdges[i]-10),NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
      h_inclGenJetPt_flavor[i] = new TH2D(Form("h_inclGenJetPt_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_inclGenMuonTag_flavor[i] = new TH2D(Form("h_inclGenJetPt_inclGenMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. gen muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
      h_inclGenJetPt_inclRecoMuonTag_flavor[i] = new TH2D(Form("h_inclGenJetPt_inclRecoMuonTag_flavor_C%i",i),Form("JetFlavorID vs incl. gen p_{T}^{jet}, tagged with incl. reco muon, hiBin %i - %i",centEdges[i-1],centEdges[i]),NPtBins,ptMin,ptMax,27,-5,22);
    }

    h_matchedRecoJetPt_genJetPt[i][0]->Sumw2();
    h_matchedRecoJetPt_genJetPt[i][1]->Sumw2();
    h_matchedRecoJetPt_genJetPt[i][2]->Sumw2();
    h_matchedRecoJetPt_genJetPt[i][3]->Sumw2();
    h_matchedRecoJetPt_genJetPt[i][4]->Sumw2();
    h_matchedRecoJetPt_genJetPt[i][5]->Sumw2();
    h_matchedRecoJetPt_genJetPt[i][6]->Sumw2();
    h_inclGenJetPt_flavor[i]->Sumw2();
    h_inclGenJetPt_inclGenMuonTag_flavor[i]->Sumw2();
    h_inclGenJetPt_inclRecoMuonTag_flavor[i]->Sumw2();

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
  cout << "Loading muon triggers..." << endl;
  em->loadMuonTrigger(hltString);
  cout << "	Loading gen particles..." << endl;
  em->loadGenParticle();
  cout << "	Variables initilized!" << endl << endl ;
  int NEvents = em->evtTree->GetEntries();
  cout << "	Number of events = " << NEvents << endl;


  // define event filters
  em->regEventFilter(NeventFilters, eventFilters);

  TRandom *randomGenerator = new TRandom2();

  // jet-energy resolution fit function
  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,500);
  JER_fxn->SetParameter(0,1.26585e-01);
  JER_fxn->SetParameter(1,-9.72986e-01);
  JER_fxn->SetParameter(2,3.67352e-04);

  // define vz & hiBin reweighting functions
  loadFitFxn_vz();

  loadFitFxn_hiBin();

  // load JER correction fit fxn
  loadFitFxn_PYTHIA_JERCorrection();


  TFile *f_neutrino_energy_fraction_map = TFile::Open("/eos/cms/store/group/phys_heavyions/cbennett/maps/neutrino_energy_fraction_map.root");
  TH2D *neutrino_energy_fraction_map;
  TH1D *neutrino_energy_fraction_map_proj;
  f_neutrino_energy_fraction_map->GetObject("neutrino_energy_fraction_map",neutrino_energy_fraction_map);

  TFile *f_neutrino_energy_map = TFile::Open("/eos/cms/store/group/phys_heavyions/cbennett/maps/neutrino_energy_map.root");
  TH2D *neutrino_energy_map;
  TH1D *neutrino_energy_map_proj;
  f_neutrino_energy_map->GetObject("neutrino_energy_map",neutrino_energy_map);

  TFile *f_neutrino_tag_fraction = TFile::Open("/eos/cms/store/group/phys_heavyions/cbennett/maps/neutrino_tag_fraction.root");
  TH1D *neutrino_tag_fraction;
  f_neutrino_tag_fraction->GetObject("neutrino_tag_fraction",neutrino_tag_fraction);


  
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

    if(applyJet60Trigger){
      if(em->HLT_HICsAK4PFJet60Eta1p5_v1 == 0) continue;
    }
    if(applyJet80Trigger){
      //std::cout << "jet80 (event "<< evi << ") = " << em->HLT_HICsAK4PFJet80Eta1p5_v1 << std::endl;
      if(em->HLT_HICsAK4PFJet80Eta1p5_v1 == 0) continue;
    }

    // apply HLT
    int triggerDecision = em->HLT_HIL3Mu12_v1;
    int triggerDecision_Prescl = em->HLT_HIL3Mu12_v1_Prescl;
    //if(!triggerIsOn(triggerDecision,triggerDecision_Prescl)) continue;

    // RECO VARIABLES
	
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};

    int CentralityIndex = getCentBin(em->hiBin-hiBinShift);

    if(CentralityIndex < 0) continue;


    
    double w_reweight_hiBin = fitFxn_hiBin->Eval(em->hiBin-hiBinShift);

	
    //double w_reweight_vz = fitFxn_vz->Eval(em->vz);
    double w_reweight_vz = 1.0;
	

    double w = em->weight * w_reweight_vz * w_reweight_hiBin;

    // GEN JET LOOP
    for(int i = 0; i < em->ngj ; i++){

      // JET VARIABLES
      double x = em->genjetpt[i];
      double y = em->genjeteta[i];
      double z = em->genjetphi[i];

      double matchedRecoJetPt = 0.0;
      double matchedRawJetPt = 0.0;
      double recoMuonPt = 0.0;
      double recoMuonEta = 0.0;
			
      if(TMath::Abs(y) > etaMax) continue;

      // if(doRemoveHYDJETjet){
      // 	if(remove_HYDJET_jet(em->pthat, x)) continue;
      // }
	
      // GET FLAVOR FROM RECO MATCH
      bool hasRecoJetMatch = false;
      bool hasRecoJetMuon = false;
      bool hasRecoMuon = false;
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

	    if(em->mupt[k] > 14.0) hasRecoJetMuon = true;

	    JEC.SetJetPT(em->rawpt[k]);
	    JEC.SetJetEta(em->jeteta[k]);
	    JEC.SetJetPhi(em->jetphi[k]);

	    matchedRecoJetPt = JEC.GetCorrectedPT();
	    //matchedRecoJetPt = em->jetpt[k];
	    matchedRawJetPt = em->rawpt[k];
	    recoMuonPt = em->mupt[k];
	    recoMuonEta = em->mueta[k];

	    if(recoMuonPt > 14. && fabs(recoMuonEta) < 2.) hasRecoMuon = true;

	    if(doRemoveHYDJETjet){
	      if(remove_HYDJET_jet(em->pthat, matchedRecoJetPt)) continue;
	    }

	    JEU.SetJetPT(matchedRecoJetPt);
	    JEU.SetJetEta(em->jeteta[k]);
	    JEU.SetJetPhi(em->jetphi[k]);

	    // initialize
	    double correctedPt_down = 1.0;
	    double correctedPt_up = 1.0;

	    if(apply_JEU_shift_up){
	      correctedPt_up = matchedRecoJetPt * (1 + JEU.GetUncertainty().second);
	      matchedRecoJetPt = correctedPt_up;
	    }
	    else if(apply_JEU_shift_down){
	      correctedPt_down = matchedRecoJetPt * (1 - JEU.GetUncertainty().first);
	      matchedRecoJetPt = correctedPt_down;
	    }

	    double mu = 1.0;
	    double sigma = 0.2;
	    double smear = 0.0;

	    if(apply_JER_smear){
	      sigma = 0.663*JER_fxn->Eval(matchedRecoJetPt); // apply a 20% smear
	      smear = randomGenerator->Gaus(mu,sigma);
	      matchedRecoJetPt = matchedRecoJetPt * smear;
	    }

	    double mu_JERCorrection = 1.0;
	    double sigma_JERCorrection = 0.2;
	    double smear_JERCorrection = 0.0; // smeared pT
	    double k_JERCorrection = 0.0; // smearing parameter
	    if(doJERCorrection){
	      k_JERCorrection = TMath::Sqrt(fitFxn_PYTHIA_JERCorrection->Eval(x)*fitFxn_PYTHIA_JERCorrection->Eval(x) - 1.);
	      sigma_JERCorrection = k_JERCorrection*JER_fxn->Eval(matchedRecoJetPt);
	      smear_JERCorrection = randomGenerator->Gaus(mu_JERCorrection,sigma_JERCorrection);
	      matchedRecoJetPt = matchedRecoJetPt * smear_JERCorrection;
	    }

	    double skipDoBJetNeutrinoEnergyShift_diceRoll = 0.0;
	    double smear_doBJetNeutrinoEnergyShift = 0.0;
	    if(doBJetNeutrinoEnergyShift){
	    //if(doBJetNeutrinoEnergyShift && hasRecoJetMuon){
	      skipDoBJetNeutrinoEnergyShift_diceRoll = randomGenerator->Rndm();
	      if(skipDoBJetNeutrinoEnergyShift_diceRoll > neutrino_tag_fraction->GetBinContent(neutrino_tag_fraction->FindBin(matchedRecoJetPt))) continue;
	      neutrino_energy_map_proj = (TH1D*) neutrino_energy_map->ProjectionX("neutrino_energy_map_proj", neutrino_energy_map->GetYaxis()->FindBin(matchedRecoJetPt),neutrino_energy_map->GetYaxis()->FindBin(matchedRecoJetPt)+1);
	      smear_doBJetNeutrinoEnergyShift = neutrino_energy_map_proj->GetRandom();
	      matchedRecoJetPt += smear_doBJetNeutrinoEnergyShift;
	    }
	    
	  }	
	}

      } // end recoJet loop

      jetFlavorInt = em->refparton_flavorForB[recoJetFlavorFlag];
			
			
      // fill response matrix
      //if(hasRecoJetMatch && hasRecoJetMuon) {
      if(hasRecoJetMatch && hasRecoJetMuon && triggerIsOn(triggerDecision,triggerDecision_Prescl)) {
      //if(hasRecoJetMatch) {
	h_matchedRecoJetPt_genJetPt[0][0]->Fill(matchedRecoJetPt,x,w);
	h_matchedRecoJetPt_genJetPt[CentralityIndex][0]->Fill(matchedRecoJetPt,x,w);

	h_matchedRecoJetPt_genJetPt_var[0]->Fill(matchedRecoJetPt,x,w);
	h_matchedRecoJetPt_genJetPt_var[CentralityIndex]->Fill(matchedRecoJetPt,x,w);

	h_matchedRecoJetPtOverGenJetPt_genJetPt[0][0]->Fill(matchedRecoJetPt/x,x,w);
	h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][0]->Fill(matchedRecoJetPt/x,x,w);

	if(x>60){
	  h_matchedRecoJetPtOverGenJetPt_genJetEta[0][0]->Fill(matchedRecoJetPt/x,y,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][0]->Fill(matchedRecoJetPt/x,y,w);
	}


	if(fabs(jetFlavorInt) == 5){
	  h_matchedRecoJetPt_genJetPt[0][1]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPt_genJetPt[CentralityIndex][1]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][1]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][1]->Fill(matchedRecoJetPt/x,x,w);
				
	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][1]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][1]->Fill(matchedRecoJetPt/x,y,w);
	  }
	} 
	if(fabs(jetFlavorInt) == 4){
	  h_matchedRecoJetPt_genJetPt[0][2]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPt_genJetPt[CentralityIndex][2]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][2]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][2]->Fill(matchedRecoJetPt/x,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][2]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][2]->Fill(matchedRecoJetPt/x,y,w);
	  }

	} 
	if(fabs(jetFlavorInt) == 1 || fabs(jetFlavorInt) == 2){
	  h_matchedRecoJetPt_genJetPt[0][3]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPt_genJetPt[CentralityIndex][3]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][3]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][3]->Fill(matchedRecoJetPt/x,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][3]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][3]->Fill(matchedRecoJetPt/x,y,w);
	  }
	} 
	if(fabs(jetFlavorInt) == 3){
	  h_matchedRecoJetPt_genJetPt[0][4]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPt_genJetPt[CentralityIndex][4]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][4]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][4]->Fill(matchedRecoJetPt/x,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][4]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][4]->Fill(matchedRecoJetPt/x,y,w);
	  }

	}  
	if(jetFlavorInt == 21){
	  h_matchedRecoJetPt_genJetPt[0][5]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPt_genJetPt[CentralityIndex][5]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][5]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][5]->Fill(matchedRecoJetPt/x,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][5]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][5]->Fill(matchedRecoJetPt/x,y,w);
	  }

	}  
	if(jetFlavorInt == 0){
	  h_matchedRecoJetPt_genJetPt[0][6]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPt_genJetPt[CentralityIndex][6]->Fill(matchedRecoJetPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[0][6]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[CentralityIndex][6]->Fill(matchedRecoJetPt/x,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[0][6]->Fill(matchedRecoJetPt/x,y,w);
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[CentralityIndex][6]->Fill(matchedRecoJetPt/x,y,w);
	  }

	}

	if(hasRecoMuon){
	  h_inclGenJetPt_inclRecoMuonTag_flavor[0]->Fill(x,jetFlavorInt,w);
	  h_inclGenJetPt_inclRecoMuonTag_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
	}
      }
			
      h_inclGenJetPt_flavor[0]->Fill(x,jetFlavorInt,w);
      h_inclGenJetPt_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
      // begin gen-muon loop

      bool hasGenMuon = false;
      
      for(int j = 0; j < em->gpptp->size(); j++){

	if(hasGenMuon) continue;

	if(TMath::Abs(em->gppdgIDp->at(j)) != 13) continue;

	if(isWDecayMuon(em->gpptp->at(j),x)) continue; // skip if "WDecay" muon (has majority of jet pt)

	double genMuonPt_j = em->gpptp->at(j);
	double genMuonEta_j = em->gpetap->at(j);
	double genMuonPhi_j = em->gpphip->at(j);

	if(genMuonPt_j < muPtCut || fabs(genMuonEta_j) > 2.0) continue;

	if(getDr(genMuonEta_j,genMuonPhi_j,y,z) < deltaRCut){
	  hasGenMuon = true;
	  h_inclGenJetPt_inclGenMuonTag_flavor[0]->Fill(x,jetFlavorInt,w);
	  h_inclGenJetPt_inclGenMuonTag_flavor[CentralityIndex]->Fill(x,jetFlavorInt,w);
	}

      } // end gen-muon loop

      // begin reco-muon loop

      
		

		




    }
    // END GEN JET LOOP

	

  } // END EVENT LOOP
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  for(int j = 0; j < NCentralityIndices; j++){

    h_inclGenJetPt_flavor[j]->Write();
    h_inclGenJetPt_inclGenMuonTag_flavor[j]->Write();
    h_inclGenJetPt_inclRecoMuonTag_flavor[j]->Write();
    
    h_matchedRecoJetPt_genJetPt[j][0]->Write();
    h_matchedRecoJetPt_genJetPt[j][1]->Write();
    h_matchedRecoJetPt_genJetPt[j][2]->Write();
    h_matchedRecoJetPt_genJetPt[j][3]->Write();
    h_matchedRecoJetPt_genJetPt[j][4]->Write();
    h_matchedRecoJetPt_genJetPt[j][5]->Write();
    h_matchedRecoJetPt_genJetPt[j][6]->Write();


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







