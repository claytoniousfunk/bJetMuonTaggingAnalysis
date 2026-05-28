

TFile *file_pp, *file_C4, *file_C3, *file_C2, *file_C1;
TH1D *corrFactor_1_pp, *corrFactor_2_pp, *corrFactor_3_pp, *corrFactor_3_data_pp;
TH1D *corrFactor_1_C4, *corrFactor_2_C4, *corrFactor_3_C4, *corrFactor_3_data_C4;
TH1D *corrFactor_1_C3, *corrFactor_2_C3, *corrFactor_3_C3, *corrFactor_3_data_C3;
TH1D *corrFactor_1_C2, *corrFactor_2_C2, *corrFactor_3_C2, *corrFactor_3_data_C2;
TH1D *corrFactor_1_C1, *corrFactor_2_C1, *corrFactor_3_C1, *corrFactor_3_data_C1;
// shorthand names
TH1D *a0, *a1, *a2, *a3, *a4;
TH1D *b0, *b1, *b2, *b3, *b4;
TH1D *c0, *c1, *c2, *c3, *c4;
TH1D *d0, *d1, *d2, *d3, *d4;

void plotCorrectionFactors_4CentBins(){

  file_pp = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_pp.root");
  file_C4 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C4.root");
  file_C3 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C3.root");
  file_C2 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C2.root");
  file_C1 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C1.root");

  file_pp->GetObject("corrFactor_1_pp",corrFactor_1_pp);
  file_pp->GetObject("corrFactor_2_pp",corrFactor_2_pp);
  file_pp->GetObject("corrFactor_3_pp",corrFactor_3_pp);
  file_pp->GetObject("corrFactor_3_data_pp",corrFactor_3_data_pp);

  file_C4->GetObject("corrFactor_1_C4",corrFactor_1_C4);
  file_C4->GetObject("corrFactor_2_C4",corrFactor_2_C4);
  file_C4->GetObject("corrFactor_3_C4",corrFactor_3_C4);
  file_C4->GetObject("corrFactor_3_data_C4",corrFactor_3_data_C4);

  file_C3->GetObject("corrFactor_1_C3",corrFactor_1_C3);
  file_C3->GetObject("corrFactor_2_C3",corrFactor_2_C3);
  file_C3->GetObject("corrFactor_3_C3",corrFactor_3_C3);
  file_C3->GetObject("corrFactor_3_data_C3",corrFactor_3_data_C3);
  
  file_C2->GetObject("corrFactor_1_C2",corrFactor_1_C2);
  file_C2->GetObject("corrFactor_2_C2",corrFactor_2_C2);
  file_C2->GetObject("corrFactor_3_C2",corrFactor_3_C2);
  file_C2->GetObject("corrFactor_3_data_C2",corrFactor_3_data_C2);

  file_C1->GetObject("corrFactor_1_C1",corrFactor_1_C1);
  file_C1->GetObject("corrFactor_2_C1",corrFactor_2_C1);
  file_C1->GetObject("corrFactor_3_C1",corrFactor_3_C1);
  file_C1->GetObject("corrFactor_3_data_C1",corrFactor_3_data_C1);

  a0 = (TH1D*) corrFactor_1_pp->Clone("a0");
  a1 = (TH1D*) corrFactor_1_C1->Clone("a1");
  a2 = (TH1D*) corrFactor_1_C2->Clone("a2");
  a3 = (TH1D*) corrFactor_1_C3->Clone("a3");
  a4 = (TH1D*) corrFactor_1_C4->Clone("a4");

  b0 = (TH1D*) corrFactor_2_pp->Clone("b0");
  b1 = (TH1D*) corrFactor_2_C1->Clone("b1");
  b2 = (TH1D*) corrFactor_2_C2->Clone("b2");
  b3 = (TH1D*) corrFactor_2_C3->Clone("b3");
  b4 = (TH1D*) corrFactor_2_C4->Clone("b4");

  c0 = (TH1D*) corrFactor_3_pp->Clone("c0");
  c1 = (TH1D*) corrFactor_3_C1->Clone("c1");
  c2 = (TH1D*) corrFactor_3_C2->Clone("c2");
  c3 = (TH1D*) corrFactor_3_C3->Clone("c3");
  c4 = (TH1D*) corrFactor_3_C4->Clone("c4");

  d0 = (TH1D*) corrFactor_3_data_pp->Clone("d0");
  d1 = (TH1D*) corrFactor_3_data_C1->Clone("d1");
  d2 = (TH1D*) corrFactor_3_data_C2->Clone("d2");
  d3 = (TH1D*) corrFactor_3_data_C3->Clone("d3");
  d4 = (TH1D*) corrFactor_3_data_C4->Clone("d4");

  

  a0->SetLineColor(kBlack);
  a0->SetMarkerColor(kBlack);
  a0->SetMarkerStyle(24);
  a0->SetMarkerSize(1.4);

  a1->SetLineColor(kRed-4);
  a1->SetMarkerColor(kRed-4);
  a1->SetMarkerStyle(47);
  a1->SetMarkerSize(1.4);

  a2->SetLineColor(kGreen+2);
  a2->SetMarkerColor(kGreen+2);
  a2->SetMarkerStyle(34);
  a2->SetMarkerSize(1.4);

  a3->SetLineColor(kBlue-4);
  a3->SetMarkerColor(kBlue-4);
  a3->SetMarkerStyle(21);
  a3->SetMarkerSize(1.4);

  a4->SetLineColor(kBlack);
  a4->SetMarkerColor(kBlack);
  a4->SetMarkerStyle(33);
  a4->SetMarkerSize(1.4);

  b0->SetLineColor(kBlack);
  b0->SetMarkerColor(kBlack);
  b0->SetMarkerStyle(20);
  b0->SetMarkerSize(1.4);

  b1->SetLineColor(kMagenta-9);
  b1->SetMarkerColor(kMagenta-9);
  b1->SetMarkerStyle(47);
  b1->SetMarkerSize(1.4);

  b2->SetLineColor(kGreen+2);
  b2->SetMarkerColor(kGreen+2);
  b2->SetMarkerStyle(34);
  b2->SetMarkerSize(1.4);

  b3->SetLineColor(kRed-4);
  b3->SetMarkerColor(kRed-4);
  b3->SetMarkerStyle(21);
  b3->SetMarkerSize(1.4);

  b4->SetLineColor(kBlue+1);
  b4->SetMarkerColor(kBlue+1);
  b4->SetMarkerStyle(33);
  b4->SetMarkerSize(1.4);
  
  c0->SetLineColor(kBlack);
  c0->SetMarkerColor(kBlack);
  c0->SetMarkerStyle(20);
  c0->SetMarkerSize(1.4);

  c1->SetLineColor(kMagenta-9);
  c1->SetMarkerColor(kMagenta-9);
  c1->SetMarkerStyle(47);
  c1->SetMarkerSize(1.4);

  c2->SetLineColor(kGreen+2);
  c2->SetMarkerColor(kGreen+2);
  c2->SetMarkerStyle(34);
  c2->SetMarkerSize(1.4);

  c3->SetLineColor(kRed-4);
  c3->SetMarkerColor(kRed-4);
  c3->SetMarkerStyle(21);
  c3->SetMarkerSize(1.4);

  c4->SetLineColor(kBlue+1);
  c4->SetMarkerColor(kBlue+1);
  c4->SetMarkerStyle(33);
  c4->SetMarkerSize(1.4);
  
  d0->SetLineColor(kBlack);
  d0->SetMarkerColor(kBlack);
  d0->SetMarkerStyle(20);
  d0->SetMarkerSize(1.4);

  d1->SetLineColor(kMagenta-9);
  d1->SetMarkerColor(kMagenta-9);
  d1->SetMarkerStyle(47);
  d1->SetMarkerSize(1.4);

  d2->SetLineColor(kGreen+2);
  d2->SetMarkerColor(kGreen+2);
  d2->SetMarkerStyle(34);
  d2->SetMarkerSize(1.4);

  d3->SetLineColor(kRed-4);
  d3->SetMarkerColor(kRed-4);
  d3->SetMarkerStyle(21);
  d3->SetMarkerSize(1.4);

  d4->SetLineColor(kBlue+1);
  d4->SetMarkerColor(kBlue+1);
  d4->SetMarkerStyle(33);
  d4->SetMarkerSize(1.4);
  
  double labelSize = 0.04;
  double titleSize = 0.052;

  TCanvas *canv_a = new TCanvas("canv_a","corrFactor 1",700,700);
  canv_a->cd();
  TPad *pad_a = new TPad("pad_a","pad_a",0,0,1,1);
  pad_a->SetLeftMargin(0.2);
  pad_a->SetBottomMargin(0.2);
  pad_a->Draw();
  pad_a->cd();
  a0->SetTitle("Fraction of #font[52]{b}-jets tagged with genMuon");
  a0->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  a0->GetYaxis()->SetTitle("");
  a0->GetXaxis()->SetLabelSize(labelSize);
  a0->GetXaxis()->SetTitleSize(titleSize);
  a0->GetYaxis()->SetLabelSize(labelSize);
  a0->GetYaxis()->SetTitleSize(titleSize);
  a0->GetXaxis()->SetRangeUser(80,300);
  a0->GetYaxis()->SetRangeUser(0,0.15);
  a0->Draw();
  a1->Draw("same");
  a2->Draw("same");
  a3->Draw("same");
  a4->Draw("same");

  double legTextSize = 0.033;
  TLegend *leg = new TLegend(0.4,0.32,0.88,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(legTextSize);
  leg->AddEntry(a0,"PYTHIA","p");
  leg->AddEntry(a4,"PYTHIA+HYDJET 50-80%","p");
  leg->AddEntry(a3,"PYTHIA+HYDJET 30-50%","p");
  leg->AddEntry(a2,"PYTHIA+HYDJET 10-30%","p");
  leg->AddEntry(a1,"PYTHIA+HYDJET 0-10%","p");
  leg->Draw();

  TLegend *leg2 = new TLegend(0.4,0.32,0.88,0.45);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(legTextSize);
  // leg2->AddEntry(a0,"pp","p");
  // leg2->AddEntry(a4,"PbPb 50-80%","p");
  // leg2->AddEntry(a3,"PbPb 30-50%","p");
  // leg2->AddEntry(a2,"PbPb 10-30%","p");
  leg2->AddEntry(a1,"PbPb 0-10%","p");
  //leg2->Draw();

  TCanvas *canv_b = new TCanvas("canv_b","corrFactor 2",700,700);
  canv_b->cd();
  TPad *pad_b = new TPad("pad_b","pad_b",0,0,1,1);
  pad_b->SetLeftMargin(0.2);
  pad_b->SetBottomMargin(0.2);
  pad_b->Draw();
  pad_b->cd();
  b0->SetTitle("Fraction of #font[52]{b}-jet gen muons matched to reco muons");
  b0->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  b0->GetYaxis()->SetTitle("");
  b0->GetXaxis()->SetLabelSize(labelSize);
  b0->GetXaxis()->SetTitleSize(titleSize);
  b0->GetYaxis()->SetLabelSize(labelSize);
  b0->GetYaxis()->SetTitleSize(titleSize);
  b0->GetYaxis()->SetRangeUser(0.75,1);
  b0->GetXaxis()->SetRangeUser(80,300);
  b0->Draw();
  b1->Draw("same");
  b2->Draw("same");
  b3->Draw("same");
  b4->Draw("same");
  leg->Draw();

  TCanvas *canv_c = new TCanvas("canv_c","corrFactor 3",700,700);
  canv_c->cd();
  TPad *pad_c = new TPad("pad_c","pad_c",0,0,1,1);
  pad_c->SetLeftMargin(0.2);
  pad_c->SetBottomMargin(0.2);
  pad_c->Draw();
  pad_c->cd();
  c0->SetTitle("Fraction of #font[52]{b}-jet reco muons that fire the trigger");
  c0->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  c0->GetYaxis()->SetTitle("");
  c0->GetXaxis()->SetLabelSize(labelSize);
  c0->GetXaxis()->SetTitleSize(titleSize);
  c0->GetYaxis()->SetLabelSize(labelSize);
  c0->GetYaxis()->SetTitleSize(titleSize);
  c0->GetYaxis()->SetRangeUser(0.6,1);
  c0->GetXaxis()->SetRangeUser(80,300);
  c0->Draw();
  c1->Draw("same");
  c2->Draw("same");
  c3->Draw("same");
  c4->Draw("same");
  leg->Draw();


  // TCanvas *canv_d = new TCanvas("canv_d","corrFactor 3, from data",700,700);
  // canv_d->cd();
  // TPad *pad_d = new TPad("pad_d","pad_d",0,0,1,1);
  // pad_d->SetLeftMargin(0.2);
  // pad_d->SetBottomMargin(0.2);
  // pad_d->Draw();
  // pad_d->cd();
  // d0->SetTitle("Fraction of in-jet reco muons that fire the trigger");
  // d0->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  // d0->GetYaxis()->SetTitle("");
  // d0->GetXaxis()->SetLabelSize(labelSize);
  // d0->GetXaxis()->SetTitleSize(titleSize);
  // d0->GetYaxis()->SetLabelSize(labelSize);
  // d0->GetYaxis()->SetTitleSize(titleSize);
  // d0->GetYaxis()->SetRangeUser(0.6,1);
  // d0->GetXaxis()->SetRangeUser(80,300);
  // d0->SetStats(0);
  // d0->Draw();
  // d1->Draw("same");
  // d2->Draw("same");
  // d3->Draw("same");
  // d4->Draw("same");
  // leg2->Draw();
  // d0->Fit("pol0");
  // d1->Fit("pol0");
  // d2->Fit("pol0");
  // d3->Fit("pol0");
  // d4->Fit("pol0");

  ////////////////////////////////////////////////////////////////////////

  TCanvas *canv_d = new TCanvas("canv_d","corrFactor 3, from data",700,700);
  canv_d->cd();
  TPad *pad_d = new TPad("pad_d","pad_d",0,0,1,1);
  pad_d->SetLeftMargin(0.2);
  pad_d->SetBottomMargin(0.2);
  pad_d->Draw();
  pad_d->cd();
  d1->SetTitle("Fraction of in-jet reco muons that fire the trigger");
  d1->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  d1->GetYaxis()->SetTitle("");
  d1->GetXaxis()->SetLabelSize(labelSize);
  d1->GetXaxis()->SetTitleSize(titleSize);
  d1->GetYaxis()->SetLabelSize(labelSize);
  d1->GetYaxis()->SetTitleSize(titleSize);
  d1->GetYaxis()->SetRangeUser(0.6,1);
  d1->GetXaxis()->SetRangeUser(80,300);
  d1->SetStats(0);

  d1->Draw();
  
  leg2->Draw();
  d1->Fit("pol0");
  


  

  canv_a->SaveAs("../../figures/correctionFactors/genMuonTag.pdf");
  canv_b->SaveAs("../../figures/correctionFactors/muonReco.pdf");
  canv_c->SaveAs("../../figures/correctionFactors/muonTrigger.pdf");
  canv_d->SaveAs("../../figures/correctionFactors/muonTrigger_data.pdf");
  
  
}
