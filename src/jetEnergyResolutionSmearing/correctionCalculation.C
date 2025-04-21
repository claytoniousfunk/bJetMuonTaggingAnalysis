// general ROOT/C includes
#include <iostream>
#include "TFile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TRandom2.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TProfile2D.h"
#include <TF1.h>
#include "assert.h"
#include <fstream>
#include "TMath.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TMath.h"
#include <TNtuple.h>
#include "TChain.h"
#include <TString.h>
#include <TLatex.h>
#include <TCut.h>
#include "TDatime.h"
#include <vector>
#include "TCanvas.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TLine.h"


TFile *input_PbPb, *input_pp;
TH2D *XX0, *XX1, *XX2, *XX3, *XX4;  // original 2D spectra (for MC flavor-projection)
TH1D *X0, *X1, *X2, *X3, *X4;  // original spectra
TH1D *B0, *B1, *B2; // b-jets
TH1D *Bbar0, *Bbar1, *Bbar2; // bbar-jets
TH1D *Bgs0, *Bgs1, *Bgs2; // bGS-jets
TH1D *h0, *h1, *h2, *h3, *h4; // sampled spectra
TH1D *s0, *s1, *s2, *s3, *s4; // smeared spectra
TH1D *r0, *r1, *r2, *r3, *r4; // ratios
double C_incl_0, C_incl_1, C_incl_2, C_incl_3, C_incl_4; // fit parameters
double S_incl_0, S_incl_1, S_incl_2, S_incl_3, S_incl_4;
double N_incl_0, N_incl_1, N_incl_2, N_incl_3, N_incl_4;
double C_muTaggedB_0, C_muTaggedB_1, C_muTaggedB_2, C_muTaggedB_3, C_muTaggedB_4; // fit parameters
double S_muTaggedB_0, S_muTaggedB_1, S_muTaggedB_2, S_muTaggedB_3, S_muTaggedB_4;
double N_muTaggedB_0, N_muTaggedB_1, N_muTaggedB_2, N_muTaggedB_3, N_muTaggedB_4;
TF1 *smear_fxn_pp, *smear_fxn_C1, *smear_fxn_C2;
TF1 *JER_fxn_incl_pp, *JER_fxn_incl_C1, *JER_fxn_incl_C2, *JER_fxn_incl_C3, *JER_fxn_incl_C4;
TF1 *smear_fxn_muTaggedB_pp, *smear_fxn_muTaggedB_C1, *smear_fxn_muTaggedB_C2, *smear_fxn_muTaggedB_C3, *smear_fxn_muTaggedB_C4;
TF1 *JER_fxn_muTaggedB_pp, *JER_fxn_muTaggedB_C1, *JER_fxn_muTaggedB_C2, *JER_fxn_muTaggedB_C3, *JER_fxn_muTaggedB_C4;
TRandom *randomGenerator;
TLine *line;
TLatex *la;

void normalize_by_highPt(TH1D *h, double pt_norm){
  
  h->Scale(1./h->Integral(h->GetXaxis()->FindBin(pt_norm),h->GetXaxis()->FindBin(1000.)));
  //return h;
  
}

void normalize_by_highPt(TH1D *h, double pt_norm_1, double pt_norm_2){
  
  h->Scale(1./h->Integral(h->GetXaxis()->FindBin(pt_norm_1),h->GetXaxis()->FindBin(pt_norm_2)));
  //return h;
  
}

void stylize_histos(TH1D *h0, TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  h0->SetLineColor(kBlack);
  h1->SetLineColor(kMagenta-7);
  h2->SetLineColor(kGreen+2);
  h3->SetLineColor(kBlue-4);
  h4->SetLineColor(kRed-4);

  h0->SetLineWidth(2);
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);

  
}

void stylize_histos(TH1D *h0, TH1D *h1, TH1D *h2){

  h0->SetLineColor(kBlack);
  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);

  h0->SetLineWidth(2);
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  
}

