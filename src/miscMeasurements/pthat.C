void pthat(){

  //TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/response/PH_DiJet_pTjet-5_pThat-25_removeHYDJETjet0p45_response_fineCentBins.root");
  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/response/PH_DiJet_pTjet-5_pThat-25_response_fineCentBins.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/response/PH_DiJet_pTjet-5_pThat-15_response_fineCentBins_prime.root");

  TH2D *H1, *H2;
  TH1D *h1, *h2;

  //f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C1",H1);
  //f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C1",H2);

  // f1->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",H1);
  // f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",H2);

  // f1->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H1);
  // f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H2);

  f1->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H1);
  f2->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H2);

    
  // f1->GetObject("h_inclRecoJetPt_flavor_C1",H1);
  // f2->GetObject("h_inclRecoJetPt_flavor_C1",H2);

  cout << "entries(pThat > 15) = " << H1->GetEntries() << endl;
  //cout << "entries(pThat > 25, pThat > 0.45*pTjet) = " << H2->GetEntries() << endl;
  cout << "entries(pThat > 25) = " << H2->GetEntries() << endl;

  

  
  h1 = (TH1D*) H1->ProjectionX("h1",H2->ProjectionY()->FindBin(20.),H2->ProjectionY()->FindBin(500.));
  h2 = (TH1D*) H2->ProjectionX("h2",H2->ProjectionY()->FindBin(20.),H2->ProjectionY()->FindBin(500.));

  // h2->Draw();

  TH1D *r = (TH1D*) h1->Clone("r");
  r->Divide(h1,h2,1,1,"B");
  r->SetStats(0);
  //r->SetTitle("P+H 0-10%, Inclusive jets");
  //r->SetTitle("P+H 0-10%, #mu-tagged jets");
  r->GetYaxis()->SetRangeUser(0.3,1);
  r->SetTitle("");
  r->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  //r->GetYaxis()->SetTitle("N^{jet}(#hat{p}_{T} > 25, #hat{p}_{T} > 0.45 p_{T}^{jet}) / N^{jet}(#hat{p}_{T} > 15)");
  r->GetYaxis()->SetTitle("N^{jet}(#hat{p}_{T} > 25) / N^{jet}(#hat{p}_{T} > 15)");
  //r->GetYaxis()->SetTitle("N^{jet}(#hat{p}_{T} > 15, #hat{p}_{T} > 0.45 p_{T}^{jet}) / N^{jet}(#hat{p}_{T} > 15)");
  r->Draw();

}
