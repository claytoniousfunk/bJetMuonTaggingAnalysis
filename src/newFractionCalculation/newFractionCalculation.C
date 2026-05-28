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


void newFractionCalculation(bool useDiJetNormalizationForPP = false,
			    bool useMinBiasNormalizationForPP = true){

  TFile *file_MinBiasJetSpectra, *file_CorrectedBJetSpectra, *file_MuTagMuTrigBJetSpectra, *file_DoubleRatio, *file_InclJetPbPbToPP, *file_BJetPbPbToPP, *file_InclusiveBJetFraction, *file_MuTagMuTrigJetSpectra;

  TLine *li = new TLine();

  TFile *file_bFrac_CMS_pp_7TeV = TFile::Open("../../rootFiles/HEPData/JHEP042012084/bFrac.root");
  TH1F *bFrac_CMS_pp_7TeV;
  file_bFrac_CMS_pp_7TeV->GetObject("bFrac",bFrac_CMS_pp_7TeV);


  bFrac_CMS_pp_7TeV->SetLineColor(kPink-9);
  bFrac_CMS_pp_7TeV->SetMarkerColor(kPink-9);
  bFrac_CMS_pp_7TeV->SetMarkerStyle(33);
  bFrac_CMS_pp_7TeV->SetMarkerSize(2.5);
  bFrac_CMS_pp_7TeV->SetLineWidth(4);
  

  // load bPurity information

  //TFile *file_bPurity = TFile::Open("../../rootFiles/bPurityResults/latest/bPurityResults_DATA-1_mergeB-1_mergeC-1_pTrel-0.0to3.0_cMult-1.0_bMult-1.175_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0_centShiftUp-0_centShiftDown-0.root");
  TFile *file_bPurity = TFile::Open("../../rootFiles/bPurityResults/latest/pp_inclMuons.root");
  
  TH1D *bPurity_muTag_muTrig_pp, *bPurity_muTag_muTrig_C4, *bPurity_muTag_muTrig_C3, *bPurity_muTag_muTrig_C2, *bPurity_muTag_muTrig_C1;
  
  file_bPurity->GetObject("bFracResults_pp",bPurity_muTag_muTrig_pp);
  file_bPurity->GetObject("bFracResults_C4",bPurity_muTag_muTrig_C4);
  file_bPurity->GetObject("bFracResults_C3",bPurity_muTag_muTrig_C3);
  file_bPurity->GetObject("bFracResults_C2",bPurity_muTag_muTrig_C2);
  file_bPurity->GetObject("bFracResults_C1",bPurity_muTag_muTrig_C1);


  // load correction factors information
  
  TFile *file_corrFactors_pp = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_pp.root");
  TFile *file_corrFactors_C4 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C4.root");
  TFile *file_corrFactors_C3 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C3.root");
  TFile *file_corrFactors_C2 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C2.root");
  TFile *file_corrFactors_C1 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C1.root");

  TH1D *corrFactor_1_pp, *corrFactor_2_pp, *corrFactor_3_pp, *corrFactor_3d_pp;
  TH1D *corrFactor_1_C4, *corrFactor_2_C4, *corrFactor_3_C4, *corrFactor_3d_C4;
  TH1D *corrFactor_1_C3, *corrFactor_2_C3, *corrFactor_3_C3, *corrFactor_3d_C3;
  TH1D *corrFactor_1_C2, *corrFactor_2_C2, *corrFactor_3_C2, *corrFactor_3d_C2;
  TH1D *corrFactor_1_C1, *corrFactor_2_C1, *corrFactor_3_C1, *corrFactor_3d_C1;

  file_corrFactors_pp->GetObject("corrFactor_1_pp",corrFactor_1_pp);
  file_corrFactors_pp->GetObject("corrFactor_2_pp",corrFactor_2_pp);
  file_corrFactors_pp->GetObject("corrFactor_3_pp",corrFactor_3_pp);
  file_corrFactors_pp->GetObject("corrFactor_3_data_pp",corrFactor_3d_pp);

  file_corrFactors_C4->GetObject("corrFactor_1_C4",corrFactor_1_C4);
  file_corrFactors_C4->GetObject("corrFactor_2_C4",corrFactor_2_C4);
  file_corrFactors_C4->GetObject("corrFactor_3_C4",corrFactor_3_C4);
  file_corrFactors_C4->GetObject("corrFactor_3_data_C4",corrFactor_3d_C4);

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

  setErrorsToZero(corrFactor_1_C4);
  setErrorsToZero(corrFactor_2_C4);
  setErrorsToZero(corrFactor_3_C4);
  setErrorsToZero(corrFactor_3d_C4);

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

  TFile *file_PY_DiJet = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-20_removeHYDJETjet0p45_jetTrkMaxFilter_vzReweight_jetPtReweight_projectableTemplates_2025-06-17.root");

  TH2D *H_mcJetPt_flavor_pp;
  TH1D *h_mcJetPt_pp;
  TH1D *h_mcBJetPt_pp, *h_mcBBarJetPt_pp, *h_mcBGSJetPt_pp;

  file_PY_DiJet->GetObject("h_inclRecoJetPt_flavor",H_mcJetPt_flavor_pp);
  TH1D *binFinder = H_mcJetPt_flavor_pp->ProjectionY();
  double ss = 0.1;
  h_mcJetPt_pp = (TH1D*) H_mcJetPt_flavor_pp->ProjectionX("h_mcJetPt_pp",binFinder->FindBin(-5+ss),binFinder->FindBin(22-ss));
  h_mcBJetPt_pp = (TH1D*) H_mcJetPt_flavor_pp->ProjectionX("h_mcBJetPt_pp",binFinder->FindBin(5+ss),binFinder->FindBin(6-ss));
  h_mcBBarJetPt_pp = (TH1D*) H_mcJetPt_flavor_pp->ProjectionX("h_mcBBarJetPt_pp",binFinder->FindBin(-5+ss),binFinder->FindBin(-4-ss));
  h_mcBGSJetPt_pp = (TH1D*) H_mcJetPt_flavor_pp->ProjectionX("h_mcBGSJetPt_pp",binFinder->FindBin(17+ss),binFinder->FindBin(18-ss));
  h_mcBJetPt_pp->Add(h_mcBBarJetPt_pp);
  h_mcBJetPt_pp->Add(h_mcBGSJetPt_pp);

  TH1D *r_mcBJetPt_pp;
  r_mcBJetPt_pp = (TH1D*) h_mcBJetPt_pp->Clone("r_mcBJetPt_pp");
  r_mcBJetPt_pp->Divide(h_mcBJetPt_pp,h_mcJetPt_pp,1,1,"B");

  r_mcBJetPt_pp->Draw();

 
  // load spectra
  // TFile *file_pp_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15_tight_jetTrkMaxFilter_WDecayFilter_2026-2-10.root");
  // TFile *file_pp_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_MinBias_mu12_pTmu-14_tight_jetTrkMaxFilter_2025-10-15.root");
  // TFile *file_pp_DiJet = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet60HLT_mu12_pTmu-14_tight_jetTrkMaxFilter_2025-10-24.root");
  // TFile *file_PbPb_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15_tight_mu12TriggerEfficiencyCorrection_WDecayFilter_2026-2-12.root");
  // TFile *file_PbPb_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_MinBias_scan_mu12_tight_pTmu-14_hiHFcut_2025-10-16.root");
  // TFile *file_PbPb_DiJet = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet60HLT_mu12_tight_pTmu-14_hiHFcut_2025-10-27.root");


  TFile *file_pp_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15_tight_mu12TriggerEfficiencyCorrection_jetTrkMaxFilter_2026-2-12.root");
  TFile *file_pp_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_MinBias_mu12_pTmu-14_tight_jetTrkMaxFilter_2025-10-15.root");
  TFile *file_pp_DiJet = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet60HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-5.root");
  TFile *file_PbPb_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15to999_tight_mu12TriggerEfficiencyCorrection_WDecayFilter_2026-4-9.root");
  TFile *file_PbPb_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_MinBias_mu12_pTmu-15to999_tight_2026-3-5.root");
  TFile *file_PbPb_DiJet = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet60HLT_mu12_pTmu-15to999_tight_2026-3-5.root");
  


  TH1D *h_jetPt_muTag_muTrig_pp, *h_jetPt_muTag_muTrig_C4, *h_jetPt_muTag_muTrig_C3, *h_jetPt_muTag_muTrig_C2, *h_jetPt_muTag_muTrig_C1;
  TH1D *h_jetPt_pp, *h_jetPt_C4, *h_jetPt_C3, *h_jetPt_C2, *h_jetPt_C1;
  
  TH1D *getEventNumber_muTag_muTrig_pp, *getEventNumber_muTag_muTrig_C4, *getEventNumber_muTag_muTrig_C3, *getEventNumber_muTag_muTrig_C2, *getEventNumber_muTag_muTrig_C1;
  TH1D *getEventNumber_muTag_pp_SingleMuon, *getEventNumber_muTag_C4_SingleMuon, *getEventNumber_muTag_C3_SingleMuon, *getEventNumber_muTag_C2_SingleMuon, *getEventNumber_muTag_C1_SingleMuon;
  TH1D *getEventNumber_muTag_pp_DiJet, *getEventNumber_muTag_C4_DiJet, *getEventNumber_muTag_C3_DiJet, *getEventNumber_muTag_C2_DiJet, *getEventNumber_muTag_C1_DiJet;
  TH1D *getEventNumber_jet_pp_DiJet, *getEventNumber_jet_C4_DiJet, *getEventNumber_jet_C3_DiJet, *getEventNumber_jet_C2_DiJet, *getEventNumber_jet_C1_DiJet;
  TH1D *getEventNumber_jet_pp_MinBias, *getEventNumber_jet_C4_MinBias, *getEventNumber_jet_C3_MinBias, *getEventNumber_jet_C2_MinBias, *getEventNumber_jet_C1_MinBias;
  TH1D *getEventNumber_pp_MinBias, *getEventNumber_C4_MinBias, *getEventNumber_C3_MinBias, *getEventNumber_C2_MinBias, *getEventNumber_C1_MinBias;
  TH1D *getEventNumber_pp_DiJet, *getEventNumber_C4_DiJet, *getEventNumber_C3_DiJet, *getEventNumber_C2_DiJet, *getEventNumber_C1_DiJet;

  TH1D *h_dimuonMass_pp, *h_dimuonMass_C4, *h_dimuonMass_C3, *h_dimuonMass_C2, *h_dimuonMass_C1;


  // jet spectra histograms
  file_pp_SingleMuon->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_jetPt_muTag_muTrig_pp);
  file_PbPb_SingleMuon->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",h_jetPt_muTag_muTrig_C4);
  file_PbPb_SingleMuon->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",h_jetPt_muTag_muTrig_C3);
  file_PbPb_SingleMuon->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",h_jetPt_muTag_muTrig_C2);
  file_PbPb_SingleMuon->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",h_jetPt_muTag_muTrig_C1);

  if(useMinBiasNormalizationForPP) file_pp_MinBias->GetObject("h_inclRecoJetPt",h_jetPt_pp);
  else if(useDiJetNormalizationForPP) file_pp_DiJet->GetObject("h_inclRecoJetPt",h_jetPt_pp);
  else{file_pp_MinBias->GetObject("h_inclRecoJetPt",h_jetPt_pp);}
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C4",h_jetPt_C4);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C3",h_jetPt_C3);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C2",h_jetPt_C2);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C1",h_jetPt_C1);

  
  // file_PbPb_DiJet->GetObject("h_inclRecoJetPt_C4",h_jetPt_C4);
  // file_PbPb_DiJet->GetObject("h_inclRecoJetPt_C3",h_jetPt_C3);
  // file_PbPb_DiJet->GetObject("h_inclRecoJetPt_C2",h_jetPt_C2);
  // file_PbPb_DiJet->GetObject("h_inclRecoJetPt_C1",h_jetPt_C1);


  // /////// dimuon mass histograms
  file_pp_SingleMuon->GetObject("h_dimuonMass",h_dimuonMass_pp);
  file_PbPb_SingleMuon->GetObject("h_dimuonMass_C4",h_dimuonMass_C4);
  file_PbPb_SingleMuon->GetObject("h_dimuonMass_C3",h_dimuonMass_C3);
  file_PbPb_SingleMuon->GetObject("h_dimuonMass_C2",h_dimuonMass_C2);
  file_PbPb_SingleMuon->GetObject("h_dimuonMass_C1",h_dimuonMass_C1);

  double NZ_pp = h_dimuonMass_pp->Integral(h_dimuonMass_pp->GetXaxis()->FindBin(75),h_dimuonMass_pp->GetXaxis()->FindBin(105));
  double NZ_C4 = h_dimuonMass_C4->Integral(h_dimuonMass_C4->GetXaxis()->FindBin(75),h_dimuonMass_C4->GetXaxis()->FindBin(105));
  double NZ_C3 = h_dimuonMass_C3->Integral(h_dimuonMass_C3->GetXaxis()->FindBin(75),h_dimuonMass_C3->GetXaxis()->FindBin(105));
  double NZ_C2 = h_dimuonMass_C2->Integral(h_dimuonMass_C2->GetXaxis()->FindBin(75),h_dimuonMass_C2->GetXaxis()->FindBin(105));
  double NZ_C1 = h_dimuonMass_C1->Integral(h_dimuonMass_C1->GetXaxis()->FindBin(75),h_dimuonMass_C1->GetXaxis()->FindBin(105));





  
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

  file_pp_DiJet->GetObject("h_hiBin_jet",getEventNumber_jet_pp_DiJet); // new
  file_PbPb_DiJet->GetObject("h_vz_jet_C4",getEventNumber_jet_C4_DiJet);
  file_PbPb_DiJet->GetObject("h_vz_jet_C3",getEventNumber_jet_C3_DiJet);
  file_PbPb_DiJet->GetObject("h_vz_jet_C2",getEventNumber_jet_C2_DiJet);
  file_PbPb_DiJet->GetObject("h_vz_jet_C1",getEventNumber_jet_C1_DiJet);

  // file_pp_DiJet->GetObject("h_hiBin",getEventNumber_jet_pp_DiJet); // old
  // file_PbPb_DiJet->GetObject("h_hiBin",getEventNumber_jet_C4_DiJet);
  // file_PbPb_DiJet->GetObject("h_hiBin",getEventNumber_jet_C3_DiJet);
  // file_PbPb_DiJet->GetObject("h_hiBin",getEventNumber_jet_C2_DiJet);
  // file_PbPb_DiJet->GetObject("h_hiBin",getEventNumber_jet_C1_DiJet);

  file_pp_MinBias->GetObject("h_hiBin",getEventNumber_jet_pp_MinBias); // new
  file_PbPb_MinBias->GetObject("h_vz_jet_C4",getEventNumber_jet_C4_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_jet_C3",getEventNumber_jet_C3_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_jet_C2",getEventNumber_jet_C2_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_jet_C1",getEventNumber_jet_C1_MinBias);

  // file_pp_MinBias->GetObject("h_hiBin",getEventNumber_jet_pp_MinBias); // old
  // file_PbPb_MinBias->GetObject("h_hiBin",getEventNumber_jet_C4_MinBias);
  // file_PbPb_MinBias->GetObject("h_hiBin",getEventNumber_jet_C3_MinBias);
  // file_PbPb_MinBias->GetObject("h_hiBin",getEventNumber_jet_C2_MinBias);
  // file_PbPb_MinBias->GetObject("h_hiBin",getEventNumber_jet_C1_MinBias);

  file_pp_MinBias->GetObject("h_vz",getEventNumber_pp_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_C4",getEventNumber_C4_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_C3",getEventNumber_C3_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_C2",getEventNumber_C2_MinBias);
  file_PbPb_MinBias->GetObject("h_vz_C1",getEventNumber_C1_MinBias);

  // // use dijet in denominator
  if(useDiJetNormalizationForPP){
    file_pp_DiJet->GetObject("h_vz",getEventNumber_jet_pp_DiJet);
    file_pp_DiJet->GetObject("h_vz",getEventNumber_jet_pp_MinBias);
    file_pp_DiJet->GetObject("h_vz",getEventNumber_pp_MinBias);
  }

  // file_PbPb_DiJet->GetObject("h_vz_C4",getEventNumber_jet_C4_DiJet);
  // file_PbPb_DiJet->GetObject("h_vz_C4",getEventNumber_jet_C4_MinBias);
  // file_PbPb_DiJet->GetObject("h_vz_C4",getEventNumber_C4_MinBias);

  // file_PbPb_DiJet->GetObject("h_vz_C3",getEventNumber_jet_C3_DiJet);
  // file_PbPb_DiJet->GetObject("h_vz_C3",getEventNumber_jet_C3_MinBias);
  // file_PbPb_DiJet->GetObject("h_vz_C3",getEventNumber_C3_MinBias);

  // file_PbPb_DiJet->GetObject("h_vz_C2",getEventNumber_jet_C2_DiJet);
  // file_PbPb_DiJet->GetObject("h_vz_C2",getEventNumber_jet_C2_MinBias);
  // file_PbPb_DiJet->GetObject("h_vz_C2",getEventNumber_C2_MinBias);

  // file_PbPb_DiJet->GetObject("h_vz_C1",getEventNumber_jet_C1_DiJet);
  // file_PbPb_DiJet->GetObject("h_vz_C1",getEventNumber_jet_C1_MinBias);
  // file_PbPb_DiJet->GetObject("h_vz_C1",getEventNumber_C1_MinBias);
  

  // merge centralities
  // h_jetPt_muTag_muTrig_C3->Add(h_jetPt_muTag_muTrig_C4);
  // h_jetPt_C3->Add(h_jetPt_C4);

  // getEventNumber_muTag_muTrig_C3->Add(getEventNumber_muTag_muTrig_C4);
  // getEventNumber_muTag_C3_SingleMuon->Add(getEventNumber_muTag_C4_SingleMuon);
  // getEventNumber_muTag_C3_DiJet->Add(getEventNumber_muTag_C4_DiJet);
  // getEventNumber_jet_C3_DiJet->Add(getEventNumber_jet_C4_DiJet);
  // getEventNumber_jet_C3_MinBias->Add(getEventNumber_jet_C4_MinBias);
  // getEventNumber_C3_MinBias->Add(getEventNumber_C4_MinBias);
  

  // get event numbers
  double N_evt_muTag_muTrig_pp, N_evt_muTag_muTrig_C4, N_evt_muTag_muTrig_C3, N_evt_muTag_muTrig_C2, N_evt_muTag_muTrig_C1;
  double N_evt_muTag_pp_SingleMuon, N_evt_muTag_C4_SingleMuon, N_evt_muTag_C3_SingleMuon, N_evt_muTag_C2_SingleMuon, N_evt_muTag_C1_SingleMuon;
  double N_evt_muTag_pp_DiJet, N_evt_muTag_C4_DiJet, N_evt_muTag_C3_DiJet, N_evt_muTag_C2_DiJet, N_evt_muTag_C1_DiJet;
  double N_evt_jet_pp_DiJet, N_evt_jet_C4_DiJet, N_evt_jet_C3_DiJet, N_evt_jet_C2_DiJet, N_evt_jet_C1_DiJet;
  double N_evt_jet_pp_MinBias, N_evt_jet_C4_MinBias, N_evt_jet_C3_MinBias, N_evt_jet_C2_MinBias, N_evt_jet_C1_MinBias;
  double N_evt_pp_MinBias, N_evt_C4_MinBias, N_evt_C3_MinBias, N_evt_C2_MinBias, N_evt_C1_MinBias;
  

  N_evt_muTag_muTrig_pp = getEventNumber_muTag_muTrig_pp->GetEntries();
  N_evt_muTag_muTrig_C4 = getEventNumber_muTag_muTrig_C4->Integral();
  N_evt_muTag_muTrig_C3 = getEventNumber_muTag_muTrig_C3->Integral();
  N_evt_muTag_muTrig_C2 = getEventNumber_muTag_muTrig_C2->Integral();
  N_evt_muTag_muTrig_C1 = getEventNumber_muTag_muTrig_C1->Integral();

  cout << "N_evt_muTag_muTrig_pp = " << N_evt_muTag_muTrig_pp << endl;

  N_evt_muTag_pp_SingleMuon = getEventNumber_muTag_pp_SingleMuon->GetEntries();
  N_evt_muTag_C4_SingleMuon = getEventNumber_muTag_C4_SingleMuon->Integral();
  N_evt_muTag_C3_SingleMuon = getEventNumber_muTag_C3_SingleMuon->Integral();
  N_evt_muTag_C2_SingleMuon = getEventNumber_muTag_C2_SingleMuon->Integral();
  N_evt_muTag_C1_SingleMuon = getEventNumber_muTag_C1_SingleMuon->Integral();

  cout << "N_evt_muTag_pp_SingleMuon = " << N_evt_muTag_pp_SingleMuon << endl;

  N_evt_muTag_pp_DiJet = getEventNumber_muTag_pp_DiJet->GetEntries();
  N_evt_muTag_C4_DiJet = getEventNumber_muTag_C4_DiJet->Integral();
  N_evt_muTag_C3_DiJet = getEventNumber_muTag_C3_DiJet->Integral();
  N_evt_muTag_C2_DiJet = getEventNumber_muTag_C2_DiJet->Integral();
  N_evt_muTag_C1_DiJet = getEventNumber_muTag_C1_DiJet->Integral();

  cout << "N_evt_muTag_pp_DiJet = " << N_evt_muTag_pp_DiJet << endl;

  N_evt_jet_pp_DiJet = getEventNumber_jet_pp_DiJet->GetEntries(); // new
  N_evt_jet_C4_DiJet = getEventNumber_jet_C4_DiJet->Integral();
  N_evt_jet_C3_DiJet = getEventNumber_jet_C3_DiJet->Integral();
  N_evt_jet_C2_DiJet = getEventNumber_jet_C2_DiJet->Integral();
  N_evt_jet_C1_DiJet = getEventNumber_jet_C1_DiJet->Integral();

  // N_evt_jet_pp_DiJet = getEventNumber_jet_pp_DiJet->GetEntries(); // old
  // N_evt_jet_C4_DiJet = integrate(getEventNumber_jet_C4_DiJet,100,180);
  // N_evt_jet_C3_DiJet = integrate(getEventNumber_jet_C3_DiJet,60,100);
  // N_evt_jet_C2_DiJet = integrate(getEventNumber_jet_C2_DiJet,20,60);
  // N_evt_jet_C1_DiJet = integrate(getEventNumber_jet_C1_DiJet,0,20);

  cout << "N_evt_jet_pp_DiJet = " << N_evt_jet_pp_DiJet << endl;
  cout << "N_evt_jet_C4_DiJet = " << N_evt_jet_C4_DiJet << endl;
  cout << "N_evt_jet_C3_DiJet = " << N_evt_jet_C3_DiJet << endl;
  cout << "N_evt_jet_C2_DiJet = " << N_evt_jet_C2_DiJet << endl;
  cout << "N_evt_jet_C1_DiJet = " << N_evt_jet_C1_DiJet << endl;

  //cout << "N_evt_jet_C3_DiJet = " << N_evt_jet_C3_DiJet << endl;

  N_evt_jet_pp_MinBias = getEventNumber_jet_pp_MinBias->GetEntries(); // new
  N_evt_jet_C4_MinBias = getEventNumber_jet_C4_MinBias->Integral();   
  N_evt_jet_C3_MinBias = getEventNumber_jet_C3_MinBias->Integral();
  N_evt_jet_C2_MinBias = getEventNumber_jet_C2_MinBias->Integral();
  N_evt_jet_C1_MinBias = getEventNumber_jet_C1_MinBias->Integral();

  // N_evt_jet_pp_MinBias = getEventNumber_jet_pp_MinBias->GetEntries(); // old
  // N_evt_jet_C4_MinBias = integrate(getEventNumber_jet_C4_MinBias,100,180);   
  // N_evt_jet_C3_MinBias = integrate(getEventNumber_jet_C3_MinBias,60,100);
  // N_evt_jet_C2_MinBias = integrate(getEventNumber_jet_C2_MinBias,20,60);
  // N_evt_jet_C1_MinBias = integrate(getEventNumber_jet_C1_MinBias,0,20);

  cout << "N_evt_jet_pp_MinBias = " << N_evt_jet_pp_MinBias << endl;
  cout << "N_evt_jet_C4_MinBias = " << N_evt_jet_C4_MinBias << endl;
  cout << "N_evt_jet_C3_MinBias = " << N_evt_jet_C3_MinBias << endl;
  cout << "N_evt_jet_C2_MinBias = " << N_evt_jet_C2_MinBias << endl;
  cout << "N_evt_jet_C1_MinBias = " << N_evt_jet_C1_MinBias << endl;

  cout << "N_evt_jet_pp_MinBias = " << N_evt_jet_pp_MinBias << endl;

  N_evt_pp_MinBias = getEventNumber_pp_MinBias->Integral();
  N_evt_C4_MinBias = getEventNumber_C4_MinBias->Integral();
  N_evt_C3_MinBias = getEventNumber_C3_MinBias->Integral();
  N_evt_C2_MinBias = getEventNumber_C2_MinBias->Integral();
  N_evt_C1_MinBias = getEventNumber_C1_MinBias->Integral();

  cout << "N_evt_pp_MinBias = " << N_evt_pp_MinBias << endl;

  double f_evt_jet_pp, f_evt_jet_C4, f_evt_jet_C3, f_evt_jet_C2, f_evt_jet_C1;
  double f_evt_muTag_pp, f_evt_muTag_C4, f_evt_muTag_C3, f_evt_muTag_C2, f_evt_muTag_C1;
  double f_evt_muTrig_pp, f_evt_muTrig_C4, f_evt_muTrig_C3, f_evt_muTrig_C2, f_evt_muTrig_C1;

  f_evt_jet_pp = N_evt_jet_pp_MinBias / N_evt_pp_MinBias;
  f_evt_jet_C4 = N_evt_jet_C4_MinBias / N_evt_C4_MinBias;
  f_evt_jet_C3 = N_evt_jet_C3_MinBias / N_evt_C3_MinBias;
  f_evt_jet_C2 = N_evt_jet_C2_MinBias / N_evt_C2_MinBias;
  f_evt_jet_C1 = N_evt_jet_C1_MinBias / N_evt_C1_MinBias;

  f_evt_muTag_pp = N_evt_muTag_pp_DiJet / N_evt_jet_pp_DiJet;
  f_evt_muTag_C4 = N_evt_muTag_C4_DiJet / N_evt_jet_C4_DiJet;
  f_evt_muTag_C3 = N_evt_muTag_C3_DiJet / N_evt_jet_C3_DiJet;
  f_evt_muTag_C2 = N_evt_muTag_C2_DiJet / N_evt_jet_C2_DiJet;
  f_evt_muTag_C1 = N_evt_muTag_C1_DiJet / N_evt_jet_C1_DiJet;

  // f_evt_muTrig_pp = N_evt_muTag_muTrig_pp / N_evt_muTag_pp_SingleMuon;
  // f_evt_muTrig_C4 = N_evt_muTag_muTrig_C4 / N_evt_muTag_C4_SingleMuon;
  // f_evt_muTrig_C3 = N_evt_muTag_muTrig_C3 / N_evt_muTag_C3_SingleMuon;
  // f_evt_muTrig_C2 = N_evt_muTag_muTrig_C2 / N_evt_muTag_C2_SingleMuon;
  // f_evt_muTrig_C1 = N_evt_muTag_muTrig_C1 / N_evt_muTag_C1_SingleMuon;

  f_evt_muTrig_pp = 0.9543;
  f_evt_muTrig_C4 = 0.9426;
  f_evt_muTrig_C3 = 0.9384;
  f_evt_muTrig_C2 = 0.9101;
  f_evt_muTrig_C1 = 0.8471;

  cout << "f_evt_jet_pp = " << f_evt_jet_pp << endl;
  cout << "f_evt_jet_C4 = " << f_evt_jet_C4 << endl;
  cout << "f_evt_jet_C3 = " << f_evt_jet_C3 << endl;
  cout << "f_evt_jet_C2 = " << f_evt_jet_C2 << endl;
  cout << "f_evt_jet_C1 = " << f_evt_jet_C1 << endl;

  cout << "f_evt_muTag_pp = " << f_evt_muTag_pp << endl;
  cout << "f_evt_muTag_C4 = " << f_evt_muTag_C4 << endl;
  cout << "f_evt_muTag_C3 = " << f_evt_muTag_C3 << endl;
  cout << "f_evt_muTag_C2 = " << f_evt_muTag_C2 << endl;
  cout << "f_evt_muTag_C1 = " << f_evt_muTag_C1 << endl;


  cout << "f_evt_muTrig_pp = " << f_evt_muTrig_pp << endl;
  cout << "f_evt_muTrig_C4 = " << f_evt_muTrig_C4 << endl;
  cout << "f_evt_muTrig_C3 = " << f_evt_muTrig_C3 << endl;
  cout << "f_evt_muTrig_C2 = " << f_evt_muTrig_C2 << endl;
  cout << "f_evt_muTrig_C1 = " << f_evt_muTrig_C1 << endl;
  

  
  // rebin
  const int N_edge = 8;
  double newAxis[N_edge] = {80,90,100,120,150,200,300,500};
  // const int N_edge = 7;
  // double newAxis[N_edge] = {80,90,100,120,150,200,300};

  h_jetPt_muTag_muTrig_pp = (TH1D*) h_jetPt_muTag_muTrig_pp->Rebin(N_edge-1,"h_jetPt_muTag_muTrig_pp",newAxis);
  divideByBinwidth(h_jetPt_muTag_muTrig_pp);

  h_jetPt_muTag_muTrig_C4 = (TH1D*) h_jetPt_muTag_muTrig_C4->Rebin(N_edge-1,"h_jetPt_muTag_muTrig_C4",newAxis);
  divideByBinwidth(h_jetPt_muTag_muTrig_C4);

  h_jetPt_muTag_muTrig_C3 = (TH1D*) h_jetPt_muTag_muTrig_C3->Rebin(N_edge-1,"h_jetPt_muTag_muTrig_C3",newAxis);
  divideByBinwidth(h_jetPt_muTag_muTrig_C3);

  h_jetPt_muTag_muTrig_C2 = (TH1D*) h_jetPt_muTag_muTrig_C2->Rebin(N_edge-1,"h_jetPt_muTag_muTrig_C2",newAxis);
  divideByBinwidth(h_jetPt_muTag_muTrig_C2);

  h_jetPt_muTag_muTrig_C1 = (TH1D*) h_jetPt_muTag_muTrig_C1->Rebin(N_edge-1,"h_jetPt_muTag_muTrig_C1",newAxis);
  divideByBinwidth(h_jetPt_muTag_muTrig_C1);

  h_jetPt_pp = (TH1D*) h_jetPt_pp->Rebin(N_edge-1,"h_jetPt_pp",newAxis);
  divideByBinwidth(h_jetPt_pp);

  h_jetPt_C4 = (TH1D*) h_jetPt_C4->Rebin(N_edge-1,"h_jetPt_C4",newAxis);
  divideByBinwidth(h_jetPt_C4);

  h_jetPt_C3 = (TH1D*) h_jetPt_C3->Rebin(N_edge-1,"h_jetPt_C3",newAxis);
  divideByBinwidth(h_jetPt_C3);

  h_jetPt_C2 = (TH1D*) h_jetPt_C2->Rebin(N_edge-1,"h_jetPt_C2",newAxis);
  divideByBinwidth(h_jetPt_C2);

  h_jetPt_C1 = (TH1D*) h_jetPt_C1->Rebin(N_edge-1,"h_jetPt_C1",newAxis);
  divideByBinwidth(h_jetPt_C1);

  

  stylizeHistograms(h_jetPt_muTag_muTrig_pp, h_jetPt_muTag_muTrig_C1, h_jetPt_muTag_muTrig_C2, h_jetPt_muTag_muTrig_C3, h_jetPt_muTag_muTrig_C4);
  stylizeHistograms(h_jetPt_pp, h_jetPt_C1, h_jetPt_C2, h_jetPt_C3, h_jetPt_C4);


  // // scale by 1/N_evt
  // h_jetPt_muTag_muTrig_pp->Scale(1 / (1.*N_evt_muTag_muTrig_pp));
  // h_jetPt_muTag_muTrig_C4->Scale(1 / (1.*N_evt_muTag_muTrig_C4));
  // h_jetPt_muTag_muTrig_C3->Scale(1 / (1.*N_evt_muTag_muTrig_C3));  
  // h_jetPt_muTag_muTrig_C2->Scale(1 / (1.*N_evt_muTag_muTrig_C2));
  // h_jetPt_muTag_muTrig_C1->Scale(1 / (1.*N_evt_muTag_muTrig_C1));


  h_jetPt_pp->Scale(1./N_evt_pp_MinBias);
  h_jetPt_C4->Scale(1./N_evt_C4_MinBias);
  h_jetPt_C3->Scale(1./N_evt_C3_MinBias);
  h_jetPt_C2->Scale(1./N_evt_C2_MinBias);
  h_jetPt_C1->Scale(1./N_evt_C1_MinBias);

  // // scale by 1 / (NZ/recoEff^2) // need recoEff^2 because reconstructing 2 muons
  h_jetPt_muTag_muTrig_pp->Scale(1./(NZ_pp/(0.9708*0.9708)));
  h_jetPt_muTag_muTrig_C4->Scale(1./(NZ_C4/(0.9778*0.9778)));
  h_jetPt_muTag_muTrig_C3->Scale(1./(NZ_C3/(0.9856*0.9856)));
  h_jetPt_muTag_muTrig_C2->Scale(1./(NZ_C2/(0.9069*0.9069)));
  h_jetPt_muTag_muTrig_C1->Scale(1./(NZ_C1/(0.8627*0.8627)));

  // h_jetPt_muTag_muTrig_pp->Scale(1./(NZ_pp/(1.)));
  // h_jetPt_muTag_muTrig_C4->Scale(1./(NZ_C4/(1.)));
  // h_jetPt_muTag_muTrig_C3->Scale(1./(NZ_C3/(1.)));
  // h_jetPt_muTag_muTrig_C2->Scale(1./(NZ_C2/(1.)));
  // h_jetPt_muTag_muTrig_C1->Scale(1./(NZ_C1/(1.)));

  TLegend *leg = new TLegend(0.6,0.7,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  //leg->AddEntry(r_mcBJetPt_pp,"PYTHIA","l");
  //leg->AddEntry(h_jetPt_pp,"pp","p");
  leg->AddEntry(h_jetPt_C4,"PbPb 50-80%","p");  
  leg->AddEntry(h_jetPt_C3,"PbPb 30-50%","p");
  leg->AddEntry(h_jetPt_C2,"PbPb 10-30%","p");
  leg->AddEntry(h_jetPt_C1,"PbPb 0-10%","p");
  //leg->AddEntry(bFrac_CMS_pp_7TeV,"CMS #sqrt{s} = 7 TeV");

  
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
  //h_jetPt_muTag_muTrig_pp->GetYaxis()->SetTitle("1/#it{N}_{Z} d#it{N}^{jet}_{#mu-tag,#mu-trig}/d#it{p}_{T} [GeV^{-1}]");
  h_jetPt_muTag_muTrig_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //h_jetPt_muTag_muTrig_pp->GetYaxis()->SetRangeUser(0,0.06);
  h_jetPt_muTag_muTrig_pp->Draw();
  h_jetPt_muTag_muTrig_C4->Draw("same");
  h_jetPt_muTag_muTrig_C3->Draw("same");
  h_jetPt_muTag_muTrig_C2->Draw("same");
  h_jetPt_muTag_muTrig_C1->Draw("same");
  leg->Draw();
  canv_muTag_muTrig->SaveAs("./figures/spectra_muTag_muTrig.pdf");
  file_MuTagMuTrigJetSpectra = (TFile*) TFile::Open("./rootFiles/MuTagMuTrigJetSpectra/Data/histograms_MuTagMuTrigJetSpectra.root","recreate");
  h_jetPt_muTag_muTrig_pp->Write();
  h_jetPt_muTag_muTrig_C4->Write();  
  h_jetPt_muTag_muTrig_C3->Write();
  h_jetPt_muTag_muTrig_C2->Write();
  h_jetPt_muTag_muTrig_C1->Write();
  file_MuTagMuTrigJetSpectra->Close();


  // apply the bPurity fraction multiplication
  TH1D *h_bJetPt_muTag_muTrig_pp, *h_bJetPt_muTag_muTrig_C4, *h_bJetPt_muTag_muTrig_C3, *h_bJetPt_muTag_muTrig_C2, *h_bJetPt_muTag_muTrig_C1;

  h_bJetPt_muTag_muTrig_pp = (TH1D*) h_jetPt_muTag_muTrig_pp->Clone("h_bJetPt_muTag_muTrig_pp");
  h_bJetPt_muTag_muTrig_pp->Multiply(bPurity_muTag_muTrig_pp);

  h_bJetPt_muTag_muTrig_C4 = (TH1D*) h_jetPt_muTag_muTrig_C4->Clone("h_bJetPt_muTag_muTrig_C4");
  h_bJetPt_muTag_muTrig_C4->Multiply(bPurity_muTag_muTrig_C4);

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
  //h_bJetPt_muTag_muTrig_pp->GetYaxis()->SetTitle("1/#it{N}_{Z} d#it{N}^{#it{b}-jet}_{#mu-tag,#mu-trig}/d#it{p}_{T} [GeV^{-1}]");
  h_bJetPt_muTag_muTrig_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_bJetPt_muTag_muTrig_pp->GetYaxis()->SetRangeUser(2e-12,5e-3);
  h_bJetPt_muTag_muTrig_pp->Draw();
  h_bJetPt_muTag_muTrig_C4->Draw("same");
  h_bJetPt_muTag_muTrig_C3->Draw("same");
  h_bJetPt_muTag_muTrig_C2->Draw("same");
  h_bJetPt_muTag_muTrig_C1->Draw("same");
  leg->Draw();
  canv_bJet_muTag_muTrig->SaveAs("./figures/spectra_bJet_muTag_muTrig.pdf");
  file_MuTagMuTrigBJetSpectra = (TFile*) TFile::Open("./rootFiles/MuTagMuTrigBJetSpectra/Data/histograms_MuTagMuTrigBJetSpectra.root","recreate");
  h_bJetPt_muTag_muTrig_pp->Write();
  h_bJetPt_muTag_muTrig_C3->Write();
  h_bJetPt_muTag_muTrig_C4->Write();  
  h_bJetPt_muTag_muTrig_C2->Write();
  h_bJetPt_muTag_muTrig_C1->Write();
  file_MuTagMuTrigBJetSpectra->Close();


  //  bPurity_muTag_muTrig_pp->Draw();
  

  // apply the correction factors
  TH1D *h_bJetPt_corr_pp, *h_bJetPt_corr_C4, *h_bJetPt_corr_C3, *h_bJetPt_corr_C2, *h_bJetPt_corr_C1;

  h_bJetPt_corr_pp = (TH1D*) h_bJetPt_muTag_muTrig_pp->Clone("h_bJetPt_corr_pp");
  h_bJetPt_corr_C4 = (TH1D*) h_bJetPt_muTag_muTrig_C4->Clone("h_bJetPt_corr_C4");
  h_bJetPt_corr_C3 = (TH1D*) h_bJetPt_muTag_muTrig_C3->Clone("h_bJetPt_corr_C3");  
  h_bJetPt_corr_C2 = (TH1D*) h_bJetPt_muTag_muTrig_C2->Clone("h_bJetPt_corr_C2");
  h_bJetPt_corr_C1 = (TH1D*) h_bJetPt_muTag_muTrig_C1->Clone("h_bJetPt_corr_C1");

  // "MinBias equivalent events" conversion
  // h_bJetPt_corr_pp->Scale(f_evt_jet_pp * f_evt_muTag_pp * f_evt_muTrig_pp);
  // h_bJetPt_corr_C4->Scale(f_evt_jet_C4 * f_evt_muTag_C4 * f_evt_muTrig_C4);
  // h_bJetPt_corr_C3->Scale(f_evt_jet_C3 * f_evt_muTag_C3 * f_evt_muTrig_C3);  
  // h_bJetPt_corr_C2->Scale(f_evt_jet_C2 * f_evt_muTag_C2 * f_evt_muTrig_C2);
  // h_bJetPt_corr_C1->Scale(f_evt_jet_C1 * f_evt_muTag_C1 * f_evt_muTrig_C1);

  //h_bJetPt_corr_pp->Divide(corrFactor_3d_pp);
  // h_bJetPt_corr_pp->Divide(corrFactor_3_pp);
  // h_bJetPt_corr_pp->Divide(corrFactor_2_pp);
  h_bJetPt_corr_pp->Scale(1./0.9708);
  //h_bJetPt_corr_pp->Scale(1./0.91);
  h_bJetPt_corr_pp->Divide(corrFactor_1_pp);
  
  //h_bJetPt_corr_C4->Divide(corrFactor_3d_C4);
  // h_bJetPt_corr_C4->Divide(corrFactor_3_C4);
  // h_bJetPt_corr_C4->Divide(corrFactor_2_C4);
  h_bJetPt_corr_C4->Scale(1./0.9778);
  //h_bJetPt_corr_C4->Scale(1./0.94);
  h_bJetPt_corr_C4->Divide(corrFactor_1_C4);

  //h_bJetPt_corr_C3->Divide(corrFactor_3d_C3);
  // h_bJetPt_corr_C3->Divide(corrFactor_3_C3);
  // h_bJetPt_corr_C3->Divide(corrFactor_2_C3);
  h_bJetPt_corr_C3->Scale(1./0.9856);
  //h_bJetPt_corr_C3->Scale(1./0.94);
  h_bJetPt_corr_C3->Divide(corrFactor_1_C3);

  //h_bJetPt_corr_C2->Divide(corrFactor_3d_C2);
  // h_bJetPt_corr_C2->Divide(corrFactor_3_C2);
  // h_bJetPt_corr_C2->Divide(corrFactor_2_C2);
  h_bJetPt_corr_C2->Scale(1./0.9069);
  //h_bJetPt_corr_C2->Scale(1./0.90);
  h_bJetPt_corr_C2->Divide(corrFactor_1_C2);

  //h_bJetPt_corr_C1->Divide(corrFactor_3d_C1);
  // h_bJetPt_corr_C1->Divide(corrFactor_3_C1);
  // h_bJetPt_corr_C1->Divide(corrFactor_2_C1);
  h_bJetPt_corr_C1->Scale(1./0.8627);
  //h_bJetPt_corr_C1->Scale(1./0.84);
  h_bJetPt_corr_C1->Divide(corrFactor_1_C1);

  TCanvas *canv_bJet_corr = new TCanvas("canv_bJet_corr","canv_bJet_corr",700,700);
  canv_bJet_corr->cd();
  TPad *pad1_bJet_corr = new TPad("pad1_bJet_corr","pad1_bJet_corr",0,0,1,1);
  pad1_bJet_corr->SetLogy();
  pad1_bJet_corr->SetLeftMargin(0.15);
  pad1_bJet_corr->SetBottomMargin(0.15);
  pad1_bJet_corr->Draw();
  pad1_bJet_corr->cd();
  h_bJetPt_corr_pp->GetYaxis()->SetTitle("1/#it{N}^{evt}_{equiv-MinBias} d#it{N}^{corr-#it{b}}/d#it{p}_{T} [GeV^{-1}]");
  //h_bJetPt_corr_pp->GetYaxis()->SetTitle("1/#it{N}_{Z} d#it{N}^{corr-#it{b}}/d#it{p}_{T} [GeV^{-1}]");
  h_bJetPt_corr_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_bJetPt_corr_pp->GetYaxis()->SetRangeUser(2e-11,5e-3);
  h_bJetPt_corr_pp->Draw();
  h_bJetPt_corr_C4->Draw("same");
  h_bJetPt_corr_C3->Draw("same");
  h_bJetPt_corr_C2->Draw("same");
  h_bJetPt_corr_C1->Draw("same");
  leg->Draw();
  canv_bJet_corr->SaveAs("./figures/spectra_bJet_corr.pdf");
  file_CorrectedBJetSpectra = (TFile*) TFile::Open("./rootFiles/CorrectedBJetSpectra/Data/histograms_CorrectedBJetSpectra.root","recreate");
  h_bJetPt_corr_pp->Write();
  h_bJetPt_corr_C4->Write();
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
  //h_jetPt_pp->GetYaxis()->SetTitle("1/#it{N}_{#it{Z}} d#it{N}^{jet}/d#it{p}_{T} [GeV^{-1}]");
  h_jetPt_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_jetPt_pp->GetYaxis()->SetRangeUser(2e-11,5e-3);
  h_jetPt_pp->Draw();
  h_jetPt_C4->Draw("same");
  h_jetPt_C3->Draw("same");
  h_jetPt_C2->Draw("same");
  h_jetPt_C1->Draw("same");
  leg->Draw();
  canv_MinBias->SaveAs("./figures/spectra_MinBias.pdf");
  file_MinBiasJetSpectra = (TFile*) TFile::Open("./rootFiles/MinBiasJetSpectra/Data/histograms_MinBiasJetSpectra.root","recreate");
  h_jetPt_pp->Write();
  h_jetPt_C4->Write();
  h_jetPt_C3->Write();
  h_jetPt_C2->Write();
  h_jetPt_C1->Write();
  file_MinBiasJetSpectra->Close();

  // define special histograms for normalizing
  TH1D *h_bJetPt_corr_pp_norm = (TH1D*) h_bJetPt_corr_pp->Clone("h_bJetPt_corr_pp_norm"); 
  TH1D *h_jetPt_pp_norm = (TH1D*) h_jetPt_pp->Clone("h_jetPt_pp_norm");

  //h_bJetPt_corr_pp_norm->Scale(1./h_bJetPt_corr_pp_norm->Integral());
  //h_jetPt_pp_norm->Scale(1./h_jetPt_pp_norm->Integral());

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////   bJet RAA calculation


  TH1D *bJet_pp_xSection = (TH1D*) h_bJetPt_corr_pp->Clone("bJet_pp_xSection");
  // bJet_pp_xSection->Scale(N_evt_muTag_muTrig_pp / (f_evt_jet_pp * f_evt_muTag_pp * f_evt_muTrig_pp));// undo scaling only for pp
  TH1D *bJetRAA_C4 = (TH1D*) h_bJetPt_corr_C4->Clone("bJetRAA_C4");
  TH1D *bJetRAA_C3 = (TH1D*) h_bJetPt_corr_C3->Clone("bJetRAA_C3");
  TH1D *bJetRAA_C2 = (TH1D*) h_bJetPt_corr_C2->Clone("bJetRAA_C2");
  TH1D *bJetRAA_C1 = (TH1D*) h_bJetPt_corr_C1->Clone("bJetRAA_C1");

  bJet_pp_xSection->Scale(1./(299490.144921629071)); // luminosity scale [1/nb]
  bJetRAA_C4->Scale(1./(0.7452E-6)); // TAA scale [nb]
  bJetRAA_C3->Scale(1./(3.95E-6));
  bJetRAA_C2->Scale(1./(11.60E-6));
  bJetRAA_C1->Scale(1./(11.60E-6));

  bJetRAA_C4->Divide(bJetRAA_C4,bJet_pp_xSection,1,1,"");
  bJetRAA_C3->Divide(bJetRAA_C3,bJet_pp_xSection,1,1,"");
  bJetRAA_C2->Divide(bJetRAA_C2,bJet_pp_xSection,1,1,"");
  bJetRAA_C1->Divide(bJetRAA_C1,bJet_pp_xSection,1,1,"");

  TCanvas *canv_bJetRAA = new TCanvas("canv_bJetRAA","canv_bJetRAA",700,700);
  canv_bJetRAA->cd();
  //bJet_pp_xSection->Draw();
  bJetRAA_C4->Draw();
  bJetRAA_C3->Draw("same");
  bJetRAA_C2->Draw("same");
  bJetRAA_C1->Draw("same");
  
  

  



  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



  // load the reverse-unfold correction factors
  TFile *file_reverseUnfold_pp = (TFile*) TFile::Open("../../rootFiles/correctionFactors/reverseUnfoldFactor_pp.root");
  TH1D *reverseUnfoldFactor_pp;
  file_reverseUnfold_pp->GetObject("reverseUnfoldFactor_pp",reverseUnfoldFactor_pp);

  TFile *file_reverseUnfold_C4 = (TFile*) TFile::Open("../../rootFiles/correctionFactors/reverseUnfoldFactor_C4.root");
  TH1D *reverseUnfoldFactor_C4;
  file_reverseUnfold_C4->GetObject("reverseUnfoldFactor_C4",reverseUnfoldFactor_C4);

  TFile *file_reverseUnfold_C3 = (TFile*) TFile::Open("../../rootFiles/correctionFactors/reverseUnfoldFactor_C3.root");
  TH1D *reverseUnfoldFactor_C3;
  file_reverseUnfold_C3->GetObject("reverseUnfoldFactor_C3",reverseUnfoldFactor_C3);

  TFile *file_reverseUnfold_C2 = (TFile*) TFile::Open("../../rootFiles/correctionFactors/reverseUnfoldFactor_C2.root");
  TH1D *reverseUnfoldFactor_C2;
  file_reverseUnfold_C2->GetObject("reverseUnfoldFactor_C2",reverseUnfoldFactor_C2);

  TFile *file_reverseUnfold_C1 = (TFile*) TFile::Open("../../rootFiles/correctionFactors/reverseUnfoldFactor_C1.root");
  TH1D *reverseUnfoldFactor_C1;
  file_reverseUnfold_C1->GetObject("reverseUnfoldFactor_C1",reverseUnfoldFactor_C1);

  h_bJetPt_corr_pp_norm->Multiply(reverseUnfoldFactor_pp);
  h_bJetPt_corr_C4->Multiply(reverseUnfoldFactor_C4);
  h_bJetPt_corr_C3->Multiply(reverseUnfoldFactor_C3);
  h_bJetPt_corr_C2->Multiply(reverseUnfoldFactor_C2);
  h_bJetPt_corr_C1->Multiply(reverseUnfoldFactor_C1);
  
  
  
  TH1D *bFraction_C4 = (TH1D*) h_bJetPt_corr_C4->Clone("bFraction_C4");
  //bFraction_C4->Scale(1./bFraction_C4->Integral());
  bFraction_C4->Divide(bFraction_C4,h_bJetPt_corr_pp_norm,1,1,"");

  TH1D *bFraction_C3 = (TH1D*) h_bJetPt_corr_C3->Clone("bFraction_C3");
  //bFraction_C3->Scale(1./bFraction_C3->Integral());
  bFraction_C3->Divide(bFraction_C3,h_bJetPt_corr_pp_norm,1,1,"");

  TH1D *bFraction_C2 = (TH1D*) h_bJetPt_corr_C2->Clone("bFraction_C2");
  //bFraction_C2->Scale(1./bFraction_C2->Integral());
  bFraction_C2->Divide(bFraction_C2,h_bJetPt_corr_pp_norm,1,1,"");

  TH1D *bFraction_C1 = (TH1D*) h_bJetPt_corr_C1->Clone("bFraction_C1");
  //bFraction_C1->Scale(1./bFraction_C1->Integral());
  bFraction_C1->Divide(bFraction_C1,h_bJetPt_corr_pp_norm,1,1,"");

  TH1D *inclFraction_C4 = (TH1D*) h_jetPt_C4->Clone("inclFraction_C4");
  inclFraction_C4->Scale(1./inclFraction_C4->Integral());
  inclFraction_C4->Divide(inclFraction_C4,h_jetPt_pp_norm,1,1,"");
  
  TH1D *inclFraction_C3 = (TH1D*) h_jetPt_C3->Clone("inclFraction_C3");
  inclFraction_C3->Scale(1./inclFraction_C3->Integral());
  inclFraction_C3->Divide(inclFraction_C3,h_jetPt_pp_norm,1,1,"");
  
  TH1D *inclFraction_C2 = (TH1D*) h_jetPt_C2->Clone("inclFraction_C2");
  inclFraction_C2->Scale(1./inclFraction_C2->Integral());
  inclFraction_C2->Divide(inclFraction_C2,h_jetPt_pp_norm,1,1,"");
  
  TH1D *inclFraction_C1 = (TH1D*) h_jetPt_C1->Clone("inclFraction_C1");
  inclFraction_C1->Scale(1./inclFraction_C1->Integral());
  inclFraction_C1->Divide(inclFraction_C1,h_jetPt_pp_norm,1,1,"");

  TH1D *inclBFraction_pp = (TH1D*) h_bJetPt_corr_pp->Clone("inclBFraction_pp");
  inclBFraction_pp->Divide(h_bJetPt_corr_pp,h_jetPt_pp,1,1,"");

  TH1D *inclBFraction_C4 = (TH1D*) h_bJetPt_corr_C4->Clone("inclBFraction_C4");
  inclBFraction_C4->Divide(h_bJetPt_corr_C4,h_jetPt_C4,1,1,"");

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
  inclBFraction_pp->GetYaxis()->SetTitleSize(0.05);
  inclBFraction_pp->GetXaxis()->SetTitleSize(0.05);
  inclBFraction_pp->GetYaxis()->SetLabelSize(0.04);
  inclBFraction_pp->GetXaxis()->SetLabelSize(0.04);
  inclBFraction_pp->GetYaxis()->SetTitle("Inclusive #it{b}-jet fraction");
  inclBFraction_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  inclBFraction_pp->GetYaxis()->SetRangeUser(0.0,0.1);
  inclBFraction_pp->GetXaxis()->SetRangeUser(90,200);
  inclBFraction_pp->Draw();
  // inclBFraction_C4->Draw("same");  
  // inclBFraction_C3->Draw("same");
  // inclBFraction_C2->Draw("same");
  // inclBFraction_C1->Draw("same");
  r_mcBJetPt_pp->Draw("same hist l");
  bFrac_CMS_pp_7TeV->Draw("same");
  leg->Draw();
  canv_inclBFraction->SaveAs("./figures/inclusiveBJetFraction.pdf");
  file_InclusiveBJetFraction = (TFile*) TFile::Open("./rootFiles/InclusiveBJetFraction/Data/histograms_InclusiveBJetFraction.root","recreate");
  inclBFraction_pp->Write();
  inclBFraction_C4->Write();
  inclBFraction_C3->Write();
  inclBFraction_C2->Write();
  inclBFraction_C1->Write();
  file_InclusiveBJetFraction->Close();
  
  TCanvas *canv_bFraction = new TCanvas("canv_bFraction","canv_bFraction",700,700);
  canv_bFraction->cd();
  TPad *pad1_bFraction = new TPad("pad1_bFraction","pad1_bFraction",0,0,1,1);
  //pad1_bFraction->SetLogy();
  pad1_bFraction->SetLeftMargin(0.2);
  pad1_bFraction->SetBottomMargin(0.15);
  pad1_bFraction->Draw();
  pad1_bFraction->cd();
  //bFraction_C3->GetYaxis()->SetTitle("Ratio of corrected #it{b}-jet spectra (PbPb / pp)");
  bFraction_C3->GetYaxis()->SetTitleOffset(2.);
  bFraction_C3->GetYaxis()->SetTitle("#frac{1}{#it{N}_{Z}^{PbPb}} #frac{d#it{N}_{jet}^{PbPb}}{d#it{p}_{T}} #scale[3.0]{/} #frac{1}{#it{N}_{Z}^{pp}} #frac{d#it{N}_{jet}^{pp}}{d#it{p}_{T}}");
  bFraction_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  bFraction_C3->GetYaxis()->SetRangeUser(0,2);
  
  bFraction_C3->GetXaxis()->SetRangeUser(80,300);
  //bFraction_C3->GetYaxis()->SetRangeUser(0,0.05);
  //bFraction_C3->GetYaxis()->SetRangeUser(0,1000);
  bFraction_C3->Draw();
  bFraction_C2->Draw("same");
  bFraction_C1->Draw("same");
  bFraction_C4->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(80,1,300,1);
  leg->Draw();
  canv_bFraction->SaveAs("./figures/bJetPbPbToPP.pdf");
  file_BJetPbPbToPP = (TFile*) TFile::Open("./rootFiles/BJetPbPbToPP/Data/histograms_BJetPbPbToPP.root","recreate");
  bFraction_C4->Write();
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
  inclFraction_C3->GetYaxis()->SetRangeUser(0,2);
  //inclFraction_C3->GetYaxis()->SetRangeUser(0,0.05);
  //inclFraction_C3->GetYaxis()->SetRangeUser(0,1000);
  inclFraction_C3->Draw();
  inclFraction_C2->Draw("same");
  inclFraction_C1->Draw("same");
  inclFraction_C4->Draw("same");
  canv_inclFraction->SaveAs("./figures/inclJetPbPbToPP.pdf");
  file_InclJetPbPbToPP = (TFile*) TFile::Open("./rootFiles/InclJetPbPbToPP/Data/histograms_InclJetPbPbToPP.root","recreate");
  inclFraction_C4->Write();
  inclFraction_C3->Write();
  inclFraction_C2->Write();
  inclFraction_C1->Write();
  file_InclJetPbPbToPP->Close();

  TH1D *R_C4 = (TH1D*) inclBFraction_C4->Clone("R_C4");
  R_C4->Divide(inclBFraction_C4,inclBFraction_pp,1,1,"");

  TH1D *R_C3 = (TH1D*) inclBFraction_C3->Clone("R_C3");
  R_C3->Divide(inclBFraction_C3,inclBFraction_pp,1,1,"");

  TH1D *R_C2 = (TH1D*) inclBFraction_C2->Clone("R_C2");
  R_C2->Divide(inclBFraction_C2,inclBFraction_pp,1,1,"");

  TH1D *R_C1 = (TH1D*) inclBFraction_C1->Clone("R_C1");
  R_C1->Divide(inclBFraction_C1,inclBFraction_pp,1,1,"");  

  TCanvas *canv_R = new TCanvas("canv_R","canv_R",700,700);
  canv_R->cd();
  TPad *pad1_R = new TPad("pad1_R","pad1_R",0,0,1,1);
  //pad1_R->SetLogy();
  pad1_R->SetLeftMargin(0.15);
  pad1_R->SetBottomMargin(0.15);
  pad1_R->Draw();
  pad1_R->cd();
  R_C3->GetYaxis()->SetTitle("f_{#it{b}}(PbPb) / f_{#it{b}}(pp)");
  R_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  R_C3->GetYaxis()->SetRangeUser(0,3.2);
  R_C3->GetXaxis()->SetRangeUser(90,200);
  R_C3->GetYaxis()->SetTitleSize(0.05);
  R_C3->GetXaxis()->SetTitleSize(0.05);
  R_C3->GetYaxis()->SetLabelSize(0.04);
  R_C3->GetXaxis()->SetLabelSize(0.04);
  R_C3->Draw();
  R_C2->Draw("same");
  R_C1->Draw("same");
  R_C4->Draw("same");
  leg->Draw();
  li->SetLineStyle(7);
  li->DrawLine(90,1,200,1);
  canv_R->SaveAs("./figures/doubleRatio.pdf");
  file_DoubleRatio = (TFile*) TFile::Open("./rootFiles/DoubleRatio/Data/histograms_DoubleRatio.root","recreate");
  R_C4->Write();
  R_C3->Write();
  R_C2->Write();
  R_C1->Write();
  file_DoubleRatio->Close();


}

