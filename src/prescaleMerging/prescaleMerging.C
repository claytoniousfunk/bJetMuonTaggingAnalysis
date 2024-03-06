#include "../../headers/functions/divideByBinwidth.h"

void prescaleMerging(){

  // TString prescale_1_filepath = "../../rootFiles/scanningOutput/pp/pp_MinBias_Prescl_1_scan.root";
  // TString prescale_3_filepath = "../../rootFiles/scanningOutput/pp/pp_MinBias_Prescl_3_scan.root";
  // TString prescale_5_filepath = "../../rootFiles/scanningOutput/pp/pp_MinBias_Prescl_5_scan.root";

  TString prescale_1_filepath = "../../rootFiles/scanningOutput/PbPb/PbPb_MinBias_Prescl_1_scan.root";
  TString prescale_2_filepath = "../../rootFiles/scanningOutput/PbPb/PbPb_MinBias_Prescl_2_scan.root";
  TString prescale_3_filepath = "../../rootFiles/scanningOutput/PbPb/PbPb_MinBias_Prescl_3_scan.root";
  TString prescale_5_filepath = "../../rootFiles/scanningOutput/PbPb/PbPb_MinBias_Prescl_5_scan.root";
  TString prescale_7_filepath = "../../rootFiles/scanningOutput/PbPb/PbPb_MinBias_Prescl_7_scan.root";
  TString prescale_11_filepath = "../../rootFiles/scanningOutput/PbPb/PbPb_MinBias_Prescl_11_scan.root";
  TString prescale_13_filepath = "../../rootFiles/scanningOutput/PbPb/PbPb_MinBias_Prescl_13_scan.root";
  TString prescale_15_filepath = "../../rootFiles/scanningOutput/PbPb/PbPb_MinBias_Prescl_15_scan.root";
  TString prescale_17_filepath = "../../rootFiles/scanningOutput/PbPb/PbPb_MinBias_Prescl_17_scan.root";
  TString prescale_23_filepath = "../../rootFiles/scanningOutput/PbPb/PbPb_MinBias_Prescl_23_scan.root";
  
  TFile *f_prescale_1 = TFile::Open(prescale_1_filepath);
  TFile *f_prescale_2 = TFile::Open(prescale_2_filepath);
  TFile *f_prescale_3 = TFile::Open(prescale_3_filepath);
  TFile *f_prescale_5 = TFile::Open(prescale_5_filepath);
  TFile *f_prescale_7 = TFile::Open(prescale_7_filepath);
  TFile *f_prescale_11 = TFile::Open(prescale_11_filepath);
  TFile *f_prescale_13 = TFile::Open(prescale_13_filepath);
  TFile *f_prescale_15 = TFile::Open(prescale_15_filepath);
  TFile *f_prescale_17 = TFile::Open(prescale_17_filepath);
  TFile *f_prescale_23 = TFile::Open(prescale_23_filepath);
  
  TH1D *h_1, *h_2, *h_3, *h_5, *h_7, *h_11, *h_13, *h_15, *h_17, *h_23;

  f_prescale_1->GetObject("h_inclMuPt",h_1);
  f_prescale_2->GetObject("h_inclMuPt",h_2);
  f_prescale_3->GetObject("h_inclMuPt",h_3);
  f_prescale_5->GetObject("h_inclMuPt",h_5);
  f_prescale_7->GetObject("h_inclMuPt",h_7);
  f_prescale_11->GetObject("h_inclMuPt",h_11);
  f_prescale_13->GetObject("h_inclMuPt",h_13);
  f_prescale_15->GetObject("h_inclMuPt",h_15);
  f_prescale_17->GetObject("h_inclMuPt",h_17);
  f_prescale_23->GetObject("h_inclMuPt",h_23);
 


  double scalar_2 = h_2->Integral() / h_1->Integral();
  double scalar_3 = h_3->Integral() / h_1->Integral();
  double scalar_5 = h_5->Integral() / h_1->Integral();
  double scalar_7 = h_7->Integral() / h_1->Integral();
  double scalar_11 = h_11->Integral() / h_1->Integral();
  double scalar_13 = h_13->Integral() / h_1->Integral();
  double scalar_15 = h_15->Integral() / h_1->Integral();
  double scalar_17 = h_17->Integral() / h_1->Integral();
  double scalar_23 = h_23->Integral() / h_1->Integral();

  cout << "scalar_2 = " << scalar_2 << endl;
  cout << "scalar_3 = " << scalar_3 << endl;
  cout << "scalar_5 = " << scalar_5 << endl;
  cout << "scalar_7 = " << scalar_7 << endl;
  cout << "scalar_11 = " << scalar_11 << endl;
  cout << "scalar_13 = " << scalar_13 << endl;
  cout << "scalar_15 = " << scalar_15 << endl;
  cout << "scalar_17 = " << scalar_17 << endl;
  cout << "scalar_23 = " << scalar_23 << endl;


  //f_prescale_1->GetObject("h_inclRecoJetPt",h_1);
  //f_prescale_3->GetObject("h_inclRecoJetPt",h_3);
  //f_prescale_5->GetObject("h_inclRecoJetPt",h_5);

  TCanvas *canv_1 = new TCanvas("canv_1","canv_1",700,700);
  canv_1->cd();
  TPad *pad_1_lower = new TPad("pad_1_lower","pad_1_lower",0,0,1,0.4);
  TPad *pad_1_upper = new TPad("pad_1_upper","pad_1_upper",0,0.4,1,1);
  pad_1_lower->SetLeftMargin(0.2);
  pad_1_upper->SetLeftMargin(0.2);
  pad_1_lower->SetBottomMargin(0.2);
  pad_1_upper->SetBottomMargin(0.0);
  pad_1_lower->SetTopMargin(0.0);
  pad_1_upper->SetLogy();
  pad_1_lower->Draw();
  pad_1_upper->Draw();
  pad_1_upper->cd();


  h_1->SetMarkerSize(0);
  h_1->SetLineColor(1);
  h_1->SetLineWidth(3);
  h_1->SetFillColorAlpha(1,0.6);

  h_2->SetMarkerSize(0);
  h_2->SetLineColor(2);
  h_2->SetLineWidth(3);
  h_2->SetFillColorAlpha(2,0.6);

  h_3->SetMarkerSize(0);
  h_3->SetLineColor(2);
  h_3->SetLineWidth(3);
  h_3->SetFillColorAlpha(3,0.6);

  h_5->SetMarkerSize(0);
  h_5->SetLineColor(5);
  h_5->SetLineWidth(3);
  h_5->SetFillColorAlpha(5,0.6);

  h_7->SetMarkerSize(0);
  h_7->SetLineColor(7);
  h_7->SetLineWidth(3);
  h_7->SetFillColorAlpha(7,0.6);

  h_11->SetMarkerSize(0);
  h_11->SetLineColor(11);
  h_11->SetLineWidth(3);
  h_11->SetFillColorAlpha(11,0.6);

  h_13->SetMarkerSize(0);
  h_13->SetLineColor(13);
  h_13->SetLineWidth(3);
  h_13->SetFillColorAlpha(13,0.6);

  h_15->SetMarkerSize(0);
  h_15->SetLineColor(15);
  h_15->SetLineWidth(3);
  h_15->SetFillColorAlpha(15,0.6);

  h_17->SetMarkerSize(0);
  h_17->SetLineColor(17);
  h_17->SetLineWidth(3);
  h_17->SetFillColorAlpha(17,0.6);

  h_23->SetMarkerSize(0);
  h_23->SetLineColor(23);
  h_23->SetLineWidth(3);
  h_23->SetFillColorAlpha(23,0.6);

  const int N_edges = 7;
  double newPtAxis[N_edges] = {7,8,9,10,12,15,20};
  //double newPtAxis[N_edges] = {50,60,80,120,200,300,500};

  TH1D *h_1r = (TH1D*) h_1->Rebin(N_edges-1,"h_1r",newPtAxis);
  TH1D *h_2r = (TH1D*) h_2->Rebin(N_edges-1,"h_2r",newPtAxis);
  TH1D *h_3r = (TH1D*) h_3->Rebin(N_edges-1,"h_3r",newPtAxis);
  TH1D *h_5r = (TH1D*) h_5->Rebin(N_edges-1,"h_5r",newPtAxis);
  TH1D *h_7r = (TH1D*) h_7->Rebin(N_edges-1,"h_7r",newPtAxis);
  TH1D *h_11r = (TH1D*) h_11->Rebin(N_edges-1,"h_11r",newPtAxis);
  TH1D *h_13r = (TH1D*) h_13->Rebin(N_edges-1,"h_13r",newPtAxis);
  TH1D *h_15r = (TH1D*) h_15->Rebin(N_edges-1,"h_15r",newPtAxis);
  TH1D *h_17r = (TH1D*) h_17->Rebin(N_edges-1,"h_17r",newPtAxis);
  TH1D *h_23r = (TH1D*) h_23->Rebin(N_edges-1,"h_23r",newPtAxis);
  
  divideByBinwidth(h_1r); //h_1r->Scale(5.0);
  divideByBinwidth(h_2r); //h_1r->Scale(5.0);
  divideByBinwidth(h_3r); //h_3r->Scale(5.0);
  divideByBinwidth(h_5r); //h_5r->Scale(5.0);
  divideByBinwidth(h_7r); //h_7r->Scale(5.0);
  divideByBinwidth(h_11r); //h_11r->Scale(5.0);
  divideByBinwidth(h_13r); //h_13r->Scale(5.0);
  divideByBinwidth(h_15r); //h_15r->Scale(5.0);
  divideByBinwidth(h_17r); //h_17r->Scale(5.0);
  divideByBinwidth(h_23r); //h_17r->Scale(5.0);

  double yTitleSize_upper = 0.06;
  double yLabelSize_upper = 0.8 * yTitleSize_upper;

  double yTitleSize_lower = 0.09;
  double yLabelSize_lower = 0.9 * yTitleSize_lower;
  
  h_3r->GetYaxis()->SetTitle("Entries / GeV");
  h_3r->GetYaxis()->SetTitleSize(yTitleSize_upper);
  h_3r->GetYaxis()->SetLabelSize(yLabelSize_upper);

  h_3r->SetTitle("");
  h_3r->SetStats(0);
  
  h_3r->Draw();
  h_1r->Draw("same");
  h_2r->Draw("same");
  h_5r->Draw("same");
  h_7r->Draw("same");
  h_11r->Draw("same");
  h_13r->Draw("same");
  h_15r->Draw("same");
  h_17r->Draw("same");
  h_23r->Draw("same");
  
  TLegend *leg = new TLegend(0.6,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->AddEntry(h_1r,"Prescale 1 events","l");
  leg->AddEntry(h_2r,"Prescale 2 events","l");
  leg->AddEntry(h_3r,"Prescale 3 events","l");
  leg->AddEntry(h_5r,"Prescale 5 events","l");
  leg->AddEntry(h_7r,"Prescale 7 events","l");
  leg->AddEntry(h_11r,"Prescale 11 events","l");
  leg->AddEntry(h_13r,"Prescale 13 events","l");
  leg->AddEntry(h_15r,"Prescale 15 events","l");
  leg->AddEntry(h_17r,"Prescale 17 events","l");
  leg->AddEntry(h_23r,"Prescale 23 events","l");
  leg->Draw();

  TLatex *la = new TLatex();
  la->SetTextFont(62);
  la->SetTextSize(0.07);
  la->DrawLatexNDC(0.22,0.92,"CMS #scale[0.8]{#font[52]{Preliminary}}");
  la->SetTextFont(42);
  la->SetTextSize(0.058);
  la->DrawLatexNDC(0.62,0.92,"#sqrt{s_{NN}} = 5.02 TeV");

  pad_1_lower->cd();

  TH1D *r_3 = (TH1D*) h_3r->Clone("r_3");
  TH1D *r_2 = (TH1D*) h_2r->Clone("r_2");
  TH1D *r_5 = (TH1D*) h_5r->Clone("r_5");
  TH1D *r_7 = (TH1D*) h_7r->Clone("r_7");
  TH1D *r_11 = (TH1D*) h_11r->Clone("r_11");
  TH1D *r_13 = (TH1D*) h_13r->Clone("r_13");
  TH1D *r_15 = (TH1D*) h_15r->Clone("r_15");
  TH1D *r_17 = (TH1D*) h_17r->Clone("r_17");
  TH1D *r_23 = (TH1D*) h_17r->Clone("r_23");

  r_3->Divide(h_3r,h_1r,1,1,"");
  r_2->Divide(h_2r,h_1r,1,1,"");
  r_5->Divide(h_5r,h_1r,1,1,"");
  r_7->Divide(h_7r,h_1r,1,1,"");
  r_11->Divide(h_11r,h_1r,1,1,"");
  r_13->Divide(h_13r,h_1r,1,1,"");
  r_15->Divide(h_15r,h_1r,1,1,"");
  r_17->Divide(h_17r,h_1r,1,1,"");
  r_23->Divide(h_23r,h_1r,1,1,"");

  
  r_3->GetYaxis()->SetTitle("Ratio w.r.t. Prescale 1");
  r_3->GetXaxis()->SetTitle("#font[52]{p}_{T}^{#mu} [GeV]");
  //r_3->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");

  r_3->GetYaxis()->SetTitleSize(yTitleSize_lower);
  r_3->GetYaxis()->SetLabelSize(yLabelSize_lower);
  r_3->GetXaxis()->SetTitleSize(yTitleSize_lower);
  r_3->GetXaxis()->SetLabelSize(yLabelSize_lower);

  r_3->Draw();
  r_2->Draw("same");
  r_5->Draw("same");
  r_7->Draw("same");
  r_11->Draw("same");
  r_13->Draw("same");
  r_15->Draw("same");
  r_17->Draw("same");
  r_23->Draw("same");


  cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << " Prescale_1 entries = " << h_1->GetEntries() << endl;
  cout << " Prescale_2 entries = " << h_2->GetEntries() << endl;
  cout << " Prescale_3 entries = " << h_3->GetEntries() << endl;
  cout << " Prescale_5 entries = " << h_5->GetEntries() << endl;
  cout << " Prescale_7 entries = " << h_7->GetEntries() << endl;
  cout << " Prescale_11 entries = " << h_11->GetEntries() << endl;
  cout << " Prescale_13 entries = " << h_13->GetEntries() << endl;
  cout << " Prescale_15 entries = " << h_15->GetEntries() << endl;
  cout << " Prescale_17 entries = " << h_17->GetEntries() << endl;
  cout << " Prescale_23 entries = " << h_23->GetEntries() << endl;

  cout << "PRESCALE 2 FIT" << endl ;
  r_2->Fit("pol0");
  cout << "PRESCALE 3 FIT" << endl ;
  r_3->Fit("pol0");
  cout << "PRESCALE 5 FIT" << endl ;
  r_5->Fit("pol0");
  cout << "PRESCALE 7 FIT" << endl ;
  r_7->Fit("pol0");
  cout << "PRESCALE 11 FIT" << endl ;
  r_11->Fit("pol0");
  cout << "PRESCALE 13 FIT" << endl ;
  r_13->Fit("pol0");
  cout << "PRESCALE 15 FIT" << endl ;
  r_15->Fit("pol0");
  cout << "PRESCALE 17 FIT" << endl ;
  r_17->Fit("pol0");
  cout << "PRESCALE 23 FIT" << endl ;
  r_23->Fit("pol0");



  cout << endl;
  cout << " LATER! " << endl;
  cout << endl;


  
}
