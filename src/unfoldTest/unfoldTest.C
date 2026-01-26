
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>

// #include "/home/clayton/Analysis/RooUnfold/src/RooUnfold.h"
// #include "/home/clayton/Analysis/RooUnfold/src/RooFitUnfold.h"
//#include "/home/clayton/Analysis/code/RooUnfold/src/RooUnfoldResponse.h"
//#include "/home/clayton/Analysis/code/RooUnfold/src/RooUnfoldBayes.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"

#endif

#include "../../headers/functions/divideByBinwidth.h"






void unfoldTest(){

  //gSystem->Load("/home/clayton/Analysis/code/RooUnfold/build/libRooUnfold");  
    
  TFile *f1, *f2, *f3;

  f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_MinBias_mu12_pTmu-14_tight_jetTrkMaxFilter_2025-10-15.root");

  //f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-10-21.root");
  //f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-30_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-11-5.root");

  //f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-30_mu12_pTmu-14_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2026-1-12_muTaggedJets.root");


  // f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-14_tight_hiBinShift-10_leadingXjetDumpFilter_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-1-19.root");
  // f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-14_tight_hiBinShift-10_leadingXjetDumpFilter_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_BJetNeutrinoEnergyShift_2026-1-20.root");

  // f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-1-26_genMuTaggedGenJets.root");
  // f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-30_mu12_pTmu-14_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2026-1-12_muTaggedJets.root");

  f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-1-26.root");
  f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-1-26.root");  

  TH1D *Njet;

  f1->GetObject("h_inclRecoJetPt",Njet);

  TH1D *vz;

  f1->GetObject("h_vz",vz);

  TH2D *h_response;
  TH2D *H_bJets, *H_allJets;
  TH1D *h_recoBJets, *h_recoAllJets;
  TH1D *h_genBJets, *h_genAllJets;

  //f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets",h_response);
  //f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",h_response);
  //f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",h_response);
  //f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",h_response);
  //f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",h_response);


  //f2->GetObject("h_matchedRecoJetPt_genJetPt_var",h_response);
  //f2->GetObject("h_matchedRecoJetPt_genJetPt_var_C4",h_response);
  //f2->GetObject("h_matchedRecoJetPt_genJetPt_var_C3",h_response);
  //f2->GetObject("h_matchedRecoJetPt_genJetPt_var_C2",h_response);



  // f2->GetObject("h_matchedRecoJetPt_genJetPt_var_C1",h_response);
  // f3->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C1",H_bJets);

  // f2->GetObject("h_matchedRecoJetPt_genJetPt_var_C2",h_response);
  // f3->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H_bJets);

  // f2->GetObject("h_matchedRecoJetPt_genJetPt_var_C3",h_response);
  // f3->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C3",H_bJets);

  // f2->GetObject("h_matchedRecoJetPt_genJetPt_var_C4",h_response);
  // f3->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C4",H_bJets);

  f2->GetObject("h_matchedRecoJetPt_genJetPt_var",h_response);
  f3->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_bJets);
  f3->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H_allJets);

  // f2->GetObject("h_matchedRecoJetPt_genJetPt_var",h_response);
  // f3->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_bJets);


  const int N1 = 16;
  double ptAxis1[N1] = {0,10,20,30,40,50,60,70,80,90,100,120,150,200,300,500};

  h_recoBJets = (TH1D*) H_bJets->ProjectionX("h_recoBJets");
  h_genBJets = (TH1D*) H_bJets->ProjectionY("h_genBJets");

  h_recoBJets = (TH1D*) h_recoBJets->Rebin(N1-1,"h_recoBJets",ptAxis1);
  h_genBJets = (TH1D*) h_genBJets->Rebin(N1-1,"h_genBJets",ptAxis1);

  h_recoAllJets = (TH1D*) H_allJets->ProjectionX("h_recoAllJets");
  h_genAllJets = (TH1D*) H_allJets->ProjectionY("h_genAllJets");

  h_recoAllJets = (TH1D*) h_recoAllJets->Rebin(N1-1,"h_recoAllJets",ptAxis1);
  h_genAllJets = (TH1D*) h_genAllJets->Rebin(N1-1,"h_genAllJets",ptAxis1);

  // divideByBinwidth(h_recoBJets);
  // divideByBinwidth(h_genBJets);
  
  TH1D *h_meas, *h_truth;

  h_meas = (TH1D*) h_response->ProjectionX("h_meas");
    
  h_truth = (TH1D*) h_response->ProjectionY("h_truth");

  h_response->Draw("colz");
  
  RooUnfoldResponse response(h_meas,h_truth,h_response,"response","my response",0);

  RooUnfoldBayes unfold(&response, h_recoAllJets, 1);
  RooUnfoldBayes unfold_b(&response, h_recoBJets, 1);

  TH1D* h_reco= (TH1D*) unfold.Hunfold();
  TH1D *h_unfoldB = (TH1D*) unfold_b.Hunfold();

  // rebin
  const int Nedge = 15;
  double ptAxis[Nedge] = {0,10,20,30,40,50,60,70,80,100,120,150,200,300,500};


  TH1D *Njet_R = (TH1D*) Njet->Rebin(Nedge-1,"Njet_R",ptAxis);

  // divideByBinwidth(Njet_R);

  // Divide out bin width, Lint, and Nevent

  for(int i = 0; i < Njet_R->GetSize(); i++){
    double NjetBin = Njet_R->GetBinContent(i);
    double NjetBin_err = Njet_R->GetBinError(i);
    double dEta = 3.2;
    double dPt = Njet_R->GetBinWidth(i);
    double Lint = 103.9e9;
    double Nevt = 1.;
    if(dPt!=0.){
      Njet_R->SetBinContent(i,NjetBin/(dPt*dEta*Lint*Nevt));
      Njet_R->SetBinError(i,NjetBin_err/(dPt*dEta*Lint*Nevt));
    }
  }

  TCanvas *c1 = new TCanvas("c1","differential cross section",800,800);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0,1,1);
  p1->Draw();
  p1->cd();
  p1->SetLeftMargin(0.2);
  p1->SetBottomMargin(0.2);
  p1->SetLogy();
  Njet_R->SetTitle("");
  Njet_R->SetStats(0);
  Njet_R->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  Njet_R->GetYaxis()->SetTitle("d^{2}#sigma^{pp}_{jet} / d#font[52]{p}_{T} d#eta [mb/GeV]");

  Njet_R->Draw();


  TCanvas *c2 = new TCanvas("c2","unfolded spectra",800,800);
  TPad *p2 = new TPad("p2","p2",0,0.4,1,1);
  TPad *p2_1 = new TPad("p2_1","p2_1",0,0,1,0.4);
  p2->Draw();
  p2->cd();
  p2->SetLeftMargin(0.2);
  p2->SetBottomMargin(0.0);
  p2->SetLogy();
  h_truth->SetLineColor(kRed);
  h_meas->SetLineColor(kGreen+2);
  h_reco->SetLineColor(kBlue);

  h_truth->SetMarkerColor(kRed);
  h_meas->SetMarkerColor(kGreen+2);
  h_reco->SetMarkerColor(kBlue);

  h_truth->SetMarkerStyle(8);
  h_meas->SetMarkerStyle(8);
  h_reco->SetMarkerStyle(8);

  h_truth->GetXaxis()->SetLabelSize(0.0);
  h_truth->GetXaxis()->SetTitleSize(0.0);

  h_truth->SetStats(0);
  h_truth->GetYaxis()->SetTitle("Entries");
  h_truth->SetTitle("");
  h_truth->Draw();
  h_meas->Draw("same");
  h_reco->Draw("same");

  TLegend *leg = new TLegend(0.6,0.3,0.85,0.55);
  leg->SetBorderSize(0.0);
  leg->AddEntry(h_truth,"truth");
  leg->AddEntry(h_meas,"measured");
  leg->AddEntry(h_reco,"unfolded");
  leg->Draw();

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.034);
  la->DrawLatexNDC(0.6,0.85,"PYTHIA #sqrt{#font[52]{s}} = 5 TeV");
  la->DrawLatexNDC(0.6,0.78,"Bayesian unfolding via RooUnfold");

  c2->cd();
  p2_1->Draw();
  p2_1->cd();
  p2_1->SetLeftMargin(0.2);
  p2_1->SetBottomMargin(0.25);
  p2_1->SetTopMargin(0.0);

  TH1D *r_reco = (TH1D*) h_reco->Clone("r_reco");
  r_reco->Divide(h_reco,h_truth,1,1,"B");

  TH1D *r_meas = (TH1D*) h_meas->Clone("r_meas");
  r_meas->Divide(h_meas,h_truth,1,1,"B");
  
  r_reco->GetYaxis()->SetTitle("unfold / truth");
  r_reco->GetXaxis()->SetTitle("#font[52]{p}_{T}^{jet} [GeV]");
  r_reco->GetXaxis()->SetLabelSize(0.06);
  r_reco->GetXaxis()->SetTitleSize(0.07);
  r_reco->GetYaxis()->SetLabelSize(0.06);
  r_reco->GetYaxis()->SetTitleSize(0.07);
  r_reco->SetTitle("");
  r_reco->SetStats(0);
  r_reco->GetYaxis()->SetRangeUser(0.0,2.0);

  // r_reco->SetLineColor(kBlack);
  // r_reco->SetMarkerColor(kBlack);
  // r_reco->SetMarkerStyle(24);
  // r_reco->SetMarkerSize(0.8);
  r_reco->Draw();
  r_meas->Draw("same");

  TLine *l1 = new TLine(0,1,500,1);
  l1->SetLineStyle(7);
  l1->Draw();

  TCanvas *c3 = new TCanvas("c3","c3",800,800);
  c3->cd();
  TPad *p3 = new TPad("p3","p3",0,0,1,1);
  p3->SetLeftMargin(0.2);
  p3->SetBottomMargin(0.2);
  p3->SetRightMargin(0.2);
  p3->SetLogz();
  p3->Draw();
  p3->cd();
  h_response->SetTitle("");
  h_response->SetStats(0);
  h_response->GetXaxis()->SetTitle("Reconstructed jet #font[52]{p}_{T} [GeV]");
  h_response->GetYaxis()->SetTitle("Truth jet #font[52]{p}_{T} [GeV]");
  h_response->Draw("colz");
  //h_response->GetZaxis()->SetRangeUser(0.000001,7e5);




  TCanvas *c4 = new TCanvas("c4","unfolded b spectra",800,800);
  TPad *p4 = new TPad("p4","p4",0,0.4,1,1);
  TPad *p4_1 = new TPad("p4_1","p4_1",0,0,1,0.4);
  p4->Draw();
  p4->cd();
  p4->SetLeftMargin(0.2);
  p4->SetBottomMargin(0.0);
  p4->SetLogy();

  h_genBJets->SetLineColor(kRed);
  h_recoBJets->SetLineColor(kGreen+2);
  h_unfoldB->SetLineColor(kBlue);

  h_genBJets->SetMarkerColor(kRed);
  h_recoBJets->SetMarkerColor(kGreen+2);
  h_unfoldB->SetMarkerColor(kBlue);

  h_genBJets->SetMarkerStyle(8);
  h_recoBJets->SetMarkerStyle(8);
  h_unfoldB->SetMarkerStyle(8);

  h_genBJets->GetXaxis()->SetLabelSize(0.0);
  h_genBJets->GetXaxis()->SetTitleSize(0.0);

  h_genBJets->SetStats(0);
  h_genBJets->GetYaxis()->SetTitle("Entries");
  h_genBJets->SetTitle("");
  h_genBJets->Draw();
  h_recoBJets->Draw("same");
  h_unfoldB->Draw("same");

  TLegend *leg2 = new TLegend(0.6,0.3,0.85,0.55);
  leg2->SetBorderSize(0.0);
  leg2->AddEntry(h_genBJets,"truth");
  leg2->AddEntry(h_recoBJets,"measured");
  leg2->AddEntry(h_unfoldB,"unfolded");
  leg2->Draw();

  
  la->SetTextFont(42);
  la->SetTextSize(0.034);
  la->DrawLatexNDC(0.6,0.85,"PYTHIA #sqrt{#font[52]{s}} = 5 TeV");
  la->DrawLatexNDC(0.6,0.78,"Bayesian unfolding via RooUnfold");


  c4->cd();
  p4_1->Draw();
  p4_1->cd();
  p4_1->SetLeftMargin(0.2);
  p4_1->SetBottomMargin(0.25);
  p4_1->SetTopMargin(0.0);

  TH1D *r_unfoldB = (TH1D*) h_unfoldB->Clone("r_unfoldB");
  r_unfoldB->Divide(h_unfoldB,h_genBJets,1,1,"B");

  TH1D *r_recoBJets = (TH1D*) h_recoBJets->Clone("r_recoBJets");
  r_recoBJets->Divide(h_recoBJets,h_genBJets,1,1,"B");
  
  r_unfoldB->GetYaxis()->SetTitle("unfold / truth");
  r_unfoldB->GetXaxis()->SetTitle("#font[52]{p}_{T}^{jet} [GeV]");
  r_unfoldB->GetXaxis()->SetLabelSize(0.06);
  r_unfoldB->GetXaxis()->SetTitleSize(0.07);
  r_unfoldB->GetYaxis()->SetLabelSize(0.06);
  r_unfoldB->GetYaxis()->SetTitleSize(0.07);
  r_unfoldB->SetTitle("");
  r_unfoldB->SetStats(0);
  r_unfoldB->GetYaxis()->SetRangeUser(0.0,2.0);

  // r_reco->SetLineColor(kBlack);
  // r_reco->SetMarkerColor(kBlack);
  // r_reco->SetMarkerStyle(24);
  // r_reco->SetMarkerSize(0.8);
  r_unfoldB->Draw();
  r_recoBJets->Draw("same");

  l1->SetLineStyle(7);
  l1->Draw();


}
