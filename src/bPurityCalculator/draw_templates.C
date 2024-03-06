void draw_templates(){

  TFile *f1 = TFile::Open("./save_templates_mu5.root");
  TFile *f2 = TFile::Open("./save_templates_mu7.root");
  TFile *f3 = TFile::Open("./save_templates_mu12.root");

  TH1D *h1, *h2, *h3;

  double titleSize = 0.05;
  double labelSize = 0.042;

  f1->GetObject("h_data",h1);
  f2->GetObject("h_data",h2);
  f3->GetObject("h_data",h3);

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kGreen+2);
  h3->SetLineColor(kBlue-4);
  
  h1->SetMarkerColor(kBlack);
  h2->SetMarkerColor(kGreen+2);
  h3->SetMarkerColor(kBlue-4);

  h1->SetMarkerStyle(53);
  h2->SetMarkerStyle(54);
  h3->SetMarkerStyle(55);

  TCanvas *c = new TCanvas("c","canvas",700,700);
  c->cd();
  TPad *p = new TPad("p","pad",0,0,1,1);
  p->SetLeftMargin(0.2);
  p->SetBottomMargin(0.2);
  p->Draw();
  p->cd();
  h1->SetTitle("");
  h1->SetStats(0);
  h1->GetXaxis()->SetLabelSize(labelSize);
  h1->GetXaxis()->SetTitleSize(titleSize);
  h1->GetYaxis()->SetLabelSize(labelSize);
  h1->GetYaxis()->SetTitleSize(titleSize);
  h1->GetXaxis()->SetTitle("Muon #font[52]{p}_{T}^{rel} [GeV]");
  h1->GetYaxis()->SetTitle("a.u.");
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");

  TLegend *leg = new TLegend(0.43,0.7,0.8,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.8*labelSize);
  leg->AddEntry(h1,"#font[82]{HLT_HIL3Mu5_NHitQ10}","p");
  leg->AddEntry(h2,"#font[82]{HLT_HIL3Mu7_NHitQ10}","p");
  leg->AddEntry(h3,"#font[82]{HLT_HIL3Mu12}","p");
  leg->Draw();

  TLatex *la = new TLatex();
  la->SetTextSize(labelSize);
  la->SetTextFont(62);
  la->DrawLatexNDC(0.7,0.4,"Data");
  

  
    




}
