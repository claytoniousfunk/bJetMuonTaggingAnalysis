#include "../../headers/functions/divideByBinwidth.h"
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#endif

void normalizeToMatchHistogram(TH1D *h_ref, TH1D *h_mod){

  // h_ref = reference histogram
  // h_mod = modified histogram

  double normRangeLow = 20.0;
  double normRangeHigh = 30.0;
  double smallShift = 0.01;

  double normFactor_ref = h_ref->Integral(h_ref->FindBin(normRangeLow+smallShift),h_ref->FindBin(normRangeHigh - smallShift));
  double normFactor_mod = h_mod->Integral(h_mod->FindBin(normRangeLow+smallShift),h_mod->FindBin(normRangeHigh - smallShift));

  h_mod->Scale(normFactor_ref/normFactor_mod);

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

void stylizeSystematics(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  h1->SetMarkerSize(0);
  h2->SetMarkerSize(0);
  h3->SetMarkerSize(0);
  h4->SetMarkerSize(0);

  double alpha = 0.5;
  h1->SetFillColorAlpha(kRed-4,alpha);
  h2->SetFillColorAlpha(kGreen+2,alpha);
  h3->SetFillColorAlpha(kBlue-4,alpha);
  h4->SetFillColorAlpha(kGray,alpha);

}

void stylizeHistograms(TH1D *h0, TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  double lw  = 2;
  double ms = 2;
  
  h0->SetLineColor(kBlack);
  h0->SetMarkerColor(kBlack);
  h0->SetLineWidth(lw);
  h0->SetMarkerSize(ms);
  h0->SetMarkerStyle(24);
  h0->SetStats(0);
  h0->SetTitle("");

  h4->SetLineColor(kBlack);
  h4->SetMarkerColor(kBlack);
  h4->SetLineWidth(lw);
  h4->SetMarkerSize(ms);
  h4->SetMarkerStyle(33);
  h4->SetStats(0);
  h4->SetTitle("");

  h3->SetLineColor(kBlue-4);
  h3->SetMarkerColor(kBlue-4);
  h3->SetLineWidth(lw);
  h3->SetMarkerSize(ms);
  h3->SetMarkerStyle(21);
  h3->SetStats(0);
  h3->SetTitle("");
  
  h2->SetLineColor(kGreen+2);
  h2->SetMarkerColor(kGreen+2);
  h2->SetLineWidth(lw);
  h2->SetMarkerSize(ms);
  h2->SetMarkerStyle(34);
  h2->SetStats(0);
  h2->SetTitle("");

  h1->SetLineColor(kRed-4);
  h1->SetMarkerColor(kRed-4);
  h1->SetLineWidth(lw);
  h1->SetMarkerSize(ms);
  h1->SetMarkerStyle(47);
  h1->SetStats(0);
  h1->SetTitle("");

  return;

}

void stylizePubHistograms_CMS(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  double lw  = 2;
  double ms = 2;

  h1->SetLineColor(kRed-4);
  h1->SetMarkerColor(kRed-4);
  h1->SetLineWidth(lw);
  h1->SetMarkerSize(ms);
  h1->SetMarkerStyle(46);
  h1->SetStats(0);
  h1->SetTitle("");

  h2->SetLineColor(kGreen+2);
  h2->SetMarkerColor(kGreen+2);
  h2->SetLineWidth(lw);
  h2->SetMarkerSize(ms);
  h2->SetMarkerStyle(28);
  h2->SetStats(0);
  h2->SetTitle("");

  h3->SetLineColor(kBlue-4);
  h3->SetMarkerColor(kBlue-4);
  h3->SetLineWidth(lw);
  h3->SetMarkerSize(ms);
  h3->SetMarkerStyle(25);
  h3->SetStats(0);
  h3->SetTitle("");

  h4->SetLineColor(kBlack);
  h4->SetMarkerColor(kBlack);
  h4->SetLineWidth(lw);
  h4->SetMarkerSize(ms);
  h4->SetMarkerStyle(27);
  h4->SetStats(0);
  h4->SetTitle("");

}

void stylizePubHistograms_ATLAS(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  double lw  = 2;
  double ms = 2;

  h1->SetLineColor(kRed-4);
  h1->SetMarkerColor(kRed-4);
  h1->SetLineWidth(lw);
  h1->SetMarkerSize(ms);
  h1->SetMarkerStyle(24);
  h1->SetStats(0);
  h1->SetTitle("");

  h2->SetLineColor(kGreen+2);
  h2->SetMarkerColor(kGreen+2);
  h2->SetLineWidth(lw);
  h2->SetMarkerSize(ms);
  h2->SetMarkerStyle(24);
  h2->SetStats(0);
  h2->SetTitle("");

  h3->SetLineColor(kBlue-4);
  h3->SetMarkerColor(kBlue-4);
  h3->SetLineWidth(lw);
  h3->SetMarkerSize(ms);
  h3->SetMarkerStyle(24);
  h3->SetStats(0);
  h3->SetTitle("");

  h4->SetLineColor(kBlack);
  h4->SetMarkerColor(kBlack);
  h4->SetLineWidth(lw);
  h4->SetMarkerSize(ms);
  h4->SetMarkerStyle(24);
  h4->SetStats(0);
  h4->SetTitle("");

}


TH1D* stitchSamples(TH1D *h_jetMB, TH1D *h_fakeJets, TH1D *h_jet60, TH1D *h_jet80, TH1D *h_jet100,
		    bool isPP, bool isPbPb){

  TH1D *h_return = (TH1D*) h_jet100->Clone("h_return");

  double jetMB_pTmin = 60.;
  double jet60_pTmin = 100;
  double jet80_pTmin = 150;
  double jet100_pTmin = 200;
  double smallShift = 0.01;

  if(!isPP){
    jet60_pTmin = jet80_pTmin;
  }




  double N_jet100 = h_jet100->Integral(h_jet100->FindBin(jet100_pTmin + smallShift),h_jet100->FindBin(500. - smallShift));
  double N_jet80 = h_jet80->Integral(h_jet80->FindBin(jet100_pTmin + smallShift),h_jet80->FindBin(500. - smallShift));
  double N_jet60 = h_jet60->Integral(h_jet60->FindBin(jet80_pTmin + smallShift),h_jet60->FindBin(jet100_pTmin - smallShift));
  double N_jetMB = h_jetMB->Integral(h_jetMB->FindBin(jet60_pTmin + smallShift),h_jetMB->FindBin(jet80_pTmin - smallShift));
  double N_fakeJets = h_fakeJets->Integral(h_fakeJets->FindBin(jet60_pTmin + smallShift),h_fakeJets->FindBin(jet80_pTmin - smallShift));
  

  
  TH1D *h_jet80_scaled = (TH1D*) h_jet80->Clone("h_jet80_scaled");
  h_jet80_scaled->Scale(N_jet100 / N_jet80);

  double N_jet80_scaled = h_jet80_scaled->Integral(h_jet80_scaled->FindBin(jet80_pTmin + smallShift),h_jet80_scaled->FindBin(jet100_pTmin - smallShift));

  TH1D *h_jet60_scaled = (TH1D*) h_jet60->Clone("h_jet60_scaled");
  h_jet60_scaled->Scale(N_jet80_scaled / N_jet60);
  
  double N_jet60_scaled = h_jet60_scaled->Integral(h_jet60_scaled->FindBin(jet60_pTmin + smallShift),h_jet60_scaled->FindBin(jet80_pTmin - smallShift));

  TH1D *h_jetMB_scaled = (TH1D*) h_jetMB->Clone("h_jetMB_scaled");
  h_jetMB_scaled->Scale(N_jet60_scaled / N_jetMB);
  
  TH1D *h_fakeJets_scaled = (TH1D*) h_fakeJets->Clone("h_fakeJets_scaled");
  h_fakeJets_scaled->Scale(N_jet60_scaled / N_jetMB);
    
  // subtract fake jets
  if(isPbPb) h_jetMB_scaled->Add(h_fakeJets_scaled,-1);
  
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


void calculateRAA(){

  TFile *file_pp_HighEGJet_jet60 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet60HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-10.root");
  TFile *file_pp_HighEGJet_jet80 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet80HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-10.root");
  TFile *file_pp_HighEGJet_jet100 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet100HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_WDecayFilter_2026-3-11.root");
  //TFile *file_pp_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_WDecayFilter_2026-3-16.root");
  TFile *file_pp_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15to999_tight_deltaR-40_mu12TriggerEfficiencyCorrection_jetTrkMaxFilter_WDecayFilter_2026-5-4.root");
  TFile *file_pp_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_MinBias_mu12_pTmu-14_tight_jetTrkMaxFilter_2025-10-15.root");
  


  TFile *file_PbPb_HardProbes_jet60 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet60HLT_mu12_pTmu-15to999_tight_WDecayFilter_2026-3-11.root");
  TFile *file_PbPb_HardProbes_jet80 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet80HLT_mu12_pTmu-15to999_tight_jetTrkMaxFilter_WDecayFilter_2026-5-5.root");
  TFile *file_PbPb_HardProbes_jet100 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet100HLT_mu12_pTmu-15to999_tight_jetTrkMaxFilter_WDecayFilter_2026-5-5.root");
  //TFile *file_PbPb_HardProbes_jet80 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet80HLT_mu12_pTmu-15to999_tight_WDecayFilter_2026-4-8.root");
  //TFile *file_PbPb_HardProbes_jet100 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet100HLT_mu12_pTmu-15to999_tight_WDecayFilter_2026-4-8.root");
  TFile *file_PbPb_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15to999_tight_mu12TriggerEfficiencyCorrection_jetTrkMaxFilter_WDecayFilter_2026-5-4.root");
  //TFile *file_PbPb_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15to999_tight_mu12TriggerEfficiencyCorrection_jetTrkMaxFilter_WDecayFilter_2026-4-21.root");
  TFile *file_PbPb_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_MinBias_mu12_pTmu-15to999_tight_WDecayFilter_2026-4-8.root");


  TFile *file_PYTHIA_response = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-1-26.root");
  TFile *file_PH_response = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-4-6_evenEvents.root");
  

  

  
  TFile *f_pubATLAS_C1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1673184-v1-Table_19.root");
  TH1D *h_pubATLAS_C1, *h_pubATLAS_C1_err, *h_pubATLAS_C1_orig;
  TDirectoryFile *dirATLAS_C1 = (TDirectoryFile*) f_pubATLAS_C1->Get("Table 19");
  h_pubATLAS_C1 = (TH1D*) dirATLAS_C1->Get("Hist1D_y1");
  h_pubATLAS_C1_orig = (TH1D*) dirATLAS_C1->Get("Hist1D_y1");
  h_pubATLAS_C1_err = (TH1D*) dirATLAS_C1->Get("Hist1D_y1_e1plus");
  h_pubATLAS_C1->SetLineColor(kRed-4);
  for(int i = 0; i < h_pubATLAS_C1->GetSize(); i++){
    h_pubATLAS_C1->SetBinContent(i,h_pubATLAS_C1_orig->GetBinContent(i));
    h_pubATLAS_C1->SetBinError(i,h_pubATLAS_C1_err->GetBinContent(i));
  }

  TFile *f_pubCMS_C1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1848440-v1-Figure_7-3.root");
  TH1D *h_pubCMS_C1, *h_pubCMS_C1_err, *h_pubCMS_C1_orig;
  TDirectoryFile *dirCMS_C1 = (TDirectoryFile*) f_pubCMS_C1->Get("Figure 7-3");
  h_pubCMS_C1 = (TH1D*) dirCMS_C1->Get("Hist1D_y1");
  h_pubCMS_C1_orig = (TH1D*) dirCMS_C1->Get("Hist1D_y1");
  h_pubCMS_C1_err = (TH1D*) dirCMS_C1->Get("Hist1D_y1_e1plus");
  h_pubCMS_C1->SetLineColor(kRed-4);
  for(int i = 0; i < h_pubCMS_C1->GetSize(); i++){
    h_pubCMS_C1->SetBinContent(i,h_pubCMS_C1_orig->GetBinContent(i));
    h_pubCMS_C1->SetBinError(i,h_pubCMS_C1_err->GetBinContent(i));
  }


  TFile *f_pubATLAS_C2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1673184-v1-Table_20.root");
  TH1D *h_pubATLAS_C2, *h_pubATLAS_C2_err, *h_pubATLAS_C2_orig;
  TDirectoryFile *dirATLAS_C2 = (TDirectoryFile*) f_pubATLAS_C2->Get("Table 20");
  h_pubATLAS_C2 = (TH1D*) dirATLAS_C2->Get("Hist1D_y1");
  h_pubATLAS_C2_orig = (TH1D*) dirATLAS_C2->Get("Hist1D_y1");
  h_pubATLAS_C2_err = (TH1D*) dirATLAS_C2->Get("Hist1D_y1_e1plus");
  h_pubATLAS_C2->SetLineColor(kRed-4);
  for(int i = 0; i < h_pubATLAS_C2->GetSize(); i++){
    h_pubATLAS_C2->SetBinContent(i,h_pubATLAS_C2_orig->GetBinContent(i));
    h_pubATLAS_C2->SetBinError(i,h_pubATLAS_C2_err->GetBinContent(i));
  }

  TFile *f_pubCMS_C2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1848440-v1-Figure_7-3.root");
  TH1D *h_pubCMS_C2, *h_pubCMS_C2_err, *h_pubCMS_C2_orig;
  TDirectoryFile *dirCMS_C2 = (TDirectoryFile*) f_pubCMS_C2->Get("Figure 7-3");
  h_pubCMS_C2 = (TH1D*) dirCMS_C2->Get("Hist1D_y2");
  h_pubCMS_C2_orig = (TH1D*) dirCMS_C2->Get("Hist1D_y2");
  h_pubCMS_C2_err = (TH1D*) dirCMS_C2->Get("Hist1D_y2_e1plus");
  h_pubCMS_C2->SetLineColor(kRed-4);
  for(int i = 0; i < h_pubCMS_C2->GetSize(); i++){
    h_pubCMS_C2->SetBinContent(i,h_pubCMS_C2_orig->GetBinContent(i));
    h_pubCMS_C2->SetBinError(i,h_pubCMS_C2_err->GetBinContent(i));
  }


  TFile *f_pubATLAS_C3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1673184-v1-Table_22.root");
  TH1D *h_pubATLAS_C3, *h_pubATLAS_C3_err, *h_pubATLAS_C3_orig;
  TDirectoryFile *dirATLAS_C3 = (TDirectoryFile*) f_pubATLAS_C3->Get("Table 22");
  h_pubATLAS_C3 = (TH1D*) dirATLAS_C3->Get("Hist1D_y1");
  h_pubATLAS_C3_orig = (TH1D*) dirATLAS_C3->Get("Hist1D_y1");
  h_pubATLAS_C3_err = (TH1D*) dirATLAS_C3->Get("Hist1D_y1_e1plus");
  h_pubATLAS_C3->SetLineColor(kRed-4);
  for(int i = 0; i < h_pubATLAS_C3->GetSize(); i++){
    h_pubATLAS_C3->SetBinContent(i,h_pubATLAS_C3_orig->GetBinContent(i));
    h_pubATLAS_C3->SetBinError(i,h_pubATLAS_C3_err->GetBinContent(i));
  }

  TFile *f_pubCMS_C3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1848440-v1-Figure_7-3.root");
  TH1D *h_pubCMS_C3, *h_pubCMS_C3_err, *h_pubCMS_C3_orig;
  TDirectoryFile *dirCMS_C3 = (TDirectoryFile*) f_pubCMS_C3->Get("Figure 7-3");
  h_pubCMS_C3 = (TH1D*) dirCMS_C3->Get("Hist1D_y3");
  h_pubCMS_C3_orig = (TH1D*) dirCMS_C3->Get("Hist1D_y3");
  h_pubCMS_C3_err = (TH1D*) dirCMS_C3->Get("Hist1D_y3_e1plus");
  h_pubCMS_C3->SetLineColor(kRed-4);
  for(int i = 0; i < h_pubCMS_C3->GetSize(); i++){
    h_pubCMS_C3->SetBinContent(i,h_pubCMS_C3_orig->GetBinContent(i));
    h_pubCMS_C3->SetBinError(i,h_pubCMS_C3_err->GetBinContent(i));
  }

  TFile *f_pubATLAS_C4 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1673184-v1-Table_24.root");
  TH1D *h_pubATLAS_C4, *h_pubATLAS_C4_err, *h_pubATLAS_C4_orig;
  TDirectoryFile *dirATLAS_C4 = (TDirectoryFile*) f_pubATLAS_C4->Get("Table 24");
  h_pubATLAS_C4 = (TH1D*) dirATLAS_C4->Get("Hist1D_y1");
  h_pubATLAS_C4_orig = (TH1D*) dirATLAS_C4->Get("Hist1D_y1");
  h_pubATLAS_C4_err = (TH1D*) dirATLAS_C4->Get("Hist1D_y1_e1plus");
  h_pubATLAS_C4->SetLineColor(kRed-4);
  for(int i = 0; i < h_pubATLAS_C4->GetSize(); i++){
    h_pubATLAS_C4->SetBinContent(i,h_pubATLAS_C4_orig->GetBinContent(i));
    h_pubATLAS_C4->SetBinError(i,h_pubATLAS_C4_err->GetBinContent(i));
  }

  TFile *f_pubCMS_C4 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1848440-v1-Figure_7-3.root");
  TH1D *h_pubCMS_C4, *h_pubCMS_C4_err, *h_pubCMS_C4_orig;
  TDirectoryFile *dirCMS_C4 = (TDirectoryFile*) f_pubCMS_C4->Get("Figure 7-3");
  h_pubCMS_C4 = (TH1D*) dirCMS_C4->Get("Hist1D_y4");
  h_pubCMS_C4_orig = (TH1D*) dirCMS_C4->Get("Hist1D_y4");
  h_pubCMS_C4_err = (TH1D*) dirCMS_C4->Get("Hist1D_y4_e1plus");
  h_pubCMS_C4->SetLineColor(kRed-4);
  for(int i = 0; i < h_pubCMS_C4->GetSize(); i++){
    h_pubCMS_C4->SetBinContent(i,h_pubCMS_C4_orig->GetBinContent(i));
    h_pubCMS_C4->SetBinError(i,h_pubCMS_C4_err->GetBinContent(i));
  }


  TFile *f_pubATLAS_spectra_pp = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1673184-v1-Table_4.root");
  TH1D *h_pubATLAS_spectra_pp, *h_pubATLAS_spectra_pp_err, *h_pubATLAS_spectra_pp_orig;
  TDirectoryFile *dirATLAS_spectra_pp = (TDirectoryFile*) f_pubATLAS_spectra_pp->Get("Table 4");
  h_pubATLAS_spectra_pp = (TH1D*) dirATLAS_spectra_pp->Get("Hist1D_y1");
  h_pubATLAS_spectra_pp_orig = (TH1D*) dirATLAS_spectra_pp->Get("Hist1D_y1");
  h_pubATLAS_spectra_pp_err = (TH1D*) dirATLAS_spectra_pp->Get("Hist1D_y1_e1plus");
  for(int i = 0; i < h_pubATLAS_spectra_pp->GetSize(); i++){
    h_pubATLAS_spectra_pp->SetBinContent(i,h_pubATLAS_spectra_pp_orig->GetBinContent(i));
    h_pubATLAS_spectra_pp->SetBinError(i,h_pubATLAS_spectra_pp_err->GetBinContent(i));
  }

  TFile *f_pubATLAS_spectra_C1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/HEPData-ins1673184-v1-Table_11.root");
  TH1D *h_pubATLAS_spectra_C1, *h_pubATLAS_spectra_C1_err, *h_pubATLAS_spectra_C1_orig;
  TDirectoryFile *dirATLAS_spectra_C1 = (TDirectoryFile*) f_pubATLAS_spectra_C1->Get("Table 11");
  h_pubATLAS_spectra_C1 = (TH1D*) dirATLAS_spectra_C1->Get("Hist1D_y1");
  h_pubATLAS_spectra_C1_orig = (TH1D*) dirATLAS_spectra_C1->Get("Hist1D_y1");
  h_pubATLAS_spectra_C1_err = (TH1D*) dirATLAS_spectra_C1->Get("Hist1D_y1_e1plus");
  for(int i = 0; i < h_pubATLAS_spectra_C1->GetSize(); i++){
    h_pubATLAS_spectra_C1->SetBinContent(i,h_pubATLAS_spectra_C1_orig->GetBinContent(i));
    h_pubATLAS_spectra_C1->SetBinError(i,h_pubATLAS_spectra_C1_err->GetBinContent(i));
  }



  


  
  stylizePubHistograms_ATLAS(h_pubATLAS_C1, h_pubATLAS_C2, h_pubATLAS_C3, h_pubATLAS_C4);
  stylizePubHistograms_CMS(h_pubCMS_C1, h_pubCMS_C2, h_pubCMS_C3, h_pubCMS_C4);
  


  TH1D *h_pp, *h_C4, *h_C3, *h_C2, *h_C1;
  TH1D *h_pp_jetMB, *h_C4_jetMB, *h_C3_jetMB, *h_C2_jetMB, *h_C1_jetMB;
  TH1D *h_pp_jet60, *h_C4_jet60, *h_C3_jet60, *h_C2_jet60, *h_C1_jet60;
  TH1D *h_pp_jet80, *h_C4_jet80, *h_C3_jet80, *h_C2_jet80, *h_C1_jet80;
  TH1D *h_pp_jet100, *h_C4_jet100, *h_C3_jet100, *h_C2_jet100, *h_C1_jet100;
  TH1D *hiBin_pp, *hiBin_PbPb;
  TH1D *h_vz_pp, *h_vz_C4, *h_vz_C3, *h_vz_C2, *h_vz_C1;
  double N_evt_pp, N_evt_C4, N_evt_C3, N_evt_C2, N_evt_C1;
  TH1D *r_C4, *r_C3, *r_C2, *r_C1;
  double N_coll_avg_C4, N_coll_avg_C3, N_coll_avg_C2, N_coll_avg_C1;
  TH1D *h_vz_MinBias_C4, *h_vz_MinBias_C3, *h_vz_MinBias_C2, *h_vz_MinBias_C1;
  TH1D *h_vz_MinBias_Jet100_C4, *h_vz_MinBias_Jet100_C3, *h_vz_MinBias_Jet100_C2, *h_vz_MinBias_Jet100_C1;
  TH1D *h_vz_MinBias_Jet100_withJetAbove130_C4, *h_vz_MinBias_Jet100_withJetAbove130_C3, *h_vz_MinBias_Jet100_withJetAbove130_C2, *h_vz_MinBias_Jet100_withJetAbove130_C1;
  double N_evt_MinBias_C4, N_evt_MinBias_C3, N_evt_MinBias_C2, N_evt_MinBias_C1;
  double N_evt_MinBias_Jet100_C4, N_evt_MinBias_Jet100_C3, N_evt_MinBias_Jet100_C2, N_evt_MinBias_Jet100_C1;
  double N_evt_MinBias_Jet100_withJetAbove130_C4, N_evt_MinBias_Jet100_withJetAbove130_C3, N_evt_MinBias_Jet100_withJetAbove130_C2, N_evt_MinBias_Jet100_withJetAbove130_C1;
  double minBiasEquivalentEventConversion_C4, minBiasEquivalentEventConversion_C3, minBiasEquivalentEventConversion_C2, minBiasEquivalentEventConversion_C1;
  double triggerLossCorrection_C4, triggerLossCorrection_C3, triggerLossCorrection_C2, triggerLossCorrection_C1;

  TH1D *h_dimuonMass_pp, *h_dimuonMass_C4, *h_dimuonMass_C3, *h_dimuonMass_C2, *h_dimuonMass_C1;

  file_pp_SingleMuon->GetObject("h_dimuonMass",h_dimuonMass_pp); // try to normalize with SingleMuon sample (will only work if luminosities are equal)
  file_PbPb_SingleMuon->GetObject("h_dimuonMass_C4",h_dimuonMass_C4);
  file_PbPb_SingleMuon->GetObject("h_dimuonMass_C3",h_dimuonMass_C3);
  file_PbPb_SingleMuon->GetObject("h_dimuonMass_C2",h_dimuonMass_C2);
  file_PbPb_SingleMuon->GetObject("h_dimuonMass_C1",h_dimuonMass_C1);

  file_PbPb_MinBias->GetObject("h_vz_C4",h_vz_MinBias_C4);
  file_PbPb_MinBias->GetObject("h_vz_C3",h_vz_MinBias_C3);
  file_PbPb_MinBias->GetObject("h_vz_C2",h_vz_MinBias_C2);
  file_PbPb_MinBias->GetObject("h_vz_C1",h_vz_MinBias_C1);

  file_PbPb_MinBias->GetObject("h_vz_jet100_withJetAbove130_C4",h_vz_MinBias_Jet100_withJetAbove130_C4);
  file_PbPb_MinBias->GetObject("h_vz_jet100_withJetAbove130_C3",h_vz_MinBias_Jet100_withJetAbove130_C3);
  file_PbPb_MinBias->GetObject("h_vz_jet100_withJetAbove130_C2",h_vz_MinBias_Jet100_withJetAbove130_C2);
  file_PbPb_MinBias->GetObject("h_vz_jet100_withJetAbove130_C1",h_vz_MinBias_Jet100_withJetAbove130_C1);

  file_PbPb_MinBias->GetObject("h_vz_jet100_C4",h_vz_MinBias_Jet100_C4);
  file_PbPb_MinBias->GetObject("h_vz_jet100_C3",h_vz_MinBias_Jet100_C3);
  file_PbPb_MinBias->GetObject("h_vz_jet100_C2",h_vz_MinBias_Jet100_C2);
  file_PbPb_MinBias->GetObject("h_vz_jet100_C1",h_vz_MinBias_Jet100_C1);

  triggerLossCorrection_C4 = h_vz_MinBias_Jet100_C4->Integral() / h_vz_MinBias_Jet100_withJetAbove130_C4->Integral();
  triggerLossCorrection_C3 = h_vz_MinBias_Jet100_C3->Integral() / h_vz_MinBias_Jet100_withJetAbove130_C3->Integral();
  triggerLossCorrection_C2 = h_vz_MinBias_Jet100_C2->Integral() / h_vz_MinBias_Jet100_withJetAbove130_C2->Integral();
  triggerLossCorrection_C1 = h_vz_MinBias_Jet100_C1->Integral() / h_vz_MinBias_Jet100_withJetAbove130_C1->Integral();

  
  minBiasEquivalentEventConversion_C4 = h_vz_MinBias_C4->Integral() / h_vz_MinBias_Jet100_C4->Integral();
  minBiasEquivalentEventConversion_C3 = h_vz_MinBias_C3->Integral() / h_vz_MinBias_Jet100_C3->Integral();
  minBiasEquivalentEventConversion_C2 = h_vz_MinBias_C2->Integral() / h_vz_MinBias_Jet100_C2->Integral();
  minBiasEquivalentEventConversion_C1 = h_vz_MinBias_C1->Integral() / h_vz_MinBias_Jet100_C1->Integral();

  cout << "minBiasEquivalentEventConversion_C4 = " << minBiasEquivalentEventConversion_C4 << "\n";

  file_pp_HighEGJet_jet60->GetObject("h_inclRecoJetPt",h_pp_jet60);
  file_pp_HighEGJet_jet80->GetObject("h_inclRecoJetPt",h_pp_jet80);
  file_pp_HighEGJet_jet100->GetObject("h_inclRecoJetPt",h_pp_jet100);
  file_pp_MinBias->GetObject("h_inclRecoJetPt",h_pp_jetMB);

  



  file_pp_HighEGJet_jet100->GetObject("h_vz",h_vz_pp);

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


  TFile *file_fakeJets = TFile::Open("../../rootFiles/fakeJets/fakeJets.root");
  TH1D *h_fakeJets_C4, *h_fakeJets_C3, *h_fakeJets_C2, *h_fakeJets_C1;

  file_fakeJets->GetObject("h_fakeJets_C4",h_fakeJets_C4);
  file_fakeJets->GetObject("h_fakeJets_C3",h_fakeJets_C3);
  file_fakeJets->GetObject("h_fakeJets_C2",h_fakeJets_C2);
  file_fakeJets->GetObject("h_fakeJets_C1",h_fakeJets_C1);
  
  // h_fakeJets_C4->Scale(h_vz_MinBias_C4->Integral());
  // h_fakeJets_C3->Scale(h_vz_MinBias_C3->Integral());
  // h_fakeJets_C2->Scale(h_vz_MinBias_C2->Integral());
  // h_fakeJets_C1->Scale(h_vz_MinBias_C1->Integral());

  h_C4_jetMB->Scale(1./h_vz_MinBias_C4->Integral());
  h_C3_jetMB->Scale(1./h_vz_MinBias_C3->Integral());
  h_C2_jetMB->Scale(1./h_vz_MinBias_C2->Integral());
  h_C1_jetMB->Scale(1./h_vz_MinBias_C1->Integral());

  ///////////////////////////////////////////////////////////////////////////////////////
  
  TH1D *h_C1_clone = (TH1D*) h_C1_jetMB->Clone("h_C1_clone");
  TH1D *h_fakeJets_C1_clone = (TH1D*) h_fakeJets_C1->Clone("h_fakeJets_C1_clone");
  TH1D *h_C1_sub = (TH1D*) h_C1_jetMB->Clone("h_C1_sub");
  h_C1_sub->Add(h_fakeJets_C1,-1);
  h_C1_clone->SetLineColor(kRed-4);
  h_fakeJets_C1_clone->SetLineColor(kGray+1);
  h_C1_sub->SetLineColor(kRed-4);
  h_fakeJets_C1_clone->SetLineStyle(1);
  h_C1_sub->SetLineStyle(7);
  h_C1_clone->SetLineWidth(2);
  h_fakeJets_C1_clone->SetLineWidth(2);
  h_C1_sub->SetLineWidth(2);

  TH1D *r_C1_sub = (TH1D*) h_C1_sub->Clone("r_C1_sub");
  r_C1_sub->Divide(h_C1_sub,h_C1_clone,1,1,"B");

  TCanvas *canv_fakeJets_C1 = new TCanvas("canv_fakeJets_C1","canv_fakeJets_C1",700,700);
  canv_fakeJets_C1->cd();
  TPad *pad_fakeJets_C1_upper = new TPad("pad_fakeJets_C1_upper","pad_fakeJets_C1_upper",0,0.4,1,1);
  TPad *pad_fakeJets_C1_lower = new TPad("pad_fakeJets_C1_lower","pad_fakeJets_C1_lower",0,0,1,0.4);
  pad_fakeJets_C1_upper->SetLeftMargin(0.15);
  pad_fakeJets_C1_lower->SetLeftMargin(0.15);
  pad_fakeJets_C1_upper->SetBottomMargin(0.);
  pad_fakeJets_C1_lower->SetBottomMargin(0.18);
  pad_fakeJets_C1_upper->SetTopMargin(0.15);
  pad_fakeJets_C1_lower->SetTopMargin(0.);
  pad_fakeJets_C1_upper->SetLogy();
  pad_fakeJets_C1_upper->Draw();
  pad_fakeJets_C1_lower->Draw();
  pad_fakeJets_C1_upper->cd();
  h_C1_clone->SetStats(0);
  h_C1_clone->SetTitle("");
  h_C1_clone->GetYaxis()->SetLabelSize(0.045);
  h_C1_clone->GetYaxis()->SetTitleSize(0.055);
  h_C1_clone->GetYaxis()->SetTitle("#frac{1}{#it{N}^{evt}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_C1_clone->Draw("hist");
  h_fakeJets_C1_clone->Draw("hist same");
  h_C1_sub->Draw("hist same");
  TLegend *leg_fakeJets_C1 = new TLegend(0.3,0.7,0.7,0.84);
  leg_fakeJets_C1->SetBorderSize(0);
  leg_fakeJets_C1->SetTextSize(0.045);
  leg_fakeJets_C1->AddEntry(h_C1_clone,"PbPb MinBias 0-10%");
  leg_fakeJets_C1->AddEntry(h_fakeJets_C1_clone,"fake-jets, PYTHIA+HYDJET 0-10%");
  leg_fakeJets_C1->AddEntry(h_C1_sub,"Corrected PbPb MinBias 0-10%");
  leg_fakeJets_C1->Draw();

  pad_fakeJets_C1_lower->cd();
  r_C1_sub->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C1_sub->GetYaxis()->SetTitle("Corrected / Nominal");
  r_C1_sub->GetXaxis()->SetLabelSize(0.06);
  r_C1_sub->GetXaxis()->SetTitleSize(0.07);
  r_C1_sub->GetYaxis()->SetLabelSize(0.06);
  r_C1_sub->GetYaxis()->SetTitleSize(0.07);
  r_C1_sub->SetTitle("");
  r_C1_sub->SetStats(0);
  r_C1_sub->Draw("hist");

  ///////////////////////////////////////////////////////////////////////////////////////
  
  TH1D *h_C2_clone = (TH1D*) h_C2_jetMB->Clone("h_C2_clone");
  TH1D *h_fakeJets_C2_clone = (TH1D*) h_fakeJets_C2->Clone("h_fakeJets_C2_clone");
  TH1D *h_C2_sub = (TH1D*) h_C2_jetMB->Clone("h_C2_sub");
  h_C2_sub->Add(h_fakeJets_C2,-1);
  h_C2_clone->SetLineColor(kGreen+2);
  h_fakeJets_C2_clone->SetLineColor(kGray+1);
  h_C2_sub->SetLineColor(kGreen+2);
  h_fakeJets_C2_clone->SetLineStyle(1);
  h_C2_sub->SetLineStyle(7);
  h_C2_clone->SetLineWidth(2);
  h_fakeJets_C2_clone->SetLineWidth(2);
  h_C2_sub->SetLineWidth(2);

  TH1D *r_C2_sub = (TH1D*) h_C2_sub->Clone("r_C2_sub");
  r_C2_sub->Divide(h_C2_sub,h_C2_clone,1,1,"B");

  TCanvas *canv_fakeJets_C2 = new TCanvas("canv_fakeJets_C2","canv_fakeJets_C2",700,700);
  canv_fakeJets_C2->cd();
  TPad *pad_fakeJets_C2_upper = new TPad("pad_fakeJets_C2_upper","pad_fakeJets_C2_upper",0,0.4,1,1);
  TPad *pad_fakeJets_C2_lower = new TPad("pad_fakeJets_C2_lower","pad_fakeJets_C2_lower",0,0,1,0.4);
  pad_fakeJets_C2_upper->SetLeftMargin(0.15);
  pad_fakeJets_C2_lower->SetLeftMargin(0.15);
  pad_fakeJets_C2_upper->SetBottomMargin(0.);
  pad_fakeJets_C2_lower->SetBottomMargin(0.18);
  pad_fakeJets_C2_upper->SetTopMargin(0.15);
  pad_fakeJets_C2_lower->SetTopMargin(0.);
  pad_fakeJets_C2_upper->SetLogy();
  pad_fakeJets_C2_upper->Draw();
  pad_fakeJets_C2_lower->Draw();
  pad_fakeJets_C2_upper->cd();
  h_C2_clone->SetStats(0);
  h_C2_clone->SetTitle("");
  h_C2_clone->GetYaxis()->SetLabelSize(0.045);
  h_C2_clone->GetYaxis()->SetTitleSize(0.055);
  h_C2_clone->GetYaxis()->SetTitle("#frac{1}{#it{N}^{evt}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_C2_clone->Draw("hist");
  h_fakeJets_C2_clone->Draw("hist same");
  h_C2_sub->Draw("hist same");
  TLegend *leg_fakeJets_C2 = new TLegend(0.3,0.7,0.7,0.84);
  leg_fakeJets_C2->SetBorderSize(0);
  leg_fakeJets_C2->SetTextSize(0.045);
  leg_fakeJets_C2->AddEntry(h_C2_clone,"PbPb MinBias 10-30%");
  leg_fakeJets_C2->AddEntry(h_fakeJets_C2_clone,"fake-jets, PYTHIA+HYDJET 10-30%");
  leg_fakeJets_C2->AddEntry(h_C2_sub,"Corrected PbPb MinBias 10-30%");
  leg_fakeJets_C2->Draw();

  pad_fakeJets_C2_lower->cd();
  r_C2_sub->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C2_sub->GetYaxis()->SetTitle("Corrected / Nominal");
  r_C2_sub->GetXaxis()->SetLabelSize(0.06);
  r_C2_sub->GetXaxis()->SetTitleSize(0.07);
  r_C2_sub->GetYaxis()->SetLabelSize(0.06);
  r_C2_sub->GetYaxis()->SetTitleSize(0.07);
  r_C2_sub->SetTitle("");
  r_C2_sub->SetStats(0);
  r_C2_sub->Draw("hist");

  ///////////////////////////////////////////////////////////////////////////////////////
  
  TH1D *h_C3_clone = (TH1D*) h_C3_jetMB->Clone("h_C3_clone");
  TH1D *h_fakeJets_C3_clone = (TH1D*) h_fakeJets_C3->Clone("h_fakeJets_C3_clone");
  TH1D *h_C3_sub = (TH1D*) h_C3_jetMB->Clone("h_C3_sub");
  h_C3_sub->Add(h_fakeJets_C3,-1);
  h_C3_clone->SetLineColor(kBlue-4);
  h_fakeJets_C3_clone->SetLineColor(kGray+1);
  h_C3_sub->SetLineColor(kBlue-4);
  h_fakeJets_C3_clone->SetLineStyle(1);
  h_C3_sub->SetLineStyle(7);
  h_C3_clone->SetLineWidth(2);
  h_fakeJets_C3_clone->SetLineWidth(2);
  h_C3_sub->SetLineWidth(2);

  TH1D *r_C3_sub = (TH1D*) h_C3_sub->Clone("r_C3_sub");
  r_C3_sub->Divide(h_C3_sub,h_C3_clone,1,1,"B");

  TCanvas *canv_fakeJets_C3 = new TCanvas("canv_fakeJets_C3","canv_fakeJets_C3",700,700);
  canv_fakeJets_C3->cd();
  TPad *pad_fakeJets_C3_upper = new TPad("pad_fakeJets_C3_upper","pad_fakeJets_C3_upper",0,0.4,1,1);
  TPad *pad_fakeJets_C3_lower = new TPad("pad_fakeJets_C3_lower","pad_fakeJets_C3_lower",0,0,1,0.4);
  pad_fakeJets_C3_upper->SetLeftMargin(0.15);
  pad_fakeJets_C3_lower->SetLeftMargin(0.15);
  pad_fakeJets_C3_upper->SetBottomMargin(0.);
  pad_fakeJets_C3_lower->SetBottomMargin(0.18);
  pad_fakeJets_C3_upper->SetTopMargin(0.15);
  pad_fakeJets_C3_lower->SetTopMargin(0.);
  pad_fakeJets_C3_upper->SetLogy();
  pad_fakeJets_C3_upper->Draw();
  pad_fakeJets_C3_lower->Draw();
  pad_fakeJets_C3_upper->cd();
  h_C3_clone->SetStats(0);
  h_C3_clone->SetTitle("");
  h_C3_clone->GetYaxis()->SetLabelSize(0.045);
  h_C3_clone->GetYaxis()->SetTitleSize(0.055);
  h_C3_clone->GetYaxis()->SetTitle("#frac{1}{#it{N}^{evt}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_C3_clone->Draw("hist");
  h_fakeJets_C3_clone->Draw("hist same");
  h_C3_sub->Draw("hist same");
  TLegend *leg_fakeJets_C3 = new TLegend(0.3,0.7,0.7,0.84);
  leg_fakeJets_C3->SetBorderSize(0);
  leg_fakeJets_C3->SetTextSize(0.045);
  leg_fakeJets_C3->AddEntry(h_C3_clone,"PbPb MinBias 30-50%");
  leg_fakeJets_C3->AddEntry(h_fakeJets_C3_clone,"fake-jets, PYTHIA+HYDJET 30-50%");
  leg_fakeJets_C3->AddEntry(h_C3_sub,"Corrected PbPb MinBias 30-50%");
  leg_fakeJets_C3->Draw();

  pad_fakeJets_C3_lower->cd();
  r_C3_sub->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C3_sub->GetYaxis()->SetTitle("Corrected / Nominal");
  r_C3_sub->GetXaxis()->SetLabelSize(0.06);
  r_C3_sub->GetXaxis()->SetTitleSize(0.07);
  r_C3_sub->GetYaxis()->SetLabelSize(0.06);
  r_C3_sub->GetYaxis()->SetTitleSize(0.07);
  r_C3_sub->SetTitle("");
  r_C3_sub->SetStats(0);
  r_C3_sub->Draw("hist");
  ///////////////////////////////////////////////////////////////////////////////////////
  
  TH1D *h_C4_clone = (TH1D*) h_C4_jetMB->Clone("h_C4_clone");
  TH1D *h_fakeJets_C4_clone = (TH1D*) h_fakeJets_C4->Clone("h_fakeJets_C4_clone");
  TH1D *h_C4_sub = (TH1D*) h_C4_jetMB->Clone("h_C4_sub");
  h_C4_sub->Add(h_fakeJets_C4,-1);
  h_C4_clone->SetLineColor(kBlack);
  h_fakeJets_C4_clone->SetLineColor(kGray+1);
  h_C4_sub->SetLineColor(kBlack);
  h_fakeJets_C4_clone->SetLineStyle(1);
  h_C4_sub->SetLineStyle(7);
  h_C4_clone->SetLineWidth(2);
  h_fakeJets_C4_clone->SetLineWidth(2);
  h_C4_sub->SetLineWidth(2);

  TH1D *r_C4_sub = (TH1D*) h_C4_sub->Clone("r_C4_sub");
  r_C4_sub->Divide(h_C4_sub,h_C4_clone,1,1,"B");

  TCanvas *canv_fakeJets_C4 = new TCanvas("canv_fakeJets_C4","canv_fakeJets_C4",700,700);
  canv_fakeJets_C4->cd();
  TPad *pad_fakeJets_C4_upper = new TPad("pad_fakeJets_C4_upper","pad_fakeJets_C4_upper",0,0.4,1,1);
  TPad *pad_fakeJets_C4_lower = new TPad("pad_fakeJets_C4_lower","pad_fakeJets_C4_lower",0,0,1,0.4);
  pad_fakeJets_C4_upper->SetLeftMargin(0.15);
  pad_fakeJets_C4_lower->SetLeftMargin(0.15);
  pad_fakeJets_C4_upper->SetBottomMargin(0.);
  pad_fakeJets_C4_lower->SetBottomMargin(0.18);
  pad_fakeJets_C4_upper->SetTopMargin(0.15);
  pad_fakeJets_C4_lower->SetTopMargin(0.);
  pad_fakeJets_C4_upper->SetLogy();
  pad_fakeJets_C4_upper->Draw();
  pad_fakeJets_C4_lower->Draw();
  pad_fakeJets_C4_upper->cd();
  h_C4_clone->SetStats(0);
  h_C4_clone->SetTitle("");
  h_C4_clone->GetYaxis()->SetLabelSize(0.045);
  h_C4_clone->GetYaxis()->SetTitleSize(0.055);
  h_C4_clone->GetYaxis()->SetTitle("#frac{1}{#it{N}^{evt}} #frac{d#it{N}^{jet}}{d#it{p}_{T}} [GeV^{-1}]");
  h_C4_clone->Draw("hist");
  h_fakeJets_C4_clone->Draw("hist same");
  h_C4_sub->Draw("hist same");
  TLegend *leg_fakeJets_C4 = new TLegend(0.3,0.7,0.7,0.84);
  leg_fakeJets_C4->SetBorderSize(0);
  leg_fakeJets_C4->SetTextSize(0.045);
  leg_fakeJets_C4->AddEntry(h_C4_clone,"PbPb MinBias 50-80%");
  leg_fakeJets_C4->AddEntry(h_fakeJets_C4_clone,"fake-jets, PYTHIA+HYDJET 50-80%");
  leg_fakeJets_C4->AddEntry(h_C4_sub,"Corrected PbPb MinBias 50-80%");
  leg_fakeJets_C4->Draw();

  pad_fakeJets_C4_lower->cd();
  r_C4_sub->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C4_sub->GetYaxis()->SetTitle("Corrected / Nominal");
  r_C4_sub->GetXaxis()->SetLabelSize(0.06);
  r_C4_sub->GetXaxis()->SetTitleSize(0.07);
  r_C4_sub->GetYaxis()->SetLabelSize(0.06);
  r_C4_sub->GetYaxis()->SetTitleSize(0.07);
  r_C4_sub->SetTitle("");
  r_C4_sub->SetStats(0);
  r_C4_sub->Draw("hist");


  canv_fakeJets_C1->SaveAs("../../figures/JetsPerZ/fakeJets_C1.pdf");
  canv_fakeJets_C2->SaveAs("../../figures/JetsPerZ/fakeJets_C2.pdf");
  canv_fakeJets_C3->SaveAs("../../figures/JetsPerZ/fakeJets_C3.pdf");
  canv_fakeJets_C4->SaveAs("../../figures/JetsPerZ/fakeJets_C4.pdf");


  // h_C4_jetMB->Add(h_fakeJets_C4,-1);
  // h_C3_jetMB->Add(h_fakeJets_C3,-1);
  // h_C2_jetMB->Add(h_fakeJets_C2,-1);
  // h_C1_jetMB->Add(h_fakeJets_C1,-1);


  
  h_pp = (TH1D*) stitchSamples(h_pp_jetMB,h_fakeJets_C4, h_pp_jet60,h_pp_jet80,h_pp_jet100,1,0); // pp hist will ignore fakeJet entry
  h_C4 = (TH1D*) stitchSamples(h_C4_jetMB,h_fakeJets_C4, h_C4_jet60,h_C4_jet80,h_C4_jet100,0,1);
  h_C3 = (TH1D*) stitchSamples(h_C3_jetMB,h_fakeJets_C3, h_C3_jet60,h_C3_jet80,h_C3_jet100,0,1);
  h_C2 = (TH1D*) stitchSamples(h_C2_jetMB,h_fakeJets_C2, h_C2_jet60,h_C2_jet80,h_C2_jet100,0,1);
  h_C1 = (TH1D*) stitchSamples(h_C1_jetMB,h_fakeJets_C1, h_C1_jet60,h_C1_jet80,h_C1_jet100,0,1);

  // h_C4->Add(h_fakeJets_C4,-1);
  // h_C3->Add(h_fakeJets_C3,-1);
  // h_C2->Add(h_fakeJets_C2,-1);
  // h_C1->Add(h_fakeJets_C1,-1);



  
  file_PbPb_HardProbes_jet100->GetObject("h_vz_jet100_C4",h_vz_C4);
  file_PbPb_HardProbes_jet100->GetObject("h_vz_jet100_C3",h_vz_C3);
  file_PbPb_HardProbes_jet100->GetObject("h_vz_jet100_C2",h_vz_C2);
  file_PbPb_HardProbes_jet100->GetObject("h_vz_jet100_C1",h_vz_C1);

  // N_evt_pp = hiBin_pp->GetEntries();
  // N_evt_C4 = integrate(hiBin_PbPb,100,180);
  // N_evt_C3 = integrate(hiBin_PbPb,60,100);
  // N_evt_C2 = integrate(hiBin_PbPb,20,60);
  // N_evt_C1 = integrate(hiBin_PbPb,0,20);

  N_evt_pp = h_vz_pp->Integral();
  N_evt_C4 = h_vz_C4->Integral();
  N_evt_C3 = h_vz_C3->Integral();
  N_evt_C2 = h_vz_C2->Integral();
  N_evt_C1 = h_vz_C1->Integral();

  cout << "N_evt_pp = " << N_evt_pp << "\n";
  cout << "N_evt_C4 = " << N_evt_C4 << "\n";
  cout << "N_evt_C3 = " << N_evt_C3 << "\n";
  cout << "N_evt_C2 = " << N_evt_C2 << "\n";
  cout << "N_evt_C1 = " << N_evt_C1 << "\n";

  

  double jetConversion_C4 = h_C4_jet100->Integral(h_C4_jet100->FindBin(100),h_C4_jet100->FindBin(500)) / h_C4_jetMB->Integral(h_C4_jetMB->FindBin(100),h_C4_jetMB->FindBin(500)) ;
  double jetConversion_C3 = h_C3_jet100->Integral(h_C3_jet100->FindBin(100),h_C3_jet100->FindBin(500)) / h_C3_jetMB->Integral(h_C3_jetMB->FindBin(100),h_C3_jetMB->FindBin(500)) ;
  double jetConversion_C2 = h_C2_jet100->Integral(h_C2_jet100->FindBin(100),h_C2_jet100->FindBin(500)) / h_C2_jetMB->Integral(h_C2_jetMB->FindBin(100),h_C2_jetMB->FindBin(500)) ;
  double jetConversion_C1 = h_C1_jet100->Integral(h_C1_jet100->FindBin(100),h_C1_jet100->FindBin(500)) / h_C1_jetMB->Integral(h_C1_jetMB->FindBin(100),h_C1_jetMB->FindBin(500)) ;
  
  // h_fakeJets_C4->Scale(N_evt_C4 * jetConversion_C4);
  // h_fakeJets_C3->Scale(N_evt_C3 * jetConversion_C3);
  // h_fakeJets_C2->Scale(N_evt_C2 * jetConversion_C2);
  // h_fakeJets_C1->Scale(N_evt_C1 * jetConversion_C1);

  // normalizeToMatchHistogram(h_C4,h_fakeJets_C4);
  // normalizeToMatchHistogram(h_C3,h_fakeJets_C3);
  // normalizeToMatchHistogram(h_C2,h_fakeJets_C2);
  // normalizeToMatchHistogram(h_C1,h_fakeJets_C1);

  cout << "h_C1->Integral() = " << h_C4->Integral() << "\n";
  cout << "h_fakeJets_C1->Integral() = " << h_fakeJets_C4->Integral() << "\n";
  
  


  

  /////////////////////////////////////////////////////////////////////////////

  // // temporary correction due to unfinished foresting
  h_C4->Scale(1./0.975474377);
  h_C3->Scale(1./0.975474377);
  h_C2->Scale(1./0.975474377);
  h_C1->Scale(1./0.975474377);

  // h_C4->Add(h_fakeJets_C4,-1);
  // h_C3->Add(h_fakeJets_C3,-1);
  // h_C2->Add(h_fakeJets_C2,-1);
  // h_C1->Add(h_fakeJets_C1,-1);


  

  TH2D *h_response_pp, *h_response_C4, *h_response_C3, *h_response_C2, *h_response_C1;
  file_PYTHIA_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets",h_response_pp);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",h_response_C4);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",h_response_C3);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",h_response_C2);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",h_response_C1);

  TH1D *h_meas_pp, *h_meas_C4, *h_meas_C3, *h_meas_C2, *h_meas_C1;
  TH1D *h_truth_pp, *h_truth_C4, *h_truth_C3, *h_truth_C2, *h_truth_C1;

  h_meas_pp = (TH1D*) h_response_pp->ProjectionX("h_meas_pp");
  h_meas_C4 = (TH1D*) h_response_C4->ProjectionX("h_meas_C4");
  h_meas_C3 = (TH1D*) h_response_C3->ProjectionX("h_meas_C3");
  h_meas_C2 = (TH1D*) h_response_C2->ProjectionX("h_meas_C2");
  h_meas_C1 = (TH1D*) h_response_C1->ProjectionX("h_meas_C1");

  h_truth_pp = (TH1D*) h_response_pp->ProjectionY("h_truth_pp");
  h_truth_C4 = (TH1D*) h_response_C4->ProjectionY("h_truth_C4");
  h_truth_C3 = (TH1D*) h_response_C3->ProjectionY("h_truth_C3");
  h_truth_C2 = (TH1D*) h_response_C2->ProjectionY("h_truth_C2");
  h_truth_C1 = (TH1D*) h_response_C1->ProjectionY("h_truth_C1");

  RooUnfoldResponse response_pp(h_meas_pp,h_truth_pp,h_response_pp,"response_pp","pp response",0);
  RooUnfoldResponse response_C4(h_meas_C4,h_truth_C4,h_response_C4,"response_C4","C4 response",0);
  RooUnfoldResponse response_C3(h_meas_C3,h_truth_C3,h_response_C3,"response_C3","C3 response",0);
  RooUnfoldResponse response_C2(h_meas_C2,h_truth_C2,h_response_C2,"response_C2","C2 response",0);
  RooUnfoldResponse response_C1(h_meas_C1,h_truth_C1,h_response_C1,"response_C1","C1 response",0);


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

  TH1D *h_pp_unfold, *h_C4_unfold, *h_C3_unfold, *h_C2_unfold, *h_C1_unfold;

  h_pp_unfold = (TH1D*) unfold_pp.Hunfold();
  h_C4_unfold = (TH1D*) unfold_C4.Hunfold();
  h_C3_unfold = (TH1D*) unfold_C3.Hunfold();
  h_C2_unfold = (TH1D*) unfold_C2.Hunfold();
  h_C1_unfold = (TH1D*) unfold_C1.Hunfold();

  // h_pp_unfold = (TH1D*) h_pp->Clone("h_pp_unfold");
  // h_C4_unfold = (TH1D*) h_C4->Clone("h_C4_unfold");
  // h_C3_unfold = (TH1D*) h_C3->Clone("h_C3_unfold");
  // h_C2_unfold = (TH1D*) h_C2->Clone("h_C2_unfold");
  // h_C1_unfold = (TH1D*) h_C1->Clone("h_C1_unfold");

  stylizeHistograms(h_pp_unfold,h_C1_unfold,h_C2_unfold,h_C3_unfold,h_C4_unfold);

  TLegend *leg = new TLegend(0.3,0.7,0.68,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  // leg->AddEntry(r_mcBJetPt_pp,"PYTHIA","l");
  // leg->AddEntry(h_jetPt_pp,"pp","p");
  leg->AddEntry(h_C4_unfold,"PbPb 50-80%","p");  
  leg->AddEntry(h_C3_unfold,"PbPb 30-50%","p");
  leg->AddEntry(h_C2_unfold,"PbPb 10-30%","p");
  leg->AddEntry(h_C1_unfold,"PbPb 0-10%","p");

  //leg->AddEntry(h_C1_unfold,"PbPb 0-10%, this analysis","p");
  //leg->AddEntry(h_pub_C1,"PbPb 0-10%, CMS","p");
  //leg->AddEntry(h_pub_C1,"PbPb 0-10%, ATLAS","p");

  // leg->AddEntry(h_C2_unfold,"PbPb 10-30%, this analysis","p");
  // leg->AddEntry(h_pub_C2,"PbPb 10-30%, CMS","p");
  // leg->AddEntry(h_pub_C2,"PbPb 10-20%, ATLAS","p");

  // leg->AddEntry(h_C3_unfold,"PbPb 30-50%, this analysis","p");
  // leg->AddEntry(h_pub_C3,"PbPb 30-50%, CMS","p");
  // leg->AddEntry(h_pub_C3,"PbPb 30-40%, ATLAS","p");  

  // leg->AddEntry(h_C4_unfold,"PbPb 50-80%, this analysis","p");
  // leg->AddEntry(h_pub_C4,"PbPb 50-90%, CMS","p");
  // leg->AddEntry(h_pub_C4,"PbPb 50-60%, ATLAS","p");  
  
  // file_PbPb_MinBias->GetObject("h_vz_C4",h_vz_C4);
  // file_PbPb_MinBias->GetObject("h_vz_C3",h_vz_C3);
  // file_PbPb_MinBias->GetObject("h_vz_C2",h_vz_C2);
  // file_PbPb_MinBias->GetObject("h_vz_C1",h_vz_C1);

  // file_PbPb_HardProbes->GetObject("h_vz_jet100_withJetAbove130_C4",h_vz_C4);
  // file_PbPb_HardProbes->GetObject("h_vz_jet100_withJetAbove130_C3",h_vz_C3);
  // file_PbPb_HardProbes->GetObject("h_vz_jet100_withJetAbove130_C2",h_vz_C2);
  // file_PbPb_HardProbes->GetObject("h_vz_jet100_withJetAbove130_C1",h_vz_C1);

  

  // rebin
  // const int N_edge = 4;
  // double newAxis[N_edge] = {120,150,200,300};

  // const int N_edge = 23;
  // double newAxis[N_edge] = {100,105,110,115,120,125,130,135,140,145,150,160,170,180,190,200,220,240,260,280,300,350,400};

  const int N_edge = 32;
  double newAxis[N_edge] = {60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,160,170,180,190,200,220,240,260,280,300,350,400,500};

  h_pp_unfold = (TH1D*) h_pp_unfold->Rebin(N_edge-1,"h_pp_unfold",newAxis);
  divideByBinwidth(h_pp_unfold); // pT normalization
  h_pp_unfold->Scale(1./3.2); // eta normalization
  
  h_C4_unfold = (TH1D*) h_C4_unfold->Rebin(N_edge-1,"h_C4_unfold",newAxis);
  divideByBinwidth(h_C4_unfold);
  h_C4_unfold->Scale(1./3.2); // eta normalization

  h_C3_unfold = (TH1D*) h_C3_unfold->Rebin(N_edge-1,"h_C3_unfold",newAxis);
  divideByBinwidth(h_C3_unfold);
  h_C3_unfold->Scale(1./3.2); // eta normalization

  h_C2_unfold = (TH1D*) h_C2_unfold->Rebin(N_edge-1,"h_C2_unfold",newAxis);
  divideByBinwidth(h_C2_unfold);
  h_C2_unfold->Scale(1./3.2); // eta normalization

  h_C1_unfold = (TH1D*) h_C1_unfold->Rebin(N_edge-1,"h_C1_unfold",newAxis);
  divideByBinwidth(h_C1_unfold);
  h_C1_unfold->Scale(1./3.2); // eta normalization

  h_pp = (TH1D*) h_pp->Rebin(N_edge-1,"h_pp",newAxis);
  divideByBinwidth(h_pp); // pT normalization
  h_pp->Scale(1./3.2); // eta normalization
  h_pp->Scale(1./h_pp->Integral());
  
  h_C4 = (TH1D*) h_C4->Rebin(N_edge-1,"h_C4",newAxis);
  divideByBinwidth(h_C4);
  h_C4->Scale(1./3.2); // eta normalization
  h_C4->Scale(1./h_C4->Integral());

  h_C3 = (TH1D*) h_C3->Rebin(N_edge-1,"h_C3",newAxis);
  divideByBinwidth(h_C3);
  h_C3->Scale(1./3.2); // eta normalization
  h_C3->Scale(1./h_C3->Integral());

  h_C2 = (TH1D*) h_C2->Rebin(N_edge-1,"h_C2",newAxis);
  divideByBinwidth(h_C2);
  h_C2->Scale(1./3.2); // eta normalization
  h_C2->Scale(1./h_C2->Integral());

  h_C1 = (TH1D*) h_C1->Rebin(N_edge-1,"h_C1",newAxis);
  divideByBinwidth(h_C1);
  h_C1->Scale(1./3.2); // eta normalization
  h_C1->Scale(1./h_C1->Integral());

  h_meas_pp = (TH1D*) h_meas_pp->Rebin(N_edge-1,"h_meas_pp",newAxis);
  divideByBinwidth(h_meas_pp); // pT normalization
  h_meas_pp->Scale(1./3.2); // eta normalization
  h_meas_pp->Scale(1./h_meas_pp->Integral());
  
  h_meas_C4 = (TH1D*) h_meas_C4->Rebin(N_edge-1,"h_meas_C4",newAxis);
  divideByBinwidth(h_meas_C4);
  h_meas_C4->Scale(1./3.2); // eta normalization
  h_meas_C4->Scale(1./h_meas_C4->Integral());

  h_meas_C3 = (TH1D*) h_meas_C3->Rebin(N_edge-1,"h_meas_C3",newAxis);
  divideByBinwidth(h_meas_C3);
  h_meas_C3->Scale(1./3.2); // eta normalization
  h_meas_C3->Scale(1./h_meas_C3->Integral());

  h_meas_C2 = (TH1D*) h_meas_C2->Rebin(N_edge-1,"h_meas_C2",newAxis);
  divideByBinwidth(h_meas_C2);
  h_meas_C2->Scale(1./3.2); // eta normalization
  h_meas_C2->Scale(1./h_meas_C2->Integral());

  h_meas_C1 = (TH1D*) h_meas_C1->Rebin(N_edge-1,"h_meas_C1",newAxis);
  divideByBinwidth(h_meas_C1);
  h_meas_C1->Scale(1./3.2); // eta normalization
  h_meas_C1->Scale(1./h_meas_C1->Integral());
  
  // // per-event/luminosity normalization
  // h_pp_unfold->Scale(1./(299490.144921629071)); // luminosity scale [1/nb]
  // h_C4_unfold->Scale(1./(N_evt_C4*minBiasEquivalentEventConversion_C4));
  // h_C3_unfold->Scale(1./(N_evt_C3*minBiasEquivalentEventConversion_C3));
  // h_C2_unfold->Scale(1./(N_evt_C2*minBiasEquivalentEventConversion_C2));
  // h_C1_unfold->Scale(1./(N_evt_C1*minBiasEquivalentEventConversion_C1));

  // // T_AA normalization
  // //h_C4->Scale(1./(0.440E-6)); // TAA scale [nb]
  // h_C4_unfold->Scale(1./(0.7452E-6)); // TAA scale [nb]
  // h_C3_unfold->Scale(1./(3.95E-6));
  // h_C2_unfold->Scale(1./(11.60E-6));
  // h_C1_unfold->Scale(1./(23.05E-6));

  // // Z boson normalization
  double NZ_pp = h_dimuonMass_pp->Integral(h_dimuonMass_pp->GetXaxis()->FindBin(75),h_dimuonMass_pp->GetXaxis()->FindBin(105));
  double NZ_C4 = h_dimuonMass_C4->Integral(h_dimuonMass_C4->GetXaxis()->FindBin(75),h_dimuonMass_C4->GetXaxis()->FindBin(105));
  double NZ_C3 = h_dimuonMass_C3->Integral(h_dimuonMass_C3->GetXaxis()->FindBin(75),h_dimuonMass_C3->GetXaxis()->FindBin(105));
  double NZ_C2 = h_dimuonMass_C2->Integral(h_dimuonMass_C2->GetXaxis()->FindBin(75),h_dimuonMass_C2->GetXaxis()->FindBin(105));
  double NZ_C1 = h_dimuonMass_C1->Integral(h_dimuonMass_C1->GetXaxis()->FindBin(75),h_dimuonMass_C1->GetXaxis()->FindBin(105));

  // scale by muon reconstruction efficiency
  NZ_pp = NZ_pp/(0.9708*0.9708);
  NZ_C4 = NZ_C4/(0.9778*0.9778);
  NZ_C3 = NZ_C3/(0.9856*0.9856);
  NZ_C2 = NZ_C2/(0.9069*0.9069);
  NZ_C1 = NZ_C1/(0.8627*0.8627);

  // scale by events not present  in the PromptReco PbPb SingleMuon dataset.
  // will not need this when I do the proper reforest
  // NZ_C4 = NZ_C4/(41./56.);
  // NZ_C3 = NZ_C3/(41./56.);
  // NZ_C2 = NZ_C2/(41./56.);
  // NZ_C1 = NZ_C1/(41./56.);

  cout << "NZ_pp = " << NZ_pp << "\n";
  cout << "NZ_C4 = " << NZ_C4 << "\n";
  cout << "NZ_C3 = " << NZ_C3 << "\n";
  cout << "NZ_C2 = " << NZ_C2 << "\n";
  cout << "NZ_C1 = " << NZ_C1 << "\n";

  h_pp_unfold->Scale(1./NZ_pp);
  h_C4_unfold->Scale(1./NZ_C4);
  h_C3_unfold->Scale(1./NZ_C3);
  h_C2_unfold->Scale(1./NZ_C2);
  h_C1_unfold->Scale(1./NZ_C1);

  // scale by forest inefficiency in HardProbes.
  // reforesting as to not need this term, but for now this is a quick fix
  // h_C4_unfold->Scale(1./0.897);
  // h_C3_unfold->Scale(1./0.897);
  // h_C2_unfold->Scale(1./0.897);
  // h_C1_unfold->Scale(1./0.897);



  // T_AA normalization alternative method (Ncoll / sigma_tot)
  // double sigma_tot = h_pp->Integral(h_pp->FindBin(120.),h_pp->FindBin(500.));
  // h_C4->Scale(1./(30.76/sigma_tot)); // TAA scale [nb]
  // h_C3->Scale(1./(267./sigma_tot));
  // h_C2->Scale(1./(805./sigma_tot));
  // h_C1->Scale(1./(1630./sigma_tot));


  const int N_coarseAxis = 8;
  double coarseAxis[N_coarseAxis] = {80,90,100,120,150,200,300,500};

  TH1D *h_pp_unfold_r = (TH1D*) h_pp_unfold->Clone("h_pp_unfold_r");
  h_pp_unfold_r = (TH1D*) h_pp_unfold_r->Rebin(N_coarseAxis-1,"h_pp_unfold_r",coarseAxis);
  divideByBinwidth(h_pp_unfold_r);

  TH1D *h_C4_unfold_r = (TH1D*) h_C4_unfold->Clone("h_C4_unfold_r");
  h_C4_unfold_r = (TH1D*) h_C4_unfold_r->Rebin(N_coarseAxis-1,"h_C4_unfold_r",coarseAxis);
  divideByBinwidth(h_C4_unfold_r);

  TH1D *h_C3_unfold_r = (TH1D*) h_C3_unfold->Clone("h_C3_unfold_r");
  h_C3_unfold_r = (TH1D*) h_C3_unfold_r->Rebin(N_coarseAxis-1,"h_C3_unfold_r",coarseAxis);
  divideByBinwidth(h_C3_unfold_r);

  TH1D *h_C2_unfold_r = (TH1D*) h_C2_unfold->Clone("h_C2_unfold_r");
  h_C2_unfold_r = (TH1D*) h_C2_unfold_r->Rebin(N_coarseAxis-1,"h_C2_unfold_r",coarseAxis);
  divideByBinwidth(h_C2_unfold_r);

  TH1D *h_C1_unfold_r = (TH1D*) h_C1_unfold->Clone("h_C1_unfold_r");
  h_C1_unfold_r = (TH1D*) h_C1_unfold_r->Rebin(N_coarseAxis-1,"h_C1_unfold_r",coarseAxis);
  divideByBinwidth(h_C1_unfold_r);  


  r_C4 = (TH1D*) h_C4_unfold->Clone("r_C4");
  r_C4->Divide(h_C4_unfold,h_pp_unfold,1,1,"");

  r_C3 = (TH1D*) h_C3_unfold->Clone("r_C3");
  r_C3->Divide(h_C3_unfold,h_pp_unfold,1,1,"");

  r_C2 = (TH1D*) h_C2_unfold->Clone("r_C2");
  r_C2->Divide(h_C2_unfold,h_pp_unfold,1,1,"");

  r_C1 = (TH1D*) h_C1_unfold->Clone("r_C1");
  r_C1->Divide(h_C1_unfold,h_pp_unfold,1,1,"");


  TH1D *r_C4_r = (TH1D*) h_C4_unfold_r->Clone("r_C4_r");
  r_C4_r->Divide(h_C4_unfold_r,h_pp_unfold_r,1,1,"");

  TH1D *r_C3_r = (TH1D*) h_C3_unfold_r->Clone("r_C3_r");
  r_C3_r->Divide(h_C3_unfold_r,h_pp_unfold_r,1,1,"");

  TH1D *r_C2_r = (TH1D*) h_C2_unfold_r->Clone("r_C2_r");
  r_C2_r->Divide(h_C2_unfold_r,h_pp_unfold_r,1,1,"");

  TH1D *r_C1_r = (TH1D*) h_C1_unfold_r->Clone("r_C1_r");
  r_C1_r->Divide(h_C1_unfold_r,h_pp_unfold_r,1,1,"");



  TH1D *R_C4 = (TH1D*) r_C4->Clone("R_C4");
  TH1D *R_C3 = (TH1D*) r_C3->Clone("R_C3");
  TH1D *R_C2 = (TH1D*) r_C2->Clone("R_C2");
  TH1D *R_C1 = (TH1D*) r_C1->Clone("R_C1");

  TH1D *R_C4_r = (TH1D*) r_C4_r->Clone("R_C4_r");
  TH1D *R_C3_r = (TH1D*) r_C3_r->Clone("R_C3_r");
  TH1D *R_C2_r = (TH1D*) r_C2_r->Clone("R_C2_r");
  TH1D *R_C1_r = (TH1D*) r_C1_r->Clone("R_C1_r");

  for(int i = 0; i < R_C4->GetSize(); i++){
    R_C4->SetBinError(i,1./TMath::Sqrt(NZ_C4));
    R_C3->SetBinError(i,1./TMath::Sqrt(NZ_C3));
    R_C2->SetBinError(i,1./TMath::Sqrt(NZ_C2));
    R_C1->SetBinError(i,1./TMath::Sqrt(NZ_C1));

    R_C4_r->SetBinError(i,1./TMath::Sqrt(NZ_C4));
    R_C3_r->SetBinError(i,1./TMath::Sqrt(NZ_C3));
    R_C2_r->SetBinError(i,1./TMath::Sqrt(NZ_C2));
    R_C1_r->SetBinError(i,1./TMath::Sqrt(NZ_C1));
  }

  stylizeSystematics(R_C1,R_C2,R_C3,R_C4);
  stylizeSystematics(R_C1_r,R_C2_r,R_C3_r,R_C4_r);
  

  // TLegend *leg = new TLegend(0.2,0.2,0.4,0.4);
  // leg->SetBorderSize(0);
  // leg->SetTextSize(0.033);
  // leg->AddEntry(h_pp_unfold,"pp","l");
  // leg->AddEntry(h_C4_unfold,"PbPb 50-80%","l");
  // leg->AddEntry(h_C3_unfold,"PbPb 30-50%","l");
  // leg->AddEntry(h_C2_unfold,"PbPb 10-30%","l");
  // leg->AddEntry(h_C1_unfold,"PbPb 0-10%","l");


  TCanvas *canv_prime = new TCanvas("canv_prime","canv_prime",700,700);
  canv_prime->cd();
  TPad *pad_prime = new TPad("pad_prime","pad_prime",0,0,1,1);
  pad_prime->SetLeftMargin(0.2);
  pad_prime->SetBottomMargin(0.15);
  //  pad->SetLogy();
  //pad->SetLogx();
  pad_prime->Draw();
  pad_prime->cd();
  R_C1->SetTitle("");
  R_C1->SetStats(0);
  R_C1->GetYaxis()->SetTitleOffset(2.0);
  //R_C1->GetYaxis()->SetTitle("#it{R}_{AA}^{jet}");
  R_C1->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  R_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //R_C1->GetYaxis()->SetRangeUser(0,1.);
  R_C1->GetYaxis()->SetRangeUser(0,2.);
  R_C1->GetXaxis()->SetRangeUser(newAxis[0],newAxis[N_edge-1]);
  R_C1->Draw("e2");
  r_C1->Draw("same");
  R_C2->Draw("e2 same");
  r_C2->Draw("same");
  R_C3->Draw("e2 same");
  r_C3->Draw("same");
  R_C4->Draw("e2 same");
  r_C4->Draw("same");
  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(newAxis[0],1,newAxis[N_edge-1],1);
  leg->Draw();

  canv_prime->SaveAs("../../figures/JetsPerZ/JetsPerZ_lightJets.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_prime_r = new TCanvas("canv_prime_r","canv_prime_r",700,700);
  canv_prime_r->cd();
  TPad *pad_prime_r = new TPad("pad_prime_r","pad_prime_r",0,0,1,1);
  pad_prime_r->SetLeftMargin(0.2);
  pad_prime_r->SetBottomMargin(0.15);
  //  pad->SetLogy();
  //pad->SetLogx();
  pad_prime_r->Draw();
  pad_prime_r->cd();
  r_C1_r->SetTitle("");
  r_C1_r->SetStats(0);
  r_C1_r->GetYaxis()->SetTitleOffset(2.0);
  //r_C1->GetYaxis()->SetTitle("#it{R}_{AA}^{jet}");
  r_C1_r->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  r_C1_r->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //r_C1->GetYaxis()->SetRangeUser(0,1.);
  r_C1_r->GetYaxis()->SetRangeUser(0,2.);
  //r_C1_r->GetXaxis()->SetRangeUser(coarseAxis[0],coarseAxis[N_coarseAxis-1]);
  r_C1_r->GetXaxis()->SetRangeUser(80,300);
  //R_C1_r->Draw("e2");
  //r_C1_r->Draw("same");
  r_C1_r->Draw();
  //R_C2_r->Draw("e2 same");
  r_C2_r->Draw("same");
  //R_C3_r->Draw("e2 same");
  r_C3_r->Draw("same");
  //R_C4_r->Draw("e2 same");
  r_C4_r->Draw("same");
  li->SetLineStyle(7);
  //li->DrawLine(coarseAxis[0],1,coarseAxis[N_coarseAxis-1],1);
  li->DrawLine(80,1,300,1);
  leg->Draw();

  canv_prime_r->SaveAs("../../figures/JetsPerZ/JetsPerZ_lightJets_rebinned.pdf");
  TFile *file_JetsPerZ_lightJets_rebinned = (TFile*) TFile::Open("./rootFiles/JetsPerZ/histograms_JetsPerZ_lightJets_rebinned.root","recreate");
  r_C4_r->Write();
  r_C3_r->Write();
  r_C2_r->Write();
  r_C1_r->Write();
  file_JetsPerZ_lightJets_rebinned->Close();

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_compareToPub_C1 = new TCanvas("canv_compareToPub_C1","canv_compareToPub_C1",700,700);
  canv_compareToPub_C1->cd();
  TPad *pad_compareToPub_C1 = new TPad("pad_compareToPub_C1","pad_compareToPub_C1",0,0,1,1);
  pad_compareToPub_C1->SetLeftMargin(0.2);
  pad_compareToPub_C1->SetBottomMargin(0.15);
  //  pad->SetLogy();
  //pad->SetLogx();
  pad_compareToPub_C1->Draw();
  pad_compareToPub_C1->cd();
  R_C1->SetTitle("");
  R_C1->SetStats(0);
  R_C1->GetYaxis()->SetTitleOffset(2.0);
  //R_C1->GetYaxis()->SetTitle("#it{R}_{AA}^{jet}");
  R_C1->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  R_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //R_C1->GetYaxis()->SetRangeUser(0,1.);
  R_C1->GetYaxis()->SetRangeUser(0,2.);
  R_C1->GetXaxis()->SetRangeUser(newAxis[0],newAxis[N_edge-1]);
  R_C1->Draw("e2");
  r_C1->Draw("same");
  h_pubCMS_C1->Draw("same");
  h_pubATLAS_C1->Draw("same");
  TLegend *leg_compareToPub_C1 = new TLegend(0.3,0.7,0.68,0.88);
  leg_compareToPub_C1->SetBorderSize(0);
  leg_compareToPub_C1->SetTextSize(0.04);
  leg_compareToPub_C1->AddEntry(r_C1,"CMS 0-10%, this study","p");
  leg_compareToPub_C1->AddEntry(h_pubCMS_C1,"CMS 0-10%, published","p");
  leg_compareToPub_C1->AddEntry(h_pubATLAS_C1,"ATLAS 0-10%, published","p");
  leg_compareToPub_C1->Draw();
  canv_compareToPub_C1->SaveAs("../../figures/JetsPerZ/JetsPerZ_lightJets_compareToPublished_C1.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_compareToPub_C2 = new TCanvas("canv_compareToPub_C2","canv_compareToPub_C2",700,700);
  canv_compareToPub_C2->cd();
  TPad *pad_compareToPub_C2 = new TPad("pad_compareToPub_C2","pad_compareToPub_C2",0,0,1,1);
  pad_compareToPub_C2->SetLeftMargin(0.2);
  pad_compareToPub_C2->SetBottomMargin(0.15);
  //  pad->SetLogy();
  //pad->SetLogx();
  pad_compareToPub_C2->Draw();
  pad_compareToPub_C2->cd();
  R_C2->SetTitle("");
  R_C2->SetStats(0);
  R_C2->GetYaxis()->SetTitleOffset(2.0);
  //R_C2->GetYaxis()->SetTitle("#it{R}_{AA}^{jet}");
  R_C2->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  R_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //R_C2->GetYaxis()->SetRangeUser(0,1.);
  R_C2->GetYaxis()->SetRangeUser(0,2.);
  R_C2->GetXaxis()->SetRangeUser(newAxis[0],newAxis[N_edge-1]);
  R_C2->Draw("e2");
  r_C2->Draw("same");
  h_pubCMS_C2->Draw("same");
  h_pubATLAS_C2->Draw("same");
  TLegend *leg_compareToPub_C2 = new TLegend(0.3,0.7,0.68,0.88);
  leg_compareToPub_C2->SetBorderSize(0);
  leg_compareToPub_C2->SetTextSize(0.04);
  leg_compareToPub_C2->AddEntry(r_C2,"CMS 10-30%, this study","p");
  leg_compareToPub_C2->AddEntry(h_pubCMS_C2,"CMS 10-30%, published","p");
  leg_compareToPub_C2->AddEntry(h_pubATLAS_C2,"ATLAS 10-20%, published","p");
  leg_compareToPub_C2->Draw();
  canv_compareToPub_C2->SaveAs("../../figures/JetsPerZ/JetsPerZ_lightJets_compareToPublished_C2.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_compareToPub_C3 = new TCanvas("canv_compareToPub_C3","canv_compareToPub_C3",700,700);
  canv_compareToPub_C3->cd();
  TPad *pad_compareToPub_C3 = new TPad("pad_compareToPub_C3","pad_compareToPub_C3",0,0,1,1);
  pad_compareToPub_C3->SetLeftMargin(0.2);
  pad_compareToPub_C3->SetBottomMargin(0.15);
  //  pad->SetLogy();
  //pad->SetLogx();
  pad_compareToPub_C3->Draw();
  pad_compareToPub_C3->cd();
  R_C3->SetTitle("");
  R_C3->SetStats(0);
  R_C3->GetYaxis()->SetTitleOffset(2.0);
  //R_C3->GetYaxis()->SetTitle("#it{R}_{AA}^{jet}");
  R_C3->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  R_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //R_C3->GetYaxis()->SetRangeUser(0,1.);
  R_C3->GetYaxis()->SetRangeUser(0,2.);
  R_C3->GetXaxis()->SetRangeUser(newAxis[0],newAxis[N_edge-1]);
  R_C3->Draw("e2");
  r_C3->Draw("same");
  h_pubCMS_C3->Draw("same");
  h_pubATLAS_C3->Draw("same");
  TLegend *leg_compareToPub_C3 = new TLegend(0.3,0.7,0.68,0.88);
  leg_compareToPub_C3->SetBorderSize(0);
  leg_compareToPub_C3->SetTextSize(0.04);
  leg_compareToPub_C3->AddEntry(r_C3,"CMS 30-50%, this study","p");
  leg_compareToPub_C3->AddEntry(h_pubCMS_C3,"CMS 30-50%, published","p");
  leg_compareToPub_C3->AddEntry(h_pubATLAS_C3,"ATLAS 30-40%, published","p");
  leg_compareToPub_C3->Draw();
  canv_compareToPub_C3->SaveAs("../../figures/JetsPerZ/JetsPerZ_lightJets_compareToPublished_C3.pdf");
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_compareToPub_C4 = new TCanvas("canv_compareToPub_C4","canv_compareToPub_C4",700,700);
  canv_compareToPub_C4->cd();
  TPad *pad_compareToPub_C4 = new TPad("pad_compareToPub_C4","pad_compareToPub_C4",0,0,1,1);
  pad_compareToPub_C4->SetLeftMargin(0.2);
  pad_compareToPub_C4->SetBottomMargin(0.15);
  //  pad->SetLogy();
  //pad->SetLogx();
  pad_compareToPub_C4->Draw();
  pad_compareToPub_C4->cd();
  R_C4->SetTitle("");
  R_C4->SetStats(0);
  R_C4->GetYaxis()->SetTitleOffset(2.0);
  //R_C4->GetYaxis()->SetTitle("#it{R}_{AA}^{jet}");
  R_C4->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  R_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //R_C4->GetYaxis()->SetRangeUser(0,1.);
  R_C4->GetYaxis()->SetRangeUser(0,2.);
  R_C4->GetXaxis()->SetRangeUser(newAxis[0],newAxis[N_edge-1]);
  R_C4->Draw("e2");
  r_C4->Draw("same");
  h_pubCMS_C4->Draw("same");
  h_pubATLAS_C4->Draw("same");
  TLegend *leg_compareToPub_C4 = new TLegend(0.3,0.7,0.68,0.88);
  leg_compareToPub_C4->SetBorderSize(0);
  leg_compareToPub_C4->SetTextSize(0.04);
  leg_compareToPub_C4->AddEntry(r_C4,"CMS 50-80%, this study","p");
  leg_compareToPub_C4->AddEntry(h_pubCMS_C4,"CMS 50-80%, published","p");
  leg_compareToPub_C4->AddEntry(h_pubATLAS_C4,"ATLAS 50-60%, published","p");
  leg_compareToPub_C4->Draw();
  canv_compareToPub_C4->SaveAs("../../figures/JetsPerZ/JetsPerZ_lightJets_compareToPublished_C4.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // take ratio of starting reco spectra data/mc (must be approx equal for unfolding to be correct)
  TH1D *ratio_pp = (TH1D*) h_pp->Clone("ratio_pp");
  ratio_pp->Divide(h_pp,h_meas_pp,1,1,"");
  

  TCanvas *canv_compareSpectra_pp = new TCanvas("canv_compareSpectra_pp","canv_compareSpectra_pp",700,700);
  canv_compareSpectra_pp->cd();
  TPad *pad_upper_compareSpectra_pp = new TPad("pad_upper_compareSpectra_pp","pad_upper_compareSpectra_pp",0,0.4,1,1);
  TPad *pad_lower_compareSpectra_pp = new TPad("pad_lower_compareSpectra_pp","pad_lower_compareSpectra_pp",0,0.,1,0.4);
  pad_upper_compareSpectra_pp->SetLeftMargin(0.2);
  pad_lower_compareSpectra_pp->SetLeftMargin(0.2);
  pad_upper_compareSpectra_pp->SetBottomMargin(0.);
  pad_lower_compareSpectra_pp->SetBottomMargin(0.15);
  pad_upper_compareSpectra_pp->SetTopMargin(0.15);
  pad_lower_compareSpectra_pp->SetTopMargin(0.);
  pad_upper_compareSpectra_pp->Draw();
  pad_lower_compareSpectra_pp->Draw();
  pad_upper_compareSpectra_pp->cd();
  h_pp->Draw();
  h_meas_pp->Draw("same");
  pad_lower_compareSpectra_pp->cd();
  ratio_pp->Draw();
  canv_compareSpectra_pp->SaveAs("../../figures/JetsPerZ/JetPT_dataVsMC_pp.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // take ratio of starting reco spectra data/mc (must be approx equal for unfolding to be correct)
  TH1D *ratio_C4 = (TH1D*) h_C4->Clone("ratio_C4");
  ratio_C4->Divide(h_C4,h_meas_C4,1,1,"");
  

  TCanvas *canv_compareSpectra_C4 = new TCanvas("canv_compareSpectra_C4","canv_compareSpectra_C4",700,700);
  canv_compareSpectra_C4->cd();
  TPad *pad_upper_compareSpectra_C4 = new TPad("pad_upper_compareSpectra_C4","pad_upper_compareSpectra_C4",0,0.4,1,1);
  TPad *pad_lower_compareSpectra_C4 = new TPad("pad_lower_compareSpectra_C4","pad_lower_compareSpectra_C4",0,0.,1,0.4);
  pad_upper_compareSpectra_C4->SetLeftMargin(0.2);
  pad_lower_compareSpectra_C4->SetLeftMargin(0.2);
  pad_upper_compareSpectra_C4->SetBottomMargin(0.);
  pad_lower_compareSpectra_C4->SetBottomMargin(0.15);
  pad_upper_compareSpectra_C4->SetTopMargin(0.15);
  pad_lower_compareSpectra_C4->SetTopMargin(0.);
  pad_upper_compareSpectra_C4->Draw();
  pad_lower_compareSpectra_C4->Draw();
  pad_upper_compareSpectra_C4->cd();
  h_C4->Draw();
  h_meas_pp->Draw("same");
  pad_lower_compareSpectra_C4->cd();
  ratio_C4->Draw();
  canv_compareSpectra_C4->SaveAs("../../figures/JetsPerZ/JetPT_dataVsMC_C4.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // take ratio of starting reco spectra data/mc (must be approx equal for unfolding to be correct)
  TH1D *ratio_C3 = (TH1D*) h_C3->Clone("ratio_C3");
  ratio_C3->Divide(h_C3,h_meas_C3,1,1,"");
  

  TCanvas *canv_compareSpectra_C3 = new TCanvas("canv_compareSpectra_C3","canv_compareSpectra_C3",700,700);
  canv_compareSpectra_C3->cd();
  TPad *pad_upper_compareSpectra_C3 = new TPad("pad_upper_compareSpectra_C3","pad_upper_compareSpectra_C3",0,0.4,1,1);
  TPad *pad_lower_compareSpectra_C3 = new TPad("pad_lower_compareSpectra_C3","pad_lower_compareSpectra_C3",0,0.,1,0.4);
  pad_upper_compareSpectra_C3->SetLeftMargin(0.2);
  pad_lower_compareSpectra_C3->SetLeftMargin(0.2);
  pad_upper_compareSpectra_C3->SetBottomMargin(0.);
  pad_lower_compareSpectra_C3->SetBottomMargin(0.15);
  pad_upper_compareSpectra_C3->SetTopMargin(0.15);
  pad_lower_compareSpectra_C3->SetTopMargin(0.);
  pad_upper_compareSpectra_C3->Draw();
  pad_lower_compareSpectra_C3->Draw();
  pad_upper_compareSpectra_C3->cd();
  h_C3->Draw();
  h_meas_pp->Draw("same");
  pad_lower_compareSpectra_C3->cd();
  ratio_C3->Draw();
  canv_compareSpectra_C3->SaveAs("../../figures/JetsPerZ/JetPT_dataVsMC_C3.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // take ratio of starting reco spectra data/mc (must be approx equal for unfolding to be correct)
  TH1D *ratio_C2 = (TH1D*) h_C2->Clone("ratio_C2");
  ratio_C2->Divide(h_C2,h_meas_C2,1,1,"");
  

  TCanvas *canv_compareSpectra_C2 = new TCanvas("canv_compareSpectra_C2","canv_compareSpectra_C2",700,700);
  canv_compareSpectra_C2->cd();
  TPad *pad_upper_compareSpectra_C2 = new TPad("pad_upper_compareSpectra_C2","pad_upper_compareSpectra_C2",0,0.4,1,1);
  TPad *pad_lower_compareSpectra_C2 = new TPad("pad_lower_compareSpectra_C2","pad_lower_compareSpectra_C2",0,0.,1,0.4);
  pad_upper_compareSpectra_C2->SetLeftMargin(0.2);
  pad_lower_compareSpectra_C2->SetLeftMargin(0.2);
  pad_upper_compareSpectra_C2->SetBottomMargin(0.);
  pad_lower_compareSpectra_C2->SetBottomMargin(0.15);
  pad_upper_compareSpectra_C2->SetTopMargin(0.15);
  pad_lower_compareSpectra_C2->SetTopMargin(0.);
  pad_upper_compareSpectra_C2->Draw();
  pad_lower_compareSpectra_C2->Draw();
  pad_upper_compareSpectra_C2->cd();
  h_C2->SetStats(0);
  h_C2->SetTitle("");
  h_C2->Draw();
  h_meas_pp->Draw("same");
  pad_lower_compareSpectra_C2->cd();
  ratio_C2->Draw();
  ratio_C2->SetStats(0);
  ratio_C2->SetTitle("");
  canv_compareSpectra_C2->SaveAs("../../figures/JetsPerZ/JetPT_dataVsMC_C2.pdf");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // take ratio of starting reco spectra data/mc (must be approx equal for unfolding to be correct)
  TH1D *ratio_C1 = (TH1D*) h_C1->Clone("ratio_C1");
  ratio_C1->Divide(h_C1,h_meas_C1,1,1,"");
  

  TCanvas *canv_compareSpectra_C1 = new TCanvas("canv_compareSpectra_C1","canv_compareSpectra_C1",700,700);
  canv_compareSpectra_C1->cd();
  TPad *pad_upper_compareSpectra_C1 = new TPad("pad_upper_compareSpectra_C1","pad_upper_compareSpectra_C1",0,0.4,1,1);
  TPad *pad_lower_compareSpectra_C1 = new TPad("pad_lower_compareSpectra_C1","pad_lower_compareSpectra_C1",0,0.,1,0.4);
  pad_upper_compareSpectra_C1->SetLeftMargin(0.2);
  pad_lower_compareSpectra_C1->SetLeftMargin(0.2);
  pad_upper_compareSpectra_C1->SetBottomMargin(0.);
  pad_lower_compareSpectra_C1->SetBottomMargin(0.15);
  pad_upper_compareSpectra_C1->SetTopMargin(0.15);
  pad_lower_compareSpectra_C1->SetTopMargin(0.);
  pad_upper_compareSpectra_C1->Draw();
  pad_lower_compareSpectra_C1->Draw();
  pad_upper_compareSpectra_C1->cd();
  h_C1->SetStats(0);
  h_C1->SetTitle("");
  h_C1->Draw();
  h_meas_pp->Draw("same");
  pad_lower_compareSpectra_C1->cd();
  ratio_C1->SetStats(0);
  ratio_C1->SetTitle("");
  ratio_C1->Draw();
  canv_compareSpectra_C1->SaveAs("../../figures/JetsPerZ/JetPT_dataVsMC_C1.pdf");


  //////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_comparePubSpectra_pp = new TCanvas("canv_comparePubSpectra_pp","canv_comparePubSpectra_pp",700,700);
  canv_comparePubSpectra_pp->cd();
  TPad *pad_upper_comparePubSpectra_pp = new TPad("pad_upper_comparePubSpectra_pp","pad_upper_comparePubSpectra_pp",0,0.4,1,1);
  TPad *pad_lower_comparePubSpectra_pp = new TPad("pad_lower_comparePubSpectra_pp","pad_lower_comparePubSpectra_pp",0,0.,1,0.4);
  pad_upper_comparePubSpectra_pp->SetLeftMargin(0.2);
  pad_lower_comparePubSpectra_pp->SetLeftMargin(0.2);
  pad_upper_comparePubSpectra_pp->SetBottomMargin(0.);
  pad_lower_comparePubSpectra_pp->SetBottomMargin(0.15);
  pad_upper_comparePubSpectra_pp->SetTopMargin(0.15);
  pad_lower_comparePubSpectra_pp->SetTopMargin(0.);
  pad_upper_comparePubSpectra_pp->SetLogy();
  pad_upper_comparePubSpectra_pp->Draw();
  pad_lower_comparePubSpectra_pp->Draw();
  pad_upper_comparePubSpectra_pp->cd();
  //h_pp_unfold->Scale(1./h_pp_unfold->Integral(h_pp_unfold->FindBin(100),h_pp_unfold->FindBin(500)));
  //h_pubATLAS_spectra_pp->Scale(1./h_pubATLAS_spectra_pp->Integral(h_pubATLAS_spectra_pp->FindBin(100),h_pubATLAS_spectra_pp->FindBin(500)));
  h_pp_unfold->Draw();
  h_pubATLAS_spectra_pp->Draw("same");


  
}
