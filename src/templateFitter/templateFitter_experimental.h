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

#include "../../headers/goldenFileNames.h"

TFile *f1, *f2, *f3, *f4, *f_data;
TFile *f_py_C2smear, *f_py_C1smear;

// There are 3 classes of histograms, labeled "h", "g", and "k"
// - h class: either PYTHIA or DiJet PYTHIA+HYDJET MC
// - g class: MuJet PYTHIA+HYDJET MC
// - k class: BJet PYTHIA+HYDJET MC


TH2D *h0, *g0, *k0, *l0;

TH1D *h0_incl;
TH1D *h0_b, *h0_c, *h0_d, *h0_g, *h0_s, *h0_u, *h0_x, *h0_y, *h0_l, *h0_bGS;
// h0_x = ghost jets, h0_y = undefined flavor (gen jets with inaccessible recoJet pair)
// h0_l = light jets combined together
TH1D *h0_bbar, *h0_cbar, *h0_dbar, *h0_sbar, *h0_ubar;


TH1D *g0_incl;
TH1D *g0_b, *g0_c, *g0_d, *g0_g, *g0_s, *g0_u, *g0_x, *g0_y, *g0_l, *g0_bGS;
// g0_x = ghost jets, g0_y = undefined flavor (gen jets with inaccessible recoJet pair)
// g0_l = light jets combined together
TH1D *g0_bbar, *g0_cbar, *g0_dbar, *g0_sbar, *g0_ubar;

TH1D *k0_incl;
TH1D *k0_b, *k0_c, *k0_d, *k0_g, *k0_s, *k0_u, *k0_x, *k0_y, *k0_l, *k0_bGS;
// k0_x = ghost jets, k0_y = undefined flavor (gen jets with inaccessible recoJet pair)
// k0_l = light jets combined together
TH1D *k0_bbar, *k0_cbar, *k0_dbar, *k0_sbar, *k0_ubar;

TH1D *l0_incl;
TH1D *l0_b, *l0_c, *l0_d, *l0_g, *l0_s, *l0_u, *l0_x, *l0_y, *l0_l, *l0_bGS;
// l0_x = ghost jets, l0_y = undefined flavor (gen jets with inaccessible recoJet pair)
// l0_l = light jets combined together
TH1D *l0_bbar, *l0_cbar, *l0_dbar, *l0_sbar, *l0_ubar;


// histograms for rebinning
TH1D *h0_inclR, *h0_lR, *h0_bR, *h0_cR, *h0_xR;

// test histo
TH2D *hh;

double cFixVal = 0.0;


double func_temp_1(double *x, double *par){
  double xx = x[0];
  int bin = h0_bR->FindBin(xx);
  //h0_lR->Add(h0_cR);
  double b = (par[0])*h0_bR->GetBinContent(bin);
  double e = (1-par[0])*h0_lR->GetBinContent(bin);
  return b+e;
}

double func_temp_2(double *x, double *par){
  double xx = x[0];
  int bin = h0_bR->FindBin(xx);
  double b = (par[0])*h0_bR->GetBinContent(bin);
  double c = (par[1])*h0_cR->GetBinContent(bin);
  double e = (1-par[0]-par[1])*h0_lR->GetBinContent(bin);
  return b+e+c;
}

double func_temp_cFix(double *x, double *par){
  double xx = x[0];
  int bin = h0_bR->FindBin(xx);
  double b = (par[0])*h0_bR->GetBinContent(bin);
  double c = cFixVal*h0_cR->GetBinContent(bin);
  double e = (1 - par[0] - cFixVal)*h0_lR->GetBinContent(bin);
}



