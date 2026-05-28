


void plotResponseMatrix(){

  TFile *f_PY = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_vzReweight_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_2026-2-18_muTaggedJetsNoTrigger.root");
  TFile *f_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_leadingXjetDumpFilter_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_weightCut_2026-2-18_muTaggedJetsNoTrigger.root");

  TH2D *H_pp, *H_C4, *H_C3, *H_C2, *H_C1;
  f_PY->GetObject("h_matchedRecoJetPt_genJetPt_var_bJets",H_pp);
  f_PH->GetObject("h_matchedRecoJetPt_genJetPt_var_bJets_C4",H_C4);
  f_PH->GetObject("h_matchedRecoJetPt_genJetPt_var_bJets_C3",H_C3);
  f_PH->GetObject("h_matchedRecoJetPt_genJetPt_var_bJets_C2",H_C2);
  f_PH->GetObject("h_matchedRecoJetPt_genJetPt_var_bJets_C1",H_C1);

  H_pp->Scale(1./H_pp->Integral());
  H_C4->Scale(1./H_C4->Integral());
  H_C3->Scale(1./H_C3->Integral());
  H_C2->Scale(1./H_C2->Integral());
  H_C1->Scale(1./H_C1->Integral());

  double titleSize = 0.05;
  double yTitleSize = 0.043;
  double xTitleSize = 0.043;
  double yLabelSize = 0.035;
  double xLabelSize = 0.035;

  TCanvas *canv_pp = new TCanvas("canv_pp","canv_pp",700,700);
  canv_pp->cd();
  TPad *pad_pp = new TPad("pad_pp","pad_pp",0,0,1,1);
  pad_pp->SetLeftMargin(0.15);
  pad_pp->SetRightMargin(0.15);
  pad_pp->SetBottomMargin(0.15);
  pad_pp->SetLogz();
  pad_pp->Draw();
  pad_pp->cd();
  H_pp->SetStats(0);
  H_pp->SetTitleSize(titleSize);
  H_pp->SetTitle("PYTHIA, #it{b}-jets");
  H_pp->GetYaxis()->SetTitleSize(yTitleSize);
  H_pp->GetYaxis()->SetLabelSize(yLabelSize);
  H_pp->GetYaxis()->SetTitle("Generated Jet #it{p}_{T} [GeV]");
  H_pp->GetXaxis()->SetTitleSize(xTitleSize);
  H_pp->GetXaxis()->SetLabelSize(xLabelSize);
  H_pp->GetXaxis()->SetTitle("Reconstructed Jet #it{p}_{T} [GeV]");
  H_pp->Draw("colz");
  canv_pp->SaveAs("../../../figures/responseMatrix/bJetResponseMatrix_pp.pdf");

  TCanvas *canv_C4 = new TCanvas("canv_C4","canv_C4",700,700);
  canv_C4->cd();
  TPad *pad_C4 = new TPad("pad_C4","pad_C4",0,0,1,1);
  pad_C4->SetLeftMargin(0.15);
  pad_C4->SetRightMargin(0.15);
  pad_C4->SetBottomMargin(0.15);
  pad_C4->SetLogz();
  pad_C4->Draw();
  pad_C4->cd();
  H_C4->SetStats(0);
  H_C4->SetTitleSize(titleSize);
  H_C4->SetTitle("PYTHIA+HYDJET 50-80%, #it{b}-jets");
  H_C4->GetYaxis()->SetTitleSize(yTitleSize);
  H_C4->GetYaxis()->SetLabelSize(yLabelSize);
  H_C4->GetYaxis()->SetTitle("Generated Jet #it{p}_{T} [GeV]");
  H_C4->GetXaxis()->SetTitleSize(xTitleSize);
  H_C4->GetXaxis()->SetLabelSize(xLabelSize);
  H_C4->GetXaxis()->SetTitle("Reconstructed Jet #it{p}_{T} [GeV]");
  H_C4->Draw("colz");
  canv_C4->SaveAs("../../../figures/responseMatrix/bJetResponseMatrix_C4.pdf");

  TCanvas *canv_C3 = new TCanvas("canv_C3","canv_C3",700,700);
  canv_C3->cd();
  TPad *pad_C3 = new TPad("pad_C3","pad_C3",0,0,1,1);
  pad_C3->SetLeftMargin(0.15);
  pad_C3->SetRightMargin(0.15);
  pad_C3->SetBottomMargin(0.15);
  pad_C3->SetLogz();
  pad_C3->Draw();
  pad_C3->cd();
  H_C3->SetStats(0);
  H_C3->SetTitleSize(titleSize);
  H_C3->SetTitle("PYTHIA+HYDJET 30-50%, #it{b}-jets");
  H_C3->GetYaxis()->SetTitleSize(yTitleSize);
  H_C3->GetYaxis()->SetLabelSize(yLabelSize);
  H_C3->GetYaxis()->SetTitle("Generated Jet #it{p}_{T} [GeV]");
  H_C3->GetXaxis()->SetTitleSize(xTitleSize);
  H_C3->GetXaxis()->SetLabelSize(xLabelSize);
  H_C3->GetXaxis()->SetTitle("Reconstructed Jet #it{p}_{T} [GeV]");
  H_C3->Draw("colz");
  canv_C3->SaveAs("../../../figures/responseMatrix/bJetResponseMatrix_C3.pdf");

  TCanvas *canv_C2 = new TCanvas("canv_C2","canv_C2",700,700);
  canv_C2->cd();
  TPad *pad_C2 = new TPad("pad_C2","pad_C2",0,0,1,1);
  pad_C2->SetLeftMargin(0.15);
  pad_C2->SetRightMargin(0.15);
  pad_C2->SetBottomMargin(0.15);
  pad_C2->SetLogz();
  pad_C2->Draw();
  pad_C2->cd();
  H_C2->SetStats(0);
  H_C2->SetTitleSize(titleSize);
  H_C2->SetTitle("PYTHIA+HYDJET 10-30%, #it{b}-jets");
  H_C2->GetYaxis()->SetTitleSize(yTitleSize);
  H_C2->GetYaxis()->SetLabelSize(yLabelSize);
  H_C2->GetYaxis()->SetTitle("Generated Jet #it{p}_{T} [GeV]");
  H_C2->GetXaxis()->SetTitleSize(xTitleSize);
  H_C2->GetXaxis()->SetLabelSize(xLabelSize);
  H_C2->GetXaxis()->SetTitle("Reconstructed Jet #it{p}_{T} [GeV]");
  H_C2->Draw("colz");
  canv_C2->SaveAs("../../../figures/responseMatrix/bJetResponseMatrix_C2.pdf");

  TCanvas *canv_C1 = new TCanvas("canv_C1","canv_C1",700,700);
  canv_C1->cd();
  TPad *pad_C1 = new TPad("pad_C1","pad_C1",0,0,1,1);
  pad_C1->SetLeftMargin(0.15);
  pad_C1->SetRightMargin(0.15);
  pad_C1->SetBottomMargin(0.15);
  pad_C1->SetLogz();
  pad_C1->Draw();
  pad_C1->cd();
  H_C1->SetStats(0);
  H_C1->SetTitleSize(titleSize);
  H_C1->SetTitle("PYTHIA+HYDJET 0-10%, #it{b}-jets");
  H_C1->GetYaxis()->SetTitleSize(yTitleSize);
  H_C1->GetYaxis()->SetLabelSize(yLabelSize);
  H_C1->GetYaxis()->SetTitle("Generated Jet #it{p}_{T} [GeV]");
  H_C1->GetXaxis()->SetTitleSize(xTitleSize);
  H_C1->GetXaxis()->SetLabelSize(xLabelSize);
  H_C1->GetXaxis()->SetTitle("Reconstructed Jet #it{p}_{T} [GeV]");
  H_C1->Draw("colz");
  canv_C1->SaveAs("../../../figures/responseMatrix/bJetResponseMatrix_C1.pdf");
  

}
