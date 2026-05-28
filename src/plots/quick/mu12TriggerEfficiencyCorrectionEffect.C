


void mu12TriggerEfficiencyCorrectionEffect(double jetPt_low = 80,
					   double jetPt_high = 100){

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15_tight_WDecayFilter_2026-1-13.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/PbPb_SingleMuon_mu12_pTmu-15_tight_mu12TriggerEfficiencyCorrection_WDecayFilter_2026-2-9.root");

  TH2D *H1, *H2;
  TH1D *h1, *h2;

  f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C1",H1);
  f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C1",H2);

  double ss = 0.1;
  h1 = (TH1D*) H1->ProjectionX("h1",H1->ProjectionY()->FindBin(jetPt_low+ss),H1->ProjectionY()->FindBin(jetPt_high-ss),"");
  h2 = (TH1D*) H2->ProjectionX("h2",H2->ProjectionY()->FindBin(jetPt_low+ss),H2->ProjectionY()->FindBin(jetPt_high-ss),"");

  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);

  // h1->Scale(1./h1->Integral());
  // h2->Scale(1./h2->Integral());

  // h2->Draw("hist");
  // h1->Draw("hist same");

  TH1D *r = (TH1D*) h2->Clone("r");
  r->Divide(h2,h1,1,1,"B");

  r->GetYaxis()->SetRangeUser(0.7,1.3);
  r->Draw("hist");


}
