#include "../../headers/functions/divideByBinwidth.h"
#include "../../headers/goldenFileNames.h"

// bFraction results file
TFile *file_bPurity;
TString file_bPurity_name;
// bPurity histogram
TH1D *h_bPurity;
TString h_bPurity_name;
// input file paths
TFile *file_input;
// input spectra to be corrected
TH1D *h_input;
TH1D *h_vz_input;
TH1D *h_corr_1;
TH1D *h_corr_2;
TH1D *h_corr_3;
TH1D *h_corr_4;
// correction factor file paths
TFile *file_CF;
// correction factors
TH1D *h_CF_1;
TH1D *h_CF_2;
TH1D *h_CF_3;
// reference name strings
TString file_input_name;
TString h_input_name;
TString h_vz_input_name;
TString file_CF_name;
TString corr_1_name;
TString corr_2_name;
TString corr_3_name;
// MinBias file path
TFile *file_MB;
// MinBias input spectra
TH1D *h_MB;
TH1D *h_vz_MB;
TH1D *h_vz_MB_trig;
// reference name strings
TString file_MB_name;
TString h_MB_name;
TString h_vz_MB_name;
TString h_vz_MB_trig_name;
TString file_save_name;
TFile *bFractionResults_file;
TFile *JES_file;
TString JES_file_name;
TH1D *h_JES;
TString h_JES_name;

