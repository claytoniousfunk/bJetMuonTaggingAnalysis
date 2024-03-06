

double fitFxn(double *x, double *par){
  double pt = x[0];
  //double fitval = par[0]*TMath::Exp(-0.5*TMath::Power(((x[0] - par[1])/par[2]),2));
  //double fitval = par[0] + par[1] / pt + par[2] / (pt * pt) + par[3] / (pt * pt * pt) + par[4] / (pt * pt * pt * pt) ; 
  double fitval = par[0] * exp (par[1] * pt) + par[2] * exp (par[3] * pt); 
  return fitval;
}

void plotMe(){

  TFile *f = TFile::Open("PYTHIAHYDJET_DiJet_scan.root");
  //TFile *f = TFile::Open("PYTHIAHYDJET_DiJet_scan_pthat40.root");

  TH1D *h1, *h2, *r;

  f->GetObject("h_leadingGenJetPt_C0",h1);
  f->GetObject("h_leadingGenJetPt_xJets_greaterThanPthat_C0",h2);
    
  r = (TH1D*) h2->Clone("r");
  r->Divide(h2,h1,1,1,"B");

  r->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
  r->GetYaxis()->SetTitle("Fraction");

  r->GetYaxis()->SetRangeUser(0,0.8);

  r->SetTitle("Fraction of events with a leading xJet w/ p_{T} > #hat{p}_{T}");
  r->SetStats(0);
  
  
  r->Draw();


  TF1 *func = new TF1("func",fitFxn,20.,200.,4);

  
  //r->Fit(func,"M R","",20.,200.);

  auto wf = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/xDumpReweight/xDumpReweight.root","recreate");
  
  r->Write();

  wf->Close();

}
