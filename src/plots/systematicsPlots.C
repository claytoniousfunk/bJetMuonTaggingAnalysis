

#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/systematicsResults.h"


void systematicsPlots(bool do_mu5  = 0,
		      bool do_mu7  = 0,
		      bool do_mu12 = 1){

  TLatex *la = new TLatex();
  la->SetTextFont(42);


  // some draw options
  double new_bar_width = 0.3;
  double new_bar_offset = 0.05;


  ///  Calculate total
  const int N_sys_sources = 7;
  // pp

  // -- mu12
  double sys_total_pp_mu12_J1_array[N_sys_sources] = {sys_cFraction_pp_mu12_J1,
                                                      sys_lowerBound_pp_mu12_J1,
						      sys_JERsmear_pp_mu12_J1,
						      sys_bGS_pp_mu12_J1,
						      sys_JEUShiftUp_pp_mu12_J1,
						      sys_JEUShiftDown_pp_mu12_J1,
						      sys_residual_pp_mu12_J1};

  double sys_total_pp_mu12_J2_array[N_sys_sources] = {sys_cFraction_pp_mu12_J2,
                                                      sys_lowerBound_pp_mu12_J2,
						      sys_JERsmear_pp_mu12_J2,
						      sys_bGS_pp_mu12_J2,
						      sys_JEUShiftUp_pp_mu12_J2,
						      sys_JEUShiftDown_pp_mu12_J2,
						      sys_residual_pp_mu12_J2};

  double sys_total_pp_mu12_J3_array[N_sys_sources] = {sys_cFraction_pp_mu12_J3,
                                                      sys_lowerBound_pp_mu12_J3,
						      sys_JERsmear_pp_mu12_J3,
						      sys_bGS_pp_mu12_J3,
						      sys_JEUShiftUp_pp_mu12_J3,
						      sys_JEUShiftDown_pp_mu12_J3,
						      sys_residual_pp_mu12_J3};

  double sys_total_pp_mu12_J4_array[N_sys_sources] = {sys_cFraction_pp_mu12_J4,
                                                      sys_lowerBound_pp_mu12_J4,
						      sys_JERsmear_pp_mu12_J4,
						      sys_bGS_pp_mu12_J4,
						      sys_JEUShiftUp_pp_mu12_J4,
						      sys_JEUShiftDown_pp_mu12_J4,
						      sys_residual_pp_mu12_J4};

  double sys_total_pp_mu12_J5_array[N_sys_sources] = {sys_cFraction_pp_mu12_J5,
                                                      sys_lowerBound_pp_mu12_J5,
						      sys_JERsmear_pp_mu12_J5,
						      sys_bGS_pp_mu12_J5,
						      sys_JEUShiftUp_pp_mu12_J5,
						      sys_JEUShiftDown_pp_mu12_J5,
						      sys_residual_pp_mu12_J5};

  double sys_total_pp_mu12_J6_array[N_sys_sources] = {sys_cFraction_pp_mu12_J6,
                                                      sys_lowerBound_pp_mu12_J6,
						      sys_JERsmear_pp_mu12_J6,
						      sys_bGS_pp_mu12_J6,
						      sys_JEUShiftUp_pp_mu12_J6,
						      sys_JEUShiftDown_pp_mu12_J6,
						      sys_residual_pp_mu12_J6};


  // PbPb 30-90%
  // -- mu12
  double sys_total_PbPb_mu12_C2_J1_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J1,
                                                           sys_lowerBound_PbPb_mu12_C2_J1,
							   sys_JERsmear_PbPb_mu12_C2_J1,
							   sys_bGS_PbPb_mu12_C2_J1,
							   sys_JEUShiftUp_PbPb_mu12_C2_J1,
							   sys_JEUShiftDown_PbPb_mu12_C2_J1,
							   sys_residual_PbPb_mu12_C2_J1};

  double sys_total_PbPb_mu12_C2_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J2,
                                                           sys_lowerBound_PbPb_mu12_C2_J2,
							   sys_JERsmear_PbPb_mu12_C2_J2,
							   sys_bGS_PbPb_mu12_C2_J2,
							   sys_JEUShiftUp_PbPb_mu12_C2_J2,
							   sys_JEUShiftDown_PbPb_mu12_C2_J2,
							   sys_residual_PbPb_mu12_C2_J2};

  double sys_total_PbPb_mu12_C2_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J3,
                                                           sys_lowerBound_PbPb_mu12_C2_J3,
							   sys_JERsmear_PbPb_mu12_C2_J3,
							   sys_bGS_PbPb_mu12_C2_J3,
							   sys_JEUShiftUp_PbPb_mu12_C2_J3,
							   sys_JEUShiftDown_PbPb_mu12_C2_J3,
							   sys_residual_PbPb_mu12_C2_J3};

  double sys_total_PbPb_mu12_C2_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J4,
                                                           sys_lowerBound_PbPb_mu12_C2_J4,
							   sys_JERsmear_PbPb_mu12_C2_J4,
							   sys_bGS_PbPb_mu12_C2_J4,
							   sys_JEUShiftUp_PbPb_mu12_C2_J4,
							   sys_JEUShiftDown_PbPb_mu12_C2_J4,
							   sys_residual_PbPb_mu12_C2_J4};

  double sys_total_PbPb_mu12_C2_J5_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J5,
                                                           sys_lowerBound_PbPb_mu12_C2_J5,
							   sys_JERsmear_PbPb_mu12_C2_J5,
							   sys_bGS_PbPb_mu12_C2_J5,
							   sys_JEUShiftUp_PbPb_mu12_C2_J5,
							   sys_JEUShiftDown_PbPb_mu12_C2_J5,
							   sys_residual_PbPb_mu12_C2_J5};

  double sys_total_PbPb_mu12_C2_J6_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J6,
                                                           sys_lowerBound_PbPb_mu12_C2_J6,
							   sys_JERsmear_PbPb_mu12_C2_J6,
							   sys_bGS_PbPb_mu12_C2_J6,
							   sys_JEUShiftUp_PbPb_mu12_C2_J6,
							   sys_JEUShiftDown_PbPb_mu12_C2_J6,
							   sys_residual_PbPb_mu12_C2_J6};  

  // PbPb 0-30%
  // -- mu12
  double sys_total_PbPb_mu12_C1_J1_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J1,
                                                           sys_lowerBound_PbPb_mu12_C1_J1,
							   sys_JERsmear_PbPb_mu12_C1_J1,
							   sys_bGS_PbPb_mu12_C1_J1,
							   sys_JEUShiftUp_PbPb_mu12_C1_J1,
							   sys_JEUShiftDown_PbPb_mu12_C1_J1,
							   sys_residual_PbPb_mu12_C1_J1};

  double sys_total_PbPb_mu12_C1_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J2,
                                                           sys_lowerBound_PbPb_mu12_C1_J2,
							   sys_JERsmear_PbPb_mu12_C1_J2,
							   sys_bGS_PbPb_mu12_C1_J2,
							   sys_JEUShiftUp_PbPb_mu12_C1_J2,
							   sys_JEUShiftDown_PbPb_mu12_C1_J2,
							   sys_residual_PbPb_mu12_C1_J2};

  double sys_total_PbPb_mu12_C1_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J3,
                                                           sys_lowerBound_PbPb_mu12_C1_J3,
							   sys_JERsmear_PbPb_mu12_C1_J3,
							   sys_bGS_PbPb_mu12_C1_J3,
							   sys_JEUShiftUp_PbPb_mu12_C1_J3,
							   sys_JEUShiftDown_PbPb_mu12_C1_J3,
							   sys_residual_PbPb_mu12_C1_J3};

  double sys_total_PbPb_mu12_C1_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J4,
                                                           sys_lowerBound_PbPb_mu12_C1_J4,
							   sys_JERsmear_PbPb_mu12_C1_J4,
							   sys_bGS_PbPb_mu12_C1_J4,
							   sys_JEUShiftUp_PbPb_mu12_C1_J4,
							   sys_JEUShiftDown_PbPb_mu12_C1_J4,
							   sys_residual_PbPb_mu12_C1_J4};

  double sys_total_PbPb_mu12_C1_J5_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J5,
                                                           sys_lowerBound_PbPb_mu12_C1_J5,
							   sys_JERsmear_PbPb_mu12_C1_J5,
							   sys_bGS_PbPb_mu12_C1_J5,
							   sys_JEUShiftUp_PbPb_mu12_C1_J5,
							   sys_JEUShiftDown_PbPb_mu12_C1_J5,
							   sys_residual_PbPb_mu12_C1_J5};

  double sys_total_PbPb_mu12_C1_J6_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J6,
                                                           sys_lowerBound_PbPb_mu12_C1_J6,
							   sys_JERsmear_PbPb_mu12_C1_J6,
							   sys_bGS_PbPb_mu12_C1_J6,
							   sys_JEUShiftUp_PbPb_mu12_C1_J6,
							   sys_JEUShiftDown_PbPb_mu12_C1_J6,
							   sys_residual_PbPb_mu12_C1_J6};  



  double sys_total_pp_mu12_J1 = 0;
  double sys_total_pp_mu12_J2 = 0;
  double sys_total_pp_mu12_J3 = 0;
  double sys_total_pp_mu12_J4 = 0;
  double sys_total_pp_mu12_J5 = 0;
  double sys_total_pp_mu12_J6 = 0;

  double sys_total_PbPb_mu12_C2_J1 = 0;
  double sys_total_PbPb_mu12_C2_J2 = 0;
  double sys_total_PbPb_mu12_C2_J3 = 0;
  double sys_total_PbPb_mu12_C2_J4 = 0;
  double sys_total_PbPb_mu12_C2_J5 = 0;
  double sys_total_PbPb_mu12_C2_J6 = 0;

  double sys_total_PbPb_mu12_C1_J1 = 0;
  double sys_total_PbPb_mu12_C1_J2 = 0;  
  double sys_total_PbPb_mu12_C1_J3 = 0;
  double sys_total_PbPb_mu12_C1_J4 = 0;
  double sys_total_PbPb_mu12_C1_J5 = 0;
  double sys_total_PbPb_mu12_C1_J6 = 0;  


  // add the squares
  for(int i = 0; i < N_sys_sources; i++){

    // pp
    sys_total_pp_mu12_J1 += sys_total_pp_mu12_J1_array[i]*sys_total_pp_mu12_J1_array[i];
    sys_total_pp_mu12_J2 += sys_total_pp_mu12_J2_array[i]*sys_total_pp_mu12_J2_array[i];
    sys_total_pp_mu12_J3 += sys_total_pp_mu12_J3_array[i]*sys_total_pp_mu12_J3_array[i];
    sys_total_pp_mu12_J4 += sys_total_pp_mu12_J4_array[i]*sys_total_pp_mu12_J4_array[i];
    sys_total_pp_mu12_J5 += sys_total_pp_mu12_J5_array[i]*sys_total_pp_mu12_J5_array[i];
    sys_total_pp_mu12_J6 += sys_total_pp_mu12_J6_array[i]*sys_total_pp_mu12_J6_array[i];    

    // PbPb 30-90%
    sys_total_PbPb_mu12_C2_J1 += sys_total_PbPb_mu12_C2_J1_array[i]*sys_total_PbPb_mu12_C2_J1_array[i];
    sys_total_PbPb_mu12_C2_J2 += sys_total_PbPb_mu12_C2_J2_array[i]*sys_total_PbPb_mu12_C2_J2_array[i];    
    sys_total_PbPb_mu12_C2_J3 += sys_total_PbPb_mu12_C2_J3_array[i]*sys_total_PbPb_mu12_C2_J3_array[i];
    sys_total_PbPb_mu12_C2_J4 += sys_total_PbPb_mu12_C2_J4_array[i]*sys_total_PbPb_mu12_C2_J4_array[i];
    sys_total_PbPb_mu12_C2_J5 += sys_total_PbPb_mu12_C2_J5_array[i]*sys_total_PbPb_mu12_C2_J5_array[i];
    sys_total_PbPb_mu12_C2_J6 += sys_total_PbPb_mu12_C2_J6_array[i]*sys_total_PbPb_mu12_C2_J6_array[i];    

    // PbPb 0-30%
    sys_total_PbPb_mu12_C1_J1 += sys_total_PbPb_mu12_C1_J1_array[i]*sys_total_PbPb_mu12_C1_J1_array[i];
    sys_total_PbPb_mu12_C1_J2 += sys_total_PbPb_mu12_C1_J2_array[i]*sys_total_PbPb_mu12_C1_J2_array[i];
    sys_total_PbPb_mu12_C1_J3 += sys_total_PbPb_mu12_C1_J3_array[i]*sys_total_PbPb_mu12_C1_J3_array[i];
    sys_total_PbPb_mu12_C1_J4 += sys_total_PbPb_mu12_C1_J4_array[i]*sys_total_PbPb_mu12_C1_J4_array[i];
    sys_total_PbPb_mu12_C1_J5 += sys_total_PbPb_mu12_C1_J5_array[i]*sys_total_PbPb_mu12_C1_J5_array[i];
    sys_total_PbPb_mu12_C1_J6 += sys_total_PbPb_mu12_C1_J6_array[i]*sys_total_PbPb_mu12_C1_J6_array[i];    

  }

  
  sys_total_pp_mu12_J1 = TMath::Sqrt(sys_total_pp_mu12_J1);
  sys_total_pp_mu12_J2 = TMath::Sqrt(sys_total_pp_mu12_J2);
  sys_total_pp_mu12_J3 = TMath::Sqrt(sys_total_pp_mu12_J3);
  sys_total_pp_mu12_J4 = TMath::Sqrt(sys_total_pp_mu12_J4);
  sys_total_pp_mu12_J5 = TMath::Sqrt(sys_total_pp_mu12_J5);
  sys_total_pp_mu12_J6 = TMath::Sqrt(sys_total_pp_mu12_J6);

  sys_total_PbPb_mu12_C2_J1 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J1);
  sys_total_PbPb_mu12_C2_J2 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J2);
  sys_total_PbPb_mu12_C2_J3 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J3);
  sys_total_PbPb_mu12_C2_J4 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J4);
  sys_total_PbPb_mu12_C2_J5 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J5);
  sys_total_PbPb_mu12_C2_J6 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J6);

  sys_total_PbPb_mu12_C1_J1 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J1);
  sys_total_PbPb_mu12_C1_J2 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J2);
  sys_total_PbPb_mu12_C1_J3 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J3);
  sys_total_PbPb_mu12_C1_J4 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J4);
  sys_total_PbPb_mu12_C1_J5 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J5);
  sys_total_PbPb_mu12_C1_J6 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J6);

  
  const int N_sys = 8;
  string sys_names[N_sys] = {"c-fraction-variation","fit-lower-bound","Jet-energy-resolution","bGS-multiplier","JES Shift-up", "JES Shift-down","Residual-non-closure","Total"};

  // pp
  // -- mu12
  double sys_pp_mu12_J1_array[N_sys] = {sys_cFraction_pp_mu12_J1, sys_lowerBound_pp_mu12_J1, sys_JERsmear_pp_mu12_J1, sys_bGS_pp_mu12_J1, sys_JEUShiftUp_pp_mu12_J1,sys_JEUShiftDown_pp_mu12_J1, sys_residual_pp_mu12_J1, sys_total_pp_mu12_J1};
  double sys_pp_mu12_J2_array[N_sys] = {sys_cFraction_pp_mu12_J2, sys_lowerBound_pp_mu12_J2, sys_JERsmear_pp_mu12_J2, sys_bGS_pp_mu12_J2, sys_JEUShiftUp_pp_mu12_J2,sys_JEUShiftDown_pp_mu12_J2, sys_residual_pp_mu12_J2, sys_total_pp_mu12_J2};
  double sys_pp_mu12_J3_array[N_sys] = {sys_cFraction_pp_mu12_J3, sys_lowerBound_pp_mu12_J3, sys_JERsmear_pp_mu12_J3, sys_bGS_pp_mu12_J3,sys_JEUShiftUp_pp_mu12_J3,sys_JEUShiftDown_pp_mu12_J3, sys_residual_pp_mu12_J3, sys_total_pp_mu12_J3};
  double sys_pp_mu12_J4_array[N_sys] = {sys_cFraction_pp_mu12_J4, sys_lowerBound_pp_mu12_J4, sys_JERsmear_pp_mu12_J4, sys_bGS_pp_mu12_J4,sys_JEUShiftUp_pp_mu12_J4,sys_JEUShiftDown_pp_mu12_J4, sys_residual_pp_mu12_J4, sys_total_pp_mu12_J4};
  double sys_pp_mu12_J5_array[N_sys] = {sys_cFraction_pp_mu12_J5, sys_lowerBound_pp_mu12_J5, sys_JERsmear_pp_mu12_J5, sys_bGS_pp_mu12_J5,sys_JEUShiftUp_pp_mu12_J5,sys_JEUShiftDown_pp_mu12_J5, sys_residual_pp_mu12_J5, sys_total_pp_mu12_J5};
  double sys_pp_mu12_J6_array[N_sys] = {sys_cFraction_pp_mu12_J6, sys_lowerBound_pp_mu12_J6, sys_JERsmear_pp_mu12_J6, sys_bGS_pp_mu12_J6,sys_JEUShiftUp_pp_mu12_J6,sys_JEUShiftDown_pp_mu12_J6, sys_residual_pp_mu12_J6, sys_total_pp_mu12_J6};  

  // PbPb 30-90%
  // -- mu12
  double sys_PbPb_mu12_C2_J1_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J1, sys_lowerBound_PbPb_mu12_C2_J1, sys_JERsmear_PbPb_mu12_C2_J1, sys_bGS_PbPb_mu12_C2_J1,sys_JEUShiftUp_PbPb_mu12_C2_J1,sys_JEUShiftDown_PbPb_mu12_C2_J1, sys_residual_PbPb_mu12_C2_J1, sys_total_PbPb_mu12_C2_J1};
  double sys_PbPb_mu12_C2_J2_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J2, sys_lowerBound_PbPb_mu12_C2_J2, sys_JERsmear_PbPb_mu12_C2_J2, sys_bGS_PbPb_mu12_C2_J2,sys_JEUShiftUp_PbPb_mu12_C2_J2,sys_JEUShiftDown_PbPb_mu12_C2_J2, sys_residual_PbPb_mu12_C2_J2, sys_total_PbPb_mu12_C2_J2};
  double sys_PbPb_mu12_C2_J3_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J3, sys_lowerBound_PbPb_mu12_C2_J3, sys_JERsmear_PbPb_mu12_C2_J3, sys_bGS_PbPb_mu12_C2_J3,sys_JEUShiftUp_PbPb_mu12_C2_J3,sys_JEUShiftDown_PbPb_mu12_C2_J3, sys_residual_PbPb_mu12_C2_J3, sys_total_PbPb_mu12_C2_J3};
  double sys_PbPb_mu12_C2_J4_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J4, sys_lowerBound_PbPb_mu12_C2_J4, sys_JERsmear_PbPb_mu12_C2_J4, sys_bGS_PbPb_mu12_C2_J4,sys_JEUShiftUp_PbPb_mu12_C2_J4,sys_JEUShiftDown_PbPb_mu12_C2_J4, sys_residual_PbPb_mu12_C2_J4, sys_total_PbPb_mu12_C2_J4};
  double sys_PbPb_mu12_C2_J5_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J5, sys_lowerBound_PbPb_mu12_C2_J5, sys_JERsmear_PbPb_mu12_C2_J5, sys_bGS_PbPb_mu12_C2_J5,sys_JEUShiftUp_PbPb_mu12_C2_J5,sys_JEUShiftDown_PbPb_mu12_C2_J5, sys_residual_PbPb_mu12_C2_J5, sys_total_PbPb_mu12_C2_J5};
  double sys_PbPb_mu12_C2_J6_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J6, sys_lowerBound_PbPb_mu12_C2_J6, sys_JERsmear_PbPb_mu12_C2_J6, sys_bGS_PbPb_mu12_C2_J6,sys_JEUShiftUp_PbPb_mu12_C2_J6,sys_JEUShiftDown_PbPb_mu12_C2_J6, sys_residual_PbPb_mu12_C2_J6, sys_total_PbPb_mu12_C2_J6};    

  // PbPb 0-30%
  // -- mu12
  double sys_PbPb_mu12_C1_J1_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J1, sys_lowerBound_PbPb_mu12_C1_J1, sys_JERsmear_PbPb_mu12_C1_J1, sys_bGS_PbPb_mu12_C1_J1,sys_JEUShiftUp_PbPb_mu12_C1_J1,sys_JEUShiftDown_PbPb_mu12_C1_J1, sys_residual_PbPb_mu12_C1_J1, sys_total_PbPb_mu12_C1_J1};
  double sys_PbPb_mu12_C1_J2_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J2, sys_lowerBound_PbPb_mu12_C1_J2, sys_JERsmear_PbPb_mu12_C1_J2, sys_bGS_PbPb_mu12_C1_J2,sys_JEUShiftUp_PbPb_mu12_C1_J2,sys_JEUShiftDown_PbPb_mu12_C1_J2, sys_residual_PbPb_mu12_C1_J2, sys_total_PbPb_mu12_C1_J2};  
  double sys_PbPb_mu12_C1_J3_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J3, sys_lowerBound_PbPb_mu12_C1_J3, sys_JERsmear_PbPb_mu12_C1_J3, sys_bGS_PbPb_mu12_C1_J3,sys_JEUShiftUp_PbPb_mu12_C1_J3,sys_JEUShiftDown_PbPb_mu12_C1_J3, sys_residual_PbPb_mu12_C1_J3, sys_total_PbPb_mu12_C1_J3};
  double sys_PbPb_mu12_C1_J4_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J4, sys_lowerBound_PbPb_mu12_C1_J4, sys_JERsmear_PbPb_mu12_C1_J4, sys_bGS_PbPb_mu12_C1_J4,sys_JEUShiftUp_PbPb_mu12_C1_J4,sys_JEUShiftDown_PbPb_mu12_C1_J4, sys_residual_PbPb_mu12_C1_J4, sys_total_PbPb_mu12_C1_J4};
  double sys_PbPb_mu12_C1_J5_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J5, sys_lowerBound_PbPb_mu12_C1_J5, sys_JERsmear_PbPb_mu12_C1_J5, sys_bGS_PbPb_mu12_C1_J5,sys_JEUShiftUp_PbPb_mu12_C1_J5,sys_JEUShiftDown_PbPb_mu12_C1_J5, sys_residual_PbPb_mu12_C1_J5, sys_total_PbPb_mu12_C1_J5};  
  double sys_PbPb_mu12_C1_J6_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J6, sys_lowerBound_PbPb_mu12_C1_J6, sys_JERsmear_PbPb_mu12_C1_J6, sys_bGS_PbPb_mu12_C1_J6,sys_JEUShiftUp_PbPb_mu12_C1_J6,sys_JEUShiftDown_PbPb_mu12_C1_J6, sys_residual_PbPb_mu12_C1_J6, sys_total_PbPb_mu12_C1_J6};
    

  TCanvas *canv_J1 = new TCanvas("canv_J1","canv_J1",800,800);
  canv_J1->cd();
  TPad *pad_J1 = new TPad("pad_J1","pad_J1",0,0,1,1);
  pad_J1->SetLeftMargin(0.2);
  pad_J1->SetBottomMargin(0.2);
  pad_J1->Draw();
  pad_J1->cd();

  TH1D *h0_sys_J1 = new TH1D("h0_sys_J1","h0_sys_J1",N_sys,0,1.0*N_sys);
  h0_sys_J1->SetFillColor(kGreen+2);
  h0_sys_J1->SetBarWidth(0.3);
  h0_sys_J1->SetBarOffset(0.05);
  h0_sys_J1->SetStats(0);
  h0_sys_J1->SetMinimum(0.0);
  h0_sys_J1->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J1->SetBinContent(i,sys_pp_mu12_J1_array[i-1]);
    h0_sys_J1->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }


  h0_sys_J1->GetXaxis()->SetTitleSize(0.06);
  // h0_sys_J1->SetBarWidth(new_bar_width);
  // h0_sys_J1->SetBarOffset(new_bar_offset);
  h0_sys_J1->SetTitle("");
  h0_sys_J1->Draw("b");



  la->SetTextSize(0.035);

  la->DrawLatexNDC(0.535,0.8,"80 GeV < #font[52]{p}_{T}^{jet} < 100 GeV");
  
  TH1D *h1_sys_J1 = new TH1D("h1_sys_J1","h1_sys_J1",N_sys,0,1.0*N_sys);
  h1_sys_J1->SetFillColor(kRed-4);
  h1_sys_J1->SetBarWidth(0.3);
  h1_sys_J1->SetBarOffset(0.35);
  h1_sys_J1->SetStats(0);
  h1_sys_J1->SetMinimum(0.0);
  h1_sys_J1->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J1->SetBinContent(i,sys_PbPb_mu12_C2_J1_array[i-1]);
    h1_sys_J1->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J1->SetBarWidth(new_bar_width);
  // h1_sys_J1->SetBarOffset(new_bar_offset);
  h1_sys_J1->Draw("b same");

  TH1D *h2_sys_J1 = new TH1D("h2_sys_J1","h2_sys_J1",N_sys,0,1.0*N_sys);
  h2_sys_J1->SetFillColor(kBlue-4);
  h2_sys_J1->SetBarWidth(0.3);
  h2_sys_J1->SetBarOffset(0.65);
  h2_sys_J1->SetStats(0);
  h2_sys_J1->SetMinimum(0.0);
  h2_sys_J1->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J1->SetBinContent(i,sys_PbPb_mu12_C1_J1_array[i-1]);
    h2_sys_J1->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J1->SetBarWidth(new_bar_width);
  // h2_sys_J1->SetBarOffset(new_bar_offset);
  h2_sys_J1->Draw("b same");

  TLegend *leg = new TLegend(0.25,0.7,0.4,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(h0_sys_J1,"pp","f");
  leg->AddEntry(h1_sys_J1,"PbPb 30-90%","f");
  leg->AddEntry(h2_sys_J1,"PbPb 0-30%","f");
  leg->Draw();

  


  TCanvas *canv_J2 = new TCanvas("canv_J2","canv_J2",800,800);
  canv_J2->cd();
  TPad *pad_J2 = new TPad("pad_J2","pad_J2",0,0,1,1);
  pad_J2->SetLeftMargin(0.2);
  pad_J2->SetBottomMargin(0.2);
  pad_J2->Draw();
  pad_J2->cd();

  TH1D *h0_sys_J2 = new TH1D("h0_sys_J2","h0_sys_J2",N_sys,0,1.0*N_sys);
  h0_sys_J2->SetFillColor(kGreen+2);
  h0_sys_J2->SetBarWidth(0.3);
  h0_sys_J2->SetBarOffset(0.05);
  h0_sys_J2->SetStats(0);
  h0_sys_J2->SetMinimum(0.0);
  h0_sys_J2->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J2->SetBinContent(i,sys_pp_mu12_J2_array[i-1]);
    h0_sys_J2->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }


  h0_sys_J2->GetXaxis()->SetTitleSize(0.06);
  // h0_sys_J2->SetBarWidth(new_bar_width);
  // h0_sys_J2->SetBarOffset(new_bar_offset);
  h0_sys_J2->SetTitle("");
  h0_sys_J2->Draw("b");



  la->SetTextSize(0.035);

  la->DrawLatexNDC(0.535,0.8,"100 GeV < #font[52]{p}_{T}^{jet} < 120 GeV");
  
  TH1D *h1_sys_J2 = new TH1D("h1_sys_J2","h1_sys_J2",N_sys,0,1.0*N_sys);
  h1_sys_J2->SetFillColor(kRed-4);
  h1_sys_J2->SetBarWidth(0.3);
  h1_sys_J2->SetBarOffset(0.35);
  h1_sys_J2->SetStats(0);
  h1_sys_J2->SetMinimum(0.0);
  h1_sys_J2->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J2->SetBinContent(i,sys_PbPb_mu12_C2_J2_array[i-1]);
    h1_sys_J2->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J2->SetBarWidth(new_bar_width);
  // h1_sys_J2->SetBarOffset(new_bar_offset);
  h1_sys_J2->Draw("b same");

  TH1D *h2_sys_J2 = new TH1D("h2_sys_J2","h2_sys_J2",N_sys,0,1.0*N_sys);
  h2_sys_J2->SetFillColor(kBlue-4);
  h2_sys_J2->SetBarWidth(0.3);
  h2_sys_J2->SetBarOffset(0.65);
  h2_sys_J2->SetStats(0);
  h2_sys_J2->SetMinimum(0.0);
  h2_sys_J2->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J2->SetBinContent(i,sys_PbPb_mu12_C1_J2_array[i-1]);
    h2_sys_J2->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J2->SetBarWidth(new_bar_width);
  // h2_sys_J2->SetBarOffset(new_bar_offset);
  h2_sys_J2->Draw("b same");
  leg->Draw();


  // ------------------------------------------------------------------------------------------------------

  TCanvas *canv_J3 = new TCanvas("canv_J3","canv_J3",800,800);
  canv_J3->cd();
  TPad *pad_J3 = new TPad("pad_J3","pad_J3",0,0,1,1);
  pad_J3->SetLeftMargin(0.2);
  pad_J3->SetBottomMargin(0.2);
  pad_J3->Draw();
  pad_J3->cd();

  TH1D *h0_sys_J3 = new TH1D("h0_sys_J3","h0_sys_J3",N_sys,0,1.0*N_sys);
  h0_sys_J3->SetFillColor(kGreen+2);
  h0_sys_J3->SetBarWidth(0.3);
  h0_sys_J3->SetBarOffset(0.05);
  h0_sys_J3->SetStats(0);
  h0_sys_J3->SetMinimum(0.0);
  h0_sys_J3->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J3->SetBinContent(i,sys_pp_mu12_J3_array[i-1]);
    h0_sys_J3->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h0_sys_J3->GetXaxis()->SetTitleSize(0.04);
  h0_sys_J3->SetTitle("");
  // h0_sys_J3->SetBarWidth(new_bar_width);
  // h0_sys_J3->SetBarOffset(new_bar_offset);
  h0_sys_J3->Draw("b");


  
  la->DrawLatexNDC(0.535,0.8,"80 GeV < #font[52]{p}_{T}^{jet} < 120 GeV");
  
  TH1D *h1_sys_J3 = new TH1D("h1_sys_J3","h1_sys_J3",N_sys,0,1.0*N_sys);
  h1_sys_J3->SetFillColor(kRed-4);
  h1_sys_J3->SetBarWidth(0.3);
  h1_sys_J3->SetBarOffset(0.35);
  h1_sys_J3->SetStats(0);
  h1_sys_J3->SetMinimum(0.0);
  h1_sys_J3->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J3->SetBinContent(i,sys_PbPb_mu12_C2_J3_array[i-1]);
    h1_sys_J3->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J3->SetBarWidth(new_bar_width);
  // h1_sys_J3->SetBarOffset(new_bar_offset);
  h1_sys_J3->Draw("b same");

  TH1D *h2_sys_J3 = new TH1D("h2_sys_J3","h2_sys_J3",N_sys,0,1.0*N_sys);
  h2_sys_J3->SetFillColor(kBlue-4);
  h2_sys_J3->SetBarWidth(0.3);
  h2_sys_J3->SetBarOffset(0.65);
  h2_sys_J3->SetStats(0);
  h2_sys_J3->SetMinimum(0.0);
  h2_sys_J3->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J3->SetBinContent(i,sys_PbPb_mu12_C1_J3_array[i-1]);
    h2_sys_J3->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J3->SetBarWidth(new_bar_width);
  // h2_sys_J3->SetBarOffset(new_bar_offset);
  h2_sys_J3->Draw("b same");
  leg->Draw();

  // ------------------------------------------------------------------------------------------------------

  TCanvas *canv_J4 = new TCanvas("canv_J4","canv_J4",800,800);
  canv_J4->cd();
  TPad *pad_J4 = new TPad("pad_J4","pad_J4",0,0,1,1);
  pad_J4->SetLeftMargin(0.2);
  pad_J4->SetBottomMargin(0.2);
  pad_J4->Draw();
  pad_J4->cd();

  TH1D *h0_sys_J4 = new TH1D("h0_sys_J4","h0_sys_J4",N_sys,0,1.0*N_sys);
  h0_sys_J4->SetFillColor(kGreen+2);
  h0_sys_J4->SetBarWidth(0.3);
  h0_sys_J4->SetBarOffset(0.05);
  h0_sys_J4->SetStats(0);
  h0_sys_J4->SetMinimum(0.0);
  h0_sys_J4->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J4->SetBinContent(i,sys_pp_mu12_J4_array[i-1]);
    h0_sys_J4->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h0_sys_J4->GetXaxis()->SetTitleSize(0.04);
  h0_sys_J4->SetTitle("");
  // h0_sys_J4->SetBarWidth(new_bar_width);
  // h0_sys_J4->SetBarOffset(new_bar_offset);
  h0_sys_J4->Draw("b");

  la->DrawLatexNDC(0.535,0.8,"120 GeV < #font[52]{p}_{T}^{jet} < 150 GeV");
  
  TH1D *h1_sys_J4 = new TH1D("h1_sys_J4","h1_sys_J4",N_sys,0,1.0*N_sys);
  h1_sys_J4->SetFillColor(kRed-4);
  h1_sys_J4->SetBarWidth(0.3);
  h1_sys_J4->SetBarOffset(0.35);
  h1_sys_J4->SetStats(0);
  h1_sys_J4->SetMinimum(0.0);
  h1_sys_J4->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J4->SetBinContent(i,sys_PbPb_mu12_C2_J4_array[i-1]);
    h1_sys_J4->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J4->SetBarWidth(new_bar_width);
  // h1_sys_J4->SetBarOffset(new_bar_offset);
  h1_sys_J4->Draw("b same");

  TH1D *h2_sys_J4 = new TH1D("h2_sys_J4","h2_sys_J4",N_sys,0,1.0*N_sys);
  h2_sys_J4->SetFillColor(kBlue-4);
  h2_sys_J4->SetBarWidth(0.3);
  h2_sys_J4->SetBarOffset(0.65);
  h2_sys_J4->SetStats(0);
  h2_sys_J4->SetMinimum(0.0);
  h2_sys_J4->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J4->SetBinContent(i,sys_PbPb_mu12_C1_J4_array[i-1]);
    h2_sys_J4->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J4->SetBarWidth(new_bar_width);
  // h2_sys_J4->SetBarOffset(new_bar_offset);
  h2_sys_J4->Draw("b same");
  leg->Draw();


  // ------------------------------------------------------------------------------------------------------

  TCanvas *canv_J5 = new TCanvas("canv_J5","canv_J5",800,800);
  canv_J5->cd();
  TPad *pad_J5 = new TPad("pad_J5","pad_J5",0,0,1,1);
  pad_J5->SetLeftMargin(0.2);
  pad_J5->SetBottomMargin(0.2);
  pad_J5->Draw();
  pad_J5->cd();

  TH1D *h0_sys_J5 = new TH1D("h0_sys_J5","h0_sys_J5",N_sys,0,1.0*N_sys);
  h0_sys_J5->SetFillColor(kGreen+2);
  h0_sys_J5->SetBarWidth(0.3);
  h0_sys_J5->SetBarOffset(0.05);
  h0_sys_J5->SetStats(0);
  h0_sys_J5->SetMinimum(0.0);
  h0_sys_J5->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J5->SetBinContent(i,sys_pp_mu12_J5_array[i-1]);
    h0_sys_J5->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h0_sys_J5->GetXaxis()->SetTitleSize(0.04);
  h0_sys_J5->SetTitle("");
  // h0_sys_J5->SetBarWidth(new_bar_width);
  // h0_sys_J5->SetBarOffset(new_bar_offset);
  h0_sys_J5->Draw("b");

  la->DrawLatexNDC(0.535,0.8,"200 GeV < #font[52]{p}_{T}^{jet} < 300 GeV");
  
  TH1D *h1_sys_J5 = new TH1D("h1_sys_J5","h1_sys_J5",N_sys,0,1.0*N_sys);
  h1_sys_J5->SetFillColor(kRed-4);
  h1_sys_J5->SetBarWidth(0.3);
  h1_sys_J5->SetBarOffset(0.35);
  h1_sys_J5->SetStats(0);
  h1_sys_J5->SetMinimum(0.0);
  h1_sys_J5->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J5->SetBinContent(i,sys_PbPb_mu12_C2_J5_array[i-1]);
    h1_sys_J5->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J5->SetBarWidth(new_bar_width);
  // h1_sys_J5->SetBarOffset(new_bar_offset);
  h1_sys_J5->Draw("b same");

  TH1D *h2_sys_J5 = new TH1D("h2_sys_J5","h2_sys_J5",N_sys,0,1.0*N_sys);
  h2_sys_J5->SetFillColor(kBlue-4);
  h2_sys_J5->SetBarWidth(0.3);
  h2_sys_J5->SetBarOffset(0.65);
  h2_sys_J5->SetStats(0);
  h2_sys_J5->SetMinimum(0.0);
  h2_sys_J5->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J5->SetBinContent(i,sys_PbPb_mu12_C1_J5_array[i-1]);
    h2_sys_J5->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J5->SetBarWidth(new_bar_width);
  // h2_sys_J5->SetBarOffset(new_bar_offset);
  h2_sys_J5->Draw("b same");
  leg->Draw();

  // ------------------------------------------------------------------------------------------------------

  TCanvas *canv_J6 = new TCanvas("canv_J6","canv_J6",800,800);
  canv_J6->cd();
  TPad *pad_J6 = new TPad("pad_J6","pad_J6",0,0,1,1);
  pad_J6->SetLeftMargin(0.2);
  pad_J6->SetBottomMargin(0.2);
  pad_J6->Draw();
  pad_J6->cd();

  TH1D *h0_sys_J6 = new TH1D("h0_sys_J6","h0_sys_J6",N_sys,0,1.0*N_sys);
  h0_sys_J6->SetFillColor(kGreen+2);
  h0_sys_J6->SetBarWidth(0.3);
  h0_sys_J6->SetBarOffset(0.05);
  h0_sys_J6->SetStats(0);
  h0_sys_J6->SetMinimum(0.0);
  h0_sys_J6->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J6->SetBinContent(i,sys_pp_mu12_J6_array[i-1]);
    h0_sys_J6->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h0_sys_J6->GetXaxis()->SetTitleSize(0.04);
  h0_sys_J6->SetTitle("");
  // h0_sys_J6->SetBarWidth(new_bar_width);
  // h0_sys_J6->SetBarOffset(new_bar_offset);
  h0_sys_J6->Draw("b");

  la->DrawLatexNDC(0.535,0.8,"300 GeV < #font[52]{p}_{T}^{jet} < 500 GeV");
  
  TH1D *h1_sys_J6 = new TH1D("h1_sys_J6","h1_sys_J6",N_sys,0,1.0*N_sys);
  h1_sys_J6->SetFillColor(kRed-4);
  h1_sys_J6->SetBarWidth(0.3);
  h1_sys_J6->SetBarOffset(0.35);
  h1_sys_J6->SetStats(0);
  h1_sys_J6->SetMinimum(0.0);
  h1_sys_J6->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J6->SetBinContent(i,sys_PbPb_mu12_C2_J6_array[i-1]);
    h1_sys_J6->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J6->SetBarWidth(new_bar_width);
  // h1_sys_J6->SetBarOffset(new_bar_offset);
  h1_sys_J6->Draw("b same");

  TH1D *h2_sys_J6 = new TH1D("h2_sys_J6","h2_sys_J6",N_sys,0,1.0*N_sys);
  h2_sys_J6->SetFillColor(kBlue-4);
  h2_sys_J6->SetBarWidth(0.3);
  h2_sys_J6->SetBarOffset(0.65);
  h2_sys_J6->SetStats(0);
  h2_sys_J6->SetMinimum(0.0);
  h2_sys_J6->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J6->SetBinContent(i,sys_PbPb_mu12_C1_J6_array[i-1]);
    h2_sys_J6->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J6->SetBarWidth(new_bar_width);
  // h2_sys_J6->SetBarOffset(new_bar_offset);
  h2_sys_J6->Draw("b same");
  leg->Draw();

  




  canv_J1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu12_J1.pdf");
  canv_J2->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu12_J2.pdf");
  canv_J3->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu12_J3.pdf");
  canv_J4->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu12_J4.pdf");
  canv_J5->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu12_J4.pdf");
  canv_J6->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu12_J4.pdf");    







  /// now create a plot by jetPt
  
  

  // c-fraction-variation
  double input_pp_cFrac_J1 = 0;
  double input_pp_cFrac_J2 = 0;
  double input_pp_cFrac_J3 = 0;
  double input_pp_cFrac_J4 = 0;
  double input_pp_cFrac_J5 = 0;
  double input_pp_cFrac_J6 = 0;

  double input_C2_cFrac_J1 = 0;
  double input_C2_cFrac_J2 = 0;
  double input_C2_cFrac_J3 = 0;
  double input_C2_cFrac_J4 = 0;
  double input_C2_cFrac_J5 = 0;
  double input_C2_cFrac_J6 = 0;

  double input_C1_cFrac_J1 = 0;
  double input_C1_cFrac_J2 = 0;
  double input_C1_cFrac_J3 = 0;
  double input_C1_cFrac_J4 = 0;
  double input_C1_cFrac_J5 = 0;
  double input_C1_cFrac_J6 = 0;

  // fit-lower-bound
  double input_pp_lowerBound_J1 = 0;
  double input_pp_lowerBound_J2 = 0;
  double input_pp_lowerBound_J3 = 0;
  double input_pp_lowerBound_J4 = 0;
  double input_pp_lowerBound_J5 = 0;
  double input_pp_lowerBound_J6 = 0;

  double input_C2_lowerBound_J1 = 0;
  double input_C2_lowerBound_J2 = 0;
  double input_C2_lowerBound_J3 = 0;
  double input_C2_lowerBound_J4 = 0;
  double input_C2_lowerBound_J5 = 0;
  double input_C2_lowerBound_J6 = 0;

  double input_C1_lowerBound_J1 = 0;
  double input_C1_lowerBound_J2 = 0;
  double input_C1_lowerBound_J3 = 0;
  double input_C1_lowerBound_J4 = 0;
  double input_C1_lowerBound_J5 = 0;
  double input_C1_lowerBound_J6 = 0;

  // b-template-enhancement
  double input_pp_bEnhance_J1 = 0;
  double input_pp_bEnhance_J2 = 0;
  double input_pp_bEnhance_J3 = 0;
  double input_pp_bEnhance_J4 = 0;
  double input_pp_bEnhance_J5 = 0;
  double input_pp_bEnhance_J6 = 0;

  double input_C2_bEnhance_J1 = 0;
  double input_C2_bEnhance_J2 = 0;
  double input_C2_bEnhance_J3 = 0;
  double input_C2_bEnhance_J4 = 0;
  double input_C2_bEnhance_J5 = 0;
  double input_C2_bEnhance_J6 = 0;

  double input_C1_bEnhance_J1 = 0;
  double input_C1_bEnhance_J2 = 0;
  double input_C1_bEnhance_J3 = 0;
  double input_C1_bEnhance_J4 = 0;
  double input_C1_bEnhance_J5 = 0;
  double input_C1_bEnhance_J6 = 0;

  // c-template-enhancement
  double input_pp_cEnhance_J1 = 0;
  double input_pp_cEnhance_J2 = 0;
  double input_pp_cEnhance_J3 = 0;
  double input_pp_cEnhance_J4 = 0;
  double input_pp_cEnhance_J5 = 0;
  double input_pp_cEnhance_J6 = 0;

  double input_C2_cEnhance_J1 = 0;
  double input_C2_cEnhance_J2 = 0;
  double input_C2_cEnhance_J3 = 0;
  double input_C2_cEnhance_J4 = 0;
  double input_C2_cEnhance_J5 = 0;
  double input_C2_cEnhance_J6 = 0;

  double input_C1_cEnhance_J1 = 0;
  double input_C1_cEnhance_J2 = 0;  
  double input_C1_cEnhance_J3 = 0;
  double input_C1_cEnhance_J4 = 0;
  double input_C1_cEnhance_J5 = 0;
  double input_C1_cEnhance_J6 = 0;

  // JER-smear
  double input_pp_JERsmear_J1 = 0;
  double input_pp_JERsmear_J2 = 0;
  double input_pp_JERsmear_J3 = 0;
  double input_pp_JERsmear_J4 = 0;
  double input_pp_JERsmear_J5 = 0;
  double input_pp_JERsmear_J6 = 0;

  double input_C2_JERsmear_J1 = 0;
  double input_C2_JERsmear_J2 = 0;
  double input_C2_JERsmear_J3 = 0;
  double input_C2_JERsmear_J4 = 0;
  double input_C2_JERsmear_J5 = 0;
  double input_C2_JERsmear_J6 = 0;

  double input_C1_JERsmear_J1 = 0;
  double input_C1_JERsmear_J2 = 0;  
  double input_C1_JERsmear_J3 = 0;
  double input_C1_JERsmear_J4 = 0;
  double input_C1_JERsmear_J5 = 0;
  double input_C1_JERsmear_J6 = 0;

  // gluon-splitting b fraction
  double input_pp_bGS_J1 = 0;
  double input_pp_bGS_J2 = 0;
  double input_pp_bGS_J3 = 0;
  double input_pp_bGS_J4 = 0;
  double input_pp_bGS_J5 = 0;
  double input_pp_bGS_J6 = 0;

  double input_C2_bGS_J1 = 0;
  double input_C2_bGS_J2 = 0;  
  double input_C2_bGS_J3 = 0;
  double input_C2_bGS_J4 = 0;
  double input_C2_bGS_J5 = 0;
  double input_C2_bGS_J6 = 0;

  double input_C1_bGS_J1 = 0;
  double input_C1_bGS_J2 = 0;
  double input_C1_bGS_J3 = 0;
  double input_C1_bGS_J4 = 0;
  double input_C1_bGS_J5 = 0;
  double input_C1_bGS_J6 = 0;

  // JEU shift-up
  double input_pp_JEUShiftUp_J1 = 0;
  double input_pp_JEUShiftUp_J2 = 0;
  double input_pp_JEUShiftUp_J3 = 0;
  double input_pp_JEUShiftUp_J4 = 0;
  double input_pp_JEUShiftUp_J5 = 0;
  double input_pp_JEUShiftUp_J6 = 0;

  double input_C2_JEUShiftUp_J1 = 0;
  double input_C2_JEUShiftUp_J2 = 0;
  double input_C2_JEUShiftUp_J3 = 0;
  double input_C2_JEUShiftUp_J4 = 0;
  double input_C2_JEUShiftUp_J5 = 0;
  double input_C2_JEUShiftUp_J6 = 0;

  double input_C1_JEUShiftUp_J1 = 0;
  double input_C1_JEUShiftUp_J2 = 0;
  double input_C1_JEUShiftUp_J3 = 0;
  double input_C1_JEUShiftUp_J4 = 0;
  double input_C1_JEUShiftUp_J5 = 0;
  double input_C1_JEUShiftUp_J6 = 0;

  // JEU shift-down
  double input_pp_JEUShiftDown_J1 = 0;
  double input_pp_JEUShiftDown_J2 = 0;
  double input_pp_JEUShiftDown_J3 = 0;
  double input_pp_JEUShiftDown_J4 = 0;
  double input_pp_JEUShiftDown_J5 = 0;
  double input_pp_JEUShiftDown_J6 = 0;

  double input_C2_JEUShiftDown_J1 = 0;
  double input_C2_JEUShiftDown_J2 = 0;
  double input_C2_JEUShiftDown_J3 = 0;
  double input_C2_JEUShiftDown_J4 = 0;
  double input_C2_JEUShiftDown_J5 = 0;
  double input_C2_JEUShiftDown_J6 = 0;

  double input_C1_JEUShiftDown_J1 = 0;
  double input_C1_JEUShiftDown_J2 = 0;
  double input_C1_JEUShiftDown_J3 = 0;
  double input_C1_JEUShiftDown_J4 = 0;
  double input_C1_JEUShiftDown_J5 = 0;
  double input_C1_JEUShiftDown_J6 = 0;

  // residual non-closure
  double input_pp_residual_J1 = 0;
  double input_pp_residual_J2 = 0;
  double input_pp_residual_J3 = 0;
  double input_pp_residual_J4 = 0;
  double input_pp_residual_J5 = 0;
  double input_pp_residual_J6 = 0;

  double input_C2_residual_J1 = 0;
  double input_C2_residual_J2 = 0;
  double input_C2_residual_J3 = 0;
  double input_C2_residual_J4 = 0;
  double input_C2_residual_J5 = 0;
  double input_C2_residual_J6 = 0;

  double input_C1_residual_J1 = 0;
  double input_C1_residual_J2 = 0;
  double input_C1_residual_J3 = 0;
  double input_C1_residual_J4 = 0;
  double input_C1_residual_J5 = 0;
  double input_C1_residual_J6 = 0;


  
  

  
  // total
  double input_pp_total_J1 = 0;
  double input_pp_total_J2 = 0;
  double input_pp_total_J3 = 0;
  double input_pp_total_J4 = 0;
  double input_pp_total_J5 = 0;
  double input_pp_total_J6 = 0;

  double input_C2_total_J1 = 0;
  double input_C2_total_J2 = 0;
  double input_C2_total_J3 = 0;
  double input_C2_total_J4 = 0;
  double input_C2_total_J5 = 0;
  double input_C2_total_J6 = 0;

  double input_C1_total_J1 = 0;
  double input_C1_total_J2 = 0;
  double input_C1_total_J3 = 0;
  double input_C1_total_J4 = 0;
  double input_C1_total_J5 = 0;
  double input_C1_total_J6 = 0;



  // total uncertainty
  input_pp_cFrac_J1 = sys_cFraction_pp_mu12_J1;
  input_pp_cFrac_J2 = sys_cFraction_pp_mu12_J2;
  input_pp_cFrac_J3 = sys_cFraction_pp_mu12_J3;
  input_pp_cFrac_J4 = sys_cFraction_pp_mu12_J4;
  input_pp_cFrac_J5 = sys_cFraction_pp_mu12_J5;
  input_pp_cFrac_J6 = sys_cFraction_pp_mu12_J6;

  input_C2_cFrac_J1 = sys_cFraction_PbPb_mu12_C2_J1;
  input_C2_cFrac_J2 = sys_cFraction_PbPb_mu12_C2_J2;
  input_C2_cFrac_J3 = sys_cFraction_PbPb_mu12_C2_J3;
  input_C2_cFrac_J4 = sys_cFraction_PbPb_mu12_C2_J4;
  input_C2_cFrac_J5 = sys_cFraction_PbPb_mu12_C2_J5;
  input_C2_cFrac_J6 = sys_cFraction_PbPb_mu12_C2_J6;  

  input_C1_cFrac_J1 = sys_cFraction_PbPb_mu12_C1_J1;
  input_C1_cFrac_J2 = sys_cFraction_PbPb_mu12_C1_J2;
  input_C1_cFrac_J3 = sys_cFraction_PbPb_mu12_C1_J3;
  input_C1_cFrac_J4 = sys_cFraction_PbPb_mu12_C1_J4;
  input_C1_cFrac_J5 = sys_cFraction_PbPb_mu12_C1_J5;
  input_C1_cFrac_J6 = sys_cFraction_PbPb_mu12_C1_J6;

  input_pp_lowerBound_J1 = sys_lowerBound_pp_mu12_J1;
  input_pp_lowerBound_J2 = sys_lowerBound_pp_mu12_J2;
  input_pp_lowerBound_J3 = sys_lowerBound_pp_mu12_J3;
  input_pp_lowerBound_J4 = sys_lowerBound_pp_mu12_J4;
  input_pp_lowerBound_J5 = sys_lowerBound_pp_mu12_J5;
  input_pp_lowerBound_J6 = sys_lowerBound_pp_mu12_J6;

  input_C2_lowerBound_J1 = sys_lowerBound_PbPb_mu12_C2_J1;
  input_C2_lowerBound_J2 = sys_lowerBound_PbPb_mu12_C2_J2;
  input_C2_lowerBound_J3 = sys_lowerBound_PbPb_mu12_C2_J3;
  input_C2_lowerBound_J4 = sys_lowerBound_PbPb_mu12_C2_J4;
  input_C2_lowerBound_J5 = sys_lowerBound_PbPb_mu12_C2_J5;
  input_C2_lowerBound_J6 = sys_lowerBound_PbPb_mu12_C2_J6;

  input_C1_lowerBound_J1 = sys_lowerBound_PbPb_mu12_C1_J1;
  input_C1_lowerBound_J2 = sys_lowerBound_PbPb_mu12_C1_J2;
  input_C1_lowerBound_J3 = sys_lowerBound_PbPb_mu12_C1_J3;
  input_C1_lowerBound_J4 = sys_lowerBound_PbPb_mu12_C1_J4;
  input_C1_lowerBound_J5 = sys_lowerBound_PbPb_mu12_C1_J5;
  input_C1_lowerBound_J6 = sys_lowerBound_PbPb_mu12_C1_J6;  

  input_pp_bEnhance_J1 = sys_bEnhance_pp_mu12_J1;
  input_pp_bEnhance_J2 = sys_bEnhance_pp_mu12_J2;  
  input_pp_bEnhance_J3 = sys_bEnhance_pp_mu12_J3;
  input_pp_bEnhance_J4 = sys_bEnhance_pp_mu12_J4;
  input_pp_bEnhance_J5 = sys_bEnhance_pp_mu12_J5;
  input_pp_bEnhance_J6 = sys_bEnhance_pp_mu12_J6;  

  input_C2_bEnhance_J1 = sys_bEnhance_PbPb_mu12_C2_J1;
  input_C2_bEnhance_J2 = sys_bEnhance_PbPb_mu12_C2_J2;
  input_C2_bEnhance_J3 = sys_bEnhance_PbPb_mu12_C2_J3;
  input_C2_bEnhance_J4 = sys_bEnhance_PbPb_mu12_C2_J4;
  input_C2_bEnhance_J5 = sys_bEnhance_PbPb_mu12_C2_J5;
  input_C2_bEnhance_J6 = sys_bEnhance_PbPb_mu12_C2_J6;  

  input_C1_bEnhance_J1 = sys_bEnhance_PbPb_mu12_C1_J1;
  input_C1_bEnhance_J2 = sys_bEnhance_PbPb_mu12_C1_J2;
  input_C1_bEnhance_J3 = sys_bEnhance_PbPb_mu12_C1_J3;
  input_C1_bEnhance_J4 = sys_bEnhance_PbPb_mu12_C1_J4;
  input_C1_bEnhance_J5 = sys_bEnhance_PbPb_mu12_C1_J5;
  input_C1_bEnhance_J6 = sys_bEnhance_PbPb_mu12_C1_J6;

  input_pp_cEnhance_J1 = sys_cEnhance_pp_mu12_J1;
  input_pp_cEnhance_J2 = sys_cEnhance_pp_mu12_J2;
  input_pp_cEnhance_J3 = sys_cEnhance_pp_mu12_J3;
  input_pp_cEnhance_J4 = sys_cEnhance_pp_mu12_J4;
  input_pp_cEnhance_J5 = sys_cEnhance_pp_mu12_J5;
  input_pp_cEnhance_J6 = sys_cEnhance_pp_mu12_J6;

  input_C2_cEnhance_J1 = sys_cEnhance_PbPb_mu12_C2_J1;
  input_C2_cEnhance_J2 = sys_cEnhance_PbPb_mu12_C2_J2;
  input_C2_cEnhance_J3 = sys_cEnhance_PbPb_mu12_C2_J3;
  input_C2_cEnhance_J4 = sys_cEnhance_PbPb_mu12_C2_J4;
  input_C2_cEnhance_J5 = sys_cEnhance_PbPb_mu12_C2_J5;
  input_C2_cEnhance_J6 = sys_cEnhance_PbPb_mu12_C2_J6;

  input_C1_cEnhance_J1 = sys_cEnhance_PbPb_mu12_C1_J1;
  input_C1_cEnhance_J2 = sys_cEnhance_PbPb_mu12_C1_J2;
  input_C1_cEnhance_J3 = sys_cEnhance_PbPb_mu12_C1_J3;
  input_C1_cEnhance_J4 = sys_cEnhance_PbPb_mu12_C1_J4;
  input_C1_cEnhance_J5 = sys_cEnhance_PbPb_mu12_C1_J5;
  input_C1_cEnhance_J6 = sys_cEnhance_PbPb_mu12_C1_J6;

  input_pp_JERsmear_J1 = sys_JERsmear_pp_mu12_J1;
  input_pp_JERsmear_J2 = sys_JERsmear_pp_mu12_J2;
  input_pp_JERsmear_J3 = sys_JERsmear_pp_mu12_J3;
  input_pp_JERsmear_J4 = sys_JERsmear_pp_mu12_J4;
  input_pp_JERsmear_J5 = sys_JERsmear_pp_mu12_J5;
  input_pp_JERsmear_J6 = sys_JERsmear_pp_mu12_J6;

  input_C2_JERsmear_J1 = sys_JERsmear_PbPb_mu12_C2_J1;
  input_C2_JERsmear_J2 = sys_JERsmear_PbPb_mu12_C2_J2;
  input_C2_JERsmear_J3 = sys_JERsmear_PbPb_mu12_C2_J3;
  input_C2_JERsmear_J4 = sys_JERsmear_PbPb_mu12_C2_J4;
  input_C2_JERsmear_J5 = sys_JERsmear_PbPb_mu12_C2_J5;
  input_C2_JERsmear_J6 = sys_JERsmear_PbPb_mu12_C2_J6;

  input_C1_JERsmear_J1 = sys_JERsmear_PbPb_mu12_C1_J1;
  input_C1_JERsmear_J2 = sys_JERsmear_PbPb_mu12_C1_J2;
  input_C1_JERsmear_J3 = sys_JERsmear_PbPb_mu12_C1_J3;
  input_C1_JERsmear_J4 = sys_JERsmear_PbPb_mu12_C1_J4;
  input_C1_JERsmear_J5 = sys_JERsmear_PbPb_mu12_C1_J5;
  input_C1_JERsmear_J6 = sys_JERsmear_PbPb_mu12_C1_J6;
    
  input_pp_bGS_J1 = sys_bGS_pp_mu12_J1;
  input_pp_bGS_J2 = sys_bGS_pp_mu12_J2;
  input_pp_bGS_J3 = sys_bGS_pp_mu12_J3;
  input_pp_bGS_J4 = sys_bGS_pp_mu12_J4;
  input_pp_bGS_J5 = sys_bGS_pp_mu12_J5;
  input_pp_bGS_J6 = sys_bGS_pp_mu12_J6;

  input_C2_bGS_J1 = sys_bGS_PbPb_mu12_C2_J1;
  input_C2_bGS_J2 = sys_bGS_PbPb_mu12_C2_J2;
  input_C2_bGS_J3 = sys_bGS_PbPb_mu12_C2_J3;
  input_C2_bGS_J4 = sys_bGS_PbPb_mu12_C2_J4;
  input_C2_bGS_J5 = sys_bGS_PbPb_mu12_C2_J5;
  input_C2_bGS_J6 = sys_bGS_PbPb_mu12_C2_J6;

  input_C1_bGS_J1 = sys_bGS_PbPb_mu12_C1_J1;
  input_C1_bGS_J2 = sys_bGS_PbPb_mu12_C1_J2;
  input_C1_bGS_J3 = sys_bGS_PbPb_mu12_C1_J3;
  input_C1_bGS_J4 = sys_bGS_PbPb_mu12_C1_J4;
  input_C1_bGS_J5 = sys_bGS_PbPb_mu12_C1_J5;
  input_C1_bGS_J6 = sys_bGS_PbPb_mu12_C1_J6;

  input_pp_JEUShiftUp_J1 = sys_JEUShiftUp_pp_mu12_J1;
  input_pp_JEUShiftUp_J2 = sys_JEUShiftUp_pp_mu12_J2;
  input_pp_JEUShiftUp_J3 = sys_JEUShiftUp_pp_mu12_J3;
  input_pp_JEUShiftUp_J4 = sys_JEUShiftUp_pp_mu12_J4;
  input_pp_JEUShiftUp_J5 = sys_JEUShiftUp_pp_mu12_J5;
  input_pp_JEUShiftUp_J6 = sys_JEUShiftUp_pp_mu12_J6;

  input_C2_JEUShiftUp_J1 = sys_JEUShiftUp_PbPb_mu12_C2_J1;
  input_C2_JEUShiftUp_J2 = sys_JEUShiftUp_PbPb_mu12_C2_J2;
  input_C2_JEUShiftUp_J3 = sys_JEUShiftUp_PbPb_mu12_C2_J3;
  input_C2_JEUShiftUp_J4 = sys_JEUShiftUp_PbPb_mu12_C2_J4;
  input_C2_JEUShiftUp_J5 = sys_JEUShiftUp_PbPb_mu12_C2_J5;
  input_C2_JEUShiftUp_J6 = sys_JEUShiftUp_PbPb_mu12_C2_J6;

  input_C1_JEUShiftUp_J1 = sys_JEUShiftUp_PbPb_mu12_C1_J1;
  input_C1_JEUShiftUp_J2 = sys_JEUShiftUp_PbPb_mu12_C1_J2;
  input_C1_JEUShiftUp_J3 = sys_JEUShiftUp_PbPb_mu12_C1_J3;
  input_C1_JEUShiftUp_J4 = sys_JEUShiftUp_PbPb_mu12_C1_J4;
  input_C1_JEUShiftUp_J5 = sys_JEUShiftUp_PbPb_mu12_C1_J5;
  input_C1_JEUShiftUp_J6 = sys_JEUShiftUp_PbPb_mu12_C1_J6;

  input_pp_JEUShiftDown_J1 = sys_JEUShiftDown_pp_mu12_J1;
  input_pp_JEUShiftDown_J2 = sys_JEUShiftDown_pp_mu12_J2;
  input_pp_JEUShiftDown_J3 = sys_JEUShiftDown_pp_mu12_J3;
  input_pp_JEUShiftDown_J4 = sys_JEUShiftDown_pp_mu12_J4;
  input_pp_JEUShiftDown_J5 = sys_JEUShiftDown_pp_mu12_J5;
  input_pp_JEUShiftDown_J6 = sys_JEUShiftDown_pp_mu12_J6;

  input_C2_JEUShiftDown_J1 = sys_JEUShiftDown_PbPb_mu12_C2_J1;
  input_C2_JEUShiftDown_J2 = sys_JEUShiftDown_PbPb_mu12_C2_J2;
  input_C2_JEUShiftDown_J3 = sys_JEUShiftDown_PbPb_mu12_C2_J3;
  input_C2_JEUShiftDown_J4 = sys_JEUShiftDown_PbPb_mu12_C2_J4;
  input_C2_JEUShiftDown_J5 = sys_JEUShiftDown_PbPb_mu12_C2_J5;
  input_C2_JEUShiftDown_J6 = sys_JEUShiftDown_PbPb_mu12_C2_J6;

  input_C1_JEUShiftDown_J1 = sys_JEUShiftDown_PbPb_mu12_C1_J1;
  input_C1_JEUShiftDown_J2 = sys_JEUShiftDown_PbPb_mu12_C1_J2;
  input_C1_JEUShiftDown_J3 = sys_JEUShiftDown_PbPb_mu12_C1_J3;
  input_C1_JEUShiftDown_J4 = sys_JEUShiftDown_PbPb_mu12_C1_J4;
  input_C1_JEUShiftDown_J5 = sys_JEUShiftDown_PbPb_mu12_C1_J5;
  input_C1_JEUShiftDown_J6 = sys_JEUShiftDown_PbPb_mu12_C1_J6;

  input_pp_residual_J1 = sys_residual_pp_mu12_J1;
  input_pp_residual_J2 = sys_residual_pp_mu12_J2;
  input_pp_residual_J3 = sys_residual_pp_mu12_J3;
  input_pp_residual_J4 = sys_residual_pp_mu12_J4;
  input_pp_residual_J5 = sys_residual_pp_mu12_J5;
  input_pp_residual_J6 = sys_residual_pp_mu12_J6;

  input_C2_residual_J1 = sys_residual_PbPb_mu12_C2_J1;
  input_C2_residual_J2 = sys_residual_PbPb_mu12_C2_J2;
  input_C2_residual_J3 = sys_residual_PbPb_mu12_C2_J3;
  input_C2_residual_J4 = sys_residual_PbPb_mu12_C2_J4;
  input_C2_residual_J5 = sys_residual_PbPb_mu12_C2_J5;
  input_C2_residual_J6 = sys_residual_PbPb_mu12_C2_J6;

  input_C1_residual_J1 = sys_residual_PbPb_mu12_C1_J1;
  input_C1_residual_J2 = sys_residual_PbPb_mu12_C1_J2;
  input_C1_residual_J3 = sys_residual_PbPb_mu12_C1_J3;
  input_C1_residual_J4 = sys_residual_PbPb_mu12_C1_J4;
  input_C1_residual_J5 = sys_residual_PbPb_mu12_C1_J5;
  input_C1_residual_J6 = sys_residual_PbPb_mu12_C1_J6;

  input_pp_total_J1 = sys_total_pp_mu12_J1;
  input_pp_total_J2 = sys_total_pp_mu12_J2;
  input_pp_total_J3 = sys_total_pp_mu12_J3;
  input_pp_total_J4 = sys_total_pp_mu12_J4;
  input_pp_total_J5 = sys_total_pp_mu12_J5;
  input_pp_total_J6 = sys_total_pp_mu12_J6;

  input_C2_total_J1 = sys_total_PbPb_mu12_C2_J1;
  input_C2_total_J2 = sys_total_PbPb_mu12_C2_J2;
  input_C2_total_J3 = sys_total_PbPb_mu12_C2_J3;
  input_C2_total_J4 = sys_total_PbPb_mu12_C2_J4;
  input_C2_total_J5 = sys_total_PbPb_mu12_C2_J5;
  input_C2_total_J6 = sys_total_PbPb_mu12_C2_J6;

  input_C1_total_J1 = sys_total_PbPb_mu12_C1_J1;
  input_C1_total_J2 = sys_total_PbPb_mu12_C1_J2;
  input_C1_total_J3 = sys_total_PbPb_mu12_C1_J3;
  input_C1_total_J4 = sys_total_PbPb_mu12_C1_J4;
  input_C1_total_J5 = sys_total_PbPb_mu12_C1_J5;
  input_C1_total_J6 = sys_total_PbPb_mu12_C1_J6;


  
  const int N_jetPtAxisEdges = 7;
  double jetPtAxisEdges[N_jetPtAxisEdges] = {80,100,120,150,200,300,500};

  int line_width = 3;
  double marker_size = 1.0;
  
  // --------- pp ------------------------------
  TH1D *h_pp_cFraction = new TH1D("h_pp_cFraction","h_pp_cFraction",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_lowerBound = new TH1D("h_pp_lowerBound","h_pp_lowerBound",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_bEnhance = new TH1D("h_pp_bEnhance","h_pp_bEnhance",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_cEnhance = new TH1D("h_pp_cEnhance","h_pp_cEnhance",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_JERsmear = new TH1D("h_pp_JERsmear","h_pp_JERsmear",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_bGS = new TH1D("h_pp_bGS","h_pp_bGS",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_JEUShiftUp = new TH1D("h_pp_JEUShiftUp","h_pp_JEUShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_JEUShiftDown = new TH1D("h_pp_JEUShiftDown","h_pp_JEUShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_residual = new TH1D("h_pp_residual","h_pp_residual",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_total = new TH1D("h_pp_total","h_pp_total",N_jetPtAxisEdges-1,jetPtAxisEdges);

  // set bin content
  h_pp_cFraction->SetBinContent(1,input_pp_cFrac_J1);
  h_pp_cFraction->SetBinContent(2,input_pp_cFrac_J2);
  h_pp_cFraction->SetBinContent(3,input_pp_cFrac_J3);
  h_pp_cFraction->SetBinContent(4,input_pp_cFrac_J4);
  h_pp_cFraction->SetBinContent(5,input_pp_cFrac_J5);
  h_pp_cFraction->SetBinContent(6,input_pp_cFrac_J6);    

  h_pp_lowerBound->SetBinContent(1,input_pp_lowerBound_J1);
  h_pp_lowerBound->SetBinContent(2,input_pp_lowerBound_J2);
  h_pp_lowerBound->SetBinContent(3,input_pp_lowerBound_J3);
  h_pp_lowerBound->SetBinContent(4,input_pp_lowerBound_J4);
  h_pp_lowerBound->SetBinContent(5,input_pp_lowerBound_J5);
  h_pp_lowerBound->SetBinContent(6,input_pp_lowerBound_J6);

  h_pp_bEnhance->SetBinContent(1,input_pp_bEnhance_J1);
  h_pp_bEnhance->SetBinContent(2,input_pp_bEnhance_J2);
  h_pp_bEnhance->SetBinContent(3,input_pp_bEnhance_J3);
  h_pp_bEnhance->SetBinContent(4,input_pp_bEnhance_J4);
  h_pp_bEnhance->SetBinContent(5,input_pp_bEnhance_J5);
  h_pp_bEnhance->SetBinContent(6,input_pp_bEnhance_J6);

  h_pp_cEnhance->SetBinContent(1,input_pp_cEnhance_J1);
  h_pp_cEnhance->SetBinContent(2,input_pp_cEnhance_J2);
  h_pp_cEnhance->SetBinContent(3,input_pp_cEnhance_J3);
  h_pp_cEnhance->SetBinContent(4,input_pp_cEnhance_J4);
  h_pp_cEnhance->SetBinContent(5,input_pp_cEnhance_J5);
  h_pp_cEnhance->SetBinContent(6,input_pp_cEnhance_J6);

  h_pp_JERsmear->SetBinContent(1,input_pp_JERsmear_J1);
  h_pp_JERsmear->SetBinContent(2,input_pp_JERsmear_J2);
  h_pp_JERsmear->SetBinContent(3,input_pp_JERsmear_J3);
  h_pp_JERsmear->SetBinContent(4,input_pp_JERsmear_J4);
  h_pp_JERsmear->SetBinContent(5,input_pp_JERsmear_J5);
  h_pp_JERsmear->SetBinContent(6,input_pp_JERsmear_J6);

  h_pp_bGS->SetBinContent(1,input_pp_bGS_J1);
  h_pp_bGS->SetBinContent(2,input_pp_bGS_J2);
  h_pp_bGS->SetBinContent(3,input_pp_bGS_J3);
  h_pp_bGS->SetBinContent(4,input_pp_bGS_J4);
  h_pp_bGS->SetBinContent(5,input_pp_bGS_J5);
  h_pp_bGS->SetBinContent(6,input_pp_bGS_J6);

  h_pp_JEUShiftUp->SetBinContent(1,input_pp_JEUShiftUp_J1);
  h_pp_JEUShiftUp->SetBinContent(2,input_pp_JEUShiftUp_J2);
  h_pp_JEUShiftUp->SetBinContent(3,input_pp_JEUShiftUp_J3);
  h_pp_JEUShiftUp->SetBinContent(4,input_pp_JEUShiftUp_J4);
  h_pp_JEUShiftUp->SetBinContent(5,input_pp_JEUShiftUp_J5);
  h_pp_JEUShiftUp->SetBinContent(6,input_pp_JEUShiftUp_J6);

  h_pp_JEUShiftDown->SetBinContent(1,input_pp_JEUShiftDown_J1);
  h_pp_JEUShiftDown->SetBinContent(2,input_pp_JEUShiftDown_J2);
  h_pp_JEUShiftDown->SetBinContent(3,input_pp_JEUShiftDown_J3);
  h_pp_JEUShiftDown->SetBinContent(4,input_pp_JEUShiftDown_J4);
  h_pp_JEUShiftDown->SetBinContent(5,input_pp_JEUShiftDown_J5);
  h_pp_JEUShiftDown->SetBinContent(6,input_pp_JEUShiftDown_J6);

  h_pp_residual->SetBinContent(1,input_pp_residual_J1);
  h_pp_residual->SetBinContent(2,input_pp_residual_J2);
  h_pp_residual->SetBinContent(3,input_pp_residual_J3);
  h_pp_residual->SetBinContent(4,input_pp_residual_J4);
  h_pp_residual->SetBinContent(5,input_pp_residual_J5);
  h_pp_residual->SetBinContent(6,input_pp_residual_J6);

  h_pp_total->SetBinContent(1,input_pp_total_J1);
  h_pp_total->SetBinContent(2,input_pp_total_J2);
  h_pp_total->SetBinContent(3,input_pp_total_J3);
  h_pp_total->SetBinContent(4,input_pp_total_J4);
  h_pp_total->SetBinContent(5,input_pp_total_J5);
  h_pp_total->SetBinContent(6,input_pp_total_J6);

  // set style
  h_pp_cFraction->SetMarkerColor(kBlue-4);
  h_pp_lowerBound->SetMarkerColor(kRed-4);
  h_pp_bEnhance->SetMarkerColor(kGreen+2);
  h_pp_cEnhance->SetMarkerColor(kMagenta);
  h_pp_JERsmear->SetMarkerColor(kOrange);
  h_pp_bGS->SetMarkerColor(kBlue-9);
  h_pp_JEUShiftUp->SetMarkerColor(kGreen-8);
  h_pp_JEUShiftDown->SetMarkerColor(kPink+9);
  h_pp_residual->SetMarkerColor(kMagenta+3);
  h_pp_total->SetMarkerColor(kBlack);

  h_pp_cFraction->SetLineColor(kBlue-4);
  h_pp_lowerBound->SetLineColor(kRed-4);
  h_pp_bEnhance->SetLineColor(kGreen+2);
  h_pp_cEnhance->SetLineColor(kMagenta);
  h_pp_JERsmear->SetLineColor(kOrange);
  h_pp_bGS->SetLineColor(kBlue-9);
  h_pp_JEUShiftUp->SetLineColor(kGreen-8);
  h_pp_JEUShiftDown->SetLineColor(kPink+9);
  h_pp_residual->SetLineColor(kMagenta+3);
  h_pp_total->SetLineColor(kBlack);

  h_pp_cFraction->SetMarkerStyle(25);
  h_pp_lowerBound->SetMarkerStyle(26);
  h_pp_bEnhance->SetMarkerStyle(27);
  h_pp_cEnhance->SetMarkerStyle(28);
  h_pp_JERsmear->SetMarkerStyle(30);
  h_pp_bGS->SetMarkerStyle(32);
  h_pp_JEUShiftUp->SetMarkerStyle(33);
  h_pp_JEUShiftDown->SetMarkerStyle(34);
  h_pp_residual->SetMarkerStyle(35);
  h_pp_total->SetMarkerStyle(24);

  h_pp_cFraction->SetMarkerSize(marker_size);
  h_pp_lowerBound->SetMarkerSize(marker_size);
  h_pp_bEnhance->SetMarkerSize(marker_size);
  h_pp_cEnhance->SetMarkerSize(marker_size);
  h_pp_JERsmear->SetMarkerSize(marker_size);
  h_pp_bGS->SetMarkerSize(marker_size);
  h_pp_JEUShiftUp->SetMarkerSize(marker_size);
  h_pp_JEUShiftDown->SetMarkerSize(marker_size);
  h_pp_residual->SetMarkerSize(marker_size);
  h_pp_total->SetMarkerSize(marker_size);

  

  h_pp_cFraction->SetLineWidth(line_width);
  h_pp_lowerBound->SetLineWidth(line_width);
  h_pp_bEnhance->SetLineWidth(line_width);
  h_pp_cEnhance->SetLineWidth(line_width);
  h_pp_JERsmear->SetLineWidth(line_width);
  h_pp_bGS->SetLineWidth(line_width);
  h_pp_JEUShiftUp->SetLineWidth(line_width);
  h_pp_JEUShiftDown->SetLineWidth(line_width);
  h_pp_residual->SetLineWidth(line_width);
  h_pp_total->SetLineWidth(line_width);

  h_pp_cFraction->SetLineStyle(2);
  h_pp_lowerBound->SetLineStyle(3);
  h_pp_bEnhance->SetLineStyle(4);
  h_pp_cEnhance->SetLineStyle(5);
  h_pp_JERsmear->SetLineStyle(6);
  h_pp_bGS->SetLineStyle(7);
  h_pp_JEUShiftUp->SetLineStyle(8);
  h_pp_JEUShiftDown->SetLineStyle(9);
  h_pp_residual->SetLineStyle(10);
  h_pp_total->SetLineStyle(1);
  // -------------------------------------------
  TH1D *h_C2_cFraction = new TH1D("h_C2_cFraction","h_C2_cFraction",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_lowerBound = new TH1D("h_C2_lowerBound","h_C2_lowerBound",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_bEnhance = new TH1D("h_C2_bEnhance","h_C2_bEnhance",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_cEnhance = new TH1D("h_C2_cEnhance","h_C2_cEnhance",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_JERsmear = new TH1D("h_C2_JERsmear","h_C2_JERsmear",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_bGS = new TH1D("h_C2_bGS","h_C2_bGS",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_JEUShiftUp = new TH1D("h_C2_JEUShiftUp","h_C2_JEUShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_JEUShiftDown = new TH1D("h_C2_JEUShiftDown","h_C2_JEUShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_residual = new TH1D("h_C2_residual","h_C2_residual",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_total = new TH1D("h_C2_total","h_C2_total",N_jetPtAxisEdges-1,jetPtAxisEdges);
  
  h_C2_cFraction->SetBinContent(1,input_C2_cFrac_J1);
  h_C2_cFraction->SetBinContent(2,input_C2_cFrac_J2);
  h_C2_cFraction->SetBinContent(3,input_C2_cFrac_J3);
  h_C2_cFraction->SetBinContent(4,input_C2_cFrac_J4);
  h_C2_cFraction->SetBinContent(5,input_C2_cFrac_J5);
  h_C2_cFraction->SetBinContent(6,input_C2_cFrac_J6);

  h_C2_lowerBound->SetBinContent(1,input_C2_lowerBound_J1);
  h_C2_lowerBound->SetBinContent(2,input_C2_lowerBound_J2);
  h_C2_lowerBound->SetBinContent(3,input_C2_lowerBound_J3);
  h_C2_lowerBound->SetBinContent(4,input_C2_lowerBound_J4);
  h_C2_lowerBound->SetBinContent(5,input_C2_lowerBound_J5);
  h_C2_lowerBound->SetBinContent(6,input_C2_lowerBound_J6);

  h_C2_bEnhance->SetBinContent(1,input_C2_bEnhance_J1);
  h_C2_bEnhance->SetBinContent(2,input_C2_bEnhance_J2);
  h_C2_bEnhance->SetBinContent(3,input_C2_bEnhance_J3);
  h_C2_bEnhance->SetBinContent(4,input_C2_bEnhance_J4);
  h_C2_bEnhance->SetBinContent(5,input_C2_bEnhance_J5);
  h_C2_bEnhance->SetBinContent(6,input_C2_bEnhance_J6);

  h_C2_cEnhance->SetBinContent(1,input_C2_cEnhance_J1);
  h_C2_cEnhance->SetBinContent(2,input_C2_cEnhance_J2);
  h_C2_cEnhance->SetBinContent(3,input_C2_cEnhance_J3);
  h_C2_cEnhance->SetBinContent(4,input_C2_cEnhance_J4);
  h_C2_cEnhance->SetBinContent(5,input_C2_cEnhance_J5);
  h_C2_cEnhance->SetBinContent(6,input_C2_cEnhance_J6);

  h_C2_JERsmear->SetBinContent(1,input_C2_JERsmear_J1);
  h_C2_JERsmear->SetBinContent(2,input_C2_JERsmear_J2);
  h_C2_JERsmear->SetBinContent(3,input_C2_JERsmear_J3);
  h_C2_JERsmear->SetBinContent(4,input_C2_JERsmear_J4);
  h_C2_JERsmear->SetBinContent(5,input_C2_JERsmear_J5);
  h_C2_JERsmear->SetBinContent(6,input_C2_JERsmear_J6);

  h_C2_bGS->SetBinContent(1,input_C2_bGS_J1);
  h_C2_bGS->SetBinContent(2,input_C2_bGS_J2);
  h_C2_bGS->SetBinContent(3,input_C2_bGS_J3);
  h_C2_bGS->SetBinContent(4,input_C2_bGS_J4);
  h_C2_bGS->SetBinContent(5,input_C2_bGS_J5);
  h_C2_bGS->SetBinContent(6,input_C2_bGS_J6);
  
  h_C2_JEUShiftUp->SetBinContent(1,input_C2_JEUShiftUp_J1);
  h_C2_JEUShiftUp->SetBinContent(2,input_C2_JEUShiftUp_J2);
  h_C2_JEUShiftUp->SetBinContent(3,input_C2_JEUShiftUp_J3);
  h_C2_JEUShiftUp->SetBinContent(4,input_C2_JEUShiftUp_J4);
  h_C2_JEUShiftUp->SetBinContent(5,input_C2_JEUShiftUp_J5);
  h_C2_JEUShiftUp->SetBinContent(6,input_C2_JEUShiftUp_J6);

  h_C2_JEUShiftDown->SetBinContent(1,input_C2_JEUShiftDown_J1);
  h_C2_JEUShiftDown->SetBinContent(2,input_C2_JEUShiftDown_J2);
  h_C2_JEUShiftDown->SetBinContent(3,input_C2_JEUShiftDown_J3);
  h_C2_JEUShiftDown->SetBinContent(4,input_C2_JEUShiftDown_J4);
  h_C2_JEUShiftDown->SetBinContent(5,input_C2_JEUShiftDown_J5);
  h_C2_JEUShiftDown->SetBinContent(6,input_C2_JEUShiftDown_J6);

  h_C2_residual->SetBinContent(1,input_C2_residual_J1);
  h_C2_residual->SetBinContent(2,input_C2_residual_J2);
  h_C2_residual->SetBinContent(3,input_C2_residual_J3);
  h_C2_residual->SetBinContent(4,input_C2_residual_J4);
  h_C2_residual->SetBinContent(5,input_C2_residual_J5);
  h_C2_residual->SetBinContent(6,input_C2_residual_J6);

  h_C2_total->SetBinContent(1,input_C2_total_J1);
  h_C2_total->SetBinContent(2,input_C2_total_J2);
  h_C2_total->SetBinContent(3,input_C2_total_J3);
  h_C2_total->SetBinContent(4,input_C2_total_J4);
  h_C2_total->SetBinContent(5,input_C2_total_J5);
  h_C2_total->SetBinContent(6,input_C2_total_J6);

  // set style
  h_C2_cFraction->SetMarkerColor(kBlue-4);
  h_C2_lowerBound->SetMarkerColor(kRed-4);
  h_C2_bEnhance->SetMarkerColor(kGreen+2);
  h_C2_cEnhance->SetMarkerColor(kMagenta);
  h_C2_JERsmear->SetMarkerColor(kOrange);
  h_C2_bGS->SetMarkerColor(kBlue-9);
  h_C2_JEUShiftUp->SetMarkerColor(kGreen-8);
  h_C2_JEUShiftDown->SetMarkerColor(kPink+9);
  h_C2_residual->SetMarkerColor(kMagenta+3);
  h_C2_total->SetMarkerColor(kBlack);

  h_C2_cFraction->SetLineColor(kBlue-4);
  h_C2_lowerBound->SetLineColor(kRed-4);
  h_C2_bEnhance->SetLineColor(kGreen+2);
  h_C2_cEnhance->SetLineColor(kMagenta);
  h_C2_JERsmear->SetLineColor(kOrange);
  h_C2_bGS->SetLineColor(kBlue-9);
  h_C2_JEUShiftUp->SetLineColor(kGreen-8);
  h_C2_JEUShiftDown->SetLineColor(kPink+9);
  h_C2_residual->SetLineColor(kMagenta+3);
  h_C2_total->SetLineColor(kBlack);

  h_C2_cFraction->SetMarkerStyle(25);
  h_C2_lowerBound->SetMarkerStyle(26);
  h_C2_bEnhance->SetMarkerStyle(27);
  h_C2_cEnhance->SetMarkerStyle(28);
  h_C2_JERsmear->SetMarkerStyle(30);
  h_C2_bGS->SetMarkerStyle(32);
  h_C2_JEUShiftUp->SetMarkerStyle(33);
  h_C2_JEUShiftDown->SetMarkerStyle(34);
  h_C2_residual->SetMarkerStyle(35);
  h_C2_total->SetMarkerStyle(24);

  h_C2_cFraction->SetMarkerSize(marker_size);
  h_C2_lowerBound->SetMarkerSize(marker_size);
  h_C2_bEnhance->SetMarkerSize(marker_size);
  h_C2_cEnhance->SetMarkerSize(marker_size);
  h_C2_JERsmear->SetMarkerSize(marker_size);
  h_C2_bGS->SetMarkerSize(marker_size);
  h_C2_JEUShiftUp->SetMarkerSize(marker_size);
  h_C2_JEUShiftDown->SetMarkerSize(marker_size);
  h_C2_residual->SetMarkerSize(marker_size);
  h_C2_total->SetMarkerSize(marker_size);

  

  h_C2_cFraction->SetLineWidth(line_width);
  h_C2_lowerBound->SetLineWidth(line_width);
  h_C2_bEnhance->SetLineWidth(line_width);
  h_C2_cEnhance->SetLineWidth(line_width);
  h_C2_JERsmear->SetLineWidth(line_width);
  h_C2_bGS->SetLineWidth(line_width);
  h_C2_JEUShiftUp->SetLineWidth(line_width);
  h_C2_JEUShiftDown->SetLineWidth(line_width);
  h_C2_residual->SetLineWidth(line_width);
  h_C2_total->SetLineWidth(line_width);

  h_C2_cFraction->SetLineStyle(2);
  h_C2_lowerBound->SetLineStyle(3);
  h_C2_bEnhance->SetLineStyle(4);
  h_C2_cEnhance->SetLineStyle(5);
  h_C2_JERsmear->SetLineStyle(6);
  h_C2_bGS->SetLineStyle(7);
  h_C2_JEUShiftUp->SetLineStyle(8);
  h_C2_JEUShiftDown->SetLineStyle(9);
  h_C2_residual->SetLineStyle(10);
  h_C2_total->SetLineStyle(1);
  // -------------------------------------------
  TH1D *h_C1_cFraction = new TH1D("h_C1_cFraction","h_C1_cFraction",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_lowerBound = new TH1D("h_C1_lowerBound","h_C1_lowerBound",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_bEnhance = new TH1D("h_C1_bEnhance","h_C1_bEnhance",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_cEnhance = new TH1D("h_C1_cEnhance","h_C1_cEnhance",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_JERsmear = new TH1D("h_C1_JERsmear","h_C1_JERsmear",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_bGS = new TH1D("h_C1_bGS","h_C1_bGS",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_JEUShiftUp = new TH1D("h_C1_JEUShiftUp","h_C1_JEUShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_JEUShiftDown = new TH1D("h_C1_JEUShiftDown","h_C1_JEUShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_residual = new TH1D("h_C1_residual","h_C1_residual",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_total = new TH1D("h_C1_total","h_C1_total",N_jetPtAxisEdges-1,jetPtAxisEdges);
  
  h_C1_cFraction->SetBinContent(1,input_C1_cFrac_J1);
  h_C1_cFraction->SetBinContent(2,input_C1_cFrac_J2);
  h_C1_cFraction->SetBinContent(3,input_C1_cFrac_J3);
  h_C1_cFraction->SetBinContent(4,input_C1_cFrac_J4);
  h_C1_cFraction->SetBinContent(5,input_C1_cFrac_J5);
  h_C1_cFraction->SetBinContent(6,input_C1_cFrac_J6);

  h_C1_lowerBound->SetBinContent(1,input_C1_lowerBound_J1);
  h_C1_lowerBound->SetBinContent(2,input_C1_lowerBound_J2);
  h_C1_lowerBound->SetBinContent(3,input_C1_lowerBound_J3);
  h_C1_lowerBound->SetBinContent(4,input_C1_lowerBound_J4);
  h_C1_lowerBound->SetBinContent(5,input_C1_lowerBound_J5);
  h_C1_lowerBound->SetBinContent(6,input_C1_lowerBound_J6);

  h_C1_bEnhance->SetBinContent(1,input_C1_bEnhance_J1);
  h_C1_bEnhance->SetBinContent(2,input_C1_bEnhance_J2);
  h_C1_bEnhance->SetBinContent(3,input_C1_bEnhance_J3);
  h_C1_bEnhance->SetBinContent(4,input_C1_bEnhance_J4);
  h_C1_bEnhance->SetBinContent(5,input_C1_bEnhance_J5);
  h_C1_bEnhance->SetBinContent(6,input_C1_bEnhance_J6);

  h_C1_cEnhance->SetBinContent(1,input_C1_cEnhance_J1);
  h_C1_cEnhance->SetBinContent(2,input_C1_cEnhance_J2);
  h_C1_cEnhance->SetBinContent(3,input_C1_cEnhance_J3);
  h_C1_cEnhance->SetBinContent(4,input_C1_cEnhance_J4);
  h_C1_cEnhance->SetBinContent(5,input_C1_cEnhance_J5);
  h_C1_cEnhance->SetBinContent(6,input_C1_cEnhance_J6);

  h_C1_JERsmear->SetBinContent(1,input_C1_JERsmear_J1);
  h_C1_JERsmear->SetBinContent(2,input_C1_JERsmear_J2);
  h_C1_JERsmear->SetBinContent(3,input_C1_JERsmear_J3);
  h_C1_JERsmear->SetBinContent(4,input_C1_JERsmear_J4);
  h_C1_JERsmear->SetBinContent(5,input_C1_JERsmear_J5);
  h_C1_JERsmear->SetBinContent(6,input_C1_JERsmear_J6);

  h_C1_bGS->SetBinContent(1,input_C1_bGS_J1);
  h_C1_bGS->SetBinContent(2,input_C1_bGS_J2);
  h_C1_bGS->SetBinContent(3,input_C1_bGS_J3);
  h_C1_bGS->SetBinContent(4,input_C1_bGS_J4);
  h_C1_bGS->SetBinContent(5,input_C1_bGS_J5);
  h_C1_bGS->SetBinContent(6,input_C1_bGS_J6);
  
  h_C1_JEUShiftUp->SetBinContent(1,input_C1_JEUShiftUp_J1);
  h_C1_JEUShiftUp->SetBinContent(2,input_C1_JEUShiftUp_J2);
  h_C1_JEUShiftUp->SetBinContent(3,input_C1_JEUShiftUp_J3);
  h_C1_JEUShiftUp->SetBinContent(4,input_C1_JEUShiftUp_J4);
  h_C1_JEUShiftUp->SetBinContent(5,input_C1_JEUShiftUp_J5);
  h_C1_JEUShiftUp->SetBinContent(6,input_C1_JEUShiftUp_J6);

  h_C1_JEUShiftDown->SetBinContent(1,input_C1_JEUShiftDown_J1);
  h_C1_JEUShiftDown->SetBinContent(2,input_C1_JEUShiftDown_J2);
  h_C1_JEUShiftDown->SetBinContent(3,input_C1_JEUShiftDown_J3);
  h_C1_JEUShiftDown->SetBinContent(4,input_C1_JEUShiftDown_J4);
  h_C1_JEUShiftDown->SetBinContent(5,input_C1_JEUShiftDown_J5);
  h_C1_JEUShiftDown->SetBinContent(6,input_C1_JEUShiftDown_J6);

  h_C1_residual->SetBinContent(1,input_C1_residual_J1);
  h_C1_residual->SetBinContent(2,input_C1_residual_J2);
  h_C1_residual->SetBinContent(3,input_C1_residual_J3);
  h_C1_residual->SetBinContent(4,input_C1_residual_J4);
  h_C1_residual->SetBinContent(5,input_C1_residual_J5);
  h_C1_residual->SetBinContent(6,input_C1_residual_J6);

  h_C1_total->SetBinContent(1,input_C1_total_J1);
  h_C1_total->SetBinContent(2,input_C1_total_J2);
  h_C1_total->SetBinContent(3,input_C1_total_J3);
  h_C1_total->SetBinContent(4,input_C1_total_J4);
  h_C1_total->SetBinContent(5,input_C1_total_J5);
  h_C1_total->SetBinContent(6,input_C1_total_J6);

  // set style
  h_C1_cFraction->SetMarkerColor(kBlue-4);
  h_C1_lowerBound->SetMarkerColor(kRed-4);
  h_C1_bEnhance->SetMarkerColor(kGreen+2);
  h_C1_cEnhance->SetMarkerColor(kMagenta);
  h_C1_JERsmear->SetMarkerColor(kOrange);
  h_C1_bGS->SetMarkerColor(kBlue-9);
  h_C1_JEUShiftUp->SetMarkerColor(kGreen-8);
  h_C1_JEUShiftDown->SetMarkerColor(kPink+9);
  h_C1_residual->SetMarkerColor(kMagenta+3);
  h_C1_total->SetMarkerColor(kBlack);

  h_C1_cFraction->SetLineColor(kBlue-4);
  h_C1_lowerBound->SetLineColor(kRed-4);
  h_C1_bEnhance->SetLineColor(kGreen+2);
  h_C1_cEnhance->SetLineColor(kMagenta);
  h_C1_JERsmear->SetLineColor(kOrange);
  h_C1_bGS->SetLineColor(kBlue-9);
  h_C1_JEUShiftUp->SetLineColor(kGreen-8);
  h_C1_JEUShiftDown->SetLineColor(kPink+9);
  h_C1_residual->SetLineColor(kMagenta+3);
  h_C1_total->SetLineColor(kBlack);

  h_C1_cFraction->SetMarkerStyle(25);
  h_C1_lowerBound->SetMarkerStyle(26);
  h_C1_bEnhance->SetMarkerStyle(27);
  h_C1_cEnhance->SetMarkerStyle(28);
  h_C1_JERsmear->SetMarkerStyle(30);
  h_C1_bGS->SetMarkerStyle(32);
  h_C1_JEUShiftUp->SetMarkerStyle(33);
  h_C1_JEUShiftDown->SetMarkerStyle(34);
  h_C1_residual->SetMarkerStyle(35);
  h_C1_total->SetMarkerStyle(24);

  h_C1_cFraction->SetMarkerSize(marker_size);
  h_C1_lowerBound->SetMarkerSize(marker_size);
  h_C1_bEnhance->SetMarkerSize(marker_size);
  h_C1_cEnhance->SetMarkerSize(marker_size);
  h_C1_JERsmear->SetMarkerSize(marker_size);
  h_C1_bGS->SetMarkerSize(marker_size);
  h_C1_JEUShiftUp->SetMarkerSize(marker_size);
  h_C1_JEUShiftDown->SetMarkerSize(marker_size);
  h_C1_residual->SetMarkerSize(marker_size);
  h_C1_total->SetMarkerSize(marker_size);

  

  h_C1_cFraction->SetLineWidth(line_width);
  h_C1_lowerBound->SetLineWidth(line_width);
  h_C1_bEnhance->SetLineWidth(line_width);
  h_C1_cEnhance->SetLineWidth(line_width);
  h_C1_JERsmear->SetLineWidth(line_width);
  h_C1_bGS->SetLineWidth(line_width);
  h_C1_JEUShiftUp->SetLineWidth(line_width);
  h_C1_JEUShiftDown->SetLineWidth(line_width);
  h_C1_residual->SetLineWidth(line_width);
  h_C1_total->SetLineWidth(line_width);

  h_C1_cFraction->SetLineStyle(2);
  h_C1_lowerBound->SetLineStyle(3);
  h_C1_bEnhance->SetLineStyle(4);
  h_C1_cEnhance->SetLineStyle(5);
  h_C1_JERsmear->SetLineStyle(6);
  h_C1_bGS->SetLineStyle(7);
  h_C1_JEUShiftUp->SetLineStyle(8);
  h_C1_JEUShiftDown->SetLineStyle(9);
  h_C1_residual->SetLineStyle(10);
  h_C1_total->SetLineStyle(1);

  // *****************************************************************************

  
  TCanvas *canv_pp = new TCanvas("canv_pp","canv_pp",800,800);
  canv_pp->cd();
  TPad *pad_pp = new TPad("pad_pp","pad_pp",0,0,1,1);
  pad_pp->SetLeftMargin(0.2);
  pad_pp->SetBottomMargin(0.2);
  pad_pp->Draw();
  pad_pp->cd();
  h_pp_total->GetYaxis()->SetRangeUser(0,0.4);
  h_pp_total->SetTitle("");
  h_pp_total->SetStats(0);
  h_pp_total->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  h_pp_total->GetYaxis()->SetTitle("Systematic uncertainty");
  h_pp_total->Draw();
  h_pp_cFraction->Draw("same");
  h_pp_lowerBound->Draw("same");
  //h_pp_bEnhance->Draw("same");
  //h_pp_cEnhance->Draw("same");
  h_pp_JERsmear->Draw("same");
  h_pp_bGS->Draw("same");
  h_pp_JEUShiftUp->Draw("same");
  h_pp_JEUShiftDown->Draw("same");
  h_pp_residual->Draw("same");

  TLegend *leg_pp = new TLegend(0.52,0.65,0.78,0.88);
  leg_pp->SetBorderSize(0);
  leg_pp->SetTextSize(0.031);
  leg_pp->AddEntry(h_pp_total,"Total","l");
  leg_pp->AddEntry(h_pp_cFraction,"#it{c}-fraction","l");
  leg_pp->AddEntry(h_pp_lowerBound,"#it{p}_{T}^{rel} lower-bound","l");
  //leg_pp->AddEntry(h_pp_bEnhance,"#it{b}-template enhancement","l");
  //leg_pp->AddEntry(h_pp_cEnhance,"#it{c}-template enhancement","l");
  leg_pp->AddEntry(h_pp_JERsmear,"JER uncertainty","l");
  leg_pp->AddEntry(h_pp_bGS,"gluon-splitting uncertainty","l");
  leg_pp->AddEntry(h_pp_JEUShiftUp,"JEU uncertainty \"up\" ","l");
  leg_pp->AddEntry(h_pp_JEUShiftDown,"JEU uncertainty \"down\" ","l");
  leg_pp->AddEntry(h_pp_residual,"Residual non-closure ","l");
  leg_pp->Draw();

  if(do_mu7) la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}                  pp 5.02 TeV (274 pb^{-1})");
  else if(do_mu12) la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}                  pp 5.02 TeV (301 pb^{-1})");
  else{};

  // #############################################################
  
  TCanvas *canv_C2 = new TCanvas("canv_C2","canv_C2",800,800);
  canv_C2->cd();
  TPad *pad_C2 = new TPad("pad_C2","pad_C2",0,0,1,1);
  pad_C2->SetLeftMargin(0.2);
  pad_C2->SetBottomMargin(0.2);
  pad_C2->Draw();
  pad_C2->cd();
  h_C2_total->GetYaxis()->SetRangeUser(0,0.4);
  h_C2_total->SetTitle("");
  h_C2_total->SetStats(0);
  h_C2_total->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  h_C2_total->GetYaxis()->SetTitle("Systematic uncertainty");
  h_C2_total->Draw();
  h_C2_cFraction->Draw("same");
  h_C2_lowerBound->Draw("same");
  //h_C2_bEnhance->Draw("same");
  //h_C2_cEnhance->Draw("same");
  h_C2_JERsmear->Draw("same");
  h_C2_bGS->Draw("same");
  h_C2_JEUShiftUp->Draw("same");
  h_C2_JEUShiftDown->Draw("same");
  h_C2_residual->Draw("same");

  TLegend *leg_C2 = new TLegend(0.52,0.65,0.78,0.88);
  leg_C2->SetBorderSize(0);
  leg_C2->SetTextSize(0.031);
  leg_C2->AddEntry(h_C2_total,"Total","l");
  leg_C2->AddEntry(h_C2_cFraction,"#it{c}-fraction","l");
  leg_C2->AddEntry(h_C2_lowerBound,"#it{p}_{T}^{rel} lower-bound","l");
  //leg_C2->AddEntry(h_C2_bEnhance,"#it{b}-template enhancement","l");
  //leg_C2->AddEntry(h_C2_cEnhance,"#it{c}-template enhancement","l");
  leg_C2->AddEntry(h_C2_JERsmear,"JER uncertainty","l");
  leg_C2->AddEntry(h_C2_bGS,"gluon-splitting uncertainty","l");
  leg_C2->AddEntry(h_C2_JEUShiftUp,"JEU uncertainty \"up\" ","l");
  leg_C2->AddEntry(h_C2_JEUShiftDown,"JEU uncertainty \"down\" ","l");
  leg_C2->AddEntry(h_C2_residual,"Residual non-closure ","l");
  leg_C2->Draw();

  if(do_mu7) la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}      PbPb 30-90% 5.02 TeV (0.787 nb^{-1})");
  else if(do_mu12) la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}       PbPb 30-90% TeV (1.689 nb^{-1})");
  else{};

    // #############################################################
  
  TCanvas *canv_C1 = new TCanvas("canv_C1","canv_C1",800,800);
  canv_C1->cd();
  TPad *pad_C1 = new TPad("pad_C1","pad_C1",0,0,1,1);
  pad_C1->SetLeftMargin(0.2);
  pad_C1->SetBottomMargin(0.2);
  pad_C1->Draw();
  pad_C1->cd();
  h_C1_total->GetYaxis()->SetRangeUser(0,0.4);
  h_C1_total->SetTitle("");
  h_C1_total->SetStats(0);
  h_C1_total->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  h_C1_total->GetYaxis()->SetTitle("Systematic uncertainty");
  h_C1_total->Draw();
  h_C1_cFraction->Draw("same");
  h_C1_lowerBound->Draw("same");
  //h_C1_bEnhance->Draw("same");
  //h_C1_cEnhance->Draw("same");
  h_C1_JERsmear->Draw("same");
  h_C1_bGS->Draw("same");
  h_C1_JEUShiftUp->Draw("same");
  h_C1_JEUShiftDown->Draw("same");
  h_C1_residual->Draw("same");

  TLegend *leg_C1 = new TLegend(0.52,0.65,0.78,0.88);
  leg_C1->SetBorderSize(0);
  leg_C1->SetTextSize(0.031);
  leg_C1->AddEntry(h_C1_total,"Total","l");
  leg_C1->AddEntry(h_C1_cFraction,"#it{c}-fraction","l");
  leg_C1->AddEntry(h_C1_lowerBound,"#it{p}_{T}^{rel} lower-bound","l");
  //leg_C1->AddEntry(h_C1_bEnhance,"#it{b}-template enhancement","l");
  //leg_C1->AddEntry(h_C1_cEnhance,"#it{c}-template enhancement","l");
  leg_C1->AddEntry(h_C1_JERsmear,"JER uncertainty","l");
  leg_C1->AddEntry(h_C1_bGS,"gluon-splitting uncertainty","l");
  leg_C1->AddEntry(h_C1_JEUShiftUp,"JES uncertainty \"up\" ","l");
  leg_C1->AddEntry(h_C1_JEUShiftDown,"JES uncertainty \"down\" ","l");
  leg_C1->AddEntry(h_C1_residual,"Residual non-closure ","l");
  leg_C1->Draw();

  if(do_mu7) la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}      PbPb 0-30% 5.02 TeV (0.787 nb^{-1})");
  else if(do_mu12) la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}       PbPb 0-30% TeV (1.689 nb^{-1})");
  else{};
 

  
}