void spectraCorrector(bool ispp = 1,
		      bool isC2 = 0,
		      bool isC1 = 0,
		      bool isMC = 0,
		      bool isJ2 = 1,
		      bool isJ3 = 0,
		      bool isJ4 = 0){

  
  if(ispp){
    if(isMC){
      file_input_name = goldenFile_PYTHIA;
      file_MB_name = goldenFile_pp_MinBias;
    }
    else{
      file_input_name = goldenFile_pp_SingleMuon;
      file_MB_name = goldenFile_pp_MinBias;
    }
    h_input_name = "h_inclRecoJetPt_inclRecoMuonTag_triggerOn";
    h_vz_input_name = "h_vz_inclRecoMuonTag_triggerOn";
    file_CF_name = "../../rootFiles/correctionFactors/correctionFactors_pp.root";
    corr_1_name = "corrFactor_1_pp";
    corr_2_name = "corrFactor_2_pp";
    corr_3_name = "corrFactor_3_pp";
    h_MB_name = "h_inclRecoJetPt";
    h_vz_MB_name = "h_vz";
    h_vz_MB_trig_name = "h_vz_inclRecoMuonTag_triggerOn";
    file_bPurity_name = goldenFile_bPurity;
    h_bPurity_name = "bFracResults_pp";
    JES_file_name = "../../rootFiles/JES/JES_bJets_pp.root";
    h_JES_name = "JES_result_b";
  }
  else if(isC2){
    if(isMC){
      file_input_name = goldenFile_PYTHIAHYDJET_DiJet_pthat15;
      file_MB_name = goldenFile_PbPb_MinBias;
    }
    else{
      file_input_name = goldenFile_PbPb_SingleMuon;
      file_MB_name = goldenFile_PbPb_MinBias;
    }
    h_input_name = "h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2";
    h_vz_input_name = "h_vz_inclRecoMuonTag_triggerOn_C2";
    file_CF_name = "../../rootFiles/correctionFactors/correctionFactors_C2_merge.root";
    corr_1_name = "corrFactor_1_C2";
    corr_2_name = "corrFactor_2_C2";
    corr_3_name = "corrFactor_3_C2";
    h_MB_name = "h_inclRecoJetPt_C2";
    h_vz_MB_name = "h_vz_C2";
    h_vz_MB_trig_name = "h_vz_inclRecoMuonTag_triggerOn_C2";
    file_bPurity_name = goldenFile_bPurity;
    h_bPurity_name = "bFracResults_C2";
    JES_file_name = "../../rootFiles/JES/JES_bJets_C2.root";
    h_JES_name = "JES_result_b";
  }
  else if(isC1){
    if(isMC){
      file_input_name = goldenFile_PYTHIAHYDJET_DiJet_pthat15;
      file_MB_name = goldenFile_PbPb_MinBias;
    }
    else{
      file_input_name = goldenFile_PbPb_SingleMuon;
      file_MB_name = goldenFile_PbPb_MinBias;
    }
    h_input_name = "h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1";
    h_vz_input_name = "h_vz_inclRecoMuonTag_triggerOn_C1";
    file_CF_name = "../../rootFiles/correctionFactors/correctionFactors_C1_merge.root";
    corr_1_name = "corrFactor_1_C1";
    corr_2_name = "corrFactor_2_C1";
    corr_3_name = "corrFactor_3_C1";
    h_MB_name = "h_inclRecoJetPt_C1";
    h_vz_MB_name = "h_vz_C1";
    h_vz_MB_trig_name = "h_vz_inclRecoMuonTag_triggerOn_C1";
    file_bPurity_name = goldenFile_bPurity;
    h_bPurity_name = "bFracResults_C1";
    JES_file_name = "../../rootFiles/JES/JES_bJets_C1.root";
    h_JES_name = "JES_result_b";
  }
  else{};

  file_input = TFile::Open(file_input_name);
  file_input->GetObject(h_input_name,h_input);
  file_input->GetObject(h_vz_input_name,h_vz_input);
  file_CF = TFile::Open(file_CF_name);
  file_CF->GetObject(corr_1_name,h_CF_1);
  file_CF->GetObject(corr_2_name,h_CF_2);
  file_CF->GetObject(corr_3_name,h_CF_3);
  file_MB = TFile::Open(file_MB_name);
  file_MB->GetObject(h_MB_name,h_MB);
  file_MB->GetObject(h_vz_MB_name,h_vz_MB);
  file_MB->GetObject(h_vz_MB_trig_name,h_vz_MB_trig);
  //file_input->GetObject(h_vz_MB_trig_name,h_vz_MB_trig);
  file_bPurity = TFile::Open(goldenFile_bPurity);
  file_bPurity->GetObject(h_bPurity_name,h_bPurity);
  JES_file = TFile::Open(JES_file_name);
  JES_file->GetObject(h_JES_name,h_JES);
  
  // calculate number of events
  double N_evt = h_vz_input->Integral();
  double N_evt_MB = h_vz_MB->Integral();
  double N_evt_MB_trig = h_vz_MB_trig->Integral();

  
  
  // set correction factor errors to zero
  for(int i = 0; i < h_CF_1->GetSize(); i++){
    h_CF_1->SetBinError(i,0.0);
    h_CF_2->SetBinError(i,0.0);
    h_CF_3->SetBinError(i,0.0);
  }

  // rebin input histogram
  const int N_edges = 4;
  double newPtAxis[N_edges] = {60,80,120,200};
  TH1D *h_input_r = (TH1D*) h_input->Rebin(N_edges-1,"h_input_r",newPtAxis);
  TH1D *h_MB_r = (TH1D*) h_MB->Rebin(N_edges-1,"h_MB_r",newPtAxis);

  divideByBinwidth(h_input_r);
  h_input_r->Scale(5.0); // account for 5 GeV wide bins
  
  divideByBinwidth(h_MB_r);
  h_MB_r->Scale(5.0); // account for 5 GeV wide bins

    // multiply input by bFraction
  h_input_r->Multiply(h_bPurity);

  
  
  
  // scale input by 1/N_evt
  h_input_r->Scale(1./N_evt);
  h_MB_r->Scale(1./N_evt_MB);
  
  h_input_r->Draw();
  h_MB_r->Draw("same");


  cout << "N_evt_MB_trig = " << N_evt_MB_trig << endl;
  cout << "N_evt_MB = " << N_evt_MB << endl;
  cout << "selectionScaleFactor = " << N_evt_MB_trig / N_evt_MB << endl;

  /*

  h_MB_r->Scale(N_evt_MB / N_evt_MB_trig);

  
  //h_input->Draw();
  //h_input_r->Draw("same");
  h_corr_1 = (TH1D*) h_input_r->Clone("h_corr_1");
  h_corr_1->Divide(h_input_r,h_CF_3,1,1,"");
  h_corr_2 = (TH1D*) h_corr_1->Clone("h_corr_2");
  h_corr_2->Divide(h_corr_1,h_CF_2,1,1,"");
  h_corr_3 = (TH1D*) h_corr_2->Clone("h_corr_3");
  h_corr_3->Divide(h_corr_2,h_CF_1,1,1,"");
  h_corr_4 = (TH1D*) h_corr_3->Clone("h_corr_4");
  //h_corr_4->Divide(h_corr_3,h_JES,1,1,"");


  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0,1,1);
  p1->SetLeftMargin(0.2);
  p1->SetBottomMargin(0.2);
  p1->SetLogy();
  p1->Draw();
  p1->cd();
  h_input_r->GetXaxis()->SetTitle("Jet #font[52]{p}_{T} [GeV]");
  h_input_r->GetYaxis()->SetTitle("1/#font[52]{N}^{evt} d#font[52]{N}^{jet} / d#font[52]{p}_{T} [GeV^{-1}]");
  h_input_r->SetTitle("");
  h_input_r->SetStats(0);
  h_input_r->SetLineColor(kGray);
  h_corr_1->SetLineColor(kBlue-4);
  h_corr_2->SetLineColor(kRed-4);
  h_corr_3->SetLineColor(kGreen+2);
  h_corr_4->SetLineColor(kMagenta);
  h_MB_r->SetLineColor(kBlack);
  h_MB_r->SetLineStyle(7);
  h_input_r->SetLineWidth(3);
  h_corr_1->SetLineWidth(3);
  h_corr_2->SetLineWidth(3);
  h_corr_3->SetLineWidth(3);
  h_corr_4->SetLineWidth(3);
  h_MB_r->SetLineWidth(3);
  h_input_r->GetYaxis()->SetRangeUser(0.0002,2);
  h_input_r->Draw();
  h_corr_1->Draw("same");
  h_corr_2->Draw("same");
  h_corr_3->Draw("same");
  h_corr_4->Draw("same");
  h_MB_r->Draw("same");
  //h_bPurity->Draw("same");

  // calculate bRatio
  TH1D *r = (TH1D*) h_corr_3->Clone("r");
  r->Divide(h_corr_4,h_MB_r,1,1,"");

  TCanvas *c2 = new TCanvas("c2","c2",700,700);
  c2->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,1);
  p2->SetLeftMargin(0.2);
  p2->SetBottomMargin(0.2);
  p2->Draw();
  p2->cd();
  r->GetYaxis()->SetTitle("#font[52]{b}-jet fraction");
  r->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  r->SetTitle("");
  r->SetStats(0);
  r->GetYaxis()->SetRangeUser(0,0.07);
  r->Draw();

  if(ispp){
    file_save_name = "../../rootFiles/bFractionResults/bFractionResults_pp.root";
  }
  else if(isC2){
    file_save_name = "../../rootFiles/bFractionResults/bFractionResults_C2.root";
  }
  else if(isC1){
    file_save_name = "../../rootFiles/bFractionResults/bFractionResults_C1.root";
  }
  else{};

  bFractionResults_file = TFile::Open(file_save_name,"recreate");
  r->Write();
  bFractionResults_file->Close();
  
  */
  

}
