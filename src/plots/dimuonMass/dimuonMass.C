


void dimuonMass(){

  // TFile *f_pp = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_HighEGJet_Jet80HLT_mu12_pTmu-15to999_tight_deltaR-40_jetTrkMaxFilter_2026-3-2.root");
  // TFile *f_PbPb = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_HardProbes_Jet80HLT_mu12_pTmu-15_tight_WDecayFilter_2026-2-12.root");

  TFile *f_pp = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/pp_SingleMuon_mu12_pTmu-15to999_tight_deltaR-40_mu12TriggerEfficiencyCorrection_jetTrkMaxFilter_WDecayFilter_2026-5-4.root");
  //TFile *f_PbPb = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15to999_tight_mu12TriggerEfficiencyCorrection_jetTrkMaxFilter_WDecayFilter_2026-5-4.root");
  TFile *f_PbPb = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-20to999_tight_mu12TriggerEfficiencyCorrection_jetTrkMaxFilter_WDecayFilter_2026-5-7_periphTo90.root");
  // TFile *f_PbPb = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15to999_tight_mu12TriggerEfficiencyCorrection_jetTrkMaxFilter_WDecayFilter_2026-4-21.root");

  TH1D *h_pp, *h_C4, *h_C3, *h_C2, *h_C1, *h_C0;

  f_pp->GetObject("h_dimuonMass",h_pp);
  f_PbPb->GetObject("h_dimuonMass_C4",h_C4);
  f_PbPb->GetObject("h_dimuonMass_C3",h_C3);
  f_PbPb->GetObject("h_dimuonMass_C2",h_C2);
  f_PbPb->GetObject("h_dimuonMass_C1",h_C1);

  // // reco eff correction

  double muonRecoEff_pp = 0.9708;
  double muonRecoEff_C4 = 0.9778;
  double muonRecoEff_C3 = 0.9856;
  double muonRecoEff_C2 = 0.9069;
  double muonRecoEff_C1 = 0.8627;

  
  h_pp->Scale(1./(muonRecoEff_pp*muonRecoEff_pp));
  h_C4->Scale(1./(muonRecoEff_C4*muonRecoEff_C4));
  h_C3->Scale(1./(muonRecoEff_C3*muonRecoEff_C3));
  h_C2->Scale(1./(muonRecoEff_C2*muonRecoEff_C2));
  h_C1->Scale(1./(muonRecoEff_C1*muonRecoEff_C1));


  TLatex *la = new TLatex();
  la->SetTextSize(0.035);

    
  double xLabelSize = 0.040;
  double xTitleSize = 0.050;
  double yLabelSize = 0.040;
  double yTitleSize = 0.050;

  TCanvas *canv_pp = new TCanvas("canv_pp","canv_pp",700,700);
  canv_pp->cd();
  TPad *pad_pp = new TPad("pad_pp","pad_pp",0,0,1,1);
  pad_pp->SetLeftMargin(0.18);
  pad_pp->SetBottomMargin(0.15);
  pad_pp->Draw();
  pad_pp->cd();
  h_pp->SetStats(0);
  h_pp->SetTitle("pp");
  h_pp->GetXaxis()->SetLabelSize(xLabelSize);
  h_pp->GetXaxis()->SetTitleSize(xTitleSize);
  h_pp->GetXaxis()->SetTitle("#it{m}_{#it{#mu}#it{#mu}} [GeV]");
  h_pp->GetYaxis()->SetLabelSize(yLabelSize);
  h_pp->GetYaxis()->SetTitleSize(yTitleSize);
  h_pp->GetYaxis()->SetTitle("Entries");
  h_pp->Draw();
  la->DrawLatexNDC(0.23,0.4,Form("#it{N}_{#it{Z}} = %5.0f",h_pp->Integral(h_pp->GetXaxis()->FindBin(75),h_pp->GetYaxis()->FindBin(105))));

  ///////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C4 = new TCanvas("canv_C4","canv_C4",700,700);
  canv_C4->cd();
  TPad *pad_C4 = new TPad("pad_C4","pad_C4",0,0,1,1);
  pad_C4->SetLeftMargin(0.18);
  pad_C4->SetBottomMargin(0.15);
  pad_C4->Draw();
  pad_C4->cd();
  h_C4->SetStats(0);
  //h_C4->SetTitle("PbPb 50-80%");
  h_C4->SetTitle("PbPb 50-90%");
  h_C4->GetXaxis()->SetLabelSize(xLabelSize);
  h_C4->GetXaxis()->SetTitleSize(xTitleSize);
  h_C4->GetXaxis()->SetTitle("#it{m}_{#it{#mu}#it{#mu}} [GeV]");
  h_C4->GetYaxis()->SetLabelSize(yLabelSize);
  h_C4->GetYaxis()->SetTitleSize(yTitleSize);
  h_C4->GetYaxis()->SetTitle("Entries");
  h_C4->Draw();
  la->DrawLatexNDC(0.23,0.4,Form("#it{N}_{#it{Z}} = %5.0f",h_C4->Integral(h_C4->GetXaxis()->FindBin(75),h_C4->GetYaxis()->FindBin(105))));

  ///////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C3 = new TCanvas("canv_C3","canv_C3",700,700);
  canv_C3->cd();
  TPad *pad_C3 = new TPad("pad_C3","pad_C3",0,0,1,1);
  pad_C3->SetLeftMargin(0.18);
  pad_C3->SetBottomMargin(0.15);
  pad_C3->Draw();
  pad_C3->cd();
  h_C3->SetStats(0);
  h_C3->SetTitle("PbPb 30-50%");
  h_C3->GetXaxis()->SetLabelSize(xLabelSize);
  h_C3->GetXaxis()->SetTitleSize(xTitleSize);
  h_C3->GetXaxis()->SetTitle("#it{m}_{#it{#mu}#it{#mu}} [GeV]");
  h_C3->GetYaxis()->SetLabelSize(yLabelSize);
  h_C3->GetYaxis()->SetTitleSize(yTitleSize);
  h_C3->GetYaxis()->SetTitle("Entries");
  h_C3->Draw();
  la->DrawLatexNDC(0.23,0.4,Form("#it{N}_{#it{Z}} = %5.0f",h_C3->Integral(h_C3->GetXaxis()->FindBin(75),h_C3->GetYaxis()->FindBin(105))));

  ///////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C2 = new TCanvas("canv_C2","canv_C2",700,700);
  canv_C2->cd();
  TPad *pad_C2 = new TPad("pad_C2","pad_C2",0,0,1,1);
  pad_C2->SetLeftMargin(0.18);
  pad_C2->SetBottomMargin(0.15);
  pad_C2->Draw();
  pad_C2->cd();
  h_C2->SetStats(0);
  h_C2->SetTitle("PbPb 10-30%");
  h_C2->GetXaxis()->SetLabelSize(xLabelSize);
  h_C2->GetXaxis()->SetTitleSize(xTitleSize);
  h_C2->GetXaxis()->SetTitle("#it{m}_{#it{#mu}#it{#mu}} [GeV]");
  h_C2->GetYaxis()->SetLabelSize(yLabelSize);
  h_C2->GetYaxis()->SetTitleSize(yTitleSize);
  h_C2->GetYaxis()->SetTitle("Entries");
  h_C2->Draw();
  la->DrawLatexNDC(0.23,0.4,Form("#it{N}_{#it{Z}} = %5.0f",h_C2->Integral(h_C2->GetXaxis()->FindBin(75),h_C2->GetYaxis()->FindBin(105))));
  
  ///////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C1 = new TCanvas("canv_C1","canv_C1",700,700);
  canv_C1->cd();
  TPad *pad_C1 = new TPad("pad_C1","pad_C1",0,0,1,1);
  pad_C1->SetLeftMargin(0.18);
  pad_C1->SetBottomMargin(0.15);
  pad_C1->Draw();
  pad_C1->cd();
  h_C1->SetStats(0);
  h_C1->SetTitle("PbPb 0-10%");
  h_C1->GetXaxis()->SetLabelSize(xLabelSize);
  h_C1->GetXaxis()->SetTitleSize(xTitleSize);
  h_C1->GetXaxis()->SetTitle("#it{m}_{#it{#mu}#it{#mu}} [GeV]");
  h_C1->GetYaxis()->SetLabelSize(yLabelSize);
  h_C1->GetYaxis()->SetTitleSize(yTitleSize);
  h_C1->GetYaxis()->SetTitle("Entries");
  h_C1->Draw();
  la->DrawLatexNDC(0.23,0.4,Form("#it{N}_{#it{Z}} = %5.0f",h_C1->Integral(h_C1->GetXaxis()->FindBin(75),h_C1->GetYaxis()->FindBin(105))));


  ////// save canvases
  canv_pp->SaveAs("../../../figures/dimuonMass/dimuonMass_pp.pdf");
  canv_C4->SaveAs("../../../figures/dimuonMass/dimuonMass_C4.pdf");
  canv_C3->SaveAs("../../../figures/dimuonMass/dimuonMass_C3.pdf");
  canv_C2->SaveAs("../../../figures/dimuonMass/dimuonMass_C2.pdf");
  canv_C1->SaveAs("../../../figures/dimuonMass/dimuonMass_C1.pdf");



}
