


void hiBinShift(double jetPtLow = 80,
		double jetPtHigh = 100){

  TFile *f_DiJet_noShift = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  TFile *f_MuJet_noShift = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_MuJet_pThat-20_mu12_pTmu-14_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  TFile *f_BJet_noShift = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_BJet_pThat-20_mu12_pTmu-14_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_weightCut.root");
  
  TFile *f_DiJet_withShift = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-6-2.root");
  TFile *f_MuJet_withShift = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_MuJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-6-3.root");
  TFile *f_BJet_withShift = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_BJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-6-3.root");

 
  TH2D *H_DiJet_noShift, *H_MuJet_noShift, *H_BJet_noShift;
  TH2D *H_DiJet_withShift, *H_MuJet_withShift, *H_BJet_withShift;
  f_DiJet_noShift->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_DiJet_noShift);
  f_MuJet_noShift->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_MuJet_noShift);
  f_BJet_noShift->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_BJet_noShift);
  f_DiJet_withShift->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_DiJet_withShift);
  f_MuJet_withShift->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_MuJet_withShift);
  f_BJet_withShift->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_BJet_withShift);
  

  TH1D *binFinder = (TH1D*) H_DiJet_noShift->ProjectionY("binFinder");
  
  TH1D *h_DiJet_noShift = (TH1D*) H_DiJet_noShift->ProjectionX("h_DiJet_noShift",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));
  TH1D *h_MuJet_noShift = (TH1D*) H_MuJet_noShift->ProjectionX("h_MuJet_noShift",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));
  TH1D *h_BJet_noShift = (TH1D*) H_BJet_noShift->ProjectionX("h_BJet_noShift",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));
  
  TH1D *h_DiJet_withShift = (TH1D*) H_DiJet_withShift->ProjectionX("h_DiJet_withShift",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));
  TH1D *h_MuJet_withShift = (TH1D*) H_MuJet_withShift->ProjectionX("h_MuJet_withShift",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));
  TH1D *h_BJet_withShift = (TH1D*) H_BJet_withShift->ProjectionX("h_BJet_withShift",binFinder->FindBin(jetPtLow),binFinder->FindBin(jetPtHigh));

  TH1D *h0 = (TH1D*) h_DiJet_noShift->Clone("h0");
  h0->Add(h_MuJet_noShift);
  h0->Add(h_BJet_noShift);

  TH1D *h1 = (TH1D*) h_DiJet_withShift->Clone("h1");
  h1->Add(h_MuJet_withShift);
  h1->Add(h_BJet_withShift);

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
  h0->Draw("hist");
  h1->Draw("same hist");

  r->GetYaxis()->SetRangeUser(0,2);
  r->SetTitle("");
  r->SetStats(0);
  r->GetYaxis()->SetTitle("Shift / no-weight");
  r->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  //r->Draw();
  TLine *li = new TLine();
  li->SetLineStyle(7);
  //li->DrawLine(0,1,10,1);
  
  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.04);

  la->DrawLatexNDC(0.5,0.68,"PYTHIA+HYDJET 0-10%, #it{b}-jets");
  la->DrawLatexNDC(0.5,0.6,Form("%3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f",jetPtLow,jetPtHigh));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.5,0.52,"Previous shift (incorrect)");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.5,0.44,"New shift (correct)");
 
}
