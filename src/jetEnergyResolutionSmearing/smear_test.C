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


TFile *input;
TH2D *XX1, *XX2, *XX3, *XX4;  // original 2D spectra (for MC flavor-projection)
TH1D *X1, *X2, *X3, *X4;  // original spectra
TH1D *h1, *h2, *h3, *h4; // sampled spectra
TH1D *s1, *s2, *s3, *s4; // smeared spectra
TH1D *r1, *r2, *r3, *r4; // ratios
double C_1, C_2, C_3, C_4; // fit parameters
double S_1, S_2, S_3, S_4;
double N_1, N_2, N_3, N_4;
TF1 *smear_fxn_C1, *smear_fxn_C2, *smear_fxn_C3, *smear_fxn_C4;
TF1 *JER_fxn_C1, *JER_fxn_C2, *JER_fxn_C3, *JER_fxn_C4;
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

void stylize_histos(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  h1->SetLineColor(kMagenta-7);
  h2->SetLineColor(kGreen+2);
  h3->SetLineColor(kBlue-4);
  h4->SetLineColor(kRed-4);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);

  
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


void smear_test(){

  // smear-dependent variables
  //TString bottom_y_title = "centrality / 50-90%";
  TString bottom_y_title = "centrality / smeared 50-90%";
  // display smearing status
  //TString smearing_status = "No smearing";
  TString smearing_status = "Smearing on 50-90%";

  // declare some objects
  randomGenerator = new TRandom2();
  line = new TLine();
  la = new TLatex();

  // input = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/official/PbPb_MinBias_scan_mu12_tight_pTmu-14_evtFilterFix_hiHFcut.root");
  
  // input->GetObject("h_inclRecoJetPt_C1",X1);
  // input->GetObject("h_inclRecoJetPt_C2",X2);
  // input->GetObject("h_inclRecoJetPt_C3",X3);
  // input->GetObject("h_inclRecoJetPt_C4",X4);

  // TString la_leg_title = "Data";
  
  input = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/PH_DiJet_pTjet-5_pThat-15_response_fineCentBins.root");

  input->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",XX1);
  input->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",XX2);
  input->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",XX3);
  input->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",XX4);

  X1 = (TH1D*) XX1->ProjectionX("X1");
  X2 = (TH1D*) XX2->ProjectionX("X2");
  X3 = (TH1D*) XX3->ProjectionX("X3");
  X4 = (TH1D*) XX4->ProjectionX("X4");

  
  TString la_leg_title = "Simulation";



  // original histograms
  h1 = new TH1D("h1","",100,0,500);
  h2 = new TH1D("h2","",100,0,500);
  h3 = new TH1D("h3","",100,0,500);
  h4 = new TH1D("h4","",100,0,500);

  // shifted histograms
  s1 = new TH1D("s1","",100,0,500);
  s2 = new TH1D("s2","",100,0,500);
  s3 = new TH1D("s3","",100,0,500);
  s4 = new TH1D("s4","",100,0,500);

  stylize_histos(h1,h2,h3,h4);
  stylize_histos(s1,s2,s3,s4);

 
  // declare JER-fit parameters
  C_1 = 0.0402379;
  C_2 = 0.0259748;
  C_3 = 0.0332462;
  C_4 = 0.0397072;

  S_1 = 1.17329;
  S_2 = 1.32738;
  S_3 = 1.18583;
  S_4 = 1.06636;

  N_1 = 17.8523;
  N_2 = 10.6855;
  N_3 = 5.33039;
  N_4 = 1.29401;

  // define JER functions
  JER_fxn_C1 = new TF1("JER_fxn_C1", "TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  JER_fxn_C1->SetParameter(0,C_1);
  JER_fxn_C1->SetParameter(1,S_1);
  JER_fxn_C1->SetParameter(2,N_1);

  JER_fxn_C2 = new TF1("JER_fxn_C2", "TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  JER_fxn_C2->SetParameter(0,C_2);
  JER_fxn_C2->SetParameter(1,S_2);
  JER_fxn_C2->SetParameter(2,N_2);

  JER_fxn_C3 = new TF1("JER_fxn_C3", "TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  JER_fxn_C3->SetParameter(0,C_3);
  JER_fxn_C3->SetParameter(1,S_3);
  JER_fxn_C3->SetParameter(2,N_3);

  JER_fxn_C4 = new TF1("JER_fxn_C4", "TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  JER_fxn_C4->SetParameter(0,C_4);
  JER_fxn_C4->SetParameter(1,S_4);
  JER_fxn_C4->SetParameter(2,N_4);


  // define the smear functions
  // smear_fxn_C1 smears C4 to the C1 level
  smear_fxn_C1 = new TF1("smear_fxn_C1","TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x)) / TMath::Sqrt([3]*[3] + [4]*[4]/x + [5]*[5]/(x*x))",0,500);
  smear_fxn_C1->SetParameter(0,C_1);
  smear_fxn_C1->SetParameter(1,S_1);
  smear_fxn_C1->SetParameter(2,N_1);
  smear_fxn_C1->SetParameter(3,C_4);
  smear_fxn_C1->SetParameter(4,S_4);
  smear_fxn_C1->SetParameter(5,N_4);

  // smear_fxn_C2 smears C4 to the C2 level
  smear_fxn_C2 = new TF1("smear_fxn_C2","TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x)) / TMath::Sqrt([3]*[3] + [4]*[4]/x + [5]*[5]/(x*x))",0,500);
  smear_fxn_C2->SetParameter(0,C_2);
  smear_fxn_C2->SetParameter(1,S_2);
  smear_fxn_C2->SetParameter(2,N_2);
  smear_fxn_C2->SetParameter(3,C_4);
  smear_fxn_C2->SetParameter(4,S_4);
  smear_fxn_C2->SetParameter(5,N_4);

  // smear_fxn_C3 smears C4 to the C3 level
  smear_fxn_C3 = new TF1("smear_fxn_C3","TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x)) / TMath::Sqrt([3]*[3] + [4]*[4]/x + [5]*[5]/(x*x))",0,500);
  smear_fxn_C3->SetParameter(0,C_3);
  smear_fxn_C3->SetParameter(1,S_3);
  smear_fxn_C3->SetParameter(2,N_3);
  smear_fxn_C3->SetParameter(3,C_4);
  smear_fxn_C3->SetParameter(4,S_4);
  smear_fxn_C3->SetParameter(5,N_4);

 



 
  double k1 = 0.0;
  double k2 = 0.0;
  double k3 = 0.0;
  double k4 = 0.0;

  double pt1 = 0.0;
  double pt2 = 0.0;
  double pt3 = 0.0;
  double pt4 = 0.0;

  double smear_C1 = 0.0;
  double smear_C2 = 0.0;
  double smear_C3 = 0.0;
  double smear_C4 = 0.0;

  //int N_fill = 300000000;
  int N_fill = 1000000;
  //int N_fill = 500000000;

  int skip_count = 0;
  
  for(int i = 0; i < N_fill; i++){
    
    // sample a value of pt from C4 to smear
    // pt1 = X1->GetRandom();
    // pt2 = X2->GetRandom();
    // pt3 = X3->GetRandom();
    // pt4 = X4->GetRandom();
    pt1 = X4->GetRandom();
    pt2 = X4->GetRandom();
    pt3 = X4->GetRandom();
    pt4 = X4->GetRandom();
   
    // if(smear_fxn_C1->Eval(pt1)*smear_fxn_C1->Eval(pt1) < 1 ||
    //    smear_fxn_C2->Eval(pt2)*smear_fxn_C2->Eval(pt2) < 1 ||
    //    smear_fxn_C3->Eval(pt3)*smear_fxn_C3->Eval(pt3) < 1){
    //   cout << "negative in exponent! skip!" << endl;
    //   continue;
    // }
    k1 = TMath::Sqrt(smear_fxn_C1->Eval(pt1)*smear_fxn_C1->Eval(pt1) - 1);
    k2 = TMath::Sqrt(smear_fxn_C2->Eval(pt2)*smear_fxn_C2->Eval(pt2) - 1);
    k3 = TMath::Sqrt(smear_fxn_C3->Eval(pt3)*smear_fxn_C3->Eval(pt3) - 1);
    if(i==0){
      cout << "resolution-smearing parameters for event 0:" << endl;
      cout << "k1 = " << k1 << endl;
      cout << "k2 = " << k2 << endl;
      cout << "k3 = " << k3 << endl;
    }
    // calculate the smear on JER_C4 necessary to worsen resolution to central levels
    smear_C1 = randomGenerator->Gaus(1.,k1*JER_fxn_C4->Eval(pt1));
    smear_C2 = randomGenerator->Gaus(1.,k2*JER_fxn_C4->Eval(pt2));
    smear_C3 = randomGenerator->Gaus(1.,k3*JER_fxn_C4->Eval(pt3));
    // smear_C1 = randomGenerator->Gaus(1.,fabs(k1 - 1.));
    // smear_C2 = randomGenerator->Gaus(1.,fabs(k2 - 1.));
    // smear_C3 = randomGenerator->Gaus(1.,fabs(k3 - 1.));
    if(i==0){
      cout << "pt-smearing parameters for event 0:" << endl;
      cout << "smear_C1 = " << smear_C1 << endl;
      cout << "smear_C2 = " << smear_C2 << endl;
      cout << "smear_C3 = " << smear_C3 << endl;
    }
    //skip if something went weird with the smear
    // if(smear_C1 < 0 || smear_C2 < 0 || smear_C3 < 0){
    //   //cout << "negative smear value! skip!" << endl;
    //   skip_count++;
    //   //cout << "skip count = " << skip_count << endl;
    //   continue;
    // }
    s1->Fill(smear_C1 * pt1);
    s2->Fill(smear_C2 * pt2);
    s3->Fill(smear_C3 * pt3);
    // s1->Fill(1. * pt1); // turn off smearing for a sec
    // s2->Fill(1. * pt2);
    // s3->Fill(1. * pt3);
    s4->Fill(pt4);

    h1->Fill(X1->GetRandom());
    h2->Fill(X2->GetRandom());
    h3->Fill(X3->GetRandom());
    h4->Fill(X4->GetRandom());
  }

  double high_pt_norm_1 = 150.;
  double high_pt_norm_2 = 500.;

  // normalize by high pT point (shape measurement)
  normalize_by_highPt(h1, high_pt_norm_1);
  normalize_by_highPt(h2, high_pt_norm_1);
  normalize_by_highPt(h3, high_pt_norm_1);
  normalize_by_highPt(h4, high_pt_norm_1);

  normalize_by_highPt(s1, high_pt_norm_1);
  normalize_by_highPt(s2, high_pt_norm_1);
  normalize_by_highPt(s3, high_pt_norm_1);
  normalize_by_highPt(s4, high_pt_norm_1);

  // rebin
  const int N_edge = 30;
  double new_axis[N_edge] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,170,220,320,500};
  h1 = (TH1D*) h1->Rebin(N_edge-1,"h1",new_axis);
  h2 = (TH1D*) h2->Rebin(N_edge-1,"h2",new_axis);
  h3 = (TH1D*) h3->Rebin(N_edge-1,"h3",new_axis);
  h4 = (TH1D*) h4->Rebin(N_edge-1,"h4",new_axis);
  s1 = (TH1D*) s1->Rebin(N_edge-1,"s1",new_axis);
  s2 = (TH1D*) s2->Rebin(N_edge-1,"s2",new_axis);
  s3 = (TH1D*) s3->Rebin(N_edge-1,"s3",new_axis);
  s4 = (TH1D*) s4->Rebin(N_edge-1,"s4",new_axis);

  // divide by binwidth
  divideByBinwidth(h1);
  divideByBinwidth(h2);
  divideByBinwidth(h3);
  divideByBinwidth(h4);
  divideByBinwidth(s1);
  divideByBinwidth(s2);
  divideByBinwidth(s3);
  divideByBinwidth(s4);
  
  // define the ratios
  r1 = (TH1D*) s1->Clone("r1");
  r2 = (TH1D*) s2->Clone("r2");
  r3 = (TH1D*) s3->Clone("r3");
  r4 = (TH1D*) s4->Clone("r4");
  // calculate the ratios
  r1->Divide(h1,s1,1,1,"");
  r2->Divide(h2,s2,1,1,"");
  r3->Divide(h3,s3,1,1,"");
  r4->Divide(h4,s4,1,1,"");

  // r1->Divide(h1,h4,1,1,"");
  // r2->Divide(h2,h4,1,1,"");
  // r3->Divide(h3,h4,1,1,"");
  // r4->Divide(h4,h4,1,1,"");

  
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
  s2->Draw("same");
  s3->Draw("same");
  s4->Draw("same");
  // Write the legend with TLatex
  double la_leg_text_size = 0.05;
  int la_leg_text_font = 62;
  la->SetTextSize(la_leg_text_size);
  la->SetTextFont(la_leg_text_font);
  TString la_leg_title_color = "kBlack";
  TString la_leg_C1_color = "kMagenta-7";
  TString la_leg_C2_color = "kGreen+2";
  TString la_leg_C3_color = "kBlue-4";
  TString la_leg_C4_color = "kRed-4";
  // titles
  
  TString la_leg_C1_title = "PbPb 0-10%";
  TString la_leg_C2_title = "PbPb 10-30%";
  TString la_leg_C3_title = "PbPb 30-50%";
  TString la_leg_C4_title = "PbPb 50-90%";

  // TString la_leg_C1_title = "Smeared PbPb 50-90%";
  // TString la_leg_C2_title = "Smeared PbPb 50-90%";
  // TString la_leg_C3_title = "Smeared PbPb 50-90%";
  // TString la_leg_C4_title = "PbPb 50-90%";
  // title coordinates
  double la_leg_title_x_coord = 0.6;
  double la_leg_title_y_coord = 0.8;
  double la_leg_C1_y_coord = 0.72;
  double la_leg_C2_y_coord = 0.64;
  double la_leg_C3_y_coord = 0.56;
  double la_leg_C4_y_coord = 0.48;
  // set color & draw!
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(la_leg_title_x_coord,la_leg_title_y_coord,la_leg_title);
  la->SetTextColor(kMagenta-7);
  la->DrawLatexNDC(la_leg_title_x_coord,la_leg_C1_y_coord,la_leg_C1_title);
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(la_leg_title_x_coord,la_leg_C2_y_coord,la_leg_C2_title);
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(la_leg_title_x_coord,la_leg_C3_y_coord,la_leg_C3_title);
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(la_leg_title_x_coord,la_leg_C4_y_coord,la_leg_C4_title);
  
  double la_smearing_status_x_coord = 0.6;
  double la_smearing_status_y_coord = 0.40;
  la->SetTextColor(kBlack);
  la->SetTextFont(72);
  la->DrawLatexNDC(la_smearing_status_x_coord,la_smearing_status_y_coord,smearing_status); 
  
  // switch to bottom pad
  p2->cd(); 
  // draw the ratio histograms
  r1->Draw();
  r2->Draw("same");
  r3->Draw("same");
  //r4->Draw("same");
  // draw the line
  line->SetLineStyle(2);
  line->DrawLine(0,1,500,1);
  line->SetLineStyle(7);
  line->DrawLine(0,0.95,500,0.95);
  line->DrawLine(0,1.05,500,1.05);

}
