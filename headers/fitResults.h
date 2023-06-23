// Program: fitResults.h
// Author: Clayton Bennett
// Description:  This is a header file where my results will live.  This will allow multiple codes to access the data.
//
// Date : 13 October 2021



// Fits to PYTHIA
//
// with d0 cut
//
const int nFitVals = 5;
double x[nFitVals] = {55,70,100,160,350};
double ex[nFitVals] = {5,10,20,40,150};

// // mupt 6
// double PFit_d0[nFitVals] = {0.480833,0.460014,0.429087}; // ERRONEOUS
// double ePFit_d0[nFitVals] = {0.0134762,0.0137428,0.0137396}; 

// double PCount_d0[nFitVals] = {0.480489,0.457832,0.425968}; 
// double ePCount_d0[nFitVals] = {0.00916568,0.0080251,0.006365};

// // mupt 7
// double PFit_mupt7_d0[nFitVals] = {0,0,0}; 
// double ePFit_mupt7_d0[nFitVals] = {0,0,0}; 

// double PCount_mupt7_d0[nFitVals] = {0,0,0}; 
// double ePCount_mupt7_d0[nFitVals] = {0,0,0};




//no d0 cut
//

// mupt 6
// double PFit[nFitVals] = {0.370482,0.342162,0.317489}; 
// double ePFit[nFitVals] = {0.0106266,0.0109809,0.0112695}; 

// double PCount[nFitVals] = {0.369889,0.340114,0.309284}; 
// double ePCount[nFitVals] = {0.00618659,0.00530549,0.00405372};


// double PFit[nFitVals] = {4.20139e-01,3.87136e-01,3.57362e-01,3.29063e-01}; 
// double ePFit[nFitVals] = {1.74103e-02,2.18998e-02,2.95979e-02,5.32739e-02}; 

// double PCount[nFitVals] = {0.420301,0.386772,0.357382,0.328975}; 
// double ePCount[nFitVals] = {0.0101696,0.00783949,0.00652302,0.0049207};

// double GenPFit[nFitVals] = {4.57903e-01,4.50741e-01,4.33846e-01,4.11075e-01};
// double eGenPFit[nFitVals] = {9.97763e-03,7.71440e-03,1.02846e-02,1.62929e-02};

// double GenPCount[nFitVals] = {0.457736,0.450726,0.43377,0.411118};
// double eGenPCount[nFitVals] = {0.00810225,0.00537881,0.0040544,0.00317434};


// 5-10-22 - fit to PYTHIA_V2p0_L3Mu5_pthat0_15April22.root
//double PFit[nFitVals] = {4.11860e-01,3.83297e-01,3.55569e-01,3.29086e-01}; 
//double ePFit[nFitVals] = {2.21446e-02,2.19287e-02,2.84318e-02,4.80801e-02}; 

// double PCount[nFitVals] = {0.402573,0.37753,0.355607,0.328975}; 
// double ePCount[nFitVals] = {0.01706,0.00882878,0.00660292,0.0049207};

// 5-10-22, with ghost template, count remains unchanged
//double PFit[nFitVals] = {4.01752e-01,3.82481e-01,3.55558e-01,3.29114e-01}; 
//double ePFit[nFitVals] = {2.31265e-02,2.27352e-02,2.84423e-02,4.81425e-02}; 

// 5-10-22, with ghost template, overflow added to last bin, count remains unchanged
//double PFit[nFitVals] = {4.01752e-01,3.82481e-01,3.55558e-01,3.29114e-01}; 
//double ePFit[nFitVals] = {2.31265e-02,2.27352e-02,2.84423e-02,4.81425e-02}; 

// 5-10-22, NO ghost template, NO ghost entries, overflow added to last bin
//double PFit[nFitVals] = {4.13104e-01,3.78581e-01,3.55615e-01,3.28984e-01,2.80192e-01}; // fit to V2p0
//double ePFit[nFitVals] = {2.19757e-02,2.13727e-02,2.84330e-02,4.80821e-02,5.62143e-02}; 

// double PFit[nFitVals] = {4.09993e-01,3.73032e-01,3.50091e-01,3.23198e-01,2.73265e-01}; // fit to V2p3
// double ePFit[nFitVals] = {2.20375e-02,2.14247e-02,2.80099e-02,4.94818e-02,5.79372e-02};

//double PCount[nFitVals] = {0.413104,0.37858,0.355616,0.32899,0.280203}; 
//double ePCount[nFitVals] = {0.0147629,0.00880576,0.00660313,0.00492097,0.00398073};

// refit to make sure, 6-6-22

//double PFit[nFitVals] = {4.09993e-01,3.73032e-01,3.50091e-01,3.23198e-01,2.73265e-01};
//double ePFit[nFitVals] = {2.20375e-02,2.14247e-02,2.80099e-02,4.94818e-02,5.79372e-02};

