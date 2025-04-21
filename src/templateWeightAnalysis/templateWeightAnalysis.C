

void templateWeightAnalysis(){

  cout << "running templateWeightAnalysis()" << endl;

  TFile *F = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-25_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_weightCutOnLightJetTemplate_removeHYDJETjet0p45_fineCentBins_projectableTemplates_allTemplates.root");

  TH2D *H;
  const int NProjections = 2000;
  
  TH1D* h[NProjections];

  F->GetObject("h_templateWeight_muptrel_lJets_C1J1",H);

  int NLoopLow = 0;
  int NLoopHigh = 2000;

  TCanvas *canv = new TCanvas("canv","canvas",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.18);
  pad->SetBottomMargin(0.18);
  pad->Draw();
  pad->cd();

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.048);
  
  for(int i = NLoopLow; i < NLoopHigh; i++){
    h[i] = (TH1D*) H->ProjectionY(Form("h_proj_%i",i),0,NProjections-i);
    h[i]->Scale(1./h[i]->Integral());
    if(i==0){
      h[i]->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
      h[i]->GetXaxis()->SetRangeUser(0,5);
      h[i]->GetYaxis()->SetTitle("Weighted entries");
      
    }
    else{
      canv->Clear();
      h[0]->SetLineColor(kGray);
      h[0]->SetFillColorAlpha(kGray,0.6);
      h[i]->SetLineColor(kRed-4);
      h[0]->SetLineWidth(2);
      h[i]->SetLineWidth(2);
      h[0]->Draw("e2");
      h[i]->Draw("same");
      la->DrawLatexNDC(0.5,0.5,Form("weight < %1.5f",H->ProjectionX()->GetBinCenter(NProjections-i)));
      la->SetTextColor(kGray);
      la->DrawLatexNDC(0.5,0.4,"No weight cut");
      la->SetTextColor(kRed-4);
      la->DrawLatexNDC(0.5,0.32,"with weight cut");
      la->SetTextColor(kBlack);
      canv->SaveAs(Form("figures/canv_%i.png",i));
    }
   
    
  }

  

  

  
  // int plotNLow = 0;
  // int plotNHigh = 1200;

  // h[plotNLow]->SetLineColor(kBlue-4);
  // h[plotNHigh]->SetLineColor(kRed-4);
  // h[plotNLow]->SetLineWidth(2);
  // h[plotNHigh]->SetLineWidth(2);

  // h[plotNLow]->Draw();
  // h[plotNHigh]->Draw("same");

  // cout << "No cut entries = " << h[plotNLow]->GetEntries() << endl;
  // cout << "With cut entries = " << h[plotNHigh]->GetEntries() << endl;


}
