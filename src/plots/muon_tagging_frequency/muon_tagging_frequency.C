
TFile *file_pp_MC, *file_pp_data;
TFile *file_PbPb_MC, *file_PbPb_data;
TH2D *JETS_incl_pp_MC, *JETS_muTagged_pp_MC;
TH2D *JETS_incl_PbPb_C2_MC, *JETS_muTagged_PbPb_C2_MC;
TH2D *JETS_incl_PbPb_C1_MC, *JETS_muTagged_PbPb_C1_MC;
TH1D *jets_incl_pp_MC, *jets_incl_pp_data;
TH1D *jets_incl_PbPb_C2_MC, *jets_incl_PbPb_C2_data, *jets_incl_PbPb_C2_data_add;
TH1D *jets_incl_PbPb_C1_MC, *jets_incl_PbPb_C1_data, *jets_incl_PbPb_C1_data_add;
TH1D *jets_muTagged_pp_MC, *jets_muTagged_pp_data;
TH1D *jets_muTagged_PbPb_C2_MC, *jets_muTagged_PbPb_C2_data, *jets_muTagged_PbPb_C2_data_add;
TH1D *jets_muTagged_PbPb_C1_MC, *jets_muTagged_PbPb_C1_data, *jets_muTagged_PbPb_C1_data_add;
TH1D *taggingFreq_pp_MC, *taggingFreq_pp_data;
TH1D *taggingFreq_PbPb_C2_MC, *taggingFreq_PbPb_C2_data;
TH1D *taggingFreq_PbPb_C1_MC, *taggingFreq_PbPb_C1_data;
TH1D *taggingFreq_ratio_pp, *taggingFreq_ratio_C2, *taggingFreq_ratio_C1;

