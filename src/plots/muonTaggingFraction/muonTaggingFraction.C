
void configurePad(TPad *pad){
  
  double leftMargin = 0.16;
  double bottomMargin = 0.15;
  
  pad->SetLeftMargin(leftMargin);
  pad->SetBottomMargin(bottomMargin);

}

void configurePad(TPad *pad_upper,
		  TPad *pad_lower){
  
  double leftMargin = 0.16;
  double bottomMargin_upper = 0.;
  double bottomMargin_lower = 0.15;
  double topMargin_upper = 0.15;
  double topMargin_lower = 0.;
  
  pad_upper->SetLeftMargin(leftMargin);
  pad_lower->SetLeftMargin(leftMargin);
  pad_upper->SetBottomMargin(bottomMargin_upper);
  pad_lower->SetBottomMargin(bottomMargin_lower);
  pad_upper->SetTopMargin(topMargin_upper);
  pad_lower->SetTopMargin(topMargin_lower);

}

void configureHistogramForPlotting(TH1D *h){

  double titleSize = 0.05;
  double labelSize = 0.039;
  
  h->SetTitle("");
  h->SetStats(0);
  h->GetYaxis()->SetTitleSize(titleSize);
  h->GetYaxis()->SetLabelSize(labelSize);
  h->GetXaxis()->SetTitleSize(titleSize);
  h->GetXaxis()->SetLabelSize(labelSize);

}

