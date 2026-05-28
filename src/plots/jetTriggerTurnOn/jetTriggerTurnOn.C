



void jetTriggerTurnOn(){


  TFile *file_pp_jet60 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet60HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-5.root");
  TFile *file_pp_jet60PlusJet80 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet60HLT_Jet80HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-5.root");
  TFile *file_pp_jet80 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet80HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-5.root");
  TFile *file_pp_jet100 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet80HLT_Jet100HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-5.root");

  TH1D *h_pp_jet60, *h_pp_jet60PlusJet80, *h_pp_jet80, *h_pp_jet100;

  file_pp_jet60->GetObject("h_inclRecoJetPt",h_pp_jet60);
  file_pp_jet60PlusJet80->GetObject("h_inclRecoJetPt",h_pp_jet60PlusJet80);
  file_pp_jet80->GetObject("h_inclRecoJetPt",h_pp_jet80);
  file_pp_jet100->GetObject("h_inclRecoJetPt",h_pp_jet100);

  TH1D *r_pp_jet60PlusJet80, *r_pp_jet100;

  r_pp_jet60PlusJet80 = (TH1D*) h_pp_jet60PlusJet80->Clone("r_pp_jet60PlusJet80");
  r_pp_jet60PlusJet80->Divide(h_pp_jet60PlusJet80,h_pp_jet60,1,1,"B");

  r_pp_jet100 = (TH1D*) h_pp_jet100->Clone("r_pp_jet100");
  r_pp_jet100->Divide(h_pp_jet100,h_pp_jet80,1,1,"B");

  r_pp_jet100->Draw();
  r_pp_jet60PlusJet80->Draw("same");
}
