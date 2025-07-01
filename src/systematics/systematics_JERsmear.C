#include "../templateFitter/templateFitter.h"

void systematics_JERsmear(bool do_mu5 = 0,
			  bool do_mu7 = 0,
			  bool do_mu12 = 1){


  TLine *li = new TLine();
  li->SetLineStyle(7);

  TLatex *la = new TLatex();
  
  
  cout << endl;
  cout << "#######  SYSTEMATICS -- JER-smear  #########" << endl;
  cout << endl;

  TFile *file_b_noSmear, *file_b_smear;

  
  file_b_noSmear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/latest/bPurityResults_DATA-1_mergeB-1_mergeC-1_pTrel-0.0to5.0_cMult-1.0_bMult-1.0_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0_bJetEnergyShift-0.root");
  file_b_smear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/latest/bPurityResults_DATA-1_mergeB-1_mergeC-1_pTrel-0.0to5.0_cMult-1.0_bMult-1.0_JERsmear-1_JEUShiftUp-0_JEUShiftDown-0_bJetEnergyShift-0.root");
 
  TH1D *b_result_pp_noSmear, *b_result_pp_smear;
  TH1D *b_result_C3_noSmear, *b_result_C3_smear;
  TH1D *b_result_C2_noSmear, *b_result_C2_smear;
  TH1D *b_result_C1_noSmear, *b_result_C1_smear;

  file_b_noSmear->GetObject("bFracResults_pp",b_result_pp_noSmear);
  file_b_noSmear->GetObject("bFracResults_C3",b_result_C3_noSmear);
  file_b_noSmear->GetObject("bFracResults_C2",b_result_C2_noSmear);
  file_b_noSmear->GetObject("bFracResults_C1",b_result_C1_noSmear);

  file_b_smear->GetObject("bFracResults_pp",b_result_pp_smear);
  file_b_smear->GetObject("bFracResults_C3",b_result_C3_smear);
  file_b_smear->GetObject("bFracResults_C2",b_result_C2_smear);
  file_b_smear->GetObject("bFracResults_C1",b_result_C1_smear);


  b_result_C2_noSmear->Draw();
  b_result_C2_smear->Draw("same");


  
  TH1D *r_pp, *r_C2, *r_C1, *r_C3;

  r_pp = (TH1D*) b_result_pp_noSmear->Clone("r_pp");
  r_pp->Divide(b_result_pp_noSmear,b_result_pp_smear,1,1,"");

  r_C3 = (TH1D*) b_result_C3_noSmear->Clone("r_C3");
  r_C3->Divide(b_result_C3_noSmear,b_result_C3_smear,1,1,"");
  
  r_C2 = (TH1D*) b_result_C2_noSmear->Clone("r_C2");
  r_C2->Divide(b_result_C2_noSmear,b_result_C2_smear,1,1,"");

  r_C1 = (TH1D*) b_result_C1_noSmear->Clone("r_C1");
  r_C1->Divide(b_result_C1_noSmear,b_result_C1_smear,1,1,"");

  // stylize the curves
  r_pp->SetLineColor(kGreen+2);
  r_C3->SetLineColor(kRed-4);
  r_C2->SetLineColor(kBlue-4);
  r_C1->SetLineColor(kMagenta-9);

  r_pp->SetMarkerColor(kGreen+2);
  r_C3->SetMarkerColor(kRed-4);
  r_C2->SetMarkerColor(kBlue-4);
  r_C1->SetMarkerColor(kMagenta-9);

  r_pp->SetMarkerStyle(22);
  r_C3->SetMarkerStyle(23);
  r_C2->SetMarkerStyle(21);
  r_C1->SetMarkerStyle(20);

  double line_width = 2.7;
  double marker_size = 1.7;

  r_pp->SetMarkerSize(marker_size);
  r_C3->SetMarkerSize(marker_size);
  r_C2->SetMarkerSize(marker_size);
  r_C1->SetMarkerSize(marker_size);

  r_pp->SetLineWidth(line_width);
  r_C3->SetLineWidth(line_width);
  r_C2->SetLineWidth(line_width);
  r_C1->SetLineWidth(line_width);
  
  TCanvas *canv_mg_pp = new TCanvas("canv_mg_pp","canv_mg_pp",700,700);
  canv_mg_pp->cd();
  TPad *pad_mg_pp = new TPad("pad_mg_pp","pad_mg_pp",0,0,1,1);
  pad_mg_pp->SetLeftMargin(0.15);
  pad_mg_pp->SetBottomMargin(0.15);
  pad_mg_pp->Draw();
  pad_mg_pp->cd();
  // multigraph for pp
  r_C2->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  r_C2->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  r_C2->SetTitle("");
  r_C2->GetXaxis()->SetRangeUser(80,200);
  r_C2->GetYaxis()->SetRangeUser(0.4,1.6);
  r_C2->SetStats(0);
  r_C2->Draw();
  r_C1->Draw("same");
  r_pp->Draw("same");
  r_C3->Draw("same");



  
  TLegend *leg_r_pp = new TLegend(0.6,0.75,0.88,0.88);
  leg_r_pp->SetBorderSize(0);
  leg_r_pp->AddEntry(r_pp,"pp","p");
  leg_r_pp->AddEntry(r_C3,"PbPb 30-90%","p");
  leg_r_pp->AddEntry(r_C2,"PbPb 10-30%","p");
  leg_r_pp->AddEntry(r_C1,"PbPb 0-10%","p");
  leg_r_pp->Draw();
  li->DrawLine(0.6,1,1.4,1);
  la->SetTextSize(0.036);
  TString pp_data_info_string = "";
  TString pp_trigger_info_string = "";  
  pp_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}";
  pp_trigger_info_string = "#font[42]{#scale[0.8]{mu12 trigger}}";
  la->DrawLatexNDC(0.22,0.92,pp_data_info_string);
  //  la->DrawLatexNDC(0.25,0.83,pp_trigger_info_string);
  TString pp_canv_save_string = "";
  pp_canv_save_string = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/JER-smear/pp.pdf";
  
  // error values to print out on screen
  double err_pp_J1 = TMath::Abs(1.0 - r_pp->GetBinContent(1));
  double err_pp_J2 = TMath::Abs(1.0 - r_pp->GetBinContent(2));
  double err_pp_J3 = TMath::Abs(1.0 - r_pp->GetBinContent(3));
  double err_pp_J4 = TMath::Abs(1.0 - r_pp->GetBinContent(4));
  double err_pp_J5 = TMath::Abs(1.0 - r_pp->GetBinContent(5));
  double err_pp_J6 = TMath::Abs(1.0 - r_pp->GetBinContent(6));

  double err_C3_J1 = TMath::Abs(1.0 - r_C3->GetBinContent(1));
  double err_C3_J2 = TMath::Abs(1.0 - r_C3->GetBinContent(2));
  double err_C3_J3 = TMath::Abs(1.0 - r_C3->GetBinContent(3));
  double err_C3_J4 = TMath::Abs(1.0 - r_C3->GetBinContent(4));
  double err_C3_J5 = TMath::Abs(1.0 - r_C3->GetBinContent(5));
  double err_C3_J6 = TMath::Abs(1.0 - r_C3->GetBinContent(6));
  
  double err_C2_J1 = TMath::Abs(1.0 - r_C2->GetBinContent(1));
  double err_C2_J2 = TMath::Abs(1.0 - r_C2->GetBinContent(2));
  double err_C2_J3 = TMath::Abs(1.0 - r_C2->GetBinContent(3));
  double err_C2_J4 = TMath::Abs(1.0 - r_C2->GetBinContent(4));
  double err_C2_J5 = TMath::Abs(1.0 - r_C2->GetBinContent(5));
  double err_C2_J6 = TMath::Abs(1.0 - r_C2->GetBinContent(6));

  double err_C1_J1 = TMath::Abs(1.0 - r_C1->GetBinContent(1));
  double err_C1_J2 = TMath::Abs(1.0 - r_C1->GetBinContent(2));
  double err_C1_J3 = TMath::Abs(1.0 - r_C1->GetBinContent(3));
  double err_C1_J4 = TMath::Abs(1.0 - r_C1->GetBinContent(4));
  double err_C1_J5 = TMath::Abs(1.0 - r_C1->GetBinContent(5));
  double err_C1_J6 = TMath::Abs(1.0 - r_C1->GetBinContent(6));

  
  la->SetTextSize(0.026);
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.17,0.45,Form("%3.2f %%",100*err_pp_J1));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.17,0.42,Form("%3.2f %%",100*err_C3_J1));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.17,0.39,Form("%3.2f %%",100*err_C2_J1));
  la->SetTextColor(kMagenta-9);
  la->DrawLatexNDC(0.17,0.36,Form("%3.2f %%",100*err_C1_J1));

  la->SetTextSize(0.026);
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.21,0.31,Form("%3.2f %%",100*err_pp_J2));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.21,0.28,Form("%3.2f %%",100*err_C3_J2));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.21,0.25,Form("%3.2f %%",100*err_C2_J2));
  la->SetTextColor(kMagenta-9);
  la->DrawLatexNDC(0.21,0.21,Form("%3.2f %%",100*err_C1_J2));

  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.32,0.45,Form("%3.2f %%",100*err_pp_J3));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.32,0.42,Form("%3.2f %%",100*err_C3_J3));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.32,0.39,Form("%3.2f %%",100*err_C2_J3));
  la->SetTextColor(kMagenta-9);
  la->DrawLatexNDC(0.32,0.36,Form("%3.2f %%",100*err_C1_J3));

  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.45,0.32,Form("%3.2f %%",100*err_pp_J4));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.45,0.29,Form("%3.2f %%",100*err_C3_J4));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.45,0.26,Form("%3.2f %%",100*err_C2_J4));
  la->SetTextColor(kMagenta-9);
  la->DrawLatexNDC(0.45,0.23,Form("%3.2f %%",100*err_C1_J4));

  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.72,0.32,Form("%3.2f %%",100*err_pp_J5));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.72,0.29,Form("%3.2f %%",100*err_C2_J5));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.72,0.26,Form("%3.2f %%",100*err_C2_J5));
  la->SetTextColor(kMagenta-9);
  la->DrawLatexNDC(0.72,0.23,Form("%3.2f %%",100*err_C1_J5));

  // la->SetTextColor(kGreen+2);
  // la->DrawLatexNDC(0.82,0.32,Form("%3.2f %%",100*err_pp_J6));
  // la->SetTextColor(kRed-4);
  // la->DrawLatexNDC(0.82,0.29,Form("%3.2f %%",100*err_C2_J6));
  // la->SetTextColor(kBlue-4);
  // la->DrawLatexNDC(0.82,0.26,Form("%3.2f %%",100*err_C2_J6));
  // la->SetTextColor(kMagenta-9);
  // la->DrawLatexNDC(0.82,0.23,Form("%3.2f %%",100*err_C1_J6));

canv_mg_pp->SaveAs(pp_canv_save_string);

  
  
  
  
}
