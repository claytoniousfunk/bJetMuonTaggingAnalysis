void tagging_in_MinBias(){

  // files
  TFile *f_mu5 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/localScans/pp_MinBias_scan_mu5.root");
  TFile *f_mu7 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/localScans/pp_MinBias_scan_mu7.root");
  TFile *f_mu12 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/localScans/pp_MinBias_scan_mu12.root");

  // histograms
  TH1D *a1, *b1, *c1, *rc1;
  TH1D *a2, *b2, *c2, *rc2;
  TH1D *a3, *b3, *c3, *rc3;

  f_mu5->GetObject("h_inclRecoJetPt",a1);

  f_mu5->GetObject("h_inclRecoJetPt_inclRecoMuonTag",b1);

  f_mu5->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",c1);
  f_mu7->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",c2);
  f_mu12->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",c3);

  a1->SetMarkerColor(kBlack);

  b1->SetMarkerColor(kRed+4);

  c1->SetMarkerColor(kBlue+4);
  c2->SetMarkerColor(kGreen+2);
  c3->SetMarkerColor(kMagenta);

  a1->SetLineColor(kBlack);
  b1->SetLineColor(kRed+4);

  c1->SetLineColor(kBlue+4);
  c2->SetLineColor(kGreen+2);
  c3->SetLineColor(kMagenta);

  // canvas
  TCanvas *canv1 = new TCanvas("canv1","canv1",700,700);

  TPad *p1_1 = new TPad("p1_1","p1_1",0,0.4,1,1);
  TPad *p2_1 = new TPad("p2_1","p2_1",0,0,1,0.4);


  p1_1->SetLeftMargin(0.2);
  p1_1->SetBottomMargin(0.0);
  p2_1->SetLeftMargin(0.2);
  p2_1->SetTopMargin(0.0);
  p2_1->SetBottomMargin(0.2);



  p1_1->SetLogy();

  
  canv1->cd();
  p1_1->Draw();
  p1_1->cd();
  a1->Draw();
  b1->Draw("same");
  
  
  






}
