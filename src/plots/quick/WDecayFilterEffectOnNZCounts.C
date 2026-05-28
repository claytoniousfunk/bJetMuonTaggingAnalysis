


void WDecayFilterEffectOnNZCounts(){


  TFile *file_withFilter = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet60HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_WDecayFilter_2026-3-11.root");
  TFile *file_noFilter = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet60HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-10.root");

  TH1D *h_dimuonMass_withFilter, *h_dimuonMass_noFilter;

  file_noFilter->GetObject("h_dimuonMass", h_dimuonMass_noFilter);
  file_noFilter->GetObject("h_dimuonMass", h_dimuonMass_withFilter);

  std::cout << "entries (no filter) = " << h_dimuonMass_noFilter->GetEntries() << "\n";
  std::cout << "entries (with filter) = " << h_dimuonMass_withFilter->GetEntries() << "\n";





}
