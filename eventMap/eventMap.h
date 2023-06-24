
#ifndef EVENTMAP_AA2018_H
#define EVENTMAP_AA2018_H


//corresponding to 2017-2018 hiForest setup

#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <iostream>

// the flavor for B is determined by the matchedHadron flavor instead of the older version of refparton_flavorForB, switch to older version by turn AASetup = 0;
//

class eventMap  {
public :
  eventMap(){};
  eventMap(TFile*f){_file=f;};
  ~eventMap(){
    std::cout<<"deleting the eventMap"<<std::endl;
    evtTree=nullptr;
    //evtTree->ResetBranchAddresses();
    std::cout<<"eventMap: deleted."<<std::endl;
  };
  void init();
  void loadFile( TFile *f){_file = f;};
  void loadJet(const char* name);
  void loadMuon(const char* name);
  void loadMuonAnalyzer(const char* name);
  void loadMuonTrigger(const char* name);
  void loadBTagger();
  void loadBTaggerInputVariables();
  void getEvent(Long64_t j){evtTree->GetEntry(j);};
  void loadTrack();
  void loadGenParticle();
  void unloadGP();
  void regEventFilter(int nfilter, std::string *filtername);
  void regEventFilter(std::vector<std::string> &filtername);
  bool checkEventFilter(){
    //mScrapingFilterreturn 1 for event needs to be skipped
    for(auto & it : filters) if(!it) return 1;
    return 0;
  }
  int nGP(){return gpptp->size();};
  int nJet(){return njet;};
  int nGenJet(){return ngj;};
  int nTrk(){return ntrk;};
  float gppt(int j) {return gpptp->at(j);}
  float gpeta(int j) {return gpetap->at(j);}
  float gpphi(int j) {return gpphip->at(j);}
  int gpchg(int j) {return gpchgp->at(j);}
  int gppdgID(int j) {return gppdgIDp->at(j);}
  int gpIsStable(int j) {return gpStableTag->at(j);}
  int gpSube(int j){ return gpsube->at(j);}
  TTree *hltTree, *filterTree, *trkTree, *gpTree, *jetTree=nullptr, *muonTree=nullptr, *muonTriggerTree=nullptr, *muonAnalyzerTree=nullptr;
  TTree *evtTree;
  TFile *_file = 0;
  std::vector<Int_t> filters;

  // detect if is MC by checking the if Gen particle exists.
  bool isMC = 0;
  // pp or PbPb setup
  bool AASetup = 1;
  //trk part
  static const int trkMax = 99999;
  int ntrk=0;
  Float_t trkpt[trkMax],trkpterr[trkMax],trketa[trkMax],trkphi[trkMax],trkchi2[trkMax];
  UChar_t trknlayer[trkMax], trknhit[trkMax], trkndof[trkMax];
  Bool_t highPurity[trkMax];
  Float_t pfEcal[trkMax], pfHcal[trkMax];

  //evt info
  Float_t weight = 0, vz = 0, pthat = 0;
  Int_t hiBin = 0;
  ULong64_t evtNumber = 0;
  UInt_t runNumber = 0, lumiSection = 0;

  //gen particle
  int ngp = 0;
  bool stableOnly = 1;
  std::vector<float> *gpptp=0, *gpetap=0, *gpphip=0;
  std::vector<int>  *gppdgIDp=0, *gpchgp=0, *gpsube=0, *gpStableTag=0;

