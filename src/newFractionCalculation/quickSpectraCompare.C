

void quickSpectraCompare(){

  //TFile *f1 = TFile::Open("./rootFiles/MinBiasJetSpectra/Data/histograms_MinBiasJetSpectra.root");
  //TFile *f2 = TFile::Open("./rootFiles/MinBiasJetSpectra/MC/histograms_MinBiasJetSpectra.root");
  TFile *f1 = TFile::Open("./rootFiles/CorrectedBJetSpectra/Data/histograms_CorrectedBJetSpectra.root");
  //TFile *f1 = TFile::Open("./rootFiles/MuTagMuTrigJetSpectra/Data/histograms_MuTagMuTrigJetSpectra.root");


  TH1D *h_pp, *h_C4, *h_C3, *h_C2, *h_C1;
  TH1D *r_C4, *r_C3, *r_C2, *r_C1;

  f1->GetObject("h_jetPt_pp",h_pp);
  f1->GetObject("h_jetPt_C4",h_C4);
  f1->GetObject("h_jetPt_C3",h_C3);
  f1->GetObject("h_jetPt_C2",h_C2);
  f1->GetObject("h_jetPt_C1",h_C1);

  // f1->GetObject("h_bJetPt_muTag_muTrig_pp",h_pp);
  // f1->GetObject("h_bJetPt_muTag_muTrig_C4",h_C4);
  // f1->GetObject("h_bJetPt_muTag_muTrig_C3",h_C3);
  // f1->GetObject("h_bJetPt_muTag_muTrig_C2",h_C2);
  // f1->GetObject("h_bJetPt_muTag_muTrig_C1",h_C1);

  // f1->GetObject("h_jetPt_muTag_muTrig_pp",h_pp);
  // f1->GetObject("h_jetPt_muTag_muTrig_C4",h_C4);
  // f1->GetObject("h_jetPt_muTag_muTrig_C3",h_C3);
  // f1->GetObject("h_jetPt_muTag_muTrig_C2",h_C2);
  // f1->GetObject("h_jetPt_muTag_muTrig_C1",h_C1);

  h_pp->SetLineColor(kBlack-4);
  h_pp->SetMarkerColor(kBlack-4);
  h_pp->SetMarkerStyle(24);

  h_C4->SetLineColor(kBlue+1);
  h_C4->SetMarkerColor(kBlue+1);
  h_C4->SetMarkerStyle(33);
  h_C4->Scale(1./30.76);

  h_C3->SetLineColor(kRed-4);
  h_C3->SetMarkerColor(kRed-4);
  h_C3->SetMarkerStyle(21);
  h_C3->Scale(1./267.);

  h_C2->SetLineColor(kGreen+2);
  h_C2->SetMarkerColor(kGreen+2);
  h_C2->SetMarkerStyle(34);
  h_C2->Scale(1./805.);

  h_C1->SetLineColor(kMagenta-9);
  h_C1->SetMarkerColor(kMagenta-9);
  h_C1->SetMarkerStyle(34);
  h_C1->Scale(1./1630.);

  r_C4 = (TH1D*) h_C4->Clone("r_C4");
  r_C4->Divide(h_C4,h_pp,1,1,"");

  r_C3 = (TH1D*) h_C3->Clone("r_C3");
  r_C3->Divide(h_C3,h_pp,1,1,"");

  r_C2 = (TH1D*) h_C2->Clone("r_C2");
  r_C2->Divide(h_C2,h_pp,1,1,"");

  r_C1 = (TH1D*) h_C1->Clone("r_C1");
  r_C1->Divide(h_C1,h_pp,1,1,"");

  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0,1,1);
  p1->SetLeftMargin(0.15);
  p1->SetBottomMargin(0.15);
  p1->SetLogy();
  p1->Draw();
  p1->cd();
  h_pp->Draw();
  h_C4->Draw("same");
  // h_C3->Draw("same");
  // h_C2->Draw("same");
  // h_C1->Draw("same");

  TCanvas *c2 = new TCanvas("c2","c2",700,700);
  c2->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,1);
  p2->SetLeftMargin(0.15);
  p2->SetBottomMargin(0.15);
  p2->Draw();
  p2->cd();
  r_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C4->GetYaxis()->SetTitle("PbPb / pp");\
  r_C4->SetTitle("");
  r_C4->SetStats(0);
  //r_C4->GetYaxis()->SetRangeUser(0,1);
  r_C4->Draw();
  // r_C3->Draw();
  // r_C2->Draw("same");
  // r_C1->Draw("same");
  
  


}
