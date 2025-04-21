
TFile *f1, *f2;
TH1D *h1, *h2, *h3, *h4;
TH1D *r1, *r2, *r3;
TH1D *v1, *v2, *v3, *v4;

void normalize_by_highPt(TH1D *h, double pt_norm){
  
  h->Scale(1./h->Integral(h->GetXaxis()->FindBin(pt_norm),h->GetXaxis()->FindBin(1000.)));
  //return h;
  
}

void normalize_by_events(TH1D *h, TH1D *v){

  double N = v->Integral();
  h->Scale(1./N);
  
}

void take_ratio(TH1D *r, TH1D *h, TH1D *g){
  // h = central histogram
  // g = periph. histogram
  r->Divide(h,g,1,1,"");
  
}






void inclusive_spectra(){

  f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/official/PbPb_MinBias_scan_mu12_tight_pTmu-14_evtFilterFix_hiHFcut.root");

  f1->GetObject("h_inclRecoJetPt_C1",h1);
  f1->GetObject("h_inclRecoJetPt_C2",h2);
  f1->GetObject("h_inclRecoJetPt_C3",h3);
  f1->GetObject("h_inclRecoJetPt_C4",h4);

  f1->GetObject("h_vz_C1",v1);
  f1->GetObject("h_vz_C2",v2);
  f1->GetObject("h_vz_C3",v3);
  f1->GetObject("h_vz_C4",v4);

  h1->SetLineColor(kMagenta);
  h2->SetLineColor(kGreen+2);
  h3->SetLineColor(kBlue-4);
  h4->SetLineColor(kRed-4);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);

  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");
  h4->SetTitle("");

  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  h4->SetStats(0);
  

  // normalize by high pT point (shape measurement)
  normalize_by_highPt(h1, 200.);
  normalize_by_highPt(h2, 200.);
  normalize_by_highPt(h3, 200.);
  normalize_by_highPt(h4, 200.);

  // normalize by events
  // normalize_by_events(h1, v1);
  // normalize_by_events(h2, v2);
  // normalize_by_events(h3, v3);
  // normalize_by_events(h4, v4);
  

  // save spectra
  TFile *spectra_file = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/jetSpectra/jetSpectra_PbPb_MB.root","recreate");
  h1->Write("h_inclRecoJetPt_C1");
  h2->Write("h_inclRecoJetPt_C2");
  h3->Write("h_inclRecoJetPt_C3");
  h4->Write("h_inclRecoJetPt_C4");
  spectra_file->Close();

  
  // define as copy
  r1 = (TH1D*) h1->Clone("r1");
  r2 = (TH1D*) h2->Clone("r2");
  r3 = (TH1D*) h3->Clone("r3");
  
  // define ratio
  take_ratio(r1,h1,h4);
  take_ratio(r2,h2,h4);
  take_ratio(r3,h3,h4);
  

  TCanvas *canv = new TCanvas("canv","",700,700);
  canv->cd();
  TPad *p1 = new TPad("p1","p1",0,0.4,1,1);
  TPad *p2 = new TPad("p2","p2",0,0.,1,0.4);
  p1->SetLeftMargin(0.18);
  p2->SetLeftMargin(0.18);
  p1->SetBottomMargin(0.0);
  p2->SetTopMargin(0.0);
  p2->SetBottomMargin(0.18);
  p1->SetLogy();
  p1->Draw();
  p2->Draw();
  p1->cd();
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");
  h4->Draw("same");
  p2->cd();
  r1->Draw();
  r2->Draw("same");
  r3->Draw("same");

  
  

}
