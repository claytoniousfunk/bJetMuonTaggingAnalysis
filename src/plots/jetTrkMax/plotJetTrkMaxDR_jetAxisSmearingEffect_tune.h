

TString CMSString, energyString, jetPtString, hadronPtString;
TLine *li;
TLatex *la;
TFile *file_pp_mc_raw, *file_pp_mc_smeared_1, *file_pp_mc_smeared_2, *file_pp_mc_smeared_3;
TFile *file_PbPb_mc_raw, *file_PbPb_mc_smeared;
TFile *file_pp_data, *file_PbPb_data;

TH1D *binFinder;
double smallShift;

TH1D *h_dR_pp_mc_raw, *h_dR_pp_mc_smeared, *h_dR_pp_data;
TH1D *h_dR_C5_mc_raw, *h_dR_C5_mc_smeared, *h_dR_C5_data;
TH1D *h_dR_C4_mc_raw, *h_dR_C4_mc_smeared, *h_dR_C4_data;
TH1D *h_dR_C3_mc_raw, *h_dR_C3_mc_smeared, *h_dR_C3_data;
TH1D *h_dR_C2_mc_raw, *h_dR_C2_mc_smeared, *h_dR_C2_data;
TH1D *h_dR_C1_mc_raw, *h_dR_C1_mc_smeared, *h_dR_C1_data;

// ratios
TH1D *r_pp, *r_C5, *r_C4, *r_C3, *r_C2, *r_C1;
TH1D *r_pp_smeared, *r_C5_smeared, *r_C4_smeared, *r_C3_smeared, *r_C2_smeared, *r_C1_smeared;

TLegend *leg_pp, *leg_C5, *leg_C4, *leg_C3, *leg_C2, *leg_C1;

double subTitleSize;
double subLabelSize;

// double-ration PbPb/pp
TH1D *R_C5, *R_C4, *R_C3, *R_C2, *R_C1;
