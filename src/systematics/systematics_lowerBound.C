#include "../templateFitter/templateFitter.h"

void systematics_lowerBound(){


  TLine *li = new TLine();
  li->SetLineStyle(7);

  TLatex *la = new TLatex();
  
  
  cout << endl;
  cout << "#######  SYSTEMATICS -- LOWER-BOUND  #########" << endl;
  cout << endl;


  // pp ranges
  const int N_c_input_pp_J2 = 16;
  double c_input_pp_J2[N_c_input_pp_J2] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5};

  const int N_c_input_pp_J3 = 16;
  double c_input_pp_J3[N_c_input_pp_J3] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5};

  const int N_c_input_pp_J4 = 16;
  double c_input_pp_J4[N_c_input_pp_J4] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5};

  // C2 ranges
  const int N_c_input_C2_J2 = 16;
  double c_input_C2_J2[N_c_input_C2_J2] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5};

  const int N_c_input_C2_J3 = 16;
  double c_input_C2_J3[N_c_input_C2_J3] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5};
  
  const int N_c_input_C2_J4 = 16;
  double c_input_C2_J4[N_c_input_C2_J4] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5};

  // C1 ranges
  const int N_c_input_C1_J2 = 16;
  double c_input_C1_J2[N_c_input_C1_J2] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5};

  const int N_c_input_C1_J3 = 16;
  double c_input_C1_J3[N_c_input_C1_J3] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5};
  
  const int N_c_input_C1_J4 = 16;
  double c_input_C1_J4[N_c_input_C1_J4] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5};



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
  int do_mu7  = 1;
  int do_mu12 = 0;

  int do_mergeB = 1;
  int do_mergeC = 1;

  int do_2tempFit = 1;
  int do_3tempFit = 0; // one has to 1, one has to be 0 for the fit integers

  
  double pTrel_fit_low  = 0.0;
  double pTrel_fit_high = 4.0;

  double c_multiplier = 1.0;



  
  // double zeros_pp_J2[N_c_input_pp_J2] = {0};
  // double nominal_result_pp_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  // double nominal_err_pp_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  // for(int i = 0; i < N_c_input_pp_J2; i++){

  //   //    zeros_pp_J2[i] = 0.0;
  //   double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J2[i],pTrel_fit_high, 1 , 1);
  //   double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J2[i],pTrel_fit_high, 1 , 2);
    
    
  //   result_pp_J2[i] = result_i / nominal_result_pp_J2;

  //   err_result_pp_J2[i] = (result_i / nominal_result_pp_J2) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J2 / nominal_result_pp_J2)*(nominal_err_pp_J2 / nominal_result_pp_J2));

  // }

  // TGraphErrors *gr_pp_J2 = new TGraphErrors(N_c_input_pp_J2,c_input_pp_J2,result_pp_J2,zeros_pp_J2,err_result_pp_J2);

  


  // double zeros_pp_J3[N_c_input_pp_J3] = {0};
  // double nominal_result_pp_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  // double nominal_err_pp_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  // for(int i = 0; i < N_c_input_pp_J3; i++){

  //   //    zeros_pp_J3[i] = 0.0;
  //   double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J3[i],pTrel_fit_high, 1 , 1);
  //   double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J3[i],pTrel_fit_high, 1 , 2);
    
    
  //   result_pp_J3[i] = result_i / nominal_result_pp_J3;

  //   err_result_pp_J3[i] = (result_i / nominal_result_pp_J3) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J3 / nominal_result_pp_J3)*(nominal_err_pp_J3 / nominal_result_pp_J3));

  // }

  // TGraphErrors *gr_pp_J3 = new TGraphErrors(N_c_input_pp_J3,c_input_pp_J3,result_pp_J3,zeros_pp_J3,err_result_pp_J3);

  
  // double zeros_pp_J4[N_c_input_pp_J4] = {0};
  // double nominal_result_pp_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  // double nominal_err_pp_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  // for(int i = 0; i < N_c_input_pp_J4; i++){

  //   //    zeros_pp_J4[i] = 0.0;
  //   double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J4[i],pTrel_fit_high, 1 , 1);
  //   double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  1,0,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J4[i],pTrel_fit_high, 1 , 2);
    
    
  //   result_pp_J4[i] = result_i / nominal_result_pp_J4;

  //   err_result_pp_J4[i] = (result_i / nominal_result_pp_J4) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J4 / nominal_result_pp_J4)*(nominal_err_pp_J4 / nominal_result_pp_J4));

  // }

  // TGraphErrors *gr_pp_J4 = new TGraphErrors(N_c_input_pp_J4,c_input_pp_J4,result_pp_J4,zeros_pp_J4,err_result_pp_J4);




  // // stylize the curves
  // gr_pp_J2->SetLineColor(kBlue-4);
  // gr_pp_J3->SetLineColor(kRed-4);
  // gr_pp_J4->SetLineColor(kGreen+2);

  // gr_pp_J2->SetMarkerColor(kBlue-4);
  // gr_pp_J3->SetMarkerColor(kRed-4);
  // gr_pp_J4->SetMarkerColor(kGreen+2);

  // gr_pp_J2->SetMarkerStyle(20);
  // gr_pp_J3->SetMarkerStyle(21);
  // gr_pp_J4->SetMarkerStyle(22);


  // TCanvas *canv_mg_pp = new TCanvas("canv_mg_pp","canv_mg_pp",700,700);
  // canv_mg_pp->cd();
  // TPad *pad_mg_pp = new TPad("pad_mg_pp","pad_mg_pp",0,0,1,1);
  // pad_mg_pp->SetLeftMargin(0.2);
  // pad_mg_pp->SetBottomMargin(0.2);
  // pad_mg_pp->Draw();
  // pad_mg_pp->cd();
  // // multigraph for pp
  // TMultiGraph *mg_pp = new TMultiGraph();
  // mg_pp->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  // mg_pp->GetXaxis()->SetTitle("#it{#it{p}_{T}^{rel} lower-bound [GeV]");
  // mg_pp->SetTitle("");
  // mg_pp->Add(gr_pp_J2);
  // mg_pp->Add(gr_pp_J3);
  // mg_pp->Add(gr_pp_J4);
  // mg_pp->GetXaxis()->SetLimits(0.0,1.5);
  // mg_pp->GetYaxis()->SetRangeUser(0.8,1.2);
  // mg_pp->Draw("AP");
  // TLegend *leg_mg_pp = new TLegend(0.6,0.75,0.88,0.88);
  // leg_mg_pp->AddEntry(gr_pp_J2,"60 < #it{p}_{T}^{jet} < 80 GeV","p");
  // leg_mg_pp->AddEntry(gr_pp_J3,"80 < #it{p}_{T}^{jet} < 120 GeV","p");
  // leg_mg_pp->AddEntry(gr_pp_J4,"120 < #it{p}_{T}^{jet} < 200 GeV","p");
  // leg_mg_pp->Draw();
  // li->DrawLine(0.0,1,1.5,1);
  // la->SetTextSize(0.036);
  // la->DrawLatexNDC(0.5,0.92,"pp 5.02 TeV (102 pb^{-1})");
  // canv_mg_pp->SaveAs("/home/clayton/Analysis/ANDraft/figures/systematics/lower-bound/pp.pdf");
  

  
  // double zeros_C2_J2[N_c_input_C2_J2] = {0};
  // double nominal_result_C2_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  // double nominal_err_C2_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  // for(int i = 0; i < N_c_input_C2_J2; i++){

  //   //    zeros_C2_J2[i] = 0.0;
  //   double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J4[i],pTrel_fit_high, 1 , 1);
  //   double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J4[i],pTrel_fit_high, 1 , 2);
    
    
  //   result_C2_J2[i] = result_i / nominal_result_C2_J2;

  //   err_result_C2_J2[i] = (result_i / nominal_result_C2_J2) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J2 / nominal_result_C2_J2)*(nominal_err_C2_J2 / nominal_result_C2_J2));

  // }

  // TGraphErrors *gr_C2_J2 = new TGraphErrors(N_c_input_C2_J2,c_input_C2_J2,result_C2_J2,zeros_C2_J2,err_result_C2_J2);

  


  // double zeros_C2_J3[N_c_input_C2_J3] = {0};
  // double nominal_result_C2_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  // double nominal_err_C2_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  // for(int i = 0; i < N_c_input_C2_J3; i++){

  //   //    zeros_C2_J3[i] = 0.0;
  //   double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J4[i],pTrel_fit_high,1 , 1);
  //   double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J4[i],pTrel_fit_high, 1 , 2);
    
    
  //   result_C2_J3[i] = result_i / nominal_result_C2_J3;

  //   err_result_C2_J3[i] = (result_i / nominal_result_C2_J3) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J3 / nominal_result_C2_J3)*(nominal_err_C2_J3 / nominal_result_C2_J3));

  // }

  // TGraphErrors *gr_C2_J3 = new TGraphErrors(N_c_input_C2_J3,c_input_C2_J3,result_C2_J3,zeros_C2_J3,err_result_C2_J3);

  
  // double zeros_C2_J4[N_c_input_C2_J4] = {0};
  // double nominal_result_C2_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  // double nominal_err_C2_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  // for(int i = 0; i < N_c_input_C2_J4; i++){

  //   //    zeros_C2_J4[i] = 0.0;
  //   double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J4[i],pTrel_fit_high, 1 , 1);
  //   double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,0,1,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J4[i],pTrel_fit_high, 1 , 2);
    
    
  //   result_C2_J4[i] = result_i / nominal_result_C2_J4;

  //   err_result_C2_J4[i] = (result_i / nominal_result_C2_J4) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J4 / nominal_result_C2_J4)*(nominal_err_C2_J4 / nominal_result_C2_J4));

  // }

  // TGraphErrors *gr_C2_J4 = new TGraphErrors(N_c_input_C2_J4,c_input_C2_J4,result_C2_J4,zeros_C2_J4,err_result_C2_J4);




  // // stylize the curves
  // gr_C2_J2->SetLineColor(kBlue-4);
  // gr_C2_J3->SetLineColor(kRed-4);
  // gr_C2_J4->SetLineColor(kGreen+2);

  // gr_C2_J2->SetMarkerColor(kBlue-4);
  // gr_C2_J3->SetMarkerColor(kRed-4);
  // gr_C2_J4->SetMarkerColor(kGreen+2);

  // gr_C2_J2->SetMarkerStyle(20);
  // gr_C2_J3->SetMarkerStyle(21);
  // gr_C2_J4->SetMarkerStyle(22);


  // TCanvas *canv_mg_C2 = new TCanvas("canv_mg_C2","canv_mg_C2",700,700);
  // canv_mg_C2->cd();
  // TPad *pad_mg_C2 = new TPad("pad_mg_C2","pad_mg_C2",0,0,1,1);
  // pad_mg_C2->SetLeftMargin(0.2);
  // pad_mg_C2->SetBottomMargin(0.2);
  // pad_mg_C2->Draw();
  // pad_mg_C2->cd();
  // // multigraph for pp
  // TMultiGraph *mg_C2 = new TMultiGraph();
  // mg_C2->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  // mg_C2->GetXaxis()->SetTitle("#it{p}_{T}^{rel} lower-bound [GeV]");
  // mg_C2->SetTitle("");
  // mg_C2->Add(gr_C2_J2);
  // mg_C2->Add(gr_C2_J3);
  // mg_C2->Add(gr_C2_J4);
  // mg_C2->GetXaxis()->SetLimits(0.0,1.5);
  // mg_C2->GetYaxis()->SetRangeUser(0.8,1.2);
  // mg_C2->Draw("AP");
  // TLegend *leg_mg_C2 = new TLegend(0.6,0.75,0.88,0.88);
  // leg_mg_C2->AddEntry(gr_C2_J2,"60 < #it{p}_{T}^{jet} < 80 GeV","p");
  // leg_mg_C2->AddEntry(gr_C2_J3,"80 < #it{p}_{T}^{jet} < 120 GeV","p");
  // leg_mg_C2->AddEntry(gr_C2_J4,"120 < #it{p}_{T}^{jet} < 200 GeV","p");
  // leg_mg_C2->Draw();
  // li->DrawLine(0.0,1,1.5,1);
  // la->SetTextSize(0.036);
  // la->DrawLatexNDC(0.4,0.92,"PbPb 30-90% 5.02 TeV (308 #mub^{-1})");
  // canv_mg_C2->SaveAs("/home/clayton/Analysis/ANDraft/figures/systematics/lower-bound/C2.pdf");

  
  
  double zeros_C1_J2[N_c_input_C1_J2] = {0};
  double nominal_result_C1_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_C1_J2 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_C1_J2; i++){

    //    zeros_C1_J2[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C1_J2[i] , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,1,0,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_input_C1_J2[i] , 2);
    
    
    result_C1_J2[i] = result_i / nominal_result_C1_J2;

    err_result_C1_J2[i] = (result_i / nominal_result_C1_J2) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C1_J2 / nominal_result_C1_J2)*(nominal_err_C1_J2 / nominal_result_C1_J2));

  }

  TGraphErrors *gr_C1_J2 = new TGraphErrors(N_c_input_C1_J2,c_input_C1_J2,result_C1_J2,zeros_C1_J2,err_result_C1_J2);

  


  double zeros_C1_J3[N_c_input_C1_J3] = {0};
  double nominal_result_C1_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_C1_J3 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_C1_J3; i++){

    //    zeros_C1_J3[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J3[i],pTrel_fit_high, 1 , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,1,0,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J3[i],pTrel_fit_high, 1 , 2);
    
    
    result_C1_J3[i] = result_i / nominal_result_C1_J3;

    err_result_C1_J3[i] = (result_i / nominal_result_C1_J3) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C1_J3 / nominal_result_C1_J3)*(nominal_err_C1_J3 / nominal_result_C1_J3));

  }

  TGraphErrors *gr_C1_J3 = new TGraphErrors(N_c_input_C1_J3,c_input_C1_J3,result_C1_J3,zeros_C1_J3,err_result_C1_J3);

  
  double zeros_C1_J4[N_c_input_C1_J4] = {0};
  double nominal_result_C1_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 1);
  double nominal_err_C1_J4 = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, 1.0 , 2);
  
  for(int i = 0; i < N_c_input_C1_J4; i++){

    //    zeros_C1_J4[i] = 0.0;
    double result_i  = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J4[i],pTrel_fit_high, 1 , 1);
    double err_i = templateFitter(do_data, do_mu5,do_mu7,do_mu12,  0,1,0,  0,0,0,1,0,0,  do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J4[i],pTrel_fit_high, 1 , 2);
    
    
    result_C1_J4[i] = result_i / nominal_result_C1_J4;

    err_result_C1_J4[i] = (result_i / nominal_result_C1_J4) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C1_J4 / nominal_result_C1_J4)*(nominal_err_C1_J4 / nominal_result_C1_J4));

  }

  TGraphErrors *gr_C1_J4 = new TGraphErrors(N_c_input_C1_J4,c_input_C1_J4,result_C1_J4,zeros_C1_J4,err_result_C1_J4);




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
  mg_C1->GetXaxis()->SetTitle("#it{p}_{T}^{rel} lower-bound [GeV]");
  mg_C1->SetTitle("");
  mg_C1->Add(gr_C1_J2);
  mg_C1->Add(gr_C1_J3);
  mg_C1->Add(gr_C1_J4);
  mg_C1->GetXaxis()->SetLimits(0.0,1.5);
  mg_C1->GetYaxis()->SetRangeUser(0.8,1.2);
  mg_C1->Draw("AP");
  TLegend *leg_mg_C1 = new TLegend(0.6,0.75,0.88,0.88);
  leg_mg_C1->AddEntry(gr_C1_J2,"60 < #it{p}_{T}^{jet} < 80 GeV","p");
  leg_mg_C1->AddEntry(gr_C1_J3,"80 < #it{p}_{T}^{jet} < 120 GeV","p");
  leg_mg_C1->AddEntry(gr_C1_J4,"120 < #it{p}_{T}^{jet} < 200 GeV","p");
  leg_mg_C1->Draw();
  li->DrawLine(0.0,1,1.5,1);
  la->SetTextSize(0.036);
  la->DrawLatexNDC(0.4,0.92,"PbPb 0-30% 5.02 TeV (308 #mub^{-1})");
  canv_mg_C1->SaveAs("/home/clayton/Analysis/ANDraft/figures/systematics/lower-bound/C1.pdf");



}
