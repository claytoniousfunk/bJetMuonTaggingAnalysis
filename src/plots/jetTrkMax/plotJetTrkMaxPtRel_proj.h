

TString CMSString, energyString, jetPtString, hadronPtString;
TLine *li;
TLatex *la;
TFile *file_pp_mc_raw, *file_pp_mc_weighted;
TFile *file_PbPb_mc_raw, *file_PbPb_mc_weighted;
TFile *file_pp_data, *file_PbPb_data;

TH2D *H_pTrel_pp_mc_raw;
TH2D *H_pTrel_C5_mc_raw;
TH2D *H_pTrel_C4_mc_raw;
TH2D *H_pTrel_C3_mc_raw;
TH2D *H_pTrel_C2_mc_raw;
TH2D *H_pTrel_C1_mc_raw;

TH1D *h_pTrel_pp_mc_raw;
TH1D *h_pTrel_C5_mc_raw;
TH1D *h_pTrel_C4_mc_raw;
TH1D *h_pTrel_C3_mc_raw;
TH1D *h_pTrel_C2_mc_raw;
TH1D *h_pTrel_C1_mc_raw;

TH1D *h_pTrel_pp_mc_weighted;
TH1D *h_pTrel_C5_mc_weighted;
TH1D *h_pTrel_C4_mc_weighted;
TH1D *h_pTrel_C3_mc_weighted;
TH1D *h_pTrel_C2_mc_weighted;
TH1D *h_pTrel_C1_mc_weighted;

TH2D *H_pTrel_pp_data;
TH2D *H_pTrel_C5_data;
TH2D *H_pTrel_C4_data;
TH2D *H_pTrel_C3_data;
TH2D *H_pTrel_C2_data;
TH2D *H_pTrel_C1_data;

TH1D *h_pTrel_pp_data;
TH1D *h_pTrel_C5_data;
TH1D *h_pTrel_C4_data;
TH1D *h_pTrel_C3_data;
TH1D *h_pTrel_C2_data;
TH1D *h_pTrel_C1_data;

// ratios
TH1D *r_pp, *r_C5, *r_C4, *r_C3, *r_C2, *r_C1;

TLegend *leg_pp, *leg_C5, *leg_C4, *leg_C3, *leg_C2, *leg_C1;

double subTitleSize;
double subLabelSize;

// double-ration PbPb/pp
TH1D *R_C5, *R_C4, *R_C3, *R_C2, *R_C1;

const int Nedge_pTrel = 19;
double pTrel_axis[Nedge_pTrel] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.7,2.1,2.5,3.0,3.8,5.0};
