
void flavor_difference(){

  TFile *f1, *f2, *f3, *f4;

  f1 = TFile::Open("../../rootFiles/bPurityResults/MC/bPurityResults_mu7_flavorForB.root");
  f2 = TFile::Open("../../rootFiles/bPurityResults/MC/bPurityResults_mu7_matchedPartonFlavor.root");
  f3 = TFile::Open("../../rootFiles/bPurityResults/DATA/bPurityResults_mu7_flavorForB.root");
  f4 = TFile::Open("../../rootFiles/bPurityResults/DATA/bPurityResults_mu7_matchedPartonFlavor.root");
  
  TH1D *a1, *a2, *a3, *a4;
  TH1D *b1, *b2, *b3, *b4;

  f1->GetObject("bFracResults_C1",a1);
  f2->GetObject("bFracResults_C1",a2);
  f3->GetObject("bFracResults_C1",a3);
  f4->GetObject("bFracResults_C1",a4);

  f1->GetObject("bFracResults_C2",b1);
  f2->GetObject("bFracResults_C2",b2);
  f3->GetObject("bFracResults_C2",b3);
  f4->GetObject("bFracResults_C2",b4);

  TH1D *d1 = (TH1D*) a1->Clone("d1");
  d1->Add(a2,-1);
  
  TH1D *d2 = (TH1D*) b1->Clone("d2");
  d2->Add(b2,-1);

  TH1D *D1 = (TH1D*) a3->Clone("D1");
  D1->Add(a4,-1);
  
  TH1D *D2 = (TH1D*) b3->Clone("D2");
  D2->Add(b4,-1);



  
  d1->SetLineColor(kBlue-4);
  d1->SetLineWidth(2);

  d2->SetLineColor(kRed-4);
  d2->SetFillColorAlpha(kRed-4,0.6);
  d2->SetLineWidth(2);

  D1->SetLineColor(kBlue-4);
  D1->SetLineWidth(2);

  D2->SetLineColor(kRed-4);
  D2->SetFillColorAlpha(kRed-4,0.6);
  D2->SetLineWidth(2);

  TCanvas *canv_1 = new TCanvas("canv_1","canv_1",700,700);
  canv_1->cd();
  TPad *pad_1 = new TPad("pad_1","pad_1",0,0,1,1);
  pad_1->SetLeftMargin(0.2);
  pad_1->SetBottomMargin(0.2);
  pad_1->Draw();
  pad_1->cd();
  d1->SetStats(0);
  d1->SetTitle("");
  d1->GetYaxis()->SetTitle("flavorForB - matchedParton");
  d1->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  d1->GetYaxis()->SetRangeUser(-0.2,0.2);
  d1->Draw();
  d2->Draw("e2 same");

  canv_1->SaveAs("~/Documents/nuclear/GroupMeeting/figures/2024-02-13/flavor_difference_MC.pdf");


  TCanvas *canv_2 = new TCanvas("canv_2","canv_2",700,700);
  canv_2->cd();
  TPad *pad_2 = new TPad("pad_2","pad_2",0,0,1,1);
  pad_2->SetLeftMargin(0.2);
  pad_2->SetBottomMargin(0.2);
  pad_2->Draw();
  pad_2->cd();
  D1->SetStats(0);
  D1->SetTitle("");
  D1->GetYaxis()->SetTitle("flavorForB - matchedParton");
  D1->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  D1->GetYaxis()->SetRangeUser(-0.2,0.2);
  D1->Draw();
  D2->Draw("e2 same");

  canv_2->SaveAs("~/Documents/nuclear/GroupMeeting/figures/2024-02-13/flavor_difference_DATA.pdf");

  
}
