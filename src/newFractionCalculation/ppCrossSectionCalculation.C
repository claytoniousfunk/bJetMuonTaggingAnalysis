#include "../../headers/functions/divideByBinwidth.h"
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#endif

void ppCrossSectionCalculation(){

  TFile *f = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet80HLT_mu12_pTmu-14_tight_jetTrkMaxFilter_2025-12-9.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-10-21.root");

  TFile *f_pub = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1848440-v1-Figure_5-3.root");
  TH1D *h_pub, *h_pub_err, *h_pub_orig;
  TDirectoryFile *dir = (TDirectoryFile*) f_pub->Get("Figure 5-3");
  h_pub = (TH1D*) dir->Get("Hist1D_y5");
  h_pub_orig = (TH1D*) dir->Get("Hist1D_y5");
  h_pub_err = (TH1D*) dir->Get("Hist1D_y5_e1plus");
  h_pub->SetLineColor(kRed-4);
  for(int i = 0; i < h_pub->GetSize(); i++){
    h_pub->SetBinContent(i,h_pub_orig->GetBinContent(i));
    h_pub->SetBinError(i,h_pub_err->GetBinContent(i));
  }
  
  //h_pub->Draw();


  TH1D *h;

  f->GetObject("h_inclRecoJetPt",h);

  
  TH2D *h_response;

  f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets",h_response);

  TH1D *h_meas, *h_truth;

  h_meas = (TH1D*) h_response->ProjectionX();
    
  h_truth = (TH1D*) h_response->ProjectionY();

  RooUnfoldResponse response(h_meas,h_truth,h_response,"response","my response",0);


  
  RooUnfoldBayes unfold(&response, h, 1);

  TH1D* h_unfold= (TH1D*) unfold.Hunfold();
  //TH1D *h_unfold = (TH1D*) h->Clone("h_unfold");
  
  h_unfold->Scale(1./(299490.144921629071)); // luminosity scale [1/nb]

  const int N_edge = 5;
  double newAxis[N_edge] = {200,250,300,400,500};
  h_unfold = (TH1D*) h_unfold->Rebin(N_edge-1,"h_unfold",newAxis);
  divideByBinwidth(h_unfold); // pT scale


  h_unfold->Scale(1./3.2); // eta scale

  

  TCanvas *c = new TCanvas("c","canvas",700,700);
  c->cd();
  TPad *p = new TPad("p","p",0,0,1,1);
  p->SetLeftMargin(0.15);
  p->SetBottomMargin(0.15);
  //p->SetLogy();
  //p->SetLogx();
  p->Draw();
  p->cd();
  h_unfold->SetTitle("");
  h_unfold->SetStats(0);
  h_unfold->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_unfold->GetYaxis()->SetTitle("d^{2}#it{#sigma}^{jet}_{pp} / d#it{p}_{T}d#it{#eta} [nb/GeV]");
  h_unfold->GetXaxis()->SetRangeUser(200,500);
  
  h_unfold->Draw();
  h_pub->Draw("same");



  TH1D *r = (TH1D*) h_unfold->Clone("r");
  for(int i = 0; i < h_pub->GetSize(); i++){
    cout << "h_pub(" << i << ") = " << h_pub->GetBinContent(i) << "\n";
    cout << "h_unfold(" << i << ") = " << h_unfold->GetBinContent(i) << "\n";
    r->SetBinContent(i,h_unfold->GetBinContent(i)/h_pub->GetBinContent(i));
      
  }
  r->Divide(h_unfold,h_pub,1,1,"");

  TCanvas *c2 = new TCanvas("c2","c2",700,700);
  c2->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,1);
  p2->SetLeftMargin(0.15);
  p2->SetBottomMargin(0.15);
  p2->Draw();
  p2->cd();
  r->SetTitle("");
  r->SetStats(0);
  r->GetXaxis()->SetTitle("Reco Jet #it{p}_{T} [GeV]");
  r->GetYaxis()->SetTitle("Ratio");
  r->GetXaxis()->SetRangeUser(200,500);
  
  r->Draw();

  

}
