









double JES_fit(double *x, double *par){
  double xx = x[0];
  //double fitval = par[0]*TMath::Exp(-1.0*par[1]*x[0]) + par[2]*TMath::Exp(-1.0*par[3]*x[0]) + par[4]*TMath::Exp(-1.0*par[5]*x[0])+par[6];
  //double fitval = par[0]*TMath::Exp(-1.0*par[1]*x[0])+par[2]*TMath::Exp(-1.0*par[3]*x[0]);
  double fitval = TMath::Sqrt(par[0]*par[0] + par[1]*par[1]/x[0] + par[2]*par[2]/(x[0]*x[0]))  ;
  return fitval;
}

double fitfxn(double *x, double *par){
  double pt = x[0];

  double fitval = par[0]*TMath::Gaus(x[0],par[1],par[2]) + par[3]*TMath::Landau(-x[0],-par[1],par[2]); // reflected-Landu -- use for JES

  //double fitval = par[0]*TMath::Gaus(x[0],par[1],par[2]) + par[3]*TMath::Landau(x[0],par[1],par[2]); // normal Landau -- use for JES-yield-correction
  
  return fitval;
}

double fitfxn_onlyGaus(double *x, double *par){
  double pt = x[0];

  double fitval = par[0]*TMath::Gaus(x[0],par[1],par[2]); // Gaussian -- use for JER

  //double fitval = par[0]*TMath::Gaus(x[0],par[1],par[2]) + par[3]*TMath::Landau(x[0],par[1],par[2]); // normal Landau -- use for JES-yield-correction
  
  return fitval;
}




