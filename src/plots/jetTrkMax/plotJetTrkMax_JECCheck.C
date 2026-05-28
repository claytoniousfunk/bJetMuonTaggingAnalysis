

void plotJetTrkMax_JECCheck(){

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/jetTrkMax/pp_jetTrkMax_trkPt-14_jet60_2025-07-22.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/jetTrkMax/pp_jetTrkMax_trkPt-14_jet60_updatedJEC_2025-11-24.root");

  TH1D *h1, *h2;

  f1->GetObject("h_jetTrkMaxPtRel_J2",h1);
  f2->GetObject("h_jetTrkMaxPtRel_J2",h2);

  // f1->GetObject("h_jetTrkMaxDR_J4",h1);
  // f2->GetObject("h_jetTrkMaxDR_J4",h2);

  

  h1->SetLineColor(kRed-4);
  h1->SetMarkerColor(kRed-4);
  h1->SetMarkerStyle(20);

  h2->SetLineColor(kBlue-4);
  h2->SetMarkerColor(kBlue-4);
  h2->SetMarkerStyle(20);

  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0,1,1);
  p1->SetLeftMargin(0.15);
  p1->SetBottomMargin(0.15);
  p1->Draw();
  p1->cd();
  h1->SetTitle("");
  h1->SetStats(0);
  h1->GetYaxis()->SetTitle("Entries");
  //h1->GetXaxis()->SetTitle("leading-hadron #it{#Delta r}");
  //h1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h1->GetXaxis()->SetTitle("leading-hadron #it{p}_{T}^{rel} [GeV]");
  h1->Draw();
  h2->Draw("same");
  



}
