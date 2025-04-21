
#include "../../../headers/functions/divideByBinwidth.h"

void trigger_turn_on(){


  TFile *f1 = TFile::Open("../../../rootFiles/scanningOutput/HYDJET/localScans/HYDJET_trigger_scan_mu7.root");
  TFile *f2 = TFile::Open("../../../rootFiles/scanningOutput/PbPb/platinum/PbPb_MinBias_triggerEffScan_mu12_tight.root");

  
	
  //TString centInfo = "#font[62]{pp}";
  TString centInfo = "#font[62]{Cent. 0-30%}";
  //TString centInfo = "#font[62]{Cent. 30-90%}";
  TString trigInfo = "HLT_HIL3Mu7_NHitQ10_v1";
  TString muonInfo = "Tight Muon ID, |#eta^{#mu}| < 2.0";


  
  TH1D *N1, *N2, *N3, *N4;
  TH1D *N1_add, *N2_add, *N3_add, *N4_add;

  
  TH1D *D1, *D2, *D3, *D4;
  TH1D *D1_add, *D2_add, *D3_add, *D4_add;
	
  f1->GetObject("muPt_trigOn_C1",N1);
  f1->GetObject("muPt_trigOn_C2",N1_add);
  N1->Add(N1_add);
  
  f1->GetObject("muPt_all_C1",D1);
  f1->GetObject("muPt_all_C2",D1_add);
  D1->Add(D1_add);

	
  f2->GetObject("muPt_trigOn_C1",N2);
  f2->GetObject("muPt_trigOn_C2",N2_add);
  N2->Add(N2_add);
  
  f2->GetObject("muPt_all_C1",D2);
  f2->GetObject("muPt_all_C2",D2_add);
  D2->Add(D2_add);


  // const int NPtEdges = 11;
  // double newAxis[NPtEdges] = {3,4,5,6,7,8,9,12,16,21,30};


  const int NPtEdges = 22;
  double newAxis[NPtEdges] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,20,24,30};

  
  TH1D *n1, *n2;
  TH1D *d1, *d2;

  n1 = (TH1D*) N1->Rebin(NPtEdges-1,"n1",newAxis);
  d1 = (TH1D*) D1->Rebin(NPtEdges-1,"d1",newAxis);
  n2 = (TH1D*) N2->Rebin(NPtEdges-1,"n2",newAxis);
  d2 = (TH1D*) D2->Rebin(NPtEdges-1,"d2",newAxis);

  

  
	
	
  double xx = 0.01;
  double yy = 1.0;
  /*
    for(int k = 0; k < 4; k++){
    n1->SetBinContent(k,xx);
    n2->SetBinContent(k,2.*xx);
    d1->SetBinContent(k,yy);
    d2->SetBinContent(k,yy);
    }
  */


  TCanvas *c = new TCanvas("c","c",700,700);
  c->cd();
	
  TPad *p1 = new TPad("p1","p1",0,0.4,1,1);
  TPad *p2 = new TPad("p2","p2",0,0,1,0.4);
  p1->SetLeftMargin(0.2);
  p2->SetLeftMargin(0.2);
  p1->SetBottomMargin(0.0);
  p2->SetBottomMargin(0.2);
  p1->SetTopMargin(0.1);
  p2->SetTopMargin(0.0);
  p1->Draw();
  p2->Draw();
  p1->cd();



  TGraphAsymmErrors *G1 = new TGraphAsymmErrors();
  G1->Divide(n1,d1,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *G2 = new TGraphAsymmErrors();
  G2->Divide(n2,d2,"cl=0.683 b(1,1) mode");
	
  G1->SetMarkerColor(kRed-4);
  G1->SetLineColor(kRed-4);
  G1->SetMarkerStyle(20);
	
  G2->SetMarkerColor(kBlue-4);
  G2->SetLineColor(kBlue-4);
  G2->SetMarkerStyle(21);

  TH1D *rr1 = (TH1D*) n1->Clone("rr1"); // first input into the double ratio calculation
  rr1->Divide(n1,d1,1,1,"B");
  TH1D *rr2 = (TH1D*) n2->Clone("rr2"); // second input into the double ratio calculation
  rr2->Divide(n2,d2,1,1,"B");
  TH1D *rr = (TH1D*) rr2->Clone("rr"); // final double ratio result
  rr->Divide(rr2,rr1,1,1,"");
	

 

  TMultiGraph *mg = new TMultiGraph();

  mg->Add(G1);
  mg->Add(G2);

  TLine *li = new TLine();
  li->SetLineStyle(7);

  mg->SetTitle("");
  mg->GetXaxis()->SetTitleSize(0.0);
  mg->GetYaxis()->SetTitleSize(0.07);
  mg->GetXaxis()->SetLabelSize(0.0);
  mg->GetYaxis()->SetLabelSize(0.055);
  mg->GetXaxis()->SetTitle("Muon #font[52]{p}_{T} [GeV]");
  mg->GetYaxis()->SetTitle("Trigger efficiency");
  mg->GetXaxis()->SetRangeUser(3,30);
  mg->GetYaxis()->SetRangeUser(0,1);	
  mg->Draw("AP");
  mg->GetXaxis()->SetRangeUser(3,30);

  //li->DrawLine(7,0,7,1);

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.05);
  la->DrawLatexNDC(0.5,0.4,centInfo);
  la->SetTextSize(0.045);
  la->DrawLatexNDC(0.5,0.34,trigInfo);
  la->DrawLatexNDC(0.5,0.28,muonInfo);
	
  TLegend *leg = new TLegend(0.5,0.12,0.7,0.25);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.045);
  leg->AddEntry(G1,"HYDJET MinBias","p");
  leg->AddEntry(G2,"PbPb MinBias","p");
  //leg->AddEntry(G1,"PYTHIA diJet","p");
  //leg->AddEntry(G2,"pp MinBias","p");
  leg->Draw();

  p2->cd();
  rr->SetMarkerColor(kBlack);
  rr->SetLineColor(kBlack);
  rr->SetMarkerStyle(20);
  rr->Draw();
  rr->SetTitle("");
  rr->GetXaxis()->SetTitleSize(0.09);
  rr->GetYaxis()->SetTitleSize(0.09);
  rr->GetXaxis()->SetLabelSize(0.08);
  rr->GetYaxis()->SetLabelSize(0.08);
  rr->GetXaxis()->SetTitle("Muon #font[52]{p}_{T} [GeV]");
  rr->GetYaxis()->SetTitle("DATA/MC");
  rr->GetXaxis()->SetRangeUser(3,30);
  rr->GetYaxis()->SetRangeUser(0.5,1.5);
  rr->Draw();

	
  li->DrawLine(3,1,30,1);
  




}
