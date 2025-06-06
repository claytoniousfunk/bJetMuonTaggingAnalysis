
#include <iostream>
#include "TFile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TRandom.h"
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
#include <array>

#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/goldenFileNames.h"


TH1D *pythia_vz, *data_vz, *r, *pythia_w_vz;
TH2D *H_raw, *H_corr;

double func_temp(double *x, double *par){
  double vz = x[0];
  //int bin = r->FindBin(pt);
  //double fitval = par[0] + par[1]*r->GetBinContent(bin) + par[2]*TMath::Exp(-1*par[3]*r->GetBinContent(bin));
  //double fitval = par[0] + par[1]*pt + par[2]*TMath::Exp(par[3]*pt);
  //double fitval = par[0] + par[1]*vz + par[2]*vz*vz + par[3]*vz*vz*vz + par[4]*vz*vz*vz*vz + par[5]*vz*vz*vz*vz*vz + par[6]*vz*vz*vz*vz*vz*vz + par[7]*vz*vz*vz*vz*vz*vz*vz;
  //double fitval = par[0] + par[1]*vz + par[2]*vz*vz + par[3]*vz*vz*vz + par[4]*vz*vz*vz*vz + par[5]*vz*vz*vz*vz*vz;
  double fitval = par[0] + par[1]*TMath::Exp(par[2]*vz);
  return fitval;
}