  //jet set
  static const int jetMax = 9999;
  int njet=0, ngj = 0;
  Float_t jetpt[jetMax],jeteta[jetMax],jetphi[jetMax],jet_wta_eta[jetMax],jet_wta_phi[jetMax], ref_jetpt[jetMax], rawpt[jetMax];
  Float_t mupt[jetMax], mueta[jetMax], muphi[jetMax], muptrel[jetMax];
  Int_t jetTrkMax[jetMax];
  Float_t genjetpt[jetMax],genjeteta[jetMax],genjetphi[jetMax],genjet_wta_eta[jetMax],genjet_wta_phi[jetMax];
  Float_t partonFlavor[jetMax], hadronFlavor[jetMax];
  Int_t matchedPartonFlavor[jetMax], matchedHadronFlavor[jetMax];
  Int_t refparton_flavorForB[jetMax];
  Int_t refparton_flavor[jetMax];
  Int_t bHadronNumber[jetMax];
  Int_t genMatchIndex[jetMax]; 
  Float_t disc_csvV2[jetMax];
  Int_t GSP_evt[jetMax];
  Int_t muN[jetMax];

  // muon info
  static const int muonMax = 9999;
  int nMu=0;
  int nInner = 0;
  vector <float> *muPt=0, *muEta=0, *muPhi=0, *muChi2NDF=0, *muInnerD0=0, *muInnerDz=0;
  vector <int> *muIsPF=0, *muIsGlobal=0, *muIsTracker=0, *muMuonHits=0, *muStations=0, *muTrkLayers=0, *muPixelHits=0, *muCharge=0;
  vector <int> *innerNTrkHits=0;

  // muon trigger info
  int HLT_HIL3Mu5_v1, HLT_HIL3Mu7_v1, HLT_HIL3Mu5_v1_Prescl;
  int HLT_HIL3Mu5_NHitQ10_v1, HLT_HIL3Mu7_NHitQ10_v1, HLT_HIL3Mu3_NHitQ10_v1;
  int HLT_HIL3Mu5_NHitQ10_v1_Prescl, HLT_HIL3Mu7_NHitQ10_v1_Prescl, HLT_HIL3Mu3_NHitQ10_v1_Prescl;
  int HLT_HIL3Mu5_NHitQ10_tagging_v1, HLT_HIL3Mu7_NHitQ10_tagging_v1, HLT_HIL3Mu3_NHitQ10_tagging_v1;
  int HLT_HIL3Mu5_NHitQ10_tagging_v1_Prescl, HLT_HIL3Mu7_NHitQ10_tagging_v1_Prescl, HLT_HIL3Mu3_NHitQ10_tagging_v1_Prescl;
  int HLT_HIL3Mu12_v1, HLT_HIL3Mu12_v1_Prescl; 
  // mu+jet trigger
  int HLT_HIL3Mu5_AK4PFJet30_v1, HLT_HIL3Mu5_AK4PFJet40_v1, HLT_HIL3Mu5_AK4PFJet60_v1;


 
  // jet trigger info
  int HLT_HIAK4PFJet15_v1, HLT_HIAK4PFJet30_v1, HLT_HIAK4PFJet40_v1, HLT_HIAK4PFJet60_v1, HLT_HIAK4PFJet80_v1, HLT_HIAK4PFJet100_v1, HLT_HIAK4PFJet120_v1;
  int HLT_HIAK4CaloJet80_v1;
  int HLT_HIPuAK4CaloJet40Eta5p1_v1, HLT_HIPuAK4CaloJet60Eta5p1_v1, HLT_HIPuAK4CaloJet80Eta5p1_v1, HLT_HIPuAK4CaloJet100Eta5p1_v1;
  int HLT_HIPuAK4CaloJet40Eta5p1_v1_Prescl, HLT_HIPuAK4CaloJet60Eta5p1_v1_Prescl, HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl, HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl;
  int HLT_HIAK4PFJet40_v1_Prescl;
  int HLT_HIAK4PFJet60_v1_Prescl, HLT_HIAK4PFJet80_v1_Prescl, HLT_HIAK4PFJet100_v1_Prescl;
  int HLT_HICsAK4PFJet100Eta1p5_v1;
  int HLT_HICsAK4PFJet100Eta1p5_v1_Prescl;



