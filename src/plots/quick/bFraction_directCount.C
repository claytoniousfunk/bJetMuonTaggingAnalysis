#include "../../../headers/fitParameters/JESbFitParams_PYTHIA_mu12.h"
TF1 *fitFxn_PYTHIA_JESb;
#include "../../../headers/fitFunctions/fitFxn_PYTHIA_JESb.h"

void bFraction_directCount(double pT_edge_low = 110., double pT_edge_high = 120.){

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight.root");

  //TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_bJetEnergyShift_muTaggedBOverInclusiveJESCorrection.root");
  //TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_bJetNeutrinoEnergyShift_directEnergyAddition.root");
  //TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_doInclNeutrinoEnergySubtraction.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_doBJetNeutrinoEnergyShift_useNeutrinoTagFractionMap.root");
  //TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_bJetEnergyShift_newFitMethod.root");

  TH2D *H1, *H2, *H3;
  TH2D *M1, *M2, *M3;
  TH1D *mh1, *mh2, *mh3; // muon-tagged all jets
  TH1D *mb1, *mb2, *mb3; // muon-tagged b jets
  TH1D *mbb1, *mbb2, *mbb3; // muon-tagged bb jets
  TH1D *mbGS1, *mbGS2, *mbGS3; // muon-tagged bGS jets
  TH1D *h1, *h2, *h3; // inclusive all jets
  TH1D *b1, *b2, *b3; // inclusive b jets
  TH1D *bb1, *bb2, *bb3; // inclusive bb jets
  TH1D *bGS1, *bGS2, *bGS3; // inclusive bGS jets
  
  f1->GetObject("h_inclGenJetPt_flavor",H1);
  f1->GetObject("h_inclRecoJetPt_flavor",H2);
  f2->GetObject("h_inclRecoJetPt_flavor",H3);
  f1->GetObject("h_inclGenJetPt_inclRecoMuonTag_flavor",M1);
  f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor",M2);
  f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor",M3);



  TH1D *bf = (TH1D*) H1->ProjectionY();

  h1 = (TH1D*) H1->ProjectionX("h1");
  b1 = (TH1D*) H1->ProjectionX("b1",bf->FindBin(5.1),bf->FindBin(5.9));
  bb1 = (TH1D*) H1->ProjectionX("bb1",bf->FindBin(-4.9),bf->FindBin(-4.1));
  bGS1 = (TH1D*) H1->ProjectionX("bGS1",bf->FindBin(17.1),bf->FindBin(17.9));
  b1->Add(bb1);
  b1->Add(bGS1);


  h2 = (TH1D*) H2->ProjectionX("h2");
  b2 = (TH1D*) H2->ProjectionX("b2",bf->FindBin(5.1),bf->FindBin(5.9));
  bb2 = (TH1D*) H2->ProjectionX("bb2",bf->FindBin(-4.9),bf->FindBin(-4.1));
  bGS2 = (TH1D*) H2->ProjectionX("bGS2",bf->FindBin(17.1),bf->FindBin(17.9));
  b2->Add(bb2);
  b2->Add(bGS2);

  h3 = (TH1D*) H3->ProjectionX("h3");
  b3 = (TH1D*) H3->ProjectionX("b3",bf->FindBin(5.1),bf->FindBin(5.9));
  bb3 = (TH1D*) H3->ProjectionX("bb3",bf->FindBin(-4.9),bf->FindBin(-4.1));
  bGS3 = (TH1D*) H3->ProjectionX("bGS3",bf->FindBin(17.1),bf->FindBin(17.9));
  b3->Add(bb3);
  b3->Add(bGS3);

  mh1 = M1->ProjectionX("mh1");
  mb1 = (TH1D*) M1->ProjectionX("mb1",bf->FindBin(5.1),bf->FindBin(5.9));
  mbb1 = (TH1D*) M1->ProjectionX("mbb1",bf->FindBin(-4.9),bf->FindBin(-4.1));
  mbGS1 = (TH1D*) M1->ProjectionX("mbGS1",bf->FindBin(17.1),bf->FindBin(17.9));
  mb1->Add(mbb1);
  mb1->Add(mbGS1);


  
  mh2 = M2->ProjectionX("mh2");
  mb2 = (TH1D*) M2->ProjectionX("mb2",bf->FindBin(5.1),bf->FindBin(5.9));
  mbb2 = (TH1D*) M2->ProjectionX("mbb2",bf->FindBin(-4.9),bf->FindBin(-4.1));
  mbGS2 = (TH1D*) M2->ProjectionX("mbGS2",bf->FindBin(17.1),bf->FindBin(17.9));
  mb2->Add(mbb2);
  mb2->Add(mbGS2);

  mh3 = M3->ProjectionX("mh3");
  mb3 = (TH1D*) M3->ProjectionX("mb3",bf->FindBin(5.1),bf->FindBin(5.9));
  mbb3 = (TH1D*) M3->ProjectionX("mbb3",bf->FindBin(-4.9),bf->FindBin(-4.1));
  mbGS3 = (TH1D*) M3->ProjectionX("mbGS3",bf->FindBin(17.1),bf->FindBin(17.9));
  mb3->Add(mbb3);
  mb3->Add(mbGS3);
  
  mb1->Draw();
  
  // 1: incl gen
  double N_incl_1 = h1->Integral(h1->FindBin(pT_edge_low),h1->FindBin(pT_edge_high));
  double N_b_1 = b1->Integral(b1->FindBin(pT_edge_low),b1->FindBin(pT_edge_high));
  double rb_1 = N_b_1 / N_incl_1;

  // 2: incl-reco
  double N_incl_2 = h2->Integral(h2->FindBin(pT_edge_low),h2->FindBin(pT_edge_high));
  double N_b_2 = b2->Integral(b2->FindBin(pT_edge_low),b2->FindBin(pT_edge_high));
  double rb_2 = N_b_2 / N_incl_2;
  

  // 3: incl-reco, nuPt shift
  double N_incl_3 = h3->Integral(h3->FindBin(pT_edge_low),h3->FindBin(pT_edge_high));
  double N_b_3 = b3->Integral(b3->FindBin(pT_edge_low),b3->FindBin(pT_edge_high));
  double rb_3 = N_b_3 / N_incl_3;


  double N_bmuTagged_1 = mb1->Integral(mb1->FindBin(pT_edge_low),mb1->FindBin(pT_edge_high));
  double N_bmuTagged_2 = mb2->Integral(mb2->FindBin(pT_edge_low),mb2->FindBin(pT_edge_high));
  double N_bmuTagged_3 = mb3->Integral(mb3->FindBin(pT_edge_low),mb3->FindBin(pT_edge_high));
  double JES_yield_correction = N_bmuTagged_3 / N_bmuTagged_2;
  //double JES_yield_correction = 1./(N_incl_3 / N_incl_2);

  cout << endl;
  cout << " :::::::  Direct Counts - " << pT_edge_low << " < pT,jet < " <<  pT_edge_high << "  :::::::  " << endl; 
  cout << endl;
  cout << " N(incl-jet,gen,no-shift) = " << N_incl_1 << endl;
  cout << " N(incl-jet,reco,no-shift) = " << N_incl_2 << endl;
  cout << " N(incl-jet,reco,nuPt-shift) = " << N_incl_3 << endl;
  cout << " ------------------- " << endl;
  cout << " N(mu-tagged-b-jet,gen,no-shift) = " << N_bmuTagged_1 << endl;
  cout << " N(mu-tagged-b-jet,reco,no-shift) = " << N_bmuTagged_2 << endl;
  cout << " N(mu-tagged-b-jet,reco,nuPt-shift) = " << N_bmuTagged_3 << endl;

  
  cout << endl;
  cout << " Gen pT ratio = " << rb_1 << endl;
  cout << " Reco pT ratio = " << rb_2 << endl;
  cout << " JES yield correction = " << JES_yield_correction << endl;
  cout << " Corrected Reco pT ratio = " << rb_2 << " * " << JES_yield_correction << " = " << rb_2 * JES_yield_correction << endl;
  cout << " Corrected / Gen = " << rb_2* JES_yield_correction / rb_1 << endl;

  
  
  
  // loadFitFxn_PYTHIA_JESb();
  // double JES_correction = 0.5*(fitFxn_PYTHIA_JESb->Eval(pT_edge_low) + fitFxn_PYTHIA_JESb->Eval(pT_edge_high));

  // 
    

  
}
