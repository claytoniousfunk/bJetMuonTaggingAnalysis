


void flavorFraction(){

  TFile *f_PY = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-31.root");
  TFile *f_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-31.root");

  TH2D *H_pp_allJets, *H_pp_bJets, *H_pp_cJets, *H_pp_udJets, *H_pp_sJets, *H_pp_xJets;
  TH2D *H_C4_allJets, *H_C4_bJets, *H_C4_cJets, *H_C4_udJets, *H_C4_sJets, *H_C4_xJets;
  TH2D *H_C3_allJets, *H_C3_bJets, *H_C3_cJets, *H_C3_udJets, *H_C3_sJets, *H_C3_xJets;
  TH2D *H_C2_allJets, *H_C2_bJets, *H_C2_cJets, *H_C2_udJets, *H_C2_sJets, *H_C2_xJets;
  TH2D *H_C1_allJets, *H_C1_bJets, *H_C1_cJets, *H_C1_udJets, *H_C1_sJets, *H_C1_xJets;

  TH1D *h_pp_allJets, *h_pp_bJets, *h_pp_cJets, *h_pp_udJets, *h_pp_sJets, *h_pp_xJets;
  TH1D *h_C4_allJets, *h_C4_bJets, *h_C4_cJets, *h_C4_udJets, *h_C4_sJets, *h_C4_xJets;
  TH1D *h_C3_allJets, *h_C3_bJets, *h_C3_cJets, *h_C3_udJets, *h_C3_sJets, *h_C3_xJets;
  TH1D *h_C2_allJets, *h_C2_bJets, *h_C2_cJets, *h_C2_udJets, *h_C2_sJets, *h_C2_xJets;
  TH1D *h_C1_allJets, *h_C1_bJets, *h_C1_cJets, *h_C1_udJets, *h_C1_sJets, *h_C1_xJets;

  TH1D *h_pp_yJets, *h_C4_yJets, *h_C3_yJets, *h_C2_yJets, *h_C1_yJets;

  file_PY->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H_pp_allJets);
  file_PY->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_pp_bJets);
  file_PY->GetObject("h_matchedRecoJetPt_genJetPt_cJets",H_pp_cJets);
  file_PY->GetObject("h_matchedRecoJetPt_genJetPt_udJets",H_pp_udJets);
  file_PY->GetObject("h_matchedRecoJetPt_genJetPt_sJets",H_pp_sJets);
  file_PY->GetObject("h_matchedRecoJetPt_genJetPt_xJets",H_pp_xJets);
  file_PY->GetObject("h_unmatchedRecoJetPt_xJets",h_pp_yJets);

  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",H_C4_allJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C4",H_C4_bJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_cJets_C4",H_C4_cJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_udJets_C4",H_C4_udJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_sJets_C4",H_C4_sJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C4",H_C4_xJets);
  file_PY->GetObject("h_unmatchedRecoJetPt_xJets_C4",h_C4_yJets);

  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",H_C3_allJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C3",H_C3_bJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_cJets_C3",H_C3_cJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_udJets_C3",H_C3_udJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_sJets_C3",H_C3_sJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C3",H_C3_xJets);
  file_PY->GetObject("h_unmatchedRecoJetPt_xJets_C3",h_C3_yJets);

  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H_C2_allJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H_C2_bJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_cJets_C2",H_C2_cJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_udJets_C2",H_C2_udJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_sJets_C2",H_C2_sJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C2",H_C2_xJets);
  file_PY->GetObject("h_unmatchedRecoJetPt_xJets_C2",h_C2_yJets);

  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",H_C1_allJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C1",H_C1_bJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_cJets_C1",H_C1_cJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_udJets_C1",H_C1_udJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_sJets_C1",H_C1_sJets);
  file_PH->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C1",H_C1_xJets);
  file_PY->GetObject("h_unmatchedRecoJetPt_xJets_C1",h_C1_yJets);
  



  

}