void muptrelResolutionCalculator_pt(bool ispp = 1,
				    bool isC3 = 0,
				    bool isC2 = 0,
				    bool isC1 = 0,
				    bool isJ1 = 1,
				    bool isJ2 = 0,
				    bool isJ3 = 0){


  TLatex *la = new TLatex();
  
  gStyle->SetOptFit(0111);

  
  bool isPeriph = 0;
  bool isNom = 0;
  
  // bool isC3 = 0;
  // bool isC4 = 0;

  bool isCent = 0;

  TFile *f1, *f2;



  //if(ispp) f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_doBJetEnergyShift.root");
  //if(ispp) f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu7_response.root");
  //if (ispp) f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_withReco_muTaggedJets_moreFlavors.root");

  //if (ispp) f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets.root");
  if(ispp) f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/final/allTemplates/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjet_jetTrkMaxFilter_vzReweight_jetPtReweight_dRReweight_projectableTemplates_allTemplates.root");
  //if(ispp) f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/final/response/PYTHIA_response_pThat-15_inclJets.root");
  //if (ispp) f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_muTaggedJets_doBJetNeutrinoEnergyShift.root");
  //if (ispp) f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets_doJERCorrection.root");
  //if (ispp) f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_muTaggedJets_doNeutrinoEnergyAddition.root");

  //if(ispp) f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_withReco_allJets.root");
  //if(ispp) f1 = TFile::Open("~/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/PYTHIA/PYTHIA_response_JEU_up.root");
  //if(ispp) f1 = TFile::Open("~/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/PYTHIA/PYTHIA_response_JEU_down.root");
  //if(ispp) f1 = TFile::Open("~/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/PYTHIA/PYTHIA_response_JEU_down.root");
  //if(ispp) f1 = TFile::Open("/home/clayton/Analysis/code/HLTAnalysis/rootFiles/L1Ntuples/PYTHIA_response_L1Objects.root");
  //if(ispp) f1 = TFile::Open("/home/clayton/Analysis/code/triggerAnalysis/out.root");

  //else f1 = TFile::Open("~/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/PYTHIAHYDJET_DiJet_response.root"); // neutrinos included in genJets
  //else f1 = TFile::Open("~/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/PYTHIAHYDJET_DiJet_response_pthat30.root"); // neutrinos included in genJets
  //else f1 = TFile::Open("~/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/PYTHIAHYDJET/PYTHIAHYDJET_DiJet_response_JEU_up.root"); // neutrinos included in genJets
  //else f1 = TFile::Open("~/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/PYTHIAHYDJET/PYTHIAHYDJET_DiJet_response_JEU_down.root"); // neutrinos included in genJets
  //else f1 = TFile::Open("~/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/PYTHIAHYDJET_DiJet_excludeNeutrinos_response.root"); // neutrinos excluded in genJets
  //else f1 = TFile::Open("~/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/official/PYTHIAHYDJET_DiJet_response_mu12_tight_pTmu-14_pThat-30.root");  // mu-tagged jets (must be right?)
  //else f1 = TFile::Open("/home/clayton/Analysis/code/skimming/PYTHIAHYDJET_scan/rootFiles/response/PYTHIAHYDJET_response_19Aug22.root");
  //else f1 = TFile::Open("/home/clayton/Analysis/code/skimming/PYTHIAHYDJET_scan/rootFiles/response/PYTHIAHYDJET_DiJet_MuJetsOnly_CsJets_response_12June23.root");

  //else f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/PH_DiJet_pTjet-5_pThat-15_response_fineCentBins.root");  // new forest
  //else f1 = TFile::Open("~/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/PH_DiJet_pTjet-5_pThat-15_response_muTaggedJets.root");  // new forest
  else f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-40_hiHFcut_removeHYDJETjet_jetTrkMaxFilter_vzReweight_hiBinReweight_fineCentBins_projectableTemplates_allTemplates.root");  // new forest

    
  TH2D *h1, *h2, *h3, *h4, *h5, *h6, *h7;
  TH2D *a1, *a2, *a3, *a4, *a5, *a6, *a7; // for merging

  bool mergeCentralities = 0;

  bool mergeQuarks = 0; // combine all the quarks together
    
  bool mergeLights = 1;

  TString JString = "";
  if(isJ1) JString = "J1";
  else if(isJ2) JString = "J2";
  else if(isJ3) JString = "J3";
  else{};

  if(ispp){
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_allJets_%s",JString.Data()),h1);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_udJets_%s",JString.Data()),h2);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_sJets_%s",JString.Data()),h3);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_gJets_%s",JString.Data()),h4);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_cJets_%s",JString.Data()),h5);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_%s",JString.Data()),h6);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_%s",JString.Data()),h7);

    // f1->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_allJets",h1);
    // f1->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_udJets",h2);
    // f1->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_sJets",h3);
    // f1->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_gJets",h4);
    // f1->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_cJets",h5);
    // f1->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_bJets",h6);
    // f1->GetObject("h_matchedRecoJetPtOverGenJetPt_recoJetPt_bJets",h7);

    // f1->GetObject("H_hlt_forest_pt",h1);
    // f1->GetObject("H_hlt_forest_pt",h2);
    // f1->GetObject("H_hlt_forest_pt",h3);
    // f1->GetObject("H_hlt_forest_pt",h4);
    // f1->GetObject("H_hlt_forest_pt",h5);
    // f1->GetObject("H_hlt_forest_pt",h6);
    // f1->GetObject("H_hlt_forest_pt",h7);

    
  }
  
  else if(isC3){

    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_allJets_C4%s",JString.Data()),h1);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_udJets_C4%s",JString.Data()),h2);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_sJets_C4%s",JString.Data()),h3);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_gJets_C4%s",JString.Data()),h4);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_cJets_C4%s",JString.Data()),h5);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_C4%s",JString.Data()),h6);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_C4%s",JString.Data()),h7);

    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_allJets_C3%s",JString.Data()),a1);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_udJets_C3%s",JString.Data()),a2);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_sJets_C3%s",JString.Data()),a3);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_gJets_C3%s",JString.Data()),a4);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_cJets_C3%s",JString.Data()),a5);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_C3%s",JString.Data()),a6);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_C3%s",JString.Data()),a7);

    h1->Add(a1);
    h2->Add(a2);
    h3->Add(a3);
    h4->Add(a4);
    h5->Add(a5);
    h6->Add(a6);
    h7->Add(a7);
      
  }
  else if(isC2){


    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_allJets_C2%s",JString.Data()),h1);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_udJets_C2%s",JString.Data()),h2);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_sJets_C2%s",JString.Data()),h3);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_gJets_C2%s",JString.Data()),h4);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_cJets_C2%s",JString.Data()),h5);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_C2%s",JString.Data()),h6);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_C2%s",JString.Data()),h7);
    
  }
  else if(isC1){

    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_allJets_C1%s",JString.Data()),h1);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_udJets_C1%s",JString.Data()),h2);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_sJets_C1%s",JString.Data()),h3);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_gJets_C1%s",JString.Data()),h4);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_cJets_C1%s",JString.Data()),h5);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_C1%s",JString.Data()),h6);
    f1->GetObject(Form("h_muptrelRecoJetRecoMuonOverMuptrelGenJetGenMuon_muptrelGenJetGenMuon_bJets_C1%s",JString.Data()),h7);
    
  }
 
  else{} ;
  

  if(mergeCentralities && (isC1 || isC2)){
    h1->Add(a1);
    h2->Add(a2);
    h3->Add(a3);
    h4->Add(a4);
    h5->Add(a5);
    h6->Add(a6);
    h6->Add(a7);
  }

  if(mergeQuarks){
    h2->Add(h3);
    h2->Add(h5);
    h2->Add(h6);
  }
  if(mergeLights){
    h2->Add(h3);
    h2->Add(h4);
  }
  

 

  
    

  TH1D *hx_test=h2->ProjectionY();
  TAxis *xaxis = hx_test->GetXaxis();
    
    
  //const int Nbins = 7;
  // double pt_axis[Nbins] = {100,150,200,260,320,400,500};

  //const int Nbins = 20;
  //double pt_axis[Nbins] = {60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,240,260,300};

  // const int Nbins = 22;
  // double pt_axis[Nbins] = {60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,240,260,300,350,400};

  // const int Nbins = 17;
  // double pt_axis[Nbins] = {40,50,60,80,100,120,140,160,180,200,220,240,260,300,350,400,500};

  // const int Nbins = 12;
  // double pt_axis[Nbins] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.5,1.8,2.4,3.5,5.0};

  const int Nbins = 8;
  double pt_axis[Nbins] = {0.0,0.4,0.8,1.2,1.8,2.4,3.5,5.0};

  //const int Nbins = 2;
  //double pt_axis[Nbins] = {110,120};

  //const int Nbins = 9;
  //double pt_axis[Nbins] = {20,40,60,80,100,120,150,200,300};
  
  //const int Nbins = 9;
  //double pt_axis[Nbins] = {0,10,20,30,40,50,60,70,80};

  //const int Nbins = 11;
  //double pt_axis[Nbins] = {60,70,80,90,100,110,120,130,140,160,200};

  //const int Nbins = 6;
  //double pt_axis[Nbins] = {60,80,110,140,170,300};

  //const int Nbins = 4;
  //double pt_axis[Nbins] = {60,80,120,200};

  TH1D *h_fit_i = new TH1D("h_fit_i","h_fit_i",Nbins-1,pt_axis);
  TH1D *h_fit_b = new TH1D("h_fit_b","h_fit_b",Nbins-1,pt_axis);

  double x[Nbins-1];
  double left[Nbins-1];
  double ept_axis[Nbins-1];

    
  int firstxbin = 0;
  int lastxbin = 0;

  double M1[Nbins-1], M2[Nbins-1], M3[Nbins-1], M4[Nbins-1], M5[Nbins-1], M6[Nbins-1], M7[Nbins-1];
  double eM1[Nbins-1], eM2[Nbins-1], eM3[Nbins-1], eM4[Nbins-1], eM5[Nbins-1], eM6[Nbins-1], eM7[Nbins-1];
  double S1[Nbins-1], S2[Nbins-1], S3[Nbins-1], S4[Nbins-1], S5[Nbins-1], S6[Nbins-1], S7[Nbins-1];
  double eS1[Nbins-1], eS2[Nbins-1], eS3[Nbins-1], eS4[Nbins-1], eS5[Nbins-1], eS6[Nbins-1], eS7[Nbins-1];

    
  TH1D *h1_y, *h2_y, *h3_y, *h4_y, *h5_y, *h6_y, *h7_y;
  TF1 *fit1, *fit2, *fit3, *fit4, *fit5, *fit6, *fit7;
  double mu1, emu1, sig1, esig1;
  double mu2, emu2, sig2, esig2;
  double mu3, emu3, sig3, esig3;
  double mu4, emu4, sig4, esig4;
  double mu5, emu5, sig5, esig5;
  double mu6, emu6, sig6, esig6;
  double mu7, emu7, sig7, esig7;


  // int N_fit_params = 4;
  // TF1 *fxn1 = new TF1("fxn1",fitfxn,0,5,N_fit_params);
  // TF1 *fxn2 = new TF1("fxn2",fitfxn,0,5,N_fit_params);
  // TF1 *fxn3 = new TF1("fxn3",fitfxn,0,5,N_fit_params);
  // TF1 *fxn4 = new TF1("fxn4",fitfxn,0,5,N_fit_params);
  // TF1 *fxn5 = new TF1("fxn5",fitfxn,0,5,N_fit_params);
  // TF1 *fxn6 = new TF1("fxn6",fitfxn,0,5,N_fit_params);
  // TF1 *fxn7 = new TF1("fxn7",fitfxn,0,5,N_fit_params);

  int N_fit_params = 3;
  TF1 *fxn1 = new TF1("fxn1",fitfxn_onlyGaus,0,5,N_fit_params);
  TF1 *fxn2 = new TF1("fxn2",fitfxn_onlyGaus,0,5,N_fit_params);
  TF1 *fxn3 = new TF1("fxn3",fitfxn_onlyGaus,0,5,N_fit_params);
  TF1 *fxn4 = new TF1("fxn4",fitfxn_onlyGaus,0,5,N_fit_params);
  TF1 *fxn5 = new TF1("fxn5",fitfxn_onlyGaus,0,5,N_fit_params);
  TF1 *fxn6 = new TF1("fxn6",fitfxn_onlyGaus,0,5,N_fit_params);
  TF1 *fxn7 = new TF1("fxn7",fitfxn_onlyGaus,0,5,N_fit_params);

  TCanvas *ctmp = new TCanvas("ctmp","ctmp",600,600);
  TPad *ptmp = new TPad("ptmp","ptmp",0,0,1,1);
  ptmp->SetLeftMargin(0.2);
  ptmp->SetBottomMargin(0.2);
  ctmp->cd();
  ptmp->Draw();
  ptmp->cd();

    
    
  for(int i = 0; i < Nbins-1; i++){

    x[i] = (pt_axis[i+1]+pt_axis[i])/2;
    ept_axis[i] = (pt_axis[i+1] - pt_axis[i])/2;

    cout << "i = " << i << ", x[i] = " << x[i] << endl;

    firstxbin = xaxis->FindBin(pt_axis[i]+0.001);
    lastxbin = xaxis->FindBin(pt_axis[i+1]-0.001);



    
    left[i] = pt_axis[i];
    
    h1_y = h1->ProjectionX("h1_y",firstxbin,lastxbin); // allJets
    h2_y = h2->ProjectionX("h2_y",firstxbin,lastxbin); // udJets
    h3_y = h3->ProjectionX("h3_y",firstxbin,lastxbin); // sJets
    h4_y = h4->ProjectionX("h4_y",firstxbin,lastxbin); // gJets
    h5_y = h5->ProjectionX("h5_y",firstxbin,lastxbin); // cJets
    h6_y = h6->ProjectionX("h6_y",firstxbin,lastxbin); // bJets
    h7_y = h7->ProjectionX("h7_y",firstxbin,lastxbin); // bJets, neutrinos excluded in genJets


    h1_y->Scale(1./h1_y->Integral());
    h2_y->Scale(1./h2_y->Integral());
    h3_y->Scale(1./h3_y->Integral());
    h4_y->Scale(1./h4_y->Integral());
    h5_y->Scale(1./h5_y->Integral());
    h6_y->Scale(1./h6_y->Integral());
    h7_y->Scale(1./h7_y->Integral());
       
    double sigmaParMin = 0.0;
    double sigmaParMax = 0.6;
    double muParLimLow = 0.4;
    double muParLimHigh = 1.6;
   
     
    double maxBinVal_1 = h1_y->GetMean();
    double maxBinVal_2 = h2_y->GetMean();
    double maxBinVal_3 = h3_y->GetMean();
    double maxBinVal_4 = h4_y->GetMean();
    double maxBinVal_5 = h5_y->GetMean();
    double maxBinVal_6 = h6_y->GetMean();
    double maxBinVal_7 = h7_y->GetMean();

    double initStdDev_1 = h1_y->GetStdDev();
    double initStdDev_2 = h2_y->GetStdDev();
    double initStdDev_3 = h3_y->GetStdDev();
    double initStdDev_4 = h4_y->GetStdDev();
    double initStdDev_5 = h5_y->GetStdDev();
    double initStdDev_6 = h6_y->GetStdDev();
    double initStdDev_7 = h7_y->GetStdDev();

    // double fitLow = 0.0;
    // double fitHigh = 2.0;

    double fitLow = 0.5; // use this range for JES
    double fitHigh = 1.2;

    // double fitLow = 0.3; // use this range for JES-yield-correction
    // double fitHigh = 2.0;

    TString fitOptionString = "WL R";

    h1_y->Draw();

    cout << "maxBinVal_1 = " << maxBinVal_1 << endl;
    cout << "initStdDev_1 = " << initStdDev_1 << endl;

    
    fxn1->SetParameter(0,0.04);
    fxn1->SetParameter(1,maxBinVal_1);
    fxn1->SetParameter(2,initStdDev_1);
    fxn1->SetParameter(3,0.01);
    fxn1->SetParLimits(0,0,0.1);
    fxn1->SetParLimits(1,muParLimLow,muParLimHigh);
    fxn1->SetParLimits(2,sigmaParMin,sigmaParMax);
    fxn1->SetParLimits(3,0,0.1);
    h1_y->Fit(fxn1,fitOptionString,"M W L",fitLow,fitHigh);
    //h1_y->Fit("landau");
    // mu1 = fxn1->GetParameter(1);
    // emu1 = fxn1->GetParError(1);
    mu1 = maxBinVal_1;
    emu1 = TMath::Sqrt(mu1*mu1 / (1.*h1_y->GetEffectiveEntries()) );
    // sig1 = fxn1->GetParameter(2);
    // esig1 = fxn1->GetParError(2);
    sig1 = initStdDev_1;
    esig1 = TMath::Sqrt(sig1*sig1 / (1.*h1_y->GetEffectiveEntries()) );



    fxn2->SetParameter(0,0.04);
    fxn2->SetParameter(1,maxBinVal_2);
    fxn2->SetParameter(2,initStdDev_2);
    fxn2->SetParameter(3,0.01);
    fxn2->SetParLimits(0,0,0.1);
    fxn2->SetParLimits(1,muParLimLow,muParLimHigh);
    fxn2->SetParLimits(2,sigmaParMin,sigmaParMax);
    fxn1->SetParLimits(3,0,0.1);
    h2_y->Fit(fxn2,fitOptionString,"",fitLow,fitHigh);
    // mu2 = fxn2->GetParameter(1);
    // emu2 = fxn2->GetParError(1);
    mu2 = maxBinVal_2;
    emu2 = TMath::Sqrt(mu2*mu2 / (1.*h2_y->GetEffectiveEntries()) );
    // sig2 = fxn2->GetParameter(2);
    // esig2 = fxn2->GetParError(2);
    sig2 = initStdDev_2;
    esig2 = TMath::Sqrt(sig2*sig2 / (2.*h2_y->GetEffectiveEntries()) );

    fxn3->SetParameter(0,0.04);
    fxn3->SetParameter(1,maxBinVal_3);
    fxn3->SetParameter(2,initStdDev_3);
    fxn3->SetParameter(3,0.01);
    fxn3->SetParLimits(0,0,0.1);
    fxn3->SetParLimits(1,muParLimLow,muParLimHigh);
    fxn3->SetParLimits(2,sigmaParMin,sigmaParMax);
    fxn1->SetParLimits(3,0,0.1);
    h3_y->Fit(fxn3,fitOptionString,"",fitLow,fitHigh);
    // mu3 = fxn3->GetParameter(1);
    // emu3 = fxn3->GetParError(1);
    mu3 = maxBinVal_3;
    emu3 = TMath::Sqrt(mu3*mu3 / (1.*h3_y->GetEffectiveEntries()) );
    // sig3 = fxn3->GetParameter(2);
    // esig3 = fxn3->GetParError(2);
    sig3 = initStdDev_3;
    esig3 = TMath::Sqrt(sig3*sig3 / (2.*h3_y->GetEffectiveEntries()) );

    fxn4->SetParameter(0,0.04);
    fxn4->SetParameter(1,maxBinVal_4);
    fxn4->SetParameter(2,initStdDev_4);
    fxn4->SetParameter(3,0.01);
    fxn4->SetParLimits(0,0,0.1);
    fxn4->SetParLimits(1,muParLimLow,muParLimHigh);
    fxn4->SetParLimits(2,sigmaParMin,sigmaParMax);
    fxn1->SetParLimits(3,0,0.1);
    h4_y->Fit(fxn4,fitOptionString,"",fitLow,fitHigh);
    // mu4 = fxn4->GetParameter(1);
    // emu4 = fxn4->GetParError(1);
    mu4 = maxBinVal_4;
    emu4 = TMath::Sqrt(mu4*mu4 / (1.*h4_y->GetEffectiveEntries()) );
    sig4 = initStdDev_4;
    esig4 = TMath::Sqrt(sig4*sig4 / (2.*h4_y->GetEffectiveEntries()) );
    

    fxn5->SetParameter(0,0.04);
    fxn5->SetParameter(1,maxBinVal_5);
    fxn5->SetParameter(2,initStdDev_5);
    fxn5->SetParameter(3,0.01);
    fxn5->SetParLimits(0,0,0.1);
    fxn5->SetParLimits(1,muParLimLow,muParLimHigh);
    fxn5->SetParLimits(2,sigmaParMin,sigmaParMax);
    fxn1->SetParLimits(3,0,0.1);
    h5_y->Fit(fxn5,fitOptionString,"",fitLow,fitHigh);
    // mu5 = fxn5->GetParameter(1);
    // emu5 = fxn5->GetParError(1);
    mu5 = maxBinVal_5;
    emu5 = TMath::Sqrt(mu5*mu5 / (1.*h5_y->GetEffectiveEntries()) );
    // sig5 = fxn5->GetParameter(2);
    // esig5 = fxn5->GetParError(2);
    // cout << "sigma_c(" << i << ") = " << sig5 << " +/- " << esig5 << endl;
    sig5 = initStdDev_5;
    esig5 = TMath::Sqrt(sig5*sig5 / (2.*h5_y->GetEffectiveEntries()) );
    

    fxn6->SetParameter(0,0.04);
    fxn6->SetParameter(1,maxBinVal_6);
    fxn6->SetParameter(2,initStdDev_6);
    fxn6->SetParameter(3,0.01);
    fxn6->SetParLimits(0,0,0.1);
    fxn6->SetParLimits(1,muParLimLow,muParLimHigh);
    fxn6->SetParLimits(2,sigmaParMin,sigmaParMax);
    fxn1->SetParLimits(3,0,0.1);
    h6_y->Fit(fxn6,fitOptionString,"",fitLow,fitHigh);
    // mu6 = fxn6->GetParameter(1);
    // emu6 = fxn6->GetParError(1);
    mu6 = maxBinVal_6;
    emu6 = TMath::Sqrt(mu6*mu6 / (1.*h6_y->GetEffectiveEntries()) );
    // sig6 = fxn6->GetParameter(2);
    // esig6 = fxn6->GetParError(2);
    sig6 = initStdDev_6;
    esig6 = TMath::Sqrt(sig6*sig6 / (2.*h6_y->GetEffectiveEntries()) );

    fxn7->SetParameter(0,0.04);    
    fxn7->SetParameter(1,maxBinVal_7);
    fxn7->SetParameter(2,initStdDev_7);
    fxn7->SetParameter(3,0.01);
    fxn7->SetParLimits(0,0,0.1);
    //fxn7->SetParameter(1,0.94);
    //fxn7->SetParameter(2,0.1397);
    fxn7->SetParLimits(1,muParLimLow,muParLimHigh);
    fxn7->SetParLimits(2,sigmaParMin,sigmaParMax);
    fxn1->SetParLimits(3,0,0.1);
    // fxn7->SetParameter(3,0.15);
    // fxn7->SetParameter(4,1.002);
    // fxn7->SetParameter(5,0.152);
    //fxn7->SetParLimits(3,0,1000);
    //fxn7->SetParLimits(3,0.9*maxBinVal_7,1.1*maxBinVal_7);
    //fxn7->SetParLimits(4,0.5*initStdDev_7,1.5*initStdDev_7);

    h7_y->Fit(fxn7,fitOptionString,"",fitLow,fitHigh);
    //h7_y->Fit(fxn7,fitOptionString,"",0,0.9);
    // mu7 = fxn7->GetParameter(1);
    // emu7 = fxn7->GetParError(1);
    mu7 = maxBinVal_7;
    emu7 = TMath::Sqrt(mu7*mu7 / (1.*h7_y->GetEffectiveEntries()) );
    // sig7 = fxn7->GetParameter(2);
    // esig7 = fxn7->GetParError(2);
    sig7 = initStdDev_7;
    esig7 = TMath::Sqrt(sig7*sig7 / (2.*h7_y->GetEffectiveEntries()) );
    
    
    la->SetTextFont(42);
    la->SetTextSize(0.04);
    TString system_string = "";
    if(ispp) system_string = "#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}          PYTHIA (5.02 TeV)}";
    else system_string =     "#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}   PYTHIA+HYDJET (5.02 TeV)}";
    
    h7_y->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} / #it{p}_{T}^{genJet}");
    h7_y->GetYaxis()->SetTitle("Weighted entries");
    h7_y->SetStats(0);
    h7_y->SetTitle("");
    h7_y->GetXaxis()->SetRangeUser(0,2);
    //h7_y->GetYaxis()->SetRangeUser(0,0.04);
    h7_y->Draw();
    la->DrawLatexNDC(0.22,0.92,system_string);
    la->SetTextSize(0.037);
    la->DrawLatexNDC(0.65,0.6,Form("#it{#mu} = %3.3f",fxn7->GetParameter(1)));
    la->DrawLatexNDC(0.65,0.53,Form("#it{#sigma} = %3.3f",fxn7->GetParameter(2)));
    la->DrawLatexNDC(0.65,0.46,Form("#it{a}_{#it{G}} = %3.3f",fxn7->GetParameter(0)));
    la->DrawLatexNDC(0.65,0.39,Form("#it{a}_{#it{L}} = %3.3f",fxn7->GetParameter(3)));
    la->DrawLatexNDC(0.65,0.32,Form("std. dev. = %3.3f",initStdDev_7));
    la->DrawLatexNDC(0.3,0.85,Form("%3.0f < #it{p}_{T}^{genJet} (GeV) < %3.0f, #it{b}-jets",pt_axis[i],pt_axis[i+1]));
    fxn7->SetLineColor(kRed-4);
    fxn7->Draw("same");
    TF1 *fxn7_gaus = new TF1("fxn7_gaus","[0]*TMath::Gaus(x,[1],[2])",0,5);
    TF1 *fxn7_landau = new TF1("fxn7_landau","[0]*TMath::Landau(-x,-[1],[2])",0,5);
    fxn7_gaus->SetParameter(0,fxn7->GetParameter(0));
    fxn7_gaus->SetParameter(1,fxn7->GetParameter(1));
    fxn7_gaus->SetParameter(2,fxn7->GetParameter(2));
    fxn7_landau->SetParameter(0,fxn7->GetParameter(3));
    fxn7_landau->SetParameter(1,fxn7->GetParameter(1));
    fxn7_landau->SetParameter(2,fxn7->GetParameter(2));
    fxn7_gaus->SetLineColor(kBlue-4);
    fxn7_landau->SetLineColor(kGreen+2);
    fxn7_gaus->SetLineStyle(7);
    fxn7_landau->SetLineStyle(7);
    fxn7_gaus->Draw("same");
    fxn7_landau->Draw("same");
    //h7_y->SetTitle(Form("%3.0f < p_{T}^{genJet} < %3.0f, bJets",pt_axis[i],pt_axis[i+1]));
    //h7_y->SetTitle(Form("%3.0f < p_{T}^{recoJet} < %3.0f, bJets",pt_axis[i],pt_axis[i+1]));
    ctmp->SaveAs(Form("tmp/bJets/tmp_%3.0f_%3.0f.pdf",pt_axis[i],pt_axis[i+1]));


    // h1_y->GetXaxis()->SetTitle("p_{T}^{recoJet} / p_{T}^{genJet}");
    // h1_y->GetYaxis()->SetTitle("Weighted entries");
    // h1_y->Draw();
    // fxn1->SetLineColor(kRed);
    // fxn1->Draw("same");
    // TF1 *fxn1_gaus = new TF1("fxn1_gaus","[0]*TMath::Gaus(x,[1],[2])",0,5);
    // TF1 *fxn1_landau = new TF1("fxn1_landau","[0]*TMath::Landau(-x,-[1],[2])",0,5);
    // //TF1 *fxn1_landau = new TF1("fxn1_landau","[0]*TMath::Landau(x,[1],[2])",0,5);
    // TF1 *fxn1_product = new TF1("fxn1_landau","[0]*TMath::Gaus(x,[1],[2])*[3]*TMath::Landau(-x,-[4],[5])",0,5);
    // fxn1_gaus->SetParameter(0,fxn1->GetParameter(0));
    // fxn1_gaus->SetParameter(1,fxn1->GetParameter(1));
    // fxn1_gaus->SetParameter(2,fxn1->GetParameter(2));
    // fxn1_landau->SetParameter(0,fxn1->GetParameter(3));
    // fxn1_landau->SetParameter(1,fxn1->GetParameter(1));
    // fxn1_landau->SetParameter(2,fxn1->GetParameter(2));
    // fxn1_gaus->SetLineColor(kBlue-4);
    // fxn1_landau->SetLineColor(kGreen+2);
    // fxn1_product->SetLineColor(kMagenta);
    // fxn1_gaus->SetLineStyle(7);
    // fxn1_landau->SetLineStyle(7);
    // fxn1_product->SetLineStyle(7);
    // fxn1_gaus->Draw("same");
    // fxn1_landau->Draw("same");
    // h1_y->SetTitle(Form("%3.0f < p_{T}^{recoJet} < %3.0f, allJets",pt_axis[i],pt_axis[i+1]));
    // ctmp->SaveAs(Form("tmp/allJets/tmp_%3.0f_%3.0f.pdf",pt_axis[i],pt_axis[i+1]));


               
    M1[i] = mu1;
    eM1[i] = emu1; 
    M2[i] = mu2;
    eM2[i] = emu2; 
    M3[i] = mu3;
    eM3[i] = emu3; 
    M4[i] = mu4;
    eM4[i] = emu4; 
    M5[i] = mu5;
    eM5[i] = emu5;
    M6[i] = mu6;
    eM6[i] = emu6;
    M7[i] = mu7;
    eM7[i] = emu7;

    if(i==2) cout << mu3;
        

    S1[i] = sig1;
    eS1[i] = esig1;
    S2[i] = sig2;
    eS2[i] = esig2;
    S3[i] = sig3;
    eS3[i] = esig3;
    S4[i] = sig4;
    eS4[i] = esig4;
    S5[i] = sig5;
    eS5[i] = esig5;
    S6[i] = sig6;
    eS6[i] = esig6;
    S7[i] = sig7;
    eS7[i] = esig7;
        



  }

  double markerSize = 1.5;

  TGraphErrors *gr1 = new TGraphErrors(Nbins-1,x,M1,ept_axis,eM1);
    
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerColor(kBlack);
  gr1->SetLineColor(kBlack);
  //gr1->SetLineStyle(2);
  gr1->SetMarkerSize(markerSize);







  TGraphErrors *gr2 = new TGraphErrors(Nbins-1,x,M2,ept_axis,eM2);
    
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerColor(kBlue-4);
  gr2->SetLineColor(kBlue-4);
  gr2->SetMarkerSize(markerSize);

  TGraphErrors *gr3 = new TGraphErrors(Nbins-1,x,M3,ept_axis,eM3);
    
  gr3->SetMarkerStyle(46);
  gr3->SetMarkerColor(kMagenta);
  gr3->SetLineColor(kMagenta);
  gr3->SetMarkerSize(markerSize);

  TGraphErrors *gr4 = new TGraphErrors(Nbins-1,x,M4,ept_axis,eM4);
    
  gr4->SetMarkerStyle(21);
  gr4->SetMarkerColor(kOrange);
  gr4->SetLineColor(kOrange);
  gr4->SetMarkerSize(markerSize);

  TGraphErrors *gr5 = new TGraphErrors(Nbins-1,x,M5,ept_axis,eM5);
    
  gr5->SetMarkerStyle(28);
  gr5->SetMarkerColor(kGreen+2);
  gr5->SetLineColor(kGreen+2);
  gr5->SetMarkerSize(markerSize);

  TGraphErrors *gr6 = new TGraphErrors(Nbins-1,x,M6,ept_axis,eM6);
    
  gr6->SetMarkerStyle(23);
  gr6->SetMarkerColor(kRed-4);
  gr6->SetLineColor(kRed-4);
  gr6->SetMarkerSize(markerSize);

  TGraphErrors *gr7 = new TGraphErrors(Nbins-1,x,M7,ept_axis,eM7);
    
  gr7->SetMarkerStyle(23);
  gr7->SetMarkerColor(kRed-4);
  gr7->SetLineColor(kRed-4);
  gr7->SetMarkerSize(markerSize);

  for(int k = 0; k < Nbins; k++){
    cout << "gr6(" << k << ") = " << gr6->GetPointY(k) << " +/- " << gr6->GetErrorY(k) << endl;
  }


    

  TGraphErrors *Gr1 = new TGraphErrors(Nbins-1,x,S1,ept_axis,eS1);
    
  Gr1->SetMarkerStyle(20);
  Gr1->SetMarkerColor(kBlack);
  Gr1->SetLineColor(kBlack);
  //Gr1->SetLineStyle(2);
  Gr1->SetMarkerSize(markerSize);



  TH1D *h_fit = new TH1D("h_fit","h_fit",Nbins-1,x);

  // make histogram representation
  for(int k = 0; k < Nbins; k++){
    
    h_fit->SetBinContent(k,Gr1->GetPointY(k));
    h_fit->SetBinError(k,Gr1->GetErrorY(k));
    //h_fit->SetBinCenter(k,Gr1->GetPointX(k));
    cout << "h_fit(" << k << ") = " << Gr1->GetPointY(k) << " +/- " << Gr1->GetErrorY(k) << endl;

  }





  TGraphErrors *Gr2 = new TGraphErrors(Nbins-1,x,S2,ept_axis,eS2);
    
  Gr2->SetMarkerStyle(20);
  Gr2->SetMarkerColor(kBlue-4);
  Gr2->SetLineColor(kBlue-4);
  Gr2->SetMarkerSize(markerSize);

  TGraphErrors *Gr3 = new TGraphErrors(Nbins-1,x,S3,ept_axis,eS3);
    
  Gr3->SetMarkerStyle(46);
  Gr3->SetMarkerColor(kMagenta);
  Gr3->SetLineColor(kMagenta);
  Gr3->SetMarkerSize(markerSize);

  TGraphErrors *Gr4 = new TGraphErrors(Nbins-1,x,S4,ept_axis,eS4);
    
  Gr4->SetMarkerStyle(21);
  Gr4->SetMarkerColor(kOrange);
  Gr4->SetLineColor(kOrange);
  Gr4->SetMarkerSize(markerSize);

  TGraphErrors *Gr5 = new TGraphErrors(Nbins-1,x,S5,ept_axis,eS5);
    
  Gr5->SetMarkerStyle(28);
  Gr5->SetMarkerColor(kGreen+2);
  Gr5->SetLineColor(kGreen+2);
  Gr5->SetMarkerSize(markerSize);

  TGraphErrors *Gr6 = new TGraphErrors(Nbins-1,x,S6,ept_axis,eS6);
    
  Gr6->SetMarkerStyle(23);
  Gr6->SetMarkerColor(kRed-4);
  Gr6->SetLineColor(kRed-4);
  Gr6->SetMarkerSize(markerSize);

  TGraphErrors *Gr7 = new TGraphErrors(Nbins-1,x,S7,ept_axis,eS7);
    
  Gr7->SetMarkerStyle(23);
  Gr7->SetMarkerColor(kRed-4);
  Gr7->SetLineColor(kRed-4);
  Gr7->SetMarkerSize(markerSize);

  for(int k = 0; k < Nbins; k++){
    cout << "Gr7(" << k << ") = " << Gr7->GetPointY(k) << " +/- " << Gr7->GetErrorY(k) << endl;
  }

  // Gr6->SetMarkerStyle(24);
  // Gr6->SetMarkerColor(kGreen);
  // Gr6->SetLineColor(kGreen);
  // Gr6->SetMarkerSize(markerSize);




  TCanvas *c1 = new TCanvas("c1","c1",500,500);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0,1,1);
  p1->SetLeftMargin(0.2);
  p1->SetBottomMargin(0.15);
  p1->Draw();
  p1->cd();
  TMultiGraph  *mg  = new TMultiGraph();
  
  mg->Add(gr1,"p");
  
  //mg->Add(gr4,"p");
  //mg->Add(gr2,"p");
  // mg->Add(gr3,"p");
  // mg->Add(gr5,"p");
  // //mg->Add(gr6,"p");
  mg->Add(gr7,"p");

  double labelSize = 0.045;
  double titleSize = 0.055;
  int NdivVal = 508;

  //mg->GetYaxis()->SetRangeUser(0.68,1.32);
  //mg->GetYaxis()->SetRangeUser(0.68,1.62);
  mg->GetYaxis()->SetRangeUser(0.0,3.0);
  mg->GetXaxis()->SetRangeUser(0,500);
  mg->GetYaxis()->SetTitle("#mu [#font[52]{p}_{T}^{rel}(reco,reco) / #font[52]{p}_{T}^{rel}(gen,gen)]");
  mg->GetXaxis()->SetTitle("#font[52]{p}_{T}^{rel}(gen,gen) [GeV]");
  //mg->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  mg->GetXaxis()->SetLabelSize(labelSize);
  mg->GetXaxis()->SetTitleSize(titleSize);
  mg->GetYaxis()->SetLabelSize(labelSize);
  mg->GetYaxis()->SetTitleSize(titleSize);
  mg->GetXaxis()->SetTitleFont(42);
  mg->GetXaxis()->SetLabelFont(42);
  mg->GetYaxis()->SetTitleFont(42);
  mg->GetYaxis()->SetLabelFont(42);
  mg->GetYaxis()->SetNdivisions(NdivVal);
  mg->GetXaxis()->SetNdivisions(NdivVal);

  TLegend *l = new TLegend(0.64,0.22,0.89,0.44);
  l->SetBorderSize(0);
  l->SetTextFont(42);
  l->SetTextSize(0.036);
  l->SetFillStyle(0);
  l->AddEntry(gr1,"#it{#mu}-tagged jets","p");
  //l->AddEntry(gr1,"incl. jets","p");
  //l->AddEntry(gr1,"jets with added muon","l");
  //l->AddEntry(gr2,"quark jets","p");
  //l->AddEntry(gr2,"#font[52]{udsg}-jets","p");
  // //l->AddEntry(gr3,"#font[52]{s} jets","p");
  // l->AddEntry(gr4,"#font[52]{g} jets","p");
  // l->AddEntry(gr5,"#font[52]{c} jets","p");
  // //l->AddEntry(gr6,"#font[52]{b} jets","p");
  l->AddEntry(gr7,"#font[52]{b}-jets","p");

  TF1 *fitty = new TF1("fitty","[0] + [1]*x", 40, 500);
  //TF1 *fitty = new TF1("fitty","[0] + [1]*x", 40, 500);
  fitty->SetParameter(0, 0.852983);
  fitty->SetParameter(1, 0.00114738);
  //fitty->SetParameter(2, 8.03928e-06);
  //fitty->SetParameter(3, -2.01078e-08);
  //fitty->SetParameter(4,  0);
  //gr6->Fit("fitty", "M W L R");
  //gr6->Fit("fitty", "M L R");
  //fitty->SetParameter(0, 0.9);
  //fitty->SetParameter(1, 0.000124609);
  //gr1->Fit("fitty", "R");

  
  // h_fit_i->Draw();
  // h_fit_b->Draw("same");
  // h_fit_i->Fit("pol2","W M");
  // h_fit_b->Fit("pol2","W M");

  //TFile *fit_file = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/fits/muTagged.root","recreate");
  // TFile *fit_file = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/fits/inclusive.root","recreate");
  // h_fit_i->Write();
  // h_fit_b->Write();
  // fit_file->Close();
  


  
 
  
  double x_t1 = 0.43;
  double y_t1 = 0.92;
  double y_t2 = 0.85;
  double y_t3 = 0.79;
  double y_t4 = 0.73;
  double y_t5 = 0.67;

  //mg->GetListOfGraphs()->At(0)->Draw("L");
  //mg->GetListOfGraphs()->At(1)->Draw("P");
  //mg->GetListOfGraphs()->At(2)->Draw("P");
  mg->Draw("a");
  //mg->Draw("al");
  l->Draw();
  

  TLine *line = new TLine(pt_axis[0],1,pt_axis[Nbins-1],1);
  line->SetLineStyle(7);
  line->Draw();

  



  TLatex *t1 = new TLatex();
  t1->SetTextFont(42);
  t1->SetTextSize(0.037);
  //t1->DrawLatexNDC(x_t1-0.02,y_t1,"Jet energy scale");
  t1->SetTextSize(0.04);
     
  if(!ispp){
    if(isC1) t1->DrawLatexNDC(x_t1,y_t2,"PYTHIA+HYDJET 0-10%");
    else if(isC2) t1->DrawLatexNDC(x_t1,y_t2,"PYTHIA+HYDJET 10-30%");
    else if(isC3) t1->DrawLatexNDC(x_t1,y_t2,"PYTHIA+HYDJET 30-90%");
    //else if(isC4) t1->DrawLatexNDC(x_t1,y_t2,"PYTHIA+HYDJET 50-90%");
  }
  else t1->DrawLatexNDC(x_t1,y_t2,"PYTHIA");

  TString jetPtString = "";
  if(isJ1) jetPtString = "80 < #it{p}_{T}^{jet} (GeV) < 100";
  else if(isJ2) jetPtString = "100 < #it{p}_{T}^{jet} (GeV) < 120";
  else if(isJ3) jetPtString = "120 < #it{p}_{T}^{jet} (GeV) < 150";
  else{};

  t1->DrawLatexNDC(x_t1,y_t3,"#it{#mu}-tagged jets, |#eta^{jet}| < 1.6");
  t1->DrawLatexNDC(x_t1,y_t4,jetPtString);
  //t1->DrawLatexNDC(x_t1,y_t3,"inclusive jets, |#eta^{jet}| < 1.6");
  //t1->DrawLatexNDC(x_t1,y_t4,"9 < #font[52]{p}_{T}^{#mu} < 14 GeV, |#eta^{#mu}| < 2.0");
  t1->DrawLatexNDC(x_t1,y_t5,"#font[52]{p}_{T}^{#mu} > 14 GeV, |#eta^{#mu}| < 2.0");
  
   
  //c1->SaveAs("/home/clayton/Documents/nuclear/GroupMeeting/figures/01-31-23/JES-bJet.pdf");
    
  for(int i = 0; i < Nbins; i++){
    double bin_i_i = gr1->GetPointY(i);
    double err_i_i = gr1->GetErrorY(i);
    double bin_i_b = gr7->GetPointY(i);
    double err_i_b = gr7->GetErrorY(i);
    h_fit_i->SetBinContent(i+1,bin_i_i);
    h_fit_i->SetBinError(i+1,err_i_i);
    h_fit_b->SetBinContent(i+1,bin_i_b);
    h_fit_b->SetBinError(i+1,err_i_b);
  }

  TCanvas *canv_fit_test = new TCanvas("canv_fit_test", "canv_fit_test", 700,700);
  canv_fit_test->cd();
  h_fit_i->SetTitle("Fits to JES curves");
  h_fit_i->SetStats(0);
  h_fit_i->GetYaxis()->SetRangeUser(0.8,1.2);
  h_fit_i->SetLineColor(kBlack);
  h_fit_b->SetLineColor(kRed-4);
  h_fit_i->Fit("pol2");
  h_fit_b->Fit("pol2");
  h_fit_i->Draw();
  h_fit_b->Draw("same");
  
    
    
  TCanvas *c2 = new TCanvas("c2","c2",500,500);
  c2->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,1);
  p2->SetLeftMargin(0.2);
  p2->SetBottomMargin(0.15);
  p2->Draw();
  p2->cd();
  TMultiGraph  *mg2  = new TMultiGraph();
  
  mg2->Add(Gr1,"p");
  
  // mg2->Add(Gr4,"p");
  //mg2->Add(Gr2,"p");
  // //mg2->Add(Gr3,"p");
  // mg2->Add(Gr5,"p");
  // //mg2->Add(Gr6,"p");
  mg2->Add(Gr7,"p");

  //mg2->GetYaxis()->SetRangeUser(0,0.54);
  mg2->GetYaxis()->SetRangeUser(0,1.5);
  mg2->GetXaxis()->SetRangeUser(0,500);
  mg2->GetYaxis()->SetTitle("#sigma [#font[52]{p}_{T}^{rel}(reco,reco) / #font[52]{p}_{T}^{rel}(gen,gen)]");
  mg2->GetXaxis()->SetTitle("#font[52]{p}_{T}^{rel}(gen,gen) [GeV]");
  //mg2->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  mg2->GetXaxis()->SetLabelSize(labelSize);
  mg2->GetXaxis()->SetTitleSize(titleSize);
  mg2->GetYaxis()->SetLabelSize(labelSize);
  mg2->GetYaxis()->SetTitleSize(titleSize);
  mg2->GetXaxis()->SetTitleFont(42);
  mg2->GetXaxis()->SetLabelFont(42);
  mg2->GetYaxis()->SetTitleFont(42);
  mg2->GetYaxis()->SetLabelFont(42);
  mg2->GetYaxis()->SetNdivisions(NdivVal);
  mg2->GetXaxis()->SetNdivisions(NdivVal);
    
  mg2->Draw("al");
  //l->Draw();
    
   
 

  // t1->DrawLatexNDC(x_t1-0.02,y_t1,"Jet energy resolution");
   
  t1->SetTextSize(0.04);
 
  if(!ispp){
    if(isC1) t1->DrawLatexNDC(x_t1,y_t2,"PYTHIA+HYDJET 0-10%");
    else if(isC2) t1->DrawLatexNDC(x_t1,y_t2,"PYTHIA+HYDJET 10-30%");
    else if(isC3) t1->DrawLatexNDC(x_t1,y_t2,"PYTHIA+HYDJET 30-90%");
    //else if(isC4) t1->DrawLatexNDC(x_t1,y_t2,"PYTHIA+HYDJET 50-90%");
  }
  else t1->DrawLatexNDC(x_t1,y_t2,"PYTHIA");
  //t1->DrawLatexNDC(x_t1,y_t3,"|#eta^{jet}| < 1.6");
  t1->DrawLatexNDC(x_t1,y_t3,"#it{#mu}-tagged jets, |#eta^{jet}| < 1.6");
  t1->DrawLatexNDC(x_t1,y_t4,jetPtString);
  //t1->DrawLatexNDC(x_t1,y_t3,"inclusive jets, |#eta^{jet}| < 1.6");
  //t1->DrawLatexNDC(x_t1,y_t4,"#font[52]{p}_{T}^{#mu} > 7 GeV, |#eta^{#mu}| < 2.0");
  t1->DrawLatexNDC(x_t1,y_t5,"#font[52]{p}_{T}^{#mu} > 14 GeV, |#eta^{#mu}| < 2.0");


  
  TH1D *JER_result_b = new TH1D("JER_result_b","JER_result_b",Nbins-1,pt_axis);
  TH1D *JES_result_b = new TH1D("JES_result_b","JES_result_b",Nbins-1,pt_axis);
  TH1D *JER_result_i = new TH1D("JER_result_i","JER_result_i",Nbins-1,pt_axis);
  TH1D *JES_result_i = new TH1D("JES_result_i","JES_result_i",Nbins-1,pt_axis);

  for(int i = 0; i < Nbins; i++){

    if(i == 0){
      JER_result_b->SetBinContent(i,0.0);
      JER_result_b->SetBinError(i,0.0);
      JES_result_b->SetBinContent(i,0.0);
      JES_result_b->SetBinError(i,0.0);
      JER_result_i->SetBinContent(i,0.0);
      JER_result_i->SetBinError(i,0.0);
      JES_result_i->SetBinContent(i,0.0);
      JES_result_i->SetBinError(i,0.0);
    }
    else{
      JER_result_b->SetBinContent(i,S6[i-1]); // 6 = bJets
      JER_result_b->SetBinError(i,eS6[i-1]);
      JES_result_b->SetBinContent(i,M6[i-1]);
      JES_result_b->SetBinError(i,eM6[i-1]);
      JER_result_i->SetBinContent(i,S1[i-1]); // 1 = allJets
      JER_result_i->SetBinError(i,eS1[i-1]);
      JES_result_i->SetBinContent(i,M1[i-1]);
      JES_result_i->SetBinError(i,eM1[i-1]);
    }
    //cout << "JER_result[" << i << "] = " << JER_result->GetBinContent(i) << " | x[" << i << "] = " << x[i] << endl;
    //cout << "JES_result[" << i << "] = " << JES_result->GetBinContent(i) << " | x[" << i << "] = " << x[i] << endl;

  }

  TH1D *JES_bi_ratio = (TH1D*) JES_result_b->Clone("JES_bi_ratio");
  JES_bi_ratio->Divide(JES_result_b,JES_result_i,1,1,"");

  
  


  
  // TCanvas *c_test = new TCanvas("c_test","test canvas",700,700);
  // c_test->cd();
  // TPad *p_test = new TPad("p_test","p_test",0,0,1,1);
  // p_test->SetLeftMargin(0.2);
  // p_test->SetBottomMargin(0.2);
  // p_test->Draw();
  // p_test->cd();
  // //Gr1->Draw();
  // JES_bi_ratio->SetStats(0);
  // JES_bi_ratio->SetTitle("");
  // JES_bi_ratio->GetXaxis()->SetTitle("#font[52]{p}_{T}^{genJet} [GeV]");
  // JES_bi_ratio->GetYaxis()->SetTitle("JES(#font[52]{b}-jets) / JES(incl.-jets)");
  // JES_bi_ratio->GetYaxis()->SetRangeUser(0.9,1.0);
  // JES_bi_ratio->Draw();

  TF1 *func = new TF1("func",JES_fit,0.,5.,3);
  //Gr1->Fit(func,"M R WL","",0.0,5.0);
  // func->SetParameter(0,0.0049454);
  // func->SetParameter(1,1.34148);
  // func->SetParameter(2,2.89153);
  //Gr6->Fit(func,"M R WL","",60.0,500.0);
  l->Draw();
  
  
  
  
  TFile *JER_result_file = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_JERCorr.root","recreate");

  JER_result_b->Write();
  JER_result_i->Write();

  JER_result_file->Close();




  TFile *JES_result_file = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_JERCorr.root","recreate");
  
  JES_result_b->Write();
  JES_result_i->Write();
  
  JES_result_file->Close();

  
    
    
  if(ispp){
    c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muptrel/response_mu_%s.pdf",JString.Data()));
    c2->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muptrel/response_sigma_%s.pdf",JString.Data()));
  }
  else if(isC3){
    c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muptrel/response_mu_C3%s.pdf",JString.Data()));
    c2->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muptrel/response_sigma_C3%s.pdf",JString.Data()));    
  }
  else if(isC2){
    c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muptrel/response_mu_C2%s.pdf",JString.Data()));
    c2->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muptrel/response_sigma_C2%s.pdf",JString.Data()));
  }
  else if(isC1){
    c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muptrel/response_mu_C1%s.pdf",JString.Data()));
    c2->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muptrel/response_sigma_C1%s.pdf",JString.Data()));
  }
  else{};


}
