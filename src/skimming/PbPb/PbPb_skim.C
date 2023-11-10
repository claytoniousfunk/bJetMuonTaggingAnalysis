#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TF1.h"

#include "TH2F.h"
#include "TMath.h"
#include <TNtuple.h>
#include "TChain.h"
#include <TString.h>
#include <TCut.h>
#include "TStopwatch.h"
#include "TEnv.h"

#include "assert.h"
#include <fstream>
#include "TMath.h"
#include <vector>

using namespace std;

void PbPb_skim(){

  TTree *inp_tree;
  string in_file_name;

  in_file_name = "fileNames_PbPb_SingleMuon_3Oct23.txt";

  cout << "trying a file list named " << in_file_name << endl;

  string output_file_base = "./";

  output_file_base += "PbPb_skim" ;
  
  string output_file_extension = "";
  output_file_extension += ".root";

  TFile *output_file = new TFile((TString) (output_file_base+output_file_extension), "RECREATE");
  TTree *ftree = new TTree("unzipMixTree","");

  float jtpt, jteta, jtphi;
  int nref;
  
  ftree->Branch("jtpt",&jtpt);
  ftree->Branch("jteta",&jteta);
  ftree->Branch("jtphi",&jtphi);
  ftree->Branch("nref",&nref);
  
  std::ifstream instr(in_file_name.c_str(), std::ifstream::in);
  if(!instr.is_open()) cout << "filelist not found!! Exiting..." << endl;
  std::string filename;
  int ifile = 0;

  const int MAXJETS = 500;


  Float_t t_jtpt[MAXJETS], t_jteta[MAXJETS], t_jtphi[MAXJETS];

  
  int endfile = 7176;
  while(instr>>filename && ifile<endfile){
    
    cout << "Filename is " << filename << endl;
    ifile++;

    TFile *my_file = TFile::Open(filename.c_str());
    
    inp_tree = (TTree*) my_file->Get("akCs4PFJetAnalyzer/t");

    cout << "tree loaded" << endl;

    inp_tree->SetBranchAddress("jtpt",t_jtpt);
    inp_tree->SetBranchAddress("jteta",t_jteta);
    inp_tree->SetBranchAddress("jtphi",t_jtphi);

    int n_evt = inp_tree->GetEntriesFast();

    cout << "Entries: " << n_evt << endl;

    for(int evi = 0; evi < n_evt; evi++){

      inp_tree->GetEntry(evi);

      for(int jeti = 0; jeti < nref; jeti++){

	if(fabs(t_jteta[jeti]) > 1.6 || t_jtpt[jeti] < 50.) continue;

	jtpt = t_jtpt[jeti];
	jteta = t_jteta[jeti];
	jtphi = t_jtphi[jeti];

	ftree->Fill();

      } // end jet loop
      
    } // end event loop

  } // end file loop

  cout << "writing" << endl;

  output_file->cd();
  ftree->Write();
  output_file->Close();

  cout << "done" << endl;
  
}


