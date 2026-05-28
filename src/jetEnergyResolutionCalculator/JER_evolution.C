

void stylizeHistograms(TH1D *h_pp,
		       TH1D *h_C4,
		       TH1D *h_C3,
		       TH1D *h_C2,
		       TH1D *h_C1){


  double lineWidth = 2.0;

  h_pp->SetLineWidth(lineWidth);
  h_C4->SetLineWidth(lineWidth);
  h_C3->SetLineWidth(lineWidth);
  h_C2->SetLineWidth(lineWidth);
  h_C1->SetLineWidth(lineWidth);

  h_pp->SetLineColor(kBlack);
  h_C4->SetLineColor(kBlue+1);
  h_C3->SetLineColor(kRed-4);
  h_C2->SetLineColor(kGreen+2);
  h_C1->SetLineColor(kMagenta-9);



}

double JER_fit(double *x, double *par){
  double xx = x[0];
  //double fitval = par[0]*TMath::Exp(-1.0*par[1]*x[0]) + par[2]*TMath::Exp(-1.0*par[3]*x[0]) + par[4]*TMath::Exp(-1.0*par[5]*x[0])+par[6];
  double fitval = TMath::Sqrt(par[0]*par[0] + par[1]*par[1]/x[0] + par[2]*par[2]/(x[0]*x[0]))  ;
  return fitval;
}


