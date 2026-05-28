

void rawDistributions(){



  // TFile *f_DiJet_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/merge/PYTHIAHYDJET_DiJet_merge_pThat-20_mu12_pTmu-14_tight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  // TFile *f_MuJet_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_MuJet_pThat-20_mu12_pTmu-14_tight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  // TFile *f_BJet_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_BJet_pThat-20_mu12_pTmu-14_tight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");

  TFile *f_DiJet_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/merge/PYTHIAHYDJET_DiJet_merge_pThat-20_mu12_pTmu-14_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  TFile *f_MuJet_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_MuJet_pThat-20_mu12_pTmu-14_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  TFile *f_BJet_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_BJet_pThat-20_mu12_pTmu-14_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");

  TH1D *h_DiJet_noWeight, *h_MuJet_noWeight, *h_BJet_noWeight;
  
  f_DiJet_noWeight->GetObject("h_hiBin_inclRecoMuonTag_triggerOn",h_DiJet_noWeight);
  f_MuJet_noWeight->GetObject("h_hiBin_inclRecoMuonTag_triggerOn",h_MuJet_noWeight);
  f_BJet_noWeight->GetObject("h_hiBin_inclRecoMuonTag_triggerOn",h_BJet_noWeight);

  h_DiJet_noWeight->Scale(1./h_DiJet_noWeight->Integral());
  h_MuJet_noWeight->Scale(1./h_MuJet_noWeight->Integral());
  h_BJet_noWeight->Scale(1./h_BJet_noWeight->Integral());

  h_DiJet_noWeight->SetLineColor(kBlack);
  h_MuJet_noWeight->SetLineColor(kBlue-4);
  h_BJet_noWeight->SetLineColor(kRed-4);

  h_DiJet_noWeight->SetLineWidth(3);
  h_MuJet_noWeight->SetLineWidth(3);
  h_BJet_noWeight->SetLineWidth(3);

  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.2);
  pad->SetBottomMargin(0.15);
  pad->SetRightMargin(0.1);
  pad->SetTopMargin(0.1);
  pad->Draw();
  pad->cd();
  h_DiJet_noWeight->SetStats(0);
  h_DiJet_noWeight->SetTitle(0);
  h_DiJet_noWeight->GetYaxis()->SetTitleSize(0.05);
  h_DiJet_noWeight->GetYaxis()->SetLabelSize(0.04);
  h_DiJet_noWeight->GetXaxis()->SetTitleSize(0.05);
  h_DiJet_noWeight->GetXaxis()->SetLabelSize(0.04);
  h_DiJet_noWeight->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d(hiBin)");
  h_DiJet_noWeight->GetXaxis()->SetTitle("hiBin");
  h_DiJet_noWeight->Draw("hist");
  h_MuJet_noWeight->Draw("hist same");
  h_BJet_noWeight->Draw("hist same");

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.045);
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.25,0.3,"DiJet sample");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.25,0.24,"MuJet sample");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.25,0.18,"BJet sample");

}