// refit over larger ptrel range (0-10 GeV), 6-14-22

double PFit[nFitVals] = {4.09989e-01,3.73230e-01,3.50767e-01,3.26633e-01,2.81347e-01};
double ePFit[nFitVals] = {2.19998e-02,2.11229e-02,2.71559e-02,4.23385e-02,3.68806e-02};

double PFit_c[nFitVals] =  {3.32797e-01, 3.42016e-01, 3.33249e-01, 3.07347e-01, 3.08244e-01};
double ePFit_c[nFitVals] = {1.00639e-01, 9.14849e-02, 9.32135e-02, 9.34888e-02, 5.98686e-02};

double PFit_cFix[nFitVals] =  {4.09986e-01, 3.73230e-01, 3.50764e-01, 3.26633e-01, 1};
double ePFit_cFix[nFitVals] = {2.10198e-02, 1.33812e-02, 1.13583e-02, 9.43656e-03, 1};

double PFit_PH5090[nFitVals] =  {4.21748e-01, 4.17317e-01, 3.50410e-01, 2.29435e-01, 1};
double ePFit_PH5090[nFitVals] = {2.30326e-02, 2.13817e-02, 3.77251e-02, 2.95176e-02, 1};

double PFit_PH5090_cFix[nFitVals] =  {4.37278e-01, 4.20394e-01, 4.01712e-01, 3.38749e-01, 1};
double ePFit_PH5090_cFix[nFitVals] = {2.03357e-02, 1.51887e-02, 1.18909e-02, 9.97263e-03, 1};

double PH5090Fit_bAndCEnhanced_cFix[nFitVals] =  {2.75163e-01, 3.57063e-01, 3.41952e-01, 3.35268e-01, 1}; // using enhanced b and c enhanced templates
double ePH5090Fit_bAndCEnhanced_cFix[nFitVals] = {1.97411e-02, 2.02733e-02, 1.81179e-02, 1.71695e-02, 1};

double PH5090Fit_cFix[nFitVals] =  {3.99769e-01, 3.73553e-01, 3.57014e-01, 3.61600e-01, 1};
double ePH5090Fit_cFix[nFitVals] = {2.02558e-02, 2.02391e-02, 1.86968e-02, 1.73931e-02, 1};

double PH5090Fit_M[nFitVals] =  {3.97828e-01, 3.73599e-01, 3.58493e-01, 3.59640e-01, 1}; // from Matt's dijet sample
double ePH5090Fit_M[nFitVals] = {2.22465e-02, 2.13714e-02, 3.29773e-02, 4.11927e-02, 1};

double PH3050Fit_M[nFitVals] =  {4.12580e-01, 4.04616e-01, 3.60549e-01, 3.48621e-01, 1};
double ePH3050Fit_M[nFitVals] = {3.97083e-02, 3.06200e-02, 3.62275e-02, 6.07359e-02, 1};

double PH1030Fit_M[nFitVals] =  {4.24918e-01, 4.27286e-01, 4.01437e-01, 3.74709e-01, 1};
double ePH1030Fit_M[nFitVals] = {5.04354e-02, 4.53804e-02, 4.51725e-02, 4.08730e-02, 1};

double PH010Fit_M[nFitVals] =  {4.36691e-01, 4.54321e-01, 4.74900e-01, 3.88957e-01, 1};
double ePH010Fit_M[nFitVals] = {7.72052e-02, 6.60656e-02, 6.10570e-02, 5.11116e-02, 1};

double PH5090Fit[nFitVals] =  {4.25782e-01, 4.05711e-01, 3.42558e-01, 3.50631e-01, 1};
double ePH5090Fit[nFitVals] = {3.30365e-01, 5.25716e-02, 4.48932e-02, 4.94668e-02, 1};

double PH3050Fit[nFitVals] =  {3.85794e-01, 2.64778e-01, 3.67933e-01, 3.39134e-01, 1};
double ePH3050Fit[nFitVals] = {7.88337e-02, 5.46557e-02, 7.47913e-02, 8.17677e-02, 1};

double PH1030Fit[nFitVals] =  {2.63733e-01, 3.31279e-01, 2.67006e-01, 3.61552e-01, 1};
double ePH1030Fit[nFitVals] = {1.42829e-01, 8.54442e-02, 4.79770e-02, 6.42808e-02, 1};

double PH010Fit[nFitVals] =  {2.74297e-01, 7.26381e-02, 1.72406e-01, 3.65624e-01, 1};
double ePH010Fit[nFitVals] = {1.05252e-01, 7.81636e-02, 4.81805e-02, 9.42549e-02, 1};







