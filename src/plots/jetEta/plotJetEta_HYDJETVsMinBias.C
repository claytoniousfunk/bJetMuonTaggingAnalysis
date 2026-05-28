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

TString getCentString(bool doC4 = true,
		      bool doC3 = false,
		      bool doC2 = false,
		      bool doC1 = false){

  TString result = "";

  if(doC4) result = "C4";
  else if(doC3) result = "C3";
  else if(doC2) result = "C2";
  else if(doC1) result = "C1";
  else{};

  return result;

}

int getCentHiBinLowerBound(bool doC4 = true,
			      bool doC3 = false,
			      bool doC2 = false,
			      bool doC1 = false){

  int result = 0;

  if(doC4) result = 100;
  else if(doC3) result = 60;
  else if(doC2) result = 20;
  else if(doC1) result = 0;
  else{};
  
  return result;

}

int getCentHiBinUpperBound(bool doC4 = true,
			      bool doC3 = false,
			      bool doC2 = false,
			      bool doC1 = false){

  int result = 0;

  if(doC4) result = 160;
  else if(doC3) result = 100;
  else if(doC2) result = 60;
  else if(doC1) result = 20;
  else{};
  
  return result;

}

TString getTitle(bool doC4 = true,
		 bool doC3 = false,
		 bool doC2 = false,
		 bool doC1 = false){

  TString result = "";

  if(doC4) result = "PbPb 50-80%";
  else if(doC3) result = "PbPb 30-50%";
  else if(doC2) result = "PbPb 10-30%";
  else if(doC1) result = "PbPb 0-10%";
  else{};
  
  return result;

}


void stylizeHistograms(TH1D *h1,
		       TH1D *h2,
		       bool doC4,
		       bool doC3,
		       bool doC2,
		       bool doC1){

  double lineWidth = 2.0;
  h1->SetLineWidth(lineWidth);
  h2->SetLineWidth(lineWidth);

  h1->SetLineColor(kRed-4);
  h2->SetLineColor(kBlue-4);

  h1->SetStats(0);
  h2->SetStats(0);

  h1->SetTitle("");
  h2->SetTitle("");

  TString title = getTitle(doC4,doC3,doC2,doC1);
  TString xTitle = "Jet #it{#eta}";
  TString yTitle = "#frac{1}{#it{N}^{evt}} #frac{d#it{N}^{jet}}{d#it{#eta}}";

  double titleSize = 0.05;
  
  double xTitleSize = 0.046;
  double xLabelSize = 0.04;

  double yTitleSize = 0.046;
  double yLabelSize = 0.04;


  h1->SetTitleSize(titleSize);
  h2->SetTitleSize(titleSize);

  h1->SetTitle(title);
  h2->SetTitle(title);

  h1->GetXaxis()->SetLabelSize(xLabelSize);
  h2->GetXaxis()->SetLabelSize(xLabelSize);
  h1->GetXaxis()->SetTitleSize(xTitleSize);
  h2->GetXaxis()->SetTitleSize(xTitleSize);
  
  h1->GetXaxis()->SetTitle(xTitle);
  h2->GetXaxis()->SetTitle(xTitle);

  h1->GetYaxis()->SetLabelSize(yLabelSize);
  h2->GetYaxis()->SetLabelSize(yLabelSize);
  h1->GetYaxis()->SetTitleSize(yTitleSize);
  h2->GetYaxis()->SetTitleSize(yTitleSize);

  h1->GetYaxis()->SetTitle(yTitle);
  h2->GetYaxis()->SetTitle(yTitle);
  
}



void plotJetEta_HYDJETVsMinBias(bool doC4 = true,
			       bool doC3 = false,
			       bool doC2 = false,
			       bool doC1 = false){

  TFile *f_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/canonical/HYDJET_pThat-unweighted_mu12_pTmu-15to999_tight_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-28.root");
  //TFile *f_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-27.root");
  TFile *f_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_MinBias_mu12_pTmu-15to999_tight_WDecayFilter_2026-4-8.root");

  TH2D *H1;
  TH1D *h1, *h2; // jet histograms
  TH1D *n1, *n2; // event-counting histograms

  TString centString = getCentString(doC4,doC3,doC2,doC1);

  f_HYDJET->GetObject(Form("h_inclRecoJetEta_flavor_%s",centString.Data()),H1);
  //h1 = (TH1D*) H1->ProjectionX("h1",H1->GetYaxis()->FindBin(18.),H1->GetYaxis()->FindBin(18.));
  h1 = (TH1D*) H1->ProjectionX("h1",H1->GetYaxis()->FindBin(0.),H1->GetYaxis()->FindBin(0.));
  f_HYDJET->GetObject("h_hiBin",n1);

  f_MinBias->GetObject(Form("h_inclRecoJetEta_%s",centString.Data()),h2);
  f_MinBias->GetObject("h_hiBin",n2);

  double N1 = integrate(n1,getCentHiBinLowerBound(doC4,doC3,doC2,doC1),getCentHiBinUpperBound(doC4,doC3,doC2,doC1));
  double N2 = integrate(n2,getCentHiBinLowerBound(doC4,doC3,doC2,doC1),getCentHiBinUpperBound(doC4,doC3,doC2,doC1));

  cout << "N1 = " << N1 << "\n";
  cout << "N2 = " << N2 << "\n";
  
  stylizeHistograms(h1,h2,doC4,doC3,doC2,doC1);

  h1->Scale(1./N1);
  h2->Scale(1./N2);

  TH1D *r = (TH1D*) h2->Clone("r");
  r->Divide(h2,h1,1,1,"");

  TLatex *la = new TLatex();
  la->SetTextSize(0.045);

  TLine *li = new TLine();
  li->SetLineStyle(7);
  
  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad_u = new TPad("pad_u","pad_u",0,0.4,1,1);
  TPad *pad_l = new TPad("pad_l","pad_l",0,0,1,0.4);
  pad_u->SetLeftMargin(0.15);
  pad_l->SetLeftMargin(0.15);
  pad_u->SetBottomMargin(0.);
  pad_l->SetBottomMargin(0.15);
  pad_u->SetTopMargin(0.15);
  pad_l->SetTopMargin(0.);
  pad_u->Draw();
  pad_l->Draw();
  pad_u->cd();

  if(doC4) h2->GetYaxis()->SetRangeUser(0,0.001);
  else if(doC3) h2->GetYaxis()->SetRangeUser(0,0.02);
  else if(doC2) h2->GetYaxis()->SetRangeUser(0,0.07);
  else if(doC1) h2->GetYaxis()->SetRangeUser(0,0.1);
  
  h2->Draw();
  h1->Draw("same");

  TLegend *leg = new TLegend(0.6,0.6,0.84,0.74);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.044);
  leg->AddEntry(h1,"HYDJET");
  leg->AddEntry(h2,"PbPb MinBias");

  leg->Draw();

  pad_l->cd();
  r->SetTitle("");
  r->GetYaxis()->SetTitleSize(0.06);
  r->GetXaxis()->SetTitleSize(0.06);
  r->GetYaxis()->SetLabelSize(0.05);
  r->GetXaxis()->SetLabelSize(0.05);
  r->GetYaxis()->SetTitle("Data / MC  ");
  r->GetYaxis()->SetRangeUser(0,2);
  r->Draw();
  li->DrawLine(-1.6,1,1.6,1);
  
  canv->SaveAs(Form("../../../figures/jetEta/HYDJETVsMinBias/jetEta_HYDJETVsMinBias_%s.pdf",centString.Data()));

  






}
