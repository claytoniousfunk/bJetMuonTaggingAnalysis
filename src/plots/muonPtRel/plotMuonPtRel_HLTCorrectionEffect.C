
void stylizeHistograms(TH1D *h1, TH1D *h2){

  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);
  
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
    
}


void plotMuonPtRel_HLTCorrectionEffect(double jetPtLow = 80,
				       double jetPtHigh = 100){

  TFile *f_pp_noCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15_tight_jetTrkMaxFilter_2026-2-10.root");
  TFile *f_pp_wCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15_tight_mu12TriggerEfficiencyCorrection_jetTrkMaxFilter_2026-2-12.root");

  TFile *f_PYTHIA_noCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-30_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35_2026-1-13.root");
  TFile *f_PYTHIA_wCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-30_mu12_pTmu-15_tight_mu12TriggerEfficiencyCorrection_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-2-11.root");

  TFile *f_PbPb_noCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15_tight_WDecayFilter_2026-1-13.root");
  TFile *f_PbPb_wCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15_tight_mu12TriggerEfficiencyCorrection_WDecayFilter_2026-2-12.root");

  TFile *f_PH_noCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-30_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_leadingXjetDumpFilter_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_WDecayFilter_weightCut_2026-1-15.root");
  TFile *f_PH_wCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-30_mu12_pTmu-15_tight_mu12TriggerEfficiencyCorrection_vzReweight_hiBinReweight_hiBinShift-10_leadingXjetDumpFilter_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_WDecayFilter_weightCut_2026-2-12.root");


  TH2D *H_pp_MC_noCorr, *H_pp_MC_wCorr;
  TH2D *H_C4_MC_noCorr, *H_C4_MC_wCorr;
  TH2D *H_C3_MC_noCorr, *H_C3_MC_wCorr;
  TH2D *H_C2_MC_noCorr, *H_C2_MC_wCorr;
  TH2D *H_C1_MC_noCorr, *H_C1_MC_wCorr;

  TH2D *H_pp_DATA_noCorr, *H_pp_DATA_wCorr;
  TH2D *H_C4_DATA_noCorr, *H_C4_DATA_wCorr;
  TH2D *H_C3_DATA_noCorr, *H_C3_DATA_wCorr;
  TH2D *H_C2_DATA_noCorr, *H_C2_DATA_wCorr;
  TH2D *H_C1_DATA_noCorr, *H_C1_DATA_wCorr;

  TH1D *h_pp_MC_noCorr, *h_pp_MC_wCorr;
  TH1D *h_C4_MC_noCorr, *h_C4_MC_wCorr;
  TH1D *h_C3_MC_noCorr, *h_C3_MC_wCorr;
  TH1D *h_C2_MC_noCorr, *h_C2_MC_wCorr;
  TH1D *h_C1_MC_noCorr, *h_C1_MC_wCorr;

  TH1D *h_pp_DATA_noCorr, *h_pp_DATA_wCorr;
  TH1D *h_C4_DATA_noCorr, *h_C4_DATA_wCorr;
  TH1D *h_C3_DATA_noCorr, *h_C3_DATA_wCorr;
  TH1D *h_C2_DATA_noCorr, *h_C2_DATA_wCorr;
  TH1D *h_C1_DATA_noCorr, *h_C1_DATA_wCorr;

  f_pp_noCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn",H_pp_DATA_noCorr);
  f_pp_wCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn",H_pp_DATA_wCorr);
  
  f_PYTHIA_noCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_T0",H_pp_MC_noCorr);
  f_PYTHIA_wCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_T0",H_pp_MC_wCorr);

  f_PbPb_noCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C4",H_C4_DATA_noCorr);
  f_PbPb_wCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C4",H_C4_DATA_wCorr);

  f_PbPb_noCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C3",H_C3_DATA_noCorr);
  f_PbPb_wCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C3",H_C3_DATA_wCorr);

  f_PbPb_noCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C2",H_C2_DATA_noCorr);
  f_PbPb_wCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C2",H_C2_DATA_wCorr);

  f_PbPb_noCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C1",H_C1_DATA_noCorr);
  f_PbPb_wCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C1",H_C1_DATA_wCorr); 

  f_PH_noCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C4T0",H_C4_MC_noCorr);
  f_PH_wCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C4T0",H_C4_MC_wCorr);

  f_PH_noCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C3T0",H_C3_MC_noCorr);
  f_PH_wCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C3T0",H_C3_MC_wCorr);

  f_PH_noCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C2T0",H_C2_MC_noCorr);
  f_PH_wCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C2T0",H_C2_MC_wCorr);

  f_PH_noCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C1T0",H_C1_MC_noCorr);
  f_PH_wCorr->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C1T0",H_C1_MC_wCorr);
  

  

  TH1D *binFinder = H_pp_DATA_noCorr->ProjectionY();
  double ss = 0.01;
  
  h_pp_DATA_noCorr = (TH1D*) H_pp_DATA_noCorr->ProjectionX("h_pp_DATA_noCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  h_pp_DATA_wCorr = (TH1D*) H_pp_DATA_wCorr->ProjectionX("h_pp_DATA_wCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));

  h_pp_MC_noCorr = (TH1D*) H_pp_MC_noCorr->ProjectionX("h_pp_MC_noCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  h_pp_MC_wCorr = (TH1D*) H_pp_MC_wCorr->ProjectionX("h_pp_MC_wCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));

  h_C4_MC_noCorr = (TH1D*) H_C4_MC_noCorr->ProjectionX("h_C4_MC_noCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  h_C4_MC_wCorr = (TH1D*) H_C4_MC_wCorr->ProjectionX("h_C4_MC_wCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));

  h_C4_DATA_noCorr = (TH1D*) H_C4_DATA_noCorr->ProjectionX("h_C4_DATA_noCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  h_C4_DATA_wCorr = (TH1D*) H_C4_DATA_wCorr->ProjectionX("h_C4_DATA_wCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));

  h_C3_MC_noCorr = (TH1D*) H_C3_MC_noCorr->ProjectionX("h_C3_MC_noCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  h_C3_MC_wCorr = (TH1D*) H_C3_MC_wCorr->ProjectionX("h_C3_MC_wCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));

  h_C3_DATA_noCorr = (TH1D*) H_C3_DATA_noCorr->ProjectionX("h_C3_DATA_noCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  h_C3_DATA_wCorr = (TH1D*) H_C3_DATA_wCorr->ProjectionX("h_C3_DATA_wCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));

  h_C2_MC_noCorr = (TH1D*) H_C2_MC_noCorr->ProjectionX("h_C2_MC_noCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  h_C2_MC_wCorr = (TH1D*) H_C2_MC_wCorr->ProjectionX("h_C2_MC_wCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));

  h_C2_DATA_noCorr = (TH1D*) H_C2_DATA_noCorr->ProjectionX("h_C2_DATA_noCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  h_C2_DATA_wCorr = (TH1D*) H_C2_DATA_wCorr->ProjectionX("h_C2_DATA_wCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));

  h_C1_MC_noCorr = (TH1D*) H_C1_MC_noCorr->ProjectionX("h_C1_MC_noCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  h_C1_MC_wCorr = (TH1D*) H_C1_MC_wCorr->ProjectionX("h_C1_MC_wCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));

  h_C1_DATA_noCorr = (TH1D*) H_C1_DATA_noCorr->ProjectionX("h_C1_DATA_noCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  h_C1_DATA_wCorr = (TH1D*) H_C1_DATA_wCorr->ProjectionX("h_C1_DATA_wCorr",binFinder->FindBin(jetPtLow + ss),binFinder->FindBin(jetPtHigh - ss));
  

  



  
  

  






  stylizeHistograms(h_pp_MC_noCorr, h_pp_MC_wCorr);
  stylizeHistograms(h_pp_DATA_noCorr, h_pp_DATA_wCorr);
  stylizeHistograms(h_C4_MC_noCorr, h_C4_MC_wCorr);
  stylizeHistograms(h_C4_DATA_noCorr, h_C4_DATA_wCorr);
  stylizeHistograms(h_C3_MC_noCorr, h_C3_MC_wCorr);
  stylizeHistograms(h_C3_DATA_noCorr, h_C3_DATA_wCorr);
  stylizeHistograms(h_C2_MC_noCorr, h_C2_MC_wCorr);
  stylizeHistograms(h_C2_DATA_noCorr, h_C2_DATA_wCorr);
  stylizeHistograms(h_C1_MC_noCorr, h_C1_MC_wCorr);
  stylizeHistograms(h_C1_DATA_noCorr, h_C1_DATA_wCorr);





  TH1D *r_pp_MC = (TH1D*) h_pp_MC_wCorr->Clone("r_pp_MC");
  r_pp_MC->Divide(h_pp_MC_wCorr,h_pp_MC_noCorr,1,1,"B");

  TH1D *r_pp_DATA = (TH1D*) h_pp_DATA_wCorr->Clone("r_pp_DATA");
  r_pp_DATA->Divide(h_pp_DATA_wCorr,h_pp_DATA_noCorr,1,1,"B");

  TH1D *r_C4_MC = (TH1D*) h_C4_MC_wCorr->Clone("r_C4_MC");
  r_C4_MC->Divide(h_C4_MC_wCorr,h_C4_MC_noCorr,1,1,"B");

  TH1D *r_C4_DATA = (TH1D*) h_C4_DATA_wCorr->Clone("r_C4_DATA");
  r_C4_DATA->Divide(h_C4_DATA_wCorr,h_C4_DATA_noCorr,1,1,"B");

  TH1D *r_C3_MC = (TH1D*) h_C3_MC_wCorr->Clone("r_C3_MC");
  r_C3_MC->Divide(h_C3_MC_wCorr,h_C3_MC_noCorr,1,1,"B");

  TH1D *r_C3_DATA = (TH1D*) h_C3_DATA_wCorr->Clone("r_C3_DATA");
  r_C3_DATA->Divide(h_C3_DATA_wCorr,h_C3_DATA_noCorr,1,1,"B");

  TH1D *r_C2_MC = (TH1D*) h_C2_MC_wCorr->Clone("r_C2_MC");
  r_C2_MC->Divide(h_C2_MC_wCorr,h_C2_MC_noCorr,1,1,"B");

  TH1D *r_C2_DATA = (TH1D*) h_C2_DATA_wCorr->Clone("r_C2_DATA");
  r_C2_DATA->Divide(h_C2_DATA_wCorr,h_C2_DATA_noCorr,1,1,"B");

  TH1D *r_C1_MC = (TH1D*) h_C1_MC_wCorr->Clone("r_C1_MC");
  r_C1_MC->Divide(h_C1_MC_wCorr,h_C1_MC_noCorr,1,1,"B");

  TH1D *r_C1_DATA = (TH1D*) h_C1_DATA_wCorr->Clone("r_C1_DATA");
  r_C1_DATA->Divide(h_C1_DATA_wCorr,h_C1_DATA_noCorr,1,1,"B");




  

  double titleSize = 0.05;
  double xTitleSize = 0.045;
  double xLabelSize = 0.040;
  double yTitleSize = xTitleSize;
  double yLabelSize = yLabelSize;

  TLine *li = new TLine();
  li->SetLineStyle(7);

  TLatex *la = new TLatex();
  la->SetTextSize(xTitleSize);
  
    

  ///////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_pp_MC = new TCanvas("canv_pp_MC","canv_pp_MC",700,700);
  canv_pp_MC->cd();
  TPad *pad_pp_MC_upper = new TPad("pad_pp_MC_upper","pad_pp_MC_upper",0,0.4,1,1);
  TPad *pad_pp_MC_lower = new TPad("pad_pp_MC_lower","pad_pp_MC_lower",0,0,1,0.4);
  pad_pp_MC_upper->SetLeftMargin(0.18);
  pad_pp_MC_lower->SetLeftMargin(0.18);
  pad_pp_MC_upper->SetBottomMargin(0);
  pad_pp_MC_lower->SetBottomMargin(0.3);
  pad_pp_MC_lower->SetTopMargin(0);
  pad_pp_MC_upper->Draw("hist");
  pad_pp_MC_lower->Draw("hist");
  pad_pp_MC_upper->cd();

  h_pp_MC_wCorr->SetTitleSize(titleSize);
  h_pp_MC_wCorr->SetTitle("pp MC");

  h_pp_MC_wCorr->GetYaxis()->SetTitleSize(xTitleSize);
  h_pp_MC_wCorr->GetYaxis()->SetLabelSize(xLabelSize);
  h_pp_MC_wCorr->GetYaxis()->SetTitle("Entries");
  h_pp_MC_wCorr->SetStats(0);
    
  h_pp_MC_wCorr->Draw("hist");
  h_pp_MC_noCorr->Draw("hist same");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.5,"no correction");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.43,"with correction");

  pad_pp_MC_lower->cd();
  
  r_pp_MC->GetXaxis()->SetTitleSize(2.2*xTitleSize);
  r_pp_MC->GetXaxis()->SetLabelSize(2.2*xLabelSize);
  r_pp_MC->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r_pp_MC->GetYaxis()->SetTitleSize(1.8*xTitleSize);
  r_pp_MC->GetYaxis()->SetLabelSize(1.8*xLabelSize);
  r_pp_MC->GetYaxis()->SetTitle("Ratio");
  r_pp_MC->GetYaxis()->SetTitleOffset(0.6);
  r_pp_MC->GetYaxis()->SetRangeUser(0.76,1.24);
  
  r_pp_MC->SetTitle("");
  r_pp_MC->SetStats(0);
  r_pp_MC->Draw("hist");
  li->DrawLine(0,1,10,1);

  ///////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_pp_DATA = new TCanvas("canv_pp_DATA","canv_pp_DATA",700,700);
  canv_pp_DATA->cd();
  TPad *pad_pp_DATA_upper = new TPad("pad_pp_DATA_upper","pad_pp_DATA_upper",0,0.4,1,1);
  TPad *pad_pp_DATA_lower = new TPad("pad_pp_DATA_lower","pad_pp_DATA_lower",0,0,1,0.4);
  pad_pp_DATA_upper->SetLeftMargin(0.18);
  pad_pp_DATA_lower->SetLeftMargin(0.18);
  pad_pp_DATA_upper->SetBottomMargin(0);
  pad_pp_DATA_lower->SetBottomMargin(0.3);
  pad_pp_DATA_lower->SetTopMargin(0);
  pad_pp_DATA_upper->Draw("hist");
  pad_pp_DATA_lower->Draw("hist");
  pad_pp_DATA_upper->cd();

  h_pp_DATA_wCorr->SetTitleSize(titleSize);
  h_pp_DATA_wCorr->SetTitle("pp Data");

  h_pp_DATA_wCorr->GetYaxis()->SetTitleSize(xTitleSize);
  h_pp_DATA_wCorr->GetYaxis()->SetLabelSize(xLabelSize);
  h_pp_DATA_wCorr->GetYaxis()->SetTitle("Entries");
  h_pp_DATA_wCorr->SetStats(0);
    
  h_pp_DATA_wCorr->Draw("hist");
  h_pp_DATA_noCorr->Draw("hist same");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.5,"no correction");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.43,"with correction");

  pad_pp_DATA_lower->cd();
  
  r_pp_DATA->GetXaxis()->SetTitleSize(2.2*xTitleSize);
  r_pp_DATA->GetXaxis()->SetLabelSize(2.2*xLabelSize);
  r_pp_DATA->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r_pp_DATA->GetYaxis()->SetTitleSize(1.8*xTitleSize);
  r_pp_DATA->GetYaxis()->SetLabelSize(1.8*xLabelSize);
  r_pp_DATA->GetYaxis()->SetTitle("Ratio");
  r_pp_DATA->GetYaxis()->SetTitleOffset(0.6);
  r_pp_DATA->GetYaxis()->SetRangeUser(0.76,1.24);
  
  r_pp_DATA->SetTitle("");
  r_pp_DATA->SetStats(0);
  r_pp_DATA->Draw("hist");
  li->DrawLine(0,1,10,1);

  ///////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C4_MC = new TCanvas("canv_C4_MC","canv_C4_MC",700,700);
  canv_C4_MC->cd();
  TPad *pad_C4_MC_uC4er = new TPad("pad_C4_MC_uC4er","pad_C4_MC_uC4er",0,0.4,1,1);
  TPad *pad_C4_MC_lower = new TPad("pad_C4_MC_lower","pad_C4_MC_lower",0,0,1,0.4);
  pad_C4_MC_uC4er->SetLeftMargin(0.18);
  pad_C4_MC_lower->SetLeftMargin(0.18);
  pad_C4_MC_uC4er->SetBottomMargin(0);
  pad_C4_MC_lower->SetBottomMargin(0.3);
  pad_C4_MC_lower->SetTopMargin(0);
  pad_C4_MC_uC4er->Draw("hist");
  pad_C4_MC_lower->Draw("hist");
  pad_C4_MC_uC4er->cd();

  h_C4_MC_wCorr->SetTitleSize(titleSize);
  h_C4_MC_wCorr->SetTitle("PbPb 50-80% MC");

  h_C4_MC_wCorr->GetYaxis()->SetTitleSize(xTitleSize);
  h_C4_MC_wCorr->GetYaxis()->SetLabelSize(xLabelSize);
  h_C4_MC_wCorr->GetYaxis()->SetTitle("Entries");
  h_C4_MC_wCorr->SetStats(0);
    
  h_C4_MC_wCorr->Draw("hist");
  h_C4_MC_noCorr->Draw("hist same");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.5,"no correction");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.43,"with correction");

  pad_C4_MC_lower->cd();
  
  r_C4_MC->GetXaxis()->SetTitleSize(2.2*xTitleSize);
  r_C4_MC->GetXaxis()->SetLabelSize(2.2*xLabelSize);
  r_C4_MC->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r_C4_MC->GetYaxis()->SetTitleSize(1.8*xTitleSize);
  r_C4_MC->GetYaxis()->SetLabelSize(1.8*xLabelSize);
  r_C4_MC->GetYaxis()->SetTitle("Ratio");
  r_C4_MC->GetYaxis()->SetTitleOffset(0.6);
  r_C4_MC->GetYaxis()->SetRangeUser(0.76,1.24);
  
  r_C4_MC->SetTitle("");
  r_C4_MC->SetStats(0);
  r_C4_MC->Draw("hist");
  li->DrawLine(0,1,10,1);

  ///////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C4_DATA = new TCanvas("canv_C4_DATA","canv_C4_DATA",700,700);
  canv_C4_DATA->cd();
  TPad *pad_C4_DATA_uC4er = new TPad("pad_C4_DATA_uC4er","pad_C4_DATA_uC4er",0,0.4,1,1);
  TPad *pad_C4_DATA_lower = new TPad("pad_C4_DATA_lower","pad_C4_DATA_lower",0,0,1,0.4);
  pad_C4_DATA_uC4er->SetLeftMargin(0.18);
  pad_C4_DATA_lower->SetLeftMargin(0.18);
  pad_C4_DATA_uC4er->SetBottomMargin(0);
  pad_C4_DATA_lower->SetBottomMargin(0.3);
  pad_C4_DATA_lower->SetTopMargin(0);
  pad_C4_DATA_uC4er->Draw("hist");
  pad_C4_DATA_lower->Draw("hist");
  pad_C4_DATA_uC4er->cd();

  h_C4_DATA_wCorr->SetTitleSize(titleSize);
  h_C4_DATA_wCorr->SetTitle("PbPb 50-80% Data");

  h_C4_DATA_wCorr->GetYaxis()->SetTitleSize(xTitleSize);
  h_C4_DATA_wCorr->GetYaxis()->SetLabelSize(xLabelSize);
  h_C4_DATA_wCorr->GetYaxis()->SetTitle("Entries");
  h_C4_DATA_wCorr->SetStats(0);
    
  h_C4_DATA_wCorr->Draw("hist");
  h_C4_DATA_noCorr->Draw("hist same");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.5,"no correction");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.43,"with correction");

  pad_C4_DATA_lower->cd();
  
  r_C4_DATA->GetXaxis()->SetTitleSize(2.2*xTitleSize);
  r_C4_DATA->GetXaxis()->SetLabelSize(2.2*xLabelSize);
  r_C4_DATA->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r_C4_DATA->GetYaxis()->SetTitleSize(1.8*xTitleSize);
  r_C4_DATA->GetYaxis()->SetLabelSize(1.8*xLabelSize);
  r_C4_DATA->GetYaxis()->SetTitle("Ratio");
  r_C4_DATA->GetYaxis()->SetTitleOffset(0.6);
  r_C4_DATA->GetYaxis()->SetRangeUser(0.76,1.24);
  
  r_C4_DATA->SetTitle("");
  r_C4_DATA->SetStats(0);
  r_C4_DATA->Draw("hist");
  li->DrawLine(0,1,10,1);

  ///////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C3_MC = new TCanvas("canv_C3_MC","canv_C3_MC",700,700);
  canv_C3_MC->cd();
  TPad *pad_C3_MC_uC3er = new TPad("pad_C3_MC_uC3er","pad_C3_MC_uC3er",0,0.4,1,1);
  TPad *pad_C3_MC_lower = new TPad("pad_C3_MC_lower","pad_C3_MC_lower",0,0,1,0.4);
  pad_C3_MC_uC3er->SetLeftMargin(0.18);
  pad_C3_MC_lower->SetLeftMargin(0.18);
  pad_C3_MC_uC3er->SetBottomMargin(0);
  pad_C3_MC_lower->SetBottomMargin(0.3);
  pad_C3_MC_lower->SetTopMargin(0);
  pad_C3_MC_uC3er->Draw("hist");
  pad_C3_MC_lower->Draw("hist");
  pad_C3_MC_uC3er->cd();

  h_C3_MC_wCorr->SetTitleSize(titleSize);
  h_C3_MC_wCorr->SetTitle("PbPb 30-50% MC");

  h_C3_MC_wCorr->GetYaxis()->SetTitleSize(xTitleSize);
  h_C3_MC_wCorr->GetYaxis()->SetLabelSize(xLabelSize);
  h_C3_MC_wCorr->GetYaxis()->SetTitle("Entries");
  h_C3_MC_wCorr->SetStats(0);
    
  h_C3_MC_wCorr->Draw("hist");
  h_C3_MC_noCorr->Draw("hist same");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.5,"no correction");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.43,"with correction");

  pad_C3_MC_lower->cd();
  
  r_C3_MC->GetXaxis()->SetTitleSize(2.2*xTitleSize);
  r_C3_MC->GetXaxis()->SetLabelSize(2.2*xLabelSize);
  r_C3_MC->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r_C3_MC->GetYaxis()->SetTitleSize(1.8*xTitleSize);
  r_C3_MC->GetYaxis()->SetLabelSize(1.8*xLabelSize);
  r_C3_MC->GetYaxis()->SetTitle("Ratio");
  r_C3_MC->GetYaxis()->SetTitleOffset(0.6);
  r_C3_MC->GetYaxis()->SetRangeUser(0.76,1.24);
  
  r_C3_MC->SetTitle("");
  r_C3_MC->SetStats(0);
  r_C3_MC->Draw("hist");
  li->DrawLine(0,1,10,1);

  ///////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C3_DATA = new TCanvas("canv_C3_DATA","canv_C3_DATA",700,700);
  canv_C3_DATA->cd();
  TPad *pad_C3_DATA_uC3er = new TPad("pad_C3_DATA_uC3er","pad_C3_DATA_uC3er",0,0.4,1,1);
  TPad *pad_C3_DATA_lower = new TPad("pad_C3_DATA_lower","pad_C3_DATA_lower",0,0,1,0.4);
  pad_C3_DATA_uC3er->SetLeftMargin(0.18);
  pad_C3_DATA_lower->SetLeftMargin(0.18);
  pad_C3_DATA_uC3er->SetBottomMargin(0);
  pad_C3_DATA_lower->SetBottomMargin(0.3);
  pad_C3_DATA_lower->SetTopMargin(0);
  pad_C3_DATA_uC3er->Draw("hist");
  pad_C3_DATA_lower->Draw("hist");
  pad_C3_DATA_uC3er->cd();

  h_C3_DATA_wCorr->SetTitleSize(titleSize);
  h_C3_DATA_wCorr->SetTitle("PbPb 30-50% Data");

  h_C3_DATA_wCorr->GetYaxis()->SetTitleSize(xTitleSize);
  h_C3_DATA_wCorr->GetYaxis()->SetLabelSize(xLabelSize);
  h_C3_DATA_wCorr->GetYaxis()->SetTitle("Entries");
  h_C3_DATA_wCorr->SetStats(0);
    
  h_C3_DATA_wCorr->Draw("hist");
  h_C3_DATA_noCorr->Draw("hist same");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.5,"no correction");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.43,"with correction");

  pad_C3_DATA_lower->cd();
  
  r_C3_DATA->GetXaxis()->SetTitleSize(2.2*xTitleSize);
  r_C3_DATA->GetXaxis()->SetLabelSize(2.2*xLabelSize);
  r_C3_DATA->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r_C3_DATA->GetYaxis()->SetTitleSize(1.8*xTitleSize);
  r_C3_DATA->GetYaxis()->SetLabelSize(1.8*xLabelSize);
  r_C3_DATA->GetYaxis()->SetTitle("Ratio");
  r_C3_DATA->GetYaxis()->SetTitleOffset(0.6);
  r_C3_DATA->GetYaxis()->SetRangeUser(0.76,1.24);
  
  r_C3_DATA->SetTitle("");
  r_C3_DATA->SetStats(0);
  r_C3_DATA->Draw("hist");
  li->DrawLine(0,1,10,1);

  ///////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C2_MC = new TCanvas("canv_C2_MC","canv_C2_MC",700,700);
  canv_C2_MC->cd();
  TPad *pad_C2_MC_uC2er = new TPad("pad_C2_MC_uC2er","pad_C2_MC_uC2er",0,0.4,1,1);
  TPad *pad_C2_MC_lower = new TPad("pad_C2_MC_lower","pad_C2_MC_lower",0,0,1,0.4);
  pad_C2_MC_uC2er->SetLeftMargin(0.18);
  pad_C2_MC_lower->SetLeftMargin(0.18);
  pad_C2_MC_uC2er->SetBottomMargin(0);
  pad_C2_MC_lower->SetBottomMargin(0.3);
  pad_C2_MC_lower->SetTopMargin(0);
  pad_C2_MC_uC2er->Draw("hist");
  pad_C2_MC_lower->Draw("hist");
  pad_C2_MC_uC2er->cd();

  h_C2_MC_wCorr->SetTitleSize(titleSize);
  h_C2_MC_wCorr->SetTitle("PbPb 10-30% MC");

  h_C2_MC_wCorr->GetYaxis()->SetTitleSize(xTitleSize);
  h_C2_MC_wCorr->GetYaxis()->SetLabelSize(xLabelSize);
  h_C2_MC_wCorr->GetYaxis()->SetTitle("Entries");
  h_C2_MC_wCorr->SetStats(0);
    
  h_C2_MC_wCorr->Draw("hist");
  h_C2_MC_noCorr->Draw("hist same");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.5,"no correction");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.43,"with correction");

  pad_C2_MC_lower->cd();
  
  r_C2_MC->GetXaxis()->SetTitleSize(2.2*xTitleSize);
  r_C2_MC->GetXaxis()->SetLabelSize(2.2*xLabelSize);
  r_C2_MC->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r_C2_MC->GetYaxis()->SetTitleSize(1.8*xTitleSize);
  r_C2_MC->GetYaxis()->SetLabelSize(1.8*xLabelSize);
  r_C2_MC->GetYaxis()->SetTitle("Ratio");
  r_C2_MC->GetYaxis()->SetTitleOffset(0.6);
  r_C2_MC->GetYaxis()->SetRangeUser(0.76,1.24);
  
  r_C2_MC->SetTitle("");
  r_C2_MC->SetStats(0);
  r_C2_MC->Draw("hist");
  li->DrawLine(0,1,10,1);

  ///////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C2_DATA = new TCanvas("canv_C2_DATA","canv_C2_DATA",700,700);
  canv_C2_DATA->cd();
  TPad *pad_C2_DATA_uC2er = new TPad("pad_C2_DATA_uC2er","pad_C2_DATA_uC2er",0,0.4,1,1);
  TPad *pad_C2_DATA_lower = new TPad("pad_C2_DATA_lower","pad_C2_DATA_lower",0,0,1,0.4);
  pad_C2_DATA_uC2er->SetLeftMargin(0.18);
  pad_C2_DATA_lower->SetLeftMargin(0.18);
  pad_C2_DATA_uC2er->SetBottomMargin(0);
  pad_C2_DATA_lower->SetBottomMargin(0.3);
  pad_C2_DATA_lower->SetTopMargin(0);
  pad_C2_DATA_uC2er->Draw("hist");
  pad_C2_DATA_lower->Draw("hist");
  pad_C2_DATA_uC2er->cd();

  h_C2_DATA_wCorr->SetTitleSize(titleSize);
  h_C2_DATA_wCorr->SetTitle("PbPb 10-30% Data");

  h_C2_DATA_wCorr->GetYaxis()->SetTitleSize(xTitleSize);
  h_C2_DATA_wCorr->GetYaxis()->SetLabelSize(xLabelSize);
  h_C2_DATA_wCorr->GetYaxis()->SetTitle("Entries");
  h_C2_DATA_wCorr->SetStats(0);
    
  h_C2_DATA_wCorr->Draw("hist");
  h_C2_DATA_noCorr->Draw("hist same");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.5,"no correction");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.43,"with correction");

  pad_C2_DATA_lower->cd();
  
  r_C2_DATA->GetXaxis()->SetTitleSize(2.2*xTitleSize);
  r_C2_DATA->GetXaxis()->SetLabelSize(2.2*xLabelSize);
  r_C2_DATA->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r_C2_DATA->GetYaxis()->SetTitleSize(1.8*xTitleSize);
  r_C2_DATA->GetYaxis()->SetLabelSize(1.8*xLabelSize);
  r_C2_DATA->GetYaxis()->SetTitle("Ratio");
  r_C2_DATA->GetYaxis()->SetTitleOffset(0.6);
  r_C2_DATA->GetYaxis()->SetRangeUser(0.76,1.24);
  
  r_C2_DATA->SetTitle("");
  r_C2_DATA->SetStats(0);
  r_C2_DATA->Draw("hist");
  li->DrawLine(0,1,10,1);

  ///////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C1_MC = new TCanvas("canv_C1_MC","canv_C1_MC",700,700);
  canv_C1_MC->cd();
  TPad *pad_C1_MC_uC1er = new TPad("pad_C1_MC_uC1er","pad_C1_MC_uC1er",0,0.4,1,1);
  TPad *pad_C1_MC_lower = new TPad("pad_C1_MC_lower","pad_C1_MC_lower",0,0,1,0.4);
  pad_C1_MC_uC1er->SetLeftMargin(0.18);
  pad_C1_MC_lower->SetLeftMargin(0.18);
  pad_C1_MC_uC1er->SetBottomMargin(0);
  pad_C1_MC_lower->SetBottomMargin(0.3);
  pad_C1_MC_lower->SetTopMargin(0);
  pad_C1_MC_uC1er->Draw("hist");
  pad_C1_MC_lower->Draw("hist");
  pad_C1_MC_uC1er->cd();

  h_C1_MC_wCorr->SetTitleSize(titleSize);
  h_C1_MC_wCorr->SetTitle("PbPb 0-10% MC");

  h_C1_MC_wCorr->GetYaxis()->SetTitleSize(xTitleSize);
  h_C1_MC_wCorr->GetYaxis()->SetLabelSize(xLabelSize);
  h_C1_MC_wCorr->GetYaxis()->SetTitle("Entries");
  h_C1_MC_wCorr->SetStats(0);
    
  h_C1_MC_wCorr->Draw("hist");
  h_C1_MC_noCorr->Draw("hist same");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.5,"no correction");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.43,"with correction");

  pad_C1_MC_lower->cd();
  
  r_C1_MC->GetXaxis()->SetTitleSize(2.2*xTitleSize);
  r_C1_MC->GetXaxis()->SetLabelSize(2.2*xLabelSize);
  r_C1_MC->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r_C1_MC->GetYaxis()->SetTitleSize(1.8*xTitleSize);
  r_C1_MC->GetYaxis()->SetLabelSize(1.8*xLabelSize);
  r_C1_MC->GetYaxis()->SetTitle("Ratio");
  r_C1_MC->GetYaxis()->SetTitleOffset(0.6);
  r_C1_MC->GetYaxis()->SetRangeUser(0.76,1.24);
  
  r_C1_MC->SetTitle("");
  r_C1_MC->SetStats(0);
  r_C1_MC->Draw("hist");
  li->DrawLine(0,1,10,1);

  ///////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_C1_DATA = new TCanvas("canv_C1_DATA","canv_C1_DATA",700,700);
  canv_C1_DATA->cd();
  TPad *pad_C1_DATA_uC1er = new TPad("pad_C1_DATA_uC1er","pad_C1_DATA_uC1er",0,0.4,1,1);
  TPad *pad_C1_DATA_lower = new TPad("pad_C1_DATA_lower","pad_C1_DATA_lower",0,0,1,0.4);
  pad_C1_DATA_uC1er->SetLeftMargin(0.18);
  pad_C1_DATA_lower->SetLeftMargin(0.18);
  pad_C1_DATA_uC1er->SetBottomMargin(0);
  pad_C1_DATA_lower->SetBottomMargin(0.3);
  pad_C1_DATA_lower->SetTopMargin(0);
  pad_C1_DATA_uC1er->Draw("hist");
  pad_C1_DATA_lower->Draw("hist");
  pad_C1_DATA_uC1er->cd();

  h_C1_DATA_wCorr->SetTitleSize(titleSize);
  h_C1_DATA_wCorr->SetTitle("PbPb 0-10% Data");

  h_C1_DATA_wCorr->GetYaxis()->SetTitleSize(xTitleSize);
  h_C1_DATA_wCorr->GetYaxis()->SetLabelSize(xLabelSize);
  h_C1_DATA_wCorr->GetYaxis()->SetTitle("Entries");
  h_C1_DATA_wCorr->SetStats(0);
    
  h_C1_DATA_wCorr->Draw("hist");
  h_C1_DATA_noCorr->Draw("hist same");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.65,0.5,"no correction");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.65,0.43,"with correction");

  pad_C1_DATA_lower->cd();
  
  r_C1_DATA->GetXaxis()->SetTitleSize(2.2*xTitleSize);
  r_C1_DATA->GetXaxis()->SetLabelSize(2.2*xLabelSize);
  r_C1_DATA->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r_C1_DATA->GetYaxis()->SetTitleSize(1.8*xTitleSize);
  r_C1_DATA->GetYaxis()->SetLabelSize(1.8*xLabelSize);
  r_C1_DATA->GetYaxis()->SetTitle("Ratio");
  r_C1_DATA->GetYaxis()->SetTitleOffset(0.6);
  r_C1_DATA->GetYaxis()->SetRangeUser(0.76,1.24);
  
  r_C1_DATA->SetTitle("");
  r_C1_DATA->SetStats(0);
  r_C1_DATA->Draw("hist");
  li->DrawLine(0,1,10,1);



  canv_pp_MC->SaveAs("./figures/HLTCorrectionEffect/pp_MC.pdf");
  canv_pp_DATA->SaveAs("./figures/HLTCorrectionEffect/pp_DATA.pdf");
  canv_C4_MC->SaveAs("./figures/HLTCorrectionEffect/C4_MC.pdf");
  canv_C4_DATA->SaveAs("./figures/HLTCorrectionEffect/C4_DATA.pdf");
  canv_C3_MC->SaveAs("./figures/HLTCorrectionEffect/C3_MC.pdf");
  canv_C3_DATA->SaveAs("./figures/HLTCorrectionEffect/C3_DATA.pdf");
  canv_C2_MC->SaveAs("./figures/HLTCorrectionEffect/C2_MC.pdf");
  canv_C2_DATA->SaveAs("./figures/HLTCorrectionEffect/C2_DATA.pdf");
  canv_C1_MC->SaveAs("./figures/HLTCorrectionEffect/C1_MC.pdf");
  canv_C1_DATA->SaveAs("./figures/HLTCorrectionEffect/C1_DATA.pdf");



}
