

TH1D* stitchSamples_alt(TH1D *h_jetMB, TH1D *h_jet60, TH1D *h_jet80, TH1D *h_jet100,
			bool isPP, bool isPbPb){

  std::cout << "Stitching samples (alt)...\n";

  TH1D *h_return = (TH1D*) h_jet100->Clone("h_return");
  
  TH1D *h_jet80_scaled = (TH1D*) h_jet80->Clone("h_jet80_scaled");
  TH1D *h_jet60_scaled = (TH1D*) h_jet60->Clone("h_jet60_scaled");
  TH1D *h_jetMB_scaled = (TH1D*) h_jetMB->Clone("h_jetMB_scaled");

  h_jet80_scaled->Scale(2.2560173);
  h_jet60_scaled->Scale(5.7724389);

  double jetMB_pTmin = 60.;
  double jet60_pTmin = 100;
  double jet80_pTmin = 130;
  double jet100_pTmin = 200;
  double smallShift = 0.01;

  if(!isPP){
    jet60_pTmin = jet80_pTmin;
  }

  for(int i = 0; i < h_jet60->GetSize(); i++){
    double pT = h_jet60->GetBinCenter(i);
    if(pT < jet60_pTmin){
      h_return->SetBinContent(i,h_jetMB_scaled->GetBinContent(i));
      h_return->SetBinError(i,h_jetMB_scaled->GetBinError(i));
    }
    else if(pT > jet60_pTmin && pT < jet80_pTmin){
      h_return->SetBinContent(i,h_jet60_scaled->GetBinContent(i));
      h_return->SetBinError(i,h_jet60_scaled->GetBinError(i));
    }
    else if(pT > jet80_pTmin && pT < jet100_pTmin){
      h_return->SetBinContent(i,h_jet80_scaled->GetBinContent(i));
      h_return->SetBinError(i,h_jet80_scaled->GetBinError(i));
    }
    else if(pT > jet100_pTmin){
      h_return->SetBinContent(i,h_jet100->GetBinContent(i));
      h_return->SetBinError(i,h_jet100->GetBinError(i));
    }
    else{};
    
  }

  return h_return;
}


TH1D* stitchSamples(TH1D *h_jetMB, TH1D *h_jet60, TH1D *h_jet80, TH1D *h_jet100,
		    bool isPP, bool isPbPb){

  std::cout << "Stitching samples...\n";

  TH1D *h_return = (TH1D*) h_jet100->Clone("h_return");

  double jetMB_pTmin = 60.;
  double jet60_pTmin = 100;
  double jet80_pTmin = 150;
  double jet100_pTmin = 200;
  double smallShift = 0.01;

  if(!isPP){
    jet60_pTmin = jet80_pTmin;
  }

  double N_jet100 = h_jet100->Integral(h_jet100->FindBin(jet100_pTmin + smallShift),h_jet100->FindBin(500. - smallShift));
  double N_jet80 = h_jet80->Integral(h_jet80->FindBin(jet100_pTmin + smallShift),h_jet80->FindBin(500. - smallShift));
  double N_jet60 = h_jet60->Integral(h_jet60->FindBin(jet80_pTmin + smallShift),h_jet60->FindBin(jet100_pTmin - smallShift));
  double N_jetMB = h_jetMB->Integral(h_jetMB->FindBin(jet60_pTmin + smallShift),h_jetMB->FindBin(jet80_pTmin - smallShift));

  
  TH1D *h_jet80_scaled = (TH1D*) h_jet80->Clone("h_jet80_scaled");
  h_jet80_scaled->Scale(N_jet100 / N_jet80);
  std::cout << "Scaled jet80 by a factor F = " << N_jet100 / N_jet80 << "\n";

  double N_jet80_scaled = h_jet80_scaled->Integral(h_jet80_scaled->FindBin(jet80_pTmin + smallShift),h_jet80_scaled->FindBin(jet100_pTmin - smallShift));

  TH1D *h_jet60_scaled = (TH1D*) h_jet60->Clone("h_jet60_scaled");
  h_jet60_scaled->Scale(N_jet80_scaled / N_jet60);
  std::cout << "Scaled jet60 by a factor F = " << N_jet80_scaled / N_jet60 << "\n";
  
  double N_jet60_scaled = h_jet60_scaled->Integral(h_jet60_scaled->FindBin(jet60_pTmin + smallShift),h_jet60_scaled->FindBin(jet80_pTmin - smallShift));

  TH1D *h_jetMB_scaled = (TH1D*) h_jetMB->Clone("h_jetMB_scaled");
  h_jetMB_scaled->Scale(N_jet60_scaled / N_jetMB);
  std::cout << "Scaled jetMB by a factor F = " << N_jet60_scaled / N_jetMB << "\n";
  
 
  for(int i = 0; i < h_jet60->GetSize(); i++){
    double pT = h_jet60->GetBinCenter(i);
    if(pT < jet60_pTmin){
      h_return->SetBinContent(i,h_jetMB_scaled->GetBinContent(i));
      h_return->SetBinError(i,h_jetMB_scaled->GetBinError(i));
    }
    else if(pT > jet60_pTmin && pT < jet80_pTmin){
      h_return->SetBinContent(i,h_jet60_scaled->GetBinContent(i));
      h_return->SetBinError(i,h_jet60_scaled->GetBinError(i));
    }
    else if(pT > jet80_pTmin && pT < jet100_pTmin){
      h_return->SetBinContent(i,h_jet80_scaled->GetBinContent(i));
      h_return->SetBinError(i,h_jet80_scaled->GetBinError(i));
    }
    else if(pT > jet100_pTmin){
      h_return->SetBinContent(i,h_jet100->GetBinContent(i));
      h_return->SetBinError(i,h_jet100->GetBinError(i));
    }
    else{};
    
  }

  return h_return;
  
}




