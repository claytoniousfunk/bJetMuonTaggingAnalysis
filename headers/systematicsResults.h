// Systematics results

// ------------- fit-lower-bound systematics ------------------

// pp
// -- mu5 
double sys_lowerBound_pp_mu5_J2 = 0.0249;
double sys_lowerBound_pp_mu5_J3 = 0.0270;
double sys_lowerBound_pp_mu5_J4 = 0.0213;
// -- mu7
double sys_lowerBound_pp_mu7_J2 = 0.0328;
double sys_lowerBound_pp_mu7_J3 = 0.0334;
double sys_lowerBound_pp_mu7_J4 = 0.0242;
// -- mu12
double sys_lowerBound_pp_mu12_J1 = 0.0604;
double sys_lowerBound_pp_mu12_J2 = 0.0884;
double sys_lowerBound_pp_mu12_J3 = 0.0233;
double sys_lowerBound_pp_mu12_J4 = 0.0144;
double sys_lowerBound_pp_mu12_J5 = 0.0274;
double sys_lowerBound_pp_mu12_J6 = 0.1883;

// PbPb 30-90%
// -- mu5 
double sys_lowerBound_PbPb_mu5_C2_J2 = 0.0195;
double sys_lowerBound_PbPb_mu5_C2_J3 = 0.0735;
double sys_lowerBound_PbPb_mu5_C2_J4 = 0.1296;
// -- mu7 
double sys_lowerBound_PbPb_mu7_C2_J2 = 0.0333;
double sys_lowerBound_PbPb_mu7_C2_J3 = 0.0175;
double sys_lowerBound_PbPb_mu7_C2_J4 = 0.1162;
// -- mu12
//double sys_lowerBound_PbPb_mu12_C2_J2 = 0.0643;
double sys_lowerBound_PbPb_mu12_C2_J1 = 0.0924;
double sys_lowerBound_PbPb_mu12_C2_J2 = 0.0702;
double sys_lowerBound_PbPb_mu12_C2_J3 = 0.1060;
double sys_lowerBound_PbPb_mu12_C2_J4 = 0.2070;
double sys_lowerBound_PbPb_mu12_C2_J5 = 0.2117;
double sys_lowerBound_PbPb_mu12_C2_J6 = 21.6745;

// PbPb 0-30%
// -- mu5 
double sys_lowerBound_PbPb_mu5_C1_J2 = 0.0423;
double sys_lowerBound_PbPb_mu5_C1_J3 = 0.0965;
double sys_lowerBound_PbPb_mu5_C1_J4 = 0.0670;
// -- mu7 
double sys_lowerBound_PbPb_mu7_C1_J2 = 0.0534;
double sys_lowerBound_PbPb_mu7_C1_J3 = 0.1016;
double sys_lowerBound_PbPb_mu7_C1_J4 = 0.1292;
// -- mu12 
//double sys_lowerBound_PbPb_mu12_C1_J2 = 0.0926;
double sys_lowerBound_PbPb_mu12_C1_J1 = 0.0600;
double sys_lowerBound_PbPb_mu12_C1_J2 = 0.0628;
double sys_lowerBound_PbPb_mu12_C1_J3 = 0.1075;
double sys_lowerBound_PbPb_mu12_C1_J4 = 0.2156;
double sys_lowerBound_PbPb_mu12_C1_J5 = 0.4134;
double sys_lowerBound_PbPb_mu12_C1_J6 = 0.4379;


// ------------- c-fraction-variation systematics ------------------

// PYTHIA
// -- mu5
double sys_cFraction_pp_mu5_J2 = 0.0040;
double sys_cFraction_pp_mu5_J3 = 0.0118;
double sys_cFraction_pp_mu5_J4 = 0.0208;
// -- mu7
double sys_cFraction_pp_mu7_J2 = 0.0078;
double sys_cFraction_pp_mu7_J3 = 0.0139;
double sys_cFraction_pp_mu7_J4 = 0.0367;
// -- mu12
double sys_cFraction_pp_mu12_J1 = 0.0036;
double sys_cFraction_pp_mu12_J2 = 0.0120;
double sys_cFraction_pp_mu12_J3 = 0.0139;
double sys_cFraction_pp_mu12_J4 = 0.0175;
double sys_cFraction_pp_mu12_J5 = 0.0270;
double sys_cFraction_pp_mu12_J6 = 0.0390;

