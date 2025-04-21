//#include "../../../headers/goldenFileNames.h"
TString input_PYTHIA_inclJets, input_PYTHIA_inclJets_ResolutionSmear;
TString input_PH_inclJets, input_PH_inclJets_ResolutionSmear;
TFile *f_py_i, *f_py_r; // inclusive (i) and resolution-smeared (r) PYTHIA files
TFile *f_ph_i, *f_ph_r; // inclusive (i) and resolution-smeared (r) PYTHIA+HYDJET files
TH2D *H_py_i, *H_py_r;  // 2D histogram from PYTHIA
TH2D *H_ph_C1_i, *H_ph_C1_r;  // 2D histogram from PYTHIA+HYDJET 0-10%
TH2D *H_ph_C2_i, *H_ph_C2_r;  // 2D histogram from PYTHIA+HYDJET 30-50%
TH2D *A_ph_C1_i, *A_ph_C1_r;  // 2D histogram from PYTHIA+HYDJET 10-30%
TH2D *A_ph_C2_i, *A_ph_C2_r;  // 2D histogram from PYTHIA+HYDJET 50-90%
TH1D *h_py_i, *h_py_r; // 1D projections
TH1D *h_ph_C1_i, *h_ph_C1_r;
TH1D *h_ph_C2_i, *h_ph_C2_r;
TH1D *r_py, *r_ph_C2, *r_ph_C1; // ratios of resolution-smeared to nominal

void response_calculation(){

  input_PYTHIA_inclJets = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets.root";
  input_PYTHIA_inclJets_ResolutionSmear = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets_doJERCorrection.root";

  input_PH_inclJets = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/PH_DiJet_pTjet-5_pThat-15_response.root";
  input_PH_inclJets_ResolutionSmear = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/PH_DiJet_pTjet-5_pThat-15_response_doJERCorrection.root";
  
  f_py_i = TFile::Open(input_PYTHIA_inclJets);
  f_py_r = TFile::Open(input_PYTHIA_inclJets_ResolutionSmear);

  f_ph_i = TFile::Open(input_PH_inclJets);
  f_ph_r = TFile::Open(input_PH_inclJets_ResolutionSmear);

  f_py_i->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_py_i);
  f_py_r->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_py_r);


  f_ph_i->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C1",H_ph_C1_i);
  //f_ph_i->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",A_ph_C1_i);
  f_ph_i->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H_ph_C2_i);
  //f_ph_i->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C4",A_ph_C2_i);
  //H_ph_C1_i->Add(A_ph_C1_i);
  //H_ph_C2_i->Add(A_ph_C2_i);

  f_ph_r->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C1",H_ph_C1_r);
  //f_ph_r->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",A_ph_C1_r);
  f_ph_r->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H_ph_C2_r);
  //f_ph_r->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C4",A_ph_C2_r);
  //H_ph_C1_r->Add(A_ph_C1_r);
  //H_ph_C2_r->Add(A_ph_C2_r);

  h_py_i = (TH1D*) H_py_i->ProjectionX("h_py_i");
  h_py_r = (TH1D*) H_py_r->ProjectionX("h_py_r");
  h_ph_C1_i = (TH1D*) H_ph_C1_i->ProjectionX("h_ph_C1_i");
  h_ph_C2_i = (TH1D*) H_ph_C2_i->ProjectionX("h_ph_C2_i");
  h_ph_C1_r = (TH1D*) H_ph_C1_r->ProjectionX("h_ph_C1_r");
  h_ph_C2_r = (TH1D*) H_ph_C2_r->ProjectionX("h_ph_C2_r");
  

  r_py = (TH1D*) h_py_i->Clone("r_py");
  r_ph_C2 = (TH1D*) h_ph_C2_i->Clone("r_ph_C2");
  r_ph_C1 = (TH1D*) h_ph_C1_i->Clone("r_ph_C1");
  
  r_py->Divide(h_py_i,h_py_r,1,1,"B");
  r_ph_C2->Divide(h_ph_C2_i,h_ph_C2_r,1,1,"B");
  r_ph_C1->Divide(h_ph_C1_i,h_ph_C1_r,1,1,"B");

  
  r_py->Draw();
  //r_ph_C2->Draw();
  //r_ph_C1->Draw("same");
  
  





}
