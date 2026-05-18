



void projectFlavor(){



  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-12_ultraFineCentBins.root");
  //TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-13_ultraFineCentBins.root");
  //TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-30_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p35_2026-1-8.root");


  TH2D *h0, *h1, *h2, *h3, *h4; // 2d flavor-pt maps
  TH2D *hh0, *hh1, *hh2, *hh3, *hh4; // 2d flavor-pt maps
  // CENT BIN 0
  TH1D *h0_incl; // inclusive projection
  TH1D *h0_b, *h0_c, *h0_d, *h0_g, *h0_s, *h0_u; // projections of each quark flavor
  TH1D *h0_bbar, *h0_cbar, *h0_dbar, *h0_sbar, *h0_ubar; // projections of each antiquark flavor
  TH1D *h0_bGS;
  TH1D *h0_ghost;
  TH1D *h0_noFlavor;
	
  // RETRIEVE 2D MAPS

  f1->GetObject("h_inclRecoJetPt_flavor_C0", h0);

  TH1D *binFinder = h0->ProjectionY();
  TAxis *yaxis = binFinder->GetXaxis();
  double smallShift = 0.01;

  // PT
  // CENT BIN 0
  h0_incl = (TH1D*) h0->ProjectionX("h0_incl",binFinder->FindBin(-5+smallShift),binFinder->FindBin(22-smallShift));
  //TH1D *h0_incl_add = (TH1D*) h0->ProjectionX("h0_incl_add",binFinder->FindBin(1+smallShift),binFinder->FindBin(22-smallShift));
  //h0_incl->Add(h0_incl_add);

  h0_b = (TH1D*) h0->ProjectionX("h0_b",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  h0_bGS = (TH1D*) h0->ProjectionX("h0_bGS",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  h0_c = (TH1D*) h0->ProjectionX("h0_c",binFinder->FindBin(4+smallShift),binFinder->FindBin(5-smallShift));
  h0_d = (TH1D*) h0->ProjectionX("h0_d",binFinder->FindBin(1+smallShift),binFinder->FindBin(2-smallShift));
  h0_g = (TH1D*) h0->ProjectionX("h0_g",binFinder->FindBin(21+smallShift),binFinder->FindBin(22-smallShift));
  h0_s = (TH1D*) h0->ProjectionX("h0_s",binFinder->FindBin(3+smallShift),binFinder->FindBin(4-smallShift));
  h0_u = (TH1D*) h0->ProjectionX("h0_u",binFinder->FindBin(2+smallShift),binFinder->FindBin(3-smallShift));
  h0_bbar = (TH1D*) h0->ProjectionX("h0_bbar",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  h0_cbar = (TH1D*) h0->ProjectionX("h0_cbar",binFinder->FindBin(-4+smallShift),binFinder->FindBin(-3-smallShift));
  h0_dbar = (TH1D*) h0->ProjectionX("h0_dbar",binFinder->FindBin(-1+smallShift),binFinder->FindBin(0-smallShift));
  h0_sbar = (TH1D*) h0->ProjectionX("h0_sbar",binFinder->FindBin(-3+smallShift),binFinder->FindBin(-2-smallShift));
  h0_ubar = (TH1D*) h0->ProjectionX("h0_ubar",binFinder->FindBin(-2+smallShift),binFinder->FindBin(-1-smallShift));
  h0_ghost = (TH1D*) h0->ProjectionX("h0_ghost",binFinder->FindBin(0+smallShift),binFinder->FindBin(1-smallShift));
  h0_noFlavor = (TH1D*) h0->ProjectionX("h0_noFlavor",binFinder->FindBin(19+smallShift),binFinder->FindBin(20-smallShift));
	
  h0_b->Add(h0_bbar);
  h0_b->Add(h0_bGS);
  h0_c->Add(h0_cbar);
  h0_d->Add(h0_dbar);
  h0_s->Add(h0_sbar);
  h0_u->Add(h0_ubar);




  TCanvas *canv1 = new TCanvas("canv1","canv1",600,600);
  canv1->cd();
  TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
  pad1->SetLeftMargin(0.2);
  pad1->SetBottomMargin(0.2);
  pad1->SetLogy();
  pad1->Draw();
  pad1->cd();


  /*
    h0_b->Scale(1.0/h0_b->Integral());		
    h0_c->Scale(1.0/h0_c->Integral());		
    h0_u->Scale(1.0/h0_u->Integral());		
    h0_d->Scale(1.0/h0_d->Integral());		
    h0_s->Scale(1.0/h0_s->Integral());		
    h0_g->Scale(1.0/h0_g->Integral());		
    h0_ghost->Scale(1.0/h0_ghost->Integral());		
  */

  h0_b->SetLineWidth(2);
  h0_b->SetLineColor(kRed);
  h0_b->SetFillColor(kRed);

  h0_c->SetLineWidth(2);
  h0_c->SetLineColor(kGreen);
  h0_c->SetFillColor(kGreen);

  h0_u->SetLineWidth(2);
  h0_u->SetLineColor(kBlue);
  h0_u->SetFillColor(kBlue);

  h0_d->SetLineWidth(2);
  h0_d->SetLineColor(kMagenta);
  h0_d->SetFillColor(kMagenta);

  h0_s->SetLineWidth(2);
  h0_s->SetLineColor(kCyan+2);
  h0_s->SetFillColor(kCyan+2);

  h0_g->SetLineWidth(2);
  h0_g->SetLineColor(kOrange);
  h0_g->SetFillColor(kOrange);

  h0_ghost->SetLineWidth(2);
  h0_ghost->SetLineColor(kPink+10);
  h0_ghost->SetFillColor(kPink+10);

  h0_noFlavor->SetLineWidth(2);
  h0_noFlavor->SetLineColor(kCyan+2);

  h0_b->SetStats(0);
  h0_b->SetTitle("Jet spectra by flavor, PYTHIA+HYDJET 0-90%");
  //h0_b->SetTitle("Jet spectra by flavor, HYDJET 0-90%");
  //h0_b->SetTitle("Jet spectra by flavor, PYTHIA");
  //h0_b->GetYaxis()->SetTitle("1/N dN/d#font[52]{p}_{T} [GeV^{-1}]");
  h0_b->GetYaxis()->SetTitle("Entries");
  h0_b->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  h0_b->GetYaxis()->SetTitleSize(0.06);
  h0_b->GetXaxis()->SetTitleSize(0.06);
  h0_b->GetYaxis()->SetLabelSize(0.04);
  h0_b->GetXaxis()->SetLabelSize(0.04);
  h0_b->SetTitleSize(0.06);

	
  h0_b->GetYaxis()->SetRangeUser(1e-8,1e6);

	
	
  h0_b->Draw();
  h0_c->Draw("same");
  h0_u->Draw("same");
  h0_d->Draw("same");
  h0_s->Draw("same");
  h0_g->Draw("same");
  h0_ghost->Draw("same");
	
  //h0_noFlavor->Draw("same");


  TLegend *leg = new TLegend(0.7,0.7,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->AddEntry(h0_ghost,"#font[52]{x} jets");
  leg->AddEntry(h0_g,"#font[52]{g} jets");
  leg->AddEntry(h0_s,"#font[52]{s} jets");
  leg->AddEntry(h0_d,"#font[52]{d} jets");
  leg->AddEntry(h0_u,"#font[52]{u} jets");
  leg->AddEntry(h0_c,"#font[52]{c} jets");
  leg->AddEntry(h0_b,"#font[52]{b} jets");
  //leg->AddEntry(h0_noFlavor,"noFlavor jets");

  leg->Draw();

  /*	
	auto wf = TFile::Open("flavorSpectra/CC1.root","recreate");

	h0_b->Write();
	h0_c->Write();
	h0_u->Write();
	h0_d->Write();
	h0_s->Write();
	h0_g->Write();
	h0_ghost->Write();
	h0_noFlavor->Write();

	wf->Close();
  */


  // Create the stack
  THStack *hs = new THStack("hs","");
  TH1D *hsb, *hsc, *hsu, *hsd, *hss, *hsg, *hsx;
  hsb = (TH1D*) h0_b->Clone("hsb");
  hsc = (TH1D*) h0_c->Clone("hsc");
  hsu = (TH1D*) h0_u->Clone("hsu");
  hsd = (TH1D*) h0_d->Clone("hsd");
  hss = (TH1D*) h0_s->Clone("hss");
  hsg = (TH1D*) h0_g->Clone("hsg");
  hsx = (TH1D*) h0_ghost->Clone("hsx");

	
  hsb->Divide(h0_incl);
  hsc->Divide(h0_incl);
  hsu->Divide(h0_incl);
  hsd->Divide(h0_incl);
  hss->Divide(h0_incl);
  hsg->Divide(h0_incl);
  hsx->Divide(h0_incl);


	
  hs->Add(hsb);
  hs->Add(hsc);
  hs->Add(hsu);
  hs->Add(hsd);
  hs->Add(hss);
  hs->Add(hsg);
  hs->Add(hsx);

  TLegend *ls = new TLegend(0.71,0.5,0.98,0.9);
  ls->SetBorderSize(0);
  ls->SetTextSize(0.055);
  ls->AddEntry(hsx,"#font[52]{x} jets");
  ls->AddEntry(hsg,"#font[52]{g} jets");
  ls->AddEntry(hss,"#font[52]{s} jets");
  ls->AddEntry(hsd,"#font[52]{d} jets");
  ls->AddEntry(hsu,"#font[52]{u} jets");
  ls->AddEntry(hsc,"#font[52]{c} jets");
  ls->AddEntry(hsb,"#font[52]{b} jets");

  TCanvas *cs = new TCanvas("cs","cs",1000,700);
  cs->cd();
  TPad *ps = new TPad("ps","ps",0,0,1,1);
  ps->SetLeftMargin(0.2);
  ps->SetBottomMargin(0.2);
  ps->SetRightMargin(0.3);
  ps->Draw();
  ps->cd();

  hs->Draw("hist");
  hs->GetYaxis()->SetTitleSize(0.065);
  hs->GetXaxis()->SetTitleSize(0.065);
  hs->GetYaxis()->SetLabelSize(0.04);
  hs->GetXaxis()->SetLabelSize(0.04);
  hs->GetYaxis()->SetTitle("Fraction");
  hs->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  hs->GetXaxis()->SetRangeUser(0,500);
  //hs->GetYaxis()->SetRangeUser(0.,1.0);
  hs->SetMinimum(0.);
  hs->SetMaximum(1.0);

  //hs->SetTitle("refPartonFlavorForB");
  //hs->SetTitle("matchedPartonFlavor");


  ls->Draw();


  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.036);
  la->DrawLatexNDC(0.72,0.40,"PYTHIA+HYDJET 0-90%");
  //la->DrawLatexNDC(0.72,0.40,"HYDJET MinBias");
  //la->DrawLatexNDC(0.72,0.40,"PYTHIA");

  //la->DrawLatexNDC(0.72,0.35,"partonFlavor");
  la->DrawLatexNDC(0.72,0.35,"matchedPartonFlavor");
  //la->DrawLatexNDC(0.72,0.35,"refPartonFlavorForB");

  //la->DrawLatexNDC(0.72,0.30,"muon-tagged, #font[52]{p}_{T}^{#mu} > 7 GeV");

  //la->DrawLatexNDC(0.72,0.30,"refPartonFlavorForB = x");
  //la->DrawLatexNDC(0.72,0.30,"matchedPartonFlavor = x");
  //la->DrawLatexNDC(0.72,0.30,"#font[52]{x} jets removed");

















}
