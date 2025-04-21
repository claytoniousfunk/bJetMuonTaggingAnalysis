
#include "../templateFitter/templateFitter_projectableTemplates.h"

void bPurityCalculator_projectableTemplates(){

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
  // const int N_jetPtAxisEdges = 14;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {80,85,90,95,100,105,110,120,130,140,150,170,200,300};

  // const int N_jetPtAxisEdges = 8;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {80,85,90,100,120,150,200,500};

  // const int N_jetPtAxisEdges = 9;
  // double jetPtAxisEdges[N_jetPtAxisEdges] = {80,85,90,95,100,110,130,220,500};

  const int N_jetPtAxisEdges = 5;
  double jetPtAxisEdges[N_jetPtAxisEdges] = {100,110,120,150,220};
  
  double jetPtCenters[N_jetPtAxisEdges-1];
  double jetPtWidths[N_jetPtAxisEdges-1];

  for(int i = 0; i < N_jetPtAxisEdges-1; i++){
    jetPtCenters[i] = (jetPtAxisEdges[i+1] + jetPtAxisEdges[i])/2.;
    jetPtWidths[i] = (jetPtAxisEdges[i+1] - jetPtAxisEdges[i])/2;
  }
  

  
  double results_pp[N_jetPtAxisEdges-1], err_results_pp[N_jetPtAxisEdges-1];
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
  double pTrel_fit_high = 5.0;

  double c_multiplier = 1.0;
  double bGS_multiplier = 1.0;

  int do_JER_smear = 0;
  int do_JEU_up = 0;
  int do_JEU_down = 0;

  int do_bJetEnergyShift = 0;

  string output_file_string = Form("../../rootFiles/bPurityResults/final/bPurityResults_DATA-%i_mergeB-%i_mergeC-%i_pTrel-%1.1fto%1.1f_cMult-%1.1f_bMult-%1.1f_JERsmear-%i_JEUShiftUp-%i_JEUShiftDown-%i_bJetEnergyShift-%i.root",do_data,do_mergeB,do_mergeC,pTrel_fit_low,pTrel_fit_high,c_multiplier,bGS_multiplier,do_JER_smear,do_JEU_up,do_JEU_down,do_bJetEnergyShift);

  cout << output_file_string.c_str() << endl;


  for(int i = 0; i < N_jetPtAxisEdges-1; i++){
    results_pp[i] = templateFitter(do_data, 1,0,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 1);
    err_results_pp[i] = templateFitter(do_data, 1,0,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 2);

    results_C2[i] = templateFitter(do_data, 0,0,1, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 1);
    err_results_C2[i] = templateFitter(do_data, 0,0,1, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 2);

    results_C1[i] = templateFitter(do_data, 0,1,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 1);
    err_results_C1[i] = templateFitter(do_data, 0,1,0, jetPtAxisEdges[i],jetPtAxisEdges[i+1], do_mergeC,do_mergeB, do_2tempFit,do_3tempFit, pTrel_fit_low,pTrel_fit_high, c_multiplier, bGS_multiplier, 2);

    
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
  TGraphErrors *g1 = new TGraphErrors(N_jetPtAxisEdges-1,jetPtCenters,results_C2,jetPtWidths,err_results_C2);
  TGraphErrors *g2 = new TGraphErrors(N_jetPtAxisEdges-1,jetPtCenters,results_C1,jetPtWidths,err_results_C1);
	
  g0->SetLineColor(kBlack);
  g0->SetMarkerColor(kBlack);
  g0->SetMarkerStyle(22);
  g0->SetMarkerSize(1.2);

  g1->SetLineColor(kRed-4);
  g1->SetMarkerColor(kRed-4);
  g1->SetMarkerStyle(20);
  g1->SetMarkerSize(1.2);

  g2->SetLineColor(kBlue-4);
  g2->SetMarkerColor(kBlue-4);
  g2->SetMarkerStyle(21);
  g2->SetMarkerSize(1.2);
	


  /////////////////////////////  generate histogram representations for the b-jet fraction
  
  TH1D *bFracResults_pp = new TH1D("bFracResults_pp","bFracResults_pp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *bFracResults_C2 = new TH1D("bFracResults_C2","bFracResults_C2",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *bFracResults_C1 = new TH1D("bFracResults_C1","bFracResults_C1",N_jetPtAxisEdges-1,jetPtAxisEdges);
	
  for(int i = 0; i < N_jetPtAxisEdges + 1; i++){

    if(i==0){
			
      bFracResults_pp->SetBinContent(i,0);
      bFracResults_pp->SetBinError(i,0);
      bFracResults_C2->SetBinContent(i,0);
      bFracResults_C2->SetBinError(i,0);
      bFracResults_C1->SetBinContent(i,0);
      bFracResults_C1->SetBinError(i,0);

    }
    else{

      bFracResults_pp->SetBinContent(i,results_pp[i-1]);
      bFracResults_pp->SetBinError(i,err_results_pp[i-1]);
      bFracResults_C2->SetBinContent(i,results_C2[i-1]);
      bFracResults_C2->SetBinError(i,err_results_C2[i-1]);
      bFracResults_C1->SetBinContent(i,results_C1[i-1]);
      bFracResults_C1->SetBinError(i,err_results_C1[i-1]);
			
    }

  }


  m->Add(g0);
  m->Add(g1);
  m->Add(g2);
 

  m->GetYaxis()->SetTitleSize(0.06);
  m->GetXaxis()->SetTitleSize(0.06);
  m->GetYaxis()->SetLabelSize(0.045);
  m->GetXaxis()->SetLabelSize(0.045);
  //m->GetYaxis()->SetTitle("#font[52]{b} jet purity");
  m->GetYaxis()->SetTitle("#it{f}_{#it{b}}^{#it{#mu}-tagged,#it{#mu}-trig}");
  m->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");

  m->GetYaxis()->SetRangeUser(0,1);

  m->Draw("AP");
  m->SetTitle("Nominal templates");

  TLegend *leg = new TLegend(0.46,0.75,0.75,0.88);
  
  leg->AddEntry(g0,"pp","p");
  leg->AddEntry(g1,"PbPb 30-90%","p");
  leg->AddEntry(g2,"PbPb 0-30%","p");
  
  leg->SetBorderSize(0);
  leg->SetTextSize(0.032);
  leg->Draw();




  canv->SaveAs("../../figures/bPurity/bPurity.pdf");
  
  TFile *bFracResults_PYTHIAHYDJET = TFile::Open(output_file_string.c_str(),"recreate");
	
  bFracResults_pp->Write();
  bFracResults_C2->Write();
  bFracResults_C1->Write();

  bFracResults_PYTHIAHYDJET->Close();
  

}