// PYTHIA+HYDJET 30-90%
// -- mu5
double sys_cFraction_PbPb_mu5_C2_J2 = 0.0028;
double sys_cFraction_PbPb_mu5_C2_J3 = 0.0215;
double sys_cFraction_PbPb_mu5_C2_J4 = 0.0519;
// -- mu7
double sys_cFraction_PbPb_mu7_C2_J2 = 0.0049;
double sys_cFraction_PbPb_mu7_C2_J3 = 0.0190;
double sys_cFraction_PbPb_mu7_C2_J4 = 0.0385;
// -- mu12
double sys_cFraction_PbPb_mu12_C2_J1 = 0.0038;
double sys_cFraction_PbPb_mu12_C2_J2 = 0.0133;
double sys_cFraction_PbPb_mu12_C2_J3 = 0.0159;
double sys_cFraction_PbPb_mu12_C2_J4 = 0.0288;
double sys_cFraction_PbPb_mu12_C2_J5 = 0.0246;
double sys_cFraction_PbPb_mu12_C2_J6 = 1.1426;
// correlated
//double sys_cFraction_PbPb_mu12_C2_J2 = TMath::Abs(0.0049 - sys_cFraction_pp_mu12_J2);
/* double sys_cFraction_PbPb_mu12_C2_J2 = TMath::Abs(0.0043 - sys_cFraction_pp_mu12_J2); */
/* double sys_cFraction_PbPb_mu12_C2_J3 = TMath::Abs(0.0075 - sys_cFraction_pp_mu12_J3); */
/* double sys_cFraction_PbPb_mu12_C2_J4 = TMath::Abs(0.0235 - sys_cFraction_pp_mu12_J4); */

// PYTHIA+HYDJET 0-30%
// -- mu5
double sys_cFraction_PbPb_mu5_C1_J2 = 0.0148;
double sys_cFraction_PbPb_mu5_C1_J3 = 0.0068;
double sys_cFraction_PbPb_mu5_C1_J4 = 0.0314;
// -- mu7
double sys_cFraction_PbPb_mu7_C1_J2 = 0.0072;
double sys_cFraction_PbPb_mu7_C1_J3 = 0.0123;
double sys_cFraction_PbPb_mu7_C1_J4 = 0.0375;
// -- mu12
double sys_cFraction_PbPb_mu12_C1_J1 = 0.0128;
double sys_cFraction_PbPb_mu12_C1_J2 = 0.0173;
double sys_cFraction_PbPb_mu12_C1_J3 = 0.0198;
double sys_cFraction_PbPb_mu12_C1_J4 = 0.0395;
double sys_cFraction_PbPb_mu12_C1_J5 = 0.0785;
double sys_cFraction_PbPb_mu12_C1_J6 = 0.1696;

//double sys_cFraction_PbPb_mu12_C1_J2 = TMath::Abs(0.0170 - sys_cFraction_pp_mu12_J2);
/* double sys_cFraction_PbPb_mu12_C1_J2 = TMath::Abs(0.0023 - sys_cFraction_pp_mu12_J2); */
/* double sys_cFraction_PbPb_mu12_C1_J3 = TMath::Abs(0.0048 - sys_cFraction_pp_mu12_J3); */
/* double sys_cFraction_PbPb_mu12_C1_J4 = TMath::Abs(0.0197 - sys_cFraction_pp_mu12_J4); */



// ------------- bGS-multiplier systematics ------------------

// PYTHIA
// -- mu5
double sys_bGS_pp_mu5_J2 = 0.0128;
double sys_bGS_pp_mu5_J3 = 0.0256;
double sys_bGS_pp_mu5_J4 = 0.0368;
// -- mu7
double sys_bGS_pp_mu7_J2 = 0.0240;
double sys_bGS_pp_mu7_J3 = 0.0529;
double sys_bGS_pp_mu7_J4 = 0.0723;
// -- mu12
double sys_bGS_pp_mu12_J1 = 0.0455;
double sys_bGS_pp_mu12_J2 = 0.0415;
double sys_bGS_pp_mu12_J3 = 0.0444;
double sys_bGS_pp_mu12_J4 = 0.0468;
double sys_bGS_pp_mu12_J5 = 0.0475;
double sys_bGS_pp_mu12_J6 = 0.0380;