  // jet for CSV inputs
  Float_t pdisc_csvV2[jetMax];
  Float_t ndisc_csvV2[jetMax];
  Int_t nsvtx[jetMax];
  static const int csv_sv_max = 30000;
  Int_t svtxntrk[csv_sv_max];
  Float_t svtxdl[csv_sv_max];
  Float_t svtxdls[csv_sv_max];
  Float_t svtxm[csv_sv_max];

  //CSV input variables;
  Float_t csv_trkMul[jetMax];
  Float_t csv_trkIndexStart[jetMax], csv_trkIndexEnd[jetMax];
  static const int csv_trk_max = 100000;
  Float_t csv_trk3dIPSig[csv_trk_max], csv_trk3dIP[csv_trk_max], csv_trkDist[csv_trk_max];
  Float_t  csv_trkPtRel[csv_trk_max], csv_trkMomentum[csv_trk_max],csv_trkDr[csv_trk_max];
};


void eventMap::init(){
  evtTree = (TTree*) _file->Get("hiEvtAnalyzer/HiTree");
  evtTree->SetBranchAddress("vz", &vz);
  evtTree->SetBranchAddress("hiBin", &hiBin);
  evtTree->SetBranchAddress("evt", &evtNumber);
  evtTree->SetBranchAddress("run", &runNumber);
  evtTree->SetBranchAddress("lumi", &lumiSection);
  if(isMC){
    evtTree->SetBranchAddress("pthat", &pthat);
    evtTree->SetBranchAddress("weight", &weight);
  }
}

void eventMap::regEventFilter(int nfilter, std::string *filtername){
  filterTree = (TTree*) _file->Get("skimanalysis/HltTree");
  evtTree->AddFriend(filterTree);
  filters.clear();
  filters.resize(nfilter);
  for(int i=0;i<nfilter; ++i){
    if(filterTree->GetLeaf(filtername[i].c_str())){
      evtTree->SetBranchAddress(filtername[i].c_str(), &(filters[i]));
    }else{
      std::cout<<"Error: No such filter name exits: "<<filtername[i]<<std::endl;
      return;
    }
  }
}

void eventMap::regEventFilter(std::vector<std::string> &filtername){
  filterTree = (TTree*) _file->Get("skimanalysis/HltTree");
  evtTree->AddFriend(filterTree);
  filters.clear();
  filters.resize(filtername.size());
  int n = filtername.size();
  for(int i=0;i<n; ++i){
    if(filterTree->GetLeaf(filtername[i].c_str())){
      evtTree->SetBranchAddress(filtername[i].c_str(), &(filters[i]));
    }else{
      std::cout<<"Error: No such filter name exits: "<<filtername[i]<<std::endl;
      return;
    }
  }
}

void eventMap::loadTrack(){
  trkTree = (TTree*) _file->Get("ppTrack/trackTree");
  //trkTree = new Tree("ppTrack", "");
  evtTree->AddFriend(trkTree);
  evtTree->SetBranchAddress("nTrk", &ntrk);
  evtTree->SetBranchAddress("trkPt", 	&trkpt);
  evtTree->SetBranchAddress("trkEta",	&trketa);
  evtTree->SetBranchAddress("trkPhi",	&trkphi);
  evtTree->SetBranchAddress("trkPtError", &trkpterr);
  evtTree->SetBranchAddress("trkChi2", 	&trkchi2);
  evtTree->SetBranchAddress("trkNlayer", 	&trknlayer);
  evtTree->SetBranchAddress("trkNHit", 	&trknhit);
  evtTree->SetBranchAddress("trkNdof", 	&trkndof);
  evtTree->SetBranchAddress("highPurity", &highPurity);
  evtTree->SetBranchAddress("pfEcal", 	&pfEcal);
  evtTree->SetBranchAddress("pfHcal", 	&pfHcal);
}

