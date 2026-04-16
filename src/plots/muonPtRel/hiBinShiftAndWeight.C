#include "../../../headers/functions/divideByBinwidth.h"

TFile *f_noShift_noWeight;
TFile *f_withShift_noWeight;
TFile *f_noShift_withWeight;
TFile *f_withShift_withWeight;

TH1D *h_hiBin_noShift_noWeight, *h_hiBin_withShift_noWeight, *h_hiBin_noShift_withWeight, *h_hiBin_withShift_withWeight;

TH2D *H_bJets_noShift_noWeight, *H_bJets_withShift_noWeight, *H_bJets_noShift_withWeight, *H_bJets_withShift_withWeight;

TH1D *h_bJets_noShift_noWeight, *h_bJets_withShift_noWeight, *h_bJets_noShift_withWeight, *h_bJets_withShift_withWeight;
TH1D *h_bbarJets_noShift_noWeight, *h_bbarJets_withShift_noWeight, *h_bbarJets_noShift_withWeight, *h_bbarJets_withShift_withWeight;
TH1D *h_bGSJets_noShift_noWeight, *h_bGSJets_withShift_noWeight, *h_bGSJets_noShift_withWeight, *h_bGSJets_withShift_withWeight;

TLatex *la;
TLine *li;

void normalize(TH1D *h){
  h->Scale(1./h->Integral());
}

void stylize(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){
  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kRed-4);
  h4->SetLineColor(kGreen+2);

  h1->SetLineWidth(3);
  h2->SetLineWidth(3);
  h3->SetLineWidth(3);
  h4->SetLineWidth(3);
}

