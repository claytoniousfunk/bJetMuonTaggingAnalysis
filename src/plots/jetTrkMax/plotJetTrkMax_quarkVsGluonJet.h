TString CMSString, energyString, jetPtString, hadronPtString;
TLine *li;
TLatex *la;

TFile *file_pp_mc, *file_pp_data;
TH1D *h_jetPt_pp_mc;
TH1D *h_jetPt_pp_data;
TH1D *h_dR_pp_mc, *h_dR_pp_data;
TH1D *h_dR_pp_qJets_mc, *h_dR_pp_gJets_mc;
TH1D *h_pTrel_pp_mc, *h_pTrel_pp_data;


const int Nedge_pTrel = 21;
double  pTrel_axis[Nedge_pTrel] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.2,1.4,1.6,1.8,2,2.4,2.8,3.2,4,5};

const int Nedge_dR = 18;
double dR_axis[Nedge_dR] = {0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,0.12,0.14,0.16,0.18,0.2,0.24,0.3};

// const int Nedge_dR = 23;
// double dR_axis[Nedge_dR] = {0,0.005,0.01,0.015,0.02,0.025,0.03,0.035,0.04,0.045,0.05,0.06,0.07,0.08,0.09,0.1,0.12,0.14,0.16,0.18,0.2,0.24,0.3};

// const int Nedge_dR = 13;
// double dR_axis[Nedge_dR] = {0,0.02,0.04,0.06,0.08,0.1,0.12,0.14,0.16,0.18,0.2,0.24,0.3};

TH1D *r_jetPt_pp;
TH1D *r_dR_pp, *r_dR_temp;
TH1D *r_pTrel_pp;

TLegend *leg_mc;
TLegend *leg_temp;


double subTitleSize;
double subLabelSize;

TH1D *h_fit_pp, *h_fit_qJets, *h_fit_gJets;
TH1D *h_fit_pp_draw, *h_fit_qJets_draw, *h_fit_gJets_draw;
THStack *h_stack;
TH1D *h_stack_histo_rep;
TH1D *r_fit;