void eventMap::loadGenParticle(){
  gpTree = (TTree*) _file->Get("HiGenParticleAna/hi"); // for my forests
  //gpTree = (TTree*) _file->Get("leptonAna/hi"); // for muJetForest (Matt's) gen particle info
  evtTree->AddFriend(gpTree);
  evtTree->SetBranchAddress("pt",  &gpptp);
  evtTree->SetBranchAddress("eta", &gpetap);
  evtTree->SetBranchAddress("phi", &gpphip);
  evtTree->SetBranchAddress("chg", &gpchgp);
  evtTree->SetBranchAddress("pdg", &gppdgIDp);
  if(!AASetup) evtTree->SetBranchAddress("sube",&gpsube);
  if(!stableOnly) evtTree->SetBranchAddress("sta",&gpStableTag);
}

void eventMap::unloadGP(){
  evtTree->ResetBranchAddresses();
}

void eventMap::loadJet(const char* name){
  jetTree = (TTree*) _file->Get(Form("%s/t", name));
  evtTree->AddFriend(jetTree);
  evtTree->SetBranchAddress("nref", &njet);
  evtTree->SetBranchAddress("rawpt",&rawpt);
  evtTree->SetBranchAddress("jtpt", &jetpt);
  evtTree->SetBranchAddress("jteta", &jeteta);
  evtTree->SetBranchAddress("jtphi", &jetphi);
  //evtTree->SetBranchAddress("WTAeta", &jet_wta_eta);
  //evtTree->SetBranchAddress("WTAphi", &jet_wta_phi);
  evtTree->SetBranchAddress("discr_csvV2", &disc_csvV2);
  evtTree->SetBranchAddress("trackMax", &jetTrkMax);
  if(isMC){
    evtTree->SetBranchAddress("genmatchindex", &genMatchIndex);// for reco jets
    //if(AASetup) evtTree->SetBranchAddress("matchedHadronFlavor", &flavor_forb);// for reco jets
    //else evtTree->SetBranchAddress("refparton_flavorForB", &flavor_forb);// for reco jets
    evtTree->SetBranchAddress("ngen", &ngj);
    evtTree->SetBranchAddress("refpt", &ref_jetpt);
    evtTree->SetBranchAddress("genpt", &genjetpt);
    evtTree->SetBranchAddress("geneta", &genjeteta);
    evtTree->SetBranchAddress("genphi", &genjetphi);
    evtTree->SetBranchAddress("matchedPartonFlavor",matchedPartonFlavor);
    evtTree->SetBranchAddress("matchedHadronFlavor",matchedHadronFlavor);
    evtTree->SetBranchAddress("jtPartonFlavor",&partonFlavor);
    evtTree->SetBranchAddress("jtHadronFlavor",&hadronFlavor);
    evtTree->SetBranchAddress("refparton_flavorForB",&refparton_flavorForB);
    evtTree->SetBranchAddress("refparton_flavor",&refparton_flavor);
    //evtTree->SetBranchAddress("bHadronNumber",&bHadronNumber);
    //evtTree->SetBranchAddress("WTAgeneta", &genjet_wta_eta);
    //evtTree->SetBranchAddress("WTAgenphi", &genjet_wta_phi);
    //evtTree->SetBranchAddress("GSP_evt",&GSP_evt);


  }
  evtTree->SetBranchAddress("muN",&muN);
  evtTree->SetBranchAddress("mupt",&mupt);
  evtTree->SetBranchAddress("mueta",&mueta);
  evtTree->SetBranchAddress("muphi",&muphi);
  evtTree->SetBranchAddress("muptrel",&muptrel);
}

