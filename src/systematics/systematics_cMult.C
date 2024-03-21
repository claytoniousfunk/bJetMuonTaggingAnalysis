#include "../templateFitter/templateFitter.h"

void systematics_cMult(){


  TLine *li = new TLine();
  li->SetLineStyle(7);

  TLatex *la = new TLatex();
  
  
  cout << endl;
  cout << "#######  SYSTEMATICS -- C-MULTIPLIER  #########" << endl;
  cout << endl;

  // TFile *file_b_result_MC = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/bPurityResults_DATA-0_mu5-0_mu7-1_mu12-0_mergeB-1_mergeC-1_pTrel-0.0-4.0_cMult-10.root");
  // TFile *file_b_result_DATA = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/bPurityResults_DATA-1_mu5-0_mu7-1_mu12-0_mergeB-1_mergeC-1_pTrel-0.0-4.0_cMult-10.root");

  // TH1D *b_result_pp_MC, *b_result_pp_DATA;
  // TH1D *b_result_C2_MC, *b_result_C2_DATA;
  // TH1D *b_result_C1_MC, *b_result_C1_DATA;

  // file_b_result_MC->GetObject("bFracResults_pp",b_result_pp_MC);
  // file_b_result_MC->GetObject("bFracResults_C2",b_result_C2_MC);
  // file_b_result_MC->GetObject("bFracResults_C1",b_result_C1_MC);

  // file_b_result_DATA->GetObject("bFracResults_pp",b_result_pp_DATA);
  // file_b_result_DATA->GetObject("bFracResults_C2",b_result_C2_DATA);
  // file_b_result_DATA->GetObject("bFracResults_C1",b_result_C1_DATA);

  // TH1D *diff_pp, *diff_C2, *diff_C1;

  // diff_pp = (TH1D*) b_result_pp_DATA->Clone("diff_pp");
  // diff_C2 = (TH1D*) b_result_C2_DATA->Clone("diff_C2");
  // diff_C1 = (TH1D*) b_result_C1_DATA->Clone("diff_C1");

  // diff_pp->Add(b_result_pp_MC,-1.0);
  // diff_C2->Add(b_result_C2_MC,-1.0);
  // diff_C1->Add(b_result_C1_MC,-1.0);

  // diff_pp->SetLineColor(kBlack);
  // diff_pp->SetMarkerColor(kBlack);
  // diff_pp->SetLineWidth(2);

  // diff_C2->SetLineColor(kRed-4);
  // diff_C2->SetMarkerColor(kRed-4);
  // diff_C2->SetLineWidth(2);

  // diff_C1->SetLineColor(kBlue-4);
  // diff_C1->SetMarkerColor(kBlue-4);
  // diff_C1->SetLineWidth(2);

  // TCanvas* canv_diff = new TCanvas("canv_diff","canv_diff",700,700);
  // canv_diff->cd();
  // TPad *pad_diff = new TPad("pad_diff","pad_diff",0,0,1,1);
  // pad_diff->SetLeftMargin(0.2);
  // pad_diff->SetBottomMargin(0.2);
  // pad_diff->Draw();
  // pad_diff->cd();
  // diff_pp->GetYaxis()->SetTitle("#it{f}_{#it{b}}^{DATA} - #it{f}_{#it{b}}^{MC}");
  // diff_pp->GetXaxis()->SetTitle("#it{c}-multiplier");
  // diff_pp->SetTitle("");
  // diff_pp->SetStats(0);
  // diff_pp->GetYaxis()->SetRangeUser(0,0.5);
  // diff_pp->GetXaxis()->SetRangeUser(60,200);
  // diff_pp->Draw();
  // diff_C2->Draw("same");
  // diff_C1->Draw("same");

  // TLegend *leg_diff = new TLegend(0.6,0.75,0.88,0.88);
  // leg_diff->SetBorderSize(0);
  // leg_diff->SetTextSize(0.04);
  // leg_diff->AddEntry(diff_pp,"pp");
  // leg_diff->AddEntry(diff_C2,"PbPb 30-90%");
  // leg_diff->AddEntry(diff_C1,"PbPb 0-30%");
  // leg_diff->Draw();

  // canv_diff->SaveAs("/home/clayton/Analysis/ANDraft/figures/systematics/c-multiplier/b-diff.pdf");


  // pp ranges
  const int N_c_input_pp_J2 = 5;
  double c_input_pp_J2[N_c_input_pp_J2] = {0.9,0.95,1.0,1.05,1.1};

  const int N_c_input_pp_J3 = 7;
  double c_input_pp_J3[N_c_input_pp_J3] = {0.85,0.9,0.95,1.0,1.05,1.1,1.15};

  const int N_c_input_pp_J4 = 7;
  double c_input_pp_J4[N_c_input_pp_J4] = {0.85,0.9,0.95,1.0,1.05,1.1,1.15};

  // C2 ranges
  const int N_c_input_C2_J2 = 9;
  double c_input_C2_J2[N_c_input_C2_J2] = {0.8,0.85,0.9,0.95,1.0,1.05,1.1,1.15,1.2};

  const int N_c_input_C2_J3 = 9;
  double c_input_C2_J3[N_c_input_C2_J3] = {0.8,0.85,0.9,0.95,1.0,1.05,1.1,1.15,1.2};
  
  const int N_c_input_C2_J4 = 9;
  double c_input_C2_J4[N_c_input_C2_J4] = {0.8,0.85,0.9,0.95,1.0,1.05,1.1,1.15,1.2};

  // C1 ranges
  const int N_c_input_C1_J2 = 17;
  double c_input_C1_J2[N_c_input_C1_J2] = {0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.05,1.1,1.15,1.2,1.25,1.3,1.35,1.4};

  const int N_c_input_C1_J3 = 13;
  double c_input_C1_J3[N_c_input_C1_J3] = {0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.05,1.1,1.15,1.2,1.25,1.3};
  
  const int N_c_input_C1_J4 = 9;
  double c_input_C1_J4[N_c_input_C1_J4] = {0.8,0.85,0.9,0.95,1.0,1.05,1.1,1.15,1.2};



  double result_pp_J2[N_c_input_pp_J2];
  double result_pp_J3[N_c_input_pp_J3];
  double result_pp_J4[N_c_input_pp_J4];

  double result_C2_J2[N_c_input_C2_J2];
  double result_C2_J3[N_c_input_C2_J3];
  double result_C2_J4[N_c_input_C2_J4];

  double result_C1_J2[N_c_input_C1_J2];
  double result_C1_J3[N_c_input_C1_J3];
  double result_C1_J4[N_c_input_C1_J4];

  double err_result_pp_J2[N_c_input_pp_J2];
  double err_result_pp_J3[N_c_input_pp_J3];
  double err_result_pp_J4[N_c_input_pp_J4];

  double err_result_C2_J2[N_c_input_C2_J2];
  double err_result_C2_J3[N_c_input_C2_J3];
  double err_result_C2_J4[N_c_input_C2_J4];

  double err_result_C1_J2[N_c_input_C1_J2];
  double err_result_C1_J3[N_c_input_C1_J3];
  double err_result_C1_J4[N_c_input_C1_J4];




  // fit options
  int do_data = 1;
  
  int do_mu5  = 0;
  int do_mu7  = 0;
  int do_mu12 = 1;

  int do_mergeB = 1;
  int do_mergeC = 1;

  int do_2tempFit = 1;
  int do_3tempFit = 0; // one has to 1, one has to be 0 for the fit integers

  
  double pTrel_fit_low  = 0.0;
  double pTrel_fit_high = 5.0;

  double c_multiplier = 1.0;

  double small_shift = 0.01;

  
  double zeros_pp_J2[N_c_input_pp_J2] = {0};
  double deviation_pp_J2[N_c_input_pp_J2] = {0};
  double nominal_result_pp_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_pp_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_pp_J2; i++){

    //    zeros_pp_J2[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_pp_J2[i] , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_pp_J2[i] , 2);

    c_input_pp_J2[i] = c_input_pp_J2[i] - small_shift;
    
    result_pp_J2[i] = result_i / nominal_result_pp_J2;
    deviation_pp_J2[i] = TMath::Abs((result_i - nominal_result_pp_J2)/nominal_result_pp_J2);

    double b1 = result_i;
    double b2 = nominal_result_pp_J2;
    double e1 = err_i;
    double e2 = nominal_err_pp_J2;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_pp_J2[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_pp_J2[i] = (result_i / nominal_result_pp_J2) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J2 / nominal_result_pp_J2)*(nominal_err_pp_J2 / nominal_result_pp_J2));

  }

  TGraphErrors *gr_pp_J2 = new TGraphErrors(N_c_input_pp_J2,c_input_pp_J2,result_pp_J2,zeros_pp_J2,err_result_pp_J2);

  


  double zeros_pp_J3[N_c_input_pp_J3] = {0};
  double deviation_pp_J3[N_c_input_pp_J3] = {0};
  double nominal_result_pp_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_pp_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_pp_J3; i++){

    //    zeros_pp_J3[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_pp_J3[i] , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_pp_J3[i] , 2);
    
    
    result_pp_J3[i] = result_i / nominal_result_pp_J3;
    deviation_pp_J3[i] = TMath::Abs((result_i - nominal_result_pp_J3)/nominal_result_pp_J3);

    double b1 = result_i;
    double b2 = nominal_result_pp_J3;
    double e1 = err_i;
    double e2 = nominal_err_pp_J3;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_pp_J3[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_pp_J3[i] = (result_i / nominal_result_pp_J3) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J3 / nominal_result_pp_J3)*(nominal_err_pp_J3 / nominal_result_pp_J3));

  }

  TGraphErrors *gr_pp_J3 = new TGraphErrors(N_c_input_pp_J3,c_input_pp_J3,result_pp_J3,zeros_pp_J3,err_result_pp_J3);

  
  double zeros_pp_J4[N_c_input_pp_J4] = {0};
  double deviation_pp_J4[N_c_input_pp_J4] = {0};
  double nominal_result_pp_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_pp_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_pp_J4; i++){

    //    zeros_pp_J4[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_pp_J4[i] , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_pp_J4[i] , 2);
    

    c_input_pp_J4[i] = c_input_pp_J2[i] + small_shift;
    
    result_pp_J4[i] = result_i / nominal_result_pp_J4;
    deviation_pp_J4[i] = TMath::Abs((result_i - nominal_result_pp_J4)/nominal_result_pp_J4);

    double b1 = result_i;
    double b2 = nominal_result_pp_J4;
    double e1 = err_i;
    double e2 = nominal_err_pp_J4;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_pp_J4[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_pp_J4[i] = (result_i / nominal_result_pp_J4) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J4 / nominal_result_pp_J4)*(nominal_err_pp_J4 / nominal_result_pp_J4));

  }

  TGraphErrors *gr_pp_J4 = new TGraphErrors(N_c_input_pp_J4,c_input_pp_J4,result_pp_J4,zeros_pp_J4,err_result_pp_J4);


  // find max of deviaton array to use as systematic error
  double sys_err_val_pp_J2 = 0.0;
  for(int i = 0; i < N_c_input_pp_J2; i++){
    double dev_i = deviation_pp_J2[i];
    if(dev_i > sys_err_val_pp_J2) sys_err_val_pp_J2 = dev_i;
  }
  double sys_err_val_pp_J3 = 0.0;
  for(int i = 0; i < N_c_input_pp_J3; i++){
    double dev_i = deviation_pp_J3[i];
    if(dev_i > sys_err_val_pp_J3) sys_err_val_pp_J3 = dev_i;
  }
  double sys_err_val_pp_J4 = 0.0;
  for(int i = 0; i < N_c_input_pp_J4; i++){
    double dev_i = deviation_pp_J4[i];
    if(dev_i > sys_err_val_pp_J4) sys_err_val_pp_J4 = dev_i;
  }


  // stylize the curves
  gr_pp_J2->SetLineColor(kBlue-4);
  gr_pp_J3->SetLineColor(kRed-4);
  gr_pp_J4->SetLineColor(kGreen+2);

  gr_pp_J2->SetMarkerColor(kBlue-4);
  gr_pp_J3->SetMarkerColor(kRed-4);
  gr_pp_J4->SetMarkerColor(kGreen+2);

  gr_pp_J2->SetMarkerStyle(20);
  gr_pp_J3->SetMarkerStyle(21);
  gr_pp_J4->SetMarkerStyle(22);


  TCanvas *canv_mg_pp = new TCanvas("canv_mg_pp","canv_mg_pp",700,700);
  canv_mg_pp->cd();
  TPad *pad_mg_pp = new TPad("pad_mg_pp","pad_mg_pp",0,0,1,1);
  pad_mg_pp->SetLeftMargin(0.2);
  pad_mg_pp->SetBottomMargin(0.2);
  pad_mg_pp->Draw();
  pad_mg_pp->cd();
  // multigraph for pp
  TMultiGraph *mg_pp = new TMultiGraph();
  mg_pp->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  mg_pp->GetXaxis()->SetTitle("#it{c}-multiplier");
  mg_pp->SetTitle("");
  mg_pp->Add(gr_pp_J2);
  mg_pp->Add(gr_pp_J3);
  mg_pp->Add(gr_pp_J4);
  mg_pp->GetXaxis()->SetLimits(0.6,1.4);
  mg_pp->GetYaxis()->SetRangeUser(0.8,1.2);
  mg_pp->Draw("AP");
  TLegend *leg_mg_pp = new TLegend(0.6,0.75,0.88,0.88);
  leg_mg_pp->SetBorderSize(0);
  leg_mg_pp->AddEntry(gr_pp_J2,"60 < #it{p}_{T}^{jet} < 80 GeV","p");
  leg_mg_pp->AddEntry(gr_pp_J3,"80 < #it{p}_{T}^{jet} < 120 GeV","p");
  leg_mg_pp->AddEntry(gr_pp_J4,"120 < #it{p}_{T}^{jet} < 200 GeV","p");
  leg_mg_pp->Draw();
  li->DrawLine(0.6,1,1.4,1);
  la->SetTextSize(0.036);
  TString pp_data_info_string = "";
  TString pp_trigger_info_string = "";
  if(do_mu5 == 1){
    pp_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}       #font[42]{pp 5.02 TeV (99 pb^{-1})}";
    pp_trigger_info_string = "#font[42]{#scale[0.8]{mu5 trigger}}";
  }
  else if(do_mu7 == 1){
    pp_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}       #font[42]{pp 5.02 TeV (274 pb^{-1})}";
    pp_trigger_info_string = "#font[42]{#scale[0.8]{mu7 trigger}}";
  }
  else if(do_mu12 == 1){
    pp_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}       #font[42]{pp 5.02 TeV (301 pb^{-1})}";
    pp_trigger_info_string = "#font[42]{#scale[0.8]{mu12 trigger}}";
  }
  la->DrawLatexNDC(0.22,0.92,pp_data_info_string);
  la->DrawLatexNDC(0.25,0.83,pp_trigger_info_string);
  TString pp_canv_save_string = "";
  if(do_mu5 == 1) pp_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-multiplier/pp_mu5.pdf";
  else if(do_mu7 == 1) pp_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-multiplier/pp_mu7.pdf";
  else if(do_mu12 == 1) pp_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-multiplier/pp_mu12.pdf";
  else{};
  la->SetTextSize(0.032);
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.3,0.35,Form("%3.2f percent",100*sys_err_val_pp_J2));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.3,0.31,Form("%3.2f percent",100*sys_err_val_pp_J3));
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.3,0.27,Form("%3.2f percent",100*sys_err_val_pp_J4));
  la->SetTextSize(0.036);
  la->SetTextColor(kBlack);
  canv_mg_pp->SaveAs(pp_canv_save_string);  

  
  double zeros_C2_J2[N_c_input_C2_J2] = {0};
  double deviation_C2_J2[N_c_input_C2_J2] = {0};
  double nominal_result_C2_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_C2_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_C2_J2; i++){

    //    zeros_C2_J2[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C2_J2[i] , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C2_J2[i] , 2);

    c_input_C2_J2[i] = c_input_C2_J2[i] - small_shift;
    
    result_C2_J2[i] = result_i / nominal_result_C2_J2;
    deviation_C2_J2[i] = TMath::Abs((result_i - nominal_result_C2_J2)/nominal_result_C2_J2);

    double b1 = result_i;
    double b2 = nominal_result_C2_J2;
    double e1 = err_i;
    double e2 = nominal_err_C2_J2;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_C2_J2[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_C2_J2[i] = (result_i / nominal_result_C2_J2) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J2 / nominal_result_C2_J2)*(nominal_err_C2_J2 / nominal_result_C2_J2));

  }

  TGraphErrors *gr_C2_J2 = new TGraphErrors(N_c_input_C2_J2,c_input_C2_J2,result_C2_J2,zeros_C2_J2,err_result_C2_J2);

  


  double zeros_C2_J3[N_c_input_C2_J3] = {0};
  double deviation_C2_J3[N_c_input_C2_J3] = {0};
  double nominal_result_C2_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_C2_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_C2_J3; i++){

    //    zeros_C2_J3[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C2_J3[i] , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C2_J3[i] , 2);
    
    
    result_C2_J3[i] = result_i / nominal_result_C2_J3;
    deviation_C2_J3[i] = TMath::Abs((result_i - nominal_result_C2_J3)/nominal_result_C2_J3);

    double b1 = result_i;
    double b2 = nominal_result_C2_J3;
    double e1 = err_i;
    double e2 = nominal_err_C2_J3;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_C2_J3[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_C2_J3[i] = (result_i / nominal_result_C2_J3) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J3 / nominal_result_C2_J3)*(nominal_err_C2_J3 / nominal_result_C2_J3));

  }

  TGraphErrors *gr_C2_J3 = new TGraphErrors(N_c_input_C2_J3,c_input_C2_J3,result_C2_J3,zeros_C2_J3,err_result_C2_J3);

  
  double zeros_C2_J4[N_c_input_C2_J4] = {0};
  double deviation_C2_J4[N_c_input_C2_J4] = {0};
  double nominal_result_C2_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_C2_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_C2_J4; i++){

    //    zeros_C2_J4[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C2_J4[i] , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C2_J4[i] , 2);

    c_input_C2_J4[i] = c_input_C2_J4[i] + small_shift;
    
    result_C2_J4[i] = result_i / nominal_result_C2_J4;
    deviation_C2_J4[i] = TMath::Abs((result_i - nominal_result_C2_J4)/nominal_result_C2_J4);

    double b1 = result_i;
    double b2 = nominal_result_C2_J4;
    double e1 = err_i;
    double e2 = nominal_err_C2_J4;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_C2_J4[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_C2_J4[i] = (result_i / nominal_result_C2_J4) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J4 / nominal_result_C2_J4)*(nominal_err_C2_J4 / nominal_result_C2_J4));

  }

  TGraphErrors *gr_C2_J4 = new TGraphErrors(N_c_input_C2_J4,c_input_C2_J4,result_C2_J4,zeros_C2_J4,err_result_C2_J4);

  // find max of deviaton array to use as systematic error
  double sys_err_val_C2_J2 = 0.0;
  for(int i = 0; i < N_c_input_C2_J2; i++){
    double dev_i = deviation_C2_J2[i];
    if(dev_i > sys_err_val_C2_J2) sys_err_val_C2_J2 = dev_i;
  }
  double sys_err_val_C2_J3 = 0.0;
  for(int i = 0; i < N_c_input_C2_J3; i++){
    double dev_i = deviation_C2_J3[i];
    if(dev_i > sys_err_val_C2_J3) sys_err_val_C2_J3 = dev_i;
  }
  double sys_err_val_C2_J4 = 0.0;
  for(int i = 0; i < N_c_input_C2_J4; i++){
    double dev_i = deviation_C2_J4[i];
    if(dev_i > sys_err_val_C2_J4) sys_err_val_C2_J4 = dev_i;
  }

  // stylize the curves
  gr_C2_J2->SetLineColor(kBlue-4);
  gr_C2_J3->SetLineColor(kRed-4);
  gr_C2_J4->SetLineColor(kGreen+2);

  gr_C2_J2->SetMarkerColor(kBlue-4);
  gr_C2_J3->SetMarkerColor(kRed-4);
  gr_C2_J4->SetMarkerColor(kGreen+2);

  gr_C2_J2->SetMarkerStyle(20);
  gr_C2_J3->SetMarkerStyle(21);
  gr_C2_J4->SetMarkerStyle(22);


  TCanvas *canv_mg_C2 = new TCanvas("canv_mg_C2","canv_mg_C2",700,700);
  canv_mg_C2->cd();
  TPad *pad_mg_C2 = new TPad("pad_mg_C2","pad_mg_C2",0,0,1,1);
  pad_mg_C2->SetLeftMargin(0.2);
  pad_mg_C2->SetBottomMargin(0.2);
  pad_mg_C2->Draw();
  pad_mg_C2->cd();
  // multigraph for pp
  TMultiGraph *mg_C2 = new TMultiGraph();
  mg_C2->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  mg_C2->GetXaxis()->SetTitle("#it{c}-multiplier");
  mg_C2->SetTitle("");
  mg_C2->Add(gr_C2_J2);
  mg_C2->Add(gr_C2_J3);
  mg_C2->Add(gr_C2_J4);
  mg_C2->GetXaxis()->SetLimits(0.6,1.4);
  mg_C2->GetYaxis()->SetRangeUser(0.8,1.2);
  mg_C2->Draw("AP");
  TLegend *leg_mg_C2 = new TLegend(0.6,0.75,0.88,0.88);
  leg_mg_C2->SetBorderSize(0);
  leg_mg_C2->AddEntry(gr_C2_J2,"60 < #it{p}_{T}^{jet} < 80 GeV","p");
  leg_mg_C2->AddEntry(gr_C2_J3,"80 < #it{p}_{T}^{jet} < 120 GeV","p");
  leg_mg_C2->AddEntry(gr_C2_J4,"120 < #it{p}_{T}^{jet} < 200 GeV","p");
  leg_mg_C2->Draw();
  li->DrawLine(0.6,1,1.4,1);
  la->SetTextSize(0.036);
  TString C2_data_info_string = "";
  TString C2_trigger_info_string = "";
  if(do_mu5 == 1){
    C2_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}  #font[42]{PbPb 30-90% 5.02 TeV (323 #mub^{-1})}";
    C2_trigger_info_string = "#font[42]{#scale[0.8]{mu5 trigger}}";
  }
  else if(do_mu7 == 1){
    C2_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}  #font[42]{PbPb 30-90% 5.02 TeV (787 #mub^{-1})}";
    C2_trigger_info_string = "#font[42]{#scale[0.8]{mu7 trigger}}";
  }
  else if(do_mu12 == 1){
    C2_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}  #font[42]{PbPb 30-90% 5.02 TeV (1689 #mub^{-1})}";
    C2_trigger_info_string = "#font[42]{#scale[0.8]{mu12 trigger}}";
  }
  la->DrawLatexNDC(0.22,0.92,C2_data_info_string);
  la->DrawLatexNDC(0.25,0.83,C2_trigger_info_string);
  TString C2_canv_save_string = "";
  if(do_mu5 == 1) C2_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-multiplier/C2_mu5.pdf";
  else if(do_mu7 == 1) C2_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-multiplier/C2_mu7.pdf";
  else if(do_mu12 == 1) C2_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-multiplier/C2_mu12.pdf";
  else{};
  la->SetTextSize(0.032);
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.3,0.35,Form("%3.2f percent",100*sys_err_val_C2_J2));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.3,0.31,Form("%3.2f percent",100*sys_err_val_C2_J3));
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.3,0.27,Form("%3.2f percent",100*sys_err_val_C2_J4));
  la->SetTextSize(0.036);
  la->SetTextColor(kBlack);
  canv_mg_C2->SaveAs(C2_canv_save_string);

  
  
  double zeros_C1_J2[N_c_input_C1_J2] = {0};
  double deviation_C1_J2[N_c_input_C1_J2] = {0};
  double nominal_result_C1_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_C1_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_C1_J2; i++){

    //    zeros_C1_J2[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C1_J2[i] , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C1_J2[i] , 2);
    
    c_input_C1_J2[i] = c_input_C1_J2[i] - small_shift;
	
    result_C1_J2[i] = result_i / nominal_result_C1_J2;
    deviation_C1_J2[i] = TMath::Abs((result_i - nominal_result_C1_J2)/nominal_result_C1_J2);

    double b1 = result_i;
    double b2 = nominal_result_C1_J2;
    double e1 = err_i;
    double e2 = nominal_err_C1_J2;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_C1_J2[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_C1_J2[i] = (result_i / nominal_result_C1_J2) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C1_J2 / nominal_result_C1_J2)*(nominal_err_C1_J2 / nominal_result_C1_J2));

  }

  TGraphErrors *gr_C1_J2 = new TGraphErrors(N_c_input_C1_J2,c_input_C1_J2,result_C1_J2,zeros_C1_J2,err_result_C1_J2);

  


  double zeros_C1_J3[N_c_input_C1_J3] = {0};
  double deviation_C1_J3[N_c_input_C1_J3] = {0};
  double nominal_result_C1_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_C1_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_C1_J3; i++){

    //    zeros_C1_J3[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C1_J3[i] , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C1_J3[i] , 2);
    
    
    result_C1_J3[i] = result_i / nominal_result_C1_J3;
    deviation_C1_J3[i] = TMath::Abs((result_i - nominal_result_C1_J3)/nominal_result_C1_J3);

    double b1 = result_i;
    double b2 = nominal_result_C1_J3;
    double e1 = err_i;
    double e2 = nominal_err_C1_J3;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_C1_J3[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_C1_J3[i] = (result_i / nominal_result_C1_J3) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C1_J3 / nominal_result_C1_J3)*(nominal_err_C1_J3 / nominal_result_C1_J3));

  }

  TGraphErrors *gr_C1_J3 = new TGraphErrors(N_c_input_C1_J3,c_input_C1_J3,result_C1_J3,zeros_C1_J3,err_result_C1_J3);

  
  double zeros_C1_J4[N_c_input_C1_J4] = {0};
  double deviation_C1_J4[N_c_input_C1_J4] = {0};
  double nominal_result_C1_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_C1_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_C1_J4; i++){

    //    zeros_C1_J4[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C1_J4[i] , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C1_J4[i] , 2);
    
    c_input_C1_J4[i] = c_input_C1_J4[i] + small_shift;
    
    result_C1_J4[i] = result_i / nominal_result_C1_J4;
    deviation_C1_J4[i] = TMath::Abs((result_i - nominal_result_C1_J4)/nominal_result_C1_J4);

    double b1 = result_i;
    double b2 = nominal_result_C1_J4;
    double e1 = err_i;
    double e2 = nominal_err_C1_J4;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_C1_J4[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_C1_J4[i] = (result_i / nominal_result_C1_J4) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C1_J4 / nominal_result_C1_J4)*(nominal_err_C1_J4 / nominal_result_C1_J4));

  }

  TGraphErrors *gr_C1_J4 = new TGraphErrors(N_c_input_C1_J4,c_input_C1_J4,result_C1_J4,zeros_C1_J4,err_result_C1_J4);

  // find max of deviaton array to use as systematic error
  double sys_err_val_C1_J2 = 0.0;
  for(int i = 0; i < N_c_input_C1_J2; i++){
    double dev_i = deviation_C1_J2[i];
    if(dev_i > sys_err_val_C1_J2) sys_err_val_C1_J2 = dev_i;
  }
  double sys_err_val_C1_J3 = 0.0;
  for(int i = 0; i < N_c_input_C1_J3; i++){
    double dev_i = deviation_C1_J3[i];
    if(dev_i > sys_err_val_C1_J3) sys_err_val_C1_J3 = dev_i;
  }
  double sys_err_val_C1_J4 = 0.0;
  for(int i = 0; i < N_c_input_C1_J4; i++){
    double dev_i = deviation_C1_J4[i];
    if(dev_i > sys_err_val_C1_J4) sys_err_val_C1_J4 = dev_i;
  }
  

  // stylize the curves
  gr_C1_J2->SetLineColor(kBlue-4);
  gr_C1_J3->SetLineColor(kRed-4);
  gr_C1_J4->SetLineColor(kGreen+2);

  gr_C1_J2->SetMarkerColor(kBlue-4);
  gr_C1_J3->SetMarkerColor(kRed-4);
  gr_C1_J4->SetMarkerColor(kGreen+2);

  gr_C1_J2->SetMarkerStyle(20);
  gr_C1_J3->SetMarkerStyle(21);
  gr_C1_J4->SetMarkerStyle(22);


  TCanvas *canv_mg_C1 = new TCanvas("canv_mg_C1","canv_mg_C1",700,700);
  canv_mg_C1->cd();
  TPad *pad_mg_C1 = new TPad("pad_mg_C1","pad_mg_C1",0,0,1,1);
  pad_mg_C1->SetLeftMargin(0.2);
  pad_mg_C1->SetBottomMargin(0.2);
  pad_mg_C1->Draw();
  pad_mg_C1->cd();
  // multigraph for pp
  TMultiGraph *mg_C1 = new TMultiGraph();
  mg_C1->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  mg_C1->GetXaxis()->SetTitle("#it{c}-multiplier");
  mg_C1->SetTitle("");
  mg_C1->Add(gr_C1_J2);
  mg_C1->Add(gr_C1_J3);
  mg_C1->Add(gr_C1_J4);
  mg_C1->GetXaxis()->SetLimits(0.6,1.4);
  mg_C1->GetYaxis()->SetRangeUser(0.8,1.2);
  mg_C1->Draw("AP");
  TLegend *leg_mg_C1 = new TLegend(0.6,0.75,0.88,0.88);
  leg_mg_C1->SetBorderSize(0);
  leg_mg_C1->AddEntry(gr_C1_J2,"60 < #it{p}_{T}^{jet} < 80 GeV","p");
  leg_mg_C1->AddEntry(gr_C1_J3,"80 < #it{p}_{T}^{jet} < 120 GeV","p");
  leg_mg_C1->AddEntry(gr_C1_J4,"120 < #it{p}_{T}^{jet} < 200 GeV","p");
  leg_mg_C1->Draw();
  li->DrawLine(0.6,1,1.4,1);
  la->SetTextSize(0.036);
  TString C1_data_info_string = "";
  TString C1_trigger_info_string = "";
  if(do_mu5 == 1){
    C1_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}  #font[42]{PbPb 0-30% 5.02 TeV (323 #mub^{-1})}";
    C1_trigger_info_string = "#font[42]{#scale[0.8]{mu5 trigger}}";
  }
  else if(do_mu7 == 1){
    C1_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}  #font[42]{PbPb 0-30% 5.02 TeV (787 #mub^{-1})}";
    C1_trigger_info_string = "#font[42]{#scale[0.8]{mu7 trigger}}";
  }
  else if(do_mu12 == 1){
    C1_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}  #font[42]{PbPb 0-30% 5.02 TeV (1689 #mub^{-1})}";
    C1_trigger_info_string = "#font[42]{#scale[0.8]{mu12 trigger}}";
  }
  la->DrawLatexNDC(0.22,0.92,C1_data_info_string);
  la->DrawLatexNDC(0.25,0.83,C1_trigger_info_string);
  TString C1_canv_save_string = "";
  if(do_mu5 == 1) C1_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-multiplier/C1_mu5.pdf";
  else if(do_mu7 == 1) C1_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-multiplier/C1_mu7.pdf";
  else if(do_mu12 == 1) C1_canv_save_string = "/home/clayton/Analysis/ANDraft/figures/systematics/c-multiplier/C1_mu12.pdf";
  else{};
  la->SetTextSize(0.032);
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.3,0.35,Form("%3.2f percent",100*sys_err_val_C1_J2));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.3,0.31,Form("%3.2f percent",100*sys_err_val_C1_J3));
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.3,0.27,Form("%3.2f percent",100*sys_err_val_C1_J4));
  la->SetTextSize(0.036);
  la->SetTextColor(kBlack);
  canv_mg_C1->SaveAs(C1_canv_save_string);



}
