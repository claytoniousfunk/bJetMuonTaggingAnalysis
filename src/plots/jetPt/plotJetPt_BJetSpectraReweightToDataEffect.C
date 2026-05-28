#include "../../../headers/functions/divideByBinwidth.h"


void stylizeHistograms(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  double lineWidth = 2;
  
  h1->SetLineWidth(lineWidth);
  h2->SetLineWidth(lineWidth);
  h3->SetLineWidth(lineWidth);
  h4->SetLineWidth(lineWidth);

  h1->SetLineStyle(2);
  h2->SetLineStyle(2);
  h3->SetLineStyle(1);
  h4->SetLineStyle(1);

  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kBlue-4);
  h4->SetLineColor(kRed-4);

}



void plotJetPt_BJetSpectraReweightToDataEffect(){

  TLine *li = new TLine();
  

  // TFile *f_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-31.root");
  // TFile *f_re = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-31.root");





  TFile *f_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-4-6_oddEvents.root");
  TFile *f_re = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_BJetSpectraReweightToData_2026-4-9.root");

  TH2D *H_nom, *H_re;
  TH2D *G_nom, *G_re;

  TH1D *hb_nom, *hbb_nom, *hbGS_nom; // h = reco, g = gen
  TH1D *gb_nom, *gbb_nom, *gbGS_nom; 
  TH1D *hb_re, *hbb_re, *hbGS_re; 
  TH1D *gb_re, *gbb_re, *gbGS_re;

  // f_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_nom);
  // f_re->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_re);

  f_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C1",H_nom);
  f_re->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C1",H_re);

  // f_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H_nom);
  // f_re->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H_re);

  // f_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C3",H_nom);
  // f_re->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C3",H_re);

  // f_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C4",H_nom);
  // f_re->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C4",H_re);

  

  TString title = "#it{b}-jets, PYTHIA+HYDJET 0-10%";
  //TString title = "#it{b}-jets, PYTHIA";

  hb_nom = (TH1D*) H_nom->ProjectionX("hb_nom");
  gb_nom = (TH1D*) H_nom->ProjectionY("gb_nom");

  hb_re = (TH1D*) H_re->ProjectionX("hb_re");
  gb_re = (TH1D*) H_re->ProjectionY("gb_re");

  const int N_coarseAxis = 8;
  double coarseAxis[N_coarseAxis] = {80,90,100,120,150,200,300,500};

  hb_nom = (TH1D*) hb_nom->Rebin(N_coarseAxis-1,"hb_nom",coarseAxis);
  hb_re = (TH1D*) hb_re->Rebin(N_coarseAxis-1,"hb_re",coarseAxis);
  gb_nom = (TH1D*) gb_nom->Rebin(N_coarseAxis-1,"gb_nom",coarseAxis);
  gb_re = (TH1D*) gb_re->Rebin(N_coarseAxis-1,"gb_re",coarseAxis);
  divideByBinwidth(hb_nom);
  divideByBinwidth(hb_re);
  divideByBinwidth(gb_nom);
  divideByBinwidth(gb_re);

  
  stylizeHistograms(hb_nom,gb_nom,hb_re,gb_re);

  TH1D *r_reco = (TH1D*) gb_re->Clone("r_reco");
  r_reco->Divide(gb_re,hb_re,1,1,"B");

  TH1D *r_gen = (TH1D*) gb_nom->Clone("r_gen");
  r_gen->Divide(gb_nom,hb_nom,1,1,"B");


  double leftMargin = 0.15;
  double bottomMargin = 0.15;

  TLegend *leg = new TLegend(0.55,0.55,0.75,0.75);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.044);
  // leg->AddEntry(hb_nom,"Reco (nominal)","l");
  // leg->AddEntry(gb_nom,"Gen (nominal)","l");
  // leg->AddEntry(hb_re,"Reco (reweighted)","l");
  // leg->AddEntry(gb_re,"Gen (reweighted)","l");
  leg->AddEntry(hb_re,"Reco","l");
  leg->AddEntry(gb_re,"Gen","l");
  
  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad_upper = new TPad("pad_upper","pad_upper",0,0.4,1,1);
  TPad *pad_lower = new TPad("pad_lower","pad_lower",0,0,1,0.4);
  pad_upper->SetLeftMargin(0.15);
  pad_lower->SetLeftMargin(0.15);
  pad_upper->SetBottomMargin(0.);
  pad_lower->SetBottomMargin(0.18);
  pad_upper->SetTopMargin(0.15);
  pad_lower->SetTopMargin(0.);
  pad_upper->SetLogy();
  pad_upper->Draw();
  pad_lower->Draw();
  pad_upper->cd();
  hb_re->SetTitle("");
  hb_re->SetStats(0);
  hb_re->SetTitle(title);
  hb_re->GetYaxis()->SetTitleSize(0.06);
  hb_re->GetYaxis()->SetTitle("a.u.");
  hb_re->Draw("hist");
  gb_re->Draw("hist same");
  // gb_nom->Draw("hist same");
  // hb_nom->Draw("hist same");
  leg->Draw();
  pad_lower->cd();
  r_reco->SetTitle("");
  r_reco->SetStats(0);
  r_reco->GetYaxis()->SetTitleSize(0.07);
  r_reco->GetXaxis()->SetTitleSize(0.07);  
  r_reco->GetYaxis()->SetTitle("Gen / Reco");
  r_reco->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_reco->GetYaxis()->SetRangeUser(0,2);
  r_reco->Draw();
  li->SetLineStyle(7);
  li->DrawLine(80,1,500,1);
  //r_gen->Draw("same");

  TFile *file_reverseUnfoldFactor = (TFile*) TFile::Open("../../../rootFiles/correctionFactors/reverseUnfoldFactor_C1.root","recreate");
  r_reco->Write("reverseUnfoldFactor_C1");
  file_reverseUnfoldFactor->Close();
  


}
