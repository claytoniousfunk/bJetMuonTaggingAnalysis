void tagging_in_MinBias(){

  // files
  TFile *f_mu5 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/localScans/pp_MinBias_scan_mu5.root");
  TFile *f_mu7 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/localScans/pp_MinBias_scan_mu7.root");
  TFile *f_mu12 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/localScans/pp_MinBias_scan_mu12.root");

  // histograms
  TH1D *a1, *b1, *c1, *rb1, *rc1, *Rc1;
  TH1D *a2, *b2, *c2, *rc2, *Rc2;
  TH1D *a3, *b3, *c3, *rc3, *Rc3;

  f_mu5->GetObject("h_inclRecoJetPt",a1);

  f_mu5->GetObject("h_inclRecoJetPt_inclRecoMuonTag",b1);

  f_mu5->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",c1);
  f_mu7->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",c2);
  f_mu12->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",c3);

  a1->SetMarkerColor(kBlack);

  b1->SetMarkerColor(kRed-4);

  c1->SetMarkerColor(kBlue-4);
  c2->SetMarkerColor(kGreen+2);
  c3->SetMarkerColor(kMagenta-9);

  a1->SetLineColor(kBlack);
  b1->SetLineColor(kRed-4);

  c1->SetLineColor(kBlue-4);
  c2->SetLineColor(kGreen+2);
  c3->SetLineColor(kMagenta-9);

  a1->SetLineWidth(2);
  b1->SetLineWidth(2);
  c1->SetLineWidth(2);
  c2->SetLineWidth(2);
  c3->SetLineWidth(2);

  rb1 = (TH1D*) b1->Clone("rb1");
  rb1->Divide(b1,a1,1,1,"B");

  rc1 = (TH1D*) c1->Clone("rc1");
  rc1->Divide(c1,a1,1,1,"B");

  rc2 = (TH1D*) c2->Clone("rc2");
  rc2->Divide(c2,a1,1,1,"B");

  rc3 = (TH1D*) c3->Clone("rc3");
  rc3->Divide(c3,a1,1,1,"B");

  Rc1 = (TH1D*) c1->Clone("c1");
  Rc1->Divide(c1,b1,1,1,"B");

  Rc2 = (TH1D*) c2->Clone("c2");
  Rc2->Divide(c2,b1,1,1,"B");

  Rc3 = (TH1D*) c3->Clone("c3");
  Rc3->Divide(c3,b1,1,1,"B");
  
  

  // canvas
  TCanvas *canv1 = new TCanvas("canv1","canv1",700,700);

  TPad *p1_1 = new TPad("p1_1","p1_1",0,0.6,1,1);
  TPad *p2_1 = new TPad("p2_1","p2_1",0,0.3,1,0.6);
  TPad *p3_1 = new TPad("p3_1","p3_1",0,0.0,1,0.3);


  p1_1->SetLeftMargin(0.2);
  p1_1->SetBottomMargin(0.0);
  p2_1->SetLeftMargin(0.2);
  p2_1->SetTopMargin(0.0);
  p2_1->SetBottomMargin(0.0);
  p3_1->SetLeftMargin(0.2);
  p3_1->SetTopMargin(0.0);
  p3_1->SetBottomMargin(0.2);



  p1_1->SetLogy();

  
  canv1->cd();
  p1_1->Draw();
  p2_1->Draw();
  p3_1->Draw();
  
  p1_1->cd();
  a1->SetTitle("Tagging + Trigger in pp MinBias");
  a1->SetStats(0);
  a1->GetXaxis()->SetRangeUser(0,200);
  a1->GetYaxis()->SetTitle("Entries");
  a1->Draw();
  b1->Draw("same");
  c1->Draw("same");
  c2->Draw("same");
  c3->Draw("same");
  TLatex *la = new TLatex();
  la->SetTextFont(62);
  la->SetTextSize(0.045);
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.6,0.75,"incl. jets");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.6,0.70,"#mu-tagged");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.6,0.65,"#mu-tagged + mu5");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.6,0.60,"#mu-tagged + mu7");
  la->SetTextColor(kMagenta-9);
  la->DrawLatexNDC(0.6,0.55,"#mu-tagged + mu12");
						   
  p2_1->cd();
  rb1->SetTitle("");
  rb1->SetStats(0);
  rb1->GetXaxis()->SetRangeUser(0,200);
  rb1->GetYaxis()->SetRangeUser(0,0.04);
  rb1->GetXaxis()->SetTitleSize(0.06);
  rb1->GetXaxis()->SetLabelSize(0.05);
  rb1->GetYaxis()->SetTitleSize(0.06);
  rb1->GetYaxis()->SetLabelSize(0.05);
  rb1->GetYaxis()->SetTitle("Ratio to incl.");
  rb1->Draw();
  rc1->Draw("same");
  rc2->Draw("same");
  rc3->Draw("same");

  p3_1->cd();
  Rc1->SetTitle("");
  Rc1->SetStats(0);
  Rc1->GetXaxis()->SetRangeUser(0,200);
  Rc1->GetYaxis()->SetRangeUser(0,1.2);
  Rc1->GetXaxis()->SetTitleSize(0.06);
  Rc1->GetXaxis()->SetLabelSize(0.05);
  Rc1->GetYaxis()->SetTitleSize(0.06);
  Rc1->GetYaxis()->SetLabelSize(0.05);
  Rc1->GetXaxis()->SetTitle("Jet #font[52]{p}_{T} [GeV]");
  Rc1->GetYaxis()->SetTitle("Ratio to #mu-tagged");
  Rc1->Draw();
  Rc2->Draw("same");
  Rc3->Draw("same");

  canv1->SaveAs("tagging_in_MinBias.pdf");
  






}
