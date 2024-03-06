void projectMe(){

  TFile *f1 = TFile::Open("PYTHIAHYDJET_DiJet_scan.root");

  TH2D *H;

  f1->GetObject("h_genJetPt_pthat_C0",H);

  TH1D *h = (TH1D*) H->ProjectionX();

  h->Draw();


}
