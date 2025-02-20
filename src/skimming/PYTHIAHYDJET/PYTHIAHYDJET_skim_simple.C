void PYTHIAHYDJET_skim_simple(int group = 1){

  string in_file_name;
  string output_file_base = "";

  // DiJet, N = 6884
  // in_file_name = "../../../fileNames/fileNames_PYTHIAHYDJET_DiJet_withGS_withWTA.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/output_PYTHIAHYDJET_DiJet_withGS_withWTA_2/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // MuJet, N = 2923
  // in_file_name = "../../../fileNames/fileNames_PYTHIAHYDJET_MuJet_withGS_withWTA.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/output_PYTHIAHYDJET_MuJet_withGS_withWTA_2/PYTHIAHYDJET_MuJet_skim_output_%i",group);

  // MuJet, N = 4257
  // in_file_name = "../../../fileNames/fileNames_PYTHIAHYDJET_BJet_withGS_withWTA.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/output_PYTHIAHYDJET_BJet_withGS_withWTA_2/PYTHIAHYDJET_BJet_skim_output_%i",group);

  // DiJet additional, N = 6184
  // in_file_name = "../../../fileNames/fileNames_forest_PYTHIAHYDJET_DiJet_additionalMC_fullStats.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/output_skim_PYTHIAHYDJET_DiJet_additionalMC_fullStats/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // DiJet additional, N = 8117
  // in_file_name = "../../../fileNames/fileNames_forest_PYTHIAHYDJET_DiJet_additionalMC_2024-08-05.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/output_skim_PYTHIAHYDJET_DiJet_additionalMC_2024-08-05/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // // DiJet, incl, pTjet-5, N = 7117
  // in_file_name = "../../../fileNames/fileNames_PH_DiJet_pTjet-5.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/output_skim_PH_DiJet_pTjet-5_reskim/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // DiJet, additional MC, incl, pTjet-15, N = 1411
  // in_file_name = "../../../fileNames/fileNames_PH_DiJet_batch13.txt";
  // output_file_base += Form("/eos/user/c/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch13/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // DiJet, additional MC, incl, pTjet-15, N = 1188
  // in_file_name = "../../../fileNames/fileNames_PH_DiJet_batch14.txt";
  // output_file_base += Form("/eos/user/c/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch14/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // DiJet, additional MC, incl, pTjet-15, N = 1325
  //in_file_name = "../../../fileNames/fileNames_PH_DiJet_batch15.txt";
  //output_file_base += Form("/eos/user/c/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch15/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // BATCH 1: DiJet, additional MC, incl, pTjet-15, N = 1653
  // in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch1.txt";
  // output_file_base += Form("/eos/user/c/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch1/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // BATCH 2: DiJet, additional MC, incl, pTjet-15, N = 4620
  //in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch2.txt";
  //output_file_base += Form("/eos/user/c/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch2/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // BATCH 3: DiJet, additional MC, incl, pTjet-15, N = 4785 
  //in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch3.txt";
  //output_file_base += Form("/eos/user/c/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch3/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // // BATCH 4: DiJet, additional MC, incl, pTjet-15, N = 4572 
  // in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch4.txt";
  // output_file_base += Form("/eos/user/c/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch4/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // // BATCH 5: DiJet, additional MC, incl, pTjet-15, N = 4771 
  // in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch5.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch5/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // // BATCH 6: DiJet, additional MC, incl, pTjet-15, N = 4828
  // in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch6.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch6/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // // BATCH 7: DiJet, additional MC, incl, pTjet-15, N = 4004
  // in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch7.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch7/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // // BATCH 8: DiJet, additional MC, incl, pTjet-15, N = 4196
  // in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch8.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch8/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // // BATCH 9: DiJet, additional MC, incl, pTjet-15, N = 4678
  // in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch9.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch9/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // // BATCH 10: DiJet, additional MC, incl, pTjet-15, N = 4473
  // in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch10.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch10/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // PH forest with jetTrkMax information (eta, phi, dR), N = 6621
  // in_file_name = "../../../fileNames/fileNames_PH_DiJet_onlyJets_withTrackMaxInfo_allFiles_partial.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skim_PH_DiJet_onlyJets_withTrackMaxInfo_allFiles_partial/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // // PH forest with jetTrkMax information (eta, phi, dR), N = 7202
  // in_file_name = "../../../fileNames/fileNames_PH_DiJet_onlyJets_withTrackMaxInfo_withHLT.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skim_PH_DiJet_onlyJets_withTrackMaxInfo_withHLT/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // PH forest with jetTrkMax information (eta, phi, dR), N = 1
  // in_file_name = "../../../fileNames/fileNames_testForest_PH_DiJet.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skim_testForest_PH_DiJet/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // // BATCH 11: DiJet, additional MC, incl, pTjet-15, N = 2683
  // in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch11.txt";
  // output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch11/PYTHIAHYDJET_DiJet_skim_output_%i",group);

  // BATCH 11: DiJet, additional MC, incl, pTjet-15, N = 4628
  in_file_name = "../../../fileNames/dripping-tap/fileNames_PH_DiJet_batch12.txt";
  output_file_base += Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch12/PYTHIAHYDJET_DiJet_skim_output_%i",group);
  
  int endfile = 4628;



  string output_file_extension = "";
  output_file_extension += ".root";

  std::ifstream instr(in_file_name.c_str(), std::ifstream::in);
  if(!instr.is_open()) cout << "filelist not found!! Exiting..." << endl;
  std::string filename;
  Int_t ifile = 0;
 

  TFile *old_file;
  TString filename_string = "";
  TFile *new_file;
  TTree *old_filter_tree, *old_evt_tree, *old_hlt_tree, *old_jet_tree, *old_muon_tree, *old_gen_tree;
  TTree *new_filter_tree, *new_evt_tree, *new_hlt_tree, *new_jet_tree, *new_muon_tree, *new_gen_tree;
  
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
    old_file->GetObject("akCs4PFJetAnalyzer/t",old_jet_tree);
    old_file->GetObject("ggHiNtuplizerGED/EventTree",old_muon_tree);
    old_file->GetObject("HiGenParticleAna/hi",old_gen_tree);
    // deactivate all branches                                                                                   
    old_filter_tree->SetBranchStatus("*",0);
    old_evt_tree->SetBranchStatus("*",0);
    old_hlt_tree->SetBranchStatus("*",0);
    old_jet_tree->SetBranchStatus("*",0);
    old_muon_tree->SetBranchStatus("*",0);
    old_gen_tree->SetBranchStatus("*",0);
    
    // activate only our variables of interest

    // filters
    old_filter_tree->SetBranchStatus("pprimaryVertexFilter",1);
    old_filter_tree->SetBranchStatus("HBHENoiseFilterResultRun2Loose",1);
    old_filter_tree->SetBranchStatus("collisionEventSelectionAODv2",1);
    old_filter_tree->SetBranchStatus("phfCoincFilter3Th4",1);
    old_filter_tree->SetBranchStatus("phfCoincFilter2Th4",1);
    old_filter_tree->SetBranchStatus("pclusterCompatibilityFilter",1);

    // evt
    old_evt_tree->SetBranchStatus("hiBin",1);
    old_evt_tree->SetBranchStatus("hiHF",1);
    old_evt_tree->SetBranchStatus("run",1);
    old_evt_tree->SetBranchStatus("lumi",1);
    old_evt_tree->SetBranchStatus("evt",1);
    old_evt_tree->SetBranchStatus("vz",1);
    old_evt_tree->SetBranchStatus("pthat",1);
    old_evt_tree->SetBranchStatus("weight",1);

    // hlt
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu5_NHitQ10_v1",1);
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu7_NHitQ10_v1",1);
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu12_v1",1);
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu5_NHitQ10_v1_Prescl",1);
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu7_NHitQ10_v1_Prescl",1);
    old_hlt_tree->SetBranchStatus("HLT_HIL3Mu12_v1_Prescl",1);
    old_hlt_tree->SetBranchStatus("HLT_HICsAK4PFJet60Eta1p5_v1",1);
    old_hlt_tree->SetBranchStatus("HLT_HICsAK4PFJet60Eta1p5_v1_Prescl",1);
    old_hlt_tree->SetBranchStatus("HLT_HICsAK4PFJet80Eta1p5_v1",1);
    old_hlt_tree->SetBranchStatus("HLT_HICsAK4PFJet80Eta1p5_v1_Prescl",1);
    old_hlt_tree->SetBranchStatus("HLT_HICsAK4PFJet100Eta1p5_v1",1);
    old_hlt_tree->SetBranchStatus("HLT_HICsAK4PFJet100Eta1p5_v1_Prescl",1);

    // jets
    old_jet_tree->SetBranchStatus("jtpt",1);
    old_jet_tree->SetBranchStatus("rawpt",1);
    old_jet_tree->SetBranchStatus("jteta",1);
    old_jet_tree->SetBranchStatus("jtphi",1);
    old_jet_tree->SetBranchStatus("mupt",1);
    old_jet_tree->SetBranchStatus("WTAeta",1);
    old_jet_tree->SetBranchStatus("WTAphi",1);
    old_jet_tree->SetBranchStatus("trackMax",1);
    old_jet_tree->SetBranchStatus("nref",1);
    old_jet_tree->SetBranchStatus("refparton_flavor",1);
    old_jet_tree->SetBranchStatus("refparton_flavorForB",1);
    old_jet_tree->SetBranchStatus("matchedPartonFlavor",1);
    old_jet_tree->SetBranchStatus("matchedHadronFlavor",1);
    old_jet_tree->SetBranchStatus("bHadronNumber",1);
    old_jet_tree->SetBranchStatus("genpt",1);
    old_jet_tree->SetBranchStatus("geneta",1);
    old_jet_tree->SetBranchStatus("genphi",1);
    old_jet_tree->SetBranchStatus("ngen",1);
    old_jet_tree->SetBranchStatus("trackMaxEta",1);
    old_jet_tree->SetBranchStatus("trackMaxPhi",1);
    old_jet_tree->SetBranchStatus("trackMaxDR",1);

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

    // gen
    old_gen_tree->SetBranchStatus("pt",1);
    old_gen_tree->SetBranchStatus("eta",1);
    old_gen_tree->SetBranchStatus("phi",1);
    old_gen_tree->SetBranchStatus("chg",1);
    old_gen_tree->SetBranchStatus("pdg",1);
    old_gen_tree->SetBranchStatus("n",1);
    

    new_file = (TFile*) TFile::Open((TString) (output_file_base+output_file_extension),"recreate");
    
    new_filter_tree = (TTree*) old_filter_tree->CloneTree(0);
    new_evt_tree = (TTree*) old_evt_tree->CloneTree(0);
    new_hlt_tree = (TTree*) old_hlt_tree->CloneTree(0);
    new_jet_tree = (TTree*) old_jet_tree->CloneTree(0);
    new_muon_tree = (TTree*) old_muon_tree->CloneTree(0);
    new_gen_tree = (TTree*) old_gen_tree->CloneTree(0);

    new_filter_tree->CopyEntries(old_filter_tree);
    new_evt_tree->CopyEntries(old_evt_tree);
    new_hlt_tree->CopyEntries(old_hlt_tree);
    new_jet_tree->CopyEntries(old_jet_tree);
    new_muon_tree->CopyEntries(old_muon_tree);
    new_gen_tree->CopyEntries(old_gen_tree);

    new_filter_tree->SetName("filterTree");
    new_evt_tree->SetName("evtTree");
    new_hlt_tree->SetName("hltTree");
    new_jet_tree->SetName("jetTree");
    new_muon_tree->SetName("muonTree");
    new_gen_tree->SetName("genParticleTree");

    new_file->Write();

  }

}
