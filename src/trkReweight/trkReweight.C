
/*

  Code for track reweighting.
  Going to take in the in-jet tracks and compare them to light in-jet muons.

  Here are the steps in this analysis:
  - Have a baseline comparison of the track-pTrel to muon-pTrel spectra (same kinematic cuts)
  - Derive a reweighting function from comparing the track-pT to the muon-pT spectra.
  - Reweight the tracks in a separate scan.
  - Compare again, show that the reweighting procedure worked.
  - Compare again the pTrel spectra, should also be aligned.

  Input:
  - ROOT file with in-jet track pT and pTrel.  This will be the output of PYTHIA*_jetTrkMax_scan.C.
  - ROOT file with in-jet muon pT and pTrel.  This will be the output of PYTHIA*_scan.C.

*/

void trkReweight(double jetPt_low = 200.,
		 double jetPt_high = 300.){



  // PbPb simulation files
  // TFile *file_trk = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/jetTrkMax/PYTHIAHYDJET_DiJet_jetTrkMax_fineCentBins_pThat-15_trkpT-14_correctHiBinShift.root");
  // TFile *file_mu = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/correctHiBinShift/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_vzReweight_hiBinReweight_jetTrkMaxFilter_removeHYDJETjet0p45_fineCentBins_projectableTemplates_allTemplates_correctHiBinShift.root");

  // pp simulation files
  TFile *file_trk = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/final/jetTrkMax/PYTHIA_DiJet_jetTrkMax_pThat-15_trkpT-14.root");
  TFile *file_mu = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/final/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjet_jetTrkMaxFilter_vzReweight_jetPtReweight_dRReweight_projectableTemplates.root");

  TH2D *H_trk, *H_mu;
  TH2D *H_mu_dJets, *H_mu_uJets, *H_mu_sJets, *H_mu_gJets, *H_mu_lJets;
  
  TH1D *h_trk, *h_mu;

  file_trk->GetObject("h_jetTrkMaxPtRel_J6",h_trk);
  file_mu->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_uJets",H_mu_uJets);
  file_mu->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_dJets",H_mu_dJets);
  file_mu->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_sJets",H_mu_sJets);
  file_mu->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_gJets",H_mu_gJets);

  H_mu_lJets = (TH2D*) H_mu_uJets->Clone("H_mu_lJets");
  H_mu_lJets->Add(H_mu_dJets);
  H_mu_lJets->Add(H_mu_sJets);
  H_mu_lJets->Add(H_mu_gJets);

  
  h_mu = (TH1D*) H_mu_lJets->ProjectionX("h_mu",H_mu_lJets->ProjectionY()->FindBin(jetPt_low),H_mu_lJets->ProjectionY()->FindBin(jetPt_high));

  h_trk->Scale(1./h_trk->Integral());
  h_mu->Scale(1./h_mu->Integral());
  

  
  h_trk->SetLineColor(kBlue-4);
  h_mu->SetLineColor(kRed-4);

  h_trk->SetLineWidth(2);
  h_mu->SetLineWidth(2);

  TH1D *r = (TH1D*) h_trk->Clone("r");
  r->Divide(h_trk,h_mu,1,1,"");
  
  
  TLegend *leg = new TLegend(0.6,0.6,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.045);
  leg->AddEntry(h_trk,"tracks","l");
  leg->AddEntry(h_mu,"light-jet muons","l");

  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad1 = new TPad("pad1","pad1",0,0.4,1,1);
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.4);
  pad1->SetBottomMargin(0);
  pad1->SetLeftMargin(0.15);
  pad1->SetTopMargin(0.1);
  pad2->SetBottomMargin(0.18);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0.);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();

  h_trk->GetXaxis()->SetRangeUser(0,5);
  h_trk->GetYaxis()->SetRangeUser(0,0.2);
  h_trk->SetTitle("In-jet track/muon spectra, 300 < #it{p}_{T}^{jet} (GeV) < 500");
  h_trk->GetYaxis()->SetLabelSize(0.04);
  h_trk->GetYaxis()->SetTitleSize(0.06);
  h_trk->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
  h_trk->SetStats(0);
  
  h_trk->Draw("hist");
  h_mu->Draw("hist same");
  leg->Draw();

  pad2->cd();
  r->GetXaxis()->SetRangeUser(0,50);
  r->GetXaxis()->SetLabelSize(0.06);
  r->GetXaxis()->SetTitleSize(0.08);
  r->GetYaxis()->SetLabelSize(0.06);
  r->GetYaxis()->SetTitleSize(0.08);
  r->GetXaxis()->SetTitle("Track/Muon #it{p}_{T}^{rel} [GeV]");
  r->GetYaxis()->SetTitle("Tracks / Muons");
  r->SetTitle("");
  r->SetStats(0);
  r->GetYaxis()->SetRangeUser(0,2);
  r->Draw("hist");
  //r->Fit("pol1","","",14,30);



  
  
}