// PYTHIA+HYDJET 30-90%
// -- mu5
double sys_bGS_PbPb_mu5_C2_J2 = 0.0110;
double sys_bGS_PbPb_mu5_C2_J3 = 0.0230;
double sys_bGS_PbPb_mu5_C2_J4 = 0.0451;
// -- mu7
double sys_bGS_PbPb_mu7_C2_J2 = 0.0222;
double sys_bGS_PbPb_mu7_C2_J3 = 0.0468;
double sys_bGS_PbPb_mu7_C2_J4 = 0.0898;
// -- mu12
double sys_bGS_PbPb_mu12_C2_J1 = 0.0457;
double sys_bGS_PbPb_mu12_C2_J2 = 0.0501;
double sys_bGS_PbPb_mu12_C2_J3 = 0.0528;
double sys_bGS_PbPb_mu12_C2_J4 = 0.0605;
double sys_bGS_PbPb_mu12_C2_J5 = 0.0449;
double sys_bGS_PbPb_mu12_C2_J6 = 0.0796;

//double sys_bGS_PbPb_mu12_C2_J2 = TMath::Abs(0.0240 - sys_bGS_pp_mu12_J2);
/* double sys_bGS_PbPb_mu12_C2_J2 = TMath::Abs(0.0241 - sys_bGS_pp_mu12_J2); */
/* double sys_bGS_PbPb_mu12_C2_J3 = TMath::Abs(0.0472 - sys_bGS_pp_mu12_J3); */
/* double sys_bGS_PbPb_mu12_C2_J4 = TMath::Abs(0.0554 - sys_bGS_pp_mu12_J4); */

// PYTHIA+HYDJET 0-30%
// -- mu5
double sys_bGS_PbPb_mu5_C1_J2 = 0.0090;
double sys_bGS_PbPb_mu5_C1_J3 = 0.0170;
double sys_bGS_PbPb_mu5_C1_J4 = 0.0392;
// -- mu7
double sys_bGS_PbPb_mu7_C1_J2 = 0.0088;
double sys_bGS_PbPb_mu7_C1_J3 = 0.0189;
double sys_bGS_PbPb_mu7_C1_J4 = 0.0919;
// -- mu12
double sys_bGS_PbPb_mu12_C1_J1 = 0.0316;
double sys_bGS_PbPb_mu12_C1_J2 = 0.0443;
double sys_bGS_PbPb_mu12_C1_J3 = 0.0468;
double sys_bGS_PbPb_mu12_C1_J4 = 0.0605;
double sys_bGS_PbPb_mu12_C1_J5 = 0.0449;
double sys_bGS_PbPb_mu12_C1_J6 = 0.0796;

//double sys_bGS_PbPb_mu12_C1_J2 = TMath::Abs(0.0132 - sys_bGS_pp_mu12_J2);
/* double sys_bGS_PbPb_mu12_C1_J2 = TMath::Abs(0.0145 - sys_bGS_pp_mu12_J2); */
/* double sys_bGS_PbPb_mu12_C1_J3 = TMath::Abs(0.0360 - sys_bGS_pp_mu12_J3); */
/* double sys_bGS_PbPb_mu12_C1_J4 = TMath::Abs(0.0514 - sys_bGS_pp_mu12_J4); */




// ------------- b-enhancement systematics ------------------

// PYTHIA
// -- mu5
double sys_bEnhance_pp_mu5_J2 = 0.0;
double sys_bEnhance_pp_mu5_J3 = 0.0;
double sys_bEnhance_pp_mu5_J4 = 0.0;
// -- mu7
double sys_bEnhance_pp_mu7_J2 = 0.0;
double sys_bEnhance_pp_mu7_J3 = 0.0;
double sys_bEnhance_pp_mu7_J4 = 0.0;
// -- mu12
double sys_bEnhance_pp_mu12_J1 = 0.0;
double sys_bEnhance_pp_mu12_J2 = 0.0;
double sys_bEnhance_pp_mu12_J3 = 0.0;
double sys_bEnhance_pp_mu12_J4 = 0.0;
double sys_bEnhance_pp_mu12_J5 = 0.0;
double sys_bEnhance_pp_mu12_J6 = 0.0;

