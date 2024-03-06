#include "../../../headers/functions/divideByBinwidth.h"
#include "../../../headers/systematicsResults.h"
#include "../../../headers/goldenFileNames.h"


void fraction_plot(){

  TFile *x1, *x2, *x3;
  x1 = TFile::Open(goldenFile_PYTHIA_mu7);
  x2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu7);

  TH2D *Y1, *Y2, *Y3;
  TH1D *y1, *y2, *y3;
  TH1D *b1, *b2, *b3;
  TH1D *b1_add, *b2_add, *b3_add;

  x1->GetObject("h_inclRecoJetPt_flavor",Y1);
  x2->GetObject("h_inclRecoJetPt_flavor_C2",Y2);
  x2->GetObject("h_inclRecoJetPt_flavor_C1",Y3);

  y1 = (TH1D*) Y1->ProjectionX();
  y2 = (TH1D*) Y2->ProjectionX();
  y3 = (TH1D*) Y3->ProjectionX();

  TH1D *binFinder = Y1->ProjectionY();
  double smallShift = 0.01;
  
  b1 = (TH1D*) Y1->ProjectionX("b1",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  b1_add = (TH1D*) Y1->ProjectionX("b1_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  b1->Add(b1_add);

  b2 = (TH1D*) Y2->ProjectionX("b2",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  b2_add = (TH1D*) Y2->ProjectionX("b2_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  b2->Add(b2_add);

  b3 = (TH1D*) Y3->ProjectionX("b3",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  b3_add = (TH1D*) Y3->ProjectionX("b3_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  b3->Add(b3_add);



  TH1D *b_truth_pp = (TH1D*) b1->Clone("b_truth_pp");
  b_truth_pp->Divide(b1,y1,1,1,"B");
  
  TH1D *b_truth_C2 = (TH1D*) b2->Clone("b_truth_C2");
  b_truth_C2->Divide(b2,y2,1,1,"B");

  TH1D *b_truth_C1 = (TH1D*) b3->Clone("b_truth_C1");
  b_truth_C1->Divide(b3,y3,1,1,"B");

  b_truth_pp->SetLineColor(kBlue-4);
  //  b_truth_pp->SetLineStyle(7);
  b_truth_pp->SetMarkerSize(0);
  b_truth_pp->SetLineWidth(2);

  b_truth_C2->SetLineColor(kRed-4);
  //  b_truth_C2->SetLineStyle(7);
  b_truth_C2->SetMarkerSize(0);
  b_truth_C2->SetLineWidth(2);

  b_truth_C1->SetLineColor(kGreen+2);
  //  b_truth_C1->SetLineStyle(7);
  b_truth_C1->SetMarkerSize(0);
  b_truth_C1->SetLineWidth(2);

  
  
  TFile *f1, *f2, *f3;
  TFile *F1, *F2, *F3;

  // b-fraction results
  f1 = TFile::Open("../../../rootFiles/bPurityResults/MC/bPurityResults_mu5.root");
  f2 = TFile::Open("../../../rootFiles/bPurityResults/MC/bPurityResults_mu7.root");
  f3 = TFile::Open("../../../rootFiles/bPurityResults/MC/bPurityResults_mu12.root");

  F1 = TFile::Open("../../../rootFiles/bPurityResults/DATA/bPurityResults_mu5.root");
  F2 = TFile::Open("../../../rootFiles/bPurityResults/DATA/bPurityResults_mu7_matchedPartonFlavor.root");
  F3 = TFile::Open("../../../rootFiles/bPurityResults/DATA/bPurityResults_mu12.root");

  TH1D *h1, *h2, *h3;
  TH1D *H1, *H2, *H3;

  F2->GetObject("bFracResults_pp",h1);
  F2->GetObject("bFracResults_C2",h2);
  F2->GetObject("bFracResults_C1",h3);

  F1->GetObject("bFracResults_pp",H1);
  F2->GetObject("bFracResults_pp",H2);
  F3->GetObject("bFracResults_pp",H3);



  // b-enhancement files
  TFile *fb1, *fb2, *fb3;
  fb1 = TFile::Open("../tagging_sequence/b_amplifiers/ba_mu7_MCJetTrig.root");
  fb2 = TFile::Open("../tagging_sequence/b_amplifiers/ba_PbPb_C2_mu7_MCJetTrig.root");
  fb3 = TFile::Open("../tagging_sequence/b_amplifiers/ba_PbPb_C1_mu7_MCJetTrig.root");

  TH1D *ba1, *ba2, *ba3;

  fb1->GetObject("r_corr",ba1);
  fb2->GetObject("r_corr",ba2);
  fb3->GetObject("r_corr",ba3);

  const int M = 6;
  double new_axis[M] = {60,80,120,200,300,500};
  
  TH1D *ba1_R = (TH1D*) ba1->Rebin(M-1,"ba1_R",new_axis);
  TH1D *ba2_R = (TH1D*) ba2->Rebin(M-1,"ba2_R",new_axis);
  TH1D *ba3_R = (TH1D*) ba1->Rebin(M-1,"ba3_R",new_axis);

  divideByBinwidth(ba1_R);
  ba1_R->Scale(5.0); // account for 5-GeV-wide bins

  divideByBinwidth(ba2_R);
  ba2_R->Scale(5.0); // account for 5-GeV-wide bins

  divideByBinwidth(ba3_R);
  ba3_R->Scale(5.0); // account for 5-GeV-wide bins

  h1->Divide(h1,ba1_R,1,1,"");
  h2->Divide(h2,ba2_R,1,1,"");
  h3->Divide(h3,ba3_R,1,1,"");
  
  
  h1->SetLineColor(kBlue-4);
  h1->SetMarkerColor(kBlue-4);
  h1->SetMarkerStyle(53);

  h2->SetLineColor(kRed-4);
  h2->SetMarkerColor(kRed-4);
  h2->SetMarkerStyle(54);

  h3->SetLineColor(kGreen+2);
  h3->SetMarkerColor(kGreen+2);
  h3->SetMarkerStyle(55);

  TH1D *r1, *r2, *r3;

  r1 = (TH1D*) h1->Clone("r1");
  r2 = (TH1D*) h2->Clone("r2");
  r3 = (TH1D*) h3->Clone("r3");

  // r1->Divide(h1,h1,1,1,"");
  // r2->Divide(h2,h1,1,1,"");
  // r3->Divide(h3,h1,1,1,"");

  
  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.2);
  pad->SetBottomMargin(0.2);
  pad->Draw();
  pad->cd();
  //r2->GetYaxis()->SetTitle("#it{f}_{#it{b}}(PbPb) / #it{f}_{#it{b}}(pp)");
  r2->GetYaxis()->SetTitle("inclusive #font[52]{b}-jet fraction");
  r2->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  r2->GetXaxis()->SetRangeUser(60,200);
  //r2->GetYaxis()->SetRangeUser(0,2);
  r2->GetYaxis()->SetRangeUser(0,0.1);
  r2->SetTitle("");
  r2->SetStats(0);

  r2->Draw();
  r1->Draw("same");
  r3->Draw("same");
  
  // h1->Draw();
  // h2->Draw("same");
  // h3->Draw("same");

  TH1D *s1 = (TH1D*) r1->Clone("s1");
  TH1D *s2 = (TH1D*) r2->Clone("s2");
  TH1D *s3 = (TH1D*) r3->Clone("s3");

  s1->SetBinError(1,sys_total_pp_J2*s1->GetBinContent(1));
  s1->SetBinError(2,sys_total_pp_J3*s1->GetBinContent(2));
  s1->SetBinError(3,sys_total_pp_J4*s1->GetBinContent(3));
  
  s2->SetBinError(1,sys_total_PbPb_C2_J2*s2->GetBinContent(1));
  s2->SetBinError(2,sys_total_PbPb_C2_J3*s2->GetBinContent(2));
  s2->SetBinError(3,sys_total_PbPb_C2_J4*s2->GetBinContent(3));

  s3->SetBinError(1,sys_total_PbPb_C1_J2*s3->GetBinContent(1));
  s3->SetBinError(2,sys_total_PbPb_C1_J3*s3->GetBinContent(2));
  s3->SetBinError(3,sys_total_PbPb_C1_J4*s3->GetBinContent(3));

  s1->SetFillColorAlpha(kBlue-4,0.5);
  s2->SetFillColorAlpha(kRed-4,0.5);
  s3->SetFillColorAlpha(kGreen+2,0.5);
  //s1->Draw("e2 same");
  s2->Draw("e2 same");
  s3->Draw("e2 same");

  TLegend *leg = new TLegend(0.6,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.032);
  leg->AddEntry(h1,"pp","p");
  leg->AddEntry(h2,"PbPb 30-90%","p");
  leg->AddEntry(h3,"PbPb 0-30%","p");
  leg->Draw();

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.044);
  la->DrawLatexNDC(0.23,0.92,"#font[62]{CMS }#scale[0.8]{#font[52]{Preliminary}}");
  //la->DrawLatexNDC(0.6,0.92,"#font[62]{PYTHIA (5.02 TeV)}");
  //la->DrawLatexNDC(0.6,0.92,"#font[62]{pp (5.02 TeV)}");
  //la->DrawLatexNDC(0.6,0.92,"#font[62]{PbPb 0-30% (5.02 TeV)}");
  //la->DrawLatexNDC(0.5,0.92,"#font[62]{PYTHIA+HYDJET 0-30% (5.02 TeV)}");
  la->SetTextSize(0.036);
  la->DrawLatexNDC(0.3,0.4,"#sqrt{s_{NN}} = 5.02 TeV");
  la->DrawLatexNDC(0.3,0.3,"PbPb (749 #mub^{-1}), pp (280 pb^{-1})");

  
  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(60,1,200,1);

  b_truth_pp->Draw("same");
  b_truth_C2->Draw("same");
  b_truth_C1->Draw("same");

  TLegend *leg2 = new TLegend(0.25,0.65,0.5,0.85);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.032);
  leg2->AddEntry(b_truth_pp,"PYTHIA","l");
  leg2->AddEntry(b_truth_C2,"PYTHIA+HYDJET 30-90%","l");
  leg2->AddEntry(b_truth_C1,"PYTHIA+HYDJET 0-30%","l");
  leg2->Draw();

  
  
  canv->SaveAs("~/Documents/nuclear/GroupMeeting/figures/2024-02-13/results/ratio.pdf");


  /*
  TFile *fm1, *fm2, *fm3;
  fm1 = TFile::Open("../tagging_sequence/matchingFactors/mf_mu5_MCJetTrig.root");
  fm1 = TFile::Open("../tagging_sequence/matchingFactors/mf_mu5_MCJetTrig.root");

  TCanvas *canv2 = new TCanvas("canv2","canv2",700,700);
  canv2->cd();
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,1);
  pad2->SetLeftMargin(0.2);
  pad2->SetBottomMargin(0.2);
  pad2->Draw();
  pad2->cd();
  */

  
}
