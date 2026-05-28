

TString getJetPtString(double jetPtLow, double jetPtHigh){

  TString result = "";

  if(jetPtLow < 100 && jetPtHigh < 100) result = Form("pTjet-%2.0fto%2.0f",jetPtLow,jetPtHigh);
  else if(jetPtLow < 100 && jetPtHigh >= 100) result = Form("pTjet-%2.0fto%3.0f",jetPtLow,jetPtHigh);
  else if(jetPtLow >= 100 && jetPtHigh >= 100) result = Form("pTjet-%3.0fto%3.0f",jetPtLow,jetPtHigh);
  else{};

  return result;


}


void stylizeHistograms(TH1D *h1, TH1D *h2, TH1D *h3){

  double lineWidth = 2;
  h1->SetLineWidth(lineWidth);
  h2->SetLineWidth(lineWidth);
  h3->SetLineWidth(lineWidth);

  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kGreen+2);

  // h2->Scale(1./h1->Integral());
  // h1->Scale(1./h1->Integral());
  // h3->Scale(1./h3->Integral());
  

}


void plotJetPt_WDecayFilterEffect(double jetPtLow = 80,
				  double jetPtHigh = 100){

  TString jetPtSuffix = getJetPtString(jetPtLow,jetPtHigh);

  TFile *f_pp_noFilter = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15to999_tight_jetTrkMaxFilter_2026-2-19.root");
  TFile *f_pp_withFilter = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15_tight_jetTrkMaxFilter_WDecayFilter_2026-2-10.root");
  TFile *f_pp_withCut = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15to60_tight_jetTrkMaxFilter_2026-2-26.root");


  TFile *f_PbPb_noFilter = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15to999_tight_2026-2-19.root");
  TFile *f_PbPb_withFilter = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15_tight_WDecayFilter_2026-1-13.root");
  TFile *f_PbPb_withCut = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15to60_tight_2026-2-26.root");


  TH1D *h_pp_withFilter, *h_pp_noFilter, *h_pp_withCut;
  TH1D *h_C4_withFilter, *h_C4_noFilter, *h_C4_withCut;
  TH1D *h_C3_withFilter, *h_C3_noFilter, *h_C3_withCut;
  TH1D *h_C2_withFilter, *h_C2_noFilter, *h_C2_withCut;
  TH1D *h_C1_withFilter, *h_C1_noFilter, *h_C1_withCut;

  TH1D *r_pp, *r_C4, *r_C3, *r_C2, *r_C1;
  TH1D *rr_pp, *rr_C4, *rr_C3, *rr_C2, *rr_C1;

  f_pp_noFilter->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_pp_noFilter);
  f_pp_withFilter->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_pp_withFilter);
  f_pp_withCut->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_pp_withCut);
  

  f_PbPb_noFilter->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",h_C4_noFilter);
  f_PbPb_withFilter->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",h_C4_withFilter);
  f_PbPb_withCut->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",h_C4_withCut);
  

  f_PbPb_noFilter->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",h_C3_noFilter);
  f_PbPb_withFilter->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",h_C3_withFilter);
  f_PbPb_withCut->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",h_C3_withCut);
  
  
  f_PbPb_noFilter->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",h_C2_noFilter);
  f_PbPb_withFilter->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",h_C2_withFilter);
  f_PbPb_withCut->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",h_C2_withCut);
  

  f_PbPb_noFilter->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",h_C1_noFilter);
  f_PbPb_withFilter->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",h_C1_withFilter);
  f_PbPb_withCut->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",h_C1_withCut);
  
    
  stylizeHistograms(h_pp_withFilter,h_pp_noFilter,h_pp_withCut);
  stylizeHistograms(h_C4_withFilter,h_C4_noFilter,h_C4_withCut);
  stylizeHistograms(h_C3_withFilter,h_C3_noFilter,h_C3_withCut);
  stylizeHistograms(h_C2_withFilter,h_C2_noFilter,h_C2_withCut);
  stylizeHistograms(h_C1_withFilter,h_C1_noFilter,h_C1_withCut);

  r_pp = (TH1D*) h_pp_withFilter->Clone("r_pp");
  r_pp->Divide(h_pp_withFilter,h_pp_noFilter,1,1,"B");

  r_C4 = (TH1D*) h_C4_withFilter->Clone("r_C4");
  r_C4->Divide(h_C4_withFilter,h_C4_noFilter,1,1,"B");

  r_C3 = (TH1D*) h_C3_withFilter->Clone("r_C3");
  r_C3->Divide(h_C3_withFilter,h_C3_noFilter,1,1,"B");

  r_C2 = (TH1D*) h_C2_withFilter->Clone("r_C2");
  r_C2->Divide(h_C2_withFilter,h_C2_noFilter,1,1,"B");

  r_C1 = (TH1D*) h_C1_withFilter->Clone("r_C1");
  r_C1->Divide(h_C1_withFilter,h_C1_noFilter,1,1,"B");

  rr_pp = (TH1D*) h_pp_withCut->Clone("rr_pp");
  rr_pp->Divide(h_pp_withCut,h_pp_noFilter,1,1,"B");

  rr_C4 = (TH1D*) h_C4_withCut->Clone("rr_C4");
  rr_C4->Divide(h_C4_withCut,h_C4_noFilter,1,1,"B");

  rr_C3 = (TH1D*) h_C3_withCut->Clone("rr_C3");
  rr_C3->Divide(h_C3_withCut,h_C3_noFilter,1,1,"B");

  rr_C2 = (TH1D*) h_C2_withCut->Clone("rr_C2");
  rr_C2->Divide(h_C2_withCut,h_C2_noFilter,1,1,"B");

  rr_C1 = (TH1D*) h_C1_withCut->Clone("rr_C1");
  rr_C1->Divide(h_C1_withCut,h_C1_noFilter,1,1,"B");

  double leftMargin = 0.15;
  double bottomMargin = 0.15;
  double titleSize = 0.05;
  double xTitleSize = 0.065;
  double xLabelSize = 0.058;
  double yTitleSizeUpper = 0.055;
  double yLabelSizeUpper = 0.048;
  double yTitleSizeLower = 0.065;
  double yLabelSizeLower = 0.058;

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.05);

  TLine *li = new TLine();
  li->SetLineStyle(7);
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *canv_pp = new TCanvas("canv_pp","canv_pp",700,700);
  canv_pp->cd();
  TPad *pad_pp_upper = new TPad("pad_pp_upper","pad_pp_upper",0,0.4,1,1);
  TPad *pad_pp_lower = new TPad("pad_pp_lower","pad_pp_lower",0,0,1,0.4);
  pad_pp_upper->SetLeftMargin(leftMargin);
  pad_pp_lower->SetLeftMargin(leftMargin);
  pad_pp_upper->SetBottomMargin(0.0);
  pad_pp_lower->SetBottomMargin(bottomMargin);
  pad_pp_lower->SetTopMargin(0.0);
  pad_pp_upper->SetLogy();
  pad_pp_upper->Draw();
  pad_pp_lower->Draw();
  pad_pp_upper->cd();
  h_pp_noFilter->SetStats(0);
  h_pp_noFilter->SetTitleSize(titleSize);
  h_pp_noFilter->SetTitle("pp");
  h_pp_noFilter->GetYaxis()->SetTitleSize(yTitleSizeUpper);
  h_pp_noFilter->GetYaxis()->SetLabelSize(yLabelSizeUpper);
  h_pp_noFilter->GetYaxis()->SetTitle("Entries");
  //h_pp_noFilter->GetYaxis()->SetRangeUser(2e-5,2e-0);
  h_pp_noFilter->Draw();
  h_pp_withFilter->Draw("same");
  h_pp_withCut->Draw("same");
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.4,0.8,"AK4PF Jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.4,0.72,"#it{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.2,0.36,"No filter");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.2,0.28,"#it{p}_{T}^{#it{#mu}} / #it{p}_{T}^{jet} < 0.75");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.2,0.2,"#it{p}_{T}^{#it{#mu}} < 60 GeV");
  pad_pp_lower->cd();
  r_pp->SetStats(0);
  r_pp->SetTitle("");
  r_pp->GetYaxis()->SetTitleSize(yTitleSizeLower);
  r_pp->GetYaxis()->SetLabelSize(yLabelSizeLower);
  r_pp->GetYaxis()->SetTitle("Data / MC");
  r_pp->GetXaxis()->SetTitleSize(xTitleSize);
  r_pp->GetXaxis()->SetLabelSize(xLabelSize);
  r_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_pp->GetYaxis()->SetRangeUser(0.65,1.35);
  r_pp->Draw();
  rr_pp->Draw("same");
  li->DrawLine(20,1,500,1);
  canv_pp->SaveAs("../../../figures/jetPt/WDecayFilterEffect/jetPt_WDecayFilterEffect_pp.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *canv_C4 = new TCanvas("canv_C4","canv_C4",700,700);
  canv_C4->cd();
  TPad *pad_C4_upper = new TPad("pad_C4_upper","pad_C4_upper",0,0.4,1,1);
  TPad *pad_C4_lower = new TPad("pad_C4_lower","pad_C4_lower",0,0,1,0.4);
  pad_C4_upper->SetLeftMargin(leftMargin);
  pad_C4_lower->SetLeftMargin(leftMargin);
  pad_C4_upper->SetBottomMargin(0.0);
  pad_C4_lower->SetBottomMargin(bottomMargin);
  pad_C4_lower->SetTopMargin(0.0);
  pad_C4_upper->SetLogy();
  pad_C4_upper->Draw();
  pad_C4_lower->Draw();
  pad_C4_upper->cd();
  h_C4_noFilter->SetStats(0);
  h_C4_noFilter->SetTitleSize(titleSize);
  h_C4_noFilter->SetTitle("PbPb 50-80%");
  h_C4_noFilter->GetYaxis()->SetTitleSize(yTitleSizeUpper);
  h_C4_noFilter->GetYaxis()->SetLabelSize(yLabelSizeUpper);
  h_C4_noFilter->GetYaxis()->SetTitle("Entries");
  //h_C4_noFilter->GetYaxis()->SetRangeUser(2e-5,2e-0);
  h_C4_noFilter->Draw();
  h_C4_withFilter->Draw("same");
  h_C4_withCut->Draw("same");
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.4,0.8,"AK4CsPF Jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.4,0.72,"#it{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.2,0.36,"No filter");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.2,0.28,"#it{p}_{T}^{#it{#mu}} / #it{p}_{T}^{jet} < 0.75");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.2,0.2,"#it{p}_{T}^{#it{#mu}} < 60 GeV");
  pad_C4_lower->cd();
  r_C4->SetStats(0);
  r_C4->SetTitle("");
  r_C4->GetYaxis()->SetTitleSize(yTitleSizeLower);
  r_C4->GetYaxis()->SetLabelSize(yLabelSizeLower);
  r_C4->GetYaxis()->SetTitle("Ratio");
  r_C4->GetXaxis()->SetTitleSize(xTitleSize);
  r_C4->GetXaxis()->SetLabelSize(xLabelSize);
  r_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C4->GetYaxis()->SetRangeUser(0.65,1.35);
  r_C4->Draw();
  rr_C4->Draw("same");
  li->DrawLine(20,1,500,1);
  canv_C4->SaveAs("../../../figures/jetPt/WDecayFilterEffect/jetPt_WDecayFilterEffect_C4.pdf");

    ///////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *canv_C3 = new TCanvas("canv_C3","canv_C3",700,700);
  canv_C3->cd();
  TPad *pad_C3_upper = new TPad("pad_C3_upper","pad_C3_upper",0,0.4,1,1);
  TPad *pad_C3_lower = new TPad("pad_C3_lower","pad_C3_lower",0,0,1,0.4);
  pad_C3_upper->SetLeftMargin(leftMargin);
  pad_C3_lower->SetLeftMargin(leftMargin);
  pad_C3_upper->SetBottomMargin(0.0);
  pad_C3_lower->SetBottomMargin(bottomMargin);
  pad_C3_lower->SetTopMargin(0.0);
  pad_C3_upper->SetLogy();
  pad_C3_upper->Draw();
  pad_C3_lower->Draw();
  pad_C3_upper->cd();
  h_C3_noFilter->SetStats(0);
  h_C3_noFilter->SetTitleSize(titleSize);
  h_C3_noFilter->SetTitle("PbPb 30-50%");
  h_C3_noFilter->GetYaxis()->SetTitleSize(yTitleSizeUpper);
  h_C3_noFilter->GetYaxis()->SetLabelSize(yLabelSizeUpper);
  h_C3_noFilter->GetYaxis()->SetTitle("Entries");
  //h_C3_noFilter->GetYaxis()->SetRangeUser(2e-5,2e-0);
  h_C3_noFilter->Draw();
  h_C3_withFilter->Draw("same");
  h_C3_withCut->Draw("same");
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.4,0.8,"AK4CsPF Jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.4,0.72,"#it{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.2,0.36,"No filter");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.2,0.28,"#it{p}_{T}^{#it{#mu}} / #it{p}_{T}^{jet} < 0.75");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.2,0.2,"#it{p}_{T}^{#it{#mu}} < 60 GeV");
  pad_C3_lower->cd();
  r_C3->SetStats(0);
  r_C3->SetTitle("");
  r_C3->GetYaxis()->SetTitleSize(yTitleSizeLower);
  r_C3->GetYaxis()->SetLabelSize(yLabelSizeLower);
  r_C3->GetYaxis()->SetTitle("Ratio");
  r_C3->GetXaxis()->SetTitleSize(xTitleSize);
  r_C3->GetXaxis()->SetLabelSize(xLabelSize);
  r_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C3->GetYaxis()->SetRangeUser(0.65,1.35);
  r_C3->Draw();
  rr_C3->Draw("same");
  li->DrawLine(20,1,500,1);
  canv_C3->SaveAs("../../../figures/jetPt/WDecayFilterEffect/jetPt_WDecayFilterEffect_C3.pdf");

    ///////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *canv_C2 = new TCanvas("canv_C2","canv_C2",700,700);
  canv_C2->cd();
  TPad *pad_C2_upper = new TPad("pad_C2_upper","pad_C2_upper",0,0.4,1,1);
  TPad *pad_C2_lower = new TPad("pad_C2_lower","pad_C2_lower",0,0,1,0.4);
  pad_C2_upper->SetLeftMargin(leftMargin);
  pad_C2_lower->SetLeftMargin(leftMargin);
  pad_C2_upper->SetBottomMargin(0.0);
  pad_C2_lower->SetBottomMargin(bottomMargin);
  pad_C2_lower->SetTopMargin(0.0);
  pad_C2_upper->SetLogy();
  pad_C2_upper->Draw();
  pad_C2_lower->Draw();
  pad_C2_upper->cd();
  h_C2_noFilter->SetStats(0);
  h_C2_noFilter->SetTitleSize(titleSize);
  h_C2_noFilter->SetTitle("PbPb 10-30%");
  h_C2_noFilter->GetYaxis()->SetTitleSize(yTitleSizeUpper);
  h_C2_noFilter->GetYaxis()->SetLabelSize(yLabelSizeUpper);
  h_C2_noFilter->GetYaxis()->SetTitle("Entries");
  //h_C2_noFilter->GetYaxis()->SetRangeUser(2e-5,2e-0);
  h_C2_noFilter->Draw();
  h_C2_withFilter->Draw("same");
  h_C2_withCut->Draw("same");
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.4,0.8,"AK4CsPF Jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.4,0.72,"#it{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.2,0.36,"No filter");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.2,0.28,"#it{p}_{T}^{#it{#mu}} / #it{p}_{T}^{jet} < 0.75");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.2,0.2,"#it{p}_{T}^{#it{#mu}} < 60 GeV");
  pad_C2_lower->cd();
  r_C2->SetStats(0);
  r_C2->SetTitle("");
  r_C2->GetYaxis()->SetTitleSize(yTitleSizeLower);
  r_C2->GetYaxis()->SetLabelSize(yLabelSizeLower);
  r_C2->GetYaxis()->SetTitle("Ratio");
  r_C2->GetXaxis()->SetTitleSize(xTitleSize);
  r_C2->GetXaxis()->SetLabelSize(xLabelSize);
  r_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C2->GetYaxis()->SetRangeUser(0.65,1.35);
  r_C2->Draw();
  rr_C2->Draw("same");
  li->DrawLine(20,1,500,1);
  canv_C2->SaveAs("../../../figures/jetPt/WDecayFilterEffect/jetPt_WDecayFilterEffect_C2.pdf");

    ///////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *canv_C1 = new TCanvas("canv_C1","canv_C1",700,700);
  canv_C1->cd();
  TPad *pad_C1_upper = new TPad("pad_C1_upper","pad_C1_upper",0,0.4,1,1);
  TPad *pad_C1_lower = new TPad("pad_C1_lower","pad_C1_lower",0,0,1,0.4);
  pad_C1_upper->SetLeftMargin(leftMargin);
  pad_C1_lower->SetLeftMargin(leftMargin);
  pad_C1_upper->SetBottomMargin(0.0);
  pad_C1_lower->SetBottomMargin(bottomMargin);
  pad_C1_lower->SetTopMargin(0.0);
  pad_C1_upper->SetLogy();
  pad_C1_upper->Draw();
  pad_C1_lower->Draw();
  pad_C1_upper->cd();
  h_C1_noFilter->SetStats(0);
  h_C1_noFilter->SetTitleSize(titleSize);
  h_C1_noFilter->SetTitle("PbPb 0-10%");
  h_C1_noFilter->GetYaxis()->SetTitleSize(yTitleSizeUpper);
  h_C1_noFilter->GetYaxis()->SetLabelSize(yLabelSizeUpper);
  h_C1_noFilter->GetYaxis()->SetTitle("Entries");
  //h_C1_noFilter->GetYaxis()->SetRangeUser(2e-5,2e-0);
  h_C1_noFilter->Draw();
  h_C1_withFilter->Draw("same");
  h_C1_withCut->Draw("same");
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.4,0.8,"AK4CsPF Jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.4,0.72,"#it{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.2,0.36,"No filter");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.2,0.28,"#it{p}_{T}^{#it{#mu}} / #it{p}_{T}^{jet} < 0.75");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.2,0.2,"#it{p}_{T}^{#it{#mu}} < 60 GeV");
  pad_C1_lower->cd();
  r_C1->SetStats(0);
  r_C1->SetTitle("");
  r_C1->GetYaxis()->SetTitleSize(yTitleSizeLower);
  r_C1->GetYaxis()->SetLabelSize(yLabelSizeLower);
  r_C1->GetYaxis()->SetTitle("Ratio");
  r_C1->GetXaxis()->SetTitleSize(xTitleSize);
  r_C1->GetXaxis()->SetLabelSize(xLabelSize);
  r_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C1->GetYaxis()->SetRangeUser(0.65,1.35);
  r_C1->Draw();
  rr_C1->Draw("same");
  li->DrawLine(20,1,500,1);
  canv_C1->SaveAs("../../../figures/jetPt/WDecayFilterEffect/jetPt_WDecayFilterEffect_C1.pdf");



}
