void pTref_compare_neutrino(double pT_proj_low = 60.0, double pT_proj_high = 80.0){


  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_withReco_allJets.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_inclJets_noNeutrino.root");
  TFile *f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_inclJets_withNeutrino.root");
  TFile *f4 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_muTaggedJets_doBJetNeutrinoEnergyShift.root");

  TH2D *H1, *H2, *H3, *H4;

  // f1->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_allJets",H1);
  // f2->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_bJets",H2);
  // f3->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_bJets",H3);

  f1->GetObject("h_matchedRecoJetPt_genJetPt",H1);
  f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H2);
  f3->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H3);
  f3->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H4);

  TH1D *h1, *h2, *h3, *h4;

  TH1D *binFinder = H1->ProjectionX("binFinder");
  h1 = (TH1D*) H1->ProjectionY("h1",binFinder->FindBin(pT_proj_low),binFinder->FindBin(pT_proj_high));
  h2 = (TH1D*) H2->ProjectionY("h2",binFinder->FindBin(pT_proj_low),binFinder->FindBin(pT_proj_high));
  h3 = (TH1D*) H3->ProjectionY("h3",binFinder->FindBin(pT_proj_low),binFinder->FindBin(pT_proj_high));
  h4 = (TH1D*) H4->ProjectionY("h4",binFinder->FindBin(pT_proj_low),binFinder->FindBin(pT_proj_high));
  // H1->Draw();

  cout << "H1(entries) = " << H1->GetEntries() << endl;
  cout << "H2(entries) = " << H2->GetEntries() << endl;
  cout << "H3(entries) = " << H3->GetEntries() << endl;

  cout << "h1(integral) = " << h1->Integral() << endl;
  cout << "h2(integral) = " << h2->Integral() << endl;
  cout << "h3(integral) = " << h3->Integral() << endl;

  double N_tot = h2->Integral() + h3->Integral();
  double r2 = h2->Integral() / N_tot;
  double r3 = h3->Integral() / N_tot;

  h1->SetLineColor(kRed-4);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kGreen+2);
  h3->SetLineColor(kMagenta);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);

  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());
  h4->Scale(1./h4->Integral());

  //cout << "mean(h1) = " << h1->GetMean() << endl;

  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0,1,1);
  p1->SetLeftMargin(0.15);
  p1->SetBottomMargin(0.11);
  p1->Draw();
  p1->cd();

  h1->SetTitle("");
  h1->SetStats(0);
  h1->GetXaxis()->SetTitle("#it{p}_{T}^{genJet} [GeV]");
  //h1->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} / #it{p}_{T}^{genJet} [GeV]");
  h1->GetYaxis()->SetTitle("a.u.");
  h1->GetXaxis()->SetRangeUser(30,300);
  
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");
  //h4->Draw("same");

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.04);
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.5,0.85,Form("%3.0f < #it{p}_{T}^{recoJet} < %3.0f GeV",pT_proj_low,pT_proj_high));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.5,0.77,"Inclusive jets");
  la->DrawLatexNDC(0.5,0.35,Form("<#it{p}_{T}^{incl.}> = %3.3f",h1->GetMean()));
  la->SetTextColor(kBlue-4);
  //la->DrawLatexNDC(0.5,0.69,"#mu-tagged #it{b}-jets");
  la->DrawLatexNDC(0.5,0.69,Form("Jets with no #nu (%3.1f \%)",100.*r2));
  //la->DrawLatexNDC(0.5,0.27,Form("<#it{p}_{T}^{#mu-tagged-#it{b}}> = %3.3f",h2->GetMean()));
  la->DrawLatexNDC(0.5,0.27,Form("<#it{p}_{T}^{no-#nu}> = %3.3f",h2->GetMean()));
  la->SetTextColor(kGreen+2);
  //la->DrawLatexNDC(0.5,0.61,"#mu-tagged #it{b}-jets w/ correction");
  la->DrawLatexNDC(0.5,0.61,Form("#nu-tagged jet (%3.1f \%)",100.*r3));
  la->DrawLatexNDC(0.5,0.19,Form("<#it{p}_{T}^{#nu-tagged}> = %3.3f",h3->GetMean()));
  la->SetTextSize(0.036);
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.17,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{ Preliminary}}");
  la->DrawLatexNDC(0.6,0.92,"PYTHIA (5.02 TeV)");

  TCanvas *c2 = new TCanvas("c2","c2",700,700);
  c2->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,1);
  p2->SetLeftMargin(0.2);
  p2->SetBottomMargin(0.2);
  p2->Draw();
  p2->cd();
  
  
  TH1D *r = (TH1D*) h3->Clone("r");
  r->Divide(h3,h1,1,1,"");
  r->Draw();
  

}

