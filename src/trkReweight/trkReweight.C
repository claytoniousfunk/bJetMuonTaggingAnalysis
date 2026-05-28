/*

  Code for track reweighting.
  Going to take in the in-jet tracks and compare them to light in-jet muons.

  Here are the steps in this analysis:
  - Have a baseline comparison of the track-pTrel to muon-pTrel spectra (same kinematic cuts)
  - Derive a reweighting function from comparing the track-pT to the muon-pT spectra.
  - Reweight the tracks in a separate scan.
  - Compare again, show that the reweighting procedure worked.
  - Compare again the pTrel spectra, should also be aligned.

  Input:
  - ROOT file with in-jet track pT and pTrel.  This will be the output of PYTHIA*_jetTrkMax_scan.C.
  - ROOT file with in-jet muon pT and pTrel.  This will be the output of PYTHIA*_scan.C.

*/

#include "../../headers/functions/divideByBinwidth.h"


double func_temp(double *x, double *par){

  //double fitval = par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0] ;
  double fitval = par[0]*TMath::Exp(par[1]*x[0]) + par[2]*TMath::Exp(par[3]*x[0]) + par[4] ;
  //double fitval = par[0]*TMath::Exp(par[1]*x[0]) + par[2] + par[3]*x[0];
  
  return fitval;
}

TString getSystemString(bool doPP, bool doC4, bool doC3, bool doC2, bool doC1){
  TString result = "";
  if(doPP) result = "";
  else if(doC4) result = "";
  else if(doC3) result = "";
  else if(doC2) result = "";
  else if(doC1) result = "";
  else{};
  return result;
}

TString getSuffix(bool doPP, bool doC4, bool doC3, bool doC2, bool doC1){
  TString result = "";
  if(doPP) result = "T0";
  else if(doC4) result = "C4T0";
  else if(doC3) result = "C3T0";
  else if(doC2) result = "C2T0";
  else if(doC1) result = "C1T0";
  else{};
  return result;
}

TString getCanvasSavePath(bool doPP, bool doC4, bool doC3, bool doC2, bool doC1){
  TString result = "";
  if(doPP) result = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/trkReweight/pp/";
  else if(doC4) result = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/trkReweight/C4/";
  else if(doC3) result = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/trkReweight/C3/";
  else if(doC2) result = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/trkReweight/C2/";
  else if(doC1) result = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/trkReweight/C1/";
  else{};
  return result;
}


