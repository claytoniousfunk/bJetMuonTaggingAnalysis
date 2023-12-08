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

void PYTHIA_skim(int group = 0,
		 int startgroup = 0,
		 int endgroup = 20){

  TTree *jet_tree, *jet_evt_tree, *muon_tree, *muon_evt_tree, *hlt_tree, *evt_tree, *filter_tree, *gen_particle_tree, *gen_particle_evt_tree;
  string in_file_name;
  string output_file_base = "./";
 

  
  
  in_file_name = "fileNames/fileNames_PYTHIA_DiJet.txt";
  output_file_base += Form("output/PYTHIA_skim_output_%i",startgroup) ;
  

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
  TTree *my_gen_particle_tree = new TTree("genParticleTree","");
  TTree *my_gen_particle_evt_tree = new TTree("genParticleEvtTree","");

  
  // ----- filter variables 
  Int_t pPAprimaryVertexFilter,
    HBHENoiseFilterResultRun2Loose;
  my_filter_tree->Branch("pPAprimaryVertexFilter",&pPAprimaryVertexFilter);
  my_filter_tree->Branch("HBHENoiseFilterResultRun2Loose",&HBHENoiseFilterResultRun2Loose);


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
  Int_t HLT_HIL3Mu5_NHitQ10_v1, HLT_HIL3Mu7_v1, HLT_HIL3Mu12_v1;
  Int_t HLT_HIL3Mu5_NHitQ10_v1_Prescl, HLT_HIL3Mu7_v1_Prescl, HLT_HIL3Mu12_v1_Prescl;
  my_hlt_tree->Branch("HLT_HIL3Mu5_NHitQ10_v1",&HLT_HIL3Mu5_NHitQ10_v1);
  my_hlt_tree->Branch("HLT_HIL3Mu7_v1",&HLT_HIL3Mu7_v1);
  my_hlt_tree->Branch("HLT_HIL3Mu12_v1",&HLT_HIL3Mu12_v1);
  my_hlt_tree->Branch("HLT_HIL3Mu5_NHitQ10_v1_Prescl",&HLT_HIL3Mu5_NHitQ10_v1_Prescl);
  my_hlt_tree->Branch("HLT_HIL3Mu7_v1_Prescl",&HLT_HIL3Mu7_v1_Prescl);
  my_hlt_tree->Branch("HLT_HIL3Mu12_v1_Prescl",&HLT_HIL3Mu12_v1_Prescl);

  // ----- jet variables
  Float_t jtpt, rawpt, jteta, jtphi, trackMax, genpt, geneta, genphi, jtPartonFlavor, jtHadronFlavor;
  Int_t nref;
  my_jet_tree->Branch("jtpt",&jtpt);
  my_jet_tree->Branch("rawpt",&rawpt);
  my_jet_tree->Branch("jteta",&jteta);
  my_jet_tree->Branch("jtphi",&jtphi);
  my_jet_tree->Branch("trackMax",&trackMax);
  my_jet_tree->Branch("jtPartonFlavor",&jtPartonFlavor);
  my_jet_tree->Branch("jtHadronFlavor",&jtHadronFlavor);
  my_jet_tree->Branch("genpt",&genpt);
  my_jet_tree->Branch("geneta",&geneta);
  my_jet_tree->Branch("genphi",&genphi);
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

  // ----- gen-particle variables
  Float_t pt, eta, phi;
  Int_t chg, pdg, n;
  my_gen_particle_tree->Branch("pt",&pt);
  my_gen_particle_tree->Branch("eta",&eta);
  my_gen_particle_tree->Branch("phi",&phi);
  my_gen_particle_tree->Branch("chg",&chg);
  my_gen_particle_tree->Branch("pdg",&pdg);
  my_gen_particle_evt_tree->Branch("n",&n);
  
  
  std::ifstream instr(in_file_name.c_str(), std::ifstream::in);
  if(!instr.is_open()) cout << "filelist not found!! Exiting..." << endl;
  std::string filename;
  Int_t ifile = 0;

  
  // -- tree variables
  // ----- filter variables 
  Int_t t_pPAprimaryVertexFilter[1], 
    t_HBHENoiseFilterResultRun2Loose[1];
    
  // ----- event variables
  Int_t t_hiBin[1];
  UInt_t t_run[1], t_lumi[1];
  ULong64_t t_evt[1];
  Float_t t_hiHF[1];
  Float_t t_vz[1];
  // ----- HLT variables
  Int_t t_HLT_HIL3Mu5_NHitQ10_v1[1], t_HLT_HIL3Mu7_v1[1], t_HLT_HIL3Mu12_v1[1];
  Int_t t_HLT_HIL3Mu5_NHitQ10_v1_Prescl[1], t_HLT_HIL3Mu7_v1_Prescl[1], t_HLT_HIL3Mu12_v1_Prescl[1];
  // ----- jet variables
  const int MAXJETS = 1000;
  Float_t t_jtpt[MAXJETS], t_rawpt[MAXJETS], t_jteta[MAXJETS], t_jtphi[MAXJETS], t_trackMax[MAXJETS], t_jtPartonFlavor[MAXJETS], t_jtHadronFlavor[MAXJETS], t_genpt[MAXJETS], t_geneta[MAXJETS], t_genphi[MAXJETS];
  Int_t t_nref[1];
  // ----- muon variables
  vector<Float_t> *t_muPt=0, *t_muEta=0, *t_muPhi=0;
  vector<Float_t> *t_muChi2NDF=0, *t_muInnerD0=0, *t_muInnerDz=0;
  vector<Int_t> *t_muIsPF=0, *t_muIsGlobal=0, *t_muIsTracker=0, *t_muMuonHits=0, *t_muStations=0, *t_muTrkLayers=0, *t_muPixelHits=0, *t_muCharge=0;
  Int_t t_nMu[1];
  // ----- gen-particle variables
  vector<Float_t> *t_pt=0, *t_eta=0, *t_phi=0;
  vector<Int_t> *t_chg=0, *t_pdg=0;
  Int_t t_n[1];
  

  int endfile = 1193;
  while(instr>>filename && ifile<endfile){
    
    

    //cout << "Filename is " << filename << endl;
    ifile++;

    if(ifile < startgroup || ifile > endgroup) continue;


    cout << (100.)*(1.0*ifile / (1.0*endfile)) << " %" << endl;

    TFile *my_file = TFile::Open(filename.c_str());
    
    filter_tree        = (TTree*) my_file->Get("skimanalysis/HltTree");
    evt_tree           = (TTree*) my_file->Get("hiEvtAnalyzer/HiTree");
    hlt_tree           = (TTree*) my_file->Get("hltanalysis/HltTree");
    jet_tree           = (TTree*) my_file->Get("ak4PFJetAnalyzer/t");
    jet_evt_tree       = (TTree*) my_file->Get("ak4PFJetAnalyzer/t");
    muon_tree          = (TTree*) my_file->Get("ggHiNtuplizerGED/EventTree");
    muon_evt_tree      = (TTree*) my_file->Get("ggHiNtuplizerGED/EventTree");
    gen_particle_tree  = (TTree*) my_file->Get("HiGenParticleAna/hi");
    gen_particle_evt_tree  = (TTree*) my_file->Get("HiGenParticleAna/hi");

    //cout << "trees loaded" << endl;

    // ----- filter variables
    filter_tree->SetBranchAddress("pPAprimaryVertexFilter",t_pPAprimaryVertexFilter);
    filter_tree->SetBranchAddress("HBHENoiseFilterResultRun2Loose",t_HBHENoiseFilterResultRun2Loose);
    // ----- event variables
    evt_tree->SetBranchAddress("hiBin",t_hiBin);
    evt_tree->SetBranchAddress("hiHF",t_hiHF);
    evt_tree->SetBranchAddress("run",t_run);
    evt_tree->SetBranchAddress("lumi",t_lumi);
    evt_tree->SetBranchAddress("evt",t_evt);
    evt_tree->SetBranchAddress("vz",t_vz);
    // ----- HLT variables
    hlt_tree->SetBranchAddress("HLT_HIL3Mu5_NHitQ10_v1",t_HLT_HIL3Mu5_NHitQ10_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu7_v1",t_HLT_HIL3Mu7_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu12_v1",t_HLT_HIL3Mu12_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu5_NHitQ10_v1_Prescl",t_HLT_HIL3Mu5_NHitQ10_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu7_v1_Prescl",t_HLT_HIL3Mu7_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu12_v1_Prescl",t_HLT_HIL3Mu12_v1_Prescl);
    // ----- jet variables
    jet_tree->SetBranchAddress("jtpt",t_jtpt);
    jet_tree->SetBranchAddress("rawpt",t_rawpt);
    jet_tree->SetBranchAddress("jteta",t_jteta);
    jet_tree->SetBranchAddress("jtphi",t_jtphi);
    jet_tree->SetBranchAddress("trackMax",t_trackMax);
    jet_tree->SetBranchAddress("nref",t_nref);
    jet_tree->SetBranchAddress("jtPartonFlavor",t_jtPartonFlavor);
    jet_tree->SetBranchAddress("jtHadronFlavor",t_jtHadronFlavor);
    jet_tree->SetBranchAddress("genpt",t_genpt);
    jet_tree->SetBranchAddress("geneta",t_geneta);
    jet_tree->SetBranchAddress("genphi",t_genphi);
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
    // ----- gen-particle variables
    gen_particle_tree->SetBranchAddress("pt",&t_pt);
    gen_particle_tree->SetBranchAddress("eta",&t_eta);
    gen_particle_tree->SetBranchAddress("phi",&t_phi);
    gen_particle_tree->SetBranchAddress("chg",&t_chg);
    gen_particle_tree->SetBranchAddress("pdg",&t_pdg);
    gen_particle_tree->SetBranchAddress("n",t_n);    

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
      //gen_particle_tree->GetEntry(evi);
      
      pPAprimaryVertexFilter = t_pPAprimaryVertexFilter[0];
      HBHENoiseFilterResultRun2Loose = t_HBHENoiseFilterResultRun2Loose[0];

      // --- event-filter cuts
      if(pPAprimaryVertexFilter         == 0 || 
         HBHENoiseFilterResultRun2Loose == 0
	 ) continue;
      
      hiBin = t_hiBin[0];
      hiHF = t_hiHF[0];
      run = t_run[0];
      lumi = t_lumi[0];
      evt = t_evt[0];
      vz = t_vz[0];

      // --- event cuts
      if(fabs(vz) > 15.0) continue;

      HLT_HIL3Mu5_NHitQ10_v1 = t_HLT_HIL3Mu5_NHitQ10_v1[0];
      HLT_HIL3Mu7_v1 = t_HLT_HIL3Mu7_v1[0];
      HLT_HIL3Mu12_v1 = t_HLT_HIL3Mu12_v1[0];
      HLT_HIL3Mu5_NHitQ10_v1_Prescl = t_HLT_HIL3Mu5_NHitQ10_v1_Prescl[0];
      HLT_HIL3Mu7_v1_Prescl = t_HLT_HIL3Mu7_v1_Prescl[0];
      HLT_HIL3Mu12_v1_Prescl = t_HLT_HIL3Mu12_v1_Prescl[0];
      
      // if all muon-triggers are off, dismiss event
      if(HLT_HIL3Mu5_NHitQ10_v1 == 0 &&
	 HLT_HIL3Mu7_v1 == 0 &&
	 HLT_HIL3Mu12_v1 == 0) continue;

      int nref_prime = 0; // counter variable for nref

      // start jet loop
      for(int jeti = 0; jeti < t_nref[0]; jeti++){

	jtpt = t_jtpt[jeti];
	rawpt = t_rawpt[jeti];
	jteta = t_jteta[jeti];
	jtphi = t_jtphi[jeti];
	trackMax = t_trackMax[jeti];
	jtPartonFlavor = t_jtPartonFlavor[jeti];
	jtHadronFlavor = t_jtHadronFlavor[jeti];
	genpt = t_genpt[jeti];
	geneta = t_geneta[jeti];
	genphi = t_genphi[jeti];
	
	// fill the tree
	my_jet_tree->Fill();
	nref_prime++;

      } // end jet loop

      nref = nref_prime;
      
      int nMu_prime = 0;

      // start muon loop
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


      int n_prime = 0;

      cout << "t_n = " << t_n[0] << endl;
      
      // start gen-particle loop
      for(int geni = 0; geni < t_n[0]; geni++){

	pt = t_pt->at(geni);
	eta = t_eta->at(geni);
	phi = t_phi->at(geni);
	chg = t_chg->at(geni);
	pdg = t_pdg->at(geni);

	// fill the tree
	my_gen_particle_tree->Fill();
	n_prime++;

      }

      n = n_prime;
      
      // fill event trees
      my_muon_evt_tree->Fill();
      //my_gen_particle_evt_tree->Fill();
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
  //my_gen_particle_tree->Write();
  //my_gen_particle_evt_tree->Write();
  output_file->Close();

  cout << "done" << endl;
  
}


