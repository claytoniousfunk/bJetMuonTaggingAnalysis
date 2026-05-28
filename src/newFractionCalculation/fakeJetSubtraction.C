
#include "../../headers/functions/divideByBinwidth.h"



void normalizeToMatchHistogram(TH1D *h_ref, TH1D *h_mod){

  // h_ref = reference histogram
  // h_mod = modified histogram

  double normRangeLow = 120.0;
  double normRangeHigh = 500.0;
  double smallShift = 0.01;

  double normFactor_ref = h_ref->Integral(h_ref->FindBin(normRangeLow+smallShift),h_ref->FindBin(normRangeHigh - smallShift));
  double normFactor_mod = h_mod->Integral(h_mod->FindBin(normRangeLow+smallShift),h_mod->FindBin(normRangeHigh - smallShift));
  double normFactor_final = normFactor_ref / normFactor_mod;

  h_mod->Scale(normFactor_final);

  cout << "modified hist by factor: " << normFactor_final << endl;

  return;

}


void normalize(TH1D *h){

  double normRangeLow = 100.0;
  double normRangeHigh = 500.0;
  double smallShift = 0.01;

  double normFactor = h->Integral(h->FindBin(normRangeLow+smallShift),h->FindBin(normRangeHigh - smallShift));

  h->Scale(1./normFactor);

  return;
  
}

void stylize(TH1D *h1, TH1D *h2, TH1D *h3){

  double lineWidth = 2.0;
  h1->SetLineWidth(lineWidth);
  h2->SetLineWidth(lineWidth);
  h3->SetLineWidth(lineWidth);

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kRed-4);

  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);

  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");
  

}

void configure2Pads(TPad *pad_upper, TPad *pad_lower){

  double leftMargin = 0.15;
  double bottomMargin = 0.15;
  double topMargin = 0.1;
  
  pad_upper->SetLeftMargin(leftMargin);
  pad_lower->SetLeftMargin(leftMargin);

  pad_upper->SetBottomMargin(0.0);
  pad_lower->SetBottomMargin(bottomMargin);

  pad_upper->SetTopMargin(topMargin);
  pad_lower->SetTopMargin(0.0);

  return;
  

}

double integrate(TH1D *h, double lowerBound, double upperBound){

  double result = 0.0;
  double smallShift = 0.01;
  
  int a = h->FindBin(lowerBound+smallShift);
  int b = h->FindBin(upperBound-smallShift);

  for(int i = a; i <= b; i++){
    result += h->GetBinContent(i);
  }

  return result;

}

void stylizeFakeJets(TH1D *h_C4, TH1D *h_C3, TH1D *h_C2, TH1D *h_C1){

  double lineWidth = 2.0;
  h_C4->SetLineWidth(lineWidth);
  h_C3->SetLineWidth(lineWidth);
  h_C2->SetLineWidth(lineWidth);
  h_C1->SetLineWidth(lineWidth);

  h_C4->SetLineColor(kBlack);
  h_C3->SetLineColor(kBlue-4);
  h_C2->SetLineColor(kGreen+2);
  h_C1->SetLineColor(kRed-4);



}


