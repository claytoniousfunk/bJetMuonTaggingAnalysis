#include "../../../headers/goldenFileNames.h"
#include "../../../headers/functions/divideByBinwidth.h"

void fraction_calculation(){

  TLatex *la = new TLatex();

  // DiJet scan file
  TFile *f_py = TFile::Open(goldenFile_PYTHIA_mu5);
  // pp MinBias file
  TFile *f_mb = TFile::Open(goldenFile_pp_MinBias_mu5);
  // pp SingleMuon file
  TFile *f_sm = TFile::Open(goldenFile_pp_SingleMuon_mu5);
  // matching factor
  TFile *f_mf = TFile::Open("../tagging_sequence/matchingFactors/mf_mu5_MCJetTrig.root");
  // b-amplifiers
  TFile *f_ba = TFile::Open("../tagging_sequence/b_amplifiers/ba_mu5_MCJetTrig.root");
  // b-fraction results
  TFile *f_bf = TFile::Open("../../../rootFiles/bPurityResults/MC/bPurityResults_mu5.root");

  
  TH1D *mf;
  f_mf->GetObject("mf",mf);

  TH1D *bf;
  f_bf->GetObject("bFracResults_pp",bf);
  
  TH1D *ba;
  f_ba->GetObject("r_corr",ba);



  TCanvas *canv_1 = new TCanvas("canv_1","canv_1",700,700);
  canv_1->cd();
  TPad *pad_1 = new TPad("pad_1","pad_1",0,0,1,1);
  pad_1->SetLeftMargin(0.2);
  pad_1->SetBottomMargin(0.2);
  pad_1->Draw();
  pad_1->cd();
  
  
  mf->Draw();
  canv_1->SaveAs("figures/pre-rebin.pdf");

  
  const int M = 6;
  double new_axis[M] = {60,80,120,200,300,500}; // M = 4

  TH1D *mf_R = (TH1D*) mf->Rebin(M-1,"mf_R",new_axis);
  TH1D *ba_R = (TH1D*) ba->Rebin(M-1,"ba_R",new_axis);

  divideByBinwidth(mf_R);
  mf_R->Scale(5.0); // account for 5-GeV-wide bins

  divideByBinwidth(ba_R);
  ba_R->Scale(5.0); // account for 5-GeV-wide bins
  
  mf_R->Draw();
  canv_1->SaveAs("figures/post-rebin.pdf");

  mf_R->Multiply(bf);
  mf_R->Draw();
  canv_1->SaveAs("figures/multiply-by-b-fraction.pdf");

  mf_R->Multiply(ba_R);
  mf_R->Draw();
  canv_1->SaveAs("figures/multiply-by-b-amplifier.pdf");
  //mf_R->Scale(1./3.);
  mf_R->GetYaxis()->SetTitle("inclusive #font[52]{b}-jet fraction");
  mf_R->SetLineColor(kBlack);
  mf_R->SetMarkerColor(kBlack);
  //mf_R->GetYaxis()->SetRangeUser(0.0,0.1);
  mf_R->Draw();
  la->SetTextFont(62);
  la->SetTextSize(0.045);
  la->DrawLatexNDC(0.23,0.92,"pp (5.02 TeV)");
  la->SetTextFont(42);
  la->SetTextSize(0.035);
  //la->DrawLatexNDC(0.5,0.42,"Correction from pure MC");
  la->DrawLatexNDC(0.5,0.42,"Correction from data jet-trig.");
  
  //canv_1->SaveAs("figures/correction-from-pure-mc.pdf");
  canv_1->SaveAs("figures/correction-from-pure-data.pdf");
  
  
  

  

  






}
