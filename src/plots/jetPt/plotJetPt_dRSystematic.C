

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


void plotJetPt_dRSystematic(double jetPtLow = 80,
			    double jetPtHigh = 100){

  TString jetPtSuffix = getJetPtString(jetPtLow,jetPtHigh);

  TFile *f_pp_dR35 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15to60_tight_deltaR-35_jetTrkMaxFilter_2026-2-26.root");
  TFile *f_pp_dR40 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15to60_tight_jetTrkMaxFilter_2026-2-26.root");
  TFile *f_pp_dR45 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15to60_tight_deltaR-45_jetTrkMaxFilter_2026-2-26.root");


  TH1D *h_pp_dR35, *h_pp_dR40, *h_pp_dR45;

  TH1D *r_pp, *r_C4, *r_C3, *r_C2, *r_C1;
  TH1D *rr_pp, *rr_C4, *rr_C3, *rr_C2, *rr_C1;

  f_pp_dR35->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_pp_dR35);
  f_pp_dR40->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_pp_dR40);
  f_pp_dR45->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_pp_dR45);
  

  
  stylizeHistograms(h_pp_dR35,h_pp_dR40,h_pp_dR45);
  

  r_pp = (TH1D*) h_pp_dR35->Clone("r_pp");
  r_pp->Divide(h_pp_dR35,h_pp_dR40,1,1,"B");

  

  rr_pp = (TH1D*) h_pp_dR45->Clone("rr_pp");
  rr_pp->Divide(h_pp_dR45,h_pp_dR40,1,1,"B");

  

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
  h_pp_dR40->SetStats(0);
  h_pp_dR40->SetTitleSize(titleSize);
  h_pp_dR40->SetTitle("pp");
  h_pp_dR40->GetYaxis()->SetTitleSize(yTitleSizeUpper);
  h_pp_dR40->GetYaxis()->SetLabelSize(yLabelSizeUpper);
  h_pp_dR40->GetYaxis()->SetTitle("Entries");
  //h_pp_noFilter->GetYaxis()->SetRangeUser(2e-5,2e-0);
  h_pp_dR40->Draw();
  h_pp_dR35->Draw("same");
  h_pp_dR45->Draw("same");
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.4,0.8,"AK4PF Jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.4,0.72,"#it{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.2,0.36,"#it{#Delta R}(#it{#mu},jet) < 0.40");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.2,0.28,"#it{#Delta R}(#it{#mu},jet) < 0.35");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.2,0.2,"#it{#Delta R}(#it{#mu},jet) < 0.45");
  pad_pp_lower->cd();
  r_pp->SetStats(0);
  r_pp->SetTitle("");
  r_pp->GetYaxis()->SetTitleSize(yTitleSizeLower);
  r_pp->GetYaxis()->SetLabelSize(yLabelSizeLower);
  r_pp->GetYaxis()->SetTitle("Ratio");
  r_pp->GetXaxis()->SetTitleSize(xTitleSize);
  r_pp->GetXaxis()->SetLabelSize(xLabelSize);
  r_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_pp->GetYaxis()->SetRangeUser(0.98,1.02);
  r_pp->Draw();
  rr_pp->Draw("same");
  li->DrawLine(20,1,500,1);
  canv_pp->SaveAs("../../../figures/jetPt/dRSystematic/jetPt_dRSystematic_pp.pdf");

 


}
