void pp_skim_simple(int group = 1){

  string in_file_name;
  string output_file_base = "";
  in_file_name = "../../../fileNames/fileNames_pp_MinBias.txt";
  output_file_base += Form("/eos/user/c/cbennett/skims/output_skims_pp_HIZeroBias1_alt/pp_MinBias_skim_output_%i",group);
  string output_file_extension = "";
  output_file_extension += ".root";

  std::ifstream instr(in_file_name.c_str(), std::ifstream::in);
  if(!instr.is_open()) cout << "filelist not found!! Exiting..." << endl;
  std::string filename;
  Int_t ifile = 0;

  //int endfile = 6033;
  int endfile = 767;

  TFile *old_file;
  TString filename_string = "";
  TFile *new_file;
  TTree *old_filter_tree, *old_evt_tree, *old_hlt_tree, *old_jet_tree, *old_muon_tree;
  TTree *new_filter_tree, *new_evt_tree, *new_hlt_tree, *new_jet_tree, *new_muon_tree;
  
  while(instr>>filename && ifile<endfile){

    ifile++;

    if(ifile != group) continue;
  
    cout << (100.)*(1.0*ifile / (1.0*endfile)) << " %" << endl;

    filename_string = filename.c_str();
    
  

    cout << "filename is " << filename_string << endl;


    old_file = TFile::Open(filename.c_str());
  
    old_file->GetObject("skimanalysis/HltTree",old_filter_tree);
    old_file->GetObject("hiEvtAnalyzer/HiTree",old_evt_tree);
    old_file->GetObject("hltanalysis/HltTree",old_hlt_tree);
    old_file->GetObject("ak4PFJetAnalyzer/t",old_jet_tree);
    old_file->GetObject("ggHiNtuplizerGED/EventTree",old_muon_tree);
    // deactivate all branches                                                                                   
    old_filter_tree->SetBranchStatus("*",0);
    old_evt_tree->SetBranchStatus("*",0);
    old_hlt_tree->SetBranchStatus("*",0);
    old_jet_tree->SetBranchStatus("*",0);
    old_muon_tree->SetBranchStatus("*",0);
    // activate only our variables of interest
    // filters
    old_filter_tree->SetBranchStatus("pprimaryVertexFilter",1);
    old_filter_tree->SetBranchStatus("pPAprimaryVertexFilter",1);
    old_filter_tree->SetBranchStatus("HBHENoiseFilterResultRun2Loose",1);
    old_filter_tree->SetBranchStatus("pBeamScrapingFilter",1);
    // evt
    old_evt_tree->SetBranchStatus("hiBin",1);
    old_evt_tree->SetBranchStatus("hiHF",1);
    old_evt_tree->SetBranchStatus("run",1);
    old_evt_tree->SetBranchStatus("lumi",1);
    old_evt_tree->SetBranchStatus("evt",1);
    old_evt_tree->SetBranchStatus("vz",1);
    // hlt
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu5_v1",1);
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu7_v1",1);
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu12_v1",1);
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu5_v1_Prescl",1);
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu7_v1_Prescl",1);
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu12_v1_Prescl",1);
    // jets
    old_jet_tree->SetBranchStatus("jtpt",1);
    old_jet_tree->SetBranchStatus("rawpt",1);
    old_jet_tree->SetBranchStatus("jteta",1);
    old_jet_tree->SetBranchStatus("jtphi",1);
    old_jet_tree->SetBranchStatus("trackMax",1);
    old_jet_tree->SetBranchStatus("nref",1);
    // muons
    old_muon_tree->SetBranchStatus("muPt",1);
    old_muon_tree->SetBranchStatus("muEta",1);
    old_muon_tree->SetBranchStatus("muPhi",1);
    old_muon_tree->SetBranchStatus("muChi2NDF",1);
    old_muon_tree->SetBranchStatus("muInnerD0",1);
    old_muon_tree->SetBranchStatus("muInnerDz",1);
    old_muon_tree->SetBranchStatus("muIsPF",1);
    old_muon_tree->SetBranchStatus("muIsGlobal",1);
    old_muon_tree->SetBranchStatus("muIsTracker",1);
    old_muon_tree->SetBranchStatus("muMuonHits",1);
    old_muon_tree->SetBranchStatus("muStations",1);
    old_muon_tree->SetBranchStatus("muTrkLayers",1);
    old_muon_tree->SetBranchStatus("muPixelHits",1);
    old_muon_tree->SetBranchStatus("muCharge",1);
    old_muon_tree->SetBranchStatus("nMu",1);

    new_file = (TFile*) TFile::Open((TString) (output_file_base+output_file_extension),"recreate");
    
    new_filter_tree = (TTree*) old_filter_tree->CloneTree(0);
    new_evt_tree = (TTree*) old_evt_tree->CloneTree(0);
    new_hlt_tree = (TTree*) old_hlt_tree->CloneTree(0);
    new_jet_tree = (TTree*) old_jet_tree->CloneTree(0);
    new_muon_tree = (TTree*) old_muon_tree->CloneTree(0);

    new_filter_tree->CopyEntries(old_filter_tree);
    new_evt_tree->CopyEntries(old_evt_tree);
    new_hlt_tree->CopyEntries(old_hlt_tree);
    new_jet_tree->CopyEntries(old_jet_tree);
    new_muon_tree->CopyEntries(old_muon_tree);

    new_filter_tree->SetName("filterTree");
    new_evt_tree->SetName("evtTree");
    new_hlt_tree->SetName("hltTree");    
    new_jet_tree->SetName("jetTree");
    new_muon_tree->SetName("muonTree");

    new_file->Write();

  }

}