void trkReweight(bool doPP = 1,
		 bool doC4 = 0,
		 bool doC3 = 0,
		 bool doC2 = 0,
		 bool doC1 = 0,
		 double jetPt_low = 80.,
		 double jetPt_high = 100.){


  TFile *file_trk, *file_trkR, *file_mu;

  if(doPP){
    file_trk = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/jetTrkMax/PYTHIA_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-8-15.root");
    file_trkR = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/jetTrkMax/PYTHIA_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_hadronPtRelReweightToMuon_2025-8-15.root");
    file_mu = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-20_removeHYDJETjet0p45_jetTrkMaxFilter_vzReweight_jetPtReweight_projectableTemplates_2025-06-17.root");
  }
  else{
    file_trk = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/jetTrkMax/PYTHIAHYDJET_DiJet_jetTrkMax_fineCentBins_pThat-20_trkpT-14_hiBinShift-10.root");
    file_trkR = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/jetTrkMax/PYTHIAHYDJET_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_hadronPtRelReweightToMuon_2025-8-15.root");
  //file_mu = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-25_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_weightCutOnLightJetTemplate0p002_removeHYDJETjet0p45_fineCentBins_projectableTemplates_allTemplates.root");
    file_mu = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-6-2.root");
  }
  
  TString sytemString = getSystemString(doPP,doC4,doC3,doC2,doC1);
  TString suffix = getSuffix(doPP,doC4,doC3,doC2,doC1);

  TH2D *H_trk, *H_mu, *H_trkR;
  TH2D *H_mu_dJets, *H_mu_uJets, *H_mu_sJets, *H_mu_gJets, *H_mu_lJets;  
  TH1D *h_trk, *h_mu, *h_trkR;
  

  file_trk->GetObject(Form("h_jetTrkMaxPtRel_recoJetPt_%s",suffix.Data()),H_trk);
  file_trkR->GetObject(Form("h_jetTrkMaxPtRel_recoJetPt_%s",suffix.Data()),H_trkR);
  
  file_mu->GetObject(Form("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_uJets_%s",suffix.Data()),H_mu_uJets);
  file_mu->GetObject(Form("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_dJets_%s",suffix.Data()),H_mu_dJets);
  file_mu->GetObject(Form("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_sJets_%s",suffix.Data()),H_mu_sJets);
  file_mu->GetObject(Form("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_gJets_%s",suffix.Data()),H_mu_gJets);

  //H_trk->Draw();

  H_mu_lJets = (TH2D*) H_mu_uJets->Clone("H_mu_lJets");
  H_mu_lJets->Add(H_mu_dJets);
  H_mu_lJets->Add(H_mu_sJets);
  H_mu_lJets->Add(H_mu_gJets);

  
   
  h_mu = (TH1D*) H_mu_lJets->ProjectionX("h_mu",H_mu_lJets->ProjectionY()->FindBin(jetPt_low),H_mu_lJets->ProjectionY()->FindBin(jetPt_high));
  h_trk = (TH1D*) H_trk->ProjectionX("h_trk",H_trk->ProjectionY()->FindBin(jetPt_low),H_trk->ProjectionY()->FindBin(jetPt_high));
  h_trkR = (TH1D*) H_trkR->ProjectionX("h_trkR",H_trkR->ProjectionY()->FindBin(jetPt_low),H_trkR->ProjectionY()->FindBin(jetPt_high));

  // rebin
  const int NEdge = 16;
  double newAxis[NEdge] = {0,0.2,0.4,0.6,0.8,1,1.2,1.4,1.6,1.8,2.0,2.3,2.8,3.5,5,10};
  // const int NEdge = 42;
  // double newAxis[NEdge] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4.0,5.0};
  h_mu = (TH1D*) h_mu->Rebin(NEdge-1,"h_mu",newAxis);
  h_trk = (TH1D*) h_trk->Rebin(NEdge-1,"h_trk",newAxis);
  h_trkR = (TH1D*) h_trkR->Rebin(NEdge-1,"h_trkR",newAxis);
  divideByBinwidth(h_mu);
  divideByBinwidth(h_trk);
  divideByBinwidth(h_trkR);
  
  h_trk->Scale(1./h_trk->Integral());
  h_trkR->Scale(1./h_trkR->Integral());
  h_mu->Scale(1./h_mu->Integral());

  // h_mu->Draw();
  // h_trk->Draw("same");
  

  
  h_trk->SetLineColor(kBlue-4);
  h_trkR->SetLineColor(kGreen+2);
  h_mu->SetLineColor(kRed-4);

  h_trk->SetLineWidth(2);
  h_trkR->SetLineWidth(2);
  h_mu->SetLineWidth(2);

  TH1D *r = (TH1D*) h_trk->Clone("r");
  r->Divide(h_mu,h_trk,1,1,"");

  TH1D *r2 = (TH1D*) h_trkR->Clone("r2");
  r2->Divide(h_mu,h_trkR,1,1,"");
  
  
  TLegend *leg = new TLegend(0.6,0.6,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.045);

  leg->AddEntry(h_mu,"light-jet muons","l");
  leg->AddEntry(h_trk,"tracks","l");
  //leg->AddEntry(h_trkR,"reweighted tracks","l");

  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad1 = new TPad("pad1","pad1",0,0.4,1,1);
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.4);
  pad1->SetBottomMargin(0);
  pad1->SetLeftMargin(0.15);
  pad1->SetTopMargin(0.1);
  pad2->SetBottomMargin(0.18);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0.);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();

  h_trk->GetXaxis()->SetRangeUser(newAxis[0],newAxis[NEdge-1]);
  h_trk->GetYaxis()->SetRangeUser(0,0.3);
  h_trk->SetTitle(Form("In-jet track/muon spectra, %3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f",jetPt_low,jetPt_high));
  h_trk->GetYaxis()->SetLabelSize(0.04);
  h_trk->GetYaxis()->SetTitleSize(0.06);
  h_trk->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
  h_trk->SetStats(0);
  
  h_trk->Draw("");
  h_mu->Draw("same");
  //h_trkR->Draw("same");
  leg->Draw();

  pad2->cd();
  r->GetXaxis()->SetRangeUser(0,50);
  r->GetXaxis()->SetLabelSize(0.06);
  r->GetXaxis()->SetTitleSize(0.08);
  r->GetYaxis()->SetLabelSize(0.06);
  r->GetYaxis()->SetTitleSize(0.08);
  r->GetXaxis()->SetTitle("Track/Muon #it{p}_{T}^{rel} [GeV]");
  r->GetYaxis()->SetTitle("Muons / Tracks");
  r->SetTitle("");
  r->SetStats(0);
  r->GetYaxis()->SetRangeUser(0,2);
  r->GetXaxis()->SetRangeUser(newAxis[0],newAxis[NEdge-1]);
  r->Draw("");
  //r2->Draw("same");
  //r->Fit("pol1","","",14,30);

  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(newAxis[0],1,newAxis[NEdge-1],1);

  //TF1 *func = new TF1("func",func_temp,newAxis[0],newAxis[NEdge-1],5);
  TF1 *func = new TF1("func","pol3",0,10);
  // func->SetParameter(0,1.3);
  // func->SetParameter(2,0);
  // func->SetParameter(4,0.35);
  // func->SetParLimits(0,0,5);
  // func->SetParLimits(2,0,5);
  // func->SetParLimits(1,-10,0);
  // func->SetParLimits(3,-10,0);
  //r->Fit("func","MR","",newAxis[0],newAxis[NEdge-1]);
  //r->Fit("func","MR");
  
  
 
  std::string canvas_save_string = Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/trkReweight/pp/trkReweight_jetPt-%3.0fto%3.0f.pdf",jetPt_low,jetPt_high);
  canv->SaveAs(canvas_save_string.c_str());
  

}
