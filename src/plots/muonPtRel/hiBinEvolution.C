
#include "../../../headers/functions/divideByBinwidth.h"

void hiBinEvolution(){

  TFile *input_mc = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-5-27.root");

  TFile *input_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_scan_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates_2025-05-28.root");


  const int NHiBinEdge = 6;
  double hiBinProj[NHiBinEdge] = {0,10,20,60,100,160};
  double MCHiBinShift = 10;
  
  
  TH2D *H_mc, *H_data;
  TH1D *h_mc[NHiBinEdge-1], *h_data[NHiBinEdge-1];
  TH1D *r_mc[NHiBinEdge-2], *r_data[NHiBinEdge-2], *rr[NHiBinEdge-2];
  
  input_mc->GetObject("h_muptrel_hiBin_allJets_J1",H_mc);
  input_data->GetObject("h_muptrel_hiBin_J0",H_data);
  double jetPtLow = 80;
  double jetPtHigh = 500;

  h_data[0] = (TH1D*) H_data->ProjectionY("h_data");

  h_data[0]->Draw();


  /*


  const int M = 12;
  double muRelPtAxis[M] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.5,1.8,2.4,3.5,5.0}; // M = 12
  
  Int_t colors[NHiBinEdge-1] = {kMagenta-9,kGreen+2,kBlue-4,kRed-4,kBlack};
  for(int i = 0; i < NHiBinEdge-1; i++){
    h_mc[i] = (TH1D*) H_mc->ProjectionX(Form("h_mc_%i",i),H_mc->ProjectionY()->FindBin(hiBinProj[i]+MCHiBinShift),H_mc->ProjectionY()->FindBin(hiBinProj[i+1]+MCHiBinShift));
    h_data[i] = (TH1D*) H_data->ProjectionX(Form("h_data_%i",i),H_data->ProjectionY()->FindBin(hiBinProj[i]),H_data->ProjectionY()->FindBin(hiBinProj[i+1]));
    h_mc[i]->SetLineColor(colors[i]);
    h_data[i]->SetLineColor(colors[i]);
    h_mc[i]->SetLineWidth(3);
    h_data[i]->SetLineWidth(3);
    h_mc[i] = (TH1D*) h_mc[i]->Rebin(M-1,Form("h_mc_%i",i),muRelPtAxis);
    h_data[i] = (TH1D*) h_data[i]->Rebin(M-1,Form("h_data_%i",i),muRelPtAxis);
    divideByBinwidth(h_mc[i]);
    divideByBinwidth(h_data[i]);
    h_mc[i]->Scale(1./h_mc[i]->Integral());
    h_data[i]->Scale(1./h_data[i]->Integral());
    
  }

  for(int i = 0; i < NHiBinEdge-2; i++){
    r_mc[i] = (TH1D*) h_mc[i]->Clone(Form("r_mc_%i",i));
    r_mc[i]->Divide(h_mc[i],h_mc[NHiBinEdge-2],1,1,"");
    r_data[i] = (TH1D*) h_data[i]->Clone(Form("r_data_%i",i));
    r_data[i]->Divide(h_data[i],h_data[NHiBinEdge-2],1,1,"");
    rr[i] = (TH1D*) r_data[i]->Clone(Form("rr_%i",i));
    rr[i]->Divide(r_data[i],r_mc[i],1,1,"");
  }
  
  
  
  TCanvas *canv_1 = new TCanvas("canv_1","canv_1",700,1000);
  canv_1->cd();
  TPad *pad1_1 = new TPad("pad1_1","pad1_1",0,0.4,1,1);
  TPad *pad2_1 = new TPad("pad2_1","pad2_1",0,0,1,0.4);
  pad1_1->SetLeftMargin(0.15);
  pad2_1->SetLeftMargin(0.15);
  pad1_1->SetBottomMargin(0.0);
  pad2_1->SetBottomMargin(0.2);
  pad1_1->SetTopMargin(0.1);
  pad2_1->SetTopMargin(0.0);
  pad1_1->SetRightMargin(0.15);
  pad2_1->SetRightMargin(0.15);
  pad1_1->Draw();
  pad2_1->Draw();
  pad1_1->cd();



  h_mc[0]->SetTitle("");
  h_mc[0]->SetStats(0);
  h_mc[0]->GetXaxis()->SetTitleSize(0.05);
  h_mc[0]->GetXaxis()->SetLabelSize(0.04);
  h_mc[0]->GetYaxis()->SetTitleSize(0.05);
  h_mc[0]->GetYaxis()->SetLabelSize(0.04);
  h_mc[0]->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h_mc[0]->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
  h_mc[0]->GetYaxis()->SetRangeUser(0,0.2);
  h_mc[0]->Draw("hist");
  h_mc[1]->Draw("hist same");
  h_mc[2]->Draw("hist same");
  h_mc[3]->Draw("hist same");

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.035);
  la->DrawLatexNDC(0.45,0.78,"PYTHIA+HYDJET (5.02 TeV)");
  la->DrawLatexNDC(0.45,0.7,Form("all jets, %3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f",jetPtLow,jetPtHigh));

  for(int i = 0; i < NHiBinEdge-1; i++){
    la->SetTextColor(colors[i]);
    la->DrawLatexNDC(0.45,0.62-i*0.08,Form("PYTHIA+HYDJET %3.0f - %3.0f %%",(hiBinProj[i]+MCHiBinShift)/2.,(hiBinProj[i+1]+MCHiBinShift)/2.));
    //la->DrawLatexNDC(0.45,0.62-i*0.08,"test");
  }

  pad2_1->cd();
  r_mc[0]->SetTitle("");
  r_mc[0]->SetStats(0);
  r_mc[0]->GetXaxis()->SetTitleSize(0.08);
  r_mc[0]->GetXaxis()->SetLabelSize(0.065);
  r_mc[0]->GetYaxis()->SetTitleSize(0.08);
  r_mc[0]->GetYaxis()->SetLabelSize(0.065);
  r_mc[0]->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  r_mc[0]->GetYaxis()->SetTitle("Cent. / Periph.");
  r_mc[0]->GetYaxis()->SetRangeUser(0,6);
  r_mc[0]->Draw("hist");
  r_mc[1]->Draw("hist same");
  r_mc[2]->Draw("hist same");

  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(muRelPtAxis[0],1,muRelPtAxis[M-1],1);

  

  TCanvas *canv_2 = new TCanvas("canv_2","canv_2",700,1000);
  canv_2->cd();
  TPad *pad1_2 = new TPad("pad1_2","pad1_2",0,0.4,1,1);
  TPad *pad2_2 = new TPad("pad2_2","pad2_2",0,0,1,0.4);
  pad1_2->SetLeftMargin(0.15);
  pad2_2->SetLeftMargin(0.15);
  pad1_2->SetBottomMargin(0.0);
  pad2_2->SetBottomMargin(0.2);
  pad1_2->SetTopMargin(0.1);
  pad2_2->SetTopMargin(0.0);
  pad1_2->SetRightMargin(0.15);
  pad2_2->SetRightMargin(0.15);
  pad1_2->Draw();
  pad2_2->Draw();
  pad1_2->cd();

  h_data[0]->SetTitle("");
  h_data[0]->SetStats(0);
  h_data[0]->GetXaxis()->SetTitleSize(0.05);
  h_data[0]->GetXaxis()->SetLabelSize(0.04);
  h_data[0]->GetYaxis()->SetTitleSize(0.05);
  h_data[0]->GetYaxis()->SetLabelSize(0.04);
  h_data[0]->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h_data[0]->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
  h_data[0]->GetYaxis()->SetRangeUser(0,0.2);
  h_data[0]->Draw("hist");
  h_data[1]->Draw("hist same");
  h_data[2]->Draw("hist same");
  h_data[3]->Draw("hist same");
  
  la->DrawLatexNDC(0.45,0.78,"PbPb (5.02 TeV)");
  la->DrawLatexNDC(0.45,0.7,Form("all jets, %3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f",jetPtLow,jetPtHigh));

  for(int i = 0; i < NHiBinEdge-1; i++){
    la->SetTextColor(colors[i]);
    la->DrawLatexNDC(0.55,0.62-i*0.08,Form("PbPb %3.0f - %3.0f %%",(hiBinProj[i])/2.,(hiBinProj[i+1])/2.));
  }

  pad2_2->cd();
  r_data[0]->SetTitle("");
  r_data[0]->SetStats(0);
  r_data[0]->GetXaxis()->SetTitleSize(0.08);
  r_data[0]->GetXaxis()->SetLabelSize(0.065);
  r_data[0]->GetYaxis()->SetTitleSize(0.08);
  r_data[0]->GetYaxis()->SetLabelSize(0.065);
  r_data[0]->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  r_data[0]->GetYaxis()->SetTitle("Cent. / Periph.");
  r_data[0]->GetYaxis()->SetRangeUser(0,6);
  r_data[0]->Draw("hist");
  r_data[1]->Draw("hist same");
  r_data[2]->Draw("hist same");

  li->SetLineStyle(7);
  li->DrawLine(muRelPtAxis[0],1,muRelPtAxis[M-1],1);



  
  TCanvas *canv_3 = new TCanvas("canv_3","canv_3",700,700);
  canv_3->cd();
  TPad *pad1_3 = new TPad("pad1_3","pad1_3",0,0,1,1);
  pad1_3->SetLeftMargin(0.15);
  pad1_3->SetBottomMargin(0.15);
  pad1_3->SetTopMargin(0.1);
  pad1_3->SetRightMargin(0.15);
  pad1_3->Draw();
  pad1_3->cd();
  rr[0]->SetTitle("");
  rr[0]->SetStats(0);
  rr[0]->GetXaxis()->SetTitleSize(0.05);
  rr[0]->GetXaxis()->SetLabelSize(0.04);
  rr[0]->GetYaxis()->SetTitleSize(0.05);
  rr[0]->GetYaxis()->SetLabelSize(0.04);
  rr[0]->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  rr[0]->GetYaxis()->SetTitle("R(data) / R(MC)");
  rr[0]->GetYaxis()->SetRangeUser(0,4);
  rr[0]->Draw("hist");
  rr[1]->Draw("hist same");
  rr[2]->Draw("hist same");
  li->DrawLine(muRelPtAxis[0],1,muRelPtAxis[M-1],1);



  canv_1->SaveAs(Form("../../../figures/muPtRelHiBinEvolution/mc_jetPt-%3.0fto%3.0f.pdf",jetPtLow,jetPtHigh));
  canv_2->SaveAs(Form("../../../figures/muPtRelHiBinEvolution/data_jetPt-%3.0fto%3.0f.pdf",jetPtLow,jetPtHigh));
  canv_3->SaveAs(Form("../../../figures/muPtRelHiBinEvolution/ratio_jetPt-%3.0fto%3.0f.pdf",jetPtLow,jetPtHigh));


  */


  
}