//double ppFit[nFitVals] = {3.19506e-01,3.82734e-01,4.47511e-01,4.69282e-01,2.54564e-01};
//double eppFit[nFitVals] = {8.91582e-04,1.60208e-03,3.89223e-03,1.98975e-02,8.20827e-02};

// refit data over custom bJet ranges
double ppFit[nFitVals] =  {3.16561e-01, 3.87234e-01, 4.54356e-01, 4.49279e-01, 2.95294e-01};
double eppFit[nFitVals] = {8.97323e-04, 1.70260e-03, 3.93080e-03, 1.93542e-02, 7.32146e-02};

// cFit values
double ppFit_c[nFitVals] =  {5.53152e-01, 2.04641e-01, 3.21780e-02, 1.61796e-01, 3.99770e-01};
double eppFit_c[nFitVals] = {4.62764e-03, 7.91344e-03, 1.34322e-02, 4.15626e-02, 1.14681e-01};

// pp fit with cFixed to be PYTHIA value
double ppFit_cFix[nFitVals] =  {3.30632e-01, 3.63160e-01, 3.74892e-01, 3.83052e-01, 1};
double eppFit_cFix[nFitVals] = {8.47264e-04, 9.87669e-04, 1.69035e-03, 3.96425e-03, 1};

// pp fit with PH5090 templates
double ppFit_PH5090[nFitVals] =  {4.17988e-01, 4.02277e-01, 4.85426e-01, 3.60249e-01, 1};
double eppFit_PH5090[nFitVals] = {9.85547e-04, 1.51291e-03, 5.78271e-03, 1.44021e-02, 1};

// pp fit with PH5090 templates with fixed c value
double ppFit_PH5090_cFix[nFitVals] =  {4.28498e-01, 4.20302e-01, 4.29600e-01, 4.21520e-01, 1};
double eppFit_PH5090_cFix[nFitVals] = {9.01359e-04, 1.13333e-03, 1.78894e-03, 4.21755e-03, 1};











/*

// mupt 7
double PFit_mupt7[nFitVals] = {0.394179,0.362068,0.336746}; 
double ePFit_mupt7[nFitVals] = {0.0113459,0.011512,0.0121655}; 

double PCount_mupt7[nFitVals] = {0.393545,0.35984,0.32782}; 
double ePCount_mupt7[nFitVals] = {0.00701449,0.0058012,0.00450009};








double PHC2Fit[nFitVals] = {0.319987,0.2947,0.272913};
double ePHC2Fit[nFitVals] = {0.0221628,0.0221417,0.0269384};

double PHC1Fit[nFitVals] = {0.386185,0.281197,0.275063};
double ePHC1Fit[nFitVals] = {0.0447264,0.0422175,0.0468128};

double PHC0Fit[nFitVals] = {0,0,0};
double ePHC0Fit[nFitVals] = {0,0,0};

double PHC2Count[nFitVals] = {0.342112,0.294399,0.272238};
double ePHC2Count[nFitVals] = {0.0118394,0.00920062,0.00784126};

double PHC1Count[nFitVals] = {0.350895,0.300245,0.290191};
double ePHC1Count[nFitVals] = {0.0178128,0.0172952,0.0146977};

double PHC0Count[nFitVals] = {0,0,0};
double ePHC0Count[nFitVals] = {0,0,0};










// Fits to pp data
//
// with d0 cut
//
double ppFit_d0[nFitVals] = {0.610527,0.63583,0.633088};
double eppFit_d0[nFitVals] = {0.0048207,0.00844389,0.0212361};








// no d0 cut
//
// mupt 6
// double ppFit[nFitVals] = {0.458787,0.447171,0.411423};  // fit to Matts pp data forest
// double eppFit[nFitVals] = {0.00165544,0.00295249,0.00760472};

double ppFit[nFitVals] = {0.521238,0.546853,0.537679};
double eppFit[nFitVals] = {0.00387901,0.0068355,0.0169882};

// mupt 7
double ppFit_mupt7[nFitVals] = {0.477052,0.465334,0.432426};  // fit to Matts pp data forest
double eppFit_mupt7[nFitVals] = {0.00175195,0.00314519,0.00815407};

// mupt 7
double ppFit_mupt7_lxplus[nFitVals] = {0.488493,0.466708,0.414407};  // fit to my lxplus forest
double eppFit_mupt7_lxplus[nFitVals] = {0.00399082,0.0072896,0.0183623};

double PbPbFit_C2[nFitVals] = {0.472825,0.462711,0.0983651};
double ePbPbFit_C2[nFitVals] = {0.0184255,0.0335867,0.104825};

double PbPbFit_C1[nFitVals] = {0.622188,0.527841,0};
double ePbPbFit_C1[nFitVals] = {0.0155755,0.029533,0};

double PbPbFit_C0[nFitVals] = {0,0,0};
double ePbPbFit_C0[nFitVals] = {0,0,0};


*/

