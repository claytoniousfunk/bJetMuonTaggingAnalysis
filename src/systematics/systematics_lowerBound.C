#include "../templateFitter/templateFitter_projectableTemplates_3CentBins.h"

void systematics_lowerBound(){


  TLine *li = new TLine();
  li->SetLineStyle(7);

  TLatex *la = new TLatex();
  
  
  cout << endl;
  cout << "#######  SYSTEMATICS -- LOWER-BOUND  #########" << endl;
  cout << endl;



  // pp ranges
  const int N_c_input_pp_J1 = 4;
  double c_input_pp_J1[N_c_input_pp_J1] = {0,0.1,0.2,0.3};

  const int N_c_input_pp_J2 = 4;
  double c_input_pp_J2[N_c_input_pp_J2] = {0,0.1,0.2,0.3};

  const int N_c_input_pp_J3 = 4;
  double c_input_pp_J3[N_c_input_pp_J3] = {0,0.1,0.2,0.3};

  const int N_c_input_pp_J4 = 4;
  double c_input_pp_J4[N_c_input_pp_J4] = {0,0.1,0.2,0.3};

  const int N_c_input_pp_J5 = 4;
  double c_input_pp_J5[N_c_input_pp_J5] = {0,0.1,0.2,0.3};

  const int N_c_input_pp_J6 = 4;
  double c_input_pp_J6[N_c_input_pp_J6] = {0,0.1,0.2,0.3};

  // C3 ranges
  const int N_c_input_C3_J1 = 4;
  double c_input_C3_J1[N_c_input_C3_J1] = {0,0.1,0.2,0.3};

  const int N_c_input_C3_J2 = 4;
  double c_input_C3_J2[N_c_input_C3_J2] = {0,0.1,0.2,0.3};

  const int N_c_input_C3_J3 = 4;
  double c_input_C3_J3[N_c_input_C3_J3] = {0,0.1,0.2,0.3};
  
  const int N_c_input_C3_J4 = 4;
  double c_input_C3_J4[N_c_input_C3_J4] = {0,0.1,0.2,0.3};

  const int N_c_input_C3_J5 = 4;
  double c_input_C3_J5[N_c_input_C3_J5] = {0,0.1,0.2,0.3};

  const int N_c_input_C3_J6 = 4;
  double c_input_C3_J6[N_c_input_C3_J6] = {0,0.1,0.2,0.3};

  // C2 ranges
  const int N_c_input_C2_J1 = 4;
  double c_input_C2_J1[N_c_input_C2_J1] = {0,0.1,0.2,0.3};

  const int N_c_input_C2_J2 = 4;
  double c_input_C2_J2[N_c_input_C2_J2] = {0,0.1,0.2,0.3};

  const int N_c_input_C2_J3 = 4;
  double c_input_C2_J3[N_c_input_C2_J3] = {0,0.1,0.2,0.3};
  
  const int N_c_input_C2_J4 = 4;
  double c_input_C2_J4[N_c_input_C2_J4] = {0,0.1,0.2,0.3};

  const int N_c_input_C2_J5 = 4;
  double c_input_C2_J5[N_c_input_C2_J5] = {0,0.1,0.2,0.3};

  const int N_c_input_C2_J6 = 4;
  double c_input_C2_J6[N_c_input_C2_J6] = {0,0.1,0.2,0.3};

  // C1 ranges
  const int N_c_input_C1_J1 = 4;
  double c_input_C1_J1[N_c_input_C1_J1] = {0,0.1,0.2,0.3};

  const int N_c_input_C1_J2 = 4;  
  double c_input_C1_J2[N_c_input_C1_J2] = {0,0.1,0.2,0.3};

  const int N_c_input_C1_J3 = 4;
  double c_input_C1_J3[N_c_input_C1_J3] = {0,0.1,0.2,0.3};
  
  const int N_c_input_C1_J4 = 4;
  double c_input_C1_J4[N_c_input_C1_J4] = {0,0.1,0.2,0.3};

  const int N_c_input_C1_J5 = 4;
  double c_input_C1_J5[N_c_input_C1_J5] = {0,0.1,0.2,0.3};

  const int N_c_input_C1_J6 = 4;
  double c_input_C1_J6[N_c_input_C1_J6] = {0,0.1,0.2,0.3};  




  double result_pp_J1[N_c_input_pp_J2];
  double result_pp_J2[N_c_input_pp_J2];
  double result_pp_J3[N_c_input_pp_J3];
  double result_pp_J4[N_c_input_pp_J4];
  double result_pp_J5[N_c_input_pp_J4];
  double result_pp_J6[N_c_input_pp_J4];

  double result_C3_J1[N_c_input_C3_J2];
  double result_C3_J2[N_c_input_C3_J2];
  double result_C3_J3[N_c_input_C3_J3];
  double result_C3_J4[N_c_input_C3_J4];
  double result_C3_J5[N_c_input_C3_J5];
  double result_C3_J6[N_c_input_C3_J6];
  
  double result_C2_J1[N_c_input_C2_J2];
  double result_C2_J2[N_c_input_C2_J2];
  double result_C2_J3[N_c_input_C2_J3];
  double result_C2_J4[N_c_input_C2_J4];
  double result_C2_J5[N_c_input_C2_J5];
  double result_C2_J6[N_c_input_C2_J6];

  double result_C1_J1[N_c_input_C1_J2];
  double result_C1_J2[N_c_input_C1_J2];
  double result_C1_J3[N_c_input_C1_J3];
  double result_C1_J4[N_c_input_C1_J4];
  double result_C1_J5[N_c_input_C1_J5];
  double result_C1_J6[N_c_input_C1_J6];  

  double err_result_pp_J1[N_c_input_pp_J2];
  double err_result_pp_J2[N_c_input_pp_J2];
  double err_result_pp_J3[N_c_input_pp_J3];
  double err_result_pp_J4[N_c_input_pp_J4];
  double err_result_pp_J5[N_c_input_pp_J4];
  double err_result_pp_J6[N_c_input_pp_J4];

  double err_result_C3_J1[N_c_input_C3_J2];
  double err_result_C3_J2[N_c_input_C3_J2];  
  double err_result_C3_J3[N_c_input_C3_J3];
  double err_result_C3_J4[N_c_input_C3_J4];
  double err_result_C3_J5[N_c_input_C3_J5];
  double err_result_C3_J6[N_c_input_C3_J6];

  double err_result_C2_J1[N_c_input_C2_J2];
  double err_result_C2_J2[N_c_input_C2_J2];  
  double err_result_C2_J3[N_c_input_C2_J3];
  double err_result_C2_J4[N_c_input_C2_J4];
  double err_result_C2_J5[N_c_input_C2_J5];
  double err_result_C2_J6[N_c_input_C2_J6];    

  double err_result_C1_J1[N_c_input_C1_J2];  
  double err_result_C1_J2[N_c_input_C1_J2];
  double err_result_C1_J3[N_c_input_C1_J3];
  double err_result_C1_J4[N_c_input_C1_J4];
  double err_result_C1_J5[N_c_input_C1_J5];
  double err_result_C1_J6[N_c_input_C1_J6];    

  double chi2ndof_pp_J1[N_c_input_pp_J1];
  double chi2ndof_pp_J2[N_c_input_pp_J2];
  double chi2ndof_pp_J3[N_c_input_pp_J3];
  double chi2ndof_pp_J4[N_c_input_pp_J4];
  double chi2ndof_pp_J5[N_c_input_pp_J5];
  double chi2ndof_pp_J6[N_c_input_pp_J6];

  double chi2ndof_C3_J1[N_c_input_C3_J1];
  double chi2ndof_C3_J2[N_c_input_C3_J2];
  double chi2ndof_C3_J3[N_c_input_C3_J3];
  double chi2ndof_C3_J4[N_c_input_C3_J4];
  double chi2ndof_C3_J5[N_c_input_C3_J5];
  double chi2ndof_C3_J6[N_c_input_C3_J6];

  double chi2ndof_C2_J1[N_c_input_C2_J1];
  double chi2ndof_C2_J2[N_c_input_C2_J2];
  double chi2ndof_C2_J3[N_c_input_C2_J3];
  double chi2ndof_C2_J4[N_c_input_C2_J4];
  double chi2ndof_C2_J5[N_c_input_C2_J5];
  double chi2ndof_C2_J6[N_c_input_C2_J6];

  double chi2ndof_C1_J1[N_c_input_C1_J1];
  double chi2ndof_C1_J2[N_c_input_C1_J2];
  double chi2ndof_C1_J3[N_c_input_C1_J3];
  double chi2ndof_C1_J4[N_c_input_C1_J4];
  double chi2ndof_C1_J5[N_c_input_C1_J5];
  double chi2ndof_C1_J6[N_c_input_C1_J6];


  // fit options
  int do_data = 1;

  int do_pp = 1;
  int do_C3 = 0;
  int do_C2 = 0;
  int do_C1 = 0;

  double low_jetPt = 105.;
  double high_jetPt = 110.;
  
  int do_mergeB = 1;
  int do_mergeC = 1;

  // one has to be 1, one has to be 0 for the fit integers
  int do_2tempFit = 1;
  int do_3tempFit = 0; 

  
  double pTrel_fit_low  = 0.0;
  double pTrel_fit_high = 5.0;

  double c_multiplier = 1.0;
  double bGS_multiplier = 1.0;

  //double small_shift = 0.005;
  double small_shift = 0.00;

  double line_width = 1.7;
  double marker_size = 1.7;

  ////// *************************************************************************************************************** ///////////////


  // // J1 settings set by hand
  // low_jetPt = 80.;
  // high_jetPt = 90.;
  // double zeros_pp_J1[N_c_input_pp_J1] = {0};
  // double deviation_pp_J1[N_c_input_pp_J1] = {0};
  // double nominal_result_pp_J1 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_pp_J1 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_pp_J1; i++){

  //   //    zeros_pp_J1[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
  //   //cout << "CHI2 / NDOF ===== " << chi2ndof_i << endl;

  //   c_input_pp_J1[i] = c_input_pp_J1[i] - 2.*small_shift;
    
  //   result_pp_J1[i] = result_i / nominal_result_pp_J1;
  //   deviation_pp_J1[i] = TMath::Abs((result_i - nominal_result_pp_J1)/nominal_result_pp_J1);

  //   double b1 = result_i;
  //   double b2 = nominal_result_pp_J1;
  //   double e1 = err_i;
  //   double e2 = nominal_err_pp_J1;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_pp_J1[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_pp_J1[i] = (result_i / nominal_result_pp_J1) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J1 / nominal_result_pp_J1)*(nominal_err_pp_J1 / nominal_result_pp_J1));

  //   chi2ndof_pp_J1[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_pp_J1 = new TGraphErrors(N_c_input_pp_J1,c_input_pp_J1,result_pp_J1,zeros_pp_J1,err_result_pp_J1);
  // TGraph *gr_chi2ndof_pp_J1 = new TGraph(N_c_input_pp_J1,c_input_pp_J1,chi2ndof_pp_J1);

  // // J2 settings set by hand
  // low_jetPt = 90.;
  // high_jetPt = 100.;
  // double zeros_pp_J2[N_c_input_pp_J2] = {0};
  // double deviation_pp_J2[N_c_input_pp_J2] = {0};
  // double nominal_result_pp_J2 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_pp_J2 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_pp_J2; i++){

  //   //    zeros_pp_J2[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
  //   //cout << "CHI2 / NDOF ===== " << chi2ndof_i << endl;

  //   c_input_pp_J2[i] = c_input_pp_J2[i] - 1.*small_shift;
    
  //   result_pp_J2[i] = result_i / nominal_result_pp_J2;
  //   deviation_pp_J2[i] = TMath::Abs((result_i - nominal_result_pp_J2)/nominal_result_pp_J2);

  //   double b1 = result_i;
  //   double b2 = nominal_result_pp_J2;
  //   double e1 = err_i;
  //   double e2 = nominal_err_pp_J2;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_pp_J2[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_pp_J2[i] = (result_i / nominal_result_pp_J2) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J2 / nominal_result_pp_J2)*(nominal_err_pp_J2 / nominal_result_pp_J2));

  //   chi2ndof_pp_J2[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_pp_J2 = new TGraphErrors(N_c_input_pp_J2,c_input_pp_J2,result_pp_J2,zeros_pp_J2,err_result_pp_J2);
  // TGraph *gr_chi2ndof_pp_J2 = new TGraph(N_c_input_pp_J2,c_input_pp_J2,chi2ndof_pp_J2);
  

  // // J3 settings set by hand
  // low_jetPt = 100.;
  // high_jetPt = 120.;
  // double zeros_pp_J3[N_c_input_pp_J3] = {0};
  // double deviation_pp_J3[N_c_input_pp_J3] = {0};
  // double nominal_result_pp_J3 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_pp_J3 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_pp_J3; i++){

  //   //    zeros_pp_J3[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    
    
  //   result_pp_J3[i] = result_i / nominal_result_pp_J3;
  //   deviation_pp_J3[i] = TMath::Abs((result_i - nominal_result_pp_J3)/nominal_result_pp_J3);

  //   double b1 = result_i;
  //   double b2 = nominal_result_pp_J3;
  //   double e1 = err_i;
  //   double e2 = nominal_err_pp_J3;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_pp_J3[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_pp_J3[i] = (result_i / nominal_result_pp_J3) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J3 / nominal_result_pp_J3)*(nominal_err_pp_J3 / nominal_result_pp_J3));

  //   chi2ndof_pp_J3[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_pp_J3 = new TGraphErrors(N_c_input_pp_J3,c_input_pp_J3,result_pp_J3,zeros_pp_J3,err_result_pp_J3);
  // TGraph *gr_chi2ndof_pp_J3 = new TGraph(N_c_input_pp_J3,c_input_pp_J3,chi2ndof_pp_J3);

  // // J4 settings set by hand
  // low_jetPt = 120.;
  // high_jetPt = 150.;  
  // double zeros_pp_J4[N_c_input_pp_J4] = {0};
  // double deviation_pp_J4[N_c_input_pp_J4] = {0};
  // double nominal_result_pp_J4 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_pp_J4 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_pp_J4; i++){

  //   //    zeros_pp_J4[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

  //   c_input_pp_J4[i] = c_input_pp_J4[i] + 1.*small_shift;
    
  //   result_pp_J4[i] = result_i / nominal_result_pp_J4;
  //   deviation_pp_J4[i] = TMath::Abs((result_i - nominal_result_pp_J4)/nominal_result_pp_J4);

  //   double b1 = result_i;
  //   double b2 = nominal_result_pp_J4;
  //   double e1 = err_i;
  //   double e2 = nominal_err_pp_J4;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_pp_J4[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_pp_J4[i] = (result_i / nominal_result_pp_J4) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J4 / nominal_result_pp_J4)*(nominal_err_pp_J4 / nominal_result_pp_J4));

  //   chi2ndof_pp_J4[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_pp_J4 = new TGraphErrors(N_c_input_pp_J4,c_input_pp_J4,result_pp_J4,zeros_pp_J4,err_result_pp_J4);
  // TGraph *gr_chi2ndof_pp_J4 = new TGraph(N_c_input_pp_J4,c_input_pp_J4,chi2ndof_pp_J4);

  // // J5 settings set by hand
  // low_jetPt = 150.;
  // high_jetPt = 200.;  
  // double zeros_pp_J5[N_c_input_pp_J5] = {0};
  // double deviation_pp_J5[N_c_input_pp_J5] = {0};
  // double nominal_result_pp_J5 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_pp_J5 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_pp_J5; i++){

  //   //    zeros_pp_J5[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

  //   c_input_pp_J5[i] = c_input_pp_J5[i] + 2.*small_shift;
    
  //   result_pp_J5[i] = result_i / nominal_result_pp_J5;
  //   deviation_pp_J5[i] = TMath::Abs((result_i - nominal_result_pp_J5)/nominal_result_pp_J5);

  //   double b1 = result_i;
  //   double b2 = nominal_result_pp_J5;
  //   double e1 = err_i;
  //   double e2 = nominal_err_pp_J5;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_pp_J5[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_pp_J5[i] = (result_i / nominal_result_pp_J5) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J5 / nominal_result_pp_J5)*(nominal_err_pp_J5 / nominal_result_pp_J5));

  //   chi2ndof_pp_J5[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_pp_J5 = new TGraphErrors(N_c_input_pp_J5,c_input_pp_J5,result_pp_J5,zeros_pp_J5,err_result_pp_J5);
  // TGraph *gr_chi2ndof_pp_J5 = new TGraph(N_c_input_pp_J5,c_input_pp_J5,chi2ndof_pp_J5);

  // // J6 settings by hand
  // low_jetPt = 200.;
  // high_jetPt = 300.;  
  // double zeros_pp_J6[N_c_input_pp_J6] = {0};
  // double deviation_pp_J6[N_c_input_pp_J6] = {0};
  // double nominal_result_pp_J6 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_pp_J6 = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_pp_J6; i++){

  //   //    zeros_pp_J6[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 1,0,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_pp_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

  //   c_input_pp_J6[i] = c_input_pp_J6[i] + 3.*small_shift;
    
  //   result_pp_J6[i] = result_i / nominal_result_pp_J6;
  //   deviation_pp_J6[i] = TMath::Abs((result_i - nominal_result_pp_J6)/nominal_result_pp_J6);

  //   double b1 = result_i;
  //   double b2 = nominal_result_pp_J6;
  //   double e1 = err_i;
  //   double e2 = nominal_err_pp_J6;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_pp_J6[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_pp_J6[i] = (result_i / nominal_result_pp_J6) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_pp_J6 / nominal_result_pp_J6)*(nominal_err_pp_J6 / nominal_result_pp_J6));

  //   chi2ndof_pp_J6[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_pp_J6 = new TGraphErrors(N_c_input_pp_J6,c_input_pp_J6,result_pp_J6,zeros_pp_J6,err_result_pp_J6);
  // TGraph *gr_chi2ndof_pp_J6 = new TGraph(N_c_input_pp_J6,c_input_pp_J6,chi2ndof_pp_J6);




  
  // // find max of deviaton array to use as systematic error
  // double sys_err_val_pp_J1 = 0.0;
  // for(int i = 0; i < N_c_input_pp_J1; i++){
  //   double dev_i = deviation_pp_J1[i];
  //   if(dev_i > sys_err_val_pp_J1) sys_err_val_pp_J1 = dev_i;
  // }
  // double sys_err_val_pp_J2 = 0.0;
  // for(int i = 0; i < N_c_input_pp_J2; i++){
  //   double dev_i = deviation_pp_J2[i];
  //   if(dev_i > sys_err_val_pp_J2) sys_err_val_pp_J2 = dev_i;
  // }
  // double sys_err_val_pp_J3 = 0.0;
  // for(int i = 0; i < N_c_input_pp_J3; i++){
  //   double dev_i = deviation_pp_J3[i];
  //   if(dev_i > sys_err_val_pp_J3) sys_err_val_pp_J3 = dev_i;
  // }
  // double sys_err_val_pp_J4 = 0.0;
  // for(int i = 0; i < N_c_input_pp_J4; i++){
  //   double dev_i = deviation_pp_J4[i];
  //   if(dev_i > sys_err_val_pp_J4) sys_err_val_pp_J4 = dev_i;
  // }
  // double sys_err_val_pp_J5 = 0.0;
  // for(int i = 0; i < N_c_input_pp_J5; i++){
  //   double dev_i = deviation_pp_J5[i];
  //   if(dev_i > sys_err_val_pp_J5) sys_err_val_pp_J5 = dev_i;
  // }
  // double sys_err_val_pp_J6 = 0.0;
  // for(int i = 0; i < N_c_input_pp_J6; i++){
  //   double dev_i = deviation_pp_J6[i];
  //   if(dev_i > sys_err_val_pp_J6) sys_err_val_pp_J6 = dev_i;
  // }  

  // // stylize the curves
  // gr_pp_J1->SetLineColor(kBlack);
  // gr_pp_J2->SetLineColor(kBlue-4);
  // gr_pp_J3->SetLineColor(kRed-4);
  // gr_pp_J4->SetLineColor(kGreen+2);
  // gr_pp_J5->SetLineColor(kMagenta-3);
  // gr_pp_J6->SetLineColor(kOrange);

  
  // gr_pp_J1->SetLineWidth(line_width);
  // gr_pp_J2->SetLineWidth(line_width);
  // gr_pp_J3->SetLineWidth(line_width);
  // gr_pp_J4->SetLineWidth(line_width);
  // gr_pp_J5->SetLineWidth(line_width);
  // gr_pp_J6->SetLineWidth(line_width);

  // gr_pp_J1->SetMarkerColor(kBlack);
  // gr_pp_J2->SetMarkerColor(kBlue-4);
  // gr_pp_J3->SetMarkerColor(kRed-4);
  // gr_pp_J4->SetMarkerColor(kGreen+2);
  // gr_pp_J5->SetMarkerColor(kMagenta-3);
  // gr_pp_J6->SetMarkerColor(kOrange);

  // gr_pp_J1->SetMarkerSize(marker_size);
  // gr_pp_J2->SetMarkerSize(marker_size);
  // gr_pp_J3->SetMarkerSize(marker_size);
  // gr_pp_J4->SetMarkerSize(marker_size);
  // gr_pp_J5->SetMarkerSize(marker_size);
  // gr_pp_J6->SetMarkerSize(marker_size);

  // gr_pp_J1->SetMarkerStyle(34);
  // gr_pp_J2->SetMarkerStyle(20);
  // gr_pp_J3->SetMarkerStyle(21);
  // gr_pp_J4->SetMarkerStyle(22);
  // gr_pp_J5->SetMarkerStyle(33);
  // gr_pp_J6->SetMarkerStyle(29);

  // gr_chi2ndof_pp_J1->SetLineColor(kBlack);
  // gr_chi2ndof_pp_J2->SetLineColor(kBlue-4);
  // gr_chi2ndof_pp_J3->SetLineColor(kRed-4);
  // gr_chi2ndof_pp_J4->SetLineColor(kGreen+2);
  // gr_chi2ndof_pp_J5->SetLineColor(kMagenta-3);
  // gr_chi2ndof_pp_J6->SetLineColor(kOrange);

  // gr_chi2ndof_pp_J1->SetMarkerColor(kBlack);
  // gr_chi2ndof_pp_J2->SetMarkerColor(kBlue-4);
  // gr_chi2ndof_pp_J3->SetMarkerColor(kRed-4);
  // gr_chi2ndof_pp_J4->SetMarkerColor(kGreen+2);
  // gr_chi2ndof_pp_J5->SetMarkerColor(kMagenta-3);
  // gr_chi2ndof_pp_J6->SetMarkerColor(kOrange);

  // gr_chi2ndof_pp_J1->SetMarkerStyle(34);
  // gr_chi2ndof_pp_J2->SetMarkerStyle(20);
  // gr_chi2ndof_pp_J3->SetMarkerStyle(21);
  // gr_chi2ndof_pp_J4->SetMarkerStyle(22);
  // gr_chi2ndof_pp_J5->SetMarkerStyle(33);
  // gr_chi2ndof_pp_J6->SetMarkerStyle(29);

  // TCanvas *canv_mg_pp = new TCanvas("canv_mg_pp","canv_mg_pp",700,700);
  // canv_mg_pp->cd();
  // TPad *pad_mg_pp = new TPad("pad_mg_pp","pad_mg_pp",0,0.,1,1);
  // TPad *pad_mg_pp_low = new TPad("pad_mg_pp","pad_mg_pp",0,0,1,0.3);
  // pad_mg_pp->SetLeftMargin(0.15);
  // pad_mg_pp_low->SetLeftMargin(0.15);
  // pad_mg_pp->SetBottomMargin(0.2);
  // pad_mg_pp_low->SetTopMargin(0.0);
  // pad_mg_pp_low->SetBottomMargin(0.2);
  // pad_mg_pp_low->SetLogy(0);
  // pad_mg_pp->Draw();
  // //pad_mg_pp_low->Draw();
  // pad_mg_pp->cd();
  // // multigraph for pp
  // TMultiGraph *mg_pp = new TMultiGraph();
  // mg_pp->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  // mg_pp->GetXaxis()->SetTitle("Fit lower bound [GeV]");
  // mg_pp->SetTitle("");
  // mg_pp->Add(gr_pp_J1);  
  // mg_pp->Add(gr_pp_J2);
  // mg_pp->Add(gr_pp_J3);
  // mg_pp->Add(gr_pp_J4);
  // mg_pp->Add(gr_pp_J5);
  // mg_pp->Add(gr_pp_J6);    
  // mg_pp->GetXaxis()->SetLimits(-0.05,0.55);
  // mg_pp->GetYaxis()->SetRangeUser(0.75,1.25);
  // mg_pp->Draw("AP");
  // TLegend *leg_mg_pp = new TLegend(0.55,0.25,0.88,0.45);
  // leg_mg_pp->SetBorderSize(0);
  // leg_mg_pp->SetTextSize(0.03);
  // leg_mg_pp->AddEntry(gr_pp_J1,"80 < #it{p}_{T}^{jet} < 90 GeV","p");  
  // leg_mg_pp->AddEntry(gr_pp_J2,"90 < #it{p}_{T}^{jet} < 100 GeV","p");
  // leg_mg_pp->AddEntry(gr_pp_J3,"100 < #it{p}_{T}^{jet} < 120 GeV","p");
  // leg_mg_pp->AddEntry(gr_pp_J4,"120 < #it{p}_{T}^{jet} < 150 GeV","p");
  // leg_mg_pp->AddEntry(gr_pp_J5,"150 < #it{p}_{T}^{jet} < 200 GeV","p");
  // leg_mg_pp->AddEntry(gr_pp_J6,"200 < #it{p}_{T}^{jet} < 300 GeV","p");
  // leg_mg_pp->Draw();
  // li->DrawLine(-0.05,1,.55,1);
  // la->SetTextSize(0.036);
  // TString pp_data_info_string = "";
  // TString pp_trigger_info_string = "";
  // pp_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}   #font[42]{pp 5.02 TeV (301 pb^{-1})}";
  // pp_trigger_info_string = "#font[42]{#scale[0.8]{mu12 trigger}}";
  // la->DrawLatexNDC(0.17,0.92,pp_data_info_string);
  // //la->DrawLatexNDC(0.25,0.83,pp_trigger_info_string);
  // TString pp_canv_save_string = "";
  // pp_canv_save_string = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/lower-bound/pp.pdf";
  // la->SetTextSize(0.032);
  // la->SetTextColor(kBlack);
  // la->DrawLatexNDC(0.3,0.43,Form("%3.2f %%",100*sys_err_val_pp_J1));
  // la->SetTextColor(kBlue-4);
  // la->DrawLatexNDC(0.3,0.39,Form("%3.2f %%",100*sys_err_val_pp_J2));
  // la->SetTextColor(kRed-4);
  // la->DrawLatexNDC(0.3,0.35,Form("%3.2f %%",100*sys_err_val_pp_J3));
  // la->SetTextColor(kGreen+2);
  // la->DrawLatexNDC(0.3,0.31,Form("%3.2f %%",100*sys_err_val_pp_J4));
  // la->SetTextColor(kMagenta-3);
  // la->DrawLatexNDC(0.3,0.27,Form("%3.2f %%",100*sys_err_val_pp_J5));
  // la->SetTextColor(kOrange);
  // la->DrawLatexNDC(0.3,0.23,Form("%3.2f %%",100*sys_err_val_pp_J6));
  // la->SetTextSize(0.036);
  // la->SetTextColor(kBlack);
  // canv_mg_pp->SaveAs(pp_canv_save_string);

  

  ////// *************************************************************************************************************** ///////////////

  

  // // J1 settings set by hand
  // low_jetPt = 80.;
  // high_jetPt = 90.;
  // double zeros_C3_J1[N_c_input_C3_J1] = {0};
  // double deviation_C3_J1[N_c_input_C3_J1] = {0};
  // double nominal_result_C3_J1 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C3_J1 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C3_J1; i++){

  //   //    zeros_C3_J1[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
  //   //cout << "CHI2 / NDOF ===== " << chi2ndof_i << endl;

  //   c_input_C3_J1[i] = c_input_C3_J1[i] - 2.*small_shift;
    
  //   result_C3_J1[i] = result_i / nominal_result_C3_J1;
  //   deviation_C3_J1[i] = TMath::Abs((result_i - nominal_result_C3_J1)/nominal_result_C3_J1);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C3_J1;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C3_J1;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C3_J1[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C3_J1[i] = (result_i / nominal_result_C3_J1) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C3_J1 / nominal_result_C3_J1)*(nominal_err_C3_J1 / nominal_result_C3_J1));

  //   chi2ndof_C3_J1[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C3_J1 = new TGraphErrors(N_c_input_C3_J1,c_input_C3_J1,result_C3_J1,zeros_C3_J1,err_result_C3_J1);
  // TGraph *gr_chi2ndof_C3_J1 = new TGraph(N_c_input_C3_J1,c_input_C3_J1,chi2ndof_C3_J1);

  // // J2 settings set by hand
  // low_jetPt = 90.;
  // high_jetPt = 100.;
  // double zeros_C3_J2[N_c_input_C3_J2] = {0};
  // double deviation_C3_J2[N_c_input_C3_J2] = {0};
  // double nominal_result_C3_J2 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C3_J2 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C3_J2; i++){

  //   //    zeros_C3_J2[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
  //   //cout << "CHI2 / NDOF ===== " << chi2ndof_i << endl;

  //   c_input_C3_J2[i] = c_input_C3_J2[i] - 1.*small_shift;
    
  //   result_C3_J2[i] = result_i / nominal_result_C3_J2;
  //   deviation_C3_J2[i] = TMath::Abs((result_i - nominal_result_C3_J2)/nominal_result_C3_J2);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C3_J2;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C3_J2;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C3_J2[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C3_J2[i] = (result_i / nominal_result_C3_J2) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C3_J2 / nominal_result_C3_J2)*(nominal_err_C3_J2 / nominal_result_C3_J2));

  //   chi2ndof_C3_J2[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C3_J2 = new TGraphErrors(N_c_input_C3_J2,c_input_C3_J2,result_C3_J2,zeros_C3_J2,err_result_C3_J2);
  // TGraph *gr_chi2ndof_C3_J2 = new TGraph(N_c_input_C3_J2,c_input_C3_J2,chi2ndof_C3_J2);
  

  // // J3 settings set by hand
  // low_jetPt = 100.;
  // high_jetPt = 120.;
  // double zeros_C3_J3[N_c_input_C3_J3] = {0};
  // double deviation_C3_J3[N_c_input_C3_J3] = {0};
  // double nominal_result_C3_J3 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C3_J3 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C3_J3; i++){

  //   //    zeros_C3_J3[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    
    
  //   result_C3_J3[i] = result_i / nominal_result_C3_J3;
  //   deviation_C3_J3[i] = TMath::Abs((result_i - nominal_result_C3_J3)/nominal_result_C3_J3);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C3_J3;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C3_J3;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C3_J3[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C3_J3[i] = (result_i / nominal_result_C3_J3) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C3_J3 / nominal_result_C3_J3)*(nominal_err_C3_J3 / nominal_result_C3_J3));

  //   chi2ndof_C3_J3[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C3_J3 = new TGraphErrors(N_c_input_C3_J3,c_input_C3_J3,result_C3_J3,zeros_C3_J3,err_result_C3_J3);
  // TGraph *gr_chi2ndof_C3_J3 = new TGraph(N_c_input_C3_J3,c_input_C3_J3,chi2ndof_C3_J3);

  // // J4 settings set by hand
  // low_jetPt = 120.;
  // high_jetPt = 150.;  
  // double zeros_C3_J4[N_c_input_C3_J4] = {0};
  // double deviation_C3_J4[N_c_input_C3_J4] = {0};
  // double nominal_result_C3_J4 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C3_J4 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C3_J4; i++){

  //   //    zeros_C3_J4[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

  //   c_input_C3_J4[i] = c_input_C3_J4[i] + 1.*small_shift;
    
  //   result_C3_J4[i] = result_i / nominal_result_C3_J4;
  //   deviation_C3_J4[i] = TMath::Abs((result_i - nominal_result_C3_J4)/nominal_result_C3_J4);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C3_J4;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C3_J4;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C3_J4[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C3_J4[i] = (result_i / nominal_result_C3_J4) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C3_J4 / nominal_result_C3_J4)*(nominal_err_C3_J4 / nominal_result_C3_J4));

  //   chi2ndof_C3_J4[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C3_J4 = new TGraphErrors(N_c_input_C3_J4,c_input_C3_J4,result_C3_J4,zeros_C3_J4,err_result_C3_J4);
  // TGraph *gr_chi2ndof_C3_J4 = new TGraph(N_c_input_C3_J4,c_input_C3_J4,chi2ndof_C3_J4);

  // // J5 settings set by hand
  // low_jetPt = 150.;
  // high_jetPt = 200.;  
  // double zeros_C3_J5[N_c_input_C3_J5] = {0};
  // double deviation_C3_J5[N_c_input_C3_J5] = {0};
  // double nominal_result_C3_J5 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C3_J5 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C3_J5; i++){

  //   //    zeros_C3_J5[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

  //   c_input_C3_J5[i] = c_input_C3_J5[i] + 2.*small_shift;
    
  //   result_C3_J5[i] = result_i / nominal_result_C3_J5;
  //   deviation_C3_J5[i] = TMath::Abs((result_i - nominal_result_C3_J5)/nominal_result_C3_J5);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C3_J5;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C3_J5;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C3_J5[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C3_J5[i] = (result_i / nominal_result_C3_J5) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C3_J5 / nominal_result_C3_J5)*(nominal_err_C3_J5 / nominal_result_C3_J5));

  //   chi2ndof_C3_J5[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C3_J5 = new TGraphErrors(N_c_input_C3_J5,c_input_C3_J5,result_C3_J5,zeros_C3_J5,err_result_C3_J5);
  // TGraph *gr_chi2ndof_C3_J5 = new TGraph(N_c_input_C3_J5,c_input_C3_J5,chi2ndof_C3_J5);

  // // J6 settings by hand
  // low_jetPt = 200.;
  // high_jetPt = 300.;  
  // double zeros_C3_J6[N_c_input_C3_J6] = {0};
  // double deviation_C3_J6[N_c_input_C3_J6] = {0};
  // double nominal_result_C3_J6 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C3_J6 = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C3_J6; i++){

  //   //    zeros_C3_J6[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,0,1, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C3_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

  //   c_input_C3_J6[i] = c_input_C3_J6[i] + 3.*small_shift;
    
  //   result_C3_J6[i] = result_i / nominal_result_C3_J6;
  //   deviation_C3_J6[i] = TMath::Abs((result_i - nominal_result_C3_J6)/nominal_result_C3_J6);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C3_J6;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C3_J6;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C3_J6[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C3_J6[i] = (result_i / nominal_result_C3_J6) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C3_J6 / nominal_result_C3_J6)*(nominal_err_C3_J6 / nominal_result_C3_J6));

  //   chi2ndof_C3_J6[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C3_J6 = new TGraphErrors(N_c_input_C3_J6,c_input_C3_J6,result_C3_J6,zeros_C3_J6,err_result_C3_J6);
  // TGraph *gr_chi2ndof_C3_J6 = new TGraph(N_c_input_C3_J6,c_input_C3_J6,chi2ndof_C3_J6);




  
  // // find max of deviaton array to use as systematic error
  // double sys_err_val_C3_J1 = 0.0;
  // for(int i = 0; i < N_c_input_C3_J1; i++){
  //   double dev_i = deviation_C3_J1[i];
  //   if(dev_i > sys_err_val_C3_J1) sys_err_val_C3_J1 = dev_i;
  // }
  // double sys_err_val_C3_J2 = 0.0;
  // for(int i = 0; i < N_c_input_C3_J2; i++){
  //   double dev_i = deviation_C3_J2[i];
  //   if(dev_i > sys_err_val_C3_J2) sys_err_val_C3_J2 = dev_i;
  // }
  // double sys_err_val_C3_J3 = 0.0;
  // for(int i = 0; i < N_c_input_C3_J3; i++){
  //   double dev_i = deviation_C3_J3[i];
  //   if(dev_i > sys_err_val_C3_J3) sys_err_val_C3_J3 = dev_i;
  // }
  // double sys_err_val_C3_J4 = 0.0;
  // for(int i = 0; i < N_c_input_C3_J4; i++){
  //   double dev_i = deviation_C3_J4[i];
  //   if(dev_i > sys_err_val_C3_J4) sys_err_val_C3_J4 = dev_i;
  // }
  // double sys_err_val_C3_J5 = 0.0;
  // for(int i = 0; i < N_c_input_C3_J5; i++){
  //   double dev_i = deviation_C3_J5[i];
  //   if(dev_i > sys_err_val_C3_J5) sys_err_val_C3_J5 = dev_i;
  // }
  // double sys_err_val_C3_J6 = 0.0;
  // for(int i = 0; i < N_c_input_C3_J6; i++){
  //   double dev_i = deviation_C3_J6[i];
  //   if(dev_i > sys_err_val_C3_J6) sys_err_val_C3_J6 = dev_i;
  // }  

  // // stylize the curves
  // gr_C3_J1->SetLineColor(kBlack);
  // gr_C3_J2->SetLineColor(kBlue-4);
  // gr_C3_J3->SetLineColor(kRed-4);
  // gr_C3_J4->SetLineColor(kGreen+2);
  // gr_C3_J5->SetLineColor(kMagenta-3);
  // gr_C3_J6->SetLineColor(kOrange);

  // gr_C3_J1->SetLineWidth(line_width);
  // gr_C3_J2->SetLineWidth(line_width);
  // gr_C3_J3->SetLineWidth(line_width);
  // gr_C3_J4->SetLineWidth(line_width);
  // gr_C3_J5->SetLineWidth(line_width);
  // gr_C3_J6->SetLineWidth(line_width);

  // gr_C3_J1->SetMarkerColor(kBlack);
  // gr_C3_J2->SetMarkerColor(kBlue-4);
  // gr_C3_J3->SetMarkerColor(kRed-4);
  // gr_C3_J4->SetMarkerColor(kGreen+2);
  // gr_C3_J5->SetMarkerColor(kMagenta-3);
  // gr_C3_J6->SetMarkerColor(kOrange);

  // gr_C3_J1->SetMarkerSize(marker_size);
  // gr_C3_J2->SetMarkerSize(marker_size);
  // gr_C3_J3->SetMarkerSize(marker_size);
  // gr_C3_J4->SetMarkerSize(marker_size);
  // gr_C3_J5->SetMarkerSize(marker_size);
  // gr_C3_J6->SetMarkerSize(marker_size);
  
  // gr_C3_J1->SetMarkerStyle(34);
  // gr_C3_J2->SetMarkerStyle(20);
  // gr_C3_J3->SetMarkerStyle(21);
  // gr_C3_J4->SetMarkerStyle(22);
  // gr_C3_J5->SetMarkerStyle(33);
  // gr_C3_J6->SetMarkerStyle(29);

  // gr_chi2ndof_C3_J1->SetLineColor(kBlack);
  // gr_chi2ndof_C3_J2->SetLineColor(kBlue-4);
  // gr_chi2ndof_C3_J3->SetLineColor(kRed-4);
  // gr_chi2ndof_C3_J4->SetLineColor(kGreen+2);
  // gr_chi2ndof_C3_J5->SetLineColor(kMagenta-3);
  // gr_chi2ndof_C3_J6->SetLineColor(kOrange);

  // gr_chi2ndof_C3_J1->SetMarkerColor(kBlack);
  // gr_chi2ndof_C3_J2->SetMarkerColor(kBlue-4);
  // gr_chi2ndof_C3_J3->SetMarkerColor(kRed-4);
  // gr_chi2ndof_C3_J4->SetMarkerColor(kGreen+2);
  // gr_chi2ndof_C3_J5->SetMarkerColor(kMagenta-3);
  // gr_chi2ndof_C3_J6->SetMarkerColor(kOrange);

  // gr_chi2ndof_C3_J1->SetMarkerStyle(34);
  // gr_chi2ndof_C3_J2->SetMarkerStyle(20);
  // gr_chi2ndof_C3_J3->SetMarkerStyle(21);
  // gr_chi2ndof_C3_J4->SetMarkerStyle(22);
  // gr_chi2ndof_C3_J5->SetMarkerStyle(33);
  // gr_chi2ndof_C3_J6->SetMarkerStyle(29);

  // TCanvas *canv_mg_C3 = new TCanvas("canv_mg_C3","canv_mg_C3",700,700);
  // canv_mg_C3->cd();
  // TPad *pad_mg_C3 = new TPad("pad_mg_C3","pad_mg_C3",0,0.,1,1);
  // TPad *pad_mg_C3_low = new TPad("pad_mg_C3","pad_mg_C3",0,0,1,0.3);
  // pad_mg_C3->SetLeftMargin(0.15);
  // pad_mg_C3_low->SetLeftMargin(0.15);
  // pad_mg_C3->SetBottomMargin(0.2);
  // pad_mg_C3_low->SetTopMargin(0.0);
  // pad_mg_C3_low->SetBottomMargin(0.2);
  // pad_mg_C3_low->SetLogy(0);
  // pad_mg_C3->Draw();
  // //pad_mg_C3_low->Draw();
  // pad_mg_C3->cd();
  // // multigraph for C3
  // TMultiGraph *mg_C3 = new TMultiGraph();
  // mg_C3->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  // mg_C3->GetXaxis()->SetTitle("Fit lower bound [GeV]");
  // mg_C3->SetTitle("");
  // mg_C3->Add(gr_C3_J1);  
  // mg_C3->Add(gr_C3_J2);
  // mg_C3->Add(gr_C3_J3);
  // mg_C3->Add(gr_C3_J4);
  // mg_C3->Add(gr_C3_J5);
  // mg_C3->Add(gr_C3_J6);    
  // mg_C3->GetXaxis()->SetLimits(-0.05,0.55);
  // mg_C3->GetYaxis()->SetRangeUser(0.75,1.25);
  // mg_C3->Draw("AP");
  // TLegend *leg_mg_C3 = new TLegend(0.55,0.25,0.88,0.45);
  // leg_mg_C3->SetBorderSize(0);
  // leg_mg_C3->SetTextSize(0.03);
  // leg_mg_C3->AddEntry(gr_C3_J1,"80 < #it{p}_{T}^{jet} < 90 GeV","p");  
  // leg_mg_C3->AddEntry(gr_C3_J2,"90 < #it{p}_{T}^{jet} < 100 GeV","p");
  // leg_mg_C3->AddEntry(gr_C3_J3,"100 < #it{p}_{T}^{jet} < 120 GeV","p");
  // leg_mg_C3->AddEntry(gr_C3_J4,"120 < #it{p}_{T}^{jet} < 150 GeV","p");
  // leg_mg_C3->AddEntry(gr_C3_J5,"150 < #it{p}_{T}^{jet} < 200 GeV","p");
  // leg_mg_C3->AddEntry(gr_C3_J6,"200 < #it{p}_{T}^{jet} < 300 GeV","p");
  // leg_mg_C3->Draw();
  // li->DrawLine(-0.05,1,.55,1);
  // la->SetTextSize(0.036);
  // TString C3_data_info_string = "";
  // TString C3_trigger_info_string = "";
  // C3_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}       #font[42]{PbPb 30-90% 5.02 TeV)}";
  // C3_trigger_info_string = "#font[42]{#scale[0.8]{mu12 trigger}}";
  // la->DrawLatexNDC(0.17,0.92,C3_data_info_string);
  // //la->DrawLatexNDC(0.25,0.83,C3_trigger_info_string);
  // TString C3_canv_save_string = "";
  // C3_canv_save_string = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/lower-bound/C3.pdf";
  // la->SetTextSize(0.032);
  // la->SetTextColor(kBlack);
  // la->DrawLatexNDC(0.2,0.43,Form("%3.2f %%",100*sys_err_val_C3_J1));
  // la->SetTextColor(kBlue-4);
  // la->DrawLatexNDC(0.2,0.39,Form("%3.2f %%",100*sys_err_val_C3_J2));
  // la->SetTextColor(kRed-4);
  // la->DrawLatexNDC(0.2,0.35,Form("%3.2f %%",100*sys_err_val_C3_J3));
  // la->SetTextColor(kGreen+2);
  // la->DrawLatexNDC(0.2,0.31,Form("%3.2f %%",100*sys_err_val_C3_J4));
  // la->SetTextColor(kMagenta-3);
  // la->DrawLatexNDC(0.2,0.27,Form("%3.2f %%",100*sys_err_val_C3_J5));
  // la->SetTextColor(kOrange);
  // la->DrawLatexNDC(0.2,0.23,Form("%3.2f %%",100*sys_err_val_C3_J6));
  // la->SetTextSize(0.036);
  // la->SetTextColor(kBlack);
  // canv_mg_C3->SaveAs(C3_canv_save_string);

  ////// *************************************************************************************************************** ///////////////

  // // J1 settings set by hand
  // low_jetPt = 80.;
  // high_jetPt = 90.;
  // double zeros_C2_J1[N_c_input_C2_J1] = {0};
  // double deviation_C2_J1[N_c_input_C2_J1] = {0};
  // double nominal_result_C2_J1 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C2_J1 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C2_J1; i++){

  //   //    zeros_C2_J1[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
  //   //cout << "CHI2 / NDOF ===== " << chi2ndof_i << endl;

  //   c_input_C2_J1[i] = c_input_C2_J1[i] - 2.*small_shift;
    
  //   result_C2_J1[i] = result_i / nominal_result_C2_J1;
  //   deviation_C2_J1[i] = TMath::Abs((result_i - nominal_result_C2_J1)/nominal_result_C2_J1);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C2_J1;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C2_J1;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C2_J1[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C2_J1[i] = (result_i / nominal_result_C2_J1) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J1 / nominal_result_C2_J1)*(nominal_err_C2_J1 / nominal_result_C2_J1));

  //   chi2ndof_C2_J1[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C2_J1 = new TGraphErrors(N_c_input_C2_J1,c_input_C2_J1,result_C2_J1,zeros_C2_J1,err_result_C2_J1);
  // TGraph *gr_chi2ndof_C2_J1 = new TGraph(N_c_input_C2_J1,c_input_C2_J1,chi2ndof_C2_J1);

  // // J2 settings set by hand
  // low_jetPt = 90.;
  // high_jetPt = 100.;
  // double zeros_C2_J2[N_c_input_C2_J2] = {0};
  // double deviation_C2_J2[N_c_input_C2_J2] = {0};
  // double nominal_result_C2_J2 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C2_J2 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C2_J2; i++){

  //   //    zeros_C2_J2[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
  //   //cout << "CHI2 / NDOF ===== " << chi2ndof_i << endl;

  //   c_input_C2_J2[i] = c_input_C2_J2[i] - 1.*small_shift;
    
  //   result_C2_J2[i] = result_i / nominal_result_C2_J2;
  //   deviation_C2_J2[i] = TMath::Abs((result_i - nominal_result_C2_J2)/nominal_result_C2_J2);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C2_J2;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C2_J2;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C2_J2[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C2_J2[i] = (result_i / nominal_result_C2_J2) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J2 / nominal_result_C2_J2)*(nominal_err_C2_J2 / nominal_result_C2_J2));

  //   chi2ndof_C2_J2[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C2_J2 = new TGraphErrors(N_c_input_C2_J2,c_input_C2_J2,result_C2_J2,zeros_C2_J2,err_result_C2_J2);
  // TGraph *gr_chi2ndof_C2_J2 = new TGraph(N_c_input_C2_J2,c_input_C2_J2,chi2ndof_C2_J2);
  

  // // J3 settings set by hand
  // low_jetPt = 100.;
  // high_jetPt = 120.;
  // double zeros_C2_J3[N_c_input_C2_J3] = {0};
  // double deviation_C2_J3[N_c_input_C2_J3] = {0};
  // double nominal_result_C2_J3 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C2_J3 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C2_J3; i++){

  //   //    zeros_C2_J3[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    
    
  //   result_C2_J3[i] = result_i / nominal_result_C2_J3;
  //   deviation_C2_J3[i] = TMath::Abs((result_i - nominal_result_C2_J3)/nominal_result_C2_J3);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C2_J3;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C2_J3;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C2_J3[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C2_J3[i] = (result_i / nominal_result_C2_J3) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J3 / nominal_result_C2_J3)*(nominal_err_C2_J3 / nominal_result_C2_J3));

  //   chi2ndof_C2_J3[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C2_J3 = new TGraphErrors(N_c_input_C2_J3,c_input_C2_J3,result_C2_J3,zeros_C2_J3,err_result_C2_J3);
  // TGraph *gr_chi2ndof_C2_J3 = new TGraph(N_c_input_C2_J3,c_input_C2_J3,chi2ndof_C2_J3);

  // // J4 settings set by hand
  // low_jetPt = 120.;
  // high_jetPt = 150.;  
  // double zeros_C2_J4[N_c_input_C2_J4] = {0};
  // double deviation_C2_J4[N_c_input_C2_J4] = {0};
  // double nominal_result_C2_J4 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C2_J4 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C2_J4; i++){

  //   //    zeros_C2_J4[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

  //   c_input_C2_J4[i] = c_input_C2_J4[i] + 1.*small_shift;
    
  //   result_C2_J4[i] = result_i / nominal_result_C2_J4;
  //   deviation_C2_J4[i] = TMath::Abs((result_i - nominal_result_C2_J4)/nominal_result_C2_J4);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C2_J4;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C2_J4;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C2_J4[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C2_J4[i] = (result_i / nominal_result_C2_J4) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J4 / nominal_result_C2_J4)*(nominal_err_C2_J4 / nominal_result_C2_J4));

  //   chi2ndof_C2_J4[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C2_J4 = new TGraphErrors(N_c_input_C2_J4,c_input_C2_J4,result_C2_J4,zeros_C2_J4,err_result_C2_J4);
  // TGraph *gr_chi2ndof_C2_J4 = new TGraph(N_c_input_C2_J4,c_input_C2_J4,chi2ndof_C2_J4);

  // // J5 settings set by hand
  // low_jetPt = 150.;
  // high_jetPt = 200.;  
  // double zeros_C2_J5[N_c_input_C2_J5] = {0};
  // double deviation_C2_J5[N_c_input_C2_J5] = {0};
  // double nominal_result_C2_J5 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C2_J5 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C2_J5; i++){

  //   //    zeros_C2_J5[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

  //   c_input_C2_J5[i] = c_input_C2_J5[i] + 2.*small_shift;
    
  //   result_C2_J5[i] = result_i / nominal_result_C2_J5;
  //   deviation_C2_J5[i] = TMath::Abs((result_i - nominal_result_C2_J5)/nominal_result_C2_J5);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C2_J5;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C2_J5;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C2_J5[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C2_J5[i] = (result_i / nominal_result_C2_J5) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J5 / nominal_result_C2_J5)*(nominal_err_C2_J5 / nominal_result_C2_J5));

  //   chi2ndof_C2_J5[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C2_J5 = new TGraphErrors(N_c_input_C2_J5,c_input_C2_J5,result_C2_J5,zeros_C2_J5,err_result_C2_J5);
  // TGraph *gr_chi2ndof_C2_J5 = new TGraph(N_c_input_C2_J5,c_input_C2_J5,chi2ndof_C2_J5);

  // // J6 settings by hand
  // low_jetPt = 200.;
  // high_jetPt = 300.;  
  // double zeros_C2_J6[N_c_input_C2_J6] = {0};
  // double deviation_C2_J6[N_c_input_C2_J6] = {0};
  // double nominal_result_C2_J6 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  // double nominal_err_C2_J6 = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  // for(int i = 0; i < N_c_input_C2_J6; i++){

  //   //    zeros_C2_J6[i] = 0.0;
  //   double result_i  = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  //   double err_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  //   double chi2ndof_i = templateFitter(do_data, 0,0,1,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C2_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

  //   c_input_C2_J6[i] = c_input_C2_J6[i] + 3.*small_shift;
    
  //   result_C2_J6[i] = result_i / nominal_result_C2_J6;
  //   deviation_C2_J6[i] = TMath::Abs((result_i - nominal_result_C2_J6)/nominal_result_C2_J6);

  //   double b1 = result_i;
  //   double b2 = nominal_result_C2_J6;
  //   double e1 = err_i;
  //   double e2 = nominal_err_C2_J6;
  //   double b1sq = b1*b1; double b2sq = b2*b2;
  //   double e1sq = e1*e1; double e2sq = e2*e2;
  //   err_result_C2_J6[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
  //   // err_result_C2_J6[i] = (result_i / nominal_result_C2_J6) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C2_J6 / nominal_result_C2_J6)*(nominal_err_C2_J6 / nominal_result_C2_J6));

  //   chi2ndof_C2_J6[i] = chi2ndof_i;

  // }

  // TGraphErrors *gr_C2_J6 = new TGraphErrors(N_c_input_C2_J6,c_input_C2_J6,result_C2_J6,zeros_C2_J6,err_result_C2_J6);
  // TGraph *gr_chi2ndof_C2_J6 = new TGraph(N_c_input_C2_J6,c_input_C2_J6,chi2ndof_C2_J6);




  
  // // find max of deviaton array to use as systematic error
  // double sys_err_val_C2_J1 = 0.0;
  // for(int i = 0; i < N_c_input_C2_J1; i++){
  //   double dev_i = deviation_C2_J1[i];
  //   if(dev_i > sys_err_val_C2_J1) sys_err_val_C2_J1 = dev_i;
  // }
  // double sys_err_val_C2_J2 = 0.0;
  // for(int i = 0; i < N_c_input_C2_J2; i++){
  //   double dev_i = deviation_C2_J2[i];
  //   if(dev_i > sys_err_val_C2_J2) sys_err_val_C2_J2 = dev_i;
  // }
  // double sys_err_val_C2_J3 = 0.0;
  // for(int i = 0; i < N_c_input_C2_J3; i++){
  //   double dev_i = deviation_C2_J3[i];
  //   if(dev_i > sys_err_val_C2_J3) sys_err_val_C2_J3 = dev_i;
  // }
  // double sys_err_val_C2_J4 = 0.0;
  // for(int i = 0; i < N_c_input_C2_J4; i++){
  //   double dev_i = deviation_C2_J4[i];
  //   if(dev_i > sys_err_val_C2_J4) sys_err_val_C2_J4 = dev_i;
  // }
  // double sys_err_val_C2_J5 = 0.0;
  // for(int i = 0; i < N_c_input_C2_J5; i++){
  //   double dev_i = deviation_C2_J5[i];
  //   if(dev_i > sys_err_val_C2_J5) sys_err_val_C2_J5 = dev_i;
  // }
  // double sys_err_val_C2_J6 = 0.0;
  // for(int i = 0; i < N_c_input_C2_J6; i++){
  //   double dev_i = deviation_C2_J6[i];
  //   if(dev_i > sys_err_val_C2_J6) sys_err_val_C2_J6 = dev_i;
  // }  

  // // stylize the curves
  // gr_C2_J1->SetLineColor(kBlack);
  // gr_C2_J2->SetLineColor(kBlue-4);
  // gr_C2_J3->SetLineColor(kRed-4);
  // gr_C2_J4->SetLineColor(kGreen+2);
  // gr_C2_J5->SetLineColor(kMagenta-3);
  // gr_C2_J6->SetLineColor(kOrange);

  // gr_C2_J1->SetMarkerColor(kBlack);
  // gr_C2_J2->SetMarkerColor(kBlue-4);
  // gr_C2_J3->SetMarkerColor(kRed-4);
  // gr_C2_J4->SetMarkerColor(kGreen+2);
  // gr_C2_J5->SetMarkerColor(kMagenta-3);
  // gr_C2_J6->SetMarkerColor(kOrange);

  // gr_C2_J1->SetMarkerStyle(34);
  // gr_C2_J2->SetMarkerStyle(20);
  // gr_C2_J3->SetMarkerStyle(21);
  // gr_C2_J4->SetMarkerStyle(22);
  // gr_C2_J5->SetMarkerStyle(33);
  // gr_C2_J6->SetMarkerStyle(29);

  // gr_C2_J1->SetLineWidth(line_width);
  // gr_C2_J2->SetLineWidth(line_width);
  // gr_C2_J3->SetLineWidth(line_width);
  // gr_C2_J4->SetLineWidth(line_width);
  // gr_C2_J5->SetLineWidth(line_width);
  // gr_C2_J6->SetLineWidth(line_width);

  // gr_C2_J1->SetMarkerSize(marker_size);
  // gr_C2_J2->SetMarkerSize(marker_size);
  // gr_C2_J3->SetMarkerSize(marker_size);
  // gr_C2_J4->SetMarkerSize(marker_size);
  // gr_C2_J5->SetMarkerSize(marker_size);
  // gr_C2_J6->SetMarkerSize(marker_size);


  // gr_chi2ndof_C2_J1->SetLineColor(kBlack);
  // gr_chi2ndof_C2_J2->SetLineColor(kBlue-4);
  // gr_chi2ndof_C2_J3->SetLineColor(kRed-4);
  // gr_chi2ndof_C2_J4->SetLineColor(kGreen+2);
  // gr_chi2ndof_C2_J5->SetLineColor(kMagenta-3);
  // gr_chi2ndof_C2_J6->SetLineColor(kOrange);

  // gr_chi2ndof_C2_J1->SetMarkerColor(kBlack);
  // gr_chi2ndof_C2_J2->SetMarkerColor(kBlue-4);
  // gr_chi2ndof_C2_J3->SetMarkerColor(kRed-4);
  // gr_chi2ndof_C2_J4->SetMarkerColor(kGreen+2);
  // gr_chi2ndof_C2_J5->SetMarkerColor(kMagenta-3);
  // gr_chi2ndof_C2_J6->SetMarkerColor(kOrange);

  // gr_chi2ndof_C2_J1->SetMarkerStyle(34);
  // gr_chi2ndof_C2_J2->SetMarkerStyle(20);
  // gr_chi2ndof_C2_J3->SetMarkerStyle(21);
  // gr_chi2ndof_C2_J4->SetMarkerStyle(22);
  // gr_chi2ndof_C2_J5->SetMarkerStyle(33);
  // gr_chi2ndof_C2_J6->SetMarkerStyle(29);

  // TCanvas *canv_mg_C2 = new TCanvas("canv_mg_C2","canv_mg_C2",700,700);
  // canv_mg_C2->cd();
  // TPad *pad_mg_C2 = new TPad("pad_mg_C2","pad_mg_C2",0,0.,1,1);
  // TPad *pad_mg_C2_low = new TPad("pad_mg_C2","pad_mg_C2",0,0,1,0.3);
  // pad_mg_C2->SetLeftMargin(0.15);
  // pad_mg_C2_low->SetLeftMargin(0.15);
  // pad_mg_C2->SetBottomMargin(0.2);
  // pad_mg_C2_low->SetTopMargin(0.0);
  // pad_mg_C2_low->SetBottomMargin(0.2);
  // pad_mg_C2_low->SetLogy(0);
  // pad_mg_C2->Draw();
  // //pad_mg_C2_low->Draw();
  // pad_mg_C2->cd();
  // // multigraph for C2
  // TMultiGraph *mg_C2 = new TMultiGraph();
  // mg_C2->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  // mg_C2->GetXaxis()->SetTitle("Fit lower bound [GeV]");
  // mg_C2->SetTitle("");
  // mg_C2->Add(gr_C2_J1);  
  // mg_C2->Add(gr_C2_J2);
  // mg_C2->Add(gr_C2_J3);
  // mg_C2->Add(gr_C2_J4);
  // mg_C2->Add(gr_C2_J5);
  // mg_C2->Add(gr_C2_J6);    
  // mg_C2->GetXaxis()->SetLimits(-0.05,0.55);
  // mg_C2->GetYaxis()->SetRangeUser(0.75,1.25);
  // mg_C2->Draw("AP");
  // TLegend *leg_mg_C2 = new TLegend(0.55,0.25,0.88,0.45);
  // leg_mg_C2->SetBorderSize(0);
  // leg_mg_C2->SetTextSize(0.03);
  // leg_mg_C2->AddEntry(gr_C2_J1,"80 < #it{p}_{T}^{jet} < 90 GeV","p");  
  // leg_mg_C2->AddEntry(gr_C2_J2,"90 < #it{p}_{T}^{jet} < 100 GeV","p");
  // leg_mg_C2->AddEntry(gr_C2_J3,"100 < #it{p}_{T}^{jet} < 120 GeV","p");
  // leg_mg_C2->AddEntry(gr_C2_J4,"120 < #it{p}_{T}^{jet} < 150 GeV","p");
  // leg_mg_C2->AddEntry(gr_C2_J5,"150 < #it{p}_{T}^{jet} < 200 GeV","p");
  // leg_mg_C2->AddEntry(gr_C2_J6,"200 < #it{p}_{T}^{jet} < 300 GeV","p");
  // leg_mg_C2->Draw();
  // li->DrawLine(-0.05,1,.55,1);
  // la->SetTextSize(0.036);
  // TString C2_data_info_string = "";
  // TString C2_trigger_info_string = "";
  // C2_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}       #font[42]{PbPb 10-30% 5.02 TeV)}";
  // C2_trigger_info_string = "#font[42]{#scale[0.8]{mu12 trigger}}";
  // la->DrawLatexNDC(0.17,0.92,C2_data_info_string);
  // //la->DrawLatexNDC(0.25,0.83,C2_trigger_info_string);
  // TString C2_canv_save_string = "";
  // C2_canv_save_string = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/lower-bound/C2.pdf";
  // la->SetTextSize(0.032);
  // la->SetTextColor(kBlack);
  // la->DrawLatexNDC(0.2,0.43,Form("%3.2f %%",100*sys_err_val_C2_J1));
  // la->SetTextColor(kBlue-4);
  // la->DrawLatexNDC(0.2,0.39,Form("%3.2f %%",100*sys_err_val_C2_J2));
  // la->SetTextColor(kRed-4);
  // la->DrawLatexNDC(0.2,0.35,Form("%3.2f %%",100*sys_err_val_C2_J3));
  // la->SetTextColor(kGreen+2);
  // la->DrawLatexNDC(0.2,0.31,Form("%3.2f %%",100*sys_err_val_C2_J4));
  // la->SetTextColor(kMagenta-3);
  // la->DrawLatexNDC(0.2,0.27,Form("%3.2f %%",100*sys_err_val_C2_J5));
  // la->SetTextColor(kOrange);
  // la->DrawLatexNDC(0.2,0.23,Form("%3.2f %%",100*sys_err_val_C2_J6));
  // la->SetTextSize(0.036);
  // la->SetTextColor(kBlack);
  // canv_mg_C2->SaveAs(C2_canv_save_string);

  ////// *************************************************************************************************************** ///////////////

  

  // J1 settings set by hand
  low_jetPt = 80.;
  high_jetPt = 90.;
  double zeros_C1_J1[N_c_input_C1_J1] = {0};
  double deviation_C1_J1[N_c_input_C1_J1] = {0};
  double nominal_result_C1_J1 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  double nominal_err_C1_J1 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  for(int i = 0; i < N_c_input_C1_J1; i++){

    //    zeros_C1_J1[i] = 0.0;
    double result_i  = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
    double err_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
    double chi2ndof_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J1[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    //cout << "CHI2 / NDOF ===== " << chi2ndof_i << endl;

    c_input_C1_J1[i] = c_input_C1_J1[i] - 2.*small_shift;
    
    result_C1_J1[i] = result_i / nominal_result_C1_J1;
    deviation_C1_J1[i] = TMath::Abs((result_i - nominal_result_C1_J1)/nominal_result_C1_J1);

    double b1 = result_i;
    double b2 = nominal_result_C1_J1;
    double e1 = err_i;
    double e2 = nominal_err_C1_J1;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_C1_J1[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_C1_J1[i] = (result_i / nominal_result_C1_J1) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C1_J1 / nominal_result_C1_J1)*(nominal_err_C1_J1 / nominal_result_C1_J1));

    chi2ndof_C1_J1[i] = chi2ndof_i;

  }

  TGraphErrors *gr_C1_J1 = new TGraphErrors(N_c_input_C1_J1,c_input_C1_J1,result_C1_J1,zeros_C1_J1,err_result_C1_J1);
  TGraph *gr_chi2ndof_C1_J1 = new TGraph(N_c_input_C1_J1,c_input_C1_J1,chi2ndof_C1_J1);

  // J2 settings set by hand
  low_jetPt = 90.;
  high_jetPt = 100.;
  double zeros_C1_J2[N_c_input_C1_J2] = {0};
  double deviation_C1_J2[N_c_input_C1_J2] = {0};
  double nominal_result_C1_J2 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  double nominal_err_C1_J2 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  for(int i = 0; i < N_c_input_C1_J2; i++){

    //    zeros_C1_J2[i] = 0.0;
    double result_i  = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
    double err_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
    double chi2ndof_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J2[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    //cout << "CHI2 / NDOF ===== " << chi2ndof_i << endl;

    c_input_C1_J2[i] = c_input_C1_J2[i] - 1.*small_shift;
    
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

    chi2ndof_C1_J2[i] = chi2ndof_i;

  }

  TGraphErrors *gr_C1_J2 = new TGraphErrors(N_c_input_C1_J2,c_input_C1_J2,result_C1_J2,zeros_C1_J2,err_result_C1_J2);
  TGraph *gr_chi2ndof_C1_J2 = new TGraph(N_c_input_C1_J2,c_input_C1_J2,chi2ndof_C1_J2);
  

  // J3 settings set by hand
  low_jetPt = 100.;
  high_jetPt = 120.;
  double zeros_C1_J3[N_c_input_C1_J3] = {0};
  double deviation_C1_J3[N_c_input_C1_J3] = {0};
  double nominal_result_C1_J3 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  double nominal_err_C1_J3 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  for(int i = 0; i < N_c_input_C1_J3; i++){

    //    zeros_C1_J3[i] = 0.0;
    double result_i  = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
    double err_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
    double chi2ndof_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J3[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    
    
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

    chi2ndof_C1_J3[i] = chi2ndof_i;

  }

  TGraphErrors *gr_C1_J3 = new TGraphErrors(N_c_input_C1_J3,c_input_C1_J3,result_C1_J3,zeros_C1_J3,err_result_C1_J3);
  TGraph *gr_chi2ndof_C1_J3 = new TGraph(N_c_input_C1_J3,c_input_C1_J3,chi2ndof_C1_J3);

  // J4 settings set by hand
  low_jetPt = 120.;
  high_jetPt = 150.;  
  double zeros_C1_J4[N_c_input_C1_J4] = {0};
  double deviation_C1_J4[N_c_input_C1_J4] = {0};
  double nominal_result_C1_J4 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  double nominal_err_C1_J4 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  for(int i = 0; i < N_c_input_C1_J4; i++){

    //    zeros_C1_J4[i] = 0.0;
    double result_i  = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
    double err_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
    double chi2ndof_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J4[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

    c_input_C1_J4[i] = c_input_C1_J4[i] + 1.*small_shift;
    
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

    chi2ndof_C1_J4[i] = chi2ndof_i;

  }

  TGraphErrors *gr_C1_J4 = new TGraphErrors(N_c_input_C1_J4,c_input_C1_J4,result_C1_J4,zeros_C1_J4,err_result_C1_J4);
  TGraph *gr_chi2ndof_C1_J4 = new TGraph(N_c_input_C1_J4,c_input_C1_J4,chi2ndof_C1_J4);

  // J5 settings set by hand
  low_jetPt = 150.;
  high_jetPt = 200.;  
  double zeros_C1_J5[N_c_input_C1_J5] = {0};
  double deviation_C1_J5[N_c_input_C1_J5] = {0};
  double nominal_result_C1_J5 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  double nominal_err_C1_J5 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  for(int i = 0; i < N_c_input_C1_J5; i++){

    //    zeros_C1_J5[i] = 0.0;
    double result_i  = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
    double err_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
    double chi2ndof_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J5[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

    c_input_C1_J5[i] = c_input_C1_J5[i] + 2.*small_shift;
    
    result_C1_J5[i] = result_i / nominal_result_C1_J5;
    deviation_C1_J5[i] = TMath::Abs((result_i - nominal_result_C1_J5)/nominal_result_C1_J5);

    double b1 = result_i;
    double b2 = nominal_result_C1_J5;
    double e1 = err_i;
    double e2 = nominal_err_C1_J5;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_C1_J5[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_C1_J5[i] = (result_i / nominal_result_C1_J5) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C1_J5 / nominal_result_C1_J5)*(nominal_err_C1_J5 / nominal_result_C1_J5));

    chi2ndof_C1_J5[i] = chi2ndof_i;

  }

  TGraphErrors *gr_C1_J5 = new TGraphErrors(N_c_input_C1_J5,c_input_C1_J5,result_C1_J5,zeros_C1_J5,err_result_C1_J5);
  TGraph *gr_chi2ndof_C1_J5 = new TGraph(N_c_input_C1_J5,c_input_C1_J5,chi2ndof_C1_J5);

  // J6 settings by hand
  low_jetPt = 200.;
  high_jetPt = 300.;  
  double zeros_C1_J6[N_c_input_C1_J6] = {0};
  double deviation_C1_J6[N_c_input_C1_J6] = {0};
  double nominal_result_C1_J6 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
  double nominal_err_C1_J6 = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
  
  for(int i = 0; i < N_c_input_C1_J6; i++){

    //    zeros_C1_J6[i] = 0.0;
    double result_i  = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 1);
    double err_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 2);
    double chi2ndof_i = templateFitter(do_data, 0,1,0,0, low_jetPt,high_jetPt, do_mergeB,do_mergeC,  do_2tempFit,do_3tempFit,  c_input_C1_J6[i],pTrel_fit_high, c_multiplier , bGS_multiplier, 3);
    

    c_input_C1_J6[i] = c_input_C1_J6[i] + 3.*small_shift;
    
    result_C1_J6[i] = result_i / nominal_result_C1_J6;
    deviation_C1_J6[i] = TMath::Abs((result_i - nominal_result_C1_J6)/nominal_result_C1_J6);

    double b1 = result_i;
    double b2 = nominal_result_C1_J6;
    double e1 = err_i;
    double e2 = nominal_err_C1_J6;
    double b1sq = b1*b1; double b2sq = b2*b2;
    double e1sq = e1*e1; double e2sq = e2*e2;
    err_result_C1_J6[i] = TMath::Abs(((1. - 2.*b1/b2)*e1sq + b1sq*e2sq/b2sq) / b2sq);
    // err_result_C1_J6[i] = (result_i / nominal_result_C1_J6) * TMath::Sqrt((err_i/result_i)*(err_i/result_i) + (nominal_err_C1_J6 / nominal_result_C1_J6)*(nominal_err_C1_J6 / nominal_result_C1_J6));

    chi2ndof_C1_J6[i] = chi2ndof_i;

  }

  TGraphErrors *gr_C1_J6 = new TGraphErrors(N_c_input_C1_J6,c_input_C1_J6,result_C1_J6,zeros_C1_J6,err_result_C1_J6);
  TGraph *gr_chi2ndof_C1_J6 = new TGraph(N_c_input_C1_J6,c_input_C1_J6,chi2ndof_C1_J6);




  
  // find max of deviaton array to use as systematic error
  double sys_err_val_C1_J1 = 0.0;
  for(int i = 0; i < N_c_input_C1_J1; i++){
    double dev_i = deviation_C1_J1[i];
    if(dev_i > sys_err_val_C1_J1) sys_err_val_C1_J1 = dev_i;
  }
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
  double sys_err_val_C1_J5 = 0.0;
  for(int i = 0; i < N_c_input_C1_J5; i++){
    double dev_i = deviation_C1_J5[i];
    if(dev_i > sys_err_val_C1_J5) sys_err_val_C1_J5 = dev_i;
  }
  double sys_err_val_C1_J6 = 0.0;
  for(int i = 0; i < N_c_input_C1_J6; i++){
    double dev_i = deviation_C1_J6[i];
    if(dev_i > sys_err_val_C1_J6) sys_err_val_C1_J6 = dev_i;
  }  

  // stylize the curves
  gr_C1_J1->SetLineColor(kBlack);
  gr_C1_J2->SetLineColor(kBlue-4);
  gr_C1_J3->SetLineColor(kRed-4);
  gr_C1_J4->SetLineColor(kGreen+2);
  gr_C1_J5->SetLineColor(kMagenta-3);
  gr_C1_J6->SetLineColor(kOrange);

  gr_C1_J1->SetMarkerColor(kBlack);
  gr_C1_J2->SetMarkerColor(kBlue-4);
  gr_C1_J3->SetMarkerColor(kRed-4);
  gr_C1_J4->SetMarkerColor(kGreen+2);
  gr_C1_J5->SetMarkerColor(kMagenta-3);
  gr_C1_J6->SetMarkerColor(kOrange);

  gr_C1_J1->SetMarkerStyle(34);
  gr_C1_J2->SetMarkerStyle(20);
  gr_C1_J3->SetMarkerStyle(21);
  gr_C1_J4->SetMarkerStyle(22);
  gr_C1_J5->SetMarkerStyle(33);
  gr_C1_J6->SetMarkerStyle(29);

  gr_C1_J1->SetLineWidth(line_width);
  gr_C1_J2->SetLineWidth(line_width);
  gr_C1_J3->SetLineWidth(line_width);
  gr_C1_J4->SetLineWidth(line_width);
  gr_C1_J5->SetLineWidth(line_width);
  gr_C1_J6->SetLineWidth(line_width);

  gr_C1_J1->SetMarkerSize(marker_size);
  gr_C1_J2->SetMarkerSize(marker_size);
  gr_C1_J3->SetMarkerSize(marker_size);
  gr_C1_J4->SetMarkerSize(marker_size);
  gr_C1_J5->SetMarkerSize(marker_size);
  gr_C1_J6->SetMarkerSize(marker_size);
  
  gr_chi2ndof_C1_J1->SetLineColor(kBlack);
  gr_chi2ndof_C1_J2->SetLineColor(kBlue-4);
  gr_chi2ndof_C1_J3->SetLineColor(kRed-4);
  gr_chi2ndof_C1_J4->SetLineColor(kGreen+2);
  gr_chi2ndof_C1_J5->SetLineColor(kMagenta-3);
  gr_chi2ndof_C1_J6->SetLineColor(kOrange);

  gr_chi2ndof_C1_J1->SetMarkerColor(kBlack);
  gr_chi2ndof_C1_J2->SetMarkerColor(kBlue-4);
  gr_chi2ndof_C1_J3->SetMarkerColor(kRed-4);
  gr_chi2ndof_C1_J4->SetMarkerColor(kGreen+2);
  gr_chi2ndof_C1_J5->SetMarkerColor(kMagenta-3);
  gr_chi2ndof_C1_J6->SetMarkerColor(kOrange);

  gr_chi2ndof_C1_J1->SetMarkerStyle(34);
  gr_chi2ndof_C1_J2->SetMarkerStyle(20);
  gr_chi2ndof_C1_J3->SetMarkerStyle(21);
  gr_chi2ndof_C1_J4->SetMarkerStyle(22);
  gr_chi2ndof_C1_J5->SetMarkerStyle(33);
  gr_chi2ndof_C1_J6->SetMarkerStyle(29);

  TCanvas *canv_mg_C1 = new TCanvas("canv_mg_C1","canv_mg_C1",700,700);
  canv_mg_C1->cd();
  TPad *pad_mg_C1 = new TPad("pad_mg_C1","pad_mg_C1",0,0.,1,1);
  TPad *pad_mg_C1_low = new TPad("pad_mg_C1","pad_mg_C1",0,0,1,0.3);
  pad_mg_C1->SetLeftMargin(0.15);
  pad_mg_C1_low->SetLeftMargin(0.15);
  pad_mg_C1->SetBottomMargin(0.2);
  pad_mg_C1_low->SetTopMargin(0.0);
  pad_mg_C1_low->SetBottomMargin(0.2);
  pad_mg_C1_low->SetLogy(0);
  pad_mg_C1->Draw();
  //pad_mg_C1_low->Draw();
  pad_mg_C1->cd();
  // multigraph for C1
  TMultiGraph *mg_C1 = new TMultiGraph();
  mg_C1->GetYaxis()->SetTitle("#it{b}-purity deviation from nominal");
  mg_C1->GetXaxis()->SetTitle("Fit lower bound [GeV]");
  mg_C1->SetTitle("");
  mg_C1->Add(gr_C1_J1);  
  mg_C1->Add(gr_C1_J2);
  mg_C1->Add(gr_C1_J3);
  mg_C1->Add(gr_C1_J4);
  mg_C1->Add(gr_C1_J5);
  mg_C1->Add(gr_C1_J6);    
  mg_C1->GetXaxis()->SetLimits(-0.05,0.55);
  mg_C1->GetYaxis()->SetRangeUser(0.75,1.25);
  mg_C1->Draw("AP");
  TLegend *leg_mg_C1 = new TLegend(0.55,0.25,0.88,0.45);
  leg_mg_C1->SetBorderSize(0);
  leg_mg_C1->SetTextSize(0.03);
  leg_mg_C1->AddEntry(gr_C1_J1,"80 < #it{p}_{T}^{jet} < 90 GeV","p");  
  leg_mg_C1->AddEntry(gr_C1_J2,"90 < #it{p}_{T}^{jet} < 100 GeV","p");
  leg_mg_C1->AddEntry(gr_C1_J3,"100 < #it{p}_{T}^{jet} < 120 GeV","p");
  leg_mg_C1->AddEntry(gr_C1_J4,"120 < #it{p}_{T}^{jet} < 150 GeV","p");
  leg_mg_C1->AddEntry(gr_C1_J5,"150 < #it{p}_{T}^{jet} < 200 GeV","p");
  leg_mg_C1->AddEntry(gr_C1_J6,"200 < #it{p}_{T}^{jet} < 300 GeV","p");
  leg_mg_C1->Draw();
  li->DrawLine(-0.05,1,.55,1);
  la->SetTextSize(0.036);
  TString C1_data_info_string = "";
  TString C1_trigger_info_string = "";
  C1_data_info_string = "#font[62]{CMS }#font[52]{#scale[0.8]{Premilinary}}       #font[42]{PbPb 0-10% 5.02 TeV)}";
  C1_trigger_info_string = "#font[42]{#scale[0.8]{mu12 trigger}}";
  la->DrawLatexNDC(0.17,0.92,C1_data_info_string);
  //la->DrawLatexNDC(0.25,0.83,C1_trigger_info_string);
  TString C1_canv_save_string = "";
  C1_canv_save_string = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/lower-bound/C1.pdf";
  la->SetTextSize(0.032);
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.2,0.43,Form("%3.2f %%",100*sys_err_val_C1_J1));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.2,0.39,Form("%3.2f %%",100*sys_err_val_C1_J2));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.2,0.35,Form("%3.2f %%",100*sys_err_val_C1_J3));
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.2,0.31,Form("%3.2f %%",100*sys_err_val_C1_J4));
  la->SetTextColor(kMagenta-3);
  la->DrawLatexNDC(0.2,0.27,Form("%3.2f %%",100*sys_err_val_C1_J5));
  la->SetTextColor(kOrange);
  la->DrawLatexNDC(0.2,0.23,Form("%3.2f %%",100*sys_err_val_C1_J6));
  la->SetTextSize(0.036);
  la->SetTextColor(kBlack);
  canv_mg_C1->SaveAs(C1_canv_save_string);
    

}
