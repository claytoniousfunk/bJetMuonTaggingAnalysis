
#include "../../headers/goldenFileNames.h"
#include "../../headers/functions/divideByBinwidth.h"

TFile *f1, *f2;
TH1D *n1, *n2, *n3;
TH1D *d1, *d2, *d3;
TH1D *N1, *N2, *N3;
TH1D *D1, *D2, *D3;

void muonReconstructionEfficiencyCalculator(){

  f1 = TFile::Open(goldenFile_PYTHIA_muonReco);
  //f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_muonReco);

  f1->GetObject("h_matchedGenMuonPt",n1);
  f1->GetObject("h_inclGenMuonPt",d1);

  f1->GetObject("h_matchedGenMuonEta",N1);
  f1->GetObject("h_inclGenMuonEta",D1);

  const int NPtEdges = 12;
  double newPtAxis[NPtEdges] = {5,6,7,8,9,12,14,16,20,24,30,40};

  TH1D *n1r = (TH1D*) n1->Rebin(NPtEdges-1,"n1r",newPtAxis);
  TH1D *d1r = (TH1D*) d1->Rebin(NPtEdges-1,"d1r",newPtAxis);

  divideByBinwidth(n1r);
  divideByBinwidth(d1r);

  TGraphAsymmErrors *g1 = new TGraphAsymmErrors();
  g1->Divide(n1r,d1r,"cl=0.683 b(1,1) mode");

  TCanvas *c2 = new TCanvas("c2","c2",600,600);
  c2->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,1);
  p2->SetLeftMargin(0.2);
  p2->SetBottomMargin(0.2);
  p2->SetTopMargin(0.18);
  p2->Draw();
  p2->cd();
  g1->SetMarkerStyle(22);
  g1->SetMarkerColor(kBlack);
  g1->SetLineColor(kBlack);

  g1->GetXaxis()->SetRangeUser(0,newPtAxis[NPtEdges-1]);
  g1->GetYaxis()->SetRangeUser(0.7,1);
  g1->GetXaxis()->SetTitleSize(0.06);
  g1->GetYaxis()->SetTitleSize(0.06);
  g1->GetXaxis()->SetLabelSize(0.045);
  g1->GetYaxis()->SetLabelSize(0.045);
  g1->GetYaxis()->SetTitle("Reconstruction efficiency");
  g1->GetXaxis()->SetTitle("Muon #font[52]{p}_{T} [GeV]");
  g1->SetTitle("");
  g1->Draw("AP ep");
  // TLatex *la = new TLatex();
  // la->SetTextSize(0.035);
  // la->SetTextFont(42);
  // la->DrawLatexNDC(0.21,0.95,sampleName);
  // la->SetTextSize(0.03);
  // la->DrawLatexNDC(0.21,0.9,triggerName);
  // la->DrawLatexNDC(0.21,0.85,muonInfo);



  
}