void muonTaggingFraction(){

  TFile *f_PYTHIA, *f_pp, *f_PYTHIAHYDJET, *f_PYTHIAHYDJET_muTagged, *f_PbPb;

  // f_PYTHIA = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_Jet60HLT_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-10-24.root");
  // f_pp = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet60HLT_mu12_pTmu-14_tight_jetTrkMaxFilter_2025-10-24.root");
  // f_PYTHIAHYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-20_Jet60HLT_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-10-27.root");
  // f_PYTHIAHYDJET_muTagged = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-20_Jet60HLT_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-10-27_muTaggedJets.root");
  // f_PbPb = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet60HLT_mu12_tight_pTmu-14_hiHFcut_2025-10-27.root");

  f_PYTHIA = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_Jet80HLT_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-10-23.root");
  f_pp = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet80HLT_mu12_pTmu-14_tight_jetTrkMaxFilter_2025-10-24.root");
  f_PYTHIAHYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-20_Jet80HLT_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-10-24.root");
  f_PYTHIAHYDJET_muTagged = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-20_Jet80HLT_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-10-27_muTaggedJets.root");
  f_PbPb = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet80HLT_mu12_tight_pTmu-14_hiHFcut_2025-10-24.root");
  
  TH2D *H_inclJets_PYTHIA, *H_inclJets_PYTHIAHYDJET_C4, *H_inclJets_PYTHIAHYDJET_C3, *H_inclJets_PYTHIAHYDJET_C2, *H_inclJets_PYTHIAHYDJET_C1;
  TH2D *H_inclXJets_PYTHIA, *H_inclXJets_PYTHIAHYDJET_C4, *H_inclXJets_PYTHIAHYDJET_C3, *H_inclXJets_PYTHIAHYDJET_C2, *H_inclXJets_PYTHIAHYDJET_C1;
  TH2D *H_muTaggedJets_PYTHIA, *H_muTaggedJets_PYTHIAHYDJET_C4, *H_muTaggedJets_PYTHIAHYDJET_C3, *H_muTaggedJets_PYTHIAHYDJET_C2, *H_muTaggedJets_PYTHIAHYDJET_C1;
  TH2D *H_muTaggedXJets_PYTHIA, *H_muTaggedXJets_PYTHIAHYDJET_C4, *H_muTaggedXJets_PYTHIAHYDJET_C3, *H_muTaggedXJets_PYTHIAHYDJET_C2, *H_muTaggedXJets_PYTHIAHYDJET_C1;
  TH1D *inclJets_PYTHIA, *inclJets_pp, *inclJets_PH_C4, *inclJets_PH_C3, *inclJets_PH_C2, *inclJets_PH_C1, *inclJets_PbPb_C4, *inclJets_PbPb_C3, *inclJets_PbPb_C2, *inclJets_PbPb_C1;
  TH1D *muTaggedJets_PYTHIA, *muTaggedJets_pp, *muTaggedJets_PH_C4, *muTaggedJets_PH_C3, *muTaggedJets_PH_C2, *muTaggedJets_PH_C1, *muTaggedJets_PbPb_C4, *muTaggedJets_PbPb_C3, *muTaggedJets_PbPb_C2, *muTaggedJets_PbPb_C1;

  f_PYTHIA->GetObject("h_inclRecoJetPt_flavor",H_inclJets_PYTHIA);
  f_PYTHIA->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",H_muTaggedJets_PYTHIA);
  f_PYTHIAHYDJET->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",H_inclJets_PYTHIAHYDJET_C4);
  f_PYTHIAHYDJET->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",H_inclJets_PYTHIAHYDJET_C3);
  f_PYTHIAHYDJET->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H_inclJets_PYTHIAHYDJET_C2);
  f_PYTHIAHYDJET->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",H_inclJets_PYTHIAHYDJET_C1);
  f_PYTHIAHYDJET->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C4",H_inclXJets_PYTHIAHYDJET_C4);
  f_PYTHIAHYDJET->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C3",H_inclXJets_PYTHIAHYDJET_C3);
  f_PYTHIAHYDJET->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C2",H_inclXJets_PYTHIAHYDJET_C2);
  f_PYTHIAHYDJET->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C1",H_inclXJets_PYTHIAHYDJET_C1);
  f_PYTHIAHYDJET_muTagged->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C4",H_muTaggedJets_PYTHIAHYDJET_C4);
  f_PYTHIAHYDJET_muTagged->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C3",H_muTaggedJets_PYTHIAHYDJET_C3);
  f_PYTHIAHYDJET_muTagged->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C2",H_muTaggedJets_PYTHIAHYDJET_C2);
  f_PYTHIAHYDJET_muTagged->GetObject("h_matchedRecoJetPt_genJetPt_allJets_C1",H_muTaggedJets_PYTHIAHYDJET_C1);
  f_PYTHIAHYDJET_muTagged->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C4",H_muTaggedXJets_PYTHIAHYDJET_C4);
  f_PYTHIAHYDJET_muTagged->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C3",H_muTaggedXJets_PYTHIAHYDJET_C3);
  f_PYTHIAHYDJET_muTagged->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C2",H_muTaggedXJets_PYTHIAHYDJET_C2);
  f_PYTHIAHYDJET_muTagged->GetObject("h_matchedRecoJetPt_genJetPt_xJets_C1",H_muTaggedXJets_PYTHIAHYDJET_C1);

  H_inclJets_PYTHIAHYDJET_C4->Add(H_inclJets_PYTHIAHYDJET_C4,H_inclXJets_PYTHIAHYDJET_C4,1,-1);
  H_inclJets_PYTHIAHYDJET_C3->Add(H_inclJets_PYTHIAHYDJET_C3,H_inclXJets_PYTHIAHYDJET_C3,1,-1);
  H_inclJets_PYTHIAHYDJET_C2->Add(H_inclJets_PYTHIAHYDJET_C2,H_inclXJets_PYTHIAHYDJET_C2,1,-1);
  H_inclJets_PYTHIAHYDJET_C1->Add(H_inclJets_PYTHIAHYDJET_C1,H_inclXJets_PYTHIAHYDJET_C1,1,-1);

  H_muTaggedJets_PYTHIAHYDJET_C4->Add(H_muTaggedJets_PYTHIAHYDJET_C4,H_muTaggedXJets_PYTHIAHYDJET_C4,1,-1);
  H_muTaggedJets_PYTHIAHYDJET_C3->Add(H_muTaggedJets_PYTHIAHYDJET_C3,H_muTaggedXJets_PYTHIAHYDJET_C3,1,-1);
  H_muTaggedJets_PYTHIAHYDJET_C2->Add(H_muTaggedJets_PYTHIAHYDJET_C2,H_muTaggedXJets_PYTHIAHYDJET_C2,1,-1);
  H_muTaggedJets_PYTHIAHYDJET_C1->Add(H_muTaggedJets_PYTHIAHYDJET_C1,H_muTaggedXJets_PYTHIAHYDJET_C1,1,-1);
  
  inclJets_PYTHIA = (TH1D*) H_inclJets_PYTHIA->ProjectionX("inclJets_PYTHIA");
  muTaggedJets_PYTHIA = (TH1D*) H_muTaggedJets_PYTHIA->ProjectionX("muTaggedJets_PYTHIA");

  inclJets_PH_C4 = (TH1D*) H_inclJets_PYTHIAHYDJET_C4->ProjectionX("inclJets_PH_C4");
  inclJets_PH_C3 = (TH1D*) H_inclJets_PYTHIAHYDJET_C3->ProjectionX("inclJets_PH_C3");
  inclJets_PH_C2 = (TH1D*) H_inclJets_PYTHIAHYDJET_C2->ProjectionX("inclJets_PH_C2");
  inclJets_PH_C1 = (TH1D*) H_inclJets_PYTHIAHYDJET_C1->ProjectionX("inclJets_PH_C1");

  muTaggedJets_PH_C4 = (TH1D*) H_muTaggedJets_PYTHIAHYDJET_C4->ProjectionX("muTaggedJets_PH_C4");
  muTaggedJets_PH_C3 = (TH1D*) H_muTaggedJets_PYTHIAHYDJET_C3->ProjectionX("muTaggedJets_PH_C3");
  muTaggedJets_PH_C2 = (TH1D*) H_muTaggedJets_PYTHIAHYDJET_C2->ProjectionX("muTaggedJets_PH_C2");
  muTaggedJets_PH_C1 = (TH1D*) H_muTaggedJets_PYTHIAHYDJET_C1->ProjectionX("muTaggedJets_PH_C1");

  f_pp->GetObject("h_inclRecoJetPt",inclJets_pp);
  f_pp->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",muTaggedJets_pp);
  f_PbPb->GetObject("h_inclRecoJetPt_C4",inclJets_PbPb_C4);
  f_PbPb->GetObject("h_inclRecoJetPt_C3",inclJets_PbPb_C3);
  f_PbPb->GetObject("h_inclRecoJetPt_C2",inclJets_PbPb_C2);
  f_PbPb->GetObject("h_inclRecoJetPt_C1",inclJets_PbPb_C1);
  f_PbPb->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",muTaggedJets_PbPb_C4);
  f_PbPb->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",muTaggedJets_PbPb_C3);
  f_PbPb->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",muTaggedJets_PbPb_C2);
  f_PbPb->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",muTaggedJets_PbPb_C1);


  // rebin

  const int N_edge = 23;
  double newAxis[N_edge] = {20,25,30,35,40,45,50,55,60,70,80,90,100,110,120,140,160,180,200,250,300,400,500};
  
  inclJets_pp = (TH1D*) inclJets_pp->Rebin(N_edge-1,"inclJets_pp",newAxis);
  muTaggedJets_pp = (TH1D*) muTaggedJets_pp->Rebin(N_edge-1,"muTaggedJets_pp",newAxis);

  inclJets_PbPb_C4 = (TH1D*) inclJets_PbPb_C4->Rebin(N_edge-1,"inclJets_PbPb_C4",newAxis);
  muTaggedJets_PbPb_C4 = (TH1D*) muTaggedJets_PbPb_C4->Rebin(N_edge-1,"muTaggedJets_PbPb_C4",newAxis);

  inclJets_PbPb_C3 = (TH1D*) inclJets_PbPb_C3->Rebin(N_edge-1,"inclJets_PbPb_C3",newAxis);
  muTaggedJets_PbPb_C3 = (TH1D*) muTaggedJets_PbPb_C3->Rebin(N_edge-1,"muTaggedJets_PbPb_C3",newAxis);

  inclJets_PbPb_C2 = (TH1D*) inclJets_PbPb_C2->Rebin(N_edge-1,"inclJets_PbPb_C2",newAxis);
  muTaggedJets_PbPb_C2 = (TH1D*) muTaggedJets_PbPb_C2->Rebin(N_edge-1,"muTaggedJets_PbPb_C2",newAxis);

  inclJets_PbPb_C1 = (TH1D*) inclJets_PbPb_C1->Rebin(N_edge-1,"inclJets_PbPb_C1",newAxis);
  muTaggedJets_PbPb_C1 = (TH1D*) muTaggedJets_PbPb_C1->Rebin(N_edge-1,"muTaggedJets_PbPb_C1",newAxis);

  inclJets_PYTHIA = (TH1D*) inclJets_PYTHIA->Rebin(N_edge-1,"inclJets_PYTHIA",newAxis);
  muTaggedJets_PYTHIA = (TH1D*) muTaggedJets_PYTHIA->Rebin(N_edge-1,"muTaggedJets_PYTHIA",newAxis);

  inclJets_PH_C4 = (TH1D*) inclJets_PH_C4->Rebin(N_edge-1,"inclJets_PH_C4",newAxis);
  muTaggedJets_PH_C4 = (TH1D*) muTaggedJets_PH_C4->Rebin(N_edge-1,"muTaggedJets_PH_C4",newAxis);

  inclJets_PH_C3 = (TH1D*) inclJets_PH_C3->Rebin(N_edge-1,"inclJets_PH_C3",newAxis);
  muTaggedJets_PH_C3 = (TH1D*) muTaggedJets_PH_C3->Rebin(N_edge-1,"muTaggedJets_PH_C3",newAxis);

  inclJets_PH_C2 = (TH1D*) inclJets_PH_C2->Rebin(N_edge-1,"inclJets_PH_C2",newAxis);
  muTaggedJets_PH_C2 = (TH1D*) muTaggedJets_PH_C2->Rebin(N_edge-1,"muTaggedJets_PH_C2",newAxis);

  inclJets_PH_C1 = (TH1D*) inclJets_PH_C1->Rebin(N_edge-1,"inclJets_PH_C1",newAxis);
  muTaggedJets_PH_C1 = (TH1D*) muTaggedJets_PH_C1->Rebin(N_edge-1,"muTaggedJets_PH_C1",newAxis);
  

  

  TH1D *r_PYTHIA, *r_pp, *r_PH_C4, *r_PH_C3, *r_PH_C2, *r_PH_C1, *r_PbPb_C4, *r_PbPb_C3, *r_PbPb_C2, *r_PbPb_C1;

  r_PYTHIA = (TH1D*) inclJets_PYTHIA->Clone("r_PYTHIA");
  r_PYTHIA->Divide(muTaggedJets_PYTHIA,inclJets_PYTHIA,1,1,"B");

  r_pp = (TH1D*) inclJets_pp->Clone("r_pp");
  r_pp->Divide(muTaggedJets_pp,inclJets_pp,1,1,"B");

  r_PH_C4 = (TH1D*) inclJets_PH_C4->Clone("r_PH_C4");
  r_PH_C4->Divide(muTaggedJets_PH_C4,inclJets_PH_C4,1,1,"B");

  r_PH_C3 = (TH1D*) inclJets_PH_C3->Clone("r_PH_C3");
  r_PH_C3->Divide(muTaggedJets_PH_C3,inclJets_PH_C3,1,1,"B");

  r_PH_C2 = (TH1D*) inclJets_PH_C2->Clone("r_PH_C2");
  r_PH_C2->Divide(muTaggedJets_PH_C2,inclJets_PH_C2,1,1,"B");

  r_PH_C1 = (TH1D*) inclJets_PH_C1->Clone("r_PH_C1");
  r_PH_C1->Divide(muTaggedJets_PH_C1,inclJets_PH_C1,1,1,"B");

  r_PbPb_C4 = (TH1D*) inclJets_PbPb_C4->Clone("r_PbPb_C4");
  r_PbPb_C4->Divide(muTaggedJets_PbPb_C4,inclJets_PbPb_C4,1,1,"B");

  r_PbPb_C3 = (TH1D*) inclJets_PbPb_C3->Clone("r_PbPb_C3");
  r_PbPb_C3->Divide(muTaggedJets_PbPb_C3,inclJets_PbPb_C3,1,1,"B");

  r_PbPb_C2 = (TH1D*) inclJets_PbPb_C2->Clone("r_PbPb_C2");
  r_PbPb_C2->Divide(muTaggedJets_PbPb_C2,inclJets_PbPb_C2,1,1,"B");

  r_PbPb_C1 = (TH1D*) inclJets_PbPb_C1->Clone("r_PbPb_C1");
  r_PbPb_C1->Divide(muTaggedJets_PbPb_C1,inclJets_PbPb_C1,1,1,"B");

  TH1D *rr_pp, *rr_C4, *rr_C3, *rr_C2, *rr_C1; // double ratio DATA/MC
  
  rr_pp = (TH1D*) r_pp->Clone("rr_pp");
  rr_pp->Divide(r_pp,r_PYTHIA,1,1,"");

  rr_C4 = (TH1D*) r_PbPb_C4->Clone("rr_C4");
  rr_C4->Divide(r_PbPb_C4,r_PH_C4,1,1,"");

  rr_C3 = (TH1D*) r_PbPb_C3->Clone("rr_C3");
  rr_C3->Divide(r_PbPb_C3,r_PH_C3,1,1,"");

  rr_C2 = (TH1D*) r_PbPb_C2->Clone("rr_C2");
  rr_C2->Divide(r_PbPb_C2,r_PH_C2,1,1,"");

  rr_C1 = (TH1D*) r_PbPb_C1->Clone("rr_C1");
  rr_C1->Divide(r_PbPb_C1,r_PH_C1,1,1,"");

  TLine *li = new TLine();
  li->SetLineStyle(7);

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.048);

  TLegend *leg_pp = new TLegend(0.22,0.6,0.4,0.8);
  leg_pp->SetBorderSize(0);
  leg_pp->SetTextSize(0.048);
  leg_pp->AddEntry(r_PYTHIA,"PYTHIA");
  leg_pp->AddEntry(r_pp,"pp HighEGJet");

  TLegend *leg_C4 = new TLegend(0.18,0.6,0.4,0.8);
  leg_C4->SetBorderSize(0);
  leg_C4->SetTextSize(0.048);
  leg_C4->AddEntry(r_PH_C4,"PYTHIA+HYDJET 50-80%");
  leg_C4->AddEntry(r_PbPb_C4,"PbPb HardProbes 50-80%");

  TLegend *leg_C3 = new TLegend(0.18,0.6,0.4,0.8);
  leg_C3->SetBorderSize(0);
  leg_C3->SetTextSize(0.048);
  leg_C3->AddEntry(r_PH_C3,"PYTHIA+HYDJET 30-50%");
  leg_C3->AddEntry(r_PbPb_C3,"PbPb HardProbes 30-50%");

  TLegend *leg_C2 = new TLegend(0.18,0.6,0.4,0.8);
  leg_C2->SetBorderSize(0);
  leg_C2->SetTextSize(0.048);
  leg_C2->AddEntry(r_PH_C2,"PYTHIA+HYDJET 10-30%");
  leg_C2->AddEntry(r_PbPb_C2,"PbPb HardProbes 10-30%");

  TLegend *leg_C1 = new TLegend(0.18,0.6,0.4,0.8);
  leg_C1->SetBorderSize(0);
  leg_C1->SetTextSize(0.048);
  leg_C1->AddEntry(r_PH_C1,"PYTHIA+HYDJET 0-10%");
  leg_C1->AddEntry(r_PbPb_C1,"PbPb HardProbes 0-10%");

  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_pp = new TCanvas("canv_pp","canv_pp",700,700);
  canv_pp->cd();
  TPad *pad_pp_upper = new TPad("pad_pp_upper","pad_pp_upper",0,0.5,1,1);
  TPad *pad_pp_lower = new TPad("pad_pp_lower","pad_pp_lower",0,0,1,0.5);
  configurePad(pad_pp_upper,pad_pp_lower);
  pad_pp_upper->Draw();
  pad_pp_lower->Draw();
  pad_pp_upper->cd();
  configureHistogramForPlotting(r_PYTHIA);
  r_PYTHIA->GetYaxis()->SetRangeUser(0,0.014);
  r_PYTHIA->GetYaxis()->SetTitle("#it{#mu}-tagged fraction");
  r_PYTHIA->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_PYTHIA->SetLineColor(kBlue-4);
  r_pp->SetLineColor(kRed-4);
  r_PYTHIA->Draw();
  r_pp->Draw("same");
  leg_pp->Draw();
  la->DrawLatexNDC(0.52,0.75,"jet80 + mu12 trigger");
  la->DrawLatexNDC(0.52,0.67,"AK4PF jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.52,0.59,"#it{p}_{T}^{#it{#mu}} > 14 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  pad_pp_lower->cd();
  configureHistogramForPlotting(rr_pp);
  rr_pp->SetLineColor(kRed-4);
  rr_pp->GetYaxis()->SetRangeUser(0.36,1.64);
  rr_pp->GetYaxis()->SetTitle("Data / MC");
  rr_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  rr_pp->Draw();
  li->DrawLine(20,1,500,1);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C4 = new TCanvas("canv_C4","canv_C4",700,700);
  canv_C4->cd();
  TPad *pad_C4_upper = new TPad("pad_C4_upper","pad_C4_upper",0,0.5,1,1);
  TPad *pad_C4_lower = new TPad("pad_C4_lower","pad_C4_lower",0,0,1,0.5);
  configurePad(pad_C4_upper,pad_C4_lower);
  pad_C4_upper->Draw();
  pad_C4_lower->Draw();
  pad_C4_upper->cd();
  configureHistogramForPlotting(r_PH_C4);
  r_PH_C4->GetYaxis()->SetRangeUser(0,0.014);
  r_PH_C4->GetYaxis()->SetTitle("#it{#mu}-tagged fraction");
  r_PH_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_PH_C4->SetLineColor(kBlue-4);
  r_PbPb_C4->SetLineColor(kRed-4);
  r_PH_C4->Draw();
  r_PbPb_C4->Draw("same");
  leg_C4->Draw();
  la->DrawLatexNDC(0.62,0.75,"jet80 + mu12 trigger");
  la->DrawLatexNDC(0.62,0.67,"AK4CsPF jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.62,0.59,"#it{p}_{T}^{#it{#mu}} > 14 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  pad_C4_lower->cd();
  configureHistogramForPlotting(rr_C4);
  rr_C4->SetLineColor(kRed-4);
  rr_C4->GetYaxis()->SetRangeUser(0.36,1.64);
  rr_C4->GetYaxis()->SetTitle("Data / MC");
  rr_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  rr_C4->Draw();
  li->DrawLine(20,1,500,1);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C3 = new TCanvas("canv_C3","canv_C3",700,700);
  canv_C3->cd();
  TPad *pad_C3_upper = new TPad("pad_C3_upper","pad_C3_upper",0,0.5,1,1);
  TPad *pad_C3_lower = new TPad("pad_C3_lower","pad_C3_lower",0,0,1,0.5);
  configurePad(pad_C3_upper,pad_C3_lower);
  pad_C3_upper->Draw();
  pad_C3_lower->Draw();
  pad_C3_upper->cd();
  configureHistogramForPlotting(r_PH_C3);
  r_PH_C3->GetYaxis()->SetRangeUser(0,0.014);
  r_PH_C3->GetYaxis()->SetTitle("#it{#mu}-tagged fraction");
  r_PH_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_PH_C3->SetLineColor(kBlue-4);
  r_PbPb_C3->SetLineColor(kRed-4);
  r_PH_C3->Draw();
  r_PbPb_C3->Draw("same");
  leg_C3->Draw();
  la->DrawLatexNDC(0.62,0.75,"jet80 + mu12 trigger");
  la->DrawLatexNDC(0.62,0.67,"AK4CsPF jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.62,0.59,"#it{p}_{T}^{#it{#mu}} > 14 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  pad_C3_lower->cd();
  configureHistogramForPlotting(rr_C3);
  rr_C3->SetLineColor(kRed-4);
  rr_C3->GetYaxis()->SetRangeUser(0.36,1.64);
  rr_C3->GetYaxis()->SetTitle("Data / MC");
  rr_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  rr_C3->Draw();
  li->DrawLine(20,1,500,1);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C2 = new TCanvas("canv_C2","canv_C2",700,700);
  canv_C2->cd();
  TPad *pad_C2_upper = new TPad("pad_C2_upper","pad_C2_upper",0,0.5,1,1);
  TPad *pad_C2_lower = new TPad("pad_C2_lower","pad_C2_lower",0,0,1,0.5);
  configurePad(pad_C2_upper,pad_C2_lower);
  pad_C2_upper->Draw();
  pad_C2_lower->Draw();
  pad_C2_upper->cd();
  configureHistogramForPlotting(r_PH_C2);
  r_PH_C2->GetYaxis()->SetRangeUser(0,0.014);
  r_PH_C2->GetYaxis()->SetTitle("#it{#mu}-tagged fraction");
  r_PH_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_PH_C2->SetLineColor(kBlue-4);
  r_PbPb_C2->SetLineColor(kRed-4);
  r_PH_C2->Draw();
  r_PbPb_C2->Draw("same");
  leg_C2->Draw();
  la->DrawLatexNDC(0.62,0.75,"jet80 + mu12 trigger");
  la->DrawLatexNDC(0.62,0.67,"AK4CsPF jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.62,0.59,"#it{p}_{T}^{#it{#mu}} > 14 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  pad_C2_lower->cd();
  configureHistogramForPlotting(rr_C2);
  rr_C2->SetLineColor(kRed-4);
  rr_C2->GetYaxis()->SetRangeUser(0.36,1.64);
  rr_C2->GetYaxis()->SetTitle("Data / MC");
  rr_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  rr_C2->Draw();
  li->DrawLine(20,1,500,1);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C1 = new TCanvas("canv_C1","canv_C1",700,700);
  canv_C1->cd();
  TPad *pad_C1_upper = new TPad("pad_C1_upper","pad_C1_upper",0,0.5,1,1);
  TPad *pad_C1_lower = new TPad("pad_C1_lower","pad_C1_lower",0,0,1,0.5);
  configurePad(pad_C1_upper,pad_C1_lower);
  pad_C1_upper->Draw();
  pad_C1_lower->Draw();
  pad_C1_upper->cd();
  configureHistogramForPlotting(r_PH_C1);
  r_PH_C1->GetYaxis()->SetRangeUser(0,0.014);
  r_PH_C1->GetYaxis()->SetTitle("#it{#mu}-tagged fraction");
  r_PH_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_PH_C1->SetLineColor(kBlue-4);
  r_PbPb_C1->SetLineColor(kRed-4);
  r_PH_C1->Draw();
  r_PbPb_C1->Draw("same");
  leg_C1->Draw();
  la->DrawLatexNDC(0.62,0.75,"jet80 + mu12 trigger");
  la->DrawLatexNDC(0.62,0.67,"AK4CsPF jets, |#it{#eta}^{jet}| < 1.6");
  la->DrawLatexNDC(0.62,0.59,"#it{p}_{T}^{#it{#mu}} > 14 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  pad_C1_lower->cd();
  configureHistogramForPlotting(rr_C1);
  rr_C1->SetLineColor(kRed-4);
  rr_C1->GetYaxis()->SetRangeUser(0.36,1.64);
  rr_C1->GetYaxis()->SetTitle("Data / MC");
  rr_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  rr_C1->Draw();
  li->DrawLine(20,1,500,1);

  ///////////////////////////////////////////////////////////////////////////////////////////////////

  canv_pp->SaveAs("../../../figures/muonTaggingFraction/pp.pdf");
  canv_C4->SaveAs("../../../figures/muonTaggingFraction/C4.pdf");
  canv_C3->SaveAs("../../../figures/muonTaggingFraction/C3.pdf");
  canv_C2->SaveAs("../../../figures/muonTaggingFraction/C2.pdf");
  canv_C1->SaveAs("../../../figures/muonTaggingFraction/C1.pdf");

}
