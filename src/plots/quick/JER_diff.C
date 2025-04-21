

TFile *f1, *f2;
TH1D *h1, *h2, *r;

void JER_diff(){

  f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_incl.root");
  f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_muTagged.root");

  f1->GetObject("JER_result_i",h1);
  f2->GetObject("JER_result_b",h2);

  r = (TH1D*) h1->Clone("h1");
  r->Divide(h2,h1,1,1,"");
  r->Draw();
  r->Fit("pol0");

  

}