// PbPb 30-90%
// -- mu5
double sys_bEnhance_PbPb_mu5_C2_J2 = 0.0436;
double sys_bEnhance_PbPb_mu5_C2_J3 = 0.0130;
double sys_bEnhance_PbPb_mu5_C2_J4 = 0.0160;
// -- mu7
double sys_bEnhance_PbPb_mu7_C2_J2 = 0.0408;
double sys_bEnhance_PbPb_mu7_C2_J3 = 0.0956;
double sys_bEnhance_PbPb_mu7_C2_J4 = 0.0027;
// -- mu12
/* double sys_bEnhance_PbPb_mu12_C2_J2 = 0.0278; */
/* double sys_bEnhance_PbPb_mu12_C2_J3 = 0.0262; */
/* double sys_bEnhance_PbPb_mu12_C2_J4 = 0.0051; */

double sys_bEnhance_PbPb_mu12_C2_J1 = 0.0;
double sys_bEnhance_PbPb_mu12_C2_J2 = 0.0;
double sys_bEnhance_PbPb_mu12_C2_J3 = 0.0;
double sys_bEnhance_PbPb_mu12_C2_J4 = 0.0;
double sys_bEnhance_PbPb_mu12_C2_J5 = 0.0;
double sys_bEnhance_PbPb_mu12_C2_J6 = 0.0;

// PbPb 0-30%
// -- mu5
double sys_bEnhance_PbPb_mu5_C1_J2 = 0.0870;
double sys_bEnhance_PbPb_mu5_C1_J3 = 0.0477;
double sys_bEnhance_PbPb_mu5_C1_J4 = 0.0291;
// -- mu7
double sys_bEnhance_PbPb_mu7_C1_J2 = 0.1544;
double sys_bEnhance_PbPb_mu7_C1_J3 = 0.0925;
double sys_bEnhance_PbPb_mu7_C1_J4 = 0.2531;
// -- mu12
/* double sys_bEnhance_PbPb_mu12_C1_J2 = 0.1461; */
/* double sys_bEnhance_PbPb_mu12_C1_J3 = 0.0696; */
/* double sys_bEnhance_PbPb_mu12_C1_J4 = 0.0748; */

double sys_bEnhance_PbPb_mu12_C1_J1 = 0.0;
double sys_bEnhance_PbPb_mu12_C1_J2 = 0.0;
double sys_bEnhance_PbPb_mu12_C1_J3 = 0.0;
double sys_bEnhance_PbPb_mu12_C1_J4 = 0.0;
double sys_bEnhance_PbPb_mu12_C1_J5 = 0.0;
double sys_bEnhance_PbPb_mu12_C1_J6 = 0.0;





// ------------- c-enhancement systematics ------------------

// PYTHIA
// -- mu5
double sys_cEnhance_pp_mu5_J2 = 0.0;
double sys_cEnhance_pp_mu5_J3 = 0.0;
double sys_cEnhance_pp_mu5_J4 = 0.0;
// -- mu7
double sys_cEnhance_pp_mu7_J2 = 0.0;
double sys_cEnhance_pp_mu7_J3 = 0.0;
double sys_cEnhance_pp_mu7_J4 = 0.0;
// -- mu12
double sys_cEnhance_pp_mu12_J1 = 0.0;
double sys_cEnhance_pp_mu12_J2 = 0.0;
double sys_cEnhance_pp_mu12_J3 = 0.0;
double sys_cEnhance_pp_mu12_J4 = 0.0;
double sys_cEnhance_pp_mu12_J5 = 0.0;
double sys_cEnhance_pp_mu12_J6 = 0.0;

// PbPb 30-90%
// -- mu5
double sys_cEnhance_PbPb_mu5_C2_J2 = 0.0226;
double sys_cEnhance_PbPb_mu5_C2_J3 = 0.0113;
double sys_cEnhance_PbPb_mu5_C2_J4 = 0.0642;
// -- mu7
double sys_cEnhance_PbPb_mu7_C2_J2 = 0.0193;
double sys_cEnhance_PbPb_mu7_C2_J3 = 0.0381;
double sys_cEnhance_PbPb_mu7_C2_J4 = 0.0051;
// -- mu12
/* double sys_cEnhance_PbPb_mu12_C2_J2 = 0.0019; */
/* double sys_cEnhance_PbPb_mu12_C2_J3 = 0.0060; */
/* double sys_cEnhance_PbPb_mu12_C2_J4 = 0.0082; */

