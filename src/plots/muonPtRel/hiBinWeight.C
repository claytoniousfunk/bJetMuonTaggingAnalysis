


void hiBinWeight(double jetPtLow = 80,
		 double jetPtHigh = 100){

  TFile *f_DiJet_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/merge/PYTHIAHYDJET_DiJet_merge_pThat-20_mu12_pTmu-14_tight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  TFile *f_MuJet_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_MuJet_pThat-20_mu12_pTmu-14_tight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  TFile *f_BJet_noWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_BJet_pThat-20_mu12_pTmu-14_tight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  
  TFile *f_DiJet_withWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/merge/PYTHIAHYDJET_DiJet_merge_pThat-20_mu12_pTmu-14_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  TFile *f_MuJet_withWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_MuJet_pThat-20_mu12_pTmu-14_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  TFile *f_BJet_withWeight = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_BJet_pThat-20_mu12_pTmu-14_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");

 
  TH2D *H_DiJet_noWeight, *H_MuJet_noWeight, *H_BJet_noWeight;
  TH2D *H_DiJet_withWeight, *H_MuJet_withWeight, *H_BJet_withWeight;
  f_DiJet_noWeight->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C1T0",H_DiJet_noWeight);
  f_MuJet_noWeight->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C1T0",H_MuJet_noWeight);
  f_BJet_noWeight->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C1T0",H_BJet_noWeight);
  f_DiJet_withWeight->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C1T0",H_DiJet_withWeight);
  f_MuJet_withWeight->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C1T0",H_MuJet_withWeight);
  f_BJet_withWeight->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C1T0",H_BJet_withWeight);
  

  TH1D *binFinder = (TH1D*) H_DiJet_noWeight->ProjectionY("binFinder");
  
  TH1D *h_DiJet_noWeight = (TH1D*) H_DiJet_noWeight->ProjectionX("h_DiJet_noWeight",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));
  TH1D *h_MuJet_noWeight = (TH1D*) H_MuJet_noWeight->ProjectionX("h_MuJet_noWeight",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));
  TH1D *h_BJet_noWeight = (TH1D*) H_BJet_noWeight->ProjectionX("h_BJet_noWeight",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));
  
  TH1D *h_DiJet_withWeight = (TH1D*) H_DiJet_withWeight->ProjectionX("h_DiJet_withWeight",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));
  TH1D *h_MuJet_withWeight = (TH1D*) H_MuJet_withWeight->ProjectionX("h_MuJet_withWeight",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));
  TH1D *h_BJet_withWeight = (TH1D*) H_BJet_withWeight->ProjectionX("h_BJet_withWeight",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));

  TH1D *h0 = (TH1D*) h_DiJet_noWeight->Clone("h0");
  h0->Add(h_MuJet_noWeight);
  h0->Add(h_BJet_noWeight);

  TH1D *h1 = (TH1D*) h_DiJet_withWeight->Clone("h1");
  h1->Add(h_MuJet_withWeight);
  h1->Add(h_BJet_withWeight);

  h0->Scale(1./h0->Integral());
  h1->Scale(1./h1->Integral());


  h0->SetLineColor(kBlue-4);
  h1->SetLineColor(kGreen+2);
  
  h0->SetLineWidth(2);
  h1->SetLineWidth(2);

  
  TH1D *r = (TH1D*) h1->Clone("r");
  r->Divide(h1,h0,1,1,"B");


  h0->SetStats(0);
  h0->SetTitle("");
  h0->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  // h0->Draw();
  // h1->Draw("same");

  r->GetYaxis()->SetRangeUser(0,2);
  r->SetTitle("");
  r->SetStats(0);
  r->GetYaxis()->SetTitle("Weight / no-weight");
  r->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  r->Draw();
  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(0,1,10,1);
  
  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.04);

  la->DrawLatexNDC(0.5,0.68,"PYTHIA+HYDJET 0-10%, #it{b}-jets");
  la->DrawLatexNDC(0.5,0.6,Form("%3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f",jetPtLow,jetPtHigh));
  la->SetTextColor(kBlue-4);
  // la->DrawLatexNDC(0.5,0.52,"No hiBin weight");
  la->SetTextColor(kGreen+2);
  // la->DrawLatexNDC(0.5,0.44,"with hiBin weight");
 
}
