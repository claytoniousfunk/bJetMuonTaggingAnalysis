void neutrinoTagging(){

  //TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-30_muTaggedJets_noTrig.root");
  //TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-30_muTaggedJets_noTrig_withNeutrino.root");

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_muTaggedJets.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_muTaggedJets_withNeutrino.root");

  //TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_muTaggedJets.root");
  //TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_muTaggedJets_withNeutrino.root");
  
  //TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_withNeutrinos_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight.root");


  TH2D *H1, *H2, *H3, *H4;

  // f1->GetObject("h_inclRecoJetPt_flavor",H1);
  // f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor",H1);
  // f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_flavor",H2);
  // f1->GetObject("h_inclRecoJetPt_inclGenMuonTag_genNeutrinoTag_genNeutrinoPt",H4);

  f1->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H1);
  f2->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H2);
  f2->GetObject("h_matchedNeutrinoPt_recoJetPt_bJets",H3);

  TH1D *h1, *h2;

  //h1 = (TH1D*) H1->ProjectionY("h1");
  //h2 = (TH1D*) H2->ProjectionY("h2");

  h1 = (TH1D*) H1->ProjectionX("h1");
  h2 = (TH1D*) H2->ProjectionX("h2");

  TH1D *r;

  r = (TH1D*) h2->Clone("r");
  r->Divide(h2,h1,1,1,"B");




  TCanvas *canv1 = new TCanvas("canv1","canv1",700,700);
  canv1->cd();
  TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0.15);
  pad1->Draw();
  pad1->cd();
  r->SetStats(0);
  r->SetTitleSize(0.04);
  r->SetTitle("Fraction of #it{#mu}-tagged-b-jets tagged with gen-#it{#nu}");
  r->GetXaxis()->SetTitleSize(0.04);
  r->GetYaxis()->SetTitleSize(0.04);
  r->GetXaxis()->SetLabelSize(0.037);
  r->GetYaxis()->SetLabelSize(0.037);
  //r->GetXaxis()->SetTitle("#it{p}_{T}^{genJet} [GeV]");
  r->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  r->GetYaxis()->SetTitle("#it{f}_{#it{#nu}-tag}^{#it{#mu}-tagged-#it{b}-jet}");
  r->GetYaxis()->SetRangeUser(0.4,1.0);
  r->Draw();

  TFile *file_out = TFile::Open("./neutrino_tag_fraction.root","recreate");
  r->Write("neutrino_tag_fraction");
  file_out->Close();

  
  TCanvas *canv2 = new TCanvas("canv2","canv2",700,700);
  canv2->cd();
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,1);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.15);
  pad2->SetLogz();
  pad2->Draw();
  pad2->cd();
  H3->SetStats(0);
  H3->SetTitleSize(0.04);
  H3->SetTitle("#it{b}-jet neutrino-energy-fraction map");
  H3->GetXaxis()->SetTitleSize(0.04);
  H3->GetYaxis()->SetTitleSize(0.04);
  H3->GetXaxis()->SetLabelSize(0.037);
  H3->GetYaxis()->SetLabelSize(0.037);
  H3->GetYaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  H3->GetXaxis()->SetTitle("#it{p}_{T}^{#it{#nu}} [GeV]");
  //H3->GetXaxis()->SetRangeUser(0,0.5);
  H3->Draw();



  /*
  f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_flavor",H3);
  f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_genNeutrinoTag_genNeutrinoPt",H4);

  //H4->Draw("colz");

  // TH2D *R2, *R3;

  // R2 = (TH2D*) H2->Clone("R2");
  // R2->Divide(H2,H1,1,1,"B");

  // R3 = (TH2D*) H3->Clone("R3");
  // R3->Divide(H3,H2,1,1,"B");
  
  // //H1->Draw("colz");
  // //R2->Draw("colz");
  // R3->Draw("colz");

  TH1D *b1, *b2, *b3, *b4;
  TH1D *bb1, *bb2, *bb3, *bb4;
  TH1D *bGS1, *bGS2, *bGS3, *bGS4;

  double ss = 0.1;
  
  TH1D *bf = (TH1D*) H1->ProjectionY();

  b1 = (TH1D*) H1->ProjectionX("b1",bf->FindBin(5.+ss),bf->FindBin(6.-ss));
  bb1 = (TH1D*) H1->ProjectionX("bb1",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));
  bGS1 = (TH1D*) H1->ProjectionX("bGS1",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));
  
  b2 = (TH1D*) H2->ProjectionX("b2",bf->FindBin(5.+ss),bf->FindBin(6.-ss));
  bb2 = (TH1D*) H2->ProjectionX("bb2",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));
  bGS2 = (TH1D*) H2->ProjectionX("bGS2",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));
  
  b3 = (TH1D*) H3->ProjectionX("b3",bf->FindBin(5.+ss),bf->FindBin(6.-ss));
  bb3 = (TH1D*) H3->ProjectionX("bb3",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));
  bGS3 = (TH1D*) H3->ProjectionX("bGS3",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));

  b4 = (TH1D*) H4->ProjectionX("b4",bf->FindBin(5.+ss),bf->FindBin(6.-ss));
  bb4 = (TH1D*) H4->ProjectionX("bb4",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));
  bGS4 = (TH1D*) H4->ProjectionX("bGS4",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));

  b1->Add(bb1);
  b1->Add(bGS1);
  
  b2->Add(bb2);
  b2->Add(bGS2);

  b3->Add(bb3);
  b3->Add(bGS3);

  b4->Add(bb4);
  b4->Add(bGS4);

  TH1D *r2, *r3;

  TCanvas *canv2 = new TCanvas("canv2","canv2",700,700);
  canv2->cd();
  r2 = (TH1D*) b2->Clone("r2");
  r2->Divide(b2,b1,1,1,"B");
  //r2->SetTitle("Fraction of #it{b}-jets tagged with gen muon");
  r2->SetTitle("Fraction of #it{b}-jets tagged with reco muon");
  r2->SetStats(0);
  r2->Draw();

  TCanvas *canv3 = new TCanvas("canv3","canv3",700,700);
  canv3->cd();
  r3 = (TH1D*) b3->Clone("r2");
  r3->Divide(b3,b2,1,1,"B");
  //r3->SetTitle("Fraction of gen-muon-tagged #it{b}-jets tagged with gen neutrino");
  r3->SetTitle("Fraction of reco-muon-tagged #it{b}-jets tagged with gen neutrino");
  r3->SetStats(0);
  r3->Draw();
  */

}