double sys_cEnhance_PbPb_mu12_C2_J1 = 0.0;
double sys_cEnhance_PbPb_mu12_C2_J2 = 0.0;
double sys_cEnhance_PbPb_mu12_C2_J3 = 0.0;
double sys_cEnhance_PbPb_mu12_C2_J4 = 0.0;
double sys_cEnhance_PbPb_mu12_C2_J5 = 0.0;
double sys_cEnhance_PbPb_mu12_C2_J6 = 0.0;

// PbPb 0-30%
// -- mu5
double sys_cEnhance_PbPb_mu5_C1_J2 = 0.0130;
double sys_cEnhance_PbPb_mu5_C1_J3 = 0.0171;
double sys_cEnhance_PbPb_mu5_C1_J4 = 0.0033;
// -- mu7
double sys_cEnhance_PbPb_mu7_C1_J2 = 0.0044;
double sys_cEnhance_PbPb_mu7_C1_J3 = 0.0201;
double sys_cEnhance_PbPb_mu7_C1_J4 = 0.0248;
// -- mu12
/* double sys_cEnhance_PbPb_mu12_C1_J2 = 0.0042; */
/* double sys_cEnhance_PbPb_mu12_C1_J3 = 0.0023; */
/* double sys_cEnhance_PbPb_mu12_C1_J4 = 0.0403; */

double sys_cEnhance_PbPb_mu12_C1_J1 = 0.0;
double sys_cEnhance_PbPb_mu12_C1_J2 = 0.0;
double sys_cEnhance_PbPb_mu12_C1_J3 = 0.0;
double sys_cEnhance_PbPb_mu12_C1_J4 = 0.0;
double sys_cEnhance_PbPb_mu12_C1_J5 = 0.0;
double sys_cEnhance_PbPb_mu12_C1_J6 = 0.0;


// ------------- JER-smear systematics ------------------

// PYTHIA
// -- mu5
double sys_JERsmear_pp_mu5_J2 = 0.0002;
double sys_JERsmear_pp_mu5_J3 = 0.0043;
double sys_JERsmear_pp_mu5_J4 = 0.0130;
// -- mu7
double sys_JERsmear_pp_mu7_J2 = 0.0478;
double sys_JERsmear_pp_mu7_J3 = 0.0041;
double sys_JERsmear_pp_mu7_J4 = 0.0263;
// -- mu12
double sys_JERsmear_pp_mu12_J1 = 0.0040;
double sys_JERsmear_pp_mu12_J2 = 0.0327;
double sys_JERsmear_pp_mu12_J3 = 0.0055;
double sys_JERsmear_pp_mu12_J4 = 0.0398;
double sys_JERsmear_pp_mu12_J5 = 0.0024;
double sys_JERsmear_pp_mu12_J6 = 0.0341;

// PYTHIAHYDJET 30-90%
// -- mu5
double sys_JERsmear_PbPb_mu5_C2_J2 = 0.0247;
double sys_JERsmear_PbPb_mu5_C2_J3 = 0.0061;
double sys_JERsmear_PbPb_mu5_C2_J4 = 0.0505;
// -- mu7
double sys_JERsmear_PbPb_mu7_C2_J2 = 0.1234;
double sys_JERsmear_PbPb_mu7_C2_J3 = 0.0105;
double sys_JERsmear_PbPb_mu7_C2_J4 = 0.1097;
// -- mu12
//double sys_JERsmear_PbPb_mu12_C2_J2 = 0.0346;
double sys_JERsmear_PbPb_mu12_C2_J1 = 0.0522;
double sys_JERsmear_PbPb_mu12_C2_J2 = 0.0161;
double sys_JERsmear_PbPb_mu12_C2_J3 = 0.0159;
double sys_JERsmear_PbPb_mu12_C2_J4 = 0.0653;
double sys_JERsmear_PbPb_mu12_C2_J5 = 0.0321;
double sys_JERsmear_PbPb_mu12_C2_J6 = 0.2144;

