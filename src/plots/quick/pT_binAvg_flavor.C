void pT_binAvg_flavor(){

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-30_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_bJetEnergyShift_method3.root");

  TH2D *H, *G, *K;

  f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",H);
  f1->GetObject("h_inclGenJetPt_flavor",G);
  f2->GetObject("h_inclRecoJetPt_flavor",K);

  H->Draw();

  TH1D *h_i, *g_i, *k_i;
  TH1D *h_b, *h_bb, *h_bGS;
  TH1D *g_b, *g_bb, *g_bGS;
  TH1D *k_b, *k_bb, *k_bGS;

  TH1D *binFinder = (TH1D*) H->ProjectionY();
  
  h_i = (TH1D*) H->ProjectionX("h_i");
  h_b = (TH1D*) H->ProjectionX("h_b",binFinder->FindBin(5.1),binFinder->FindBin(5.9));
  h_bb = (TH1D*) H->ProjectionX("h_bb",binFinder->FindBin(-4.9),binFinder->FindBin(-4.1));
  h_bGS = (TH1D*) H->ProjectionX("h_bGS",binFinder->FindBin(17.1),binFinder->FindBin(17.9));

  h_b->Add(h_bb);
  h_b->Add(h_bGS);

  g_i = (TH1D*) G->ProjectionX("g_i");
  g_b = (TH1D*) G->ProjectionX("g_b",binFinder->FindBin(5.1),binFinder->FindBin(5.9));
  g_bb = (TH1D*) G->ProjectionX("g_bb",binFinder->FindBin(-4.9),binFinder->FindBin(-4.1));
  g_bGS = (TH1D*) G->ProjectionX("g_bGS",binFinder->FindBin(17.1),binFinder->FindBin(17.9));

  g_b->Add(g_bb);
  g_b->Add(g_bGS);

  k_i = (TH1D*) K->ProjectionX("k_i");
  k_b = (TH1D*) K->ProjectionX("k_b",binFinder->FindBin(5.1),binFinder->FindBin(5.9));
  k_bb = (TH1D*) K->ProjectionX("k_bb",binFinder->FindBin(-4.9),binFinder->FindBin(-4.1));
  k_bGS = (TH1D*) K->ProjectionX("k_bGS",binFinder->FindBin(17.1),binFinder->FindBin(17.9));

  k_b->Add(k_bb);
  k_b->Add(k_bGS);


  
  TH1D *rb_g, *rb_h, *rb_k;

  rb_h = (TH1D*) h_b->Clone("rb_h");
  rb_h->Divide(h_b,h_i,1,1,"B");
  
  rb_g = (TH1D*) g_b->Clone("rb_g");
  rb_g->Divide(g_b,g_i,1,1,"B");

  rb_k = (TH1D*) k_b->Clone("rb_k");
  rb_k->Divide(k_b,k_i,1,1,"B");

  rb_g->SetLineColor(kBlack);
  rb_h->SetLineColor(kBlue-4);
  rb_k->SetLineColor(kGreen+2);

  rb_h->SetStats(0);
  rb_h->SetTitle("");
  rb_h->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  rb_h->GetYaxis()->SetTitle("Inclusive #it{b}-jet fraction");
  rb_h->Draw();
  rb_g->Draw("same");
  rb_k->Draw("same");

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.04);
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.5,0.8,"Gen");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.5,0.72,"Nom. Reco");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.5,0.64,"Corr. Reco");

  double pT_low_1 = 60.0;
  double pT_high_1 = 80.0;
  double smallShift = 0.1;
  int bin_low_1 = h_i->FindBin(pT_low_1 + smallShift);
  int bin_high_1 = h_i->FindBin(pT_high_1 - smallShift);
  double h_i_sum = 0.0;
  double h_i_weight = 0.0;
  double h_b_sum = 0.0;
  double h_b_weight = 0.0;

  for(int i = bin_low_1; i < bin_high_1; i++){
    h_i_sum += h_i->GetBinCenter(i) * h_i->GetBinContent(i);
    h_i_weight += h_i->GetBinContent(i);
    h_b_sum += h_b->GetBinCenter(i) * h_b->GetBinContent(i);
    h_b_weight += h_b->GetBinContent(i);
  }
  
  
  cout << "==== 60 < pT,jet < 80 GeV ====" << endl;
  cout << "    <pT,allJet> = " << h_i_sum / h_i_weight << endl;
  cout << "    <pT,bJet> = " << h_b_sum / h_b_weight << endl;

  pT_low_1 = 80.0;
  pT_high_1 = 120.0;
  smallShift = 0.1;
  bin_low_1 = h_i->FindBin(pT_low_1 + smallShift);
  bin_high_1 = h_i->FindBin(pT_high_1 - smallShift);
  h_i_sum = 0.0;
  h_i_weight = 0.0;
  h_b_sum = 0.0;
  h_b_weight = 0.0;

  for(int i = bin_low_1; i < bin_high_1; i++){
    h_i_sum += h_i->GetBinCenter(i) * h_i->GetBinContent(i);
    h_i_weight += h_i->GetBinContent(i);
    h_b_sum += h_b->GetBinCenter(i) * h_b->GetBinContent(i);
    h_b_weight += h_b->GetBinContent(i);
  }

  cout << "==== 80 < pT,jet < 120 GeV ====" << endl;
  cout << "    <pT,allJet> = " << h_i_sum / h_i_weight << endl;
  cout << "    <pT,bJet> = " << h_b_sum / h_b_weight << endl;

  pT_low_1 = 120.0;
  pT_high_1 = 200.0;
  smallShift = 0.1;
  bin_low_1 = h_i->FindBin(pT_low_1 + smallShift);
  bin_high_1 = h_i->FindBin(pT_high_1 - smallShift);
  h_i_sum = 0.0;
  h_i_weight = 0.0;
  h_b_sum = 0.0;
  h_b_weight = 0.0;

  for(int i = bin_low_1; i < bin_high_1; i++){
    h_i_sum += h_i->GetBinCenter(i) * h_i->GetBinContent(i);
    h_i_weight += h_i->GetBinContent(i);
    h_b_sum += h_b->GetBinCenter(i) * h_b->GetBinContent(i);
    h_b_weight += h_b->GetBinContent(i);
  }

  cout << "==== 120 < pT,jet < 200 GeV ====" << endl;
  cout << "    <pT,allJet> = " << h_i_sum / h_i_weight << endl;
  cout << "    <pT,bJet> = " << h_b_sum / h_b_weight << endl;

}