void eventMap::loadMuon(const char* name){
  muonTree = (TTree*) _file->Get(Form("%s/EventTree",name));
  evtTree->AddFriend(muonTree);
  evtTree->SetBranchAddress("muPt",&muPt);
  evtTree->SetBranchAddress("muEta",&muEta);
  evtTree->SetBranchAddress("muPhi",&muPhi);
  evtTree->SetBranchAddress("muChi2NDF",&muChi2NDF);
  evtTree->SetBranchAddress("muInnerD0",&muInnerD0);
  evtTree->SetBranchAddress("muInnerDz",&muInnerDz);
  evtTree->SetBranchAddress("nMu",&nMu);
  evtTree->SetBranchAddress("muIsGlobal",&muIsGlobal);
  evtTree->SetBranchAddress("muIsTracker",&muIsTracker);
  evtTree->SetBranchAddress("muIsPF",&muIsPF);
  evtTree->SetBranchAddress("muMuonHits",&muMuonHits);
  evtTree->SetBranchAddress("muStations",&muStations);
  evtTree->SetBranchAddress("muTrkLayers",&muTrkLayers);
  evtTree->SetBranchAddress("muPixelHits",&muPixelHits);
  evtTree->SetBranchAddress("muCharge",&muCharge);

}

void eventMap::loadMuonAnalyzer(const char* name){

  muonAnalyzerTree = (TTree*) _file->Get(Form("%s/MuonTree",name));
  evtTree->AddFriend(muonAnalyzerTree);
  evtTree->SetBranchAddress("innerNTrkHits",&innerNTrkHits);
  evtTree->SetBranchAddress("nInner",&nInner);

}