void pTref_compare_correction_method(double pT_proj_low = 60.0, double pT_proj_high = 80.0){


  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_withReco_allJets.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_muTaggedJets.root");
  TFile *f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_muTaggedJets_doNeutrinoEnergyAddition.root");
  TFile *f4 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_muTaggedJets_doBJetNeutrinoEnergyShift.root");

  TH2D *H1, *H2, *H3, *H4;

  // f1->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_allJets",H1);
  // f2->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_bJets",H2);
  // f3->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_bJets",H3);

  f1->GetObject("h_matchedRecoJetPt_genJetPt",H1);
  f2->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H2);
  f3->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H3);
  f4->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H4);

  TH1D *h1, *h2, *h3, *h4;

  TH1D *binFinder = H1->ProjectionX("binFinder");
  h1 = (TH1D*) H1->ProjectionY("h1",binFinder->FindBin(pT_proj_low),binFinder->FindBin(pT_proj_high));
  h2 = (TH1D*) H2->ProjectionY("h2",binFinder->FindBin(pT_proj_low),binFinder->FindBin(pT_proj_high));
  h3 = (TH1D*) H3->ProjectionY("h3",binFinder->FindBin(pT_proj_low),binFinder->FindBin(pT_proj_high));
  h4 = (TH1D*) H4->ProjectionY("h4",binFinder->FindBin(pT_proj_low),binFinder->FindBin(pT_proj_high));
  // H1->Draw();

  cout << "H1(entries) = " << H1->GetEntries() << endl;
  cout << "H2(entries) = " << H2->GetEntries() << endl;
  cout << "H3(entries) = " << H3->GetEntries() << endl;

  cout << "h1(integral) = " << h1->Integral() << endl;
  cout << "h2(integral) = " << h2->Integral() << endl;
  cout << "h3(integral) = " << h3->Integral() << endl;

  double N_tot = h2->Integral() + h3->Integral();
  double r2 = h2->Integral() / N_tot;
  double r3 = h3->Integral() / N_tot;

  h1->SetLineColor(kRed-4);
  h2->SetLineColor(kBlue+9);
  h3->SetLineColor(kGreen+2);
  h4->SetLineColor(kMagenta);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);

  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());
  h4->Scale(1./h4->Integral());

  //cout << "mean(h1) = " << h1->GetMean() << endl;

  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0,1,1);
  p1->SetLeftMargin(0.15);
  p1->SetBottomMargin(0.11);
  p1->Draw();
  p1->cd();

  h1->SetTitle("");
  h1->SetStats(0);
  h1->GetXaxis()->SetTitle("#it{p}_{T}^{genJet} [GeV]");
  //h1->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} / #it{p}_{T}^{genJet} [GeV]");
  h1->GetYaxis()->SetTitle("a.u.");
  h1->GetXaxis()->SetRangeUser(30,300);
  
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");
  h4->Draw("same");

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.04);
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.5,0.85,Form("%3.0f < #it{p}_{T}^{recoJet} < %3.0f GeV",pT_proj_low,pT_proj_high));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.5,0.77,"Inclusive jets");
  la->DrawLatexNDC(0.5,0.35,Form("<#it{p}_{T}^{incl.}> = %3.3f",h1->GetMean()));
  la->SetTextColor(kBlue+9);
  //la->DrawLatexNDC(0.5,0.69,"#mu-tagged #it{b}-jets");
  la->DrawLatexNDC(0.5,0.69,"#it{#mu}-tagged jets");
  //la->DrawLatexNDC(0.5,0.27,Form("<#it{p}_{T}^{#mu-tagged-#it{b}}> = %3.3f",h2->GetMean()));
  la->DrawLatexNDC(0.5,0.27,Form("<#it{p}_{T}^{#it{#mu}-tagged-jet}> = %3.3f",h2->GetMean()));
  la->SetTextColor(kGreen+2);
  //la->DrawLatexNDC(0.5,0.61,"#mu-tagged #it{b}-jets w/ correction");
  la->DrawLatexNDC(0.5,0.61,"#it{#mu}-tagged jet w/ #it{#nu}-addition");
  la->DrawLatexNDC(0.5,0.19,Form("<#it{p}_{T,#it{#nu}-add}^{#it{#mu}-tagged-jet}> = %3.3f",h3->GetMean()));
  la->SetTextColor(kMagenta);
  la->DrawLatexNDC(0.5,0.53,"#it{#mu}-tagged jet w/ #it{#nu}-smear");
  la->DrawLatexNDC(0.5,0.11,Form("<#it{p}_{T,#it{#nu}-smear}^{#it{#mu}-tagged-jet}> = %3.3f",h4->GetMean()));
  la->SetTextSize(0.036);
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.17,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{ Preliminary}}");
  la->DrawLatexNDC(0.6,0.92,"PYTHIA (5.02 TeV)");

  TCanvas *c2 = new TCanvas("c2","c2",700,700);
  c2->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,1);
  p2->SetLeftMargin(0.2);
  p2->SetBottomMargin(0.2);
  p2->Draw();
  p2->cd();
  
  
  TH1D *r = (TH1D*) h3->Clone("r");
  r->Divide(h3,h1,1,1,"");
  r->Draw();
  

}

void pTref_compare(double pT_proj_low = 60.0, double pT_proj_high = 80.0){
  //pTref_compare_neutrino(pT_proj_low, pT_proj_high);
  pTref_compare_correction_method(pT_proj_low, pT_proj_high);
  return;
}
