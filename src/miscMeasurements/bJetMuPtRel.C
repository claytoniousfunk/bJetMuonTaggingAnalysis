
TFile *f1, *f2, *f3;
TH2D *H1, *H2, *H3;
TH2D *A1, *A2, *A3;
TH1D *h1, *h2, *h3;
TH1D *a1, *a2, *a3;
TH1D *aa1, *aa2, *aa3;


void bJetMuPtRel(){

  f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/correctHiBinShift/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_vzReweight_hiBinReweight_jetTrkMaxFilter_removeHYDJETjet0p45_fineCentBins_projectableTemplates_allTemplates_correctHiBinShift.root");

  f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/correctHiBinShift/PYTHIAHYDJET_MuJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_vzReweight_hiBinReweight_jetTrkMaxFilter_removeHYDJETjet0p45_fineCentBins_projectableTemplates_allTemplates_correctHiBinShift.root");

  f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/correctHiBinShift/PYTHIAHYDJET_BJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_vzReweight_hiBinReweight_jetTrkMaxFilter_removeHYDJETjet0p45_fineCentBins_projectableTemplates_allTemplates_correctHiBinShift.root");

  f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H1);
  f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H2);
  f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H3);

  f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",A1);
  f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",A2);
  f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",A3);

  h1 = (TH1D*) H1->ProjectionX("h1");
  h2 = (TH1D*) H2->ProjectionX("h2");
  h3 = (TH1D*) H3->ProjectionX("h3");

  a1 = (TH1D*) A1->ProjectionX("a1");
  a2 = (TH1D*) A2->ProjectionX("a2");
  a3 = (TH1D*) A3->ProjectionX("a3");

  h1->Add(h2);
  h1->Add(h3);
  a1->Add(a2);
  a1->Add(a3);

  

  h1->Scale(1./h1->Integral());
  a1->Scale(1./a1->Integral());

  h1->SetLineColor(kRed-4);
  a1->SetLineColor(kBlue-4);

  h1->SetLineWidth(2);
  a1->SetLineWidth(2);

  h1->SetTitle("");
  h1->SetStats(0);
  h1->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h1->GetYaxis()->SetTitle("a.u.");
  h1->Draw("hist");
  a1->Draw("hist same");


  TH1D *r = (TH1D*) h1->Clone("r");
  r->Divide(h1,a1,1,1,"");

  r->GetYaxis()->SetRangeUser(0,2);
  r->GetYaxis()->SetTitle("P+H 0-10% / P+H 10-30%");
  r->Draw("hist");
  
  

  


}
