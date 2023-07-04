

TFile *file_pp, *file_C2, *file_C1;
TH1D *corrFactor_1_pp, *corrFactor_2_pp, *corrFactor_3_pp;
TH1D *corrFactor_1_C2, *corrFactor_2_C2, *corrFactor_3_C2;
TH1D *corrFactor_1_C1, *corrFactor_2_C1, *corrFactor_3_C1;
// shorthand names
TH1D *a0, *a1, *a2;
TH1D *b0, *b1, *b2;
TH1D *c0, *c1, *c2;

void plotCorrectionFactors(){

  file_pp = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_pp.root");
  file_C2 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C2.root");
  file_C1 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C1.root");

  file_pp->GetObject("corrFactor_1_pp",corrFactor_1_pp);
  file_pp->GetObject("corrFactor_2_pp",corrFactor_2_pp);
  file_pp->GetObject("corrFactor_3_pp",corrFactor_3_pp);

  file_C2->GetObject("corrFactor_1_C2",corrFactor_1_C2);
  file_C2->GetObject("corrFactor_2_C2",corrFactor_2_C2);
  file_C2->GetObject("corrFactor_3_C2",corrFactor_3_C2);

  file_C1->GetObject("corrFactor_1_C1",corrFactor_1_C1);
  file_C1->GetObject("corrFactor_2_C1",corrFactor_2_C1);
  file_C1->GetObject("corrFactor_3_C1",corrFactor_3_C1);

  a0 = (TH1D*) corrFactor_1_pp->Clone("a0");
  a1 = (TH1D*) corrFactor_1_C2->Clone("a1");
  a2 = (TH1D*) corrFactor_1_C1->Clone("a2");

  b0 = (TH1D*) corrFactor_2_pp->Clone("b0");
  b1 = (TH1D*) corrFactor_2_C2->Clone("b1");
  b2 = (TH1D*) corrFactor_2_C1->Clone("b2");

  c0 = (TH1D*) corrFactor_3_pp->Clone("c0");
  c1 = (TH1D*) corrFactor_3_C2->Clone("c1");
  c2 = (TH1D*) corrFactor_3_C1->Clone("c2");

  a0->SetLineColor(kBlack);
  a0->SetMarkerColor(kBlack);
  a0->SetMarkerStyle(22);

  a1->SetLineColor(kRed-4);
  a1->SetMarkerColor(kRed-4);
  a1->SetMarkerStyle(20);

  a2->SetLineColor(kBlue-4);
  a2->SetMarkerColor(kBlue-4);
  a2->SetMarkerStyle(21);

  b0->SetLineColor(kBlack);
  b0->SetMarkerColor(kBlack);
  b0->SetMarkerStyle(22);

  b1->SetLineColor(kRed-4);
  b1->SetMarkerColor(kRed-4);
  b1->SetMarkerStyle(20);

  b2->SetLineColor(kBlue-4);
  b2->SetMarkerColor(kBlue-4);
  b2->SetMarkerStyle(21);

  c0->SetLineColor(kBlack);
  c0->SetMarkerColor(kBlack);
  c0->SetMarkerStyle(22);

  c1->SetLineColor(kRed-4);
  c1->SetMarkerColor(kRed-4);
  c1->SetMarkerStyle(20);

  c2->SetLineColor(kBlue-4);
  c2->SetMarkerColor(kBlue-4);
  c2->SetMarkerStyle(21);

  double labelSize = 0.04;
  double titleSize = 0.052;

  TCanvas *canv_a = new TCanvas("canv_a","corrFactor 1",700,700);
  canv_a->cd();
  TPad *pad_a = new TPad("pad_a","pad_a",0,0,1,1);
  pad_a->SetLeftMargin(0.2);
  pad_a->SetBottomMargin(0.2);
  pad_a->Draw();
  pad_a->cd();
  a0->SetTitle("Fraction of reco #font[52]{b}-jets tagged with genMuon");
  a0->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  a0->GetYaxis()->SetTitle("");
  a0->GetXaxis()->SetLabelSize(labelSize);
  a0->GetXaxis()->SetTitleSize(titleSize);
  a0->GetYaxis()->SetLabelSize(labelSize);
  a0->GetYaxis()->SetTitleSize(titleSize);
  a0->GetXaxis()->SetRangeUser(60,200);
  a0->Draw();
  a1->Draw("same");
  a2->Draw("same");

  double legTextSize = 0.033;
  TLegend *leg = new TLegend(0.4,0.32,0.88,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(legTextSize);
  leg->AddEntry(a0,"PYTHIA","p");
  leg->AddEntry(a1,"PYTHIA+HYDJET 30-90%","p");
  leg->AddEntry(a2,"PYTHIA+HYDJET 0-30%","p");
  leg->Draw();

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
  b0->GetXaxis()->SetRangeUser(60,200);
  b0->Draw();
  b1->Draw("same");
  b2->Draw("same");
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
  c0->GetXaxis()->SetRangeUser(60,200);
  c0->Draw();
  c1->Draw("same");
  c2->Draw("same");
  leg->Draw();

  canv_a->SaveAs("../../figures/correctionFactors/genMuonTag.pdf");
  canv_b->SaveAs("../../figures/correctionFactors/muonReco.pdf");
  canv_c->SaveAs("../../figures/correctionFactors/muonTrigger.pdf");
  
  
}
