// Systematics results

// ------------- c-fraction-variation systematics ------------------

// PYTHIA
double sys_cFraction_PYTHIA_J2 = 0.00956138;
double sys_cFraction_PYTHIA_J3 = 0.0282143;
double sys_cFraction_PYTHIA_J4 = 0.0575053;

// PYTHIA+HYDJET 30-90%
double sys_cFraction_PYTHIAHYDJET_C2_J2 = 0.00571947;
double sys_cFraction_PYTHIAHYDJET_C2_J3 = 0.0214228;
double sys_cFraction_PYTHIAHYDJET_C2_J4 = 0.0384951;

// PYTHIA+HYDJET 0-30%
double sys_cFraction_PYTHIAHYDJET_C1_J2 = 0.0534973;
double sys_cFraction_PYTHIAHYDJET_C1_J3 = 0.00102558;
double sys_cFraction_PYTHIAHYDJET_C1_J4 = 0.0387503;


// ------------- fit-lower-bound systematics ------------------

// pp
double sys_lowerBound_pp_J2 = 0.0104906;
double sys_lowerBound_pp_J3 = 0.0101662;
double sys_lowerBound_pp_J4 = 0.00151101;

// PbPb 30-90%
double sys_lowerBound_PbPb_C2_J2 = 0.0188855;
double sys_lowerBound_PbPb_C2_J3 = 0.016958;
double sys_lowerBound_PbPb_C2_J4 = 0.0991;

// PbPb 0-30%
double sys_lowerBound_PbPb_C1_J2 = 0.0321734;
double sys_lowerBound_PbPb_C1_J3 = 0.0216787;
double sys_lowerBound_PbPb_C1_J4 = 0.0693144;


// ------------- b-enhancement systematics ------------------

// PYTHIA
double sys_bEnhance_PYTHIA_J2 = 0.0;
double sys_bEnhance_PYTHIA_J3 = 0.0;
double sys_bEnhance_PYTHIA_J4 = 0.0;

// PYTHIAHYDJET 30-90%
//double sys_bEnhance_PYTHIAHYDJET_C2_J2 = 0.0443665;
//double sys_bEnhance_PYTHIAHYDJET_C2_J3 = 0.017151;

double sys_bEnhance_PYTHIAHYDJET_C2_J2 = 0.0516102; // conservative estimate
double sys_bEnhance_PYTHIAHYDJET_C2_J3 = 0.0516102; // conservative estimate
double sys_bEnhance_PYTHIAHYDJET_C2_J4 = 0.0516102;

// PYTHIAHYDJET 0-30%
//double sys_bEnhance_PYTHIAHYDJET_C1_J2 = 0.00810496;
//double sys_bEnhance_PYTHIAHYDJET_C1_J3 = 0.0218218;

double sys_bEnhance_PYTHIAHYDJET_C1_J2 = 0.0218218; // conservative estimate
double sys_bEnhance_PYTHIAHYDJET_C1_J3 = 0.0218218; // conservative estimate
double sys_bEnhance_PYTHIAHYDJET_C1_J4 = 0.0218218;

// ------------- c-enhancement systematics ------------------

// PYTHIA
double sys_cEnhance_PYTHIA_J2 = 0.0;
double sys_cEnhance_PYTHIA_J3 = 0.0;
double sys_cEnhance_PYTHIA_J4 = 0.0;

// PYTHIAHYDJET 30-90%
//double sys_cEnhance_PYTHIAHYDJET_C2_J2 = 0.0435187;
//double sys_cEnhance_PYTHIAHYDJET_C2_J3 = 0.00599605;

double sys_cEnhance_PYTHIAHYDJET_C2_J2 = 0.103233; // conservative estimate
double sys_cEnhance_PYTHIAHYDJET_C2_J3 = 0.103233; // conservative estimate
double sys_cEnhance_PYTHIAHYDJET_C2_J4 = 0.103233;

// PYTHIAHYDJET 0-30%
//double sys_cEnhance_PYTHIAHYDJET_C1_J2 = 0.0041745;
//double sys_cEnhance_PYTHIAHYDJET_C1_J3 = 0.0120317;
//double sys_cEnhance_PYTHIAHYDJET_C1_J4 = 0.0585442;

