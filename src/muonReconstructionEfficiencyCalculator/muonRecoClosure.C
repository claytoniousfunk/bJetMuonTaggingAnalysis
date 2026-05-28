
#include "../../headers/functions/divideByBinwidth.h"


void stylizeHistograms(TH1D *h1, TH1D *h2, TH1D *h3){

  double lineWidth = 2.0;
  h1->SetLineWidth(lineWidth);
  h2->SetLineWidth(lineWidth);
  h3->SetLineWidth(lineWidth);

  double markerSize = 1.4;
  h1->SetMarkerSize(markerSize);
  h2->SetMarkerSize(markerSize);
  h3->SetMarkerSize(markerSize);

  h1->SetMarkerColor(kBlue-4);
  h2->SetMarkerColor(kRed-4);
  h3->SetMarkerColor(kGreen+2);

  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kGreen+2);
  
}


void muonRecoClosure(){

  // TFile *f_genMuTagged = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-1-26_genMuTaggedGenJets.root");
  // TFile *f_recoMuTagged = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-1-29_muTaggedJetsNoTrigger.root");

  TFile *f_genMuTagged = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-2-2.root");
  TFile *f_recoMuTagged = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-2-2.root");

  
  TFile *f_bJetMuRecoCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/");

  TH2D *H_bJets_recoMuTagged, *H_bJets_genMuTagged;
  TH1D *h_bJets_recoMuTagged, *h_bbarJets_recoMuTagged, *h_bGSJets_recoMuTagged;
  TH1D *h_bJets_genMuTagged, *h_bbarJets_genMuTagged, *h_bGSJets_genMuTagged;
  TH1D *h_bJets_recoMuTagged_withCorr;
  TH1D *h_bJetMuRecoCorr;
  TH1D *r_reco, *r_corr;

  // f_genMuTagged->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_bJets_genMuTagged);
  // f_recoMuTagged->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_bJets_recoMuTagged);
  // f_bJetMuRecoCorr->GetObject("corrFactor_2_pp",h_bJetMuRecoCorr);

  // f_genMuTagged->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor",H_bJets_genMuTagged);
  // f_recoMuTagged->GetObject("h_inclRecoJetPt_matchedRecoMuonTag_flavor",H_bJets_recoMuTagged);
  f_genMuTagged->GetObject("h_inclGenJetPt_inclGenMuonTag_flavor",H_bJets_genMuTagged);
  f_recoMuTagged->GetObject("h_inclGenJetPt_matchedRecoMuonTag_flavor",H_bJets_recoMuTagged);
  f_bJetMuRecoCorr->GetObject("corrFactor_2_pp",h_bJetMuRecoCorr);

  TH1D *binFinder = H_bJets_genMuTagged->ProjectionY();
  double smallShift = 0.01;
  
  h_bJets_genMuTagged = (TH1D*) H_bJets_genMuTagged->ProjectionX("h_bJets_genMuTagged",binFinder->FindBin(5.+smallShift),binFinder->FindBin(6.- smallShift));
  h_bJets_recoMuTagged = (TH1D*) H_bJets_recoMuTagged->ProjectionX("h_bJets_recoMuTagged",binFinder->FindBin(5.+smallShift),binFinder->FindBin(6.- smallShift));

  h_bbarJets_genMuTagged = (TH1D*) H_bJets_genMuTagged->ProjectionX("h_bbarJets_genMuTagged",binFinder->FindBin(-5.+smallShift),binFinder->FindBin(-4.- smallShift));
  h_bbarJets_recoMuTagged = (TH1D*) H_bJets_recoMuTagged->ProjectionX("h_bbarJets_recoMuTagged",binFinder->FindBin(-5.+smallShift),binFinder->FindBin(-4.- smallShift));

  h_bGSJets_genMuTagged = (TH1D*) H_bJets_genMuTagged->ProjectionX("h_bGSJets_genMuTagged",binFinder->FindBin(17.+smallShift),binFinder->FindBin(18.- smallShift));
  h_bGSJets_recoMuTagged = (TH1D*) H_bJets_recoMuTagged->ProjectionX("h_bGSJets_recoMuTagged",binFinder->FindBin(17.+smallShift),binFinder->FindBin(18.- smallShift));

  h_bJets_genMuTagged->Add(h_bbarJets_genMuTagged);
  h_bJets_genMuTagged->Add(h_bGSJets_genMuTagged);
  h_bJets_recoMuTagged->Add(h_bbarJets_recoMuTagged);
  h_bJets_recoMuTagged->Add(h_bGSJets_recoMuTagged);

  const int N_edge = 8;
  double newAxis[N_edge] = {80,90,100,120,150,200,300,500};

  h_bJets_genMuTagged = (TH1D*) h_bJets_genMuTagged->Rebin(N_edge-1,"h_bJets_genMuTagged",newAxis);
  h_bJets_recoMuTagged = (TH1D*) h_bJets_recoMuTagged->Rebin(N_edge-1,"h_bJets_recoMuTagged",newAxis);

  divideByBinwidth(h_bJets_genMuTagged);
  divideByBinwidth(h_bJets_recoMuTagged);

  h_bJets_recoMuTagged_withCorr = (TH1D*) h_bJets_recoMuTagged->Clone("h_bJets_recoMuTagged_withCorr");
  //h_bJets_recoMuTagged_withCorr->Divide(h_bJets_recoMuTagged,h_bJetMuRecoCorr,1,1,"B");
  h_bJets_recoMuTagged_withCorr->Scale(1./0.9708);
  

  stylizeHistograms(h_bJets_genMuTagged,h_bJets_recoMuTagged,h_bJets_recoMuTagged_withCorr);

  r_reco = (TH1D*) h_bJets_recoMuTagged->Clone("r_reco");
  r_corr = (TH1D*) h_bJets_recoMuTagged_withCorr->Clone("r_reco");

  r_reco->Divide(h_bJets_recoMuTagged,h_bJets_genMuTagged,1,1,"B");
  r_corr->Divide(h_bJets_recoMuTagged_withCorr,h_bJets_genMuTagged,1,1,"B");
  
  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  //pad->SetLogy();
  pad->Draw();
  pad->cd();

  ////////////////////////////////////////////////////

  // h_bJets_genMuTagged->Draw();
  // h_bJets_recoMuTagged->Draw("same");
  // h_bJets_recoMuTagged_withCorr->Draw("same");

  ////////////////////////////////////////////////////
  
  r_reco->GetYaxis()->SetRangeUser(0.9,1.1);
  r_reco->Draw("");
  r_corr->Draw("same");

  ///////////////////////////////////////////////////

}
