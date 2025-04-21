
TFile *file_pp_MinBias, *file_pp_DiJet, *file_pp_SingleMuon;
TFile *file_PbPb_MinBias, *file_PbPb_DiJet, *file_PbPb_SingleMuon;

TH1D *h_vz_pp_MinBias, *h_hiBin_pp_MinBias;
TH1D *h_vz_pp_DiJet, *h_hiBin_pp_DiJet;
TH1D *h_vz_pp_SingleMuon, *h_hiBin_pp_SingleMuon;

double N_evt_jet_pp_MinBias, N_evt_pp_MinBias;
double N_evt_muTag_pp_DiJet, N_evt_jet_pp_DiJet;
double N_evt_muTagMuTrig_pp_SingleMuon, N_evt_muTag_pp_SingleMuon;
double f_evt_jet_pp, f_evt_muTag_pp, f_evt_muTrig_pp, f_evt_tot_pp;


void eventCorrection_3CentBins(){

  file_pp_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/final/pp_MinBias_mu12_tight_pTmu-14_projectableTemplates.root");
  file_pp_DiJet = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/final/pp_HighEGJet_jet60_mu12_tight_pTmu-14_projectableTemplates.root");
  file_pp_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/final/pp_SingleMuon_mu12_tight_pTmu-14_projectableTemplates.root");

  file_PbPb_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/final/");

  file_pp_MinBias->GetObject("h_vz",h_vz_pp_MinBias);
  file_pp_MinBias->GetObject("h_hiBin",h_hiBin_pp_MinBias);
  file_pp_DiJet->GetObject("h_vz_inclRecoMuonTag",h_vz_pp_DiJet);
  file_pp_DiJet->GetObject("h_hiBin",h_hiBin_pp_DiJet);
  file_pp_SingleMuon->GetObject("h_vz_inclRecoMuonTag",h_vz_pp_SingleMuon);
  file_pp_SingleMuon->GetObject("h_hiBin_inclRecoMuonTag_triggerOn",h_hiBin_pp_SingleMuon);

  N_evt_pp_MinBias = h_vz_pp_MinBias->GetEntries();
  N_evt_jet_pp_MinBias = h_hiBin_pp_MinBias->GetEntries();
  f_evt_jet_pp = N_evt_jet_pp_MinBias / N_evt_pp_MinBias;

  N_evt_jet_pp_DiJet = h_hiBin_pp_DiJet->GetEntries();
  N_evt_muTag_pp_DiJet = h_vz_pp_DiJet->GetEntries();
  f_evt_muTag_pp = N_evt_muTag_pp_DiJet / N_evt_jet_pp_DiJet;

  N_evt_muTag_pp_SingleMuon = h_vz_pp_SingleMuon->GetEntries();
  N_evt_muTagMuTrig_pp_SingleMuon = h_hiBin_pp_SingleMuon->GetEntries();
  f_evt_muTrig_pp = N_evt_muTagMuTrig_pp_SingleMuon / N_evt_muTag_pp_SingleMuon;

  f_evt_tot_pp = f_evt_jet_pp * f_evt_muTag_pp * f_evt_muTrig_pp;

  cout << "N_evt_pp_MinBias = " << N_evt_pp_MinBias << endl;
  cout << "N_evt_jet_pp_MinBias = " << N_evt_jet_pp_MinBias << endl;
  cout << "f_evt_jet = " << f_evt_jet << endl;
  
  cout << "N_evt_jet_pp_DiJet = " << N_evt_jet_pp_DiJet << endl;
  cout << "N_evt_muTag_pp_DiJet = " << N_evt_muTag_pp_DiJet << endl;
  cout << "f_evt_muTag = " << f_evt_muTag << endl;

  cout << "N_evt_muTag_pp_SingleMuon = " << N_evt_muTag_pp_SingleMuon << endl;
  cout << "N_evt_muTagMuTrig_pp_SingleMuon = " << N_evt_muTagMuTrig_pp_SingleMuon << endl;
  cout << "f_evt_muTrig = " << f_evt_muTrig << endl;

  cout << "f_evt_tot = " << f_evt_tot << endl;


}
