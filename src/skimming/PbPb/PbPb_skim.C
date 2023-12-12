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

void PbPb_skim(int group = 0,
	       int startgroup = 0,
	       int endgroup = 20){

  TTree *jet_tree, *jet_evt_tree, *muon_tree, *muon_evt_tree, *hlt_tree, *evt_tree, *filter_tree;
  string in_file_name;
  string output_file_base = "./";
  
  
  in_file_name = "fileNames/fileNames_PbPb_SingleMuon_3Oct23_%i.txt";
  output_file_base += Form("output/PbPb_skim_output_%i",group) ;
  

  cout << "trying a file list named " << in_file_name << endl;

  
  
  string output_file_extension = "";
  output_file_extension += ".root";

  TFile *output_file = new TFile((TString) (output_file_base+output_file_extension), "RECREATE");
  TTree *my_filter_tree = new TTree("filterTree","");
  TTree *my_evt_tree = new TTree("evtTree","");
  TTree *my_hlt_tree = new TTree("hltTree","");
  TTree *my_jet_tree = new TTree("jetTree","");
  TTree *my_jet_evt_tree = new TTree("jetEvtTree","");
  TTree *my_muon_tree = new TTree("muonTree","");
  TTree *my_muon_evt_tree = new TTree("muonEvtTree","");

  
  // ----- filter variables 
  Int_t pprimaryVertexFilter,
    HBHENoiseFilterResultRun2Loose,
    collisionEventSelectionAODv2,
    phfCoincFilter3Th4,
    pclusterCompatibilityFilter;
  my_filter_tree->Branch("pprimaryVertexFilter",&pprimaryVertexFilter);
  my_filter_tree->Branch("HBHENoiseFilterResultRun2Loose",&HBHENoiseFilterResultRun2Loose);
  my_filter_tree->Branch("collisionEventSelectionAODv2",&collisionEventSelectionAODv2);
  my_filter_tree->Branch("phfCoincFilter3Th4",&phfCoincFilter3Th4);
  my_filter_tree->Branch("pclusterCompatibilityFilter",&pclusterCompatibilityFilter);

  // ----- event variables
  Int_t hiBin, run, lumi, evt;
  Float_t vz, hiHF;
  my_evt_tree->Branch("hiBin",&hiBin);
  my_evt_tree->Branch("hiHF",&hiHF);
  my_evt_tree->Branch("run",&run);
  my_evt_tree->Branch("lumi",&lumi);
  my_evt_tree->Branch("evt",&evt);
  my_evt_tree->Branch("vz",&vz);

  // ----- HLT variables
  Int_t HLT_HIL3Mu5_NHitQ10_v1, HLT_HIL3Mu7_NHitQ10_v1, HLT_HIL3Mu12_v1;
  Int_t HLT_HIL3Mu5_NHitQ10_v1_Prescl, HLT_HIL3Mu7_NHitQ10_v1_Prescl, HLT_HIL3Mu12_v1_Prescl;
  my_hlt_tree->Branch("HLT_HIL3Mu5_NHitQ10_v1",&HLT_HIL3Mu5_NHitQ10_v1);
  my_hlt_tree->Branch("HLT_HIL3Mu7_NHitQ10_v1",&HLT_HIL3Mu7_NHitQ10_v1);
  my_hlt_tree->Branch("HLT_HIL3Mu12_v1",&HLT_HIL3Mu12_v1);
  my_hlt_tree->Branch("HLT_HIL3Mu5_NHitQ10_v1_Prescl",&HLT_HIL3Mu5_NHitQ10_v1_Prescl);
  my_hlt_tree->Branch("HLT_HIL3Mu7_NHitQ10_v1_Prescl",&HLT_HIL3Mu7_NHitQ10_v1_Prescl);
  my_hlt_tree->Branch("HLT_HIL3Mu12_v1_Prescl",&HLT_HIL3Mu12_v1_Prescl);

  // ----- jet variables
  Float_t jtpt, rawpt, jteta, jtphi, trackMax;
  Int_t nref;
  my_jet_tree->Branch("jtpt",&jtpt);
  my_jet_tree->Branch("rawpt",&rawpt);
  my_jet_tree->Branch("jteta",&jteta);
  my_jet_tree->Branch("jtphi",&jtphi);
  my_jet_tree->Branch("trackMax",&trackMax);
  my_jet_evt_tree->Branch("nref",&nref);

  // ----- muon variables
  Float_t muPt, muEta, muPhi;
  Float_t muChi2NDF, muInnerD0, muInnerDz;
  Int_t muIsPF, muIsGlobal, muIsTracker, muMuonHits, muStations, muTrkLayers, muPixelHits, muCharge;
  Int_t nMu;
  my_muon_tree->Branch("muPt",&muPt);
  my_muon_tree->Branch("muEta",&muEta);
  my_muon_tree->Branch("muPhi",&muPhi);
  my_muon_tree->Branch("muChi2NDF",&muChi2NDF);
  my_muon_tree->Branch("muInnerD0",&muInnerD0);
  my_muon_tree->Branch("muInnerDz",&muInnerDz);
  my_muon_tree->Branch("muIsPF",&muIsPF);
  my_muon_tree->Branch("muIsGlobal",&muIsGlobal);
  my_muon_tree->Branch("muIsTracker",&muIsTracker);
  my_muon_tree->Branch("muMuonHits",&muMuonHits);
  my_muon_tree->Branch("muStations",&muStations);
  my_muon_tree->Branch("muTrkLayers",&muTrkLayers);
  my_muon_tree->Branch("muPixelHits",&muPixelHits);
  my_muon_tree->Branch("muCharge",&muCharge);
  my_muon_evt_tree->Branch("nMu",&nMu);
  
  std::ifstream instr(in_file_name.c_str(), std::ifstream::in);
  if(!instr.is_open()) cout << "filelist not found!! Exiting..." << endl;
  std::string filename;
  Int_t ifile = 0;

  
  // -- tree variables
  // ----- filter variables 
  Int_t t_pprimaryVertexFilter[1], 
    t_HBHENoiseFilterResultRun2Loose[1], 
    t_collisionEventSelectionAODv2[1], 
    t_phfCoincFilter3Th4[1], 
    t_pclusterCompatibilityFilter[1];
  // ----- event variables
  Int_t t_hiBin[1];
  UInt_t t_run[1], t_lumi[1];
  ULong64_t t_evt[1];
  Float_t t_hiHF[1];
  Float_t t_vz[1];
  // ----- HLT variables
  Int_t t_HLT_HIL3Mu5_NHitQ10_v1[1], t_HLT_HIL3Mu7_NHitQ10_v1[1], t_HLT_HIL3Mu12_v1[1];
  Int_t t_HLT_HIL3Mu5_NHitQ10_v1_Prescl[1], t_HLT_HIL3Mu7_NHitQ10_v1_Prescl[1], t_HLT_HIL3Mu12_v1_Prescl[1];
  // ----- jet variables
  const int MAXJETS = 1000;
  Float_t t_jtpt[MAXJETS], t_rawpt[MAXJETS], t_jteta[MAXJETS], t_jtphi[MAXJETS], t_trackMax[MAXJETS];
  Int_t t_nref[1];
  // ----- muon variables
  vector<float> *t_muPt=0, *t_muEta=0, *t_muPhi=0;
  vector<Float_t> *t_muChi2NDF=0, *t_muInnerD0=0, *t_muInnerDz=0;
  vector<Int_t> *t_muIsPF=0, *t_muIsGlobal=0, *t_muIsTracker=0, *t_muMuonHits=0, *t_muStations=0, *t_muTrkLayers=0, *t_muPixelHits=0, *t_muCharge=0;
  Int_t t_nMu[1];
  
  int endfile = 7176;
    
  while(instr>>filename && ifile<endfile){
    
    //cout << "Filename is " << filename << endl;
    ifile++;

    if(ifile < startgroup || ifile > endgroup) continue;
    
    cout << (100.)*(1.0*ifile / (1.0*endfile)) << " %" << endl;

    TFile *my_file = TFile::Open(filename.c_str());
    
    filter_tree     = (TTree*) my_file->Get("skimanalysis/HltTree");
    evt_tree        = (TTree*) my_file->Get("hiEvtAnalyzer/HiTree");
    hlt_tree        = (TTree*) my_file->Get("hltanalysis/HltTree");
    jet_tree        = (TTree*) my_file->Get("akCs4PFJetAnalyzer/t");
    jet_evt_tree    = (TTree*) my_file->Get("akCs4PFJetAnalyzer/t");
    muon_tree       = (TTree*) my_file->Get("ggHiNtuplizerGED/EventTree");
    muon_evt_tree   = (TTree*) my_file->Get("ggHiNtuplizerGED/EventTree");

    //cout << "trees loaded" << endl;

    // ----- filter variables
    filter_tree->SetBranchAddress("pprimaryVertexFilter",t_pprimaryVertexFilter);
    filter_tree->SetBranchAddress("HBHENoiseFilterResultRun2Loose",t_HBHENoiseFilterResultRun2Loose);
    filter_tree->SetBranchAddress("collisionEventSelectionAODv2",t_collisionEventSelectionAODv2);
    filter_tree->SetBranchAddress("phfCoincFilter3Th4",t_phfCoincFilter3Th4);
    filter_tree->SetBranchAddress("pclusterCompatibilityFilter",t_pclusterCompatibilityFilter);
    // ----- event variables
    evt_tree->SetBranchAddress("hiBin",t_hiBin);
    evt_tree->SetBranchAddress("hiHF",t_hiHF);
    evt_tree->SetBranchAddress("run",t_run);
    evt_tree->SetBranchAddress("lumi",t_lumi);
    evt_tree->SetBranchAddress("evt",t_evt);
    evt_tree->SetBranchAddress("vz",t_vz);
    // ----- HLT variables
    hlt_tree->SetBranchAddress("HLT_HIL3Mu5_NHitQ10_v1",t_HLT_HIL3Mu5_NHitQ10_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu7_NHitQ10_v1",t_HLT_HIL3Mu7_NHitQ10_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu12_v1",t_HLT_HIL3Mu12_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu5_NHitQ10_v1_Prescl",t_HLT_HIL3Mu5_NHitQ10_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu7_NHitQ10_v1_Prescl",t_HLT_HIL3Mu7_NHitQ10_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu12_v1_Prescl",t_HLT_HIL3Mu12_v1_Prescl);
    // ----- jet variables
    jet_tree->SetBranchAddress("jtpt",t_jtpt);
    jet_tree->SetBranchAddress("rawpt",t_rawpt);
    jet_tree->SetBranchAddress("jteta",t_jteta);
    jet_tree->SetBranchAddress("jtphi",t_jtphi);
    jet_tree->SetBranchAddress("trackMax",t_trackMax);
    jet_tree->SetBranchAddress("nref",t_nref);
    // ----- muon variables
    muon_tree->SetBranchAddress("muPt",&t_muPt);
    muon_tree->SetBranchAddress("muEta",&t_muEta);
    muon_tree->SetBranchAddress("muPhi",&t_muPhi);
    muon_tree->SetBranchAddress("muChi2NDF",&t_muChi2NDF);
    muon_tree->SetBranchAddress("muInnerD0",&t_muInnerD0);
    muon_tree->SetBranchAddress("muInnerDz",&t_muInnerDz);
    muon_tree->SetBranchAddress("muIsPF",&t_muIsPF);
    muon_tree->SetBranchAddress("muIsGlobal",&t_muIsGlobal);
    muon_tree->SetBranchAddress("muIsTracker",&t_muIsTracker);
    muon_tree->SetBranchAddress("muMuonHits",&t_muMuonHits);
    muon_tree->SetBranchAddress("muStations",&t_muStations);
    muon_tree->SetBranchAddress("muTrkLayers",&t_muTrkLayers);
    muon_tree->SetBranchAddress("muPixelHits",&t_muPixelHits);
    muon_tree->SetBranchAddress("muCharge",&t_muCharge);
    muon_tree->SetBranchAddress("nMu",t_nMu);

    int n_evt = evt_tree->GetEntriesFast();

    //cout << "Entries: " << n_evt << endl;

    for(int evi = 0; evi < n_evt; evi++){

      filter_tree->GetEntry(evi);
      evt_tree->GetEntry(evi);
      hlt_tree->GetEntry(evi);
      jet_tree->GetEntry(evi);
      jet_evt_tree->GetEntry(evi);
      muon_tree->GetEntry(evi);
      muon_evt_tree->GetEntry(evi);
      
      pprimaryVertexFilter = t_pprimaryVertexFilter[0];
      HBHENoiseFilterResultRun2Loose = t_HBHENoiseFilterResultRun2Loose[0];
      collisionEventSelectionAODv2 = t_collisionEventSelectionAODv2[0];
      phfCoincFilter3Th4 = t_phfCoincFilter3Th4[0];
      pclusterCompatibilityFilter = t_pclusterCompatibilityFilter[0];

      // --- event-filter cuts
      if(pprimaryVertexFilter           == 0 || 
         HBHENoiseFilterResultRun2Loose == 0 || 
	 collisionEventSelectionAODv2   == 0 ||
	 phfCoincFilter3Th4             == 0 ||
	 pclusterCompatibilityFilter    == 0
	 ) continue;
      
      hiBin = t_hiBin[0];
      hiHF = t_hiHF[0];
      run = t_run[0];
      lumi = t_lumi[0];
      evt = t_evt[0];
      vz = t_vz[0];

      // --- event cuts
      if(hiBin > 180 || fabs(vz) > 15.0 || hiHF > 5500) continue;

      HLT_HIL3Mu5_NHitQ10_v1 = t_HLT_HIL3Mu5_NHitQ10_v1[0];
      HLT_HIL3Mu7_NHitQ10_v1 = t_HLT_HIL3Mu7_NHitQ10_v1[0];
      HLT_HIL3Mu12_v1 = t_HLT_HIL3Mu12_v1[0];
      HLT_HIL3Mu5_NHitQ10_v1_Prescl = t_HLT_HIL3Mu5_NHitQ10_v1_Prescl[0];
      HLT_HIL3Mu7_NHitQ10_v1_Prescl = t_HLT_HIL3Mu7_NHitQ10_v1_Prescl[0];
      HLT_HIL3Mu12_v1_Prescl = t_HLT_HIL3Mu12_v1_Prescl[0];
      
      // if all muon-triggers are off, dismiss event
      if(HLT_HIL3Mu5_NHitQ10_v1 == 0 &&
	 HLT_HIL3Mu7_NHitQ10_v1 == 0 &&
	 HLT_HIL3Mu12_v1 == 0) continue;

      int nref_prime = 0; // counter variable for nref
      
      for(int jeti = 0; jeti < t_nref[0]; jeti++){

	jtpt = t_jtpt[jeti];
	rawpt = t_rawpt[jeti];
	jteta = t_jteta[jeti];
	jtphi = t_jtphi[jeti];
	trackMax = t_trackMax[jeti];

	// fill the tree
	my_jet_tree->Fill();
	nref_prime++;

      } // end jet loop

      nref = nref_prime;
      
      int nMu_prime = 0;
      
      for(int mui = 0; mui < t_nMu[0]; mui++){

	muPt = t_muPt->at(mui);
	muEta = t_muEta->at(mui);
	muPhi = t_muPhi->at(mui);
	muChi2NDF = t_muChi2NDF->at(mui);
	muInnerD0 = t_muInnerD0->at(mui);
	muInnerDz = t_muInnerDz->at(mui);
	muIsPF = t_muIsPF->at(mui);
	muIsGlobal = t_muIsGlobal->at(mui);
	muIsTracker = t_muIsTracker->at(mui);
	muMuonHits = t_muMuonHits->at(mui);
	muStations = t_muStations->at(mui);
	muTrkLayers = t_muTrkLayers->at(mui);
	muPixelHits = t_muPixelHits->at(mui);
	muCharge = t_muCharge->at(mui);

	// fill the tree
	my_muon_tree->Fill();
	nMu_prime++;

      } // end muon loop

      nMu = nMu_prime;
      
      
      // fill event trees
      my_muon_evt_tree->Fill();
      my_jet_evt_tree->Fill();
      my_filter_tree->Fill();
      my_evt_tree->Fill();
      my_hlt_tree->Fill();


    } // end event loop

    my_file->Close();

  } // end file loop

  cout << "writing" << endl;

  output_file->cd();
  my_filter_tree->Write();
  my_evt_tree->Write();
  my_hlt_tree->Write();
  my_jet_tree->Write();
  my_jet_evt_tree->Write();
  my_muon_tree->Write();
  my_muon_evt_tree->Write();
  output_file->Close();

  cout << "done" << endl;
  
}


