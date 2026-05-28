

TString CMSString, energyString, jetPtString, hadronPtString;
TLine *li;
TLatex *la;
TFile *file_pp_data, *file_PbPb_data;

TH1D *binFinder;
double smallShift;

TH1D *h_dR_pp_data;
TH1D *h_dR_C5_data;
TH1D *h_dR_C4_data;
TH1D *h_dR_C3_data;
TH1D *h_dR_C2_data;
TH1D *h_dR_C1_data;

// ratios
TH1D *r_C5, *r_C4, *r_C3, *r_C2, *r_C1;


TLegend *leg_pp, *leg_C5, *leg_C4, *leg_C3, *leg_C2, *leg_C1;

double subTitleSize;
double subLabelSize;

// double-ration PbPb/pp
TH1D *R_C5, *R_C4, *R_C3, *R_C2, *R_C1;

const int Nedge_dR = 19;
double dR_axis[Nedge_dR] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.7,2.1,2.5,3.0,3.8,5.0};
