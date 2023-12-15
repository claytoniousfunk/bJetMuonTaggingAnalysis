void pp_skim_simple(int group = 1){

  string in_file_name;
  string output_file_base = "./";
  in_file_name = "fileNames/fileNames_pp_SingleMuon_24Oct23.txt";
  output_file_base += Form("output/pp_SingleMuon_skim_output_%i",group);
  string output_file_extension = "";
  output_file_extension += ".root";

  std::ifstream instr(in_file_name.c_str(), std::ifstream::in);
  if(!instr.is_open()) cout << "filelist not found!! Exiting..." << endl;
  std::string filename;
  Int_t ifile = 0;

  int endfile = 6033;

  TFile *old_file;
  TString filename_string = "";
  TFile *new_file;
  TTree *new_jet_tree;
  while(instr>>filename && ifile<endfile){

    ifile++;

    if(ifile != group) continue;
  
    cout << (100.)*(1.0*ifile / (1.0*endfile)) << " %" << endl;

    filename_string = filename.c_str();
    
  

    cout << "filename is " << filename_string << endl;


    old_file = TFile::Open(filename.c_str());
  
    TTree *old_jet_tree;
    old_file->GetObject("ak4PFJetAnalyzer/t",old_jet_tree);
    // deactivate all branches                                                                                                                                             
    old_jet_tree->SetBranchStatus("*",0);
    // activate only our variables of interest                                                                                                                             
    old_jet_tree->SetBranchStatus("jtpt",1);
    old_jet_tree->SetBranchStatus("jteta",1);
    old_jet_tree->SetBranchStatus("jtphi",1);
    old_jet_tree->SetBranchStatus("nref",1);

    new_file = (TFile*) TFile::Open((TString) (output_file_base+output_file_extension),"recreate");
    new_jet_tree = (TTree*) old_jet_tree->CloneTree(0);

    new_jet_tree->CopyEntries(old_jet_tree);

    new_file->Write();

  }

}
