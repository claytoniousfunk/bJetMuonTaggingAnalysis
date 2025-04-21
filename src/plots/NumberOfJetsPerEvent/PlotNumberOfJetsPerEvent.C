
void Stylize(TH1D *h1, TH1D *h2){
  h1->SetLineColor(kBlue-4);
  h1->SetMarkerColor(kBlue-4);
  h1->SetLineWidth(2);
  h2->SetLineColor(kRed-4);
  h2->SetMarkerColor(kRed-4);
  h2->SetLineWidth(2);
  return;
}

void Normalize(TH1D *h){
  int LowerBin = 0;
  int UpperBin = 0;
  LowerBin = h->FindBin(1.01); // 1 plus a small amount
  UpperBin = h->FindBin(99.9); // 100 minus a small amount
  double NormalizationConstant = h->Integral(LowerBin,UpperBin);
  h->Scale(1./NormalizationConstant);
  return;
}

void PlotNumberOfJetsPerEvent(){

  TFile *fileData, *fileMC;

  fileData = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/final/PbPb_SingleMuon_scan_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates.root");
  fileMC = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_removeHYDJETjet_jetTrkMaxFilter_vzReweight_hiBinReweight_fineCentBins_projectableTemplates_allTemplates.root");

  TH1D *NJetPerEventData, *NJetPerEventMC;
  TH1D *NMuTaggedJetPerEventData, *NMuTaggedJetPerEventMC;
  

  fileData->GetObject("h_NJetPerEvent_C1",NJetPerEventData);
  fileMC->GetObject("h_NJetPerEvent_C1",NJetPerEventMC);

  fileData->GetObject("h_NMuTaggedJetPerEvent_C1",NMuTaggedJetPerEventData);
  fileMC->GetObject("h_NMuTaggedJetPerEvent_C1",NMuTaggedJetPerEventMC);

  Stylize(NJetPerEventMC,NJetPerEventData);
  Stylize(NMuTaggedJetPerEventMC,NMuTaggedJetPerEventData);

  Normalize(NJetPerEventMC);
  Normalize(NJetPerEventData);
  Normalize(NMuTaggedJetPerEventMC);
  Normalize(NMuTaggedJetPerEventData);
  
  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->Draw();
  pad->cd();
  NMuTaggedJetPerEventMC->GetXaxis()->SetRangeUser(1,3);
  NMuTaggedJetPerEventMC->Draw("hist");
  NMuTaggedJetPerEventData->Draw("hist same");
  


}
