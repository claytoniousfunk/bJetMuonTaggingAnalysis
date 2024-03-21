

#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/systematicsResults.h"


void systematicsPlots(bool do_mu5  = 1,
		      bool do_mu7  = 0,
		      bool do_mu12 = 0){

  TLatex *la = new TLatex();
  la->SetTextFont(42);


  // some draw options
  double new_bar_width = 0.3;
  double new_bar_offset = 0.05;


  ///  Calculate total
  const int N_sys_sources = 6;
  // pp
  // -- mu5
  double sys_total_pp_mu5_J2_array[N_sys_sources] = {sys_cFraction_pp_mu5_J2,
                                                     sys_lowerBound_pp_mu5_J2,
						     sys_bEnhance_pp_mu5_J2,
						     sys_cEnhance_pp_mu5_J2,
						     sys_JERsmear_pp_mu5_J2,
						     sys_centShift_pp_mu5_J2};

  double sys_total_pp_mu5_J3_array[N_sys_sources] = {sys_cFraction_pp_mu5_J3,
                                                     sys_lowerBound_pp_mu5_J3,
						     sys_bEnhance_pp_mu5_J3,
						     sys_cEnhance_pp_mu5_J3,
						     sys_JERsmear_pp_mu5_J3,
						     sys_centShift_pp_mu5_J3};

  double sys_total_pp_mu5_J4_array[N_sys_sources] = {sys_cFraction_pp_mu5_J4,
                                                     sys_lowerBound_pp_mu5_J4,
						     sys_bEnhance_pp_mu5_J4,
						     sys_cEnhance_pp_mu5_J4,
						     sys_JERsmear_pp_mu5_J4,
						     sys_centShift_pp_mu5_J4};
  // -- mu7
  double sys_total_pp_mu7_J2_array[N_sys_sources] = {sys_cFraction_pp_mu7_J2,
                                                     sys_lowerBound_pp_mu7_J2,
						     sys_bEnhance_pp_mu7_J2,
						     sys_cEnhance_pp_mu7_J2,
						     sys_JERsmear_pp_mu7_J2,
						     sys_centShift_pp_mu7_J2};

  double sys_total_pp_mu7_J3_array[N_sys_sources] = {sys_cFraction_pp_mu7_J3,
                                                     sys_lowerBound_pp_mu7_J3,
						     sys_bEnhance_pp_mu7_J3,
						     sys_cEnhance_pp_mu7_J3,
						     sys_JERsmear_pp_mu7_J3,
						     sys_centShift_pp_mu7_J3};

  double sys_total_pp_mu7_J4_array[N_sys_sources] = {sys_cFraction_pp_mu7_J4,
                                                     sys_lowerBound_pp_mu7_J4,
						     sys_bEnhance_pp_mu7_J4,
						     sys_cEnhance_pp_mu7_J4,
						     sys_JERsmear_pp_mu7_J4,
						     sys_centShift_pp_mu7_J4};

  // -- mu12
  double sys_total_pp_mu12_J2_array[N_sys_sources] = {sys_cFraction_pp_mu12_J2,
                                                      sys_lowerBound_pp_mu12_J2,
						      sys_bEnhance_pp_mu12_J2,
						      sys_cEnhance_pp_mu12_J2,
						      sys_JERsmear_pp_mu12_J2,
						      sys_centShift_pp_mu12_J2};

  double sys_total_pp_mu12_J3_array[N_sys_sources] = {sys_cFraction_pp_mu12_J3,
                                                      sys_lowerBound_pp_mu12_J3,
						      sys_bEnhance_pp_mu12_J3,
						      sys_cEnhance_pp_mu12_J3,
						      sys_JERsmear_pp_mu12_J3,
						      sys_centShift_pp_mu12_J3};

  double sys_total_pp_mu12_J4_array[N_sys_sources] = {sys_cFraction_pp_mu12_J4,
                                                      sys_lowerBound_pp_mu12_J4,
						      sys_bEnhance_pp_mu12_J4,
						      sys_cEnhance_pp_mu12_J4,
						      sys_JERsmear_pp_mu12_J4,
						      sys_centShift_pp_mu12_J4};


  // PbPb 30-90%
  // -- mu5
  double sys_total_PbPb_mu5_C2_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu5_C2_J2,
                                                          sys_lowerBound_PbPb_mu5_C2_J2,
							  sys_bEnhance_PbPb_mu5_C2_J2,
							  sys_cEnhance_PbPb_mu5_C2_J2,
							  sys_JERsmear_PbPb_mu5_C2_J2,
							  sys_centShift_PbPb_mu5_C2_J2};

  double sys_total_PbPb_mu5_C2_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu5_C2_J3,
                                                          sys_lowerBound_PbPb_mu5_C2_J3,
							  sys_bEnhance_PbPb_mu5_C2_J3,
							  sys_cEnhance_PbPb_mu5_C2_J3,
							  sys_JERsmear_PbPb_mu5_C2_J3,
							  sys_centShift_PbPb_mu5_C2_J3};

  double sys_total_PbPb_mu5_C2_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu5_C2_J4,
                                                          sys_lowerBound_PbPb_mu5_C2_J4,
							  sys_bEnhance_PbPb_mu5_C2_J4,
							  sys_cEnhance_PbPb_mu5_C2_J4,
							  sys_JERsmear_PbPb_mu5_C2_J4,
							  sys_centShift_PbPb_mu5_C2_J4};
  // -- mu7
  double sys_total_PbPb_mu7_C2_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu7_C2_J2,
                                                          sys_lowerBound_PbPb_mu7_C2_J2,
							  sys_bEnhance_PbPb_mu7_C2_J2,
							  sys_cEnhance_PbPb_mu7_C2_J2,
							  sys_JERsmear_PbPb_mu7_C2_J2,
							  sys_centShift_PbPb_mu7_C2_J2};

  double sys_total_PbPb_mu7_C2_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu7_C2_J3,
                                                          sys_lowerBound_PbPb_mu7_C2_J3,
							  sys_bEnhance_PbPb_mu7_C2_J3,
							  sys_cEnhance_PbPb_mu7_C2_J3,
							  sys_JERsmear_PbPb_mu7_C2_J3,
							  sys_centShift_PbPb_mu7_C2_J3};

  double sys_total_PbPb_mu7_C2_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu7_C2_J4,
                                                          sys_lowerBound_PbPb_mu7_C2_J4,
							  sys_bEnhance_PbPb_mu7_C2_J4,
							  sys_cEnhance_PbPb_mu7_C2_J4,
							  sys_JERsmear_PbPb_mu7_C2_J4,
							  sys_centShift_PbPb_mu7_C2_J4};
  // -- mu12
  double sys_total_PbPb_mu12_C2_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J2,
                                                           sys_lowerBound_PbPb_mu12_C2_J2,
							   sys_bEnhance_PbPb_mu12_C2_J2,
							   sys_cEnhance_PbPb_mu12_C2_J2,
							   sys_JERsmear_PbPb_mu12_C2_J2,
							   sys_centShift_PbPb_mu12_C2_J2};

  double sys_total_PbPb_mu12_C2_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J3,
                                                           sys_lowerBound_PbPb_mu12_C2_J3,
							   sys_bEnhance_PbPb_mu12_C2_J3,
							   sys_cEnhance_PbPb_mu12_C2_J3,
							   sys_JERsmear_PbPb_mu12_C2_J3,
							   sys_centShift_PbPb_mu12_C2_J3};

  double sys_total_PbPb_mu12_C2_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J4,
                                                           sys_lowerBound_PbPb_mu12_C2_J4,
							   sys_bEnhance_PbPb_mu12_C2_J4,
							   sys_cEnhance_PbPb_mu12_C2_J4,
							   sys_JERsmear_PbPb_mu12_C2_J4,
							   sys_centShift_PbPb_mu12_C2_J4};

  // PbPb 0-30%
  // -- mu5
  double sys_total_PbPb_mu5_C1_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu5_C1_J2,
                                                          sys_lowerBound_PbPb_mu5_C1_J2,
							  sys_bEnhance_PbPb_mu5_C1_J2,
							  sys_cEnhance_PbPb_mu5_C1_J2,
							  sys_JERsmear_PbPb_mu5_C1_J2,
							  sys_centShift_PbPb_mu5_C1_J2};

  double sys_total_PbPb_mu5_C1_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu5_C1_J3,
                                                          sys_lowerBound_PbPb_mu5_C1_J3,
							  sys_bEnhance_PbPb_mu5_C1_J3,
							  sys_cEnhance_PbPb_mu5_C1_J3,
							  sys_JERsmear_PbPb_mu5_C1_J3,
							  sys_centShift_PbPb_mu5_C1_J3};

  double sys_total_PbPb_mu5_C1_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu5_C1_J4,
                                                          sys_lowerBound_PbPb_mu5_C1_J4,
							  sys_bEnhance_PbPb_mu5_C1_J4,
							  sys_cEnhance_PbPb_mu5_C1_J4,
							  sys_JERsmear_PbPb_mu5_C1_J4,
							  sys_centShift_PbPb_mu5_C1_J4};
  // -- mu7
  double sys_total_PbPb_mu7_C1_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu7_C1_J2,
                                                          sys_lowerBound_PbPb_mu7_C1_J2,
							  sys_bEnhance_PbPb_mu7_C1_J2,
							  sys_cEnhance_PbPb_mu7_C1_J2,
							  sys_JERsmear_PbPb_mu7_C1_J2,
							  sys_centShift_PbPb_mu7_C1_J2};

  double sys_total_PbPb_mu7_C1_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu7_C1_J3,
                                                          sys_lowerBound_PbPb_mu7_C1_J3,
							  sys_bEnhance_PbPb_mu7_C1_J3,
							  sys_cEnhance_PbPb_mu7_C1_J3,
							  sys_JERsmear_PbPb_mu7_C1_J3,
							  sys_centShift_PbPb_mu7_C1_J3};

  double sys_total_PbPb_mu7_C1_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu7_C1_J4,
                                                          sys_lowerBound_PbPb_mu7_C1_J4,
							  sys_bEnhance_PbPb_mu7_C1_J4,
							  sys_cEnhance_PbPb_mu7_C1_J4,
							  sys_JERsmear_PbPb_mu7_C1_J4,
							  sys_centShift_PbPb_mu7_C1_J4};
  // -- mu12
  double sys_total_PbPb_mu12_C1_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J2,
                                                           sys_lowerBound_PbPb_mu12_C1_J2,
							   sys_bEnhance_PbPb_mu12_C1_J2,
							   sys_cEnhance_PbPb_mu12_C1_J2,
							   sys_JERsmear_PbPb_mu12_C1_J2,
							   sys_centShift_PbPb_mu12_C1_J2};

  double sys_total_PbPb_mu12_C1_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J3,
                                                           sys_lowerBound_PbPb_mu12_C1_J3,
							   sys_bEnhance_PbPb_mu12_C1_J3,
							   sys_cEnhance_PbPb_mu12_C1_J3,
							   sys_JERsmear_PbPb_mu12_C1_J3,
							   sys_centShift_PbPb_mu12_C1_J3};

  double sys_total_PbPb_mu12_C1_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J4,
                                                           sys_lowerBound_PbPb_mu12_C1_J4,
							   sys_bEnhance_PbPb_mu12_C1_J4,
							   sys_cEnhance_PbPb_mu12_C1_J4,
							   sys_JERsmear_PbPb_mu12_C1_J4,
							   sys_centShift_PbPb_mu12_C1_J4};



  double sys_total_pp_mu5_J2 = 0;
  double sys_total_pp_mu5_J3 = 0;
  double sys_total_pp_mu5_J4 = 0;

  double sys_total_pp_mu7_J2 = 0;
  double sys_total_pp_mu7_J3 = 0;
  double sys_total_pp_mu7_J4 = 0;

  double sys_total_pp_mu12_J2 = 0;
  double sys_total_pp_mu12_J3 = 0;
  double sys_total_pp_mu12_J4 = 0;

  double sys_total_PbPb_mu5_C2_J2 = 0;
  double sys_total_PbPb_mu5_C2_J3 = 0;
  double sys_total_PbPb_mu5_C2_J4 = 0;

  double sys_total_PbPb_mu7_C2_J2 = 0;
  double sys_total_PbPb_mu7_C2_J3 = 0;
  double sys_total_PbPb_mu7_C2_J4 = 0;

  double sys_total_PbPb_mu12_C2_J2 = 0;
  double sys_total_PbPb_mu12_C2_J3 = 0;
  double sys_total_PbPb_mu12_C2_J4 = 0;

  double sys_total_PbPb_mu5_C1_J2 = 0;
  double sys_total_PbPb_mu5_C1_J3 = 0;
  double sys_total_PbPb_mu5_C1_J4 = 0;

  double sys_total_PbPb_mu7_C1_J2 = 0;
  double sys_total_PbPb_mu7_C1_J3 = 0;
  double sys_total_PbPb_mu7_C1_J4 = 0;

  double sys_total_PbPb_mu12_C1_J2 = 0;
  double sys_total_PbPb_mu12_C1_J3 = 0;
  double sys_total_PbPb_mu12_C1_J4 = 0;


  // add the squares
  for(int i = 0; i < N_sys_sources; i++){

    // pp
    sys_total_pp_mu5_J2 += sys_total_pp_mu5_J2_array[i]*sys_total_pp_mu5_J2_array[i];
    sys_total_pp_mu5_J3 += sys_total_pp_mu5_J3_array[i]*sys_total_pp_mu5_J3_array[i];
    sys_total_pp_mu5_J4 += sys_total_pp_mu5_J4_array[i]*sys_total_pp_mu5_J4_array[i];

    sys_total_pp_mu7_J2 += sys_total_pp_mu7_J2_array[i]*sys_total_pp_mu7_J2_array[i];
    sys_total_pp_mu7_J3 += sys_total_pp_mu7_J3_array[i]*sys_total_pp_mu7_J3_array[i];
    sys_total_pp_mu7_J4 += sys_total_pp_mu7_J4_array[i]*sys_total_pp_mu7_J4_array[i];

    sys_total_pp_mu12_J2 += sys_total_pp_mu12_J2_array[i]*sys_total_pp_mu12_J2_array[i];
    sys_total_pp_mu12_J3 += sys_total_pp_mu12_J3_array[i]*sys_total_pp_mu12_J3_array[i];
    sys_total_pp_mu12_J4 += sys_total_pp_mu12_J4_array[i]*sys_total_pp_mu12_J4_array[i];

    // PbPb 30-90%
    sys_total_PbPb_mu5_C2_J2 += sys_total_PbPb_mu5_C2_J2_array[i]*sys_total_PbPb_mu5_C2_J2_array[i];
    sys_total_PbPb_mu5_C2_J3 += sys_total_PbPb_mu5_C2_J3_array[i]*sys_total_PbPb_mu5_C2_J3_array[i];
    sys_total_PbPb_mu5_C2_J4 += sys_total_PbPb_mu5_C2_J4_array[i]*sys_total_PbPb_mu5_C2_J4_array[i];

    sys_total_PbPb_mu7_C2_J2 += sys_total_PbPb_mu7_C2_J2_array[i]*sys_total_PbPb_mu7_C2_J2_array[i];
    sys_total_PbPb_mu7_C2_J3 += sys_total_PbPb_mu7_C2_J3_array[i]*sys_total_PbPb_mu7_C2_J3_array[i];
    sys_total_PbPb_mu7_C2_J4 += sys_total_PbPb_mu7_C2_J4_array[i]*sys_total_PbPb_mu7_C2_J4_array[i];

    sys_total_PbPb_mu12_C2_J2 += sys_total_PbPb_mu12_C2_J2_array[i]*sys_total_PbPb_mu12_C2_J2_array[i];
    sys_total_PbPb_mu12_C2_J3 += sys_total_PbPb_mu12_C2_J3_array[i]*sys_total_PbPb_mu12_C2_J3_array[i];
    sys_total_PbPb_mu12_C2_J4 += sys_total_PbPb_mu12_C2_J4_array[i]*sys_total_PbPb_mu12_C2_J4_array[i];

    // PbPb 0-30%
    sys_total_PbPb_mu5_C1_J2 += sys_total_PbPb_mu5_C1_J2_array[i]*sys_total_PbPb_mu5_C1_J2_array[i];
    sys_total_PbPb_mu5_C1_J3 += sys_total_PbPb_mu5_C1_J3_array[i]*sys_total_PbPb_mu5_C1_J3_array[i];
    sys_total_PbPb_mu5_C1_J4 += sys_total_PbPb_mu5_C1_J4_array[i]*sys_total_PbPb_mu5_C1_J4_array[i];

    sys_total_PbPb_mu7_C1_J2 += sys_total_PbPb_mu7_C1_J2_array[i]*sys_total_PbPb_mu7_C1_J2_array[i];
    sys_total_PbPb_mu7_C1_J3 += sys_total_PbPb_mu7_C1_J3_array[i]*sys_total_PbPb_mu7_C1_J3_array[i];
    sys_total_PbPb_mu7_C1_J4 += sys_total_PbPb_mu7_C1_J4_array[i]*sys_total_PbPb_mu7_C1_J4_array[i];

    sys_total_PbPb_mu12_C1_J2 += sys_total_PbPb_mu12_C1_J2_array[i]*sys_total_PbPb_mu12_C1_J2_array[i];
    sys_total_PbPb_mu12_C1_J3 += sys_total_PbPb_mu12_C1_J3_array[i]*sys_total_PbPb_mu12_C1_J3_array[i];
    sys_total_PbPb_mu12_C1_J4 += sys_total_PbPb_mu12_C1_J4_array[i]*sys_total_PbPb_mu12_C1_J4_array[i];

  }

  sys_total_pp_mu5_J2 = TMath::Sqrt(sys_total_pp_mu5_J2);
  sys_total_pp_mu5_J3 = TMath::Sqrt(sys_total_pp_mu5_J3);
  sys_total_pp_mu5_J4 = TMath::Sqrt(sys_total_pp_mu5_J4);
  sys_total_pp_mu7_J2 = TMath::Sqrt(sys_total_pp_mu7_J2);
  sys_total_pp_mu7_J3 = TMath::Sqrt(sys_total_pp_mu7_J3);
  sys_total_pp_mu7_J4 = TMath::Sqrt(sys_total_pp_mu7_J4);
  sys_total_pp_mu12_J2 = TMath::Sqrt(sys_total_pp_mu12_J2);
  sys_total_pp_mu12_J3 = TMath::Sqrt(sys_total_pp_mu12_J3);
  sys_total_pp_mu12_J4 = TMath::Sqrt(sys_total_pp_mu12_J4);

  sys_total_PbPb_mu5_C2_J2 = TMath::Sqrt(sys_total_PbPb_mu5_C2_J2);
  sys_total_PbPb_mu5_C2_J3 = TMath::Sqrt(sys_total_PbPb_mu5_C2_J3);
  sys_total_PbPb_mu5_C2_J4 = TMath::Sqrt(sys_total_PbPb_mu5_C2_J4);
  sys_total_PbPb_mu7_C2_J2 = TMath::Sqrt(sys_total_PbPb_mu7_C2_J2);
  sys_total_PbPb_mu7_C2_J3 = TMath::Sqrt(sys_total_PbPb_mu7_C2_J3);
  sys_total_PbPb_mu7_C2_J4 = TMath::Sqrt(sys_total_PbPb_mu7_C2_J4);
  sys_total_PbPb_mu12_C2_J2 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J2);
  sys_total_PbPb_mu12_C2_J3 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J3);
  sys_total_PbPb_mu12_C2_J4 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J4);

  sys_total_PbPb_mu5_C1_J2 = TMath::Sqrt(sys_total_PbPb_mu5_C1_J2);
  sys_total_PbPb_mu5_C1_J3 = TMath::Sqrt(sys_total_PbPb_mu5_C1_J3);
  sys_total_PbPb_mu5_C1_J4 = TMath::Sqrt(sys_total_PbPb_mu5_C1_J4);
  sys_total_PbPb_mu7_C1_J2 = TMath::Sqrt(sys_total_PbPb_mu7_C1_J2);
  sys_total_PbPb_mu7_C1_J3 = TMath::Sqrt(sys_total_PbPb_mu7_C1_J3);
  sys_total_PbPb_mu7_C1_J4 = TMath::Sqrt(sys_total_PbPb_mu7_C1_J4);
  sys_total_PbPb_mu12_C1_J2 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J2);
  sys_total_PbPb_mu12_C1_J3 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J3);
  sys_total_PbPb_mu12_C1_J4 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J4);


  
  const int N_sys = 7;
  string sys_names[N_sys] = {"c-fraction-variation","fit-lower-bound","b-template-enhancement","c-template-enhancement","Jet-energy-resolution","centrality-shift","Total"};

  // pp
  // -- mu5
  double sys_pp_mu5_J2_array[N_sys] = {sys_cFraction_pp_mu5_J2, sys_lowerBound_pp_mu5_J2, sys_bEnhance_pp_mu5_J2, sys_cEnhance_pp_mu5_J2, sys_JERsmear_pp_mu5_J2, sys_centShift_pp_mu5_J2, sys_total_pp_mu5_J2};
  double sys_pp_mu5_J3_array[N_sys] = {sys_cFraction_pp_mu5_J3, sys_lowerBound_pp_mu5_J3, sys_bEnhance_pp_mu5_J3, sys_cEnhance_pp_mu5_J3, sys_JERsmear_pp_mu5_J3, sys_centShift_pp_mu5_J3, sys_total_pp_mu5_J3};
  double sys_pp_mu5_J4_array[N_sys] = {sys_cFraction_pp_mu5_J4, sys_lowerBound_pp_mu5_J4, sys_bEnhance_pp_mu5_J4, sys_cEnhance_pp_mu5_J4, sys_JERsmear_pp_mu5_J4, sys_centShift_pp_mu5_J4, sys_total_pp_mu5_J4};
  // -- mu7
  double sys_pp_mu7_J2_array[N_sys] = {sys_cFraction_pp_mu7_J2, sys_lowerBound_pp_mu7_J2, sys_bEnhance_pp_mu7_J2, sys_cEnhance_pp_mu7_J2, sys_JERsmear_pp_mu7_J2, sys_centShift_pp_mu7_J2, sys_total_pp_mu7_J2};
  double sys_pp_mu7_J3_array[N_sys] = {sys_cFraction_pp_mu7_J3, sys_lowerBound_pp_mu7_J3, sys_bEnhance_pp_mu7_J3, sys_cEnhance_pp_mu7_J3, sys_JERsmear_pp_mu7_J3, sys_centShift_pp_mu7_J3, sys_total_pp_mu7_J3};
  double sys_pp_mu7_J4_array[N_sys] = {sys_cFraction_pp_mu7_J4, sys_lowerBound_pp_mu7_J4, sys_bEnhance_pp_mu7_J4, sys_cEnhance_pp_mu7_J4, sys_JERsmear_pp_mu7_J4, sys_centShift_pp_mu7_J4, sys_total_pp_mu7_J4};
  // -- mu12
  double sys_pp_mu12_J2_array[N_sys] = {sys_cFraction_pp_mu12_J2, sys_lowerBound_pp_mu12_J2, sys_bEnhance_pp_mu12_J2, sys_cEnhance_pp_mu12_J2, sys_JERsmear_pp_mu12_J2, sys_centShift_pp_mu12_J2, sys_total_pp_mu12_J2};
  double sys_pp_mu12_J3_array[N_sys] = {sys_cFraction_pp_mu12_J3, sys_lowerBound_pp_mu12_J3, sys_bEnhance_pp_mu12_J3, sys_cEnhance_pp_mu12_J3, sys_JERsmear_pp_mu12_J3, sys_centShift_pp_mu12_J3, sys_total_pp_mu12_J3};
  double sys_pp_mu12_J4_array[N_sys] = {sys_cFraction_pp_mu12_J4, sys_lowerBound_pp_mu12_J4, sys_bEnhance_pp_mu12_J4, sys_cEnhance_pp_mu12_J4, sys_JERsmear_pp_mu12_J4, sys_centShift_pp_mu12_J4, sys_total_pp_mu12_J4};

  // PbPb 30-90%
  // -- mu5
  double sys_PbPb_mu5_C2_J2_array[N_sys] = {sys_cFraction_PbPb_mu5_C2_J2, sys_lowerBound_PbPb_mu5_C2_J2, sys_bEnhance_PbPb_mu5_C2_J2, sys_cEnhance_PbPb_mu5_C2_J2, sys_JERsmear_PbPb_mu5_C2_J2, sys_centShift_PbPb_mu5_C2_J2, sys_total_PbPb_mu5_C2_J2};
  double sys_PbPb_mu5_C2_J3_array[N_sys] = {sys_cFraction_PbPb_mu5_C2_J3, sys_lowerBound_PbPb_mu5_C2_J3, sys_bEnhance_PbPb_mu5_C2_J3, sys_cEnhance_PbPb_mu5_C2_J3, sys_JERsmear_PbPb_mu5_C2_J3, sys_centShift_PbPb_mu5_C2_J3, sys_total_PbPb_mu5_C2_J3};
  double sys_PbPb_mu5_C2_J4_array[N_sys] = {sys_cFraction_PbPb_mu5_C2_J4, sys_lowerBound_PbPb_mu5_C2_J4, sys_bEnhance_PbPb_mu5_C2_J4, sys_cEnhance_PbPb_mu5_C2_J4, sys_JERsmear_PbPb_mu5_C2_J4, sys_centShift_PbPb_mu5_C2_J4, sys_total_PbPb_mu5_C2_J4};
  // -- mu7
  double sys_PbPb_mu7_C2_J2_array[N_sys] = {sys_cFraction_PbPb_mu7_C2_J2, sys_lowerBound_PbPb_mu7_C2_J2, sys_bEnhance_PbPb_mu7_C2_J2, sys_cEnhance_PbPb_mu7_C2_J2, sys_JERsmear_PbPb_mu7_C2_J2, sys_centShift_PbPb_mu7_C2_J2, sys_total_PbPb_mu7_C2_J2};
  double sys_PbPb_mu7_C2_J3_array[N_sys] = {sys_cFraction_PbPb_mu7_C2_J3, sys_lowerBound_PbPb_mu7_C2_J3, sys_bEnhance_PbPb_mu7_C2_J3, sys_cEnhance_PbPb_mu7_C2_J3, sys_JERsmear_PbPb_mu7_C2_J3, sys_centShift_PbPb_mu7_C2_J3, sys_total_PbPb_mu7_C2_J3};
  double sys_PbPb_mu7_C2_J4_array[N_sys] = {sys_cFraction_PbPb_mu7_C2_J4, sys_lowerBound_PbPb_mu7_C2_J4, sys_bEnhance_PbPb_mu7_C2_J4, sys_cEnhance_PbPb_mu7_C2_J4, sys_JERsmear_PbPb_mu7_C2_J4, sys_centShift_PbPb_mu7_C2_J4, sys_total_PbPb_mu7_C2_J4};
  // -- mu12
  double sys_PbPb_mu12_C2_J2_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J2, sys_lowerBound_PbPb_mu12_C2_J2, sys_bEnhance_PbPb_mu12_C2_J2, sys_cEnhance_PbPb_mu12_C2_J2, sys_JERsmear_PbPb_mu12_C2_J2, sys_centShift_PbPb_mu12_C2_J2, sys_total_PbPb_mu12_C2_J2};
  double sys_PbPb_mu12_C2_J3_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J3, sys_lowerBound_PbPb_mu12_C2_J3, sys_bEnhance_PbPb_mu12_C2_J3, sys_cEnhance_PbPb_mu12_C2_J3, sys_JERsmear_PbPb_mu12_C2_J3, sys_centShift_PbPb_mu12_C2_J3, sys_total_PbPb_mu12_C2_J3};
  double sys_PbPb_mu12_C2_J4_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J4, sys_lowerBound_PbPb_mu12_C2_J4, sys_bEnhance_PbPb_mu12_C2_J4, sys_cEnhance_PbPb_mu12_C2_J4, sys_JERsmear_PbPb_mu12_C2_J4, sys_centShift_PbPb_mu12_C2_J4, sys_total_PbPb_mu12_C2_J4};

  // PbPb 0-30%
  // -- mu5
  double sys_PbPb_mu5_C1_J2_array[N_sys] = {sys_cFraction_PbPb_mu5_C1_J2, sys_lowerBound_PbPb_mu5_C1_J2, sys_bEnhance_PbPb_mu5_C1_J2, sys_cEnhance_PbPb_mu5_C1_J2, sys_JERsmear_PbPb_mu5_C1_J2, sys_centShift_PbPb_mu5_C1_J2, sys_total_PbPb_mu5_C1_J2};
  double sys_PbPb_mu5_C1_J3_array[N_sys] = {sys_cFraction_PbPb_mu5_C1_J3, sys_lowerBound_PbPb_mu5_C1_J3, sys_bEnhance_PbPb_mu5_C1_J3, sys_cEnhance_PbPb_mu5_C1_J3, sys_JERsmear_PbPb_mu5_C1_J3, sys_centShift_PbPb_mu5_C1_J3, sys_total_PbPb_mu5_C1_J3};
  double sys_PbPb_mu5_C1_J4_array[N_sys] = {sys_cFraction_PbPb_mu5_C1_J4, sys_lowerBound_PbPb_mu5_C1_J4, sys_bEnhance_PbPb_mu5_C1_J4, sys_cEnhance_PbPb_mu5_C1_J4, sys_JERsmear_PbPb_mu5_C1_J4, sys_centShift_PbPb_mu5_C1_J4, sys_total_PbPb_mu5_C1_J4};
  // -- mu7
  double sys_PbPb_mu7_C1_J2_array[N_sys] = {sys_cFraction_PbPb_mu7_C1_J2, sys_lowerBound_PbPb_mu7_C1_J2, sys_bEnhance_PbPb_mu7_C1_J2, sys_cEnhance_PbPb_mu7_C1_J2, sys_JERsmear_PbPb_mu7_C1_J2, sys_centShift_PbPb_mu7_C1_J2, sys_total_PbPb_mu7_C1_J2};
  double sys_PbPb_mu7_C1_J3_array[N_sys] = {sys_cFraction_PbPb_mu7_C1_J3, sys_lowerBound_PbPb_mu7_C1_J3, sys_bEnhance_PbPb_mu7_C1_J3, sys_cEnhance_PbPb_mu7_C1_J3, sys_JERsmear_PbPb_mu7_C1_J3, sys_centShift_PbPb_mu7_C1_J3, sys_total_PbPb_mu7_C1_J3};
  double sys_PbPb_mu7_C1_J4_array[N_sys] = {sys_cFraction_PbPb_mu7_C1_J4, sys_lowerBound_PbPb_mu7_C1_J4, sys_bEnhance_PbPb_mu7_C1_J4, sys_cEnhance_PbPb_mu7_C1_J4, sys_JERsmear_PbPb_mu7_C1_J4, sys_centShift_PbPb_mu7_C1_J4, sys_total_PbPb_mu7_C1_J4};
  // -- mu12
  double sys_PbPb_mu12_C1_J2_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J2, sys_lowerBound_PbPb_mu12_C1_J2, sys_bEnhance_PbPb_mu12_C1_J2, sys_cEnhance_PbPb_mu12_C1_J2, sys_JERsmear_PbPb_mu12_C1_J2, sys_centShift_PbPb_mu12_C1_J2, sys_total_PbPb_mu12_C1_J2};
  double sys_PbPb_mu12_C1_J3_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J3, sys_lowerBound_PbPb_mu12_C1_J3, sys_bEnhance_PbPb_mu12_C1_J3, sys_cEnhance_PbPb_mu12_C1_J3, sys_JERsmear_PbPb_mu12_C1_J3, sys_centShift_PbPb_mu12_C1_J3, sys_total_PbPb_mu12_C1_J3};
  double sys_PbPb_mu12_C1_J4_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J4, sys_lowerBound_PbPb_mu12_C1_J4, sys_bEnhance_PbPb_mu12_C1_J4, sys_cEnhance_PbPb_mu12_C1_J4, sys_JERsmear_PbPb_mu12_C1_J4, sys_centShift_PbPb_mu12_C1_J4, sys_total_PbPb_mu12_C1_J4};
    
    


  
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
    if(do_mu5) h0_sys_J2->SetBinContent(i,sys_pp_mu5_J2_array[i-1]);
    else if(do_mu7) h0_sys_J2->SetBinContent(i,sys_pp_mu7_J2_array[i-1]);
    else if(do_mu12) h0_sys_J2->SetBinContent(i,sys_pp_mu12_J2_array[i-1]);
    else{};
    h0_sys_J2->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }


  h0_sys_J2->GetXaxis()->SetTitleSize(0.06);
  // h0_sys_J2->SetBarWidth(new_bar_width);
  // h0_sys_J2->SetBarOffset(new_bar_offset);
  h0_sys_J2->SetTitle("");
  h0_sys_J2->Draw("b");





  la->SetTextSize(0.035);

  la->DrawLatexNDC(0.535,0.8,"60 GeV < #font[52]{p}_{T}^{jet} < 80 GeV");
  
  TH1D *h1_sys_J2 = new TH1D("h1_sys_J2","h1_sys_J2",N_sys,0,1.0*N_sys);
  h1_sys_J2->SetFillColor(kRed-4);
  h1_sys_J2->SetBarWidth(0.3);
  h1_sys_J2->SetBarOffset(0.35);
  h1_sys_J2->SetStats(0);
  h1_sys_J2->SetMinimum(0.0);
  h1_sys_J2->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    if(do_mu5) h1_sys_J2->SetBinContent(i,sys_PbPb_mu5_C2_J2_array[i-1]);
    else if(do_mu7) h1_sys_J2->SetBinContent(i,sys_PbPb_mu7_C2_J2_array[i-1]);
    else if(do_mu12) h1_sys_J2->SetBinContent(i,sys_PbPb_mu12_C2_J2_array[i-1]);
    else{};
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
    if(do_mu5) h2_sys_J2->SetBinContent(i,sys_PbPb_mu5_C1_J2_array[i-1]);
    else if(do_mu7) h2_sys_J2->SetBinContent(i,sys_PbPb_mu7_C1_J2_array[i-1]);
    else if(do_mu12) h2_sys_J2->SetBinContent(i,sys_PbPb_mu12_C1_J2_array[i-1]);
    else{};
    h2_sys_J2->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J2->SetBarWidth(new_bar_width);
  // h2_sys_J2->SetBarOffset(new_bar_offset);
  h2_sys_J2->Draw("b same");

  TLegend *leg = new TLegend(0.25,0.7,0.4,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(h0_sys_J2,"pp","f");
  leg->AddEntry(h1_sys_J2,"PbPb 30-90%","f");
  leg->AddEntry(h2_sys_J2,"PbPb 0-30%","f");
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
    if(do_mu5) h0_sys_J3->SetBinContent(i,sys_pp_mu5_J3_array[i-1]);
    else if(do_mu7) h0_sys_J3->SetBinContent(i,sys_pp_mu7_J3_array[i-1]);
    else if(do_mu12) h0_sys_J3->SetBinContent(i,sys_pp_mu12_J3_array[i-1]);
    else{};
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
    if(do_mu5) h1_sys_J3->SetBinContent(i,sys_PbPb_mu5_C2_J3_array[i-1]);
    else if(do_mu7) h1_sys_J3->SetBinContent(i,sys_PbPb_mu7_C2_J3_array[i-1]);
    else if(do_mu12) h1_sys_J3->SetBinContent(i,sys_PbPb_mu12_C2_J3_array[i-1]);
    else{};
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
    if(do_mu5) h2_sys_J3->SetBinContent(i,sys_PbPb_mu5_C1_J3_array[i-1]);
    else if(do_mu7) h2_sys_J3->SetBinContent(i,sys_PbPb_mu7_C1_J3_array[i-1]);
    else if(do_mu12) h2_sys_J3->SetBinContent(i,sys_PbPb_mu12_C1_J3_array[i-1]);
    else{};
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
    if(do_mu5) h0_sys_J4->SetBinContent(i,sys_pp_mu5_J4_array[i-1]);
    else if(do_mu7) h0_sys_J4->SetBinContent(i,sys_pp_mu7_J4_array[i-1]);
    else if(do_mu12) h0_sys_J4->SetBinContent(i,sys_pp_mu12_J4_array[i-1]);
    else{};
    h0_sys_J4->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h0_sys_J4->GetXaxis()->SetTitleSize(0.04);
  h0_sys_J4->SetTitle("");
  // h0_sys_J4->SetBarWidth(new_bar_width);
  // h0_sys_J4->SetBarOffset(new_bar_offset);
  h0_sys_J4->Draw("b");

  la->DrawLatexNDC(0.535,0.8,"120 GeV < #font[52]{p}_{T}^{jet} < 200 GeV");
  
  TH1D *h1_sys_J4 = new TH1D("h1_sys_J4","h1_sys_J4",N_sys,0,1.0*N_sys);
  h1_sys_J4->SetFillColor(kRed-4);
  h1_sys_J4->SetBarWidth(0.3);
  h1_sys_J4->SetBarOffset(0.35);
  h1_sys_J4->SetStats(0);
  h1_sys_J4->SetMinimum(0.0);
  h1_sys_J4->SetMaximum(0.3);

  for(int i = 1; i <= N_sys; i++){
    if(do_mu5) h1_sys_J4->SetBinContent(i,sys_PbPb_mu5_C2_J4_array[i-1]);
    else if(do_mu7) h1_sys_J4->SetBinContent(i,sys_PbPb_mu7_C2_J4_array[i-1]);
    else if(do_mu12) h1_sys_J4->SetBinContent(i,sys_PbPb_mu12_C2_J4_array[i-1]);
    else{};
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
    if(do_mu5) h2_sys_J4->SetBinContent(i,sys_PbPb_mu5_C1_J4_array[i-1]);
    else if(do_mu7) h2_sys_J4->SetBinContent(i,sys_PbPb_mu7_C1_J4_array[i-1]);
    else if(do_mu12) h2_sys_J4->SetBinContent(i,sys_PbPb_mu12_C1_J4_array[i-1]);
    else{};
    h2_sys_J4->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J4->SetBarWidth(new_bar_width);
  // h2_sys_J4->SetBarOffset(new_bar_offset);
  h2_sys_J4->Draw("b same");
  leg->Draw();


  if(do_mu5){
    canv_J2->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu5_J2.pdf");
    canv_J3->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu5_J3.pdf");
    canv_J4->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu5_J4.pdf");
  }
  else if(do_mu7){
    canv_J2->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu7_J2.pdf");
    canv_J3->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu7_J3.pdf");
    canv_J4->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu7_J4.pdf");
  }
  else if(do_mu12){
    canv_J2->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu12_J2.pdf");
    canv_J3->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu12_J3.pdf");
    canv_J4->SaveAs("/home/clayton/Analysis/code/bJet_analysis/systematics/nicePlots/mu12_J4.pdf");
  }

  // // c-fraction-variation
  // double input_pp_cFrac_J2 = 0;
  // double input_pp_cFrac_J3 = 0;
  // double input_pp_cFrac_J4 = 0;

  // double input_C2_cFrac_J2 = 0;
  // double input_C2_cFrac_J3 = 0;
  // double input_C2_cFrac_J4 = 0;

  // double input_C1_cFrac_J2 = 0;
  // double input_C1_cFrac_J3 = 0;
  // double input_C1_cFrac_J4 = 0;

  // // fit-lower-bound
  // double input_pp_lowerBound_J2 = 0;
  // double input_pp_lowerBound_J3 = 0;
  // double input_pp_lowerBound_J4 = 0;

  // double input_C2_lowerBound_J2 = 0;
  // double input_C2_lowerBound_J3 = 0;
  // double input_C2_lowerBound_J4 = 0;

  // double input_C1_lowerBound_J2 = 0;
  // double input_C1_lowerBound_J3 = 0;
  // double input_C1_lowerBound_J4 = 0;

  // // b-template-enhancement
  // double input_pp_bEnhance_J2 = 0;
  // double input_pp_bEnhance_J3 = 0;
  // double input_pp_bEnhance_J4 = 0;

  // double input_C2_bEnhance_J2 = 0;
  // double input_C2_bEnhance_J3 = 0;
  // double input_C2_bEnhance_J4 = 0;

  // double input_C1_bEnhance_J2 = 0;
  // double input_C1_bEnhance_J3 = 0;
  // double input_C1_bEnhance_J4 = 0;

  // // c-template-enhancement
  // double input_pp_cEnhance_J2 = 0;
  // double input_pp_cEnhance_J3 = 0;
  // double input_pp_cEnhance_J4 = 0;

  // double input_C2_cEnhance_J2 = 0;
  // double input_C2_cEnhance_J3 = 0;
  // double input_C2_cEnhance_J4 = 0;

  // double input_C1_cEnhance_J2 = 0;
  // double input_C1_cEnhance_J3 = 0;
  // double input_C1_cEnhance_J4 = 0;

  // // JER-smear
  // double input_pp_JERsmear_J2 = 0;
  // double input_pp_JERsmear_J3 = 0;
  // double input_pp_JERsmear_J4 = 0;

  // double input_C2_JERsmear_J2 = 0;
  // double input_C2_JERsmear_J3 = 0;
  // double input_C2_JERsmear_J4 = 0;

  // double input_C1_JERsmear_J2 = 0;
  // double input_C1_JERsmear_J3 = 0;
  // double input_C1_JERsmear_J4 = 0;

  // // centrality-shift
  // double input_pp_centShift_J2 = 0;
  // double input_pp_centShift_J3 = 0;
  // double input_pp_centShift_J4 = 0;

  // double input_C2_centShift_J2 = 0;
  // double input_C2_centShift_J3 = 0;
  // double input_C2_centShift_J4 = 0;

  // double input_C1_centShift_J2 = 0;
  // double input_C1_centShift_J3 = 0;
  // double input_C1_centShift_J4 = 0;

  // if(do_mu5){
  //   input_pp_cFrac_J2 = sys_cFraction_pp_mu5_J2;
  //   input_pp_cFrac_J3 = sys_cFraction_pp_mu5_J3;
  //   input_pp_cFrac_J4 = sys_cFraction_pp_mu5_J4;

  //   input_C2_cFrac_J2 = sys_cFraction_C2_mu5_J2;
  //   input_C2_cFrac_J3 = sys_cFraction_C2_mu5_J3;
  //   input_C2_cFrac_J4 = sys_cFraction_C2_mu5_J4;

  //   input_C1_cFrac_J2 = sys_cFraction_C1_mu5_J2;
  //   input_C1_cFrac_J3 = sys_cFraction_C1_mu5_J3;
  //   input_C1_cFrac_J4 = sys_cFraction_C1_mu5_J4;

  //   input_pp_lowerBound_J2 = sys_lowerBound_pp_mu5_J2;
  //   input_pp_lowerBound_J3 = sys_lowerBound_pp_mu5_J3;
  //   input_pp_lowerBound_J4 = sys_lowerBound_pp_mu5_J4;

  //   input_C2_lowerBound_J2 = sys_lowerBound_C2_mu5_J2;
  //   input_C2_lowerBound_J3 = sys_lowerBound_C2_mu5_J3;
  //   input_C2_lowerBound_J4 = sys_lowerBound_C2_mu5_J4;

  //   input_C1_lowerBound_J2 = sys_lowerBound_C1_mu5_J2;
  //   input_C1_lowerBound_J3 = sys_lowerBound_C1_mu5_J3;
  //   input_C1_lowerBound_J4 = sys_lowerBound_C1_mu5_J4;

  //   input_pp_bEnhance_J2 = sys_bEnhance_pp_mu5_J2;
  //   input_pp_bEnhance_J3 = sys_bEnhance_pp_mu5_J3;
  //   input_pp_bEnhance_J4 = sys_bEnhance_pp_mu5_J4;

  //   input_C2_bEnhance_J2 = sys_bEnhance_C2_mu5_J2;
  //   input_C2_bEnhance_J3 = sys_bEnhance_C2_mu5_J3;
  //   input_C2_bEnhance_J4 = sys_bEnhance_C2_mu5_J4;

  //   input_C1_bEnhance_J2 = sys_bEnhance_C1_mu5_J2;
  //   input_C1_bEnhance_J3 = sys_bEnhance_C1_mu5_J3;
  //   input_C1_bEnhance_J4 = sys_bEnhance_C1_mu5_J4;

  //   input_pp_cEnhance_J2 = sys_cEnhance_pp_mu5_J2;
  //   input_pp_cEnhance_J3 = sys_cEnhance_pp_mu5_J3;
  //   input_pp_cEnhance_J4 = sys_cEnhance_pp_mu5_J4;

  //   input_C2_cEnhance_J2 = sys_cEnhance_C2_mu5_J2;
  //   input_C2_cEnhance_J3 = sys_cEnhance_C2_mu5_J3;
  //   input_C2_cEnhance_J4 = sys_cEnhance_C2_mu5_J4;

  //   input_C1_cEnhance_J2 = sys_cEnhance_C1_mu5_J2;
  //   input_C1_cEnhance_J3 = sys_cEnhance_C1_mu5_J3;
  //   input_C1_cEnhance_J4 = sys_cEnhance_C1_mu5_J4;

  //   input_pp_JERsmear_J2 = sys_JERsmear_pp_mu5_J2;
  //   input_pp_JERsmear_J3 = sys_JERsmear_pp_mu5_J3;
  //   input_pp_JERsmear_J4 = sys_JERsmear_pp_mu5_J4;

  //   input_C2_JERsmear_J2 = sys_JERsmear_C2_mu5_J2;
  //   input_C2_JERsmear_J3 = sys_JERsmear_C2_mu5_J3;
  //   input_C2_JERsmear_J4 = sys_JERsmear_C2_mu5_J4;

  //   input_C1_JERsmear_J2 = sys_JERsmear_C1_mu5_J2;
  //   input_C1_JERsmear_J3 = sys_JERsmear_C1_mu5_J3;
  //   input_C1_JERsmear_J4 = sys_JERsmear_C1_mu5_J4;
    
  //   input_pp_centShift_J2 = sys_centShift_pp_mu5_J2;
  //   input_pp_centShift_J3 = sys_centShift_pp_mu5_J3;
  //   input_pp_centShift_J4 = sys_centShift_pp_mu5_J4;

  //   input_C2_centShift_J2 = sys_centShift_C2_mu5_J2;
  //   input_C2_centShift_J3 = sys_centShift_C2_mu5_J3;
  //   input_C2_centShift_J4 = sys_centShift_C2_mu5_J4;

  //   input_C1_centShift_J2 = sys_centShift_C1_mu5_J2;
  //   input_C1_centShift_J3 = sys_centShift_C1_mu5_J3;
  //   input_C1_centShift_J4 = sys_centShift_C1_mu5_J4;
   
  // }

  // if(do_mu7){
  //   input_pp_cFrac_J2 = sys_cFraction_pp_mu7_J2;
  //   input_pp_cFrac_J3 = sys_cFraction_pp_mu7_J3;
  //   input_pp_cFrac_J4 = sys_cFraction_pp_mu7_J4;

  //   input_C2_cFrac_J2 = sys_cFraction_C2_mu7_J2;
  //   input_C2_cFrac_J3 = sys_cFraction_C2_mu7_J3;
  //   input_C2_cFrac_J4 = sys_cFraction_C2_mu7_J4;

  //   input_C1_cFrac_J2 = sys_cFraction_C1_mu7_J2;
  //   input_C1_cFrac_J3 = sys_cFraction_C1_mu7_J3;
  //   input_C1_cFrac_J4 = sys_cFraction_C1_mu7_J4;

  //   input_pp_lowerBound_J2 = sys_lowerBound_pp_mu7_J2;
  //   input_pp_lowerBound_J3 = sys_lowerBound_pp_mu7_J3;
  //   input_pp_lowerBound_J4 = sys_lowerBound_pp_mu7_J4;

  //   input_C2_lowerBound_J2 = sys_lowerBound_C2_mu7_J2;
  //   input_C2_lowerBound_J3 = sys_lowerBound_C2_mu7_J3;
  //   input_C2_lowerBound_J4 = sys_lowerBound_C2_mu7_J4;

  //   input_C1_lowerBound_J2 = sys_lowerBound_C1_mu7_J2;
  //   input_C1_lowerBound_J3 = sys_lowerBound_C1_mu7_J3;
  //   input_C1_lowerBound_J4 = sys_lowerBound_C1_mu7_J4;

  //   input_pp_bEnhance_J2 = sys_bEnhance_pp_mu7_J2;
  //   input_pp_bEnhance_J3 = sys_bEnhance_pp_mu7_J3;
  //   input_pp_bEnhance_J4 = sys_bEnhance_pp_mu7_J4;

  //   input_C2_bEnhance_J2 = sys_bEnhance_C2_mu7_J2;
  //   input_C2_bEnhance_J3 = sys_bEnhance_C2_mu7_J3;
  //   input_C2_bEnhance_J4 = sys_bEnhance_C2_mu7_J4;

  //   input_C1_bEnhance_J2 = sys_bEnhance_C1_mu7_J2;
  //   input_C1_bEnhance_J3 = sys_bEnhance_C1_mu7_J3;
  //   input_C1_bEnhance_J4 = sys_bEnhance_C1_mu7_J4;

  //   input_pp_cEnhance_J2 = sys_cEnhance_pp_mu7_J2;
  //   input_pp_cEnhance_J3 = sys_cEnhance_pp_mu7_J3;
  //   input_pp_cEnhance_J4 = sys_cEnhance_pp_mu7_J4;

  //   input_C2_cEnhance_J2 = sys_cEnhance_C2_mu7_J2;
  //   input_C2_cEnhance_J3 = sys_cEnhance_C2_mu7_J3;
  //   input_C2_cEnhance_J4 = sys_cEnhance_C2_mu7_J4;

  //   input_C1_cEnhance_J2 = sys_cEnhance_C1_mu7_J2;
  //   input_C1_cEnhance_J3 = sys_cEnhance_C1_mu7_J3;
  //   input_C1_cEnhance_J4 = sys_cEnhance_C1_mu7_J4;

  //   input_pp_JERsmear_J2 = sys_JERsmear_pp_mu7_J2;
  //   input_pp_JERsmear_J3 = sys_JERsmear_pp_mu7_J3;
  //   input_pp_JERsmear_J4 = sys_JERsmear_pp_mu7_J4;

  //   input_C2_JERsmear_J2 = sys_JERsmear_C2_mu7_J2;
  //   input_C2_JERsmear_J3 = sys_JERsmear_C2_mu7_J3;
  //   input_C2_JERsmear_J4 = sys_JERsmear_C2_mu7_J4;

  //   input_C1_JERsmear_J2 = sys_JERsmear_C1_mu7_J2;
  //   input_C1_JERsmear_J3 = sys_JERsmear_C1_mu7_J3;
  //   input_C1_JERsmear_J4 = sys_JERsmear_C1_mu7_J4;
    
  //   input_pp_centShift_J2 = sys_centShift_pp_mu7_J2;
  //   input_pp_centShift_J3 = sys_centShift_pp_mu7_J3;
  //   input_pp_centShift_J4 = sys_centShift_pp_mu7_J4;

  //   input_C2_centShift_J2 = sys_centShift_C2_mu7_J2;
  //   input_C2_centShift_J3 = sys_centShift_C2_mu7_J3;
  //   input_C2_centShift_J4 = sys_centShift_C2_mu7_J4;

  //   input_C1_centShift_J2 = sys_centShift_C1_mu7_J2;
  //   input_C1_centShift_J3 = sys_centShift_C1_mu7_J3;
  //   input_C1_centShift_J4 = sys_centShift_C1_mu7_J4;

  // }

  // if(do_mu12){
  //   input_pp_cFrac_J2 = sys_cFraction_pp_mu12_J2;
  //   input_pp_cFrac_J3 = sys_cFraction_pp_mu12_J3;
  //   input_pp_cFrac_J4 = sys_cFraction_pp_mu12_J4;

  //   input_C2_cFrac_J2 = sys_cFraction_C2_mu12_J2;
  //   input_C2_cFrac_J3 = sys_cFraction_C2_mu12_J3;
  //   input_C2_cFrac_J4 = sys_cFraction_C2_mu12_J4;

  //   input_C1_cFrac_J2 = sys_cFraction_C1_mu12_J2;
  //   input_C1_cFrac_J3 = sys_cFraction_C1_mu12_J3;
  //   input_C1_cFrac_J4 = sys_cFraction_C1_mu12_J4;

  //   input_pp_lowerBound_J2 = sys_lowerBound_pp_mu12_J2;
  //   input_pp_lowerBound_J3 = sys_lowerBound_pp_mu12_J3;
  //   input_pp_lowerBound_J4 = sys_lowerBound_pp_mu12_J4;

  //   input_C2_lowerBound_J2 = sys_lowerBound_C2_mu12_J2;
  //   input_C2_lowerBound_J3 = sys_lowerBound_C2_mu12_J3;
  //   input_C2_lowerBound_J4 = sys_lowerBound_C2_mu12_J4;

  //   input_C1_lowerBound_J2 = sys_lowerBound_C1_mu12_J2;
  //   input_C1_lowerBound_J3 = sys_lowerBound_C1_mu12_J3;
  //   input_C1_lowerBound_J4 = sys_lowerBound_C1_mu12_J4;

  //   input_pp_bEnhance_J2 = sys_bEnhance_pp_mu12_J2;
  //   input_pp_bEnhance_J3 = sys_bEnhance_pp_mu12_J3;
  //   input_pp_bEnhance_J4 = sys_bEnhance_pp_mu12_J4;

  //   input_C2_bEnhance_J2 = sys_bEnhance_C2_mu12_J2;
  //   input_C2_bEnhance_J3 = sys_bEnhance_C2_mu12_J3;
  //   input_C2_bEnhance_J4 = sys_bEnhance_C2_mu12_J4;

  //   input_C1_bEnhance_J2 = sys_bEnhance_C1_mu12_J2;
  //   input_C1_bEnhance_J3 = sys_bEnhance_C1_mu12_J3;
  //   input_C1_bEnhance_J4 = sys_bEnhance_C1_mu12_J4;

  //   input_pp_cEnhance_J2 = sys_cEnhance_pp_mu12_J2;
  //   input_pp_cEnhance_J3 = sys_cEnhance_pp_mu12_J3;
  //   input_pp_cEnhance_J4 = sys_cEnhance_pp_mu12_J4;

  //   input_C2_cEnhance_J2 = sys_cEnhance_C2_mu12_J2;
  //   input_C2_cEnhance_J3 = sys_cEnhance_C2_mu12_J3;
  //   input_C2_cEnhance_J4 = sys_cEnhance_C2_mu12_J4;

  //   input_C1_cEnhance_J2 = sys_cEnhance_C1_mu12_J2;
  //   input_C1_cEnhance_J3 = sys_cEnhance_C1_mu12_J3;
  //   input_C1_cEnhance_J4 = sys_cEnhance_C1_mu12_J4;

  //   input_pp_JERsmear_J2 = sys_JERsmear_pp_mu12_J2;
  //   input_pp_JERsmear_J3 = sys_JERsmear_pp_mu12_J3;
  //   input_pp_JERsmear_J4 = sys_JERsmear_pp_mu12_J4;

  //   input_C2_JERsmear_J2 = sys_JERsmear_C2_mu12_J2;
  //   input_C2_JERsmear_J3 = sys_JERsmear_C2_mu12_J3;
  //   input_C2_JERsmear_J4 = sys_JERsmear_C2_mu12_J4;

  //   input_C1_JERsmear_J2 = sys_JERsmear_C1_mu12_J2;
  //   input_C1_JERsmear_J3 = sys_JERsmear_C1_mu12_J3;
  //   input_C1_JERsmear_J4 = sys_JERsmear_C1_mu12_J4;
    
  //   input_pp_centShift_J2 = sys_centShift_pp_mu12_J2;
  //   input_pp_centShift_J3 = sys_centShift_pp_mu12_J3;
  //   input_pp_centShift_J4 = sys_centShift_pp_mu12_J4;

  //   input_C2_centShift_J2 = sys_centShift_C2_mu12_J2;
  //   input_C2_centShift_J3 = sys_centShift_C2_mu12_J3;
  //   input_C2_centShift_J4 = sys_centShift_C2_mu12_J4;

  //   input_C1_centShift_J2 = sys_centShift_C1_mu12_J2;
  //   input_C1_centShift_J3 = sys_centShift_C1_mu12_J3;
  //   input_C1_centShift_J4 = sys_centShift_C1_mu12_J4;

  // }

  // THStack *pp_stack, *C2_stack, *C1_stack;
  // const int N_jetPtAxisEdges = 4;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {60,80,120,200};
  // TH1D *h_pp_cFraction = new TH1D("h_pp_cFraction","h_pp_cFraction",N_jetPtAxisEdges-1,jetPtAxisEdges);
  // TH1D *h_pp_lowerBound = new TH1D("h_pp_lowerBound","h_pp_lowerBound",N_jetPtAxisEdges-1,jetPtAxisEdges);
  // TH1D *h_pp_bEnhance = new TH1D("h_pp_bEnhance","h_pp_bEnhance",N_jetPtAxisEdges-1,jetPtAxisEdges);
  // TH1D *h_pp_cEnhance = new TH1D("h_pp_cEnhance","h_pp_cEnhance",N_jetPtAxisEdges-1,jetPtAxisEdges);
  // TH1D *h_pp_JERsmear = new TH1D("h_pp_JERsmear","h_pp_JERsmear",N_jetPtAxisEdges-1,jetPtAxisEdges);
  // TH1D *h_pp_centShift = new TH1D("h_pp_centShift","h_pp_centShift",N_jetPtAxisEdges-1,jetPtAxisEdges);
  
  // h_pp_cFraction->SetBinContent(1,input_pp_cFrac_J2);
  // h_pp_cFraction->SetBinContent(2,input_pp_cFrac_J3);
  // h_pp_cFraction->SetBinContent(3,input_pp_cFrac_J4);

  // h_pp_lowerBound->SetBinContent(1,input_pp_lowerBound_J2);
  // h_pp_lowerBound->SetBinContent(2,input_pp_lowerBound_J3);
  // h_pp_lowerBound->SetBinContent(3,input_pp_lowerBound_J4);

  // h_pp_bEnhance->SetBinContent(1,input_pp_bEnhance_J2);
  // h_pp_bEnhance->SetBinContent(2,input_pp_bEnhance_J3);
  // h_pp_bEnhance->SetBinContent(3,input_pp_bEnhance_J4);

  // h_pp_cEnhance->SetBinContent(1,input_pp_cEnhance_J2);
  // h_pp_cEnhance->SetBinContent(2,input_pp_cEnhance_J3);
  // h_pp_cEnhance->SetBinContent(3,input_pp_cEnhance_J4);

  // h_pp_JERsmear->SetBinContent(1,input_pp_JERsmear_J2);
  // h_pp_JERsmear->SetBinContent(2,input_pp_JERsmear_J3);
  // h_pp_JERsmear->SetBinContent(3,input_pp_JERsmear_J4);

  // h_pp_centShift->SetBinContent(1,input_pp_centShift_J2);
  // h_pp_centShift->SetBinContent(2,input_pp_centShift_J3);
  // h_pp_centShift->SetBinContent(3,input_pp_centShift_J4);

  // h_pp_cFraction->SetFillColorAlpha(kBlue-4);
  // h_pp_lowerBound->SetFillColorAlpha(kRed-4);
  // h_pp_bEnhance->SetFillColorAlpha(kGreen+2);
  // h_pp_cEnhance->SetFillColorAlpha(kMagenta);
  // h_pp_JERsmear->SetFillColorAlpha(kOrange);
  // h_pp_centShift->SetFillColorAlpha(kBlue+4);

  // pp_stack->Add();
  
}