void JER_evolution(){

  TFile *file_JER_pp, *file_JER_C4, *file_JER_C3, *file_JER_C2, *file_JER_C1;
  TFile *file_JES_pp, *file_JES_C4, *file_JES_C3, *file_JES_C2, *file_JES_C1;

  file_JER_pp = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_pp.root");
  file_JER_C4 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_C4.root");
  file_JER_C3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_C3.root");
  file_JER_C2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_C2.root");
  file_JER_C1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_C1.root");

  file_JES_pp = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_pp.root");
  file_JES_C4 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_C4.root");
  file_JES_C3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_C3.root");
  file_JES_C2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_C2.root");
  file_JES_C1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_C1.root");

  TH1D *JER_b_pp, *JER_b_C4, *JER_b_C3, *JER_b_C2, *JER_b_C1;
  TH1D *JER_i_pp, *JER_i_C4, *JER_i_C3, *JER_i_C2, *JER_i_C1;
  TH1D *r_JER_b_C4, *r_JER_b_C3, *r_JER_b_C2, *r_JER_b_C1;
  TH1D *r_JER_i_C4, *r_JER_i_C3, *r_JER_i_C2, *r_JER_i_C1;

  TH1D *JES_b_pp, *JES_b_C4, *JES_b_C3, *JES_b_C2, *JES_b_C1;
  TH1D *JES_i_pp, *JES_i_C4, *JES_i_C3, *JES_i_C2, *JES_i_C1;
  TH1D *r_JES_b_C4, *r_JES_b_C3, *r_JES_b_C2, *r_JES_b_C1;
  TH1D *r_JES_i_C4, *r_JES_i_C3, *r_JES_i_C2, *r_JES_i_C1;

  file_JER_pp->GetObject("JER_result_b",JER_b_pp);
  file_JER_C4->GetObject("JER_result_b",JER_b_C4);
  file_JER_C3->GetObject("JER_result_b",JER_b_C3);
  file_JER_C2->GetObject("JER_result_b",JER_b_C2);
  file_JER_C1->GetObject("JER_result_b",JER_b_C1);

  file_JER_pp->GetObject("JER_result_i",JER_i_pp);
  file_JER_C4->GetObject("JER_result_i",JER_i_C4);
  file_JER_C3->GetObject("JER_result_i",JER_i_C3);
  file_JER_C2->GetObject("JER_result_i",JER_i_C2);
  file_JER_C1->GetObject("JER_result_i",JER_i_C1);

  file_JES_pp->GetObject("JES_result_b",JES_b_pp);
  file_JES_C4->GetObject("JES_result_b",JES_b_C4);
  file_JES_C3->GetObject("JES_result_b",JES_b_C3);
  file_JES_C2->GetObject("JES_result_b",JES_b_C2);
  file_JES_C1->GetObject("JES_result_b",JES_b_C1);

  file_JES_pp->GetObject("JES_result_i",JES_i_pp);
  file_JES_C4->GetObject("JES_result_i",JES_i_C4);
  file_JES_C3->GetObject("JES_result_i",JES_i_C3);
  file_JES_C2->GetObject("JES_result_i",JES_i_C2);
  file_JES_C1->GetObject("JES_result_i",JES_i_C1);

  stylizeHistograms(JER_b_pp,JER_b_C4,JER_b_C3,JER_b_C2,JER_b_C1);
  stylizeHistograms(JER_i_pp,JER_i_C4,JER_i_C3,JER_i_C2,JER_i_C1);
  stylizeHistograms(JES_b_pp,JES_b_C4,JES_b_C3,JES_b_C2,JES_b_C1);
  stylizeHistograms(JES_i_pp,JES_i_C4,JES_i_C3,JES_i_C2,JES_i_C1);

  r_JER_b_C4 = (TH1D*) JER_b_C4->Clone("r_JER_b_C4");
  r_JER_b_C3 = (TH1D*) JER_b_C3->Clone("r_JER_b_C3");
  r_JER_b_C2 = (TH1D*) JER_b_C2->Clone("r_JER_b_C2");
  r_JER_b_C1 = (TH1D*) JER_b_C1->Clone("r_JER_b_C1");
  
  r_JER_b_C4->Divide(JER_b_C4,JER_b_pp,1,1,"");
  r_JER_b_C3->Divide(JER_b_C3,JER_b_pp,1,1,"");
  r_JER_b_C2->Divide(JER_b_C2,JER_b_pp,1,1,"");
  r_JER_b_C1->Divide(JER_b_C1,JER_b_pp,1,1,"");

  r_JER_i_C4 = (TH1D*) JER_i_C4->Clone("r_JER_i_C4");
  r_JER_i_C3 = (TH1D*) JER_i_C3->Clone("r_JER_i_C3");
  r_JER_i_C2 = (TH1D*) JER_i_C2->Clone("r_JER_i_C2");
  r_JER_i_C1 = (TH1D*) JER_i_C1->Clone("r_JER_i_C1");
  
  r_JER_i_C4->Divide(JER_i_C4,JER_i_pp,1,1,"");
  r_JER_i_C3->Divide(JER_i_C3,JER_i_pp,1,1,"");
  r_JER_i_C2->Divide(JER_i_C2,JER_i_pp,1,1,"");
  r_JER_i_C1->Divide(JER_i_C1,JER_i_pp,1,1,"");

  r_JES_b_C4 = (TH1D*) JES_b_C4->Clone("r_JES_b_C4");
  r_JES_b_C3 = (TH1D*) JES_b_C3->Clone("r_JES_b_C3");
  r_JES_b_C2 = (TH1D*) JES_b_C2->Clone("r_JES_b_C2");
  r_JES_b_C1 = (TH1D*) JES_b_C1->Clone("r_JES_b_C1");
  
  r_JES_b_C4->Divide(JES_b_C4,JES_b_pp,1,1,"");
  r_JES_b_C3->Divide(JES_b_C3,JES_b_pp,1,1,"");
  r_JES_b_C2->Divide(JES_b_C2,JES_b_pp,1,1,"");
  r_JES_b_C1->Divide(JES_b_C1,JES_b_pp,1,1,"");

  r_JES_i_C4 = (TH1D*) JES_i_C4->Clone("r_JES_i_C4");
  r_JES_i_C3 = (TH1D*) JES_i_C3->Clone("r_JES_i_C3");
  r_JES_i_C2 = (TH1D*) JES_i_C2->Clone("r_JES_i_C2");
  r_JES_i_C1 = (TH1D*) JES_i_C1->Clone("r_JES_i_C1");
  
  r_JES_i_C4->Divide(JES_i_C4,JES_i_pp,1,1,"");
  r_JES_i_C3->Divide(JES_i_C3,JES_i_pp,1,1,"");
  r_JES_i_C2->Divide(JES_i_C2,JES_i_pp,1,1,"");
  r_JES_i_C1->Divide(JES_i_C1,JES_i_pp,1,1,"");



  double leftMargin = 0.15;
  double bottomMargin = 0.15;
  double topMargin = 0.15;
  double titleSize = 0.06;
  double labelSize = 0.05;
  double JER_min = 0.05;
  double JER_max = 0.35;
  double JES_min = 0.85;
  double JES_max = 1.3;
  TLine *li = new TLine();
  li->SetLineStyle(7);
  TLatex *la = new TLatex();
  la->SetTextFont(42);
  double textSize = 0.06;
  la->SetTextSize(textSize);

  TLegend *leg = new TLegend(0.5,0.4,0.88,0.68);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.8*textSize);
  leg->AddEntry(JER_i_pp,"PYTHIA");
  leg->AddEntry(JER_i_C4,"PYTHIA+HYDJET 50-80%");
  leg->AddEntry(JER_i_C3,"PYTHIA+HYDJET 30-50%");
  leg->AddEntry(JER_i_C2,"PYTHIA+HYDJET 10-30%");
  leg->AddEntry(JER_i_C1,"PYTHIA+HYDJET 0-10%");
  
  TCanvas *canv_JER_i = new TCanvas("canv_JER_i","inclusive jets JER",700,700);
  canv_JER_i->cd();
  TPad *pad_JER_i_low = new TPad("pad_JER_i_low","pad_JER_i_low",0,0,1,0.5);
  TPad *pad_JER_i_high = new TPad("pad_JER_i_high","pad_JER_i_high",0,0.5,1,1);
  pad_JER_i_low->SetLeftMargin(leftMargin);
  pad_JER_i_high->SetLeftMargin(leftMargin);
  pad_JER_i_low->SetBottomMargin(bottomMargin);
  pad_JER_i_high->SetBottomMargin(0.);
  pad_JER_i_low->SetTopMargin(0.);
  pad_JER_i_high->SetTopMargin(topMargin);
  pad_JER_i_low->Draw();
  pad_JER_i_high->Draw();
  pad_JER_i_high->cd();
  JER_i_pp->SetStats(0);
  JER_i_pp->SetTitle("");
  JER_i_pp->GetYaxis()->SetTitleSize(titleSize);
  JER_i_pp->GetYaxis()->SetLabelSize(labelSize);
  JER_i_pp->GetYaxis()->SetTitle("#it{#sigma}(#it{p}_{T}^{recoJet}/#it{p}_{T}^{genJet})");
  JER_i_pp->GetYaxis()->SetRangeUser(JER_min,JER_max);
  JER_i_pp->Draw();
  JER_i_C4->Draw("same");
  JER_i_C3->Draw("same");
  JER_i_C2->Draw("same");
  JER_i_C1->Draw("same");
  la->DrawLatexNDC(0.6,0.75,"inclusive jets");
  leg->Draw();
  pad_JER_i_low->cd();
  r_JER_i_C4->SetStats(0);
  r_JER_i_C4->SetTitle("");
  r_JER_i_C4->GetYaxis()->SetTitleSize(titleSize);
  r_JER_i_C4->GetYaxis()->SetLabelSize(labelSize);
  r_JER_i_C4->GetYaxis()->SetTitle("#it{#sigma}(PbPb) / #it{#sigma}(pp)");
  r_JER_i_C4->GetXaxis()->SetTitleSize(titleSize);
  r_JER_i_C4->GetXaxis()->SetLabelSize(labelSize);
  r_JER_i_C4->GetXaxis()->SetTitle("#it{p}_{T}^{genJet} [GeV]");
  r_JER_i_C4->GetYaxis()->SetRangeUser(0.8,2.7);
  r_JER_i_C4->Draw();
  r_JER_i_C3->Draw("same");
  r_JER_i_C2->Draw("same");
  r_JER_i_C1->Draw("same");
  li->DrawLine(60,1,500,1);

  /////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_JER_b = new TCanvas("canv_JER_b","b-jets JER",700,700);
  canv_JER_b->cd();
  TPad *pad_JER_b_low = new TPad("pad_JER_b_low","pad_JER_b_low",0,0,1,0.5);
  TPad *pad_JER_b_high = new TPad("pad_JER_b_high","pad_JER_b_high",0,0.5,1,1);
  pad_JER_b_low->SetLeftMargin(leftMargin);
  pad_JER_b_high->SetLeftMargin(leftMargin);
  pad_JER_b_low->SetBottomMargin(bottomMargin);
  pad_JER_b_high->SetBottomMargin(0.);
  pad_JER_b_low->SetTopMargin(0.);
  pad_JER_b_high->SetTopMargin(topMargin);
  pad_JER_b_low->Draw();
  pad_JER_b_high->Draw();
  pad_JER_b_high->cd();
  JER_b_pp->SetStats(0);
  JER_b_pp->SetTitle("");
  JER_b_pp->GetYaxis()->SetTitleSize(titleSize);
  JER_b_pp->GetYaxis()->SetLabelSize(labelSize);
  JER_b_pp->GetYaxis()->SetTitle("#it{#sigma}(#it{p}_{T}^{recoJet}/#it{p}_{T}^{genJet})");
  JER_b_pp->GetYaxis()->SetRangeUser(JER_min,JER_max);
  JER_b_pp->Draw();
  JER_b_C4->Draw("same");
  JER_b_C3->Draw("same");
  JER_b_C2->Draw("same");
  JER_b_C1->Draw("same");
  la->DrawLatexNDC(0.6,0.75,"#it{b}-jets");
  leg->Draw();
  pad_JER_b_low->cd();
  r_JER_b_C4->SetStats(0);
  r_JER_b_C4->SetTitle("");
  r_JER_b_C4->GetYaxis()->SetTitleSize(titleSize);
  r_JER_b_C4->GetYaxis()->SetLabelSize(labelSize);
  r_JER_b_C4->GetYaxis()->SetTitle("#it{#sigma}(PbPb) / #it{#sigma}(pp)");
  r_JER_b_C4->GetXaxis()->SetTitleSize(titleSize);
  r_JER_b_C4->GetXaxis()->SetLabelSize(labelSize);
  r_JER_b_C4->GetXaxis()->SetTitle("#it{p}_{T}^{genJet} [GeV]");
  r_JER_b_C4->GetYaxis()->SetRangeUser(0.8,2.7);
  r_JER_b_C4->Draw();
  r_JER_b_C3->Draw("same");
  r_JER_b_C2->Draw("same");
  r_JER_b_C1->Draw("same");
  li->DrawLine(60,1,500,1);

  //////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_JES_i = new TCanvas("canv_JES_i","inclusive jets JES",700,700);
  canv_JES_i->cd();
  TPad *pad_JES_i_low = new TPad("pad_JES_i_low","pad_JES_i_low",0,0,1,0.5);
  TPad *pad_JES_i_high = new TPad("pad_JES_i_high","pad_JES_i_high",0,0.5,1,1);
  pad_JES_i_low->SetLeftMargin(leftMargin);
  pad_JES_i_high->SetLeftMargin(leftMargin);
  pad_JES_i_low->SetBottomMargin(bottomMargin);
  pad_JES_i_high->SetBottomMargin(0.);
  pad_JES_i_low->SetTopMargin(0.);
  pad_JES_i_high->SetTopMargin(topMargin);
  pad_JES_i_low->Draw();
  pad_JES_i_high->Draw();
  pad_JES_i_high->cd();
  JES_i_pp->SetStats(0);
  JES_i_pp->SetTitle("");
  JES_i_pp->GetYaxis()->SetTitleSize(titleSize);
  JES_i_pp->GetYaxis()->SetLabelSize(labelSize);
  JES_i_pp->GetYaxis()->SetTitle("#it{#mu}(#it{p}_{T}^{recoJet}/#it{p}_{T}^{genJet})");
  JES_i_pp->GetYaxis()->SetRangeUser(JES_min,JES_max);
  JES_i_pp->Draw();
  JES_i_C4->Draw("same");
  JES_i_C3->Draw("same");
  JES_i_C2->Draw("same");
  JES_i_C1->Draw("same");
  la->DrawLatexNDC(0.6,0.75,"inclusive jets");
  leg->Draw();
  pad_JES_i_low->cd();
  r_JES_i_C4->SetStats(0);
  r_JES_i_C4->SetTitle("");
  r_JES_i_C4->GetYaxis()->SetTitleSize(titleSize);
  r_JES_i_C4->GetYaxis()->SetLabelSize(labelSize);
  r_JES_i_C4->GetYaxis()->SetTitle("#it{#mu}(PbPb) / #it{#mu}(pp)");
  r_JES_i_C4->GetXaxis()->SetTitleSize(titleSize);
  r_JES_i_C4->GetXaxis()->SetLabelSize(labelSize);
  r_JES_i_C4->GetXaxis()->SetTitle("#it{p}_{T}^{genJet} [GeV]");
  r_JES_i_C4->GetYaxis()->SetRangeUser(0.9,1.1);
  r_JES_i_C4->Draw();
  r_JES_i_C3->Draw("same");
  r_JES_i_C2->Draw("same");
  r_JES_i_C1->Draw("same");
  li->DrawLine(60,1,500,1);

  //////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_JES_b = new TCanvas("canv_JES_b","b-jets JES",700,700);
  canv_JES_b->cd();
  TPad *pad_JES_b_low = new TPad("pad_JES_b_low","pad_JES_b_low",0,0,1,0.5);
  TPad *pad_JES_b_high = new TPad("pad_JES_b_high","pad_JES_b_high",0,0.5,1,1);
  pad_JES_b_low->SetLeftMargin(leftMargin);
  pad_JES_b_high->SetLeftMargin(leftMargin);
  pad_JES_b_low->SetBottomMargin(bottomMargin);
  pad_JES_b_high->SetBottomMargin(0.);
  pad_JES_b_low->SetTopMargin(0.);
  pad_JES_b_high->SetTopMargin(topMargin);
  pad_JES_b_low->Draw();
  pad_JES_b_high->Draw();
  pad_JES_b_high->cd();
  JES_b_pp->SetStats(0);
  JES_b_pp->SetTitle("");
  JES_b_pp->GetYaxis()->SetTitleSize(titleSize);
  JES_b_pp->GetYaxis()->SetLabelSize(labelSize);
  JES_b_pp->GetYaxis()->SetTitle("#it{#mu}(#it{p}_{T}^{recoJet}/#it{p}_{T}^{genJet})");
  JES_b_pp->GetYaxis()->SetRangeUser(JES_min,JES_max);
  JES_b_pp->Draw();
  JES_b_C4->Draw("same");
  JES_b_C3->Draw("same");
  JES_b_C2->Draw("same");
  JES_b_C1->Draw("same");
  la->DrawLatexNDC(0.6,0.75,"#it{b}-jets");
  leg->Draw();
  pad_JES_b_low->cd();
  r_JES_b_C4->SetStats(0);
  r_JES_b_C4->SetTitle("");
  r_JES_b_C4->GetYaxis()->SetTitleSize(titleSize);
  r_JES_b_C4->GetYaxis()->SetLabelSize(labelSize);
  r_JES_b_C4->GetYaxis()->SetTitle("#it{#mu}(PbPb) / #it{#mu}(pp)");
  r_JES_b_C4->GetXaxis()->SetTitleSize(titleSize);
  r_JES_b_C4->GetXaxis()->SetLabelSize(labelSize);
  r_JES_b_C4->GetXaxis()->SetTitle("#it{p}_{T}^{genJet} [GeV]");
  r_JES_b_C4->GetYaxis()->SetRangeUser(0.9,1.1);
  r_JES_b_C4->Draw();
  r_JES_b_C3->Draw("same");
  r_JES_b_C2->Draw("same");
  r_JES_b_C1->Draw("same");
  li->DrawLine(60,1,500,1);

  ////////////////////////////////////////////////////////////////////////////////////////////

  canv_JER_i->SaveAs("./figures/JER_evolution_inclJets.pdf");
  canv_JER_b->SaveAs("./figures/JER_evolution_bJets.pdf");
  canv_JES_i->SaveAs("./figures/JES_evolution_inclJets.pdf");
  canv_JES_b->SaveAs("./figures/JES_evolution_bJets.pdf");

  ////////////////////////////////////////////////////////////////////////////////////////////

  TF1 *func = new TF1("func",JER_fit,30.,500.,3);
  std::cout << "\n fitting pp: \n";
  JER_i_pp->Fit(func,"M R WL","",30,500);
  std::cout << "\n fitting C4: \n";
  JER_i_C4->Fit(func,"M R WL","",30,500);
  std::cout << "\n fitting C3: \n";
  JER_i_C3->Fit(func,"M R WL","",30,500);
  std::cout << "\n fitting C2: \n";
  JER_i_C2->Fit(func,"M R WL","",30,500);
  std::cout << "\n fitting C1: \n";
  JER_i_C1->Fit(func,"M R WL","",30,500);

}
