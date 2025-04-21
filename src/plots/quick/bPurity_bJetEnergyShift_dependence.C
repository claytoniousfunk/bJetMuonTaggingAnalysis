void bPurity_bJetEnergyShift_dependence(){

  TFile *f_1, *f0;  // initial spectra files

  f_1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight.root");
  //f0 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_doBJetNeutrinoEnergyShift.root");
  f0 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_bJetNeutrinoEnergyShift_directEnergyAddition.root");

  //f0 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_doBJetNeutrinoEnergyShift_recoBasedDiceRoll.root");

  //f_1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_withNeutrinos_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight.root");
  //f0 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_withNeutrinos_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_neutrinoEnergyAddition.root");

  TH2D *H_1, *H0;
  TH1D *h_1, *h0;

  f_1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",H_1);
  f0->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",H0);
  //f_1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor",H_1);
  //f0->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor",H0);
  //f_1->GetObject("h_inclRecoJetPt_flavor",H_1);
  //f0->GetObject("h_inclRecoJetPt_flavor",H0);

  cout << "H_1(entries) = " << H_1->GetEntries() << endl;
  cout << "H0(entries) = " << H0->GetEntries() << endl;

  TH1D *b_1, *bb_1, *bGS_1;
  TH1D *b_0, *bb_0, *bGS_0;

  TH1D *binFinder = H0->ProjectionY();

  b_1 = (TH1D*) H_1->ProjectionX("b_1",binFinder->FindBin(5.1),binFinder->FindBin(5.9));
  bb_1 = (TH1D*) H_1->ProjectionX("bb_1",binFinder->FindBin(-4.9),binFinder->FindBin(-4.1));
  bGS_1 = (TH1D*) H_1->ProjectionX("bGS_1",binFinder->FindBin(17.1),binFinder->FindBin(17.9));

  b_0 = (TH1D*) H0->ProjectionX("b_0",binFinder->FindBin(5.1),binFinder->FindBin(5.9));
  bb_0 = (TH1D*) H0->ProjectionX("bb_0",binFinder->FindBin(-4.9),binFinder->FindBin(-4.1));
  bGS_0 = (TH1D*) H0->ProjectionX("bGS_0",binFinder->FindBin(17.1),binFinder->FindBin(17.9));

  

  b_0->Add(bb_0);
  b_0->Add(bGS_0);
  b_1->Add(bb_1);
  b_1->Add(bGS_1);
  
  h_1 = (TH1D*) b_1->Clone("h_1");
  h0 = (TH1D*) b_0->Clone("h0");
  
  //h_1 = (TH1D*) H_1->ProjectionX("h_1");
  //h0 = (TH1D*) H0->ProjectionX("h0");

  h_1->SetLineColor(kBlue-4);
  h0->SetLineColor(kRed-4);

  h_1->SetLineWidth(2);
  h0->SetLineWidth(2);

  TCanvas *c0 = new TCanvas("c0","c0",700,700);
  c0->cd();
  c0->SetLogy();
  h_1->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  h_1->GetYaxis()->SetTitle("N^{jet}(#it{#mu}-tagged)");
  h_1->SetTitle("");
  h_1->SetStats(0);
  h_1->Draw();
  h0->Draw("same");

  TH1D *r0  = (TH1D*) h0->Clone("r0");
  r0->Divide(h0,h_1,1,1,"B");
  
  TCanvas *c_1 = new TCanvas("c_1","c_1",700,700);
  c_1->cd();
  r0->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  //r0->GetYaxis()->SetTitle("N^{#it{#mu}-#it{b}-jet}(w/ corr.) / N^{#it{#mu}-#it{b}-jet}(nom.)");
  r0->GetYaxis()->SetTitle("N^{incl-jet}(w/ corr.) / N^{incl-jet}(nom.)");
  r0->SetTitle("");
  r0->SetStats(0);
  r0->Draw();
  
  
  
  TFile *f1, *f2;

  f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/golden/bPurityResults_DATA-0_mu5-0_mu7-0_mu12-1_mergeB-0_mergeC-0_pTrel-0.0to5.0_cMult-1.0_bMult-1.0_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0_bJetEnergyShift-0.root");
  f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/golden/bPurityResults_DATA-0_mu5-0_mu7-0_mu12-1_mergeB-0_mergeC-0_pTrel-0.0to5.0_cMult-1.0_bMult-1.0_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0_bJetEnergyShift-1.root");

  TH1D *h1, *h2;

  f1->GetObject("bFracResults_pp",h1);
  f2->GetObject("bFracResults_pp",h2);

  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);

  // h1->Draw();
  // h2->Draw("same");


  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();

  
  TH1D *r = (TH1D*) h1->Clone("h1");
  r->Divide(h1,h2,1,1,"B");

  r->SetTitle("");
  r->SetStats(0);
  r->GetYaxis()->SetTitle("#it{f}_{#it{b}}^{nom.}(pp) / #it{f}_{#it{b}}^{corr.}(pp)");
  r->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  r->GetYaxis()->SetRangeUser(0.99,1.01);
  
    
  r->Draw();



  TFile *f3, *f4;

  f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/plots/tagging_sequence/matchingFactors/mf_mu12_nom.root");
  f4 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/plots/tagging_sequence/matchingFactors/mf_mu12_bJetEnergyShift.root");

  TH1D *h3, *h4;

  f3->GetObject("mf",h3);
  f4->GetObject("mf",h4);

  h3->SetLineColor(kBlue-4);
  h4->SetLineColor(kRed-4);

  h3->SetLineWidth(2);
  h4->SetLineWidth(2);


  TCanvas *c2 = new TCanvas("c2","c2",700,700);
  c2->cd();

  h3->Draw();
  h4->Draw("same");


  TFile *f5, *f6;

  f5 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/plots/tagging_sequence/b_amplifiers/ba_pp_mu12_nom.root");
  f6 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/src/plots/tagging_sequence/b_amplifiers/ba_pp_mu12_bJetEnergyShift.root");

  TH1D *h5, *h6;

  f5->GetObject("r_corr",h5);
  f6->GetObject("r_corr",h6);

  h5->SetLineColor(kBlue-4);
  h6->SetLineColor(kRed-4);

  h5->SetLineWidth(2);
  h6->SetLineWidth(2);

  TCanvas *c3 = new TCanvas("c3","c3",700,700);
  c3->cd();

  h5->Draw();
  h6->Draw("same");



  

}