// PbPb 0-30%
// -- mu5
double sys_JERsmear_PbPb_mu5_C1_J2 = 0.0855;
double sys_JERsmear_PbPb_mu5_C1_J3 = 0.1390;
double sys_JERsmear_PbPb_mu5_C1_J4 = 0.0132;
// -- mu7
double sys_JERsmear_PbPb_mu7_C1_J2 = 0.1699;
double sys_JERsmear_PbPb_mu7_C1_J3 = 0.0633;
double sys_JERsmear_PbPb_mu7_C1_J4 = 0.0518;
// -- mu12
//double sys_JERsmear_PbPb_mu12_C1_J2 = 0.0756;
double sys_JERsmear_PbPb_mu12_C1_J1 = 0.0232;
double sys_JERsmear_PbPb_mu12_C1_J2 = 0.0379;
double sys_JERsmear_PbPb_mu12_C1_J3 = 0.0138;
double sys_JERsmear_PbPb_mu12_C1_J4 = 0.0140;
double sys_JERsmear_PbPb_mu12_C1_J5 = 0.0377;
double sys_JERsmear_PbPb_mu12_C1_J6 = 0.0562;


// ------------- centrality-shift systematics ------------------

// PYTHIA
// -- mu5
double sys_centShift_pp_mu5_J2 = 0.0;
double sys_centShift_pp_mu5_J3 = 0.0;
double sys_centShift_pp_mu5_J4 = 0.0;
// -- mu7
double sys_centShift_pp_mu7_J2 = 0.0;
double sys_centShift_pp_mu7_J3 = 0.0;
double sys_centShift_pp_mu7_J4 = 0.0;
// -- mu12
double sys_centShift_pp_mu12_J2 = 0.0;
double sys_centShift_pp_mu12_J3 = 0.0;
double sys_centShift_pp_mu12_J4 = 0.0;

// PYTHIAHYDJET 30-90%
// -- mu5
double sys_centShift_PbPb_mu5_C2_J2 = 0.0;
double sys_centShift_PbPb_mu5_C2_J3 = 0.0;
double sys_centShift_PbPb_mu5_C2_J4 = 0.0;
// -- mu7
double sys_centShift_PbPb_mu7_C2_J2 = 0.0;
double sys_centShift_PbPb_mu7_C2_J3 = 0.0;
double sys_centShift_PbPb_mu7_C2_J4 = 0.0;
// -- mu12
double sys_centShift_PbPb_mu12_C2_J2 = 0.0;
double sys_centShift_PbPb_mu12_C2_J3 = 0.0;
double sys_centShift_PbPb_mu12_C2_J4 = 0.0;

// PbPb 0-30%
// -- mu5
double sys_centShift_PbPb_mu5_C1_J2 = 0.0;
double sys_centShift_PbPb_mu5_C1_J3 = 0.0;
double sys_centShift_PbPb_mu5_C1_J4 = 0.0;
// -- mu7
double sys_centShift_PbPb_mu7_C1_J2 = 0.0;
double sys_centShift_PbPb_mu7_C1_J3 = 0.0;
double sys_centShift_PbPb_mu7_C1_J4 = 0.0;
// -- mu12
double sys_centShift_PbPb_mu12_C1_J2 = 0.0;
double sys_centShift_PbPb_mu12_C1_J3 = 0.0;
double sys_centShift_PbPb_mu12_C1_J4 = 0.0;


// ------------- JEU-shift-up systematics ------------------

// PYTHIA
// -- mu5
double sys_JEUShiftUp_pp_mu5_J2 = 0.0;
double sys_JEUShiftUp_pp_mu5_J3 = 0.0;
double sys_JEUShiftUp_pp_mu5_J4 = 0.0;
// -- mu7
double sys_JEUShiftUp_pp_mu7_J2 = 0.0218;
double sys_JEUShiftUp_pp_mu7_J3 = 0.0168;
double sys_JEUShiftUp_pp_mu7_J4 = 0.0205;
// -- mu12
double sys_JEUShiftUp_pp_mu12_J1 = 0.0207;
double sys_JEUShiftUp_pp_mu12_J2 = 0.0278;
double sys_JEUShiftUp_pp_mu12_J3 = 0.0039;
double sys_JEUShiftUp_pp_mu12_J4 = 0.0078;
double sys_JEUShiftUp_pp_mu12_J5 = 0.0214;
double sys_JEUShiftUp_pp_mu12_J6 = 0.0104;

