


void debug_hiBin(){

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-4-28.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-19.root");

  TH1D *h1, *h2;

  f1->GetObject("h_hiBin",h1);
  f2->GetObject("h_hiBin",h2);

  cout << "h1->Integral() = " << h1->Integral() << endl;
  cout << "h2->Integral() = " << h2->Integral() << endl;

  h2->Draw();


}
