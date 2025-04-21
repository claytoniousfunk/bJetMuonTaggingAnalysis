


void xJetsPerEvent(){




  TFile *f1, *f2, *f3, *f4, *f5, *f6;

  TH2D *H1, *H2, *H3, *H4, *H5, *H6;
  TH1D *h1, *h2, *h3, *h4, *h5, *h6;
  TH1D *v1, *v2, *v3, *v4, *v5, *v6;


  f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/fineCentBins/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_removeHYDJETjet_jetTrkMaxFilter_vzReweight_hiBinReweight_weightCut0p005_fineCentBins_projectableTemplates.root");                                                                                                
  f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_noWeightCut_fineCentBins_projectableTemplates_allTemplates.root");                                                                                                      
  f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-25_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_noWeightCut_fineCentBins_projectableTemplates_allTemplates.root");                                                                                                      
  f4 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-25_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_noWeightCut_removeHYDJETjet_fineCentBins_projectableTemplates_allTemplates.root");                                                                                      
  f5 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-25_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_noWeightCut_removeHYDJETjet0p4_fineCentBins_projectableTemplates_allTemplates.root");                                                                                   
  f6 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-25_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_noWeightCut_removeHYDJETjet0p45_fineCentBins_projectableTemplates_allTemplates.root");

  f1->GetObject("h_inclRecoJetPt_flavor_C1", H1);
  f2->GetObject("h_inclRecoJetPt_flavor_C1", H2);
  f3->GetObject("h_inclRecoJetPt_flavor_C1", H3);
  f4->GetObject("h_inclRecoJetPt_flavor_C1", H4);
  f5->GetObject("h_inclRecoJetPt_flavor_C1", H5);
  f6->GetObject("h_inclRecoJetPt_flavor_C1", H6);

  f1->GetObject("h_vz_C1", v1);
  f2->GetObject("h_vz_C1", v2);
  f3->GetObject("h_vz_C1", v3);
  f4->GetObject("h_vz_C1", v4);
  f5->GetObject("h_vz_C1", v5);
  f6->GetObject("h_vz_C1", v6);
  

  TH1D *bf = (TH1D*) H1->ProjectionY("bf");
  double ss = 0.01;
    

  h1 = (TH1D*) H1->ProjectionX("h1",bf->FindBin(0.+ss),bf->FindBin(1.-ss));
  h2 = (TH1D*) H2->ProjectionX("h2",bf->FindBin(0.+ss),bf->FindBin(1.-ss));
  h3 = (TH1D*) H3->ProjectionX("h3",bf->FindBin(0.+ss),bf->FindBin(1.-ss));
  h4 = (TH1D*) H4->ProjectionX("h4",bf->FindBin(0.+ss),bf->FindBin(1.-ss));
  h5 = (TH1D*) H5->ProjectionX("h5",bf->FindBin(0.+ss),bf->FindBin(1.-ss));
  h6 = (TH1D*) H6->ProjectionX("h6",bf->FindBin(0.+ss),bf->FindBin(1.-ss));

  h1->Scale(1./v1->Integral());
  h2->Scale(1./v2->Integral());
  h3->Scale(1./v3->Integral());
  h4->Scale(1./v4->Integral());
  h5->Scale(1./v5->Integral());
  h6->Scale(1./v6->Integral());

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kRed-4);
  h4->SetLineColor(kGreen+2);
  h5->SetLineColor(kMagenta-9);
  h6->SetLineColor(kOrange);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  h5->SetLineWidth(2);
  h6->SetLineWidth(2);


  TLegend *leg = new TLegend(0.5,0.5,0.7,0.7);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->AddEntry(h1,"pThat > 15, weight < 0.005");
  leg->AddEntry(h2,"pThat > 15");
  leg->AddEntry(h3,"pThat > 25");
  leg->AddEntry(h4,"pThat > 25, pThat > 0.35* pTjet");
  leg->AddEntry(h5,"pThat > 25, pThat > 0.40* pTjet");
  leg->AddEntry(h6,"pThat > 25, pThat > 0.45* pTjet");
  
  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.15);
  pad->SetBottomMargin(0.15);
  pad->SetLogy();
  pad->Draw();
  pad->cd();
  h1->GetYaxis()->SetTitle("1/N^{evt} dN^{x-jet}/dp_{T} [GeV^{-1}]");
  h1->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
  h1->SetTitle("x-jets per event");
  h1->SetStats(0);
  h1->Draw("hist");
  h2->Draw("hist same");
  h3->Draw("hist same");
  h4->Draw("hist same");
  h5->Draw("hist same");
  h6->Draw("hist same");
  leg->Draw();


}
