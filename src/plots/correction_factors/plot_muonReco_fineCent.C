
void stylize_histos(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4, TH1D *h5){


  cout << "stylizing histograms..." << endl;
  
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  h5->SetLineWidth(2);

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kBlue-4);
  h4->SetLineColor(kGreen+2);
  h5->SetLineColor(kMagenta-3);

  h1->SetMarkerColor(kBlack);
  h2->SetMarkerColor(kRed-4);
  h3->SetMarkerColor(kBlue-4);
  h4->SetMarkerColor(kGreen+2);
  h5->SetMarkerColor(kMagenta-3);

  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  h4->SetStats(0);
  h5->SetStats(0);

  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");
  h4->SetTitle("");
  h5->SetTitle("");
  
  
}


void plot_muonReco_fineCent(){


  TFile *f_py = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight.root");
  TFile *f_ph = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_newJetBins_fineCentBins.root");

  TH2D *H0_py, *H1_py;
  TH2D *H0_ph_C1, *H1_ph_C1;
  TH2D *H0_ph_C2, *H1_ph_C2;
  TH2D *H0_ph_C3, *H1_ph_C3;
  TH2D *H0_ph_C4, *H1_ph_C4;

  TH1D *h0_py, *h1_py;
  TH1D *h0_ph_C1, *h1_ph_C1;
  TH1D *h0_ph_C2, *h1_ph_C2;
  TH1D *h0_ph_C3, *h1_ph_C3;
  TH1D *h0_ph_C4, *h1_ph_C4;

  // f_py->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor",H0_py);
  // f_py->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",H1_py);

  // f_ph->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C1",H0_ph_C1);
  // f_ph->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C2",H0_ph_C2);
  // f_ph->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C3",H0_ph_C3);
  // f_ph->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor_C4",H0_ph_C4);

  // f_ph->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C1",H1_ph_C1);
  // f_ph->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C2",H1_ph_C2);
  // f_ph->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C3",H1_ph_C3);
  // f_ph->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C4",H1_ph_C4);



  f_py->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor",H0_py);
  f_py->GetObject("h_inclRecoJetPt_matchedRecoMuonTag_flavor",H1_py);

  f_ph->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C1",H0_ph_C1);
  f_ph->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C2",H0_ph_C2);
  f_ph->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C3",H0_ph_C3);
  f_ph->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor_C4",H0_ph_C4);

  f_ph->GetObject("h_inclRecoJetPt_matchedRecoMuonTag_flavor_C1",H1_ph_C1);
  f_ph->GetObject("h_inclRecoJetPt_matchedRecoMuonTag_flavor_C2",H1_ph_C2);
  f_ph->GetObject("h_inclRecoJetPt_matchedRecoMuonTag_flavor_C3",H1_ph_C3);
  f_ph->GetObject("h_inclRecoJetPt_matchedRecoMuonTag_flavor_C4",H1_ph_C4);


  
  //  H0_ph_C1->Draw();



 

  h0_py = (TH1D*) H0_py->ProjectionX("h0_py");
  h1_py = (TH1D*) H1_py->ProjectionX("h1_py");
  
  h0_ph_C1 = (TH1D*) H0_ph_C1->ProjectionX("h0_ph_C1");
  h0_ph_C2 = (TH1D*) H0_ph_C2->ProjectionX("h0_ph_C2");
  h0_ph_C3 = (TH1D*) H0_ph_C3->ProjectionX("h0_ph_C3");
  h0_ph_C4 = (TH1D*) H0_ph_C4->ProjectionX("h0_ph_C4");

  h1_ph_C1 = (TH1D*) H1_ph_C1->ProjectionX("h1_ph_C1");
  h1_ph_C2 = (TH1D*) H1_ph_C2->ProjectionX("h1_ph_C2");
  h1_ph_C3 = (TH1D*) H1_ph_C3->ProjectionX("h1_ph_C3");
  h1_ph_C4 = (TH1D*) H1_ph_C4->ProjectionX("h1_ph_C4");

  const int N_edge = 10;
  double newAxis[N_edge] = {60,70,80,90,100,120,150,200,300,500};

  h0_py = (TH1D*) h0_py->Rebin(N_edge-1,"h0_py",newAxis);
  h1_py = (TH1D*) h1_py->Rebin(N_edge-1,"h1_py",newAxis);

  h0_ph_C1 = (TH1D*) h0_ph_C1->Rebin(N_edge-1,"h0_ph_C1",newAxis);
  h1_ph_C1 = (TH1D*) h1_ph_C1->Rebin(N_edge-1,"h1_ph_C1",newAxis);

  h0_ph_C2 = (TH1D*) h0_ph_C2->Rebin(N_edge-1,"h0_ph_C2",newAxis);
  h1_ph_C2 = (TH1D*) h1_ph_C2->Rebin(N_edge-1,"h1_ph_C2",newAxis);

  h0_ph_C3 = (TH1D*) h0_ph_C3->Rebin(N_edge-1,"h0_ph_C3",newAxis);
  h1_ph_C3 = (TH1D*) h1_ph_C3->Rebin(N_edge-1,"h1_ph_C3",newAxis);

  h0_ph_C4 = (TH1D*) h0_ph_C4->Rebin(N_edge-1,"h0_ph_C4",newAxis);
  h1_ph_C4 = (TH1D*) h1_ph_C4->Rebin(N_edge-1,"h1_ph_C4",newAxis);
  
  

  TH1D *r_py = (TH1D*) h0_py->Clone("r_py");
  TH1D *r_ph_C1 = (TH1D*) h0_ph_C1->Clone("r_ph_C1");
  TH1D *r_ph_C2 = (TH1D*) h0_ph_C2->Clone("r_ph_C2");
  TH1D *r_ph_C3 = (TH1D*) h0_ph_C3->Clone("r_ph_C3");
  TH1D *r_ph_C4 = (TH1D*) h0_ph_C4->Clone("r_ph_C4");

  r_py->Divide(h1_py,h0_py,1,1,"B");
  r_ph_C1->Divide(h1_ph_C1,h0_ph_C1,1,1,"B");
  r_ph_C2->Divide(h1_ph_C2,h0_ph_C2,1,1,"B");
  r_ph_C3->Divide(h1_ph_C3,h0_ph_C3,1,1,"B");
  r_ph_C4->Divide(h1_ph_C4,h0_ph_C4,1,1,"B");

  stylize_histos(r_py,r_ph_C2,r_ph_C1,r_ph_C3,r_ph_C4); 

  r_py->Draw();
  r_ph_C1->Draw("same");
  r_ph_C2->Draw("same");
  r_ph_C3->Draw("same");
  r_ph_C4->Draw("same");
  

  
}
