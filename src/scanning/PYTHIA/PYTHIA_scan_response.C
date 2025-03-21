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
//#include "../../../headers/fitParameters/vzFitParams_PYTHIA_mu5.h"
//#include "../../../headers/fitParameters/vzFitParams_PYTHIA_mu7.h"
#include "../../../headers/fitParameters/vzFitParams_PYTHIA_mu12.h"
// jetPt-fit parameters
//#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu5.h"
//#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu7.h"
#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu12.h"
// JESb fit params
//#include "../../../headers/fitParameters/JESbFitParams_PYTHIA_mu7.h"
#include "../../../headers/fitParameters/JESbFitParams_PYTHIA_mu12.h"
// JERCorrection params
#include "../../../headers/fitParameters/JERCorrectionParams_PYTHIA_mu12.h"
TF1 *fitFxn_hiBin, *fitFxn_vz, *fitFxn_jetPt, *fitFxn_PYTHIA_JESb, *fitFxn_PYTHIA_JERCorrection;
// vz-fit function
#include "../../../headers/fitFunctions/fitFxn_vz_PYTHIA.h"
// jetPt-fit function
#include "../../../headers/fitFunctions/fitFxn_jetPt.h"
// JESb-fit function
#include "../../../headers/fitFunctions/fitFxn_PYTHIA_JESb.h"
// JER-correction function
#include "../../../headers/fitFunctions/fitFxn_PYTHIA_JERCorrection.h"

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


