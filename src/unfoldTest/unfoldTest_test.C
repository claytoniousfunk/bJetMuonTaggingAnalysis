
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>

// #include "/home/clayton/Analysis/RooUnfold/src/RooUnfold.h"
// #include "/home/clayton/Analysis/RooUnfold/src/RooFitUnfold.h"
//#include "/home/clayton/Analysis/code/RooUnfold/src/RooUnfoldResponse.h"
//#include "/home/clayton/Analysis/code/RooUnfold/src/RooUnfoldBayes.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"

#endif

#include "../../headers/functions/divideByBinwidth.h"


void scaleHistogram(TH1D *h, double low, double high){

  h->Scale(1./h->Integral(h->FindBin(low),h->FindBin(high)));

}

void stylizeHistograms(TH1D *h1, TH1D *h2, TH1D *h3){

  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kGreen+2);

}

void stylizeHistograms(TH1D *h_pp, TH1D *h_C4, TH1D *h_C3, TH1D *h_C2, TH1D *h_C1){

  h_pp->SetLineColor(kBlack);
  h_C4->SetLineColor(kBlue-4);
  h_C3->SetLineColor(kRed-4);
  h_C2->SetLineColor(kGreen+2);
  h_C1->SetLineColor(kMagenta-9);

  h_pp->SetLineWidth(2);
  h_C4->SetLineWidth(2);
  h_C3->SetLineWidth(2);
  h_C2->SetLineWidth(2);
  h_C1->SetLineWidth(2);

}

void normalize(TH1D* h){

  double low = 150;
  double high = 500;
  h->Scale(1./h->Integral(h->FindBin(low),h->FindBin(high)));

}


TH1D* stitchSamples(TH1D *h_jetMB, TH1D *h_jet60, TH1D *h_jet80, TH1D *h_jet100,
		    bool isPP, bool isPbPb){

  TH1D *h_return = (TH1D*) h_jet100->Clone("h_return");

  double jetMB_pTmin = 60.;
  double jet60_pTmin = 100;
  double jet80_pTmin = 130;
  double jet100_pTmin = 200;
  double smallShift = 0.01;

  if(!isPP){
    jet60_pTmin = jet80_pTmin;
  }




  double N_jet100 = h_jet100->Integral(h_jet100->FindBin(jet100_pTmin + smallShift),h_jet100->FindBin(500. - smallShift));
  double N_jet80 = h_jet80->Integral(h_jet80->FindBin(jet100_pTmin + smallShift),h_jet80->FindBin(500. - smallShift));
  double N_jet60 = h_jet60->Integral(h_jet60->FindBin(jet80_pTmin + smallShift),h_jet60->FindBin(jet100_pTmin - smallShift));
  double N_jetMB = h_jetMB->Integral(h_jetMB->FindBin(jet60_pTmin + smallShift),h_jetMB->FindBin(jet80_pTmin - smallShift));

  

  
  TH1D *h_jet80_scaled = (TH1D*) h_jet80->Clone("h_jet80_scaled");
  h_jet80_scaled->Scale(N_jet100 / N_jet80);

  double N_jet80_scaled = h_jet80_scaled->Integral(h_jet80_scaled->FindBin(jet80_pTmin + smallShift),h_jet80_scaled->FindBin(jet100_pTmin - smallShift));

  TH1D *h_jet60_scaled = (TH1D*) h_jet60->Clone("h_jet60_scaled");
  h_jet60_scaled->Scale(N_jet80_scaled / N_jet60);
  
  double N_jet60_scaled = h_jet60_scaled->Integral(h_jet60_scaled->FindBin(jet60_pTmin + smallShift),h_jet60_scaled->FindBin(jet80_pTmin - smallShift));

  TH1D *h_jetMB_scaled = (TH1D*) h_jetMB->Clone("h_jetMB_scaled");
  h_jetMB_scaled->Scale(N_jet60_scaled / N_jetMB);
  
  
  
  

  

  for(int i = 0; i < h_jet60->GetSize(); i++){
    double pT = h_jet60->GetBinCenter(i);
    if(pT < jet60_pTmin){
      h_return->SetBinContent(i,h_jetMB_scaled->GetBinContent(i));
      h_return->SetBinError(i,h_jetMB_scaled->GetBinError(i));
    }
    else if(pT > jet60_pTmin && pT < jet80_pTmin){
      h_return->SetBinContent(i,h_jet60_scaled->GetBinContent(i));
      h_return->SetBinError(i,h_jet60_scaled->GetBinError(i));
    }
    else if(pT > jet80_pTmin && pT < jet100_pTmin){
      h_return->SetBinContent(i,h_jet80_scaled->GetBinContent(i));
      h_return->SetBinError(i,h_jet80_scaled->GetBinError(i));
    }
    else if(pT > jet100_pTmin){
      h_return->SetBinContent(i,h_jet100->GetBinContent(i));
      h_return->SetBinError(i,h_jet100->GetBinError(i));
    }
    else{};
    
  }

  return h_return;
  
}




