


void JES_ratio(){

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_incl_pp.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_muTagged_pp.root");

  TH1D *j1, *j2;

  f1->GetObject("JES_result_i",j1);
  f2->GetObject("JES_result_i",j2);

  TH1D *r = (TH1D*) j1->Clone("r");
  r->Divide(j2,j1,1,1,"");
  r->Draw();
  r->Fit("pol1");

}
