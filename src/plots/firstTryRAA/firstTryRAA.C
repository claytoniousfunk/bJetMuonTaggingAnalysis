


void firstTryRAA(){

  TFile *f_PbPb = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/final/PbPb_HardProbes_scan_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates.root");
  TFile *f_pp = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/platinum/pp_MinBias_mu12_tight_pTmu-14_evtFilterFix_newJetBins.root");

  TH1D *h_C1, *h_pp;
  TH1D *h_vz_pp, *h_hiBin;

  f_pp->GetObject("h_inclRecoJetPt",h_pp);
  f_pp->GetObject("h_vz",h_vz_pp);
  f_PbPb->GetObject("h_inclRecoJetPt_C1",h_C1);
  f_PbPb->GetObject("h_hiBin",h_hiBin);

  // count events from hiBin distribution
  double hiBin_lowerBound = 0.0;
  double hiBin_upperBound = 20.0;
  double smallShift = 0.01;
  int lowBin_hiBin = h_hiBin->FindBin(hiBin_lowerBound+smallShift);
  int highBin_hiBin = h_hiBin->FindBin(hiBin_upperBound-smallShift);

  double vz_lowerBound = -15.0;
  double vz_upperBound = 15.0;
  int lowBin_vz = h_vz_pp->FindBin(vz_lowerBound+smallShift);
  int highBin_vz = h_vz_pp->FindBin(vz_upperBound-smallShift);

  double S_C1 = 0.0;
  double S_pp = 0.0;

  for(int i = lowBin_vz; i <= highBin_vz; i++){
    S_pp += h_vz_pp->GetBinContent(i);
  }
  
  for(int i = lowBin_hiBin; i <= highBin_hiBin; i++){
    S_C1 += h_hiBin->GetBinContent(i);
  }

  
  double N_C1 = S_C1;
  double N_pp = S_pp;

  cout << "N_pp = " << N_pp << endl;
  cout << "N_C1 = " << N_C1 << endl;

  h_pp->Scale(1./N_pp);
  h_C1->Scale(1./N_C1/1630.);

  TH1D *r = (TH1D*) h_C1->Clone("r");
  r->Divide(h_C1,h_pp,1,1,"");

  r->Draw();

  // h_pp->Draw();
  // h_C1->Draw("same");
  
}
