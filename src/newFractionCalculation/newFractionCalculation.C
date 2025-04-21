#include "../../headers/functions/divideByBinwidth.h"

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

void setErrorsToZero(TH1D *h){

  for(int i = 0; i < h->GetSize(); i++){
    h->SetBinError(i,0);
  }

  return;

}


void stylizeHistograms(TH1D *h0, TH1D *h1, TH1D *h2, TH1D *h3){

  double lw  = 2;
  double ms = 1.4;
  
  h0->SetLineColor(kBlack);
  h0->SetMarkerColor(kBlack);
  h0->SetLineWidth(lw);
  h0->SetMarkerSize(ms);
  h0->SetMarkerStyle(20);
  h0->SetStats(0);
  h0->SetTitle("");

  h3->SetLineColor(kRed-4);
  h3->SetMarkerColor(kRed-4);
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

  h1->SetLineColor(kMagenta-9);
  h1->SetMarkerColor(kMagenta-9);
  h1->SetLineWidth(lw);
  h1->SetMarkerSize(ms);
  h1->SetMarkerStyle(47);
  h1->SetStats(0);
  h1->SetTitle("");

  return;

}


void newFractionCalculation(){

  TFile *file_MinBiasJetSpectra, *file_CorrectedBJetSpectra, *file_MuTagMuTrigBJetSpectra, *file_DoubleRatio, *file_InclJetPbPbToPP, *file_BJetPbPbToPP, *file_InclusiveBJetFraction, *file_MuTagMuTrigJetSpectra;

  

  // load bPurity information

  TFile *file_bPurity = TFile::Open("../../rootFiles/bPurityResults/final/bPurityResults_DATA-1_mergeB-1_mergeC-1_pTrel-0.0to5.0_cMult-1.0_bMult-1.0_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0_bJetEnergyShift-0.root");
  
  TH1D *bPurity_muTag_muTrig_pp, *bPurity_muTag_muTrig_C3, *bPurity_muTag_muTrig_C2, *bPurity_muTag_muTrig_C1;
  
  file_bPurity->GetObject("bFracResults_pp",bPurity_muTag_muTrig_pp);
  file_bPurity->GetObject("bFracResults_C3",bPurity_muTag_muTrig_C3);
  file_bPurity->GetObject("bFracResults_C2",bPurity_muTag_muTrig_C2);
  file_bPurity->GetObject("bFracResults_C1",bPurity_muTag_muTrig_C1);


  // load correction factors information
  
  TFile *file_corrFactors_pp = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_pp.root");
  TFile *file_corrFactors_C3 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C3.root");
  TFile *file_corrFactors_C2 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C2.root");
  TFile *file_corrFactors_C1 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C1.root");

  TH1D *corrFactor_1_pp, *corrFactor_2_pp, *corrFactor_3_pp, *corrFactor_3d_pp;
  TH1D *corrFactor_1_C3, *corrFactor_2_C3, *corrFactor_3_C3, *corrFactor_3d_C3;
  TH1D *corrFactor_1_C2, *corrFactor_2_C2, *corrFactor_3_C2, *corrFactor_3d_C2;
  TH1D *corrFactor_1_C1, *corrFactor_2_C1, *corrFactor_3_C1, *corrFactor_3d_C1;

  file_corrFactors_pp->GetObject("corrFactor_1_pp",corrFactor_1_pp);
  file_corrFactors_pp->GetObject("corrFactor_2_pp",corrFactor_2_pp);
  file_corrFactors_pp->GetObject("corrFactor_3_pp",corrFactor_3_pp);
  file_corrFactors_pp->GetObject("corrFactor_3_data_pp",corrFactor_3d_pp);

  file_corrFactors_C3->GetObject("corrFactor_1_C3",corrFactor_1_C3);
  file_corrFactors_C3->GetObject("corrFactor_2_C3",corrFactor_2_C3);
  file_corrFactors_C3->GetObject("corrFactor_3_C3",corrFactor_3_C3);
  file_corrFactors_C3->GetObject("corrFactor_3_data_C3",corrFactor_3d_C3);

  file_corrFactors_C2->GetObject("corrFactor_1_C2",corrFactor_1_C2);
  file_corrFactors_C2->GetObject("corrFactor_2_C2",corrFactor_2_C2);
  file_corrFactors_C2->GetObject("corrFactor_3_C2",corrFactor_3_C2);
  file_corrFactors_C2->GetObject("corrFactor_3_data_C2",corrFactor_3d_C2);
  
  file_corrFactors_C1->GetObject("corrFactor_1_C1",corrFactor_1_C1);
  file_corrFactors_C1->GetObject("corrFactor_2_C1",corrFactor_2_C1);
  file_corrFactors_C1->GetObject("corrFactor_3_C1",corrFactor_3_C1);
  file_corrFactors_C1->GetObject("corrFactor_3_data_C1",corrFactor_3d_C1);

  // set the correction factor errors to zero
  setErrorsToZero(corrFactor_1_pp);
  setErrorsToZero(corrFactor_2_pp);
  setErrorsToZero(corrFactor_3_pp);
  setErrorsToZero(corrFactor_3d_pp);

  setErrorsToZero(corrFactor_1_C3);
  setErrorsToZero(corrFactor_2_C3);
  setErrorsToZero(corrFactor_3_C3);
  setErrorsToZero(corrFactor_3d_C3);

  setErrorsToZero(corrFactor_1_C2);
  setErrorsToZero(corrFactor_2_C2);
  setErrorsToZero(corrFactor_3_C2);
  setErrorsToZero(corrFactor_3d_C2);

  setErrorsToZero(corrFactor_1_C1);
  setErrorsToZero(corrFactor_2_C1);
  setErrorsToZero(corrFactor_3_C1);
  setErrorsToZero(corrFactor_3d_C1);



  

  // load spectra
  TFile *file_pp_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/final/pp_SingleMuon_mu12_tight_pTmu-14_projectableTemplates.root");
  TFile *file_pp_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/final/pp_MinBias_mu12_tight_pTmu-14_projectableTemplates.root");
  TFile *file_pp_DiJet = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/final/pp_HighEGJet_jet60_mu12_tight_pTmu-14_projectableTemplates.root");

  TFile *file_PbPb_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/final/PbPb_SingleMuon_scan_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates.root");
  TFile *file_PbPb_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/final/PbPb_MinBias_scan_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates.root");
  TFile *file_PbPb_DiJet = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/final/PbPb_HardProbes_scan_jet60_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates.root");
  


  TH1D *h_jetPt_muTag_muTrig_pp, *h_jetPt_muTag_muTrig_C4, *h_jetPt_muTag_muTrig_C3, *h_jetPt_muTag_muTrig_C2, *h_jetPt_muTag_muTrig_C1;
  TH1D *h_jetPt_pp, *h_jetPt_C4, *h_jetPt_C3, *h_jetPt_C2, *h_jetPt_C1;
  
  TH1D *getEventNumber_muTag_muTrig_pp, *getEventNumber_muTag_muTrig_C4, *getEventNumber_muTag_muTrig_C3, *getEventNumber_muTag_muTrig_C2, *getEventNumber_muTag_muTrig_C1;
  TH1D *getEventNumber_muTag_pp_SingleMuon, *getEventNumber_muTag_C4_SingleMuon, *getEventNumber_muTag_C3_SingleMuon, *getEventNumber_muTag_C2_SingleMuon, *getEventNumber_muTag_C1_SingleMuon;
  TH1D *getEventNumber_muTag_pp_DiJet, *getEventNumber_muTag_C4_DiJet, *getEventNumber_muTag_C3_DiJet, *getEventNumber_muTag_C2_DiJet, *getEventNumber_muTag_C1_DiJet;
  TH1D *getEventNumber_jet_pp_DiJet, *getEventNumber_jet_C4_DiJet, *getEventNumber_jet_C3_DiJet, *getEventNumber_jet_C2_DiJet, *getEventNumber_jet_C1_DiJet;
  TH1D *getEventNumber_jet_pp_MinBias, *getEventNumber_jet_C4_MinBias, *getEventNumber_jet_C3_MinBias, *getEventNumber_jet_C2_MinBias, *getEventNumber_jet_C1_MinBias;
  TH1D *getEventNumber_pp_MinBias, *getEventNumber_C4_MinBias, *getEventNumber_C3_MinBias, *getEventNumber_C2_MinBias, *getEventNumber_C1_MinBias;


  // jet spectra histograms
  file_pp_SingleMuon->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_jetPt_muTag_muTrig_pp);
  file_PbPb_SingleMuon->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",h_jetPt_muTag_muTrig_C4);
  file_PbPb_SingleMuon->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",h_jetPt_muTag_muTrig_C3);
  file_PbPb_SingleMuon->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",h_jetPt_muTag_muTrig_C2);
  file_PbPb_SingleMuon->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",h_jetPt_muTag_muTrig_C1);

  file_pp_MinBias->GetObject("h_inclRecoJetPt",h_jetPt_pp);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C4",h_jetPt_C4);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C3",h_jetPt_C3);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C2",h_jetPt_C2);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C1",h_jetPt_C1);


  // eventNumber histograms
  file_pp_SingleMuon->GetObject("h_vz_inclRecoMuonTag_triggerOn",getEventNumber_muTag_muTrig_pp);
  file_PbPb_SingleMuon->GetObject("h_vz_inclRecoMuonTag_triggerOn_C4",getEventNumber_muTag_muTrig_C4);
  file_PbPb_SingleMuon->GetObject("h_vz_inclRecoMuonTag_triggerOn_C3",getEventNumber_muTag_muTrig_C3);
  file_PbPb_SingleMuon->GetObject("h_vz_inclRecoMuonTag_triggerOn_C2",getEventNumber_muTag_muTrig_C2);
  file_PbPb_SingleMuon->GetObject("h_vz_inclRecoMuonTag_triggerOn_C1",getEventNumber_muTag_muTrig_C1);

  file_pp_SingleMuon->GetObject("h_vz_inclRecoMuonTag",getEventNumber_muTag_pp_SingleMuon);
  file_PbPb_SingleMuon->GetObject("h_vz_inclRecoMuonTag_C4",getEventNumber_muTag_C4_SingleMuon);
  file_PbPb_SingleMuon->GetObject("h_vz_inclRecoMuonTag_C3",getEventNumber_muTag_C3_SingleMuon);
  file_PbPb_SingleMuon->GetObject("h_vz_inclRecoMuonTag_C2",getEventNumber_muTag_C2_SingleMuon);
  file_PbPb_SingleMuon->GetObject("h_vz_inclRecoMuonTag_C1",getEventNumber_muTag_C1_SingleMuon);

  file_pp_DiJet->GetObject("h_vz_inclRecoMuonTag",getEventNumber_muTag_pp_DiJet);
  file_PbPb_DiJet->GetObject("h_vz_inclRecoMuonTag_C4",getEventNumber_muTag_C4_DiJet);
  file_PbPb_DiJet->GetObject("h_vz_inclRecoMuonTag_C3",getEventNumber_muTag_C3_DiJet);
  file_PbPb_DiJet->GetObject("h_vz_inclRecoMuonTag_C2",getEventNumber_muTag_C2_DiJet);
  file_PbPb_DiJet->GetObject("h_vz_inclRecoMuonTag_C1",getEventNumber_muTag_C1_DiJet);

  file_pp_DiJet->GetObject("h_hiBin",getEventNumber_jet_pp_DiJet);
  file_PbPb_DiJet->GetObject("h_hiBin",getEventNumber_jet_C4_DiJet);
  file_PbPb_DiJet->GetObject("h_hiBin",getEventNumber_jet_C3_DiJet);
  file_PbPb_DiJet->GetObject("h_hiBin",getEventNumber_jet_C2_DiJet);
  file_PbPb_DiJet->GetObject("h_hiBin",getEventNumber_jet_C1_DiJet);

  file_pp_MinBias->GetObject("h_hiBin",getEventNumber_jet_pp_MinBias);
  file_PbPb_MinBias->GetObject("h_hiBin",getEventNumber_jet_C4_MinBias);
  file_PbPb_MinBias->GetObject("h_hiBin",getEventNumber_jet_C3_MinBias);
  file_PbPb_MinBias->GetObject("h_hiBin",getEventNumber_jet_C2_MinBias);
  file_PbPb_MinBias->GetObject("h_hiBin",getEventNumber_jet_C1_MinBias);

  file_pp_MinBias->GetObject("h_vz",getEventNumber_pp_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_C4",getEventNumber_C4_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_C3",getEventNumber_C3_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_C2",getEventNumber_C2_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_C1",getEventNumber_C1_MinBias);

  

  

  

  // merge centralities
  h_jetPt_muTag_muTrig_C3->Add(h_jetPt_muTag_muTrig_C4);
  h_jetPt_C3->Add(h_jetPt_C4);

  getEventNumber_muTag_muTrig_C3->Add(getEventNumber_muTag_muTrig_C4);
  getEventNumber_muTag_C3_SingleMuon->Add(getEventNumber_muTag_C4_SingleMuon);
  getEventNumber_muTag_C3_DiJet->Add(getEventNumber_muTag_C4_DiJet);
  getEventNumber_jet_C3_DiJet->Add(getEventNumber_jet_C4_DiJet);
  getEventNumber_jet_C3_MinBias->Add(getEventNumber_jet_C4_MinBias);
  getEventNumber_C3_MinBias->Add(getEventNumber_C4_MinBias);
  

  // get event numbers
  double N_evt_muTag_muTrig_pp, N_evt_muTag_muTrig_C3, N_evt_muTag_muTrig_C2, N_evt_muTag_muTrig_C1;
  double N_evt_muTag_pp_SingleMuon, N_evt_muTag_C3_SingleMuon, N_evt_muTag_C2_SingleMuon, N_evt_muTag_C1_SingleMuon;
  double N_evt_muTag_pp_DiJet, N_evt_muTag_C3_DiJet, N_evt_muTag_C2_DiJet, N_evt_muTag_C1_DiJet;
  double N_evt_jet_pp_DiJet, N_evt_jet_C3_DiJet, N_evt_jet_C2_DiJet, N_evt_jet_C1_DiJet;
  double N_evt_jet_pp_MinBias, N_evt_jet_C3_MinBias, N_evt_jet_C2_MinBias, N_evt_jet_C1_MinBias;
  double N_evt_pp_MinBias, N_evt_C3_MinBias, N_evt_C2_MinBias, N_evt_C1_MinBias;
  

  N_evt_muTag_muTrig_pp = getEventNumber_muTag_muTrig_pp->GetEntries();
  N_evt_muTag_muTrig_C3 = getEventNumber_muTag_muTrig_C3->GetEntries();
  N_evt_muTag_muTrig_C2 = getEventNumber_muTag_muTrig_C2->GetEntries();
  N_evt_muTag_muTrig_C1 = getEventNumber_muTag_muTrig_C1->GetEntries();

  //cout << "N_evt_muTag_muTrig_pp = " << N_evt_muTag_muTrig_pp << endl;

  N_evt_muTag_pp_SingleMuon = getEventNumber_muTag_pp_SingleMuon->GetEntries();
  N_evt_muTag_C3_SingleMuon = getEventNumber_muTag_C3_SingleMuon->GetEntries();
  N_evt_muTag_C2_SingleMuon = getEventNumber_muTag_C2_SingleMuon->GetEntries();
  N_evt_muTag_C1_SingleMuon = getEventNumber_muTag_C1_SingleMuon->GetEntries();

  //cout << "N_evt_muTag_pp_SingleMuon = " << N_evt_muTag_pp_SingleMuon << endl;

  N_evt_muTag_pp_DiJet = getEventNumber_muTag_pp_DiJet->GetEntries();
  N_evt_muTag_C3_DiJet = getEventNumber_muTag_C3_DiJet->GetEntries();
  N_evt_muTag_C2_DiJet = getEventNumber_muTag_C2_DiJet->GetEntries();
  N_evt_muTag_C1_DiJet = getEventNumber_muTag_C1_DiJet->GetEntries();

  //cout << "N_evt_muTag_pp_DiJet = " << N_evt_muTag_pp_DiJet << endl;

  N_evt_jet_pp_DiJet = getEventNumber_jet_pp_DiJet->GetEntries();
  N_evt_jet_C3_DiJet = integrate(getEventNumber_jet_C3_DiJet,60,180); 
  N_evt_jet_C2_DiJet = integrate(getEventNumber_jet_C2_DiJet,20,60);
  N_evt_jet_C1_DiJet = integrate(getEventNumber_jet_C1_DiJet,0,20);

  //cout << "N_evt_jet_pp_DiJet = " << N_evt_jet_pp_DiJet << endl;
  //cout << "N_evt_jet_C3_DiJet = " << N_evt_jet_C3_DiJet << endl;

  N_evt_jet_pp_MinBias = getEventNumber_jet_pp_MinBias->GetEntries();
  N_evt_jet_C3_MinBias = integrate(getEventNumber_jet_C3_MinBias,60,180);
  N_evt_jet_C2_MinBias = integrate(getEventNumber_jet_C2_MinBias,20,60);
  N_evt_jet_C1_MinBias = integrate(getEventNumber_jet_C1_MinBias,0,20);

  //cout << "N_evt_jet_pp_MinBias = " << N_evt_jet_pp_MinBias << endl;

  N_evt_pp_MinBias = getEventNumber_pp_MinBias->GetEntries();
  N_evt_C3_MinBias = getEventNumber_C3_MinBias->GetEntries();
  N_evt_C2_MinBias = getEventNumber_C2_MinBias->GetEntries();
  N_evt_C1_MinBias = getEventNumber_C1_MinBias->GetEntries();

  //cout << "N_evt_pp_MinBias = " << N_evt_pp_MinBias << endl;

  double f_evt_jet_pp, f_evt_jet_C3, f_evt_jet_C2, f_evt_jet_C1;
  double f_evt_muTag_pp, f_evt_muTag_C3, f_evt_muTag_C2, f_evt_muTag_C1;
  double f_evt_muTrig_pp, f_evt_muTrig_C3, f_evt_muTrig_C2, f_evt_muTrig_C1;

  f_evt_jet_pp = N_evt_jet_pp_MinBias / N_evt_pp_MinBias;
  f_evt_jet_C3 = N_evt_jet_C3_MinBias / N_evt_C3_MinBias;
  f_evt_jet_C2 = N_evt_jet_C2_MinBias / N_evt_C2_MinBias;
  f_evt_jet_C1 = N_evt_jet_C1_MinBias / N_evt_C1_MinBias;

  f_evt_muTag_pp = N_evt_muTag_pp_DiJet / N_evt_jet_pp_DiJet;
  f_evt_muTag_C3 = N_evt_muTag_C3_DiJet / N_evt_jet_C3_DiJet;
  f_evt_muTag_C2 = N_evt_muTag_C2_DiJet / N_evt_jet_C2_DiJet;
  f_evt_muTag_C1 = N_evt_muTag_C1_DiJet / N_evt_jet_C1_DiJet;

  f_evt_muTrig_pp = N_evt_muTag_muTrig_pp / N_evt_muTag_pp_SingleMuon;
  f_evt_muTrig_C3 = N_evt_muTag_muTrig_C3 / N_evt_muTag_C3_SingleMuon;
  f_evt_muTrig_C2 = N_evt_muTag_muTrig_C2 / N_evt_muTag_C2_SingleMuon;
  f_evt_muTrig_C1 = N_evt_muTag_muTrig_C1 / N_evt_muTag_C1_SingleMuon;

  cout << "f_evt_jet_pp = " << f_evt_jet_pp << endl;
  cout << "f_evt_muTag_pp = " << f_evt_muTag_pp << endl;
  cout << "f_evt_muTrig_pp = " << f_evt_muTrig_pp << endl;
  

  
  // rebin
  const int N_edge = 5;
  double newAxis[N_edge] = {80,100,120,150,200};

  h_jetPt_muTag_muTrig_pp = (TH1D*) h_jetPt_muTag_muTrig_pp->Rebin(N_edge-1,"h_jetPt_muTag_muTrig_pp",newAxis);
  divideByBinwidth(h_jetPt_muTag_muTrig_pp);

  h_jetPt_muTag_muTrig_C3 = (TH1D*) h_jetPt_muTag_muTrig_C3->Rebin(N_edge-1,"h_jetPt_muTag_muTrig_C3",newAxis);
  divideByBinwidth(h_jetPt_muTag_muTrig_C3);

  h_jetPt_muTag_muTrig_C2 = (TH1D*) h_jetPt_muTag_muTrig_C2->Rebin(N_edge-1,"h_jetPt_muTag_muTrig_C2",newAxis);
  divideByBinwidth(h_jetPt_muTag_muTrig_C2);

  h_jetPt_muTag_muTrig_C1 = (TH1D*) h_jetPt_muTag_muTrig_C1->Rebin(N_edge-1,"h_jetPt_muTag_muTrig_C1",newAxis);
  divideByBinwidth(h_jetPt_muTag_muTrig_C1);

  h_jetPt_pp = (TH1D*) h_jetPt_pp->Rebin(N_edge-1,"h_jetPt_pp",newAxis);
  divideByBinwidth(h_jetPt_pp);

  h_jetPt_C3 = (TH1D*) h_jetPt_C3->Rebin(N_edge-1,"h_jetPt_C3",newAxis);
  divideByBinwidth(h_jetPt_C3);

  h_jetPt_C2 = (TH1D*) h_jetPt_C2->Rebin(N_edge-1,"h_jetPt_C2",newAxis);
  divideByBinwidth(h_jetPt_C2);

  h_jetPt_C1 = (TH1D*) h_jetPt_C1->Rebin(N_edge-1,"h_jetPt_C1",newAxis);
  divideByBinwidth(h_jetPt_C1);

  

  stylizeHistograms(h_jetPt_muTag_muTrig_pp, h_jetPt_muTag_muTrig_C1, h_jetPt_muTag_muTrig_C2, h_jetPt_muTag_muTrig_C3);
  stylizeHistograms(h_jetPt_pp, h_jetPt_C1, h_jetPt_C2, h_jetPt_C3);


  // scale by 1/N_evt
  h_jetPt_muTag_muTrig_pp->Scale(1./N_evt_muTag_muTrig_pp);
  h_jetPt_muTag_muTrig_C3->Scale(1./N_evt_muTag_muTrig_C3);
  h_jetPt_muTag_muTrig_C2->Scale(1./N_evt_muTag_muTrig_C2);
  h_jetPt_muTag_muTrig_C1->Scale(1./N_evt_muTag_muTrig_C1);

  h_jetPt_pp->Scale(1./N_evt_pp_MinBias);
  h_jetPt_C3->Scale(1./N_evt_C3_MinBias);
  h_jetPt_C2->Scale(1./N_evt_C2_MinBias);
  h_jetPt_C1->Scale(1./N_evt_C1_MinBias);

  TLegend *leg = new TLegend(0.6,0.7,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(h_jetPt_pp,"pp","p");
  leg->AddEntry(h_jetPt_C3,"PbPb 30-90%","p");
  leg->AddEntry(h_jetPt_C2,"PbPb 10-30%","p");
  leg->AddEntry(h_jetPt_C1,"PbPb 0-10%","p");

  
  // -------------- mu-tag mu-trig spectra
  TCanvas *canv_muTag_muTrig = new TCanvas("canv_muTag_muTrig","canv_muTag_muTrig",700,700);
  canv_muTag_muTrig->cd();
  TPad *pad1_muTag_muTrig = new TPad("pad1_muTag_muTrig","pad1_muTag_muTrig",0,0,1,1);
  pad1_muTag_muTrig->SetLeftMargin(0.15);
  pad1_muTag_muTrig->SetBottomMargin(0.15);
  pad1_muTag_muTrig->SetLogy();
  pad1_muTag_muTrig->Draw();
  pad1_muTag_muTrig->cd();
  h_jetPt_muTag_muTrig_pp->GetYaxis()->SetTitle("1/#it{N}^{evt}_{#mu-tag,#mu-trig} d#it{N}^{jet}_{#mu-tag,#mu-trig}/d#it{p}_{T} [GeV^{-1}]");
  h_jetPt_muTag_muTrig_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //h_jetPt_muTag_muTrig_pp->GetYaxis()->SetRangeUser(0,0.06);
  h_jetPt_muTag_muTrig_pp->Draw();
  h_jetPt_muTag_muTrig_C3->Draw("same");
  h_jetPt_muTag_muTrig_C2->Draw("same");
  h_jetPt_muTag_muTrig_C1->Draw("same");
  leg->Draw();
  canv_muTag_muTrig->SaveAs("./figures/spectra_muTag_muTrig.pdf");
  file_MuTagMuTrigJetSpectra = (TFile*) TFile::Open("./rootFiles/MuTagMuTrigJetSpectra/Data/histograms_MuTagMuTrigJetSpectra.root","recreate");
  h_jetPt_muTag_muTrig_pp->Write();
  h_jetPt_muTag_muTrig_C3->Write();
  h_jetPt_muTag_muTrig_C2->Write();
  h_jetPt_muTag_muTrig_C1->Write();
  file_MuTagMuTrigJetSpectra->Close();


  // apply the bPurity fraction multiplication
  TH1D *h_bJetPt_muTag_muTrig_pp, *h_bJetPt_muTag_muTrig_C3, *h_bJetPt_muTag_muTrig_C2, *h_bJetPt_muTag_muTrig_C1;

  h_bJetPt_muTag_muTrig_pp = (TH1D*) h_jetPt_muTag_muTrig_pp->Clone("h_bJetPt_muTag_muTrig_pp");
  h_bJetPt_muTag_muTrig_pp->Multiply(bPurity_muTag_muTrig_pp);

  h_bJetPt_muTag_muTrig_C3 = (TH1D*) h_jetPt_muTag_muTrig_C3->Clone("h_bJetPt_muTag_muTrig_C3");
  h_bJetPt_muTag_muTrig_C3->Multiply(bPurity_muTag_muTrig_C3);

  h_bJetPt_muTag_muTrig_C2 = (TH1D*) h_jetPt_muTag_muTrig_C2->Clone("h_bJetPt_muTag_muTrig_C2");
  h_bJetPt_muTag_muTrig_C2->Multiply(bPurity_muTag_muTrig_C2);

  h_bJetPt_muTag_muTrig_C1 = (TH1D*) h_jetPt_muTag_muTrig_C1->Clone("h_bJetPt_muTag_muTrig_C1");
  h_bJetPt_muTag_muTrig_C1->Multiply(bPurity_muTag_muTrig_C1);

  TCanvas *canv_bJet_muTag_muTrig = new TCanvas("canv_bJet_muTag_muTrig","canv_bJet_muTag_muTrig",700,700);
  canv_bJet_muTag_muTrig->cd();
  TPad *pad1_bJet_muTag_muTrig = new TPad("pad1_bJet_muTag_muTrig","pad1_bJet_muTag_muTrig",0,0,1,1);
  pad1_bJet_muTag_muTrig->SetLogy();
  pad1_bJet_muTag_muTrig->SetLeftMargin(0.15);
  pad1_bJet_muTag_muTrig->SetBottomMargin(0.15);
  pad1_bJet_muTag_muTrig->Draw();
  pad1_bJet_muTag_muTrig->cd();
  h_bJetPt_muTag_muTrig_pp->GetYaxis()->SetTitle("1/#it{N}^{evt}_{#mu-tag,#mu-trig} d#it{N}^{#it{b}-jet}_{#mu-tag,#mu-trig}/d#it{p}_{T} [GeV^{-1}]");
  h_bJetPt_muTag_muTrig_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //h_bJetPt_muTag_muTrig_pp->GetYaxis()->SetRangeUser(0,0.06);
  h_bJetPt_muTag_muTrig_pp->Draw();
  h_bJetPt_muTag_muTrig_C3->Draw("same");
  h_bJetPt_muTag_muTrig_C2->Draw("same");
  h_bJetPt_muTag_muTrig_C1->Draw("same");
  leg->Draw();
  canv_bJet_muTag_muTrig->SaveAs("./figures/spectra_bJet_muTag_muTrig.pdf");
  file_MuTagMuTrigBJetSpectra = (TFile*) TFile::Open("./rootFiles/MuTagMuTrigBJetSpectra/Data/histograms_MuTagMuTrigBJetSpectra.root","recreate");
  h_bJetPt_muTag_muTrig_pp->Write();
  h_bJetPt_muTag_muTrig_C3->Write();
  h_bJetPt_muTag_muTrig_C2->Write();
  h_bJetPt_muTag_muTrig_C1->Write();
  file_MuTagMuTrigBJetSpectra->Close();


  //  bPurity_muTag_muTrig_pp->Draw();
  

  // apply the correction factors
  TH1D *h_bJetPt_corr_pp, *h_bJetPt_corr_C3, *h_bJetPt_corr_C2, *h_bJetPt_corr_C1;

  h_bJetPt_corr_pp = (TH1D*) h_bJetPt_muTag_muTrig_pp->Clone("h_bJetPt_corr_pp");
  h_bJetPt_corr_C3 = (TH1D*) h_bJetPt_muTag_muTrig_C3->Clone("h_bJetPt_corr_C3");
  h_bJetPt_corr_C2 = (TH1D*) h_bJetPt_muTag_muTrig_C2->Clone("h_bJetPt_corr_C2");
  h_bJetPt_corr_C1 = (TH1D*) h_bJetPt_muTag_muTrig_C1->Clone("h_bJetPt_corr_C1");

  h_bJetPt_corr_pp->Divide(corrFactor_3d_pp);
  h_bJetPt_corr_pp->Divide(corrFactor_2_pp);
  h_bJetPt_corr_pp->Divide(corrFactor_1_pp);
  h_bJetPt_corr_pp->Scale(f_evt_jet_pp * f_evt_muTag_pp * f_evt_muTrig_pp);

  h_bJetPt_corr_C3->Divide(corrFactor_3d_C3);
  h_bJetPt_corr_C3->Divide(corrFactor_2_C3);
  h_bJetPt_corr_C3->Divide(corrFactor_1_C3);
  h_bJetPt_corr_C3->Scale(f_evt_jet_C3 * f_evt_muTag_C3 * f_evt_muTrig_C3);

  h_bJetPt_corr_C2->Divide(corrFactor_3d_C2);
  h_bJetPt_corr_C2->Divide(corrFactor_2_C2);
  h_bJetPt_corr_C2->Divide(corrFactor_1_C2);
  h_bJetPt_corr_C2->Scale(f_evt_jet_C2 * f_evt_muTag_C2 * f_evt_muTrig_C2);

  h_bJetPt_corr_C1->Divide(corrFactor_3d_C1);
  h_bJetPt_corr_C1->Divide(corrFactor_2_C1);
  h_bJetPt_corr_C1->Divide(corrFactor_1_C1);
  h_bJetPt_corr_C1->Scale(f_evt_jet_C1 * f_evt_muTag_C1 * f_evt_muTrig_C1);

  TCanvas *canv_bJet_corr = new TCanvas("canv_bJet_corr","canv_bJet_corr",700,700);
  canv_bJet_corr->cd();
  TPad *pad1_bJet_corr = new TPad("pad1_bJet_corr","pad1_bJet_corr",0,0,1,1);
  pad1_bJet_corr->SetLogy();
  pad1_bJet_corr->SetLeftMargin(0.15);
  pad1_bJet_corr->SetBottomMargin(0.15);
  pad1_bJet_corr->Draw();
  pad1_bJet_corr->cd();
  h_bJetPt_corr_pp->GetYaxis()->SetTitle("1/#it{N}^{evt}_{equiv-MinBias} d#it{N}^{corr-#it{b}}/d#it{p}_{T} [GeV^{-1}]");
  h_bJetPt_corr_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_bJetPt_corr_pp->GetYaxis()->SetRangeUser(2e-10,5e-3);
  h_bJetPt_corr_pp->Draw();
  h_bJetPt_corr_C3->Draw("same");
  h_bJetPt_corr_C2->Draw("same");
  h_bJetPt_corr_C1->Draw("same");
  leg->Draw();
  canv_bJet_corr->SaveAs("./figures/spectra_bJet_corr.pdf");
  file_CorrectedBJetSpectra = (TFile*) TFile::Open("./rootFiles/CorrectedBJetSpectra/Data/histograms_CorrectedBJetSpectra.root","recreate");
  h_bJetPt_corr_pp->Write();
  h_bJetPt_corr_C3->Write();
  h_bJetPt_corr_C2->Write();
  h_bJetPt_corr_C1->Write();
  file_CorrectedBJetSpectra->Close();


  TCanvas *canv_MinBias = new TCanvas("canv_MinBias","canv_MinBias",700,700);
  canv_MinBias->cd();
  TPad *pad1_MinBias = new TPad("pad1_MinBias","pad1_MinBias",0,0,1,1);
  pad1_MinBias->SetLogy();
  pad1_MinBias->SetLeftMargin(0.15);
  pad1_MinBias->SetBottomMargin(0.15);
  pad1_MinBias->Draw();
  pad1_MinBias->cd();
  h_jetPt_pp->GetYaxis()->SetTitle("1/#it{N}^{evt}_{MinBias} d#it{N}^{jet}/d#it{p}_{T} [GeV^{-1}]");
  h_jetPt_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_jetPt_pp->GetYaxis()->SetRangeUser(2e-10,5e-3);
  h_jetPt_pp->Draw();
  h_jetPt_C3->Draw("same");
  h_jetPt_C2->Draw("same");
  h_jetPt_C1->Draw("same");
  leg->Draw();
  canv_MinBias->SaveAs("./figures/spectra_MinBias.pdf");
  file_MinBiasJetSpectra = (TFile*) TFile::Open("./rootFiles/MinBiasJetSpectra/Data/histograms_MinBiasJetSpectra.root","recreate");
  h_jetPt_pp->Write();
  h_jetPt_C3->Write();
  h_jetPt_C2->Write();
  h_jetPt_C1->Write();
  file_MinBiasJetSpectra->Close();


  TH1D *bFraction_C3 = (TH1D*) h_bJetPt_corr_C3->Clone("bFraction_C3");
  bFraction_C3->Divide(h_bJetPt_corr_C3,h_bJetPt_corr_pp,1,1,"");

  TH1D *bFraction_C2 = (TH1D*) h_bJetPt_corr_C2->Clone("bFraction_C2");
  bFraction_C2->Divide(h_bJetPt_corr_C2,h_bJetPt_corr_pp,1,1,"");

  TH1D *bFraction_C1 = (TH1D*) h_bJetPt_corr_C1->Clone("bFraction_C1");
  bFraction_C1->Divide(h_bJetPt_corr_C1,h_bJetPt_corr_pp,1,1,"");

  TH1D *inclFraction_C3 = (TH1D*) h_jetPt_C3->Clone("inclFraction_C3");
  inclFraction_C3->Divide(h_jetPt_C3,h_jetPt_pp,1,1,"");
  
  TH1D *inclFraction_C2 = (TH1D*) h_jetPt_C2->Clone("inclFraction_C2");
  inclFraction_C2->Divide(h_jetPt_C2,h_jetPt_pp,1,1,"");
  
  TH1D *inclFraction_C1 = (TH1D*) h_jetPt_C1->Clone("inclFraction_C1");
  inclFraction_C1->Divide(h_jetPt_C1,h_jetPt_pp,1,1,"");

  TH1D *inclBFraction_pp = (TH1D*) h_bJetPt_corr_pp->Clone("inclBFraction_pp");
  inclBFraction_pp->Divide(h_bJetPt_corr_pp,h_jetPt_pp,1,1,"");

  TH1D *inclBFraction_C3 = (TH1D*) h_bJetPt_corr_C3->Clone("inclBFraction_C3");
  inclBFraction_C3->Divide(h_bJetPt_corr_C3,h_jetPt_C3,1,1,"");

  TH1D *inclBFraction_C2 = (TH1D*) h_bJetPt_corr_C2->Clone("inclBFraction_C2");
  inclBFraction_C2->Divide(h_bJetPt_corr_C2,h_jetPt_C2,1,1,"");

  TH1D *inclBFraction_C1 = (TH1D*) h_bJetPt_corr_C1->Clone("inclBFraction_C1");
  inclBFraction_C1->Divide(h_bJetPt_corr_C1,h_jetPt_C1,1,1,"");

  TCanvas *canv_inclBFraction = new TCanvas("canv_inclBFraction","canv_inclBFraction",700,700);
  canv_inclBFraction->cd();
  TPad *pad1_inclBFraction = new TPad("pad1_inclBFraction","pad1_inclBFraction",0,0,1,1);
  //pad1_inclBFraction->SetLogy();
  pad1_inclBFraction->SetLeftMargin(0.15);
  pad1_inclBFraction->SetBottomMargin(0.15);
  pad1_inclBFraction->Draw();
  pad1_inclBFraction->cd();
  inclBFraction_pp->GetYaxis()->SetTitle("Inclusive #it{b}-jet fraction");
  inclBFraction_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  inclBFraction_pp->GetYaxis()->SetRangeUser(0.02,0.05);
  inclBFraction_pp->Draw();
  // inclBFraction_C3->Draw("same");
  // inclBFraction_C2->Draw("same");
  // inclBFraction_C1->Draw("same");
  leg->Draw();
  canv_inclBFraction->SaveAs("./figures/inclusiveBJetFraction.pdf");
  file_InclusiveBJetFraction = (TFile*) TFile::Open("./rootFiles/InclusiveBJetFraction/Data/histograms_InclusiveBJetFraction.root","recreate");
  inclBFraction_pp->Write();
  inclBFraction_C3->Write();
  inclBFraction_C2->Write();
  inclBFraction_C1->Write();
  file_InclusiveBJetFraction->Close();
  
  TCanvas *canv_bFraction = new TCanvas("canv_bFraction","canv_bFraction",700,700);
  canv_bFraction->cd();
  TPad *pad1_bFraction = new TPad("pad1_bFraction","pad1_bFraction",0,0,1,1);
  //pad1_bFraction->SetLogy();
  pad1_bFraction->SetLeftMargin(0.15);
  pad1_bFraction->SetBottomMargin(0.15);
  pad1_bFraction->Draw();
  pad1_bFraction->cd();
  bFraction_C3->GetYaxis()->SetTitle("Ratio of corrected #it{b}-jet spectra (PbPb / pp)");
  bFraction_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  bFraction_C3->GetYaxis()->SetRangeUser(0,2700);
  bFraction_C3->Draw();
  bFraction_C2->Draw("same");
  bFraction_C1->Draw("same");
  canv_bFraction->SaveAs("./figures/bJetPbPbToPP.pdf");
  file_BJetPbPbToPP = (TFile*) TFile::Open("./rootFiles/BJetPbPbToPP/Data/histograms_BJetPbPbToPP.root","recreate");
  bFraction_C3->Write();
  bFraction_C2->Write();
  bFraction_C1->Write();
  file_BJetPbPbToPP->Close();

  TCanvas *canv_inclFraction = new TCanvas("canv_inclFraction","canv_inclFraction",700,700);
  canv_inclFraction->cd();
  TPad *pad1_inclFraction = new TPad("pad1_inclFraction","pad1_inclFraction",0,0,1,1);
  //pad1_inclFraction->SetLogy();
  pad1_inclFraction->SetLeftMargin(0.15);
  pad1_inclFraction->SetBottomMargin(0.15);
  pad1_inclFraction->Draw();
  pad1_inclFraction->cd();
  inclFraction_C3->GetYaxis()->SetTitle("Ratio of inclusive jet-spectra (PbPb / pp)");
  inclFraction_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  inclFraction_C3->GetYaxis()->SetRangeUser(0,2700);
  inclFraction_C3->Draw();
  inclFraction_C2->Draw("same");
  inclFraction_C1->Draw("same");
  canv_inclFraction->SaveAs("./figures/inclJetPbPbToPP.pdf");
  file_InclJetPbPbToPP = (TFile*) TFile::Open("./rootFiles/InclJetPbPbToPP/Data/histograms_InclJetPbPbToPP.root","recreate");
  inclFraction_C3->Write();
  inclFraction_C2->Write();
  inclFraction_C1->Write();
  file_InclJetPbPbToPP->Close();

  TH1D *R_C3 = (TH1D*) bFraction_C3->Clone("R_C3");
  R_C3->Divide(bFraction_C3,inclFraction_C3,1,1,"");

  TH1D *R_C2 = (TH1D*) bFraction_C2->Clone("R_C2");
  R_C2->Divide(bFraction_C2,inclFraction_C2,1,1,"");

  TH1D *R_C1 = (TH1D*) bFraction_C1->Clone("R_C1");
  R_C1->Divide(bFraction_C1,inclFraction_C1,1,1,"");  

  TCanvas *canv_R = new TCanvas("canv_R","canv_R",700,700);
  canv_R->cd();
  TPad *pad1_R = new TPad("pad1_R","pad1_R",0,0,1,1);
  //pad1_R->SetLogy();
  pad1_R->SetLeftMargin(0.15);
  pad1_R->SetBottomMargin(0.15);
  pad1_R->Draw();
  pad1_R->cd();
  R_C3->GetYaxis()->SetTitle("R^{b-corr}(PbPb/pp) / R^{incl}(PbPb/pp)");
  R_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  R_C3->GetYaxis()->SetRangeUser(0,3.2);
  R_C3->Draw();
  R_C2->Draw("same");
  R_C1->Draw("same");
  canv_R->SaveAs("./figures/doubleRatio.pdf");
  file_DoubleRatio = (TFile*) TFile::Open("./rootFiles/DoubleRatio/Data/histograms_DoubleRatio.root","recreate");
  R_C3->Write();
  R_C2->Write();
  R_C1->Write();
  file_DoubleRatio->Close();
  
  

}
