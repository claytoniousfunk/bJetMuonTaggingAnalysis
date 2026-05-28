


void systematics_JERsmear_spectraEffect_bJets(bool doPP = 1,
					      bool doC4 = 0,
					      bool doC3 = 0,
					      bool doC2 = 0,
					      bool doC1 = 0){

  TFile *f_pp_incl_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-9-25.root");
  TFile *f_pp_incl_smear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_applyJERSmear_2025-9-25.root");
  TFile *f_pp_muTagged_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-9-25_muTaggedJets.root");
  TFile *f_pp_muTagged_smear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_applyJERSmear_2025-9-25_muTaggedJets.root");

  // // pThat > 20 GeV
  // TFile *f_PbPb_incl_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-9-19.root");
  // TFile *f_PbPb_incl_smear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_applyJERSmear_2025-11-4.root");
  // TFile *f_PbPb_muTagged_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-11-5_muTaggedJets.root");
  // TFile *f_PbPb_muTagged_smear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_applyJERSmear_2025-11-4_muTaggedJets.root");

  // pThat > 30 GeV
  TFile *f_PbPb_incl_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-30_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-11-5.root");
  TFile *f_PbPb_incl_smear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-30_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_applyJERSmear_2025-11-5.root");
  TFile *f_PbPb_muTagged_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-30_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-11-5_muTaggedJets.root");
  TFile *f_PbPb_muTagged_smear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-30_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_applyJERSmear_2025-11-5_muTaggedJets.root");


  TH2D *H_pp_incl_nom, *H_pp_incl_smear, *H_pp_muTagged_nom, *H_pp_muTagged_smear;
  TH1D *h_pp_incl_nom, *h_pp_incl_smear, *h_pp_muTagged_nom, *h_pp_muTagged_smear;

  if(doPP){
    f_pp_incl_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_pp_incl_nom);
    f_pp_incl_smear->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_pp_incl_smear);
    f_pp_muTagged_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_pp_muTagged_nom);
    f_pp_muTagged_smear->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H_pp_muTagged_smear);
  }
  else if(doC4){
    f_PbPb_incl_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C4",H_pp_incl_nom);
    f_PbPb_incl_smear->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C4",H_pp_incl_smear);
    f_PbPb_muTagged_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C4",H_pp_muTagged_nom);
    f_PbPb_muTagged_smear->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C4",H_pp_muTagged_smear);
  }
  else if(doC3){
    f_PbPb_incl_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C3",H_pp_incl_nom);
    f_PbPb_incl_smear->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C3",H_pp_incl_smear);
    f_PbPb_muTagged_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C3",H_pp_muTagged_nom);
    f_PbPb_muTagged_smear->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C3",H_pp_muTagged_smear);
  }
  else if(doC2){
    f_PbPb_incl_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H_pp_incl_nom);
    f_PbPb_incl_smear->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H_pp_incl_smear);
    f_PbPb_muTagged_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H_pp_muTagged_nom);
    f_PbPb_muTagged_smear->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C2",H_pp_muTagged_smear);
  }
  else if(doC1){
    f_PbPb_incl_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C1",H_pp_incl_nom);
    f_PbPb_incl_smear->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C1",H_pp_incl_smear);
    f_PbPb_muTagged_nom->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C1",H_pp_muTagged_nom);
    f_PbPb_muTagged_smear->GetObject("h_matchedRecoJetPt_genJetPt_bJets_C1",H_pp_muTagged_smear);
  }
  else{
    std::cout << "no object found, exiting...\n";
    return;
  }

  
  h_pp_incl_nom = (TH1D*) H_pp_incl_nom->ProjectionX("h_pp_incl_nom");
  h_pp_incl_smear = (TH1D*) H_pp_incl_smear->ProjectionX("h_pp_incl_smear");
  h_pp_muTagged_nom = (TH1D*) H_pp_muTagged_nom->ProjectionX("h_pp_muTagged_nom");
  h_pp_muTagged_smear = (TH1D*) H_pp_muTagged_smear->ProjectionX("h_pp_muTagged_smear");


  TH1D *R_pp_incl, *R_pp_muTagged;
  TH1D *F_pp_nom, *F_pp_smear;

  R_pp_incl = (TH1D*) h_pp_incl_smear->Clone("R_pp_incl");
  R_pp_muTagged = (TH1D*) h_pp_muTagged_smear->Clone("R_pp_muTagged");

  R_pp_incl->Divide(h_pp_incl_smear,h_pp_incl_nom,1,1,"B");
  R_pp_muTagged->Divide(h_pp_muTagged_smear,h_pp_muTagged_nom,1,1,"B");

  // R_pp_incl->Draw();
  // R_pp_muTagged->Draw("same");

  F_pp_nom = (TH1D*) h_pp_muTagged_nom->Clone("F_pp_nom");
  F_pp_smear = (TH1D*) h_pp_muTagged_smear->Clone("F_pp_smear");
  
  F_pp_nom->Divide(h_pp_muTagged_nom,h_pp_incl_nom,1,1,"B");
  F_pp_smear->Divide(h_pp_muTagged_smear,h_pp_incl_smear,1,1,"B");

  F_pp_nom->SetLineColor(kBlue-4);
  F_pp_smear->SetLineColor(kRed-4);

  F_pp_nom->SetLineWidth(2);
  F_pp_smear->SetLineWidth(2);

  TCanvas *canv_F = new TCanvas("canv_F","canv_F",700,700);
  canv_F->cd();
  TPad *pad_F = new TPad("pad_F","pad_F",0,0,1,1);
  pad_F->SetLeftMargin(0.15);
  pad_F->SetBottomMargin(0.15);
  pad_F->Draw();
  pad_F->cd();
  TLegend *leg_F = new TLegend(0.22,0.68,0.42,0.88);
  leg_F->SetBorderSize(0);
  leg_F->SetTextSize(0.035);
  leg_F->AddEntry(F_pp_nom,"nominal");
  leg_F->AddEntry(F_pp_smear,"smeared");
  F_pp_nom->SetTitle("");
  F_pp_nom->SetStats(0);
  F_pp_nom->GetXaxis()->SetLabelSize(0.035);
  F_pp_nom->GetXaxis()->SetTitleSize(0.045);
  F_pp_nom->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  F_pp_nom->GetYaxis()->SetLabelSize(0.035);
  F_pp_nom->GetYaxis()->SetTitleSize(0.045);
  F_pp_nom->GetYaxis()->SetTitle("#it{#mu}-tagged fraction");
  //F_pp_nom->GetYaxis()->SetRangeUser(0,0.015);
  F_pp_nom->GetYaxis()->SetRangeUser(0,0.15);
  F_pp_nom->Draw();
  F_pp_smear->Draw("same");
  leg_F->Draw();



  const int N_edge = 11;
  double newAxis[N_edge] = {30,40,50,60,80,100,120,150,200,300,500};

  F_pp_smear = (TH1D*) F_pp_smear->Rebin(N_edge-1,"F_pp_smear",newAxis);
  F_pp_nom = (TH1D*) F_pp_nom->Rebin(N_edge-1,"F_pp_nom",newAxis);


  TH1D *delta = (TH1D*) F_pp_smear->Clone("delta");
  delta->Divide(F_pp_smear,F_pp_nom,1,1,"");

  for(int i = 0; i < delta->GetSize(); i++){

  //   delta->SetBinContent(i,TMath::Abs(F_pp_smear->GetBinContent(i) - F_pp_nom->GetBinContent(i))/(0.5*(F_pp_nom->GetBinContent(i) + F_pp_smear->GetBinContent(i))));
  //   delta->SetBinError(i,delta->GetBinContent(i)*TMath::Sqrt((F_pp_smear->GetBinError(i)/F_pp_smear->GetBinContent(i))*(F_pp_smear->GetBinError(i)/F_pp_smear->GetBinContent(i)) + (F_pp_nom->GetBinError(i)/F_pp_nom->GetBinContent(i))*(F_pp_nom->GetBinError(i)/F_pp_nom->GetBinContent(i))));


    std::cout << "|1 - delta(" << i << ")| = " << fabs(1. - delta->GetBinContent(i)) << " +/- " << delta->GetBinError(i) << "\n";
    
  }


  TCanvas *canv_delta = new TCanvas("canv_delta","canv_delta",700,700);
  canv_delta->cd();
  TPad *pad_delta = new TPad("pad_delta","pad_delta",0,0,1,1);
  pad_delta->SetLeftMargin(0.15);
  pad_delta->SetBottomMargin(0.15);
  pad_delta->Draw();
  pad_delta->cd();
  delta->SetTitle("");
  delta->SetStats(0);
  delta->GetXaxis()->SetLabelSize(0.035);
  delta->GetXaxis()->SetTitleSize(0.045);
  delta->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  delta->GetYaxis()->SetLabelSize(0.035);
  delta->GetYaxis()->SetTitleSize(0.045);
  //delta->GetYaxis()->SetTitle("#Delta f / f");
  //delta->GetYaxis()->SetRangeUser(0,0.3);
  delta->GetYaxis()->SetTitle("Smeared / Nominal");
  delta->GetYaxis()->SetRangeUser(0.8,1.1);
  delta->Draw();

  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(newAxis[0],1,newAxis[N_edge-1],1);







  string canv_suffix = "";
  if(doPP) canv_suffix = "pp";
  else if(doC4) canv_suffix = "C4";
  else if(doC3) canv_suffix = "C3";
  else if(doC2) canv_suffix = "C2";
  else if(doC1) canv_suffix = "C1";
  else{};



  canv_F->SaveAs(Form("../../figures/systematics/JER-smear-spectra/muTaggedFraction_%s.pdf",canv_suffix.c_str()));
  canv_delta->SaveAs(Form("../../figures/systematics/JER-smear-spectra/delta_%s.pdf",canv_suffix.c_str()));


  auto wf = TFile::Open(Form("../../rootFiles/systematics/JER-smear-spectra/histograms_%s.root",canv_suffix.c_str()),"recreate");
  F_pp_nom->Write();
  F_pp_smear->Write();
  delta->Write();
  wf->Close();

  return;
  
  

}