void muon_tagging_frequency(){

  file_PbPb_MC = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_newJetBins.root");
  //file_PbPb_MC = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/fineCentBins/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_removeHYDJETjet_jetTrkMaxFilter_vzReweight_hiBinReweight_weightCut0p005_fineCentBins_projectableTemplates.root");
  //file_PbPb_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/platinum/PbPb_MinBias_mu12_tight_pTmu-14_evtFilterFix_hiHFcut_newJetBins.root");
  file_PbPb_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/platinum/PbPb_HardProbes_mu12_tight_pTmu-14_evtFilterFix_hiHFcut_newJetBins.root");
  //file_PbPb_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/final/PbPb_SingleMuon_scan_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates.root");
  file_pp_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/final/pp_HighEGJet_jet60_mu12_tight_pTmu-14_projectableTemplates.root");
  //file_pp_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/final/pp_MinBias_mu12_tight_pTmu-14_projectableTemplates.root");
  //file_pp_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/final/pp_SingleMuon_mu12_tight_pTmu-14_projectableTemplates.root");
  file_pp_MC = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/final/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjet_jetTrkMaxFilter_vzReweight_jetPtReweight_dRReweight_projectableTemplates.root");


  TString muonTagString = "_inclRecoMuonTag";
  //TString muonTagString = "_inclRecoMuonTag_triggerOn";
  
  file_pp_data->GetObject("h_inclRecoJetPt",jets_incl_pp_data);
  file_pp_data->GetObject(Form("h_inclRecoJetPt%s",muonTagString.Data()),jets_muTagged_pp_data);

  // const int N_edge = 7;
  // double newAxis[N_edge] = {80,100,120,150,200,300,500};

  const int N_edge = 14;
  double newAxis[N_edge] = {80,85,90,95,100,105,110,115,120,125,130,150,200,300};

  // const int N_edge = 6;
  // double newAxis[N_edge] = {80,90,100,120,150,200};

  // const int N_edge = 5;
  // double newAxis[N_edge] = {120,130,150,170,220};
  
  TH1D *jets_incl_pp_data_R = (TH1D*) jets_incl_pp_data->Rebin(N_edge-1,"jets_incl_pp_data_R",newAxis);
  TH1D *jets_muTagged_pp_data_R = (TH1D*) jets_muTagged_pp_data->Rebin(N_edge-1,"jets_muTagged_pp_data_R",newAxis);
  

  
  
  taggingFreq_pp_data = (TH1D*) jets_muTagged_pp_data_R->Clone("taggingFreq_pp_data");
  taggingFreq_pp_data->Divide(jets_muTagged_pp_data_R,jets_incl_pp_data_R,1,1,"B");

   
  
  file_PbPb_data->GetObject("h_inclRecoJetPt_C2",jets_incl_PbPb_C2_data);
  file_PbPb_data->GetObject(Form("h_inclRecoJetPt%s_C2",muonTagString.Data()),jets_muTagged_PbPb_C2_data);
  TH1D *jets_incl_PbPb_C2_data_R = (TH1D*) jets_incl_PbPb_C2_data->Rebin(N_edge-1,"jets_incl_PbPb_C2_data_R",newAxis);
  TH1D *jets_muTagged_PbPb_C2_data_R = (TH1D*) jets_muTagged_PbPb_C2_data->Rebin(N_edge-1,"jets_muTagged_PbPb_C2_data_R",newAxis);
  
  file_PbPb_data->GetObject("h_inclRecoJetPt_C1",jets_incl_PbPb_C1_data);
  file_PbPb_data->GetObject(Form("h_inclRecoJetPt%s_C1",muonTagString.Data()),jets_muTagged_PbPb_C1_data);
  TH1D *jets_incl_PbPb_C1_data_R = (TH1D*) jets_incl_PbPb_C1_data->Rebin(N_edge-1,"jets_incl_PbPb_C1_data_R",newAxis);
  TH1D *jets_muTagged_PbPb_C1_data_R = (TH1D*) jets_muTagged_PbPb_C1_data->Rebin(N_edge-1,"jets_muTagged_PbPb_C1_data_R",newAxis);
  taggingFreq_PbPb_C2_data = (TH1D*) jets_muTagged_PbPb_C2_data_R->Clone("taggingFreq_PbPb_C2_data");
  taggingFreq_PbPb_C2_data->Divide(jets_muTagged_PbPb_C2_data_R,jets_incl_PbPb_C2_data_R,1,1,"B");
  taggingFreq_PbPb_C1_data = (TH1D*) jets_muTagged_PbPb_C1_data_R->Clone("taggingFreq_PbPb_C1_data");
  taggingFreq_PbPb_C1_data->Divide(jets_muTagged_PbPb_C1_data_R,jets_incl_PbPb_C1_data_R,1,1,"B");

  file_pp_MC->GetObject("h_inclRecoJetPt_flavor",JETS_incl_pp_MC);
  jets_incl_pp_MC = (TH1D*) JETS_incl_pp_MC->ProjectionX("jets_incl_pp_MC");
  TH1D *jets_incl_pp_MC_R = (TH1D*) jets_incl_pp_MC->Rebin(N_edge-1,"jets_incl_pp_MC_R",newAxis);
  file_pp_MC->GetObject(Form("h_inclRecoJetPt%s_flavor",muonTagString.Data()),JETS_muTagged_pp_MC);
  jets_muTagged_pp_MC = (TH1D*) JETS_muTagged_pp_MC->ProjectionX("jets_muTagged_pp_MC");
  TH1D *jets_muTagged_pp_MC_R = (TH1D*) jets_muTagged_pp_MC->Rebin(N_edge-1,"jets_muTagged_pp_MC_R",newAxis);
  taggingFreq_pp_MC = (TH1D*) jets_muTagged_pp_MC_R->Clone("taggingFreq_pp_MC");
  taggingFreq_pp_MC->Divide(jets_muTagged_pp_MC_R, jets_incl_pp_MC_R,1,1,"B");

  file_PbPb_MC->GetObject("h_inclRecoJetPt_flavor_C2",JETS_incl_PbPb_C2_MC);
  jets_incl_PbPb_C2_MC = (TH1D*) JETS_incl_PbPb_C2_MC->ProjectionX("jets_incl_PbPb_C2_MC");
  TH1D *jets_incl_PbPb_C2_MC_R = (TH1D*) jets_incl_PbPb_C2_MC->Rebin(N_edge-1,"jets_incl_PbPb_C2_MC_R",newAxis);
  file_PbPb_MC->GetObject(Form("h_inclRecoJetPt%s_flavor_C2",muonTagString.Data()),JETS_muTagged_PbPb_C2_MC);
  jets_muTagged_PbPb_C2_MC = (TH1D*) JETS_muTagged_PbPb_C2_MC->ProjectionX("jets_muTagged_PbPb_C2_MC");
  TH1D *jets_muTagged_PbPb_C2_MC_R = (TH1D*) jets_muTagged_PbPb_C2_MC->Rebin(N_edge-1,"jets_muTagged_PbPb_C2_MC_R",newAxis);
  file_PbPb_MC->GetObject("h_inclRecoJetPt_flavor_C1",JETS_incl_PbPb_C1_MC);
  jets_incl_PbPb_C1_MC = (TH1D*) JETS_incl_PbPb_C1_MC->ProjectionX("jets_incl_PbPb_C1_MC");
  TH1D *jets_incl_PbPb_C1_MC_R = (TH1D*) jets_incl_PbPb_C1_MC->Rebin(N_edge-1,"jets_incl_PbPb_C1_MC_R",newAxis);
  file_PbPb_MC->GetObject(Form("h_inclRecoJetPt%s_flavor_C1",muonTagString.Data()),JETS_muTagged_PbPb_C1_MC);
  jets_muTagged_PbPb_C1_MC = (TH1D*) JETS_muTagged_PbPb_C1_MC->ProjectionX("jets_muTagged_PbPb_C1_MC");
  TH1D *jets_muTagged_PbPb_C1_MC_R = (TH1D*) jets_muTagged_PbPb_C1_MC->Rebin(N_edge-1,"jets_muTagged_PbPb_C1_MC_R",newAxis);
  taggingFreq_PbPb_C2_MC = (TH1D*) jets_muTagged_PbPb_C2_MC_R->Clone("taggingFreq_PbPb_C2_MC");
  taggingFreq_PbPb_C2_MC->Divide(jets_muTagged_PbPb_C2_MC_R,jets_incl_PbPb_C2_MC_R,1,1,"B");
  taggingFreq_PbPb_C1_MC = (TH1D*) jets_muTagged_PbPb_C1_MC_R->Clone("taggingFreq_PbPb_C1_MC");
  taggingFreq_PbPb_C1_MC->Divide(jets_muTagged_PbPb_C1_MC_R,jets_incl_PbPb_C1_MC_R,1,1,"B");

  taggingFreq_ratio_C2 = (TH1D*) taggingFreq_PbPb_C2_data->Clone("taggingFreq_ratio_C2");
  taggingFreq_ratio_C2->Divide(taggingFreq_PbPb_C2_data,taggingFreq_PbPb_C2_MC,1,1,"");
  taggingFreq_ratio_C1 = (TH1D*) taggingFreq_PbPb_C1_data->Clone("taggingFreq_ratio_C1");
  taggingFreq_ratio_C1->Divide(taggingFreq_PbPb_C1_data,taggingFreq_PbPb_C1_MC,1,1,"");
  taggingFreq_ratio_pp = (TH1D*) taggingFreq_pp_data->Clone("taggingFreq_ratio_pp");
  taggingFreq_ratio_pp->Divide(taggingFreq_pp_data,taggingFreq_pp_MC,1,1,"");

  TLatex *la = new TLatex();
  la->SetTextSize(0.06);

  TCanvas *canv_tf_pp = new TCanvas("canv_tf_pp","Tagging Freq - pp",700,700);
  canv_tf_pp->cd();
  TPad *pad_tf_pp = new TPad("pad_tf_pp","pad_tf_pp",0,0,1,1);
  pad_tf_pp->SetLeftMargin(0.15);
  pad_tf_pp->SetBottomMargin(0.15);
  pad_tf_pp->Draw();
  pad_tf_pp->cd();
  taggingFreq_pp_MC->SetLineColor(kBlue-4);
  taggingFreq_pp_data->SetLineColor(kRed-4);
  taggingFreq_ratio_pp->SetLineColor(kRed-4);
  taggingFreq_pp_MC->SetLineWidth(2);
  taggingFreq_pp_data->SetLineWidth(2);
  taggingFreq_ratio_pp->SetLineWidth(2);
  taggingFreq_pp_MC->GetYaxis()->SetTitle("Muon-tag frequency");
  taggingFreq_pp_MC->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  taggingFreq_pp_MC->GetYaxis()->SetRangeUser(0,0.01);
  taggingFreq_pp_MC->SetStats(0);
  taggingFreq_pp_MC->SetTitle("");
  taggingFreq_pp_MC->Draw();
  taggingFreq_pp_data->Draw("same");
  taggingFreq_ratio_pp->SetStats(0);
  taggingFreq_ratio_pp->SetTitle("");
  la->DrawLatexNDC(0.22,0.92,"pp");

  
  


  TCanvas *canv_tf_C2 = new TCanvas("canv_tf_C2","Tagging Freq - 30-90%",700,700);
  canv_tf_C2->cd();
  TPad *pad_tf_C2 = new TPad("pad_tf_C2","pad_tf_C2",0,0,1,1);
  pad_tf_C2->SetLeftMargin(0.15);
  pad_tf_C2->SetBottomMargin(0.15);
  pad_tf_C2->Draw();
  pad_tf_C2->cd();
  taggingFreq_PbPb_C2_MC->SetLineColor(kBlue-4);
  taggingFreq_PbPb_C2_data->SetLineColor(kRed-4);
  taggingFreq_ratio_C2->SetLineColor(kRed-4);
  taggingFreq_PbPb_C2_MC->SetLineWidth(2);
  taggingFreq_PbPb_C2_data->SetLineWidth(2);
  taggingFreq_ratio_C2->SetLineWidth(2);
  taggingFreq_PbPb_C2_MC->GetYaxis()->SetTitle("Muon-tag frequency");
  taggingFreq_PbPb_C2_MC->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  taggingFreq_PbPb_C2_MC->GetYaxis()->SetRangeUser(0,0.01);
  taggingFreq_PbPb_C2_MC->SetStats(0);
  taggingFreq_PbPb_C2_MC->SetTitle("");
  taggingFreq_PbPb_C2_MC->Draw();
  taggingFreq_PbPb_C2_data->Draw("same");
  // taggingFreq_ratio_C2->SetStats(0);
  // taggingFreq_ratio_C2->SetTitle("");
  // taggingFreq_ratio_C2->GetYaxis()->SetRangeUser(0.65,1.35);
  // taggingFreq_ratio_C2->Draw();
  la->DrawLatexNDC(0.22,0.92,"PbPb 30-90%");
  

  TCanvas *canv_tf_C1 = new TCanvas("canv_tf_C1","Tagging Freq - 0-30%",700,700);
  canv_tf_C1->cd();
  TPad *pad_tf_C1 = new TPad("pad_tf_C1","pad_tf_C1",0,0,1,1);
  pad_tf_C1->SetLeftMargin(0.15);
  pad_tf_C1->SetBottomMargin(0.15);
  pad_tf_C1->Draw();
  pad_tf_C1->cd();
  taggingFreq_PbPb_C1_MC->SetLineColor(kBlue-4);
  taggingFreq_PbPb_C1_data->SetLineColor(kRed-4);
  taggingFreq_ratio_C1->SetLineColor(kRed-4);
  taggingFreq_PbPb_C1_MC->SetLineWidth(2);
  taggingFreq_PbPb_C1_data->SetLineWidth(2);
  taggingFreq_ratio_C1->SetLineWidth(2);
  taggingFreq_PbPb_C1_MC->GetYaxis()->SetTitle("Muon-tag frequency");
  taggingFreq_PbPb_C1_MC->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  taggingFreq_PbPb_C1_MC->GetYaxis()->SetRangeUser(0,0.01);
  taggingFreq_PbPb_C1_MC->SetStats(0);
  taggingFreq_PbPb_C1_MC->SetTitle("");
  taggingFreq_PbPb_C1_MC->Draw();
  taggingFreq_PbPb_C1_data->Draw("same");
  // taggingFreq_ratio_C1->SetStats(0);
  // taggingFreq_ratio_C1->SetTitle("");
  // taggingFreq_ratio_C1->Draw();
  // taggingFreq_ratio_C1->GetYaxis()->SetRangeUser(0.65,1.35);
  la->DrawLatexNDC(0.22,0.92,"PbPb 0-30%");


  TH1D *ctp_data = (TH1D*) taggingFreq_PbPb_C1_data->Clone("ctp_data");
  ctp_data->Divide(taggingFreq_PbPb_C1_data,taggingFreq_PbPb_C2_data,1,1,"");
  TH1D *ctp_MC = (TH1D*) taggingFreq_PbPb_C1_MC->Clone("ctp_MC");
  ctp_MC->Divide(taggingFreq_PbPb_C1_MC,taggingFreq_PbPb_C2_MC,1,1,"");

  // ctp = central-to-peripheral
  TCanvas *canv_ctp = new TCanvas("canv_ctp","central-to-periph ratio",700,700);
  canv_ctp->cd();
  TPad *pad_ctp = new TPad("pad_ctp","pad_ctp",0,0,1,1);
  pad_ctp->SetLeftMargin(0.15);
  pad_ctp->SetBottomMargin(0.15);
  pad_ctp->Draw();
  pad_ctp->cd();
  ctp_data->GetYaxis()->SetTitle("Central/Periph. (Muon-tag frequency)");
  ctp_data->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  ctp_data->GetYaxis()->SetRangeUser(0,2);
  ctp_data->SetTitle("");
  ctp_data->SetStats(0);
  ctp_data->Draw();
  ctp_MC->Draw("same");
	       
  auto wf = TFile::Open(Form("./rootFiles/output%s.root",muonTagString.Data()),"recreate");

  taggingFreq_pp_MC->Write();
  taggingFreq_pp_data->Write();
  taggingFreq_PbPb_C2_MC->Write();
  taggingFreq_PbPb_C2_data->Write();
  taggingFreq_PbPb_C1_MC->Write();
  taggingFreq_PbPb_C1_data->Write();

  wf->Close();

}
