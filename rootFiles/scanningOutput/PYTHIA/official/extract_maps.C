
void extract_neutrino_map(){

  TFile *file_in = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_muTaggedJets_withNeutrino.root");
  TH2D *H_save;
  file_in->GetObject("h_matchedNeutrinoPt_recoJetPt_bJets",H_save);
  TFile *file_out = TFile::Open("./neutrino_energy_map.root","recreate");
  H_save->Write("neutrino_energy_map");
  
}




void extract_maps(){

  extrac_neutrino_map();
  extract_neutrino_tag_fraction();
  
  return;

}
