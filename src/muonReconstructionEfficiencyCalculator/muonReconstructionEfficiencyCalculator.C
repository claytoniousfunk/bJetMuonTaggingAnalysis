#include "../../headers/goldenFileNames.h"
#include "../../headers/functions/divideByBinwidth.h"

TFile *f1, *f2;
TH1D *n1, *n2, *n3;
TH1D *d1, *d2, *d3;
TH1D *N1, *N2, *N3;
TH1D *D1, *D2, *D3;

void muonReconstructionEfficiencyCalculator(){

  f1 = TFile::Open(goldenFile_PYTHIA_muonReco_bJets);
  f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_muonReco_bJets);

  f1->GetObject("h_matchedGenMuonPt",n1);
  f1->GetObject("h_inclGenMuonPt",d1);

  f2->GetObject("h_matchedGenMuonPt_C2",n2);
  f2->GetObject("h_inclGenMuonPt_C2",d2);

  f2->GetObject("h_matchedGenMuonPt_C1",n3);
  f2->GetObject("h_inclGenMuonPt_C1",d3);

  f1->GetObject("h_matchedGenMuonEta",N1);
  f1->GetObject("h_inclGenMuonEta",D1);

  f2->GetObject("h_matchedGenMuonEta_C2",N2);
  f2->GetObject("h_inclGenMuonEta_C2",D2);

  f2->GetObject("h_matchedGenMuonEta_C1",N3);
  f2->GetObject("h_inclGenMuonEta_C1",D3);

  const int NPtEdges = 10;
  double newPtAxis[NPtEdges] = {5,6,7,8,9,12,16,21,30,40};

  const int NEtaEdges = 11;
  double newEtaAxis[NEtaEdges] = {-2,-1.6,-1.2,-0.8,-0.4,0,0.4,0.8,1.2,1.6,2};

  // pt histograms
  TH1D *n1r = (TH1D*) n1->Rebin(NPtEdges-1,"n1r",newPtAxis);
  TH1D *d1r = (TH1D*) d1->Rebin(NPtEdges-1,"d1r",newPtAxis);

  TH1D *n2r = (TH1D*) n2->Rebin(NPtEdges-1,"n2r",newPtAxis);
  TH1D *d2r = (TH1D*) d2->Rebin(NPtEdges-1,"d2r",newPtAxis);

  TH1D *n3r = (TH1D*) n3->Rebin(NPtEdges-1,"n3r",newPtAxis);
  TH1D *d3r = (TH1D*) d3->Rebin(NPtEdges-1,"d3r",newPtAxis);

  // eta histograms
  TH1D *N1r = (TH1D*) N1->Rebin(NEtaEdges-1,"N1r",newEtaAxis);
  TH1D *D1r = (TH1D*) D1->Rebin(NEtaEdges-1,"D1r",newEtaAxis);

  TH1D *N2r = (TH1D*) N2->Rebin(NEtaEdges-1,"N2r",newEtaAxis);
  TH1D *D2r = (TH1D*) D2->Rebin(NEtaEdges-1,"D2r",newEtaAxis);

  TH1D *N3r = (TH1D*) N3->Rebin(NEtaEdges-1,"N3r",newEtaAxis);
  TH1D *D3r = (TH1D*) D3->Rebin(NEtaEdges-1,"D3r",newEtaAxis);
  
  divideByBinwidth(n1r);
  divideByBinwidth(d1r);
  divideByBinwidth(n2r);
  divideByBinwidth(d2r);
  divideByBinwidth(n3r);
  divideByBinwidth(d3r);

  divideByBinwidth(N1r);
  divideByBinwidth(D1r);
  divideByBinwidth(N2r);
  divideByBinwidth(D2r);
  divideByBinwidth(N3r);
  divideByBinwidth(D3r);

  TGraphAsymmErrors *g1 = new TGraphAsymmErrors();
  g1->Divide(n1r,d1r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *g2 = new TGraphAsymmErrors();
  g2->Divide(n2r,d2r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *g3 = new TGraphAsymmErrors();
  g3->Divide(n3r,d3r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *G1 = new TGraphAsymmErrors();
  G1->Divide(N1r,D1r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *G2 = new TGraphAsymmErrors();
  G2->Divide(N2r,D2r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *G3 = new TGraphAsymmErrors();
  G3->Divide(N3r,D3r,"cl=0.683 b(1,1) mode");


  g1->SetMarkerStyle(22);
  g1->SetMarkerColor(kBlack);
  g1->SetLineColor(kBlack);

  g2->SetMarkerStyle(20);
  g2->SetMarkerColor(kRed-4);
  g2->SetLineColor(kRed-4);

  g3->SetMarkerStyle(21);
  g3->SetMarkerColor(kBlue-4);
  g3->SetLineColor(kBlue-4);

  G1->SetMarkerStyle(22);
  G1->SetMarkerColor(kBlack);
  G1->SetLineColor(kBlack);

  G2->SetMarkerStyle(20);
  G2->SetMarkerColor(kRed-4);
  G2->SetLineColor(kRed-4);

  G3->SetMarkerStyle(21);
  G3->SetMarkerColor(kBlue-4);
  G3->SetLineColor(kBlue-4);

  TMultiGraph *mg_pt = new TMultiGraph();

  mg_pt->Add(g1);
  mg_pt->Add(g2);
  mg_pt->Add(g3);

  TMultiGraph *mg_eta = new TMultiGraph();

  mg_eta->Add(G1);
  mg_eta->Add(G2);
  mg_eta->Add(G3);
  

  

  TCanvas *c_pt = new TCanvas("c_pt","c_pt",700,700);
  c_pt->cd();
  TPad *p_pt = new TPad("p_pt","p_pt",0,0,1,1);
  p_pt->SetLeftMargin(0.2);
  p_pt->SetBottomMargin(0.2);
  p_pt->Draw();
  p_pt->cd();


  mg_pt->GetXaxis()->SetRangeUser(0,newPtAxis[NPtEdges-1]);
  mg_pt->GetYaxis()->SetRangeUser(0.5,1);
  mg_pt->GetXaxis()->SetTitleSize(0.05);
  mg_pt->GetYaxis()->SetTitleSize(0.05);
  mg_pt->GetXaxis()->SetLabelSize(0.04);
  mg_pt->GetYaxis()->SetLabelSize(0.04);
  mg_pt->GetYaxis()->SetTitle("Reco+ID efficiency");
  mg_pt->GetXaxis()->SetTitle("Muon #font[52]{p}_{T} [GeV]");
  mg_pt->SetTitle("");
  mg_pt->Draw("AP ep");
  TLatex *la = new TLatex();
  la->SetTextSize(0.032);
  la->SetTextFont(42);
  TString sampleName = "#scale[1.2]{#font[62]{CMS}} #font[52]{Preliminary}                        #sqrt{s_{NN}} = 5.02 TeV";
  TString muonInfo = "Muon reconstruction";
  la->DrawLatexNDC(0.21,0.92,sampleName);
  la->SetTextSize(0.03);
  //la->DrawLatexNDC(0.21,0.9,triggerName);
  la->DrawLatexNDC(0.25,0.5,muonInfo);
  la->DrawLatexNDC(0.25,0.46,"Tight muon ID");
  la->DrawLatexNDC(0.25,0.42,"Tagged to #font[52]{b}-jets, #font[52]{p}_{T}^{jet} > 60 GeV, |#eta^{jet}| < 1.6");

  TLegend *leg = new TLegend(0.22,0.25,0.5,0.38);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.032);
  leg->AddEntry(g1,"PYTHIA","p");
  leg->AddEntry(g2,"PYTHIA+HYDJET 30-90%","p");
  leg->AddEntry(g3,"PYTHIA+HYDJET 0-30%","p");
  leg->Draw();

  TCanvas *c_eta = new TCanvas("c_eta","c_eta",700,700);
  c_eta->cd();
  TPad *p_eta = new TPad("p_eta","p_eta",0,0,1,1);
  p_eta->SetLeftMargin(0.2);
  p_eta->SetBottomMargin(0.2);
  p_eta->Draw();
  p_eta->cd();

  mg_eta->GetXaxis()->SetRangeUser(newEtaAxis[0],newEtaAxis[NEtaEdges-1]);
  mg_eta->GetYaxis()->SetRangeUser(0.5,1);
  mg_eta->GetXaxis()->SetTitleSize(0.05);
  mg_eta->GetYaxis()->SetTitleSize(0.05);
  mg_eta->GetXaxis()->SetLabelSize(0.04);
  mg_eta->GetYaxis()->SetLabelSize(0.04);
  mg_eta->GetYaxis()->SetTitle("Reco+ID efficiency");
  mg_eta->GetXaxis()->SetTitle("Muon #eta");
  mg_eta->SetTitle("");
  mg_eta->Draw("AP ep");
  la->SetTextSize(0.032);
  la->DrawLatexNDC(0.21,0.92,sampleName);
  la->SetTextSize(0.03);
  //la->DrawLatexNDC(0.21,0.9,triggerName);
  la->DrawLatexNDC(0.25,0.5,muonInfo);
  la->DrawLatexNDC(0.25,0.46,"Tight muon ID");
  la->DrawLatexNDC(0.25,0.42,"Tagged to #font[52]{b}-jets, #font[52]{p}_{T}^{jet} > 60 GeV, |#eta^{jet}| < 1.6");

  leg->Draw();

  c_pt->SaveAs("../../figures/muonReconstructionEfficiency/muonPt_bJets.pdf");
  c_eta->SaveAs("../../figures/muonReconstructionEfficiency/muonEta_bJets.pdf");


  
}
