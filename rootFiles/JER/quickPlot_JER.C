void quickPlot_JER(){

  TFile *f1 = TFile::Open("JER_C0_pthat30.root");
  TFile *f2 = TFile::Open("JER_C0_pthat40.root");
  TFile *f3 = TFile::Open("JER_C0_pthat50.root");

  TH1D *h1, *h2, *h3;

  f1->GetObject("JER_result_b",h1);
  f2->GetObject("JER_result_b",h2);
  f3->GetObject("JER_result_b",h3);

  h1->SetMarkerColor(kBlack);
  h2->SetMarkerColor(kBlack);
  h3->SetMarkerColor(kBlack);

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlack);
  h3->SetLineColor(kBlack);

  h1->SetMarkerStyle(20);
  h2->SetMarkerStyle(24);
  h3->SetMarkerStyle(25);


  TH1D *r2, *r3;

  r2 = (TH1D*) h2->Clone("r2");
  r2->Divide(h2,h1,1,1,"B");

  r3 = (TH1D*) h3->Clone("r3");
  r3->Divide(h3,h1,1,1,"B");
  

  double titleSize = 0.06;
  double labelSize = 0.05;
  double lowerPadScalar = 1.3;

  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad1 = new TPad("pad1","pad1",0,0.4,1,1);
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.4);
  pad1->SetLeftMargin(0.2);
  pad2->SetLeftMargin(0.2);
  pad1->SetBottomMargin(0.0);
  pad2->SetBottomMargin(0.2);
  pad1->SetTopMargin(0.2);
  pad2->SetTopMargin(0.0);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  h1->GetYaxis()->SetTitleSize(titleSize);
  h1->GetYaxis()->SetLabelSize(titleSize);
  h1->SetStats(0);
  h1->SetTitle("");
  h1->GetYaxis()->SetTitle("#sigma(#font[52]{p}_{T}^{recoJet} / #font[52]{p}_{T}^{genJet})");
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");
  TLegend *leg = new TLegend(0.3,0.15,0.4,0.35);
  leg->SetTextSize(labelSize);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"#hat{#font[52]{p}}_{T} > 30 GeV","p");
  leg->AddEntry(h2,"#hat{#font[52]{p}}_{T} > 40 GeV","p");
  leg->AddEntry(h3,"#hat{#font[52]{p}}_{T} > 50 GeV","p");
  leg->Draw();
  pad2->cd();
  r2->GetYaxis()->SetTitleSize(lowerPadScalar*titleSize);
  r2->GetYaxis()->SetLabelSize(lowerPadScalar*titleSize);
  r2->GetXaxis()->SetTitleSize(lowerPadScalar*titleSize);
  r2->GetXaxis()->SetLabelSize(lowerPadScalar*titleSize);
  r2->GetXaxis()->SetTitle("#font[52]{p}_{T}^{genJet} [GeV]");
  r2->GetYaxis()->SetTitle("X / pThat30 ");
  r2->SetStats(0);
  r2->SetTitle("");
  r2->Draw();
  r3->Draw("same");
  TLine *li = new TLine();
  li->SetLineStyle(7);
  

  
  
  
  
}
