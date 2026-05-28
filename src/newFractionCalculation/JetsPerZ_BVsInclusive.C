


void stylizeHistograms_bJets(TH1D *h_C4,
			     TH1D *h_C3,
			     TH1D *h_C2,
			     TH1D *h_C1){


  h_C4->SetMarkerStyle(33);
  h_C3->SetMarkerStyle(21);
  h_C2->SetMarkerStyle(34);
  h_C1->SetMarkerStyle(47);


}

void stylizeHistograms_inclJets(TH1D *h_C4,
			     TH1D *h_C3,
			     TH1D *h_C2,
			     TH1D *h_C1){


  h_C4->SetMarkerStyle(27);
  h_C3->SetMarkerStyle(25);
  h_C2->SetMarkerStyle(28);
  h_C1->SetMarkerStyle(46);


}



void JetsPerZ_BVsInclusive(){

  TLine *li = new TLine();
  li->SetLineStyle(7);
  
  TFile *file_bJets = TFile::Open("./rootFiles/BJetPbPbToPP/Data/histograms_BJetPbPbToPP.root");
  TFile *file_inclJets = TFile::Open("./rootFiles/JetsPerZ/histograms_JetsPerZ_lightJets_rebinned.root");

  TH1D *h_C4_bJets, *h_C4_inclJets, *r_C4;
  TH1D *h_C3_bJets, *h_C3_inclJets, *r_C3;
  TH1D *h_C2_bJets, *h_C2_inclJets, *r_C2;
  TH1D *h_C1_bJets, *h_C1_inclJets, *r_C1;

  file_bJets->GetObject("bFraction_C4",h_C4_bJets);
  file_bJets->GetObject("bFraction_C3",h_C3_bJets);
  file_bJets->GetObject("bFraction_C2",h_C2_bJets);
  file_bJets->GetObject("bFraction_C1",h_C1_bJets);

  file_inclJets->GetObject("r_C4_r",h_C4_inclJets);
  file_inclJets->GetObject("r_C3_r",h_C3_inclJets);
  file_inclJets->GetObject("r_C2_r",h_C2_inclJets);
  file_inclJets->GetObject("r_C1_r",h_C1_inclJets);

  stylizeHistograms_bJets(h_C4_bJets,h_C3_bJets,h_C2_bJets,h_C1_bJets);
  stylizeHistograms_inclJets(h_C4_inclJets,h_C3_inclJets,h_C2_inclJets,h_C1_inclJets);

  r_C4 = (TH1D*) h_C4_bJets->Clone("r_C4");
  r_C4->Divide(h_C4_bJets,h_C4_inclJets,1,1,"");

  r_C3 = (TH1D*) h_C3_bJets->Clone("r_C3");
  r_C3->Divide(h_C3_bJets,h_C3_inclJets,1,1,"");

  r_C2 = (TH1D*) h_C2_bJets->Clone("r_C2");
  r_C2->Divide(h_C2_bJets,h_C2_inclJets,1,1,"");

  r_C1 = (TH1D*) h_C1_bJets->Clone("r_C1");
  r_C1->Divide(h_C1_bJets,h_C1_inclJets,1,1,"");


  TCanvas *canv_C4 = new TCanvas("canv_C4","canv_C4",700,700);
  canv_C4->cd();
  TPad *pad_C4_upper = new TPad("pad_C4_upper","pad_C4_upper",0,0.4,1,1);
  TPad *pad_C4_lower = new TPad("pad_C4_lower","pad_C4_lower",0,0,1,0.4);
  pad_C4_upper->SetLeftMargin(0.15);
  pad_C4_lower->SetLeftMargin(0.15);
  pad_C4_upper->SetBottomMargin(0.);
  pad_C4_lower->SetBottomMargin(0.15);
  pad_C4_upper->SetTopMargin(0.15);
  pad_C4_lower->SetTopMargin(0.);
  pad_C4_upper->Draw();
  pad_C4_lower->Draw();
  pad_C4_upper->cd();
  h_C4_bJets->SetTitleSize(0.055);
  h_C4_bJets->SetTitle("PbPb 50-80%");
  h_C4_bJets->GetYaxis()->SetTitleSize(0.048);
  h_C4_bJets->GetYaxis()->SetLabelSize(0.038);
  h_C4_bJets->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  h_C4_bJets->GetYaxis()->SetRangeUser(0,1.5);
  h_C4_bJets->GetXaxis()->SetRangeUser(80,300);
  h_C4_bJets->Draw("");
  h_C4_inclJets->Draw("same");
  TLegend *leg_C4 = new TLegend(0.18,0.05,0.35,0.2);
  leg_C4->SetBorderSize(0);
  leg_C4->SetTextSize(0.05);
  leg_C4->AddEntry(h_C4_bJets,"#it{b} jets");
  leg_C4->AddEntry(h_C4_inclJets,"inclusive jets");
  leg_C4->Draw();
  pad_C4_lower->cd();
  r_C4->GetYaxis()->SetTitleSize(0.068);
  r_C4->GetYaxis()->SetLabelSize(0.058);
  r_C4->GetXaxis()->SetTitleSize(0.068);
  r_C4->GetXaxis()->SetLabelSize(0.058);
  r_C4->GetYaxis()->SetRangeUser(0,2);
  r_C4->GetXaxis()->SetRangeUser(80,300);
  r_C4->GetYaxis()->SetTitle("#it{b} / inclusive");
  r_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C4->Draw();
  li->DrawLine(80,1,300,1);
  canv_C4->SaveAs("../../figures/JetsPerZ/JetsPerZ_BVsInclusive_C4.pdf");


  TCanvas *canv_C3 = new TCanvas("canv_C3","canv_C3",700,700);
  canv_C3->cd();
  TPad *pad_C3_upper = new TPad("pad_C3_upper","pad_C3_upper",0,0.4,1,1);
  TPad *pad_C3_lower = new TPad("pad_C3_lower","pad_C3_lower",0,0,1,0.4);
  pad_C3_upper->SetLeftMargin(0.15);
  pad_C3_lower->SetLeftMargin(0.15);
  pad_C3_upper->SetBottomMargin(0.);
  pad_C3_lower->SetBottomMargin(0.15);
  pad_C3_upper->SetTopMargin(0.15);
  pad_C3_lower->SetTopMargin(0.);
  pad_C3_upper->Draw();
  pad_C3_lower->Draw();
  pad_C3_upper->cd();
  h_C3_bJets->SetTitleSize(0.055);
  h_C3_bJets->SetTitle("PbPb 30-50%");
  h_C3_bJets->GetYaxis()->SetTitleSize(0.048);
  h_C3_bJets->GetYaxis()->SetLabelSize(0.038);
  h_C3_bJets->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  h_C3_bJets->GetYaxis()->SetRangeUser(0,1.5);
  h_C3_bJets->GetXaxis()->SetRangeUser(80,300);
  h_C3_bJets->Draw("");
  h_C3_inclJets->Draw("same");
  TLegend *leg_C3 = new TLegend(0.18,0.05,0.35,0.2);
  leg_C3->SetBorderSize(0);
  leg_C3->SetTextSize(0.05);
  leg_C3->AddEntry(h_C3_bJets,"#it{b} jets");
  leg_C3->AddEntry(h_C3_inclJets,"inclusive jets");
  leg_C3->Draw();
  pad_C3_lower->cd();
  r_C3->GetYaxis()->SetTitleSize(0.068);
  r_C3->GetYaxis()->SetLabelSize(0.058);
  r_C3->GetXaxis()->SetTitleSize(0.068);
  r_C3->GetXaxis()->SetLabelSize(0.058);
  r_C3->GetYaxis()->SetRangeUser(0,2);
  r_C3->GetXaxis()->SetRangeUser(80,300);
  r_C3->GetYaxis()->SetTitle("#it{b} / inclusive");
  r_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C3->Draw();
  li->DrawLine(80,1,300,1);
  canv_C3->SaveAs("../../figures/JetsPerZ/JetsPerZ_BVsInclusive_C3.pdf");


  TCanvas *canv_C2 = new TCanvas("canv_C2","canv_C2",700,700);
  canv_C2->cd();
  TPad *pad_C2_upper = new TPad("pad_C2_upper","pad_C2_upper",0,0.4,1,1);
  TPad *pad_C2_lower = new TPad("pad_C2_lower","pad_C2_lower",0,0,1,0.4);
  pad_C2_upper->SetLeftMargin(0.15);
  pad_C2_lower->SetLeftMargin(0.15);
  pad_C2_upper->SetBottomMargin(0.);
  pad_C2_lower->SetBottomMargin(0.15);
  pad_C2_upper->SetTopMargin(0.15);
  pad_C2_lower->SetTopMargin(0.);
  pad_C2_upper->Draw();
  pad_C2_lower->Draw();
  pad_C2_upper->cd();
  h_C2_bJets->SetTitleSize(0.055);
  h_C2_bJets->SetTitle("PbPb 30-50%");
  h_C2_bJets->GetYaxis()->SetTitleSize(0.048);
  h_C2_bJets->GetYaxis()->SetLabelSize(0.038);
  h_C2_bJets->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  h_C2_bJets->GetYaxis()->SetRangeUser(0,1.5);
  h_C2_bJets->GetXaxis()->SetRangeUser(80,300);
  h_C2_bJets->Draw("");
  h_C2_inclJets->Draw("same");
  TLegend *leg_C2 = new TLegend(0.18,0.05,0.35,0.2);
  leg_C2->SetBorderSize(0);
  leg_C2->SetTextSize(0.05);
  leg_C2->AddEntry(h_C2_bJets,"#it{b} jets");
  leg_C2->AddEntry(h_C2_inclJets,"inclusive jets");
  leg_C2->Draw();
  pad_C2_lower->cd();
  r_C2->GetYaxis()->SetTitleSize(0.068);
  r_C2->GetYaxis()->SetLabelSize(0.058);
  r_C2->GetXaxis()->SetTitleSize(0.068);
  r_C2->GetXaxis()->SetLabelSize(0.058);
  r_C2->GetYaxis()->SetRangeUser(0,2);
  r_C2->GetXaxis()->SetRangeUser(80,300);
  r_C2->GetYaxis()->SetTitle("#it{b} / inclusive");
  r_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C2->Draw();
  li->DrawLine(80,1,300,1);
  canv_C2->SaveAs("../../figures/JetsPerZ/JetsPerZ_BVsInclusive_C2.pdf");


  TCanvas *canv_C1 = new TCanvas("canv_C1","canv_C1",700,700);
  canv_C1->cd();
  TPad *pad_C1_upper = new TPad("pad_C1_upper","pad_C1_upper",0,0.4,1,1);
  TPad *pad_C1_lower = new TPad("pad_C1_lower","pad_C1_lower",0,0,1,0.4);
  pad_C1_upper->SetLeftMargin(0.15);
  pad_C1_lower->SetLeftMargin(0.15);
  pad_C1_upper->SetBottomMargin(0.);
  pad_C1_lower->SetBottomMargin(0.15);
  pad_C1_upper->SetTopMargin(0.15);
  pad_C1_lower->SetTopMargin(0.);
  pad_C1_upper->Draw();
  pad_C1_lower->Draw();
  pad_C1_upper->cd();
  h_C1_bJets->SetTitleSize(0.055);
  h_C1_bJets->SetTitle("PbPb 30-50%");
  h_C1_bJets->GetYaxis()->SetTitleSize(0.048);
  h_C1_bJets->GetYaxis()->SetLabelSize(0.038);
  h_C1_bJets->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  h_C1_bJets->GetYaxis()->SetRangeUser(0,1.5);
  h_C1_bJets->GetXaxis()->SetRangeUser(80,300);
  h_C1_bJets->Draw("");
  h_C1_inclJets->Draw("same");
  TLegend *leg_C1 = new TLegend(0.18,0.05,0.35,0.2);
  leg_C1->SetBorderSize(0);
  leg_C1->SetTextSize(0.05);
  leg_C1->AddEntry(h_C1_bJets,"#it{b} jets");
  leg_C1->AddEntry(h_C1_inclJets,"inclusive jets");
  leg_C1->Draw();
  pad_C1_lower->cd();
  r_C1->GetYaxis()->SetTitleSize(0.068);
  r_C1->GetYaxis()->SetLabelSize(0.058);
  r_C1->GetXaxis()->SetTitleSize(0.068);
  r_C1->GetXaxis()->SetLabelSize(0.058);
  r_C1->GetYaxis()->SetRangeUser(0,2);
  r_C1->GetXaxis()->SetRangeUser(80,300);
  r_C1->GetYaxis()->SetTitle("#it{b} / inclusive");
  r_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C1->Draw();
  li->DrawLine(80,1,300,1);
  canv_C1->SaveAs("../../figures/JetsPerZ/JetsPerZ_BVsInclusive_C1.pdf");

  

    
  



}
