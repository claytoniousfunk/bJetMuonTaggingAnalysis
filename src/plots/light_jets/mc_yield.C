


#include "../../../headers/goldenFileNames.h"

void mc_yield(){

  //TFile *f1 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat50_newJetBins);
  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/dripping-tap/PH_DiJet_batch1_scan_mu12_tight_pTmu-14_pThat-50_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_newJetBins.root");

  TH2D *H0;
  TH2D *J1, *J2, *J3;

  f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C0",H0);
  f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C0J1",J1);
  f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C0J2",J2);
  f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C0J3",J3);

  cout << "Entries[80 < pTjet(GeV) < 120] = " << J1->GetEntries() + J2->GetEntries() + J3->GetEntries() << endl;

  TH1D *h0, *h0_add, *h0_add2;
  TH1D *j1, *j1_add, *j1_add2;
  TH1D *j2, *j2_add, *j2_add2;
  TH1D *j3, *j3_add, *j3_add2;

  h0 = (TH1D*) H0->ProjectionX("h0",H0->ProjectionY()->FindBin(-2.9),H0->ProjectionY()->FindBin(-0.1));
  h0_add = (TH1D*) H0->ProjectionX("h0_add",H0->ProjectionY()->FindBin(1.1),H0->ProjectionY()->FindBin(3.9));
  h0_add2 = (TH1D*) H0->ProjectionX("h0_add2",H0->ProjectionY()->FindBin(21.1),H0->ProjectionY()->FindBin(21.9));

  h0->Add(h0_add);
  h0->Add(h0_add2);

  j1 = (TH1D*) J1->ProjectionX("j1",J1->ProjectionY()->FindBin(-2.9),J1->ProjectionY()->FindBin(-0.1));
  j1_add = (TH1D*) J1->ProjectionX("j1_add",J1->ProjectionY()->FindBin(1.1),J1->ProjectionY()->FindBin(3.9));
  j1_add2 = (TH1D*) J1->ProjectionX("j1_add2",J1->ProjectionY()->FindBin(21.1),J1->ProjectionY()->FindBin(21.9));

  j1->Add(j1_add);
  j1->Add(j1_add2);

  j2 = (TH1D*) J2->ProjectionX("j2",J2->ProjectionY()->FindBin(-2.9),J2->ProjectionY()->FindBin(-0.1));
  j2_add = (TH1D*) J2->ProjectionX("j2_add",J2->ProjectionY()->FindBin(1.1),J2->ProjectionY()->FindBin(3.9));
  j2_add2 = (TH1D*) J2->ProjectionX("j2_add2",J2->ProjectionY()->FindBin(21.1),J2->ProjectionY()->FindBin(21.9));

  j2->Add(j2_add);
  j2->Add(j2_add2);

  j3 = (TH1D*) J3->ProjectionX("j3",J3->ProjectionY()->FindBin(-2.9),J3->ProjectionY()->FindBin(-0.1));
  j3_add = (TH1D*) J3->ProjectionX("j3_add",J3->ProjectionY()->FindBin(1.1),J3->ProjectionY()->FindBin(3.9));
  j3_add2 = (TH1D*) J3->ProjectionX("j3_add2",J3->ProjectionY()->FindBin(21.1),J3->ProjectionY()->FindBin(21.9));

  j3->Add(j3_add);
  j3->Add(j3_add2);

  

  j1->Add(j2);
  j1->Add(j3);
  

  //h0->Draw();

  double int_lower_bound = 80.0;
  double int_upper_bound = 120.0;
  double small_shift = 0.01;

  int lower_bin = h0->FindBin(int_lower_bound + small_shift);
  int upper_bin = h0->FindBin(int_upper_bound - small_shift);

  cout << "lower bin = " << lower_bin << endl;
  cout << "upper bin = " << upper_bin << endl;

  double N_int = h0->Integral(lower_bin,upper_bin,"width");

  cout << "N_int [80 < pT(GeV) < 120] = " << N_int << endl;

  double N_count = j1->Integral();

  cout << "N_count [80 < pT(GeV) < 120] = " << N_count << endl;


}
