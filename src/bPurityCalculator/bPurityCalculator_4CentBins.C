
#include "../templateFitter/templateFitter_projectableTemplates_4CentBins.h"
#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/systematicsResults_4CentBins.h"

void bPurityCalculator_4CentBins(){

  cout << endl;
  cout << "#######  RUNNING B-PURITY CALCULATOR  #########" << endl;
  cout << endl;
  
  // const int N_jetPtAxisEdges = 5;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {60,80,120,200,300};
  // double jetPtCenters[N_jetPtAxisEdges-1] = {70,100,160,250};
  // double jetPtWidths[N_jetPtAxisEdges-1] = {10,20,40,50};

  // const int N_jetPtAxisEdges = 7;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {120,130,140,150,170,200,300};
  // const int N_jetPtAxisEdges = 10;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {80,85,90,100,110,120,130,150,200,300};
  // const int N_jetPtAxisEdges = 13;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {80,85,90,95,100,105,110,120,130,140,150,170,200};

  // const int N_jetPtAxisEdges = 8;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {80,85,90,100,120,150,200,500};

  // const int N_jetPtAxisEdges = 11;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {80,85,90,95,100,105,110,130,150,170,200};

  // const int N_jetPtAxisEdges = 3;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {120,150,200};

  // const int N_jetPtAxisEdges = 10;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {50,60,70,80,100,120,150,200,300,500};

  // const int N_jetPtAxisEdges = 8;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {100,120,130,150,170,200,300,500};

  const int N_jetPtAxisEdges = 8;
  double jetPtAxisEdges[N_jetPtAxisEdges] = {80,90,100,120,150,200,300,500};

  // const int N_jetPtAxisEdges = 10;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {100,110,120,130,140,150,170,200,250,300};

  // const int N_jetPtAxisEdges = 4;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {100,120,150,200};

  
  double jetPtCenters[N_jetPtAxisEdges-1];
  double jetPtWidths[N_jetPtAxisEdges-1];

  for(int i = 0; i < N_jetPtAxisEdges-1; i++){
    jetPtCenters[i] = (jetPtAxisEdges[i+1] + jetPtAxisEdges[i])/2.;
    jetPtWidths[i] = (jetPtAxisEdges[i+1] - jetPtAxisEdges[i])/2;
  }
  

  
  double results_pp[N_jetPtAxisEdges-1], err_results_pp[N_jetPtAxisEdges-1];
  double results_C4[N_jetPtAxisEdges-1], err_results_C4[N_jetPtAxisEdges-1];
  double results_C3[N_jetPtAxisEdges-1], err_results_C3[N_jetPtAxisEdges-1];
  double results_C2[N_jetPtAxisEdges-1], err_results_C2[N_jetPtAxisEdges-1];
  double results_C1[N_jetPtAxisEdges-1], err_results_C1[N_jetPtAxisEdges-1];


  // templateFitter(isData,  inMu5, isMu7, isMu12, ispp,isC1,isC2,  isJ1,isJ2,isJ3,isJ4,isJ5,isJ6,  mergeC,mergeB,
  //                               2tempFit,3tempFit,  low_x,high_x,  c_multiplier, bGS_multiplier, return)

  //templateFitter(1,  0,0,1,  0,1,0,0,0,0,  0,0,  0,1,  0.0,4.0,  1);

  

  int do_data = 1;
  
  int do_mergeB = 1;
  int do_mergeC = 1;

  // one has to 1, one has to be 0 for the fit integers
  int do_2tempFit = 1;
  int do_3tempFit = 0; 

  
  double pTrel_fit_low  = 0.0;
  double pTrel_fit_high = 3.0;

  double c_multiplier = 1.0;
  double bGS_multiplier = 1.175;

  int do_JER_smear = 0;
  int do_JEU_up = 0;
  int do_JEU_down = 0;

  int do_centShiftUp = 0;
  int do_centShiftDown = 0;

  string output_file_string = Form("../../rootFiles/bPurityResults/latest/bPurityResults_DATA-%i_mergeB-%i_mergeC-%i_pTrel-%1.1fto%1.1f_cMult-%1.1f_bMult-%1.3f_JERsmear-%i_JEUShiftUp-%i_JEUShiftDown-%i_centShiftUp-%i_centShiftDown-%i.root",do_data,do_mergeB,do_mergeC,pTrel_fit_low,pTrel_fit_high,c_multiplier,bGS_multiplier,do_JER_smear,do_JEU_up,do_JEU_down,do_centShiftUp,do_centShiftDown);

  cout << output_file_string.c_str() << endl;


  for(int i = 0; i < N_jetPtAxisEdges-1; i++){
    results_pp[i] = templateFitter(do_data, 1,0,0,0,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 1);
    err_results_pp[i] = templateFitter(do_data, 1,0,0,0,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 2);

    results_C4[i] = templateFitter(do_data, 0,0,0,0,1, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 1);
    err_results_C4[i] = templateFitter(do_data, 0,0,0,0,1, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 2);
    
    results_C3[i] = templateFitter(do_data, 0,0,0,1,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 1);
    err_results_C3[i] = templateFitter(do_data, 0,0,0,1,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 2);

    results_C2[i] = templateFitter(do_data, 0,0,1,0,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 1);
    err_results_C2[i] = templateFitter(do_data, 0,0,1,0,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 2);

    results_C1[i] = templateFitter(do_data, 0,1,0,0,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 1);
    err_results_C1[i] = templateFitter(do_data, 0,1,0,0,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 2);

    
  }



  /////////////////////////////////////////////////////////////   plot the b-jet purity results
  
  TCanvas *canv = new TCanvas("canv","canv",600,600);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.15);
  pad->SetBottomMargin(0.15);
  pad->Draw();
  pad->cd();
	
  TMultiGraph *m = new TMultiGraph();
  TGraphErrors *g0 = new TGraphErrors(N_jetPtAxisEdges-1,jetPtCenters,results_pp,jetPtWidths,err_results_pp);
  TGraphErrors *g1 = new TGraphErrors(N_jetPtAxisEdges-1,jetPtCenters,results_C1,jetPtWidths,err_results_C1);
  TGraphErrors *g2 = new TGraphErrors(N_jetPtAxisEdges-1,jetPtCenters,results_C2,jetPtWidths,err_results_C2);
  TGraphErrors *g3 = new TGraphErrors(N_jetPtAxisEdges-1,jetPtCenters,results_C3,jetPtWidths,err_results_C3);
  TGraphErrors *g4 = new TGraphErrors(N_jetPtAxisEdges-1,jetPtCenters,results_C4,jetPtWidths,err_results_C4);

  double lw  = 2;
  double ms = 2;
  
  g0->SetLineColor(kBlack);
  g0->SetLineWidth(lw);
  g0->SetMarkerColor(kBlack);
  g0->SetMarkerStyle(24);
  g0->SetMarkerSize(ms);

  g4->SetLineColor(kBlack);
  g4->SetLineWidth(lw);
  g4->SetMarkerColor(kBlack);
  g4->SetMarkerStyle(33);
  g4->SetMarkerSize(ms);

  g3->SetLineColor(kBlue-4);
  g3->SetLineWidth(lw);
  g3->SetMarkerColor(kBlue-4);
  g3->SetMarkerStyle(21);
  g3->SetMarkerSize(ms);

  g2->SetLineColor(kGreen+2);
  g2->SetLineWidth(lw);
  g2->SetMarkerColor(kGreen+2);
  g2->SetMarkerStyle(34);
  g2->SetMarkerSize(ms);
  
  g1->SetLineColor(kRed-4);
  g1->SetLineWidth(lw);
  g1->SetMarkerColor(kRed-4);
  g1->SetMarkerStyle(47);
  g1->SetMarkerSize(ms);

  




	


  /////////////////////////////  generate histogram representations for the b-jet fraction
  
  TH1D *bFracResults_pp = new TH1D("bFracResults_pp","bFracResults_pp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *bFracResults_C4 = new TH1D("bFracResults_C4","bFracResults_C4",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *bFracResults_C3 = new TH1D("bFracResults_C3","bFracResults_C3",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *bFracResults_C2 = new TH1D("bFracResults_C2","bFracResults_C2",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *bFracResults_C1 = new TH1D("bFracResults_C1","bFracResults_C1",N_jetPtAxisEdges-1,jetPtAxisEdges);
	
  for(int i = 0; i < N_jetPtAxisEdges + 1; i++){

    if(i==0){
      
      bFracResults_pp->SetBinContent(i,0);
      bFracResults_pp->SetBinError(i,0);
      bFracResults_C4->SetBinContent(i,0);
      bFracResults_C4->SetBinError(i,0);
      bFracResults_C3->SetBinContent(i,0);
      bFracResults_C3->SetBinError(i,0);
      bFracResults_C2->SetBinContent(i,0);
      bFracResults_C2->SetBinError(i,0);
      bFracResults_C1->SetBinContent(i,0);
      bFracResults_C1->SetBinError(i,0);

    }
    else{

      bFracResults_pp->SetBinContent(i,results_pp[i-1]);
      bFracResults_pp->SetBinError(i,err_results_pp[i-1]);
      bFracResults_C4->SetBinContent(i,results_C4[i-1]);
      bFracResults_C4->SetBinError(i,err_results_C4[i-1]);
      bFracResults_C3->SetBinContent(i,results_C3[i-1]);
      bFracResults_C3->SetBinError(i,err_results_C3[i-1]);
      bFracResults_C2->SetBinContent(i,results_C2[i-1]);
      bFracResults_C2->SetBinError(i,err_results_C2[i-1]);
      bFracResults_C1->SetBinContent(i,results_C1[i-1]);
      bFracResults_C1->SetBinError(i,err_results_C1[i-1]);
			
    }

  }


  /////////////////////////////  generate histogram representations for the systematics
  
  TH1D *bFracSys_pp = (TH1D*) bFracResults_pp->Clone("bFracSys_pp");
  TH1D *bFracSys_C4 = (TH1D*) bFracResults_C4->Clone("bFracSys_C4");
  TH1D *bFracSys_C3 = (TH1D*) bFracResults_C3->Clone("bFracSys_C3");
  TH1D *bFracSys_C2 = (TH1D*) bFracResults_C2->Clone("bFracSys_C2");
  TH1D *bFracSys_C1 = (TH1D*) bFracResults_C1->Clone("bFracSys_C1");

  const int N_sys_sources = 6;

  double sys_total_pp_mu12_J1_array[N_sys_sources] = {sys_cFraction_pp_mu12_J1,
                                                      sys_lowerBound_pp_mu12_J1,
						      sys_JERsmear_pp_mu12_J1,
						      sys_bGS_pp_mu12_J1,
						      sys_JEUShiftCombined_pp_mu12_J1,
						      sys_centShiftCombined_pp_mu12_J1};

  double sys_total_pp_mu12_J2_array[N_sys_sources] = {sys_cFraction_pp_mu12_J2,
                                                      sys_lowerBound_pp_mu12_J2,
						      sys_JERsmear_pp_mu12_J2,
						      sys_bGS_pp_mu12_J2,
						      sys_JEUShiftCombined_pp_mu12_J2,
						      sys_centShiftCombined_pp_mu12_J2};

  double sys_total_pp_mu12_J3_array[N_sys_sources] = {sys_cFraction_pp_mu12_J3,
                                                      sys_lowerBound_pp_mu12_J3,
						      sys_JERsmear_pp_mu12_J3,
						      sys_bGS_pp_mu12_J3,
						      sys_JEUShiftCombined_pp_mu12_J3,
						      sys_centShiftCombined_pp_mu12_J3};

  double sys_total_pp_mu12_J4_array[N_sys_sources] = {sys_cFraction_pp_mu12_J4,
                                                      sys_lowerBound_pp_mu12_J4,
						      sys_JERsmear_pp_mu12_J4,
						      sys_bGS_pp_mu12_J4,
						      sys_JEUShiftCombined_pp_mu12_J4,
						      sys_centShiftCombined_pp_mu12_J4};

  double sys_total_pp_mu12_J5_array[N_sys_sources] = {sys_cFraction_pp_mu12_J5,
                                                      sys_lowerBound_pp_mu12_J5,
						      sys_JERsmear_pp_mu12_J5,
						      sys_bGS_pp_mu12_J5,
						      sys_JEUShiftCombined_pp_mu12_J5,
						      sys_centShiftCombined_pp_mu12_J5};

  double sys_total_pp_mu12_J6_array[N_sys_sources] = {sys_cFraction_pp_mu12_J6,
                                                      sys_lowerBound_pp_mu12_J6,
						      sys_JERsmear_pp_mu12_J6,
						      sys_bGS_pp_mu12_J6,
						      sys_JEUShiftCombined_pp_mu12_J6,
						      sys_centShiftCombined_pp_mu12_J6};



  // PbPb 50-80%
  double sys_total_PbPb_mu12_C4_J1_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C4_J1,
                                                           sys_lowerBound_PbPb_mu12_C4_J1,
							   sys_JERsmear_PbPb_mu12_C4_J1,
							   sys_bGS_PbPb_mu12_C4_J1,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J1,
							   sys_centShiftCombined_PbPb_mu12_C4_J1};

  double sys_total_PbPb_mu12_C4_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C4_J2,
                                                           sys_lowerBound_PbPb_mu12_C4_J2,
							   sys_JERsmear_PbPb_mu12_C4_J2,
							   sys_bGS_PbPb_mu12_C4_J2,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J2,
							   sys_centShiftCombined_PbPb_mu12_C4_J2};

  double sys_total_PbPb_mu12_C4_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C4_J3,
                                                           sys_lowerBound_PbPb_mu12_C4_J3,
							   sys_JERsmear_PbPb_mu12_C4_J3,
							   sys_bGS_PbPb_mu12_C4_J3,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J3,
							   sys_centShiftCombined_PbPb_mu12_C4_J3};

  double sys_total_PbPb_mu12_C4_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C4_J4,
                                                           sys_lowerBound_PbPb_mu12_C4_J4,
							   sys_JERsmear_PbPb_mu12_C4_J4,
							   sys_bGS_PbPb_mu12_C4_J4,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J4,
							   sys_centShiftCombined_PbPb_mu12_C4_J4};

  double sys_total_PbPb_mu12_C4_J5_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C4_J5,
                                                           sys_lowerBound_PbPb_mu12_C4_J5,
							   sys_JERsmear_PbPb_mu12_C4_J5,
							   sys_bGS_PbPb_mu12_C4_J5,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J5,
							   sys_centShiftCombined_PbPb_mu12_C4_J5};

  double sys_total_PbPb_mu12_C4_J6_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C4_J6,
                                                           sys_lowerBound_PbPb_mu12_C4_J6,
							   sys_JERsmear_PbPb_mu12_C4_J6,
							   sys_bGS_PbPb_mu12_C4_J6,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J6,
							   sys_centShiftCombined_PbPb_mu12_C4_J6};

  // PbPb 30-50%
  double sys_total_PbPb_mu12_C3_J1_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C3_J1,
                                                           sys_lowerBound_PbPb_mu12_C3_J1,
							   sys_JERsmear_PbPb_mu12_C3_J1,
							   sys_bGS_PbPb_mu12_C3_J1,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J1,
							   sys_centShiftCombined_PbPb_mu12_C3_J1};

  double sys_total_PbPb_mu12_C3_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C3_J2,
                                                           sys_lowerBound_PbPb_mu12_C3_J2,
							   sys_JERsmear_PbPb_mu12_C3_J2,
							   sys_bGS_PbPb_mu12_C3_J2,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J2,
							   sys_centShiftCombined_PbPb_mu12_C3_J2};

  double sys_total_PbPb_mu12_C3_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C3_J3,
                                                           sys_lowerBound_PbPb_mu12_C3_J3,
							   sys_JERsmear_PbPb_mu12_C3_J3,
							   sys_bGS_PbPb_mu12_C3_J3,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J3,
							   sys_centShiftCombined_PbPb_mu12_C3_J3};

  double sys_total_PbPb_mu12_C3_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C3_J4,
                                                           sys_lowerBound_PbPb_mu12_C3_J4,
							   sys_JERsmear_PbPb_mu12_C3_J4,
							   sys_bGS_PbPb_mu12_C3_J4,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J4,
							   sys_centShiftCombined_PbPb_mu12_C3_J4};

  double sys_total_PbPb_mu12_C3_J5_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C3_J5,
                                                           sys_lowerBound_PbPb_mu12_C3_J5,
							   sys_JERsmear_PbPb_mu12_C3_J5,
							   sys_bGS_PbPb_mu12_C3_J5,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J5,
							   sys_centShiftCombined_PbPb_mu12_C3_J5};

  double sys_total_PbPb_mu12_C3_J6_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C3_J6,
                                                           sys_lowerBound_PbPb_mu12_C3_J6,
							   sys_JERsmear_PbPb_mu12_C3_J6,
							   sys_bGS_PbPb_mu12_C3_J6,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J6,
							   sys_centShiftCombined_PbPb_mu12_C3_J6};



  // PbPb 10-30%
  double sys_total_PbPb_mu12_C2_J1_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J1,
                                                           sys_lowerBound_PbPb_mu12_C2_J1,
							   sys_JERsmear_PbPb_mu12_C2_J1,
							   sys_bGS_PbPb_mu12_C2_J1,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J1,
							   sys_centShiftCombined_PbPb_mu12_C2_J1};

  double sys_total_PbPb_mu12_C2_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J2,
                                                           sys_lowerBound_PbPb_mu12_C2_J2,
							   sys_JERsmear_PbPb_mu12_C2_J2,
							   sys_bGS_PbPb_mu12_C2_J2,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J2,
							   sys_centShiftCombined_PbPb_mu12_C2_J2};

  double sys_total_PbPb_mu12_C2_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J3,
                                                           sys_lowerBound_PbPb_mu12_C2_J3,
							   sys_JERsmear_PbPb_mu12_C2_J3,
							   sys_bGS_PbPb_mu12_C2_J3,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J3,
							   sys_centShiftCombined_PbPb_mu12_C2_J3};

  double sys_total_PbPb_mu12_C2_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J4,
                                                           sys_lowerBound_PbPb_mu12_C2_J4,
							   sys_JERsmear_PbPb_mu12_C2_J4,
							   sys_bGS_PbPb_mu12_C2_J4,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J4,
							   sys_centShiftCombined_PbPb_mu12_C2_J4};

  double sys_total_PbPb_mu12_C2_J5_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J5,
                                                           sys_lowerBound_PbPb_mu12_C2_J5,
							   sys_JERsmear_PbPb_mu12_C2_J5,
							   sys_bGS_PbPb_mu12_C2_J5,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J5,
							   sys_centShiftCombined_PbPb_mu12_C2_J5};

  double sys_total_PbPb_mu12_C2_J6_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C2_J6,
                                                           sys_lowerBound_PbPb_mu12_C2_J6,
							   sys_JERsmear_PbPb_mu12_C2_J6,
							   sys_bGS_PbPb_mu12_C2_J6,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J6,
							   sys_centShiftCombined_PbPb_mu12_C2_J6};

  // PbPb 0-10%
  double sys_total_PbPb_mu12_C1_J1_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J1,
                                                           sys_lowerBound_PbPb_mu12_C1_J1,
							   sys_JERsmear_PbPb_mu12_C1_J1,
							   sys_bGS_PbPb_mu12_C1_J1,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J1,
							   sys_centShiftCombined_PbPb_mu12_C1_J1};

  double sys_total_PbPb_mu12_C1_J2_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J2,
                                                           sys_lowerBound_PbPb_mu12_C1_J2,
							   sys_JERsmear_PbPb_mu12_C1_J2,
							   sys_bGS_PbPb_mu12_C1_J2,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J2,
							   sys_centShiftCombined_PbPb_mu12_C1_J2};

  double sys_total_PbPb_mu12_C1_J3_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J3,
                                                           sys_lowerBound_PbPb_mu12_C1_J3,
							   sys_JERsmear_PbPb_mu12_C1_J3,
							   sys_bGS_PbPb_mu12_C1_J3,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J3,
							   sys_centShiftCombined_PbPb_mu12_C1_J3};

  double sys_total_PbPb_mu12_C1_J4_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J4,
                                                           sys_lowerBound_PbPb_mu12_C1_J4,
							   sys_JERsmear_PbPb_mu12_C1_J4,
							   sys_bGS_PbPb_mu12_C1_J4,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J4,
							   sys_centShiftCombined_PbPb_mu12_C1_J4};

  double sys_total_PbPb_mu12_C1_J5_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J5,
                                                           sys_lowerBound_PbPb_mu12_C1_J5,
							   sys_JERsmear_PbPb_mu12_C1_J5,
							   sys_bGS_PbPb_mu12_C1_J5,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J5,
							   sys_centShiftCombined_PbPb_mu12_C1_J5};

  double sys_total_PbPb_mu12_C1_J6_array[N_sys_sources] = {sys_cFraction_PbPb_mu12_C1_J6,
                                                           sys_lowerBound_PbPb_mu12_C1_J6,
							   sys_JERsmear_PbPb_mu12_C1_J6,
							   sys_bGS_PbPb_mu12_C1_J6,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J6,
							   sys_centShiftCombined_PbPb_mu12_C1_J6};

  double sys_total_pp_mu12_J1 = 0;
  double sys_total_pp_mu12_J2 = 0;
  double sys_total_pp_mu12_J3 = 0;
  double sys_total_pp_mu12_J4 = 0;
  double sys_total_pp_mu12_J5 = 0;
  double sys_total_pp_mu12_J6 = 0;

  double sys_total_PbPb_mu12_C4_J1 = 0;
  double sys_total_PbPb_mu12_C4_J2 = 0;
  double sys_total_PbPb_mu12_C4_J3 = 0;
  double sys_total_PbPb_mu12_C4_J4 = 0;
  double sys_total_PbPb_mu12_C4_J5 = 0;
  double sys_total_PbPb_mu12_C4_J6 = 0;

  double sys_total_PbPb_mu12_C3_J1 = 0;
  double sys_total_PbPb_mu12_C3_J2 = 0;
  double sys_total_PbPb_mu12_C3_J3 = 0;
  double sys_total_PbPb_mu12_C3_J4 = 0;
  double sys_total_PbPb_mu12_C3_J5 = 0;
  double sys_total_PbPb_mu12_C3_J6 = 0;

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

    // PbPb 50-80%
    sys_total_PbPb_mu12_C4_J1 += sys_total_PbPb_mu12_C4_J1_array[i]*sys_total_PbPb_mu12_C4_J1_array[i];
    sys_total_PbPb_mu12_C4_J2 += sys_total_PbPb_mu12_C4_J2_array[i]*sys_total_PbPb_mu12_C4_J2_array[i];    
    sys_total_PbPb_mu12_C4_J3 += sys_total_PbPb_mu12_C4_J3_array[i]*sys_total_PbPb_mu12_C4_J3_array[i];
    sys_total_PbPb_mu12_C4_J4 += sys_total_PbPb_mu12_C4_J4_array[i]*sys_total_PbPb_mu12_C4_J4_array[i];
    sys_total_PbPb_mu12_C4_J5 += sys_total_PbPb_mu12_C4_J5_array[i]*sys_total_PbPb_mu12_C4_J5_array[i];
    sys_total_PbPb_mu12_C4_J6 += sys_total_PbPb_mu12_C4_J6_array[i]*sys_total_PbPb_mu12_C4_J6_array[i];

    // PbPb 30-50%
    sys_total_PbPb_mu12_C3_J1 += sys_total_PbPb_mu12_C3_J1_array[i]*sys_total_PbPb_mu12_C3_J1_array[i];
    sys_total_PbPb_mu12_C3_J2 += sys_total_PbPb_mu12_C3_J2_array[i]*sys_total_PbPb_mu12_C3_J2_array[i];    
    sys_total_PbPb_mu12_C3_J3 += sys_total_PbPb_mu12_C3_J3_array[i]*sys_total_PbPb_mu12_C3_J3_array[i];
    sys_total_PbPb_mu12_C3_J4 += sys_total_PbPb_mu12_C3_J4_array[i]*sys_total_PbPb_mu12_C3_J4_array[i];
    sys_total_PbPb_mu12_C3_J5 += sys_total_PbPb_mu12_C3_J5_array[i]*sys_total_PbPb_mu12_C3_J5_array[i];
    sys_total_PbPb_mu12_C3_J6 += sys_total_PbPb_mu12_C3_J6_array[i]*sys_total_PbPb_mu12_C3_J6_array[i];    
 
    // PbPb 10-30%
    sys_total_PbPb_mu12_C2_J1 += sys_total_PbPb_mu12_C2_J1_array[i]*sys_total_PbPb_mu12_C2_J1_array[i];
    sys_total_PbPb_mu12_C2_J2 += sys_total_PbPb_mu12_C2_J2_array[i]*sys_total_PbPb_mu12_C2_J2_array[i];    
    sys_total_PbPb_mu12_C2_J3 += sys_total_PbPb_mu12_C2_J3_array[i]*sys_total_PbPb_mu12_C2_J3_array[i];
    sys_total_PbPb_mu12_C2_J4 += sys_total_PbPb_mu12_C2_J4_array[i]*sys_total_PbPb_mu12_C2_J4_array[i];
    sys_total_PbPb_mu12_C2_J5 += sys_total_PbPb_mu12_C2_J5_array[i]*sys_total_PbPb_mu12_C2_J5_array[i];
    sys_total_PbPb_mu12_C2_J6 += sys_total_PbPb_mu12_C2_J6_array[i]*sys_total_PbPb_mu12_C2_J6_array[i];    

    // PbPb 0-10%
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

  sys_total_PbPb_mu12_C4_J1 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J1);
  sys_total_PbPb_mu12_C4_J2 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J2);
  sys_total_PbPb_mu12_C4_J3 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J3);
  sys_total_PbPb_mu12_C4_J4 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J4);
  sys_total_PbPb_mu12_C4_J5 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J5);
  sys_total_PbPb_mu12_C4_J6 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J6);

  sys_total_PbPb_mu12_C3_J1 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J1);
  sys_total_PbPb_mu12_C3_J2 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J2);
  sys_total_PbPb_mu12_C3_J3 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J3);
  sys_total_PbPb_mu12_C3_J4 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J4);
  sys_total_PbPb_mu12_C3_J5 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J5);
  sys_total_PbPb_mu12_C3_J6 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J6);

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

  double sys_array_pp[N_jetPtAxisEdges-1] = {sys_total_pp_mu12_J1,sys_total_pp_mu12_J2,sys_total_pp_mu12_J3,sys_total_pp_mu12_J4,sys_total_pp_mu12_J5,sys_total_pp_mu12_J6};
  double sys_array_C4[N_jetPtAxisEdges-1] = {sys_total_PbPb_mu12_C4_J1,sys_total_PbPb_mu12_C4_J2,sys_total_PbPb_mu12_C4_J3,sys_total_PbPb_mu12_C4_J4,sys_total_PbPb_mu12_C4_J5,sys_total_PbPb_mu12_C4_J6};
  double sys_array_C3[N_jetPtAxisEdges-1] = {sys_total_PbPb_mu12_C3_J1,sys_total_PbPb_mu12_C3_J2,sys_total_PbPb_mu12_C3_J3,sys_total_PbPb_mu12_C3_J4,sys_total_PbPb_mu12_C3_J5,sys_total_PbPb_mu12_C3_J6};
  double sys_array_C2[N_jetPtAxisEdges-1] = {sys_total_PbPb_mu12_C2_J1,sys_total_PbPb_mu12_C2_J2,sys_total_PbPb_mu12_C2_J3,sys_total_PbPb_mu12_C2_J4,sys_total_PbPb_mu12_C2_J5,sys_total_PbPb_mu12_C2_J6};
  double sys_array_C1[N_jetPtAxisEdges-1] = {sys_total_PbPb_mu12_C1_J1,sys_total_PbPb_mu12_C1_J2,sys_total_PbPb_mu12_C1_J3,sys_total_PbPb_mu12_C1_J4,sys_total_PbPb_mu12_C1_J5,sys_total_PbPb_mu12_C1_J6};

  
  for(int i = 0; i < N_jetPtAxisEdges + 1; i++){

    if(i==0){
      
      bFracSys_pp->SetBinContent(i,0);
      bFracSys_pp->SetBinError(i,0);
      bFracSys_C4->SetBinContent(i,0);
      bFracSys_C4->SetBinError(i,0);
      bFracSys_C3->SetBinContent(i,0);
      bFracSys_C3->SetBinError(i,0);
      bFracSys_C2->SetBinContent(i,0);
      bFracSys_C2->SetBinError(i,0);
      bFracSys_C1->SetBinContent(i,0);
      bFracSys_C1->SetBinError(i,0);

    }
    else{

      bFracSys_pp->SetBinContent(i,results_pp[i-1]);
      bFracSys_pp->SetBinError(i,bFracResults_pp->GetBinContent(i)*sys_array_pp[i-1]);
      bFracSys_C4->SetBinContent(i,results_C4[i-1]);
      bFracSys_C4->SetBinError(i,bFracResults_C4->GetBinContent(i)*sys_array_C4[i-1]);
      bFracSys_C3->SetBinContent(i,results_C3[i-1]);
      bFracSys_C3->SetBinError(i,bFracResults_C3->GetBinContent(i)*sys_array_C3[i-1]);
      bFracSys_C2->SetBinContent(i,results_C2[i-1]);
      bFracSys_C2->SetBinError(i,bFracResults_C2->GetBinContent(i)*sys_array_C2[i-1]);
      bFracSys_C1->SetBinContent(i,results_C1[i-1]);
      bFracSys_C1->SetBinError(i,bFracResults_C1->GetBinContent(i)*sys_array_C1[i-1]);
			
    }

  }






  

  m->Add(g0);
  m->Add(g1);
  m->Add(g2);
  m->Add(g3);
  m->Add(g4);
 

  m->GetYaxis()->SetTitleSize(0.06);
  m->GetXaxis()->SetTitleSize(0.06);
  m->GetYaxis()->SetLabelSize(0.045);
  m->GetXaxis()->SetLabelSize(0.045);
  //m->GetYaxis()->SetTitle("#font[52]{b} jet purity");
  m->GetYaxis()->SetTitle("#it{f}_{#it{b}}^{#it{#mu}-tag,#it{#mu}-trig}");
  m->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");

  m->GetYaxis()->SetRangeUser(0,1);

  m->Draw("AP");
  m->SetTitle("Nominal templates");

  TLegend *leg = new TLegend(0.46,0.75,0.75,0.88);
  
  leg->AddEntry(g0,"pp","p");
  leg->AddEntry(g4,"PbPb 50-80%","p");
  leg->AddEntry(g3,"PbPb 30-50%","p");
  leg->AddEntry(g2,"PbPb 10-30%","p");
  leg->AddEntry(g1,"PbPb 0-10%","p");
  
  leg->SetBorderSize(0);
  leg->SetTextSize(0.032);
  leg->Draw();




  canv->SaveAs("../../figures/bPurity/bPurity.pdf");




  TCanvas *canv_pp = new TCanvas("canv_pp","canv_pp",700,700);
  canv_pp->cd();
  TPad *pad_pp = new TPad("pad_pp","pad_pp",0,0,1,1);
  pad_pp->SetLeftMargin(0.15);
  pad_pp->SetBottomMargin(0.15);
  pad_pp->Draw();
  pad_pp->cd();

  bFracResults_pp->SetLineColor(kBlack);
  bFracResults_pp->SetLineWidth(2);
  bFracResults_pp->SetMarkerColor(kBlack);
  bFracResults_pp->SetMarkerStyle(20);
  bFracResults_pp->SetMarkerSize(1.4);

  bFracResults_pp->GetYaxis()->SetRangeUser(0,1);
  bFracResults_pp->GetXaxis()->SetRangeUser(jetPtAxisEdges[0],jetPtAxisEdges[N_jetPtAxisEdges-1]);
  
  bFracResults_pp->Draw();

  bFracSys_pp->SetFillColorAlpha(kBlack,1.0);
  bFracSys_pp->SetFillStyle(3345);
  bFracSys_pp->Draw("e2 same");





  TCanvas *canv_C4 = new TCanvas("canv_C4","canv_C4",700,700);
  canv_C4->cd();
  TPad *pad_C4 = new TPad("pad_C4","pad_C4",0,0,1,1);
  pad_C4->SetLeftMargin(0.15);
  pad_C4->SetBottomMargin(0.15);
  pad_C4->Draw();
  pad_C4->cd();

  bFracResults_C4->SetLineColor(kBlue+1);
  bFracResults_C4->SetLineWidth(2);
  bFracResults_C4->SetMarkerColor(kBlue+1);
  bFracResults_C4->SetMarkerStyle(20);
  bFracResults_C4->SetMarkerSize(1.4);

  bFracResults_C4->GetYaxis()->SetRangeUser(0,1);
  bFracResults_C4->GetXaxis()->SetRangeUser(jetPtAxisEdges[0],jetPtAxisEdges[N_jetPtAxisEdges-1]);
  
  bFracResults_C4->Draw();

  bFracSys_C4->SetFillColorAlpha(kBlue+1,1.0);
  bFracSys_C4->SetFillStyle(3345);
  bFracSys_C4->Draw("e2 same");


  TCanvas *canv_C3 = new TCanvas("canv_C3","canv_C3",700,700);
  canv_C3->cd();
  TPad *pad_C3 = new TPad("pad_C3","pad_C3",0,0,1,1);
  pad_C3->SetLeftMargin(0.15);
  pad_C3->SetBottomMargin(0.15);
  pad_C3->Draw();
  pad_C3->cd();

  bFracResults_C3->SetLineColor(kRed-4);
  bFracResults_C3->SetLineWidth(2);
  bFracResults_C3->SetMarkerColor(kRed-4);
  bFracResults_C3->SetMarkerStyle(20);
  bFracResults_C3->SetMarkerSize(1.4);

  bFracResults_C3->GetYaxis()->SetRangeUser(0,1);
  bFracResults_C3->GetXaxis()->SetRangeUser(jetPtAxisEdges[0],jetPtAxisEdges[N_jetPtAxisEdges-1]);
  
  bFracResults_C3->Draw();

  bFracSys_C3->SetFillColorAlpha(kRed-4,1.0);
  bFracSys_C3->SetFillStyle(3345);
  bFracSys_C3->Draw("e2 same");


  TCanvas *canv_C2 = new TCanvas("canv_C2","canv_C2",700,700);
  canv_C2->cd();
  TPad *pad_C2 = new TPad("pad_C2","pad_C2",0,0,1,1);
  pad_C2->SetLeftMargin(0.15);
  pad_C2->SetBottomMargin(0.15);
  pad_C2->Draw();
  pad_C2->cd();

  bFracResults_C2->SetLineColor(kGreen+2);
  bFracResults_C2->SetLineWidth(2);
  bFracResults_C2->SetMarkerColor(kGreen+2);
  bFracResults_C2->SetMarkerStyle(20);
  bFracResults_C2->SetMarkerSize(1.4);

  bFracResults_C2->GetYaxis()->SetRangeUser(0,1);
  bFracResults_C2->GetXaxis()->SetRangeUser(jetPtAxisEdges[0],jetPtAxisEdges[N_jetPtAxisEdges-1]);
  
  bFracResults_C2->Draw();

  bFracSys_C2->SetFillColorAlpha(kGreen+2,1.0);
  bFracSys_C2->SetFillStyle(3345);
  bFracSys_C2->Draw("e2 same");


  TCanvas *canv_C1 = new TCanvas("canv_C1","canv_C1",700,700);
  canv_C1->cd();
  TPad *pad_C1 = new TPad("pad_C1","pad_C1",0,0,1,1);
  pad_C1->SetLeftMargin(0.15);
  pad_C1->SetBottomMargin(0.15);
  pad_C1->Draw();
  pad_C1->cd();

  bFracResults_C1->SetLineColor(kMagenta-9);
  bFracResults_C1->SetLineWidth(2);
  bFracResults_C1->SetMarkerColor(kMagenta-9);
  bFracResults_C1->SetMarkerStyle(20);
  bFracResults_C1->SetMarkerSize(1.4);

  bFracResults_C1->GetYaxis()->SetRangeUser(0,1);
  bFracResults_C1->GetXaxis()->SetRangeUser(jetPtAxisEdges[0],jetPtAxisEdges[N_jetPtAxisEdges-1]);
  
  bFracResults_C1->Draw();

  bFracSys_C1->SetFillColorAlpha(kMagenta-9,1.0);
  bFracSys_C1->SetFillStyle(3345);
  bFracSys_C1->Draw("e2 same");



  TCanvas *canv_all = new TCanvas("canv_all","canv_all",2500,700);
  canv_all->Divide(5,1);
  canv_all->cd(1);
  TPad *pad_all_1 = new TPad("pad_all_1","pad_all_1",0,0,1,1);
  pad_all_1->SetRightMargin(0.0);
  pad_all_1->Draw();
  pad_all_1->cd();
  bFracResults_pp->SetStats(0);
  bFracResults_pp->SetTitle("pp");
  bFracResults_pp->GetYaxis()->SetTitle("#it{b}-jet purity");
  bFracResults_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  bFracResults_pp->Draw();
  bFracSys_pp->Draw("e2 same");
  canv_all->cd(2);
  TPad *pad_all_2 = new TPad("pad_all_2","pad_all_2",0,0,1,1);
  pad_all_2->SetLeftMargin(0.0);
  pad_all_2->SetRightMargin(0);
  pad_all_2->Draw();
  pad_all_2->cd();
  bFracResults_C4->GetYaxis()->SetLabelSize(0);
  bFracResults_C4->GetYaxis()->SetLabelOffset(0);
  bFracResults_C4->SetStats(0);
  bFracResults_C4->SetTitle("PbPb 50-80%");
  bFracResults_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  bFracResults_C4->Draw();
  bFracSys_C4->Draw("e2 same");
  canv_all->cd(3);
  TPad *pad_all_3 = new TPad("pad_all_3","pad_all_3",0,0,1,1);
  pad_all_3->SetLeftMargin(0);
  pad_all_3->SetRightMargin(0);
  pad_all_3->Draw();
  pad_all_3->cd();
  bFracResults_C3->SetStats(0);
  bFracResults_C3->SetTitle("PbPb 30-50%");
  bFracResults_C3->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  bFracResults_C3->Draw();
  bFracSys_C3->Draw("e2 same");
  canv_all->cd(4);
  TPad *pad_all_4 = new TPad("pad_all_4","pad_all_4",0,0,1,1);
  pad_all_4->SetLeftMargin(0);
  pad_all_4->SetRightMargin(0);
  pad_all_4->Draw();
  pad_all_4->cd();
  bFracResults_C2->SetStats(0);
  bFracResults_C2->SetTitle("PbPb 10-30%");
  bFracResults_C2->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  bFracResults_C2->Draw();
  bFracSys_C2->Draw("e2 same");
  canv_all->cd(5);
  TPad *pad_all_5 = new TPad("pad_all_5","pad_all_5",0,0,1,1);
  pad_all_5->SetLeftMargin(0);
  pad_all_5->Draw();
  pad_all_5->cd();
  bFracResults_C1->SetStats(0);
  bFracResults_C1->SetTitle("PbPb 0-10%");
  bFracResults_C1->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  bFracResults_C1->Draw();
  bFracSys_C1->Draw("e2 same");  

  canv_all->SaveAs("../../figures/bPurity/bPurity_all.pdf");
  
  
  TFile *bFracResults_PYTHIAHYDJET = TFile::Open(output_file_string.c_str(),"recreate");
	
  bFracResults_pp->Write();
  bFracResults_C4->Write();
  bFracResults_C3->Write();
  bFracResults_C2->Write();
  bFracResults_C1->Write();

  bFracResults_PYTHIAHYDJET->Close();
  

}