double sys_cEnhance_PYTHIAHYDJET_C1_J2 = 0.0585442; // conservative estimate
double sys_cEnhance_PYTHIAHYDJET_C1_J3 = 0.0585442; // conservative estimate
double sys_cEnhance_PYTHIAHYDJET_C1_J4 = 0.0585442;



// ------------- JER systematics ------------------

// PYTHIA
double sys_JER_PYTHIA_J2 = 0.00281898;
double sys_JER_PYTHIA_J3 = 0.00142284;
double sys_JER_PYTHIA_J4 = 0.0370289;

// PYTHIAHYDJET 30-90%
double sys_JER_PYTHIAHYDJET_C2_J2 = 0.0058656;
double sys_JER_PYTHIAHYDJET_C2_J3 = 0.00519364;
double sys_JER_PYTHIAHYDJET_C2_J4 = 0.0134687;

// PYTHIAHYDJET 0-30%
double sys_JER_PYTHIAHYDJET_C1_J2 = 0.0737484;
double sys_JER_PYTHIAHYDJET_C1_J3 = 0.0395018;
double sys_JER_PYTHIAHYDJET_C1_J4 = 0.0995807;


// ------------ centrality shift (2%) -------------------
// PYTHIA
double sys_centShift_PYTHIA_J2 = 0.0;
double sys_centShift_PYTHIA_J3 = 0.0;
double sys_centShift_PYTHIA_J4 = 0.0;

// PYTHIAHYDJET 30-90%
double sys_centShift_PYTHIAHYDJET_C2_J2 = 0.0325818 ;
double sys_centShift_PYTHIAHYDJET_C2_J3 = 0.0681032 ;
double sys_centShift_PYTHIAHYDJET_C2_J4 = 0.021499 ;

// PYTHIAHYDJET 0-30%
double sys_centShift_PYTHIAHYDJET_C1_J2 = 0.100813 ;
double sys_centShift_PYTHIAHYDJET_C1_J3 = 0.0478048 ;
double sys_centShift_PYTHIAHYDJET_C1_J4 = 0.077617 ;

double sys_total_pp_J2 = TMath::Sqrt(sys_cFraction_PYTHIA_J2*sys_cFraction_PYTHIA_J2 +
				     sys_lowerBound_pp_J2*sys_lowerBound_pp_J2 +
				     sys_bEnhance_PYTHIA_J2*sys_bEnhance_PYTHIA_J2 +
				     sys_cEnhance_PYTHIA_J2*sys_cEnhance_PYTHIA_J2 +
				     sys_JER_PYTHIA_J2*sys_JER_PYTHIA_J2 +
				     sys_centShift_PYTHIA_J2*sys_centShift_PYTHIA_J2);

double sys_total_pp_J3 = TMath::Sqrt(sys_cFraction_PYTHIA_J3*sys_cFraction_PYTHIA_J3 +
				     sys_lowerBound_pp_J3*sys_lowerBound_pp_J3 +
				     sys_bEnhance_PYTHIA_J3*sys_bEnhance_PYTHIA_J3 +
				     sys_cEnhance_PYTHIA_J3*sys_cEnhance_PYTHIA_J3 +
				     sys_JER_PYTHIA_J3*sys_JER_PYTHIA_J3 +
				     sys_centShift_PYTHIA_J3*sys_centShift_PYTHIA_J3);

double sys_total_pp_J4 = TMath::Sqrt(sys_cFraction_PYTHIA_J4*sys_cFraction_PYTHIA_J4 +
				     sys_lowerBound_pp_J4*sys_lowerBound_pp_J4 +
				     sys_bEnhance_PYTHIA_J4*sys_bEnhance_PYTHIA_J4 +
				     sys_cEnhance_PYTHIA_J4*sys_cEnhance_PYTHIA_J4 +
				     sys_JER_PYTHIA_J4*sys_JER_PYTHIA_J4 +
				     sys_centShift_PYTHIA_J4*sys_centShift_PYTHIA_J4);

double sys_total_PbPb_C2_J2 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C2_J2*sys_cFraction_PYTHIAHYDJET_C2_J2 +
					  sys_lowerBound_PbPb_C2_J2*sys_lowerBound_PbPb_C2_J2 +
					  sys_bEnhance_PYTHIAHYDJET_C2_J2*sys_bEnhance_PYTHIAHYDJET_C2_J2 +
					  sys_cEnhance_PYTHIAHYDJET_C2_J2*sys_cEnhance_PYTHIAHYDJET_C2_J2 +
					  sys_JER_PYTHIAHYDJET_C2_J2*sys_JER_PYTHIAHYDJET_C2_J2 +
					  sys_centShift_PYTHIAHYDJET_C2_J2*sys_centShift_PYTHIAHYDJET_C2_J2);