void hiBinShiftAndWeight(){

  f_noShift_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinShift-0_jetTrkMaxFilter_removeHYDJETjet0p45.root");
  f_withShift_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-6-4.root");
  f_noShift_withWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-0_jetTrkMaxFilter_removeHYDJETjet0p45_2025-6-4.root");
  f_withShift_withWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-6-2.root");

  

  f_noShift_noWeight->GetObject("h_hiBin_inclRecoMuonTag_triggerOn",h_hiBin_noShift_noWeight);
  f_noShift_withWeight->GetObject("h_hiBin_raw",h_hiBin_noShift_withWeight);
  f_withShift_noWeight->GetObject("h_hiBin_raw",h_hiBin_withShift_noWeight);
  f_withShift_withWeight->GetObject("h_hiBin_raw",h_hiBin_withShift_withWeight);

  TH1D *h_new = (TH1D*) h_hiBin_noShift_noWeight->Clone("h_new");
  for(int i = 0; i < h_hiBin_noShift_noWeight->GetSize() - 10; i++){
    h_hiBin_noShift_noWeight->SetBinContent(i,h_hiBin_noShift_noWeight->GetBinContent(i+10));
    h_hiBin_noShift_noWeight->SetBinError(i,h_hiBin_noShift_noWeight->GetBinError(i+10));
    
  }

  normalize(h_hiBin_noShift_noWeight);
  normalize(h_hiBin_noShift_withWeight);
  normalize(h_hiBin_withShift_noWeight);
  normalize(h_hiBin_withShift_withWeight);
  stylize(h_hiBin_noShift_noWeight, h_hiBin_noShift_withWeight, h_hiBin_withShift_noWeight, h_hiBin_withShift_withWeight);

  f_noShift_noWeight->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_bJets_noShift_noWeight);
  f_noShift_withWeight->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_bJets_noShift_withWeight);
  f_withShift_noWeight->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_bJets_withShift_noWeight);
  f_withShift_withWeight->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_bJets_withShift_withWeight);

  double jetPtLow = 90;
  double jetPtHigh = 110;
  double smallShift = 0.01;
  TH1D *binFinder = (TH1D*) H_bJets_noShift_noWeight->ProjectionY();
  h_bJets_noShift_noWeight = (TH1D*) H_bJets_noShift_noWeight->ProjectionX("h_bJets_noShift_noWeight",binFinder->FindBin(jetPtLow + smallShift),binFinder->FindBin(jetPtHigh - smallShift));
  h_bJets_noShift_withWeight = (TH1D*) H_bJets_noShift_withWeight->ProjectionX("h_bJets_noShift_withWeight",binFinder->FindBin(jetPtLow + smallShift),binFinder->FindBin(jetPtHigh - smallShift));
  h_bJets_withShift_noWeight = (TH1D*) H_bJets_withShift_noWeight->ProjectionX("h_bJets_withShift_noWeight",binFinder->FindBin(jetPtLow + smallShift),binFinder->FindBin(jetPtHigh - smallShift));
  h_bJets_withShift_withWeight = (TH1D*) H_bJets_withShift_withWeight->ProjectionX("h_bJets_withShift_withWeight",binFinder->FindBin(jetPtLow + smallShift),binFinder->FindBin(jetPtHigh - smallShift));
    
  
  stylize(h_bJets_noShift_noWeight, h_bJets_noShift_withWeight, h_bJets_withShift_noWeight, h_bJets_withShift_withWeight);

  const int Nedge = 9;
  double newAxis[Nedge] = {0.0,0.3,0.6,0.9,1.3,1.8,2.4,3.5,5};
  h_bJets_noShift_noWeight = (TH1D*) h_bJets_noShift_noWeight->Rebin(Nedge-1,"h_bJets_noShift_noWeight",newAxis);
  h_bJets_noShift_withWeight = (TH1D*) h_bJets_noShift_withWeight->Rebin(Nedge-1,"h_bJets_noShift_withWeight",newAxis);
  h_bJets_withShift_noWeight = (TH1D*) h_bJets_withShift_noWeight->Rebin(Nedge-1,"h_bJets_withShift_noWeight",newAxis);
  h_bJets_withShift_withWeight = (TH1D*) h_bJets_withShift_withWeight->Rebin(Nedge-1,"h_bJets_withShift_withWeight",newAxis);

  divideByBinwidth(h_bJets_noShift_noWeight);
  divideByBinwidth(h_bJets_noShift_withWeight);
  divideByBinwidth(h_bJets_withShift_noWeight);
  divideByBinwidth(h_bJets_withShift_withWeight);
  
  normalize(h_bJets_noShift_noWeight);
  normalize(h_bJets_noShift_withWeight);
  normalize(h_bJets_withShift_noWeight);
  normalize(h_bJets_withShift_withWeight);

  TH1D *r1, *r2, *r3;
  r1 = (TH1D*) h_bJets_noShift_withWeight->Clone("r1");
  r2 = (TH1D*) h_bJets_withShift_noWeight->Clone("r2");
  r3 = (TH1D*) h_bJets_withShift_withWeight->Clone("r3");
  r1->Divide(h_bJets_noShift_withWeight,h_bJets_noShift_noWeight,1,1,"B");
  r2->Divide(h_bJets_withShift_noWeight,h_bJets_noShift_noWeight,1,1,"B");
  r3->Divide(h_bJets_withShift_withWeight,h_bJets_noShift_noWeight,1,1,"B");

  TCanvas *canv_1 = new TCanvas("canv_1","canv_1",700,700);
  canv_1->cd();
  TPad *pad_1 = new TPad("pad_1","pad_1",0,0,1,1);
  pad_1->SetLeftMargin(0.15);
  pad_1->SetBottomMargin(0.15);
  pad_1->SetTopMargin(0.1);
  pad_1->SetBottomMargin(0.1);
  pad_1->Draw();
  pad_1->cd();
  h_hiBin_noShift_noWeight->SetTitle("");
  h_hiBin_noShift_noWeight->SetStats(0);
  h_hiBin_noShift_noWeight->GetXaxis()->SetTitleSize(0.045);
  h_hiBin_noShift_noWeight->GetYaxis()->SetTitleSize(0.045);
  h_hiBin_noShift_noWeight->GetXaxis()->SetTitle("hiBin");
  h_hiBin_noShift_noWeight->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d(hiBin)");
  h_hiBin_noShift_noWeight->GetYaxis()->SetRangeUser(0,0.03);
  h_hiBin_noShift_noWeight->Draw("hist");
  h_hiBin_noShift_withWeight->Draw("hist same");
  h_hiBin_withShift_noWeight->Draw("hist same");
  h_hiBin_withShift_withWeight->Draw("hist same");

  la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.035);
  la->DrawLatexNDC(0.5,0.8,"PYTHIA+HYDJET");
  la->DrawLatexNDC(0.5,0.73,"#it{#mu}-tagged jet events");
  la->SetTextFont(62);
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.5,0.66,"no shift, no weight");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.5,0.59,"with shift, no weight");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.5,0.52,"no shift, with weight");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.5,0.45,"with shift, with weight");

  
  TCanvas *canv_2 = new TCanvas("canv_2","canv_2",700,700);
  canv_2->cd();
  TPad *pad_2_up = new TPad("pad_2_up","pad_2_up",0,0.4,1,1);
  TPad *pad_2_down = new TPad("pad_2_down","pad_2_down",0,0,1,0.4);
  pad_2_up->SetLeftMargin(0.15);
  pad_2_up->SetBottomMargin(0.0);
  pad_2_up->SetTopMargin(0.1);
  pad_2_up->SetRightMargin(0.1);
  pad_2_down->SetLeftMargin(0.15);
  pad_2_down->SetBottomMargin(0.2);
  pad_2_down->SetTopMargin(0.0);
  pad_2_down->SetRightMargin(0.1);
  pad_2_up->Draw();
  pad_2_down->Draw();
  pad_2_up->cd();
  h_bJets_noShift_noWeight->SetTitle("");
  h_bJets_noShift_noWeight->SetStats(0);
  h_bJets_noShift_noWeight->GetXaxis()->SetTitleSize(0.045);
  h_bJets_noShift_noWeight->GetYaxis()->SetTitleSize(0.045);
  h_bJets_noShift_noWeight->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  h_bJets_noShift_noWeight->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
  h_bJets_noShift_noWeight->GetYaxis()->SetRangeUser(0,0.3);
  h_bJets_noShift_noWeight->Draw("hist");
  h_bJets_noShift_withWeight->Draw("hist same");
  h_bJets_withShift_noWeight->Draw("hist same");
  h_bJets_withShift_withWeight->Draw("hist same");
  la->SetTextFont(42);
  la->SetTextColor(kBlack);
  la->SetTextSize(0.045);
  la->DrawLatexNDC(0.6,0.6,"PYTHIA+HYDJET 0-10%");
  la->DrawLatexNDC(0.6,0.53,"#it{b}-jets");
  la->DrawLatexNDC(0.6,0.46,Form("%3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f",jetPtLow,jetPtHigh));
  pad_2_down->cd();
  r1->SetTitle("");
  r1->SetStats(0);
  r1->GetXaxis()->SetTitleSize(0.07);
  r1->GetXaxis()->SetLabelSize(0.06);
  r1->GetYaxis()->SetTitleSize(0.07);
  r1->GetYaxis()->SetLabelSize(0.06);
  r1->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  r1->GetYaxis()->SetTitle("altered / nominal");
  r1->GetYaxis()->SetRangeUser(0,2);
  r1->Draw("hist");
  r2->Draw("hist same");
  r3->Draw("hist same");
  

  li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);

}
