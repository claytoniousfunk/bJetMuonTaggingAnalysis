
#include "../../headers/functions/divideByBinwidth.h"
#include "../../headers/goldenFileNames.h"

TFile *f1, *f2, *f0;

void fractionEvolution(bool ispp = 1, bool isC3 = 0, bool isC2 = 0, bool isC1 = 0){

  /* if(ispp) f1 = TFile::Open(goldenFile_PYTHIA_mu12_pThat15_newJetBins); */
  /* else f1 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat15_newJetBins); */

  if(ispp){
    f0 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/final/response/PYTHIA_response_pThat-15_inclJets.root");
    f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/final/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjet_jetTrkMaxFilter_vzReweight_jetPtReweight_dRReweight_projectableTemplates.root");
    f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/final/pp_HighEGJet_jet60_mu12_tight_pTmu-14_projectableTemplates.root");
  }
  else{
    f0 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/response/PH_DiJet_pTjet-5_pThat-15_response_fineCentBins_prime.root");
    f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_fineCentBins_projectableTemplates_allTemplates.root");
    f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/final/PbPb_HardProbes_scan_jet60_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates.root");    
  }
  
  TH2D *h0, *h1, *h2, *h3, *h4; // 2d flavor-pt maps
  TH2D *hh0;
  // CENT BIN 0
  TH1D *h0_incl; // inclusive projection
  TH1D *h0_b, *h0_bGS, *h0_c, *h0_d, *h0_g, *h0_s, *h0_u; // projections of each quark flavor
  TH1D *h0_bbar, *h0_cbar, *h0_dbar, *h0_sbar, *h0_ubar; // projections of each antiquark flavor
  TH1D *h0_ghost;
  TH1D *h0_noFlavor;


  TH2D *j0, *j1, *j2, *j3, *j4; // 2d flavor-eta maps
  TH2D *jj0, *jj1, *jj2, *jj3;
  // CENT BIN 0
  TH1D *j0_incl;
  TH1D *j0_b, *j0_bGS, *j0_c, *j0_d, *j0_g, *j0_s, *j0_u; // projections of each quark flavor
  TH1D *j0_bbar, *j0_cbar, *j0_dbar, *j0_sbar, *j0_ubar; // projections of each antiquark flavor
  TH1D *j0_ghost;
  TH1D *j0_noFlavor;

  TH1D *j1_incl;
  TH1D *j1_b, *j1_bGS, *j1_c, *j1_d, *j1_g, *j1_s, *j1_u; // projections of each quark flavor
  TH1D *j1_bbar, *j1_cbar, *j1_dbar, *j1_sbar, *j1_ubar; // projections of each antiquark flavor
  TH1D *j1_ghost;
  TH1D *j1_noFlavor;

  TH1D *j2_incl;
  TH1D *j2_b, *j2_bGS, *j2_c, *j2_d, *j2_g, *j2_s, *j2_u; // projections of each quark flavor
  TH1D *j2_bbar, *j2_cbar, *j2_dbar, *j2_sbar, *j2_ubar; // projections of each antiquark flavor
  TH1D *j2_ghost;
  TH1D *j2_noFlavor;
	
	
  TH1D *j3_incl;
  TH1D *j3_b, *j3_bGS, *j3_c, *j3_d, *j3_g, *j3_s, *j3_u; // projections of each quark flavor
  TH1D *j3_bbar, *j3_cbar, *j3_dbar, *j3_sbar, *j3_ubar; // projections of each antiquark flavor
  TH1D *j3_ghost;
  TH1D *j3_noFlavor;

  TH1D *J1_incl, *J2_incl;  // histograms in data
  TH1D *JJ1_incl, *JJ2_incl;

  TH2D *x0, *xx0; // I need another histo
  TH1D *x0_incl; // inclusive projection
  TH1D *x0_b, *x0_bGS, *x0_c, *x0_d, *x0_g, *x0_s, *x0_u; // projections of each quark flavor
  TH1D *x0_bbar, *x0_cbar, *x0_dbar, *x0_sbar, *x0_ubar; // projections of each antiquark flavor
  TH1D *x0_ghost;
  TH1D *x0_noFlavor;
	
  // RETRIEVE 2D MAPS

  if(ispp){
    // f0->GetObject("h_inclGenJetPt_flavor", h0);
    // f0->GetObject("h_inclGenJetPt_inclGenMuonTag_flavor",j0);
    f1->GetObject("h_inclRecoJetPt_flavor", h0);
    f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor",j0);
    f0->GetObject("h_inclGenJetPt_inclRecoMuonTag_flavor",j1);
    //f1->GetObject("h_inclRecoJetPt_flavor", h0);
    //f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor",j0);
    //f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor",j1);
    //f1->GetObject("h_inclRecoJetPt_flavor",x0);
    f1->GetObject("h_inclGenJetPt_flavor",x0);
    f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor",j2);
    f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",j3);
    f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag",J1_incl);
    f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",J2_incl);
  }
  else if(isC3){
    // f0->GetObject("h_inclGenJetPt_flavor_C3", h0);
    // f0->GetObject("h_inclGenJetPt_inclGenMuonTag_flavor_C3",j0);
    f1->GetObject("h_inclRecoJetPt_flavor_C3", h0);
    f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C3",j0);
    f0->GetObject("h_inclGenJetPt_inclRecoMuonTag_flavor_C3",j1);
    //f1->GetObject("h_inclRecoJetPt_flavor_C3", h0);
    //f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C3",j0);
    //f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C3",j1);
    //f1->GetObject("h_inclRecoJetPt_flavor_C3",x0);
    f1->GetObject("h_inclGenJetPt_flavor_C3",x0);
    f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C3",j2);
    f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C3",j3);
    f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_C3",J1_incl);
    f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",J2_incl);

    // f0->GetObject("h_inclGenJetPt_flavor_C4", hh0);
    // f0->GetObject("h_inclGenJetPt_inclGenMuonTag_flavor_C4",jj0);
    f1->GetObject("h_inclRecoJetPt_flavor_C4", hh0);
    f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C4",jj0);
    f0->GetObject("h_inclGenJetPt_inclRecoMuonTag_flavor_C4",jj1);
    //f1->GetObject("h_inclRecoJetPt_flavor_C4", hh0); 
    //f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C4",jj0); 
    //f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C4",jj1);
    //f1->GetObject("h_inclRecoJetPt_flavor_C4",xx0);
    f1->GetObject("h_inclGenJetPt_flavor_C4",xx0);
    f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C4",jj2);
    f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C4",jj3);
    f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_C4",JJ1_incl);
    f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",JJ2_incl);

    h0->Add(hh0);
    j0->Add(jj0);
    j1->Add(jj1);
    j2->Add(jj2);
    j3->Add(jj3);
    J1_incl->Add(JJ1_incl);
    J2_incl->Add(JJ2_incl);
    x0->Add(xx0);
    
  }
  else if(isC2){
    // f0->GetObject("h_inclGenJetPt_flavor_C2", h0);
    // f0->GetObject("h_inclGenJetPt_inclGenMuonTag_flavor_C2",j0);
    f1->GetObject("h_inclRecoJetPt_flavor_C2", h0);
    f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C2",j0);
    f0->GetObject("h_inclGenJetPt_inclRecoMuonTag_flavor_C2",j1);
    //f1->GetObject("h_inclRecoJetPt_flavor_C2", h0);
    //f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C2",j0);
    //f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C2",j1);
    //f1->GetObject("h_inclRecoJetPt_flavor_C2",x0);
    f1->GetObject("h_inclGenJetPt_flavor_C2",x0);
    f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C2",j2);
    f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C2",j3);
    f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_C2",J1_incl);
    f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",J2_incl);
  }
  else if(isC1){
    // f0->GetObject("h_inclGenJetPt_flavor_C1", h0);
    // f0->GetObject("h_inclGenJetPt_inclGenMuonTag_flavor_C1",j0);
    f1->GetObject("h_inclRecoJetPt_flavor_C1", h0);
    f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C1",j0);
    f0->GetObject("h_inclGenJetPt_inclRecoMuonTag_flavor_C1",j1);
    //f1->GetObject("h_inclRecoJetPt_flavor_C1", h0);
    //f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C1",j0);
    //f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C1",j1);
    //f1->GetObject("h_inclRecoJetPt_flavor_C1",x0);
    f1->GetObject("h_inclGenJetPt_flavor_C1",x0);
    f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C1",j2);
    f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C1",j3);
    f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_C1",J1_incl);
    f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",J2_incl);
  }
  //factorization2
  // f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor",j0);
  // f1->GetObject("h_inclRecoJetPt_triggerOn_inclGenMuonTag_flavor",j1);
  // f1->GetObject("h_inclRecoJetPt_triggerOn_inclRecoMuonTag_flavor",j2);
  // f1->GetObject("h_inclRecoJetPt_triggerOn_inclRecoMuonTag_flavor",j3);
	
  TH1D *binFinder = h0->ProjectionY();
  TAxis *yaxis = binFinder->GetXaxis();
  double smallShift = 0.01;

  // PT
  // CENT BIN 0
  h0_incl = (TH1D*) h0->ProjectionX("h0_incl",binFinder->FindBin(-5+smallShift),binFinder->FindBin(22-smallShift));
  //TH1D *h0_incl_add = (TH1D*) h0->ProjectionX("h0_incl_add",binFinder->FindBin(1+smallShift),binFinder->FindBin(22-smallShift));
  //h0_incl->Add(h0_incl_add);

  h0_b = (TH1D*) h0->ProjectionX("h0_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  h0_bGS = (TH1D*) h0->ProjectionX("h0_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  h0_c = (TH1D*) h0->ProjectionX("h0_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
  h0_d = (TH1D*) h0->ProjectionX("h0_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
  h0_g = (TH1D*) h0->ProjectionX("h0_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
  h0_s = (TH1D*) h0->ProjectionX("h0_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
  h0_u = (TH1D*) h0->ProjectionX("h0_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
  h0_bbar = (TH1D*) h0->ProjectionX("h0_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  h0_cbar = (TH1D*) h0->ProjectionX("h0_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
  h0_dbar = (TH1D*) h0->ProjectionX("h0_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
  h0_sbar = (TH1D*) h0->ProjectionX("h0_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
  h0_ubar = (TH1D*) h0->ProjectionX("h0_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
  h0_ghost = (TH1D*) h0->ProjectionX("h0_ghost",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
  h0_noFlavor = (TH1D*) h0->ProjectionX("h0_noFlavor",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));
	
  // ETA
  // CENT BIN 0
  j0_incl = (TH1D*) j0->ProjectionX("j0_incl",binFinder->FindBin(-5+smallShift),binFinder->FindBin(22-smallShift));
  //TH1D *j0_incl_add = (TH1D*) j0->ProjectionX("j0_incl_add",binFinder->FindBin(1+smallShift),binFinder->FindBin(22-smallShift));
  //j0_incl->Add(j0_incl_add);

  j0_b = (TH1D*) j0->ProjectionX("j0_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  j0_bGS = (TH1D*) j0->ProjectionX("j0_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  j0_c = (TH1D*) j0->ProjectionX("j0_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
  j0_d = (TH1D*) j0->ProjectionX("j0_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
  j0_g = (TH1D*) j0->ProjectionX("j0_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
  j0_s = (TH1D*) j0->ProjectionX("j0_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
  j0_u = (TH1D*) j0->ProjectionX("j0_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
  j0_bbar = (TH1D*) j0->ProjectionX("j0_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  j0_cbar = (TH1D*) j0->ProjectionX("j0_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
  j0_dbar = (TH1D*) j0->ProjectionX("j0_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
  j0_sbar = (TH1D*) j0->ProjectionX("j0_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
  j0_ubar = (TH1D*) j0->ProjectionX("j0_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
  j0_ghost = (TH1D*) j0->ProjectionX("j0_ghost",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
  j0_noFlavor = (TH1D*) j0->ProjectionX("j0_noFlavor",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));

  x0_incl = (TH1D*) x0->ProjectionX("x0_incl",binFinder->FindBin(-5+smallShift),binFinder->FindBin(22-smallShift));
  //TH1D *x0_incl_add = (TH1D*) x0->ProjectionX("x0_incl_add",binFinder->FindBin(1+smallShift),binFinder->FindBin(22-smallShift));
  //x0_incl->Add(x0_incl_add);

  x0_b = (TH1D*) x0->ProjectionX("x0_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  x0_bGS = (TH1D*) x0->ProjectionX("x0_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  x0_c = (TH1D*) x0->ProjectionX("x0_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
  x0_d = (TH1D*) x0->ProjectionX("x0_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
  x0_g = (TH1D*) x0->ProjectionX("x0_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
  x0_s = (TH1D*) x0->ProjectionX("x0_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
  x0_u = (TH1D*) x0->ProjectionX("x0_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
  x0_bbar = (TH1D*) x0->ProjectionX("x0_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  x0_cbar = (TH1D*) x0->ProjectionX("x0_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
  x0_dbar = (TH1D*) x0->ProjectionX("x0_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
  x0_sbar = (TH1D*) x0->ProjectionX("x0_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
  x0_ubar = (TH1D*) x0->ProjectionX("x0_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
  x0_ghost = (TH1D*) x0->ProjectionX("x0_ghost",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
  x0_noFlavor = (TH1D*) x0->ProjectionX("x0_noFlavor",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));
	

  j1_incl = (TH1D*) j1->ProjectionX("j1_incl",binFinder->FindBin(-5+smallShift),binFinder->FindBin(22-smallShift));
  //TH1D *j1_incl_add = (TH1D*) j1->ProjectionX("j1_incl_add",binFinder->FindBin(1+smallShift),binFinder->FindBin(22-smallShift));
  //j1_incl->Add(j1_incl_add);

  j1_b = (TH1D*) j1->ProjectionX("j1_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  j1_bGS = (TH1D*) j1->ProjectionX("j1_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  j1_c = (TH1D*) j1->ProjectionX("j1_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
  j1_d = (TH1D*) j1->ProjectionX("j1_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
  j1_g = (TH1D*) j1->ProjectionX("j1_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
  j1_s = (TH1D*) j1->ProjectionX("j1_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
  j1_u = (TH1D*) j1->ProjectionX("j1_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
  j1_bbar = (TH1D*) j1->ProjectionX("j1_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  j1_cbar = (TH1D*) j1->ProjectionX("j1_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
  j1_dbar = (TH1D*) j1->ProjectionX("j1_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
  j1_sbar = (TH1D*) j1->ProjectionX("j1_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
  j1_ubar = (TH1D*) j1->ProjectionX("j1_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
  j1_ghost = (TH1D*) j1->ProjectionX("j1_ghost",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
  j1_noFlavor = (TH1D*) j1->ProjectionX("j1_noFlavor",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));


  j2_incl = (TH1D*) j2->ProjectionX("j2_incl",binFinder->FindBin(-5+smallShift),binFinder->FindBin(22-smallShift));
  //TH1D *j2_incl_add = (TH1D*) j2->ProjectionX("j2_incl_add",binFinder->FindBin(1+smallShift),binFinder->FindBin(0-smallShift));
  //j2_incl->Add(j2_incl_add);

  j2_b = (TH1D*) j2->ProjectionX("j2_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  j2_bGS = (TH1D*) j2->ProjectionX("j2_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  j2_c = (TH1D*) j2->ProjectionX("j2_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
  j2_d = (TH1D*) j2->ProjectionX("j2_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
  j2_g = (TH1D*) j2->ProjectionX("j2_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
  j2_s = (TH1D*) j2->ProjectionX("j2_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
  j2_u = (TH1D*) j2->ProjectionX("j2_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
  j2_bbar = (TH1D*) j2->ProjectionX("j2_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  j2_cbar = (TH1D*) j2->ProjectionX("j2_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
  j2_dbar = (TH1D*) j2->ProjectionX("j2_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
  j2_sbar = (TH1D*) j2->ProjectionX("j2_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
  j2_ubar = (TH1D*) j2->ProjectionX("j2_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
  j2_ghost = (TH1D*) j2->ProjectionX("j2_ghost",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
  j2_noFlavor = (TH1D*) j2->ProjectionX("j2_noFlavor",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));
	

  j3_incl = (TH1D*) j3->ProjectionX("j3_incl",binFinder->FindBin(-5+smallShift),binFinder->FindBin(22-smallShift));
  //TH1D* j3_incl_add = (TH1D*) j3->ProjectionX("j3_incl_add",binFinder->FindBin(1+smallShift),binFinder->FindBin(0-smallShift));
  //j3_incl->Add(j3_incl_add);

  j3_b = (TH1D*) j3->ProjectionX("j3_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  j3_bGS = (TH1D*) j3->ProjectionX("j3_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  j3_c = (TH1D*) j3->ProjectionX("j3_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
  j3_d = (TH1D*) j3->ProjectionX("j3_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
  j3_g = (TH1D*) j3->ProjectionX("j3_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
  j3_s = (TH1D*) j3->ProjectionX("j3_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
  j3_u = (TH1D*) j3->ProjectionX("j3_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
  j3_bbar = (TH1D*) j3->ProjectionX("j3_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  j3_cbar = (TH1D*) j3->ProjectionX("j3_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
  j3_dbar = (TH1D*) j3->ProjectionX("j3_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
  j3_sbar = (TH1D*) j3->ProjectionX("j3_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
  j3_ubar = (TH1D*) j3->ProjectionX("j3_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
  j3_ghost = (TH1D*) j3->ProjectionX("j3_ghost",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
  j3_noFlavor = (TH1D*) j3->ProjectionX("j3_noFlavor",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));
  // COMBINE QUARK AND ANTI-QUARK HISTOGRAMS
	
  // PT
  // CENT BIN 0
  h0_b->Add(h0_bbar);
  h0_b->Add(h0_bGS);
  h0_c->Add(h0_cbar);
  h0_d->Add(h0_dbar);
  h0_s->Add(h0_sbar);
  h0_u->Add(h0_ubar);

  x0_b->Add(x0_bbar);
  x0_b->Add(x0_bGS);
  x0_c->Add(x0_cbar);
  x0_d->Add(x0_dbar);
  x0_s->Add(x0_sbar);
  x0_u->Add(x0_ubar);

  // ETA
  // CENT BIN 0
  j0_b->Add(j0_bbar);
  j0_b->Add(j0_bGS);
  j0_c->Add(j0_cbar);
  j0_d->Add(j0_dbar);
  j0_s->Add(j0_sbar);
  j0_u->Add(j0_ubar);
	
	
  j1_b->Add(j1_bbar);
  j1_b->Add(j1_bGS);
  j1_c->Add(j1_cbar);
  j1_d->Add(j1_dbar);
  j1_s->Add(j1_sbar);
  j1_u->Add(j1_ubar);
	
  j2_b->Add(j2_bbar);
  j2_b->Add(j2_bGS);
  j2_c->Add(j2_cbar);
  j2_d->Add(j2_dbar);
  j2_s->Add(j2_sbar);
  j2_u->Add(j2_ubar);
	
  j3_b->Add(j3_bbar);
  j3_b->Add(j3_bGS);
  j3_c->Add(j3_cbar);
  j3_d->Add(j3_dbar);
  j3_s->Add(j3_sbar);
  j3_u->Add(j3_ubar);
	
  // CREATE THE COMBINED LIGHT-QUARK HISTOGRAM
	
  // PT
  // CENT BIN 0
  TH1D *h0_l;
  h0_l = (TH1D*) h0_u->Clone("h0_l");
  h0_l->Add(h0_d);
  h0_l->Add(h0_s);
  h0_l->Add(h0_g);
  h0_l->Add(h0_ghost);

  TH1D *x0_l;
  x0_l = (TH1D*) x0_u->Clone("x0_l");
  x0_l->Add(x0_d);
  x0_l->Add(x0_s);
  x0_l->Add(x0_g);
  x0_l->Add(x0_ghost);
	

  // ETA
  // CENT BIN 0
  TH1D *j0_l;
  j0_l = (TH1D*) j0_u->Clone("j0_l");
  j0_l->Add(j0_d);
  j0_l->Add(j0_s);
  j0_l->Add(j0_g);
  j0_l->Add(j0_ghost);
	

  TH1D *j1_l;
  j1_l = (TH1D*) j1_u->Clone("j1_l");
  j1_l->Add(j1_d);
  j1_l->Add(j1_s);
  j1_l->Add(j1_g);
  j1_l->Add(j1_ghost);

	
  TH1D *j2_l;
  j2_l = (TH1D*) j2_u->Clone("j2_l");
  j2_l->Add(j2_d);
  j2_l->Add(j2_s);
  j2_l->Add(j2_g);
  j2_l->Add(j2_ghost);
	
	
  TH1D *j3_l;
  j3_l = (TH1D*) j3_u->Clone("j3_l");
  j3_l->Add(j3_d);
  j3_l->Add(j3_s);
  j3_l->Add(j3_g);
  j3_l->Add(j3_ghost);
	
	
	
	
	
  // REBIN 
  //const int N_jetPtBins = 14;
  //double jetPtAxis[N_jetPtBins] = {50,60,70,80,90,100,120,140,160,200,250,320,400,500};

  const int N_jetPtBins = 6;
  double jetPtAxis[N_jetPtBins] = {80,90,100,120,150,200};

   
    
  const int N_jetEtaBins = 33;
  double jetEtaAxis[N_jetEtaBins] = {-1.6,-1.5,-1.4,-1.3,-1.2,-1.1,-1.0,-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2,-0.1, 0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6};


  // PT
  // CENT BIN 0
  TH1D *h0_inclR = (TH1D*) h0_incl->Rebin(N_jetPtBins-1,"h0_inclR",jetPtAxis);
  TH1D *h0_bR = (TH1D*) h0_b->Rebin(N_jetPtBins-1,"h0_bR",jetPtAxis);
  TH1D *h0_cR = (TH1D*) h0_c->Rebin(N_jetPtBins-1,"h0_cR",jetPtAxis);
  TH1D *h0_lR = (TH1D*) h0_l->Rebin(N_jetPtBins-1,"h0_lR",jetPtAxis);
  TH1D *h0_ghostR = (TH1D*) h0_ghost->Rebin(N_jetPtBins-1,"h0_ghostR",jetPtAxis);
  TH1D *h0_noFlavorR = (TH1D*) h0_noFlavor->Rebin(N_jetPtBins-1,"h0_noFlavorR",jetPtAxis);

  TH1D *x0_inclR = (TH1D*) x0_incl->Rebin(N_jetPtBins-1,"x0_inclR",jetPtAxis);
  TH1D *x0_bR = (TH1D*) x0_b->Rebin(N_jetPtBins-1,"x0_bR",jetPtAxis);
  TH1D *x0_cR = (TH1D*) x0_c->Rebin(N_jetPtBins-1,"x0_cR",jetPtAxis);
  TH1D *x0_lR = (TH1D*) x0_l->Rebin(N_jetPtBins-1,"x0_lR",jetPtAxis);
  TH1D *x0_ghostR = (TH1D*) x0_ghost->Rebin(N_jetPtBins-1,"x0_ghostR",jetPtAxis);
  TH1D *x0_noFlavorR = (TH1D*) x0_noFlavor->Rebin(N_jetPtBins-1,"x0_noFlavorR",jetPtAxis);

  // ETA
  // CENT BIN 0
  TH1D *j0_inclR = (TH1D*) j0_incl->Rebin(N_jetPtBins-1,"j0_inclR",jetPtAxis);
  TH1D *j0_bR = (TH1D*) j0_b->Rebin(N_jetPtBins-1,"j0_bR",jetPtAxis);
  TH1D *j0_cR = (TH1D*) j0_c->Rebin(N_jetPtBins-1,"j0_cR",jetPtAxis);
  TH1D *j0_lR = (TH1D*) j0_l->Rebin(N_jetPtBins-1,"j0_lR",jetPtAxis);
  TH1D *j0_ghostR = (TH1D*) j0_ghost->Rebin(N_jetPtBins-1,"j0_ghostR",jetPtAxis);
  TH1D *j0_noFlavorR = (TH1D*) j0_noFlavor->Rebin(N_jetPtBins-1,"j0_noFlavorR",jetPtAxis);
	
  TH1D *j1_inclR = (TH1D*) j1_incl->Rebin(N_jetPtBins-1,"j1_inclR",jetPtAxis);
  TH1D *j1_bR = (TH1D*) j1_b->Rebin(N_jetPtBins-1,"j1_bR",jetPtAxis);
  TH1D *j1_cR = (TH1D*) j1_c->Rebin(N_jetPtBins-1,"j1_cR",jetPtAxis);
  TH1D *j1_lR = (TH1D*) j1_l->Rebin(N_jetPtBins-1,"j1_lR",jetPtAxis);
  TH1D *j1_ghostR = (TH1D*) j1_ghost->Rebin(N_jetPtBins-1,"j1_ghostR",jetPtAxis);
  TH1D *j1_noFlavorR = (TH1D*) j1_noFlavor->Rebin(N_jetPtBins-1,"j1_noFlavorR",jetPtAxis);
	
	
  TH1D *j2_inclR = (TH1D*) j2_incl->Rebin(N_jetPtBins-1,"j2_inclR",jetPtAxis);
  TH1D *j2_bR = (TH1D*) j2_b->Rebin(N_jetPtBins-1,"j2_bR",jetPtAxis);
  TH1D *j2_cR = (TH1D*) j2_c->Rebin(N_jetPtBins-1,"j2_cR",jetPtAxis);
  TH1D *j2_lR = (TH1D*) j2_l->Rebin(N_jetPtBins-1,"j2_lR",jetPtAxis);
  TH1D *j2_ghostR = (TH1D*) j2_ghost->Rebin(N_jetPtBins-1,"j2_ghostR",jetPtAxis);
  TH1D *j2_noFlavorR = (TH1D*) j2_noFlavor->Rebin(N_jetPtBins-1,"j2_noFlavorR",jetPtAxis);
	
	
  TH1D *j3_inclR = (TH1D*) j3_incl->Rebin(N_jetPtBins-1,"j3_inclR",jetPtAxis);
  TH1D *j3_bR = (TH1D*) j3_b->Rebin(N_jetPtBins-1,"j3_bR",jetPtAxis);
  TH1D *j3_cR = (TH1D*) j3_c->Rebin(N_jetPtBins-1,"j3_cR",jetPtAxis);
  TH1D *j3_lR = (TH1D*) j3_l->Rebin(N_jetPtBins-1,"j3_lR",jetPtAxis);
  TH1D *j3_ghostR = (TH1D*) j3_ghost->Rebin(N_jetPtBins-1,"j3_ghostR",jetPtAxis);
  TH1D *j3_noFlavorR = (TH1D*) j3_noFlavor->Rebin(N_jetPtBins-1,"j3_noFlavorR",jetPtAxis);
	
  TH1D *J1_inclR = (TH1D*) J1_incl->Rebin(N_jetPtBins-1,"J1_inclR",jetPtAxis);
  TH1D *J2_inclR = (TH1D*) J2_incl->Rebin(N_jetPtBins-1,"J2_inclR",jetPtAxis);	
	
	
	
	
  // DIVIDE BY BIN-WIDTH
	
 
  // allJets
  h0_inclR = divideByBinwidth(h0_inclR);
  // bJets  
  h0_bR = divideByBinwidth(h0_bR);
  // cJets
  h0_cR = divideByBinwidth(h0_cR);
  // lJets
  h0_lR = divideByBinwidth(h0_lR);
  // ghostJets
  h0_ghostR = divideByBinwidth(h0_ghostR);
  // noFlavorJets
  h0_noFlavorR = divideByBinwidth(h0_noFlavorR);

  // allJets
  x0_inclR = divideByBinwidth(x0_inclR);
  // bJets  
  x0_bR = divideByBinwidth(x0_bR);
  // cJets
  x0_cR = divideByBinwidth(x0_cR);
  // lJets
  x0_lR = divideByBinwidth(x0_lR);
  // ghostJets
  x0_ghostR = divideByBinwidth(x0_ghostR);
  // noFlavorJets
  x0_noFlavorR = divideByBinwidth(x0_noFlavorR);

  // allJets
  j0_inclR = divideByBinwidth(j0_inclR);
  // bJets  
  j0_bR = divideByBinwidth(j0_bR);
  // cJets
  j0_cR = divideByBinwidth(j0_cR);
  // lJets
  j0_lR = divideByBinwidth(j0_lR);
  // ghostJets
  j0_ghostR = divideByBinwidth(j0_ghostR);
  // noFlavorJets
  j0_noFlavorR = divideByBinwidth(j0_noFlavorR);

  // allJets
  j1_inclR = divideByBinwidth(j1_inclR);
  // bJets  
  j1_bR = divideByBinwidth(j1_bR);
  // cJets
  j1_cR = divideByBinwidth(j1_cR);
  // lJets
  j1_lR = divideByBinwidth(j1_lR);
  // ghostJets
  j1_ghostR = divideByBinwidth(j1_ghostR);
  // noFlavorJets
  j1_noFlavorR = divideByBinwidth(j1_noFlavorR);

  // allJets
  j2_inclR = divideByBinwidth(j2_inclR);
  // bJets  
  j2_bR = divideByBinwidth(j2_bR);
  // cJets
  j2_cR = divideByBinwidth(j2_cR);
  // lJets
  j2_lR = divideByBinwidth(j2_lR);
  // ghostJets
  j2_ghostR = divideByBinwidth(j2_ghostR);
  // noFlavorJets
  j2_noFlavorR = divideByBinwidth(j2_noFlavorR);

  // allJets
  j3_inclR = divideByBinwidth(j3_inclR);
  // bJets  
  j3_bR = divideByBinwidth(j3_bR);
  // cJets
  j3_cR = divideByBinwidth(j3_cR);
  // lJets
  j3_lR = divideByBinwidth(j3_lR);
  // ghostJets
  j3_ghostR = divideByBinwidth(j3_ghostR);
  // noFlavorJets
  j3_noFlavorR = divideByBinwidth(j3_noFlavorR);

  J1_inclR = divideByBinwidth(J1_inclR);
  J2_inclR = divideByBinwidth(J2_inclR);


  // style stuff
  h0_bR->SetLineColor(kRed);
  j0_bR->SetLineColor(kGreen+1);
  j1_bR->SetLineColor(kBlue);
  j2_bR->SetLineColor(kCyan+2);
  j3_bR->SetLineColor(kMagenta);

  h0_bR->SetMarkerColor(kRed);
  j0_bR->SetMarkerColor(kGreen+1);
  j1_bR->SetMarkerColor(kBlue);
  j2_bR->SetMarkerColor(kCyan+2);
  j3_bR->SetMarkerColor(kMagenta);

	
  h0_cR->SetLineColor(kRed);
  j0_cR->SetLineColor(kGreen+1);
  j1_cR->SetLineColor(kBlue);
  j2_cR->SetLineColor(kCyan+2);
  j3_cR->SetLineColor(kMagenta);

  h0_cR->SetMarkerColor(kRed);
  j0_cR->SetMarkerColor(kGreen+1);
  j1_cR->SetMarkerColor(kBlue);
  j2_cR->SetMarkerColor(kCyan+2);
  j3_cR->SetMarkerColor(kMagenta);
	
	
  h0_lR->SetLineColor(kRed);
  j0_lR->SetLineColor(kGreen+1);
  j1_lR->SetLineColor(kBlue);
  j2_lR->SetLineColor(kCyan+2);
  j3_lR->SetLineColor(kMagenta);

  h0_lR->SetMarkerColor(kRed);
  j0_lR->SetMarkerColor(kGreen+1);
  j1_lR->SetMarkerColor(kBlue);
  j2_lR->SetMarkerColor(kCyan+2);
  j3_lR->SetMarkerColor(kMagenta);


	

  double markSize = 1.2;
	
  // PT
  // CENT BIN 0
  h0_bR->SetMarkerSize(markSize);
  j0_bR->SetMarkerSize(markSize);
  j1_bR->SetMarkerSize(markSize);	
  j2_bR->SetMarkerSize(markSize);
  j3_bR->SetMarkerSize(markSize);
	

  // ETA
  // CENT BIN 0
  h0_cR->SetMarkerSize(markSize);
  j0_cR->SetMarkerSize(markSize);
  j1_cR->SetMarkerSize(markSize);	
  j2_cR->SetMarkerSize(markSize);
  j3_cR->SetMarkerSize(markSize);
	

  h0_lR->SetMarkerSize(markSize);
  j0_lR->SetMarkerSize(markSize);
  j1_lR->SetMarkerSize(markSize);	
  j2_lR->SetMarkerSize(markSize);
  j3_lR->SetMarkerSize(markSize);




  int markStyle1 = 24;
  int markStyle2 = 28;
  int markStyle3 = 32;
  int markStyle4 = 46;
  int markStyle5 = 35;

  // PT
  // CENT BIN 0
	
  h0_bR->SetMarkerStyle(markStyle1);
  j0_bR->SetMarkerStyle(markStyle2);
  j1_bR->SetMarkerStyle(markStyle3);
  j2_bR->SetMarkerStyle(markStyle4);
  j3_bR->SetMarkerStyle(markStyle5);
	
	
  // PT
  // CENT BIN 0
  h0_cR->SetMarkerStyle(markStyle1);
  j0_cR->SetMarkerStyle(markStyle2);
  j1_cR->SetMarkerStyle(markStyle3);
  j2_cR->SetMarkerStyle(markStyle4);
  j3_cR->SetMarkerStyle(markStyle5);
	

  h0_lR->SetMarkerStyle(markStyle1);
  j0_lR->SetMarkerStyle(markStyle2);
  j1_lR->SetMarkerStyle(markStyle3);
  j2_lR->SetMarkerStyle(markStyle4);
  j3_lR->SetMarkerStyle(markStyle5);


  TH1D *r0_b = (TH1D*) j0_bR->Clone("r0_b");
  r0_b->Divide(h0_bR,h0_inclR,1,1,"B");

  TH1D *r1_b = (TH1D*) h0_bR->Clone("r1_b");
  r1_b->Divide(j0_bR,h0_bR,1,1,"B");
	
  TH1D *r2_b = (TH1D*) j1_bR->Clone("r2_b");
  r2_b->Divide(j1_bR,h0_bR,1,1,"B");

  // TH1D *r2_b = (TH1D*) j2_bR->Clone("r2_b");
  // r2_b->Divide(j2_bR,h0_bR,1,1,"B");

  TH1D *r3_b = (TH1D*) j2_bR->Clone("r3_b");
  r3_b->Divide(j2_bR,x0_bR,1,1,"B");
	
	
  TH1D *r0_c = (TH1D*) j0_cR->Clone("r0_c");
  r0_c->Divide(j0_cR,h0_cR,1,1,"B");
	
  TH1D *r1_c = (TH1D*) j1_cR->Clone("r1_c");
  r1_c->Divide(j1_cR,h0_cR,1,1,"B");

  TH1D *r2_c = (TH1D*) j2_cR->Clone("r2_c");
  r2_c->Divide(j2_cR,h0_cR,1,1,"B");

  TH1D *r3_c = (TH1D*) j3_cR->Clone("r3_c");
  r3_c->Divide(j3_cR,h0_cR,1,1,"B");
	
	
  TH1D *r0_l = (TH1D*) j0_lR->Clone("r0_l");
  r0_l->Divide(j0_lR,h0_lR,1,1,"B");
	
  TH1D *r1_l = (TH1D*) j1_lR->Clone("r1_l");
  r1_l->Divide(j1_lR,h0_lR,1,1,"B");

  TH1D *r2_l = (TH1D*) j2_lR->Clone("r2_l");
  r2_l->Divide(j2_lR,h0_lR,1,1,"B");

  TH1D *r3_l = (TH1D*) j3_lR->Clone("r3_l");
  r3_l->Divide(j3_lR,h0_lR,1,1,"B");

  TH1D *r_J2 = (TH1D*) J2_inclR->Clone("r_J2");
  r_J2->Divide(J2_inclR,J1_inclR,1,1,"B");
	
  // ETA
  // CENT BIN 0
			
  // LATEX OBJECT
  TLatex *la = new TLatex();
  double laTextSize = 0.1;
  double laTitleSize = 0.05;
  int laTextFont = 42;
  la->SetTextFont(laTextFont);

  // pT spectra
  // canvas
  TCanvas *c1 = new TCanvas("c1","c1",1300,600);
  c1->Divide(4,1);
    	
	
  c1->cd(1);
  // ranges for plots
  double minY = 3e-6;
  double maxY = 3e3;
  // ranges for ratioPlots
  double smallNumber = 0.1;
  double ratioMinY_b = 0.065*(1.-smallNumber);
  double ratioMaxY_b = 0.13*(1.+smallNumber);	
  double ratioMinY_c = 0.02*(1.-smallNumber);
  double ratioMaxY_c = 0.06*(1.+smallNumber);	
  double ratioMinY_l_1 = 0.0e-3*(1.-smallNumber);
  double ratioMaxY_l_1 = 0.4e-3*(1.+smallNumber);	
  double ratioMinY_l_2 = 0.001*(1.-smallNumber);
  double ratioMaxY_l_2 = 0.0055*(1.+smallNumber);	
	
	
	
  la->SetTextSize(laTitleSize);
  double laTitleCoordX_1 = 0.1;
  double laTitleCoordY_1 = 0.8;
  double laTitleCoordY_2 = 0.72;
  double laTitleCoordY_3 = 0.64;
  double laTitleCoordY_4 = 0.56;
  double laTitleCoordY_5 = 0.48;
	
  la->DrawLatexNDC(laTitleCoordX_1,laTitleCoordY_1,"PYTHIA #sqrt{#font[52]{s}} = 5 TeV");
  la->DrawLatexNDC(laTitleCoordX_1,laTitleCoordY_2,"Anti-#font[52]{k}_{T} jets, R = 0.4");
  la->DrawLatexNDC(laTitleCoordX_1,laTitleCoordY_3,"50 < #font[52]{p}_{T}^{jet} < 500 GeV, |#eta^{jet}| < 1.6");
  la->DrawLatexNDC(laTitleCoordX_1,laTitleCoordY_4,"#font[52]{p}_{T}^{#mu} > 7 GeV, |#eta^{#mu}| < 2.0");
	

  //la->DrawLatexNDC(laTitleCoordX_1,laTitleCoordY_5,"#font[52]{p}_{T}^{#mu} > 7 GeV, |#eta^{#mu}| < 2.0");
	
  double legCoordX_1 = 0.08;
  double legCoordX_2 = 0.44;
  double legCoordY_1 = 0.05;
  double legCoordY_2 = 0.4;

  TLegend *leg1 = new TLegend(legCoordX_1,legCoordY_1,legCoordX_2,legCoordY_2);
  leg1->SetBorderSize(0);
  leg1->AddEntry(h0_bR,"recoJets","p");
  //factorization1
  leg1->AddEntry(j0_bR,"recoJets-genMuons","p");
  leg1->AddEntry(j1_bR,"recoJets-recoMuons","p");
  leg1->AddEntry(j2_bR,"recoJets-recoMuons + trigger","p");
  // leg1->AddEntry(j3_bR,"recoJets-matchedRecoMuons + trigger","p");
  //factorization2
  // leg1->AddEntry(j0_bR,"recoJets-genMuons","p");
  // leg1->AddEntry(j1_bR,"recoJets-genMuons + trigger","p");
  // leg1->AddEntry(j2_bR,"recoJets-recoMuons + trigger","p");
  //leg1->AddEntry(j3_bR,"recoJets-matchedRecoMuons + trigger","p");
  leg1->SetTextSize(0.05);
  leg1->Draw();	
	
  /////////////// CENT BIN 0 ///////////////////
	
  c1->cd(2);

  TPad *pad1_0 = new TPad("pad1_0","pad1_0",0,0.5,1,1);
  TPad *pad2_0 = new TPad("pad1_0","pad1_0",0,0,1,0.5);

  // margins
  double lm = 0.2;
  double bm = 0.3;
  double tm = 0.0;
  double yto = 1.6;
  pad1_0->SetLeftMargin(lm);
  pad1_0->SetBottomMargin(0.0);
  pad2_0->SetTopMargin(0.0);
  pad2_0->SetLeftMargin(lm);
  pad2_0->SetBottomMargin(0.7*bm);

  pad1_0->Draw();
  pad1_0->SetLogy();
  pad1_0->cd();
  // label sizes
  double xt = 0.07;
  double xl = 0.05;
  double yt = 0.06;
  double yl = 0.05;
  h0_bR->GetYaxis()->SetRangeUser(minY,maxY);
  r0_b->GetYaxis()->SetTitleOffset(yto);
  h0_bR->GetYaxis()->SetTitleOffset(yto);
  r0_b->GetXaxis()->SetTitleSize(xt);
  r0_b->GetXaxis()->SetLabelSize(xl);
  r0_b->GetYaxis()->SetTitleSize(yt);
  r0_b->GetYaxis()->SetLabelSize(yl);
  h0_bR->GetXaxis()->SetTitleSize(0);
  h0_bR->GetXaxis()->SetLabelSize(0);
  h0_bR->GetYaxis()->SetTitleSize(yt);
  h0_bR->GetYaxis()->SetLabelSize(yl);
  h0_bR->GetYaxis()->SetTitle("d#font[52]{N} / d#font[52]{p}_{T}^{jet} [GeV^{-1}]");
  r0_b->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  r0_b->GetYaxis()->SetTitle("Fraction");
  h0_bR->SetTitle("#font[52]{b} jets");
  r0_b->SetTitle("");
  r0_b->SetStats(0);
  h0_bR->SetStats(0);
  h0_bR->Draw();
  j0_bR->Draw("same");
  j1_bR->Draw("same");
  j2_bR->Draw("same");
  //j3_bR->Draw("same");
	
	
  la->SetTextSize(laTextSize);

  double laCoordX_1 = 0.6;
  double laCoordY_1 = 0.7;
  //la->DrawLatexNDC(laCoordX_1,laCoordY_1,"cent. 0-90%");


  c1->cd(2);
  pad2_0->Draw();
  //pad2_0->SetLogy();
  pad2_0->cd();

  double ratioMinY = 0.00003;
  double ratioMaxY = 0.2;
  //r0_b->GetYaxis()->SetLogy();



  r0_b->GetYaxis()->SetRangeUser(ratioMinY_b,ratioMaxY_b);
  r0_b->Draw();
  r1_b->Draw("same");
  r2_b->Draw("same");
  r3_b->Draw("same");

  /////////////////////////////////////////////////////////////////


	
  /////////////////////////////////////////////////////////////////
  c1->cd(3);


  TPad *pad3_0 = new TPad("pad3_0","pad3_0",0,0.5,1,1);
  TPad *pad4_0 = new TPad("pad4_0","pad4_0",0,0,1,0.5);

  // margins
    
  pad3_0->SetLeftMargin(lm);
  pad3_0->SetBottomMargin(0.0);
  pad4_0->SetTopMargin(0.0);
  pad4_0->SetLeftMargin(lm);
  pad4_0->SetBottomMargin(0.7*bm);

  pad3_0->Draw();
  pad3_0->SetLogy();
  pad3_0->cd();
  // label sizes
  
  r0_c->GetYaxis()->SetTitleOffset(yto);
  h0_cR->GetYaxis()->SetRangeUser(minY,maxY);
  h0_cR->GetYaxis()->SetTitleOffset(yto);
  r0_c->GetXaxis()->SetTitleSize(xt);
  r0_c->GetXaxis()->SetLabelSize(xl);
  r0_c->GetYaxis()->SetTitleSize(yt);
  r0_c->GetYaxis()->SetLabelSize(yl);
  h0_cR->GetXaxis()->SetTitleSize(0);
  h0_cR->GetXaxis()->SetLabelSize(0);
  h0_cR->GetYaxis()->SetTitleSize(yt);
  h0_cR->GetYaxis()->SetLabelSize(yl);
  h0_cR->GetYaxis()->SetTitle("d#font[52]{N} / d#font[52]{p}_{T}^{jet} [GeV^{-1}]");
  r0_c->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  r0_c->GetYaxis()->SetTitle("Fraction");
  h0_cR->SetTitle("#font[52]{c} jets");
  r0_c->SetTitle("");
  r0_c->SetStats(0);
  h0_cR->SetStats(0);
  h0_cR->Draw();
  j0_cR->Draw("same");
  j1_cR->Draw("same");
  j2_cR->Draw("same");
  //j3_cR->Draw("same");
	
	
	
  la->SetTextSize(laTextSize);


  //la->DrawLatexNDC(laCoordX_1,laCoordY_1,"cent. 0-90%");


  c1->cd(3);
  pad4_0->Draw();
  //pad4_0->SetLogy();
  pad4_0->cd();


  r0_c->GetYaxis()->SetRangeUser(ratioMinY_c,ratioMaxY_c);
  r0_c->Draw();
  r1_c->Draw("same");
  r2_c->Draw("same");
  //r3_c->Draw("same");


  /////////////////////////////////////////////////////////////////


	
  c1->cd(4);


  TPad *pad5_0 = new TPad("pad5_0","pad5_0",0,0.5,1,1);
  TPad *pad6_0 = new TPad("pad6_0","pad6_0",0,0,1,0.3);
  TPad *pad6_1 = new TPad("pad6_1","pad6_1",0,0.3,1,0.5);
  // margins
    
  pad5_0->SetLeftMargin(lm);
  pad5_0->SetBottomMargin(0.0);
  pad6_1->SetBottomMargin(0.0);
  pad6_1->SetTopMargin(0.0);
  pad6_0->SetTopMargin(0.0);
  pad6_0->SetLeftMargin(lm);
  pad6_1->SetLeftMargin(lm);
  pad6_0->SetBottomMargin(bm);

  pad5_0->Draw();
  pad5_0->SetLogy();
  pad5_0->cd();
  // label sizes
  h0_lR->GetYaxis()->SetRangeUser(minY,maxY);	
  r0_l->GetYaxis()->SetTitleOffset(0.7*yto);
  h0_lR->GetYaxis()->SetTitleOffset(yto);
  r0_l->GetXaxis()->SetTitleSize(1.5*xt);
  r0_l->GetXaxis()->SetLabelSize(1.5*xl);
  r0_l->GetYaxis()->SetTitleSize(1.5*yt);
  r0_l->GetYaxis()->SetLabelSize(1.5*yl);

  r2_l->GetXaxis()->SetTitleSize(0.0);
  r2_l->GetXaxis()->SetLabelSize(0.0);
  r2_l->GetYaxis()->SetTitleSize(2.2*yt);
  r2_l->GetYaxis()->SetLabelSize(2.2*yl);



  h0_lR->GetXaxis()->SetTitleSize(0);
  h0_lR->GetXaxis()->SetLabelSize(0);
  h0_lR->GetYaxis()->SetTitleSize(yt);
  h0_lR->GetYaxis()->SetLabelSize(yl);
  h0_lR->GetYaxis()->SetTitle("d#font[52]{N} / d#font[52]{p}_{T}^{jet} [GeV^{-1}]");
  r0_l->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  r0_l->GetYaxis()->SetTitle("Fraction #times 10^{3}");
  r2_l->GetYaxis()->SetTitle("Fraction");
  h0_lR->SetTitle("#font[52]{udsg} jets");
  r0_l->SetTitle("");
  r2_l->SetTitle("");
  r0_l->SetStats(0);
  r2_l->SetStats(0);
  h0_lR->SetStats(0);
  h0_lR->Draw();
  j0_lR->Draw("same");
  j1_lR->Draw("same");
  j2_lR->Draw("same");
  //j3_lR->Draw("same");
	
	
  la->SetTextSize(laTextSize);


  //la->DrawLatexNDC(laCoordX_1,laCoordY_1,"cent. 0-90%");


  c1->cd(4);
  pad6_0->Draw();
  //pad6_0->SetLogy();
  pad6_0->cd();

  double amp = 1.0;
  double udsgScaleDownFactor = 1./amp;
  for(int j = 0; j < r0_l->GetSize(); j++){

    r0_l->SetBinContent(j,udsgScaleDownFactor*r0_l->GetBinContent(j));
    r0_l->SetBinError(j,udsgScaleDownFactor*r0_l->GetBinError(j));
    cout << "j = " << j << ", r0_l[j] = " << r0_l->GetBinContent(j) << endl;

  }
  //r0_l->Scale(udsgScaleDownFactor);
  //r0_l->GetYaxis()->SetRangeUser(0,42);
  r0_l->GetYaxis()->SetRangeUser(ratioMinY_l_1,ratioMaxY_l_1);
  r0_l->Draw();
	

	
  laTextSize=0.05;
  la->SetTextSize(laTextSize);
  la->SetTextColor(kGreen+2);
  //la->DrawLatexNDC(0.6,0.4,Form("Divided by %2.0f",amp));


  c1->cd(4);
  pad6_1->Draw();
  pad6_1->cd();
  r2_l->GetYaxis()->SetRangeUser(ratioMinY_l_2,ratioMaxY_l_2);
  r2_l->Draw();
  r1_l->Draw("same");
	
	
	
	
	

	
  TH1D *corrFactor_1, *corrFactor_2, *corrFactor_3, *corrFactor_3_data, *corrFactor_4;
	
  corrFactor_1 = (TH1D*) r0_b->Clone("corrFactor_1");
	
  corrFactor_2 = (TH1D*) r1_b->Clone("corrFactor_2");
  //corrFactor_2->Divide(r1_b,r0_b,1,1,"B");
	
  corrFactor_3 = (TH1D*) r2_b->Clone("corrFactor_3");
  //corrFactor_3->Divide(r2_b,r1_b,1,1,"B");

  corrFactor_3_data = (TH1D*) r_J2->Clone("corrFactor_3_data");

  corrFactor_4 = (TH1D*) r3_b->Clone("corrFactor_4");
	
  corrFactor_1->SetTitle("bJet Correction Factor 1");



  double tSize = 0.05;
  double lSize = 0.038;	
	
	
	
  TCanvas *canv_bJetCorr_1 = new TCanvas("canv_bJetCorr_1","bJet correction factor 1",700,700);
  canv_bJetCorr_1->cd();
  TPad *pad1_bJetCorr_1 = new TPad("pad1_bJetCorr_1","pad1_bJetCorr_1",0,0,1,1);
  pad1_bJetCorr_1->SetLeftMargin(0.2);
  pad1_bJetCorr_1->SetBottomMargin(0.2);
  pad1_bJetCorr_1->Draw();
  pad1_bJetCorr_1->cd();
  corrFactor_1->GetXaxis()->SetTitleSize(tSize);
  corrFactor_1->GetYaxis()->SetTitleSize(tSize);
  corrFactor_1->GetXaxis()->SetLabelSize(lSize);
  corrFactor_1->GetYaxis()->SetLabelSize(lSize);
  corrFactor_1->GetYaxis()->SetRangeUser(0,0.2);
  corrFactor_1->GetYaxis()->SetTitle("Correction");
  corrFactor_1->Draw();
	
	
  TCanvas *canv_bJetCorr_2 = new TCanvas("canv_bJetCorr_2","bJet correction factor 2",700,700);
  canv_bJetCorr_2->cd();
  TPad *pad1_bJetCorr_2 = new TPad("pad1_bJetCorr_2","pad1_bJetCorr_2",0,0,1,1);
  pad1_bJetCorr_2->SetLeftMargin(0.2);
  pad1_bJetCorr_2->SetBottomMargin(0.2);
  pad1_bJetCorr_2->Draw();
  pad1_bJetCorr_2->cd();
  corrFactor_2->GetXaxis()->SetTitleSize(tSize);
  corrFactor_2->GetYaxis()->SetTitleSize(tSize);
  corrFactor_2->GetXaxis()->SetLabelSize(lSize);
  corrFactor_2->GetYaxis()->SetLabelSize(lSize);
  corrFactor_2->SetStats(0);
  corrFactor_2->GetYaxis()->SetTitle("Correction");
  corrFactor_2->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  corrFactor_2->SetTitle("bJet Correction Factor 2");
  //corrFactor_2->GetYaxis()->SetRangeUser(0.95,1);
  corrFactor_2->GetYaxis()->SetRangeUser(0.0,0.2);
  corrFactor_2->Draw();
	
  TCanvas *canv_bJetCorr_3 = new TCanvas("canv_bJetCorr_3","bJet correction factor 3",700,700);
  canv_bJetCorr_3->cd();
  TPad *pad1_bJetCorr_3 = new TPad("pad1_bJetCorr_3","pad1_bJetCorr_3",0,0,1,1);
  pad1_bJetCorr_3->SetLeftMargin(0.2);
  pad1_bJetCorr_3->SetBottomMargin(0.2);
  pad1_bJetCorr_3->Draw();
  pad1_bJetCorr_3->cd();
  corrFactor_3->GetXaxis()->SetTitleSize(tSize);
  corrFactor_3->GetYaxis()->SetTitleSize(tSize);
  corrFactor_3->GetXaxis()->SetLabelSize(lSize);
  corrFactor_3->GetYaxis()->SetLabelSize(lSize);
  corrFactor_3->SetStats(0);
  corrFactor_3->GetYaxis()->SetTitle("Correction");
  corrFactor_3->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  corrFactor_3->SetTitle("bJet Correction Factor 3");
  corrFactor_3->GetYaxis()->SetRangeUser(0.90,1);
  corrFactor_3->Draw();
	

  TString output_filePath = "";
  TString corrFactor_1_name = "";
  TString corrFactor_2_name = "";
  TString corrFactor_3_name = "";
  TString corrFactor_3_data_name = "";
  TString corrFactor_4_name = "";

  if(ispp){
    output_filePath = "../../rootFiles/spectraFractions/correctionFactors_pp.root";
    corrFactor_1_name = "corrFactor_1_pp";
    corrFactor_2_name = "corrFactor_2_pp";
    corrFactor_3_name = "corrFactor_3_pp";
    corrFactor_3_data_name = "corrFactor_3_data_pp";
    corrFactor_4_name = "corrFactor_4_pp";
  }
  else if(isC3){
    output_filePath = "../../rootFiles/spectraFractions/correctionFactors_C3.root";
    corrFactor_1_name = "corrFactor_1_C3";
    corrFactor_2_name = "corrFactor_2_C3";
    corrFactor_3_name = "corrFactor_3_C3";
    corrFactor_3_data_name = "corrFactor_3_data_C3";
    corrFactor_4_name = "corrFactor_4_C3";
  }
  else if(isC2){
    output_filePath = "../../rootFiles/spectraFractions/correctionFactors_C2.root";
    corrFactor_1_name = "corrFactor_1_C2";
    corrFactor_2_name = "corrFactor_2_C2";
    corrFactor_3_name = "corrFactor_3_C2";
    corrFactor_3_data_name = "corrFactor_3_data_C2";
    corrFactor_4_name = "corrFactor_4_C2";
  }
  else if(isC1){
    output_filePath = "../../rootFiles/spectraFractions/correctionFactors_C1.root";
    corrFactor_1_name = "corrFactor_1_C1";
    corrFactor_2_name = "corrFactor_2_C1";
    corrFactor_3_name = "corrFactor_3_C1";
    corrFactor_3_data_name = "corrFactor_3_data_C1";
    corrFactor_4_name = "corrFactor_4_C1";
  }


  
  auto wf = TFile::Open(output_filePath,"recreate");

  corrFactor_1->Write(corrFactor_1_name);
  corrFactor_2->Write(corrFactor_2_name);
  corrFactor_3->Write(corrFactor_3_name);
  corrFactor_3_data->Write(corrFactor_3_data_name);
  corrFactor_4->Write(corrFactor_4_name);  

  wf->Close();	
	

  

}