void stylizeHistograms(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  h1->SetMarkerColor(kBlack);
  h2->SetMarkerColor(kRed-4);
  h3->SetMarkerColor(kBlue-4);
  h4->SetMarkerColor(kGreen+2);
  
  h1->SetLineColor(kBlack);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kBlue-4);
  h4->SetLineColor(kGreen+2);
  
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  
}


void plotJetPt_stitch(){

  TLine *li = new TLine();

  TFile *file_pp_HighEGJet_jet60 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet60HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-10.root");
  TFile *file_pp_HighEGJet_jet80 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet80HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-10.root");
  TFile *file_pp_HighEGJet_jet100 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet100HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_WDecayFilter_2026-3-11.root");
  TFile *file_pp_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_WDecayFilter_2026-3-16.root");
  TFile *file_pp_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_MinBias_mu12_pTmu-14_tight_jetTrkMaxFilter_2025-10-15.root");
  


  TFile *file_PbPb_HardProbes_jet60 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet60HLT_mu12_pTmu-15to999_tight_WDecayFilter_2026-3-11.root");
  TFile *file_PbPb_HardProbes_jet80 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet80HLT_mu12_pTmu-15to999_tight_WDecayFilter_2026-4-8.root");
  TFile *file_PbPb_HardProbes_jet100 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet100HLT_mu12_pTmu-15to999_tight_WDecayFilter_2026-4-8.root");
  TFile *file_PbPb_SingleMuon = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15to999_tight_mu12TriggerEfficiencyCorrection_WDecayFilter_2026-4-9.root");
  TFile *file_PbPb_MinBias = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_MinBias_mu12_pTmu-15to999_tight_WDecayFilter_2026-4-8.root");



  TFile *file_PYTHIA_response = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-31.root");
  TFile *file_PH_response = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_2026-3-31.root");

  TH2D *H_ppMC, *H_C4MC, *H_C3MC, *H_C2MC, *H_C1MC;
  TH1D *h_unmatched_ppMC, *h_unmatched_C4MC, *h_unmatched_C3MC, *h_unmatched_C2MC, *h_unmatched_C1MC;

  file_PYTHIA_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H_ppMC);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",H_C4MC);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",H_C3MC);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H_C2MC);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",H_C1MC);

  file_PYTHIA_response->GetObject("h_unmatchedRecoJetPt_xJets",h_unmatched_ppMC);
  file_PH_response->GetObject("h_unmatchedRecoJetPt_xJets_C4",h_unmatched_C4MC);
  file_PH_response->GetObject("h_unmatchedRecoJetPt_xJets_C3",h_unmatched_C3MC);
  file_PH_response->GetObject("h_unmatchedRecoJetPt_xJets_C2",h_unmatched_C2MC);
  file_PH_response->GetObject("h_unmatchedRecoJetPt_xJets_C1",h_unmatched_C1MC);

  file_PYTHIA_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H_ppMC);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",H_C4MC);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",H_C3MC);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H_C2MC);
  file_PH_response->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",H_C1MC);

  TH1D *h_ppMC, *h_C4MC, *h_C3MC, *h_C2MC, *h_C1MC;

  // //// take ratio to reco
  h_ppMC = (TH1D*) H_ppMC->ProjectionX("h_ppMC");
  h_C4MC = (TH1D*) H_C4MC->ProjectionX("h_C4MC");
  h_C3MC = (TH1D*) H_C3MC->ProjectionX("h_C3MC");
  h_C2MC = (TH1D*) H_C2MC->ProjectionX("h_C2MC");
  h_C1MC = (TH1D*) H_C1MC->ProjectionX("h_C1MC");

  std::cout << "entries(C1, 2D) = " << H_C1MC->GetEntries() << "\n";
  std::cout << "entries(C1, unmatched) = " << h_unmatched_C1MC->GetEntries() << "\n";
  
  // // add unmatched jets
  // h_ppMC->Add(h_unmatched_ppMC);
  // h_C4MC->Add(h_unmatched_C4MC);
  // h_C3MC->Add(h_unmatched_C3MC);
  // h_C2MC->Add(h_unmatched_C2MC);
  // h_C1MC->Add(h_unmatched_C1MC);

  
  
  // ///// take ratio to PYTHIA gen
  // h_ppMC = (TH1D*) H_ppMC->ProjectionY("h_ppMC");
  // h_C4MC = (TH1D*) H_ppMC->ProjectionY("h_C4MC");
  // h_C3MC = (TH1D*) H_ppMC->ProjectionY("h_C3MC");
  // h_C2MC = (TH1D*) H_ppMC->ProjectionY("h_C2MC");
  // h_C1MC = (TH1D*) H_ppMC->ProjectionY("h_C1MC");



  // TH1D *bFrac_MinBias, *bFrac_DiJet;
  // file_bFrac_MinBias->GetObject("inclBFraction_pp",bFrac_MinBias);
  // file_bFrac_DiJet_jet60->GetObject("inclBFraction_pp",bFrac_DiJet);

  // stylizeHistograms(bFrac_MinBias,bFrac_DiJet);

  // bFrac_MinBias->Draw();
  // bFrac_DiJet->Draw("same");

  TH1D *h_pp, *h_C4, *h_C3, *h_C2, *h_C1;
  TH1D *h_pp_jetMB, *h_C4_jetMB, *h_C3_jetMB, *h_C2_jetMB, *h_C1_jetMB;
  TH1D *h_pp_jet60, *h_C4_jet60, *h_C3_jet60, *h_C2_jet60, *h_C1_jet60;
  TH1D *h_pp_jet80, *h_C4_jet80, *h_C3_jet80, *h_C2_jet80, *h_C1_jet80;
  TH1D *h_pp_jet100, *h_C4_jet100, *h_C3_jet100, *h_C2_jet100, *h_C1_jet100;

  file_pp_MinBias->GetObject("h_inclRecoJetPt",h_pp_jetMB);
  file_pp_HighEGJet_jet60->GetObject("h_inclRecoJetPt",h_pp_jet60);
  file_pp_HighEGJet_jet80->GetObject("h_inclRecoJetPt",h_pp_jet80);
  file_pp_HighEGJet_jet100->GetObject("h_inclRecoJetPt",h_pp_jet100);


  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C4",h_C4_jetMB);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C3",h_C3_jetMB);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C2",h_C2_jetMB);
  file_PbPb_MinBias->GetObject("h_inclRecoJetPt_C1",h_C1_jetMB);

  file_PbPb_HardProbes_jet60->GetObject("h_inclRecoJetPt_C4",h_C4_jet60);
  file_PbPb_HardProbes_jet60->GetObject("h_inclRecoJetPt_C3",h_C3_jet60);
  file_PbPb_HardProbes_jet60->GetObject("h_inclRecoJetPt_C2",h_C2_jet60);
  file_PbPb_HardProbes_jet60->GetObject("h_inclRecoJetPt_C1",h_C1_jet60);

  file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_C4",h_C4_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_C3",h_C3_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_C2",h_C2_jet80);
  file_PbPb_HardProbes_jet80->GetObject("h_inclRecoJetPt_C1",h_C1_jet80);

  file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_C4",h_C4_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_C3",h_C3_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_C2",h_C2_jet100);
  file_PbPb_HardProbes_jet100->GetObject("h_inclRecoJetPt_C1",h_C1_jet100);


  h_pp = (TH1D*) stitchSamples(h_pp_jetMB,h_pp_jet60,h_pp_jet80,h_pp_jet100,1,0);
  h_C4 = (TH1D*) stitchSamples(h_C4_jetMB,h_C4_jet60,h_C4_jet80,h_C4_jet100,0,1);
  h_C3 = (TH1D*) stitchSamples(h_C3_jetMB,h_C3_jet60,h_C3_jet80,h_C3_jet100,0,1);
  h_C2 = (TH1D*) stitchSamples(h_C2_jetMB,h_C2_jet60,h_C2_jet80,h_C2_jet100,0,1);
  h_C1 = (TH1D*) stitchSamples(h_C1_jetMB,h_C1_jet60,h_C1_jet80,h_C1_jet100,0,1);
  // h_C4 = (TH1D*) stitchSamples_alt(h_C4_jetMB,h_C4_jet60,h_C4_jet80,h_C4_jet100,0,1);
  // h_C3 = (TH1D*) stitchSamples_alt(h_C3_jetMB,h_C3_jet60,h_C3_jet80,h_C3_jet100,0,1);
  // h_C2 = (TH1D*) stitchSamples_alt(h_C2_jetMB,h_C2_jet60,h_C2_jet80,h_C2_jet100,0,1);
  // h_C1 = (TH1D*) stitchSamples_alt(h_C1_jetMB,h_C1_jet60,h_C1_jet80,h_C1_jet100,0,1);

  stylizeHistograms(h_pp_jetMB,h_pp_jet60,h_pp_jet80,h_pp_jet100);
  stylizeHistograms(h_C4_jetMB,h_C4_jet60,h_C4_jet80,h_C4_jet100);
  stylizeHistograms(h_C3_jetMB,h_C3_jet60,h_C3_jet80,h_C3_jet100);
  stylizeHistograms(h_C2_jetMB,h_C2_jet60,h_C2_jet80,h_C2_jet100);
  stylizeHistograms(h_C1_jetMB,h_C1_jet60,h_C1_jet80,h_C1_jet100);
  

  double leftMargin = 0.15;
  double bottomMargin = 0.15;
  double xmin = 50;
  double xmax = 300;
  double ymin = 0.2;
  double ymax = 8.E7;
  double legendXmin = 0.72;
  double legendXmax = 0.88;
  double legendYmin = 0.72;
  double legendYmax = 0.88;
  double legendTextSize = 0.038;
  TLegend *leg_pp_spectra = new TLegend(legendXmin,legendYmin,legendXmax,legendYmax);
  leg_pp_spectra->SetBorderSize(0);
  leg_pp_spectra->SetTextSize(legendTextSize);
  leg_pp_spectra->AddEntry(h_pp_jetMB,"MinBias","l");
  leg_pp_spectra->AddEntry(h_pp_jet60,"Jet60","l");
  leg_pp_spectra->AddEntry(h_pp_jet80,"Jet80","l");
  leg_pp_spectra->AddEntry(h_pp_jet100,"Jet100","l");

  
  /////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_pp_spectra = new TCanvas("canv_pp_spectra","canv_pp_spectra",700,700);
  canv_pp_spectra->cd();
  TPad *pad_pp_spectra = new TPad("pad_pp_spectra","pad_pp_spectra",0,0,1,1);
  pad_pp_spectra->SetLeftMargin(leftMargin);
  pad_pp_spectra->SetBottomMargin(bottomMargin);
  pad_pp_spectra->SetLogy();
  pad_pp_spectra->Draw();
  pad_pp_spectra->cd();
  h_pp_jetMB->SetTitle("pp");
  h_pp_jetMB->SetStats(0);
  h_pp_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_pp_jetMB->GetYaxis()->SetRangeUser(ymin,ymax);
  h_pp_jetMB->GetYaxis()->SetTitle("Entries");
  h_pp_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_pp_jetMB->Draw();
  h_pp_jet60->Draw("same");
  h_pp_jet80->Draw("same");
  h_pp_jet100->Draw("same");
  leg_pp_spectra->Draw();
  canv_pp_spectra->SaveAs("../../../figures/jetPt/stitch/jetPt_pp_spectra.pdf");

  TCanvas *canv_C4_spectra = new TCanvas("canv_C4_spectra","canv_C4_spectra",700,700);
  canv_C4_spectra->cd();
  TPad *pad_C4_spectra = new TPad("pad_C4_spectra","pad_C4_spectra",0,0,1,1);
  pad_C4_spectra->SetLeftMargin(leftMargin);
  pad_C4_spectra->SetBottomMargin(bottomMargin);
  pad_C4_spectra->SetLogy();
  pad_C4_spectra->Draw();
  pad_C4_spectra->cd();
  h_C4_jetMB->SetTitle("PbPb 50-80%");
  h_C4_jetMB->SetStats(0);
  h_C4_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C4_jetMB->GetYaxis()->SetTitle("Entries");
  h_C4_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C4_jetMB->Draw();
  h_C4_jet60->Draw("same");
  h_C4_jet80->Draw("same");
  h_C4_jet100->Draw("same");
  leg_pp_spectra->Draw();
  canv_C4_spectra->SaveAs("../../../figures/jetPt/stitch/jetPt_C4_spectra.pdf");
  

  TCanvas *canv_C3_spectra = new TCanvas("canv_C3_spectra","canv_C3_spectra",700,700);
  canv_C3_spectra->cd();
  TPad *pad_C3_spectra = new TPad("pad_C3_spectra","pad_C3_spectra",0,0,1,1);
  pad_C3_spectra->SetLeftMargin(leftMargin);
  pad_C3_spectra->SetBottomMargin(bottomMargin);
  pad_C3_spectra->SetLogy();
  pad_C3_spectra->Draw();
  pad_C3_spectra->cd();
  h_C3_jetMB->SetTitle("PbPb 30-50%");
  h_C3_jetMB->SetStats(0);
  h_C3_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C3_jetMB->GetYaxis()->SetTitle("Entries");
  h_C3_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C3_jetMB->Draw();
  h_C3_jet60->Draw("same");
  h_C3_jet80->Draw("same");
  h_C3_jet100->Draw("same");
  leg_pp_spectra->Draw();
  canv_C3_spectra->SaveAs("../../../figures/jetPt/stitch/jetPt_C3_spectra.pdf");
  
  TCanvas *canv_C2_spectra = new TCanvas("canv_C2_spectra","canv_C2_spectra",700,700);
  canv_C2_spectra->cd();
  TPad *pad_C2_spectra = new TPad("pad_C2_spectra","pad_C2_spectra",0,0,1,1);
  pad_C2_spectra->SetLeftMargin(leftMargin);
  pad_C2_spectra->SetBottomMargin(bottomMargin);
  pad_C2_spectra->SetLogy();
  pad_C2_spectra->Draw();
  pad_C2_spectra->cd();
  h_C2_jetMB->SetTitle("PbPb 10-30%");
  h_C2_jetMB->SetStats(0);
  h_C2_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C2_jetMB->GetYaxis()->SetTitle("Entries");
  h_C2_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C2_jetMB->Draw();
  h_C2_jet60->Draw("same");
  h_C2_jet80->Draw("same");
  h_C2_jet100->Draw("same");
  leg_pp_spectra->Draw();
  canv_C2_spectra->SaveAs("../../../figures/jetPt/stitch/jetPt_C2_spectra.pdf");

  TCanvas *canv_C1_spectra = new TCanvas("canv_C1_spectra","canv_C1_spectra",700,700);
  canv_C1_spectra->cd();
  TPad *pad_C1_spectra = new TPad("pad_C1_spectra","pad_C1_spectra",0,0,1,1);
  pad_C1_spectra->SetLeftMargin(leftMargin);
  pad_C1_spectra->SetBottomMargin(bottomMargin);
  pad_C1_spectra->SetLogy();
  pad_C1_spectra->Draw();
  pad_C1_spectra->cd();
  h_C1_jetMB->SetTitle("PbPb 0-10%");
  h_C1_jetMB->SetStats(0);
  h_C1_jetMB->GetXaxis()->SetRangeUser(xmin,xmax);
  h_C1_jetMB->GetYaxis()->SetTitle("Entries");
  h_C1_jetMB->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C1_jetMB->Draw();
  h_C1_jet60->Draw("same");
  h_C1_jet80->Draw("same");
  h_C1_jet100->Draw("same");
  leg_pp_spectra->Draw();
  canv_C1_spectra->SaveAs("../../../figures/jetPt/stitch/jetPt_C1_spectra.pdf");
  

  /////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_pp_stitch = new TCanvas("canv_pp_stitch","canv_pp_stitch",700,700);
  canv_pp_stitch->cd();
  TPad *pad_pp_stitch = new TPad("pad_pp_stitch","pad_pp_stitch",0,0,1,1);
  pad_pp_stitch->SetLeftMargin(leftMargin);
  pad_pp_stitch->SetBottomMargin(bottomMargin);
  pad_pp_stitch->SetLogy();
  pad_pp_stitch->Draw();
  pad_pp_stitch->cd();
  h_pp->SetTitle("pp");
  h_pp->SetStats(0);
  h_pp->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_pp->GetYaxis()->SetRangeUser(ymin,ymax);
  h_pp->GetYaxis()->SetTitle("Scaled Entries");
  h_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_pp->Draw();
  canv_pp_stitch->SaveAs("../../../figures/jetPt/stitch/jetPt_pp_stitch.pdf");

  TCanvas *canv_C4_stitch = new TCanvas("canv_C4_stitch","canv_C4_stitch",700,700);
  canv_C4_stitch->cd();
  TPad *pad_C4_stitch = new TPad("pad_C4_stitch","pad_C4_stitch",0,0,1,1);
  pad_C4_stitch->SetLeftMargin(leftMargin);
  pad_C4_stitch->SetBottomMargin(bottomMargin);
  pad_C4_stitch->SetLogy();
  pad_C4_stitch->Draw();
  pad_C4_stitch->cd();
  h_C4->SetTitle("PbPb 50-80%");
  h_C4->SetStats(0);
  h_C4->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C4->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C4->GetYaxis()->SetTitle("Scaled Entries");
  h_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C4->Draw();
  canv_C4_stitch->SaveAs("../../../figures/jetPt/stitch/jetPt_C4_stitch.pdf");

  TCanvas *canv_C3_stitch = new TCanvas("canv_C3_stitch","canv_C3_stitch",700,700);
  canv_C3_stitch->cd();
  TPad *pad_C3_stitch = new TPad("pad_C3_stitch","pad_C3_stitch",0,0,1,1);
  pad_C3_stitch->SetLeftMargin(leftMargin);
  pad_C3_stitch->SetBottomMargin(bottomMargin);
  pad_C3_stitch->SetLogy();
  pad_C3_stitch->Draw();
  pad_C3_stitch->cd();
  h_C3->SetTitle("PbPb 30-50%");
  h_C3->SetStats(0);
  h_C3->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C3->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C3->GetYaxis()->SetTitle("Scaled Entries");
  h_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C3->Draw();
  canv_C3_stitch->SaveAs("../../../figures/jetPt/stitch/jetPt_C3_stitch.pdf");

  TCanvas *canv_C2_stitch = new TCanvas("canv_C2_stitch","canv_C2_stitch",700,700);
  canv_C2_stitch->cd();
  TPad *pad_C2_stitch = new TPad("pad_C2_stitch","pad_C2_stitch",0,0,1,1);
  pad_C2_stitch->SetLeftMargin(leftMargin);
  pad_C2_stitch->SetBottomMargin(bottomMargin);
  pad_C2_stitch->SetLogy();
  pad_C2_stitch->Draw();
  pad_C2_stitch->cd();
  h_C2->SetTitle("PbPb 10-30%");
  h_C2->SetStats(0);
  h_C2->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C2->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C2->GetYaxis()->SetTitle("Scaled Entries");
  h_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C2->Draw();
  canv_C2_stitch->SaveAs("../../../figures/jetPt/stitch/jetPt_C2_stitch.pdf");

  TCanvas *canv_C1_stitch = new TCanvas("canv_C1_stitch","canv_C1_stitch",700,700);
  canv_C1_stitch->cd();
  TPad *pad_C1_stitch = new TPad("pad_C1_stitch","pad_C1_stitch",0,0,1,1);
  pad_C1_stitch->SetLeftMargin(leftMargin);
  pad_C1_stitch->SetBottomMargin(bottomMargin);
  pad_C1_stitch->SetLogy();
  pad_C1_stitch->Draw();
  pad_C1_stitch->cd();
  h_C1->SetTitle("PbPb 0-10%");
  h_C1->SetStats(0);
  h_C1->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C1->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C1->GetYaxis()->SetTitle("Scaled Entries");
  h_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  h_C1->Draw();
  canv_C1_stitch->SaveAs("../../../figures/jetPt/stitch/jetPt_C1_stitch.pdf");

  /////////////////////////////////////////////////////////////////////////////////////////

  TLegend *leg_compareToMC = new TLegend(0.70,0.70,0.84,0.84);
  leg_compareToMC->SetBorderSize(0);
  leg_compareToMC->SetTextSize(0.055);
  leg_compareToMC->AddEntry(h_pp,"Data");
  leg_compareToMC->AddEntry(h_ppMC,"MC");
  
  TCanvas *canv_pp_compareToMC = new TCanvas("canv_pp_compareToMC","canv_pp_compareToMC",700,700);
  canv_pp_compareToMC->cd();
  TPad *pad_pp_compareToMC_upper = new TPad("pad_pp_compareToMC_upper","pad_pp_compareToMC_upper",0,0.4,1,1);
  TPad *pad_pp_compareToMC_lower = new TPad("pad_pp_compareToMC_lower","pad_pp_compareToMC_lower",0,0,1,0.4);
  pad_pp_compareToMC_upper->SetLeftMargin(leftMargin);
  pad_pp_compareToMC_lower->SetLeftMargin(leftMargin);
  pad_pp_compareToMC_upper->SetBottomMargin(0);
  pad_pp_compareToMC_lower->SetBottomMargin(bottomMargin);
  pad_pp_compareToMC_upper->SetTopMargin(bottomMargin);
  pad_pp_compareToMC_lower->SetTopMargin(0);
  pad_pp_compareToMC_upper->SetLogy();
  pad_pp_compareToMC_upper->Draw();
  pad_pp_compareToMC_lower->Draw();
  pad_pp_compareToMC_upper->cd();
  h_pp->SetTitle("pp");
  h_pp->SetStats(0);
  h_pp->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_pp->GetYaxis()->SetRangeUser(ymin,ymax);
  h_pp->GetYaxis()->SetTitle("Scaled Entries");
  h_pp->SetLineWidth(2);
  h_ppMC->SetLineWidth(2);
  h_ppMC->SetLineColor(kRed-4);
  h_pp->SetLineColor(kBlue-4);
  h_pp->Draw();
  TH1D *h_ppMC_scaled = (TH1D*) h_ppMC->Clone("h_ppMC");
  h_ppMC_scaled->Scale(h_pp->Integral(h_pp->FindBin(200),h_pp->FindBin(500)) / h_ppMC->Integral(h_ppMC->FindBin(200),h_ppMC->FindBin(500)));  // normalize by high pT
  h_ppMC_scaled->Draw("same");
  leg_compareToMC->Draw();
  pad_pp_compareToMC_lower->cd();
  TH1D *r_pp = (TH1D*) h_pp->Clone("r_pp");
  r_pp->Divide(h_pp,h_ppMC_scaled,1,1,"");
  r_pp->SetTitle("");
  r_pp->GetXaxis()->SetTitleSize(0.065);
  r_pp->GetXaxis()->SetLabelSize(0.057);
  r_pp->GetYaxis()->SetTitleSize(0.065);
  r_pp->GetYaxis()->SetLabelSize(0.057);
  r_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_pp->GetYaxis()->SetTitle("Data / MC");
  r_pp->GetYaxis()->SetRangeUser(0,2);
  r_pp->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_pp_compareToMC->SaveAs("../../../figures/jetPt/stitch/jetPt_pp_compareToMC.pdf");


  TCanvas *canv_C4_compareToMC = new TCanvas("canv_C4_compareToMC","canv_C4_compareToMC",700,700);
  canv_C4_compareToMC->cd();
  TPad *pad_C4_compareToMC_upper = new TPad("pad_C4_compareToMC_upper","pad_C4_compareToMC_upper",0,0.4,1,1);
  TPad *pad_C4_compareToMC_lower = new TPad("pad_C4_compareToMC_lower","pad_C4_compareToMC_lower",0,0,1,0.4);
  pad_C4_compareToMC_upper->SetLeftMargin(leftMargin);
  pad_C4_compareToMC_lower->SetLeftMargin(leftMargin);
  pad_C4_compareToMC_upper->SetBottomMargin(0);
  pad_C4_compareToMC_lower->SetBottomMargin(bottomMargin);
  pad_C4_compareToMC_upper->SetTopMargin(bottomMargin);
  pad_C4_compareToMC_lower->SetTopMargin(0);
  pad_C4_compareToMC_upper->SetLogy();
  pad_C4_compareToMC_upper->Draw();
  pad_C4_compareToMC_lower->Draw();
  pad_C4_compareToMC_upper->cd();
  h_C4->SetTitle("PbPb 50-80%");
  h_C4->SetStats(0);
  h_C4->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C4->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C4->GetYaxis()->SetTitle("Scaled Entries");
  h_C4->SetLineWidth(2);
  h_C4MC->SetLineWidth(2);
  h_C4MC->SetLineColor(kRed-4);
  h_C4->SetLineColor(kBlue-4);
  h_C4->Draw();
  TH1D *h_C4MC_scaled = (TH1D*) h_C4MC->Clone("h_C4MC");
  h_C4MC_scaled->Scale(h_C4->Integral(h_C4->FindBin(200),h_C4->FindBin(500)) / h_C4MC->Integral(h_C4MC->FindBin(200),h_C4MC->FindBin(500)));  // normalize by high pT
  h_C4MC_scaled->Draw("same");
  leg_compareToMC->Draw();
  pad_C4_compareToMC_lower->cd();
  TH1D *r_C4 = (TH1D*) h_C4->Clone("r_C4");
  r_C4->Divide(h_C4,h_C4MC_scaled,1,1,"");
  r_C4->SetTitle("");
  r_C4->GetXaxis()->SetTitleSize(0.065);
  r_C4->GetXaxis()->SetLabelSize(0.057);
  r_C4->GetYaxis()->SetTitleSize(0.065);
  r_C4->GetYaxis()->SetLabelSize(0.057);
  r_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C4->GetYaxis()->SetTitle("Data / MC");
  r_C4->GetYaxis()->SetRangeUser(0,2);
  r_C4->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C4_compareToMC->SaveAs("../../../figures/jetPt/stitch/jetPt_C4_compareToMC.pdf");

  TCanvas *canv_C3_compareToMC = new TCanvas("canv_C3_compareToMC","canv_C3_compareToMC",700,700);
  canv_C3_compareToMC->cd();
  TPad *pad_C3_compareToMC_upper = new TPad("pad_C3_compareToMC_upper","pad_C3_compareToMC_upper",0,0.4,1,1);
  TPad *pad_C3_compareToMC_lower = new TPad("pad_C3_compareToMC_lower","pad_C3_compareToMC_lower",0,0,1,0.4);
  pad_C3_compareToMC_upper->SetLeftMargin(leftMargin);
  pad_C3_compareToMC_lower->SetLeftMargin(leftMargin);
  pad_C3_compareToMC_upper->SetBottomMargin(0);
  pad_C3_compareToMC_lower->SetBottomMargin(bottomMargin);
  pad_C3_compareToMC_upper->SetTopMargin(bottomMargin);
  pad_C3_compareToMC_lower->SetTopMargin(0);
  pad_C3_compareToMC_upper->SetLogy();
  pad_C3_compareToMC_upper->Draw();
  pad_C3_compareToMC_lower->Draw();
  pad_C3_compareToMC_upper->cd();
  h_C3->SetTitle("PbPb 30-50%");
  h_C3->SetStats(0);
  h_C3->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C3->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C3->GetYaxis()->SetTitle("Scaled Entries");
  h_C3->SetLineWidth(2);
  h_C3MC->SetLineWidth(2);
  h_C3MC->SetLineColor(kRed-4);
  h_C3->SetLineColor(kBlue-4);
  h_C3->Draw();
  TH1D *h_C3MC_scaled = (TH1D*) h_C3MC->Clone("h_C3MC");
  h_C3MC_scaled->Scale(h_C3->Integral(h_C3->FindBin(200),h_C3->FindBin(500)) / h_C3MC->Integral(h_C3MC->FindBin(200),h_C3MC->FindBin(500)));  // normalize by high pT
  h_C3MC_scaled->Draw("same");
  leg_compareToMC->Draw();
  pad_C3_compareToMC_lower->cd();
  TH1D *r_C3 = (TH1D*) h_C3->Clone("r_C3");
  r_C3->Divide(h_C3,h_C3MC_scaled,1,1,"");
  r_C3->SetTitle("");
  r_C3->GetXaxis()->SetTitleSize(0.065);
  r_C3->GetXaxis()->SetLabelSize(0.057);
  r_C3->GetYaxis()->SetTitleSize(0.065);
  r_C3->GetYaxis()->SetLabelSize(0.057);
  r_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C3->GetYaxis()->SetTitle("Data / MC");
  r_C3->GetYaxis()->SetRangeUser(0,2);
  r_C3->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C3_compareToMC->SaveAs("../../../figures/jetPt/stitch/jetPt_C3_compareToMC.pdf");

  TCanvas *canv_C2_compareToMC = new TCanvas("canv_C2_compareToMC","canv_C2_compareToMC",700,700);
  canv_C2_compareToMC->cd();
  TPad *pad_C2_compareToMC_upper = new TPad("pad_C2_compareToMC_upper","pad_C2_compareToMC_upper",0,0.4,1,1);
  TPad *pad_C2_compareToMC_lower = new TPad("pad_C2_compareToMC_lower","pad_C2_compareToMC_lower",0,0,1,0.4);
  pad_C2_compareToMC_upper->SetLeftMargin(leftMargin);
  pad_C2_compareToMC_lower->SetLeftMargin(leftMargin);
  pad_C2_compareToMC_upper->SetBottomMargin(0);
  pad_C2_compareToMC_lower->SetBottomMargin(bottomMargin);
  pad_C2_compareToMC_upper->SetTopMargin(bottomMargin);
  pad_C2_compareToMC_lower->SetTopMargin(0);
  pad_C2_compareToMC_upper->SetLogy();
  pad_C2_compareToMC_upper->Draw();
  pad_C2_compareToMC_lower->Draw();
  pad_C2_compareToMC_upper->cd();
  h_C2->SetTitle("PbPb 10-30%");
  h_C2->SetStats(0);
  h_C2->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C2->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C2->GetYaxis()->SetTitle("Scaled Entries");
  h_C2->SetLineWidth(2);
  h_C2MC->SetLineWidth(2);
  h_C2MC->SetLineColor(kRed-4);
  h_C2->SetLineColor(kBlue-4);
  h_C2->Draw();
  TH1D *h_C2MC_scaled = (TH1D*) h_C2MC->Clone("h_C2MC");
  h_C2MC_scaled->Scale(h_C2->Integral(h_C2->FindBin(200),h_C2->FindBin(500)) / h_C2MC->Integral(h_C2MC->FindBin(200),h_C2MC->FindBin(500)));  // normalize by high pT
  h_C2MC_scaled->Draw("same");
  leg_compareToMC->Draw();
  pad_C2_compareToMC_lower->cd();
  TH1D *r_C2 = (TH1D*) h_C2->Clone("r_C2");
  r_C2->Divide(h_C2,h_C2MC_scaled,1,1,"");
  r_C2->SetTitle("");
  r_C2->GetXaxis()->SetTitleSize(0.065);
  r_C2->GetXaxis()->SetLabelSize(0.057);
  r_C2->GetYaxis()->SetTitleSize(0.065);
  r_C2->GetYaxis()->SetLabelSize(0.057);
  r_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C2->GetYaxis()->SetTitle("Data / MC");
  r_C2->GetYaxis()->SetRangeUser(0,2);
  r_C2->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C2_compareToMC->SaveAs("../../../figures/jetPt/stitch/jetPt_C2_compareToMC.pdf");

  TCanvas *canv_C1_compareToMC = new TCanvas("canv_C1_compareToMC","canv_C1_compareToMC",700,700);
  canv_C1_compareToMC->cd();
  TPad *pad_C1_compareToMC_upper = new TPad("pad_C1_compareToMC_upper","pad_C1_compareToMC_upper",0,0.4,1,1);
  TPad *pad_C1_compareToMC_lower = new TPad("pad_C1_compareToMC_lower","pad_C1_compareToMC_lower",0,0,1,0.4);
  pad_C1_compareToMC_upper->SetLeftMargin(leftMargin);
  pad_C1_compareToMC_lower->SetLeftMargin(leftMargin);
  pad_C1_compareToMC_upper->SetBottomMargin(0);
  pad_C1_compareToMC_lower->SetBottomMargin(bottomMargin);
  pad_C1_compareToMC_upper->SetTopMargin(bottomMargin);
  pad_C1_compareToMC_lower->SetTopMargin(0);
  pad_C1_compareToMC_upper->SetLogy();
  pad_C1_compareToMC_upper->Draw();
  pad_C1_compareToMC_lower->Draw();
  pad_C1_compareToMC_upper->cd();
  h_C1->SetTitle("PbPb 0-10%");
  h_C1->SetStats(0);
  h_C1->GetXaxis()->SetRangeUser(xmin,xmax);
  //h_C1->GetYaxis()->SetRangeUser(ymin,ymax);
  h_C1->GetYaxis()->SetTitle("Scaled Entries");
  h_C1->SetLineWidth(2);
  h_C1MC->SetLineWidth(2);
  h_C1MC->SetLineColor(kRed-4);
  h_C1->SetLineColor(kBlue-4);
  h_C1->Draw();
  TH1D *h_C1MC_scaled = (TH1D*) h_C1MC->Clone("h_C1MC");
  h_C1MC_scaled->Scale(h_C1->Integral(h_C1->FindBin(200),h_C1->FindBin(500)) / h_C1MC->Integral(h_C1MC->FindBin(200),h_C1MC->FindBin(500)));  // normalize by high pT
  h_C1MC_scaled->Draw("same");
  leg_compareToMC->Draw();
  pad_C1_compareToMC_lower->cd();
  TH1D *r_C1 = (TH1D*) h_C1->Clone("r_C1");
  r_C1->Divide(h_C1,h_C1MC_scaled,1,1,"");
  r_C1->SetTitle("");
  r_C1->GetXaxis()->SetTitleSize(0.065);
  r_C1->GetXaxis()->SetLabelSize(0.057);
  r_C1->GetYaxis()->SetTitleSize(0.065);
  r_C1->GetYaxis()->SetLabelSize(0.057);
  r_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C1->GetYaxis()->SetTitle("Data / MC");
  r_C1->GetYaxis()->SetRangeUser(0,2);
  r_C1->Draw();
  li->SetLineStyle(7);
  li->DrawLine(50,1,300,1);
  canv_C1_compareToMC->SaveAs("../../../figures/jetPt/stitch/jetPt_C1_compareToMC.pdf");

}
