



void leadingHadronRAA(){


  double trkptCut = 0.7;
  double trketaCut = 1.;
  
  const unsigned int NMAXTRK = 10000;
  float trkpt_pp[NMAXTRK];
  float trketa_pp[NMAXTRK];
  float trkphi_pp[NMAXTRK];
  int ntrk_pp;
  float vz_pp;

  float trkpt_PbPb[NMAXTRK];
  float trketa_PbPb[NMAXTRK];
  float trkphi_PbPb[NMAXTRK];
  int ntrk_PbPb;
  float vz_PbPb;
  Int_t hiBin;

  float trkPtMin = 0.;
  float trkPtMax = 50.;
  int NTrkPtBins = 500;

  float vzMin = -15.;
  float vzMax = 15.;
  int NVzBins = 30;

  TH1D *h_trkpt_pp = new TH1D("h_trkpt_pp","trkpt_pp",NTrkPtBins,trkPtMin,trkPtMax);
  TH1D *h_vz_pp = new TH1D("h_vz_pp","vz_pp",NVzBins,vzMin,vzMax);
  
  TH1D *h_trkpt_PbPb_C4 = new TH1D("h_trkpt_PbPb_C4","trkpt_PbPb_C4",NTrkPtBins,trkPtMin,trkPtMax);
  TH1D *h_vz_PbPb_C4 = new TH1D("h_vz_PbPb_C4","vz_PbPb_C4",NVzBins,vzMin,vzMax);

  TH1D *h_trkpt_PbPb_C3 = new TH1D("h_trkpt_PbPb_C3","trkpt_PbPb_C3",NTrkPtBins,trkPtMin,trkPtMax);
  TH1D *h_vz_PbPb_C3 = new TH1D("h_vz_PbPb_C3","vz_PbPb_C3",NVzBins,vzMin,vzMax);

  TH1D *h_trkpt_PbPb_C2 = new TH1D("h_trkpt_PbPb_C2","trkpt_PbPb_C2",NTrkPtBins,trkPtMin,trkPtMax);
  TH1D *h_vz_PbPb_C2 = new TH1D("h_vz_PbPb_C2","vz_PbPb_C2",NVzBins,vzMin,vzMax);

  TH1D *h_trkpt_PbPb_C1 = new TH1D("h_trkpt_PbPb_C1","trkpt_PbPb_C1",NTrkPtBins,trkPtMin,trkPtMax);
  TH1D *h_vz_PbPb_C1 = new TH1D("h_vz_PbPb_C1","vz_PbPb_C1",NVzBins,vzMin,vzMax);

  TFile *file_pp = TFile::Open("/home/clayton/Analysis/phase-change/leading-hadron-to-jet-dR/rootFiles/input/pp/pp_merge.root");
  TFile *file_PbPb = TFile::Open("/home/clayton/Analysis/phase-change/leading-hadron-to-jet-dR/rootFiles/input/PbPb/HiForestAOD_PbPb_E1CEAF92BB64.root");

  TTree *tree_pp_trk = 0;
  TTree *tree_pp_evt = 0;
  TTree *tree_pp_flt = 0;
  
  TTree *tree_PbPb_trk = 0;
  TTree *tree_PbPb_evt = 0;
  TTree *tree_PbPb_flt = 0;

  // configure pp track tree
  tree_pp_trk = (TTree*) file_pp->Get("ppTrack/trackTree");
  tree_pp_trk->SetBranchStatus("*",0);     // disable all branches
  tree_pp_trk->SetBranchStatus("trkPt",1);   // enable event information
  tree_pp_trk->SetBranchStatus("trkEta",1);
  tree_pp_trk->SetBranchStatus("trkPhi",1);
  tree_pp_trk->SetBranchStatus("nTrk",1);
  // configure pp event tree
  tree_pp_evt = (TTree*) file_pp->Get("hiEvtAnalyzer/HiTree");
  tree_pp_evt->SetBranchStatus("*",0);
  tree_pp_evt->SetBranchStatus("vz",1);
  // configure pp event-filter tree
  tree_pp_flt = (TTree*) file_pp->Get("skimanalysis/HltTree");
  tree_pp_flt->SetBranchStatus("*",0);
  tree_pp_flt->SetBranchStatus("pprimaryVertexFilter",1);

  // configure PbPb track tree
  tree_PbPb_trk = (TTree*) file_PbPb->Get("ppTrack/trackTree");
  tree_PbPb_trk->SetBranchStatus("*",0);     // disable all branches
  tree_PbPb_trk->SetBranchStatus("trkPt",1);   // enable event information
  tree_PbPb_trk->SetBranchStatus("trkEta",1);
  tree_PbPb_trk->SetBranchStatus("trkPhi",1);
  tree_PbPb_trk->SetBranchStatus("nTrk",1);
  // configure PbPb event tree
  tree_PbPb_evt = (TTree*) file_PbPb->Get("hiEvtAnalyzer/HiTree");
  tree_PbPb_evt->SetBranchStatus("*",0);
  tree_PbPb_evt->SetBranchStatus("vz",1);
  tree_PbPb_evt->SetBranchStatus("hiBin",1);
  // configure PbPb event-filter tree
  tree_PbPb_flt = (TTree*) file_PbPb->Get("skimanalysis/HltTree");
  tree_PbPb_flt->SetBranchStatus("*",0);

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  
  tree_pp_trk->SetBranchAddress("trkPt",&trkpt_pp);
  tree_pp_trk->SetBranchAddress("trkEta",&trketa_pp);
  tree_pp_trk->SetBranchAddress("trkPhi",&trkphi_pp);
  tree_pp_trk->SetBranchAddress("nTrk",&ntrk_pp);
  tree_pp_evt->SetBranchAddress("vz",&vz_pp);

  tree_PbPb_trk->SetBranchAddress("trkPt",&trkpt_PbPb);
  tree_PbPb_trk->SetBranchAddress("trkEta",&trketa_PbPb);
  tree_PbPb_trk->SetBranchAddress("trkPhi",&trkphi_PbPb);
  tree_PbPb_trk->SetBranchAddress("nTrk",&ntrk_PbPb);
  tree_PbPb_evt->SetBranchAddress("vz",&vz_PbPb);
  tree_PbPb_evt->SetBranchAddress("hiBin",&hiBin);

  ///////////////////////////////////////////////////////////////////////////////////////////
  

  for (Long64_t entry_j = 0; entry_j < tree_pp_evt->GetEntries(); entry_j++){

    tree_pp_trk->GetEntry(entry_j);
    tree_pp_evt->GetEntry(entry_j);

    if(vz_pp > 15.) continue;

    h_vz_pp->Fill(vz_pp);

    for(int k = 0; k < ntrk_pp; k++){

      if(trkpt_pp[k] < trkptCut || fabs(trketa_pp[k]) > trketaCut) continue;

      h_trkpt_pp->Fill(trkpt_pp[k]);
      // h_trketa_pp->Fill(trketa_pp[k]);
      // h_trkphi_pp->Fill(trkphi_pp[k]);
      
    }

  }

  auto wf_pp = TFile::Open("../../rootFiles/leadingHadronRAA/trkHistograms_pp.root","recreate");
  h_trkpt_pp->Write();
  h_vz_pp->Write();
  // h_trketa_pp->Write();
  // h_trkphi_pp->Write();
  wf_pp->Close();


  ///////////////////////////////////////////////////////////////////////////////////////////////


  for (Long64_t entry_j = 0; entry_j < tree_PbPb_evt->GetEntries(); entry_j++){

    if(entry_j == 590) continue; // broken event for some reason, idk

    //cout << "entry_j = " << entry_j << "\n";

    tree_PbPb_trk->GetEntry(entry_j);
    tree_PbPb_evt->GetEntry(entry_j);

    //cout << "hiBin = " << hiBin << "\n";

    if(vz_PbPb > 15.) continue;
    if(hiBin > 180 || hiBin < 0) continue;

    if(hiBin >= 0 && hiBin < 20){
      h_vz_PbPb_C1->Fill(vz_PbPb);
    }
    else if(hiBin >= 20 && hiBin < 60){
      h_vz_PbPb_C2->Fill(vz_PbPb);
    }
    else if(hiBin >= 60 && hiBin < 100){
      h_vz_PbPb_C3->Fill(vz_PbPb);
    }
    else if(hiBin >= 100 && hiBin < 180){
      h_vz_PbPb_C4->Fill(vz_PbPb);
    }
    else{continue;}

    for(int k = 0; k < ntrk_PbPb; k++){

      if(trkpt_PbPb[k] < trkptCut || fabs(trketa_PbPb[k]) > trketaCut) continue;


      if(hiBin >= 0 && hiBin < 20){
	h_trkpt_PbPb_C1->Fill(trkpt_PbPb[k]);
      }
      else if(hiBin >= 20 && hiBin < 60){
	h_trkpt_PbPb_C2->Fill(trkpt_PbPb[k]);
      }
      else if(hiBin >= 60 && hiBin < 100){
	h_trkpt_PbPb_C3->Fill(trkpt_PbPb[k]);
      }
      else if(hiBin >= 100 && hiBin < 180){
	h_trkpt_PbPb_C4->Fill(trkpt_PbPb[k]);
      }
      else{continue;}
      // h_trketa_PbPb->Fill(trketa_PbPb[k]);
      // h_trkphi_PbPb->Fill(trkphi_PbPb[k]);
      
    }

  }

  auto wf_PbPb = TFile::Open("../../rootFiles/leadingHadronRAA/trkHistograms_PbPb.root","recreate");
  h_trkpt_PbPb_C4->Write();
  h_trkpt_PbPb_C3->Write();
  h_trkpt_PbPb_C2->Write();
  h_trkpt_PbPb_C1->Write();
  h_vz_PbPb_C4->Write();
  h_vz_PbPb_C3->Write();
  h_vz_PbPb_C2->Write();
  h_vz_PbPb_C1->Write();
  // h_trketa_PbPb->Write();
  // h_trkphi_PbPb->Write();
  wf_PbPb->Close();

  

}