double templateFitter(TH1D *h0_incl_in,
		      TH1D *h0_b_in,
		      TH1D *h0_c_in,
		      TH1D *h0_l_in,
		      TH1D *h0_x_in,
		      bool isData = 1,
		      bool isMu5  = 1,
		      bool isMu7  = 0,
		      bool isMu12 = 0,
		      bool ispp   = 0,
		      bool isC1   = 0,
		      bool isC2   = 1,
		      bool isJ1   = 0,
		      bool isJ2   = 0,
		      bool isJ3   = 0,
		      bool isJ4   = 1,
		      bool isJ5   = 0,
		      bool isJ6   = 0,
		      bool mergeCtemplates = true,
		      bool mergeBtemplates = true,
		      bool do2templateFit  = true,
		      bool do3templateFit  = false,
		      double low_x  = 0.0,
		      double high_x = 5.0,
		      double c_multiplier = 1.0,
		      double bGS_multiplier = 1.0,
		      int returnValueIndex = 1
		      ){

  double result[4];

  h0_incl = h0_incl_in;
  h0_b = h0_b_in;
  h0_c = h0_c_in;
  h0_l = h0_l_in;
  h0_x = h0_x_in;

  TString input_PYTHIA;
  TString input_pp;
  TString input_PYTHIAHYDJET_DiJet;
  TString input_PYTHIAHYDJET_DiJet_additionalMC;
  TString input_PYTHIAHYDJET_MuJet;
  TString input_PYTHIAHYDJET_BJet;
  TString input_PbPb;
  TString input_PYTHIA_C2smear, input_PYTHIA_C1smear;
  
  if(isMu5){

    input_pp   = goldenFile_pp_SingleMuon_mu5;
    input_PbPb = goldenFile_PbPb_SingleMuon_mu5;

    
    input_PYTHIA             = goldenFile_PYTHIA_mu5_pThat15;
    input_PYTHIAHYDJET_DiJet = goldenFile_PYTHIAHYDJET_DiJet_mu5_pThat15;
    input_PYTHIAHYDJET_MuJet = goldenFile_PYTHIAHYDJET_MuJet_mu5_pThat15;
    input_PYTHIAHYDJET_BJet  = goldenFile_PYTHIAHYDJET_BJet_mu5_pThat15;

  }

  else if(isMu7){

    input_pp   = goldenFile_pp_SingleMuon_mu7;
    input_PbPb = goldenFile_PbPb_SingleMuon_mu7;

    input_PYTHIA             = goldenFile_PYTHIA_mu7_pThat30;
    input_PYTHIAHYDJET_DiJet = goldenFile_PYTHIAHYDJET_DiJet_mu7_pThat30;
    input_PYTHIAHYDJET_MuJet = goldenFile_PYTHIAHYDJET_MuJet_mu7_pThat30;
    input_PYTHIAHYDJET_BJet  = goldenFile_PYTHIAHYDJET_BJet_mu7_pThat30;
    input_PYTHIAHYDJET_DiJet_additionalMC = goldenFile_PYTHIAHYDJET_DiJet_additionalMC_mu12_pThat30;
    
  }

  else if(isMu12){

    input_pp   = goldenFile_pp_SingleMuon_mu12_newJetBins;
    input_PbPb = goldenFile_PbPb_SingleMuon_mu12_newJetBins;

    input_PYTHIA             = goldenFile_PYTHIA_mu12_pThat15_newJetBins;
    input_PYTHIAHYDJET_DiJet = goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat15_newJetBins;
    input_PYTHIAHYDJET_DiJet_additionalMC = goldenFile_PYTHIAHYDJET_DiJet_additionalMC_mu12_pThat30;
    input_PYTHIAHYDJET_MuJet = goldenFile_PYTHIAHYDJET_MuJet_mu12_pThat15_newJetBins;
    input_PYTHIAHYDJET_BJet  = goldenFile_PYTHIAHYDJET_BJet_mu12_pThat15_newJetBins;

    input_PYTHIA_C2smear = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/platinum/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_muPtRelReweightC2_newJetBins.root";
    input_PYTHIA_C1smear = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/platinum/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_muPtRelReweightC1_newJetBins.root";
   
  }
	
  else{};


  cout << "input_PYTHIA: " << input_PYTHIA << endl;
  cout << "input_pp: " << input_pp << endl;
  cout << "input_PYTHIAHYDJET_DiJet: " << input_PYTHIAHYDJET_DiJet << endl;
  cout << "input_PYTHIAHYDJET_DiJet_additionalMC: " << input_PYTHIAHYDJET_DiJet_additionalMC << endl;
  cout << "input_PbPb: " << input_PbPb << endl;
  
  if(ispp){
	
    f1 = TFile::Open(input_PYTHIA);
    if(!isData) f_data = TFile::Open(input_PYTHIA);
    else f_data = TFile::Open(input_pp);	

    if(isJ1){
      f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J1",h0);
      if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_J1",h0_incl);		
    }
    if(isJ2){
      f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J2",h0);
      if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_J2",h0_incl);		
    }
    if(isJ3){
      f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J3",h0);
      if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_J3",h0_incl);		
    }
    if(isJ4){
      f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J4",h0);
      if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_J4",h0_incl);		
    }
    if(isJ5){
      f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J5",h0);
      if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_J5",h0_incl);		
    }
    if(isJ6){
      f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J6",h0);
      if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_J6",h0_incl);		
    }


  }
  
  if(!ispp){

    f1 = TFile::Open(input_PYTHIAHYDJET_DiJet);
    f2 = TFile::Open(input_PYTHIAHYDJET_BJet);
    f3 = TFile::Open(input_PYTHIAHYDJET_MuJet);
    f4 = TFile::Open(input_PYTHIAHYDJET_DiJet_additionalMC);
    f_py_C1smear = TFile::Open(input_PYTHIA_C1smear);
    f_py_C2smear = TFile::Open(input_PYTHIA_C2smear);
    
    if(!isData) f_data = TFile::Open(input_PYTHIAHYDJET_DiJet);
    else f_data = TFile::Open(input_PbPb);
    

    if(isC1){

      if(isJ1){
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J1",h0);
	//f_py_C1smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J1",h0);
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J1",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J1",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J1",k0);
	//if(isData) f_data->GetObject("h_muPtRel_C1J1",h0_incl);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C1J1",h0_incl);
      }
      if(isJ2){
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2",h0);
	//f_py_C1smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J2",h0);
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2",k0);
	f4->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2",l0);
	//if(isData) f_data->GetObject("h_muPtRel_C1J2",h0_incl);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C1J2",h0_incl);
      }
      if(isJ3){
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J3",h0);
	//f_py_C1smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J3",h0);
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J3",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J3",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J3",k0);
	//if(isData) f_data->GetObject("h_muPtRel_C1J3",h0_incl);		
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C1J3",h0_incl);
      }
      if(isJ4){
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J4",h0);
	//f_py_C1smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J4",h0);
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J4",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J4",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J4",k0);
	//if(isData) f_data->GetObject("h_muPtRel_C1J4",h0_incl);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C1J4",h0_incl);
      }
      if(isJ5){
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J5",h0);
	//f_py_C1smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J5",h0);
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J5",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J5",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J5",k0);
	//if(isData) f_data->GetObject("h_muPtRel_C1J5",h0_incl);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C1J5",h0_incl);
      }
      if(isJ6){
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J6",h0);
	//f_py_C1smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J6",h0);
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J6",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J6",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J6",k0);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J6",h0_incl);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C1J6",h0_incl);
      }
    }
	    

    if(isC2){

      if(isJ1){
	//f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J1",h0);
	f_py_C2smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J1",h0);
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J1",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J1",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J1",k0);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J1",h0_incl);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C2J1",h0_incl);
      }
      if(isJ2){
	//f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J2",h0);
	f_py_C2smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J2",h0);
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J2",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J2",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J2",k0);
	f4->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J2",l0);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J2",h0_incl);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C2J2",h0_incl);
      }
      if(isJ3){
	//f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J3",h0);
	f_py_C2smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J3",h0);
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J3",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J3",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J3",k0);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J3",h0_incl);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C2J3",h0_incl);
      }
      if(isJ4){
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J4",h0);
	f_py_C2smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J4",h0);
	//f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J4",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J4",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J4",k0);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J4",h0_incl);		
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C2J4",h0_incl);
      }
      if(isJ5){
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J5",h0);
	f_py_C2smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J5",h0);
	//f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J5",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J5",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J5",k0);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J5",h0_incl);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C2J5",h0_incl);
      }
      if(isJ6){
	f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J6",h0);
	f_py_C2smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J6",h0);
	//f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J6",hh);
	f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J6",g0);
	f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J6",k0);
	//if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C2J6",h0_incl);
        //if(isData) f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C2J6",h0_incl);
      }
    }

	
  }



  TH1D *binFinder = h0->ProjectionY();
  TAxis *yaxis = binFinder->GetXaxis();
  double smallShift = 0.01;

  //TH1D *h0_l;
  TH1D *g0_l;
  TH1D *k0_l;
	
  if(ispp){	

    if(!isData){
      //h0_incl = (TH1D*) h0->ProjectionX("h0_incl",binFinder->FindBin(-5+smallShift),binFinder->FindBin(22-smallShift));
    }
    //h0_b = (TH1D*) h0->ProjectionX("h0_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
    //h0_c = (TH1D*) h0->ProjectionX("h0_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
    h0_d = (TH1D*) h0->ProjectionX("h0_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
    h0_g = (TH1D*) h0->ProjectionX("h0_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
    h0_s = (TH1D*) h0->ProjectionX("h0_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
    h0_u = (TH1D*) h0->ProjectionX("h0_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
    h0_bbar = (TH1D*) h0->ProjectionX("h0_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
    h0_cbar = (TH1D*) h0->ProjectionX("h0_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
    h0_dbar = (TH1D*) h0->ProjectionX("h0_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
    h0_sbar = (TH1D*) h0->ProjectionX("h0_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
    h0_ubar = (TH1D*) h0->ProjectionX("h0_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
    //h0_x = (TH1D*) h0->ProjectionX("h0_x",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
    h0_y = (TH1D*) h0->ProjectionX("h0_y",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));
    h0_bGS = (TH1D*) h0->ProjectionX("h0_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));

    //h0_b->Add(h0_bbar);
    //h0_c->Add(h0_cbar);
    h0_d->Add(h0_dbar);
    h0_s->Add(h0_sbar);
    h0_u->Add(h0_ubar);


    // h0_l = (TH1D*) h0_u->Clone("h0_l");
    // h0_l->Add(h0_d);
    // h0_l->Add(h0_s);
    // h0_l->Add(h0_g);


  }

  if(!ispp){
	  
    //if(!isData) h0_incl = (TH1D*) hh->ProjectionX("h0_incl",binFinder->FindBin(-5+smallShift),binFinder->FindBin(22-smallShift));

    //h0_b = (TH1D*) h0->ProjectionX("h0_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
    //h0_c = (TH1D*) h0->ProjectionX("h0_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));

    h0_d = (TH1D*) h0->ProjectionX("h0_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
    h0_g = (TH1D*) h0->ProjectionX("h0_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
    h0_s = (TH1D*) h0->ProjectionX("h0_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
    h0_u = (TH1D*) h0->ProjectionX("h0_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));

    // h0_d = (TH1D*) hh->ProjectionX("h0_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
    // h0_g = (TH1D*) hh->ProjectionX("h0_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
    // h0_s = (TH1D*) hh->ProjectionX("h0_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
    // h0_u = (TH1D*) hh->ProjectionX("h0_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));

    
    h0_bbar = (TH1D*) h0->ProjectionX("h0_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
    h0_cbar = (TH1D*) h0->ProjectionX("h0_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));

    h0_dbar = (TH1D*) h0->ProjectionX("h0_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
    h0_sbar = (TH1D*) h0->ProjectionX("h0_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
    h0_ubar = (TH1D*) h0->ProjectionX("h0_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));

    // h0_dbar = (TH1D*) hh->ProjectionX("h0_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
    // h0_sbar = (TH1D*) hh->ProjectionX("h0_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
    // h0_ubar = (TH1D*) hh->ProjectionX("h0_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
    
    //h0_x = (TH1D*) h0->ProjectionX("h0_x",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
    h0_y = (TH1D*) h0->ProjectionX("h0_y",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));
    h0_bGS = (TH1D*) h0->ProjectionX("h0_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));

    //h0_b->Add(h0_bbar);
    //h0_c->Add(h0_cbar);
    h0_d->Add(h0_dbar);
    h0_s->Add(h0_sbar);
    h0_u->Add(h0_ubar);


    // h0_l = (TH1D*) h0_u->Clone("h0_l");
    // h0_l->Add(h0_d);
    // h0_l->Add(h0_s);
    // h0_l->Add(h0_g);

    /////////////////////////////

    g0_b = (TH1D*) g0->ProjectionX("g0_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
    g0_c = (TH1D*) g0->ProjectionX("g0_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
    g0_d = (TH1D*) g0->ProjectionX("g0_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
    g0_g = (TH1D*) g0->ProjectionX("g0_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
    g0_s = (TH1D*) g0->ProjectionX("g0_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
    g0_u = (TH1D*) g0->ProjectionX("g0_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
    g0_bbar = (TH1D*) g0->ProjectionX("g0_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
    g0_cbar = (TH1D*) g0->ProjectionX("g0_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
    g0_dbar = (TH1D*) g0->ProjectionX("g0_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
    g0_sbar = (TH1D*) g0->ProjectionX("g0_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
    g0_ubar = (TH1D*) g0->ProjectionX("g0_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
    g0_x = (TH1D*) g0->ProjectionX("g0_x",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
    g0_y = (TH1D*) g0->ProjectionX("g0_y",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));
    g0_bGS = (TH1D*) g0->ProjectionX("g0_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));

    g0_b->Add(g0_bbar);
    g0_c->Add(g0_cbar);
    g0_d->Add(g0_dbar);
    g0_s->Add(g0_sbar);
    g0_u->Add(g0_ubar);


    g0_l = (TH1D*) g0_u->Clone("g0_l");
    g0_l->Add(g0_d);
    g0_l->Add(g0_s);
    g0_l->Add(g0_g);

    ////////////////////////////
    
    k0_b = (TH1D*) k0->ProjectionX("k0_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
    k0_c = (TH1D*) k0->ProjectionX("k0_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
    k0_d = (TH1D*) k0->ProjectionX("k0_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
    k0_g = (TH1D*) k0->ProjectionX("k0_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
    k0_s = (TH1D*) k0->ProjectionX("k0_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
    k0_u = (TH1D*) k0->ProjectionX("k0_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
    k0_bbar = (TH1D*) k0->ProjectionX("k0_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
    k0_cbar = (TH1D*) k0->ProjectionX("k0_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
    k0_dbar = (TH1D*) k0->ProjectionX("k0_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
    k0_sbar = (TH1D*) k0->ProjectionX("k0_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
    k0_ubar = (TH1D*) k0->ProjectionX("k0_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
    k0_x = (TH1D*) k0->ProjectionX("k0_x",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
    k0_y = (TH1D*) k0->ProjectionX("k0_y",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));
    k0_bGS = (TH1D*) k0->ProjectionX("k0_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));

    k0_b->Add(k0_bbar);
    k0_c->Add(k0_cbar);
    k0_d->Add(k0_dbar);
    k0_s->Add(k0_sbar);
    k0_u->Add(k0_ubar);


    k0_l = (TH1D*) k0_u->Clone("k0_l");
    k0_l->Add(k0_d);
    k0_l->Add(k0_s);
    k0_l->Add(k0_g);

    if(isJ2){
      
      l0_b = (TH1D*) l0->ProjectionX("l0_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
      l0_c = (TH1D*) l0->ProjectionX("l0_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
      l0_d = (TH1D*) l0->ProjectionX("l0_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
      l0_g = (TH1D*) l0->ProjectionX("l0_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
      l0_s = (TH1D*) l0->ProjectionX("l0_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
      l0_u = (TH1D*) l0->ProjectionX("l0_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
      l0_bbar = (TH1D*) l0->ProjectionX("l0_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
      l0_cbar = (TH1D*) l0->ProjectionX("l0_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
      l0_dbar = (TH1D*) l0->ProjectionX("l0_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
      l0_sbar = (TH1D*) l0->ProjectionX("l0_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
      l0_ubar = (TH1D*) l0->ProjectionX("l0_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
      l0_x = (TH1D*) l0->ProjectionX("l0_x",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
      l0_y = (TH1D*) l0->ProjectionX("l0_y",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));
      l0_bGS = (TH1D*) l0->ProjectionX("l0_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));

      l0_b->Add(l0_bbar);
      l0_c->Add(l0_cbar);
      l0_d->Add(l0_dbar);
      l0_s->Add(l0_sbar);
      l0_u->Add(l0_ubar);

      l0_l = (TH1D*) l0_u->Clone("l0_l");
      l0_l->Add(l0_d);
      l0_l->Add(l0_s);
      l0_l->Add(l0_g);
      
    }

  }


  // TFile *file = TFile::Open("light-template-old.root","recreate");
  // h0_l->Write();
  // file->Close();


  
  ////////// Calculate exact count ///////////////
		
  double b_frac = 0.0;
  double eb_frac = 0.0;
  double eps = 0.001;
  if(!isData){

		
    TH1D *h_sum = (TH1D*) h0_incl->Clone("h_sum");
    //h_sum->Add(h_muRelPt_c);  h_sum->Add(h_muRelPt_l);

    double en_tot;
    double n_tot = h_sum->IntegralAndError(h0_incl->FindBin(low_x+eps),h0_incl->FindBin(high_x-eps),en_tot,"");
    cout << "n_tot = " << n_tot << " pm " << en_tot << endl;
    double en_b, en_bGS;
    double n_b = h0_b->IntegralAndError(h0_b->FindBin(low_x+eps),h0_b->FindBin(high_x-eps),en_b,"");
    //double n_bGS = h0_bGS->IntegralAndError(h0_bGS->FindBin(low_x+eps),h0_bGS->FindBin(high_x-eps),en_bGS,"");
    double n_bGS = 0.0;
    en_bGS = 0.0;
    //en_b = (n_b + n_bGS) * TMath::Sqrt((en_b/n_b)*(en_b/n_b) + (en_bGS/n_bGS)*(en_bGS/n_bGS)  );
    n_b += n_bGS;
    

    
    cout << "n_b = " << n_b << " pm " << en_b << endl;
    b_frac = n_b / n_tot;
    eb_frac = b_frac*(TMath::Sqrt(TMath::Power(en_b/n_b,2)+TMath::Power(en_tot/n_tot,2)));


    cout << "exact count b-fraction = " << b_frac << "+/- " << eb_frac << endl;

    result[0] = b_frac;
    result[1] = eb_frac;

  }

  else{
    result[0] = -1.0;
    result[1] = -1.0;
  }


  // scaling before merging the c-template.
  //double c_truth = h0_c->Integral() / (h0_l->Integral() + h0_b->Integral() + h0_c->Integral() + h0_bGS->Integral());
  //double l_truth = h0_l->Integral() / (h0_l->Integral() + h0_b->Integral() + h0_c->Integral() + h0_bGS->Integral());
  double c_truth = h0_c->Integral() / (h0_l->Integral() + h0_b->Integral() + h0_c->Integral());
  double l_truth = h0_l->Integral() / (h0_l->Integral() + h0_b->Integral() + h0_c->Integral());
  
  cout << "c_truth = " << c_truth << ", l_truth = " << l_truth << endl;

  cFixVal = c_multiplier*c_truth;

  ///////////// end calculate exact count ///////////////////////


  /////////////  Configure/merge templates ///////////////////////
  // bGS multiplier
  // h0_bGS->Scale(bGS_multiplier);
  // if(!ispp){
  //   k0_bGS->Scale(bGS_multiplier);
  //   g0_bGS->Scale(bGS_multiplier);
  // }
  // add scaled bGS templates to b templates
  // first, get integral from both
  
	
  // merge templates if desired
  if(!ispp && mergeCtemplates){
    cout << "merging c-template..." << endl;
    h0_c->Add(k0_c); // merge with muJet sample

  }
  if(!ispp && mergeBtemplates){
    cout << "merging b-template..." << endl;
    //h0_b->Add(g0_b); // merge with muJet sample
    //h0_b->Add(k0_b);
    h0_bGS->Add(g0_bGS); // merge with bJet sample
    h0_bGS->Add(k0_bGS);
  }

  
  // low-pT template tests, comment out after completion
  // make the template just use the muJet sample
  //h0_b = (TH1D*) k0_b->Clone("h0_b");




  
  
  double N_h0_b = h0_b->Integral();
  double N_h0_bGS = h0_bGS->Integral();
  double N_h0_bTot = N_h0_b + N_h0_bGS;

  double N_g0_b = h0_b->Integral();
  double N_g0_bGS = h0_bGS->Integral();
  double N_g0_bTot = N_h0_b + N_h0_bGS;
  
  double f_b_truth = N_h0_b / N_h0_bTot;
  double f_bGS_truth = N_h0_bGS / N_h0_bTot; // by construction, f_b_truth + f_bGS_truth = 1
  double GS_enhancement_shift = bGS_multiplier - 1.; // GS_enhancement_shift = percent to increase the GS jets by
  double GS_enhancement_factor = 1. + (GS_enhancement_shift / f_bGS_truth); // multiply this by the current GS fraction and it will result in an increase given by GS_enhancement_shift;
  
  //h0_b->Scale(f_b_truth / h0_b->Integral());
  //h0_bGS->Scale(GS_enhancement_factor * f_bGS_truth / h0_bGS->Integral());
  
  //h0_b->Add(h0_bGS);

  
  // merge ghost jets with lights
  //h0_l->Add(h0_x);

  


  cout << "b-jets: N = " << h0_b->GetEntries() << ", I = " << h0_b->Integral() << ", I/N = " << (1.0*h0_b->Integral())/(1.0*h0_b->GetEntries()) << endl;
  cout << "c-jets: N = " << h0_c->GetEntries() << ", I = " << h0_c->Integral() << ", I/N = " << (1.0*h0_c->Integral())/(1.0*h0_c->GetEntries()) << endl;
  cout << "l-jets: N = " << h0_l->GetEntries() << ", I = " << h0_l->Integral() << ", I/N = " << (1.0*h0_l->Integral())/(1.0*h0_l->GetEntries()) << endl;

  cout << "x" << endl;

  // //scale the merged light templates properly
  double light_nom_scale = 1.0; // final correction
  double light_nom_scale_prime = 1.0; // integral entry
  double light_nom_scale_pprime = 1.0; // error entry
  double light_add_scale = 1.0; // final correction
  double light_add_scale_prime = 1.0; // integral entry
  double light_add_scale_pprime = 1.0; // error entry
  if(!ispp && isJ2){
    light_nom_scale_prime = h0_l->IntegralAndError(h0_l->FindBin(0.0),h0_l->FindBin(10.0),light_nom_scale_pprime);
    light_add_scale_prime = l0_l->IntegralAndError(l0_l->FindBin(0.0),l0_l->FindBin(10.0),light_add_scale_pprime);
    light_nom_scale = light_nom_scale_pprime / light_nom_scale_prime;
    light_add_scale = light_add_scale_pprime / light_add_scale_prime;
    h0_l->Scale(light_nom_scale / h0_l->Integral());
    l0_l->Scale(light_add_scale / l0_l->Integral());
    //h0_l->Add(l0_l);
  }

  // if(!ispp && isJ2){
  //   h0_l = (TH1D*) l0_l->Clone("h0_l"); // swap light template for privately-generated sample
  // }

  cout << "x" << endl;

  
  cout << "x" << endl;

  // START -- EXPERIMENTAL
  
  // if(!ispp){
  //   cout << "experimental light-jet merge:" << endl;
  //   cout << "  h0_l->GetEntries() = " << h0_l->GetEntries() << endl;
  //   cout << "  k0_l->GetEntries() = " << k0_l->GetEntries() << endl;
  //   cout << " adding..." << endl;
  //   h0_l->Add(k0_l);
  //   //h0_l->Add(l0_l);
  // }
  
  // END -- EXPERIMENTAL
  
  // add cJets to lJets (for 2-template fit)
  if(do2templateFit){
    h0_c->Scale(c_multiplier * c_truth / h0_c->Integral());
    h0_l->Scale(l_truth / h0_l->Integral());

    h0_l->Add(h0_c);
  }


  
  cout << "x" << endl;


 
  
  ///////////// clone the flavor histograms
  TH1D *h0_b_draw = (TH1D*) h0_b->Clone("h0_b_draw");
  TH1D *h0_c_draw = (TH1D*) h0_c->Clone("h0_c_draw");
  TH1D *h0_l_draw = (TH1D*) h0_l->Clone("h0_l_draw");
  TH1D *h0_x_draw = (TH1D*) h0_x->Clone("h0_x_draw");


  //////////// Done configuring/merging templates /////////////////////
	

  int Njet = h0_incl->GetEntries();

  // normalize the templates
  h0_l->Scale(1./h0_l->Integral());
  h0_b->Scale(1./h0_b->Integral());
  h0_c->Scale(1./h0_c->Integral());

  h0_l_draw->Scale(1./h0_l_draw->Integral());
  h0_b_draw->Scale(1./h0_b_draw->Integral());
  h0_c_draw->Scale(1./h0_c_draw->Integral());
  h0_x_draw->Scale(1./h0_x_draw->Integral());
 

  // normalize the data
  h0_incl->Scale(1./h0_incl->Integral());
  // define the stack
  THStack *h_stack = new THStack("h_stack","");
  THStack *h_stack2 = new THStack("h_stack2","");

  //const int M = 41;
  //const int M = 31;
  //const int M = 17;
  const int M = 20;
  //const int M = 19;
  //const int M = 12;
  //const int M = 8;
  
  //double muRelPtAxis[M] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0}; // M = 31
  //double muRelPtAxis[M] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4.0}; // M = 41

  double muRelPtAxis[M] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.7,2.1,2.5,3.0,3.8,5.0,7.0}; // M = 20
  //double muRelPtAxis[M] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.7,2.1,2.5,3.0,3.8,5.0}; // M = 19
  //double muRelPtAxis[M] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.5,1.8,2.4,3.5,5.0}; // M = 12
  //double muRelPtAxis[M] = {0.0,0.3,0.6,0.9,1.3,1.8,2.5,4.0}; // M = 8
		

  h0_inclR = (TH1D*) h0_incl->Rebin(M-1,"h0_inclR",muRelPtAxis);
  h0_lR = (TH1D*) h0_l->Rebin(M-1,"h0_lR",muRelPtAxis);
  h0_bR = (TH1D*) h0_b->Rebin(M-1,"h0_bR",muRelPtAxis);
  h0_cR = (TH1D*) h0_c->Rebin(M-1,"h0_cR",muRelPtAxis);
  h0_xR = (TH1D*) h0_x->Rebin(M-1,"h0_xR",muRelPtAxis);

  TH1D *h0_b_drawR = (TH1D*) h0_b_draw->Rebin(M-1,"h0_b_drawR",muRelPtAxis);
  TH1D *h0_c_drawR = (TH1D*) h0_c_draw->Rebin(M-1,"h0_c_drawR",muRelPtAxis);
  TH1D *h0_l_drawR = (TH1D*) h0_l_draw->Rebin(M-1,"h0_l_drawR",muRelPtAxis);	
  TH1D *h0_x_drawR = (TH1D*) h0_x_draw->Rebin(M-1,"h0_x_drawR",muRelPtAxis);


  
  // add overflow bin to last bin
  int lastBin = h0_inclR->GetSize();
  // h0_inclR->SetBinContent(lastBin-1,h0_inclR->GetBinContent(lastBin)+h0_inclR->GetBinContent(lastBin-1));
  // h0_lR->SetBinContent(lastBin-1,h0_lR->GetBinContent(lastBin)+h0_lR->GetBinContent(lastBin-1));
  // h0_bR->SetBinContent(lastBin-1,h0_bR->GetBinContent(lastBin)+h0_bR->GetBinContent(lastBin-1));
  // h0_cR->SetBinContent(lastBin-1,h0_cR->GetBinContent(lastBin)+h0_cR->GetBinContent(lastBin-1));
  // h0_xR->SetBinContent(lastBin-1,h0_xR->GetBinContent(lastBin)+h0_xR->GetBinContent(lastBin-1));

  // h0_l_drawR->SetBinContent(lastBin-1,h0_l_drawR->GetBinContent(lastBin)+h0_l_drawR->GetBinContent(lastBin-1));
  // h0_c_drawR->SetBinContent(lastBin-1,h0_c_drawR->GetBinContent(lastBin)+h0_c_drawR->GetBinContent(lastBin-1));
  // h0_b_drawR->SetBinContent(lastBin-1,h0_b_drawR->GetBinContent(lastBin)+h0_b_drawR->GetBinContent(lastBin-1));
  // h0_x_drawR->SetBinContent(lastBin-1,h0_x_drawR->GetBinContent(lastBin)+h0_x_drawR->GetBinContent(lastBin-1));
  
	
  // normalize by bin width
  int N1 = h0_inclR->GetSize();
  for(int i=0;i<N1;i++){
    double x1 = h0_inclR->GetBinWidth(i);
    double y1 = h0_inclR->GetBinContent(i);
    double z1 = h0_inclR->GetBinError(i);
    if(x1!=0){
      h0_inclR->SetBinContent(i,y1/x1);
      h0_inclR->SetBinError(i,z1/x1);
    }
  }

  int N_l = h0_lR->GetSize();
  for(int i=0;i<N_l;i++){
    double x1 = h0_lR->GetBinWidth(i);
    double y1 = h0_lR->GetBinContent(i);
    double z1 = h0_lR->GetBinError(i);
    if(x1!=0){
      h0_lR->SetBinContent(i,y1/x1);
      h0_lR->SetBinError(i,z1/x1);
      //h0_lR->SetBinError(i,0.0); // suppress light-jet template errors (experimental)
    }
  }

  int N_b = h0_bR->GetSize();
  for(int i=0;i<N_b;i++){
    double x1 = h0_bR->GetBinWidth(i);
    double y1 = h0_bR->GetBinContent(i);
    double z1 = h0_bR->GetBinError(i);
    if(x1!=0){
      h0_bR->SetBinContent(i,y1/x1);
      h0_bR->SetBinError(i,z1/x1);
    }
  }

  int N_c = h0_cR->GetSize();
  for(int i=0;i<N_c;i++){
    double x1 = h0_cR->GetBinWidth(i);
    double y1 = h0_cR->GetBinContent(i);
    double z1 = h0_cR->GetBinError(i);
    if(x1!=0){
      h0_cR->SetBinContent(i,y1/x1);
      h0_cR->SetBinError(i,z1/x1);
    }
  }

  int N_x = h0_xR->GetSize();
  for(int i=0;i<N_x;i++){
    double x1 = h0_xR->GetBinWidth(i);
    double y1 = h0_xR->GetBinContent(i);
    double z1 = h0_xR->GetBinError(i);
    if(x1!=0){
      h0_xR->SetBinContent(i,y1/x1);
      h0_xR->SetBinError(i,z1/x1);
    }
  }

  for(int i=0;i<N_x;i++){
    double x1 = h0_l_drawR->GetBinWidth(i);
    double y1 = h0_l_drawR->GetBinContent(i);
    double z1 = h0_l_drawR->GetBinError(i);
    if(x1!=0){
      h0_l_drawR->SetBinContent(i,y1/x1);
      h0_l_drawR->SetBinError(i,z1/x1);
    }
  }

  for(int i=0;i<N_x;i++){
    double x1 = h0_b_drawR->GetBinWidth(i);
    double y1 = h0_b_drawR->GetBinContent(i);
    double z1 = h0_b_drawR->GetBinError(i);
    if(x1!=0){
      h0_b_drawR->SetBinContent(i,y1/x1);
      h0_b_drawR->SetBinError(i,z1/x1);
    }
  }

  for(int i=0;i<N_x;i++){
    double x1 = h0_c_drawR->GetBinWidth(i);
    double y1 = h0_c_drawR->GetBinContent(i);
    double z1 = h0_c_drawR->GetBinError(i);
    if(x1!=0){
      h0_c_drawR->SetBinContent(i,y1/x1);
      h0_c_drawR->SetBinError(i,z1/x1);
    }
  }

  for(int i=0;i<N_x;i++){
    double x1 = h0_x_drawR->GetBinWidth(i);
    double y1 = h0_x_drawR->GetBinContent(i);
    double z1 = h0_x_drawR->GetBinError(i);
    if(x1!=0){
      h0_x_drawR->SetBinContent(i,y1/x1);
      h0_x_drawR->SetBinError(i,z1/x1);
    }
  }
	
  TH1D *fitRatio = (TH1D*) h0_inclR->Clone("fitRatio");

  ////////////////////////////  template fit plot      

  TCanvas *c1 = new TCanvas("c1","c1",500,500);
  c1->cd();
  TPad *pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
  TPad *pad2 = new TPad("pad2","pad2",0.,0.0,1.0,0.3);
  pad1->Draw();
  pad1->cd();
  pad1->SetLeftMargin(0.2);
  pad1->SetBottomMargin(0.04);	

     		
  int numPar = 2;
  TF1 *func;

  /////////////////////// Configure the fit function /////////////////////

  cout << ":::::  outside do3templateFit :::::: " << endl; 
  
  if(do2templateFit){
    func = new TF1("func",func_temp_1,low_x,high_x,1);
  }
  else if(do3templateFit){
    func = new TF1("func",func_temp_2,low_x,high_x,2);
   
    //func->FixParameter(1,cFixVal);
    //func = new TF1("func",func_temp_cFix,low_x,high_x,1);
    cout << ":::::  inside do3templateFit :::::: " << endl; 
  }
  
  ////////////////////  End configure fit function ///////////////////////////

  ///////// initialize parameters to diJet MC truth values
  func->SetParameter(0,0.4);
  func->SetParameter(1,cFixVal);

  // if(ispp){
  //   if(isJ2) func->SetParameter(0,0.3715);
  //   else if(isJ3) func->SetParameter(0,0.3535);
  //   else if(isJ4) func->SetParameter(0,0.3241);
  //   else {};
  // }
  // else if(isC2){
  //   if(isJ2) func->SetParameter(0,0.3991);
  //   else if(isJ3) func->SetParameter(0,0.3554);
  //   else if(isJ4) func->SetParameter(0,0.3466);
  //   else{} ;
  // }
  // else if(isC1){
  //   if(isJ2) func->SetParameter(0,0.3606);
  //   else if(isJ3) func->SetParameter(0,3723);
  //   else if(isJ4) func->SetParameter(0,0.3652);
  //   else{} ;
  // }

	
  if(do2templateFit){
    func->SetParName(0,"b");
  }
  else if(do3templateFit){
    func->SetParName(0,"b");
    func->SetParName(1,"c");
  }
  func->SetParLimits(0,0.0,1.0);
  func->SetParLimits(1,0.0,1.0);
  //func->SetParLimits(2,0.0,1.0);
  //func->SetParLimits(3,0.0,1.0);

  TH1D *h_draw = (TH1D*) h0_inclR->Clone("h_draw");

  h0_inclR->Fit(func,"M R","N",low_x,high_x);
  //h0_inclR->Fit(func,"WL M R","N",low_x,high_x);

  gStyle->SetOptFit(0);
  h0_inclR->SetTitle("");
  h0_inclR->SetStats(0);
		
  h_draw->SetMarkerStyle(8);
  h_draw->SetMarkerColor(kBlack);
  h_draw->SetLineColor(kBlack);
  h0_inclR->SetMarkerStyle(8);
  h0_inclR->SetMarkerColor(kBlack);
		
  //h_muRelPt->SetFillColorAlpha(kBlack,0.5);
  h0_bR->SetStats(0);
  h0_cR->SetStats(0);
  h0_lR->SetStats(0);
  h0_xR->SetStats(0);

  h0_b_drawR->SetStats(0);
  h0_c_drawR->SetStats(0);
  h0_l_drawR->SetStats(0);
  h0_x_drawR->SetStats(0);

  double alphaVal = 0.6;
  double markerVal = 0.0;
  double markerVal2 = 1.0;
		
  h0_bR->SetMarkerStyle(20);
  h0_bR->SetMarkerSize(markerVal);
  h0_bR->SetMarkerColor(kRed);
  h0_bR->SetLineColor(kRed);
  h0_bR->SetFillColorAlpha(kRed,alphaVal);

  h0_b_drawR->SetMarkerStyle(20);
  h0_b_drawR->SetMarkerSize(markerVal2);
  h0_b_drawR->SetMarkerColor(kRed);
  h0_b_drawR->SetLineColor(kRed);
  h0_b_drawR->SetFillColorAlpha(kRed,alphaVal);

  TH1D *h0_bR2 = (TH1D*) h0_bR->Clone("h0_bR2");
  h0_bR2->SetFillColorAlpha(kRed,1);

  h0_cR->SetMarkerStyle(20);
  h0_cR->SetMarkerSize(markerVal);
  h0_cR->SetMarkerColor(kGreen+1);
  h0_cR->SetLineColor(kGreen+1);
  h0_cR->SetFillColorAlpha(kGreen+1,alphaVal);

  h0_c_drawR->SetMarkerStyle(20);
  h0_c_drawR->SetMarkerSize(markerVal2);
  h0_c_drawR->SetMarkerColor(kGreen+1);
  h0_c_drawR->SetLineColor(kGreen+1);
  h0_c_drawR->SetFillColorAlpha(kGreen+1,alphaVal);

  TH1D *h0_cR2 = (TH1D*) h0_cR->Clone("h0_cR2");
  h0_cR2->SetFillColorAlpha(kGreen+1,1);

  //////// Configure histogram fill color /////////////
	        
  h0_lR->SetMarkerStyle(20);
  h0_lR->SetMarkerSize(markerVal);
  h0_l_drawR->SetMarkerStyle(20);
  h0_l_drawR->SetMarkerSize(markerVal2);
  if(do2templateFit){
    h0_lR->SetMarkerColor(kBlue+2);
    h0_lR->SetLineColor(kBlue+2);
    h0_lR->SetFillColorAlpha(kBlue+2,alphaVal);
    h0_l_drawR->SetMarkerColor(kBlue+2);
    h0_l_drawR->SetLineColor(kBlue+2);
    h0_l_drawR->SetFillColorAlpha(kBlue+2,alphaVal);
  }
  else{
    h0_lR->SetMarkerColor(kBlue-4);
    h0_lR->SetLineColor(kBlue-4);
    h0_lR->SetFillColorAlpha(kBlue-4,alphaVal);
    h0_l_drawR->SetMarkerColor(kBlue-4);
    h0_l_drawR->SetLineColor(kBlue-4);
    h0_l_drawR->SetFillColorAlpha(kBlue-4,alphaVal);
  }

  /// ----------- save shapes of templates for later comparison ------------
  // TFile *save_templates_file = TFile::Open("save_templates_mu12.root","recreate");
  // h_draw->Write("h_data");
  // h0_b_drawR->Write("h_b");
  // h0_c_drawR->Write("h_c");
  // h0_l_drawR->Write("h_l");
  // save_templates_file->Close();
  

    
    
 
  TH1D *h0_lR2 = (TH1D*) h0_lR->Clone("h0_lR2");
 
		
  h0_xR->SetMarkerStyle(20);
  h0_xR->SetMarkerSize(markerVal);
  h0_xR->SetMarkerColor(kPink+1);
  h0_xR->SetLineColor(kPink+1);
  h0_xR->SetFillColorAlpha(kPink+1,alphaVal);

  TH1D *h0_xR2 = (TH1D*) h0_xR->Clone("h0_xR2");

  h0_x_drawR->SetMarkerStyle(20);
  h0_x_drawR->SetMarkerSize(markerVal2);
  h0_x_drawR->SetMarkerColor(kPink+1);
  h0_x_drawR->SetLineColor(kPink+1);
  h0_x_drawR->SetFillColorAlpha(kPink+1,alphaVal);


  double p0 = func->GetParameter(0);
  double ep0 = func->GetParError(0);
  double p1 = func->GetParameter(1);
  double ep1 = func->GetParError(1);
  double p2 = func->GetParameter(2);
  double ep2 = func->GetParError(2);
  double chi2 = func->GetChisquare();
  double ndof = func->GetNDF() * 1.0;

  cout << "chi2 from fit = " << chi2 << endl;

  result[2] = p0;
  result[3] = ep0;

  h0_incl->SetStats(1);

  TH1D *h_muRelPt_l_scaled = (TH1D*) h0_lR->Clone("h_muRelPt_l_scaled");
  TH1D *h_muRelPt_c_scaled = (TH1D*) h0_cR->Clone("h_muRelPt_c_scaled");
  TH1D *h_muRelPt_b_scaled = (TH1D*) h0_bR->Clone("h_muRelPt_b_scaled");
  TH1D *h_muRelPt_x_scaled = (TH1D*) h0_xR->Clone("h_muRelPt_x_scaled");

  TH1D *h_muRelPt_l_scaled2 = (TH1D*) h0_lR2->Clone("h_muRelPt_l_scaled2");
  TH1D *h_muRelPt_c_scaled2 = (TH1D*) h0_cR2->Clone("h_muRelPt_c_scaled2");
  TH1D *h_muRelPt_b_scaled2 = (TH1D*) h0_bR2->Clone("h_muRelPt_b_scaled2");
  TH1D *h_muRelPt_x_scaled2 = (TH1D*) h0_xR2->Clone("h_muRelPt_x_scaled2");
		
  //TH1D *h_muRelPt_bGS_scaled = (TH1D*) h_muRelPt_bGS->Clone("h_muRelPt_bGS_scaled");

  

		
  //////////////  configure scaled histos ///////////////////

  if(do2templateFit){
    h_muRelPt_b_scaled->Scale(p0);
    h_muRelPt_l_scaled->Scale(1-p0);
    h_muRelPt_b_scaled2->Scale(p0);
    h_muRelPt_l_scaled2->Scale(1-p0);
  }
  else if(do3templateFit){
    h_muRelPt_b_scaled->Scale(p0);
    h_muRelPt_c_scaled->Scale(p1);
    h_muRelPt_l_scaled->Scale(1-p0-p1);
    h_muRelPt_b_scaled2->Scale(p0);
    h_muRelPt_c_scaled2->Scale(p1);
    h_muRelPt_l_scaled2->Scale(1-p0-p1);
  }

  h0_l->SetStats(0);

  //cout << "p0 = " << p0 << ", fixVal = " << fixVal << ", 1-p0-fixVal = " << 1 - fixVal - p0 << endl;
		

  //////////////// configure stacked histogram
  h_stack->Add(h_muRelPt_b_scaled);
  if(do3templateFit) h_stack->Add(h_muRelPt_c_scaled);
  h_stack->Add(h_muRelPt_l_scaled);

  h_stack2->Add(h_muRelPt_b_scaled2);  
  if(do3templateFit) h_stack2->Add(h_muRelPt_c_scaled2);
  h_stack2->Add(h_muRelPt_l_scaled2);

  TH1D *stack_histo_rep = (TH1D*) h_muRelPt_b_scaled->Clone("stack_histo_rep");
  if(do3templateFit) stack_histo_rep->Add(h_muRelPt_c_scaled);
  stack_histo_rep->Add(h_muRelPt_l_scaled);

  ////////////// end configure stacked histogram


  cout << "b template integral = " << h_muRelPt_b_scaled->Integral() << endl;
		
  h_stack->Draw();
  h_stack->GetXaxis()->SetLimits(0.0,3.0);
  h_stack->GetXaxis()->SetLabelSize(0);
  h_stack->GetYaxis()->SetTitleSize(0.08);
  h_stack->GetYaxis()->SetLabelSize(0.05);
  h_stack->GetYaxis()->SetTitle("Entries");
  h_stack->Draw("hist");
  h_stack2->Draw("same");
  h_draw->Draw("ep same");
  h_stack->SetMinimum(0.0);
  h_stack->SetMaximum(1.6);
  auto legend = new TLegend(0.68,0.65,0.88,0.87);

  // configure fit legend
  if(isData){
    legend->AddEntry(h0_inclR,"Data","p");
  }
  else{
    legend->AddEntry(h0_inclR,"Simulation","p");
  }
	
  legend->AddEntry(h_muRelPt_b_scaled,"#font[52]{b} jets","f");
  if(do3templateFit){
    legend->AddEntry(h_muRelPt_c_scaled,"#font[52]{c} jets","f");
    legend->AddEntry(h_muRelPt_l_scaled,"light jets","f");
  }
  else legend->AddEntry(h_muRelPt_l_scaled,"light+#font[52]{c} jets","f");
  
  
  legend->SetBorderSize(0);
  legend->Draw();

  TLatex *t_title = new TLatex();
  TLatex *t_pythia = new TLatex();
  TLatex *t_pt = new TLatex();
  TLatex *t_eta = new TLatex();
  TLatex *t_HLT = new TLatex();
  TLatex *t_b = new TLatex();	
  TLatex *t_eb = new TLatex();
  TLatex *t_b_truth = new TLatex();	
  TLatex *t_eb_truth = new TLatex();

  t_title->SetTextFont(62);
  t_pythia->SetTextFont(42);
  t_pt->SetTextFont(42);
  t_eta->SetTextFont(42);
  t_HLT->SetTextFont(42);
  t_b->SetTextFont(62);
  t_eb->SetTextFont(42);
  t_b_truth->SetTextFont(42);
  t_eb_truth->SetTextFont(42);

  t_title->SetTextSize(0.055);
  t_pythia->SetTextSize(0.047);
  t_pt->SetTextSize(0.045);
  t_HLT->SetTextSize(0.045);
  t_b->SetTextSize(0.045);

  double x_t0 = 0.5;
  double x_t1 = 0.22;
  double x_t = 0.45;
  double y_t1 = 0.92;
  double y_t2 = 0.92;
  double y_t3 = 0.7;
  double y_t4 = 0.6;
  double y_t5 = 0.6;
  double y_t6 = 0.5;
  double y_t7 = 0.50;
  double y_t8 = 0.4;
  double y_t9 = 0.8;
		


  
  t_title->DrawLatexNDC(x_t1,y_t1,"CMS #scale[0.8]{#font[52]{Preliminary}}");
  if(isData){
    if(ispp){
      if(isMu7) t_pythia->DrawLatexNDC(x_t0,y_t2,"#font[42]{pp 5.02 TeV (274 pb^{-1})}");
      else if(isMu12) t_pythia->DrawLatexNDC(x_t0,y_t2,"#font[42]{pp 5.02 TeV (301 pb^{-1})}");
      else{};
    }
	  
    if(isC1){
      if(isMu7) t_pythia->DrawLatexNDC(x_t0,y_t2,"PbPb 0-30% 5.02 TeV (787 #mub^{-1})");
      else if(isMu12) t_pythia->DrawLatexNDC(x_t0,y_t2,"PbPb 0-30% 5.02 TeV (1689 #mub^{-1})");
      else{};
    }
    if(isC2){
      if(isMu7) t_pythia->DrawLatexNDC(x_t0,y_t2,"PbPb 30-30% 5.02 TeV (787 #mub^{-1})");
      else if(isMu12) t_pythia->DrawLatexNDC(x_t0,y_t2,"PbPb 30-30% 5.02 TeV (1689 #mub^{-1})");
      else{};
    }
  }
            
  if(!isData) {
    if(ispp) t_pythia->DrawLatexNDC(x_t0,y_t2,"PYTHIA (5.02 TeV)");
    if(isC1) t_pythia->DrawLatexNDC(x_t0,y_t2,"PYTHIA+HYDJET 0-30% (5.02 TeV)");
    if(isC2) t_pythia->DrawLatexNDC(x_t0,y_t2,"PYTHIA+HYDJET 30-30% (5.02 TeV)");
  }

			
  
  if(isJ1) t_pt->DrawLatexNDC(0.23,0.71,"80 < #font[52]{p}_{T}^{jet} < 100 GeV, |#it{#eta}^{jet}| < 1.6");
  if(isJ2) t_pt->DrawLatexNDC(0.23,0.71,"100 < #font[52]{p}_{T}^{jet} < 120 GeV, |#it{#eta}^{jet}| < 1.6");
  if(isJ3) t_pt->DrawLatexNDC(0.23,0.71,"120 < #font[52]{p}_{T}^{jet} < 150 GeV, |#it{#eta}^{jet}| < 1.6");
  if(isJ4) t_pt->DrawLatexNDC(0.23,0.71,"150 < #font[52]{p}_{T}^{jet} < 200 GeV, |#it{#eta}^{jet}| < 1.6");
  if(isJ5) t_pt->DrawLatexNDC(0.23,0.71,"200 < #font[52]{p}_{T}^{jet} < 300 GeV, |#it{#eta}^{jet}| < 1.6");
  if(isJ6) t_pt->DrawLatexNDC(0.23,0.71,"300 < #font[52]{p}_{T}^{jet} < 500 GeV, |#it{#eta}^{jet}| < 1.6");
	
  if(isMu5) t_HLT->DrawLatexNDC(0.23,0.65,"#font[52]{p}_{T}^{#mu} > 7 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  else if(isMu7) t_HLT->DrawLatexNDC(0.23,0.65,"9 < #font[52]{p}_{T}^{#mu} < 14 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  else if(isMu12) t_HLT->DrawLatexNDC(0.23,0.65,"#font[52]{p}_{T}^{#mu} > 14 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  else{};
  
  t_b->DrawLatexNDC(0.48,0.52,Form("#it{f}_{#it{b}}^{#it{#mu}-tagged,#it{#mu}-trig} = %.4f #pm %.4f", p0, ep0));
  //if(!isData) t_b->DrawLatexNDC(0.48,0.45,Form("#it{f}_{#it{b}}^{true} = %.4f #pm %.4f", b_frac, eb_frac));

  t_b->SetTextFont(42);
  if(isData) {
    t_b->DrawLatexNDC(0.48,0.45,Form("#chi^{2}/ndof = %3.1f",chi2/ndof));
    t_b->DrawLatexNDC(0.48,0.38,Form("#it{N}^{jet} = %i",Njet));
    //t_b->DrawLatexNDC(0.53,0.31,"#it{g}#rightarrow#it{b}#bar{#it{b}} jets increased by 20%");
    //t_b->DrawLatexNDC(0.53,0.24,"JER in MC smeared by 20%");
  }
  
  else{
   
    t_b->DrawLatexNDC(0.48,0.38,Form("#chi^{2}/ndof = %3.1f",chi2/ndof));
    //t_b->DrawLatexNDC(0.53,0.31,"#it{g}#rightarrow#it{b}#bar{#it{b}} jets increased by 20%");
  }


  if(ispp){
    t_b->DrawLatexNDC(0.23,0.83,"Anti-#font[52]{k}_{T} PF jets, tight muon ID");
    if(isMu7) t_b->DrawLatexNDC(0.23,0.77,"#font[82]{HLT_HIL3Mu7_v1}");
    else if(isMu12) t_b->DrawLatexNDC(0.23,0.77,"#font[82]{HLT_HIL3Mu12_v1}");
    else{};
  }
  else{
    t_b->DrawLatexNDC(0.23,0.83,"Anti-#font[52]{k}_{T} CsPF jets, tight muon ID");
    if(isMu7) t_b->DrawLatexNDC(0.23,0.77,"#font[82]{HLT_HIL3Mu7_NHitQ10_v1}");
    else if(isMu12) t_b->DrawLatexNDC(0.23,0.77,"#font[82]{HLT_HIL3Mu12_v1}");
    else{};
  }
  // if(!isData){
  //   t_b_truth->DrawLatexNDC(x_t,y_t7,Form("#scale[0.8]{b_{count} = %.4f #pm}",b_frac));
  //   t_eb_truth->DrawLatexNDC(x_t+0.183,y_t7,Form("#scale[0.8]{%.4f}",eb_frac));
  // }
		
  c1->cd();
  pad2->SetBottomMargin(0.4);
  pad2->SetLeftMargin(0.2);
  pad2->SetTopMargin(0.04);
  pad2->Draw();
  pad2->cd();
				
  //fitRatio->Divide(func);
  fitRatio->Divide(fitRatio,stack_histo_rep,1,1,"");
  fitRatio->SetStats(0);
  fitRatio->SetTitle("");
  fitRatio->SetMarkerStyle(8);
  fitRatio->SetMarkerColor(kBlack);
  fitRatio->SetLineColor(kBlack);
  fitRatio->SetFillColorAlpha(kBlack,0.5);
  fitRatio->Draw("e1");
  fitRatio->GetYaxis()->SetTitle("Points / Fit");
  fitRatio->GetYaxis()->SetTitleSize(0.14);
  fitRatio->GetYaxis()->SetLabelSize(0.12);
  fitRatio->GetYaxis()->SetTitleOffset(0.5);
  fitRatio->GetXaxis()->SetTitle("muon #font[52]{p}_{T}^{rel} [GeV]");
  fitRatio->GetXaxis()->SetTitleOffset(1.1);
  fitRatio->GetXaxis()->SetTitleSize(.14);
  fitRatio->GetXaxis()->SetLabelSize(0.11);
  //fitRatio->GetXaxis()->SetRangeUser(0.0,4.0);
  fitRatio->SetMinimum(0.6);
  fitRatio->SetMaximum(1.4);
  fitRatio->GetYaxis()->SetNdivisions(404);
  TLine *line2 = new TLine(muRelPtAxis[0],1.0,muRelPtAxis[M-1],1.0);
  line2->SetLineStyle(7);
  line2->Draw();
  TLine *line1 = new TLine(muRelPtAxis[0],1.2,muRelPtAxis[M-1],1.2);
  line1->SetLineStyle(2);
  line1->Draw();
  TLine *line3 = new TLine(muRelPtAxis[0],0.8,muRelPtAxis[M-1],0.8);
  line3->SetLineStyle(2);
  line3->Draw();
        


  ////////////////////////////  template shapes plot

  TCanvas *c2 = new TCanvas("c2","c2",500,500);
  c2->cd();
  TPad *pad3 = new TPad("pad3","pad3",0.0,0.4,1.0,1.0);
  TPad *pad4 = new TPad("pad4","pad4",0.0,0.0,1.0,0.4);
  pad3->Draw();
  pad4->Draw();
  pad3->cd();
  pad3->SetLeftMargin(0.2);
  pad3->SetBottomMargin(0.03);

	

  h0_l_drawR->SetTitle("");
  h0_l_drawR->GetXaxis()->SetTitle("");
  h0_l_drawR->GetXaxis()->SetLabelSize(0);
  h0_l_drawR->GetXaxis()->SetRangeUser(muRelPtAxis[0],muRelPtAxis[M-1]);
  h0_l_drawR->GetYaxis()->SetTitle("a.u.");
  h0_l_drawR->GetYaxis()->SetLabelSize(0.06);
  h0_l_drawR->GetYaxis()->SetTitleSize(0.09);
  h0_l_drawR->GetYaxis()->SetRangeUser(0.0,1.5);
			
  //////////// configure which template shapes to draw
		
  
  h0_l_drawR->Draw();
  h0_b_drawR->Draw("same");
  if(do3templateFit) h0_c_drawR->Draw("same");
  
  TLegend *l2 = new TLegend(0.65,0.15,0.85,0.4);

  /////// configure the legend for template shapes plot

  if(do2templateFit) l2->AddEntry(h0_l_drawR,"light+#font[52]{c} jets","p");
  else l2->AddEntry(h0_l_drawR,"light jets","p");
  if(do3templateFit) l2->AddEntry(h0_c_drawR,"#font[52]{c} jets","p");
  l2->AddEntry(h0_b_drawR,"#font[52]{b} jets","p");
  //l2->AddEntry(h0_ghost_drawR,"#font[52]{x} jets","p");
  

  //l2->AddEntry(h0_ghostR,"ghost jets","p");
  l2->SetBorderSize(0);
  l2->Draw();

  t_title->DrawLatexNDC(x_t1,y_t1,"CMS #scale[0.8]{#font[52]{Preliminary}}");
			
  if(ispp) t_pythia->DrawLatexNDC(x_t0,y_t2,"PYTHIA (5.02 TeV)");
  else {
    if(isC1) t_pythia->DrawLatexNDC(x_t0,y_t2,"PYTHIA+HYDJET 0-30% (5.02 TeV)");
    if(isC2) t_pythia->DrawLatexNDC(x_t0,y_t2,"PYTHIA+HYDJET 30-30% (5.02 TeV)");
  }
			
  //if(isC0C1){
  //t_pythia->DrawLatexNDC(x_t,y_t2,"#scale[0.8]{PYTHIA+HYDJET 0-30%, #sqrt{#font[52]{s}_{NN}} = 5 TeV}");
  //}
            
			
			
  
  if(isJ1) t_pt->DrawLatexNDC(x_t,y_t3,"80 < #font[52]{p}_{T}^{jet} < 100 GeV, |#font[52]{#eta}^{jet}| < 1.6");
  else if(isJ2) t_pt->DrawLatexNDC(x_t,y_t3,"100 < #font[52]{p}_{T}^{jet} < 120 GeV, |#font[52]{#eta}^{jet}| < 1.6");
  else if(isJ3) t_pt->DrawLatexNDC(x_t,y_t3,"120 < #font[52]{p}_{T}^{jet} < 150 GeV, |#font[52]{#eta}^{jet}| < 1.6");
  else if(isJ4) t_pt->DrawLatexNDC(x_t,y_t3,"150 < #font[52]{p}_{T}^{jet} < 200 GeV, |#font[52]{#eta}^{jet}| < 1.6");
  else if(isJ5) t_pt->DrawLatexNDC(x_t,y_t3,"200 < #font[52]{p}_{T}^{jet} < 300 GeV, |#font[52]{#eta}^{jet}| < 1.6");
  else if(isJ6) t_pt->DrawLatexNDC(x_t,y_t3,"300 < #font[52]{p}_{T}^{jet} < 500 GeV, |#font[52]{#eta}^{jet}| < 1.6");
  else {};
	
  if(isMu7){
    t_pt->DrawLatexNDC(x_t, y_t4,"9 < #font[52]{p}_{T}^{#mu} < 14 GeV, |#font[52]{#eta}^{#mu}| < 2.0, tight muon ID");
  }
  else if(isMu12){
    t_pt->DrawLatexNDC(x_t, y_t4,"#font[52]{p}_{T}^{#mu} > 14 GeV, |#font[52]{#eta}^{#mu}| < 2.0, tight muon ID");
  }
  //t_pt->DrawLatexNDC(x_t, y_t4,"#scale[0.8]{#font[52]{p}_{T}^{#mu} > 9 GeV, |#font[52]{#eta}^{#mu}| < 2.0, tight muon ID}");
			
  //t_HLT->DrawLatexNDC(x_t,y_t5,"#scale[0.8]{HLT_HIL3Mu5_NHitQ10_v1}");
        
  pad4->cd();
  pad4->SetLeftMargin(0.2);
  pad4->SetBottomMargin(0.4);

  TH1D *r1 = (TH1D*) h0_l_drawR->Clone("r1");
  TH1D *r2 = (TH1D*) h0_c_drawR->Clone("r2");
  r1->Divide(h0_bR);
  r2->Divide(h0_bR);
  //r1->SetMarkerColor(kBlack);
  //r1->SetMarkerStyle(24);
  r1->GetXaxis()->SetTitle("muon #font[52]{p}_{T}^{rel} [GeV]");
  r1->GetXaxis()->SetLabelSize(0.10);
  r1->GetXaxis()->SetTitleSize(0.13);
  r1->GetYaxis()->SetTitle("Ratio to #it{b}");
  r1->GetYaxis()->SetLabelSize(0.10);
  r1->GetYaxis()->SetTitleSize(0.11);
  r1->GetYaxis()->SetRangeUser(0.0,2.0);
  r1->SetTitle("");
  r1->SetStats(0);
  r1->GetXaxis()->SetRangeUser(muRelPtAxis[0],muRelPtAxis[M-1]);
  r1->GetYaxis()->SetNdivisions(404);
  r1->Draw();
  if(do3templateFit) r2->Draw("same");
  line2->Draw();

  // save the plots
	

  if(ispp){

    if(isJ1){
      c1->SaveAs("../../figures/templateFits/pp/J1/templateFit_diJet.pdf");		
      c2->SaveAs("../../figures/templateShapes/pp/J1/templateShape_diJet.pdf");
    }		
    if(isJ2){
      c1->cd();
      c1->SaveAs("../../figures/templateFits/pp/J2/templateFit_diJet.pdf");		
      c2->cd();
      c2->SaveAs("../../figures/templateShapes/pp/J2/templateShape_diJet.pdf");
    }		
    if(isJ3){
      c1->SaveAs("../../figures/templateFits/pp/J3/templateFit_diJet.pdf");		
      c2->SaveAs("../../figures/templateShapes/pp/J3/templateShape_diJet.pdf");
    }		
    if(isJ4){
      c1->SaveAs("../../figures/templateFits/pp/J4/templateFit_diJet.pdf");		
      c2->SaveAs("../../figures/templateShapes/pp/J4/templateShape_diJet.pdf");
    }		
    if(isJ5){
      c1->SaveAs("../../figures/templateFits/pp/J5/templateFit_diJet.pdf");		
      c2->SaveAs("../../figures/templateShapes/pp/J5/templateShape_diJet.pdf");
    }		
    if(isJ6){
      c1->SaveAs("../../figures/templateFits/pp/J6/templateFit_diJet.pdf");		
      c2->SaveAs("../../figures/templateShapes/pp/J6/templateShape_diJet.pdf");
    }		

  }


  if(!ispp && !mergeBtemplates && !mergeCtemplates){
    if(isC2){
      if(isJ1){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J1/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J1/templateShape_diJet.pdf");
      }		
      if(isJ2){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J2/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J2/templateShape_diJet.pdf");
      }		
      if(isJ3){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J3/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J3/templateShape_diJet.pdf");
      }		
      if(isJ4){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J4/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J4/templateShape_diJet.pdf");
      }		
      if(isJ5){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J5/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J5/templateShape_diJet.pdf");
      }		
      if(isJ6){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J6/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J6/templateShape_diJet.pdf");
      }		
    }
    if(isC1){
      if(isJ1){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J1/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J1/templateShape_diJet.pdf");
      }		
      if(isJ2){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J2/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J2/templateShape_diJet.pdf");
      }		
      if(isJ3){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J3/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J3/templateShape_diJet.pdf");
      }		
      if(isJ4){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J4/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J4/templateShape_diJet.pdf");
      }		
      if(isJ5){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J5/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J5/templateShape_diJet.pdf");
      }		
      if(isJ6){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J6/templateFit_diJet.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J6/templateShape_diJet.pdf");
      }		
    }
  }





  if(!ispp && mergeBtemplates && !mergeCtemplates){
    if(isC2){
      if(isJ1){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J1/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J1/templateShape_bJetEnhanced.pdf");
      }		
      if(isJ2){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J2/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J2/templateShape_bJetEnhanced.pdf");
      }		
      if(isJ3){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J3/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J3/templateShape_bJetEnhanced.pdf");
      }		
      if(isJ4){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J4/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J4/templateShape_bJetEnhanced.pdf");
      }		
      if(isJ5){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J5/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J5/templateShape_bJetEnhanced.pdf");
      }		
      if(isJ6){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J6/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J6/templateShape_bJetEnhanced.pdf");
      }		
    }
    if(isC1){
      if(isJ1){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J1/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J1/templateShape_bJetEnhanced.pdf");
      }		
      if(isJ2){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J2/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J2/templateShape_bJetEnhanced.pdf");
      }		
      if(isJ3){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J3/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J3/templateShape_bJetEnhanced.pdf");
      }		
      if(isJ4){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J4/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J4/templateShape_bJetEnhanced.pdf");
      }		
      if(isJ5){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J5/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J5/templateShape_bJetEnhanced.pdf");
      }		
      if(isJ6){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J6/templateFit_bJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J6/templateShape_bJetEnhanced.pdf");
      }		
    }
  }


  if(!ispp && mergeBtemplates && mergeCtemplates){
    if(isC2){
      if(isJ1){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J1/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J1/templateShape_bPlusMuJetEnhanced.pdf");
      }		
      if(isJ2){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J2/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J2/templateShape_bPlusMuJetEnhanced.pdf");
      }		
      if(isJ3){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J3/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J3/templateShape_bPlusMuJetEnhanced.pdf");
      }		
      if(isJ4){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J4/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J4/templateShape_bPlusMuJetEnhanced.pdf");
      }		
      if(isJ5){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J5/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J5/templateShape_bPlusMuJetEnhanced.pdf");
      }		
      if(isJ6){
	c1->SaveAs("../../figures/templateFits/PbPb_3090/J6/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_3090/J6/templateShape_bPlusMuJetEnhanced.pdf");
      }		
    }
    if(isC1){
      if(isJ1){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J1/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J1/templateShape_bPlusMuJetEnhanced.pdf");
      }		
      if(isJ2){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J2/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J2/templateShape_bPlusMuJetEnhanced.pdf");
      }		
      if(isJ3){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J3/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J3/templateShape_bPlusMuJetEnhanced.pdf");
      }		
      if(isJ4){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J4/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J4/templateShape_bPlusMuJetEnhanced.pdf");
      }		
      if(isJ5){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J5/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J5/templateShape_bPlusMuJetEnhanced.pdf");
      }		
      if(isJ6){
	c1->SaveAs("../../figures/templateFits/PbPb_030/J6/templateFit_bPlusMuJetEnhanced.pdf");		
	c2->SaveAs("../../figures/templateShapes/PbPb_030/J6/templateShape_bPlusMuJetEnhanced.pdf");
      }		
    }
  }

  if(returnValueIndex == 1) return p0;
  if(returnValueIndex == 2) return ep0;
  if(returnValueIndex == 3) return chi2/ndof;


  











}
