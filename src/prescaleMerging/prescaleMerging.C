void prescaleMerging(){

  TString prescale_1_filepath = "../../rootFiles/scanningOutput/pp/test_1.root";
  TString prescale_3_filepath = "../../rootFiles/scanningOutput/pp/test_3.root";
  TString prescale_5_filepath = "../../rootFiles/scanningOutput/pp/test_5.root";

  TFile *f_prescale_1 = TFile::Open(prescale_1_filepath);
  TFile *f_prescale_3 = TFile::Open(prescale_3_filepath);
  TFile *f_prescale_5 = TFile::Open(prescale_5_filepath);
 
  TH1D *h_1, *h_3, *h_5;

  f_prescale_1->GetObject("h_inclRecoJetPt",h_1);
  f_prescale_3->GetObject("h_inclRecoJetPt",h_3);
  f_prescale_5->GetObject("h_inclRecoJetPt",h_5);

  TCanvas *canv_1 = new TCanvas("canv_1","canv_1",700,700);
  canv_1->cd();
  TPad *pad_1_lower = new TPad("pad_1_lower","pad_1_lower",0,0,1,0.4);
  TPad *pad_1_upper = new TPad("pad_1_upper","pad_1_upper",0,0.4,1,1);
  pad_1_lower->SetLeftMargin(0.2);
  pad_1_upper->SetLeftMargin(0.2);
  pad_1_lower->SetBottomMargin(0.2);
  pad_1_upper->SetBottomMargin(0.0);
  pad_1_lower->SetTopMargin(0.0);
  pad_1_lower->Draw();
  pad_1_upper->Draw();
  pad_1_upper->cd();


  h_1->SetMarkerSize(0);
  h_1->SetLineColor(kBlue-4);
  h_1->SetFillColorAlpha(kBlue-4,0.6);

  h_3->SetMarkerSize(0);
  h_3->SetLineColor(kRed-4);
  h_3->SetFillColorAlpha(kRed-4,0.6);

  h_5->SetMarkerSize(0);
  h_5->SetLineColor(kGreen+2);
  h_5->SetFillColorAlpha(kGreen+2,0.6);

  
  h_1->Draw();
  h_3->Draw("same");
  h_5->Draw("same");

}
