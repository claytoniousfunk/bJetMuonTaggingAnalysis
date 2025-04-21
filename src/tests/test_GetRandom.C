
void test_GetRandom(){

  TFile *f = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/neutrino_energy_fraction_map.root");

  TH2D *H;
  TH1D *h;
  TH1D *h_GetRandom = new TH1D("h_GetRandom","h_GetRandom",100,0,1);

  f->GetObject("neutrino_energy_fraction_map",H);

  double jetPt = 60.0;

  h = (TH1D*) H->ProjectionX("h",H->GetYaxis()->FindBin(jetPt),H->GetYaxis()->FindBin(jetPt)+1);

  int N_fill = 10000;

  for(int i = 0; i < N_fill; i++){
    h_GetRandom->Fill(h->GetRandom());
  }


  h->Scale(1./h->Integral());
  h_GetRandom->Scale(1./h_GetRandom->Integral());
  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.2);
  pad->SetBottomMargin(0.2);
  pad->SetLogy();
  pad->Draw();
  pad->cd();
  h->SetLineColor(kBlue-4);
  h->SetLineWidth(2);
  h_GetRandom->SetLineColor(kRed-4);
  h_GetRandom->SetLineWidth(2);
  h->Draw();
  h_GetRandom->Draw("same");
}
