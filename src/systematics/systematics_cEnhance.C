#include "../templateFitter/templateFitter.h"

void systematics_cEnhance(bool do_mu5 = 0,
			  bool do_mu7 = 0,
			  bool do_mu12 = 1){


  TLine *li = new TLine();
  li->SetLineStyle(7);

  TLatex *la = new TLatex();
  
  
  cout << endl;
  cout << "#######  SYSTEMATICS -- C-ENHANCEMENT  #########" << endl;
  cout << endl;

  TFile *file_b_noEnhance, *file_b_cEnhance;

  if(do_mu5){
    file_b_noEnhance = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/bPurityResults_DATA-1_mu5-1_mu7-0_mu12-0_mergeB-1_mergeC-0_pTrel-0.0-5.0_cMult-1.0_bMult-1.2-JERsmear-0.root");
    file_b_cEnhance = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/bPurityResults_DATA-1_mu5-1_mu7-0_mu12-0_mergeB-1_mergeC-1_pTrel-0.0-5.0_cMult-1.0_bMult-1.2-JERsmear-0.root");
  }
  else if(do_mu7){
    file_b_noEnhance = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/golden/bPurityResults_DATA-1_mu5-0_mu7-1_mu12-0_mergeB-1_mergeC-0_pTrel-0.0to5.0_cMult-1.0_bMult-1.2_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0.root");
    file_b_cEnhance = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/golden/bPurityResults_DATA-1_mu5-0_mu7-1_mu12-0_mergeB-1_mergeC-1_pTrel-0.0to5.0_cMult-1.0_bMult-1.2_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0.root");
  }
  else if(do_mu12){
    file_b_noEnhance = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/golden/bPurityResults_DATA-1_mu5-0_mu7-0_mu12-1_mergeB-1_mergeC-0_pTrel-0.0to5.0_cMult-1.0_bMult-1.2_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0.root");
    file_b_cEnhance = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/golden/bPurityResults_DATA-1_mu5-0_mu7-0_mu12-1_mergeB-1_mergeC-1_pTrel-0.0to5.0_cMult-1.0_bMult-1.2_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0.root");
  }
  else{};
  
  TH1D *b_result_pp_noEnhance, *b_result_pp_cEnhance;
  TH1D *b_result_C2_noEnhance, *b_result_C2_cEnhance;
  TH1D *b_result_C1_noEnhance, *b_result_C1_cEnhance;

  file_b_noEnhance->GetObject("bFracResults_pp",b_result_pp_noEnhance);
  file_b_noEnhance->GetObject("bFracResults_C2",b_result_C2_noEnhance);
  file_b_noEnhance->GetObject("bFracResults_C1",b_result_C1_noEnhance);

  file_b_cEnhance->GetObject("bFracResults_pp",b_result_pp_cEnhance);
  file_b_cEnhance->GetObject("bFracResults_C2",b_result_C2_cEnhance);
  file_b_cEnhance->GetObject("bFracResults_C1",b_result_C1_cEnhance);


  b_result_C2_noEnhance->Draw();
  b_result_C2_cEnhance->Draw("same");


  
  TH1D *r_pp, *r_C2, *r_C1;
  r_pp = (TH1D*) b_result_pp_noEnhance->Clone("r_pp");
  r_pp->Divide(b_result_pp_noEnhance,b_result_pp_cEnhance,1,1,"");

  r_C2 = (TH1D*) b_result_C2_noEnhance->Clone("r_C2");
  r_C2->Divide(b_result_C2_noEnhance,b_result_C2_cEnhance,1,1,"");

  r_C1 = (TH1D*) b_result_C1_noEnhance->Clone("r_C1");
  r_C1->Divide(b_result_C1_noEnhance,b_result_C1_cEnhance,1,1,"");

  // stylize the curves
  r_pp->SetLineColor(kGreen+2);
  r_C2->SetLineColor(kRed-4);
  r_C1->SetLineColor(kBlue-4);

  r_pp->SetMarkerColor(kGreen+2);
  r_C2->SetMarkerColor(kRed-4);
  r_C1->SetMarkerColor(kBlue-4);

  r_pp->SetMarkerStyle(22);
  r_C2->SetMarkerStyle(21);
  r_C1->SetMarkerStyle(20);
  
  TCanvas *canv_mg_pp = new TCanvas("canv_mg_pp","canv_mg_pp",700,700);
  canv_mg_pp->cd();
  TPad *pad_mg_pp = new TPad("pad_mg_pp","pad_mg_pp",0,0,1,1);
  pad_mg_pp->SetLeftMargin(0.2);
  pad_mg_pp->SetBottomMargin(0.2);
  pad_mg_pp->Draw();
  pad_mg_pp->cd();
  // multigraph for pp
  r_C2->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  r_C2->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  r_C2->SetTitle("");
  r_C2->GetXaxis()->SetRangeUser(60,200);
  r_C2->GetYaxis()->SetRangeUser(0.4,1.6);
  r_C2->SetStats(0);
  r_C2->Draw();
  r_C1->Draw("same");



  
  TLegend *leg_r_pp = new TLegend(0.6,0.75,0.88,0.88);
  leg_r_pp->SetBorderSize(0);
  leg_r_pp->AddEntry(r_C2,"PbPb 30-90%","p");
  leg_r_pp->AddEntry(r_C1,"PbPb 0-30%","p");
  leg_r_pp->Draw();
  li->DrawLine(0.6,1,1.4,1);
  la->SetTextSize(0.036);
  TString pp_data_info_string = "";
  TString pp_trigger_info_string = "";
  if(do_mu5 == 1){
    pp_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}";
    pp_trigger_info_string = "#font[42]{#scale[0.8]{mu5 trigger}}";
  }
  else if(do_mu7 == 1){
    pp_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}";
    pp_trigger_info_string = "#font[42]{#scale[0.8]{mu7 trigger}}";
  }
  else if(do_mu12 == 1){
    pp_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}";
    pp_trigger_info_string = "#font[42]{#scale[0.8]{mu12 trigger}}";
  }
  la->DrawLatexNDC(0.22,0.92,pp_data_info_string);
  la->DrawLatexNDC(0.25,0.83,pp_trigger_info_string);
  TString pp_canv_save_string = "";
  if(do_mu5 == 1) pp_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-enhance/pp_mu5.pdf";
  else if(do_mu7 == 1) pp_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-enhance/pp_mu7.pdf";
  else if(do_mu12 == 1) pp_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-enhance/pp_mu12.pdf";
  else{};

  // error values to print out on screen
  double err_C2_J2 = TMath::Abs(1.0 - r_C2->GetBinContent(1));
  double err_C2_J3 = TMath::Abs(1.0 - r_C2->GetBinContent(2));
  double err_C2_J4 = TMath::Abs(1.0 - r_C2->GetBinContent(3));
  double err_C1_J2 = TMath::Abs(1.0 - r_C1->GetBinContent(1));
  double err_C1_J3 = TMath::Abs(1.0 - r_C1->GetBinContent(2));
  double err_C1_J4 = TMath::Abs(1.0 - r_C1->GetBinContent(3));

  
  la->SetTextSize(0.027);
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.22,0.35,Form("%3.2f percent",100*err_C2_J2));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.22,0.31,Form("%3.2f percent",100*err_C1_J2));

  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.34,0.27,Form("%3.2f percent",100*err_C2_J3));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.34,0.23,Form("%3.2f percent",100*err_C1_J3));

  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.62,0.32,Form("%3.2f percent",100*err_C2_J4));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.62,0.28,Form("%3.2f percent",100*err_C1_J4));


  // la->SetTextSize(0.032);
  // la->SetTextColor(kBlue-4);
  // la->DrawLatexNDC(0.3,0.35,Form("%3.2f percent",100*sys_err_val_pp_J2));
  // la->SetTextColor(kRed-4);
  // la->DrawLatexNDC(0.3,0.31,Form("%3.2f percent",100*sys_err_val_pp_J3));
  // la->SetTextColor(kGreen+2);
  // la->DrawLatexNDC(0.3,0.27,Form("%3.2f percent",100*sys_err_val_pp_J4));
  // la->SetTextSize(0.036);
  // la->SetTextColor(kBlack);
  canv_mg_pp->SaveAs(pp_canv_save_string);

  
  
  
  
}
