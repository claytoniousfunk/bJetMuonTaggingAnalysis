void purity_diff(){

  TFile *f1, *f2;

  f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/MC/bPurityResults.root");
  f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/DATA/bPurityResults.root");

  TH1D *m1, *m2, *m3; // MC histograms
  TH1D *d1, *d2, *d3; // DATA histograms

  f1->GetObject("bFracResults_C1",m1);
  f1->GetObject("bFracResults_C2",m2);
  f1->GetObject("bFracResults_pp",m3);

  f2->GetObject("bFracResults_C1",d1);
  f2->GetObject("bFracResults_C2",d2);
  f2->GetObject("bFracResults_pp",d3);

  TH1D *s1, *s2, *s3; // difference histograms, "s" for sum.

  s1 = (TH1D*) d1->Clone("s1"); // clone data
  s2 = (TH1D*) d2->Clone("s2"); // clone data
  s3 = (TH1D*) d3->Clone("s3"); // clone data
  
  s1->Add(m1,-1); // subtract MC
  s2->Add(m2,-1); // subtract MC
  s3->Add(m3,-1); // subtract MC

  s1->SetMarkerColor(kBlue-4);
  s1->SetLineColor(kBlue-4);
  s1->SetLineWidth(2);

  s2->SetMarkerColor(kRed-4);
  s2->SetLineColor(kRed-4);
  s2->SetLineWidth(2);

  s3->SetMarkerColor(kBlack);
  s3->SetLineColor(kBlack);
  s3->SetLineWidth(2);

  TCanvas *canv = new TCanvas("canv","canvas",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.2);
  pad->SetBottomMargin(0.2);
  pad->Draw();
  pad->cd();
  s1->GetXaxis()->SetTitle("Reco jet p_{T} [GeV]");
  s1->GetYaxis()->SetTitle("b(DATA) - b(MC)");
  s1->SetTitle("");
  s1->GetYaxis()->SetRangeUser(0,0.6);
  s1->SetStats(0);
  
  s1->Draw();
  s2->Draw("same");
  s3->Draw("same");

  TLatex *la = new TLatex();
  la->SetTextFont(62);
  la->SetTextSize(0.045);
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.65,0.75,"pp");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.7,"PbPb 30-90%");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.65,"PbPb 0-30%");



}
