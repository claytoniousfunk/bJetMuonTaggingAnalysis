
#include "../templateFitter/templateFitter.h"

void bPurityCalculator_oneOff(){

  cout << endl;
  cout << "#######  RUNNING B-PURITY CALCULATOR (v. One-Off) #########" << endl;
  cout << endl;
  
  // const int N_jetPtAxisEdges = 5;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {60,80,120,200,300};
  // double jetPtCenters[N_jetPtAxisEdges-1] = {70,100,160,250};
  // double jetPtWidths[N_jetPtAxisEdges-1] = {10,20,40,50};

  const int N_jetPtAxisEdges = 6;
  double jetPtAxisEdges[N_jetPtAxisEdges] = {60,80,120,200,300,500};
  double jetPtCenters[N_jetPtAxisEdges-1] = {70,100,160,250,400};
  double jetPtWidths[N_jetPtAxisEdges-1] = {10,20,40,50,100};

  
  double results_pp[N_jetPtAxisEdges-1], err_results_pp[N_jetPtAxisEdges-1];
  double results_C2[N_jetPtAxisEdges-1], err_results_C2[N_jetPtAxisEdges-1];
  double results_C1[N_jetPtAxisEdges-1], err_results_C1[N_jetPtAxisEdges-1];


  // templateFitter(isData,  inMu5, isMu7, isMu12, ispp,isC1,isC2,  isJ1,isJ2,isJ3,isJ4,isJ5,isJ6,  mergeC,mergeB,
  //                               2tempFit,3tempFit,  low_x,high_x,  c_multiplier, bGS_multiplier, return)

  //templateFitter(1,  0,0,1,  0,1,0,0,0,0,  0,0,  0,1,  0.0,4.0,  1);

  

  int do_data = 1;
  
  int do_mu5  = 1;
  int do_mu7  = 0;
  int do_mu12 = 0;

  int do_pp = 1;
  int do_C2 = 0;
  int do_C1 = 0;

  int do_J1 = 0;
  int do_J2 = 1;
  int do_J3 = 0;
  int do_J4 = 0;
  int do_J5 = 0;
  int do_J6 = 0;
  
  int do_mergeB = 1;
  int do_mergeC = 1;

  int do_2tempFit = 1;
  int do_3tempFit = 0; // one has to 1, one has to be 0 for the fit integers

  
  double pTrel_fit_low  = 0.0;
  double pTrel_fit_high = 5.0;

  double c_multiplier = 1.0;
  double bGS_multiplier = 1.0;

  
  templateFitter(do_data, do_mu5,do_mu7,do_mu12,  do_pp,do_C1,do_C2,  do_J1,do_J2,do_J3,do_J4,do_J5,do_J6,  do_mergeC,do_mergeB,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 1);

  

}

