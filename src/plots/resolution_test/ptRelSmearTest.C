


void ptRelSmearTest(){

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/platinum/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_newJetBins.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/platinum/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_muPtRelReweightC2_newJetBins.root");
  TFile *f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/platinum/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_muPtRelReweightC1_newJetBins.root");

  TH2D *H1, *H2, *H3;
  TH1D *h1, *h2, *h3;

  f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J1",H1);
  f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J1",H2);
  f3->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J1",H3);

  h1 = (TH1D*) H1->ProjectionX("h1");
  h2 = (TH1D*) H2->ProjectionX("h2");
  h3 = (TH1D*) H3->ProjectionX("h3");

  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kGreen+2);

  h1->SetStats(0);
  h1->SetTitle("PYTHIA, 80 < #it{p}_{T}^{jet} (GeV) < 100");
  h1->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h1->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T} [GeV^{-1}]");


  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");

  
  
  
}
