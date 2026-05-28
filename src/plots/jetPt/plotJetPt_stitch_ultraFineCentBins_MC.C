#include "../../../headers/functions/divideByBinwidth.h"

TH1D* stitchSamples_alt(TH1D *h_jetMB, TH1D *h_jet60, TH1D *h_jet80, TH1D *h_jet100,
			bool isPP, bool isPbPb){

  std::cout << "Stitching samples (alt)...\n";

  TH1D *h_return = (TH1D*) h_jet100->Clone("h_return");
  
  TH1D *h_jet80_scaled = (TH1D*) h_jet80->Clone("h_jet80_scaled");
  TH1D *h_jet60_scaled = (TH1D*) h_jet60->Clone("h_jet60_scaled");
  TH1D *h_jetMB_scaled = (TH1D*) h_jetMB->Clone("h_jetMB_scaled");

  h_jet80_scaled->Scale(2.2560173);
  h_jet60_scaled->Scale(5.7724389);

  double jetMB_pTmin = 60.;
  double jet60_pTmin = 100;
  double jet80_pTmin = 130;
  double jet100_pTmin = 200;
  double smallShift = 0.01;

  if(!isPP){
    jet60_pTmin = jet80_pTmin;
  }

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


TH1D* stitchSamples(TH1D *h_jetMB, TH1D *h_jet60, TH1D *h_jet80, TH1D *h_jet100,
		    bool isPP, bool isPbPb){

  std::cout << "Stitching samples...\n";

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

  
  TH1D *h_jet80_scaled = (TH1D*) h_jet80->Clone("h_jet80_scaled");
  h_jet80_scaled->Scale(N_jet100 / N_jet80);
  std::cout << "Scaled jet80 by a factor F = " << N_jet100 / N_jet80 << "\n";

  double N_jet80_scaled = h_jet80_scaled->Integral(h_jet80_scaled->FindBin(jet80_pTmin + smallShift),h_jet80_scaled->FindBin(jet100_pTmin - smallShift));

  TH1D *h_jet60_scaled = (TH1D*) h_jet60->Clone("h_jet60_scaled");
  h_jet60_scaled->Scale(N_jet80_scaled / N_jet60);
  std::cout << "Scaled jet60 by a factor F = " << N_jet80_scaled / N_jet60 << "\n";
  
  double N_jet60_scaled = h_jet60_scaled->Integral(h_jet60_scaled->FindBin(jet60_pTmin + smallShift),h_jet60_scaled->FindBin(jet80_pTmin - smallShift));

  TH1D *h_jetMB_scaled = (TH1D*) h_jetMB->Clone("h_jetMB_scaled");
  h_jetMB_scaled->Scale(N_jet60_scaled / N_jetMB);
  std::cout << "Scaled jetMB by a factor F = " << N_jet60_scaled / N_jetMB << "\n";
  
 
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




void stylizeHistograms(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  h1->SetMarkerColor(kBlack);
  h2->SetMarkerColor(kRed-4);
  h3->SetMarkerColor(kBlue-4);
  h4->SetMarkerColor(kGreen+2);
  
  h1->SetLineColor(kBlack);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kBlue-4);
  h4->SetLineColor(kGreen+2);
  
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  
}


void plotJetPt_stitch_ultraFineCentBins_MC(){

  TLine *li = new TLine();

  TString fileString_PYTHIA = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-2-2.root";
  
  TFile *file_pp_HighEGJet_jet60 = TFile::Open(fileString_PYTHIA);
  TFile *file_pp_HighEGJet_jet80 = TFile::Open(fileString_PYTHIA);
  TFile *file_pp_HighEGJet_jet100 = TFile::Open(fileString_PYTHIA);
  TFile *file_pp_MinBias = TFile::Open(fileString_PYTHIA);
  


  //TString fileString_PYTHIAHYDJET = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-8_ultraFineCentBins.root";
  TString fileString_PYTHIAHYDJET = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-5-12_ultraFineCentBins.root";
  
  TFile *file_PbPb_HardProbes_jet60 = TFile::Open(fileString_PYTHIAHYDJET);
  TFile *file_PbPb_HardProbes_jet80 = TFile::Open(fileString_PYTHIAHYDJET);
  TFile *file_PbPb_HardProbes_jet100 = TFile::Open(fileString_PYTHIAHYDJET);
  TFile *file_PbPb_MinBias = TFile::Open(fileString_PYTHIAHYDJET);


  
  // // add unmatched jets
  // h_ppMC->Add(h_unmatched_ppMC);
  // h_C4MC->Add(h_unmatched_C4MC);
  // h_C3MC->Add(h_unmatched_C3MC);
  // h_C2MC->Add(h_unmatched_C2MC);
  // h_C1MC->Add(h_unmatched_C1MC);

  
  
  // ///// take ratio to PYTHIA gen
  // h_ppMC = (TH1D*) H_ppMC->ProjectionY("h_ppMC");
  // h_C4MC = (TH1D*) H_ppMC->ProjectionY("h_C4MC");
  // h_C3MC = (TH1D*) H_ppMC->ProjectionY("h_C3MC");
  // h_C2MC = (TH1D*) H_ppMC->ProjectionY("h_C2MC");
  // h_C1MC = (TH1D*) H_ppMC->ProjectionY("h_C1MC");



  // TH1D *bFrac_MinBias, *bFrac_DiJet;
  // file_bFrac_MinBias->GetObject("inclBFraction_pp",bFrac_MinBias);
  // file_bFrac_DiJet_jet60->GetObject("inclBFraction_pp",bFrac_DiJet);

  // stylizeHistograms(bFrac_MinBias,bFrac_DiJet);

  // bFrac_MinBias->Draw();
  // bFrac_DiJet->Draw("same");

  TH2D *H_pp, *H_C8, *H_C7, *H_C6, *H_C5, *H_C4, *H_C3, *H_C2, *H_C1;
  TH2D *H_pp_jetMB, *H_C8_jetMB, *H_C7_jetMB, *H_C6_jetMB, *H_C5_jetMB, *H_C4_jetMB, *H_C3_jetMB, *H_C2_jetMB, *H_C1_jetMB;
  TH2D *H_pp_jet60;
  TH2D *H_pp_jet80, *H_C8_jet80, *H_C7_jet80, *H_C6_jet80, *H_C5_jet80, *H_C4_jet80, *H_C3_jet80, *H_C2_jet80, *H_C1_jet80;
  TH2D *H_pp_jet100, *H_C8_jet100, *H_C7_jet100, *H_C6_jet100, *H_C5_jet100, *H_C4_jet100, *H_C3_jet100, *H_C2_jet100, *H_C1_jet100;

  TH1D *h_pp, *h_C8, *h_C7, *h_C6, *h_C5, *h_C4, *h_C3, *h_C2, *h_C1;
  TH1D *h_pp_jetMB, *h_C8_jetMB, *h_C7_jetMB, *h_C6_jetMB, *h_C5_jetMB, *h_C4_jetMB, *h_C3_jetMB, *h_C2_jetMB, *h_C1_jetMB;
  TH1D *h_pp_jet60;
  TH1D *h_pp_jet80, *h_C8_jet80, *h_C7_jet80, *h_C6_jet80, *h_C5_jet80, *h_C4_jet80, *h_C3_jet80, *h_C2_jet80, *h_C1_jet80;
  TH1D *h_pp_jet100, *h_C8_jet100, *h_C7_jet100, *h_C6_jet100, *h_C5_jet100, *h_C4_jet100, *h_C3_jet100, *h_C2_jet100, *h_C1_jet100;

  file_pp_MinBias->GetObject("h_inclRecoJetPt_flavor",H_pp_jetMB);
  file_pp_HighEGJet_jet60->GetObject("h_inclRecoJetPt_flavor",H_pp_jet60);
  file_pp_HighEGJet_jet80->GetObject("h_inclRecoJetPt_flavor",H_pp_jet80);
  file_pp_HighEGJet_jet100->GetObject("h_inclRecoJetPt_flavor",H_pp_jet100);

  h_pp_jetMB = (TH1D*) H_pp_jetMB->ProjectionX("h_pp_jetMB",H_pp_jetMB->GetYaxis()->FindBin(-5),H_pp_jetMB->GetYaxis()->FindBin(-1),"e");
  h_pp_jetMB->Add(H_pp_jetMB->ProjectionX("h_pp_jetMB_add",H_pp_jetMB->GetYaxis()->FindBin(-5),H_pp_jetMB->GetYaxis()->FindBin(-1),"e"));
  h_pp_jet60 = (TH1D*) H_pp_jet60->ProjectionX("h_pp_jet60",H_pp_jet60->GetYaxis()->FindBin(-5),H_pp_jet60->GetYaxis()->FindBin(-1),"e");
  h_pp_jet60->Add(H_pp_jet60->ProjectionX("h_pp_jet60_add",H_pp_jet60->GetYaxis()->FindBin(-5),H_pp_jet60->GetYaxis()->FindBin(-1),"e"));
  h_pp_jet80 = (TH1D*) H_pp_jet80->ProjectionX("h_pp_jet80",H_pp_jet80->GetYaxis()->FindBin(-5),H_pp_jet80->GetYaxis()->FindBin(-1),"e");
  h_pp_jet80->Add(H_pp_jet80->ProjectionX("h_pp_jet80_add",H_pp_jet80->GetYaxis()->FindBin(-5),H_pp_jet80->GetYaxis()->FindBin(-1),"e"));
  h_pp_jet100 = (TH1D*) H_pp_jet100->ProjectionX("h_pp_jet100",H_pp_jet100->GetYaxis()->FindBin(-5),H_pp_jet100->GetYaxis()->FindBin(-1),"e");
  h_pp_jet100->Add(H_pp_jet100->ProjectionX("h_pp_jet100_add",H_pp_jet100->GetYaxis()->FindBin(-5),H_pp_jet100->GetYaxis()->FindBin(-1),"e"));

  // file_PbPb_MinBias->GetObject("h_inclRecoJetPt_flavor_C8",H_C8_jetMB);
  // file_PbPb_MinBias->GetObject("h_inclRecoJetPt_flavor_C7",H_C7_jetMB);
  // file_PbPb_MinBias->GetObject("h_inclRecoJetPt_flavor_C6",H_C6_jetMB);
  // file_PbPb_MinBias->GetObject("h_inclRecoJetPt_flavor_C5",H_C5_jetMB);
  // file_PbPb_MinBias->GetObject("h_inclRecoJetPt_flavor_C4",H_C4_jetMB);
  // file_PbPb_MinBias->GetObject("h_inclRecoJetPt_flavor_C3",H_C3_jetMB);
  // file_PbPb_MinBias->GetObject("h_inclRecoJetPt_flavor_C2",H_C2_jetMB);
  // file_PbPb_MinBias->GetObject("h_inclRecoJetPt_flavor_C1",H_C1_jetMB);

  file_PbPb_MinBias->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C8",H_C8_jetMB);
  file_PbPb_MinBias->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C7",H_C7_jetMB);
  file_PbPb_MinBias->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C6",H_C6_jetMB);
  file_PbPb_MinBias->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C5",H_C5_jetMB);
  file_PbPb_MinBias->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",H_C4_jetMB);
  file_PbPb_MinBias->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",H_C3_jetMB);
  file_PbPb_MinBias->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H_C2_jetMB);
  file_PbPb_MinBias->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",H_C1_jetMB);

  // h_C8_jetMB = (TH1D*) H_C8_jetMB->ProjectionX("h_C8_jetMB",H_C8_jetMB->GetYaxis()->FindBin(-5),H_C8_jetMB->GetYaxis()->FindBin(-1),"e");
  // h_C8_jetMB->Add(H_C8_jetMB->ProjectionX("h_C8_jetMB_add",H_C8_jetMB->GetYaxis()->FindBin(-5),H_C8_jetMB->GetYaxis()->FindBin(-1),"e"));
  // h_C7_jetMB = (TH1D*) H_C7_jetMB->ProjectionX("h_C7_jetMB",H_C7_jetMB->GetYaxis()->FindBin(-5),H_C7_jetMB->GetYaxis()->FindBin(-1),"e");
  // h_C7_jetMB->Add(H_C7_jetMB->ProjectionX("h_C7_jetMB_add",H_C7_jetMB->GetYaxis()->FindBin(-5),H_C7_jetMB->GetYaxis()->FindBin(-1),"e"));
  // h_C6_jetMB = (TH1D*) H_C6_jetMB->ProjectionX("h_C6_jetMB",H_C6_jetMB->GetYaxis()->FindBin(-5),H_C6_jetMB->GetYaxis()->FindBin(-1),"e");
  // h_C6_jetMB->Add(H_C6_jetMB->ProjectionX("h_C6_jetMB_add",H_C6_jetMB->GetYaxis()->FindBin(-5),H_C6_jetMB->GetYaxis()->FindBin(-1),"e"));
  // h_C5_jetMB = (TH1D*) H_C5_jetMB->ProjectionX("h_C5_jetMB",H_C5_jetMB->GetYaxis()->FindBin(-5),H_C5_jetMB->GetYaxis()->FindBin(-1),"e");
  // h_C5_jetMB->Add(H_C5_jetMB->ProjectionX("h_C5_jetMB_add",H_C5_jetMB->GetYaxis()->FindBin(-5),H_C5_jetMB->GetYaxis()->FindBin(-1),"e"));
  // h_C4_jetMB = (TH1D*) H_C4_jetMB->ProjectionX("h_C4_jetMB",H_C4_jetMB->GetYaxis()->FindBin(-5),H_C4_jetMB->GetYaxis()->FindBin(-1),"e");
  // h_C4_jetMB->Add(H_C4_jetMB->ProjectionX("h_C4_jetMB_add",H_C4_jetMB->GetYaxis()->FindBin(-5),H_C4_jetMB->GetYaxis()->FindBin(-1),"e"));
  // h_C3_jetMB = (TH1D*) H_C3_jetMB->ProjectionX("h_C3_jetMB",H_C3_jetMB->GetYaxis()->FindBin(-5),H_C3_jetMB->GetYaxis()->FindBin(-1),"e");
  // h_C3_jetMB->Add(H_C3_jetMB->ProjectionX("h_C3_jetMB_add",H_C3_jetMB->GetYaxis()->FindBin(-5),H_C3_jetMB->GetYaxis()->FindBin(-1),"e"));
  // h_C2_jetMB = (TH1D*) H_C2_jetMB->ProjectionX("h_C2_jetMB",H_C2_jetMB->GetYaxis()->FindBin(-5),H_C2_jetMB->GetYaxis()->FindBin(-1),"e");
  // h_C2_jetMB->Add(H_C2_jetMB->ProjectionX("h_C2_jetMB_add",H_C2_jetMB->GetYaxis()->FindBin(-5),H_C2_jetMB->GetYaxis()->FindBin(-1),"e"));
  // h_C1_jetMB = (TH1D*) H_C1_jetMB->ProjectionX("h_C1_jetMB",H_C1_jetMB->GetYaxis()->FindBin(-5),H_C1_jetMB->GetYaxis()->FindBin(-1),"e");
  // h_C1_jetMB->Add(H_C1_jetMB->ProjectionX("h_C1_jetMB_add",H_C1_jetMB->GetYaxis()->FindBin(-5),H_C1_jetMB->GetYaxis()->FindBin(-1),"e"));

  h_C8_jetMB = (TH1D*) H_C8_jetMB->ProjectionX("h_C8_jetMB");
  h_C7_jetMB = (TH1D*) H_C7_jetMB->ProjectionX("h_C7_jetMB");
  h_C6_jetMB = (TH1D*) H_C6_jetMB->ProjectionX("h_C6_jetMB");
  h_C5_jetMB = (TH1D*) H_C5_jetMB->ProjectionX("h_C5_jetMB");
  h_C4_jetMB = (TH1D*) H_C4_jetMB->ProjectionX("h_C4_jetMB");
  h_C3_jetMB = (TH1D*) H_C3_jetMB->ProjectionX("h_C3_jetMB");
  h_C2_jetMB = (TH1D*) H_C2_jetMB->ProjectionX("h_C2_jetMB");
  h_C1_jetMB = (TH1D*) H_C1_jetMB->ProjectionX("h_C1_jetMB");
 

  // file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_flavor_C8",H_C8_jet80);
  // file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_flavor_C7",H_C7_jet80);
  // file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_flavor_C6",H_C6_jet80);
  // file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_flavor_C5",H_C5_jet80);
  // file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_flavor_C4",H_C4_jet80);
  // file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_flavor_C3",H_C3_jet80);
  // file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_flavor_C2",H_C2_jet80);
  // file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_flavor_C1",H_C1_jet80);

  file_PbPb_HardProbes_jet80->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C8",H_C8_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C7",H_C7_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C6",H_C6_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C5",H_C5_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",H_C4_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",H_C3_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H_C2_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",H_C1_jet80);

  // h_C8_jet80 = (TH1D*) H_C8_jet80->ProjectionX("h_C8_jet80",H_C8_jet80->GetYaxis()->FindBin(-5),H_C8_jet80->GetYaxis()->FindBin(-1),"e");
  // h_C8_jet80->Add(H_C8_jet80->ProjectionX("h_C8_jet80_add",H_C8_jet80->GetYaxis()->FindBin(-5),H_C8_jet80->GetYaxis()->FindBin(-1),"e"));
  // h_C7_jet80 = (TH1D*) H_C7_jet80->ProjectionX("h_C7_jet80",H_C7_jet80->GetYaxis()->FindBin(-5),H_C7_jet80->GetYaxis()->FindBin(-1),"e");
  // h_C7_jet80->Add(H_C7_jet80->ProjectionX("h_C7_jet80_add",H_C7_jet80->GetYaxis()->FindBin(-5),H_C7_jet80->GetYaxis()->FindBin(-1),"e"));
  // h_C6_jet80 = (TH1D*) H_C6_jet80->ProjectionX("h_C6_jet80",H_C6_jet80->GetYaxis()->FindBin(-5),H_C6_jet80->GetYaxis()->FindBin(-1),"e");
  // h_C6_jet80->Add(H_C6_jet80->ProjectionX("h_C6_jet80_add",H_C6_jet80->GetYaxis()->FindBin(-5),H_C6_jet80->GetYaxis()->FindBin(-1),"e"));
  // h_C5_jet80 = (TH1D*) H_C5_jet80->ProjectionX("h_C5_jet80",H_C5_jet80->GetYaxis()->FindBin(-5),H_C5_jet80->GetYaxis()->FindBin(-1),"e");
  // h_C5_jet80->Add(H_C5_jet80->ProjectionX("h_C5_jet80_add",H_C5_jet80->GetYaxis()->FindBin(-5),H_C5_jet80->GetYaxis()->FindBin(-1),"e"));
  // h_C4_jet80 = (TH1D*) H_C4_jet80->ProjectionX("h_C4_jet80",H_C4_jet80->GetYaxis()->FindBin(-5),H_C4_jet80->GetYaxis()->FindBin(-1),"e");
  // h_C4_jet80->Add(H_C4_jet80->ProjectionX("h_C4_jet80_add",H_C4_jet80->GetYaxis()->FindBin(-5),H_C4_jet80->GetYaxis()->FindBin(-1),"e"));
  // h_C3_jet80 = (TH1D*) H_C3_jet80->ProjectionX("h_C3_jet80",H_C3_jet80->GetYaxis()->FindBin(-5),H_C3_jet80->GetYaxis()->FindBin(-1),"e");
  // h_C3_jet80->Add(H_C3_jet80->ProjectionX("h_C3_jet80_add",H_C3_jet80->GetYaxis()->FindBin(-5),H_C3_jet80->GetYaxis()->FindBin(-1),"e"));
  // h_C2_jet80 = (TH1D*) H_C2_jet80->ProjectionX("h_C2_jet80",H_C2_jet80->GetYaxis()->FindBin(-5),H_C2_jet80->GetYaxis()->FindBin(-1),"e");
  // h_C2_jet80->Add(H_C2_jet80->ProjectionX("h_C2_jet80_add",H_C2_jet80->GetYaxis()->FindBin(-5),H_C2_jet80->GetYaxis()->FindBin(-1),"e"));
  // h_C1_jet80 = (TH1D*) H_C1_jet80->ProjectionX("h_C1_jet80",H_C1_jet80->GetYaxis()->FindBin(-5),H_C1_jet80->GetYaxis()->FindBin(-1),"e");
  // h_C1_jet80->Add(H_C1_jet80->ProjectionX("h_C1_jet80_add",H_C1_jet80->GetYaxis()->FindBin(-5),H_C1_jet80->GetYaxis()->FindBin(-1),"e"));

  h_C8_jet80 = (TH1D*) H_C8_jet80->ProjectionX("h_C8_jet80");
  h_C7_jet80 = (TH1D*) H_C7_jet80->ProjectionX("h_C7_jet80");
  h_C6_jet80 = (TH1D*) H_C6_jet80->ProjectionX("h_C6_jet80");
  h_C5_jet80 = (TH1D*) H_C5_jet80->ProjectionX("h_C5_jet80");
  h_C4_jet80 = (TH1D*) H_C4_jet80->ProjectionX("h_C4_jet80");
  h_C3_jet80 = (TH1D*) H_C3_jet80->ProjectionX("h_C3_jet80");
  h_C2_jet80 = (TH1D*) H_C2_jet80->ProjectionX("h_C2_jet80");
  h_C1_jet80 = (TH1D*) H_C1_jet80->ProjectionX("h_C1_jet80");
 


  // file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_flavor_C8",H_C8_jet100);
  // file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_flavor_C7",H_C7_jet100);
  // file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_flavor_C6",H_C6_jet100);
  // file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_flavor_C5",H_C5_jet100);
  // file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_flavor_C4",H_C4_jet100);
  // file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_flavor_C3",H_C3_jet100);
  // file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_flavor_C2",H_C2_jet100);
  // file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_flavor_C1",H_C1_jet100);

  file_PbPb_HardProbes_jet100->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C8",H_C8_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C7",H_C7_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C6",H_C6_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C5",H_C5_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",H_C4_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",H_C3_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H_C2_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",H_C1_jet100);

  // h_C8_jet100 = (TH1D*) H_C8_jet100->ProjectionX("h_C8_jet100",H_C8_jet100->GetYaxis()->FindBin(-5),H_C8_jet100->GetYaxis()->FindBin(-1),"e");
  // h_C8_jet100->Add(H_C8_jet100->ProjectionX("h_C8_jet100_add",H_C8_jet100->GetYaxis()->FindBin(-5),H_C8_jet100->GetYaxis()->FindBin(-1),"e"));
  // h_C7_jet100 = (TH1D*) H_C7_jet100->ProjectionX("h_C7_jet100",H_C7_jet100->GetYaxis()->FindBin(-5),H_C7_jet100->GetYaxis()->FindBin(-1),"e");
  // h_C7_jet100->Add(H_C7_jet100->ProjectionX("h_C7_jet100_add",H_C7_jet100->GetYaxis()->FindBin(-5),H_C7_jet100->GetYaxis()->FindBin(-1),"e"));
  // h_C6_jet100 = (TH1D*) H_C6_jet100->ProjectionX("h_C6_jet100",H_C6_jet100->GetYaxis()->FindBin(-5),H_C6_jet100->GetYaxis()->FindBin(-1),"e");
  // h_C6_jet100->Add(H_C6_jet100->ProjectionX("h_C6_jet100_add",H_C6_jet100->GetYaxis()->FindBin(-5),H_C6_jet100->GetYaxis()->FindBin(-1),"e"));
  // h_C5_jet100 = (TH1D*) H_C5_jet100->ProjectionX("h_C5_jet100",H_C5_jet100->GetYaxis()->FindBin(-5),H_C5_jet100->GetYaxis()->FindBin(-1),"e");
  // h_C5_jet100->Add(H_C5_jet100->ProjectionX("h_C5_jet100_add",H_C5_jet100->GetYaxis()->FindBin(-5),H_C5_jet100->GetYaxis()->FindBin(-1),"e"));
  // h_C4_jet100 = (TH1D*) H_C4_jet100->ProjectionX("h_C4_jet100",H_C4_jet100->GetYaxis()->FindBin(-5),H_C4_jet100->GetYaxis()->FindBin(-1),"e");
  // h_C4_jet100->Add(H_C4_jet100->ProjectionX("h_C4_jet100_add",H_C4_jet100->GetYaxis()->FindBin(-5),H_C4_jet100->GetYaxis()->FindBin(-1),"e"));
  // h_C3_jet100 = (TH1D*) H_C3_jet100->ProjectionX("h_C3_jet100",H_C3_jet100->GetYaxis()->FindBin(-5),H_C3_jet100->GetYaxis()->FindBin(-1),"e");
  // h_C3_jet100->Add(H_C3_jet100->ProjectionX("h_C3_jet100_add",H_C3_jet100->GetYaxis()->FindBin(-5),H_C3_jet100->GetYaxis()->FindBin(-1),"e"));
  // h_C2_jet100 = (TH1D*) H_C2_jet100->ProjectionX("h_C2_jet100",H_C2_jet100->GetYaxis()->FindBin(-5),H_C2_jet100->GetYaxis()->FindBin(-1),"e");
  // h_C2_jet100->Add(H_C2_jet100->ProjectionX("h_C2_jet100_add",H_C2_jet100->GetYaxis()->FindBin(-5),H_C2_jet100->GetYaxis()->FindBin(-1),"e"));
  // h_C1_jet100 = (TH1D*) H_C1_jet100->ProjectionX("h_C1_jet100",H_C1_jet100->GetYaxis()->FindBin(-5),H_C1_jet100->GetYaxis()->FindBin(-1),"e");
  // h_C1_jet100->Add(H_C1_jet100->ProjectionX("h_C1_jet100_add",H_C1_jet100->GetYaxis()->FindBin(-5),H_C1_jet100->GetYaxis()->FindBin(-1),"e"));

  h_C8_jet100 = (TH1D*) H_C8_jet100->ProjectionX("h_C8_jet100");
  h_C7_jet100 = (TH1D*) H_C7_jet100->ProjectionX("h_C7_jet100");
  h_C6_jet100 = (TH1D*) H_C6_jet100->ProjectionX("h_C6_jet100");
  h_C5_jet100 = (TH1D*) H_C5_jet100->ProjectionX("h_C5_jet100");
  h_C4_jet100 = (TH1D*) H_C4_jet100->ProjectionX("h_C4_jet100");
  h_C3_jet100 = (TH1D*) H_C3_jet100->ProjectionX("h_C3_jet100");
  h_C2_jet100 = (TH1D*) H_C2_jet100->ProjectionX("h_C2_jet100");
  h_C1_jet100 = (TH1D*) H_C1_jet100->ProjectionX("h_C1_jet100");
 





  
  h_pp = (TH1D*) stitchSamples(h_pp_jetMB,h_pp_jet60,h_pp_jet80,h_pp_jet100,1,0);
  h_C8 = (TH1D*) stitchSamples(h_C8_jetMB,h_C8_jet80,h_C8_jet80,h_C8_jet100,0,1);
  h_C7 = (TH1D*) stitchSamples(h_C7_jetMB,h_C7_jet80,h_C7_jet80,h_C7_jet100,0,1);
  h_C6 = (TH1D*) stitchSamples(h_C6_jetMB,h_C6_jet80,h_C6_jet80,h_C6_jet100,0,1);
  h_C5 = (TH1D*) stitchSamples(h_C5_jetMB,h_C5_jet80,h_C5_jet80,h_C5_jet100,0,1);
  h_C4 = (TH1D*) stitchSamples(h_C4_jetMB,h_C4_jet80,h_C4_jet80,h_C4_jet100,0,1);
  h_C3 = (TH1D*) stitchSamples(h_C3_jetMB,h_C3_jet80,h_C3_jet80,h_C3_jet100,0,1);
  h_C2 = (TH1D*) stitchSamples(h_C2_jetMB,h_C2_jet80,h_C2_jet80,h_C2_jet100,0,1);
  h_C1 = (TH1D*) stitchSamples(h_C1_jetMB,h_C1_jet80,h_C1_jet80,h_C1_jet100,0,1);


  stylizeHistograms(h_pp_jetMB,h_pp_jet60,h_pp_jet80,h_pp_jet100);
  stylizeHistograms(h_C8_jetMB,h_C8_jet80,h_C8_jet80,h_C8_jet100);
  stylizeHistograms(h_C7_jetMB,h_C7_jet80,h_C7_jet80,h_C7_jet100);
  stylizeHistograms(h_C6_jetMB,h_C6_jet80,h_C6_jet80,h_C6_jet100);
  stylizeHistograms(h_C5_jetMB,h_C5_jet80,h_C5_jet80,h_C5_jet100);
  stylizeHistograms(h_C4_jetMB,h_C4_jet80,h_C4_jet80,h_C4_jet100);
  stylizeHistograms(h_C3_jetMB,h_C3_jet80,h_C3_jet80,h_C3_jet100);
  stylizeHistograms(h_C2_jetMB,h_C2_jet80,h_C2_jet80,h_C2_jet100);
  stylizeHistograms(h_C1_jetMB,h_C1_jet80,h_C1_jet80,h_C1_jet100);

  const int N_edge = 26;
  double newAxis[N_edge] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300};

  h_pp = (TH1D*) h_pp->Rebin(N_edge-1,"h_pp",newAxis);
  h_C8 = (TH1D*) h_C8->Rebin(N_edge-1,"h_C8",newAxis);
  h_C7 = (TH1D*) h_C7->Rebin(N_edge-1,"h_C7",newAxis);
  h_C6 = (TH1D*) h_C6->Rebin(N_edge-1,"h_C6",newAxis);
  h_C5 = (TH1D*) h_C5->Rebin(N_edge-1,"h_C5",newAxis);
  h_C4 = (TH1D*) h_C4->Rebin(N_edge-1,"h_C4",newAxis);
  h_C3 = (TH1D*) h_C3->Rebin(N_edge-1,"h_C3",newAxis);
  h_C2 = (TH1D*) h_C2->Rebin(N_edge-1,"h_C2",newAxis);
  h_C1 = (TH1D*) h_C1->Rebin(N_edge-1,"h_C1",newAxis);

  divideByBinwidth(h_pp);
  divideByBinwidth(h_C8);
  divideByBinwidth(h_C7);
  divideByBinwidth(h_C6);
  divideByBinwidth(h_C5);
  divideByBinwidth(h_C4);
  divideByBinwidth(h_C3);
  divideByBinwidth(h_C2);
  divideByBinwidth(h_C1);
  

  double leftMargin = 0.15;
  double bottomMargin = 0.15;
  double xmin = 50;
  double xmax = 300;
  double ymin = 0.2;
  double ymax = 8.E7;
  double legendXmin = 0.72;
  double legendXmax = 0.88;
  double legendYmin = 0.72;
  double legendYmax = 0.88;
  double legendTextSize = 0.038;
  TLegend *leg_pp_spectra = new TLegend(legendXmin,legendYmin,legendXmax,legendYmax);
  leg_pp_spectra->SetBorderSize(0);
  leg_pp_spectra->SetTextSize(legendTextSize);
  leg_pp_spectra->AddEntry(h_pp_jetMB,"MinBias","l");
  leg_pp_spectra->AddEntry(h_pp_jet60,"Jet60","l");
  leg_pp_spectra->AddEntry(h_pp_jet80,"Jet80","l");
  leg_pp_spectra->AddEntry(h_pp_jet100,"Jet100","l");

  TLegend *leg_PbPb_spectra = new TLegend(legendXmin,legendYmin,legendXmax,legendYmax);
  leg_PbPb_spectra->SetBorderSize(0);
  leg_PbPb_spectra->SetTextSize(legendTextSize);
  leg_PbPb_spectra->AddEntry(h_C4_jetMB,"MinBias","l");
  leg_PbPb_spectra->AddEntry(h_C4_jet80,"Jet80","l");
  leg_PbPb_spectra->AddEntry(h_C4_jet100,"Jet100","l");

  
  /////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_pp_spectra = new TCanvas("canv_pp_spectra","canv_pp_spectra",700,700);
  canv_pp_spectra->cd();
  TPad *pad_pp_spectra = new TPad("pad_pp_spectra","pad_pp_spectra",0,0,1,1);
  pad_pp_spectra->SetLeftMargin(leftMargin);
  pad_pp_spectra->SetBottomMargin(bottomMargin);
  pad_pp_spectra->SetLogy();
  pad_pp_spectra->Draw();
  pad_pp_spectra->cd();
  h_pp_jetMB->SetTitle("pp");
  h_pp_jetMB->SetStats(0);
  h_pp_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_pp_jetMB->GetYaxis()->SetRangeUser(ymin,ymax);
  h_pp_jetMB->GetYaxis()->SetTitle("Entries");
  h_pp_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_pp_jetMB->Draw();
  h_pp_jet60->Draw("same");
  h_pp_jet80->Draw("same");
  h_pp_jet100->Draw("same");
  leg_pp_spectra->Draw();
  canv_pp_spectra->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_pp_spectra.pdf");

  
  
  TCanvas *canv_C8_spectra = new TCanvas("canv_C8_spectra","canv_C8_spectra",700,700);
  canv_C8_spectra->cd();
  TPad *pad_C8_spectra = new TPad("pad_C8_spectra","pad_C8_spectra",0,0,1,1);
  pad_C8_spectra->SetLeftMargin(leftMargin);
  pad_C8_spectra->SetBottomMargin(bottomMargin);
  pad_C8_spectra->SetLogy();
  pad_C8_spectra->Draw();
  pad_C8_spectra->cd();
  h_C8_jetMB->SetTitle("PbPb 35-40%");
  h_C8_jetMB->SetStats(0);
  h_C8_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C8_jetMB->GetYaxis()->SetTitle("Entries");
  h_C8_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C8_jetMB->Draw();
  h_C8_jet80->Draw("same");
  h_C8_jet100->Draw("same");
  leg_PbPb_spectra->Draw();
  canv_C8_spectra->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C8_spectra.pdf");

  

  TCanvas *canv_C7_spectra = new TCanvas("canv_C7_spectra","canv_C7_spectra",700,700);
  canv_C7_spectra->cd();
  TPad *pad_C7_spectra = new TPad("pad_C7_spectra","pad_C7_spectra",0,0,1,1);
  pad_C7_spectra->SetLeftMargin(leftMargin);
  pad_C7_spectra->SetBottomMargin(bottomMargin);
  pad_C7_spectra->SetLogy();
  pad_C7_spectra->Draw();
  pad_C7_spectra->cd();
  h_C7_jetMB->SetTitle("PbPb 30-35%");
  h_C7_jetMB->SetStats(0);
  h_C7_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C7_jetMB->GetYaxis()->SetTitle("Entries");
  h_C7_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C7_jetMB->Draw();
  h_C7_jet80->Draw("same");
  h_C7_jet100->Draw("same");
  leg_PbPb_spectra->Draw();
  canv_C7_spectra->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C7_spectra.pdf");

  TCanvas *canv_C6_spectra = new TCanvas("canv_C6_spectra","canv_C6_spectra",700,700);
  canv_C6_spectra->cd();
  TPad *pad_C6_spectra = new TPad("pad_C6_spectra","pad_C6_spectra",0,0,1,1);
  pad_C6_spectra->SetLeftMargin(leftMargin);
  pad_C6_spectra->SetBottomMargin(bottomMargin);
  pad_C6_spectra->SetLogy();
  pad_C6_spectra->Draw();
  pad_C6_spectra->cd();
  h_C6_jetMB->SetTitle("PbPb 25-30%");
  h_C6_jetMB->SetStats(0);
  h_C6_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C6_jetMB->GetYaxis()->SetTitle("Entries");
  h_C6_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C6_jetMB->Draw();
  h_C6_jet80->Draw("same");
  h_C6_jet100->Draw("same");
  leg_PbPb_spectra->Draw();
  canv_C6_spectra->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C6_spectra.pdf");

  TCanvas *canv_C5_spectra = new TCanvas("canv_C5_spectra","canv_C5_spectra",700,700);
  canv_C5_spectra->cd();
  TPad *pad_C5_spectra = new TPad("pad_C5_spectra","pad_C5_spectra",0,0,1,1);
  pad_C5_spectra->SetLeftMargin(leftMargin);
  pad_C5_spectra->SetBottomMargin(bottomMargin);
  pad_C5_spectra->SetLogy();
  pad_C5_spectra->Draw();
  pad_C5_spectra->cd();
  h_C5_jetMB->SetTitle("PbPb 20-25%");
  h_C5_jetMB->SetStats(0);
  h_C5_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C5_jetMB->GetYaxis()->SetTitle("Entries");
  h_C5_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C5_jetMB->Draw();
  h_C5_jet80->Draw("same");
  h_C5_jet100->Draw("same");
  leg_PbPb_spectra->Draw();
  canv_C5_spectra->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C5_spectra.pdf");


  TCanvas *canv_C4_spectra = new TCanvas("canv_C4_spectra","canv_C4_spectra",700,700);
  canv_C4_spectra->cd();
  TPad *pad_C4_spectra = new TPad("pad_C4_spectra","pad_C4_spectra",0,0,1,1);
  pad_C4_spectra->SetLeftMargin(leftMargin);
  pad_C4_spectra->SetBottomMargin(bottomMargin);
  pad_C4_spectra->SetLogy();
  pad_C4_spectra->Draw();
  pad_C4_spectra->cd();
  h_C4_jetMB->SetTitle("PbPb 15-20%");
  h_C4_jetMB->SetStats(0);
  h_C4_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C4_jetMB->GetYaxis()->SetTitle("Entries");
  h_C4_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C4_jetMB->Draw();
  h_C4_jet80->Draw("same");
  h_C4_jet100->Draw("same");
  leg_PbPb_spectra->Draw();
  canv_C4_spectra->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C4_spectra.pdf");
  

  TCanvas *canv_C3_spectra = new TCanvas("canv_C3_spectra","canv_C3_spectra",700,700);
  canv_C3_spectra->cd();
  TPad *pad_C3_spectra = new TPad("pad_C3_spectra","pad_C3_spectra",0,0,1,1);
  pad_C3_spectra->SetLeftMargin(leftMargin);
  pad_C3_spectra->SetBottomMargin(bottomMargin);
  pad_C3_spectra->SetLogy();
  pad_C3_spectra->Draw();
  pad_C3_spectra->cd();
  h_C3_jetMB->SetTitle("PbPb 10-15%");
  h_C3_jetMB->SetStats(0);
  h_C3_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C3_jetMB->GetYaxis()->SetTitle("Entries");
  h_C3_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C3_jetMB->Draw();
  h_C3_jet80->Draw("same");
  h_C3_jet100->Draw("same");
  leg_PbPb_spectra->Draw();
  canv_C3_spectra->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C3_spectra.pdf");


  TCanvas *canv_C2_spectra = new TCanvas("canv_C2_spectra","canv_C2_spectra",700,700);
  canv_C2_spectra->cd();
  TPad *pad_C2_spectra = new TPad("pad_C2_spectra","pad_C2_spectra",0,0,1,1);
  pad_C2_spectra->SetLeftMargin(leftMargin);
  pad_C2_spectra->SetBottomMargin(bottomMargin);
  pad_C2_spectra->SetLogy();
  pad_C2_spectra->Draw();
  pad_C2_spectra->cd();
  h_C2_jetMB->SetTitle("PbPb 5-10%");
  h_C2_jetMB->SetStats(0);
  h_C2_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C2_jetMB->GetYaxis()->SetTitle("Entries");
  h_C2_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C2_jetMB->Draw();
  h_C2_jet80->Draw("same");
  h_C2_jet100->Draw("same");
  leg_PbPb_spectra->Draw();
  canv_C2_spectra->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C2_spectra.pdf");


  TCanvas *canv_C1_spectra = new TCanvas("canv_C1_spectra","canv_C1_spectra",700,700);
  canv_C1_spectra->cd();
  TPad *pad_C1_spectra = new TPad("pad_C1_spectra","pad_C1_spectra",0,0,1,1);
  pad_C1_spectra->SetLeftMargin(leftMargin);
  pad_C1_spectra->SetBottomMargin(bottomMargin);
  pad_C1_spectra->SetLogy();
  pad_C1_spectra->Draw();
  pad_C1_spectra->cd();
  h_C1_jetMB->SetTitle("PbPb 0-5%");
  h_C1_jetMB->SetStats(0);
  h_C1_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C1_jetMB->GetYaxis()->SetTitle("Entries");
  h_C1_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C1_jetMB->Draw();
  h_C1_jet80->Draw("same");
  h_C1_jet100->Draw("same");
  leg_PbPb_spectra->Draw();
  canv_C1_spectra->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C1_spectra.pdf");
  
  
  

  /////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_pp_stitch = new TCanvas("canv_pp_stitch","canv_pp_stitch",700,700);
  canv_pp_stitch->cd();
  TPad *pad_pp_stitch = new TPad("pad_pp_stitch","pad_pp_stitch",0,0,1,1);
  pad_pp_stitch->SetLeftMargin(leftMargin);
  pad_pp_stitch->SetBottomMargin(bottomMargin);
  pad_pp_stitch->SetLogy();
  pad_pp_stitch->Draw();
  pad_pp_stitch->cd();
  h_pp->SetTitle("pp");
  h_pp->SetStats(0);
  h_pp->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_pp->GetYaxis()->SetRangeUser(ymin,ymax);
  h_pp->GetYaxis()->SetTitle("Scaled Entries");
  h_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_pp->Draw();
  canv_pp_stitch->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_pp_stitch.pdf");


  /*
  
  TCanvas *canv_C8_stitch = new TCanvas("canv_C8_stitch","canv_C8_stitch",700,700);
  canv_C8_stitch->cd();
  TPad *pad_C8_stitch = new TPad("pad_C8_stitch","pad_C8_stitch",0,0,1,1);
  pad_C8_stitch->SetLeftMargin(leftMargin);
  pad_C8_stitch->SetBottomMargin(bottomMargin);
  pad_C8_stitch->SetLogy();
  pad_C8_stitch->Draw();
  pad_C8_stitch->cd();
  h_C8->SetTitle("PbPb 35-40%");
  h_C8->SetStats(0);
  h_C8->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C8->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C8->GetYaxis()->SetTitle("Scaled Entries");
  h_C8->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C8->Draw();
  canv_C8_stitch->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C8_stitch.pdf");

  TCanvas *canv_C7_stitch = new TCanvas("canv_C7_stitch","canv_C7_stitch",700,700);
  canv_C7_stitch->cd();
  TPad *pad_C7_stitch = new TPad("pad_C7_stitch","pad_C7_stitch",0,0,1,1);
  pad_C7_stitch->SetLeftMargin(leftMargin);
  pad_C7_stitch->SetBottomMargin(bottomMargin);
  pad_C7_stitch->SetLogy();
  pad_C7_stitch->Draw();
  pad_C7_stitch->cd();
  h_C7->SetTitle("PbPb 35-40%");
  h_C7->SetStats(0);
  h_C7->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C7->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C7->GetYaxis()->SetTitle("Scaled Entries");
  h_C7->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C7->Draw();
  canv_C7_stitch->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C7_stitch.pdf");

  TCanvas *canv_C6_stitch = new TCanvas("canv_C6_stitch","canv_C6_stitch",700,700);
  canv_C6_stitch->cd();
  TPad *pad_C6_stitch = new TPad("pad_C6_stitch","pad_C6_stitch",0,0,1,1);
  pad_C6_stitch->SetLeftMargin(leftMargin);
  pad_C6_stitch->SetBottomMargin(bottomMargin);
  pad_C6_stitch->SetLogy();
  pad_C6_stitch->Draw();
  pad_C6_stitch->cd();
  h_C6->SetTitle("PbPb 35-40%");
  h_C6->SetStats(0);
  h_C6->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C6->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C6->GetYaxis()->SetTitle("Scaled Entries");
  h_C6->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C6->Draw();
  canv_C6_stitch->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C6_stitch.pdf");

  TCanvas *canv_C5_stitch = new TCanvas("canv_C5_stitch","canv_C5_stitch",700,700);
  canv_C5_stitch->cd();
  TPad *pad_C5_stitch = new TPad("pad_C5_stitch","pad_C5_stitch",0,0,1,1);
  pad_C5_stitch->SetLeftMargin(leftMargin);
  pad_C5_stitch->SetBottomMargin(bottomMargin);
  pad_C5_stitch->SetLogy();
  pad_C5_stitch->Draw();
  pad_C5_stitch->cd();
  h_C5->SetTitle("PbPb 35-40%");
  h_C5->SetStats(0);
  h_C5->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C5->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C5->GetYaxis()->SetTitle("Scaled Entries");
  h_C5->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C5->Draw();
  canv_C5_stitch->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C5_stitch.pdf");

  */

  TCanvas *canv_C4_stitch = new TCanvas("canv_C4_stitch","canv_C4_stitch",700,700);
  canv_C4_stitch->cd();
  TPad *pad_C4_stitch = new TPad("pad_C4_stitch","pad_C4_stitch",0,0,1,1);
  pad_C4_stitch->SetLeftMargin(leftMargin);
  pad_C4_stitch->SetBottomMargin(bottomMargin);
  pad_C4_stitch->SetLogy();
  pad_C4_stitch->Draw();
  pad_C4_stitch->cd();
  h_C4->SetTitle("PbPb 15-20%");
  h_C4->SetStats(0);
  h_C4->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C4->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C4->GetYaxis()->SetTitle("Scaled Entries");
  h_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C4->Draw();
  canv_C4_stitch->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C4_stitch.pdf");


  TCanvas *canv_C3_stitch = new TCanvas("canv_C3_stitch","canv_C3_stitch",700,700);
  canv_C3_stitch->cd();
  TPad *pad_C3_stitch = new TPad("pad_C3_stitch","pad_C3_stitch",0,0,1,1);
  pad_C3_stitch->SetLeftMargin(leftMargin);
  pad_C3_stitch->SetBottomMargin(bottomMargin);
  pad_C3_stitch->SetLogy();
  pad_C3_stitch->Draw();
  pad_C3_stitch->cd();
  h_C3->SetTitle("PbPb 10-15%");
  h_C3->SetStats(0);
  h_C3->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C3->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C3->GetYaxis()->SetTitle("Scaled Entries");
  h_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C3->Draw();
  canv_C3_stitch->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C3_stitch.pdf");


  TCanvas *canv_C2_stitch = new TCanvas("canv_C2_stitch","canv_C2_stitch",700,700);
  canv_C2_stitch->cd();
  TPad *pad_C2_stitch = new TPad("pad_C2_stitch","pad_C2_stitch",0,0,1,1);
  pad_C2_stitch->SetLeftMargin(leftMargin);
  pad_C2_stitch->SetBottomMargin(bottomMargin);
  pad_C2_stitch->SetLogy();
  pad_C2_stitch->Draw();
  pad_C2_stitch->cd();
  h_C2->SetTitle("PbPb 5-10%");
  h_C2->SetStats(0);
  h_C2->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C2->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C2->GetYaxis()->SetTitle("Scaled Entries");
  h_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C2->Draw();
  canv_C2_stitch->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C2_stitch.pdf");


  TCanvas *canv_C1_stitch = new TCanvas("canv_C1_stitch","canv_C1_stitch",700,700);
  canv_C1_stitch->cd();
  TPad *pad_C1_stitch = new TPad("pad_C1_stitch","pad_C1_stitch",0,0,1,1);
  pad_C1_stitch->SetLeftMargin(leftMargin);
  pad_C1_stitch->SetBottomMargin(bottomMargin);
  pad_C1_stitch->SetLogy();
  pad_C1_stitch->Draw();
  pad_C1_stitch->cd();
  h_C1->SetTitle("PbPb 0-5%");
  h_C1->SetStats(0);
  h_C1->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C1->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C1->GetYaxis()->SetTitle("Scaled Entries");
  h_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C1->Draw();
  canv_C1_stitch->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C1_stitch.pdf");
  
  /////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C8_compareToPP = new TCanvas("canv_C8_compareToPP","canv_C8_compareToPP",700,700);
  canv_C8_compareToPP->cd();
  TPad *pad_C8_compareToPP_upper = new TPad("pad_C8_compareToPP_upper","pad_C8_compareToPP_upper",0,0.4,1,1);
  TPad *pad_C8_compareToPP_lower = new TPad("pad_C8_compareToPP_lower","pad_C8_compareToPP_lower",0,0,1,0.4);
  pad_C8_compareToPP_upper->SetLeftMargin(leftMargin);
  pad_C8_compareToPP_lower->SetLeftMargin(leftMargin);
  pad_C8_compareToPP_upper->SetBottomMargin(0);
  pad_C8_compareToPP_lower->SetBottomMargin(bottomMargin);
  pad_C8_compareToPP_upper->SetTopMargin(bottomMargin);
  pad_C8_compareToPP_lower->SetTopMargin(0);
  pad_C8_compareToPP_upper->SetLogy();
  pad_C8_compareToPP_upper->Draw();
  pad_C8_compareToPP_lower->Draw();
  pad_C8_compareToPP_upper->cd();
  h_C8->SetTitle("");
  h_C8->SetStats(0);
  h_C8->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C8->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C8->GetYaxis()->SetTitle("Scaled Entries");
  h_C8->SetLineWidth(2);
  h_pp->SetLineWidth(2);
  h_pp->SetLineColor(kRed-4);
  h_C8->SetLineColor(kBlue-4);
  h_C8->Draw();
  TH1D *h_pp_scaledToC8 = (TH1D*) h_pp->Clone("h_pp_scaledToC8");
  h_pp_scaledToC8->Scale(h_C8->Integral(h_C8->FindBin(200),h_C8->FindBin(500)) / h_pp->Integral(h_pp->FindBin(200),h_pp->FindBin(500)));  // normalize by high pT
  h_pp_scaledToC8->Draw("same");
  TLegend *leg_C8_compareToPP = new TLegend(0.65,0.65,0.84,0.84);
  leg_C8_compareToPP->SetBorderSize(0);
  leg_C8_compareToPP->SetTextSize(0.045);
  leg_C8_compareToPP->AddEntry(h_pp_scaledToC8,"pp","l");
  leg_C8_compareToPP->AddEntry(h_C8,"PbPb 35-40%","l");
  leg_C8_compareToPP->Draw();
  pad_C8_compareToPP_lower->cd();
  TH1D *r_C8 = (TH1D*) h_C8->Clone("r_C8");
  r_C8->Divide(h_C8,h_pp_scaledToC8,1,1,"");
  r_C8->SetTitle("");
  r_C8->GetXaxis()->SetTitleSize(0.065);
  r_C8->GetXaxis()->SetLabelSize(0.057);
  r_C8->GetYaxis()->SetTitleSize(0.065);
  r_C8->GetYaxis()->SetLabelSize(0.057);
  r_C8->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C8->GetYaxis()->SetTitle("PbPb / pp");
  r_C8->GetYaxis()->SetRangeUser(0,10);
  r_C8->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C8_compareToPP->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C8_compareToPP.pdf");
  

  TCanvas *canv_C7_compareToPP = new TCanvas("canv_C7_compareToPP","canv_C7_compareToPP",700,700);
  canv_C7_compareToPP->cd();
  TPad *pad_C7_compareToPP_upper = new TPad("pad_C7_compareToPP_upper","pad_C7_compareToPP_upper",0,0.4,1,1);
  TPad *pad_C7_compareToPP_lower = new TPad("pad_C7_compareToPP_lower","pad_C7_compareToPP_lower",0,0,1,0.4);
  pad_C7_compareToPP_upper->SetLeftMargin(leftMargin);
  pad_C7_compareToPP_lower->SetLeftMargin(leftMargin);
  pad_C7_compareToPP_upper->SetBottomMargin(0);
  pad_C7_compareToPP_lower->SetBottomMargin(bottomMargin);
  pad_C7_compareToPP_upper->SetTopMargin(bottomMargin);
  pad_C7_compareToPP_lower->SetTopMargin(0);
  pad_C7_compareToPP_upper->SetLogy();
  pad_C7_compareToPP_upper->Draw();
  pad_C7_compareToPP_lower->Draw();
  pad_C7_compareToPP_upper->cd();
  h_C7->SetTitle("");
  h_C7->SetStats(0);
  h_C7->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C7->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C7->GetYaxis()->SetTitle("Scaled Entries");
  h_C7->SetLineWidth(2);
  h_pp->SetLineWidth(2);
  h_pp->SetLineColor(kRed-4);
  h_C7->SetLineColor(kBlue-4);
  h_C7->Draw();
  TH1D *h_pp_scaledToC7 = (TH1D*) h_pp->Clone("h_pp_scaledToC7");
  h_pp_scaledToC7->Scale(h_C7->Integral(h_C7->FindBin(200),h_C7->FindBin(500)) / h_pp->Integral(h_pp->FindBin(200),h_pp->FindBin(500)));  // normalize by high pT
  h_pp_scaledToC7->Draw("same");
  TLegend *leg_C7_compareToPP = new TLegend(0.65,0.65,0.84,0.84);
  leg_C7_compareToPP->SetBorderSize(0);
  leg_C7_compareToPP->SetTextSize(0.045);
  leg_C7_compareToPP->AddEntry(h_pp_scaledToC7,"pp","l");
  leg_C7_compareToPP->AddEntry(h_C7,"PbPb 30-35%","l");
  leg_C7_compareToPP->Draw();
  pad_C7_compareToPP_lower->cd();
  TH1D *r_C7 = (TH1D*) h_C7->Clone("r_C7");
  r_C7->Divide(h_C7,h_pp_scaledToC7,1,1,"");
  r_C7->SetTitle("");
  r_C7->GetXaxis()->SetTitleSize(0.065);
  r_C7->GetXaxis()->SetLabelSize(0.057);
  r_C7->GetYaxis()->SetTitleSize(0.065);
  r_C7->GetYaxis()->SetLabelSize(0.057);
  r_C7->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C7->GetYaxis()->SetTitle("PbPb / pp");
  r_C7->GetYaxis()->SetRangeUser(0,10);
  r_C7->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C7_compareToPP->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C7_compareToPP.pdf");

  TCanvas *canv_C6_compareToPP = new TCanvas("canv_C6_compareToPP","canv_C6_compareToPP",700,700);
  canv_C6_compareToPP->cd();
  TPad *pad_C6_compareToPP_upper = new TPad("pad_C6_compareToPP_upper","pad_C6_compareToPP_upper",0,0.4,1,1);
  TPad *pad_C6_compareToPP_lower = new TPad("pad_C6_compareToPP_lower","pad_C6_compareToPP_lower",0,0,1,0.4);
  pad_C6_compareToPP_upper->SetLeftMargin(leftMargin);
  pad_C6_compareToPP_lower->SetLeftMargin(leftMargin);
  pad_C6_compareToPP_upper->SetBottomMargin(0);
  pad_C6_compareToPP_lower->SetBottomMargin(bottomMargin);
  pad_C6_compareToPP_upper->SetTopMargin(bottomMargin);
  pad_C6_compareToPP_lower->SetTopMargin(0);
  pad_C6_compareToPP_upper->SetLogy();
  pad_C6_compareToPP_upper->Draw();
  pad_C6_compareToPP_lower->Draw();
  pad_C6_compareToPP_upper->cd();
  h_C6->SetTitle("");
  h_C6->SetStats(0);
  h_C6->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C6->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C6->GetYaxis()->SetTitle("Scaled Entries");
  h_C6->SetLineWidth(2);
  h_pp->SetLineWidth(2);
  h_pp->SetLineColor(kRed-4);
  h_C6->SetLineColor(kBlue-4);
  h_C6->Draw();
  TH1D *h_pp_scaledToC6 = (TH1D*) h_pp->Clone("h_pp_scaledToC6");
  h_pp_scaledToC6->Scale(h_C6->Integral(h_C6->FindBin(200),h_C6->FindBin(500)) / h_pp->Integral(h_pp->FindBin(200),h_pp->FindBin(500)));  // normalize by high pT
  h_pp_scaledToC6->Draw("same");
  TLegend *leg_C6_compareToPP = new TLegend(0.65,0.65,0.84,0.84);
  leg_C6_compareToPP->SetBorderSize(0);
  leg_C6_compareToPP->SetTextSize(0.045);
  leg_C6_compareToPP->AddEntry(h_pp_scaledToC6,"pp","l");
  leg_C6_compareToPP->AddEntry(h_C6,"PbPb 25-30%","l");
  leg_C6_compareToPP->Draw();
  pad_C6_compareToPP_lower->cd();
  TH1D *r_C6 = (TH1D*) h_C6->Clone("r_C6");
  r_C6->Divide(h_C6,h_pp_scaledToC6,1,1,"");
  r_C6->SetTitle("");
  r_C6->GetXaxis()->SetTitleSize(0.065);
  r_C6->GetXaxis()->SetLabelSize(0.057);
  r_C6->GetYaxis()->SetTitleSize(0.065);
  r_C6->GetYaxis()->SetLabelSize(0.057);
  r_C6->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C6->GetYaxis()->SetTitle("PbPb / pp");
  r_C6->GetYaxis()->SetRangeUser(0,10);
  r_C6->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C6_compareToPP->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C6_compareToPP.pdf");


  
  TCanvas *canv_C5_compareToPP = new TCanvas("canv_C5_compareToPP","canv_C5_compareToPP",700,700);
  canv_C5_compareToPP->cd();
  TPad *pad_C5_compareToPP_upper = new TPad("pad_C5_compareToPP_upper","pad_C5_compareToPP_upper",0,0.4,1,1);
  TPad *pad_C5_compareToPP_lower = new TPad("pad_C5_compareToPP_lower","pad_C5_compareToPP_lower",0,0,1,0.4);
  pad_C5_compareToPP_upper->SetLeftMargin(leftMargin);
  pad_C5_compareToPP_lower->SetLeftMargin(leftMargin);
  pad_C5_compareToPP_upper->SetBottomMargin(0);
  pad_C5_compareToPP_lower->SetBottomMargin(bottomMargin);
  pad_C5_compareToPP_upper->SetTopMargin(bottomMargin);
  pad_C5_compareToPP_lower->SetTopMargin(0);
  pad_C5_compareToPP_upper->SetLogy();
  pad_C5_compareToPP_upper->Draw();
  pad_C5_compareToPP_lower->Draw();
  pad_C5_compareToPP_upper->cd();
  h_C5->SetTitle("");
  h_C5->SetStats(0);
  h_C5->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C5->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C5->GetYaxis()->SetTitle("Scaled Entries");
  h_C5->SetLineWidth(2);
  h_pp->SetLineWidth(2);
  h_pp->SetLineColor(kRed-4);
  h_C5->SetLineColor(kBlue-4);
  h_C5->Draw();
  TH1D *h_pp_scaledToC5 = (TH1D*) h_pp->Clone("h_pp_scaledToC5");
  h_pp_scaledToC5->Scale(h_C5->Integral(h_C5->FindBin(200),h_C5->FindBin(500)) / h_pp->Integral(h_pp->FindBin(200),h_pp->FindBin(500)));  // normalize by high pT
  h_pp_scaledToC5->Draw("same");
  TLegend *leg_C5_compareToPP = new TLegend(0.65,0.65,0.84,0.84);
  leg_C5_compareToPP->SetBorderSize(0);
  leg_C5_compareToPP->SetTextSize(0.045);
  leg_C5_compareToPP->AddEntry(h_pp_scaledToC5,"pp","l");
  leg_C5_compareToPP->AddEntry(h_C5,"PbPb 20-25%","l");
  leg_C5_compareToPP->Draw();
  pad_C5_compareToPP_lower->cd();
  TH1D *r_C5 = (TH1D*) h_C5->Clone("r_C5");
  r_C5->Divide(h_C5,h_pp_scaledToC5,1,1,"");
  r_C5->SetTitle("");
  r_C5->GetXaxis()->SetTitleSize(0.065);
  r_C5->GetXaxis()->SetLabelSize(0.057);
  r_C5->GetYaxis()->SetTitleSize(0.065);
  r_C5->GetYaxis()->SetLabelSize(0.057);
  r_C5->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C5->GetYaxis()->SetTitle("PbPb / pp");
  r_C5->GetYaxis()->SetRangeUser(0,10);
  r_C5->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C5_compareToPP->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C5_compareToPP.pdf");

  
  TCanvas *canv_C4_compareToPP = new TCanvas("canv_C4_compareToPP","canv_C4_compareToPP",700,700);
  canv_C4_compareToPP->cd();
  TPad *pad_C4_compareToPP_upper = new TPad("pad_C4_compareToPP_upper","pad_C4_compareToPP_upper",0,0.4,1,1);
  TPad *pad_C4_compareToPP_lower = new TPad("pad_C4_compareToPP_lower","pad_C4_compareToPP_lower",0,0,1,0.4);
  pad_C4_compareToPP_upper->SetLeftMargin(leftMargin);
  pad_C4_compareToPP_lower->SetLeftMargin(leftMargin);
  pad_C4_compareToPP_upper->SetBottomMargin(0);
  pad_C4_compareToPP_lower->SetBottomMargin(bottomMargin);
  pad_C4_compareToPP_upper->SetTopMargin(bottomMargin);
  pad_C4_compareToPP_lower->SetTopMargin(0);
  pad_C4_compareToPP_upper->SetLogy();
  pad_C4_compareToPP_upper->Draw();
  pad_C4_compareToPP_lower->Draw();
  pad_C4_compareToPP_upper->cd();
  h_C4->SetTitle("");
  h_C4->SetStats(0);
  h_C4->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C4->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C4->GetYaxis()->SetTitle("Scaled Entries");
  h_C4->SetLineWidth(2);
  h_pp->SetLineWidth(2);
  h_pp->SetLineColor(kRed-4);
  h_C4->SetLineColor(kBlue-4);
  h_C4->Draw();
  TH1D *h_pp_scaledToC4 = (TH1D*) h_pp->Clone("h_pp_scaledToC4");
  h_pp_scaledToC4->Scale(h_C4->Integral(h_C4->FindBin(200),h_C4->FindBin(500)) / h_pp->Integral(h_pp->FindBin(200),h_pp->FindBin(500)));  // normalize by high pT
  h_pp_scaledToC4->Draw("same");
  TLegend *leg_C4_compareToPP = new TLegend(0.65,0.65,0.84,0.84);
  leg_C4_compareToPP->SetBorderSize(0);
  leg_C4_compareToPP->SetTextSize(0.045);
  leg_C4_compareToPP->AddEntry(h_pp_scaledToC4,"pp","l");
  leg_C4_compareToPP->AddEntry(h_C4,"PbPb 15-20%","l");
  leg_C4_compareToPP->Draw();
  pad_C4_compareToPP_lower->cd();
  TH1D *r_C4 = (TH1D*) h_C4->Clone("r_C4");
  r_C4->Divide(h_C4,h_pp_scaledToC4,1,1,"");
  r_C4->SetTitle("");
  r_C4->GetXaxis()->SetTitleSize(0.065);
  r_C4->GetXaxis()->SetLabelSize(0.057);
  r_C4->GetYaxis()->SetTitleSize(0.065);
  r_C4->GetYaxis()->SetLabelSize(0.057);
  r_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C4->GetYaxis()->SetTitle("PbPb / pp");
  r_C4->GetYaxis()->SetRangeUser(0,10);
  r_C4->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C4_compareToPP->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C4_compareToPP.pdf");


  TCanvas *canv_C3_compareToPP = new TCanvas("canv_C3_compareToPP","canv_C3_compareToPP",700,700);
  canv_C3_compareToPP->cd();
  TPad *pad_C3_compareToPP_upper = new TPad("pad_C3_compareToPP_upper","pad_C3_compareToPP_upper",0,0.4,1,1);
  TPad *pad_C3_compareToPP_lower = new TPad("pad_C3_compareToPP_lower","pad_C3_compareToPP_lower",0,0,1,0.4);
  pad_C3_compareToPP_upper->SetLeftMargin(leftMargin);
  pad_C3_compareToPP_lower->SetLeftMargin(leftMargin);
  pad_C3_compareToPP_upper->SetBottomMargin(0);
  pad_C3_compareToPP_lower->SetBottomMargin(bottomMargin);
  pad_C3_compareToPP_upper->SetTopMargin(bottomMargin);
  pad_C3_compareToPP_lower->SetTopMargin(0);
  pad_C3_compareToPP_upper->SetLogy();
  pad_C3_compareToPP_upper->Draw();
  pad_C3_compareToPP_lower->Draw();
  pad_C3_compareToPP_upper->cd();
  h_C3->SetTitle("");
  h_C3->SetStats(0);
  h_C3->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C3->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C3->GetYaxis()->SetTitle("Scaled Entries");
  h_C3->SetLineWidth(2);
  h_pp->SetLineWidth(2);
  h_pp->SetLineColor(kRed-4);
  h_C3->SetLineColor(kBlue-4);
  h_C3->Draw();
  TH1D *h_pp_scaledToC3 = (TH1D*) h_pp->Clone("h_pp_scaledToC3");
  h_pp_scaledToC3->Scale(h_C3->Integral(h_C3->FindBin(200),h_C3->FindBin(500)) / h_pp->Integral(h_pp->FindBin(200),h_pp->FindBin(500)));  // normalize by high pT
  h_pp_scaledToC3->Draw("same");
  TLegend *leg_C3_compareToPP = new TLegend(0.65,0.65,0.84,0.84);
  leg_C3_compareToPP->SetBorderSize(0);
  leg_C3_compareToPP->SetTextSize(0.045);
  leg_C3_compareToPP->AddEntry(h_pp_scaledToC3,"pp","l");
  leg_C3_compareToPP->AddEntry(h_C3,"PbPb 10-15%","l");
  leg_C3_compareToPP->Draw();
  pad_C3_compareToPP_lower->cd();
  TH1D *r_C3 = (TH1D*) h_C3->Clone("r_C3");
  r_C3->Divide(h_C3,h_pp_scaledToC3,1,1,"");
  r_C3->SetTitle("");
  r_C3->GetXaxis()->SetTitleSize(0.065);
  r_C3->GetXaxis()->SetLabelSize(0.057);
  r_C3->GetYaxis()->SetTitleSize(0.065);
  r_C3->GetYaxis()->SetLabelSize(0.057);
  r_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C3->GetYaxis()->SetTitle("PbPb / pp");
  r_C3->GetYaxis()->SetRangeUser(0,10);
  r_C3->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C3_compareToPP->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C3_compareToPP.pdf");


  TCanvas *canv_C2_compareToPP = new TCanvas("canv_C2_compareToPP","canv_C2_compareToPP",700,700);
  canv_C2_compareToPP->cd();
  TPad *pad_C2_compareToPP_upper = new TPad("pad_C2_compareToPP_upper","pad_C2_compareToPP_upper",0,0.4,1,1);
  TPad *pad_C2_compareToPP_lower = new TPad("pad_C2_compareToPP_lower","pad_C2_compareToPP_lower",0,0,1,0.4);
  pad_C2_compareToPP_upper->SetLeftMargin(leftMargin);
  pad_C2_compareToPP_lower->SetLeftMargin(leftMargin);
  pad_C2_compareToPP_upper->SetBottomMargin(0);
  pad_C2_compareToPP_lower->SetBottomMargin(bottomMargin);
  pad_C2_compareToPP_upper->SetTopMargin(bottomMargin);
  pad_C2_compareToPP_lower->SetTopMargin(0);
  pad_C2_compareToPP_upper->SetLogy();
  pad_C2_compareToPP_upper->Draw();
  pad_C2_compareToPP_lower->Draw();
  pad_C2_compareToPP_upper->cd();
  h_C2->SetTitle("");
  h_C2->SetStats(0);
  h_C2->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C2->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C2->GetYaxis()->SetTitle("Scaled Entries");
  h_C2->SetLineWidth(2);
  h_pp->SetLineWidth(2);
  h_pp->SetLineColor(kRed-4);
  h_C2->SetLineColor(kBlue-4);
  h_C2->Draw();
  TH1D *h_pp_scaledToC2 = (TH1D*) h_pp->Clone("h_pp_scaledToC2");
  h_pp_scaledToC2->Scale(h_C2->Integral(h_C2->FindBin(200),h_C2->FindBin(500)) / h_pp->Integral(h_pp->FindBin(200),h_pp->FindBin(500)));  // normalize by high pT
  h_pp_scaledToC2->Draw("same");
  TLegend *leg_C2_compareToPP = new TLegend(0.65,0.65,0.84,0.84);
  leg_C2_compareToPP->SetBorderSize(0);
  leg_C2_compareToPP->SetTextSize(0.045);
  leg_C2_compareToPP->AddEntry(h_pp_scaledToC2,"pp","l");
  leg_C2_compareToPP->AddEntry(h_C2,"PbPb 5-10%","l");
  leg_C2_compareToPP->Draw();
  pad_C2_compareToPP_lower->cd();
  TH1D *r_C2 = (TH1D*) h_C2->Clone("r_C2");
  r_C2->Divide(h_C2,h_pp_scaledToC2,1,1,"");
  r_C2->SetTitle("");
  r_C2->GetXaxis()->SetTitleSize(0.065);
  r_C2->GetXaxis()->SetLabelSize(0.057);
  r_C2->GetYaxis()->SetTitleSize(0.065);
  r_C2->GetYaxis()->SetLabelSize(0.057);
  r_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C2->GetYaxis()->SetTitle("PbPb / pp");
  r_C2->GetYaxis()->SetRangeUser(0,10);
  r_C2->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C2_compareToPP->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C2_compareToPP.pdf");


  TCanvas *canv_C1_compareToPP = new TCanvas("canv_C1_compareToPP","canv_C1_compareToPP",700,700);
  canv_C1_compareToPP->cd();
  TPad *pad_C1_compareToPP_upper = new TPad("pad_C1_compareToPP_upper","pad_C1_compareToPP_upper",0,0.4,1,1);
  TPad *pad_C1_compareToPP_lower = new TPad("pad_C1_compareToPP_lower","pad_C1_compareToPP_lower",0,0,1,0.4);
  pad_C1_compareToPP_upper->SetLeftMargin(leftMargin);
  pad_C1_compareToPP_lower->SetLeftMargin(leftMargin);
  pad_C1_compareToPP_upper->SetBottomMargin(0);
  pad_C1_compareToPP_lower->SetBottomMargin(bottomMargin);
  pad_C1_compareToPP_upper->SetTopMargin(bottomMargin);
  pad_C1_compareToPP_lower->SetTopMargin(0);
  pad_C1_compareToPP_upper->SetLogy();
  pad_C1_compareToPP_upper->Draw();
  pad_C1_compareToPP_lower->Draw();
  pad_C1_compareToPP_upper->cd();
  h_C1->SetTitle("");
  h_C1->SetStats(0);
  h_C1->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C1->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C1->GetYaxis()->SetTitle("Scaled Entries");
  h_C1->SetLineWidth(2);
  h_pp->SetLineWidth(2);
  h_pp->SetLineColor(kRed-4);
  h_C1->SetLineColor(kBlue-4);
  h_C1->Draw();
  TH1D *h_pp_scaledToC1 = (TH1D*) h_pp->Clone("h_pp_scaledToC1");
  h_pp_scaledToC1->Scale(h_C1->Integral(h_C1->FindBin(200),h_C1->FindBin(500)) / h_pp->Integral(h_pp->FindBin(200),h_pp->FindBin(500)));  // normalize by high pT
  h_pp_scaledToC1->Draw("same");
  TLegend *leg_C1_compareToPP = new TLegend(0.65,0.65,0.84,0.84);
  leg_C1_compareToPP->SetBorderSize(0);
  leg_C1_compareToPP->SetTextSize(0.045);
  leg_C1_compareToPP->AddEntry(h_pp_scaledToC1,"pp","l");
  leg_C1_compareToPP->AddEntry(h_C1,"PbPb 0-5%","l");
  leg_C1_compareToPP->Draw();
  pad_C1_compareToPP_lower->cd();
  TH1D *r_C1 = (TH1D*) h_C1->Clone("r_C1");
  r_C1->Divide(h_C1,h_pp_scaledToC1,1,1,"");
  r_C1->SetTitle("");
  r_C1->GetXaxis()->SetTitleSize(0.065);
  r_C1->GetXaxis()->SetLabelSize(0.057);
  r_C1->GetYaxis()->SetTitleSize(0.065);
  r_C1->GetYaxis()->SetLabelSize(0.057);
  r_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C1->GetYaxis()->SetTitle("PbPb / pp");
  r_C1->GetYaxis()->SetRangeUser(0,10);
  r_C1->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C1_compareToPP->SaveAs("../../../figures/jetPt/stitch_ultraFineCentBins_MC/jetPt_C1_compareToPP.pdf");

}