// PYTHIAHYDJET 30-90%
// -- mu5
double sys_JEUShiftUp_PbPb_mu5_C2_J2 = 0.0;
double sys_JEUShiftUp_PbPb_mu5_C2_J3 = 0.0;
double sys_JEUShiftUp_PbPb_mu5_C2_J4 = 0.0;
// -- mu7
double sys_JEUShiftUp_PbPb_mu7_C2_J2 = 0.0268;
double sys_JEUShiftUp_PbPb_mu7_C2_J3 = 0.0090;
double sys_JEUShiftUp_PbPb_mu7_C2_J4 = 0.0333;
// -- mu12
double sys_JEUShiftUp_PbPb_mu12_C2_J1 = 0.0861;
double sys_JEUShiftUp_PbPb_mu12_C2_J2 = 0.0055;
double sys_JEUShiftUp_PbPb_mu12_C2_J3 = 0.0257;
double sys_JEUShiftUp_PbPb_mu12_C2_J4 = 0.0290;
double sys_JEUShiftUp_PbPb_mu12_C2_J5 = 0.0115;
double sys_JEUShiftUp_PbPb_mu12_C2_J6 = 0.2873;

// PbPb 0-30%
// -- mu5
double sys_JEUShiftUp_PbPb_mu5_C1_J2 = 0.0;
double sys_JEUShiftUp_PbPb_mu5_C1_J3 = 0.0;
double sys_JEUShiftUp_PbPb_mu5_C1_J4 = 0.0;
// -- mu7
double sys_JEUShiftUp_PbPb_mu7_C1_J2 = 0.0652;
double sys_JEUShiftUp_PbPb_mu7_C1_J3 = 0.0142;
double sys_JEUShiftUp_PbPb_mu7_C1_J4 = 0.0231;
// -- mu12
double sys_JEUShiftUp_PbPb_mu12_C1_J1 = 0.0128;
double sys_JEUShiftUp_PbPb_mu12_C1_J2 = 0.0308;
double sys_JEUShiftUp_PbPb_mu12_C1_J3 = 0.0031;
double sys_JEUShiftUp_PbPb_mu12_C1_J4 = 0.0329;
double sys_JEUShiftUp_PbPb_mu12_C1_J5 = 0.0097;
double sys_JEUShiftUp_PbPb_mu12_C1_J6 = 0.0316;

// ------------- JEU-Shift-down systematics ------------------

// PYTHIA
// -- mu5
double sys_JEUShiftDown_pp_mu5_J2 = 0.0;
double sys_JEUShiftDown_pp_mu5_J3 = 0.0;
double sys_JEUShiftDown_pp_mu5_J4 = 0.0;
// -- mu7
double sys_JEUShiftDown_pp_mu7_J2 = 0.0300;
double sys_JEUShiftDown_pp_mu7_J3 = 0.0116;
double sys_JEUShiftDown_pp_mu7_J4 = 0.0226;
// -- mu12
double sys_JEUShiftDown_pp_mu12_J1 = 0.0104;
double sys_JEUShiftDown_pp_mu12_J2 = 0.0206;
double sys_JEUShiftDown_pp_mu12_J3 = 0.0018;
double sys_JEUShiftDown_pp_mu12_J4 = 0.0002;
double sys_JEUShiftDown_pp_mu12_J5 = 0.0037;
double sys_JEUShiftDown_pp_mu12_J6 = 0.0132;

// PYTHIAHYDJET 30-90%
// -- mu5
double sys_JEUShiftDown_PbPb_mu5_C2_J2 = 0.0;
double sys_JEUShiftDown_PbPb_mu5_C2_J3 = 0.0;
double sys_JEUShiftDown_PbPb_mu5_C2_J4 = 0.0;
// -- mu7
double sys_JEUShiftDown_PbPb_mu7_C2_J2 = 0.0280;
double sys_JEUShiftDown_PbPb_mu7_C2_J3 = 0.0134;
double sys_JEUShiftDown_PbPb_mu7_C2_J4 = 0.0265;
// -- mu12
double sys_JEUShiftDown_PbPb_mu12_C2_J1 = 0.0064;
double sys_JEUShiftDown_PbPb_mu12_C2_J2 = 0.0147;
double sys_JEUShiftDown_PbPb_mu12_C2_J3 = 0.0008;
double sys_JEUShiftDown_PbPb_mu12_C2_J4 = 0.0011;
double sys_JEUShiftDown_PbPb_mu12_C2_J5 = 0.0897;
double sys_JEUShiftDown_PbPb_mu12_C2_J6 = 0.0000;