TH1D* divideByBinwidth(TH1D* h_in){

  for(int k = 0; k < h_in->GetSize(); k++){

    double value = h_in->GetBinContent(k);
    double error = h_in->GetBinError(k);
    double width = h_in->GetBinWidth(k);

    if(width != 0){

      h_in->SetBinContent(k,value/width);
      h_in->SetBinError(k,error/width);

    }

  }

  return h_in;

}


void correctionCalculation(){
  

  // smear-dependent variables
  TString bottom_y_title = "centrality / 50-90%";
  //TString bottom_y_title = "centrality / smeared 50-90%";
  // display smearing status
  TString smearing_status = "";
  //TString smearing_status = "No smearing";
  //TString smearing_status = "Smearing on 50-90%";

  // declare some objects
  randomGenerator = new TRandom2();
  line = new TLine();
  la = new TLatex();


  // /////////////////////     the data option
  // input_pp = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/platinum/pp_MinBias_mu12_tight_pTmu-14_evtFilterFix_newJetBins.root");
  // input_PbPb = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/official/PbPb_MinBias_scan_mu12_tight_pTmu-14_evtFilterFix_hiHFcut.root");

  // input_pp->GetObject("h_inclRecoJetPt",X0");
  // input_PbPb->GetObject("h_inclRecoJetPt_C1",X1);
  // input_PbPb->GetObject("h_inclRecoJetPt_C2",X2);
  // input_PbPb->GetObject("h_inclRecoJetPt_C3",X3);
  // input_PbPb->GetObject("h_inclRecoJetPt_C4",X4);

  // TString la_leg_title = "Data";


  // /////////////////////     the mc option
  input_pp = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/platinum/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_newJetBins.root");
  input_PbPb = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/official/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_newJetBins.root");

  input_pp->GetObject("h_inclRecoJetPt_flavor",XX0);
  input_PbPb->GetObject("h_inclRecoJetPt_flavor_C1",XX1);
  input_PbPb->GetObject("h_inclRecoJetPt_flavor_C2",XX2);
  

  X0 = (TH1D*) XX0->ProjectionX("X0");
  X1 = (TH1D*) XX1->ProjectionX("X1");
  X2 = (TH1D*) XX2->ProjectionX("X2");

  B0 = (TH1D*) XX0->ProjectionX("B0",XX0->ProjectionY()->FindBin(5.1),XX0->ProjectionY()->FindBin(5.9));
  Bbar0 = (TH1D*) XX0->ProjectionX("Bbar0",XX0->ProjectionY()->FindBin(-4.9),XX0->ProjectionY()->FindBin(-4.1));
  Bgs0 = (TH1D*) XX0->ProjectionX("Bgs0",XX0->ProjectionY()->FindBin(17.1),XX0->ProjectionY()->FindBin(17.9));

  B1 = (TH1D*) XX0->ProjectionX("B1",XX0->ProjectionY()->FindBin(5.1),XX0->ProjectionY()->FindBin(5.9));
  Bbar1 = (TH1D*) XX0->ProjectionX("Bbar1",XX0->ProjectionY()->FindBin(-4.9),XX0->ProjectionY()->FindBin(-4.1));
  Bgs1 = (TH1D*) XX0->ProjectionX("Bgs1",XX0->ProjectionY()->FindBin(17.1),XX0->ProjectionY()->FindBin(17.9));

  B2 = (TH1D*) XX0->ProjectionX("B2",XX0->ProjectionY()->FindBin(5.1),XX0->ProjectionY()->FindBin(5.9));
  Bbar2 = (TH1D*) XX0->ProjectionX("Bbar2",XX0->ProjectionY()->FindBin(-4.9),XX0->ProjectionY()->FindBin(-4.1));
  Bgs2 = (TH1D*) XX0->ProjectionX("Bgs2",XX0->ProjectionY()->FindBin(17.1),XX0->ProjectionY()->FindBin(17.9));

  B0->Add(Bbar0); B0->Add(Bgs0);
  B1->Add(Bbar1); B1->Add(Bgs1);
  B2->Add(Bbar2); B2->Add(Bgs2);
  
  TString la_leg_title = "Simulation";


  // original histograms
  h0 = new TH1D("h0","",100,0,500);
  h1 = new TH1D("h1","",100,0,500);
  h2 = new TH1D("h2","",100,0,500);
 

  // shifted histograms
  s0 = new TH1D("s0","",100,0,500);
  s1 = new TH1D("s1","",100,0,500);
  s2 = new TH1D("s2","",100,0,500);
  
  stylize_histos(h0,h1,h2);
  stylize_histos(s0,s1,s2);
  h0->SetLineStyle(7);
  h1->SetLineStyle(7);
  h2->SetLineStyle(7);

 
  // declare JER-fit parameters
  C_incl_0 = 0.055038;
  C_incl_1 = 0.0336093;
  C_incl_2 = 0.0049454;

  S_incl_0 = 0.872444;
  S_incl_1 = 1.28817;
  S_incl_2 = 1.34148;

  N_incl_0 = 0.108847;
  N_incl_1 = 14.2742;
  N_incl_2 = 2.89153;

  C_muTaggedB_0 = 0.06563;
  C_muTaggedB_1 = 0.012635;
  C_muTaggedB_2 = 0.0239102;

  S_muTaggedB_0 = 0.991014;
  S_muTaggedB_1 = 1.82447;
  S_muTaggedB_2 = 1.43697;

  N_muTaggedB_0 = 0.0986609;
  N_muTaggedB_1 = 10.1138;
  N_muTaggedB_2 = 0.824199;



  // define JER functions

  JER_fxn_incl_pp = new TF1("JER_fxn_incl_pp", "TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  JER_fxn_incl_pp->SetParameter(0,C_incl_0);
  JER_fxn_incl_pp->SetParameter(1,S_incl_0);
  JER_fxn_incl_pp->SetParameter(2,N_incl_0);

  JER_fxn_incl_C1 = new TF1("JER_fxn_incl_C1", "TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  JER_fxn_incl_C1->SetParameter(0,C_incl_1);
  JER_fxn_incl_C1->SetParameter(1,S_incl_1);
  JER_fxn_incl_C1->SetParameter(2,N_incl_1);

  JER_fxn_incl_C2 = new TF1("JER_fxn_incl_C2", "TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  JER_fxn_incl_C2->SetParameter(0,C_incl_2);
  JER_fxn_incl_C2->SetParameter(1,S_incl_2);
  JER_fxn_incl_C2->SetParameter(2,N_incl_2);

  JER_fxn_muTaggedB_pp = new TF1("JER_fxn_muTaggedB_pp", "TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  JER_fxn_muTaggedB_pp->SetParameter(0,C_muTaggedB_0);
  JER_fxn_muTaggedB_pp->SetParameter(1,S_muTaggedB_0);
  JER_fxn_muTaggedB_pp->SetParameter(2,N_muTaggedB_0);

  JER_fxn_muTaggedB_C1 = new TF1("JER_fxn_muTaggedB_C1", "TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  JER_fxn_muTaggedB_C1->SetParameter(0,C_muTaggedB_1);
  JER_fxn_muTaggedB_C1->SetParameter(1,S_muTaggedB_1);
  JER_fxn_muTaggedB_C1->SetParameter(2,N_muTaggedB_1);

  JER_fxn_muTaggedB_C2 = new TF1("JER_fxn_muTaggedB_C2", "TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  JER_fxn_muTaggedB_C2->SetParameter(0,C_muTaggedB_2);
  JER_fxn_muTaggedB_C2->SetParameter(1,S_muTaggedB_2);
  JER_fxn_muTaggedB_C2->SetParameter(2,N_muTaggedB_2);

  // JER_fxn_incl_pp->GetYaxis()->SetRangeUser(0,0.5);
  // JER_fxn_incl_pp->Draw();
  // JER_fxn_muTaggedB_pp->SetLineStyle(7);
  // JER_fxn_muTaggedB_pp->Draw("same");

  // JER_fxn_incl_C2->GetYaxis()->SetRangeUser(0,0.5);
  // JER_fxn_incl_C2->Draw();
  // JER_fxn_muTaggedB_C2->SetLineStyle(7);
  // JER_fxn_muTaggedB_C2->Draw("same");

  // JER_fxn_incl_C1->GetYaxis()->SetRangeUser(0,0.5);
  // JER_fxn_incl_C1->Draw();
  // JER_fxn_muTaggedB_C1->SetLineStyle(7);
  // JER_fxn_muTaggedB_C1->Draw("same");





  // define the smear functions
  smear_fxn_pp = new TF1("smear_fxn_pp","TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x)) / TMath::Sqrt([3]*[3] + [4]*[4]/x + [5]*[5]/(x*x))",0,500);
  smear_fxn_pp->SetParameter(0,C_muTaggedB_0);
  smear_fxn_pp->SetParameter(1,S_muTaggedB_0);
  smear_fxn_pp->SetParameter(2,N_muTaggedB_0);
  smear_fxn_pp->SetParameter(3,C_incl_0);
  smear_fxn_pp->SetParameter(4,S_incl_0);
  smear_fxn_pp->SetParameter(5,N_incl_0);

  smear_fxn_C1 = new TF1("smear_fxn_C1","TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x)) / TMath::Sqrt([3]*[3] + [4]*[4]/x + [5]*[5]/(x*x))",0,500);
  smear_fxn_C1->SetParameter(0,C_muTaggedB_1);
  smear_fxn_C1->SetParameter(1,S_muTaggedB_1);
  smear_fxn_C1->SetParameter(2,N_muTaggedB_1);
  smear_fxn_C1->SetParameter(3,C_incl_1);
  smear_fxn_C1->SetParameter(4,S_incl_1);
  smear_fxn_C1->SetParameter(5,N_incl_1);

  smear_fxn_C2 = new TF1("smear_fxn_C2","TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x)) / TMath::Sqrt([3]*[3] + [4]*[4]/x + [5]*[5]/(x*x))",0,500);
  smear_fxn_C2->SetParameter(0,C_muTaggedB_2);
  smear_fxn_C2->SetParameter(1,S_muTaggedB_2);
  smear_fxn_C2->SetParameter(2,N_muTaggedB_2);
  smear_fxn_C2->SetParameter(3,C_incl_2);
  smear_fxn_C2->SetParameter(4,S_incl_2);
  smear_fxn_C2->SetParameter(5,N_incl_2);

  // smear_fxn_pp->GetYaxis()->SetRangeUser(0.7,1.3);
  // smear_fxn_pp->Draw();

  // smear_fxn_C2->GetYaxis()->SetRangeUser(0.7,1.3);
  // smear_fxn_C2->Draw();

  smear_fxn_C1->GetYaxis()->SetRangeUser(0.7,1.3);
  smear_fxn_C1->Draw();

  
  /*   
  double k0 = 0.0;
  double k1 = 0.0;
  double k2 = 0.0;
  
  double pt0 = 0.0;
  double pt1 = 0.0;
  double pt2 = 0.0;

  double smear_pp = 0.0;
  double smear_C1 = 0.0;
  double smear_C2 = 0.0;

  int N_fill = 1000000;
  //int N_fill = 300000000;
  //int N_fill = 500000000;

  int skip_count = 0;
  
  for(int i = 0; i < N_fill; i++){
    
    // sample a value of pt from C4 to smear
    pt0 = B0->GetRandom();
    pt1 = B1->GetRandom();
    pt2 = B2->GetRandom();
 
    
    if(smear_fxn_pp->Eval(pt0)*smear_fxn_pp->Eval(pt0) < 1 ||
       smear_fxn_C1->Eval(pt1)*smear_fxn_C1->Eval(pt1) < 1 ||
       smear_fxn_C2->Eval(pt2)*smear_fxn_C2->Eval(pt2) < 1){
      //cout << "negative in exponent! skip!" << endl;
      k0 = 0;
      k1 = 0.;
      k2 = 0.;
    }
    else{
      k0 = TMath::Sqrt(smear_fxn_pp->Eval(pt0)*smear_fxn_pp->Eval(pt0) - 1);
      k1 = TMath::Sqrt(smear_fxn_C1->Eval(pt1)*smear_fxn_C1->Eval(pt1) - 1);
      k2 = TMath::Sqrt(smear_fxn_C2->Eval(pt2)*smear_fxn_C2->Eval(pt2) - 1);
    }
    if(i==0){
      cout << "resolution-smearing parameters for event 0:" << endl;
      cout << "k0 = " << k0 << endl;
      cout << "k1 = " << k1 << endl;
      cout << "k2 = " << k2 << endl;
    }
    // calculate the smear on JER_C4 necessary to worsen resolution to central levels
    smear_pp = randomGenerator->Gaus(1.,k0*JER_fxn_incl_pp->Eval(pt0));
    smear_C1 = randomGenerator->Gaus(1.,k1*JER_fxn_incl_C1->Eval(pt1));
    smear_C2 = randomGenerator->Gaus(1.,k2*JER_fxn_incl_C2->Eval(pt2));
    if(i==0){
      cout << "pt-smearing parameters for event 0:" << endl;
      cout << "smear_pp = " << smear_pp << endl;
      cout << "smear_C1 = " << smear_C1 << endl;
      cout << "smear_C2 = " << smear_C2 << endl;
    }
    //skip if something went weird with the smear
    if(smear_pp < 0 || smear_C1 < 0 || smear_C2 < 0){
      //cout << "negative smear value! skip!" << endl;
      skip_count++;
      //cout << "skip count = " << skip_count << endl;
      continue;
    }
    s0->Fill(smear_pp * pt0);
    s1->Fill(smear_C1 * pt1);
    s2->Fill(smear_C2 * pt2);
   
   

    h0->Fill(B0->GetRandom());
    h1->Fill(B1->GetRandom());
    h2->Fill(B2->GetRandom());

  }

  double high_pt_norm_1 = 130.;
  double high_pt_norm_2 = 500.;

  // normalize by high pT point (shape measurement)
  //normalize_by_highPt(h0, high_pt_norm_1);
  //normalize_by_highPt(h1, high_pt_norm_1);
  //normalize_by_highPt(h2, high_pt_norm_1);

  //normalize_by_highPt(s0, high_pt_norm_1);
  //normalize_by_highPt(s1, high_pt_norm_1);
  //normalize_by_highPt(s2, high_pt_norm_1);


  // rebin
  const int N_edge = 30;
  double new_axis[N_edge] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,170,220,320,500};
  h0 = (TH1D*) h0->Rebin(N_edge-1,"h0",new_axis);
  h1 = (TH1D*) h1->Rebin(N_edge-1,"h1",new_axis);
  h2 = (TH1D*) h2->Rebin(N_edge-1,"h2",new_axis);

  s0 = (TH1D*) s0->Rebin(N_edge-1,"s0",new_axis);
  s1 = (TH1D*) s1->Rebin(N_edge-1,"s1",new_axis);
  s2 = (TH1D*) s2->Rebin(N_edge-1,"s2",new_axis);


  // divide by binwidth
  divideByBinwidth(h0);
  divideByBinwidth(h1);
  divideByBinwidth(h2);

  divideByBinwidth(s0);
  divideByBinwidth(s1);
  divideByBinwidth(s2);

  
  // define the ratios
  r0 = (TH1D*) s0->Clone("r0");
  r1 = (TH1D*) s1->Clone("r1");
  r2= (TH1D*) s2->Clone("r2");

  // calculate the ratios
  r0->Divide(s0,h0,1,1,"");
  r1->Divide(s1,h1,1,1,"");
  r2->Divide(s2,h2,1,1,"");


  
  TCanvas *canv = new TCanvas("canv","",700,700);
  canv->cd();
  TPad *p1 = new TPad("p1","p1",0,0.4,1,1);
  TPad *p2 = new TPad("p2","p2",0,0.,1,0.4);
  // pad margin and style
  p1->SetLeftMargin(0.18);
  p2->SetLeftMargin(0.18);
  p1->SetBottomMargin(0.0);
  p2->SetTopMargin(0.0);
  p2->SetBottomMargin(0.2);
  p1->SetLogy();
  p1->Draw();
  p2->Draw();
  // switch to top pad
  p1->cd();
  // set label styles
  double labelSize = 0.05;
  double titleSize = 0.06;
  double lower_pad_label_amplifier = 1.3;
  // y-axis
  s1->GetYaxis()->SetLabelSize(labelSize);
  r1->GetYaxis()->SetLabelSize(lower_pad_label_amplifier*labelSize);
  s1->GetYaxis()->SetTitleSize(titleSize);
  r1->GetYaxis()->SetTitleSize(lower_pad_label_amplifier*titleSize);
  r1->GetYaxis()->SetRangeUser(0.78,1.22);
  //TString top_y_title = Form("1/#it{N}^{recoJet}_{%3.0f < #it{p}_{T} (GeV) < %3.0f} d#it{N}^{recoJet}/d#it{p}_{T}",high_pt_norm_1, high_pt_norm_2);
  TString top_y_title = Form("1/#it{N}^{recoJet}_{#it{p}_{T} (GeV) > %3.0f} d#it{N}^{recoJet}/d#it{p}_{T}",high_pt_norm_1);
  
  
  s1->GetYaxis()->SetTitle(top_y_title);
  r1->GetYaxis()->SetTitle(bottom_y_title);
  // x-axis
  r1->GetXaxis()->SetLabelSize(lower_pad_label_amplifier*labelSize);
  r1->GetXaxis()->SetTitleSize(lower_pad_label_amplifier*titleSize);
  TString x_title = "#it{p}_{T}^{recoJet} [GeV]";
  r1->GetXaxis()->SetTitle(x_title);
  // other style stuff
  s1->SetStats(0);
  r1->SetStats(0);
  // draw the top histograms
  s1->Draw();
  s0->Draw("same");
  s2->Draw("same");
  h0->Draw("same");
  h1->Draw("same");
  h2->Draw("same");
  
  // Write the legend with TLatex
  double la_leg_text_size = 0.05;
  int la_leg_text_font = 62;
  la->SetTextSize(la_leg_text_size);
  la->SetTextFont(la_leg_text_font);
  TString la_leg_title_color = "kBlack";
  TString la_leg_pp_color = "kBlack";
  TString la_leg_C1_color = "kBlue-4";
  TString la_leg_C2_color = "kRed-4";
  // titles
  TString la_leg_pp_title = "pp";
  TString la_leg_C1_title = "PbPb 0-30%";
  TString la_leg_C2_title = "PbPb 30-90%";


  // title coordinates
  double la_leg_title_x_coord = 0.6;
  double la_leg_title_y_coord = 0.8;
  double la_leg_pp_y_coord = 0.72;
  double la_leg_C1_y_coord = 0.64;
  double la_leg_C2_y_coord = 0.56;
  // set color & draw!
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(la_leg_title_x_coord,la_leg_title_y_coord,la_leg_title);
  la->DrawLatexNDC(la_leg_title_x_coord,la_leg_pp_y_coord,la_leg_pp_title);
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(la_leg_title_x_coord,la_leg_C1_y_coord,la_leg_C1_title);
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(la_leg_title_x_coord,la_leg_C2_y_coord,la_leg_C2_title);

  
  double la_smearing_status_x_coord = 0.6;
  double la_smearing_status_y_coord = 0.40;
  la->SetTextColor(kBlack);
  la->SetTextFont(72);
  la->DrawLatexNDC(la_smearing_status_x_coord,la_smearing_status_y_coord,smearing_status); 
  
  // switch to bottom pad
  p2->cd(); 
  // draw the ratio histograms
  r1->Draw();
  r0->Draw("same");
  r2->Draw("same");
  //r4->Draw("same");
  // draw the line
  line->SetLineStyle(2);
  line->DrawLine(0,1,500,1);
  line->SetLineStyle(7);
  line->DrawLine(0,0.95,500,0.95);
  line->DrawLine(0,1.05,500,1.05);

  */
}
