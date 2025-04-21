#include "../../../headers/functions/divideByBinwidth.h"
void bGS_compare(){

  TLatex *la = new TLatex();
  
  //TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/spring2024scans/PYTHIAHYDJET_DiJet_withGS_scan_mu5_pThat15_removeHYDJETjets_vzAndHiBinReweight.root");
  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/spring2024scans/PYTHIA_DiJet_withGS_scan_mu5_pThat15_removeHYDJETjets_vzReweight.root");

  TH2D *H1, *H2, *H3;

  // f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2",H1);
  // f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J3",H2);
  // f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J4",H3);

  f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J2",H1);
  f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J3",H2);
  f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J4",H3);

  TH1D *b_nom_1, *b_nom_2, *b_nom_3;
  TH1D *bbar_nom_1, *bbar_nom_2, *bbar_nom_3;
  TH1D *b_GS_1, *b_GS_2, *b_GS_3;
  TH1D *light_1, *light_2, *light_3;
  TH1D *glu_1, *glu_2, *glu_3;

  TH1D *binFinder = (TH1D*) H1->ProjectionY("binFinder");
  double smallShift = 0.01;

  b_nom_1 = (TH1D*) H1->ProjectionX("b_nom_1",binFinder->FindBin(5. + smallShift), binFinder->FindBin(6. - smallShift));
  bbar_nom_1 = (TH1D*) H1->ProjectionX("bbar_nom_1",binFinder->FindBin(-5. + smallShift), binFinder->FindBin(-4. - smallShift));
  b_GS_1 = (TH1D*) H1->ProjectionX("b_GS_1",binFinder->FindBin(17. + smallShift), binFinder->FindBin(18. - smallShift));
  b_nom_1->Add(bbar_nom_1);
  light_1 = (TH1D*) H1->ProjectionX("light_1",binFinder->FindBin(-3. + smallShift), binFinder->FindBin(3. - smallShift));
  glu_1 = (TH1D*) H1->ProjectionX("glu_1",binFinder->FindBin(21. + smallShift), binFinder->FindBin(22. - smallShift));
  light_1->Add(glu_1);

  b_nom_2 = (TH1D*) H2->ProjectionX("b_nom_2",binFinder->FindBin(5. + smallShift), binFinder->FindBin(6. - smallShift));
  bbar_nom_2 = (TH1D*) H2->ProjectionX("bbar_nom_2",binFinder->FindBin(-5. + smallShift), binFinder->FindBin(-4. - smallShift));
  b_GS_2 = (TH1D*) H2->ProjectionX("b_GS_2",binFinder->FindBin(17. + smallShift), binFinder->FindBin(18. - smallShift));
  b_nom_2->Add(bbar_nom_2);
  light_2 = (TH1D*) H2->ProjectionX("light_2",binFinder->FindBin(-3. + smallShift), binFinder->FindBin(3. - smallShift));
  glu_2 = (TH1D*) H2->ProjectionX("glu_2",binFinder->FindBin(21. + smallShift), binFinder->FindBin(22. - smallShift));
  light_2->Add(glu_2);

  b_nom_3 = (TH1D*) H3->ProjectionX("b_nom_3",binFinder->FindBin(5. + smallShift), binFinder->FindBin(6. - smallShift));
  bbar_nom_3 = (TH1D*) H3->ProjectionX("bbar_nom_3",binFinder->FindBin(-5. + smallShift), binFinder->FindBin(-4. - smallShift));
  b_GS_3 = (TH1D*) H3->ProjectionX("b_GS_3",binFinder->FindBin(17. + smallShift), binFinder->FindBin(18. - smallShift));
  b_nom_3->Add(bbar_nom_3);
  light_3 = (TH1D*) H3->ProjectionX("light_3",binFinder->FindBin(-3. + smallShift), binFinder->FindBin(3. - smallShift));
  glu_3 = (TH1D*) H3->ProjectionX("glu_3",binFinder->FindBin(21. + smallShift), binFinder->FindBin(22. - smallShift));
  light_3->Add(glu_3);


  

  

  // rebin
  const int M = 12;
  double muRelPtAxis[M] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.5,1.8,2.4,3.5,5.0}; // M = 11
  TH1D *b_nom_1_R = (TH1D*) b_nom_1->Rebin(M-1,"b_nom_1_R",muRelPtAxis);
  TH1D *b_nom_2_R = (TH1D*) b_nom_2->Rebin(M-1,"b_nom_2_R",muRelPtAxis);
  TH1D *b_nom_3_R = (TH1D*) b_nom_3->Rebin(M-1,"b_nom_3_R",muRelPtAxis);
  TH1D *b_GS_1_R = (TH1D*) b_GS_1->Rebin(M-1,"b_GS_1_R",muRelPtAxis);
  TH1D *b_GS_2_R = (TH1D*) b_GS_2->Rebin(M-1,"b_GS_2_R",muRelPtAxis);
  TH1D *b_GS_3_R = (TH1D*) b_GS_3->Rebin(M-1,"b_GS_3_R",muRelPtAxis);
  TH1D *light_1_R = (TH1D*) light_1->Rebin(M-1,"light_1_R",muRelPtAxis);
  TH1D *light_2_R = (TH1D*) light_2->Rebin(M-1,"light_2_R",muRelPtAxis);
  TH1D *light_3_R = (TH1D*) light_3->Rebin(M-1,"light_3_R",muRelPtAxis);
  
  // stylize
  light_1_R->SetLineColor(kBlack);
  light_2_R->SetLineColor(kBlack);
  light_3_R->SetLineColor(kBlack);
  
  b_nom_1_R->SetLineColor(kBlue-4);
  b_nom_2_R->SetLineColor(kBlue-4);
  b_nom_3_R->SetLineColor(kBlue-4);

  b_GS_1_R->SetLineColor(kRed-4);
  b_GS_2_R->SetLineColor(kRed-4);
  b_GS_3_R->SetLineColor(kRed-4);

  b_nom_1_R->SetLineWidth(3);
  b_nom_2_R->SetLineWidth(3);
  b_nom_3_R->SetLineWidth(3);

  b_GS_1_R->SetLineWidth(3);
  b_GS_2_R->SetLineWidth(3);
  b_GS_3_R->SetLineWidth(3);

  light_1_R->SetLineWidth(3);
  light_2_R->SetLineWidth(3);
  light_3_R->SetLineWidth(3);

  // divide by binwidth
  divideByBinwidth(b_nom_1_R);
  divideByBinwidth(b_GS_1_R);
  divideByBinwidth(b_nom_2_R);
  divideByBinwidth(b_GS_2_R);
  divideByBinwidth(b_nom_3_R);
  divideByBinwidth(b_GS_3_R);
  divideByBinwidth(light_1_R);
  divideByBinwidth(light_2_R);
  divideByBinwidth(light_3_R);


  double f_bGS_1 = b_GS_1_R->Integral() / (b_GS_1_R->Integral() + b_nom_1_R->Integral());
  double f_bGS_2 = b_GS_2_R->Integral() / (b_GS_2_R->Integral() + b_nom_2_R->Integral());
  double f_bGS_3 = b_GS_3_R->Integral() / (b_GS_3_R->Integral() + b_nom_3_R->Integral());

  double f_nom_1 = 1. - f_bGS_1;
  double f_nom_2 = 1. - f_bGS_2;
  double f_nom_3 = 1. - f_bGS_3;


  b_nom_1_R->SetFillColorAlpha(kBlue-4,0.6);
  b_GS_1_R->SetFillColorAlpha(kRed-4,0.6);
  b_nom_2_R->SetFillColorAlpha(kBlue-4,0.6);
  b_GS_2_R->SetFillColorAlpha(kRed-4,0.6);
  b_nom_3_R->SetFillColorAlpha(kBlue-4,0.6);
  b_GS_3_R->SetFillColorAlpha(kRed-4,0.6);
  THStack *stack1 = new THStack("stack1","");
  THStack *stack2 = new THStack("stack2","");
  THStack *stack3 = new THStack("stack3","");
  stack1->Add(b_nom_1_R);
  stack1->Add(b_GS_1_R);
  stack2->Add(b_nom_2_R);
  stack2->Add(b_GS_2_R);
  stack3->Add(b_nom_3_R);
  stack3->Add(b_GS_3_R);

  la->SetTextSize(0.045);

  TCanvas *canv2 = new TCanvas("canv2","canv2",1400,700);
  canv2->Divide(3,1);
  canv2->cd(1);
  stack1->Draw("hist");
  stack1->GetXaxis()->SetTitleSize(0.045);
  stack1->GetYaxis()->SetTitleSize(0.045);
  stack1->GetXaxis()->SetLabelSize(0.036);
  stack1->GetYaxis()->SetLabelSize(0.036);
  stack1->SetTitle("PYTHIA  60 < #it{p}_{T}^{jet} < 80 GeV");
  stack1->GetYaxis()->SetTitle("Weighted entries");
  stack1->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.5,0.7,Form("#it{f}_{#it{b}}^{GS} = %2.2f percent",100*f_bGS_1));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.5,0.62,Form("#it{f}_{#it{b}}^{nom} = %2.2f percent",100*f_nom_1)); 
  canv2->cd(2);
  stack2->Draw("hist");
  stack2->GetXaxis()->SetTitleSize(0.045);
  stack2->GetYaxis()->SetTitleSize(0.045);
  stack2->GetXaxis()->SetLabelSize(0.036);
  stack2->GetYaxis()->SetLabelSize(0.036);
  stack2->SetTitle("PYTHIA  80 < #it{p}_{T}^{jet} < 120 GeV");
  stack2->GetYaxis()->SetTitle("Weighted entries");
  stack2->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.5,0.7,Form("#it{f}_{#it{b}}^{GS} = %2.2f percent",100*f_bGS_2));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.5,0.62,Form("#it{f}_{#it{b}}^{nom} = %2.2f percent",100*f_nom_2));
  canv2->cd(3);
  stack3->Draw("hist");
  stack3->GetXaxis()->SetTitleSize(0.045);
  stack3->GetYaxis()->SetTitleSize(0.045);
  stack3->GetXaxis()->SetLabelSize(0.036);
  stack3->GetYaxis()->SetLabelSize(0.036);
  stack3->SetTitle("PYTHIA  120 < #it{p}_{T}^{jet} < 200 GeV");
  stack3->GetYaxis()->SetTitle("Weighted entries");
  stack3->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.5,0.7,Form("#it{f}_{#it{b}}^{GS} = %2.2f percent",100*f_bGS_3));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.5,0.62,Form("#it{f}_{#it{b}}^{nom} = %2.2f percent",100*f_nom_3));
  


  


  // scale all by integral
  b_nom_1_R->Scale(1./b_nom_1_R->Integral());
  b_nom_2_R->Scale(1./b_nom_2_R->Integral());
  b_nom_3_R->Scale(1./b_nom_3_R->Integral());

  b_GS_1_R->Scale(1./b_GS_1_R->Integral());
  b_GS_2_R->Scale(1./b_GS_2_R->Integral());
  b_GS_3_R->Scale(1./b_GS_3_R->Integral());

  light_1_R->Scale(1./light_1_R->Integral());
  light_2_R->Scale(1./light_2_R->Integral());
  light_3_R->Scale(1./light_3_R->Integral());

  // calculate ratio
  TH1D *r_1, *r_2, *r_3;
  r_1 = (TH1D*) b_GS_1_R->Clone("r_1");
  r_1->Divide(b_GS_1_R,light_1_R,1,1,"");

  r_2 = (TH1D*) b_GS_2_R->Clone("r_2");
  r_2->Divide(b_GS_2_R,light_2_R,1,1,"");

  r_3 = (TH1D*) b_GS_3_R->Clone("r_3");
  r_3->Divide(b_GS_3_R,light_3_R,1,1,"");

  TH1D *R_1, *R_2, *R_3;
  R_1 = (TH1D*) b_nom_1_R->Clone("R_1");
  R_1->Divide(b_nom_1_R,light_1_R,1,1,"");

  R_2 = (TH1D*) b_nom_2_R->Clone("R_2");
  R_2->Divide(b_nom_2_R,light_2_R,1,1,"");

  R_3 = (TH1D*) b_nom_3_R->Clone("R_3");
  R_3->Divide(b_nom_3_R,light_3_R,1,1,"");

  TLine *li = new TLine();
  li->SetLineStyle(7);
  TCanvas *canv = new TCanvas("canv","canv",1400,700);
  canv->Divide(3,1);
  canv->cd(1);
  TPad *pad_1_1 = new TPad("pad_1_1","pad_1_1",0,0.4,1,1);
  TPad *pad_1_2 = new TPad("pad_1_2","pad_1_2",0,0,1,0.4);
  pad_1_1->SetLeftMargin(0.2);
  pad_1_1->SetTopMargin(0.1);
  pad_1_1->SetRightMargin(0.2);
  pad_1_1->SetBottomMargin(0.0);
  pad_1_2->SetLeftMargin(0.2);
  pad_1_2->SetTopMargin(0.0);
  pad_1_2->SetRightMargin(0.2);
  pad_1_2->SetBottomMargin(0.2);
  pad_1_1->Draw();
  pad_1_2->Draw();
  pad_1_1->cd();
  b_nom_1_R->SetTitle("");
  b_nom_1_R->SetStats(0);
  b_nom_1_R->SetTitle("PYTHIA  60 < #it{p}_{T}^{jet} < 80 GeV");
  b_nom_1_R->GetYaxis()->SetTitle("a.u.");
  b_nom_1_R->GetYaxis()->SetRangeUser(0,0.2);
  b_nom_1_R->Draw();
  b_GS_1_R->Draw("same");
  light_1_R->Draw("same");
  pad_1_2->cd();
  r_1->SetTitle("");
  r_1->SetStats(0);
  r_1->GetXaxis()->SetTitleSize(0.06);
  r_1->GetXaxis()->SetLabelSize(0.048);
  r_1->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  r_1->GetYaxis()->SetTitle("Ratio");
  r_1->GetYaxis()->SetRangeUser(0,2);
  r_1->Draw();
  R_1->Draw("same");
  li->DrawLine(0,1,5,1);
  canv->cd(2);
  TPad *pad_2_1 = new TPad("pad_2_1","pad_2_1",0,0.4,1,1);
  TPad *pad_2_2 = new TPad("pad_2_2","pad_2_2",0,0,1,0.4);
  pad_2_1->SetLeftMargin(0.2);
  pad_2_1->SetTopMargin(0.1);
  pad_2_1->SetRightMargin(0.2);
  pad_2_1->SetBottomMargin(0.0);
  pad_2_2->SetLeftMargin(0.2);
  pad_2_2->SetTopMargin(0.0);
  pad_2_2->SetRightMargin(0.2);
  pad_2_2->SetBottomMargin(0.2);
  pad_2_1->Draw();
  pad_2_2->Draw();
  pad_2_1->cd();
  b_nom_2_R->SetTitle("");
  b_nom_2_R->SetStats(0);
  b_nom_2_R->SetTitle("PYTHIA  80 < #it{p}_{T}^{jet} < 120 GeV");
  b_nom_2_R->GetYaxis()->SetTitle("a.u.");
  b_nom_2_R->GetYaxis()->SetRangeUser(0,0.2);
  b_nom_2_R->Draw();
  b_GS_2_R->Draw("same");
  light_2_R->Draw("same");
  pad_2_2->cd();
  r_2->SetTitle("");
  r_2->SetStats(0);
  r_2->GetXaxis()->SetTitleSize(0.06);
  r_2->GetXaxis()->SetLabelSize(0.048);
  r_2->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  r_2->GetYaxis()->SetTitle("Ratio");
  r_2->GetYaxis()->SetRangeUser(0,2);
  r_2->Draw();
  R_2->Draw("same");
  li->DrawLine(0,1,5,1);
  canv->cd(3);
  TPad *pad_3_1 = new TPad("pad_3_1","pad_3_1",0,0.4,1,1);
  TPad *pad_3_2 = new TPad("pad_3_2","pad_3_2",0,0,1,0.4);
  pad_3_1->SetLeftMargin(0.2);
  pad_3_1->SetTopMargin(0.1);
  pad_3_1->SetRightMargin(0.2);
  pad_3_1->SetBottomMargin(0.0);
  pad_3_2->SetLeftMargin(0.2);
  pad_3_2->SetTopMargin(0.0);
  pad_3_2->SetRightMargin(0.2);
  pad_3_2->SetBottomMargin(0.2);
  pad_3_1->Draw();
  pad_3_2->Draw();
  pad_3_1->cd();
  b_nom_3_R->SetTitle("");
  b_nom_3_R->SetStats(0);
  b_nom_3_R->SetTitle("PYTHIA  120 < #it{p}_{T}^{jet} < 200 GeV");
  b_nom_3_R->GetYaxis()->SetTitle("a.u.");
  b_nom_3_R->GetYaxis()->SetRangeUser(0,0.2);
  b_nom_3_R->Draw();
  b_GS_3_R->Draw("same");
  light_3_R->Draw("same");
  pad_3_2->cd();
  r_3->SetTitle("");
  r_3->SetStats(0);
  r_3->GetXaxis()->SetTitleSize(0.06);
  r_3->GetXaxis()->SetLabelSize(0.048);
  r_3->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  r_3->GetYaxis()->SetTitle("Ratio");
  r_3->GetYaxis()->SetRangeUser(0,2);
  r_3->Draw();
  R_3->Draw("same");
  li->DrawLine(0,1,5,1);
  

}
