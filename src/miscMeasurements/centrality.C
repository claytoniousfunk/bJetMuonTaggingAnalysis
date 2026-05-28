


void centrality(){

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_fineCentBins_projectableTemplates_allTemplates.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/noHiBinShift/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_vzReweight_hiBinReweight_jetTrkMaxFilter_removeHYDJETjet0p45_fineCentBins_projectableTemplates_allTemplates_noHiBinShift.root");
  TFile *f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/correctHiBinShift/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_vzReweight_hiBinReweight_jetTrkMaxFilter_removeHYDJETjet0p45_fineCentBins_projectableTemplates_allTemplates_correctHiBinShift.root");


  TH2D *H1, *H2, *H3;
  TH1D *h1, *h2, *h3;
  TH1D *a1, *a2, *a3;
  TH1D *b1, *b2, *b3;
  
  f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H1);
  f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H2);
  f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H3);

  H1->Draw();


  h1 = (TH1D*) H1->ProjectionX("h1",H1->ProjectionY()->FindBin(80),H1->ProjectionY()->FindBin(100));
  h2 = (TH1D*) H2->ProjectionX("h2",H2->ProjectionY()->FindBin(80),H2->ProjectionY()->FindBin(100));
  h3 = (TH1D*) H3->ProjectionX("h3",H3->ProjectionY()->FindBin(80),H3->ProjectionY()->FindBin(100));

  a1 = (TH1D*) H1->ProjectionX("a1",H1->ProjectionY()->FindBin(80),H1->ProjectionY()->FindBin(100));
  a2 = (TH1D*) H2->ProjectionX("a2",H2->ProjectionY()->FindBin(80),H2->ProjectionY()->FindBin(100));
  a3 = (TH1D*) H3->ProjectionX("a3",H3->ProjectionY()->FindBin(80),H3->ProjectionY()->FindBin(100));

  b1 = (TH1D*) H1->ProjectionX("b1",H1->ProjectionY()->FindBin(80),H1->ProjectionY()->FindBin(100));
  b2 = (TH1D*) H2->ProjectionX("b2",H2->ProjectionY()->FindBin(80),H2->ProjectionY()->FindBin(100));
  b3 = (TH1D*) H3->ProjectionX("b3",H3->ProjectionY()->FindBin(80),H3->ProjectionY()->FindBin(100));
  
  h1->Add(a1); h1->Add(b1);
  h2->Add(a2); h2->Add(b2);
  h3->Add(a3); h3->Add(b3);


  h1->SetLineColor(kBlack);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kBlue-4);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);

  h1->Rebin(2);
  h2->Rebin(2);
  h3->Rebin(2);

  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());

  h1->Draw("hist");
  h2->Draw("hist same");
  h3->Draw("hist same");
  

}
