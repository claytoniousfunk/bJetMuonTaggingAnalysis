

TString CMSString, energyString, jetPtString, hadronPtString;
TLine *li;
TLatex *la;
TFile *file_pp_mc_raw, *file_PbPb_mc_raw;

TH1D *binFinder;
double smallShift;

TH1D *h_dR_pp_mc_raw;
TH1D *h_dR_C5_mc_raw;
TH1D *h_dR_C4_mc_raw;
TH1D *h_dR_C3_mc_raw;
TH1D *h_dR_C2_mc_raw;
TH1D *h_dR_C1_mc_raw;

// ratios
TH1D *r_C5, *r_C4, *r_C3, *r_C2, *r_C1;

TLegend *leg_C5, *leg_C4, *leg_C3, *leg_C2, *leg_C1;

double subTitleSize;
double subLabelSize;

// double-ration PbPb/pp
TH1D *R_C5, *R_C4, *R_C3, *R_C2, *R_C1;

const int Nedge_dR = 18;
double dR_axis[Nedge_dR] = {0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,0.12,0.14,0.16,0.18,0.2,0.24,0.3};