void eventMap::loadMuonTrigger(const char* name){
  muonTriggerTree = (TTree*) _file->Get(Form("%s/HltTree",name));
  evtTree->AddFriend(muonTriggerTree);
  evtTree->SetBranchAddress("HLT_HIL3Mu5_v1",&HLT_HIL3Mu5_v1);
  evtTree->SetBranchAddress("HLT_HIL3Mu5_v1_Prescl",&HLT_HIL3Mu5_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIL3Mu3_NHitQ10_v1",&HLT_HIL3Mu3_NHitQ10_v1);
  evtTree->SetBranchAddress("HLT_HIL3Mu5_NHitQ10_v1",&HLT_HIL3Mu5_NHitQ10_v1);
  evtTree->SetBranchAddress("HLT_HIL3Mu3_NHitQ10_tagging_v1",&HLT_HIL3Mu3_NHitQ10_tagging_v1);
  evtTree->SetBranchAddress("HLT_HIL3Mu5_NHitQ10_tagging_v1",&HLT_HIL3Mu5_NHitQ10_tagging_v1);
  evtTree->SetBranchAddress("HLT_HIL3Mu7_NHitQ10_v1",&HLT_HIL3Mu7_NHitQ10_v1);
  evtTree->SetBranchAddress("HLT_HIL3Mu3_NHitQ10_v1_Prescl",&HLT_HIL3Mu3_NHitQ10_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIL3Mu5_NHitQ10_v1_Prescl",&HLT_HIL3Mu5_NHitQ10_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIL3Mu3_NHitQ10_tagging_v1_Prescl",&HLT_HIL3Mu3_NHitQ10_tagging_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIL3Mu5_NHitQ10_tagging_v1_Prescl",&HLT_HIL3Mu5_NHitQ10_tagging_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIL3Mu7_NHitQ10_v1_Prescl",&HLT_HIL3Mu7_NHitQ10_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIL3Mu7_v1",&HLT_HIL3Mu7_v1);
  evtTree->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet30_v1",&HLT_HIL3Mu5_AK4PFJet30_v1);
  evtTree->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet40_v1",&HLT_HIL3Mu5_AK4PFJet40_v1);
  evtTree->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet60_v1",&HLT_HIL3Mu5_AK4PFJet60_v1);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet15_v1",&HLT_HIAK4PFJet15_v1);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet30_v1",&HLT_HIAK4PFJet30_v1);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet40_v1",&HLT_HIAK4PFJet40_v1);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet40_v1_Prescl",&HLT_HIAK4PFJet40_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet60_v1",&HLT_HIAK4PFJet60_v1);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet60_v1_Prescl",&HLT_HIAK4PFJet60_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet80_v1",&HLT_HIAK4PFJet80_v1);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet80_v1_Prescl",&HLT_HIAK4PFJet80_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet100_v1",&HLT_HIAK4PFJet100_v1);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet100_v1_Prescl",&HLT_HIAK4PFJet100_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIAK4PFJet120_v1",&HLT_HIAK4PFJet120_v1);
  evtTree->SetBranchAddress("HLT_HIAK4CaloJet80_v1",&HLT_HIAK4CaloJet80_v1);
  evtTree->SetBranchAddress("HLT_HICsAK4PFJet100Eta1p5_v1",&HLT_HICsAK4PFJet100Eta1p5_v1);
  evtTree->SetBranchAddress("HLT_HICsAK4PFJet100Eta1p5_v1_Prescl",&HLT_HICsAK4PFJet100Eta1p5_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIL3Mu12_v1",&HLT_HIL3Mu12_v1);
  evtTree->SetBranchAddress("HLT_HIL3Mu12_v1_Prescl",&HLT_HIL3Mu12_v1_Prescl);
	
  evtTree->SetBranchAddress("HLT_HIPuAK4CaloJet40Eta5p1_v1",&HLT_HIPuAK4CaloJet40Eta5p1_v1);
  evtTree->SetBranchAddress("HLT_HIPuAK4CaloJet40Eta5p1_v1_Prescl",&HLT_HIPuAK4CaloJet40Eta5p1_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIPuAK4CaloJet60Eta5p1_v1",&HLT_HIPuAK4CaloJet60Eta5p1_v1);
  evtTree->SetBranchAddress("HLT_HIPuAK4CaloJet60Eta5p1_v1_Prescl",&HLT_HIPuAK4CaloJet60Eta5p1_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIPuAK4CaloJet80Eta5p1_v1",&HLT_HIPuAK4CaloJet80Eta5p1_v1);
  evtTree->SetBranchAddress("HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl",&HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl);
  evtTree->SetBranchAddress("HLT_HIPuAK4CaloJet100Eta5p1_v1",&HLT_HIPuAK4CaloJet100Eta5p1_v1);
  evtTree->SetBranchAddress("HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl",&HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl);

}

void eventMap::loadBTagger(){
  if(jetTree ==nullptr) {
    std::cout<<"Please load the jets by calling loadJet(jetset_name) before load the btagger for that certain jet set."<<std::endl;
    return;
  }
  evtTree->SetBranchAddress("pdiscr_csvV2", &pdisc_csvV2);
  evtTree->SetBranchAddress("ndiscr_csvV2", &ndisc_csvV2);
  evtTree->SetBranchAddress("nsvtx", &nsvtx);
  evtTree->SetBranchAddress("svtxntrk", &svtxntrk);
  evtTree->SetBranchAddress("svtxdl", &svtxdl);
  evtTree->SetBranchAddress("svtxdls", &svtxdls);
  evtTree->SetBranchAddress("svtxm", &svtxm);
}

void eventMap::loadBTaggerInputVariables(){
  //	evtTree->SetBranchAddress("TagVarCSV_jetNSecondaryVertices", &csv_jetNSV);
  evtTree->SetBranchAddress("Jet_nFirstTrkTagVarCSV", &csv_trkIndexStart);
  evtTree->SetBranchAddress("Jet_nLastTrkTagVarCSV", &csv_trkIndexEnd);
  evtTree->SetBranchAddress("TagVarCSV_jetNTracks", &csv_trkMul);
  evtTree->SetBranchAddress("TagVarCSV_trackSip3dVal", &csv_trk3dIP);
  evtTree->SetBranchAddress("TagVarCSV_trackSip3dSig", &csv_trk3dIPSig);
  evtTree->SetBranchAddress("TagVarCSV_trackJetDistVal", &csv_trkDist);
  evtTree->SetBranchAddress("TagVarCSV_trackPtRel", &csv_trkPtRel);
  evtTree->SetBranchAddress("TagVarCSV_trackMomentum", &csv_trkMomentum);
  evtTree->SetBranchAddress("TagVarCSV_trackDeltaR", &csv_trkDr);
}

#endif
