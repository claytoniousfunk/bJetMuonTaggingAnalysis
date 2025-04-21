#include "../../../headers/fitParameters/JESbFitParams_PYTHIA_mu12.h"
TF1 *fitFxn_PYTHIA_JESb;
#include "../../../headers/fitFunctions/fitFxn_PYTHIA_JESb.h"

void bFraction_directCount_shift(double pT_edge_low = 110., double pT_edge_high = 120.){




  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets_doNeutrinoEnergyAddition.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_muTaggedJets_doBJetNeutrinoEnergyShift.root");
  

  TH2D *H1, *H2, *H3;
  TH2D *M1, *M2, *M3;
  TH1D *mh1, *mh2, *mh3; // muon-tagged all jets
  TH1D *mb1, *mb2, *mb3; // muon-tagged b jets
  TH1D *mbb1, *mbb2, *mbb3; // muon-tagged bb jets
  TH1D *mbGS1, *mbGS2, *mbGS3; // muon-tagged bGS jets
  TH1D *h1, *h2, *h3; // inclusive all jets
  TH1D *b1, *b2, *b3; // inclusive b jets
  TH1D *bb1, *bb2, *bb3; // inclusive bb jets
  TH1D *bGS1, *bGS2, *bGS3; // inclusive bGS jets
  
  f1->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H1);
  f1->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H2);

  h1 = (TH1D*) H1->ProjectionX("h1");
  h2 = (TH1D*) H2->ProjectionX("h2");

  TH1D *r = (TH1D*) h1->Clone("r");
  r->Divide(h2,h1,1,1,"B");
  r->Draw();

  
}