// PbPb 0-30%
// -- mu5
double sys_JEUShiftDown_PbPb_mu5_C1_J2 = 0.0;
double sys_JEUShiftDown_PbPb_mu5_C1_J3 = 0.0;
double sys_JEUShiftDown_PbPb_mu5_C1_J4 = 0.0;
// -- mu7
double sys_JEUShiftDown_PbPb_mu7_C1_J2 = 0.0267;
double sys_JEUShiftDown_PbPb_mu7_C1_J3 = 0.0793;
double sys_JEUShiftDown_PbPb_mu7_C1_J4 = 0.0065;
// -- mu12
double sys_JEUShiftDown_PbPb_mu12_C1_J1 = 0.0182;
double sys_JEUShiftDown_PbPb_mu12_C1_J2 = 0.0034;
double sys_JEUShiftDown_PbPb_mu12_C1_J3 = 0.0172;
double sys_JEUShiftDown_PbPb_mu12_C1_J4 = 0.0332;
double sys_JEUShiftDown_PbPb_mu12_C1_J5 = 0.0534;
double sys_JEUShiftDown_PbPb_mu12_C1_J6 = 0.0000;

// ------------- residual non-closure systematics ------------------

// PYTHIA
// -- mu5
double sys_residual_pp_mu5_J2 = 0.0;
double sys_residual_pp_mu5_J3 = 0.0;
double sys_residual_pp_mu5_J4 = 0.0;
// -- mu7
double sys_residual_pp_mu7_J2 = 0.0;
double sys_residual_pp_mu7_J3 = 0.0;
double sys_residual_pp_mu7_J4 = 0.0;
// -- mu12
double sys_residual_pp_mu12_J1 = 0.0;
double sys_residual_pp_mu12_J2 = 0.0;
double sys_residual_pp_mu12_J3 = 0.0;
double sys_residual_pp_mu12_J4 = 0.0;
double sys_residual_pp_mu12_J5 = 0.0;
double sys_residual_pp_mu12_J6 = 0.0;

/* double sys_residual_pp_mu12_J2 = 0.0; */
/* double sys_residual_pp_mu12_J3 = 0.0; */
/* double sys_residual_pp_mu12_J4 = 0.0; */

// PYTHIAHYDJET 30-90%
// -- mu5
double sys_residual_PbPb_mu5_C2_J2 = 0.0;
double sys_residual_PbPb_mu5_C2_J3 = 0.0;
double sys_residual_PbPb_mu5_C2_J4 = 0.0;
// -- mu7
double sys_residual_PbPb_mu7_C2_J2 = 0.0;
double sys_residual_PbPb_mu7_C2_J3 = 0.0;
double sys_residual_PbPb_mu7_C2_J4 = 0.0;
// -- mu12
double sys_residual_PbPb_mu12_C2_J1 = sys_residual_pp_mu12_J1;
double sys_residual_PbPb_mu12_C2_J2 = sys_residual_pp_mu12_J2;
double sys_residual_PbPb_mu12_C2_J3 = sys_residual_pp_mu12_J3;
double sys_residual_PbPb_mu12_C2_J4 = sys_residual_pp_mu12_J4;
double sys_residual_PbPb_mu12_C2_J5 = sys_residual_pp_mu12_J5;
double sys_residual_PbPb_mu12_C2_J6 = sys_residual_pp_mu12_J6;

// PbPb 0-30%
// -- mu5
double sys_residual_PbPb_mu5_C1_J2 = 0.0;
double sys_residual_PbPb_mu5_C1_J3 = 0.0;
double sys_residual_PbPb_mu5_C1_J4 = 0.0;
// -- mu7
double sys_residual_PbPb_mu7_C1_J2 = 0.0;
double sys_residual_PbPb_mu7_C1_J3 = 0.0;
double sys_residual_PbPb_mu7_C1_J4 = 0.0;
// -- mu12
double sys_residual_PbPb_mu12_C1_J1 = sys_residual_pp_mu12_J1;
double sys_residual_PbPb_mu12_C1_J2 = sys_residual_pp_mu12_J2;
double sys_residual_PbPb_mu12_C1_J3 = sys_residual_pp_mu12_J3;
double sys_residual_PbPb_mu12_C1_J4 = sys_residual_pp_mu12_J4;
double sys_residual_PbPb_mu12_C1_J5 = sys_residual_pp_mu12_J5;
double sys_residual_PbPb_mu12_C1_J6 = sys_residual_pp_mu12_J6;