void PYTHIA_scan_response(int group = 1){

  TString input = Form("/eos/user/c/cbennett/skims/output_skim_PYTHIA_DiJet_withGS_withNeutrinos/PYTHIA_DiJet_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIA_response_pThat-15_inclJets/PYTHIA_DiJet_scan_output_%i.root",group);


  
  //printIntroduction();
  readConfig();

  // JET ENERGY CORRECTIONS
  vector<string> Files;
  
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt"); // LXPLUS

  JetCorrector JEC(Files);

  JetUncertainty JEU("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_Uncertainty_AK4PF.txt");

  // WEIGHT FUNCTIONS

  


  //  initialize histograms
  // JETS

  TH2D *h_matchedRecoJetPt_genJetPt[7];
  TH2D *h_matchedRecoJetPt_genNeutrinoTag_genJetPt[7];
  TH2D *h_matchedNeutrinoPt_recoJetPt[7];
  TH2D *h_matchedNeutrinoPt_genJetPt[7];
  TH2D *h_matchedRecoJetPt_genJetPt_var;
  TH2D *h_matchedRecoJetPtOverGenJetPt_genJetPt[7];
  TH2D *h_matchedRecoJetPtOverGenJetPt_recoJetPt[7];
  TH2D *h_matchedRecoJetPtOverGenJetPt_genJetEta[7];
  TH2D *h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[7];
  TH2D *h_matchedNeutrinoPtOverGenJetPt_genJetPt[7];
  TH2D *h_matchedNeutrinoPtOverGenJetPt_recoJetPt[7];
  TH2D *h_matchedNeutrinoPtOverRecoJetPt_genJetPt[7];



  // Define histograms
  const int N1 = 9;
  double ptAxis1[N1] = {50,60,80,100,120,150,200,300,500};
  const int N2 = 32;
  double ptAxis2[N2] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,500};



  

  h_matchedRecoJetPt_genJetPt[0] = new TH2D("h_matchedRecoJetPt_genJetPt_allJets","genJetPt vs. matchedRecoJetPt, allJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genJetPt[1] = new TH2D("h_matchedRecoJetPt_genJetPt_bJets","genJetPt vs. matchedRecoJetPt, bJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genJetPt[2] = new TH2D("h_matchedRecoJetPt_genJetPt_cJets","genJetPt vs. matchedRecoJetPt, cJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genJetPt[3] = new TH2D("h_matchedRecoJetPt_genJetPt_udJets","genJetPt vs. matchedRecoJetPt, udJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genJetPt[4] = new TH2D("h_matchedRecoJetPt_genJetPt_sJets","genJetPt vs. matchedRecoJetPt, sJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genJetPt[5] = new TH2D("h_matchedRecoJetPt_genJetPt_gJets","genJetPt vs. matchedRecoJetPt, gJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genJetPt[6] = new TH2D("h_matchedRecoJetPt_genJetPt_xJets","genJetPt vs. matchedRecoJetPt, xJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);

  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[0] = new TH2D("h_matchedRecoJetPt_genNeutrinoTag_genJetPt_allJets","genJetPt vs. matchedRecoJetPt, #nu-tagged jets, allJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[1] = new TH2D("h_matchedRecoJetPt_genNeutrinoTag_genJetPt_bJets","genJetPt vs. matchedRecoJetPt, #nu-tagged jets, bJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[2] = new TH2D("h_matchedRecoJetPt_genNeutrinoTag_genJetPt_cJets","genJetPt vs. matchedRecoJetPt, #nu-tagged jets, cJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[3] = new TH2D("h_matchedRecoJetPt_genNeutrinoTag_genJetPt_udJets","genJetPt vs. matchedRecoJetPt, #nu-tagged jets, udJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[4] = new TH2D("h_matchedRecoJetPt_genNeutrinoTag_genJetPt_sJets","genJetPt vs. matchedRecoJetPt, #nu-tagged jets, sJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[5] = new TH2D("h_matchedRecoJetPt_genNeutrinoTag_genJetPt_gJets","genJetPt vs. matchedRecoJetPt, #nu-tagged jets, gJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[6] = new TH2D("h_matchedRecoJetPt_genNeutrinoTag_genJetPt_xJets","genJetPt vs. matchedRecoJetPt, #nu-tagged jets, xJets",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);

  h_matchedNeutrinoPt_recoJetPt[0] = new TH2D("h_matchedNeutrinoPt_recoJetPt_allJets","neutrino pT vs. recoJet pT, allJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_recoJetPt[1] = new TH2D("h_matchedNeutrinoPt_recoJetPt_bJets","neutrino pT vs. recoJet pT, bJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_recoJetPt[2] = new TH2D("h_matchedNeutrinoPt_recoJetPt_cJets","neutrino pT vs. recoJet pT, cJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_recoJetPt[3] = new TH2D("h_matchedNeutrinoPt_recoJetPt_udJets","neutrino pT vs. recoJet pT, udJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_recoJetPt[4] = new TH2D("h_matchedNeutrinoPt_recoJetPt_sJets","neutrino pT vs. recoJet pT, sJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_recoJetPt[5] = new TH2D("h_matchedNeutrinoPt_recoJetPt_gJets","neutrino pT vs. recoJet pT, gJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_recoJetPt[6] = new TH2D("h_matchedNeutrinoPt_recoJetPt_xJets","neutrino pT vs. recoJet pT, xJets",100,0,100,NPtBins,ptMin,ptMax);

  h_matchedNeutrinoPt_genJetPt[0] = new TH2D("h_matchedNeutrinoPt_genJetPt_allJets","neutrino pT vs. genJet pT, allJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_genJetPt[1] = new TH2D("h_matchedNeutrinoPt_genJetPt_bJets","neutrino pT vs. genJet pT, bJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_genJetPt[2] = new TH2D("h_matchedNeutrinoPt_genJetPt_cJets","neutrino pT vs. genJet pT, cJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_genJetPt[3] = new TH2D("h_matchedNeutrinoPt_genJetPt_udJets","neutrino pT vs. genJet pT, udJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_genJetPt[4] = new TH2D("h_matchedNeutrinoPt_genJetPt_sJets","neutrino pT vs. genJet pT, sJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_genJetPt[5] = new TH2D("h_matchedNeutrinoPt_genJetPt_gJets","neutrino pT vs. genJet pT, gJets",100,0,100,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPt_genJetPt[6] = new TH2D("h_matchedNeutrinoPt_genJetPt_xJets","neutrino pT vs. genJet pT, xJets",100,0,100,NPtBins,ptMin,ptMax);
  
  
  h_matchedRecoJetPt_genJetPt[0]->Sumw2();
  h_matchedRecoJetPt_genJetPt[1]->Sumw2();
  h_matchedRecoJetPt_genJetPt[2]->Sumw2();
  h_matchedRecoJetPt_genJetPt[3]->Sumw2();
  h_matchedRecoJetPt_genJetPt[4]->Sumw2();
  h_matchedRecoJetPt_genJetPt[5]->Sumw2();
  h_matchedRecoJetPt_genJetPt[6]->Sumw2();

  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[0]->Sumw2();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[1]->Sumw2();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[2]->Sumw2();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[3]->Sumw2();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[4]->Sumw2();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[5]->Sumw2();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[6]->Sumw2();

  h_matchedNeutrinoPt_recoJetPt[0]->Sumw2();
  h_matchedNeutrinoPt_recoJetPt[1]->Sumw2();
  h_matchedNeutrinoPt_recoJetPt[2]->Sumw2();
  h_matchedNeutrinoPt_recoJetPt[3]->Sumw2();
  h_matchedNeutrinoPt_recoJetPt[4]->Sumw2();
  h_matchedNeutrinoPt_recoJetPt[5]->Sumw2();
  h_matchedNeutrinoPt_recoJetPt[6]->Sumw2();


  h_matchedNeutrinoPt_genJetPt[0]->Sumw2();
  h_matchedNeutrinoPt_genJetPt[1]->Sumw2();
  h_matchedNeutrinoPt_genJetPt[2]->Sumw2();
  h_matchedNeutrinoPt_genJetPt[3]->Sumw2();
  h_matchedNeutrinoPt_genJetPt[4]->Sumw2();
  h_matchedNeutrinoPt_genJetPt[5]->Sumw2();
  h_matchedNeutrinoPt_genJetPt[6]->Sumw2();

  
  h_matchedRecoJetPt_genJetPt_var = new TH2D("h_matchedRecoJetPt_genJetPt_var","genJetPt vs. matchedRecoJetPt, var bins",N1-1,ptAxis1,N2-1,ptAxis2);
    
  h_matchedRecoJetPt_genJetPt_var->Sumw2();  
		
    
  h_matchedRecoJetPtOverGenJetPt_genJetPt[0] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_allJets","matchedRecoJetPt/genJetPt vs genJetPt, all flavors",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[1] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_bJets","matchedRecoJetPt/genJetPt vs genJetPt, bJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[2] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_cJets","matchedRecoJetPt/genJetPt vs genJetPt, cJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[3] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_udJets","matchedRecoJetPt/genJetPt vs genJetPt, udJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[4] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_sJets","matchedRecoJetPt/genJetPt vs genJetPt, sJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[5] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_gJets","matchedRecoJetPt/genJetPt vs genJetPt, gJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[6] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_xJets","matchedRecoJetPt/genJetPt vs genJetPt, xJets",500,0,5,NPtBins,ptMin,ptMax);

  h_matchedRecoJetPtOverGenJetPt_recoJetPt[0] = new TH2D("h_matchedRecoJetPtOverGenJetPt_recoJetPt_allJets","matchedRecoJetPt/genJetPt vs recoJetPt, all flavors",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[1] = new TH2D("h_matchedRecoJetPtOverGenJetPt_recoJetPt_bJets","matchedRecoJetPt/genJetPt vs recoJetPt, bJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[2] = new TH2D("h_matchedRecoJetPtOverGenJetPt_recoJetPt_cJets","matchedRecoJetPt/genJetPt vs recoJetPt, cJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[3] = new TH2D("h_matchedRecoJetPtOverGenJetPt_recoJetPt_udJets","matchedRecoJetPt/genJetPt vs recoJetPt, udJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[4] = new TH2D("h_matchedRecoJetPtOverGenJetPt_recoJetPt_sJets","matchedRecoJetPt/genJetPt vs recoJetPt, sJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[5] = new TH2D("h_matchedRecoJetPtOverGenJetPt_recoJetPt_gJets","matchedRecoJetPt/genJetPt vs recoJetPt, gJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[6] = new TH2D("h_matchedRecoJetPtOverGenJetPt_recoJetPt_xJets","matchedRecoJetPt/genJetPt vs recoJetPt, xJets",500,0,5,NPtBins,ptMin,ptMax);

  h_matchedRecoJetPtOverGenJetPt_genJetEta[0] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_allJets","matchedRecoJetPt/genJetPt vs genJetEta, all flavors",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[1] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_bJets","matchedRecoJetPt/genJetPt vs genJetEta, bJets",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[2] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_cJets","matchedRecoJetPt/genJetPt vs genJetEta, cJets",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[3] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_udJets","matchedRecoJetPt/genJetPt vs genJetEta, udJets",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[4] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_sJets","matchedRecoJetPt/genJetPt vs genJetEta, sJets",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[5] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_gJets","matchedRecoJetPt/genJetPt vs genJetEta, gJets",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[6] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_xJets","matchedRecoJetPt/genJetPt vs genJetEta, xJets",500,0,5,NEtaBins,etaMin,etaMax);

  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[0] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_recoJetPt_allJets","matchedNeutrinoPt / recoJetPt vs. recoJetPt, all flavors",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[1] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_recoJetPt_bJets","matchedNeutrinoPt / recoJetPt vs. recoJetPt, bJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[2] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_recoJetPt_cJets","matchedNeutrinoPt / recoJetPt vs. recoJetPt, cJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[3] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_recoJetPt_udJets","matchedNeutrinoPt / recoJetPt vs. recoJetPt, udJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[4] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_recoJetPt_sJets","matchedNeutrinoPt / recoJetPt vs. recoJetPt, sJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[5] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_recoJetPt_gJets","matchedNeutrinoPt / recoJetPt vs. recoJetPt, gJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[6] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_recoJetPt_xJets","matchedNeutrinoPt / recoJetPt vs. recoJetPt, xJets",500,0,5,NPtBins,ptMin,ptMax);

  h_matchedNeutrinoPtOverGenJetPt_genJetPt[0] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_genJetPt_allJets","matchedNeutrinoPt / genJetPt vs. genJetPt, all flavors",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[1] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_genJetPt_bJets","matchedNeutrinoPt / genJetPt vs. genJetPt, bJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[2] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_genJetPt_cJets","matchedNeutrinoPt / genJetPt vs. genJetPt, cJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[3] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_genJetPt_udJets","matchedNeutrinoPt / genJetPt vs. genJetPt, udJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[4] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_genJetPt_sJets","matchedNeutrinoPt / genJetPt vs. genJetPt, sJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[5] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_genJetPt_gJets","matchedNeutrinoPt / genJetPt vs. genJetPt, gJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[6] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_genJetPt_xJets","matchedNeutrinoPt / genJetPt vs. genJetPt, xJets",500,0,5,NPtBins,ptMin,ptMax);

  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[0] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_recoJetPt_allJets","matchedNeutrinoPt / genJetPt vs. recoJetPt, all flavors",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[1] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_recoJetPt_bJets","matchedNeutrinoPt / genJetPt vs. recoJetPt, bJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[2] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_recoJetPt_cJets","matchedNeutrinoPt / genJetPt vs. recoJetPt, cJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[3] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_recoJetPt_udJets","matchedNeutrinoPt / genJetPt vs. recoJetPt, udJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[4] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_recoJetPt_sJets","matchedNeutrinoPt / genJetPt vs. recoJetPt, sJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[5] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_recoJetPt_gJets","matchedNeutrinoPt / genJetPt vs. recoJetPt, gJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[6] = new TH2D("h_matchedNeutrinoPtOverGenJetPt_recoJetPt_xJets","matchedNeutrinoPt / genJetPt vs. recoJetPt, xJets",500,0,5,NPtBins,ptMin,ptMax);

  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[0] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_genJetPt_allJets","matchedNeutrinoPt / recoJetPt vs. genJetPt, all flavors",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[1] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_genJetPt_bJets","matchedNeutrinoPt / recoJetPt vs. genJetPt, bJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[2] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_genJetPt_cJets","matchedNeutrinoPt / recoJetPt vs. genJetPt, cJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[3] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_genJetPt_udJets","matchedNeutrinoPt / recoJetPt vs. genJetPt, udJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[4] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_genJetPt_sJets","matchedNeutrinoPt / recoJetPt vs. genJetPt, sJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[5] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_genJetPt_gJets","matchedNeutrinoPt / recoJetPt vs. genJetPt, gJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[6] = new TH2D("h_matchedNeutrinoPtOverRecoJetPt_genJetPt_xJets","matchedNeutrinoPt / recoJetPt vs. genJetPt, xJets",500,0,5,NPtBins,ptMin,ptMax);


      
  h_matchedRecoJetPtOverGenJetPt_genJetPt[0]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[1]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[2]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[3]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[4]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[5]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[6]->Sumw2();

  h_matchedRecoJetPtOverGenJetPt_recoJetPt[0]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[1]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[2]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[3]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[4]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[5]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[6]->Sumw2();

  h_matchedRecoJetPtOverGenJetPt_genJetEta[0]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[1]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[2]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[3]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[4]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[5]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[6]->Sumw2();

  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[0]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[1]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[2]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[3]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[4]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[5]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[6]->Sumw2();

  h_matchedNeutrinoPtOverGenJetPt_genJetPt[0]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[1]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[2]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[3]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[4]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[5]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[6]->Sumw2();

  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[0]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[1]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[2]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[3]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[4]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[5]->Sumw2();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[6]->Sumw2();

  
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[0]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[1]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[2]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[3]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[4]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[5]->Sumw2();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[6]->Sumw2();



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

  TRandom *randomGenerator = new TRandom2();

  // jet-energy resolution fit function
  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,300);
  JER_fxn->SetParameter(0,1.26585e-01);
  JER_fxn->SetParameter(1,-9.72986e-01);
  JER_fxn->SetParameter(2,3.67352e-04);


  loadFitFxn_vz();
  loadFitFxn_PYTHIA_JESb();
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
    if(em->checkEventFilter()) continue;
    //cout << "Event #" << evi << " passed the global cuts!" << endl;


    double w_reweight_vz = 1.0;
    if(doVzReweight){
      w_reweight_vz = fitFxn_vz->Eval(em->vz);
    }


    
    // apply HLT
    // int triggerDecision = em->HLT_HIL3Mu5_NHitQ10_v1;
    // int triggerDecision_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl;

    // int triggerDecision = em->HLT_HIL3Mu7_v1;
    // int triggerDecision_Prescl = em->HLT_HIL3Mu7_v1_Prescl;

    int triggerDecision = em->HLT_HIL3Mu12_v1;
    int triggerDecision_Prescl = em->HLT_HIL3Mu12_v1_Prescl;

    //cout << "triggerDecision = " << triggerDecision << endl;

    
    //if(!triggerIsOn(triggerDecision,triggerDecision_Prescl)) continue;

    //cout << "lets go!" << endl;

    // RECO VARIABLES
	
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};
    
    double w_pthat = em->weight;

    double w = w_pthat * w_reweight_vz;

    // GEN JET LOOP
    for(int i = 0; i < em->ngj ; i++){

      // JET VARIABLES
      double x = em->genjetpt[i];
      double y = em->genjeteta[i];
      double z = em->genjetphi[i];

      double matchedRecoJetPt = 0.0;
      double matchedRawJetPt = 0.0;
      double matchedNeutrinoPt = 0.0;
      			
      if(TMath::Abs(y) > etaMax) continue;
	
      // GET FLAVOR FROM RECO MATCH
      bool hasRecoJetMatch = false;
      bool hasRecoJetMuon = false;
      bool hasRecoJetNeutrino = false;
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
	    //if(em->mupt[k] > 7.0 && em->mupt[k] < 14.0) hasRecoJetMuon = true;

	    JEC.SetJetPT(em->rawpt[k]);
	    JEC.SetJetEta(em->jeteta[k]);
	    JEC.SetJetPhi(em->jetphi[k]);

	    matchedRecoJetPt = JEC.GetCorrectedPT();
	    //matchedRecoJetPt = em->jetpt[k];
	    matchedRawJetPt = em->rawpt[k];

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
	      //sigma = 0.83066239*JER_fxn->Eval(matchedRecoJetPt); // apply a 30% smear
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

	    if(doBJetEnergyShift){
	      matchedRecoJetPt = matchedRecoJetPt * (1.0 / fitFxn_PYTHIA_JESb->Eval(matchedRecoJetPt));
	    }

	    // loop through gen particles to find gen-neutrino match
	    for(int j = 0; j < em->gpptp->size(); j++){
	      if(TMath::Abs(em->gppdgIDp->at(j)) != 12 && TMath::Abs(em->gppdgIDp->at(j)) != 14 && TMath::Abs(em->gppdgIDp->at(j)) != 16 && TMath::Abs(em->gppdgIDp->at(j)) != 18) continue;
	      double genNeutrinoPt_j = em->gpptp->at(j);
	      double genNeutrinoEta_j = em->gpetap->at(j);
	      double genNeutrinoPhi_j = em->gpphip->at(j);
	      if(genNeutrinoPt_j < nuPtCut || genNeutrinoPt_j > nuPtMaxCut || fabs(genNeutrinoEta_j) > 2.0) continue;
	      if(getDr(genNeutrinoEta_j,genNeutrinoPhi_j,em->jeteta[k],em->jetphi[k]) < deltaRCut){
		hasRecoJetNeutrino = true;
		matchedNeutrinoPt = genNeutrinoPt_j;
	      }

	    }

	    if(doNeutrinoEnergyAddition && hasRecoJetNeutrino){
	      matchedRecoJetPt += matchedNeutrinoPt;
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
      }

      jetFlavorInt = em->partonFlavor[recoJetFlavorFlag];
      //if(fabs(jetFlavorInt) == 5 && bHadronNumber == 2) jetFlavorInt = 17; // 17 = bJet from gluon-splitting

			
			
      // fill response matrix
      if(hasRecoJetMatch) {
      
      //if(hasRecoJetMatch && !hasRecoJetNeutrino) {   // keep only neutrino-less jets
      //if(hasRecoJetMatch && hasRecoJetNeutrino) {   // keep only neutrino-full jets
      //if(hasRecoJetMatch && hasRecoJetMuon && matchedRecoJetPt) {   // keep only muon-tagged jets
      //if(hasRecoJetMatch && hasRecoJetMuon && hasRecoJetNeutrino) { // keep only muon-tagged + neutrino-tagged jets

	//cout << "matchedRecoJetPt = " << matchedRecoJetPt << endl;
	
	h_matchedRecoJetPt_genJetPt[0]->Fill(matchedRecoJetPt,x,w);
	h_matchedNeutrinoPt_recoJetPt[0]->Fill(matchedNeutrinoPt,matchedRecoJetPt,w);
	h_matchedNeutrinoPt_genJetPt[0]->Fill(matchedNeutrinoPt,x,w);

	h_matchedRecoJetPt_genJetPt_var->Fill(matchedRecoJetPt,x,w);
	

	h_matchedRecoJetPtOverGenJetPt_genJetPt[0]->Fill(matchedRecoJetPt/x,x,w);
	h_matchedRecoJetPtOverGenJetPt_recoJetPt[0]->Fill(matchedRecoJetPt/x,matchedRecoJetPt,w);
	h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[0]->Fill(matchedNeutrinoPt/matchedRecoJetPt,matchedRecoJetPt,w);
	h_matchedNeutrinoPtOverGenJetPt_genJetPt[0]->Fill(matchedNeutrinoPt/x,x,w);
	h_matchedNeutrinoPtOverGenJetPt_recoJetPt[0]->Fill(matchedNeutrinoPt/x,matchedRecoJetPt,w);
	h_matchedNeutrinoPtOverRecoJetPt_genJetPt[0]->Fill(matchedNeutrinoPt/matchedRecoJetPt,x,w);

	if(x>60){
	  h_matchedRecoJetPtOverGenJetPt_genJetEta[0]->Fill(matchedRecoJetPt/x,y,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetEta[0]->Fill(matchedRecoJetPt/x,y,w);
	}


	if(fabs(jetFlavorInt) == 5){
	  h_matchedRecoJetPt_genJetPt[1]->Fill(matchedRecoJetPt,x,w);
	  h_matchedNeutrinoPt_recoJetPt[1]->Fill(matchedNeutrinoPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPt_genJetPt[1]->Fill(matchedNeutrinoPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[1]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_recoJetPt[1]->Fill(matchedRecoJetPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[1]->Fill(matchedNeutrinoPt/matchedRecoJetPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverGenJetPt_genJetPt[1]->Fill(matchedNeutrinoPt/x,x,w);
	  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[1]->Fill(matchedNeutrinoPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[1]->Fill(matchedNeutrinoPt/matchedRecoJetPt,x,w);
	  				
	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[1]->Fill(matchedRecoJetPt/x,y,w);
	    
	  }
	} 
	if(fabs(jetFlavorInt) == 4){
	  h_matchedRecoJetPt_genJetPt[2]->Fill(matchedRecoJetPt,x,w);
	  h_matchedNeutrinoPt_recoJetPt[2]->Fill(matchedNeutrinoPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPt_genJetPt[2]->Fill(matchedNeutrinoPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[2]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_recoJetPt[2]->Fill(matchedRecoJetPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[2]->Fill(matchedNeutrinoPt/matchedRecoJetPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverGenJetPt_genJetPt[2]->Fill(matchedNeutrinoPt/x,x,w);
	  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[2]->Fill(matchedNeutrinoPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[2]->Fill(matchedNeutrinoPt/matchedRecoJetPt,x,w);
	  
	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[2]->Fill(matchedRecoJetPt/x,y,w);
	  
	  }

	} 
	if(fabs(jetFlavorInt) == 1 || fabs(jetFlavorInt) == 2){
	  h_matchedRecoJetPt_genJetPt[3]->Fill(matchedRecoJetPt,x,w);
	  h_matchedNeutrinoPt_recoJetPt[3]->Fill(matchedNeutrinoPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPt_genJetPt[3]->Fill(matchedNeutrinoPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[3]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_recoJetPt[3]->Fill(matchedRecoJetPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[3]->Fill(matchedNeutrinoPt/matchedRecoJetPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverGenJetPt_genJetPt[3]->Fill(matchedNeutrinoPt/x,x,w);
	  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[3]->Fill(matchedNeutrinoPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[3]->Fill(matchedNeutrinoPt/matchedRecoJetPt,x,w);
	  
	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[3]->Fill(matchedRecoJetPt/x,y,w);
	  
	  }
	} 
	if(fabs(jetFlavorInt) == 3){
	  h_matchedRecoJetPt_genJetPt[4]->Fill(matchedRecoJetPt,x,w);
	  h_matchedNeutrinoPt_recoJetPt[4]->Fill(matchedNeutrinoPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPt_genJetPt[4]->Fill(matchedNeutrinoPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[4]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_recoJetPt[4]->Fill(matchedRecoJetPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[4]->Fill(matchedNeutrinoPt/matchedRecoJetPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverGenJetPt_genJetPt[4]->Fill(matchedNeutrinoPt/x,x,w);
	  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[4]->Fill(matchedNeutrinoPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[4]->Fill(matchedNeutrinoPt/matchedRecoJetPt,x,w);

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[4]->Fill(matchedRecoJetPt/x,y,w);
	    
	  }

	}  
	if(jetFlavorInt == 21){
	  h_matchedRecoJetPt_genJetPt[5]->Fill(matchedRecoJetPt,x,w);
	  h_matchedNeutrinoPt_recoJetPt[5]->Fill(matchedNeutrinoPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPt_genJetPt[5]->Fill(matchedNeutrinoPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[5]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_recoJetPt[5]->Fill(matchedRecoJetPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[5]->Fill(matchedNeutrinoPt/matchedRecoJetPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverGenJetPt_genJetPt[5]->Fill(matchedNeutrinoPt/x,x,w);
	  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[5]->Fill(matchedNeutrinoPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[5]->Fill(matchedNeutrinoPt/matchedRecoJetPt,x,w);
	  
	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[5]->Fill(matchedRecoJetPt/x,y,w);
	    
	  }

	}  
	if(jetFlavorInt == 0){
	  h_matchedRecoJetPt_genJetPt[6]->Fill(matchedRecoJetPt,x,w);
	  h_matchedNeutrinoPt_recoJetPt[6]->Fill(matchedNeutrinoPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPt_genJetPt[6]->Fill(matchedNeutrinoPt,x,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[6]->Fill(matchedRecoJetPt/x,x,w);
	  h_matchedRecoJetPtOverGenJetPt_recoJetPt[6]->Fill(matchedRecoJetPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[6]->Fill(matchedNeutrinoPt/matchedRecoJetPt,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverGenJetPt_genJetPt[6]->Fill(matchedNeutrinoPt/x,x,w);
	  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[6]->Fill(matchedNeutrinoPt/x,matchedRecoJetPt,w);
	  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[6]->Fill(matchedNeutrinoPt/matchedRecoJetPt,x,w);
	  
	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[6]->Fill(matchedRecoJetPt/x,y,w);
	  
	  }

	}
      }
			



		

		




    }
    // END GEN JET LOOP

	

  } // END EVENT LOOP
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  
    
  h_matchedRecoJetPt_genJetPt[0]->Write();
  h_matchedRecoJetPt_genJetPt[1]->Write();
  h_matchedRecoJetPt_genJetPt[2]->Write();
  h_matchedRecoJetPt_genJetPt[3]->Write();
  h_matchedRecoJetPt_genJetPt[4]->Write();
  h_matchedRecoJetPt_genJetPt[5]->Write();
  h_matchedRecoJetPt_genJetPt[6]->Write();

  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[0]->Write();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[1]->Write();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[2]->Write();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[3]->Write();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[4]->Write();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[5]->Write();
  h_matchedRecoJetPt_genNeutrinoTag_genJetPt[6]->Write();

  
  h_matchedNeutrinoPt_recoJetPt[0]->Write();
  h_matchedNeutrinoPt_recoJetPt[1]->Write();
  h_matchedNeutrinoPt_recoJetPt[2]->Write();
  h_matchedNeutrinoPt_recoJetPt[3]->Write();
  h_matchedNeutrinoPt_recoJetPt[4]->Write();
  h_matchedNeutrinoPt_recoJetPt[5]->Write();
  h_matchedNeutrinoPt_recoJetPt[6]->Write();

  h_matchedNeutrinoPt_genJetPt[0]->Write();
  h_matchedNeutrinoPt_genJetPt[1]->Write();
  h_matchedNeutrinoPt_genJetPt[2]->Write();
  h_matchedNeutrinoPt_genJetPt[3]->Write();
  h_matchedNeutrinoPt_genJetPt[4]->Write();
  h_matchedNeutrinoPt_genJetPt[5]->Write();
  h_matchedNeutrinoPt_genJetPt[6]->Write();

  
  h_matchedRecoJetPt_genJetPt_var->Write();
    
  h_matchedRecoJetPtOverGenJetPt_genJetPt[0]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[1]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[2]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[3]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[4]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[5]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[6]->Write();

    
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[0]->Write();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[1]->Write();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[2]->Write();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[3]->Write();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[4]->Write();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[5]->Write();
  h_matchedRecoJetPtOverGenJetPt_recoJetPt[6]->Write();

  
  h_matchedRecoJetPtOverGenJetPt_genJetEta[0]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[1]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[2]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[3]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[4]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[5]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[6]->Write();

  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[0]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[1]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[2]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[3]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[4]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[5]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_recoJetPt[6]->Write();

  h_matchedNeutrinoPtOverGenJetPt_genJetPt[0]->Write();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[1]->Write();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[2]->Write();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[3]->Write();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[4]->Write();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[5]->Write();
  h_matchedNeutrinoPtOverGenJetPt_genJetPt[6]->Write();

  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[0]->Write();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[1]->Write();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[2]->Write();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[3]->Write();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[4]->Write();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[5]->Write();
  h_matchedNeutrinoPtOverGenJetPt_recoJetPt[6]->Write();

  
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[0]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[1]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[2]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[3]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[4]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[5]->Write();
  h_matchedNeutrinoPtOverRecoJetPt_genJetPt[6]->Write();
  






  wf->Close();
  return;
  // END WRITE



}







