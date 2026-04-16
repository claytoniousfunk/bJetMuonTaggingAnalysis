
#include "../../../headers/functions/divideByBinwidth.h"

void hiBinProjection(){

  TFile *input_mc = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-5-27.root");

  TFile *input_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_scan_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates_2025-05-28.root");

  TH2D *H_mc, *H_data;
  TH1D *h_mc, *h_data;
  
  input_mc->GetObject("h_muptrel_hiBin_allJets_J1",H_mc);
  
  h_mc = (TH1D*) H_mc->ProjectionX("h_mc",H_mc->ProjectionY()->FindBin(10.),H_mc->ProjectionY()->FindBin(30.));
  
  input_data->GetObject("h_muptrel_hiBin_J1",H_data);
  
  h_data = (TH1D*) H_data->ProjectionX("h_data",H_data->ProjectionY()->FindBin(0.),H_data->ProjectionY()->FindBin(20.));




  const int M = 13;
  double muRelPtAxis[M] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.5,1.8,2.4,3.5,5.0,10}; // M = 13
  //double muRelPtAxis[M] = {0.0,0.3,0.6,0.9,1.3,1.8,2.4,3.5,5}; // M = 9
  
  // h_mc = (TH1D*) h_mc->Rebin(M-1,"h_mc",muRelPtAxis);
  // h_data = (TH1D*) h_data->Rebin(M-1,"h_data",muRelPtAxis);

  divideByBinwidth(h_mc);
  divideByBinwidth(h_data);
  
  h_mc->Scale(1./h_mc->Integral());
  h_data->Scale(1./h_data->Integral());
  
  h_mc->SetLineColor(kBlue-4);
  h_data->SetLineColor(kRed-4);

  h_mc->SetLineWidth(2);
  h_data->SetLineWidth(2);


  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.15);
  pad->Draw();
  pad->cd();

  h_mc->SetTitle("");
  h_mc->SetStats(0);
  h_mc->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h_mc->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
  h_mc->Draw();
  h_data->Draw("same");

  TLatex *la = new TLatex();
  la->SetTextFont(62);
  la->SetTextSize(0.035);
  la->DrawLatexNDC(0.5,0.7,"all jets, 80 < #it{p}_{T}^{jet} (GeV) < 100");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.5,0.6,"PYTHIA+HYDJET 5-15%");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.5,0.5,"PbPb 0-10%");
  //la->DrawLatexNDC(0.5,0.5,"PYTHIA+HYDJET 10-15%");

  // H_data->Draw("colz");


  */

}
