
#include "../templateFitter/templateFitter_projectableTemplates_3CentBins.h"

void bPurityCalculator_projectableTemplates_3CentBins_oneOff(){

  cout << endl;
  cout << "#######  RUNNING B-PURITY CALCULATOR (v. 3-cent-bins.One-Off) #########" << endl;
  cout << endl;
  
  // const int N_jetPtAxisEdges = 5;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {60,80,120,200,300};
  // double jetPtCenters[N_jetPtAxisEdges-1] = {70,100,160,250};
  // double jetPtWidths[N_jetPtAxisEdges-1] = {10,20,40,50};




  // templateFitter(isData,  inMu5, isMu7, isMu12, ispp,isC1,isC2,  isJ1,isJ2,isJ3,isJ4,isJ5,isJ6,  mergeC,mergeB,
  //                               2tempFit,3tempFit,  low_x,high_x,  c_multiplier, bGS_multiplier, return)

  //templateFitter(1,  0,0,1,  0,1,0,0,0,0,  0,0,  0,1,  0.0,4.0,  1);

  int do_data = 1;

  int do_pp = 0;
  int do_C3 = 0;
  int do_C2 = 0;
  int do_C1 = 1;

  double low_jetPt = 80.;
  double high_jetPt = 100.;
  
  int do_mergeB = 1;
  int do_mergeC = 1;

  // one has to be 1, one has to be 0 for the fit integers
  int do_2tempFit = 0;
  int do_3tempFit = 1; 

  
  double pTrel_fit_low  = 0.0;
  double pTrel_fit_high = 5.0;

  double c_multiplier = 1.0;
  double bGS_multiplier = 1.0;

  
  templateFitter(do_data, do_pp,do_C1,do_C2,do_C3,  low_jetPt,high_jetPt,  do_mergeC,do_mergeB,  do_2tempFit,do_3tempFit,  pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 1);

  

}

