


void jetFilter(){

  TFile *f1, *f2, *f3, *f4, *f5;
  TH2D *H1, *H2, *H3, *H4, *H5;
  TH1D *h1, *h2, *h3, *h4, *h5;
  TH1D *a1, *a2, *a3, *a4, *a5;
  TH1D *r2, *r3, *r4, *r5;
  
  f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_noWeightCut_fineCentBins_projectableTemplates_allTemplates.root");	
  f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-25_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_noWeightCut_fineCentBins_projectableTemplates_allTemplates.root");
  f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-25_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_noWeightCut_removeHYDJETjet_fineCentBins_projectableTemplates_allTemplates.root");
  f4 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-25_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_noWeightCut_removeHYDJETjet0p4_fineCentBins_projectableTemplates_allTemplates.root");
  f5 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-25_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_noWeightCut_removeHYDJETjet0p45_fineCentBins_projectableTemplates_allTemplates.root");

  

  f1->GetObject("h_inclGenJetPt_flavor_C1",H1);
  f2->GetObject("h_inclGenJetPt_flavor_C1",H2);
  f3->GetObject("h_inclGenJetPt_flavor_C1",H3);
  f4->GetObject("h_inclGenJetPt_flavor_C1",H4);
  f5->GetObject("h_inclGenJetPt_flavor_C1",H5);

  TH1D *bf = H1->ProjectionY();
  double ss = 0.01;
  
  h1 = (TH1D*) H1->ProjectionX("h1",bf->FindBin(-5+ss),bf->FindBin(0-ss));
  h2 = (TH1D*) H2->ProjectionX("h2",bf->FindBin(-5+ss),bf->FindBin(0-ss));
  h3 = (TH1D*) H3->ProjectionX("h3",bf->FindBin(-5+ss),bf->FindBin(0-ss));
  h4 = (TH1D*) H4->ProjectionX("h4",bf->FindBin(-5+ss),bf->FindBin(0-ss));
  h5 = (TH1D*) H5->ProjectionX("h5",bf->FindBin(-5+ss),bf->FindBin(0-ss));

  double ghostSkip = 1.;
  a1 = (TH1D*) H1->ProjectionX("a1",bf->FindBin(ghostSkip+ss),bf->FindBin(22-ss));
  a2 = (TH1D*) H2->ProjectionX("a2",bf->FindBin(ghostSkip+ss),bf->FindBin(22-ss));
  a3 = (TH1D*) H3->ProjectionX("a3",bf->FindBin(ghostSkip+ss),bf->FindBin(22-ss));
  a4 = (TH1D*) H4->ProjectionX("a4",bf->FindBin(ghostSkip+ss),bf->FindBin(22-ss));
  a5 = (TH1D*) H5->ProjectionX("a5",bf->FindBin(ghostSkip+ss),bf->FindBin(22-ss));

  h1->Add(a1);
  h2->Add(a2);
  h3->Add(a3);
  h4->Add(a4);
  h5->Add(a5);

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kRed-4);
  h4->SetLineColor(kGreen+2);
  h5->SetLineColor(kMagenta-9);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  h5->SetLineWidth(2);


  r2 = (TH1D*) h2->Clone("r2");
  r2->Divide(h2,h1,1,1,"B");

  r3 = (TH1D*) h3->Clone("r3");
  r3->Divide(h3,h1,1,1,"B");

  r4 = (TH1D*) h4->Clone("r4");
  r4->Divide(h4,h1,1,1,"B");

  r5 = (TH1D*) h5->Clone("r5");
  r5->Divide(h5,h1,1,1,"B");

  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->Draw();
  pad->cd();
  r2->SetTitle("");
  r2->GetYaxis()->SetTitle("Ratio to pThat > 15 sample  ");
  r2->GetXaxis()->SetTitle("Gen jet p_{T} [GeV]");
  r2->SetStats(0);
  r2->Draw("hist");
  r3->Draw("hist same");
  r4->Draw("hist same");
  r5->Draw("hist same");

  
  
  


}