void fakeJetSubtraction(){

  TFile *file_PYTHIA = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-2-2.root");
  //TFile *file_PYTHIA = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_Jet60HLT_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-10-24.root");
  

  //TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/latest/HYDJET_pThat-unweighted_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-12_ultraFineCentBins.root");
  //TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/latest/HYDJET_pThat-unweighted_Jet60HLT_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-12_ultraFineCentBins.root");
  //TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-4-17.root");
  //TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-4-28.root");

  // TFile *file_PH_evt = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-8_ultraFineCentBins.root");
  // TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-5-12_ultraFineCentBins.root");

  // TFile *file_PH_evt = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-12_ultraFineCentBins.root");
  //TFile *file_PH_evt = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_Jet60HLT_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-12_ultraFineCentBins.root");
  // TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-5-12_ultraFineCentBins.root");
  //TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_Jet60HLT_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-5-12_ultraFineCentBins.root");


  // TFile *file_PH_evt = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-13_ultraFineCentBins.root");
  // TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-13_ultraFineCentBins.root");
  // TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-13_ultraFineCentBins.root");

  // TFile *file_PH_evt = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_Jet60HLT_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-12_ultraFineCentBins.root");
  // TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_Jet60HLT_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-12_ultraFineCentBins.root");
  // TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/latest/HYDJET_pThat-unweighted_Jet60HLT_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-12_ultraFineCentBins.root");

  // TFile *file_PH_evt = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-unweighted_Jet60HLT_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-13_ultraFineCentBins.root");
  // TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-unweighted_Jet60HLT_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-13_ultraFineCentBins.root");
  // TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-unweighted_Jet60HLT_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-13_ultraFineCentBins.root");

  // TFile *file_PH_evt = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-4-28.root");
  // TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-4-28.root");
  // TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/latest/HYDJET_pThat-unweighted_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-4-21.root");

  // TFile *file_PH_evt = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-19.root");
  // TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-19.root");
  // TFile *file_PHw = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-19.root");
  // TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/latest/HYDJET_pThat-unweighted_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-19.root");

  // TFile *file_PH_evt = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_Jet60HLT_mu12_pTmu-15to999_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-19.root");
  // TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_Jet60HLT_mu12_pTmu-15to999_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-19.root");
  // TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/latest/HYDJET_pThat-unweighted_Jet60HLT_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-19.root");

  
  // TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-21.root");
  
  //TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-21.root");
  // TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/canonical/HYDJET_pThat-unweighted_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-27.root");



  TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-27.root");
  TFile *file_PHw = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-27.root");
  TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-27.root");
  //TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-26.root");

  //TFile *file_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-26.root");
  // TFile *file_PHw = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-27.root");
  //TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/canonical/HYDJET_pThat-unweighted_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-27.root");
  TFile *file_PbPb = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_MinBias_mu12_pTmu-15to999_tight_WDecayFilter_2026-4-8.root");

  

  



  
  TH2D *H_HYDJET_C4, *H_HYDJET_C3, *H_HYDJET_C2, *H_HYDJET_C1;
  TH2D *H_PH_C4, *H_PH_C3, *H_PH_C2, *H_PH_C1;
  TH2D *H_PHw_C4, *H_PHw_C3, *H_PHw_C2, *H_PHw_C1;
  TH2D *H_PYTHIA;
  TH1D *h_HYDJET_allJets_C4, *h_HYDJET_allJets_C3, *h_HYDJET_allJets_C2, *h_HYDJET_allJets_C1;
  TH1D *h_PH_matchedJets_C4, *h_PH_matchedJets_C3, *h_PH_matchedJets_C2, *h_PH_matchedJets_C1;
  TH1D *h_PHw_matchedJets_C4, *h_PHw_matchedJets_C3, *h_PHw_matchedJets_C2, *h_PHw_matchedJets_C1;
  TH1D *h_PH_allJets_C4, *h_PH_allJets_C3, *h_PH_allJets_C2, *h_PH_allJets_C1;
  TH1D *h_PHw_allJets_C4, *h_PHw_allJets_C3, *h_PHw_allJets_C2, *h_PHw_allJets_C1;
  TH1D *h_PH_matchedJetsAdd_C4, *h_PH_matchedJetsAdd_C3, *h_PH_matchedJetsAdd_C2, *h_PH_matchedJetsAdd_C1;
  TH1D *h_PH_matchedJetsAdd2_C4, *h_PH_matchedJetsAdd2_C3, *h_PH_matchedJetsAdd2_C2, *h_PH_matchedJetsAdd2_C1;
  TH1D *h_PHw_matchedJetsAdd_C4, *h_PHw_matchedJetsAdd_C3, *h_PHw_matchedJetsAdd_C2, *h_PHw_matchedJetsAdd_C1;
  TH1D *h_PHw_matchedJetsAdd2_C4, *h_PHw_matchedJetsAdd2_C3, *h_PHw_matchedJetsAdd2_C2, *h_PHw_matchedJetsAdd2_C1;
  TH1D *h_PbPb_C4, *h_PbPb_C3, *h_PbPb_C2, *h_PbPb_C1;
  TH1D *h_PYTHIA_allJets;
  TH1D *h_hiBin_HYDJET, *h_hiBin_PH, *h_hiBin_PbPb;
  TH1D *h_vz_HYDJET, *h_vz_PH;


  file_PbPb->GetObject("h_inclRecoJetPt_C4",h_PbPb_C4);
  file_PbPb->GetObject("h_inclRecoJetPt_C3",h_PbPb_C3);
  file_PbPb->GetObject("h_inclRecoJetPt_C2",h_PbPb_C2);
  file_PbPb->GetObject("h_inclRecoJetPt_C1",h_PbPb_C1);
  file_PbPb->GetObject("h_hiBin",h_hiBin_PbPb);

  double N_PbPb_C4 = integrate(h_hiBin_PbPb,100,160);
  double N_PbPb_C3 = integrate(h_hiBin_PbPb,60,100);
  double N_PbPb_C2 = integrate(h_hiBin_PbPb,20,60);
  double N_PbPb_C1 = integrate(h_hiBin_PbPb,0,20);
		       
    
  file_PYTHIA->GetObject("h_inclRecoJetPt_flavor",H_PYTHIA);
  
  file_HYDJET->GetObject("h_inclRecoJetPt_flavor_C4",H_HYDJET_C4);
  file_HYDJET->GetObject("h_inclRecoJetPt_flavor_C3",H_HYDJET_C3);
  file_HYDJET->GetObject("h_inclRecoJetPt_flavor_C2",H_HYDJET_C2);
  file_HYDJET->GetObject("h_inclRecoJetPt_flavor_C1",H_HYDJET_C1);
  file_HYDJET->GetObject("h_hiBin",h_hiBin_HYDJET);

  int shift = 0; // artifically apply shift now to side-step bug in scanning code
  double N_HYDJET_C4 = integrate(h_hiBin_HYDJET,100+shift,160+shift);
  double N_HYDJET_C3 = integrate(h_hiBin_HYDJET,60+shift,100+shift);
  double N_HYDJET_C2 = integrate(h_hiBin_HYDJET,20+shift,60+shift);
  double N_HYDJET_C1 = integrate(h_hiBin_HYDJET,0+shift,20+shift);

  cout << "N_HYDJET_C4 = " << N_HYDJET_C4 << endl;
  cout << "N_HYDJET_C3 = " << N_HYDJET_C3 << endl;
  cout << "N_HYDJET_C2 = " << N_HYDJET_C2 << endl;
  cout << "N_HYDJET_C1 = " << N_HYDJET_C1 << endl;


  file_PH->GetObject("h_inclRecoJetPt_flavor_C4",H_PH_C4);
  file_PH->GetObject("h_inclRecoJetPt_flavor_C3",H_PH_C3);
  file_PH->GetObject("h_inclRecoJetPt_flavor_C2",H_PH_C2);
  file_PH->GetObject("h_inclRecoJetPt_flavor_C1",H_PH_C1);
  file_PH->GetObject("h_hiBin",h_hiBin_PH);

  file_PHw->GetObject("h_inclRecoJetPt_flavor_C4",H_PHw_C4);
  file_PHw->GetObject("h_inclRecoJetPt_flavor_C3",H_PHw_C3);
  file_PHw->GetObject("h_inclRecoJetPt_flavor_C2",H_PHw_C2);
  file_PHw->GetObject("h_inclRecoJetPt_flavor_C1",H_PHw_C1);

  
  double N_PH_C4 = integrate(h_hiBin_PH,100+shift,160+shift);
  double N_PH_C3 = integrate(h_hiBin_PH,60+shift,100+shift);
  double N_PH_C2 = integrate(h_hiBin_PH,20+shift,60+shift);
  double N_PH_C1 = integrate(h_hiBin_PH,0+shift,20+shift);

  cout << "N_PH_C4 = " << N_PH_C4 << endl;
  cout << "N_PH_C3 = " << N_PH_C3 << endl;
  cout << "N_PH_C2 = " << N_PH_C2 << endl;
  cout << "N_PH_C1 = " << N_PH_C1 << endl;

  h_PYTHIA_allJets = (TH1D*) H_PYTHIA->ProjectionX("h_PYTHIA_allJets");

  // just get x-jets
  // h_HYDJET_allJets_C4 = (TH1D*) H_HYDJET_C4->ProjectionX("h_HYDJET_allJets_C4",H_HYDJET_C4->GetYaxis()->FindBin(0.),H_HYDJET_C4->GetYaxis()->FindBin(0.));
  // h_HYDJET_allJets_C3 = (TH1D*) H_HYDJET_C3->ProjectionX("h_HYDJET_allJets_C3",H_HYDJET_C3->GetYaxis()->FindBin(0.),H_HYDJET_C3->GetYaxis()->FindBin(0.));
  // h_HYDJET_allJets_C2 = (TH1D*) H_HYDJET_C2->ProjectionX("h_HYDJET_allJets_C2",H_HYDJET_C2->GetYaxis()->FindBin(0.),H_HYDJET_C2->GetYaxis()->FindBin(0.));
  // h_HYDJET_allJets_C1 = (TH1D*) H_HYDJET_C1->ProjectionX("h_HYDJET_allJets_C1",H_HYDJET_C1->GetYaxis()->FindBin(0.),H_HYDJET_C1->GetYaxis()->FindBin(0.));

  // just get the x-jets (unmatched)
  h_HYDJET_allJets_C4 = (TH1D*) H_HYDJET_C4->ProjectionX("h_HYDJET_allJets_C4",H_HYDJET_C4->GetYaxis()->FindBin(18.),H_HYDJET_C4->GetYaxis()->FindBin(18.));
  h_HYDJET_allJets_C3 = (TH1D*) H_HYDJET_C3->ProjectionX("h_HYDJET_allJets_C3",H_HYDJET_C3->GetYaxis()->FindBin(18.),H_HYDJET_C3->GetYaxis()->FindBin(18.));
  h_HYDJET_allJets_C2 = (TH1D*) H_HYDJET_C2->ProjectionX("h_HYDJET_allJets_C2",H_HYDJET_C2->GetYaxis()->FindBin(18.),H_HYDJET_C2->GetYaxis()->FindBin(18.));
  h_HYDJET_allJets_C1 = (TH1D*) H_HYDJET_C1->ProjectionX("h_HYDJET_allJets_C1",H_HYDJET_C1->GetYaxis()->FindBin(18.),H_HYDJET_C1->GetYaxis()->FindBin(18.));

  // get all jets
  // h_HYDJET_allJets_C4 = (TH1D*) H_HYDJET_C4->ProjectionX("h_HYDJET_allJets_C4",H_HYDJET_C4->GetYaxis()->FindBin(-5.),H_HYDJET_C4->GetYaxis()->FindBin(21.));
  // h_HYDJET_allJets_C3 = (TH1D*) H_HYDJET_C3->ProjectionX("h_HYDJET_allJets_C3",H_HYDJET_C3->GetYaxis()->FindBin(-5.),H_HYDJET_C3->GetYaxis()->FindBin(21.));
  // h_HYDJET_allJets_C2 = (TH1D*) H_HYDJET_C2->ProjectionX("h_HYDJET_allJets_C2",H_HYDJET_C2->GetYaxis()->FindBin(-5.),H_HYDJET_C2->GetYaxis()->FindBin(21.));
  // h_HYDJET_allJets_C1 = (TH1D*) H_HYDJET_C1->ProjectionX("h_HYDJET_allJets_C1",H_HYDJET_C1->GetYaxis()->FindBin(-5.),H_HYDJET_C1->GetYaxis()->FindBin(21.));

  double smallShift = 0.01;
  
  h_PH_matchedJets_C4 = (TH1D*) H_PH_C4->ProjectionX("h_PH_matchedJets_C4",H_PH_C4->GetYaxis()->FindBin(-5.+smallShift),H_PH_C4->GetYaxis()->FindBin(0.-smallShift));
  h_PH_matchedJetsAdd_C4 = (TH1D*) H_PH_C4->ProjectionX("h_PH_matchedJetsAdd_C4",H_PH_C4->GetYaxis()->FindBin(1.+smallShift),H_PH_C4->GetYaxis()->FindBin(18.-smallShift));
  h_PH_matchedJetsAdd2_C4 = (TH1D*) H_PH_C4->ProjectionX("h_PH_matchedJetsAdd2_C4",H_PH_C4->GetYaxis()->FindBin(19.+smallShift),H_PH_C4->GetYaxis()->FindBin(22.-smallShift));
  h_PH_matchedJets_C4->Add(h_PH_matchedJetsAdd_C4);
  h_PH_matchedJets_C4->Add(h_PH_matchedJetsAdd2_C4);

  h_PH_matchedJets_C3 = (TH1D*) H_PH_C3->ProjectionX("h_PH_matchedJets_C3",H_PH_C3->GetYaxis()->FindBin(-5.+smallShift),H_PH_C3->GetYaxis()->FindBin(0.-smallShift));
  h_PH_matchedJetsAdd_C3 = (TH1D*) H_PH_C3->ProjectionX("h_PH_matchedJetsAdd_C3",H_PH_C3->GetYaxis()->FindBin(1.+smallShift),H_PH_C3->GetYaxis()->FindBin(18.-smallShift));
  h_PH_matchedJetsAdd2_C3 = (TH1D*) H_PH_C3->ProjectionX("h_PH_matchedJetsAdd2_C3",H_PH_C3->GetYaxis()->FindBin(19.+smallShift),H_PH_C3->GetYaxis()->FindBin(22.-smallShift));
  h_PH_matchedJets_C3->Add(h_PH_matchedJetsAdd_C3);
  h_PH_matchedJets_C3->Add(h_PH_matchedJetsAdd2_C3);

  h_PH_matchedJets_C2 = (TH1D*) H_PH_C2->ProjectionX("h_PH_matchedJets_C2",H_PH_C2->GetYaxis()->FindBin(-5.+smallShift),H_PH_C2->GetYaxis()->FindBin(0.-smallShift));
  h_PH_matchedJetsAdd_C2 = (TH1D*) H_PH_C2->ProjectionX("h_PH_matchedJetsAdd_C2",H_PH_C2->GetYaxis()->FindBin(1.+smallShift),H_PH_C2->GetYaxis()->FindBin(18.-smallShift));
  h_PH_matchedJetsAdd2_C2 = (TH1D*) H_PH_C2->ProjectionX("h_PH_matchedJetsAdd2_C2",H_PH_C2->GetYaxis()->FindBin(19.+smallShift),H_PH_C2->GetYaxis()->FindBin(22.-smallShift));
  h_PH_matchedJets_C2->Add(h_PH_matchedJetsAdd_C2);
  h_PH_matchedJets_C2->Add(h_PH_matchedJetsAdd2_C2);

  h_PH_matchedJets_C1 = (TH1D*) H_PH_C1->ProjectionX("h_PH_matchedJets_C1",H_PH_C1->GetYaxis()->FindBin(-5.+smallShift),H_PH_C1->GetYaxis()->FindBin(0.-smallShift));
  h_PH_matchedJetsAdd_C1 = (TH1D*) H_PH_C1->ProjectionX("h_PH_matchedJetsAdd_C1",H_PH_C1->GetYaxis()->FindBin(1.+smallShift),H_PH_C1->GetYaxis()->FindBin(18.-smallShift));
  h_PH_matchedJetsAdd2_C1 = (TH1D*) H_PH_C1->ProjectionX("h_PH_matchedJetsAdd2_C1",H_PH_C1->GetYaxis()->FindBin(19.+smallShift),H_PH_C1->GetYaxis()->FindBin(22.-smallShift));
  h_PH_matchedJets_C1->Add(h_PH_matchedJetsAdd_C1);
  h_PH_matchedJets_C1->Add(h_PH_matchedJetsAdd2_C1);



  



  h_PHw_matchedJets_C4 = (TH1D*) H_PHw_C4->ProjectionX("h_PHw_matchedJets_C4",H_PHw_C4->GetYaxis()->FindBin(-5.+smallShift),H_PHw_C4->GetYaxis()->FindBin(0.-smallShift));
  h_PHw_matchedJetsAdd_C4 = (TH1D*) H_PHw_C4->ProjectionX("h_PHw_matchedJetsAdd_C4",H_PHw_C4->GetYaxis()->FindBin(1.+smallShift),H_PHw_C4->GetYaxis()->FindBin(18.-smallShift));
  h_PHw_matchedJetsAdd2_C4 = (TH1D*) H_PHw_C4->ProjectionX("h_PHw_matchedJetsAdd2_C4",H_PHw_C4->GetYaxis()->FindBin(19.+smallShift),H_PHw_C4->GetYaxis()->FindBin(22.-smallShift));
  h_PHw_matchedJets_C4->Add(h_PHw_matchedJetsAdd_C4);
  h_PHw_matchedJets_C4->Add(h_PHw_matchedJetsAdd2_C4);
  //h_PHw_matchedJets_C4 = (TH1D*) H_PHw_C4->ProjectionX("h_PHw_matchedJets_C4");
  
  

  h_PHw_matchedJets_C3 = (TH1D*) H_PHw_C3->ProjectionX("h_PHw_matchedJets_C3",H_PHw_C3->GetYaxis()->FindBin(-5.+smallShift),H_PHw_C3->GetYaxis()->FindBin(0.-smallShift));
  h_PHw_matchedJetsAdd_C3 = (TH1D*) H_PHw_C3->ProjectionX("h_PHw_matchedJetsAdd_C3",H_PHw_C3->GetYaxis()->FindBin(1.+smallShift),H_PHw_C3->GetYaxis()->FindBin(18.-smallShift));
  h_PHw_matchedJetsAdd2_C3 = (TH1D*) H_PHw_C3->ProjectionX("h_PHw_matchedJetsAdd2_C3",H_PHw_C3->GetYaxis()->FindBin(19.+smallShift),H_PHw_C3->GetYaxis()->FindBin(22.-smallShift));
  h_PHw_matchedJets_C3->Add(h_PHw_matchedJetsAdd_C3);
  h_PHw_matchedJets_C3->Add(h_PHw_matchedJetsAdd2_C3);
  // h_PHw_matchedJets_C3 = (TH1D*) H_PHw_C3->ProjectionX("h_PHw_matchedJets_C3");

  h_PHw_matchedJets_C2 = (TH1D*) H_PHw_C2->ProjectionX("h_PHw_matchedJets_C2",H_PHw_C2->GetYaxis()->FindBin(-5.+smallShift),H_PHw_C2->GetYaxis()->FindBin(0.-smallShift));
  h_PHw_matchedJetsAdd_C2 = (TH1D*) H_PHw_C2->ProjectionX("h_PHw_matchedJetsAdd_C2",H_PHw_C2->GetYaxis()->FindBin(1.+smallShift),H_PHw_C2->GetYaxis()->FindBin(18.-smallShift));
  h_PHw_matchedJetsAdd2_C2 = (TH1D*) H_PHw_C2->ProjectionX("h_PHw_matchedJetsAdd2_C2",H_PHw_C2->GetYaxis()->FindBin(19.+smallShift),H_PHw_C2->GetYaxis()->FindBin(22.-smallShift));
  h_PHw_matchedJets_C2->Add(h_PHw_matchedJetsAdd_C2);
  h_PHw_matchedJets_C2->Add(h_PHw_matchedJetsAdd2_C2);
  // h_PHw_matchedJets_C2 = (TH1D*) H_PHw_C2->ProjectionX("h_PHw_matchedJets_C2");

  h_PHw_matchedJets_C1 = (TH1D*) H_PHw_C1->ProjectionX("h_PHw_matchedJets_C1",H_PHw_C1->GetYaxis()->FindBin(-5.+smallShift),H_PHw_C1->GetYaxis()->FindBin(0.-smallShift));
  h_PHw_matchedJetsAdd_C1 = (TH1D*) H_PHw_C1->ProjectionX("h_PHw_matchedJetsAdd_C1",H_PHw_C1->GetYaxis()->FindBin(1.+smallShift),H_PHw_C1->GetYaxis()->FindBin(18.-smallShift));
  h_PHw_matchedJetsAdd2_C1 = (TH1D*) H_PHw_C1->ProjectionX("h_PHw_matchedJetsAdd2_C1",H_PHw_C1->GetYaxis()->FindBin(19.+smallShift),H_PHw_C1->GetYaxis()->FindBin(22.-smallShift));
  h_PHw_matchedJets_C1->Add(h_PHw_matchedJetsAdd_C1);
  h_PHw_matchedJets_C1->Add(h_PHw_matchedJetsAdd2_C1);
  // h_PHw_matchedJets_C1 = (TH1D*) H_PHw_C1->ProjectionX("h_PHw_matchedJets_C1");


  

  // h_PH_allJets_C4 = (TH1D*) H_PH_C4->ProjectionX("h_PH_allJets_C4",H_PH_C4->GetYaxis()->FindBin(-5.+smallShift),H_PH_C4->GetYaxis()->FindBin(22.-smallShift));
  // h_PH_allJets_C3 = (TH1D*) H_PH_C3->ProjectionX("h_PH_allJets_C3",H_PH_C3->GetYaxis()->FindBin(-5.+smallShift),H_PH_C3->GetYaxis()->FindBin(22.-smallShift));
  // h_PH_allJets_C2 = (TH1D*) H_PH_C2->ProjectionX("h_PH_allJets_C2",H_PH_C2->GetYaxis()->FindBin(-5.+smallShift),H_PH_C2->GetYaxis()->FindBin(22.-smallShift));
  // h_PH_allJets_C1 = (TH1D*) H_PH_C1->ProjectionX("h_PH_allJets_C1",H_PH_C1->GetYaxis()->FindBin(-5.+smallShift),H_PH_C1->GetYaxis()->FindBin(22.-smallShift));

  h_PH_allJets_C4 = (TH1D*) H_PH_C4->ProjectionX("h_PH_allJets_C4");
  h_PH_allJets_C3 = (TH1D*) H_PH_C3->ProjectionX("h_PH_allJets_C3");
  h_PH_allJets_C2 = (TH1D*) H_PH_C2->ProjectionX("h_PH_allJets_C2");
  h_PH_allJets_C1 = (TH1D*) H_PH_C1->ProjectionX("h_PH_allJets_C1");

  h_PHw_allJets_C4 = (TH1D*) H_PHw_C4->ProjectionX("h_PHw_allJets_C4");
  h_PHw_allJets_C3 = (TH1D*) H_PHw_C3->ProjectionX("h_PHw_allJets_C3");
  h_PHw_allJets_C2 = (TH1D*) H_PHw_C2->ProjectionX("h_PHw_allJets_C2");
  h_PHw_allJets_C1 = (TH1D*) H_PHw_C1->ProjectionX("h_PHw_allJets_C1");


  // TH1D *r = (TH1D*) h_PH_allJets_C1->Clone("r");
  // r->Divide(h_PH_allJets_C1,h_PH_matchedJets_C1,1,1,"B");
  // r->Draw();





  
  TH1D *h_HYDJET_allJets_C4_clone = (TH1D*) h_HYDJET_allJets_C4->Clone("h_HYDJET_allJets_C4_clone");

  normalize(h_PYTHIA_allJets);
  normalize(h_HYDJET_allJets_C4_clone);
  
  stylize(h_PYTHIA_allJets, h_HYDJET_allJets_C4, h_PH_matchedJets_C4);
  stylize(h_PYTHIA_allJets, h_HYDJET_allJets_C4_clone, h_PH_matchedJets_C4);
  stylize(h_PYTHIA_allJets, h_HYDJET_allJets_C3, h_PH_matchedJets_C3);
  stylize(h_PYTHIA_allJets, h_HYDJET_allJets_C2, h_PH_matchedJets_C2);
  stylize(h_PYTHIA_allJets, h_HYDJET_allJets_C1, h_PH_matchedJets_C1);

  stylize(h_PYTHIA_allJets, h_HYDJET_allJets_C4, h_PHw_matchedJets_C4);
  stylize(h_PYTHIA_allJets, h_HYDJET_allJets_C4_clone, h_PHw_matchedJets_C4);
  stylize(h_PYTHIA_allJets, h_HYDJET_allJets_C3, h_PHw_matchedJets_C3);
  stylize(h_PYTHIA_allJets, h_HYDJET_allJets_C2, h_PHw_matchedJets_C2);
  stylize(h_PYTHIA_allJets, h_HYDJET_allJets_C1, h_PHw_matchedJets_C1);

  // const int N_edge = 5;
  // double newAxis[N_edge] = {80,100,120,150,200};

  // const int N_edge = 22;
  // double newAxis[N_edge] = {20,30,40,50,60,70,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,500};

  const int N_edge = 9;
  double newAxis[N_edge] = {20,30,40,50,60,80,100,120,500};

  // const int N_edge = 10;
  // double newAxis[N_edge] = {20,30,40,50,60,80,100,120,150,200};

  // h_PYTHIA_allJets = (TH1D*) h_PYTHIA_allJets->Rebin(N_edge-1,"h_PYTHIA_allJets",newAxis);
  // h_HYDJET_allJets_C4 = (TH1D*) h_HYDJET_allJets_C4->Rebin(N_edge-1,"h_HYDJET_allJets_C4",newAxis);
  // h_HYDJET_allJets_C4_clone = (TH1D*) h_HYDJET_allJets_C4_clone->Rebin(N_edge-1,"h_HYDJET_allJets_C4_clone",newAxis);
  // h_HYDJET_allJets_C3 = (TH1D*) h_HYDJET_allJets_C3->Rebin(N_edge-1,"h_HYDJET_allJets_C3",newAxis);
  // h_HYDJET_allJets_C2 = (TH1D*) h_HYDJET_allJets_C2->Rebin(N_edge-1,"h_HYDJET_allJets_C2",newAxis);
  // h_HYDJET_allJets_C1 = (TH1D*) h_HYDJET_allJets_C1->Rebin(N_edge-1,"h_HYDJET_allJets_C1",newAxis);
  // h_PH_matchedJets_C4 = (TH1D*) h_PH_matchedJets_C4->Rebin(N_edge-1,"h_PH_matchedJets_C4",newAxis);
  // h_PH_matchedJets_C3 = (TH1D*) h_PH_matchedJets_C3->Rebin(N_edge-1,"h_PH_matchedJets_C3",newAxis);
  // h_PH_matchedJets_C2 = (TH1D*) h_PH_matchedJets_C2->Rebin(N_edge-1,"h_PH_matchedJets_C2",newAxis);
  // h_PH_matchedJets_C1 = (TH1D*) h_PH_matchedJets_C1->Rebin(N_edge-1,"h_PH_matchedJets_C1",newAxis);
  // h_PH_allJets_C4 = (TH1D*) h_PH_allJets_C4->Rebin(N_edge-1,"h_PH_allJets_C4",newAxis);
  // h_PH_allJets_C3 = (TH1D*) h_PH_allJets_C3->Rebin(N_edge-1,"h_PH_allJets_C3",newAxis);
  // h_PH_allJets_C2 = (TH1D*) h_PH_allJets_C2->Rebin(N_edge-1,"h_PH_allJets_C2",newAxis);
  // h_PH_allJets_C1 = (TH1D*) h_PH_allJets_C1->Rebin(N_edge-1,"h_PH_allJets_C1",newAxis);
  // h_PHw_matchedJets_C4 = (TH1D*) h_PHw_matchedJets_C4->Rebin(N_edge-1,"h_PHw_matchedJets_C4",newAxis);
  // h_PHw_matchedJets_C3 = (TH1D*) h_PHw_matchedJets_C3->Rebin(N_edge-1,"h_PHw_matchedJets_C3",newAxis);
  // h_PHw_matchedJets_C2 = (TH1D*) h_PHw_matchedJets_C2->Rebin(N_edge-1,"h_PHw_matchedJets_C2",newAxis);
  // h_PHw_matchedJets_C1 = (TH1D*) h_PHw_matchedJets_C1->Rebin(N_edge-1,"h_PHw_matchedJets_C1",newAxis);
  // h_PHw_allJets_C4 = (TH1D*) h_PHw_allJets_C4->Rebin(N_edge-1,"h_PHw_allJets_C4",newAxis);
  // h_PHw_allJets_C3 = (TH1D*) h_PHw_allJets_C3->Rebin(N_edge-1,"h_PHw_allJets_C3",newAxis);
  // h_PHw_allJets_C2 = (TH1D*) h_PHw_allJets_C2->Rebin(N_edge-1,"h_PHw_allJets_C2",newAxis);
  // h_PHw_allJets_C1 = (TH1D*) h_PHw_allJets_C1->Rebin(N_edge-1,"h_PHw_allJets_C1",newAxis);

  // divideByBinwidth(h_PYTHIA_allJets);
  // divideByBinwidth(h_HYDJET_allJets_C4_clone);
  // divideByBinwidth(h_HYDJET_allJets_C4);
  // divideByBinwidth(h_HYDJET_allJets_C3);
  // divideByBinwidth(h_HYDJET_allJets_C2);
  // divideByBinwidth(h_HYDJET_allJets_C1);
  // divideByBinwidth(h_PH_matchedJets_C4);
  // divideByBinwidth(h_PH_matchedJets_C3);
  // divideByBinwidth(h_PH_matchedJets_C2);
  // divideByBinwidth(h_PH_matchedJets_C1);
  // divideByBinwidth(h_PH_allJets_C4);
  // divideByBinwidth(h_PH_allJets_C3);
  // divideByBinwidth(h_PH_allJets_C2);
  // divideByBinwidth(h_PH_allJets_C1);
  // divideByBinwidth(h_PHw_matchedJets_C4);
  // divideByBinwidth(h_PHw_matchedJets_C3);
  // divideByBinwidth(h_PHw_matchedJets_C2);
  // divideByBinwidth(h_PHw_matchedJets_C1);
  // divideByBinwidth(h_PHw_allJets_C4);
  // divideByBinwidth(h_PHw_allJets_C3);
  // divideByBinwidth(h_PHw_allJets_C2);
  // divideByBinwidth(h_PHw_allJets_C1);

  
  TLine *li = new TLine();
  li->SetLineStyle(7);

  
  

  TCanvas *canv_C4sc = new TCanvas("canv_C4sc","canv_C4sc",700,700); // sc = spectra compare
  TPad *pad_C4sc_upper = new TPad("pad_C4sc_upper","pad_C4sc_upper",0,0.4,1,1);
  TPad *pad_C4sc_lower = new TPad("pad_C4sc_lower","pad_C4sc_lower",0,0,1,0.4);
  configure2Pads(pad_C4sc_upper,pad_C4sc_lower);
  canv_C4sc->cd();
  pad_C4sc_upper->SetLogy();
  pad_C4sc_upper->Draw();
  pad_C4sc_lower->Draw();
  pad_C4sc_upper->cd();
  h_HYDJET_allJets_C4_clone->GetYaxis()->SetTitleSize(0.05);
  h_HYDJET_allJets_C4_clone->GetYaxis()->SetLabelSize(0.045);
  h_HYDJET_allJets_C4_clone->GetYaxis()->SetTitle("#frac{1}{#it{N}^{jet}_{#it{p}_{T} > 120 GeV}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_HYDJET_allJets_C4_clone->Draw("hist");
  h_PYTHIA_allJets->Draw("hist same");
  TLegend *leg_C4sc = new TLegend(0.6,0.6,0.85,0.85);
  leg_C4sc->SetBorderSize(0);
  leg_C4sc->SetTextSize(0.04);
  leg_C4sc->AddEntry(h_HYDJET_allJets_C4_clone,"HYDJET 50-80%");
  leg_C4sc->AddEntry(h_PYTHIA_allJets,"PYTHIA");
  leg_C4sc->Draw();
  pad_C4sc_lower->cd();
  TH1D *r_C4sc = (TH1D*) h_HYDJET_allJets_C4_clone->Clone("r_C4sc");
  r_C4sc->Divide(h_HYDJET_allJets_C4_clone,h_PYTHIA_allJets,1,1,"");
  r_C4sc->GetYaxis()->SetRangeUser(0.,2.);
  r_C4sc->GetYaxis()->SetTitleSize(0.06);
  r_C4sc->GetYaxis()->SetLabelSize(0.05);
  r_C4sc->GetXaxis()->SetTitleSize(0.06);
  r_C4sc->GetXaxis()->SetLabelSize(0.05);
  r_C4sc->GetYaxis()->SetTitle("HYDJET / PYTHIA");
  r_C4sc->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C4sc->Draw();
  li->DrawLine(newAxis[0],1,newAxis[N_edge-1],1);



  
  
  

  // scale by 1/Nevt

  // h_HYDJET_allJets_C4->Scale(1./N_HYDJET_C4);
  // h_HYDJET_allJets_C3->Scale(1./N_HYDJET_C3);
  // h_HYDJET_allJets_C2->Scale(1./N_HYDJET_C2);
  // h_HYDJET_allJets_C1->Scale(1./N_HYDJET_C1);

  // h_PH_matchedJets_C4->Scale(1./N_PH_C4);
  // h_PH_matchedJets_C3->Scale(1./N_PH_C3);
  // h_PH_matchedJets_C2->Scale(1./N_PH_C2);
  // h_PH_matchedJets_C1->Scale(1./N_PH_C1);

  // normalize(h_HYDJET_allJets_C4);
  // normalize(h_HYDJET_allJets_C3);
  // normalize(h_HYDJET_allJets_C2);
  // normalize(h_HYDJET_allJets_C1);

  // normalize(h_PH_matchedJets_C4);
  // normalize(h_PH_matchedJets_C3);
  // normalize(h_PH_matchedJets_C2);
  // normalize(h_PH_matchedJets_C1);

  TH1D *h_PHw_matchedJets_C4_clone = (TH1D*) h_PHw_matchedJets_C4->Clone("h_PHw_matchedJets_C4_clone");
  TH1D *h_PHw_matchedJets_C3_clone = (TH1D*) h_PHw_matchedJets_C3->Clone("h_PHw_matchedJets_C3_clone");
  TH1D *h_PHw_matchedJets_C2_clone = (TH1D*) h_PHw_matchedJets_C2->Clone("h_PHw_matchedJets_C2_clone");
  TH1D *h_PHw_matchedJets_C1_clone = (TH1D*) h_PHw_matchedJets_C1->Clone("h_PHw_matchedJets_C1_clone");

  normalizeToMatchHistogram(h_HYDJET_allJets_C4, h_PHw_matchedJets_C4_clone);
  normalizeToMatchHistogram(h_HYDJET_allJets_C3, h_PHw_matchedJets_C3_clone);
  normalizeToMatchHistogram(h_HYDJET_allJets_C2, h_PHw_matchedJets_C2_clone);
  normalizeToMatchHistogram(h_HYDJET_allJets_C1, h_PHw_matchedJets_C1_clone);

  // normalizeToMatchHistogram(h_HYDJET_allJets_C4, h_PHw_allJets_C4);
  // normalizeToMatchHistogram(h_HYDJET_allJets_C3, h_PHw_allJets_C3);
  // normalizeToMatchHistogram(h_HYDJET_allJets_C2, h_PHw_allJets_C2);
  // normalizeToMatchHistogram(h_HYDJET_allJets_C1, h_PHw_allJets_C1);

  TCanvas *canv_C4 = new TCanvas("canv_C4","canv_C4",700,700);
  TPad *pad_C4_upper = new TPad("pad_C4_upper","pad_C4_upper",0,0.4,1,1);
  TPad *pad_C4_lower = new TPad("pad_C4_lower","pad_C4_lower",0,0,1,0.4);
  configure2Pads(pad_C4_upper,pad_C4_lower);
  canv_C4->cd();
  pad_C4_upper->SetLogy();
  pad_C4_upper->Draw();
  pad_C4_lower->Draw();
  pad_C4_upper->cd();
  h_HYDJET_allJets_C4->GetYaxis()->SetTitleSize(0.05);
  h_HYDJET_allJets_C4->GetYaxis()->SetLabelSize(0.045);
  h_HYDJET_allJets_C4->GetYaxis()->SetTitle("#frac{1}{#it{N}^{jet}_{#it{p}_{T} > 120 GeV}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_HYDJET_allJets_C4->Draw("hist");
  h_PHw_matchedJets_C4_clone->Draw("hist same");
  TLegend *leg_C4 = new TLegend(0.6,0.6,0.85,0.85);
  leg_C4->SetBorderSize(0);
  leg_C4->SetTextSize(0.04);
  leg_C4->AddEntry(h_HYDJET_allJets_C4_clone,"HYDJET 50-80%");
  leg_C4->AddEntry(h_PHw_matchedJets_C4,"matched P+H 50-80%");
  leg_C4->Draw();
  pad_C4_lower->cd();
  TH1D *r_C4 = (TH1D*) h_HYDJET_allJets_C4->Clone("r_C4");
  r_C4->Divide(h_HYDJET_allJets_C4,h_PHw_matchedJets_C4_clone,1,1,"");
  r_C4->GetYaxis()->SetRangeUser(0.,2.);
  r_C4->GetYaxis()->SetTitleSize(0.06);
  r_C4->GetYaxis()->SetLabelSize(0.05);
  r_C4->GetXaxis()->SetTitleSize(0.06);
  r_C4->GetXaxis()->SetLabelSize(0.05);
  r_C4->GetYaxis()->SetTitle("HYDJET / P+H");
  r_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C4->Draw();
  li->DrawLine(newAxis[0],1,newAxis[N_edge-1],1);


  TCanvas *canv_C3 = new TCanvas("canv_C3","canv_C3",700,700);
  TPad *pad_C3_upper = new TPad("pad_C3_upper","pad_C3_upper",0,0.4,1,1);
  TPad *pad_C3_lower = new TPad("pad_C3_lower","pad_C3_lower",0,0,1,0.4);
  configure2Pads(pad_C3_upper,pad_C3_lower);
  canv_C3->cd();
  pad_C3_upper->SetLogy();
  pad_C3_upper->Draw();
  pad_C3_lower->Draw();
  pad_C3_upper->cd();
  h_HYDJET_allJets_C3->GetYaxis()->SetTitleSize(0.05);
  h_HYDJET_allJets_C3->GetYaxis()->SetLabelSize(0.045);
  h_HYDJET_allJets_C3->GetYaxis()->SetTitle("#frac{1}{#it{N}^{jet}_{#it{p}_{T} > 120 GeV}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_HYDJET_allJets_C3->Draw("hist");
  h_PHw_matchedJets_C3_clone->Draw("hist same");
  TLegend *leg_C3 = new TLegend(0.6,0.6,0.85,0.85);
  leg_C3->SetBorderSize(0);
  leg_C3->SetTextSize(0.04);
  leg_C3->AddEntry(h_HYDJET_allJets_C3,"HYDJET 30-50%");
  leg_C3->AddEntry(h_PHw_matchedJets_C3,"matched P+H 30-50%");
  leg_C3->Draw();
  pad_C3_lower->cd();
  TH1D *r_C3 = (TH1D*) h_HYDJET_allJets_C3->Clone("r_C3");
  r_C3->Divide(h_HYDJET_allJets_C3,h_PHw_matchedJets_C3_clone,1,1,"");
  r_C3->GetYaxis()->SetRangeUser(0.,2.);
  r_C3->GetYaxis()->SetTitleSize(0.06);
  r_C3->GetYaxis()->SetLabelSize(0.05);
  r_C3->GetXaxis()->SetTitleSize(0.06);
  r_C3->GetXaxis()->SetLabelSize(0.05);
  r_C3->GetYaxis()->SetTitle("HYDJET / P+H");
  r_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C3->Draw();
  li->DrawLine(newAxis[0],1,newAxis[N_edge-1],1);


  TCanvas *canv_C2 = new TCanvas("canv_C2","canv_C2",700,700);
  TPad *pad_C2_upper = new TPad("pad_C2_upper","pad_C2_upper",0,0.4,1,1);
  TPad *pad_C2_lower = new TPad("pad_C2_lower","pad_C2_lower",0,0,1,0.4);
  configure2Pads(pad_C2_upper,pad_C2_lower);
  canv_C2->cd();
  pad_C2_upper->SetLogy();
  pad_C2_upper->Draw();
  pad_C2_lower->Draw();
  pad_C2_upper->cd();
  h_HYDJET_allJets_C2->GetYaxis()->SetTitleSize(0.05);
  h_HYDJET_allJets_C2->GetYaxis()->SetLabelSize(0.045);
  h_HYDJET_allJets_C2->GetYaxis()->SetTitle("#frac{1}{#it{N}^{jet}_{#it{p}_{T} > 120 GeV}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_HYDJET_allJets_C2->Draw("hist");
  h_PHw_matchedJets_C2_clone->Draw("hist same");
  TLegend *leg_C2 = new TLegend(0.6,0.6,0.85,0.85);
  leg_C2->SetBorderSize(0);
  leg_C2->SetTextSize(0.04);
  leg_C2->AddEntry(h_HYDJET_allJets_C2,"HYDJET 10-30%");
  leg_C2->AddEntry(h_PHw_matchedJets_C2,"matched P+H 10-30%");
  leg_C2->Draw();
  pad_C2_lower->cd();
  TH1D *r_C2 = (TH1D*) h_HYDJET_allJets_C2->Clone("r_C2");
  r_C2->Divide(h_HYDJET_allJets_C2,h_PHw_matchedJets_C2_clone,1,1,"");
  r_C2->GetYaxis()->SetRangeUser(0.,2.);
  r_C2->GetYaxis()->SetTitleSize(0.06);
  r_C2->GetYaxis()->SetLabelSize(0.05);
  r_C2->GetXaxis()->SetTitleSize(0.06);
  r_C2->GetXaxis()->SetLabelSize(0.05);
  r_C2->GetYaxis()->SetTitle("HYDJET / P+H");
  r_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C2->Draw();
  li->DrawLine(newAxis[0],1,newAxis[N_edge-1],1);


  TCanvas *canv_C1 = new TCanvas("canv_C1","canv_C1",700,700);
  TPad *pad_C1_upper = new TPad("pad_C1_upper","pad_C1_upper",0,0.4,1,1);
  TPad *pad_C1_lower = new TPad("pad_C1_lower","pad_C1_lower",0,0,1,0.4);
  configure2Pads(pad_C1_upper,pad_C1_lower);
  canv_C1->cd();
  pad_C1_upper->SetLogy();
  pad_C1_upper->Draw();
  pad_C1_lower->Draw();
  pad_C1_upper->cd();
  h_HYDJET_allJets_C1->GetYaxis()->SetTitleSize(0.05);
  h_HYDJET_allJets_C1->GetYaxis()->SetLabelSize(0.045);
  h_HYDJET_allJets_C1->GetYaxis()->SetTitle("#frac{1}{#it{N}^{jet}_{#it{p}_{T} > 120 GeV}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_HYDJET_allJets_C1->Draw("hist");
  h_PHw_matchedJets_C1_clone->Draw("hist same");
  TLegend *leg_C1 = new TLegend(0.6,0.6,0.85,0.85);
  leg_C1->SetBorderSize(0);
  leg_C1->SetTextSize(0.04);
  leg_C1->AddEntry(h_HYDJET_allJets_C1,"HYDJET 0-10%");
  leg_C1->AddEntry(h_PHw_matchedJets_C1,"matched P+H 0-10%");
  leg_C1->Draw();
  pad_C1_lower->cd();
  TH1D *r_C1 = (TH1D*) h_HYDJET_allJets_C1->Clone("r_C1");
  r_C1->Divide(h_HYDJET_allJets_C1,h_PHw_matchedJets_C1_clone,1,1,"");
  r_C1->GetYaxis()->SetRangeUser(0.,2.);
  r_C1->GetYaxis()->SetTitleSize(0.06);
  r_C1->GetYaxis()->SetLabelSize(0.05);
  r_C1->GetXaxis()->SetTitleSize(0.06);
  r_C1->GetXaxis()->SetLabelSize(0.05);
  r_C1->GetYaxis()->SetTitle("HYDJET / P+H");
  r_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C1->Draw();
  li->DrawLine(newAxis[0],1,newAxis[N_edge-1],1);
  


  

  TH1D *h_fakeJets_C4, *h_fakeJets_C3, *h_fakeJets_C2, *h_fakeJets_C1;

  h_fakeJets_C4 = (TH1D*) h_HYDJET_allJets_C4->Clone("h_fakeJets_C4");
  //h_fakeJets_C4->Add(h_PH_matchedJets_C4,-1);
  normalizeToMatchHistogram(h_fakeJets_C4, h_PHw_matchedJets_C4);
  h_fakeJets_C4->Add(h_PHw_matchedJets_C4,-1);
  h_fakeJets_C4->Scale(1./N_HYDJET_C4);

  h_fakeJets_C3 = (TH1D*) h_HYDJET_allJets_C3->Clone("h_fakeJets_C3");
  // h_fakeJets_C3->Add(h_PH_matchedJets_C3,-1);
  normalizeToMatchHistogram(h_fakeJets_C3, h_PHw_matchedJets_C3);
  h_fakeJets_C3->Add(h_PHw_matchedJets_C3,-1);
  h_fakeJets_C3->Scale(1./N_HYDJET_C3);

  h_fakeJets_C2 = (TH1D*) h_HYDJET_allJets_C2->Clone("h_fakeJets_C2");
  // h_fakeJets_C2->Add(h_PH_matchedJets_C2,-1);
  normalizeToMatchHistogram(h_fakeJets_C2, h_PHw_matchedJets_C2);
  h_fakeJets_C2->Add(h_PHw_matchedJets_C2,-1);
  h_fakeJets_C2->Scale(1./N_HYDJET_C2);

  h_fakeJets_C1 = (TH1D*) h_HYDJET_allJets_C1->Clone("h_fakeJets_C1");
  // h_fakeJets_C1->Add(h_PH_matchedJets_C1,-1);
  normalizeToMatchHistogram(h_fakeJets_C1, h_PHw_matchedJets_C1);
  h_fakeJets_C1->Add(h_PHw_matchedJets_C1,-1);
  h_fakeJets_C1->Scale(1./N_HYDJET_C1);




  stylizeFakeJets(h_fakeJets_C4,h_fakeJets_C3,h_fakeJets_C2,h_fakeJets_C1);

  TCanvas *canv_fakeJets = new TCanvas("canv_fakeJets","canv_fakeJets",700,700);
  canv_fakeJets->cd();
  TPad *pad_fakeJets = new TPad("pad_fakeJets","pad_fakeJets",0,0,1,1);
  pad_fakeJets->SetLeftMargin(0.15);
  pad_fakeJets->SetBottomMargin(0.15);
  //pad_fakeJets->SetLogy();
  pad_fakeJets->Draw();
  pad_fakeJets->cd();
  h_fakeJets_C1->GetYaxis()->SetTitleSize(0.04);
  h_fakeJets_C1->GetYaxis()->SetLabelSize(0.03);
  h_fakeJets_C1->GetXaxis()->SetTitleSize(0.04);
  h_fakeJets_C1->GetXaxis()->SetLabelSize(0.03);
  h_fakeJets_C1->GetYaxis()->SetTitle("#frac{1}{#it{N}^{evt}} #frac{d#it{N}^{fake-jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_fakeJets_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //h_fakeJets_C1->GetXaxis()->SetRangeUser(80,150);
  h_fakeJets_C1->Draw("hist");
  h_fakeJets_C2->Draw("hist same");
  h_fakeJets_C3->Draw("hist same");
  h_fakeJets_C4->Draw("hist same");
  TLegend *leg_fakeJets = new TLegend(0.6,0.6,0.85,0.85);
  leg_fakeJets->SetBorderSize(0);
  leg_fakeJets->SetTextSize(0.035);
  leg_fakeJets->AddEntry(h_fakeJets_C4,"HYDJET 50-80%");
  leg_fakeJets->AddEntry(h_fakeJets_C3,"HYDJET 30-50%");
  leg_fakeJets->AddEntry(h_fakeJets_C2,"HYDJET 10-30%");
  leg_fakeJets->AddEntry(h_fakeJets_C1,"HYDJET 0-10%");
  leg_fakeJets->Draw();



  TFile *file_fakeJets = (TFile*) TFile::Open("../../rootFiles/fakeJets/fakeJets.root","recreate");
  h_fakeJets_C4->Write();
  h_fakeJets_C3->Write();
  h_fakeJets_C2->Write();
  h_fakeJets_C1->Write();
  file_fakeJets->Close();
  
  
  canv_C4sc->SaveAs("../../figures/fakeJetSubtraction/jetPt_HYDJETVsPYTHIA_C4.pdf");
  canv_C4->SaveAs("../../figures/fakeJetSubtraction/jetPt_HYDJETVsMatchedPH_C4.pdf");
  canv_C3->SaveAs("../../figures/fakeJetSubtraction/jetPt_HYDJETVsMatchedPH_C3.pdf");
  canv_C2->SaveAs("../../figures/fakeJetSubtraction/jetPt_HYDJETVsMatchedPH_C2.pdf");
  canv_C1->SaveAs("../../figures/fakeJetSubtraction/jetPt_HYDJETVsMatchedPH_C1.pdf");
  canv_fakeJets->SaveAs("../../figures/fakeJetSubtraction/jetPt_fakeJets.pdf");


  ///*
  
  TH1D *h_PHw_allJets_corr_C4 = (TH1D*) h_PHw_allJets_C4->Clone("h_PHw_allJets_corr_C4");
  TH1D *h_PHw_allJets_corr_C3 = (TH1D*) h_PHw_allJets_C3->Clone("h_PHw_allJets_corr_C3");
  TH1D *h_PHw_allJets_corr_C2 = (TH1D*) h_PHw_allJets_C2->Clone("h_PHw_allJets_corr_C2");
  TH1D *h_PHw_allJets_corr_C1 = (TH1D*) h_PHw_allJets_C1->Clone("h_PHw_allJets_corr_C1");

  h_PHw_matchedJets_C4->Scale(1./N_PH_C4);
  h_PHw_matchedJets_C3->Scale(1./N_PH_C3);
  h_PHw_matchedJets_C2->Scale(1./N_PH_C2);
  h_PHw_matchedJets_C1->Scale(1./N_PH_C1);

  h_PHw_allJets_corr_C4->Scale(1./N_PH_C4);
  h_PHw_allJets_corr_C3->Scale(1./N_PH_C3);
  h_PHw_allJets_corr_C2->Scale(1./N_PH_C2);
  h_PHw_allJets_corr_C1->Scale(1./N_PH_C1);

  h_PHw_allJets_C4->Scale(1./N_PH_C4);
  h_PHw_allJets_C3->Scale(1./N_PH_C3);
  h_PHw_allJets_C2->Scale(1./N_PH_C2);
  h_PHw_allJets_C1->Scale(1./N_PH_C1);
  

  // subtract the fake jets
  h_PHw_allJets_corr_C4->Add(h_fakeJets_C4,-1);
  h_PHw_allJets_corr_C3->Add(h_fakeJets_C3,-1);
  h_PHw_allJets_corr_C2->Add(h_fakeJets_C2,-1);
  h_PHw_allJets_corr_C1->Add(h_fakeJets_C1,-1);



  // cout << "h_PH_allJets_corr_C1->Integral() = " << h_PH_allJets_corr_C1->Integral() << endl;
  // cout << "h_fakeJets_C1->Integral() = " << h_fakeJets_C1->Integral() << endl;


  // stylize(h_PH_allJets_C4,h_PH_allJets_corr_C4,h_PH_matchedJets_C4);
  // stylize(h_PH_allJets_C3,h_PH_allJets_corr_C3,h_PH_matchedJets_C3);
  // stylize(h_PH_allJets_C2,h_PH_allJets_corr_C2,h_PH_matchedJets_C2);
  // stylize(h_PH_allJets_C1,h_PH_allJets_corr_C1,h_PH_matchedJets_C1);

  stylize(h_PHw_allJets_C4,h_PHw_allJets_corr_C4,h_PHw_matchedJets_C4);
  stylize(h_PHw_allJets_C3,h_PHw_allJets_corr_C3,h_PHw_matchedJets_C3);
  stylize(h_PHw_allJets_C2,h_PHw_allJets_corr_C2,h_PHw_matchedJets_C2);
  stylize(h_PHw_allJets_C1,h_PHw_allJets_corr_C1,h_PHw_matchedJets_C1);
  

  TH1D *r_orig_C4 = (TH1D*) h_PHw_allJets_C4->Clone("r_orig_C4");
  r_orig_C4->Divide(h_PHw_allJets_C4,h_PHw_matchedJets_C4,1,1,"B");

  TH1D *r_orig_C3 = (TH1D*) h_PHw_allJets_C3->Clone("r_orig_C3");
  r_orig_C3->Divide(h_PHw_allJets_C3,h_PHw_matchedJets_C3,1,1,"B");

  TH1D *r_orig_C2 = (TH1D*) h_PHw_allJets_C2->Clone("r_orig_C2");
  r_orig_C2->Divide(h_PHw_allJets_C2,h_PHw_matchedJets_C2,1,1,"B");

  TH1D *r_orig_C1 = (TH1D*) h_PHw_allJets_C1->Clone("r_orig_C1");
  r_orig_C1->Divide(h_PHw_allJets_C1,h_PHw_matchedJets_C1,1,1,"B");
  

  TH1D *r_closure_C4 = (TH1D*) h_PHw_allJets_corr_C4->Clone("r_closure_C4");
  r_closure_C4->Divide(h_PHw_allJets_corr_C4,h_PHw_matchedJets_C4,1,1,"B");

  TH1D *r_closure_C3 = (TH1D*) h_PHw_allJets_corr_C3->Clone("r_closure_C3");
  r_closure_C3->Divide(h_PHw_allJets_corr_C3,h_PHw_matchedJets_C3,1,1,"B");

  TH1D *r_closure_C2 = (TH1D*) h_PHw_allJets_corr_C2->Clone("r_closure_C2");
  r_closure_C2->Divide(h_PHw_allJets_corr_C2,h_PHw_matchedJets_C2,1,1,"B");

  TH1D *r_closure_C1 = (TH1D*) h_PHw_allJets_corr_C1->Clone("r_closure_C1");
  r_closure_C1->Divide(h_PHw_allJets_corr_C1,h_PHw_matchedJets_C1,1,1,"B");


  

  TCanvas *canv_closure_C4 = new TCanvas("canv_closure_C4","canv_closure_C4",700,700);
  TPad *pad_closure_C4_upper = new TPad("pad_closure_C4_upper","pad_closure_C4_upper",0,0.4,1,1);
  TPad *pad_closure_C4_lower = new TPad("pad_closure_C4_lower","pad_closure_C4_lower",0,0,1,0.4);
  configure2Pads(pad_closure_C4_upper,pad_closure_C4_lower);
  canv_closure_C4->cd();
  pad_closure_C4_upper->SetLogy();
  pad_closure_C4_upper->Draw();
  pad_closure_C4_lower->Draw();
  pad_closure_C4_upper->cd();  
  h_PHw_allJets_corr_C4->GetYaxis()->SetTitleSize(0.05);
  h_PHw_allJets_corr_C4->GetYaxis()->SetLabelSize(0.045);
  h_PHw_allJets_corr_C4->GetYaxis()->SetTitle("#frac{1}{#it{N}^{jet}_{#it{p}_{T} > 120 GeV}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_PHw_allJets_corr_C4->Draw("hist");
  h_PHw_allJets_C4->Draw("hist same");
  h_PHw_matchedJets_C4->Draw("hist same");
  h_fakeJets_C4->SetLineStyle(7);
  h_fakeJets_C4->Draw("hist same");
  TLegend *leg_closure_C4 = new TLegend(0.6,0.6,0.85,0.85);
  leg_closure_C4->SetBorderSize(0);
  leg_closure_C4->SetTextSize(0.04);
  leg_closure_C4->AddEntry(h_PHw_allJets_C4,"Reco P+H 50-80%");
  leg_closure_C4->AddEntry(h_PHw_allJets_corr_C4,"Corrected P+H 50-80%");
  leg_closure_C4->AddEntry(h_PHw_matchedJets_C4,"Matched P+H 50-80%");
  leg_closure_C4->AddEntry(h_fakeJets_C4,"FakeJets 50-80%");
  leg_closure_C4->Draw();
  pad_closure_C4_lower->cd();
  r_closure_C4->GetYaxis()->SetRangeUser(0.,2.);
  r_closure_C4->GetYaxis()->SetTitleSize(0.06);
  r_closure_C4->GetYaxis()->SetLabelSize(0.05);
  r_closure_C4->GetXaxis()->SetTitleSize(0.06);
  r_closure_C4->GetXaxis()->SetLabelSize(0.05);
  r_closure_C4->GetYaxis()->SetTitle("Ratio to Matched");
  r_closure_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_closure_C4->Draw();
  r_orig_C4->Draw("same");
  li->DrawLine(0,1,500,1);

  TCanvas *canv_closure_C3 = new TCanvas("canv_closure_C3","canv_closure_C3",700,700);
  TPad *pad_closure_C3_upper = new TPad("pad_closure_C3_upper","pad_closure_C3_upper",0,0.4,1,1);
  TPad *pad_closure_C3_lower = new TPad("pad_closure_C3_lower","pad_closure_C3_lower",0,0,1,0.4);
  configure2Pads(pad_closure_C3_upper,pad_closure_C3_lower);
  canv_closure_C3->cd();
  pad_closure_C3_upper->SetLogy();
  pad_closure_C3_upper->Draw();
  pad_closure_C3_lower->Draw();
  pad_closure_C3_upper->cd();  
  h_PHw_allJets_corr_C3->GetYaxis()->SetTitleSize(0.05);
  h_PHw_allJets_corr_C3->GetYaxis()->SetLabelSize(0.045);
  h_PHw_allJets_corr_C3->GetYaxis()->SetTitle("#frac{1}{#it{N}^{jet}_{#it{p}_{T} > 120 GeV}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_PHw_allJets_corr_C3->Draw("hist");
  h_PHw_allJets_C3->Draw("hist same");
  h_PHw_matchedJets_C3->Draw("hist same");
  h_fakeJets_C3->Draw("hist same");
  h_fakeJets_C3->SetLineStyle(7);
  TLegend *leg_closure_C3 = new TLegend(0.6,0.6,0.85,0.85);
  leg_closure_C3->SetBorderSize(0);
  leg_closure_C3->SetTextSize(0.04);
  leg_closure_C3->AddEntry(h_PHw_allJets_C3,"Reco P+H 30-50%");
  leg_closure_C3->AddEntry(h_PHw_allJets_corr_C3,"Corrected P+H 30-50%");
  leg_closure_C3->AddEntry(h_PHw_matchedJets_C3,"Matched P+H 30-50%");
  leg_closure_C3->AddEntry(h_fakeJets_C3,"FakeJets 30-50%");
  leg_closure_C3->Draw();
  pad_closure_C3_lower->cd();
  r_closure_C3->GetYaxis()->SetRangeUser(0.,2.);
  r_closure_C3->GetYaxis()->SetTitleSize(0.06);
  r_closure_C3->GetYaxis()->SetLabelSize(0.05);
  r_closure_C3->GetXaxis()->SetTitleSize(0.06);
  r_closure_C3->GetXaxis()->SetLabelSize(0.05);
  r_closure_C3->GetYaxis()->SetTitle("Ratio to Matched");
  r_closure_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_closure_C3->Draw();
  r_orig_C3->Draw("same");
  li->DrawLine(0,1,500,1);


  TCanvas *canv_closure_C2 = new TCanvas("canv_closure_C2","canv_closure_C2",700,700);
  TPad *pad_closure_C2_upper = new TPad("pad_closure_C2_upper","pad_closure_C2_upper",0,0.4,1,1);
  TPad *pad_closure_C2_lower = new TPad("pad_closure_C2_lower","pad_closure_C2_lower",0,0,1,0.4);
  configure2Pads(pad_closure_C2_upper,pad_closure_C2_lower);
  canv_closure_C2->cd();
  pad_closure_C2_upper->SetLogy();
  pad_closure_C2_upper->Draw();
  pad_closure_C2_lower->Draw();
  pad_closure_C2_upper->cd();  
  h_PHw_allJets_corr_C2->GetYaxis()->SetTitleSize(0.05);
  h_PHw_allJets_corr_C2->GetYaxis()->SetLabelSize(0.045);
  h_PHw_allJets_corr_C2->GetYaxis()->SetTitle("#frac{1}{#it{N}^{jet}_{#it{p}_{T} > 120 GeV}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_PHw_allJets_corr_C2->Draw("hist");
  h_PHw_allJets_C2->Draw("hist same");
  h_PHw_matchedJets_C2->Draw("hist same");
  h_fakeJets_C2->Draw("hist same");
  h_fakeJets_C2->SetLineStyle(7);
  TLegend *leg_closure_C2 = new TLegend(0.6,0.6,0.85,0.85);
  leg_closure_C2->SetBorderSize(0);
  leg_closure_C2->SetTextSize(0.04);
  leg_closure_C2->AddEntry(h_PHw_allJets_C2,"Reco P+H 10-30%");
  leg_closure_C2->AddEntry(h_PHw_allJets_corr_C2,"Corrected P+H 10-30%");
  leg_closure_C2->AddEntry(h_PHw_matchedJets_C2,"Matched P+H 10-30%");
  leg_closure_C2->AddEntry(h_fakeJets_C2,"FakeJets 10-30%");
  leg_closure_C2->Draw();
  pad_closure_C2_lower->cd();
  r_closure_C2->GetYaxis()->SetRangeUser(0.,2.);
  r_closure_C2->GetYaxis()->SetTitleSize(0.06);
  r_closure_C2->GetYaxis()->SetLabelSize(0.05);
  r_closure_C2->GetXaxis()->SetTitleSize(0.06);
  r_closure_C2->GetXaxis()->SetLabelSize(0.05);
  r_closure_C2->GetYaxis()->SetTitle("Ratio to Matched");
  r_closure_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_closure_C2->Draw();
  r_orig_C2->Draw("same");
  li->DrawLine(0,1,500,1);


  TCanvas *canv_closure_C1 = new TCanvas("canv_closure_C1","canv_closure_C1",700,700);
  TPad *pad_closure_C1_upper = new TPad("pad_closure_C1_upper","pad_closure_C1_upper",0,0.4,1,1);
  TPad *pad_closure_C1_lower = new TPad("pad_closure_C1_lower","pad_closure_C1_lower",0,0,1,0.4);
  configure2Pads(pad_closure_C1_upper,pad_closure_C1_lower);
  canv_closure_C1->cd();
  pad_closure_C1_upper->SetLogy();
  pad_closure_C1_upper->Draw();
  pad_closure_C1_lower->Draw();
  pad_closure_C1_upper->cd();  
  h_PHw_allJets_corr_C1->GetYaxis()->SetTitleSize(0.05);
  h_PHw_allJets_corr_C1->GetYaxis()->SetLabelSize(0.045);
  h_PHw_allJets_corr_C1->GetYaxis()->SetTitle("#frac{1}{#it{N}^{jet}_{#it{p}_{T} > 120 GeV}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_PHw_allJets_corr_C1->Draw("hist");
  h_PHw_allJets_C1->Draw("hist same");
  h_PHw_matchedJets_C1->Draw("hist same");
  h_fakeJets_C1->Draw("hist same");
  h_fakeJets_C1->SetLineStyle(7);
  TLegend *leg_closure_C1 = new TLegend(0.6,0.6,0.85,0.85);
  leg_closure_C1->SetBorderSize(0);
  leg_closure_C1->SetTextSize(0.04);
  leg_closure_C1->AddEntry(h_PHw_allJets_C1,"Reco P+H 0-10%");
  leg_closure_C1->AddEntry(h_PHw_allJets_corr_C1,"Corrected P+H 0-10%");
  leg_closure_C1->AddEntry(h_PHw_matchedJets_C1,"Matched P+H 0-10%");
  leg_closure_C1->AddEntry(h_fakeJets_C1,"FakeJets 0-10%");
  leg_closure_C1->Draw();
  pad_closure_C1_lower->cd();
  r_closure_C1->GetYaxis()->SetRangeUser(0.,2.);
  r_closure_C1->GetYaxis()->SetTitleSize(0.06);
  r_closure_C1->GetYaxis()->SetLabelSize(0.05);
  r_closure_C1->GetXaxis()->SetTitleSize(0.06);
  r_closure_C1->GetXaxis()->SetLabelSize(0.05);
  r_closure_C1->GetYaxis()->SetTitle("Ratio to Matched");
  r_closure_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_closure_C1->Draw();
  r_orig_C1->Draw("same");
  li->DrawLine(0,1,500,1);


  canv_closure_C4->SaveAs("../../figures/fakeJetSubtraction/jetPt_HYDJETVsMatchedPH_closure_C4.pdf");
  canv_closure_C3->SaveAs("../../figures/fakeJetSubtraction/jetPt_HYDJETVsMatchedPH_closure_C3.pdf");
  canv_closure_C2->SaveAs("../../figures/fakeJetSubtraction/jetPt_HYDJETVsMatchedPH_closure_C2.pdf");
  canv_closure_C1->SaveAs("../../figures/fakeJetSubtraction/jetPt_HYDJETVsMatchedPH_closure_C1.pdf");

  //*/
  
}