void unfoldTest_test(){

  TLine *li = new TLine();

  //gSystem->Load("/home/clayton/Analysis/code/RooUnfold/build/libRooUnfold");  
    

  TFile *file_pp_HighEGJet_jet60 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet60HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-10.root");
  TFile *file_pp_HighEGJet_jet80 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet80HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-10.root");
  TFile *file_pp_HighEGJet_jet100 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet100HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_WDecayFilter_2026-3-11.root");
  TFile *file_pp_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_WDecayFilter_2026-3-16.root");
  TFile *file_pp_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_MinBias_mu12_pTmu-14_tight_jetTrkMaxFilter_2025-10-15.root");

  TFile *file_PbPb_HardProbes_jet60 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet60HLT_mu12_pTmu-15to999_tight_WDecayFilter_2026-3-11.root");
  TFile *file_PbPb_HardProbes_jet80 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet80HLT_mu12_pTmu-15to999_tight_WDecayFilter_2026-3-11.root");
  TFile *file_PbPb_HardProbes_jet100 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet100HLT_mu12_pTmu-15to999_tight_WDecayFilter_2026-3-11.root");
  TFile *file_PbPb_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15to999_tight_WDecayFilter_2026-3-12.root");
  TFile *file_PbPb_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_MinBias_mu12_pTmu-15to999_tight_2026-3-5.root");


  //TFile *file_PYTHIA_response_even = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-20_mu12_pTmu-15_tight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-3-17_evenEvents.root");
  //TFile *file_PYTHIA_response_even = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-31_evenEvents.root"); // with unmatched data
  TFile *file_PYTHIA_response_even = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-4-1_evenEvents_matchedRecoJetPtCut60.root"); // with unmatched data
  
  //TFile *file_PYTHIA_response_odd = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-20_mu12_pTmu-15_tight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_weightCut_2026-3-17_oddEvents.root");
  //TFile *file_PYTHIA_response_odd = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-31_evenEvents.root");
  TFile *file_PYTHIA_response_odd = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-4-1_oddEvents_matchedRecoJetPtCut60.root");

  //TFile *file_PH_response_even = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_leadingXjetDumpFilter_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-24_evenEvents.root");
  //TFile *file_PH_response_even = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-4-1_evenEvents.root");
  //TFile *file_PH_response_even = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-4-1_evenEvents_matchedRecoJetPtCut60.root");
  TFile *file_PH_response_even = TFile::Open("/home/clayton/Downloads/PYTHIAHYDJET_scan_output_1.root");
  
  //TFile *file_PH_response_odd = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_leadingXjetDumpFilter_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-24_oddEvents.root");
  //TFile *file_PH_response_odd = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-4-1_evenEvents.root");
  TFile *file_PH_response_odd = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-4-1_oddEvents_matchedRecoJetPtCut60.root");


  TH1D *h_pp, *h_C4, *h_C3, *h_C2, *h_C1;
  TH1D *h_pp_jetMB, *h_C4_jetMB, *h_C3_jetMB, *h_C2_jetMB, *h_C1_jetMB;
  TH1D *h_pp_jet60, *h_C4_jet60, *h_C3_jet60, *h_C2_jet60, *h_C1_jet60;
  TH1D *h_pp_jet80, *h_C4_jet80, *h_C3_jet80, *h_C2_jet80, *h_C1_jet80;
  TH1D *h_pp_jet100, *h_C4_jet100, *h_C3_jet100, *h_C2_jet100, *h_C1_jet100;

  file_pp_HighEGJet_jet60->GetObject("h_inclRecoJetPt",h_pp_jet60);
  file_pp_HighEGJet_jet80->GetObject("h_inclRecoJetPt",h_pp_jet80);
  file_pp_HighEGJet_jet100->GetObject("h_inclRecoJetPt",h_pp_jet100);
  file_pp_MinBias->GetObject("h_inclRecoJetPt",h_pp_jetMB);

  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C4",h_C4_jetMB);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C3",h_C3_jetMB);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C2",h_C2_jetMB);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C1",h_C1_jetMB);

  file_PbPb_HardProbes_jet60->GetObject("h_inclRecoJetPt_C4",h_C4_jet60);
  file_PbPb_HardProbes_jet60->GetObject("h_inclRecoJetPt_C3",h_C3_jet60);
  file_PbPb_HardProbes_jet60->GetObject("h_inclRecoJetPt_C2",h_C2_jet60);
  file_PbPb_HardProbes_jet60->GetObject("h_inclRecoJetPt_C1",h_C1_jet60);

  file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_C4",h_C4_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_C3",h_C3_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_C2",h_C2_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_C1",h_C1_jet80);

  file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_C4",h_C4_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_C3",h_C3_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_C2",h_C2_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_C1",h_C1_jet100);

  h_pp = (TH1D*) stitchSamples(h_pp_jetMB,h_pp_jet60,h_pp_jet80,h_pp_jet100,1,0);
  h_C4 = (TH1D*) stitchSamples(h_C4_jetMB,h_C4_jet60,h_C4_jet80,h_C4_jet100,0,1);
  h_C3 = (TH1D*) stitchSamples(h_C3_jetMB,h_C3_jet60,h_C3_jet80,h_C3_jet100,0,1);
  h_C2 = (TH1D*) stitchSamples(h_C2_jetMB,h_C2_jet60,h_C2_jet80,h_C2_jet100,0,1);
  h_C1 = (TH1D*) stitchSamples(h_C1_jetMB,h_C1_jet60,h_C1_jet80,h_C1_jet100,0,1);

  

  TH2D *h_response_pp, *h_response_C4, *h_response_C3, *h_response_C2, *h_response_C1;
  TH2D *h_response_pp_odd, *h_response_C4_odd, *h_response_C3_odd, *h_response_C2_odd, *h_response_C1_odd;
  TH2D *h_response_pp_even, *h_response_C4_even, *h_response_C3_even, *h_response_C2_even, *h_response_C1_even;
  TH1D *h_unmatched_pp, *h_unmatched_C4, *h_unmatched_C3, *h_unmatched_C2, *h_unmatched_C1;
  TH1D *h_unmatchedGen_pp, *h_unmatchedGen_C4, *h_unmatchedGen_C3, *h_unmatchedGen_C2, *h_unmatchedGen_C1;
  
  file_PYTHIA_response_even->GetObject("h_matchedRecoJetPt_genJetPt_allJets",h_response_pp_even);
  file_PH_response_even->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",h_response_C4_even);
  file_PH_response_even->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",h_response_C3_even);
  file_PH_response_even->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",h_response_C2_even);
  file_PH_response_even->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",h_response_C1_even);

  file_PYTHIA_response_even->GetObject("h_unmatchedRecoJetPt_allJets",h_unmatched_pp);
  file_PH_response_even->GetObject("h_unmatchedRecoJetPt_allJets_C4",h_unmatched_C4);
  file_PH_response_even->GetObject("h_unmatchedRecoJetPt_allJets_C3",h_unmatched_C3);
  file_PH_response_even->GetObject("h_unmatchedRecoJetPt_allJets_C2",h_unmatched_C2);
  file_PH_response_even->GetObject("h_unmatchedRecoJetPt_allJets_C1",h_unmatched_C1);

  file_PYTHIA_response_even->GetObject("h_unmatchedGenJetPt",h_unmatchedGen_pp);
  file_PH_response_even->GetObject("h_unmatchedGenJetPt_C4",h_unmatchedGen_C4);
  file_PH_response_even->GetObject("h_unmatchedGenJetPt_C3",h_unmatchedGen_C3);
  file_PH_response_even->GetObject("h_unmatchedGenJetPt_C2",h_unmatchedGen_C2);
  file_PH_response_even->GetObject("h_unmatchedGenJetPt_C1",h_unmatchedGen_C1);

  file_PYTHIA_response_odd->GetObject("h_matchedRecoJetPt_genJetPt_allJets",h_response_pp_odd);
  file_PH_response_odd->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",h_response_C4_odd);
  file_PH_response_odd->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",h_response_C3_odd);
  file_PH_response_odd->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",h_response_C2_odd);
  file_PH_response_odd->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",h_response_C1_odd);

  TH1D *h_ppMC, *h_C4MC, *h_C3MC, *h_C2MC, *h_C1MC;
  TH1D *h_meas_pp, *h_meas_C4, *h_meas_C3, *h_meas_C2, *h_meas_C1;
  TH1D *h_truth_pp, *h_truth_C4, *h_truth_C3, *h_truth_C2, *h_truth_C1;
  

  h_ppMC = (TH1D*) h_response_pp_odd->ProjectionX("h_ppMC");
  h_C4MC = (TH1D*) h_response_C4_odd->ProjectionX("h_C4MC");
  h_C3MC = (TH1D*) h_response_C3_odd->ProjectionX("h_C3MC");
  h_C2MC = (TH1D*) h_response_C2_odd->ProjectionX("h_C2MC");
  h_C1MC = (TH1D*) h_response_C1_odd->ProjectionX("h_C1MC");
  
  h_meas_pp = (TH1D*) h_response_pp_even->ProjectionX("h_meas_pp");
  h_meas_C4 = (TH1D*) h_response_C4_even->ProjectionX("h_meas_C4");
  h_meas_C3 = (TH1D*) h_response_C3_even->ProjectionX("h_meas_C3");
  h_meas_C2 = (TH1D*) h_response_C2_even->ProjectionX("h_meas_C2");
  h_meas_C1 = (TH1D*) h_response_C1_even->ProjectionX("h_meas_C1");

  TH1D *h_meas_pp_res = (TH1D*) h_meas_pp->Clone("h_meas_pp_res");
  TH1D *h_meas_C4_res = (TH1D*) h_meas_C4->Clone("h_meas_C4_res");
  TH1D *h_meas_C3_res = (TH1D*) h_meas_C3->Clone("h_meas_C3_res");
  TH1D *h_meas_C2_res = (TH1D*) h_meas_C2->Clone("h_meas_C2_res");
  TH1D *h_meas_C1_res = (TH1D*) h_meas_C1->Clone("h_meas_C1_res");
  
  // h_meas_pp_res->Add(h_unmatched_pp);
  // h_meas_C4_res->Add(h_unmatched_C4);
  // h_meas_C3_res->Add(h_unmatched_C3);
  // h_meas_C2_res->Add(h_unmatched_C2);
  // h_meas_C1_res->Add(h_unmatched_C1);

  // h_ppMC->Add(h_unmatched_pp);
  // h_C4MC->Add(h_unmatched_C4);
  // h_C3MC->Add(h_unmatched_C3);
  // h_C2MC->Add(h_unmatched_C2);
  // h_C1MC->Add(h_unmatched_C1);

  
  h_truth_pp = (TH1D*) h_response_pp_even->ProjectionY("h_truth_pp");
  h_truth_C4 = (TH1D*) h_response_C4_even->ProjectionY("h_truth_C4");
  h_truth_C3 = (TH1D*) h_response_C3_even->ProjectionY("h_truth_C3");
  h_truth_C2 = (TH1D*) h_response_C2_even->ProjectionY("h_truth_C2");
  h_truth_C1 = (TH1D*) h_response_C1_even->ProjectionY("h_truth_C1");

  // h_truth_pp->Add(h_unmatchedGen_pp);
  // h_truth_C4->Add(h_unmatchedGen_C4);
  // h_truth_C3->Add(h_unmatchedGen_C3);
  // h_truth_C2->Add(h_unmatchedGen_C2);
  // h_truth_C1->Add(h_unmatchedGen_C1);

  RooUnfoldResponse response_pp(h_meas_pp_res,h_truth_pp,h_response_pp_even,"response_pp","pp response");
  // RooUnfoldResponse response_C4(h_meas_C4_res,h_truth_C4,h_response_C4_even,"response_C4","C4 response");
  // RooUnfoldResponse response_C3(h_meas_C3_res,h_truth_C3,h_response_C3_even,"response_C3","C3 response");
  // RooUnfoldResponse response_C2(h_meas_C2_res,h_truth_C2,h_response_C2_even,"response_C2","C2 response");
  // RooUnfoldResponse response_C1(h_meas_C1_res,h_truth_C1,h_response_C1_even,"response_C1","C1 response");

  
  RooUnfoldResponse *response_C4 = nullptr;
  RooUnfoldResponse *response_C3 = nullptr;
  RooUnfoldResponse *response_C2 = nullptr;
  RooUnfoldResponse *response_C1 = nullptr;

  file_PH_response_even->GetObject("response_C4",response_C4);
  file_PH_response_even->GetObject("response_C3",response_C3);
  file_PH_response_even->GetObject("response_C2",response_C2);
  file_PH_response_even->GetObject("response_C1",response_C1);

  

  
  TCanvas *canv_response_pp = new TCanvas("canv_response_pp","canv_response_pp",700,700);
  canv_response_pp->cd();
  TPad *pad_response_pp = new TPad("pad_response_pp","pad_response_pp",0,0,1,1);
  pad_response_pp->SetLeftMargin(0.15);
  pad_response_pp->SetBottomMargin(0.15);
  pad_response_pp->SetLogz();
  pad_response_pp->Draw();
  pad_response_pp->cd();
  h_response_pp_even->SetTitle("");
  h_response_pp_even->GetYaxis()->SetTitle("Truth Jet #it{p}_{T} [GeV]");
  h_response_pp_even->GetXaxis()->SetTitle("Reco Jet #it{p}_{T} [GeV]");
  h_response_pp_even->SetStats(0);
  h_response_pp_even->Draw("colz");
  canv_response_pp->SaveAs("../../figures/unfoldTest/response_pp.pdf");

  TCanvas *canv_response_C4 = new TCanvas("canv_response_C4","canv_response_C4",700,700);
  canv_response_C4->cd();
  TPad *pad_response_C4 = new TPad("pad_response_C4","pad_response_C4",0,0,1,1);
  pad_response_C4->SetLeftMargin(0.15);
  pad_response_C4->SetBottomMargin(0.15);
  pad_response_C4->SetLogz();
  pad_response_C4->Draw();
  pad_response_C4->cd();
  h_response_C4_even->SetTitle("");
  h_response_C4_even->GetYaxis()->SetTitle("Truth Jet #it{p}_{T} [GeV]");
  h_response_C4_even->GetXaxis()->SetTitle("Reco Jet #it{p}_{T} [GeV]");
  h_response_C4_even->SetStats(0);
  h_response_C4_even->Draw("colz");
  canv_response_C4->SaveAs("../../figures/unfoldTest/response_C4.pdf");

  TCanvas *canv_response_C3 = new TCanvas("canv_response_C3","canv_response_C3",700,700);
  canv_response_C3->cd();
  TPad *pad_response_C3 = new TPad("pad_response_C3","pad_response_C3",0,0,1,1);
  pad_response_C3->SetLeftMargin(0.15);
  pad_response_C3->SetBottomMargin(0.15);
  pad_response_C3->SetLogz();
  pad_response_C3->Draw();
  pad_response_C3->cd();
  h_response_C3_even->SetTitle("");
  h_response_C3_even->GetYaxis()->SetTitle("Truth Jet #it{p}_{T} [GeV]");
  h_response_C3_even->GetXaxis()->SetTitle("Reco Jet #it{p}_{T} [GeV]");
  h_response_C3_even->SetStats(0);
  h_response_C3_even->Draw("colz");
  canv_response_C3->SaveAs("../../figures/unfoldTest/response_C3.pdf");

  TCanvas *canv_response_C2 = new TCanvas("canv_response_C2","canv_response_C2",700,700);
  canv_response_C2->cd();
  TPad *pad_response_C2 = new TPad("pad_response_C2","pad_response_C2",0,0,1,1);
  pad_response_C2->SetLeftMargin(0.15);
  pad_response_C2->SetBottomMargin(0.15);
  pad_response_C2->SetLogz();
  pad_response_C2->Draw();
  pad_response_C2->cd();
  h_response_C2_even->SetTitle("");
  h_response_C2_even->GetYaxis()->SetTitle("Truth Jet #it{p}_{T} [GeV]");
  h_response_C2_even->GetXaxis()->SetTitle("Reco Jet #it{p}_{T} [GeV]");
  h_response_C2_even->SetStats(0);
  h_response_C2_even->Draw("colz");
  canv_response_C2->SaveAs("../../figures/unfoldTest/response_C2.pdf");

  TCanvas *canv_response_C1 = new TCanvas("canv_response_C1","canv_response_C1",700,700);
  canv_response_C1->cd();
  TPad *pad_response_C1 = new TPad("pad_response_C1","pad_response_C1",0,0,1,1);
  pad_response_C1->SetLeftMargin(0.15);
  pad_response_C1->SetBottomMargin(0.15);
  pad_response_C1->SetLogz();
  pad_response_C1->Draw();
  pad_response_C1->cd();
  h_response_C1_even->SetTitle("");
  h_response_C1_even->GetYaxis()->SetTitle("Truth Jet #it{p}_{T} [GeV]");
  h_response_C1_even->GetXaxis()->SetTitle("Reco Jet #it{p}_{T} [GeV]");
  h_response_C1_even->SetStats(0);
  h_response_C1_even->Draw("colz");
  canv_response_C1->SaveAs("../../figures/unfoldTest/response_C1.pdf");


  TH1D *h_meas_pp_copy = (TH1D*) h_meas_pp_res->Clone("h_meas_pp_copy");
  TH1D *r_reco_C4 = (TH1D*) h_meas_C4_res->Clone("r_reco_C4");
  TH1D *r_reco_C3 = (TH1D*) h_meas_C3_res->Clone("r_reco_C3");
  TH1D *r_reco_C2 = (TH1D*) h_meas_C2_res->Clone("r_reco_C2");
  TH1D *r_reco_C1 = (TH1D*) h_meas_C1_res->Clone("r_reco_C1");
  stylizeHistograms(h_meas_pp_copy,r_reco_C4,r_reco_C3,r_reco_C2,r_reco_C1);
  // h_meas_pp_copy->Scale(1./h_meas_pp_copy->Integral());
  // r_reco_C4->Scale(1./r_reco_C4->Integral());
  // r_reco_C3->Scale(1./r_reco_C3->Integral());
  // r_reco_C2->Scale(1./r_reco_C2->Integral());
  // r_reco_C1->Scale(1./r_reco_C1->Integral());
  normalize(h_meas_pp_copy);
  normalize(r_reco_C4);
  normalize(r_reco_C3);
  normalize(r_reco_C2);
  normalize(r_reco_C1);
  r_reco_C4->Divide(r_reco_C4,h_meas_pp_copy,1,1,"");
  r_reco_C3->Divide(r_reco_C3,h_meas_pp_copy,1,1,"");
  r_reco_C2->Divide(r_reco_C2,h_meas_pp_copy,1,1,"");
  r_reco_C1->Divide(r_reco_C1,h_meas_pp_copy,1,1,"");


  
  TH1D *h_truth_pp_copy = (TH1D*) h_truth_pp->Clone("h_truth_pp_copy");
  TH1D *r_gen_C4 = (TH1D*) h_truth_C4->Clone("r_gen_C4");
  TH1D *r_gen_C3 = (TH1D*) h_truth_C3->Clone("r_gen_C3");
  TH1D *r_gen_C2 = (TH1D*) h_truth_C2->Clone("r_gen_C2");
  TH1D *r_gen_C1 = (TH1D*) h_truth_C1->Clone("r_gen_C1");
  stylizeHistograms(h_truth_pp_copy,r_gen_C4,r_gen_C3,r_gen_C2,r_gen_C1);
  // h_truth_pp_copy->Scale(1./h_truth_pp_copy->Integral());
  // r_gen_C4->Scale(1./r_gen_C4->Integral());
  // r_gen_C3->Scale(1./r_gen_C3->Integral());
  // r_gen_C2->Scale(1./r_gen_C2->Integral());
  // r_gen_C1->Scale(1./r_gen_C1->Integral());
  normalize(h_truth_pp_copy);
  normalize(r_gen_C4);
  normalize(r_gen_C3);
  normalize(r_gen_C2);
  normalize(r_gen_C1);
  r_gen_C4->Divide(r_gen_C4,h_truth_pp_copy,1,1,"");
  r_gen_C3->Divide(r_gen_C3,h_truth_pp_copy,1,1,"");
  r_gen_C2->Divide(r_gen_C2,h_truth_pp_copy,1,1,"");
  r_gen_C1->Divide(r_gen_C1,h_truth_pp_copy,1,1,"");

  TLegend *leg_r = new TLegend(0.7,0.88,0.7,0.88);
  leg_r->SetBorderSize(0);
  leg_r->SetTextSize(0.045);
  leg_r->AddEntry(r_reco_C4,"P+H 50-80%");
  leg_r->AddEntry(r_reco_C3,"P+H 30-50%");
  leg_r->AddEntry(r_reco_C2,"P+H 10-30%");
  leg_r->AddEntry(r_reco_C1,"P+H 0-10%");

  li->SetLineStyle(7);
  
  TCanvas *canv_r_reco = new TCanvas("canv_r_reco","canv_r_reco",700,700);
  canv_r_reco->cd();
  TPad *pad_r_reco = new TPad("pad_r_reco","pad_r_reco",0,0,1,1);
  pad_r_reco->SetLeftMargin(0.15);
  pad_r_reco->SetBottomMargin(0.15);
  pad_r_reco->Draw();
  pad_r_reco->cd();
  r_reco_C4->SetStats(0);
  r_reco_C4->SetTitle("");
  r_reco_C4->GetYaxis()->SetTitle("P+H / P");
  r_reco_C4->GetXaxis()->SetTitle("Reco Jet #it{p}_{T} [GeV]");
  r_reco_C4->GetYaxis()->SetRangeUser(0,6.5);
  r_reco_C4->Draw();
  r_reco_C3->Draw("same");
  r_reco_C2->Draw("same");
  r_reco_C1->Draw("same");
  li->DrawLine(30,1,500,1);
  leg_r->Draw();
  canv_r_reco->SaveAs("../../figures/unfoldTest/r_reco.pdf");

  TCanvas *canv_r_gen = new TCanvas("canv_r_gen","canv_r_gen",700,700);
  canv_r_gen->cd();
  TPad *pad_r_gen = new TPad("pad_r_gen","pad_r_gen",0,0,1,1);
  pad_r_gen->SetLeftMargin(0.15);
  pad_r_gen->SetBottomMargin(0.15);
  pad_r_gen->Draw();
  pad_r_gen->cd();
  r_gen_C4->SetStats(0);
  r_gen_C4->SetTitle("");
  r_gen_C4->GetYaxis()->SetTitle("P+H / P");
  r_gen_C4->GetXaxis()->SetTitle("Reco Jet #it{p}_{T} [GeV]");
  r_gen_C4->GetYaxis()->SetRangeUser(0.75,1.25);
  r_gen_C4->Draw();
  r_gen_C3->Draw("same");
  r_gen_C2->Draw("same");
  r_gen_C1->Draw("same");
  li->DrawLine(30,1,500,1);
  leg_r->Draw();
  canv_r_gen->SaveAs("../../figures/unfoldTest/r_gen.pdf");


  TH1D *h_pp_copy = (TH1D*) h_pp->Clone("h_pp_copy");
  TH1D *h_C4_copy = (TH1D*) h_C4->Clone("h_C4_copy");
  TH1D *h_C3_copy = (TH1D*) h_C3->Clone("h_C3_copy");
  TH1D *h_C2_copy = (TH1D*) h_C2->Clone("h_C2_copy");
  TH1D *h_C1_copy = (TH1D*) h_C1->Clone("h_C1_copy");
  
  TH1D *r_data_C4 = (TH1D*) h_C4->Clone("r_C4");
  TH1D *r_data_C3 = (TH1D*) h_C3->Clone("r_C3");
  TH1D *r_data_C2 = (TH1D*) h_C2->Clone("r_C2");
  TH1D *r_data_C1 = (TH1D*) h_C1->Clone("r_C1");

  // h_pp_copy->Scale(1./h_pp_copy->Integral());
  // r_data_C4->Scale(1./r_data_C4->Integral());
  // r_data_C3->Scale(1./r_data_C3->Integral());
  // r_data_C2->Scale(1./r_data_C2->Integral());
  // r_data_C1->Scale(1./r_data_C1->Integral());
  normalize(h_pp_copy);
  normalize(r_data_C4);
  normalize(r_data_C3);
  normalize(r_data_C2);
  normalize(r_data_C1);

  r_data_C4->Divide(r_data_C4,h_pp_copy,1,1,"");
  r_data_C3->Divide(r_data_C3,h_pp_copy,1,1,"");
  r_data_C2->Divide(r_data_C2,h_pp_copy,1,1,"");
  r_data_C1->Divide(r_data_C1,h_pp_copy,1,1,"");

  stylizeHistograms(h_pp_copy,r_data_C4,r_data_C3,r_data_C2,r_data_C1);

  TCanvas *canv_r_data = new TCanvas("canv_r_data","canv_r_data",700,700);
  canv_r_data->cd();
  TPad *pad_r_data = new TPad("pad_r_data","pad_r_data",0,0,1,1);
  pad_r_data->SetLeftMargin(0.15);
  pad_r_data->SetBottomMargin(0.15);
  pad_r_data->Draw();
  pad_r_data->cd();
  r_data_C4->SetStats(0);
  r_data_C4->SetTitle("");
  r_data_C4->GetYaxis()->SetTitle("PbPb / pp");
  r_data_C4->GetYaxis()->SetRangeUser(0,6.5);
  r_data_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_data_C4->Draw();
  r_data_C3->Draw("same");
  r_data_C2->Draw("same");
  r_data_C1->Draw("same");
  li->DrawLine(30,1,500,1);
  leg_r->Draw();
  canv_r_data->SaveAs("../../figures/unfoldTest/r_data.pdf");
















  //////////////////////////////////////////

  int N_iter_pp = 1;
  int N_iter_C4 = 1;
  int N_iter_C3 = 1;
  int N_iter_C2 = 1;
  int N_iter_C1 = 1;

  RooUnfoldBayes unfold_pp(&response_pp, h_pp, N_iter_pp);
  RooUnfoldBayes unfold_C4(&response_C4, h_C4, N_iter_C4);
  RooUnfoldBayes unfold_C3(&response_C3, h_C3, N_iter_C3);
  RooUnfoldBayes unfold_C2(&response_C2, h_C2, N_iter_C2);
  RooUnfoldBayes unfold_C1(&response_C1, h_C1, N_iter_C1);

  RooUnfoldBayes unfold_ppMC(&response_pp, h_ppMC, N_iter_pp);
  RooUnfoldBayes unfold_C4MC(&response_C4, h_C4MC, N_iter_C4);
  RooUnfoldBayes unfold_C3MC(&response_C3, h_C3MC, N_iter_C3);
  RooUnfoldBayes unfold_C2MC(&response_C2, h_C2MC, N_iter_C2);
  RooUnfoldBayes unfold_C1MC(&response_C1, h_C1MC, N_iter_C1);

  RooUnfoldBayes unfold_meas_pp(&response_pp, h_meas_pp, N_iter_pp);
  RooUnfoldBayes unfold_meas_C4(&response_C4, h_meas_C4, N_iter_C4);
  RooUnfoldBayes unfold_meas_C3(&response_C3, h_meas_C3, N_iter_C3);
  RooUnfoldBayes unfold_meas_C2(&response_C2, h_meas_C2, N_iter_C2);
  RooUnfoldBayes unfold_meas_C1(&response_C1, h_meas_C1, N_iter_C1);

  TH1D *h_pp_unfold, *h_C4_unfold, *h_C3_unfold, *h_C2_unfold, *h_C1_unfold;
  TH1D *h_ppMC_unfold, *h_C4MC_unfold, *h_C3MC_unfold, *h_C2MC_unfold, *h_C1MC_unfold;
  TH1D *h_meas_pp_unfold, *h_meas_C4_unfold, *h_meas_C3_unfold, *h_meas_C2_unfold, *h_meas_C1_unfold;
  const int N_iter_tot = 10;
  TH1D *h_pp_unfold_iterTest[N_iter_tot], *h_C4_unfold_iterTest[N_iter_tot], *h_C3_unfold_iterTest[N_iter_tot], *h_C2_unfold_iterTest[N_iter_tot], *h_C1_unfold_iterTest[N_iter_tot];
  TH1D *h_ppMC_unfold_iterTest[N_iter_tot], *h_C4MC_unfold_iterTest[N_iter_tot], *h_C3MC_unfold_iterTest[N_iter_tot], *h_C2MC_unfold_iterTest[N_iter_tot], *h_C1MC_unfold_iterTest[N_iter_tot];

  h_pp_unfold = (TH1D*) unfold_pp.Hunfold();
  h_C4_unfold = (TH1D*) unfold_C4.Hunfold();
  h_C3_unfold = (TH1D*) unfold_C3.Hunfold();
  h_C2_unfold = (TH1D*) unfold_C2.Hunfold();
  h_C1_unfold = (TH1D*) unfold_C1.Hunfold();

  h_ppMC_unfold = (TH1D*) unfold_ppMC.Hunfold();
  h_C4MC_unfold = (TH1D*) unfold_C4MC.Hunfold();
  h_C3MC_unfold = (TH1D*) unfold_C3MC.Hunfold();
  h_C2MC_unfold = (TH1D*) unfold_C2MC.Hunfold();
  h_C1MC_unfold = (TH1D*) unfold_C1MC.Hunfold();

  h_meas_pp_unfold = (TH1D*) unfold_meas_pp.Hunfold();
  h_meas_C4_unfold = (TH1D*) unfold_meas_C4.Hunfold();
  h_meas_C3_unfold = (TH1D*) unfold_meas_C3.Hunfold();
  h_meas_C2_unfold = (TH1D*) unfold_meas_C2.Hunfold();
  h_meas_C1_unfold = (TH1D*) unfold_meas_C1.Hunfold();

  
  int colorArray[10] = {1,2,4,8,9,12,20,26,31,38};
  //int colorArray[N_iter_tot] = {1,2};

  for(int i = 0; i < N_iter_tot; i++){

    //h_pp_unfold_iterTest[i] = (TH1D*) h_pp->Clone(Form("h_pp_unfold_iterTest_%i",i));
    std::cout << "setting iterations...\n";

    unfold_pp.SetIterations(i+1);
    unfold_ppMC.SetIterations(i+1);
    h_pp_unfold_iterTest[i] = (TH1D*) unfold_pp.Hunfold();
    h_ppMC_unfold_iterTest[i] = (TH1D*) unfold_ppMC.Hunfold();

    unfold_C4.SetIterations(i+1);
    unfold_C4MC.SetIterations(i+1);
    h_C4_unfold_iterTest[i] = (TH1D*) unfold_C4.Hunfold();
    h_C4MC_unfold_iterTest[i] = (TH1D*) unfold_C4MC.Hunfold();

    unfold_C3.SetIterations(i+1);
    unfold_C3MC.SetIterations(i+1);
    h_C3_unfold_iterTest[i] = (TH1D*) unfold_C3.Hunfold();
    h_C3MC_unfold_iterTest[i] = (TH1D*) unfold_C3MC.Hunfold();

    unfold_C2.SetIterations(i+1);
    unfold_C2MC.SetIterations(i+1);
    h_C2_unfold_iterTest[i] = (TH1D*) unfold_C2.Hunfold();
    h_C2MC_unfold_iterTest[i] = (TH1D*) unfold_C2MC.Hunfold();

    unfold_C1.SetIterations(i+1);
    unfold_C1MC.SetIterations(i+1);
    h_C1_unfold_iterTest[i] = (TH1D*) unfold_C1.Hunfold();
    h_C1MC_unfold_iterTest[i] = (TH1D*) unfold_C1MC.Hunfold();


    std::cout << "iterations = " << unfold_pp.GetIterations() << "\n";

    // quick stylize
    h_pp_unfold_iterTest[i]->SetLineColor(colorArray[i]);
    h_ppMC_unfold_iterTest[i]->SetLineColor(colorArray[i]);

    h_C4_unfold_iterTest[i]->SetLineColor(colorArray[i]);
    h_C4MC_unfold_iterTest[i]->SetLineColor(colorArray[i]);

    h_C3_unfold_iterTest[i]->SetLineColor(colorArray[i]);
    h_C3MC_unfold_iterTest[i]->SetLineColor(colorArray[i]);

    h_C2_unfold_iterTest[i]->SetLineColor(colorArray[i]);
    h_C2MC_unfold_iterTest[i]->SetLineColor(colorArray[i]);

    h_C1_unfold_iterTest[i]->SetLineColor(colorArray[i]);
    h_C1MC_unfold_iterTest[i]->SetLineColor(colorArray[i]);

    h_pp_unfold_iterTest[i]->SetLineWidth(2);
    h_ppMC_unfold_iterTest[i]->SetLineWidth(2);

    h_C4_unfold_iterTest[i]->SetLineWidth(2);
    h_C4MC_unfold_iterTest[i]->SetLineWidth(2);

    h_C3_unfold_iterTest[i]->SetLineWidth(2);
    h_C3MC_unfold_iterTest[i]->SetLineWidth(2);

    h_C2_unfold_iterTest[i]->SetLineWidth(2);
    h_C2MC_unfold_iterTest[i]->SetLineWidth(2);

    h_C1_unfold_iterTest[i]->SetLineWidth(2);
    h_C1MC_unfold_iterTest[i]->SetLineWidth(2);
    
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////

  li->SetLineStyle(7);

  TH1D *h_ppMC_draw = (TH1D*) h_ppMC->Clone("h_ppMC_draw");
  h_ppMC_draw->SetLineStyle(2);
  TH1D *h_C4MC_draw = (TH1D*) h_C4MC->Clone("h_C4MC_draw");
  h_C4MC_draw->SetLineStyle(2);
  TH1D *h_C3MC_draw = (TH1D*) h_C3MC->Clone("h_C3MC_draw");
  h_C3MC_draw->SetLineStyle(2);
  TH1D *h_C2MC_draw = (TH1D*) h_C2MC->Clone("h_C2MC_draw");
  h_C2MC_draw->SetLineStyle(2);
  TH1D *h_C1MC_draw = (TH1D*) h_C1MC->Clone("h_C1MC_draw");
  h_C1MC_draw->SetLineStyle(2);
  
  TLegend *leg_pp_iterTest = new TLegend(0.55,0.35,0.81,0.81);
  leg_pp_iterTest->SetBorderSize(0);
  leg_pp_iterTest->SetTextSize(0.06);
  leg_pp_iterTest->AddEntry(h_ppMC_draw,"0 iterations");
  for(int i = 0; i < N_iter_tot; i++){
    if(i == 0) leg_pp_iterTest->AddEntry(h_pp_unfold_iterTest[i],Form("%i iteration",i+1),"l");
    else leg_pp_iterTest->AddEntry(h_pp_unfold_iterTest[i],Form("%i iterations",i+1),"l");
  }


  
  TCanvas *canv_pp_iterTest = new TCanvas("canv_pp_iterTest","canv_pp_iterTest",700,700);
  canv_pp_iterTest->cd();
  TPad *pad_pp_iterTest_upper = new TPad("pad_pp_iterTest_upper","pad_pp_iterTest_upper",0,0.4,1,1);
  TPad *pad_pp_iterTest_lower = new TPad("pad_pp_iterTest_lower","pad_pp_iterTest_lower",0,0,1,0.4);
  pad_pp_iterTest_upper->SetLeftMargin(0.15);
  pad_pp_iterTest_lower->SetLeftMargin(0.15);
  pad_pp_iterTest_upper->SetBottomMargin(0.);
  pad_pp_iterTest_lower->SetBottomMargin(0.15);
  pad_pp_iterTest_upper->SetTopMargin(0.15);
  pad_pp_iterTest_lower->SetTopMargin(0.);
  pad_pp_iterTest_upper->SetLogy();
  pad_pp_iterTest_upper->Draw();
  pad_pp_iterTest_lower->Draw();
  pad_pp_iterTest_upper->cd();
  //stylizeHistograms(h_truth_pp,h_pp_iterTest,h_pp_iterTest_unfold);
  for(int i = 0; i < N_iter_tot; i++){
    if(i==0){
      h_pp_unfold_iterTest[i]->SetStats(0);
      h_pp_unfold_iterTest[i]->SetTitle("pp");
      h_pp_unfold_iterTest[i]->Draw();
    }
    else h_pp_unfold_iterTest[i]->Draw("same");
  }
  h_truth_pp->Draw("same");
  leg_pp_iterTest->Draw();
  pad_pp_iterTest_lower->cd();
  TH1D *r_pp_iterTest_unfold[N_iter_tot];
  for(int i = 0; i < N_iter_tot; i++){
    r_pp_iterTest_unfold[i] = (TH1D*) h_pp_unfold_iterTest[i]->Clone(Form("r_pp_iterTest_unfold_%i",i));
    r_pp_iterTest_unfold[i]->Divide(h_pp_unfold_iterTest[i],h_truth_pp,1,1,"B");
    if(i == 0){
      r_pp_iterTest_unfold[i]->Draw();
      //r_pp_iterTest_unfold[0]->GetYaxis()->SetRangeUser(0.,2.);
      
    }
    else r_pp_iterTest_unfold[i]->Draw("same");
  }
  canv_pp_iterTest->SaveAs("../../figures/unfoldTest/pp_iterTest.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_ppMC_iterTest = new TCanvas("canv_ppMC_iterTest","canv_ppMC_iterTest",700,700);
  canv_ppMC_iterTest->cd();
  TPad *pad_ppMC_iterTest_upper = new TPad("pad_ppMC_iterTest_upper","pad_ppMC_iterTest_upper",0,0.4,1,1);
  TPad *pad_ppMC_iterTest_lower = new TPad("pad_ppMC_iterTest_lower","pad_ppMC_iterTest_lower",0,0,1,0.4);
  pad_ppMC_iterTest_upper->SetLeftMargin(0.15);
  pad_ppMC_iterTest_lower->SetLeftMargin(0.15);
  pad_ppMC_iterTest_upper->SetBottomMargin(0.);
  pad_ppMC_iterTest_lower->SetBottomMargin(0.15);
  pad_ppMC_iterTest_upper->SetTopMargin(0.15);
  pad_ppMC_iterTest_lower->SetTopMargin(0.);
  pad_ppMC_iterTest_upper->SetLogy();
  pad_ppMC_iterTest_upper->Draw();
  pad_ppMC_iterTest_lower->Draw();
  pad_ppMC_iterTest_upper->cd();
  //stylizeHistograms(h_truth_pp,h_ppMC_iterTest,h_ppMC_iterTest_unfold);
  for(int i = 0; i < N_iter_tot; i++){
    if(i==0){
      h_ppMC_unfold_iterTest[i]->SetStats(0);
      h_ppMC_unfold_iterTest[i]->SetTitle("PYTHIA");
      h_ppMC_unfold_iterTest[i]->Draw();
    }
    else h_ppMC_unfold_iterTest[i]->Draw("same");
  }
  h_truth_pp->Draw("same");
  h_ppMC_draw->Draw("same");
  leg_pp_iterTest->Draw();
  pad_ppMC_iterTest_lower->cd();
  TH1D *r_ppMC_iterTest_unfold[N_iter_tot];
  for(int i = 0; i < N_iter_tot; i++){
    r_ppMC_iterTest_unfold[i] = (TH1D*) h_ppMC_unfold_iterTest[i]->Clone(Form("r_ppMC_iterTest_unfold_%i",i));
    r_ppMC_iterTest_unfold[i]->Divide(h_ppMC_unfold_iterTest[i],h_truth_pp,1,1,"B");
    if(i == 0){
      r_ppMC_iterTest_unfold[i]->Draw();
      r_ppMC_iterTest_unfold[0]->GetYaxis()->SetRangeUser(0.,2.);
    }
    else r_ppMC_iterTest_unfold[i]->Draw("same");
  }
  TH1D *r_ppMC_draw = (TH1D*) h_ppMC_draw->Clone("r_ppMC_draw");
  r_ppMC_draw->Divide(h_ppMC_draw,h_truth_pp,1,1,"B");
  r_ppMC_draw->Draw("same");
  li->DrawLine(30,1,500,1);
  canv_ppMC_iterTest->SaveAs("../../figures/unfoldTest/ppMC_iterTest.pdf");

  //////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C4_iterTest = new TCanvas("canv_C4_iterTest","canv_C4_iterTest",700,700);
  canv_C4_iterTest->cd();
  TPad *pad_C4_iterTest_upper = new TPad("pad_C4_iterTest_upper","pad_C4_iterTest_upper",0,0.4,1,1);
  TPad *pad_C4_iterTest_lower = new TPad("pad_C4_iterTest_lower","pad_C4_iterTest_lower",0,0,1,0.4);
  pad_C4_iterTest_upper->SetLeftMargin(0.15);
  pad_C4_iterTest_lower->SetLeftMargin(0.15);
  pad_C4_iterTest_upper->SetBottomMargin(0.);
  pad_C4_iterTest_lower->SetBottomMargin(0.15);
  pad_C4_iterTest_upper->SetTopMargin(0.15);
  pad_C4_iterTest_lower->SetTopMargin(0.);
  pad_C4_iterTest_upper->SetLogy();
  pad_C4_iterTest_upper->Draw();
  pad_C4_iterTest_lower->Draw();
  pad_C4_iterTest_upper->cd();
  //stylizeHistograms(h_truth_C4,h_C4_iterTest,h_C4_iterTest_unfold);
  for(int i = 0; i < N_iter_tot; i++){
    if(i==0){
      h_C4_unfold_iterTest[i]->SetStats(0);
      h_C4_unfold_iterTest[i]->SetTitle("PbPb 50-80%");
      h_C4_unfold_iterTest[i]->Draw();
    }
    else h_C4_unfold_iterTest[i]->Draw("same");
  }
  h_truth_C4->Draw("same");
  leg_pp_iterTest->Draw();
  pad_C4_iterTest_lower->cd();
  TH1D *r_C4_iterTest_unfold[N_iter_tot];
  for(int i = 0; i < N_iter_tot; i++){
    r_C4_iterTest_unfold[i] = (TH1D*) h_C4_unfold_iterTest[i]->Clone(Form("r_C4_iterTest_unfold_%i",i));
    r_C4_iterTest_unfold[i]->Divide(h_C4_unfold_iterTest[i],h_truth_C4,1,1,"B");
    if(i == 0){
      r_C4_iterTest_unfold[i]->Draw();
      //r_C4_iterTest_unfold[0]->GetYaxis()->SetRangeUser(0.,2.);
      
    }
    else r_C4_iterTest_unfold[i]->Draw("same");
  }
  canv_C4_iterTest->SaveAs("../../figures/unfoldTest/C4_iterTest.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C4MC_iterTest = new TCanvas("canv_C4MC_iterTest","canv_C4MC_iterTest",700,700);
  canv_C4MC_iterTest->cd();
  TPad *pad_C4MC_iterTest_upper = new TPad("pad_C4MC_iterTest_upper","pad_C4MC_iterTest_upper",0,0.4,1,1);
  TPad *pad_C4MC_iterTest_lower = new TPad("pad_C4MC_iterTest_lower","pad_C4MC_iterTest_lower",0,0,1,0.4);
  pad_C4MC_iterTest_upper->SetLeftMargin(0.15);
  pad_C4MC_iterTest_lower->SetLeftMargin(0.15);
  pad_C4MC_iterTest_upper->SetBottomMargin(0.);
  pad_C4MC_iterTest_lower->SetBottomMargin(0.15);
  pad_C4MC_iterTest_upper->SetTopMargin(0.15);
  pad_C4MC_iterTest_lower->SetTopMargin(0.);
  pad_C4MC_iterTest_upper->SetLogy();
  pad_C4MC_iterTest_upper->Draw();
  pad_C4MC_iterTest_lower->Draw();
  pad_C4MC_iterTest_upper->cd();
  //stylizeHistograms(h_truth_C4,h_C4MC_iterTest,h_C4MC_iterTest_unfold);
  for(int i = 0; i < N_iter_tot; i++){
    if(i==0){
      h_C4MC_unfold_iterTest[i]->SetStats(0);
      h_C4MC_unfold_iterTest[i]->SetTitle("PYTHIA+HYDJET 50-80%");
      h_C4MC_unfold_iterTest[i]->Draw();
    }
    else h_C4MC_unfold_iterTest[i]->Draw("same");
  }
  h_truth_C4->Draw("same");
  h_C4MC_draw->Draw("same");
  leg_pp_iterTest->Draw();
  pad_C4MC_iterTest_lower->cd();
  TH1D *r_C4MC_iterTest_unfold[N_iter_tot];
  for(int i = 0; i < N_iter_tot; i++){
    r_C4MC_iterTest_unfold[i] = (TH1D*) h_C4MC_unfold_iterTest[i]->Clone(Form("r_C4MC_iterTest_unfold_%i",i));
    r_C4MC_iterTest_unfold[i]->Divide(h_C4MC_unfold_iterTest[i],h_truth_C4,1,1,"B");
    if(i == 0){
      r_C4MC_iterTest_unfold[i]->Draw();
      r_C4MC_iterTest_unfold[0]->GetYaxis()->SetRangeUser(0.,2.);
    }
    else r_C4MC_iterTest_unfold[i]->Draw("same");
  }
  TH1D *r_C4MC_draw = (TH1D*) h_C4MC_draw->Clone("r_C4MC_draw");
  r_C4MC_draw->Divide(h_C4MC_draw,h_truth_C4,1,1,"B");
  r_C4MC_draw->Draw("same");
  li->DrawLine(30,1,500,1);
  canv_C4MC_iterTest->SaveAs("../../figures/unfoldTest/C4MC_iterTest.pdf");

    //////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C3_iterTest = new TCanvas("canv_C3_iterTest","canv_C3_iterTest",700,700);
  canv_C3_iterTest->cd();
  TPad *pad_C3_iterTest_upper = new TPad("pad_C3_iterTest_upper","pad_C3_iterTest_upper",0,0.4,1,1);
  TPad *pad_C3_iterTest_lower = new TPad("pad_C3_iterTest_lower","pad_C3_iterTest_lower",0,0,1,0.4);
  pad_C3_iterTest_upper->SetLeftMargin(0.15);
  pad_C3_iterTest_lower->SetLeftMargin(0.15);
  pad_C3_iterTest_upper->SetBottomMargin(0.);
  pad_C3_iterTest_lower->SetBottomMargin(0.15);
  pad_C3_iterTest_upper->SetTopMargin(0.15);
  pad_C3_iterTest_lower->SetTopMargin(0.);
  pad_C3_iterTest_upper->SetLogy();
  pad_C3_iterTest_upper->Draw();
  pad_C3_iterTest_lower->Draw();
  pad_C3_iterTest_upper->cd();
  //stylizeHistograms(h_truth_C3,h_C3_iterTest,h_C3_iterTest_unfold);
  for(int i = 0; i < N_iter_tot; i++){
    if(i==0){
      h_C3_unfold_iterTest[i]->SetStats(0);
      h_C3_unfold_iterTest[i]->SetTitle("PbPb 30-50%");
      h_C3_unfold_iterTest[i]->Draw();
    }
    else h_C3_unfold_iterTest[i]->Draw("same");
  }
  h_truth_C3->Draw("same");
  leg_pp_iterTest->Draw();
  pad_C3_iterTest_lower->cd();
  TH1D *r_C3_iterTest_unfold[N_iter_tot];
  for(int i = 0; i < N_iter_tot; i++){
    r_C3_iterTest_unfold[i] = (TH1D*) h_C3_unfold_iterTest[i]->Clone(Form("r_C3_iterTest_unfold_%i",i));
    r_C3_iterTest_unfold[i]->Divide(h_C3_unfold_iterTest[i],h_truth_C3,1,1,"B");
    if(i == 0){
      r_C3_iterTest_unfold[i]->Draw();
      //r_C3_iterTest_unfold[0]->GetYaxis()->SetRangeUser(0.,2.);
      
    }
    else r_C3_iterTest_unfold[i]->Draw("same");
  }
  li->DrawLine(30,1,500,1);
  canv_C3_iterTest->SaveAs("../../figures/unfoldTest/C3_iterTest.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C3MC_iterTest = new TCanvas("canv_C3MC_iterTest","canv_C3MC_iterTest",700,700);
  canv_C3MC_iterTest->cd();
  TPad *pad_C3MC_iterTest_upper = new TPad("pad_C3MC_iterTest_upper","pad_C3MC_iterTest_upper",0,0.4,1,1);
  TPad *pad_C3MC_iterTest_lower = new TPad("pad_C3MC_iterTest_lower","pad_C3MC_iterTest_lower",0,0,1,0.4);
  pad_C3MC_iterTest_upper->SetLeftMargin(0.15);
  pad_C3MC_iterTest_lower->SetLeftMargin(0.15);
  pad_C3MC_iterTest_upper->SetBottomMargin(0.);
  pad_C3MC_iterTest_lower->SetBottomMargin(0.15);
  pad_C3MC_iterTest_upper->SetTopMargin(0.15);
  pad_C3MC_iterTest_lower->SetTopMargin(0.);
  pad_C3MC_iterTest_upper->SetLogy();
  pad_C3MC_iterTest_upper->Draw();
  pad_C3MC_iterTest_lower->Draw();
  pad_C3MC_iterTest_upper->cd();
  //stylizeHistograms(h_truth_C3,h_C3MC_iterTest,h_C3MC_iterTest_unfold);
  for(int i = 0; i < N_iter_tot; i++){
    if(i==0){
      h_C3MC_unfold_iterTest[i]->SetStats(0);
      h_C3MC_unfold_iterTest[i]->SetTitle("PYTHIA+HYDJET 30-50%");
      h_C3MC_unfold_iterTest[i]->Draw();
    }
    else h_C3MC_unfold_iterTest[i]->Draw("same");
  }
  h_truth_C3->Draw("same");
  h_C3MC_draw->Draw("same");
  leg_pp_iterTest->Draw();
  pad_C3MC_iterTest_lower->cd();
  TH1D *r_C3MC_iterTest_unfold[N_iter_tot];
  for(int i = 0; i < N_iter_tot; i++){
    r_C3MC_iterTest_unfold[i] = (TH1D*) h_C3MC_unfold_iterTest[i]->Clone(Form("r_C3MC_iterTest_unfold_%i",i));
    r_C3MC_iterTest_unfold[i]->Divide(h_C3MC_unfold_iterTest[i],h_truth_C3,1,1,"B");
    if(i == 0){
      r_C3MC_iterTest_unfold[i]->Draw();
      r_C3MC_iterTest_unfold[0]->GetYaxis()->SetRangeUser(0.,2.);
    }
    else r_C3MC_iterTest_unfold[i]->Draw("same");
  }
  TH1D *r_C3MC_draw = (TH1D*) h_C3MC_draw->Clone("r_C3MC_draw");
  r_C3MC_draw->Divide(h_C3MC_draw,h_truth_C3,1,1,"B");
  r_C3MC_draw->Draw("same");
  li->DrawLine(30,1,500,1);
  canv_C3MC_iterTest->SaveAs("../../figures/unfoldTest/C3MC_iterTest.pdf");

    //////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C2_iterTest = new TCanvas("canv_C2_iterTest","canv_C2_iterTest",700,700);
  canv_C2_iterTest->cd();
  TPad *pad_C2_iterTest_upper = new TPad("pad_C2_iterTest_upper","pad_C2_iterTest_upper",0,0.4,1,1);
  TPad *pad_C2_iterTest_lower = new TPad("pad_C2_iterTest_lower","pad_C2_iterTest_lower",0,0,1,0.4);
  pad_C2_iterTest_upper->SetLeftMargin(0.15);
  pad_C2_iterTest_lower->SetLeftMargin(0.15);
  pad_C2_iterTest_upper->SetBottomMargin(0.);
  pad_C2_iterTest_lower->SetBottomMargin(0.15);
  pad_C2_iterTest_upper->SetTopMargin(0.15);
  pad_C2_iterTest_lower->SetTopMargin(0.);
  pad_C2_iterTest_upper->SetLogy();
  pad_C2_iterTest_upper->Draw();
  pad_C2_iterTest_lower->Draw();
  pad_C2_iterTest_upper->cd();
  //stylizeHistograms(h_truth_C2,h_C2_iterTest,h_C2_iterTest_unfold);
  for(int i = 0; i < N_iter_tot; i++){
    if(i==0){
      h_C2_unfold_iterTest[i]->SetStats(0);
      h_C2_unfold_iterTest[i]->SetTitle("PbPb 10-30%");
      h_C2_unfold_iterTest[i]->Draw();
    }
    else h_C2_unfold_iterTest[i]->Draw("same");
  }
  h_truth_C2->Draw("same");
  leg_pp_iterTest->Draw();
  pad_C2_iterTest_lower->cd();
  TH1D *r_C2_iterTest_unfold[N_iter_tot];
  for(int i = 0; i < N_iter_tot; i++){
    r_C2_iterTest_unfold[i] = (TH1D*) h_C2_unfold_iterTest[i]->Clone(Form("r_C2_iterTest_unfold_%i",i));
    r_C2_iterTest_unfold[i]->Divide(h_C2_unfold_iterTest[i],h_truth_C2,1,1,"B");
    if(i == 0){
      r_C2_iterTest_unfold[i]->Draw();
      //r_C2_iterTest_unfold[0]->GetYaxis()->SetRangeUser(0.,2.);
      
    }
    else r_C2_iterTest_unfold[i]->Draw("same");
  }
  canv_C2_iterTest->SaveAs("../../figures/unfoldTest/C2_iterTest.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C2MC_iterTest = new TCanvas("canv_C2MC_iterTest","canv_C2MC_iterTest",700,700);
  canv_C2MC_iterTest->cd();
  TPad *pad_C2MC_iterTest_upper = new TPad("pad_C2MC_iterTest_upper","pad_C2MC_iterTest_upper",0,0.4,1,1);
  TPad *pad_C2MC_iterTest_lower = new TPad("pad_C2MC_iterTest_lower","pad_C2MC_iterTest_lower",0,0,1,0.4);
  pad_C2MC_iterTest_upper->SetLeftMargin(0.15);
  pad_C2MC_iterTest_lower->SetLeftMargin(0.15);
  pad_C2MC_iterTest_upper->SetBottomMargin(0.);
  pad_C2MC_iterTest_lower->SetBottomMargin(0.15);
  pad_C2MC_iterTest_upper->SetTopMargin(0.15);
  pad_C2MC_iterTest_lower->SetTopMargin(0.);
  pad_C2MC_iterTest_upper->SetLogy();
  pad_C2MC_iterTest_upper->Draw();
  pad_C2MC_iterTest_lower->Draw();
  pad_C2MC_iterTest_upper->cd();
  //stylizeHistograms(h_truth_C2,h_C2MC_iterTest,h_C2MC_iterTest_unfold);
  for(int i = 0; i < N_iter_tot; i++){
    if(i==0){
      h_C2MC_unfold_iterTest[i]->SetStats(0);
      h_C2MC_unfold_iterTest[i]->SetTitle("PYTHIA+HYDJET 10-30%");
      h_C2MC_unfold_iterTest[i]->Draw();
    }
    else h_C2MC_unfold_iterTest[i]->Draw("same");
  }
  h_truth_C2->Draw("same");
  h_C2MC_draw->Draw("same");
  leg_pp_iterTest->Draw();
  pad_C2MC_iterTest_lower->cd();
  TH1D *r_C2MC_iterTest_unfold[N_iter_tot];
  for(int i = 0; i < N_iter_tot; i++){
    r_C2MC_iterTest_unfold[i] = (TH1D*) h_C2MC_unfold_iterTest[i]->Clone(Form("r_C2MC_iterTest_unfold_%i",i));
    r_C2MC_iterTest_unfold[i]->Divide(h_C2MC_unfold_iterTest[i],h_truth_C2,1,1,"B");
    if(i == 0){
      r_C2MC_iterTest_unfold[i]->Draw();
      r_C2MC_iterTest_unfold[0]->GetYaxis()->SetRangeUser(0.,2.);
    }
    else r_C2MC_iterTest_unfold[i]->Draw("same");
  }
  TH1D *r_C2MC_draw = (TH1D*) h_C2MC_draw->Clone("r_C2MC_draw");
  r_C2MC_draw->Divide(h_C2MC_draw,h_truth_C2,1,1,"B");
  r_C2MC_draw->Draw("same");
  li->DrawLine(30,1,500,1);
  canv_C2MC_iterTest->SaveAs("../../figures/unfoldTest/C2MC_iterTest.pdf");

    //////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C1_iterTest = new TCanvas("canv_C1_iterTest","canv_C1_iterTest",700,700);
  canv_C1_iterTest->cd();
  TPad *pad_C1_iterTest_upper = new TPad("pad_C1_iterTest_upper","pad_C1_iterTest_upper",0,0.4,1,1);
  TPad *pad_C1_iterTest_lower = new TPad("pad_C1_iterTest_lower","pad_C1_iterTest_lower",0,0,1,0.4);
  pad_C1_iterTest_upper->SetLeftMargin(0.15);
  pad_C1_iterTest_lower->SetLeftMargin(0.15);
  pad_C1_iterTest_upper->SetBottomMargin(0.);
  pad_C1_iterTest_lower->SetBottomMargin(0.15);
  pad_C1_iterTest_upper->SetTopMargin(0.15);
  pad_C1_iterTest_lower->SetTopMargin(0.);
  pad_C1_iterTest_upper->SetLogy();
  pad_C1_iterTest_upper->Draw();
  pad_C1_iterTest_lower->Draw();
  pad_C1_iterTest_upper->cd();
  //stylizeHistograms(h_truth_C1,h_C1_iterTest,h_C1_iterTest_unfold);
  for(int i = 0; i < N_iter_tot; i++){
    if(i==0){
      h_C1_unfold_iterTest[i]->SetStats(0);
      h_C1_unfold_iterTest[i]->SetTitle("PbPb 0-10%");
      h_C1_unfold_iterTest[i]->Draw();
    }
    else h_C1_unfold_iterTest[i]->Draw("same");
  }
  h_truth_C1->Draw("same");
  leg_pp_iterTest->Draw();
  pad_C1_iterTest_lower->cd();
  TH1D *r_C1_iterTest_unfold[N_iter_tot];
  for(int i = 0; i < N_iter_tot; i++){
    r_C1_iterTest_unfold[i] = (TH1D*) h_C1_unfold_iterTest[i]->Clone(Form("r_C1_iterTest_unfold_%i",i));
    r_C1_iterTest_unfold[i]->Divide(h_C1_unfold_iterTest[i],h_truth_C1,1,1,"B");
    if(i == 0){
      r_C1_iterTest_unfold[i]->Draw();
      //r_C1_iterTest_unfold[0]->GetYaxis()->SetRangeUser(0.,2.);
      
    }
    else r_C1_iterTest_unfold[i]->Draw("same");
  }
  canv_C1_iterTest->SaveAs("../../figures/unfoldTest/C1_iterTest.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C1MC_iterTest = new TCanvas("canv_C1MC_iterTest","canv_C1MC_iterTest",700,700);
  canv_C1MC_iterTest->cd();
  TPad *pad_C1MC_iterTest_upper = new TPad("pad_C1MC_iterTest_upper","pad_C1MC_iterTest_upper",0,0.4,1,1);
  TPad *pad_C1MC_iterTest_lower = new TPad("pad_C1MC_iterTest_lower","pad_C1MC_iterTest_lower",0,0,1,0.4);
  pad_C1MC_iterTest_upper->SetLeftMargin(0.15);
  pad_C1MC_iterTest_lower->SetLeftMargin(0.15);
  pad_C1MC_iterTest_upper->SetBottomMargin(0.);
  pad_C1MC_iterTest_lower->SetBottomMargin(0.15);
  pad_C1MC_iterTest_upper->SetTopMargin(0.15);
  pad_C1MC_iterTest_lower->SetTopMargin(0.);
  pad_C1MC_iterTest_upper->SetLogy();
  pad_C1MC_iterTest_upper->Draw();
  pad_C1MC_iterTest_lower->Draw();
  pad_C1MC_iterTest_upper->cd();
  //stylizeHistograms(h_truth_C1,h_C1MC_iterTest,h_C1MC_iterTest_unfold);
  for(int i = 0; i < N_iter_tot; i++){
    if(i==0){
      h_C1MC_unfold_iterTest[i]->SetStats(0);
      h_C1MC_unfold_iterTest[i]->SetTitle("PYTHIA+HYDJET 0-10%");
      h_C1MC_unfold_iterTest[i]->Draw();
    }
    else h_C1MC_unfold_iterTest[i]->Draw("same");
  }
  h_truth_C1->Draw("same");
  h_C1MC_draw->Draw("same");
  leg_pp_iterTest->Draw();
  pad_C1MC_iterTest_lower->cd();
  TH1D *r_C1MC_iterTest_unfold[N_iter_tot];
  for(int i = 0; i < N_iter_tot; i++){
    r_C1MC_iterTest_unfold[i] = (TH1D*) h_C1MC_unfold_iterTest[i]->Clone(Form("r_C1MC_iterTest_unfold_%i",i));
    r_C1MC_iterTest_unfold[i]->Divide(h_C1MC_unfold_iterTest[i],h_truth_C1,1,1,"B");
    if(i == 0){
      r_C1MC_iterTest_unfold[i]->Draw();
      r_C1MC_iterTest_unfold[0]->GetYaxis()->SetRangeUser(0.,2.);
    }
    else r_C1MC_iterTest_unfold[i]->Draw("same");
  }
  TH1D *r_C1MC_draw = (TH1D*) h_C1MC_draw->Clone("r_C1MC_draw");
  r_C1MC_draw->Divide(h_C1MC_draw,h_truth_C1,1,1,"B");
  r_C1MC_draw->Draw("same");
  li->DrawLine(30,1,500,1);
  canv_C1MC_iterTest->SaveAs("../../figures/unfoldTest/C1MC_iterTest.pdf");


  
  ///////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_ppMC = new TCanvas("canv_ppMC","canv_ppMC",700,700);
  canv_ppMC->cd();
  TPad *pad_ppMC_upper = new TPad("pad_ppMC_upper","pad_ppMC_upper",0,0.4,1,1);
  TPad *pad_ppMC_lower = new TPad("pad_ppMC_lower","pad_ppMC_lower",0,0,1,0.4);
  pad_ppMC_upper->SetLeftMargin(0.15);
  pad_ppMC_lower->SetLeftMargin(0.15);
  pad_ppMC_upper->SetBottomMargin(0.);
  pad_ppMC_lower->SetBottomMargin(0.15);
  pad_ppMC_upper->SetTopMargin(0.15);
  pad_ppMC_lower->SetTopMargin(0.);
  pad_ppMC_upper->SetLogy();
  pad_ppMC_upper->Draw();
  pad_ppMC_lower->Draw();
  pad_ppMC_upper->cd();
  stylizeHistograms(h_truth_pp,h_ppMC,h_ppMC_unfold);
  h_ppMC->Draw();
  h_ppMC_unfold->Draw("same");
  h_truth_pp->Draw("same");
  pad_ppMC_lower->cd();
  TH1D *r_ppMC = (TH1D*) h_ppMC->Clone("r_ppMC");
  r_ppMC->Divide(h_ppMC,h_truth_pp,1,1,"B");
  TH1D *r_ppMC_unfold = (TH1D*) h_ppMC_unfold->Clone("r_ppMC_unfold");
  r_ppMC_unfold->Divide(h_ppMC_unfold,h_truth_pp,1,1,"B");
  r_ppMC->GetYaxis()->SetRangeUser(0.,2.);
  r_ppMC->Draw();
  r_ppMC_unfold->Draw("same");

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_pp = new TCanvas("canv_pp","canv_pp",700,700);
  canv_pp->cd();
  TPad *pad_pp_upper = new TPad("pad_pp_upper","pad_pp_upper",0,0.4,1,1);
  TPad *pad_pp_lower = new TPad("pad_pp_lower","pad_pp_lower",0,0,1,0.4);
  pad_pp_upper->SetLeftMargin(0.15);
  pad_pp_lower->SetLeftMargin(0.15);
  pad_pp_upper->SetBottomMargin(0.);
  pad_pp_lower->SetBottomMargin(0.15);
  pad_pp_upper->SetTopMargin(0.15);
  pad_pp_lower->SetTopMargin(0.);
  pad_pp_upper->SetLogy();
  pad_pp_upper->Draw();
  pad_pp_lower->Draw();
  pad_pp_upper->cd();
  stylizeHistograms(h_truth_pp,h_pp,h_pp_unfold);
  // scaleHistogram(h_pp,200,500);
  // scaleHistogram(h_pp_unfold,200,500);
  // scaleHistogram(h_truth_pp,200,500);
  h_pp_unfold->Scale(h_truth_pp->Integral()/h_pp->Integral());
  h_pp->Scale(h_truth_pp->Integral()/h_pp->Integral());
  h_pp->Draw();
  h_pp_unfold->Draw("same");
  h_truth_pp->Draw("same");
  pad_pp_lower->cd();
  TH1D *r_pp = (TH1D*) h_pp->Clone("r_pp");
  r_pp->Divide(h_pp,h_truth_pp,1,1,"B");
  TH1D *r_pp_unfold = (TH1D*) h_pp_unfold->Clone("r_pp_unfold");
  r_pp_unfold->Divide(h_pp_unfold,h_truth_pp,1,1,"B");
  //r_pp->GetYaxis()->SetRangeUser(0.,2.);
  r_pp->Draw();
  r_pp_unfold->Draw("same");





  
}