double sys_total_PbPb_C2_J3 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C2_J3*sys_cFraction_PYTHIAHYDJET_C2_J3 +
					  sys_lowerBound_PbPb_C2_J3*sys_lowerBound_PbPb_C2_J3 +
					  sys_bEnhance_PYTHIAHYDJET_C2_J3*sys_bEnhance_PYTHIAHYDJET_C2_J3 +
					  sys_cEnhance_PYTHIAHYDJET_C2_J3*sys_cEnhance_PYTHIAHYDJET_C2_J3 +
					  sys_JER_PYTHIAHYDJET_C2_J3*sys_JER_PYTHIAHYDJET_C2_J3 +
					  sys_centShift_PYTHIAHYDJET_C2_J3*sys_centShift_PYTHIAHYDJET_C2_J3);

double sys_total_PbPb_C2_J4 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C2_J4*sys_cFraction_PYTHIAHYDJET_C2_J4 +
					  sys_lowerBound_PbPb_C2_J4*sys_lowerBound_PbPb_C2_J4 +
					  sys_bEnhance_PYTHIAHYDJET_C2_J4*sys_bEnhance_PYTHIAHYDJET_C2_J4 +
					  sys_cEnhance_PYTHIAHYDJET_C2_J4*sys_cEnhance_PYTHIAHYDJET_C2_J4 +
					  sys_JER_PYTHIAHYDJET_C2_J4*sys_JER_PYTHIAHYDJET_C2_J4 +
					  sys_centShift_PYTHIAHYDJET_C2_J4*sys_centShift_PYTHIAHYDJET_C2_J4);

double sys_total_PbPb_C1_J2 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C1_J2*sys_cFraction_PYTHIAHYDJET_C1_J2 +
					  sys_lowerBound_PbPb_C1_J2*sys_lowerBound_PbPb_C1_J2 +
					  sys_bEnhance_PYTHIAHYDJET_C1_J2*sys_bEnhance_PYTHIAHYDJET_C1_J2 +
					  sys_cEnhance_PYTHIAHYDJET_C1_J2*sys_cEnhance_PYTHIAHYDJET_C1_J2 +
					  sys_JER_PYTHIAHYDJET_C1_J2*sys_JER_PYTHIAHYDJET_C1_J2 +
					  sys_centShift_PYTHIAHYDJET_C1_J2*sys_centShift_PYTHIAHYDJET_C1_J2);

double sys_total_PbPb_C1_J3 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C1_J3*sys_cFraction_PYTHIAHYDJET_C1_J3 +
					  sys_lowerBound_PbPb_C1_J3*sys_lowerBound_PbPb_C1_J3 +
					  sys_bEnhance_PYTHIAHYDJET_C1_J3*sys_bEnhance_PYTHIAHYDJET_C1_J3 +
					  sys_cEnhance_PYTHIAHYDJET_C1_J3*sys_cEnhance_PYTHIAHYDJET_C1_J3 +
					  sys_JER_PYTHIAHYDJET_C1_J3*sys_JER_PYTHIAHYDJET_C1_J3 +
					  sys_centShift_PYTHIAHYDJET_C1_J3*sys_centShift_PYTHIAHYDJET_C1_J3);

double sys_total_PbPb_C1_J4 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C1_J4*sys_cFraction_PYTHIAHYDJET_C1_J4 +
					  sys_lowerBound_PbPb_C1_J4*sys_lowerBound_PbPb_C1_J4 +
					  sys_bEnhance_PYTHIAHYDJET_C1_J4*sys_bEnhance_PYTHIAHYDJET_C1_J4 +
					  sys_cEnhance_PYTHIAHYDJET_C1_J4*sys_cEnhance_PYTHIAHYDJET_C1_J4 +
					  sys_JER_PYTHIAHYDJET_C1_J4*sys_JER_PYTHIAHYDJET_C1_J4 +
					  sys_centShift_PYTHIAHYDJET_C2_J4*sys_centShift_PYTHIAHYDJET_C2_J4);


