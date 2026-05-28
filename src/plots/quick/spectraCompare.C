


void stylizeHistograms(TH1D *h1, TH1D *h2){

  double lineWidth = 2.0;
  h1->SetLineWidth(lineWidth);
  h2->SetLineWidth(lineWidth);
  
  h1->SetLineColor(kRed-4);
  h2->SetLineColor(kBlue-4);

}

double integrate(TH1D *h, double lowerBound, double upperBound){

  double result = 0.0;
  double smallShift = 0.01;
  
  int a = h->FindBin(lowerBound+smallShift);
  int b = h->FindBin(upperBound-smallShift);

  for(int i = a; i <= b; i++){
    result += h->GetBinContent(i);
  }

  return result;

}

void spectraCompare(){

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_2026-3-25.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-25.root");

  TH2D *H1, *H2;
  TH2D *N1, *N2; // get event number
  TH1D *h1, *h2;

  // f1->GetObject("h_vz_jet",h1);
  // f1->GetObject("h_vz_inclRecoMuonTag",h2);

  f1->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H1);
  f1->GetObject("h_leadingRecoJetPtOverPThat_pThat_C2",N1);

  f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H2);
  f2->GetObject("h_leadingRecoJetPtOverPThat_pThat_C2",N2);

  

  std::cout << "H1 entries = " << H1->GetEntries() << "\n";
  std::cout << "H2 entries = " << H2->GetEntries() << "\n";

  std::cout << "N1 entries = " << N1->GetEntries() << "\n";
  std::cout << "N2 entries = " << N2->GetEntries() << "\n";

  h1 = (TH1D*) H1->ProjectionX("h1");
  h2 = (TH1D*) H2->ProjectionX("h2");


  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  //pad->SetLogy();
  pad->Draw();
  pad->cd();
  h1->SetTitle("");
  h1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h1->GetYaxis()->SetTitle("Entries");
  h1->SetLineColor(kRed-4);
  h2->SetLineColor(kBlue-4);
  h1->SetMarkerColor(kRed-4);
  h2->SetMarkerColor(kBlue-4);
  h1->SetMarkerStyle(20);
  h2->SetMarkerStyle(25);
  h1->Draw();
  h2->Draw("same");
  
  TH1D *r = (TH1D*) h2->Clone("r");
  r->Divide(h2,h1,1,1,"B");
  r->SetTitle("");
  r->GetYaxis()->SetTitle("With-weight-cut / no-weight-cut");
  r->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r->SetStats(0);
  r->Draw();


}