void plot_and_reweight_jetPt(bool isPP   = 1,
			     bool isC2   = 0,
			     bool isC1   = 0,
			     bool ismu5  = 0,
			     bool ismu7  = 0,
			     bool ismu12 = 1){
  
  TFile *f_data, *f_pythia, *f_pythia_weighted;

  if(isPP){
    if(ismu5){
      f_data = TFile::Open(goldenFile_pp_SingleMuon_mu5);
      f_pythia = TFile::Open(goldenFile_PYTHIA_mu5_RAW);
      f_pythia_weighted = TFile::Open(goldenFile_PYTHIA_mu12_pThat15);
    }
    else if(ismu7){
      f_data = TFile::Open(goldenFile_pp_SingleMuon_mu7);
      f_pythia = TFile::Open(goldenFile_PYTHIA_mu7_RAW);
      f_pythia_weighted = TFile::Open(goldenFile_PYTHIA_mu7_pThat30);
    }
    else if(ismu12){
      f_data = TFile::Open(goldenFile_pp_SingleMuon_mu12);
      f_pythia = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/obsidian/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-45_removeHYDJETjet_jetTrkMaxFilter_vzReweight_newJetBins.root");
      f_pythia_weighted = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/obsidian/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-45_removeHYDJETjet_jetTrkMaxFilter_vzReweight_jetPtReweight_newJetBins.root");
    }
    else{};
  }
  if(isC1 || isC2){
    if(ismu5){
      f_data = TFile::Open(goldenFile_PbPb_SingleMuon_mu5);
      f_pythia = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu5_RAW);
      f_pythia_weighted = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu5_pThat30);
    }
    else if(ismu7){
      f_data = TFile::Open(goldenFile_PbPb_SingleMuon_mu7);
      f_pythia = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu7_RAW);
      f_pythia_weighted = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu7_pThat30);
    }
    else if(ismu12){
      f_data = TFile::Open(goldenFile_PbPb_SingleMuon_mu12);
      f_pythia = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat30);
      f_pythia_weighted = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat30);
    }
    else{};
  }

  // PYTHIA
  if(isPP){
    f_pythia->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",H_raw);
    f_pythia_weighted->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",H_corr);
    f_data->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",data_vz);
  }
  else if(isC2){
    f_pythia->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C2",H_raw);
    f_pythia_weighted->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C2",H_corr);
    f_data->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",data_vz);
  }
  else if(isC1){
    f_pythia->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C1",H_raw);
    f_pythia_weighted->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C1",H_corr);
    f_data->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",data_vz);
  }
  else{};

  pythia_vz = (TH1D*) H_raw->ProjectionX("pythia_vz");
  pythia_w_vz = (TH1D*) H_corr->ProjectionX("pythia_w_vz");
    
  TF1 *func = new TF1("fit",func_temp,0,500,3);
  func->SetParameter(0,1.0);
  func->SetParameter(1,1.0);
  func->SetParameter(2,-0.1);



  // const int N = 12;
  // double vz_axis[N] = {-15.0,-10.0,-7.0,-5.0,-3.0,-1.0,1.0,3.0,5.0,7.0,10.0,15.0}; // N = 12

  const int N = 17;
  double vz_axis[N] = {80,85,90,95,100,110,120,130,140,150,160,180,200,250,320,400,500};


  // normalize
  pythia_vz->Scale(1.0/pythia_vz->Integral(pythia_vz->GetXaxis()->FindBin(vz_axis[0]),pythia_vz->GetXaxis()->FindBin(vz_axis[N-1])));
  pythia_w_vz->Scale(1.0/pythia_w_vz->Integral(pythia_w_vz->GetXaxis()->FindBin(vz_axis[0]),pythia_w_vz->GetXaxis()->FindBin(vz_axis[N-1])));
  data_vz->Scale(1.0/data_vz->Integral(data_vz->GetXaxis()->FindBin(vz_axis[0]),data_vz->GetXaxis()->FindBin(vz_axis[N-1])));

  
  /////////////////////////////////////////    spectrum plot    /////////////////////////////////////////////////
    

  // Define the Canvas
    
  TCanvas *c2 = new TCanvas("c2", "canvas", 500, 500);
      
  c2->cd();
      
  //c2->SetLogy();
  TPad *pad2 = new TPad("pad2", "pad2", 0.0, 0.5, 1., 1.);
  //pad1->SetGridx();         // Vertical grid
  pad2->SetLeftMargin(0.25);
  pad2->SetBottomMargin(0.00);
  pad2->SetLogy();
  pad2->Draw();             // Draw the upper pad: pad1
  pad2->cd();
      

  // jet pT 
    
    
  TH1D *pythia_vz_rebin = (TH1D*) pythia_vz->Rebin(N-1,"pythia_vz_rebin",vz_axis);
  TH1D *pythia_w_vz_rebin = (TH1D*) pythia_w_vz->Rebin(N-1,"pythia_w_vz_rebin",vz_axis);
  TH1D *data_vz_rebin = (TH1D*) data_vz->Rebin(N-1,"data_vz_rebin",vz_axis);

  // TH1D *pythia_vz_rebin = (TH1D*) pythia_vz->Clone("pythia_vz_rebin");
  // TH1D *pythia_w_vz_rebin = (TH1D*) pythia_w_vz->Clone("pythia_w_vz_rebin");
  // TH1D *data_vz_rebin = (TH1D*) data_vz->Clone("data_vz_rebin");

  // normalize pythia_pt by bin width
  
  int Nbin1 = pythia_vz_rebin->GetSize();
  TH1D *pythia_vz_xnorm = (TH1D*) pythia_vz_rebin->Clone("pythia_vz_xnorm");

  for (int i=0;i<Nbin1;i++){

    double x1 = pythia_vz_rebin->GetBinWidth(i);
    double y1 = pythia_vz_rebin->GetBinContent(i);
    double z1 = pythia_vz_rebin->GetBinError(i);
    double r1 = 0.0;
    double e1 = 0.0;
      
    if(x1!=0){

      r1 = y1/x1;    
      e1 = z1/x1;
      pythia_vz_xnorm->SetBinContent(i,r1); 
      pythia_vz_xnorm->SetBinError(i,e1);
 
               
    }
      
  }
      
  // normalize data_pt by bin width
  
  int Nbin2 = data_vz_rebin->GetSize();
  TH1D* data_vz_xnorm = (TH1D*) data_vz_rebin->Clone("data_vz_xnorm");

  for (int j=0;j<Nbin2;j++){

    double x2 = data_vz_rebin->GetBinWidth(j);
    double y2 = data_vz_rebin->GetBinContent(j);
    double z2= data_vz_rebin->GetBinError(j);
    double r2= 0.0;
    double e2= 0.0;
      
    if(x2!=0){

      r2 = y2/x2;    
      e2 = z2/x2;
      data_vz_xnorm->SetBinContent(j,r2); 
      data_vz_xnorm->SetBinError(j,e2);
 
               
    }
      
  }
    
  int Nbin3 = pythia_w_vz_rebin->GetSize();
  TH1D* pythia_w_vz_xnorm = (TH1D*) pythia_w_vz_rebin->Clone("pythia_w_vz_xnorm");

  for (int j=0;j<Nbin3;j++){

    double x2 = pythia_w_vz_rebin->GetBinWidth(j);
    double y2 = pythia_w_vz_rebin->GetBinContent(j);
    double z2= pythia_w_vz_rebin->GetBinError(j);
    double r2= 0.0;
    double e2= 0.0;
      
    if(x2!=0){

      r2 = y2/x2;    
      e2 = z2/x2;
      pythia_w_vz_xnorm->SetBinContent(j,r2); 
      pythia_w_vz_xnorm->SetBinError(j,e2);
 
               
    }
      
  }
    
  double msize = 1.0;

  pythia_vz_xnorm->SetMarkerStyle(23);
  pythia_vz_xnorm->SetMarkerColor(kBlue);
  pythia_vz_xnorm->SetLineColor(kBlue);
  pythia_vz_xnorm->SetMarkerSize(msize);
  pythia_vz_xnorm->SetFillColorAlpha(kBlue,0.7);
  pythia_vz_xnorm->SetStats(0);
  //pythia_vz_xnorm->SetTitle("Centrality 30-90%");
      
  pythia_w_vz_xnorm -> SetMarkerStyle(8);
  pythia_w_vz_xnorm->SetMarkerColor(kGreen+2);
  pythia_w_vz_xnorm->SetLineColor(kGreen+2);
  pythia_w_vz_xnorm->SetMarkerSize(msize);
  pythia_w_vz_xnorm->SetFillColorAlpha(kGreen+2,0.7);
  pythia_w_vz_xnorm->SetStats(0);
  pythia_w_vz_xnorm->SetTitle("");
      

  data_vz_xnorm->SetMarkerStyle(25);
  data_vz_xnorm->SetMarkerColor(kRed);
  data_vz_xnorm->SetLineColor(kRed);
  data_vz_xnorm->SetMarkerSize(msize);
  data_vz_xnorm->SetFillColorAlpha(kRed,0.7);
  data_vz_xnorm->SetStats(0);
  data_vz_xnorm->SetTitle("");   

   
  data_vz_xnorm->GetYaxis()->SetTitleSize(0.1);
  data_vz_xnorm->GetXaxis()->SetTitleSize(0.0);
  data_vz_xnorm->GetYaxis()->SetLabelSize(0.08);
  data_vz_xnorm->GetXaxis()->SetLabelSize(0.0);


  //data_vz_xnorm->GetYaxis()->SetRangeUser(0.0,0.20);
      
      

  auto legend = new TLegend(0.28,0.7,0.5,0.89);
  if(isPP){
    legend->AddEntry(data_vz_xnorm,"pp SingleMuon","p");
    legend->AddEntry(pythia_vz_xnorm,"PYTHIA (w/ jet-filter + #it{v}_{z}-weight)","p");
    legend->AddEntry(pythia_w_vz_xnorm,"PYTHIA (w/ jet-filter + #it{v}_{z}-weight + #it{p}_{T}-weight)","p");
  }
  if(isC1 || isC2){
    legend->AddEntry(data_vz_xnorm,"PbPb SingleMuon","p");
    legend->AddEntry(pythia_vz_xnorm,"PYTHIA+HYDJET w/ jet-filter","p");
    legend->AddEntry(pythia_w_vz_xnorm,"PYTHIA+HYDJET weighted + jet-filter","p");
  }
      
  legend->SetBorderSize(0);
  legend->SetTextSize(0.06);

     
  data_vz_xnorm->GetYaxis()->SetTitle("1/#font[52]{N}^{jet}_{tot} d#font[52]{N}^{jet}/d#it{p}_{T}^{jet}");
  data_vz_xnorm->GetYaxis()->SetRangeUser(1.0e-8,1.0e4);

  pythia_vz_xnorm->SetTitle("");
      
	
  data_vz_xnorm->Draw();
  pythia_vz_xnorm->Draw("same");
  pythia_w_vz_xnorm->Draw("same");
  legend->Draw();


  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.06);
  double la_y_pos = 0.7; // latex y position variable
  double la_x_pos = 0.33; // latex x position variable
  double la_y_off = 0.08; // latex y offset variable
  TString jet_info_string_pp = "anti-#font[52]{k}_{T} PF jets, |#it{#eta}^{jet}| < 1.6";
    TString jet_info_string_PbPb = "anti-#font[52]{k}_{T} CsPF jets, |#it{#eta}^{jet}| < 1.6";
    //la->DrawLatexNDC(la_x_pos,la_y_pos,"#it{#mu}-triggered events w/ #it{#mu}-tagged jet");
  if(isPP)  la->DrawLatexNDC(la_x_pos,la_y_pos - 1*la_y_off, jet_info_string_pp);
  else la->DrawLatexNDC(la_x_pos,la_y_pos - 1*la_y_off, jet_info_string_PbPb);



  if(ismu5){
    la->DrawLatexNDC(la_x_pos,la_y_pos - 2*la_y_off,"hybrid-soft muon ID, #font[52]{p}_{T}^{#mu} > 7 GeV, |#it{#eta}^{#mu}| < 2.0");
    la->DrawLatexNDC(la_x_pos,la_y_pos - 3*la_y_off,"mu5 trigger");
  }
  else if(ismu7){
    la->DrawLatexNDC(la_x_pos,la_y_pos - 2*la_y_off,"tight muon ID, 9 < #font[52]{p}_{T}^{#mu} < 14 GeV, |#it{#eta}^{#mu}| < 2.0");
    la->DrawLatexNDC(la_x_pos,la_y_pos - 3*la_y_off,"mu7 trigger");
  }
  else if(ismu12){
    la->DrawLatexNDC(la_x_pos,la_y_pos - 2*la_y_off,"tight muon ID, #font[52]{p}_{T}^{#it{#mu}} > 14 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
    la->DrawLatexNDC(la_x_pos,la_y_pos - 3*la_y_off,"mu12 trigger, #hat{#it{p}}_{T} > 45 GeV");
  }
  else {};

  la->SetTextSize(0.07);
  la->DrawLatexNDC(0.26,0.92,"#font[62]{CMS }#font[52]{#scale[0.8]{Preliminary}}");
  la->SetTextSize(0.065);;
  if(isPP){
    if(ismu5) la->DrawLatexNDC(0.6,0.92,"pp 5.02 TeV (99 pb^{-1})");
    else if(ismu7) la->DrawLatexNDC(0.6,0.92,"pp 5.02 TeV (274 pb^{-1})");
    else if(ismu12) la->DrawLatexNDC(0.6,0.92,"pp 5.02 TeV (301 pb^{-1})");
    else{};
  }
  else if(isC1 || isC2){
    if(ismu5) la->DrawLatexNDC(0.56,0.92,"PbPb 5.02 TeV (323 #mub^{-1})");
    else if(ismu7) la->DrawLatexNDC(0.56,0.92,"PbPb 5.02 TeV (787 #mub^{-1})");
    else if(ismu12) la->DrawLatexNDC(0.55,0.92,"PbPb 5.02 TeV (1689 #mub^{-1})");
    else{};
  }
  
  ///////////////////////////////////////////////////////////////////////////  ratio plot  ////////////////////////////////////////////////////////////////////////////


  c2->cd();
  TPad *pad1 = new TPad("pad1","pad1",0.,0.0,1.,0.5);
  //pad1->SetGridx();
  pad1->SetBottomMargin(0.3);
  pad1->SetLeftMargin(0.25);
  pad1->SetTopMargin(0.0);
  pad1->Draw();
  pad1->cd();
  r = (TH1D*)data_vz_xnorm->Clone("r");
  TH1D *r2 = (TH1D*)data_vz_xnorm->Clone("r2");
  r->Divide(pythia_vz_xnorm);
  r2->Divide(pythia_w_vz_xnorm);
  r->SetMarkerStyle(23);
  r->SetMarkerColor(kBlue);
  r->SetMarkerSize(1.0);
  r2->SetMarkerStyle(20);
  r2->SetMarkerColor(kGreen+2);
  r2->SetMarkerSize(1.0);
  r->SetLineColor(kBlue);
  r2->SetLineColor(kGreen+2);
  r->SetStats(0);
  r->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  r->GetXaxis()->SetTitleSize(0.10);
  r->GetXaxis()->SetLabelSize(0.08);
  r->GetYaxis()->SetTitle("DATA / MC");
  r->GetYaxis()->SetTitleSize(0.10);
  r->GetYaxis()->SetLabelSize(0.08);
  r->SetTitle("");
  r->GetYaxis()->SetNdivisions(508);
  r->Draw();
  r2->Draw("same");
  //func->SetParNames("a_0","a_1","a_2","a_3","a_4");
  //r->Fit("func","MR","N",-15.0,15.0);
  r->GetYaxis()->SetRangeUser(0.6,1.4);
  TLine *l1 = new TLine(vz_axis[0],1,vz_axis[N-1],1);
  l1->SetLineStyle(7);
  l1->Draw();
  TLine *l2 = new TLine(vz_axis[0],1.2,vz_axis[N-1],1.2);
  l2->SetLineStyle(2);
  l2->Draw();
  TLine *l3 = new TLine(vz_axis[0],0.8,vz_axis[N-1],0.8);
  l3->SetLineStyle(2);
  l3->Draw();
  //gStyle->SetOptFit(1);
  //r->Fit("pol3");
  //r->Fit("fit");
  //r->Fit("pol1");
  //r->Fit("expo");
  auto legend2 = new TLegend(0.27,0.12,0.72,0.42);
  legend2->AddEntry(r,"no weight","p");
  legend2->AddEntry(r2,"with weight","p");
  legend2->SetBorderSize(0);
  legend2->SetTextSize(0.065);
  //legend2->Draw();
  // if(isPP){
  //   if(ismu5) c2->SaveAs("/home/clayton/Analysis/ANDraft/figures/vz_spectra/pp_mu5.pdf");
  //   else if(ismu7) c2->SaveAs("/home/clayton/Analysis/ANDraft/figures/vz_spectra/pp_mu7.pdf");
  //   else if(ismu12) c2->SaveAs("/home/clayton/Analysis/ANDraft/figures/vz_spectra/pp_mu12.pdf");
  //   else{};
  // }
  // if(isC1 || isC2){
  //   if(ismu5) c2->SaveAs("/home/clayton/Analysis/ANDraft/figures/vz_spectra/PbPb_mu5.pdf");
  //   else if(ismu7) c2->SaveAs("/home/clayton/Analysis/ANDraft/figures/vz_spectra/PbPb_mu7.pdf");
  //   else if(ismu12) c2->SaveAs("/home/clayton/Analysis/ANDraft/figures/vz_spectra/PbPb_mu12.pdf");
  //   else{};
  // }
    

  /*
    double a0 = func->GetParameter(0);
    double e_a0 = func->GetParError(0);
    double a1 = func->GetParameter(1);
    double e_a1 = func->GetParError(1);
    double a2 = func->GetParameter(2);
    double e_a2 = func->GetParError(2);
    double a3 = func->GetParameter(3);
    double e_a3 = func->GetParError(3);
    //double a4 = func->GetParameter(4);
    //double e_a4 = func->GetParError(4);
    TF1 *fit_fxn = new TF1("fit_fxn","[0]+[1]*x + [2]*x*x + [3]*x*x*x ",-15.0,15.0);
    fit_fxn->SetParameters(a0,a1,a2,a3);
  */  
    
  /*
    TCanvas *c3 = new TCanvas("c3","c3",500,500);
    c3->cd();
    TPad *pad3 = new TPad("pad3","pad3",0.0,0.3,1.0,1.0);
    TPad *pad4 = new TPad("pad4","pad4",0.0,0.0,1.0,0.3);
    pad4->SetLeftMargin(0.15);
    pad4->SetBottomMargin(0.3);
    pad4->Draw();
    pad3->SetLeftMargin(0.15);
    pad3->SetLogy();
    pad3->Draw();
    pad3->cd();

    
    //fit_fxn->Draw();

    TH1D* pythia_vz_xnorm_fitscaled = (TH1D*)pythia_vz_xnorm->Clone("pythia_vz_xnorm_fitscaled");
    int Nbin3 = pythia_vz_xnorm_fitscaled->GetSize();
    for(int k=0;k<Nbin3;k++){
    double pteval = pythia_vz_xnorm_fitscaled->GetXaxis()->GetBinCenter(k);
    double fitscale = fit_fxn->Eval(pteval);
    double oldval = pythia_vz_xnorm_fitscaled->GetBinContent(k);
    double olderror = pythia_vz_xnorm_fitscaled->GetBinError(k);
    double newval = oldval/fitscale;
    double newerror = newval*TMath::Sqrt(TMath::Power(olderror/oldval,2) + TMath::Power(e_a0/a0,2) + TMath::Power(e_a1/a1,2) + TMath::Power(e_a2/a2,2) + TMath::Power(e_a3/a3,2));
    pythia_vz_xnorm_fitscaled->SetBinContent(k,newval);
    pythia_vz_xnorm_fitscaled->SetBinError(k,newerror);
    }    
   
    pythia_vz_xnorm_fitscaled->SetMarkerColor(kGreen+2);
    pythia_vz_xnorm_fitscaled->SetFillColorAlpha(kGreen+2,0.7);
    pythia_vz_xnorm_fitscaled->SetMarkerStyle(24);
    data_vz_xnorm->GetYaxis()->SetTitle("1/N^{jet} dN^{jet}/dv_{z}");
    data_vz_xnorm->GetYaxis()->SetTitleSize(0.04);
   
    data_vz_xnorm->SetMarkerStyle(24);

    data_vz_xnorm->Draw("ep");
    pythia_vz_xnorm_fitscaled->Draw("ep same");

    pad4->cd();
    TH1D *r2 = (TH1D*) pythia_vz_xnorm_fitscaled->Clone("r2");
    r2->Divide(data_vz_xnorm);
    r2->SetMarkerColor(kBlack);
   
    r2->Draw("ep");
    r2->SetMinimum(0.8);
    r2->SetMaximum(1.2);
    r2->GetXaxis()->SetTitle("jet v_{z} [mm]");
    r2->GetYaxis()->SetTitle("Pythia / data");
    r2->GetXaxis()->SetTitleSize(0.09);
    r2->GetYaxis()->SetTitleSize(0.08);
    c3->SaveAs("/home/clayton/Analysis/code/normalizeAndCompareSpectra/figures/pythiaDataVzRescaleCompare.pdf");

  */
    

    









}
